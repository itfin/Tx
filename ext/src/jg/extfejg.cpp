#include "kcomm.h"
#include <queue>
#include "JGtdcTraderApi.h"
#include "JGtdcOptTraderApi.h"

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
Z CJGtdcOptTraderApi *pOptTradeApi=NULL;
ZJ sessid=0;
ZI isopt=0;

#define JGPUB(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));
#define RETURNONERR(s) if(JG_TDC_ANSRESULT_Success!=(h->ResultType)){mpub(knk(2,ks("JGError"),knk(3,ki(n),kp(s),kp(h->ErrorInfo))));R;}

class CTradeHandler : public CJGtdcTraderSpi,public CJGtdcOptTraderSpi{
public: 
  CTradeHandler(){} 
  ~CTradeHandler(){}

  virtual void OnFrontConnected() {JGPUB("FrontConnectedT",knk(0))};
  virtual void OnFrontDisConnected() {JGPUB("FrontDisConnectedT",knk(0))};
  virtual void OnRspError(const char* p){JGPUB("JGError",knk(3,ki(0),kp("RspError"),kp((S)p)))};
	///< 订阅推送数据应答

  virtual void OnRspSubscription(CJGtdcRspUserSubData* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("Subscription");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("SubscriptionT",knk(4,ki(n),ki(m),ki(i),ki(p->SubDataType)));p++);  
  }
	///< 用户登录应答
  virtual void OnRspUserLogin(CJGtdcRspUserLogin* p,CJGtdcRspInfoField* h,int n){
    if(NULL!=h)RETURNONERR("RspUserLogin");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("LoginT",knk(6,ki(n),ki(m),ki(i),kp(p->ClientID),kp(p->FundAccount),ki(p->SupportSubType)));p++);  
  };
	///< 用户登出应答
  virtual void OnRspUserLogout(CJGtdcRspUserLogout* p,CJGtdcRspInfoField* h,int n) {
    if(NULL!=h)RETURNONERR("RspUserLogout");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("LogoutT",knk(5,ki(n),ki(m),ki(i),kp(p->ClientID),kp(p->FundAccount)));p++);  
  };
	///< 报单录入应答
  virtual void OnRspOrderInsert(CJGtdcRspOrderInsert* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderInsert");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderInsert",knk(14,ki(n),ki(m),ki(i),ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->BatchNo),kp(p->StockAccount),kp(p->StockCode),ki(p->ExchangeType),ki(p->TradeType),ki(p->PriceType),kj(p->OrderVolume),kj(p->OrderPrice)));p++);
  };
	///< 报单撤销应答
  virtual void OnRspOrderCancel(CJGtdcRspOrderCancel* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderCancel");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderCancel",knk(8,ki(n),ki(m),ki(i),ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->NewEntrustNo),kp(p->BatchNo)));p++);
  };
	///< 投资者可撤单查询应答
  virtual void OnRspQryCancel(CJGtdcRspQryCancel* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryCancel");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryCancel",knk(26,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者委托查询应答
  virtual void OnRspQryOrder(CJGtdcRspQryOrder* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryOrder");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryOrder",knk(26,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者成交单查询应答
  virtual void OnRspQryTrade(CJGtdcRspQryTrade* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryTrade");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryTrade",knk(25,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance)));p++);
  };
	///< 投资者持仓查询
  virtual void OnRspQryHold(CJGtdcRspQryHold* p, CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspQryHold");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryHold",knk(24,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kp(p->StockAccount),kp(p->StockCode),kp(p->StockName),ki(p->ExchangeType),kc(p->MoneyType),kj(p->YdAmount),kj(p->StockAmount),kj(p->EnableAmount),kj(p->PurchaseAmount),kj(p->PossessAmount),kj(p->FrozenAmount),kj(p->YStoreAmount),kj(p->CostPrice),kj(p->KeepCostPrice),kf(p->BuyCost),kf(p->StockBalance),kf(p->FloatIncome),kf(p->ProIncome)));p++);
  };
	///< 投资者资金查询
  virtual void OnRspQryFund(CJGtdcRspQryFund* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryFund");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryFund",knk(20,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kc(p->MoneyType),kc(p->MainFlag),kf(p->EnableBalance),kf(p->FetchBalance),kf(p->FrozenBalance),kf(p->StockBalance),kf(p->FundBalance),kf(p->AssetBalance),kf(p->InCome),kf(p->EnableBalanceHK),kf(0.),kf(0.),kf(0.),kf(0.)));p++);
  };
	///< 投资者最大委托数查询应答
  virtual void OnRspQryMax(CJGtdcRspQryMax* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryMax");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryMax",knk(11,ki(n),ki(m),ki(i),kp(p->StockAccount),ki(p->ExchangeType),kp(p->StockCode),ki(p->TradeType),ki(p->PriceType),kj(p->OrderPrice),kp(p->BatchNo),kj(p->MaxAmount)));p++);
  };
	///< 投资者报单通知
  virtual void OnRtnOrder(CJGtdcRspQryOrder *p,int m) {
    DO(m,JGPUB("Order",knk(25,ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance),ki(p->ServiceType)));p++);
  };
	///< 投资者成交通知
  virtual void OnRtnTrade(CJGtdcRspQryTrade *p,int m) {
    DO(m,JGPUB("Trade",knk(24,ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->OrderVolume),kj(p->OrderPrice),kj(p->BusinessVolume),kj(p->BusinessPrice),kj(p->CancelVolume),kf(p->BusinessBalance)));p++);
  };


  ////////////////////////////////////融资融券专用///////////////////////////////////////////////////////////
  ///< 投资者融资融券资产查询
  virtual void OnRspQryAssets(CJGtdcRspQryAssets* pRspQryAssets, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者融券可卖数量查询
  virtual void OnRspQryMaxLoan(CJGtdcRspQryMaxLoan* p,CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspQryMaxLoan");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryMaxLoan",knk(7,ki(n),ki(m),ki(i),ki(p->ExchangeType),kp(p->StockCode),kp(p->StockName),kj(p->MaxLoanAmount)));p++);    
  };
  ///< 投资者可融券私有卖出数量查询
  virtual void OnRspQryReserveCreditStock(CJGtdcRspQryReserveCreditStock *p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryReserveCreditStock");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryReserveCreditStock",knk(10,ki(n),ki(m),ki(i),ki(p->ExchangeType),kp(p->StockCode),kp(p->StockName),kj(p->ReserveAmount),kj(p->ReserveRemainAmount),ki(p->StartDate),ki(p->EndDate)));p++);    

  };
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
  virtual void OnRspQryObject(CJGtdcRspQryObject *p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryObject");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryObject",knk(11,ki(n),ki(m),ki(i),ki(p->ExchangeType),kp(p->StockCode),kp(p->StockName),kp(p->PositionStr),ki(p->ObjectRights),kf(p->FinanceBailRatio),kf(p->ShortsellBailRatio),kf(p->MortgageRatio)));p++);    
  };
  ///< 投资者信用账户与普通账户对应关系查询应答
  virtual void OnRspQryAccMatch(CJGtdcRspQryAccMatch *pRspQryAccMatch, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };

  ////////////////////////港股通专用功能函数//////////////////////////////////////////////////////////////
  ///< 投资者港股通可撤单查询
  virtual void OnRspQryHKCancel(CJGtdcRspQryCancel* pRspQryCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者港股通委托查询
  virtual void OnRspQryHKOrder(CJGtdcRspQryOrder* pRspQryOrder, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者港股通成交单查询
  virtual void OnRspQryHKTrade(CJGtdcRspQryTrade* pRspQryTrade, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者港股通持仓查询
  virtual void OnRspQryHKHold(CJGtdcRspQryHold* pRspQryHold, CJGtdcRspInfoField* pRspInfo, int nRequestID){ };
  ///< 投资者港股通资金查询
  virtual void OnRspQryHKFund(CJGtdcRspQryFund* pRspQryFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者港股通汇率查询
  virtual void OnRspQryHKExRate(CJGtdcRspQryHKExRate* pRspQryHKExRate, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者港股通额度查询
  virtual void OnRspQryHKLimit(CJGtdcRspQryHKLimit* pRspQryHKLimit, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };

  ///Opt callback   
  virtual void OnRspError(const std::string& strError){JGPUB("JGError",knk(3,ki(0),kp("RspError"),kp((S)strError.c_str())))};
  ///< 用户登录应答
  virtual void OnRspOptionUserLogin(CJGtdcRspUserLogin* p, CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspOptionUserLogin");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("LoginT",knk(6,ki(n),ki(m),ki(i),kp(p->ClientID),kp(p->FundAccount),ki(p->SupportSubType)));p++);  
  };
  ///< 用户登出应答
  virtual void OnRspOptionUserLogout(CJGtdcRspUserLogout* p, CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspOptionUserLogout");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("LogoutT",knk(5,ki(n),ki(m),ki(i),kp(p->ClientID),kp(p->FundAccount)));p++);  
  };
  ///< 投资者期权合约查询应答
  virtual void OnRspOptionQryContract(CJGtdcOptionRspQryContract* p, CJGtdcRspInfoField* h, int n){
    if(NULL!=h)RETURNONERR("RspOptionQryContract");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OptionQryContract",knk(35,ki(n),ki(m),ki(i),ki(p->ExchangeType),kp(p->ContractNumber),kp(p->ContractCode),kp(p->ContractName),kc(p->OptionType),kp(p->StockCode),kp(p->StockName),kc(p->StockType),kp(p->PositionStr),kc(p->MoneyType),ki(p->AmountMultiple),ki(p->OptionVersion),ki(p->TradeBeginDate),ki(p->TradeEndDate),ki(p->ExerciseBeginDate),ki(p->ExerciseEndDate),kj(p->OptionPreClosePrice),kj(p->StockPreClosePrice),kj(p->OptionUpPrice),kj(p->OptionDownPrice),kj(p->ExercisePrice),kf(p->UnitBail),kj(p->MaxMarketEntrustAmount),kj(p->MinMarketEntrustAmount),kj(p->MaxLimitEntrustAmount),kj(p->MinLimitEntrustAmount),kc(p->OptionStatus),kc(p->OptionMode),kc(p->OpenType),kc(p->SuspendedType),kc(p->ExpireType),kc(p->AdjustType)));p++);  
  };
  ///< 投资者期权委托下单应答
  virtual void OnRspOptionEntrust(CJGtdcOptionRspEntrust* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderInsert");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderInsert",knk(14,ki(n),ki(m),ki(i),ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->BatchNo),kp(p->StockAccount),kp(p->ContractNumber),ki(p->ExchangeType),ki(p->TradeType),ki(p->PriceType),kj(p->EntrustAmount),kj(p->EntrustPrice)));p++);
  };
  ///< 投资者期权委托撤单应答
  virtual void OnRspOptionCancel(CJGtdcOptionRspCancel* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspOrderCancel");if((NULL==p)||(NULL==h))R;
    int m=h->nFieldItem;DO(m,JGPUB("OrderCancel",knk(8,ki(n),ki(m),ki(i),ki(p->ResultType),kp(p->ErrorInfo),kp(p->EntrustNo),kp(p->NewEntrustNo),kp(p->BatchNo)));p++);    
  };
  ///< 投资者期权最大交易数量查询应答
  virtual void OnRspOptionQryMax(CJGtdcOptionRspQryMax* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryMax");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryMax",knk(11,ki(n),ki(m),ki(i),kp(p->StockAccount),ki(p->ExchangeType),kp(p->ContractNumber),ki(p->TradeType),ki(p->PriceType),kj(p->EntrustPrice),kp(p->BatchNo),kj(p->MaxAmount)));p++);    
  };
  ///< 投资者期权备兑证券划转应答
  virtual void OnRspOptionCoveredTrans(CJGtdcOptionRspCoveredTrans* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权备兑可划转数量查询应答
  virtual void OnRspOptionQryCoveredMax(CJGtdcOptionRspQryCoveredMax* p, CJGtdcRspInfoField* h, int n) {};
  ///< 投资者期权资金查询应答
  virtual void OnRspOptionQryFund(CJGtdcOptionRspQryFund* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryFund");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryFund",knk(20,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kc(p->MoneyType),kc(p->MainFlag),kf(p->EnableBalance),kf(p->FetchBalance),kf(p->FrozenBalance),kf(p->StockBalance),kf(p->FundBalance),kf(p->AssetBalance),kf(p->Income),kf(p->EnableBail),kf(p->UsedBail),kf(p->AgreeAssureRatio),kf(p->RiskRatio),kf(p->RiskRatio1)));p++);    
  };
  ///< 投资者期权持仓查询应答
  virtual void OnRspOptionQryHold(CJGtdcOptionRspQryHold* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryHold");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryHold",knk(24,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),kp(p->StockAccount),kp(p->ContractNumber),kp(p->ContractName),ki(p->ExchangeType),kc(p->MoneyType),kj(p->OptionYDAmount),kj(p->OptionAmount),kj(p->EnableAmount),kj(p->TodayOpenAmount),kj(p->PossessAmount),kj(p->FrozenAmount),kj(p->PremiumBalance),kj(p->CostPrice),kj(p->BailBalance),kf(p->BuyCost),kf(p->OptionBalance),kf(p->HoldIncome),kf(p->PayoffIncome)));p++);
  };
  ///< 投资者期权委托查询应答
  virtual void OnRspOptionQryEntrust(CJGtdcOptionRspQryEntrust* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryOrder");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryOrder",knk(26,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->ContractNumber),kp(p->ContractName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->EntrustAmount),kj(p->EntrustPrice),kj(p->BusinessAmount),kj(p->BusinessPrice),kj(p->CancelAmount),kf(p->BusinessBalance),ki(0)));p++);    
  };
  ///< 投资者期权可撤单查询应答
  virtual void OnRspOptionQryRevocEnt(CJGtdcOptionRspQryRevocEnt* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryCancel");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryCancel",knk(26,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->ContractNumber),kp(p->ContractName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->EntrustAmount),kj(p->EntrustPrice),kj(p->BusinessAmount),kj(p->BusinessPrice),kj(p->CancelAmount),kf(p->BusinessBalance),ki(0)));p++);    
  };
  ///< 投资者期权增量成交查询应答
  virtual void OnRspOptionQryBusByPos(CJGtdcOptionRspQryBusByPos* p, CJGtdcRspInfoField* h, int n) {
    if(NULL!=h)RETURNONERR("RspQryTrade");if((NULL==p)||(NULL==h))R;    
    int m=h->nFieldItem;DO(m,JGPUB("QryTrade",knk(25,ki(n),ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->ContractNumber),kp(p->ContractName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->EntrustAmount),kj(p->EntrustPrice),kj(p->BusinessAmount),kj(p->BusinessPrice),kj(p->CancelAmount),kf(p->BusinessBalance)));p++);    
  };
  ///< 投资者期权备兑持仓查询应答
  virtual void OnRspOptionQryCoveredHold(CJGtdcOptionRspQryCoveredHold* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权行权指派查询应答
  virtual void OnRspOptionQryExerciseAssign(CJGtdcOptionRspQryExerciseAssign* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权备兑持仓不足查询应答
  virtual void OnRspOptionQryLackCoveredStock(CJGtdcOptionRspQryLackCoveredStock* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权可取资金查询应答
  virtual void OnRspOptionQryFetchFund(CJGtdcOptionRspQryFetchFund* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权历史委托查询应答
  virtual void OnRspOptionQryHisEntrust(CJGtdcOptionRspQryHisEntrust* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权历史成交查询应答
  virtual void OnRspOptionQryHisBusiness(CJGtdcOptionRspQryHisBusiness* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权历史行权指派查询应答
  virtual void OnRspOptionQryHisExerciseAssign(CJGtdcOptionRspQryHisExerciseAssign* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权增加自动行权应答
  virtual void OnRspOptionAddAutoExercise(CJGtdcOptionRspAddAutoExercise* p, CJGtdcRspInfoField* h, int n) { };
  ///< 投资者期权修改自动行权应答
  virtual void OnRspOptionModAutoExercise(CJGtdcOptionRspModAutoExercise* pRspModAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权删除自动行权应答
  virtual void OnRspOptionDelAutoExercise(CJGtdcOptionRspDelAutoExercise* pRspDelAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权自动行权查询应答
  virtual void OnRspOptionQryAutoExercise(CJGtdcOptionRspQryAutoExercise* pRspQryAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权备兑可划转查询应答
  virtual void OnRspOptionQryCovered(CJGtdcOptionRspQryCovered* pRspQryCovered, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权昨日持仓查询应答
  virtual void OnRspOptionQryHisHold(CJGtdcOptionRspQryHisHold* pRspQryHisHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权结算单查询应答
  virtual void OnRspOptionQrySettlement(CJGtdcOptionRspQrySettlement* pRspQrySettlement, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权交割单查询应答
  virtual void OnRspOptionQryDelivery(CJGtdcOptionRspQryDelivery* pRspQryDelivery, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权调拨资金应答
  virtual void OnRspOptionTransferFund(CJGtdcOptionRspTransferFund* pRspTransferFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权个股组合拆分委托应答
  virtual void OnRspOptionShareCombSplitEntrust(CJGtdcOptionRspShareCombSplitEntrust* pRspShareCombSplitEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权个股组合持仓明细查询应答
  virtual void OnRspOptionQryShareCombSplitHold(CJGtdcOptionRspQryShareCombSplitHold* pQryShareCombSplitHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权个股可组合可拆分手数查询应答
  virtual void OnRspOptionQryShareCombSplitLots(CJGtdcOptionRspQryShareCombSplitLots* pRspQryShareCombSplitLots, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权个股客户资金变动流水历史查询应答
  virtual void OnRspOptionQryShareUserHisFundChange(CJGtdcOptionRspQryShareUserHisFundChange* pRspQryShareUserHisFundChange, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权结算单确认应答
  virtual void OnRspOptionSettlementConfrim(CJGtdcOptionRspSettlementConfrim* pRspSettlementConfrim, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者委托通知
  virtual void OnRtnOptionOrder(CJGtdcOptionRspQryEntrust* p, int m){
    DO(m,JGPUB("Order",knk(25,ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->ContractNumber),kp(p->ContractName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->EntrustStatus),ki(p->TradeType),ki(p->PriceType),ki(p->EntrustDate),ki(p->EntrustTime),kj(p->EntrustAmount),kj(p->EntrustPrice),kj(p->BusinessAmount),kj(p->BusinessPrice),kj(p->CancelAmount),kf(p->BusinessBalance),ki(0)));p++);
  };
  ///< 投资者成交通知
  virtual void OnRtnOptionTrade(CJGtdcOptionRspQryBusByPos* p, int m){
    DO(m,JGPUB("Trade",knk(24,ki(m),ki(i),kp(p->BranchNo),kp(p->ClientID),kp(p->FundAccount),ki(p->ExchangeType),kp(p->StockAccount),kp(p->SeatNo),kp(p->ContractNumber),kp(p->ContractName),kp(p->PositionStr),kp(p->EntrustNo),kc(p->MoneyType),kc(p->BusinessStatus),ki(p->TradeType),ki(p->PriceType),ki(p->BusinessDate),ki(p->BusinessTime),kj(p->EntrustAmount),kj(p->EntrustPrice),kj(p->BusinessAmount),kj(p->BusinessPrice),kj(p->CancelAmount),kf(p->BusinessBalance)));p++);
  };


  ///< 投资者期权银行账号查询应答
  virtual void OnRspOptionQryBankAccount(CJGtdcOptionRspQryBankAccount* pRspQryBankAccount, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权银衍转账应答
  virtual void OnRspOptionBankTrans(CJGtdcOptionRspBankTrans* pRspBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权银衍转账查询应答
  virtual void OnRspOptionQryBankTrans(CJGtdcOptionRspQryBankTrans* pRspQryBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权银衍转账可转资金应答
  virtual void OnRspOptionQryBankMaxTrans(CJGtdcOptionRspQryBankMaxTrans* pRspQryBankMaxTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权查询子账户及其资金应答
  virtual void OnRspOptionQryChildBankFund(CJGtdcOptionRspQryChildBankFund* pRspQryChildBankFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
  ///< 投资者期权同名账户资金内转应答
  virtual void OnRspOptionQryInTransferFund(CJGtdcOptionRspInTransferFund* pRspInTransferFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
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

    if((2<y->n)&&kK(y)[2]->g)isopt=1;

    if(isopt){
      pOptTradeApi = CJGtdcOptTraderApi::CreatetdcTraderApi();
      if(NULL==pOptTradeApi) R ki(-10004);

      if(!pOptTradeApi->Init()) R ki(-10005);
      mpub(knk(2,ks("JGTInit"),knk(1,kp((S)pOptTradeApi->GetVersion(v0,v1)))));
      
      pTradeSpi = new CTradeHandler();
      pOptTradeApi->RegisterCallBack(pTradeSpi);

      if(!pOptTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);
    }else{      
      pTradeApi = CJGtdcTraderApi::CreatetdcTraderApi();
      if(NULL==pTradeApi) R ki(-10004);

      if(!pTradeApi->Init()) R ki(-10005);
      mpub(knk(2,ks("JGTInit"),knk(1,kp((S)pTradeApi->GetVersion(v0,v1)))));
      
      pTradeSpi = new CTradeHandler();
      pTradeApi->RegisterCallBack(pTradeSpi);

      if(!pTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);

      pTradeApi->OpenOrderSequential(true);
    }  
    R ki(run);
  }

  K1(freejgt){
    if(!run) R ki(-1);

    if(isopt){
      pOptTradeApi->Disconnect();
      pOptTradeApi->RegisterCallBack(NULL);
      pOptTradeApi->Fini();
      pOptTradeApi->Release();
      pOptTradeApi=NULL;
    }else{  
      pTradeApi->Disconnect();
      pTradeApi->RegisterCallBack(NULL);
      pTradeApi->Fini();
      pTradeApi->Release();
      pTradeApi=NULL;
    }
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
    if(!run) R ki(-1);
    if(isopt){
      if(NULL==pOptTradeApi) R ki(-10005);
      if(!pOptTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);
    }else{
      if(NULL==pTradeApi) R ki(-10005);
      if(!pTradeApi->Connect(kK(y)[0]->s,kK(y)[1]->h)) R ki(-10006);
    }
    R ki(0);
  }
  
  K2(userLoginT){
    if(!run) R ki(-1);

      CJGtdcReqUserLogin req;

      //pTradeApi->SetUserMachineInfo(NULL);
      
      req.LoginType=kK(y)[0]->g; 
      req.ExchangeType=kK(y)[1]->i; 
      strcpy(req.BranchNo,kK(y)[2]->s); 
      strcpy(req.LoginCode,kK(y)[3]->s);
      strcpy(req.LoginPassword,kK(y)[4]->s);
      strcpy(req.MACAddress,kK(y)[5]->s);
      strcpy(req.IPAddress,kK(y)[6]->s);
      strcpy(req.MD5,kK(y)[7]->s);
    
    if(isopt)R ki(pOptTradeApi->ReqOptionUserLogin(&req,xi));	  

    R ki(pTradeApi->ReqUserLogin(&req,(0<kK(y)[8]->i)?true:false,xi));
  }
  
  K2(userLogoutT){
    if(!run) R ki(-1);
      
    CJGtdcReqUserLogout req;

    strcpy(req.ClientID,kK(y)[0]->s); 
    strcpy(req.FundAccount,kK(y)[1]->s);
    if(isopt)R ki(pOptTradeApi->ReqOptionUserLogout(&req,xi)); 
    R ki(pTradeApi->ReqUserLogout(&req,xi)); 
  }

  K2(reqSubscriptionT){
    if(!run) R ki(-1);
    
    CJGtdcReqUserSubData req;
    strcpy(req.ClientID,kK(y)[0]->s);
    req.SubType=kK(y)[1]->g;
    req.SubDataType=kK(y)[2]->i;

    if(isopt)R ki(pOptTradeApi->ReqSubscription(&req,xi)); 
    R ki(pTradeApi->ReqSubscription(&req,xi)); 
 }

  K2(getUserAccountT){
    if(!run) R ki(-1);

    CJGtdcUserAccountInfo a;
    CJGtdcUserHolderInfo h[24];
    int nHolderItem;
    int r;

    if(isopt) r=pOptTradeApi->GetUserAccount(kK(y)[0]->s,a,&h[0],nHolderItem);
    else  r=pTradeApi->GetUserAccount(kK(y)[0]->s,a,&h[0],nHolderItem);
    
    if(!r){
      K L=knk(0);
      DO(nHolderItem,ja(&L,knk(7,ki(h[i].ExchangeType),kp(h[i].StockAccount),kp(h[i].HolderName),kp(h[i].SeatNo),kc(h[i].MoneyType),kc(h[i].HolderStatus),kc(h[i].MainType))));
      JGPUB("UserAccountT",knk(8,kp(a.FundAccount),kp(a.PassWord),kp(a.BranchNo),kp(a.ClientID),kp(a.ClientName),kp(a.BankCode),kc(a.AccountRights),L));  
    }
    R ki(r);
 }
  
  K2(orderInsert){
    if(!run) R ki(-1);

    if(isopt){
      CJGtdcOptionReqEntrust req;
      strcpy(req.ClientID,kK(y)[0]->s);
      strcpy(req.BatchNo,kK(y)[1]->s);
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.ExchangeType=kK(y)[3]->i;
      req.TradeType=kK(y)[4]->i;
      req.PriceType=kK(y)[5]->i;
      req.EntrustAmount=kK(y)[6]->j;
      req.EntrustPrice=kK(y)[7]->j;
      req.OffsetType=kK(y)[8]->g;
      req.CoveredType=kK(y)[9]->g;
    
      R ki(pOptTradeApi->ReqOptionEntrust(&req,1,xi));      
    }else{
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
 }

  K2(orderCancel){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqCancel req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.ExchangeType=kK(y)[1]->i;
      strcpy(req.EntrustNo,kK(y)[2]->s);
      strcpy(req.BatchNo,kK(y)[3]->s);
    
      R ki(pOptTradeApi->ReqOptionCancel(&req,1,xi));
    }else{ 
      CJGtdcReqOrderCancel req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.ExchangeType=kK(y)[1]->i;
      strcpy(req.EntrustNo,kK(y)[2]->s);
      strcpy(req.BatchNo,kK(y)[3]->s);
    
      R ki(pTradeApi->ReqOrderCancel(&req,1,xi));
    }
 }
  
  K2(qryCancel){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqQryRevocEnt req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.ExchangeType=kK(y)[3]->i;    
      strcpy(req.EntrustNo,kK(y)[4]->s);
      req.QueryDirection=kK(y)[5]->i;    
      req.QueryAmount=kK(y)[6]->i;    
      strcpy(req.PositionStr,kK(y)[7]->s);
    
      R ki(pOptTradeApi->ReqOptionQryRevocEnt(&req,xi));
    }else{  
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
 }
  
  K2(qryOrder){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqQryEntrust req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.ExchangeType=kK(y)[3]->i;    
      strcpy(req.EntrustNo,kK(y)[4]->s);
      req.QueryDirection=kK(y)[5]->i;    
      req.QueryAmount=kK(y)[6]->i;    
      strcpy(req.PositionStr,kK(y)[7]->s);
    
      R ki(pOptTradeApi->ReqOptionQryEntrust(&req,xi));
    }else{  
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
 }
  
  K2(qryTrade){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqQryBusByPos req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.ExchangeType=kK(y)[3]->i;    
      strcpy(req.EntrustNo,kK(y)[4]->s);
      req.QueryDirection=kK(y)[5]->i;    
      req.QueryAmount=kK(y)[6]->i;    
      strcpy(req.PositionStr,kK(y)[7]->s);
    
      R ki(pOptTradeApi->ReqOptionQryBusByPos(&req,xi));      
    }else{  
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
 }
  
  K2(qryHold){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqQryHold req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.ExchangeType=kK(y)[3]->i;    
      req.QueryDirection=kK(y)[4]->i;    
      req.QueryAmount=kK(y)[5]->i;    
      strcpy(req.PositionStr,kK(y)[6]->s);

      R ki(pOptTradeApi->ReqOptionQryHold(&req,xi));
    }else{  
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
 }
  
  K2(qryFund){
    if(!run) R ki(-1);
    
    if(isopt){
      CJGtdcOptionReqQryFund req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      req.MoneyType=kK(y)[1]->g;
    
      R ki(pOptTradeApi->ReqOptionQryFund(&req,xi));
    }else{  
      CJGtdcReqQryFund req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.QueryMode=kK(y)[1]->i;
      req.MoneyType=kK(y)[1]->g;
    
      R ki(pTradeApi->ReqQryFund(&req,xi));
    }
 }
  
  K2(qryMax){
    if(!run) R ki(-1);

    if(isopt){
      CJGtdcOptionReqQryMax req;
      strcpy(req.ClientID,kK(y)[0]->s);
      req.ExchangeType=kK(y)[1]->i;
      strcpy(req.ContractNumber,kK(y)[2]->s);
      req.TradeType=kK(y)[3]->i;
      req.PriceType=kK(y)[4]->i;
      req.EntrustPrice=kK(y)[5]->j;
      strcpy(req.BatchNo,kK(y)[6]->s);
      req.OffsetType=kK(y)[7]->g;
      req.CoveredType=kK(y)[8]->g;
      
    
      R ki(pOptTradeApi->ReqOptionQryMax(&req,xi));
    }else{
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

  K2(qryOptionContract){
    if(!run) R ki(-1);

    if(!isopt) R ki(0);

    CJGtdcOptionReqQryContract req;
    
    strcpy(req.ClientID,kK(y)[0]->s);
    req.ExchangeType=kK(y)[1]->i;

    R ki(pOptTradeApi->ReqOptionQryContract(&req,xi));
  }

  K2(qryObject){
    if(!run) R ki(-1);

    if(isopt) R ki(0);

    CJGtdcReqQryObject req;
    
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    req.ExchangeType=kK(y)[2]->i;    
    strcpy(req.StockCode,kK(y)[3]->s);
    req.QueryDirection=kK(y)[4]->i;    
    req.QueryAmount=kK(y)[5]->i;    
    strcpy(req.PositionStr,kK(y)[6]->s);

    R ki(pTradeApi->ReqQryObject(&req,xi));
  }  

  K2(qryMaxLoan){
    if(!run) R ki(-1);

    if(isopt) R ki(0);

    CJGtdcReqQryMaxLoan req;
    
    strcpy(req.ClientID,kK(y)[0]->s);
    req.QueryMode=kK(y)[1]->i;
    req.ExchangeType=kK(y)[2]->i;    
    strcpy(req.StockCode,kK(y)[3]->s);
    req.QueryAmount=kK(y)[4]->i;    

    R ki(pTradeApi->ReqQryMaxLoan(&req,xi));
  }  

  K2(qryReserveCreditStock){
    if(!run) R ki(-1);

    if(isopt) R ki(0);

    CJGtdcReqQryReserveCreditStock req;
    
    strcpy(req.ClientID,kK(y)[0]->s);
    req.ExchangeType=kK(y)[1]->i;    
    strcpy(req.StockCode,kK(y)[2]->s);

    R ki(pTradeApi->ReqQryReserveCreditStock(&req,xi));
  }  

}
