#include "DolphinDB.h"
#include "Util.h"
#include "Streaming.h"

#include "kcomm.h"

using namespace dolphindb; 
using namespace std; 

#define PIPE_CAPACITY 65536
#define b9
#define d9
ZI run=0,p[2];ZC b[2*PIPE_CAPACITY];

#if defined(WIN32)||defined(WIN64)
#include <process.h>
ZI pipe(I*p){R !CreatePipe((PHANDLE)p+0,(PHANDLE)p+1,0,0);}
ZI dwBytes;
#define read(x,y,z) ReadFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL) 
#define write(x,y,z) WriteFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL); 
#define close(x) CloseHandle((HANDLE)x)
Z CRITICAL_SECTION g_CS;
#define INITLOCK InitializeCriticalSection(&g_CS)
#define FREELOCK DeleteCriticalSection(&g_CS)
#define LOCK EnterCriticalSection(&g_CS)
#define UNLOCK LeaveCriticalSection(&g_CS)
#else
Z pthread_mutex_t g_mutex=PTHREAD_MUTEX_INITIALIZER;
#define INITLOCK 
#define FREELOCK 
#define LOCK pthread_mutex_lock(&g_mutex)
#define UNLOCK pthread_mutex_unlock(&g_mutex)
#endif

Z std::queue<K> mq;

ZK onmq(I i){
  K L=knk(0);
  //O("onmq:%d\n",i);

  read(i,&b,PIPE_CAPACITY);

  LOCK;
  while (!mq.empty()){
    jk(&L,d9(mq.front()));
    mq.pop();
  }
  UNLOCK;

  k(0,"onddb",L,(K)0);
  R ki(0);
}

Z V mpub(K x){
  //O("mpub:%d\n",0);
  LOCK;
  mq.push(b9(1,x));
  UNLOCK;    
  write(p[1],&b,1);
};

ZK d2q(ConstantSP v){
  DATA_FORM f=v->getForm();
  DATA_TYPE t=v->getType(),t1=v->getRawType();
  INDEX n=v->size(),m=v->columns();
  ConstantSP v1;
  K z,L,L1;
    
  //O("form=%d,type=%d,rawtype=%d,size=%d\n",f,t,t1,n);
    
  switch(f){
  case DF_SCALAR:
    {
      switch(t){
      case DT_VOID:{z=ka(101);z->g=0;R z;};
      case DT_BOOL:R kb(v->getBool());
      case DT_CHAR:R kc(v->getChar());
      case DT_SHORT:R kh(v->getShort());
      case DT_SYMBOL:
      case DT_INT:R ki(v->getInt());
      case DT_LONG:R kj(v->getLong());
      case DT_FLOAT:R ke(v->getFloat());
      case DT_DOUBLE:R kf(v->getDouble());
      case DT_STRING:R kpn((S)v->getString().c_str(),v->getString().length());
      case DT_DATE:R kd(v->getInt()-10957);
      case DT_TIME:R kt(v->getInt());
      case DT_NANOTIME:R ktj(-KN,v->getLong());
      case DT_NANOTIMESTAMP:R ktj(-KP,v->getLong()-10957*24*3600*1000000000l);
      default:O("[d2q]type(%d)not match\n",t);    
      }
      break;
    }
  case DF_VECTOR:
  case DF_PAIR:
    {
      switch(t){
      case DT_VOID:{L=knk(0);DO(n,z=ka(101);z->g=0;jk(&L,z));R L;}
      case DT_BOOL:{L=ktn(KB,n);DO(n,kG(L)[i]=v->getBool(i));R L;}
      case DT_CHAR:{L=ktn(KC,n);DO(n,kC(L)[i]=v->getChar(i));R L;}
      case DT_SHORT:{L=ktn(KH,n);DO(n,kH(L)[i]=v->getShort(i));R L;}
      case DT_SYMBOL:	
      case DT_INT:{L=ktn(KI,n);DO(n,kI(L)[i]=v->getInt(i));R L;}
      case DT_LONG:{L=ktn(KJ,n);DO(n,kJ(L)[i]=v->getLong(i));R L;}
      case DT_FLOAT:{L=ktn(KE,n);DO(n,kE(L)[i]=v->getFloat(i));R L;}
      case DT_DOUBLE:{L=ktn(KF,n);DO(n,kF(L)[i]=v->getDouble(i));R L;}
      case DT_STRING:{L=knk(0);DO(n,jk(&L,kpn((S)v->getString(i).c_str(),v->getString(i).length())));R L;}
      case DT_DATE:{L=ktn(KD,n);DO(n,kI(L)[i]=v->getInt(i)-10957);R L;}
      case DT_TIME:{L=ktn(KT,n);DO(n,kI(L)[i]=v->getInt(i));R L;}
      case DT_NANOTIME:{L=ktn(KN,n);DO(n,kJ(L)[i]=v->getLong(i));R L;}
      case DT_NANOTIMESTAMP:{L=ktn(KP,n);DO(n,kJ(L)[i]=v->getLong(i)-10957*24*3600*1000000000l);R L;}
      case DT_ANY:{L=knk(0);DO(n,jk(&L,d2q(v->get(i))));R L;}
      default:O("[d2q]type(%d)not match\n",t);    
      }
      break;
    }
  case DF_MATRIX:{L=knk(0);DO(m,jk(&L,d2q(v->getColumn(i))));R L;}
  case DF_DICTIONARY:{L=xD(d2q(v->keys()),d2q(v->values()));R L;}
  case DF_TABLE:{v1=v->keys();L1=ktn(KS,m);DO(m,kS(L1)[i]=ss((S)v1->getString(i).c_str()));L=xT(xD(L1,d2q(v->values())));R L;}  
  default:O("[d2q]form(%d)not match\n",f);      
  }
  R K(0);
}

Z DATA_TYPE qt2dt(I x){
  switch(x){
  case -KB:
  case KB:R DT_BOOL;
  case -KG:  
  case -KC:R DT_CHAR;
  case KG:        
  case KC:R DT_STRING;
  case -KH:
  case KH:R DT_SHORT;      
  case -KI:
  case KI:R DT_INT;
  case -KJ:
  case KJ:R DT_LONG;
  case -KE:
  case KE:R DT_FLOAT;
  case -KF:
  case KF:R DT_DOUBLE;
  case -KD:
  case KD:R DT_DATE;
  case -KT:
  case KT:R DT_TIME;
  case -KN:
  case KN:R DT_NANOTIME;
  case -KP:
  case KP:R DT_NANOTIMESTAMP;
  case -KS:
  case KS:R DT_STRING;
    break;
  }
  R DT_ANY;
}
  
Z ConstantSP q2d(K x){
  I t=xt,t0,t1;
  J n=xn,m,j;
  ConstantSP v,D0,D1;
  Dictionary* d;
  K L0,L1;

  //O("[q2d]t=%d,n=%d\n",t,n);
  switch(t){
  case -KB:R Util::createBool(xg);
  case -KG:  
  case -KC:R Util::createChar(xg);
  case -KH:R Util::createShort(xh);
  case -KI:R Util::createInt(xi);
  case -KJ:R Util::createLong(xj);
  case -KE:R Util::createFloat(xe);
  case -KF:R Util::createDouble(xf);
  case -KD:R Util::createDate(xi+10957);
  case -KT:R Util::createTime(xi);
  case -KN:R Util::createNanoTime(xj);
  case -KP:R Util::createNanoTimestamp(xj+10957*24*3600*1000000000l);
  case -KS:R Util::createString(xs);

  case KB:{v=Util::createVector(DT_BOOL,n);v->setBool(0,n,(S)xG);R v;}
  case KG:  
  case KC:{v=Util::createVector(DT_CHAR,n);v->setChar(0,n,(S)xG);R v;} //v=Util::createString(string((S)xG,(S)xG+n));
  case KH:{v=Util::createVector(DT_SHORT,n);v->setShort(0,n,xH);R v;}
  case KI:{v=Util::createVector(DT_INT,n);v->setInt(0,n,xI);R v;}
  case KJ:{v=Util::createVector(DT_LONG,n);v->setLong(0,n,xJ);R v;}
  case KE:{v=Util::createVector(DT_FLOAT,n);v->setFloat(0,n,xE);R v;}
  case KF:{v=Util::createVector(DT_DOUBLE,n);v->setDouble(0,n,xF);R v;}
  case KD:{v=Util::createVector(DT_DATE,n);DO(n,xI[i]+=10957);v->setInt(0,n,xI);DO(n,xI[i]+=10957);R v;}
  case KT:{v=Util::createVector(DT_TIME,n);v->setInt(0,n,xI);R v;}
  case KN:{v=Util::createVector(DT_NANOTIME,n);v->setLong(0,n,xJ);R v;}
  case KP:{v=Util::createVector(DT_NANOTIMESTAMP,n);DO(n,xJ[i]+=10957*24*3600*1000000000l);v->setLong(0,n,xJ);DO(n,xJ[i]-=10957*24*3600*1000000000l);R v;}
  case KS:{v=Util::createVector(DT_STRING,n);v->setString(0,n,xS);R v;}
 
  case XD:{L0=kK(x)[0];L1=kK(x)[1];d=Util::createDictionary(qt2dt(L0->t),qt2dt(L1->t));D0=q2d(L0);D1=q2d(L1);DO(L0->n,d->set(D0->get(i),D1->get(i)));R d;}
  case XT:{vector<string> names;vector<ConstantSP> cols;L0=kK(x->k)[0];L1=kK(x->k)[1];DO(L0->n,names.push_back(kS(L0)[i]);v=q2d(kK(L1)[i]);cols.push_back(v));R Util::createTable(names,cols);}

  case 0:{j=0;DO(n,if(10!=kK(x)[i]->t){j=1;break;});v=Util::createVector(j>0?DT_ANY:DT_STRING,n);DO(n,v->set(i,q2d(xK[i])));R v;}  
  case 101:R Util::createNullConstant(DT_VOID);  
  default:O("[q2d]type(%d)not match\n",t);      
  }	  
  R Util::createNullConstant(DT_VOID);
}

Z MessageHandler onstreaming(string t,string a,Message m){
  //O("======================onddb\n");
  mpub(knk(2,ks("STREAMING"),knk(3,ks((S)t.c_str()),ks((S)a.c_str()),d2q(m))));
  R NULL;
}

#define CONNMAX 128 
#define CLIENTMAX 5

Z vector<DBConnection> c;
ZI CIDX=0;

Z ThreadedClient t[CLIENTMAX]={ThreadedClient(0),ThreadedClient(0),ThreadedClient(0),ThreadedClient(0),ThreadedClient(0)};
ZI TIDX=0;

ZV* sub_thread(V* p){
  K x=(K)p;
  I i=kK(x)[0]->i;
  K y=kK(x)[1];
  S tbl=kK(y)[2]->s;
  S act=kK(y)[3]->s;
  //O("[enter:%d] sub_thread\n",i);
  
  auto cb = [tbl,act](Message m) { onstreaming(string(tbl),string(act),m);};
  
  auto s=t[i].subscribe(kK(y)[0]->s,kK(y)[1]->i,cb,tbl,act,0,true,nullptr,true,false,kK(y)[4]->s,kK(y)[5]->s);
  //O("[sub] sub_thread\n");
  //  sleep(10);
  //  tc->unsubscribe(kK(y)[0]->s,kK(y)[1]->i,kK(y)[2]->s,kK(y)[3]->s);  
  s->join();
  
  //O("[exit] sub_thread\n");
  R 0;
}

ZV* unsub_thread(V* p){
  K x=(K)p;
  I i=kK(x)[0]->i;
  K y=kK(x)[1];
  //O("before unsub[%d]...\n",i);
   t[i].unsubscribe(kK(y)[0]->s,kK(y)[1]->i,kK(y)[2]->s,kK(y)[3]->s);
   //O("unsub...\n");
   R 0;
}

extern "C"{
  K1(ddbinit){
    I f=0;

    if(run) R ki(-10001);

    if(pipe(p)) R ki(-10009);

#if defined(WIN32)||defined(WIN64)
#else
    if(-1==(f = fcntl(p[0],F_GETFL,0)))R ki(-10002);
    f |= O_NONBLOCK;
    if (fcntl(p[0],F_SETFL,f)==-1) R ki(-10003);
#endif

    run++;
    INITLOCK;
    sd1(p[0],onmq);

    R ki(run);
  }

 K1(ddbfree){
    if(!run) R ki(-1);

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
 }
    
  K2(ddbconn){
    if(CIDX>=CONNMAX) R ki(0);
    try{
      c.push_back(DBConnection(false,(0<y->g)?true:false));
      bool r=c[CIDX].connect(kK(x)[0]->s,kK(x)[1]->i,kK(x)[2]->s,kK(x)[3]->s);
      if(r){
	c[CIDX].initialize();
	CIDX++;
	R ki((0<y->g)?-CIDX:CIDX);
      }
    }catch(exception &e){}
    R ki(0);
  }

  K1(ddbdisc){
    I h=abs(xi)-1;
    if(h<0||h>=CIDX) R ki(-1);

    try{
      c[h].close();
    }catch(exception &e){}
      
    R ki(0);
  } 

  K2(ddblogin){
    I h=abs(xi)-1;
    if(h<0||h>=CIDX) R ki(-1);
    
    try{
      c[h].login(kK(y)[0]->s,kK(y)[1]->s,0<kK(y)[2]->g);
    }catch(exception &e){}
    R ki(0);
  }

  K3(ddbrun){
    char buf[BUFLEN];
    ConstantSP v;
    vector<ConstantSP> args;
    I t=z->t;
    J n=z->n;

    I h=abs(xi)-1;
    if(h<0||h>=CIDX) R (K)0;

    try{
      kstrncpy(buf,y,BUFLEN);
      if(0==n){
	v=c[h].run(buf);
      }else{
	if((1==n)||t!=0)args.push_back(q2d(z));
	else DO(n-1,args.push_back(q2d(kK(z)[i])))
	v=c[h].run(buf,args);
      }
    }catch(exception &e){R (K)0;}

    R d2q(v);
  }

  K3(ddbupload){
    ConstantSP v;
    I t=y->t;
    J n=y->n;
    vector<string> names;
    vector<ConstantSP> objs;

    I h=abs(xi)-1;
    if(h<0||h>=CIDX) R (K)0;

    try{
      if(-11==t) v=c[h].upload(y->s,q2d(z));
      else if(11==t){
      DO(n,names.push_back(kS(y)[i]);objs.push_back(q2d(kK(z)[i])));
      v=c[h].upload(names,objs);
      }
    }catch(exception &e){R (K)0;}

    R d2q(v);
  }

  K2(ddbsub){
    pthread_t tid;
    if(TIDX>=CLIENTMAX) R ki(-1);
    try{
      K p=knk(2,ki(TIDX),y);
      r1(y);r1(p);
      pthread_create(&tid, NULL,sub_thread,p);
      TIDX++;
      R ki(TIDX);
    }catch(exception &e){R ki(-1);}    
    R ki(0);
  }

  K2(ddbunsub){
    pthread_t tid;
    I h=abs(xi)-1;
    if(h<0||h>=TIDX) R ki(-1);
    try{
      K p=knk(2,ki(h),y);
      r1(x);r1(y);r1(p);
      pthread_create(&tid, NULL,unsub_thread,p);
      R ki(tid);
    }catch(exception &e){R ki(-1);}    
    R ki(0);
  }
}
