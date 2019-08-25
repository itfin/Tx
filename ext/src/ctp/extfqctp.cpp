#include "kcomm.h"
#include <queue>
#include "ThostFtdcMdApi.h"


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

//extern "C" K2(userLoginQ); 
//extern "C" K1(subscribeMarketData); 
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
  //k(-c,"onctp",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};

Z CThostFtdcMdApi *pQuoteApi;

ZC FRONTLIST[BUFLEN];
ZC BROKER[SYMSIZE];
ZC USER[SYMSIZE];
ZC PASSWORD[SYMSIZE];
ZC SYMLIST[BUFLEN];

#define CTPPUB(x,y) mpub(knk(2,ks(x),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));
#define RETURNONERR if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError"),knk(3,ki(nRequestID),kb(bIsLast),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg)))));R;}

class CQuoteHandler : public CThostFtdcMdSpi{
public: 
  CQuoteHandler(CThostFtdcMdApi *pUserApi) : m_pUserApi(pUserApi) {} 
  ~CQuoteHandler(){} 

  virtual void OnFrontConnected() { 
    O("OnFrontConnected.\n"); 
    mpub(knk(2,ks("FrontConnectQ"),knk(0)));
    //userLoginQ(ki(10000),knk(4,ks("20000"),ks("000000005188"),ks("1"),ki(0)));
  } 

  virtual void OnFrontDisconnected(int nReason) { 
    O("OnFrontDisconnected.\n"); 
    mpub(knk(2,ks("FrontDisconnectQ"),knk(1,ki(nReason))));
  } 

  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    O("OnRspUserLogin:%d\n",p); 
    RETURNONERR;
    CTPPUB("UserLoginQ",knk(3,ki(p->FrontID),ki(p->SessionID),kp(p->MaxOrderRef)));
    //subscribeMarketData(ks("IF1211,IF1212"));
  } 
  
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    O("OnRspUserLogout.\n");   
  };

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    O("OnRspError:\n"); 
    O("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg); 
    O("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast); 
  }
 
  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *f, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    //    O("OnRspSubMarketData.\n");   
    if(NULL==f) R;
    LOCK;
    mq.push(b9(1,knk(2,ks("MDSub"),knk(1,kp(f->InstrumentID)))));
    UNLOCK;    
    write(p[1],&b,1);
  };

  virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    O("OnRspUnSubMarketData.\n");   
  };

  virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *f, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    if(NULL==f) R;
    LOCK;
    mq.push(b9(1,knk(2,ks("QTSub"),knk(1,kp(f->InstrumentID)))));
    UNLOCK;    
    write(p[1],&b,1);
  };

  virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *f){
    if(NULL==f) R;
    //O("OnRtnDepthMarketData:%d\n",f);   
    LOCK;
    mq.push(b9(1,knk(2,ks("DepthMD"),knk(43,kp(f->TradingDay),kp(f->InstrumentID),kp(f->ExchangeID),kp(f->ExchangeInstID),kf(f->LastPrice),kf(f->PreSettlementPrice),kf(f->PreClosePrice),kf(f->PreOpenInterest),kf(f->OpenPrice),kf(f->HighestPrice),kf(f->LowestPrice),ki(f->Volume),kf(f->Turnover),kf(f->OpenInterest),kf(f->ClosePrice),kf(f->SettlementPrice),kf(f->UpperLimitPrice),kf(f->LowerLimitPrice),kf(f->PreDelta),kf(f->CurrDelta),kp(f->UpdateTime),ki(f->UpdateMillisec),kf(f->BidPrice1),ki(f->BidVolume1),kf(f->AskPrice1),ki(f->AskVolume1),kf(f->BidPrice2),ki(f->BidVolume2),kf(f->AskPrice2),ki(f->AskVolume2),kf(f->BidPrice3),ki(f->BidVolume3),kf(f->AskPrice3),ki(f->AskVolume3),kf(f->BidPrice4),ki(f->BidVolume4),kf(f->AskPrice4),ki(f->AskVolume4),kf(f->BidPrice5),ki(f->BidVolume5),kf(f->AskPrice5),ki(f->AskVolume5),kf(f->AveragePrice)))));
    UNLOCK;    
    write(p[1],&b,1);
  };

  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *f){
    if(NULL==f) R;
    //O("OnRtnForQuoteRsp:%d\n",f);   
    LOCK;
    mq.push(b9(1,knk(2,ks("QuoteReq"),knk(5,kp(f->TradingDay),kp(f->InstrumentID),kp(f->ForQuoteSysID),kp(f->ForQuoteTime),kp(f->ActionDay)))));
    UNLOCK;    
    write(p[1],&b,1);
  };

private: 
  CThostFtdcMdApi *m_pUserApi;
};

Z CQuoteHandler * pQuoteSpi;

extern "C"{
  K2(initctpq){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0;
    char buf[1024];

    if(run) R ki(-1);

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
    sprintf(buf,"/tmp/CTPQ_%s",y->s);
    pQuoteApi = CThostFtdcMdApi::CreateFtdcMdApi(buf,false);
    O(pQuoteApi->GetApiVersion());
    pQuoteSpi = new CQuoteHandler(pQuoteApi);
    pQuoteApi->RegisterSpi((CThostFtdcMdSpi*)pQuoteSpi);

    pQuoteApi->RegisterFront(xs);
    pQuoteApi->Init();
   
    R ki(run);
  }

  K1(freectpq){
    if(!run) R ki(-1);

    pQuoteApi->RegisterSpi(NULL);
    pQuoteApi->Release();
    pQuoteApi=NULL;
    delete pQuoteSpi;
    pQuoteSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(ctpqrun){
    R ki(run);
  } 

  K2(userLoginQ){
    if(!run) R ki(-1);

    CThostFtdcReqUserLoginField req; 

    strcpy(req.BrokerID,kK(y)[0]->s); 
    strcpy(req.UserID,kK(y)[1]->s); 
    strcpy(req.Password,kK(y)[2]->s); 
    strcpy(req.UserProductInfo,kK(y)[3]->s);
    R ki(pQuoteApi->ReqUserLogin(&req,xi)); 
  }

  K2(subscribe){ //(symlist,tag)tag=0(MarketData),tag=1(Quote) 
    I n=0,r=0;
    const S split = ","; 
    S p=NULL,sa[BUFLEN];
    C buf[BUFLEN];

    if(!run) R ki(-1);
    strcpy(buf,xs);
    p=strtok (buf,split); 
    while(p!=NULL){
      sa[n]=p;
      n++;
      p=strtok(NULL,split);
    } 
    if(0<y->i){
      r=pQuoteApi->SubscribeForQuoteRsp(sa,n);
      O("[subQT]:%d\n",n);
    }else{

      r=pQuoteApi->SubscribeMarketData(sa,n);
      O("[subMD]:%d\n",n);
    }
    R ki(r);
  }
}

