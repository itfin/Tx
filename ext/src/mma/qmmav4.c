#if defined(WIN32)||defined(WIN64)
#include "mathlink.h"
#else
#include "mathlink.h"
#endif
#include "kcomm.h"

#define ONMLERR fprintf(stderr,"[line:%d,code:%d]Error detected by MathLink: %s!\n",__LINE__,MLError(ml_lp),MLErrorMessage(ml_lp));MLClearError(ml_lp)
#define MLENDPACKET r=MLEndPacket(ml_lp) /*printf("MLEndPacket\n");*/
MLENV ml_ep = (MLENV)0;
MLINK ml_lp = (MLINK)0;
Z S logfilename;

K1(mlopen){
  int ml_err=0,i=0;
  ml_ep =  MLInitialize(0);
  if( ml_ep == (MLENV)0) R ki(-1);
  //for(i=0;i<x->n;i++)printf("argv[%d]:%s\n",i,kS(x)[i]);
  ml_lp = MLOpenArgcArgv(ml_ep,x->n,kS(x),&ml_err);
  //printf("MLOpenArgcArgv:%d\n",ml_err);
  if(ml_lp == (MLINK)0) R ki(-2);
  if(!MLActivate(ml_lp)) R ki(-3);

#if defined(_DEBUG)  
  if(!MLLogFileNameForLink(ml_lp, &logfilename)) R ki(-4);
  DBG("[linklogfile]%s!\n",logfilename);
  if(!MLLogStreamToFile(ml_lp,logfilename)) R ki(-5);
#endif  
  
  setm(1);
  setbuf(stdout,NULL);
  
  R ki(ml_err);
}

K1(mlclose){
  if(NULL==ml_lp)R ki(-1);
  if(x->i)MLPutFunction(ml_lp, "Exit",0);
#if defined(_DEBUG)  
  MLReleaseLogFileNameForLink(ml_lp, logfilename);
#endif  

  MLClose( ml_lp);
  if( ml_ep) MLDeinitialize( ml_ep);
  R ki(0);
}

K1(mlgetexpr){
  int tag=0,len,i,t,m,r,lenh,r1,r2,tagh;
  S s;
  K v,L,h,vh;
  DBG("Enter mlgetexpr!\n");
  tag=MLGetNext(ml_lp);
  DBG("%s:%d,xt:%d,xi:%d\n","mlgetexpr",tag,x->t,x->i);
  switch (tag){
  case MLTKINT:v=ki(0);DBG("1\n");R (MLGetInteger32(ml_lp,&v->i))?v:0;
  case MLTKREAL:v=kf(0.);DBG("2\n");R (MLGetReal64(ml_lp,&v->f))?v:0;
  case MLTKSYM:if(!MLGetSymbol(ml_lp,&s)){DBG("3\n");R 0;}else {v=ks(s);MLReleaseSymbol(ml_lp,s);DBG("4\n");R v;}
  case MLTKSTR:if(!MLGetByteString(ml_lp,&s,&len,0)){DBG("5\n");R knk(0);}else {v=kpn(s,len);MLReleaseByteString(ml_lp,s,len);DBG("5\n");R v;}
  case MLTKFUNC:
    len=0;
    r=MLGetFunction(ml_lp,&s,&len);
    if(!r){
      DBG("<7>FuncHead is not symbol:[r=%d,len=%d,sym=%s]\n",r,len,s);
      DBG("ERROR:[%d](%s)!\n",MLError(ml_lp),MLErrorMessage(ml_lp));      
      /*
      tagh=MLGetNextRaw(ml_lp);
      r1=MLGetArgCount(ml_lp,&lenh);
      DBG("tagh=%d,lenh=%d\n",tagh,lenh);
      r2=MLGetSymbol(ml_lp,&s);
      vh=knk(0);
      for(i=0;i<lenh;i++)jk(&vh,mlgetexpr(x));      
      h=knk(3,x,ks(s),vh);
      
      v=knk(0);
      for(i=0;i<len;i++)jk(&v,mlgetexpr(x));
      L=knk(3,x,h,v); //ks("MLFUN")
      */ 
    }else{
      DBG("[Fun](%s)len=%d!\n",s,len);
      if(!strcmp(s,"List")){
	L=knk(0);
	m=1;
	for(i=0;i<len;i++){
	  v=mlgetexpr(x);
	  jk(&L,v);
	  
	  if(0==i){t=v->t;m=0;}
	  
	  else if(t!=v->t){m=1;}
	}
	if((!m)&&(t<0)){
	  v=ktn(-t,0);
	  for(i=0;i<len;i++)ja(&v,&(kK(L)[i]->k));
	  DBG("8\n");
	  R v;
	}else{}
      }else{
	v=knk(0);
	for(i=0;i<len;i++)jk(&v,mlgetexpr(x));
	L=knk(3,x,ks(s),v); //ks("MLFUN")
      };
      MLReleaseSymbol(ml_lp,s);
      DBG("9\n");R L;
    }
  case MLTKERROR:
  default:
      DBG("MLTKERROR:[%d](%s)!\n",MLError(ml_lp),MLErrorMessage(ml_lp));    
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

  tag=MLGetNext(ml_lp);
  /*
  printf("MLTKERR=%d\n",MLTKERR);
  printf("MLTKINT=%d\n",MLTKINT);
  printf("MLTKFUNC=%d\n",MLTKFUNC);
  printf("MLTKREAL=%d\n",MLTKREAL);
  printf("MLTKSTR=%d\n",MLTKSTR);
  printf("MLTKSYM=%d\n",MLTKSYM);
  printf("MLTKOLDINT=%d\n",MLTKOLDINT);
  printf("MLTKOLDREAL=%d\n",MLTKOLDREAL);
  printf("MLTKOLDSTR=%d\n",MLTKOLDSTR);
  printf("MLTKOLDSYM=%d\n",MLTKOLDSYM);
  */
  if(! MLGetIntegerArray(ml_lp, &data, &dims, &heads, &d)){
    ONMLERR;
    R (K) 0;
  }

  for(i=0;i<d;i++)size*=dims[i];
  L=ia2q(data,dims,d,size);
  MLReleaseInteger32Array(ml_lp, data, dims, heads, d);
  R L;
}

K1(mlgetfarray){
  double *data;
  long *dims;
  char **heads;
  long d,size=1,i; 
  K L;

  MLGetNext(ml_lp);
  if(! MLGetRealArray(ml_lp, &data, &dims, &heads, &d)){
    ONMLERR;
    R (K) 0;
  }

  for(i=0;i<d;i++)size*=dims[i];
  L=fa2q(data,dims,d,size);
  MLReleaseReal64Array(ml_lp, data, dims, heads, d);	
  R L;
}

K1(mlgetilist){
  int *data,i;
  long length;
  K L;

  MLGetNext(ml_lp);
  if(!MLGetIntegerList(ml_lp, &data, &length)){
    ONMLERR;
    R (K) 0;
  }

  L=ktn(KI,length);
  for(i=0;i<length;i++)kI(L)[i]=*(data+i);
  MLReleaseInteger32List(ml_lp, data, length);
  R L;
}

K1(mlgetflist){
  double *data;
  int length,i;
  K L;

  MLGetNext(ml_lp);
  if(! MLGetReal64List(ml_lp, &data, &length)){
    ONMLERR;
    R (K) 0;
  }

  L=ktn(KF,length);
  for(i=0;i<length;i++)kF(L)[i]=*(data+i);
  MLReleaseReal64List(ml_lp,data,length);
  R L;
}

K2(mlget){
  int pkt,r;
  int tag=y->i;
  
  r=MLNewPacket(ml_lp);
  DBG("[%s]r=%d,:xt:%d,xi:%d,yt:%d,yi:%d\n","mlget",r,x->t,x->i,y->t,y->i);
  
  while((pkt = MLNextPacket(ml_lp)) && pkt != RETURNPKT){ /*TEXTPKT:2,MESSAGEPKT:5,RETURNPKT:3 */
    DBG("recv pkt:%d\n",pkt);
    MLNewPacket(ml_lp);
    //while((i<600)&&(0==MLReady(ml_lp))){i++;usleep(100000);DBG("i=%d\n",i);}
  }
  //    MLNewPacket(ml_lp);
  //  R ki(-1);
  
  if(!pkt){
    ONMLERR;
    R 0;
  }else if(!tag){
    MLNewPacket(ml_lp);
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
  mlint64 j={0,0}; 
  //printf("%s:%d,%d\n","mlput",x->t,x->n);
  switch(x->t){
  case -KB: 
  case -KG: 
  case -KC:b[0]=x->g;R MLPutString(ml_lp,b); 
  case -KH:R MLPutInteger16(ml_lp,x->h);
  case -KI:R MLPutInteger32(ml_lp,x->i);
  case -KJ:*(J*)&j=x->j;R MLPutInteger64(ml_lp,j);
  case -KE:R MLPutReal32(ml_lp,x->e); 
  case -KF:R MLPutReal64(ml_lp,x->f); 
  case -KS:R MLPutSymbol(ml_lp,x->s);

  case KB: 
  case KG: 
  case KC:R MLPutByteString(ml_lp,kG(x),x->n);
  case KH:R MLPutInteger16List(ml_lp,kH(x),x->n);
  case KI:R MLPutInteger32List(ml_lp,kI(x),x->n);
  case KJ:R MLPutInteger64List(ml_lp,(mlint64*)kJ(x),x->n);
  case KE:R MLPutReal32List(ml_lp,kE(x),x->n); 
  case KF:R MLPutReal64List(ml_lp,kF(x),x->n);

  case KS:if(!MLPutFunction(ml_lp,"List",x->n)){
      R 0;
    }else{
      for(i=0;i<x->n;i++)if(!MLPutSymbol(ml_lp,kS(x)[i]))R 0;
    }
    break;
  case 0:
    if(0==x->n){
      R MLPutFunction(ml_lp, "List",0);
    }else if((3==x->n)&&(fstype==kK(x)[0]->t)){
      z=kK(x)[2];
      if(!MLPutFunction(ml_lp,kK(x)[1]->s,z->n)){R 0;}else{
	switch(z->t){
	case 0:for(i=0;i<z->n;i++)if(!mlput(kK(z)[i],y))R 0;break;
	case KH:for(i=0;i<z->n;i++)if(!MLPutInteger16(ml_lp,kH(z)[i]))R 0;break;
	case KI:for(i=0;i<z->n;i++)if(!MLPutInteger32(ml_lp,kI(z)[i]))R 0;break;
	case KJ:for(i=0;i<z->n;i++){*(J*)&j=kJ(z)[i];if(!MLPutInteger64(ml_lp,j))R 0;}break;
	case KE:for(i=0;i<z->n;i++)if(!MLPutReal32(ml_lp,kE(z)[i]))R 0;break;
	case KF:for(i=0;i<z->n;i++)if(!MLPutReal64(ml_lp,kF(z)[i]))R 0;break;
	case KS:for(i=0;i<z->n;i++)if(!MLPutSymbol(ml_lp,kS(z)[i]))R 0;break;
	case KC:for(i=0;i<z->n;i++){b[0]=kC(z)[i];if(!MLPutString(ml_lp,b))R 0;}break;
	default:break;
	}
      }
    }else{
      if(!MLPutFunction(ml_lp,"List",x->n)){R 0;}else{for(i=0;i<x->n;i++)if(!mlput(kK(x)[i],y)){MLPutSymbol(ml_lp,"ParaErr");funcerr=1;}if(funcerr)R 0;}
    }
    break; 
  default:
    R 0;
  }
  R 1;
}

/*x:expr,y:`MLFUN,z:need result*/
K3(mleval){
  int r=0,i=0;
  K v=0;
  if(!MLPutFunction(ml_lp, "EvaluatePacket", 1)){ONMLERR;R 0;}
  if(!mlput(x,y)){ONMLERR;}
  MLENDPACKET;
  if(!r){ONMLERR;R 0;}
  if(!MLFlush(ml_lp)){ONMLERR;R 0;}

//  while((i<600)&&(0==MLReady(ml_lp))){i++;usleep(100000);DBG("i=%d\n",i);}
  
//  if(100==i){R 0;}
  //DBG("i=%d\n",i);
 
    v=mlget(y,z);

  if(!MLNewPacket(ml_lp)){ONMLERR;R 0;}
  R v;
}
