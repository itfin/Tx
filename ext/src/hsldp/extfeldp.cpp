#include "kqueue.h"
#include "HSSecuTradeApi.h"

#define APIPOOL_SIZE 256

ZI run=0,c;

ONMQ("onldp")

Z  CHSSecuTradeApi *pTradeApi,*ApiPool[APIPOOL_SIZE];ZI nAPI=0;   

#define MPUB(x,y) mpub(knk(3,ks(x),kj(poolidx),y));

#define LPUB(x,y) mpub(knk(3,ks(x),kj(poolidx),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));

#define RETURNONLDPERR(x) if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){DBG("[LdpError]ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);MPUB("LdpError",knk(3,ki(nRequestID),kb(bIsLast),knk(3,kp(x),ki(pRspInfo->ErrorID),kp((S)pRspInfo->ErrorMsg))));R;}

class CTradeHandler : public CHSSecuTradeSpi{
public: 
  J poolidx=-1;
  CTradeHandler(J i){poolidx=i;} 
  ~CTradeHandler(){}

  virtual void OnFrontConnected(){MPUB("FrontConnected",knk(0));};

  /// Description:当客户端与交易后台通信连接异常时，该方法被调用。
  /// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
  virtual void OnFrontDisconnected(int nResult){MPUB("FrontDisconnected",ki(nResult));};

  /// Description:接入认证
  virtual void OnRspAuthenticate(CHSSecuRspAuthenticateField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspAuthenticate");
    LPUB("RspAuthenticate",knk(3,kp(p->AccountID),kp(p->AppID),kp(p->AuthCode)));
  };

  /// Description:客户登录
  virtual void OnRspUserLogin(CHSSecuRspUserLoginField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspUserLogin");
    LPUB("RspUserLogin",knk(10,ki(p->BranchID),kp(p->AccountID),kc(p->AssetProp),kp(p->UserName),ki(p->TradingDay),kp(p->OrderRef),ki(p->SessionID),kp(p->UserID),ki(p->CorpRiskLevel),kp(p->UserNameLong)));
  };

  /// Description:证券账户信息查询
  virtual void OnRspQryStkAcct(CHSSecuRspQryStkAcctField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryStkAcct");
    LPUB("RspQryStkAcct",knk(3,kp(p->AccountID),kp(p->ExchangeID),kp(p->StockAccount)));
  };

  /// Description:报单录入
  virtual void OnRspOrderInsert(CHSSecuRspOrderInsertField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspOrderInsert");
    LPUB("RspOrderInsert",knk(8,ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),ki(p->BatchNo),kj(p->ClientOrderID),kp(p->OrderID),kp(p->ExtOrderRef)));
  };

  /// Description:报单撤单
  virtual void OnRspOrderAction(CHSSecuRspOrderActionField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspOrderAction");
    LPUB("RspOrderAction",knk(10,ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->OrigOrderPartition),kp(p->OrigBrokerOrderID),ki(p->OrigSessionID),kp(p->OrigOrderRef),kj(p->OrigClientOrderID),kp(p->OrderID),ki(p->OrigBatchNo),kp(p->OrigExtOrderRef)));
  };

  /// Description:资金查询
  virtual void OnRspQryFund(CHSSecuRspQryFundField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryFund");
    LPUB("RspQryFund",knk(8,kc(p->CurrencyID),kf(p->CurrentBalance),kf(p->BeginBalance),kf(p->AvailableBalance),kf(p->FetchBalance),kf(p->MarketValue),kf(p->TotalAsset),kf(p->CorrectBalance)));
  };

  /// Description:持仓查询
  virtual void OnRspQryHold(CHSSecuRspQryHoldField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryHold");
    LPUB("RspQryHold",knk(37,kp(p->AccountID),kp(p->ExchangeID),kp(p->StockAccount),kp(p->StockCode),kp(p->StockName),kp(p->StockType),kf(p->CurrentVolume),kf(p->AvailableVolume),kf(p->AvBuyPrice),kf(p->AssetPrice),kf(p->AchvProfit),kf(p->BeginVolume),kf(p->RealBuyVolume),kf(p->RealSellVolume),kf(p->UncomeBuyVolume),kf(p->UncomeSellVolume),kf(p->FloatProfit),kf(p->MarketValue),kf(p->LastPrice),ki(p->DelistDate),kf(p->CorrectVolume),kf(p->ETFPurRedAvailableVolume),kf(p->FrozenVolume),kf(p->CostBalance),kf(p->FinCompactAmount),kf(p->FinUncomeAmount),kf(p->FinCurrentAmount),kf(p->FinMarketValue),kf(p->CsfcSloAmount),kf(p->SloMarketValue),kf(p->SumBuyAmount),kf(p->SumBuyBalance),kf(p->SumSellAmount),kf(p->SumSellBalance),kp(p->StockNameShort),kf(p->RealBuyBalance),kf(p->RealSellBalance)));
  };

  /// Description:报单查询
  virtual void OnRspQryOrder(CHSSecuOrderField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryOrder");
    LPUB("RspQryOrder",knk(44,ki(p->TradingDay),kp(p->AccountID),ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->StockAccount),kp(p->StockCode),ki(p->Direction),kf(p->OrderPrice),kf(p->OrderVolume),kc(p->OrderStatus),ki(p->OrderCommand),ki(p->ReportTime),kp(p->ErrorMsg),kf(p->TradeVolume),ki(p->BatchNo),kf(p->WithdrawVolume),ki(p->OrderTime),kp(p->BrokerWithdrawOrderID),kf(p->FrozenBalance),kf(p->FrozenFare),ki(p->BranchID),kc(p->OrderAssStatus),kc(p->WithdrawOrderStatus),ki(p->OccurTime),kj(p->ClientOrderID),kp(p->StockName),kf(p->TradePrice),kf(p->BusinessBalance),kp(p->StockType),kp(p->OrderID),kc(p->CashgroupProp),kp(p->ExtOrderRef),kf(p->TotalBusinessFare),ki(p->SequenceNumber),kc(p->UserApplicationType),kc(p->RenewFlag),ki(p->StrategyId),kf(p->TotalRealBuyBalance),kf(p->TotalRealSellBalance),ki(p->SystemNo),ki(p->ErrorNo)));
  };

  /// Description:成交查询
  virtual void OnRspQryTrade(CHSSecuTradeField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryTrade");
    LPUB("RspQryTrade",knk(40,ki(p->TradingDay),kp(p->AccountID),ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->StockAccount),kp(p->StockCode),ki(p->Direction),ki(p->OrderCommand),kc(p->TradeStatus),kp(p->TradeID),kf(p->TradeVolume),kf(p->TradePrice),ki(p->TradeTime),kp(p->ErrorMsg),ki(p->BatchNo),kp(p->BrokerWithdrawOrderID),kf(p->BusinessBalance),ki(p->BranchID),kc(p->OrderStatus),ki(p->OccurTime),kj(p->ClientOrderID),kp(p->StockName),kf(p->OrderPrice),kp(p->OrderID),kp(p->ExtOrderRef),kf(p->TotalBusinessFare),ki(p->SequenceNumber),kf(p->RealBuyAmount),kf(p->RealBuyBalance),kf(p->RealSellAmount),kf(p->RealSellBalance),kc(p->UserApplicationType),kc(p->RenewFlag),ki(p->StrategyId),ki(p->SystemNo),kf(p->SumCashBalance),kp(p->CompactID)));
  };

  /// Description:主推-报单回报
  virtual void OnRtnOrder(CHSSecuOrderField *p) {
    MPUB("RtnOrder",knk(44,ki(p->TradingDay),kp(p->AccountID),ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->StockAccount),kp(p->StockCode),ki(p->Direction),kf(p->OrderPrice),kf(p->OrderVolume),kc(p->OrderStatus),ki(p->OrderCommand),ki(p->ReportTime),kp(p->ErrorMsg),kf(p->TradeVolume),ki(p->BatchNo),kf(p->WithdrawVolume),ki(p->OrderTime),kp(p->BrokerWithdrawOrderID),kf(p->FrozenBalance),kf(p->FrozenFare),ki(p->BranchID),kc(p->OrderAssStatus),kc(p->WithdrawOrderStatus),ki(p->OccurTime),kj(p->ClientOrderID),kp(p->StockName),kf(p->TradePrice),kf(p->BusinessBalance),kp(p->StockType),kp(p->OrderID),kc(p->CashgroupProp),kp(p->ExtOrderRef),kf(p->TotalBusinessFare),ki(p->SequenceNumber),kc(p->UserApplicationType),kc(p->RenewFlag),ki(p->StrategyId),kf(p->TotalRealBuyBalance),kf(p->TotalRealSellBalance),ki(p->SystemNo),ki(p->ErrorNo)));
    DBG("[RtnOrder](%i,%s,%s,%s,%s,%i,%f,%f,%c,%c,%i,%i,%s,%f,%f,%f,%f)\n",p->TradingDay,p->BrokerOrderID,p->OrderRef,p->ExchangeID,p->StockCode,p->Direction,p->OrderPrice,p->OrderVolume,p->OrderStatus,p->OrderAssStatus,p->OrderCommand,p->ReportTime,p->ErrorMsg,p->TradeVolume,p->WithdrawVolume,p->TradePrice,p->BusinessBalance);
  };

  /// Description:主推-成交回报
  virtual void OnRtnTrade(CHSSecuTradeField *p) {
    MPUB("RtnTrade",knk(40,ki(p->TradingDay),kp(p->AccountID),ki(p->OrderPartition),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->StockAccount),kp(p->StockCode),ki(p->Direction),ki(p->OrderCommand),kc(p->TradeStatus),kp(p->TradeID),kf(p->TradeVolume),kf(p->TradePrice),ki(p->TradeTime),kp(p->ErrorMsg),ki(p->BatchNo),kp(p->BrokerWithdrawOrderID),kf(p->BusinessBalance),ki(p->BranchID),kc(p->OrderStatus),ki(p->OccurTime),kj(p->ClientOrderID),kp(p->StockName),kf(p->OrderPrice),kp(p->OrderID),kp(p->ExtOrderRef),kf(p->TotalBusinessFare),ki(p->SequenceNumber),kf(p->RealBuyAmount),kf(p->RealBuyBalance),kf(p->RealSellAmount),kf(p->RealSellBalance),kc(p->UserApplicationType),kc(p->RenewFlag),ki(p->StrategyId),ki(p->SystemNo),kf(p->SumCashBalance),kp(p->CompactID)));
    DBG("[RtnTrade](%i,%s,%s,%s,%s,%i,%i,%c,%c,%i,%s,%f,%f,%f)\n",p->TradingDay,p->BrokerOrderID,p->OrderRef,p->ExchangeID,p->StockCode,p->Direction,p->OrderCommand,p->OrderStatus,p->TradeStatus,p->TradeTime,p->ErrorMsg,p->TradeVolume,p->TradePrice,p->BusinessBalance);
  };

  /// Description:快速交易多中心之间资金调拨
  virtual void OnRspFundAlloc(CHSSecuRspFundAllocField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspFundAlloc");
    LPUB("RspFundAlloc",knk(2,ki(p->FundTransSerialID),kj(0)));
  };
  /// Description:对端快速交易中心资金查询
  virtual void OnRspQryFundPeer(CHSSecuRspQryFundPeerField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryFundPeer");
    LPUB("RspQryFundPeer",knk(3,kf(p->CurrentBalance),kf(p->AvailableBalance),kc(p->CurrencyID)));
  };

  /// Description:锁券申请
  virtual void OnRspLockStockApply(CHSSecuRspLockStockApplyField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspLockStockApply");
    K L=knk(0);
    CHSSecuRspLockStockField *p1;
    DO(p->LockStockApplyRsp.size(),p1=&(p->LockStockApplyRsp[i]);jk(&L,knk(4,ki(p1->BatchNo),kp(p1->CompactID),ki(p1->ErrorNo),kp(p1->CompactRef))));
    LPUB("RspLockStockApply",L);
  };

  /// Description:锁券合约直接还券
  virtual void OnRspCompactDirectRepay(CHSSecuRspCompactDirectRepayField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    RETURNONLDPERR("RspCompactDirectRepay");
    K L=knk(0);
    CHSSecuRspDirectRepayField *p1;
    DO(p->CompactDirectRepayRsp.size(),p1=&(p->CompactDirectRepayRsp[i]);jk(&L,knk(3,kp(p1->CompactID),kf(p1->OccurVolume),kf(p1->PostVolume))));    
    LPUB("RspCompactDirectRepay",L);
  };

  /// Description:锁券合约了结申请
  virtual void OnRspLockCompactSettle(CHSSecuRspLockCompactSettleField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspLockCompactSettle");
    LPUB("RspLockCompactSettle",knk(2,kp(p->CompactID),kj(0)));
  };

  /// Description:可锁证券实时行情查询
  virtual void OnRspQryLockStockQuote(CHSSecuRspQryLockStockQuoteField*p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryLockStockQuote");
    LPUB("RspQryLockStockQuote",knk(11,kj(p->PositionSn),kp(p->ExchangeID),kp(p->StockCode),kp(p->StockName),kp(p->LockStockQuoteID),kf(p->AvailableVolume),ki(p->LimitDays),kf(p->LockYearRate),kf(p->BorrowYearRate),ki(p->MinInterestDays),kc(p->EarlyRecallMode)));
  };

  /// Description:锁券合约查询
  virtual void OnRspQryLockCompact(CHSSecuRspQryLockCompactField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryLockCompact");
    LPUB("RspQryLockCompact",knk(28,kj(p->PositionSn),kp(p->ExchangeID),kp(p->StockCode),kp(p->CompactID),kp(p->StockName),kc(p->LockCompactStatus),ki(p->RetEndDate),kf(p->LockYearRate),kf(p->BorrowYearRate),ki(p->MinInterestDays),kf(p->LockedVolume),kf(p->BorrowedVolume),kf(p->RepaidVolume),kf(p->EnableBorrowVolume),kf(p->EnableRepayVolume),kf(p->EnableBuyVolume),kf(p->LockCompactProfitLoss),kf(p->TodayBorrowStockInterest),kf(p->OccuredBorrowStockInterest),kf(p->TodayLockStockInterest),kf(p->OccuredLockStockInterest),kf(p->EnableDirectRepayVolume),kf(p->TodayTotalBuyVolume),kf(p->InitialPositionVolume),ki(p->CreateDate),ki(p->BatchNo),kp(p->CompactRef),kp(p->ErrorMsg)));
  };

  /// Description:保证金查询
  virtual void OnRspQryMargin(CHSSecuRspQryMarginField *p, CHSSecuRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspMargin");
    LPUB("RspQryMargin",knk(10,kf(p->EnableBalance),kf(p->BorrowSellSurplusBalance),kf(p->EnableRepayBalance),kf(p->EnableLockMargin),kf(p->EnableBorrowMargin),kf(p->OccuredBorrowStockInterest),kf(p->OccuredLockStockInterest),kf(p->TodayBorrowStockInterest),kf(p->TodayLockStockInterest),kf(p->LockCompactProfitLoss)));
  };

  /// Description:主推-锁券合约状态变更
  virtual void OnRtnLockCompact(CHSSecuLockCompactField *p) {
    MPUB("RtnLockCompact",knk(27,kp(p->ExchangeID),kp(p->StockCode),kp(p->CompactID),kp(p->StockName),kc(p->LockCompactStatus),ki(p->RetEndDate),kf(p->LockYearRate),kf(p->BorrowYearRate),ki(p->MinInterestDays),kf(p->LockedVolume),kf(p->BorrowedVolume),kf(p->RepaidVolume),kf(p->EnableBorrowVolume),kf(p->EnableRepayVolume),kf(p->EnableBuyVolume),kf(p->LockCompactProfitLoss),kf(p->TodayBorrowStockInterest),kf(p->OccuredBorrowStockInterest),kf(p->TodayLockStockInterest),kf(p->OccuredLockStockInterest),kf(p->EnableDirectRepayVolume),kf(p->TodayTotalBuyVolume),kf(p->InitialPositionVolume),ki(p->CreateDate),ki(p->BatchNo),kp(p->CompactRef),kp(p->ErrorMsg)));
  };
 
};

Z CTradeHandler * pTradeSpi,*SpiPool[APIPOOL_SIZE];;

extern "C"{
  K1(ldpapiver){
    R kp((S)GetSecuTradeApiVersion());
  }
  
  K1(ldplockfree){
#if defined(_USE_LOCKFREE_QUEUE)
    R ki(1);
#else
    R ki(0);    
#endif    
  }
  
  K1(ldperrmsg){
    if(!run) R ki(-1);
    R kp((S)pTradeApi->GetApiErrorMsg(xi));
  }
  
  K1(startstat){
    if(!run) R ki(-1);
    R ki(pTradeApi->StartTimeStat());
  }
  
  K1(stopstat){
    if(!run) R ki(-1);
    R ki(pTradeApi->StopTimeStat());
  }

  K1(exportstat){
    if(!run) R ki(-1);
    R ki(pTradeApi->ExportTimeStat());
  }
  
  K2(initldp){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
    
    if(run) R ki(-10001);
    if (r=kqinit()) R ki(r);    
    run++;

    nAPI=kK(x)[0]->n;
    DO(nAPI,ApiPool[i]=pTradeApi=NewSecuTradeApi(kS(kK(x)[0])[i]);if(NULL==pTradeApi) R ki(-10004);SpiPool[i]=pTradeSpi = new CTradeHandler(i);pTradeApi->RegisterSpi(pTradeSpi);r=(!strncmp("fens",kS(kK(x)[1])[i],4))?pTradeApi->RegisterFensServer(kS(kK(x)[1])[i],kS(y)[i]):pTradeApi->RegisterFront(kS(kK(x)[1])[i]);if(r)R ki(-abs(r));r=pTradeApi->RegisterSubModel((SUB_TERT_TYPE)kK(x)[2]->i);if(r)R ki(-abs(r));if(r=pTradeApi->Init("")) R ki(-abs(r)););
    R ki(run);
  }

  K1(freeldp){
    if(!run) R ki(-1);
    
    DO(nAPI,pTradeApi=ApiPool[i];pTradeApi->RegisterSpi(NULL);pTradeApi->ReleaseApi();ApiPool[i]=NULL;delete SpiPool[i];SpiPool[i]=NULL;);
    pTradeApi=NULL;pTradeSpi=NULL;

    kqfree();    
    run--;
    R ki(run);
  }

  K1(ldprun){
    R ki(run);
  } 

  K2(reqAuthenticate){
    if(!run) R ki(-1);
    CHSSecuReqAuthenticateField req;
    
    strcpy(req.AccountID,kK(y)[0]->s); 
    strcpy(req.AppID,kK(y)[1]->s); 
    strcpy(req.AuthCode,kK(y)[2]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqAuthenticate(&req,kI(x)[0]));
  } 

  K2(reqUserLogin){
    if(!run) R ki(-1);
    
    CHSSecuReqUserLoginField req;
    strcpy(req.AccountID,kK(y)[0]->s); 
    strcpy(req.Password,kK(y)[1]->s);
    req.UserApplicationType=kK(y)[2]->g;
    strcpy(req.UserApplicationInfo,kK(y)[3]->s); 
    strcpy(req.MacAddress,kK(y)[4]->s); 
    strcpy(req.IPAddress,kK(y)[5]->s); 
    strcpy(req.UserStationInfo,kK(y)[6]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqUserLogin(&req,kI(x)[0]));
  } 

  K2(reqQryStkAcct){
    if(!run) R ki(-1);
    
    CHSSecuReqQryStkAcctField req;
    strcpy(req.ExchangeID,kK(y)[0]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqQryStkAcct(&req,kI(x)[0]));
  } 

  K2(reqOrderInsert){
    if(!run) R ki(-1);
    
    CHSSecuReqOrderInsertField req;
    I r=-1;
    strcpy(req.ExchangeID,kK(y)[0]->s); 
    strcpy(req.StockCode,kK(y)[1]->s); 
    req.OrderCommand=kK(y)[2]->i;
    req.Direction=kK(y)[3]->i;
    req.OrderPrice=kK(y)[4]->f;
    req.OrderVolume=kK(y)[5]->f;
    strcpy(req.StockAccount,kK(y)[6]->s); 
    strcpy(req.OrderRef,kK(y)[7]->s); 
    req.UserApplicationType=kK(y)[8]->g;
    strcpy(req.UserStationInfo,kK(y)[9]->s); 
    strcpy(req.ExtOrderRef,kK(y)[10]->s); 
    req.StrategyId=kK(y)[11]->i;
    req.DTgwIndex=0;
    r=ApiPool[kI(x)[1]]->ReqOrderInsert(&req,kI(x)[0]);
    R ki(r);
  }

  K2(reqOrderAction){
    if(!run) R ki(-1);
    
    CHSSecuReqOrderActionField req;
    req.OrderPartition=kK(y)[0]->i;
    strcpy(req.BrokerOrderID,kK(y)[1]->s); 
    req.SessionID=kK(y)[2]->i;
    strcpy(req.OrderRef,kK(y)[3]->s);
    req.ClientOrderID=kK(y)[4]->j;    
    req.UserApplicationType=kK(y)[5]->g;
    strcpy(req.UserStationInfo,kK(y)[6]->s); 
    strcpy(req.StockCode,kK(y)[7]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqOrderAction(&req,kI(x)[0]));
  }

  K2(reqQryHold){
    if(!run) R ki(-1);
    
    CHSSecuReqQryHoldField req;
    strcpy(req.ExchangeID,kK(y)[0]->s); 
    strcpy(req.StockCode,kK(y)[1]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqQryHold(&req,kI(x)[0]));
  } 

  K2(reqQryFund){
    if(!run) R ki(-1);
    
    CHSSecuReqQryFundField req;
    req.CurrencyID=kK(y)[0]->g; 

    R ki(ApiPool[kI(x)[1]]->ReqQryFund(&req,kI(x)[0]));
  } 

  K2(reqQryOrder){
    if(!run) R ki(-1);
    
    CHSSecuReqQryOrderField req;
    req.OrderPartition=kK(y)[0]->i;
    strcpy(req.BrokerOrderID,kK(y)[1]->s); 
    req.SessionID=kK(y)[2]->i;
    strcpy(req.OrderRef,kK(y)[3]->s);
    req.ClientOrderID=kK(y)[4]->j;    

    R ki(ApiPool[kI(x)[1]]->ReqQryOrder(&req,kI(x)[0]));
  } 

  K2(reqQryTrade){
    if(!run) R ki(-1);
    
    CHSSecuReqQryTradeField req;
    req.OrderPartition=kK(y)[0]->i;
    strcpy(req.BrokerOrderID,kK(y)[1]->s); 
    req.SessionID=kK(y)[2]->i;
    strcpy(req.OrderRef,kK(y)[3]->s);
    req.ClientOrderID=kK(y)[4]->j;    

    R ki(ApiPool[kI(x)[1]]->ReqQryTrade(&req,kI(x)[0]));
  }   

  K2(reqFundAlloc){
    if(!run) R ki(-1);
    
    CHSSecuReqFundAllocField req;
    req.TransDirection=kK(y)[0]->g;
    req.CurrencyID=kK(y)[1]->g;
    req.OccurBalance=kK(y)[2]->f;
    req.SysnodeID=kK(y)[3]->i;    

    R ki(ApiPool[kI(x)[1]]->ReqFundAlloc(&req,kI(x)[0]));
  }   

  K2(reqQryFundPeer){
    if(!run) R ki(-1);
    
    CHSSecuReqQryFundPeerField req;
    req.SysnodeID=kK(y)[0]->i;    
    req.CurrencyID=kK(y)[1]->g;

    R ki(ApiPool[kI(x)[1]]->ReqQryFundPeer(&req,kI(x)[0]));
  }
  
  K2(reqLockStockApply){
    if(!run) R ki(-1);
    K L;
    CHSSecuReqLockStockApplyField req;
    DO(y->n,CHSSecuReqLockStockField r;L=kK(y)[i];r.BatchNo=kK(L)[0]->i;r.OrderVolume=kK(L)[1]->f;strcpy(r.LockStockQuoteID,kK(L)[2]->s);r.MinVolume=kK(L)[3]->f;strcpy(r.CompactRef,kK(L)[4]->s);req.LockStockApplyReq.push_back(r));

    R ki(ApiPool[kI(x)[1]]->ReqLockStockApply(&req,kI(x)[0]));
  }
  
  K2(reqCompactDirectRepay){
    if(!run) R ki(-1);
    
    CHSSecuReqCompactDirectRepayField req;
    strcpy(req.ExchangeID,kK(y)[0]->s);
    strcpy(req.StockCode,kK(y)[1]->s);
    strcpy(req.CompactID,kK(y)[2]->s); 
    req.OrderVolume=kK(y)[3]->f;

    R ki(ApiPool[kI(x)[1]]->ReqCompactDirectRepay(&req,kI(x)[0]));
  }
  
  K2(reqLockCompactSettle){
    if(!run) R ki(-1);
    
    CHSSecuReqLockCompactSettleField req;
    strcpy(req.CompactID,kK(y)[0]->s);    

    R ki(ApiPool[kI(x)[1]]->ReqLockCompactSettle(&req,kI(x)[0]));
  }
  
  K2(reqQryLockStockQuote){
    if(!run) R ki(-1);
    
    CHSSecuReqQryLockStockQuoteField req;
    req.PositionSn=kK(y)[0]->j;    
    req.RequestNumber=kK(y)[1]->i;
    strcpy(req.ExchangeID,kK(y)[2]->s); 
    strcpy(req.StockCode,kK(y)[3]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqQryLockStockQuote(&req,kI(x)[0]));
  }
  
 K2(reqQryLockCompact){
    if(!run) R ki(-1);
    
    CHSSecuReqQryLockCompactField req;
    req.PositionSn=kK(y)[0]->j;    
    req.RequestNumber=kK(y)[1]->i;
    strcpy(req.ExchangeID,kK(y)[2]->s); 
    strcpy(req.StockCode,kK(y)[3]->s); 
    strcpy(req.CompactID,kK(y)[4]->s); 
    req.CreateDate=kK(y)[5]->i;
    strcpy(req.CompactRef,kK(y)[6]->s); 
    
    R ki(ApiPool[kI(x)[1]]->ReqQryLockCompact(&req,kI(x)[0]));
  }
  
  K2(reqQryMargin){
    if(!run) R ki(-1);
    
    CHSSecuReqQryMarginField req;

    R ki(ApiPool[kI(x)[1]]->ReqQryMargin(&req,kI(x)[0]));
  }
  
 }
