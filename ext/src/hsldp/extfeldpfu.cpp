#include "kcomm.h"
#include <queue>
#include "HSTradeApi.h"
#include "HsFutuSystemInfo.h"
#include "DataCollect.h"

#define APIPOOL_SIZE 256
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
  read(i,&b,PIPE_CAPACITY);
  LOCK;
  while (!mq.empty()){
    jk(&L,d9(mq.front()));
    mq.pop();
  }
  UNLOCK;    
  k(0,"onldp",L,(K)0);
  R ki(0);
}

Z V mpub(K x){
  LOCK;
  mq.push(b9(1,x));
  UNLOCK;    
  write(p[1],&b,1);
};

Z  CHSTradeApi *pTradeApi,*ApiPool[APIPOOL_SIZE];ZI nAPI=0;   

#define MPUB(x,y) mpub(knk(3,ks(x),kj(i),y));

#define LPUB(x,y) mpub(knk(3,ks(x),kj(i),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));

#define RETURNONLDPERR(x) if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);MPUB("LdpError",knk(3,ki(nRequestID),kb(bIsLast),knk(3,kp(x),ki(pRspInfo->ErrorID),kp((S)pRspInfo->ErrorMsg))));R;}

class CTradeHandler : public CHSTradeSpi{
public: 
  J i=-1;
  CTradeHandler(J j){i=j;} 
  ~CTradeHandler(){}

  virtual void OnFrontConnected(){O("OnFrontConnected\n");MPUB("FrontConnected",knk(0));};

  /// Description:当客户端与交易后台通信连接异常时，该方法被调用。
  /// Others     :通过GetApiErrorMsg(nResult)获取详细错误信息。
  virtual void OnFrontDisconnected(int nResult){O("OnFrontDisconnected\n");MPUB("FrontDisconnected",ki(nResult));};

  /// Description:接入认证
  virtual void OnRspAuthenticate(CHSRspAuthenticateField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspAuthenticate");
    LPUB("RspAuthenticate",knk(3,kp(p->AccountID),kp(p->AppID),kp(p->AuthCode)));
  };

  /// Description:终端信息上报接口(中继模式)
  virtual void OnRspSubmitUserSystemInfo(CHSRspUserSystemInfoField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    RETURNONLDPERR("RspSubmitUserSystemInfo");
    LPUB("RspSubmitUserSystemInfo",knk(0));
  };

  
  /// Description:客户登录
  virtual void OnRspUserLogin(CHSRspUserLoginField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspUserLogin");
    LPUB("RspUserLogin",knk(21,ki(p->BranchID),kp(p->AccountID),kp(p->UserName),ki(p->TradingDay),ki(p->PreTradingDay),kc(p->BillConfirmFlag),ki(p->SessionID),kc(p->UserApplicationType),kp(p->UserApplicationInfo),kp(p->RiskLevel),kp(p->LastMacAddress),kp(p->LastIPAddress),ki(p->LastLoginTime),ki(p->CZCETime),ki(p->DCETime),ki(p->SHFETime),ki(p->CFFEXTime),ki(p->INETime),kp(p->MaxOrderRef),kp(p->UserID),ki(p->GFEXTime)));
  };

  /// Description:报单录入
  virtual void OnRspErrorOrderInsert(CHSRspOrderInsertField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspErrorOrderInsert");
    LPUB("RspErrorOrderInsert",knk(21,kp(p->AccountID),kp(p->OrderSysID),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->InstrumentID),kp(p->ExchangeID),kc(p->Direction),kc(p->OffsetFlag),kc(p->HedgeType),kf(p->OrderPrice),kf(p->OrderVolume),kc(p->OrderStatus),ki(p->OrderCommand),ki(p->InsertTime),kf(p->MinVolume),kf(p->SpringPrice),kc(p->SwapOrderFlag),kp(p->CombPositionID),kp(p->ExchangeAccountID),ki(p->SeatIndex)));
  };

  /// Description:报单撤单
  virtual void OnRspOrderAction(CHSRspOrderActionField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("OrderAction");
    LPUB("RspOrderAction",knk(8,kp(p->AccountID),kp(p->OrderSysID),kp(p->ExchangeID),ki(p->SessionID),kp(p->OrderRef),kc(p->OrderStatus),ki(p->InsertTime),kp(p->OrderActionRef)));
  };

  /// Description:资金查询
  virtual void OnRspQryTradingAccount(CHSRspQryTradingAccountField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryTradingAccount");
    LPUB("RspQryTradingAccount",knk(33,kp(p->AccountID),kf(p->YdBalance),kf(p->YdPositionMargin),kf(p->YdFundEquity),kf(p->FundEquity),kf(p->OptionsMarketValue),kf(p->Equity),kf(p->AvailableBalance),kf(p->WithdrawBalance),kf(p->Margin),kf(p->FrozenMargin),kf(p->ExerciseFrozenMargin),kf(p->RiskDegree),kf(p->Premium),kf(p->FrozenPremium),kf(p->Commission),kf(p->FrozenCommission),kf(p->CloseProfit),kf(p->PositionProfit),kf(p->CloseProfitByDate),kf(p->PositionProfitByDate),kf(p->Deposit),kf(p->Withdraw),kf(p->FundMortgage),kf(p->WarrantMortgage),kf(p->FrozenBalance),kf(p->UnFrozenBalance),kc(p->CurrencyID),kf(p->HedgeRiskDegree),kf(p->ShUsedBuyQuota),kf(p->SzUsedBuyQuota),kf(p->ShAvailableBuyQuota),kf(p->SzAvailableBuyQuota)));
  };

  /// Description:持仓查询
  virtual void OnRspQryPosition(CHSRspQryPositionField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryPosition");
    LPUB("RspQryPosition",knk(32,kp(p->AccountID),kp(p->ExchangeID),kp(p->InstrumentID),kc(p->Direction),kc(p->HedgeType),kf(p->YdPositionVolume),kf(p->PositionVolume),kf(p->TodayPositionVolume),kf(p->AvailablePositionVolume),kf(p->TodayAvailablePositionVolume),kf(p->PositionMargin),kf(p->Premium),kf(p->Commission),kf(p->OpenFrozenVolume),kf(p->CloseFrozenVolume),kf(p->CombVolume),kf(p->ExerciseFrozenVolume),kf(p->FrozenMargin),kf(p->ExerciseFrozenMargin),kf(p->FrozenPremium),kf(p->FrozenCommission),kf(p->OpenVolume),kf(p->CloseVolume),kf(p->OpenBalance),kf(p->CloseBalance),kf(p->OpenCost),kf(p->PositionCost),kf(p->PositionProfit),kf(p->CloseProfit),kf(p->OptionsMarketValue),kp(p->UnderlyingInstrID),kf(p->TASPositionVolume)));
  };


  /// Description:报单查询
  virtual void OnRspQryOrder(CHSOrderField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryOrder");
    LPUB("RspQryOrder",knk(31,kp(p->AccountID),kp(p->OrderSysID),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->InstrumentID),ki(p->Direction),kc(p->OffsetFlag),kc(p->HedgeType),kf(p->OrderPrice),kf(p->OrderVolume),kc(p->OrderStatus),kf(p->TradeVolume),kf(p->CancelVolume),kf(p->TradePrice),ki(p->TradingDay),ki(p->InsertDate),ki(p->InsertTime),ki(p->ReportTime),ki(p->OrderCommand),kf(p->MinVolume),kf(p->SpringPrice),kc(p->SwapOrderFlag),kc(p->ForceCloseReason),kp(p->ErrorMsg),kp(p->UnderlyingInstrID),kc(p->OrderSource),kp(p->CombPositionID),kp(p->ExchangeAccountID),ki(p->SeatIndex)));
  };

  /// Description:成交查询
  virtual void OnRspQryTrade(CHSTradeField *p, CHSRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONLDPERR("RspQryTrade");
    LPUB("RspQryTrade",knk(19,kp(p->AccountID),kp(p->TradeID),kp(p->OrderSysID),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->InstrumentID),ki(p->Direction),kc(p->OffsetFlag),kc(p->HedgeType),kf(p->TradeVolume),kf(p->TradePrice),ki(p->TradingDay),ki(p->TradeTime),kp(p->UnderlyingInstrID),kp(p->CombPositionID),kf(p->TradeCommission),kp(p->ExchangeAccountID)));
  };

  /// Description:主推-报单回报
  virtual void OnRtnOrder(CHSOrderField *p) {
    MPUB("RtnOrder",knk(31,kp(p->AccountID),kp(p->OrderSysID),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->InstrumentID),ki(p->Direction),kc(p->OffsetFlag),kc(p->HedgeType),kf(p->OrderPrice),kf(p->OrderVolume),kc(p->OrderStatus),kf(p->TradeVolume),kf(p->CancelVolume),kf(p->TradePrice),ki(p->TradingDay),ki(p->InsertDate),ki(p->InsertTime),ki(p->ReportTime),ki(p->OrderCommand),kf(p->MinVolume),kf(p->SpringPrice),kc(p->SwapOrderFlag),kc(p->ForceCloseReason),kp(p->ErrorMsg),kp(p->UnderlyingInstrID),kc(p->OrderSource),kp(p->CombPositionID),kp(p->ExchangeAccountID),ki(p->SeatIndex)));
  };

  /// Description:主推-成交回报
  virtual void OnRtnTrade(CHSTradeField *p) {
    MPUB("RtnTrade",knk(19,kp(p->AccountID),kp(p->TradeID),kp(p->OrderSysID),kp(p->BrokerOrderID),ki(p->SessionID),kp(p->OrderRef),kp(p->ExchangeID),kp(p->InstrumentID),ki(p->Direction),kc(p->OffsetFlag),kc(p->HedgeType),kf(p->TradeVolume),kf(p->TradePrice),ki(p->TradingDay),ki(p->TradeTime),kp(p->UnderlyingInstrID),kp(p->CombPositionID),kf(p->TradeCommission),kp(p->ExchangeAccountID)));
  };

};

Z CTradeHandler * pTradeSpi,*SpiPool[APIPOOL_SIZE];;

extern "C"{
  K1(ldpapiver){
    R kp((S)GetTradeApiVersion());
  }
  
  K1(ldperrmsg){
    if(!run) R ki(-1);
    R kp((S)pTradeApi->GetApiErrorMsg(xi));
  }
  
  K2(initldp){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];

    bool usefens;
    CHSInitConfigField cfg;
    
      
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
    setm(1);
    sd1(p[0],onmq);

    cfg.APICheckVersion=API_STRUCT_CHECK_VERSION;
    strcpy(cfg.CommLicense,kK(x)[4]->s);
    strcpy(cfg.SafeLevel,kK(x)[5]->s);
    strcpy(cfg.CommPassword,kK(x)[6]->s);
    strcpy(cfg.CertLicense,kK(x)[7]->s);
    strcpy(cfg.CertPassword,kK(x)[8]->s);
    
    nAPI=kK(x)[0]->n;
    usefens=kK(x)[1]->g;
    
    DO(nAPI,ApiPool[i]=pTradeApi=NewTradeApi(kS(kK(x)[0])[i]);if(NULL==pTradeApi) R ki(-10004);SpiPool[i]=pTradeSpi = new CTradeHandler(i);pTradeApi->RegisterSpi(pTradeSpi);r=usefens?pTradeApi->RegisterFensServer(kS(kK(x)[2])[i],kS(y)[i]):pTradeApi->RegisterFront(kS(kK(x)[2])[i]);if(r){MPUB("RegisterFrontError",knk(2,ki(r),kp((S)pTradeApi->GetApiErrorMsg(r))));R ki(-abs(r));};if(r=pTradeApi->Init(&cfg)) {MPUB("InitError",knk(2,ki(r),kp((S)pTradeApi->GetApiErrorMsg(r))));R ki(-abs(r));MPUB("InitOk",knk(0));}); //r=pTradeApi->RegisterSubModel((SUB_TERT_TYPE)kK(x)[3]->i);if(r)R ki(-abs(r));

    MPUB("InitAllOk",knk(0));
    
    R ki(run);
  }

  K1(freeldp){
    if(!run) R ki(-1);
    I i=0;
    
    DO(nAPI,pTradeApi=ApiPool[i];pTradeApi->RegisterSpi(NULL);MPUB("UnRegisterSpi",knk(0));pTradeApi->ReleaseApi();MPUB("ReleaseApi",knk(0));ApiPool[i]=NULL;delete SpiPool[i];SpiPool[i]=NULL;); /*pTradeApi->Join();MPUB("Join",knk(0));*/
    pTradeApi=NULL;pTradeSpi=NULL;

    MPUB("freeldp",knk(0));

    /*
      sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;
    */
    run--;
    R ki(run);
  }

  K1(ldprun){
    R ki(run);
  } 

  K2(reqAuthenticate){
    if(!run) R ki(-1);

    CHSReqAuthenticateField req;
    strcpy(req.AccountID,kK(y)[0]->s); 
    strcpy(req.Password,kK(y)[2]->s); 
    strcpy(req.AppID,kK(y)[2]->s); 
    strcpy(req.AuthCode,kK(y)[3]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqAuthenticate(&req,kI(x)[0]));
  } 

  K2(reqSubmitUserSystemInfo){
    if(!run) R ki(-1);
  
    CHSReqUserSystemInfoField req;
    strcpy(req.AppLoginTime,kK(y)[0]->s); 
    strcpy(req.AppPublicAdrr,kK(y)[1]->s); 
    strcpy(req.AppSysInfo,kK(y)[2]->s); 
    strcpy(req.AppSysInfoIntegrity,kK(y)[3]->s); 
    req.AppAbnormalType=kK(y)[4]->g; 

    R ki(ApiPool[kI(x)[1]]->ReqSubmitUserSystemInfo(&req,kI(x)[0]));
  } 

  K2(reqUserLogin){
    if(!run) R ki(-1);
    
    CHSReqUserLoginField req;
    strcpy(req.AccountID,kK(y)[0]->s); 
    strcpy(req.Password,kK(y)[1]->s);
    req.UserApplicationType=kK(y)[2]->g;
    strcpy(req.UserApplicationInfo,kK(y)[3]->s); 
    strcpy(req.MacAddress,kK(y)[4]->s); 
    strcpy(req.IPAddress,kK(y)[5]->s); 
    strcpy(req.UserStationInfo,kK(y)[6]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqUserLogin(&req,kI(x)[0]));
  } 

  K2(reqOrderInsert){
    if(!run) R ki(-1);
    
    CHSReqOrderInsertField req;
    strcpy(req.OrderRef,kK(y)[0]->s); 
    strcpy(req.ExchangeID,kK(y)[1]->s); 
    strcpy(req.InstrumentID,kK(y)[2]->s); 
    req.Direction=kK(y)[3]->g;
    req.OffsetFlag=kK(y)[4]->g;
    req.HedgeType=kK(y)[5]->g;
    req.OrderPrice=kK(y)[6]->f;
    req.OrderVolume=kK(y)[7]->f;
    req.OrderCommand=kK(y)[8]->i;
    req.MinVolume=kK(y)[9]->f;
    req.SpringPrice=kK(y)[10]->f;
    req.SwapOrderFlag=kK(y)[11]->g;
    strcpy(req.CombPositionID,kK(y)[12]->s); 
    strcpy(req.ExchangeAccountID,kK(y)[13]->s); 
    req.SeatIndex=kK(y)[14]->i;

    R ki(ApiPool[kI(x)[1]]->ReqOrderInsert(&req,kI(x)[0]));
  }

  K2(reqOrderAction){
    if(!run) R ki(-1);
    
    CHSReqOrderActionField req;
    strcpy(req.OrderSysID,kK(y)[0]->s); 
    strcpy(req.ExchangeID,kK(y)[1]->s);
    req.SessionID=kK(y)[2]->i;    
    strcpy(req.OrderRef,kK(y)[3]->s); 
    strcpy(req.OrderActionRef,kK(y)[4]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqOrderAction(&req,kI(x)[0]));
  }

  K2(reqQryPosition){
    if(!run) R ki(-1);
    
    CHSReqQryPositionField req;
    strcpy(req.ExchangeID,kK(y)[0]->s); 
    strcpy(req.InstrumentID,kK(y)[1]->s); 

    R ki(ApiPool[kI(x)[1]]->ReqQryPosition(&req,kI(x)[0]));
  } 

  K2(reqQryTradingAccount){
    if(!run) R ki(-1);
    
    CHSReqQryTradingAccountField req;

    R ki(ApiPool[kI(x)[1]]->ReqQryTradingAccount(&req,kI(x)[0]));
  } 

  K2(reqQryOrder){
    if(!run) R ki(-1);
    
    CHSReqQryOrderField req;
    strcpy(req.ExchangeID,kK(y)[0]->s); 
    strcpy(req.InstrumentID,kK(y)[1]->s);
    strcpy(req.OrderSysID,kK(y)[2]->s);
    strcpy(req.ExchangeAccountID,kK(y)[3]->s);

    R ki(ApiPool[kI(x)[1]]->ReqQryOrder(&req,kI(x)[0]));
  } 

  K2(reqQryTrade){
    if(!run) R ki(-1);
    
    CHSReqQryTradeField req;
    strcpy(req.ExchangeID,kK(y)[0]->s); 
    strcpy(req.InstrumentID,kK(y)[1]->s);
    strcpy(req.ExchangeAccountID,kK(y)[2]->s);

    R ki(ApiPool[kI(x)[1]]->ReqQryTrade(&req,kI(x)[0]));
  } 

  K1(hsdc_getsysteminfo){
    int r=0;
    char pszSysInfo[492];
    int iSysInfoLen;
    char pszSysInfoIntegrity[300];
    int iSysInfoIntegrityLen;
    
    r=hundsun_getsysteminfo(pszSysInfo,&iSysInfoLen,pszSysInfoIntegrity,&iSysInfoIntegrityLen);
    if(0==r) R knk(2,kpn((S)pszSysInfo,iSysInfoLen),kpn((S)pszSysInfoIntegrity,iSysInfoIntegrityLen));
    R ki(r);
  }

  K1(hsdc_getdetailerror){
    int r=0;
    
    char pszDetailInfo[492];
    int iDetailInfoLen;

    r=hundsun_getdetailerror(xs,pszDetailInfo,&iDetailInfoLen);
    if(0==r) R kpn((S)pszDetailInfo,iDetailInfoLen);
    R ki(r);    
  }

  K1(hsdc_version){
    R kp((S)hundsun_getversion());
  }

  K1(ctpsysinfo){
    char buf[SYMSIZE];
    I r=0,n=0;
    r=CTP_GetSystemInfo(buf,n);
    R r?kp(""):kpn((S)buf,n);
  }  
}

