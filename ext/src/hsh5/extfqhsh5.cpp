#include "kcomm.h"
#include <queue>

#include <h5sdk.h>

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
Z std::queue<K> fq;

Z int c;

ZK onmq(I i){
  K L=knk(0);
  //O("onmq:%d\n",0);

  read(i,&b,PIPE_CAPACITY);

  LOCK;
  while (!mq.empty()){
    jk(&L,d9(mq.front()));

    /*
      fq.push(mq.front());
    */

    mq.pop();
  }
  UNLOCK;    
  k(0,"onhsh5",L,(K)0);
  R ki(0);
}

Z V mpub(K x){

  LOCK;
  mq.push(b9(1,x));

  /*
    while (!fq.empty()){
    r0(fq.front());
    fq.pop();
    }
  */
  //k(-c,"onl2hr",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};

K decoderec(IRecord *r);

K decodepure(IHsCommTagItem *v){
  //O("[decodepure]v=%d\n",v);
  if(v==NULL)R knk(0);

  I m=v->GetCount(),t=v->GetValueType(0),n=0;
  K kv;

  //O("[decodepure]m=%d,t=%d\n",m,t);

  switch(t){
  case TypeInt8:
  case TypeuInt8:  
  case TypeInt16:  
  case TypeuInt16:  
  case TypeInt32:  
  case TypeuInt32:  
  case TypeInt64:  
  case TypeuInt64:
    kv=(m==1)?kj((J)((t==TypeInt8)||(t==TypeuInt8))?v->GetInt8():((t==TypeInt16)||(t==TypeuInt16))?v->GetInt16():((t==TypeInt32)||(t==TypeuInt32))?v->GetInt32():v->GetInt64()):ktn(-KJ,m);
    if(m>1)DO(m,kJ(kv)[i]=(J)((t==TypeInt8)||(t==TypeuInt8))?v->GetInt8(i):((t==TypeInt16)||(t==TypeuInt16))?v->GetInt16(i):((t==TypeInt32)||(t==TypeuInt32))?v->GetInt32(i):v->GetInt64(i));
    break;
  case TypeDouble:
    kv=(m==1)?kf(v->GetDouble()):ktn(-KF,m);
    if(m>1)DO(m,kF(kv)[i]=v->GetDouble(i));
    break;
   case TypeString:
     kv=(m==1)?kp(v->GetString()):knk(0);
     if(m>1)DO(m,jk(&kv,kp(v->GetString(i))));
     break;
   case TypeVector:
   case TypeRaw:
     n=v->GetRawDataLen();
     kv=(m==1)?kpn(v->GetRawData(&n),n):knk(0);
     if(m>1)DO(m,n=v->GetRawDataLen(i);jk(&kv,kpn(v->GetRawData(&n,i),n)));
     break;    
  default:
    kv=knk(0);
  }
    
  R kv;
}

K decodegrp(IGroup *g){
  K L=knk(0);
  I n=g->GetRecordCount();
  IRecord *r;
  K v;
  //O("[decodegrp]n=%d\n",n);
  DO(n,r=g->GetRecord(i);v=decoderec(r);jk(&L,v););
    
  R L;
}

K decodefld(IRecord *r,uint16 wTagID,bool isGroup){
  //O("[decodefld]tag=%d,isgroup=%d\n",wTagID,isGroup);

  if(isGroup){
    IGroup* g=r->GetGroup(wTagID);
    R decodegrp(g); 
  }else{
    IHsCommTagItem* v=r->GetItem(wTagID); //PureTag
    R decodepure(v);
  }
}

K decoderec(IRecord *r){
  K L0=ktn(KI,0),L1=knk(0);
  J j=0;
  uint16 wTagID;
  bool isGroup;
  I tag=0;

  //O("[enter decoderec]r=%d",r);
  if(r==NULL)R knk(0);
  
  r->BeginTourEx();
  
  while(r->GetTagEx(wTagID,isGroup)){
    tag=wTagID;
    ja(&L0,&tag);
    jk(&L1,decodefld(r,wTagID,isGroup));
    //O("[>>decoderec<<]r=%d,j=%d,tag=%d,isgroup=%d\n",r,j,wTagID,isGroup);
    j++;
  }
  R xD(L0,L1);
}

class H5SdkCallbackImpl: public H5SdkCallback {
public:
  void H5SDKAPI OnConnect(Session *session, const char *peerIp, int peerPort, const char *localIp, int localPort) {
    mpub(knk(2,ks("OnConnect"),knk(5,kj((J)session),kp(peerIp),ki(peerPort),kp(localIp),ki(localPort))));
  }

  void H5SDKAPI OnSdkLogin(Session *session) {
    mpub(knk(2,ks("OnSdkLogin"),knk(2,kj((J)session),ki(0))));
  }
  
  void H5SDKAPI OnReceived(Session *session, IHsCommMessage *response) {
    IRecord *h=response->GetHead(),*b=response->GetBody();
    K x,y;
    //O("[===============decode resp head]\n");
    x=decoderec(h);
    //O("[===============decode resp head end]\n");
    //O("[===============decode resp body]\n");
    y=decoderec(b);
    //O("[===============decode resp body end]\n");
    mpub(knk(2,ks("OnReceived"),knk(3,kj((J)session),x,y)));
    response->Release();
  }

  void H5SDKAPI OnClose(Session *session, int reason) {
    mpub(knk(2,ks("OnClose"),knk(2,kj((J)session),ki(reason))));
  }

  void H5SDKAPI OnError(Session *session, int errorNo) {
    mpub(knk(2,ks("OnError"),knk(2,kj((J)session),ki(errorNo))));
  }

  void H5SDKAPI OnCore(Session *session) {
    mpub(knk(2,ks("OnCore"),knk(2,kj((J)session),ki(0))));
  }
};

Z Session *session;
Z H5SdkCallbackImpl h5SdkCallbackImpl;

ZV kv2hv(IHsCommTagItem* hv,K x){
  J n=xn;
  
  switch(xt){
  case -KB:
  case -KC:
  case -KG:hv->SetInt8(xg);break;
  case -KH:hv->SetInt16(xh);break;
  case -KI:hv->SetInt32(xi);break;
  case -KJ:hv->SetInt64(xj);break;
  case -KF:hv->SetDouble(xf);break;      
  case -KS:hv->SetString(xs);break;
      
  case KB:
  case KC:
  case KG:DO(n,hv->SetInt8(kG(x)[i],i));break;
  case KH:DO(n,hv->SetInt16(kH(x)[i],i));break;
  case KI:DO(n,hv->SetInt32(kI(x)[i],i));break;
  case KJ:DO(n,hv->SetInt64(kJ(x)[i],i));break;
  case KF:DO(n,hv->SetDouble(kF(x)[i],i));break;      
  case KS:DO(n,hv->SetString(kS(x)[i],i));break;
  default:break;  
  }  
}

ZV fillrec(IRecord *r,K v);

ZV fillrecfld(IRecord *m,I k,K v){
  I t=v->t;
  J n=v->n;
  
  //O ("[fillrecfld]k=%d,t=%d,n=%d\n",k,t,n);
  
  if(t==0){
    IGroup *g = m->SetGroup(k);
    IRecord *r;
    DO(n,r = g->AddRecord();fillrec(r,kK(v)[i]););
  }else{
    IHsCommTagItem* hv=m->GetItem(k);
    kv2hv(hv,v);
  }
}  

ZV fillrec(IRecord *r,K v){
  K x=kK(v)[0],y=kK(v)[1];
  I n=xn,t=y->t;
  
  //O("[fillrec]n=%d,t=%d\n",n,t);
  
  DO(n,fillrecfld(r,kI(x)[i],(t==0)?kK(y)[i]:(t==KS)?ks(kS(y)[i]):(t==KF)?kf(kF(y)[i]):(t==KJ)?kj(kJ(y)[i]):(t==KI)?ki(kI(y)[i]):(t==KH)?kh(kH(y)[i]):kg(kG(y)[i])));  
}

ZV fillmsgfld(IHsCommMessage *m,I k,K v){
  I t=v->t;
  J n=v->n;
  
  //O("[fillmsgfld]k=%d,t=%d,n=%d\n",k,t,n);

  if(t==0){
    IGroup *g = m->SetGroup(k);
    IRecord *r;
    DO(n,r = g->AddRecord();fillrec(r,kK(v)[i]););
  }else{
    IHsCommTagItem* hv=m->GetItem(k);
    kv2hv(hv,v);
  }
}  
  
ZV fillreq(IHsCommMessage *m,K v){
  K x=kK(v)[0],y=kK(v)[1];
  I n=xn,t=y->t;
  
  //O("[fillreq]n=%d,t=%d\n",n,t);

  DO(n,fillmsgfld(m,kI(x)[i],(t==0)?kK(y)[i]:(t==KS)?ks(kS(y)[i]):(t==KF)?kf(kF(y)[i]):(t==KJ)?kj(kJ(y)[i]):(t==KI)?ki(kI(y)[i]):(t==KH)?kh(kH(y)[i]):kg(kG(y)[i])));
}

extern "C"{
  K1(h5ver){
    R kp((S)GetSdkVersion());
  }

  K1(h5sess){
    R kj((J)session);
  }

  K2(h5init){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
      
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

    SessionOptions *sessionOptions;
    sessionOptions = CreateSessionOptions();
    sessionOptions->AddRef();
    sessionOptions->SetServerIp(kK(x)[0]->s);
    sessionOptions->SetServerPort(kK(x)[1]->i);
    sessionOptions->SetHeartbeatTimeout(kK(x)[2]->i);
    session= CreateSession( sessionOptions);
    session->AddRef();

    session->SetAppInfo(kK(x)[3]->s,kK(x)[4]->s);

    StartSetCallback();
    session->SetCallback(&h5SdkCallbackImpl);
    StartAllSessions();
    R ki(run);
  }

  K1(h5free){
    if(!run) R ki(-1);

    StopAllSessions();
    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;
    
    run--;
    R ki(run);
  }

  K1(h5run){
    R ki(run);
  } 

  K1(h5sdklogin){
    R ki(session->AsyncSdkLogin(xi));
  }

  K1(h5conn){
    R ki(session->AsyncConnect());
  }

  K1(h5usrlogin){
    LoginAnsInfo *lp=session->LoginByUser(kS(x)[0],kS(x)[1]);
    R(lp?kp(lp->GetResult()):ki(-1));
  }

  K2(h5req){
    I r=0;
    IHsCommMessage *m=session->CreateMessage(kI(x)[0],kI(x)[1],kI(x)[2]);
    if (NULL==m){O("create message fail\n");R ki(-1);}
    fillreq(m,y);
    r=session->AsyncSend(m);
    IRecord *h=m->GetHead(),*b=m->GetBody();
    mpub(knk(2,ks("h5req"),knk(3,kj(0),decoderec(h),decoderec(b))));
    m->Release();
    R ki(r);
  }
}
