#include "wstp.h"
#include "kcomm.h"

#define ONWSERR fprintf(stderr,"[line:%d,code:%d]Error detected by MathLink: %s!\n",__LINE__,WSError(ml_lp),WSErrorMessage(ml_lp));WSClearError(ml_lp)
#define WSENDPACKET r=WSEndPacket(ml_lp) /*printf("WSEndPacket\n");*/
WSENV ml_ep = (WSENV)0;
WSLINK ml_lp = (WSLINK)0;
Z S logfilename;

K1(mlopen){
  int ml_err=0,i=0;
  ml_ep =  WSInitialize(0);
  if( ml_ep == (WSENV)0) R ki(-1);
  //for(i=0;i<x->n;i++)printf("argv[%d]:%s\n",i,kS(x)[i]);
  setm(1);
  ml_lp = WSOpenArgcArgv(ml_ep,x->n,kS(x),&ml_err);
  //printf("WSOpenArgcArgv:%d\n",ml_err);
  if(ml_lp == (WSLINK)0) R ki(-2);
  if(!WSActivate(ml_lp)) R ki(-3);

#if defined(_DEBUG)  
  if(!WSLogFileNameForLink(ml_lp, &logfilename)) R ki(-4);
  DBG("[linklogfile]%s!\n",logfilename);
  if(!WSLogStreamToFile(ml_lp,logfilename)) R ki(-5);
#endif  
  
  setm(1);
  setbuf(stdout,NULL);
  
  R ki(ml_err);
}

K1(mlclose){
  if(NULL==ml_lp)R ki(-1);
  if(x->i)WSPutFunction(ml_lp, "Exit",0);
#if defined(_DEBUG)  
  WSReleaseLogFileNameForLink(ml_lp, logfilename);
#endif  

  WSClose( ml_lp);
  if( ml_ep) WSDeinitialize( ml_ep);
  R ki(0);
}

K1(mlgetexpr){
  int tag=0,len,i,t,m,r,lenh,r1,r2,tagh;
  S s;
  K v,L,h,vh;
  DBG("Enter mlgetexpr!\n");
  tag=WSGetType(ml_lp); /*WSGetNextRaw*/
  DBG("%s:%d,xt:%d,xi:%d\n","mlgetexpr",tag,x->t,x->i);
  switch (tag){
  case WSTKINT:v=kj(0);DBG("1\n");r=WSGetInteger64(ml_lp,&v->j);if(!r){O("r=%d\n",r);ONWSERR;}R r?v:kj(0);
  case WSTKREAL:v=kf(0.);DBG("2\n");r=WSGetReal64(ml_lp,&v->f);if(!r)ONWSERR;R r?v:kf(0.);
  case WSTKSYM:r=WSGetSymbol(ml_lp,&s);if(!r){ONWSERR;DBG("3\n");R ks("");}else {v=ks(s);WSReleaseSymbol(ml_lp,s);DBG("4\n");R v;}
  case WSTKSTR:r=WSGetByteString(ml_lp,&s,&len,0);if(!r){ONWSERR;DBG("5\n");R kp("");}else {v=kpn(s,len);WSReleaseByteString(ml_lp,s,len);DBG("5\n");R v;}
  case WSTKFUNC:len=0;
    /*r=WSGetFunction(ml_lp,&s,&len);*/
    r=WSGetArgCount(ml_lp,&len);if(!r)ONWSERR;
    tagh=WSGetType(ml_lp);
    DBG("argn=%d,tagh=%d\n",len,tagh);
    if(WSTKSYM!=tagh){
      h=mlgetexpr(x);
      v=knk(0);
      for(i=0;i<len;i++)jk(&v,mlgetexpr(x));
      L=knk(3,x,h,v); //ks("WSFUN")
      R L;
    }else{
      r=WSGetSymbol(ml_lp,&s);DBG("1:r=%d,fun=%s\n",r,s);if(!r)ONWSERR;
      DBG("[Fun](%s)len=%d!\n",s,len);
      if(!strcmp(s,"List")){
	L=knk(0);
	m=1;
	for(i=0;i<len;i++){
	  v=mlgetexpr(x);
	  if(0==i){t=v->t;m=0;}
	  else if(t!=v->t){m=1;}
	  jk(&L,v);
	}
	if((!m)&&(t<0)){
	  v=ktn(-t,0);
	  for(i=0;i<len;i++)ja(&v,&(kK(L)[i]->k));
	  DBG("8\n");
	  L=v;
	}else{}
      }else{
	v=knk(0);
	for(i=0;i<len;i++)jk(&v,mlgetexpr(x));
	L=knk(3,x,ks(s),v); //ks("WSFUN")
      };
      WSReleaseSymbol(ml_lp,s);
      DBG("9\n");R L;
    }
  case WSTKERROR:
  default:
    DBG("WSTKERROR:tag=%d,[%d](%s)!\n",tag,WSError(ml_lp),WSErrorMessage(ml_lp));    
    break;
  }
  DBG("10\n");
  R knk(0); 
} 

K ia2q(int *data,long *dims,long d,long size){
  int length=dims[0],elesize=size/length,i;
  K L;

  if(1==d){
    L=ktn(KI,length);
    for(i=0;i<length;i++)kI(L)[i]=*(data+i);
    R L; 
  }else if(1<d){
    L=knk(0);
    for(i=0;i<length;i++)jk(&L,ia2q(data+i*elesize,dims+1,d-1,elesize));
    R L; 
  }

  R (K)0;
}

K fa2q(double *data,long *dims,long d,long size){
  int length=dims[0],elesize=size/length,i;
  K L;

  if(1==d){
    L=ktn(KF,length);
    for(i=0;i<length;i++)kF(L)[i]=*(data+i);
    R L; 
  }else if(1<d){
    L=knk(0);
    for(i=0;i<length;i++)jk(&L,fa2q(data+i*elesize,dims+1,d-1,elesize));
    R L; 
  }

  R (K)0;
}


K1(mlgetiarray){
  int *data,tag;
  long *dims;
  char **heads;
  long d,size=1,i;
  K L;

  tag=WSGetNext(ml_lp);
  /*
  printf("WSTKERR=%d\n",WSTKERR);
  printf("WSTKINT=%d\n",WSTKINT);
  printf("WSTKFUNC=%d\n",WSTKFUNC);
  printf("WSTKREAL=%d\n",WSTKREAL);
  printf("WSTKSTR=%d\n",WSTKSTR);
  printf("WSTKSYM=%d\n",WSTKSYM);
  printf("WSTKOLDINT=%d\n",WSTKOLDINT);
  printf("WSTKOLDREAL=%d\n",WSTKOLDREAL);
  printf("WSTKOLDSTR=%d\n",WSTKOLDSTR);
  printf("WSTKOLDSYM=%d\n",WSTKOLDSYM);
  */
  if(! WSGetIntegerArray(ml_lp, &data, &dims, &heads, &d)){
    ONWSERR;
    R (K) 0;
  }

  for(i=0;i<d;i++)size*=dims[i];
  L=ia2q(data,dims,d,size);
  WSReleaseInteger32Array(ml_lp, data, dims, heads, d);
  R L;
}

K1(mlgetfarray){
  double *data;
  long *dims;
  char **heads;
  long d,size=1,i; 
  K L;

  WSGetNext(ml_lp);
  if(! WSGetRealArray(ml_lp, &data, &dims, &heads, &d)){
    ONWSERR;
    R (K) 0;
  }

  for(i=0;i<d;i++)size*=dims[i];
  L=fa2q(data,dims,d,size);
  WSReleaseReal64Array(ml_lp, data, dims, heads, d);	
  R L;
}

K1(mlgetilist){
  int *data,i;
  long length;
  K L;

  WSGetNext(ml_lp);
  if(!WSGetIntegerList(ml_lp, &data, &length)){
    ONWSERR;
    R (K) 0;
  }

  L=ktn(KI,length);
  for(i=0;i<length;i++)kI(L)[i]=*(data+i);
  WSReleaseInteger32List(ml_lp, data, length);
  R L;
}

K1(mlgetflist){
  double *data;
  int length,i;
  K L;

  WSGetNext(ml_lp);
  if(! WSGetReal64List(ml_lp, &data, &length)){
    ONWSERR;
    R (K) 0;
  }

  L=ktn(KF,length);
  for(i=0;i<length;i++)kF(L)[i]=*(data+i);
  WSReleaseReal64List(ml_lp,data,length);
  R L;
}

K2(mlget){
  int pkt,r;
  int tag=y->i;
  
  r=WSNewPacket(ml_lp);
  DBG("[%s]r=%d,:xt:%d,xi:%d,yt:%d,yi:%d\n","mlget",r,x->t,x->i,y->t,y->i);
  
  while((pkt = WSNextPacket(ml_lp)) && pkt != RETURNPKT){ /*TEXTPKT:2,MESSAGEPKT:5,RETURNPKT:3 */
    DBG("recv pkt:%d\n",pkt);
    WSNewPacket(ml_lp);
    //while((i<600)&&(0==WSReady(ml_lp))){i++;usleep(100000);DBG("i=%d\n",i);}
  }
  //    WSNewPacket(ml_lp);
  //  R ki(-1);
  
  if(!pkt){
    ONWSERR;
    R 0;
  }else if(!tag){
    WSNewPacket(ml_lp);
    R 0;
  }else if(1==tag){
    R mlgetexpr(x);
  }else if(2==tag){
    R mlgetilist(x);
  }else if(3==tag){
    R mlgetflist(x);
  }else if(4==tag){
    R mlgetiarray(x);
  }else if(5==tag){
    R mlgetfarray(x);
  }

  R 0;
}

int mlput(K x,K y){
  int fstype=y->t,fsint=y->i,i=0,funcerr=0;
  K z;
  char b[2]={0,0};
  wsint64 j={0,0}; 
  //printf("%s:%d,%d\n","mlput",x->t,x->n);
  switch(x->t){
  case -KB: 
  case -KG: 
  case -KC:b[0]=x->g;R WSPutString(ml_lp,b); 
  case -KH:R WSPutInteger16(ml_lp,x->h);
  case -KI:R WSPutInteger32(ml_lp,x->i);
  case -KJ:*(J*)&j=x->j;R WSPutInteger64(ml_lp,j);
  case -KE:R WSPutReal32(ml_lp,x->e); 
  case -KF:R WSPutReal64(ml_lp,x->f); 
  case -KS:R WSPutSymbol(ml_lp,x->s);

  case KB: 
  case KG: 
  case KC:R WSPutByteString(ml_lp,kG(x),x->n);
  case KH:R WSPutInteger16List(ml_lp,kH(x),x->n);
  case KI:R WSPutInteger32List(ml_lp,kI(x),x->n);
  case KJ:R WSPutInteger64List(ml_lp,(wsint64*)kJ(x),x->n);
  case KE:R WSPutReal32List(ml_lp,kE(x),x->n); 
  case KF:R WSPutReal64List(ml_lp,kF(x),x->n);

  case KS:if(!WSPutFunction(ml_lp,"List",x->n)){
      R 0;
    }else{
      for(i=0;i<x->n;i++)if(!WSPutSymbol(ml_lp,kS(x)[i]))R 0;
    }
    break;
  case 0:
    if(0==x->n){
      R WSPutFunction(ml_lp, "List",0);
    }else if((3==x->n)&&(fstype==kK(x)[0]->t)){
      z=kK(x)[2];
      if(!WSPutFunction(ml_lp,kK(x)[1]->s,z->n)){R 0;}else{
	switch(z->t){
	case 0:for(i=0;i<z->n;i++)if(!mlput(kK(z)[i],y))R 0;break;
	case KH:for(i=0;i<z->n;i++)if(!WSPutInteger16(ml_lp,kH(z)[i]))R 0;break;
	case KI:for(i=0;i<z->n;i++)if(!WSPutInteger32(ml_lp,kI(z)[i]))R 0;break;
	case KJ:for(i=0;i<z->n;i++){*(J*)&j=kJ(z)[i];if(!WSPutInteger64(ml_lp,j))R 0;}break;
	case KE:for(i=0;i<z->n;i++)if(!WSPutReal32(ml_lp,kE(z)[i]))R 0;break;
	case KF:for(i=0;i<z->n;i++)if(!WSPutReal64(ml_lp,kF(z)[i]))R 0;break;
	case KS:for(i=0;i<z->n;i++)if(!WSPutSymbol(ml_lp,kS(z)[i]))R 0;break;
	case KC:for(i=0;i<z->n;i++){b[0]=kC(z)[i];if(!WSPutString(ml_lp,b))R 0;}break;
	default:break;
	}
      }
    }else{
      if(!WSPutFunction(ml_lp,"List",x->n)){R 0;}else{for(i=0;i<x->n;i++)if(!mlput(kK(x)[i],y)){WSPutSymbol(ml_lp,"ParaErr");funcerr=1;}if(funcerr)R 0;}
    }
    break; 
  default:
    R 0;
  }
  R 1;
}

/*x:expr,y:`WSFUN,z:need result*/
K3(mleval){
  int r=0,i=0;
  K v=0;
  if(!WSPutFunction(ml_lp, "EvaluatePacket", 1)){ONWSERR;R 0;}
  if(!mlput(x,y)){ONWSERR;}
  WSENDPACKET;
  if(!r){ONWSERR;R 0;}
  if(!WSFlush(ml_lp)){ONWSERR;R 0;}

//  while((i<600)&&(0==WSReady(ml_lp))){i++;usleep(100000);DBG("i=%d\n",i);}
  
//  if(100==i){R 0;}
  //DBG("i=%d\n",i);
 
    v=mlget(y,z);

  if(!WSNewPacket(ml_lp)){ONWSERR;R 0;}
  R v;
}
