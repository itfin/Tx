#include "kcomm.h"
#include <queue>
#include "DataCollect.h"
#include "ThostFtdcTraderApi.h"

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

Z CThostFtdcTraderApi *pTradeApi;

#define CTPPUB(x,y) mpub(knk(2,ks(x),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));
#define CTPPUB1(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));

#define RETURNONERR if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError"),knk(3,ki(nRequestID),kb(bIsLast),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg)))));R;}

#define RETURNONERR1 if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){O("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError1"),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg))));R;}


class CTradeHandler : public CThostFtdcTraderSpi{
public: 
  CTradeHandler(CThostFtdcTraderApi *pUserApi) : m_pUserApi(pUserApi) {} 
  CTradeHandler(){} 

  virtual void OnFrontConnected() { 
    O("OnFrontConnected.\n"); 
    mpub(knk(2,ks("FrontConnectT"),knk(0)));
  } 

  virtual void OnFrontDisconnected(int nReason) { 
    O("OnFrontDisconnected.\n"); 
    mpub(knk(2,ks("FrontDisconnectT"),knk(1,ki(nReason))));
  } 

  virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONERR;
    CTPPUB("AuthenticateT",knk(5,kp(p->BrokerID),kp(p->UserID),kp(p->UserProductInfo),kp(p->AppID),kc(p->AppType)));
  };
  
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    O("OnRspUserLogin:%d\n",p); 
    RETURNONERR;
    CTPPUB("UserLoginT",knk(3,ki(p->FrontID),ki(p->SessionID),kp(p->MaxOrderRef)));
  } 
  
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    O("OnRspUserLogout.\n");   
  };

  virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    O("OnRspError:\n"); 
    O("ErrorCode=[%d], ErrorMsg=[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg); 
    O("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast); 
  }
 
  virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQrySettlementInfoConfirm:%d\n",p); 
    RETURNONERR;
    CTPPUB("QrySettlementInfoConfirm",knk(4,kp(p->BrokerID),kp(p->InvestorID),kp(p->ConfirmDate),kp(p->ConfirmTime)));
  };

  virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspSettlementInfoConfirm:%d\n",p); 
    RETURNONERR;
    CTPPUB("SettlementInfoConfirm",knk(4,kp(p->BrokerID),kp(p->InvestorID),kp(p->ConfirmDate),kp(p->ConfirmTime)));    
  };

  virtual void OnRspQryInstrument(CThostFtdcInstrumentField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInstrument:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInstrument",knk(25,kp(p->InstrumentID),kp(p->ExchangeID),kp(p->InstrumentName),kp(p->ExchangeInstID),kp(p->ProductID),kc(p->ProductClass),ki(p->DeliveryYear),ki(p->DeliveryMonth),ki(p->MaxMarketOrderVolume),ki(p->MinMarketOrderVolume),ki(p->MaxLimitOrderVolume),ki(p->MinLimitOrderVolume),ki(p->VolumeMultiple),kf(p->PriceTick),kp(p->CreateDate),kp(p->OpenDate),kp(p->ExpireDate),kp(p->StartDelivDate),kp(p->EndDelivDate),kc(p->InstLifePhase),ki(p->IsTrading),kc(p->PositionType),kc(p->PositionDateType),kf(p->LongMarginRatio),kf(p->ShortMarginRatio)));
  };

  virtual void OnRspOrderInsert(CThostFtdcInputOrderField *p, CThostFtdcRspInfoField *pe, int nRequestID, bool bIsLast) {
    //O("OnRspOrderInsert:%d\n",p); 
    //RETURNONERR;
    CTPPUB("OrderInsert",knk(24,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kc(p->OrderPriceType),kc(p->Direction),kp(p->CombOffsetFlag),kp(p->CombHedgeFlag),kf(p->LimitPrice),ki(p->VolumeTotalOriginal),kc(p->TimeCondition),kp(p->GTDDate),kc(p->VolumeCondition),ki(p->MinVolume),kc(p->ContingentCondition),kf(p->StopPrice),kc(p->ForceCloseReason),ki(p->IsAutoSuspend),kp(p->BusinessUnit),ki(p->RequestID),ki(p->UserForceClose),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
};

  ///报单操作请求响应
  virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *p, CThostFtdcRspInfoField *pe, int nRequestID, bool bIsLast) {
    //O("OnRspOrderAction:%d\n",p); 
    //RETURNONERR;
    CTPPUB("OrderAction",knk(16,kp(p->BrokerID),kp(p->InvestorID),ki(p->OrderActionRef),kp(p->OrderRef),ki(p->RequestID),ki(p->FrontID),ki(p->SessionID),kp(p->ExchangeID),kp(p->OrderSysID),kc(p->ActionFlag),kf(p->LimitPrice),ki(p->VolumeChange),kp(p->UserID),kp(p->InstrumentID),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));  
  };

  ///询价录入请求响应
  virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *p, CThostFtdcRspInfoField *pe, int nRequestID, bool bIsLast) {
    CTPPUB("ForQuoteInsert",knk(7,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->ForQuoteRef),kp(p->UserID),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));  
  };

  ///报价录入请求响应
  virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *p, CThostFtdcRspInfoField *pe, int nRequestID, bool bIsLast) {
        CTPPUB("QuoteInsert",knk(17,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->QuoteRef),kp(p->UserID),kf(p->AskPrice),kf(p->BidPrice),ki(p->AskVolume),ki(p->BidVolume),ki(p->RequestID),kp(p->BusinessUnit),kc(p->AskOffsetFlag),kc(p->BidOffsetFlag),kc(p->AskHedgeFlag),kc(p->BidHedgeFlag),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));    
  };

  ///报价操作请求响应
  virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *p,CThostFtdcRspInfoField *pe, int nRequestID, bool bIsLast) {
        CTPPUB("QuoteAction",knk(14,kp(p->BrokerID),kp(p->InvestorID),ki(p->QuoteActionRef),kp(p->QuoteRef),ki(p->RequestID),ki(p->FrontID),ki(p->SessionID),kp(p->ExchangeID),kp(p->QuoteSysID),kc(p->ActionFlag),kp(p->UserID),kp(p->InstrumentID),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));    
  };

  ///报单通知
  virtual void OnRtnOrder(CThostFtdcOrderField *p) {
    //O("OnRtnOrder:%d\n",p); 
    CTPPUB1("Order",knk(55,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kc(p->OrderPriceType),kc(p->Direction),kp(p->CombOffsetFlag),kp(p->CombHedgeFlag),kf(p->LimitPrice),ki(p->VolumeTotalOriginal),kc(p->TimeCondition),kp(p->GTDDate),kc(p->VolumeCondition),ki(p->MinVolume),kc(p->ContingentCondition),kf(p->StopPrice),kc(p->ForceCloseReason),ki(p->IsAutoSuspend),kp(p->BusinessUnit),ki(p->RequestID),kp(p->OrderLocalID),kp(p->ExchangeID),kp(p->ParticipantID),kp(p->ClientID),kp(p->ExchangeInstID),kp(p->TraderID),ki(p->InstallID),kc(p->OrderSubmitStatus),ki(p->NotifySequence),kp(p->TradingDay),ki(p->SettlementID),kp(p->OrderSysID),kc(p->OrderSource),kc(p->OrderStatus),kc(p->OrderType),ki(p->VolumeTraded),ki(p->VolumeTotal),kp(p->InsertDate),kp(p->InsertTime),kp(p->ActiveTime),kp(p->SuspendTime),kp(p->UpdateTime),kp(p->CancelTime),kp(p->ActiveTraderID),kp(p->ClearingPartID),ki(p->SequenceNo),ki(p->FrontID),ki(p->SessionID),kp(p->UserProductInfo),kp(p->StatusMsg),ki(p->UserForceClose),kp(p->ActiveUserID),ki(p->BrokerOrderSeq),kp(p->RelativeOrderSysID)));  
  };

  ///成交通知
  virtual void OnRtnTrade(CThostFtdcTradeField *p) {
    //O("OnRtnTrade:%d\n",p); 
    CTPPUB1("Trade",knk(30,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kp(p->ExchangeID),kp(p->TradeID),kc(p->Direction),kp(p->OrderSysID),kp(p->ParticipantID),kp(p->ClientID),kc(p->TradingRole),kp(p->ExchangeInstID),kc(p->OffsetFlag),kc(p->HedgeFlag),kf(p->Price),ki(p->Volume),kp(p->TradeDate),kp(p->TradeTime),kc(p->TradeType),kc(p->PriceSource),kp(p->TraderID),kp(p->OrderLocalID),kp(p->ClearingPartID),kp(p->BusinessUnit),ki(p->SequenceNo),kp(p->TradingDay),ki(p->SettlementID),ki(p->BrokerOrderSeq),kc(p->TradeSource)));  
  };

  ///报单录入错误回报
  virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *p, CThostFtdcRspInfoField *pe) {
    //O("OnErrRtnOrderInsert:%d\n",p); 
    //RETURNONERR1;
    CTPPUB1("OrderInsertErr",knk(24,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kc(p->OrderPriceType),kc(p->Direction),kp(p->CombOffsetFlag),kp(p->CombHedgeFlag),kf(p->LimitPrice),ki(p->VolumeTotalOriginal),kc(p->TimeCondition),kp(p->GTDDate),kc(p->VolumeCondition),ki(p->MinVolume),kc(p->ContingentCondition),kf(p->StopPrice),kc(p->ForceCloseReason),ki(p->IsAutoSuspend),kp(p->BusinessUnit),ki(p->RequestID),ki(p->UserForceClose),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
  };

  ///报单操作错误回报
  virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *p, CThostFtdcRspInfoField *pe) {
    //O("OnErrRtnOrderAction:%d\n",p); 
    //RETURNONERR1;
    CTPPUB1("OrderActionErr",knk(16,kp(p->BrokerID),kp(p->InvestorID),ki(p->OrderActionRef),kp(p->OrderRef),ki(p->RequestID),ki(p->FrontID),ki(p->SessionID),kp(p->ExchangeID),kp(p->OrderSysID),kc(p->ActionFlag),kf(p->LimitPrice),ki(p->VolumeChange),kp(p->UserID),kp(p->InstrumentID),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
  };

  ///询价通知
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *p) {
    CTPPUB1("ForQuote",knk(5,kp(p->TradingDay),kp(p->InstrumentID),kp(p->ForQuoteSysID),kp(p->ForQuoteTime),kp(p->ActionDay)));  
  };

  ///报价通知
  virtual void OnRtnQuote(CThostFtdcQuoteField *p) {
    CTPPUB1("Quote",knk(41,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->QuoteRef),kp(p->UserID),kf(p->AskPrice),kf(p->BidPrice),ki(p->AskVolume),ki(p->BidVolume),ki(p->RequestID),kp(p->BusinessUnit),kc(p->AskOffsetFlag),kc(p->BidOffsetFlag),kc(p->AskHedgeFlag),kc(p->BidHedgeFlag),kp(p->QuoteLocalID),kp(p->ExchangeID),kp(p->ParticipantID),kp(p->ClientID),kp(p->ExchangeInstID),kp(p->TraderID),ki(p->InstallID),ki(p->NotifySequence),kc(p->OrderSubmitStatus),kp(p->TradingDay),ki(p->SettlementID),kp(p->QuoteSysID),kp(p->InsertDate),kp(p->InsertTime),kp(p->CancelTime),kc(p->QuoteStatus),kp(p->ClearingPartID),ki(p->SequenceNo),kp(p->AskOrderSysID),kp(p->BidOrderSysID),ki(p->FrontID),ki(p->SessionID),kp(p->UserProductInfo),kp(p->StatusMsg),kp(p->ActiveUserID),ki(p->BrokerQuoteSeq)));  
  };

  ///询价录入错误回报
  virtual void OnErrRtnForQuoteInsert(CThostFtdcInputExecOrderField *p, CThostFtdcRspInfoField *pe) {};

  ///报价录入错误回报
  virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *p, CThostFtdcRspInfoField *pe) {
    CTPPUB1("QuoteInsertErr",knk(17,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->QuoteRef),kp(p->UserID),kf(p->AskPrice),kf(p->BidPrice),ki(p->AskVolume),ki(p->BidVolume),ki(p->RequestID),kp(p->BusinessUnit),kc(p->AskOffsetFlag),kc(p->BidOffsetFlag),kc(p->AskHedgeFlag),kc(p->BidHedgeFlag),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
};

  ///报价操作错误回报
  virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *p, CThostFtdcRspInfoField *pe) {
    CTPPUB1("QuoteActionErr",knk(25,kp(p->BrokerID),kp(p->InvestorID),ki(p->QuoteActionRef),kp(p->QuoteRef),ki(p->RequestID),ki(p->FrontID),ki(p->SessionID),kp(p->ExchangeID),kp(p->QuoteSysID),kc(p->ActionFlag),kp(p->ActionDate),kp(p->ActionTime),kp(p->TraderID),ki(p->InstallID),kp(p->QuoteLocalID),kp(p->ActionLocalID),kp(p->ParticipantID),kp(p->ClientID),kp(p->BusinessUnit),kc(p->OrderActionStatus),kp(p->UserID),kp(p->StatusMsg),kp(p->InstrumentID),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
};


  ///预埋单录入请求响应
  virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///预埋撤单录入请求响应
  virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};


  ///查询最大报单数量响应
  virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("QueryMaxOrderVolume:%d\n",p); 
    RETURNONERR;
    CTPPUB("QueryMaxOrderVolume",knk(7,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kc(p->Direction),kc(p->OffsetFlag),kc(p->HedgeFlag),ki(p->MaxVolume)));
  };

  ///删除预埋单响应
  virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///删除预埋撤单响应
  virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///执行宣告录入请求响应
  virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///执行宣告操作请求响应
  virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询报单响应
  virtual void OnRspQryOrder(CThostFtdcOrderField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryOrder:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryOrder",knk(55,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kc(p->OrderPriceType),kc(p->Direction),kp(p->CombOffsetFlag),kp(p->CombHedgeFlag),kf(p->LimitPrice),ki(p->VolumeTotalOriginal),kc(p->TimeCondition),kp(p->GTDDate),kc(p->VolumeCondition),ki(p->MinVolume),kc(p->ContingentCondition),kf(p->StopPrice),kc(p->ForceCloseReason),ki(p->IsAutoSuspend),kp(p->BusinessUnit),ki(p->RequestID),kp(p->OrderLocalID),kp(p->ExchangeID),kp(p->ParticipantID),kp(p->ClientID),kp(p->ExchangeInstID),kp(p->TraderID),ki(p->InstallID),kc(p->OrderSubmitStatus),ki(p->NotifySequence),kp(p->TradingDay),ki(p->SettlementID),kp(p->OrderSysID),kc(p->OrderSource),kc(p->OrderStatus),kc(p->OrderType),ki(p->VolumeTraded),ki(p->VolumeTotal),kp(p->InsertDate),kp(p->InsertTime),kp(p->ActiveTime),kp(p->SuspendTime),kp(p->UpdateTime),kp(p->CancelTime),kp(p->ActiveTraderID),kp(p->ClearingPartID),ki(p->SequenceNo),ki(p->FrontID),ki(p->SessionID),kp(p->UserProductInfo),kp(p->StatusMsg),ki(p->UserForceClose),kp(p->ActiveUserID),ki(p->BrokerOrderSeq),kp(p->RelativeOrderSysID)));
  };

  ///请求查询成交响应
  virtual void OnRspQryTrade(CThostFtdcTradeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryTrade:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryTrade",knk(30,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kp(p->ExchangeID),kp(p->TradeID),kc(p->Direction),kp(p->OrderSysID),kp(p->ParticipantID),kp(p->ClientID),kc(p->TradingRole),kp(p->ExchangeInstID),kc(p->OffsetFlag),kc(p->HedgeFlag),kf(p->Price),ki(p->Volume),kp(p->TradeDate),kp(p->TradeTime),kc(p->TradeType),kc(p->PriceSource),kp(p->TraderID),kp(p->OrderLocalID),kp(p->ClearingPartID),kp(p->BusinessUnit),ki(p->SequenceNo),kp(p->TradingDay),ki(p->SettlementID),ki(p->BrokerOrderSeq),kc(p->TradeSource)));
  };

  ///请求查询投资者持仓响应
  virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInvestorPosition:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInvestorPosition",knk(40,kp(p->InstrumentID),kp(p->BrokerID),kp(p->InvestorID),kc(p->PosiDirection),kc(p->HedgeFlag),kc(p->PositionDate),ki(p->YdPosition),ki(p->Position),ki(p->LongFrozen),ki(p->ShortFrozen),kf(p->LongFrozenAmount),kf(p->ShortFrozenAmount),ki(p->OpenVolume),ki(p->CloseVolume),kf(p->OpenAmount),kf(p->CloseAmount),kf(p->PositionCost),kf(p->PreMargin),kf(p->UseMargin),kf(p->FrozenMargin),kf(p->FrozenCash),kf(p->FrozenCommission),kf(p->CashIn),kf(p->Commission),kf(p->CloseProfit),kf(p->PositionProfit),kf(p->PreSettlementPrice),kf(p->SettlementPrice),kp(p->TradingDay),ki(p->SettlementID),kf(p->OpenCost),kf(p->ExchangeMargin),ki(p->CombPosition),ki(p->CombLongFrozen),ki(p->CombShortFrozen),kf(p->CloseProfitByDate),kf(p->CloseProfitByTrade),ki(p->TodayPosition),kf(p->MarginRateByMoney),kf(p->MarginRateByVolume)));
};

  ///请求查询资金账户响应
  virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryTradingAccount:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryTradingAccount",knk(30,kp(p->BrokerID),kp(p->AccountID),kf(p->PreMortgage),kf(p->PreCredit),kf(p->PreDeposit),kf(p->PreBalance),kf(p->PreMargin),kf(p->InterestBase),kf(p->Interest),kf(p->Deposit),kf(p->Withdraw),kf(p->FrozenMargin),kf(p->FrozenCash),kf(p->FrozenCommission),kf(p->CurrMargin),kf(p->CashIn),kf(p->Commission),kf(p->CloseProfit),kf(p->PositionProfit),kf(p->Balance),kf(p->Available),kf(p->WithdrawQuota),kf(p->Reserve),kp(p->TradingDay),ki(p->SettlementID),kf(p->Credit),kf(p->Mortgage),kf(p->ExchangeMargin),kf(p->DeliveryMargin),kf(p->ExchangeDeliveryMargin)));
  };

  ///请求查询投资者响应
  virtual void OnRspQryInvestor(CThostFtdcInvestorField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInvestor:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInvestor",knk(12,kp(p->InvestorID),kp(p->BrokerID),kp(p->InvestorGroupID),kp(p->InvestorName),kc(p->IdentifiedCardType),kp(p->IdentifiedCardNo),ki(p->IsActive),kp(p->Telephone),kp(p->Address),kp(p->OpenDate),kp(p->Mobile),kp(p->CommModelID)));
  };

  ///请求查询交易编码响应
  virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryTradingCode:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryTradingCode",knk(6,kp(p->InvestorID),kp(p->BrokerID),kp(p->ExchangeID),kp(p->ClientID),ki(p->IsActive),kc(p->ClientIDType)));
  };

  ///请求查询合约保证金率响应
  virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInstrumentMarginRate:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInstrumentMarginRate",knk(10,kp(p->InstrumentID),kc(p->InvestorRange),kp(p->BrokerID),kp(p->InvestorID),kc(p->HedgeFlag),kf(p->LongMarginRatioByMoney),kf(p->LongMarginRatioByVolume),kf(p->ShortMarginRatioByMoney),kf(p->ShortMarginRatioByVolume),ki(p->IsRelative)));
  };

  ///请求查询合约手续费率响应
  virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInstrumentCommissionRate:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInstrumentCommissionRate",knk(10,kp(p->InstrumentID),kc(p->InvestorRange),kp(p->BrokerID),kp(p->InvestorID),kf(p->OpenRatioByMoney),kf(p->OpenRatioByVolume),kf(p->CloseRatioByMoney),kf(p->CloseRatioByVolume),kf(p->CloseTodayRatioByMoney),kf(p->CloseTodayRatioByVolume)));
  };

  ///请求查询交易所响应
  virtual void OnRspQryExchange(CThostFtdcExchangeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryExchange:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryExchange",knk(3,kp(p->ExchangeID),kp(p->ExchangeName),kc(p->ExchangeProperty)));
  };

  ///请求查询行情响应
  virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询投资者结算结果响应
  virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQrySettlementInfo:%d\n",p); 
    RETURNONERR;
    CTPPUB("QrySettlementInfo",knk(6,kp(p->TradingDay),ki(p->SettlementID),kp(p->BrokerID),kp(p->InvestorID),ki(p->SequenceNo),kp(p->Content)));
  };

  ///请求查询投资者持仓明细响应
  virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryInvestorPositionDetail:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInvestorPositionDetail",knk(26,kp(p->InstrumentID),kp(p->BrokerID),kp(p->InvestorID),kc(p->HedgeFlag),kc(p->Direction),kp(p->OpenDate),kp(p->TradeID),ki(p->Volume),kf(p->OpenPrice),kp(p->TradingDay),ki(p->SettlementID),kc(p->TradeType),kp(p->InstrumentID),kp(p->ExchangeID),kf(p->CloseProfitByDate),kf(p->CloseProfitByTrade),kf(p->PositionProfitByDate),kf(p->PositionProfitByTrade),kf(p->Margin),kf(p->ExchMargin),kf(p->MarginRateByMoney),kf(p->MarginRateByVolume),kf(p->LastSettlementPrice),kf(p->SettlementPrice),ki(p->CloseVolume),kf(p->CloseAmount)));    
  };

  ///请求查询客户通知响应
  virtual void OnRspQryNotice(CThostFtdcNoticeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryNotice:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryNotice",knk(3,kp(p->BrokerID),kp(p->Content),kp(p->SequenceLabel)));      
  };

  ///请求查询投资者组合持仓明细响应
  virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    //O("OnRspQryInvestorPositionCombineDetail:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryInvestorPositionCombineDetail",knk(19,kp(p->TradingDay),kp(p->OpenDate),kp(p->ExchangeID),ki(p->SettlementID),kp(p->BrokerID),kp(p->InvestorID),kp(p->ComTradeID),kp(p->TradeID),kp(p->InstrumentID),kc(p->HedgeFlag),kc(p->Direction),ki(p->TotalAmt),kf(p->Margin),kf(p->ExchMargin),kf(p->MarginRateByMoney),kf(p->MarginRateByVolume),ki(p->LegID),ki(p->LegMultiple),kp(p->CombInstrumentID)));    
  };

  ///请求查询仓单折抵信息响应
  virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryEWarrantOffset:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryEWarrantOffset",knk(8,kp(p->TradingDay),kp(p->BrokerID),kp(p->InvestorID),kp(p->ExchangeID),kp(p->InstrumentID),kc(p->Direction),kc(p->HedgeFlag),ki(p->Volume)));    
  };

  ///请求查询期权交易成本响应
  virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询期权合约手续费响应
  virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询执行宣告响应
  virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询询价响应
  virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询报价响应
  virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询转帐流水响应
  virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    //O("OnRspQryTransferSerial:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryTransferSerial",knk(28,ki(p->PlateSerial),kp(p->TradeDate),kp(p->TradingDay),kp(p->TradeTime),kp(p->TradeCode),ki(p->SessionID),kp(p->BankID),kp(p->BankBranchID),kc(p->BankAccType),kp(p->BankAccount),kp(p->BankSerial),kp(p->BrokerID),kp(p->BrokerBranchID),kc(p->FutureAccType),kp(p->AccountID),kp(p->InvestorID),ki(p->FutureSerial),kc(p->IdCardType),kp(p->IdentifiedCardNo),kp(p->CurrencyID),kf(p->TradeAmount),kf(p->CustFee),kf(p->BrokerFee),kc(p->AvailabilityFlag),kp(p->OperatorCode),kp(p->BankNewAccount),ki(p->ErrorID),kp(p->ErrorMsg)));    
  };

  ///合约交易状态通知
  virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *p) {
    //O("OnRtnInstrumentStatus:%d\n",p); 
    CTPPUB1("InstrumentStatus",knk(8,kp(p->ExchangeID),kp(p->ExchangeInstID),kp(p->SettlementGroupID),kp(p->InstrumentID),kc(p->InstrumentStatus),ki(p->TradingSegmentSN),kp(p->EnterTime),kc(p->EnterReason)));  
  };

  ///交易通知
  virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *p) {
    //O("OnRtnTradingNotice:%d\n",p); 
    CTPPUB1("TradingNotice",knk(6,kp(p->BrokerID),kp(p->InvestorID),kp(p->SendTime),kp(p->FieldContent),kh(p->SequenceSeries),ki(p->SequenceNo)));  
  };

  ///提示条件单校验错误
  virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *p) {
    //O("OnRtnErrorConditionalOrder:%d\n",p); 
    CTPPUB1("ErrorConditionalOrder",knk(24,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->OrderRef),kp(p->UserID),kc(p->OrderPriceType),kc(p->Direction),kp(p->CombOffsetFlag),kp(p->CombHedgeFlag),kf(p->LimitPrice),ki(p->VolumeTotalOriginal),kc(p->TimeCondition),kp(p->GTDDate),kc(p->VolumeCondition),ki(p->MinVolume),kc(p->ContingentCondition),kf(p->StopPrice),kc(p->ForceCloseReason),ki(p->IsAutoSuspend),kp(p->BusinessUnit),ki(p->RequestID),ki(p->UserForceClose),ki(p->ErrorID),kp(p->ErrorMsg)));  
  };

  ///请求查询预埋单响应
  virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

  ///请求查询预埋撤单响应
  virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

};

  ///请求查询交易通知响应
  virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryTradingNotice:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryTradingNotice",knk(8,kp(p->BrokerID),kc(p->InvestorRange),kp(p->InvestorID),kh(p->SequenceSeries),kp(p->UserID),kp(p->SendTime),ki(p->SequenceNo),kp(p->FieldContent)));
  };

  ///请求查询经纪公司交易参数响应
  virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryBrokerTradingParams:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryBrokerTradingParams",knk(5,kp(p->BrokerID),kp(p->InvestorID),kc(p->MarginPriceType),kc(p->Algorithm),kc(p->AvailIncludeCloseProfit)));
  };

  ///请求查询经纪公司交易算法响应
  virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    //O("OnRspQryBrokerTradingAlgos:%d\n",p); 
    RETURNONERR;
    CTPPUB("QryBrokerTradingAlgos",knk(6,kp(p->BrokerID),kp(p->ExchangeID),kp(p->InstrumentID),kc(p->HandlePositionAlgoID),kc(p->FindMarginRateAlgoID),kc(p->HandleTradingAccountAlgoID)));
  };

  ///申请组合录入请求响应
  virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    CTPPUB("CombActionInsert",knk(9,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->CombActionRef),kp(p->UserID),kc(p->Direction),ki(p->Volume),kc(p->CombDirection),kc(p->HedgeFlag)));
  };

  ///申请组合通知
  virtual void OnRtnCombAction(CThostFtdcCombActionField *p) {
    CTPPUB1("CombAction",knk(25,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->CombActionRef),kp(p->UserID),kc(p->Direction),ki(p->Volume),kc(p->CombDirection),kc(p->HedgeFlag),kp(p->ActionLocalID),kp(p->ExchangeID),kp(p->ParticipantID),kp(p->ClientID),kp(p->ExchangeInstID),kp(p->TraderID),ki(p->InstallID),kc(p->ActionStatus),ki(p->NotifySequence),kp(p->TradingDay),ki(p->SettlementID),ki(p->SequenceNo),ki(p->FrontID),ki(p->SessionID),kp(p->UserProductInfo),kp(p->StatusMsg)));  
  };

  ///申请组合录入错误回报
  virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *p, CThostFtdcRspInfoField *pe) {
    CTPPUB1("CombActionInsertErr",knk(11,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->CombActionRef),kp(p->UserID),kc(p->Direction),ki(p->Volume),kc(p->CombDirection),kc(p->HedgeFlag),ki((NULL==pe)?0:(pe->ErrorID)),kp((NULL==pe)?(S)"":(pe->ErrorMsg))));
  };


  ///请求查询组合合约安全系数响应
  virtual void OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONERR;
    CTPPUB("QryCombInstrumentGuard",knk(3,kp(p->BrokerID),kp(p->InstrumentID),kf(p->GuarantRatio)));
  };

  ///请求查询申请组合响应
  virtual void OnRspQryCombAction(CThostFtdcCombActionField *p, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    RETURNONERR;
    CTPPUB("QryCombAction",knk(25,kp(p->BrokerID),kp(p->InvestorID),kp(p->InstrumentID),kp(p->CombActionRef),kp(p->UserID),kc(p->Direction),ki(p->Volume),kc(p->CombDirection),kc(p->HedgeFlag),kp(p->ActionLocalID),kp(p->ExchangeID),kp(p->ParticipantID),kp(p->ClientID),kp(p->ExchangeInstID),kp(p->TraderID),ki(p->InstallID),kc(p->ActionStatus),ki(p->NotifySequence),kp(p->TradingDay),ki(p->SettlementID),ki(p->SequenceNo),ki(p->FrontID),ki(p->SessionID),kp(p->UserProductInfo),kp(p->StatusMsg)));
  };

private: 
  CThostFtdcTraderApi *m_pUserApi;
};

Z CTradeHandler * pTradeSpi;

extern "C"{

  K3(initctpt){
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

    sprintf(buf,"/tmp/CTPT_%s",y->s);
    pTradeApi = CThostFtdcTraderApi::CreateFtdcTraderApi(buf);
    O(pTradeApi->GetApiVersion());
    pTradeSpi = new CTradeHandler(pTradeApi);
    pTradeApi->RegisterSpi((CThostFtdcTraderSpi*)pTradeSpi);

    pTradeApi->SubscribePrivateTopic((0<z->i)?THOST_TERT_RESUME:THOST_TERT_QUICK);
    pTradeApi->SubscribePublicTopic((0<z->i)?THOST_TERT_RESUME:THOST_TERT_QUICK);
    pTradeApi->RegisterFront(xs);

    pTradeApi->Init();
    R ki(run);
  }

  K1(freectpt){
    if(!run) R ki(-1);

    pTradeApi->RegisterSpi(NULL);
    pTradeApi->Release();
    //delete pTradeApi;
    pTradeApi=NULL;
    delete pTradeSpi;
    pTradeSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(ctptrun){
    R ki(run);
  } 

  K2(ctpsysinfo){
    char buf[SYMSIZE];
    I r=0,n=0;
    r=CTP_GetSystemInfo(buf,n);
    R r?kp(""):kpn((S)buf,n);
  }

  K2(userAuthT){
    if(!run) R ki(-1);
    CThostFtdcReqAuthenticateField req;
    strcpy(req.BrokerID,kK(y)[0]->s); 
    strcpy(req.UserID,kK(y)[1]->s); 
    strcpy(req.UserProductInfo,kK(y)[2]->s); 
    strcpy(req.AuthCode,kK(y)[3]->s); 
    strcpy(req.AppID,kK(y)[4]->s); 
    R ki(pTradeApi->ReqAuthenticate(&req,xi)); 
  }
    
  K2(userLoginT){
    if(!run) R ki(-1);

      
    CThostFtdcReqUserLoginField req; 
    strcpy(req.BrokerID,kK(y)[0]->s); 
    strcpy(req.UserID,kK(y)[1]->s); 
    strcpy(req.Password,kK(y)[2]->s); 
    strcpy(req.UserProductInfo,kK(y)[3]->s);
    R ki(pTradeApi->ReqUserLogin(&req,xi)); 
  }

  K2(qrySettlementInfoConfirm){
    if(!run) R ki(-1);

    CThostFtdcQrySettlementInfoConfirmField req;
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQrySettlementInfoConfirm(&req,xi));
  }

  K2(settlementInfoConfirm){
    if(!run) R ki(-1);

    CThostFtdcSettlementInfoConfirmField req;
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);

    //strcpy(req.ConfirmDate,m_pUserApi->GetTradingDay());
    //strcpy(req.ConfirmTime,"09:00:00");

    R ki(pTradeApi->ReqSettlementInfoConfirm(&req,xi));
  }

  K2(orderInsert){
    if(!run) R ki(-1);

    CThostFtdcInputOrderField req;
    memset(&req,0,sizeof(req));

    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.OrderRef,kK(y)[3]->s);
    req.Direction=kK(y)[4]->g;
    req.VolumeTotalOriginal=kK(y)[5]->i;
    req.OrderPriceType=kK(y)[6]->g;
    req.LimitPrice=kK(y)[7]->f;
    req.TimeCondition=kK(y)[8]->g;
    req.VolumeCondition=kK(y)[9]->g;
    strcpy(req.CombOffsetFlag,kK(y)[10]->s);
    strcpy(req.CombHedgeFlag,kK(y)[11]->s);

    if(12<y->n){
      req.ContingentCondition=kK(y)[12]->g;
      req.StopPrice=kK(y)[13]->f;
    }else{
      req.ContingentCondition=THOST_FTDC_CC_Immediately;
      req.StopPrice=0;
    }

    req.MinVolume=1;
    req.UserForceClose=0;
    req.IsAutoSuspend=0;
    req.ForceCloseReason=THOST_FTDC_FCC_NotForceClose;

    R ki(pTradeApi->ReqOrderInsert(&req,xi));
  }

  K2(orderAction){
    if(!run) R ki(-1);

    CThostFtdcInputOrderActionField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);

    req.OrderActionRef=kK(y)[3]->i;
    req.FrontID=kK(y)[4]->i;
    req.SessionID=kK(y)[5]->i;
    strcpy(req.OrderRef,kK(y)[6]->s);
    strcpy(req.ExchangeID,kK(y)[7]->s);
    strcpy(req.OrderSysID,kK(y)[8]->s);

    req.ActionFlag=kK(y)[9]->g;

    R ki(pTradeApi->ReqOrderAction(&req,xi));
  }

  K2(forQuoteInsert){ 
    if(!run) R ki(-1);

    CThostFtdcInputForQuoteField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.ForQuoteRef,kK(y)[3]->s);

    R ki(pTradeApi->ReqForQuoteInsert(&req,xi));
  }

  K2(quoteInsert){ 
    if(!run) R ki(-1);

    CThostFtdcInputQuoteField req;
    memset(&req,0,sizeof(req));

    
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.QuoteRef,kK(y)[3]->s);

    req.AskVolume=kK(y)[4]->i;
    req.BidVolume=kK(y)[5]->i;

    req.AskPrice=kK(y)[6]->f;
    req.BidPrice=kK(y)[7]->f;

    req.AskOffsetFlag=kK(y)[8]->g;
    req.BidOffsetFlag=kK(y)[9]->g;
    req.AskHedgeFlag=kK(y)[10]->g;
    req.BidHedgeFlag=kK(y)[11]->g;

    req.RequestID=xi;    
    R ki(pTradeApi->ReqQuoteInsert(&req,xi));
  }

  K2(quoteAction){ 
    if(!run) R ki(-1);

    CThostFtdcInputQuoteActionField req;
    memset(&req,0,sizeof(req));

    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);

    req.QuoteActionRef=kK(y)[3]->i;
    req.FrontID=kK(y)[4]->i;
    req.SessionID=kK(y)[5]->i;
    strcpy(req.QuoteRef,kK(y)[6]->s);
    strcpy(req.ExchangeID,kK(y)[7]->s);
    strcpy(req.QuoteSysID,kK(y)[8]->s);

    req.ActionFlag=kK(y)[9]->g;

    R ki(pTradeApi->ReqQuoteAction(&req,xi));
  }

  K2(combActionInsert){
    if(!run) R ki(-1);

    CThostFtdcInputCombActionField req;
    memset(&req,0,sizeof(req));

    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);strcpy(req.UserID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.CombActionRef,kK(y)[3]->s);

    req.Direction=kK(y)[4]->g;
    req.Volume=kK(y)[5]->i;
    req.CombDirection=kK(y)[6]->g;
    req.HedgeFlag=kK(y)[7]->g;

    R ki(pTradeApi->ReqCombActionInsert(&req,xi));

  }
  
  K2(qryMaxOrderVolume){
    if(!run) R ki(-1);

    CThostFtdcQueryMaxOrderVolumeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    req.Direction=kK(y)[3]->g;
    req.OffsetFlag=kK(y)[4]->g;
    req.HedgeFlag=kK(y)[5]->g;

    R ki(pTradeApi->ReqQueryMaxOrderVolume(&req,xi));
  }

  K2(qryInstrument){
    if(!run) R ki(-1);

    CThostFtdcQryInstrumentField req;
    memset(&req,0,sizeof(req));
    strcpy(req.InstrumentID,kK(y)[0]->s);
    strcpy(req.ExchangeID,kK(y)[1]->s);
    strcpy(req.ExchangeInstID,kK(y)[2]->s);
    strcpy(req.ProductID,kK(y)[3]->s);
    R ki(pTradeApi->ReqQryInstrument(&req,xi));
  }

  K2(qryTradingAccount){
    if(!run) R ki(-1);

    CThostFtdcQryTradingAccountField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQryTradingAccount(&req,xi));
  }

  K2(qryInvestorPosition){
    if(!run) R ki(-1);

    CThostFtdcQryInvestorPositionField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    R ki(pTradeApi->ReqQryInvestorPosition(&req,xi));
  }

  K2(qryOrder){
    if(!run) R ki(-1);

    CThostFtdcQryOrderField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.ExchangeID,kK(y)[3]->s);
    sprintf(req.OrderSysID,"%12s",kK(y)[4]->s);
    strcpy(req.InsertTimeStart,kK(y)[5]->s);
    strcpy(req.InsertTimeEnd,kK(y)[6]->s);
    R ki(pTradeApi->ReqQryOrder(&req,xi));
  }

  K2(qryTrade){
    if(!run) R ki(-1);

    CThostFtdcQryTradeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.ExchangeID,kK(y)[3]->s);
    strcpy(req.TradeID,kK(y)[4]->s);
    strcpy(req.TradeTimeStart,kK(y)[5]->s);
    strcpy(req.TradeTimeEnd,kK(y)[6]->s);
    R ki(pTradeApi->ReqQryTrade(&req,xi));
  }

  K2(qryInvestor){
    if(!run) R ki(-1);

    CThostFtdcQryInvestorField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQryInvestor(&req,xi));
  }

  K2(qryTradingCode){
    if(!run) R ki(-1);

    CThostFtdcQryTradingCodeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.ExchangeID,kK(y)[2]->s);

    R ki(pTradeApi->ReqQryTradingCode(&req,xi));
  }

  K2(qryInstrumentCommissionRate){
    if(!run) R ki(-1);

    CThostFtdcQryInstrumentCommissionRateField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);

    R ki(pTradeApi->ReqQryInstrumentCommissionRate(&req,xi));
  }

  K2(qryInstrumentMarginRate){
    if(!run) R ki(-1);

    CThostFtdcQryInstrumentMarginRateField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    req.HedgeFlag=kK(y)[3]->g;
    R ki(pTradeApi->ReqQryInstrumentMarginRate(&req,xi));
  }

  K2(qryExchange){
    if(!run) R ki(-1);

    CThostFtdcQryExchangeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.ExchangeID,kK(y)[0]->s);
    R ki(pTradeApi->ReqQryExchange(&req,xi));
  }

  K2(qryInvestorPositionDetail){
    if(!run) R ki(-1);

    CThostFtdcQryInvestorPositionDetailField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    R ki(pTradeApi->ReqQryInvestorPositionDetail(&req,xi));
  }

  K2(qryNotice){
    if(!run) R ki(-1);

    CThostFtdcQryNoticeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    R ki(pTradeApi->ReqQryNotice(&req,xi));
  }

  K2(qryInvestorPositionCombineDetail){
    if(!run) R ki(-1);

    CThostFtdcQryInvestorPositionCombineDetailField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.CombInstrumentID,kK(y)[2]->s);
    R ki(pTradeApi->ReqQryInvestorPositionCombineDetail(&req,xi));
  }

  K2(qryEWarrantOffset){
    if(!run) R ki(-1);

    CThostFtdcQryEWarrantOffsetField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.ExchangeID,kK(y)[2]->s);
    strcpy(req.InstrumentID,kK(y)[3]->s);
    R ki(pTradeApi->ReqQryEWarrantOffset(&req,xi));
  }

  K2(qryTransferSerial){
    if(!run) R ki(-1);

    CThostFtdcQryTransferSerialField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.AccountID,kK(y)[1]->s);
    strcpy(req.BankID,kK(y)[2]->s);
    R ki(pTradeApi->ReqQryTransferSerial(&req,xi));
  }


  K2(qryTradingNotice){
    if(!run) R ki(-1);

    CThostFtdcQryTradingNoticeField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQryTradingNotice(&req,xi));
  }

  K2(qryBrokerTradingParams){
    if(!run) R ki(-1);

    CThostFtdcQryBrokerTradingParamsField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQryBrokerTradingParams(&req,xi));
  }

  K2(qryBrokerTradingAlgos){
    if(!run) R ki(-1);

    CThostFtdcQryBrokerTradingAlgosField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.ExchangeID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    R ki(pTradeApi->ReqQryBrokerTradingAlgos(&req,xi));
  }

  K2(qrySettlementInfo){
    if(!run) R ki(-1);

    CThostFtdcQrySettlementInfoField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.TradingDay,kK(y)[2]->s);
    R ki(pTradeApi->ReqQrySettlementInfo(&req,xi));
  }

  K2(qryCombInstrumentGuard){
    if(!run) R ki(-1);

    CThostFtdcQryCombInstrumentGuardField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InstrumentID,kK(y)[1]->s);
    R ki(pTradeApi->ReqQryCombInstrumentGuard(&req,xi));
  }

  K2(qryCombAction){
    if(!run) R ki(-1);

    CThostFtdcQryCombActionField req;
    memset(&req,0,sizeof(req));
    strcpy(req.BrokerID,kK(y)[0]->s);
    strcpy(req.InvestorID,kK(y)[1]->s);
    strcpy(req.InstrumentID,kK(y)[2]->s);
    strcpy(req.ExchangeID,kK(y)[3]->s);

    R ki(pTradeApi->ReqQryCombAction(&req,xi));
  }

}


/*

///报单回报 
virtual void OnRtnOrder(CThostFtdcOrderField *pOrder){
printf("OnRtnOrder:\n"); printf("OrderSysID=[%s]\n", pOrder->OrderSysID); 
} 

//O("%s,%s,%s,%s,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%s,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d,%f\n",f->TradingDay,f->InstrumentID,f->ExchangeID,f->ExchangeInstID,f->LastPrice,f->PreSettlementPrice,f->PreClosePrice,f->PreOpenInterest,f->OpenPrice,f->HghestPrice,f->LowestPrice,f->Volume,f->Turnover,f->OpenInterest,f->ClosePrice,f->SettlementPrice,f->UpperLimitPrice,f->LowerLimitPrice,f->PreDelta,f->CurrDelta,f->UpdateTime,f->UpdateMillisec,f->BidPrice1,f->BidVolume1,f->AskPrice1,f->AskVolume1,f->BidPrice2,f->BidVolume2,f->AskPrice2,f->AskVolume2,f->BidPrice3,f->BidVolume3,f->AskPrice3,f->AskVolume3,f->BidPrice4,f->BidVolume4,f->AskPrice4,f->AskVolume4,f->BidPrice5,f->BidVolume5,f->AskPrice5,f->AskVolume5,f->AveragePrice);

//O("%s,%s,%s,%d,%f,%d,%f,%f,%f,%d,%f,%d,%f,%f,%f,%f,%f,%f,%f\n",f->TradingDay,f->InstrumentID,f->UpdateTime,f->UpdateMillisec,f->LastPrice,f->Volume,f->Turnover,f->OpenInterest,f->BidPrice1,f->BidVolume1,f->AskPrice1,f->AskVolume1,f->AveragePrice,f->PreSettlementPrice,f->PreClosePrice,f->PreOpenInterest,f->OpenPrice,f->HighestPrice,f->LowestPrice); 


*/



