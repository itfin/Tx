#include "kcomm.h"
#include <queue>
#include "XtTraderApi.h"

using namespace xti;
#ifndef INT_MAX  //ºÊ»›linux
#define INT_MAX       2147483647    /* maximum (signed) int value */
#endif

#define PIPE_CAPACITY 65536
#define b9 
#define d9 

ZI run=0,p[2];ZC b[2*PIPE_CAPACITY];

#if defined(WIN32)||defined(WIN64)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
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

ZK onmq(I i){
  K L=knk(0);
  //  O("onmq:%d\n",pthread_self());

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
  k(0,"onctp",L,(K)0);

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

  UNLOCK;    
  write(p[1],&b,1);
};

Z xti::XtTraderApi *pTradeApi;

#define CTPPUB(x,y) mpub(knk(2,ks(x),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));
#define CTPPUB1(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));

#define RETURNONERR if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError"),knk(3,ki(nRequestID),kb(bIsLast),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg)))));R;}

#define RETURNONERR1 if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError1"),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg))));R;}


class CTradeHandler : public xti::XtTraderApiCallback{
public: 
  CTradeHandler(){} 

  virtual void onConnected(bool success, const char* errorMsg){ 
    O("onConnected.\n"); 
    mpub(knk(2,ks("FrontConnectT"),knk(0)));
  } 


};

Z CTradeHandler * pTradeCallBack;

extern "C"{

  K2(initctpt){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0;
    char buf[1024];
    
    if(run) R ki(-8);

    if(pipe(p)) R ki(-9);

#if defined(WIN32)||defined(WIN64)
#else
    if(-1==(f = fcntl(p[0],F_GETFL,0)))R ki(-2);
    f |= O_NONBLOCK;
    if (fcntl(p[0],F_SETFL,f)==-1) R ki(-3);
#endif

    run++;
    INITLOCK; 
    sd1(p[0],onmq);

    pTradeApi=XtTraderApi::createXtTraderApi(xs);
    pTradeCallBack=new CTradeHandler();
    pTradeApi->setCallback(pTradeCallBack);
    pTradeApi->init();    
    R ki(run);
  }

  K1(freectpt){
    if(!run) R ki(-1);

    pTradeApi->join();
    delete pTradeApi;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(ctptrun){
    R ki(run);
  } 

}
