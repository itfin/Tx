#include "kcomm.h"
#include <queue>
#include "JGtdcTraderApi.h"
#include "JGtdcTraderApi.h"
#include "JGtdcTraderApi.h"

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
  k(0,"onjg",L,(K)0);
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
  //k(-c,"onxtp",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};

Z CJGtdcTraderApi *pTradeApi=NULL;
ZJ sessid=0;

#define JGPUB(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));
#define RETURNONERR(s) if(JG_TDC_ANSRESULT_Success!=(h->ResultType)){mpub(knk(2,ks("JGError"),knk(3,ki(n),kp(s),kp(h->ErrorInfo))));R;}

class CTradeHandler : public CJGtdcTraderSpi{
public: 
  CTradeHandler(){} 
  ~CTradeHandler(){}

  virtual void OnFrontConnected() {JGPUB("FrontConnectedT",knk(0))};
  virtual void OnFrontDisConnected() {JGPUB("FrontDisConnectedT",knk(0))};
  virtual void OnRspError(const char* p){JGPUB("JGError",knk(3,ki(0),kp("RspError"),kp((S)p)))};
	///< 订阅推送数据应答

  virtual void OnRspSubscription(CJGtdcRspUserSubData* p, CJGtdcRspInfoField* h, int n) {
    RETURNONERR("Subscription");
    JGPUB("SubscriptionT",knk(2,ki(n),ki(p->SubDataType)))  
    
  };
	///< 用户登录应答
  virtual void OnRspUserLogin(CJGtdcRspUserLogin* p,CJGtdcRspInfoField* h,int n){
    if(NULL!=h)RETURNONERR("RspUserLogin");if(NULL==p)R;
    JGPUB("LoginT",knk(4,ki(n),kp(p->ClientID),kp(p->FundAccount),ki(p->SupportSubType)))  
  };
	///< 用户登出应答
  virtual void OnRspUserLogout(CJGtdcRspUserLogout* p,CJGtdcRspInfoField* h,int n) {
    if(NULL!=h)RETURNONERR("RspUserLogout");if(NULL==p)R;
    JGPUB("LogoutT",knk(3,ki(n),kp(p->ClientID),kp(p->FundAccount)))  
  };
	///< 报单录入应答
  virtual void OnRspOrderInsert(CJGtdcRspOrderInsert* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderInsert");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderInsert",knk(11,ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->BatchNo),kp(p->StockAccount),kp(p->StockCode),ki(p->ExchangeType),ki(p->TradeType),ki(p->PriceType),kj(p->OrderVolume),kj(p->OrderPrice)));p++);
  };
	///< 报单撤销应答
  virtual void OnRspOrderCancel(CJGtdcRspOrderCancel* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderCancel");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderCancel",knk(5,ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->NewEntrustNo),kp(p->BatchNo)));p++);
  };
	///< 投资者可撤单查询应答
  virtual void OnRspQryCancel(CJGtdcRspQryCancel* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryCancel");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryCancel",knk(23,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者委托查询应答
  virtual void OnRspQryOrder(CJGtdcRspQryOrder* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryOrder");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryOrder",knk(23,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者成交单查询应答
  virtual void OnRspQryTrade(CJGtdcRspQryTrade* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryTrade");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryTrade",knk(22,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance)));p++);
  };
	///< 投资者持仓查询
  virtual void OnRspQryHold(CJGtdcRspQryHold* p, CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspQryHold");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryHold",knk(21,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kp(p->StockAccount),kp(p->StockCode),kp(p->StockName),ki(p->ExchangeType),kc(p->MoneyType),kj(p->YdAmount),kj(p->StockAmount),kj(p->EnableAmount),kj(p->PurchaseAmount),kj(p->PossessAmount),kj(p->FrozenAmount),kj(p->YStoreAmount),kj(p->CostPrice),kj(p->KeepCostPrice),kf(p->BuyCost),kf(p->StockBalance),kf(p->FloatIncome),kf(p->ProIncome)));p++);
  };
	///< 投资者资金查询
  virtual void OnRspQryFund(CJGtdcRspQryFund* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryFund");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryFund",knk(13,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kc(p->MoneyType),kc(p->MainFlag),kf(p->EnableBalance),kf(p->FetchBalance),kf(p->FrozenBalance),kf(p->StockBalance),kf(p->FundBalance),kf(p->AssetBalance),kf(p->InCome),kf(p->EnableBalanceHK)));p++);
  };
	///< 投资者最大委托数查询应答
  virtual void OnRspQryMax(CJGtdcRspQryMax* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryMax");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryMax",knk(8,kp(p->StockAccount),ki(p->ExchangeType),kp(p->StockCode),ki(p->TradeType),ki(p->PriceType),kj(p->OrderPrice),kp(p->BatchNo),kj(p->MaxAmount)));p++);
  };
	///< 投资者报单通知
  virtual void OnRtnOrder(CJGtdcRspQryOrder *p,int n) {
    DO(n,JGPUB("Order",knk(23,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者成交通知
  virtual void OnRtnTrade(CJGtdcRspQryTrade *p,int n) {
    DO(n,JGPUB("Trade",knk(22,kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance)));p++);
  };


  ////////////////////////////////////融资融券专用///////////////////////////////////////////////////////////
  ///< 投资者融资融券资产查询
  virtual void OnRspQryAssets(CJGtdcRspQryAssets* pRspQryAssets, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者融券可卖数量查询
  virtual void OnRspQryMaxLoan(CJGtdcRspQryMaxLoan* pRspQryMaxLoan, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者直接还券
  virtual void OnRspStockBack(CJGtdcRspStockBack* pRspStockBack, CJGtdcRspInfoField* pRspInfo, int nRequestID){};
  ///< 投资者直接还款
  virtual void OnRspMoneyBack(CJGtdcRspMoneyBack* pRspMoneyBack, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者融资负债状况查询
  virtual void OnRspQryFinance(CJGtdcRspQryFinance* pRspQryFinance, CJGtdcRspInfoField* pRspInfo, int nRequestID) {};
  ///< 投资者融券负债状况查询
  virtual void OnRspQryShortSell(CJGtdcRspQryShortsell* pRspQryShortSell, CJGtdcRspInfoField* pRspInfo, int nRequestID){};
  ///< 投资者担保品划转
  virtual void OnRspMortgageTrans(CJGtdcRspMortgageTrans* pRspMortgageTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者标的券查询
  virtual void OnRspQryObject(CJGtdcRspQryObject *pRspQryObject, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者信用账户与普通账户对应关系查询应答
  virtual void OnRspQryAccMatch(CJGtdcRspQryAccMatch *pRspQryAccMatch, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
   
};

Z CTradeHandler * pTradeSpi;

extern "C"{
  K2(initjgt){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0,v0=0,v1=0;
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
    pTradeApi = CJGtdcTraderApi::CreatetdcTraderApi();
    if(NULL==pTradeApi) R ki(-10004);

    if(!pTradeApi->Init()) R ki(-10005);
    mpub(knk(2,ks("JGTInit"),knk(1,kp((S)pTradeApi->GetVersion(v0,v1)))));
      
    pTradeSpi = new CTradeHandler();
    pTradeApi->RegisterCallBack(pTradeSpi);

    if(!pTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);

    pTradeApi->OpenOrderSequential(true);
      
    R ki(run);
  }

  K1(freejgt){
    if(!run) R ki(-1);

    pTradeApi->Disconnect();
    pTradeApi->RegisterCallBack(NULL);
    pTradeApi->Fini();
    pTradeApi->Release();
    pTradeApi=NULL;
    delete pTradeSpi;
    pTradeSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(jgtrun){
    R ki(run);
  }


  K2(ReConnT){
    if((!run)||NULL==pTradeApi) R ki(-1);
    if(!pTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);
    R ki(0);
  }
  
  K2(userLoginT){
    if(!run) R ki(-1);
      
    CJGtdcReqUserLogin req;

    pTradeApi->SetUserMachineInfo(NULL);
      
    req.LoginType=kK(y)[0]->g; 
    req.ExchangeType=kK(y)[1]->i; 
    strcpy(req.BranchNo,kK(y)[2]->s); 
    strcpy(req.LoginCode,kK(y)[3]->s);
    strcpy(req.LoginPassword,kK(y)[4]->s);
    strcpy(req.MACAddress,kK(y)[5]->s);
    strcpy(req.IPAddress,kK(y)[6]->s);
    strcpy(req.MD5,kK(y)[7]->s);
    
    R ki(pTradeApi->ReqUserLogin(&req,(0<kK(y)[8]->i)?true:false,xi)); 
  }
  
  K2(userLogoutT){
    if(!run) R ki(-1);
      
    CJGtdcReqUserLogout req;

    strcpy(req.ClientID,kK(y)[0]->s); 
    strcpy(req.FundAccount,kK(y)[1]->s);
    
    R ki(pTradeApi->ReqUserLogout(&req,xi)); 
  }

  K2(reqSubscriptionT){
    if(!run) R ki(-1);
    
    CJGtdcReqUserSubData req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.SubType=kK(y)[1]->g;
    req.SubDataType=kK(y)[2]->i;
    
    R ki(pTradeApi->ReqSubscription(&req,xi)); 
 }

  K2(getUserAccountT){
    if(!run) R ki(-1);

    CJGtdcUserAccountInfo a;
    CJGtdcUserHolderInfo h[24];
    int nHolderItem;
    int r;

    r=pTradeApi->GetUserAccount(kK(y)[0]->s,a,&h[0],nHolderItem);
    if(!r){
      K L=knk(0);
      DO(nHolderItem,ja(&L,knk(7,ki(h[i].ExchangeType),kp(h[i].StockAccount),kp(h[i].HolderName),kp(h[i].SeatNo),kc(h[i].MoneyType),kc(h[i].HolderStatus),kc(h[i].MainType))));
      JGPUB("UserAccountT",knk(8,kp(a.FundAccount),kp(a.PassWord),kp(a.BranchNo),kp(a.ClientID),kp(a.ClientName),kp(a.BankCode),kc(a.AccountRights),L));  
    }
    R ki(r);
 }
  
  K2(orderInsert){
    if(!run) R ki(-1);
    
    CJGtdcReqOrderInsert req;
    strcpy(req.ClientID,kK(y)[0]->s);
    strcpy(req.BatchNo,kK(y)[1]->s);
    strcpy(req.StockCode,kK(y)[2]->s);
    req.ExchangeType=kK(y)[3]->i;
    req.TradeType=kK(y)[4]->i;
    req.PriceType=kK(y)[5]->i;
    req.OrderVolume=kK(y)[6]->j;
    req.OrderPrice=kK(y)[7]->j;
    
    R ki(pTradeApi->ReqOrderInsert(&req,1,xi)); 
 }

  K2(orderCancel){
    if(!run) R ki(-1);
    
    CJGtdcReqOrderCancel req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.ExchangeType=kK(y)[1]->i;
    strcpy(req.EntrustNo,kK(y)[2]->s);
    strcpy(req.BatchNo,kK(y)[3]->s);
    
    R ki(pTradeApi->ReqOrderCancel(&req,1,xi)); 
 }
  
  K2(qryCancel){
    if(!run) R ki(-1);
    
    CJGtdcReqQryCancel req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    strcpy(req.StockCode,kK(y)[2]->s);
    req.ExchangeType=kK(y)[3]->i;    
    strcpy(req.EntrustNo,kK(y)[4]->s);
    req.QueryDirection=kK(y)[5]->i;    
    req.QueryAmount=kK(y)[6]->i;    
    strcpy(req.PositionStr,kK(y)[7]->s);
    
    R ki(pTradeApi->ReqQryCancel(&req,xi)); 
 }
  
  K2(qryOrder){
    if(!run) R ki(-1);
    
    CJGtdcReqQryOrder req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    strcpy(req.StockCode,kK(y)[2]->s);
    req.ExchangeType=kK(y)[3]->i;    
    strcpy(req.EntrustNo,kK(y)[4]->s);
    req.QueryDirection=kK(y)[5]->i;    
    req.QueryAmount=kK(y)[6]->i;    
    strcpy(req.PositionStr,kK(y)[7]->s);
    
    R ki(pTradeApi->ReqQryOrder(&req,xi)); 
 }
  
  K2(qryTrade){
    if(!run) R ki(-1);
    
    CJGtdcReqQryTrade req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    strcpy(req.StockCode,kK(y)[2]->s);
    req.ExchangeType=kK(y)[3]->i;    
    strcpy(req.EntrustNo,kK(y)[4]->s);
    req.QueryDirection=kK(y)[5]->i;    
    req.QueryAmount=kK(y)[6]->i;    
    strcpy(req.PositionStr,kK(y)[7]->s);
    
    R ki(pTradeApi->ReqQryTrade(&req,xi)); 
 }
  
  K2(qryHold){
    if(!run) R ki(-1);
    
    CJGtdcReqQryHold req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    strcpy(req.StockCode,kK(y)[2]->s);
    req.ExchangeType=kK(y)[3]->i;    
    req.QueryDirection=kK(y)[4]->i;    
    req.QueryAmount=kK(y)[5]->i;    
    strcpy(req.PositionStr,kK(y)[6]->s);

    R ki(pTradeApi->ReqQryHold(&req,xi)); 
 }
  
  K2(qryFund){
    if(!run) R ki(-1);
    
    CJGtdcReqQryFund req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    req.MoneyType=kK(y)[1]->g;
    
    R ki(pTradeApi->ReqQryFund(&req,xi)); 
 }
  
  K2(qryMax){
    if(!run) R ki(-1);
    
    CJGtdcReqQryMax req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.ExchangeType=kK(y)[1]->i;
    strcpy(req.StockCode,kK(y)[2]->s);
    req.TradeType=kK(y)[3]->i;
    req.PriceType=kK(y)[4]->i;
    req.OrderPrice=kK(y)[5]->j;
    strcpy(req.BatchNo,kK(y)[6]->s);
    
    R ki(pTradeApi->ReqQryMax(&req,xi)); 
 }
  
}
