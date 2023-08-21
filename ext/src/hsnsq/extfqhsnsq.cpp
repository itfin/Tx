#include "kcomm.h"
#include "concurrentqueue.h"

#include <HSNsqApi.h>

#define PIPE_CAPACITY 65536
#define QUEUE_SIZE 65536
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
#endif

Z moodycamel::ConcurrentQueue<K> mq(QUEUE_SIZE);
Z moodycamel::ProducerToken ptok(mq);
Z moodycamel::ConsumerToken ctok(mq);

ZI c;
ZI NGROUP=0;
ZI IGROUP=0;

ZK onmq(I i){
  K L=knk(0);
  //DBG("onmq:%d\n",0);
  read(i,&b,PIPE_CAPACITY);
  K k;
  while (mq.try_dequeue(ctok,k)){jk(&L,k);}
  k(0,"onhsnsq",L,(K)0);
  R ki(0);
}

Z V mpub(K x){
  mq.enqueue(ptok,x);
  write(p[1],&b,1);
};

Z CHSNsqApi *pQuoteApi;
#define MPUB(x,y) mpub(knk(2,ks(x),y));
#define NSQPUB(x,y) mpub(knk(2,ks(x),knk(3,ki(nRequestID),kb(bIsLast),(NULL==p)?knk(0):y)));
#define RETURNONERR if((NULL!=pRspInfo)&&(0!=(pRspInfo->ErrorID))){DBG("ErrorCode=[%d], ErrorMsg=[%s]\n",pRspInfo->ErrorID,pRspInfo->ErrorMsg);mpub(knk(2,ks("CTPError"),knk(3,ki(nRequestID),kb(bIsLast),knk(2,ki(pRspInfo->ErrorID),kp(pRspInfo->ErrorMsg)))));R;}

class CQuoteHandler : public CHSNsqSpi{
public: 
  CQuoteHandler(CHSNsqApi* lpHSNsqApi):m_lpHSNsqApi(lpHSNsqApi){} 
  ~CQuoteHandler(){} 

  virtual void OnFrontConnected() { 
    DBG("OnFrontConnected.\n"); 
    MPUB("FrontConnectQ",knk(0));
  } 

  virtual void OnFrontDisconnected(int nReason) { 
    DBG("OnFrontDisconnected.\n"); 
    MPUB("FrontDisconnectQ",knk(1,ki(nReason)));
  } 

  virtual void OnRspUserLogin(CHSNsqRspUserLoginField *p, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspUserLogin:%d\n",p); 
    RETURNONERR;
    NSQPUB("UserLoginQ",knk(18,ki(p->BranchID),kp(p->AccountID),kp(p->UserName),ki(p->TradingDay),ki(p->PreTradingDay),kc(p->BillConfirmFlag),ki(p->SessionID),kc(p->UserApplicationType),kp(p->UserApplicationInfo),kp(p->RiskLevel),kp(p->LastMacAddress),kp(p->LastIPAddress),ki(p->LastLoginTime),ki(p->CZCETime),ki(p->DCETime),ki(p->SHFETime),ki(p->CFFEXTime),ki(p->INETime)));
  } 

  ////以下是现货接口

  /// Description: 订阅-现货快照行情应答	
  virtual void OnRspSecuDepthMarketDataSubscribe(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuDepthMarketDataSubscribe\n"); 
    RETURNONERR;
    NSQPUB("RspSecuDepthMarketDataSubscribe",knk(0));
  }

  /// Description: 订阅取消-现货快照行情应答
  virtual void OnRspSecuDepthMarketDataCancel(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
   DBG("OnRspSecuDepthMarketDataCancel\n"); 
    RETURNONERR;
    NSQPUB("RspSecuDepthMarketDataCancel",knk(0));
  }
  
  /// Description: 主推-现货快照行情
  ///Others     :Bid1Volume买一队列数组, Bid1Count买一队列数组个数, MaxBid1Count买一总委托笔数
  ///           :Ask1Volume卖一队列数组, Ask1Count卖一队列数组个数, MaxAsk1Count卖一总委托笔数
  virtual void OnRtnSecuDepthMarketData(CHSNsqSecuDepthMarketDataField *p, HSIntVolume Bid1Volume[], HSNum Bid1Count, HSNum MaxBid1Count, HSIntVolume Ask1Volume[], HSNum Ask1Count, HSNum MaxAsk1Count){
    DBG("OnRtnSecuDepthMarketData:%d\n",p);

    K pa=ktn(KF,10),qa=ktn(KJ,10),pb=ktn(KF,10),qb=ktn(KJ,10),vb=ktn(KJ,Bid1Count),va=ktn(KJ,Ask1Count);
    DO(10,kF(pa)[i]=p->AskPrice[i];kJ(qa)[i]=p->AskVolume[i];kF(pb)[i]=p->BidPrice[i];kJ(qb)[i]=p->BidVolume[i];);
    DO(Bid1Count,kJ(vb)[i]=Bid1Volume[i]);DO(Ask1Count,kJ(va)[i]=Ask1Volume[i]);  
    if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("DepthMD",knk(61,kp(p->ExchangeID),kp(p->InstrumentID),kf(p->LastPrice),kf(p->PreClosePrice),kf(p->OpenPrice),kf(p->HighPrice),kf(p->LowPrice),kf(p->ClosePrice),kf(p->UpperLimitPrice),kf(p->LowerLimitPrice),ki(p->TradeDate),ki(p->UpdateTime),kj(p->TradeVolume),kf(p->TradeBalance),kf(p->AveragePrice),pb,pa,qb,qa,kj(p->TradesNum),kc(p->InstrumentTradeStatus),kj(p->TotalBidVolume),kj(p->TotalAskVolume),kf(p->MaBidPrice),kf(p->MaAskPrice),kf(p->MaBondBidPrice),kf(p->MaBondAskPrice),kf(p->YieldToMaturity),kf(p->IOPV),ki(p->EtfBuycount),ki(p->EtfSellCount),kj(p->EtfBuyVolume),kf(p->EtfBuyBalance),kj(p->EtfSellVolume),kf(p->EtfSellBalance),kj(p->TotalWarrantExecVolume),kf(p->WarrantLowerPrice),kf(p->WarrantUpperPrice),kj(p->CancelBuyNum),kj(p->CancelSellNum),kj(p->CancelBuyVolume),kj(p->CancelSellVolume),kf(p->CancelBuyValue),kf(p->CancelSellValue),kj(p->TotalBuyNum),kj(p->TotalSellNum),ki(p->DurationAfterBuy),ki(p->DurationAfterSell),kj(p->BidOrdersNum),kj(p->AskOrdersNum),kf(p->PreIOPV),kj(p->ChannelNo),kf(p->BondLastAuctionPrice),kj(p->BondAuctionVolume),kf(p->BondAuctionBalance),kc(p->BondLastTradeType),kp(p->R1),kj(MaxBid1Count),vb,kj(MaxAsk1Count),va));
  }

  /// Description: 主推-现货盘后定价快照行情
  ///Others     :Bid1Volume买一队列数组, Bid1Count买一队列数组个数, MaxBid1Count买一总委托笔数
  ///           :Ask1Volume卖一队列数组, Ask1Count卖一队列数组个数, MaxAsk1Count卖一总委托笔数
  virtual void OnRtnSecuATPMarketData(CHSNsqSecuATPMarketDataField *p, HSIntVolume Bid1Volume[], HSNum Bid1Count, HSNum MaxBid1Count, HSIntVolume Ask1Volume[], HSNum Ask1Count, HSNum MaxAsk1Count){
   DBG("OnRtnSecuDepthMarketData:%d\n",p);
   K vb=ktn(KJ,Bid1Count),va=ktn(KJ,Ask1Count);
   DO(Bid1Count,kJ(vb)[i]=Bid1Volume[i]);DO(Ask1Count,kJ(va)[i]=Ask1Volume[i]);  
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("DepthMDATP",knk(26,kp(p->ExchangeID),kp(p->InstrumentID),kf(p->PreClosePrice),kf(p->ClosePrice),ki(p->TradeDate),ki(p->UpdateTime),kc(p->InstrumentTradeStatus),kj(p->TradeVolume),kf(p->TradeBalance),kj(p->TradesNum),kj(p->TotalBidVolume),kj(p->TotalAskVolume),kj(p->CancelBuyNum),kj(p->CancelSellNum),kj(p->CancelBuyVolume),kj(p->CancelSellVolume),kf(p->BidPrice1),kf(p->AskPrice1),kj(p->BidVolume1),kj(p->AskVolume1),kj(p->ChannelNo),kp(p->R1),kj(MaxBid1Count),vb,kj(MaxAsk1Count),va));
  }

  /// Description: 订阅-现货逐笔行情应答
  virtual void OnRspSecuTransactionSubscribe(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuTransactionSubscribe\n"); 
    RETURNONERR;
    NSQPUB("RspSecuTransactionSubscribe",knk(0));    
  }

  /// Description: 订阅取消-现货逐笔行情应答
  virtual void OnRspSecuTransactionCancel(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuTransactionCancel\n"); 
    RETURNONERR;
    NSQPUB("RspSecuTransactionCancel",knk(0));        
  }

  /// Description: 主推-现货逐笔成交行情
  virtual void OnRtnSecuTransactionTradeData(CHSNsqSecuTransactionTradeDataField *p){
   DBG("OnRtnSecuTransactionTradeData:%d\n",p);
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("TransactionTrade",knk(14,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->TrdPrice),kj(p->TrdVolume),kf(p->TrdMoney),kj(p->TrdBuyNo),kj(p->TrdSellNo),kc(p->TrdBSFlag),kj(p->BizIndex)));
  }

  /// Description: 主推-现货逐笔委托行情
  virtual void OnRtnSecuTransactionEntrustData(CHSNsqSecuTransactionEntrustDataField *p){
   DBG("OnRtnSecuTransactionEntrustData:%d\n",p);
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("TransactionEntrust",knk(14,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->OrdPrice),kj(p->OrdVolume),kc(p->OrdSide),kc(p->OrdType),kj(p->OrdNo),kj(p->BizIndex),kj(p->TrdVolume)));
  }

  /// Description: 主推-现货盘后固定逐笔成交行情
  virtual void OnRtnSecuATPTransactionTradeData(CHSNsqSecuTransactionTradeDataField *p){
   DBG("OnRtnSecuATPTransactionTradeData:%d\n",p);
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("TransactionTradeATP",knk(14,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->TrdPrice),kj(p->TrdVolume),kf(p->TrdMoney),kj(p->TrdBuyNo),kj(p->TrdSellNo),kc(p->TrdBSFlag),kj(p->BizIndex)));
  }


  /// Description: 获取当前交易日现货合约应答
  virtual void OnRspQrySecuInstruments(CHSNsqSecuInstrumentStaticInfoField *p, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspQrySecuInstruments:%d\n",p); 
    RETURNONERR;
    NSQPUB("RspQrySecuInstruments",knk(11,kp(p->ExchangeID),kp(p->InstrumentID),kp(p->InstrumentName),kc(p->SecurityType),kf(p->PreClosePrice),kf(p->UpperLimitPrice),kf(p->LowerLimitPrice),kf(p->PriceTick),ki(p->BuyVolumeUnit),ki(p->SellVolumeUnit),ki(p->TradeDate)));        
  }

  /// Description: 期权订阅-行情应答
  virtual void OnRspOptDepthMarketDataSubscribe(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspOptDepthMarketDataSubscribe\n"); 
    RETURNONERR;
    NSQPUB("OnRspOptDepthMarketDataSubscribe",knk(0));        
  }

  /// Description: 期权订阅取消-行情应答
  virtual void OnRspOptDepthMarketDataCancel(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspOptDepthMarketDataCancel\n"); 
    RETURNONERR;
    NSQPUB("OnRspOptDepthMarketDataCancel",knk(0));        
  }

  /// Description: 主推-期权行情
  virtual void OnRtnOptDepthMarketData(CHSNsqOptDepthMarketDataField *p){
    DBG("OnRtnOptDepthMarketData:%d\n",p);
    K pa=ktn(KF,10),qa=ktn(KJ,10),pb=ktn(KF,10),qb=ktn(KJ,10);
    DO(10,kF(pa)[i]=p->AskPrice[i];kJ(qa)[i]=p->AskVolume[i];kF(pb)[i]=p->BidPrice[i];kJ(qb)[i]=p->BidVolume[i];);

    if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("DepthMDOpt",knk(34,kp(p->ExchangeID),kp(p->InstrumentID),kf(p->LastPrice),kf(p->PreClosePrice),kf(p->OpenPrice),kf(p->HighPrice),kf(p->LowPrice),kf(p->ClosePrice),kj(p->PreOpenInterest),kj(p->OpenInterest),kf(p->PreSettlementPrice),kf(p->SettlementPrice),kf(p->UpperLimitPrice),kf(p->LowerLimitPrice),kf(p->PreDelta),kf(p->CurDelta),ki(p->TradeDate),ki(p->UpdateTime),kj(p->TradeVolume),kf(p->TradeBalance),kf(p->AveragePrice),pb,pa,qb,qa,kj(p->TradesNum),kc(p->InstrumentTradeStatus),kp(p->OpenRestriction),kf(p->AuctionPrice),kj(p->AuctionVolume),ki(p->LastEnquiryTime),kj(p->LeaveQty),ki(p->ChannelNo),kp(p->R1)));
  }

  /// Description: 获取当前交易日合约应答
  virtual void OnRspQryOptInstruments(CHSNsqOptInstrumentStaticInfoField *p, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspQryOptInstruments:%d\n",p); 
    RETURNONERR;
    NSQPUB("RspQryOptInstruments",knk(31,kp(p->ExchangeID),kp(p->InstrumentID),kp(p->InstrumentTradeID),kp(p->InstrumentName),kc(p->SecurityType),kp(p->UnderlyingInstrID),kc(p->OptionsType),kc(p->ExerciseStyle),kj(p->ContractMultiplierUnit),kf(p->ExercisePrice),ki(p->StartDate),ki(p->EndDate),ki(p->ExerciseDate),ki(p->DeliveryDate),ki(p->ExpireDate),kj(p->TotalLongPosition),kf(p->PreClosePrice),kf(p->PreSettlPrice),kf(p->UnderlyingClosePrice),kf(p->UpperLimitPrice),kf(p->LowerLimitPrice),kf(p->MarginUnit),kf(p->MarginRatioParam1),kf(p->MarginRatioParam2),kj(p->VolumeMultiple),kj(p->MinLimitOrderVolume),kj(p->MaxLimitOrderVolume),kj(p->MinMarketOrderVolume),kj(p->MaxMarketOrderVolume),kf(p->PriceTick),ki(p->TradeDate)));        
  }
	 
  /// Description: 获取合约的最新快照信息应答
  virtual void OnRspQryOptDepthMarketData(CHSNsqOptDepthMarketDataField *p, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspQryOptDepthMarketData:%d\n",p); 
    RETURNONERR;
    K pa=ktn(KF,10),qa=ktn(KJ,10),pb=ktn(KF,10),qb=ktn(KJ,10);
    DO(10,kF(pa)[i]=p->AskPrice[i];kJ(qa)[i]=p->AskVolume[i];kF(pb)[i]=p->BidPrice[i];kJ(qb)[i]=p->BidVolume[i];);
    NSQPUB("RspQryOptDepthMarketData",knk(34,kp(p->ExchangeID),kp(p->InstrumentID),kf(p->LastPrice),kf(p->PreClosePrice),kf(p->OpenPrice),kf(p->HighPrice),kf(p->LowPrice),kf(p->ClosePrice),kj(p->PreOpenInterest),kj(p->OpenInterest),kf(p->PreSettlementPrice),kf(p->SettlementPrice),kf(p->UpperLimitPrice),kf(p->LowerLimitPrice),kf(p->PreDelta),kf(p->CurDelta),ki(p->TradeDate),ki(p->UpdateTime),kj(p->TradeVolume),kf(p->TradeBalance),kf(p->AveragePrice),pb,pa,qb,qa,kj(p->TradesNum),kc(p->InstrumentTradeStatus),kp(p->OpenRestriction),kf(p->AuctionPrice),kj(p->AuctionVolume),ki(p->LastEnquiryTime),kj(p->LeaveQty),ki(p->ChannelNo),kp(p->R1)));        

  }

  ////以下是现货逐笔重建接口

  /// Description: 重建应答-现货逐笔数据
  virtual void OnRspSecuTransactionData(CHSNsqSecuTransactionDataField *pr, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuTransactionData\n"); 
    RETURNONERR;
    K L;
    char t=pr->TransType;
    switch(t){
    case '1':{
      CHSNsqSecuTransactionTradeDataField *p=&pr->TradeData;
      L=knk(14,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->TrdPrice),kj(p->TrdVolume),kf(p->TrdMoney),kj(p->TrdBuyNo),kj(p->TrdSellNo),kc(p->TrdBSFlag),kj(p->BizIndex));
      break;}
    case '2':{
      CHSNsqSecuTransactionEntrustDataField *p=&pr->EntrustData;
      L=knk(14,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->OrdPrice),kj(p->OrdVolume),kc(p->OrdSide),kc(p->OrdType),kj(p->OrdNo),kj(p->BizIndex),kj(p->TrdVolume));
      break;}  
    case '3':{
      CHSNsqBondTransactionTradeDataField *p=&pr->BondTradeData;
      L=knk(15,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->TrdPrice),kj(p->TrdVolume),kj(p->TrdBuyNo),kj(p->TrdSellNo),kc(p->TrdBSFlag),kc(p->TradeType),kh(p->SettlPeriod),kh(p->SettlType));
      break;}
    case '4':{
      CHSNsqBondTransactionEntrustDataField *p=&pr->BondEntrustData;
      L=knk(19,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->OrdPrice),kj(p->OrdVolume),kc(p->OrdSide),kc(p->OrdType),kc(p->TradeType),kh(p->SettlPeriod),kh(p->SettlType),kp(p->QuoteID),kp(p->MemberID),kp(p->InvestorType),kp(p->InvestorID),kp(p->TraderCode));
      break;}
    default:L=knk(0);  
    }
    NSQPUB("RspSecuTransactionData",knk(3,kj(pr->LatestSeqNo),kc(t),L));        
  }

  /// Description: 重建应答超时-现货逐笔数据（本回调线程与其他回调线程不同）
  virtual void OnRspSecuTransactionDataTimeout(int nRequestID){
    DBG("OnRspSecuTransactionDataTimeout\n"); 
    MPUB("RspSecuTransactionDataTimeout",knk(1,ki(nRequestID)));
  }


  /// Description: 主推-深证债券逐笔成交行情
  virtual void OnRtnBondTransactionTradeData(CHSNsqBondTransactionTradeDataField* p){
   DBG("OnRtnBondTransactionTradeData:%d\n",p);
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("TransactionTradeBond",knk(15,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->TrdPrice),kj(p->TrdVolume),kj(p->TrdBuyNo),kj(p->TrdSellNo),kc(p->TrdBSFlag),kc(p->TradeType),kh(p->SettlPeriod),kh(p->SettlType)));
  }

  /// Description: 主推-深证债券逐笔委托行情
  virtual void OnRtnBondTransactionEntrustData(CHSNsqBondTransactionEntrustDataField* p){
   DBG("OnRtnSecuTransactionEntrustData:%d\n",p);
   if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("TransactionEntrustBond",knk(19,kp(p->ExchangeID),kp(p->InstrumentID),ki(p->TransFlag),kj(p->SeqNo),ki(p->ChannelNo),ki(p->TradeDate),ki(p->TransactTime),kf(p->OrdPrice),kj(p->OrdVolume),kc(p->OrdSide),kc(p->OrdType),kc(p->TradeType),kh(p->SettlPeriod),kh(p->SettlType),kp(p->QuoteID),kp(p->MemberID),kp(p->InvestorType),kp(p->InvestorID),kp(p->TraderCode)));
  }

  ////以下是港股通接口

  /// Description: 获取当前交易日合约应答
  virtual void OnRspQryHktInstruments(CHSNsqHktInstrumentStaticInfoField *p, CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspQryHktInstruments:%d\n",p); 
    RETURNONERR;
    NSQPUB("RspQryHktInstruments",knk(8,kp(p->ExchangeID),kp(p->InstrumentID),kp(p->InstrumentName),kc(p->SecurityType),kf(p->PreClosePrice),ki(p->BuyVolumeUnit),kf(p->SellVolumeUnit),ki(p->TradeDate)));        
  }

  /// Description: 主推-港股通行情
  virtual void OnRtnHktDepthMarketData(CHSNsqHktDepthMarketDataField *p){
    DBG("OnRtnHktDepthMarketData:%d\n",p);
    K pa=ktn(KF,10),qa=ktn(KJ,10),pb=ktn(KF,10),qb=ktn(KJ,10);
    DO(10,kF(pa)[i]=p->AskPrice[i];kJ(qa)[i]=p->AskVolume[i];kF(pb)[i]=p->BidPrice[i];kJ(qb)[i]=p->BidVolume[i];);

    if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("DepthMDHkt",knk(22,kp(p->ExchangeID),kp(p->InstrumentID),kf(p->LastPrice),kf(p->PreClosePrice),kf(p->HighPrice),kf(p->LowPrice),kf(p->NomianlPrice),ki(p->TradeDate),ki(p->UpdateTime),kj(p->TradeVolume),kf(p->TradeBalance),pb,pa,qb,qa,kc(p->InstrumentTradeStatus),kc(p->BoardLotOrderBidLimit),kc(p->BoardLotOrderAskLimit),kc(p->OddLotOrderBidLimit),kc(p->OddLotOrderAskLimit),ki(p->ChannelNo),kp(p->R1)));
  }

  ////以下是现货快照Plus接口

  /// Description: 订阅-现货快照Plus行情应答	
  virtual void OnRspSecuDepthMarketDataPlusSubscribe(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuDepthMarketDataPlusSubscribe\n"); 
    RETURNONERR;
    NSQPUB("OnRspSecuDepthMarketDataPlusSubscribe",knk(0));        
  }

  /// Description: 订阅取消-现货快照Plus行情应答
  virtual void OnRspSecuDepthMarketDataPlusCancel(CHSNsqRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
    DBG("OnRspSecuDepthMarketDataPlusCancell\n"); 
    RETURNONERR;
    NSQPUB("OnRspSecuDepthMarketDataPlusCancel",knk(0));        
  }

  /// Description: 主推-现货快照Plus行情
  virtual void OnRtnSecuDepthMarketDataPlus(CHSNsqSecuDepthMarketDataPlusField *p){
    DBG("OnRtnSecuDepthMarketDataPlus:%d\n",p);
    K pa=ktn(KF,10),qa=ktn(KJ,10),pb=ktn(KF,10),qb=ktn(KJ,10);
    DO(10,kF(pa)[i]=p->AskPrice[i];kJ(qa)[i]=p->AskVolume[i];kF(pb)[i]=p->BidPrice[i];kJ(qb)[i]=p->BidVolume[i];);

    if((0==NGROUP)||IGROUP==p->ChannelNo%NGROUP)MPUB("DepthMDPlus",knk(18,ki(p->ChannelNo),kp(p->ExchangeID),kp(p->InstrumentID),kf(p->LastPrice),kf(p->OpenPrice),kf(p->HighPrice),kf(p->LowPrice),ki(p->TradeDate),ki(p->UpdateTime),kj(p->TradeVolume),kf(p->TradeBalance),kj(p->TotalBidVolume),kj(p->TotalAskVolume),kj(p->TradesNum),pb,qb,pa,qa));
  }

  /// Description: 主推-现货快照Plus行情停止通知
  ///Others     :当“快照Plus”服务发现交易所下发的某个通道的逐笔数据存在丢包时，“快照Plus”服务会自行发起对丢失逐笔数据的重建。
  ///           在重建完成之前，“快照Plus”服务会周期性推送具体通道的停止通知，从而触发本回调。
  ///           当重建完成后，具体通道的停止通知会停止推送，同时“快照Plus”服务会继续推送相应通道重建出来的快照
  virtual void OnRtnSecuDepthMarketDataPlusStopNotice(CHSNsqSecuDepthMarketDataPlusStopNoticeField *p){
    DBG("OnRtnSecuDepthMarketDataPlusStopNotice:%d\n",p);
    MPUB("DepthMDPlusStop",knk(1,ki(p->ChannelNo)));
  }

private:
  CHSNsqApi * m_lpHSNsqApi;
};

Z CQuoteHandler * pQuoteSpi;

extern "C"{
  K1(nsqver){
    R kp((S)GetNsqApiVersion());
  }

  K1(nsqerr){
    R kp((S)pQuoteApi->GetApiErrorMsg(xi));
  }
  
  K2(initnsq){
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
    sd1(p[0],onmq);
    pQuoteApi = NewNsqApiExt(kK(y)[0]->s,kK(y)[1]->s);
    pQuoteSpi = new CQuoteHandler(pQuoteApi);
    pQuoteApi->RegisterSpi(pQuoteSpi);

    //pQuoteApi->RegisterFront(xs);
    n=pQuoteApi->Init(xs);
    if(0!=n){O("init fail:iRet %d, error: %s\n",n,pQuoteApi->GetApiErrorMsg(n));R ki(-4);}
    NGROUP=kK(y)[2]->i;
    IGROUP=kK(y)[3]->i;
    R ki(run);
  }

  K1(freensq){
    if(!run) R ki(-1);

    pQuoteApi->RegisterSpi(NULL);
    pQuoteApi->ReleaseApi();
    pQuoteApi=NULL;
    delete pQuoteSpi;
    pQuoteSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);

    run--;
    R ki(run);
  }

  K1(nsqrun){
    R ki(run);
  } 

  K2(userLoginQ){
    if(!run) R ki(-1);
    CHSNsqReqUserLoginField req;

    strcpy(req.AccountID,kK(y)[0]->s); 
    strcpy(req.Password,kK(y)[1]->s);

    /*
    req.UserApplicationType=kK(y)[2]->g; 
    strcpy(req.UserApplicationInfo,kK(y)[3]->s);
    strcpy(req.MacAddress,kK(y)[4]->s);
    strcpy(req.IPAddress,kK(y)[5]->s);
    */
    
    R ki(pQuoteApi->ReqUserLogin(&req,xi));
  }


  K2(subfut){ 
    if(!run) R ki(-1);
    CHSNsqReqFutuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqFutuDepthMarketDataSubscribe(req,n,xi));
  }

  K2(cxlfut){ 
    if(!run) R ki(-1);
    CHSNsqReqFutuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqFutuDepthMarketDataCancel(req,n,xi));
  }

  K2(reqfutref){ 
    if(!run) R ki(-1);
    CHSNsqReqFutuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQryFutuInstruments(req,n,xi));
  }

  K2(reqfutsnap){ 
    if(!run) R ki(-1);
    CHSNsqReqFutuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQryFutuDepthMarketData(req,n,xi));
  }


  K2(substk){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqSecuDepthMarketDataSubscribe(req,n,xi));
  }

  K2(cxlstk){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqSecuDepthMarketDataCancel(req,n,xi));
  }


  K2(substkord){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[1]->i;
    strcpy(req[0].ExchangeID,kK(y)[2]->s); 
    R ki(pQuoteApi->ReqSecuTransactionSubscribe(kK(y)[0]->g,req,n,xi));
  }

  K2(cxlstkord){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[1]->i;
    strcpy(req[0].ExchangeID,kK(y)[2]->s); 
    R ki(pQuoteApi->ReqSecuTransactionCancel(kK(y)[0]->g,req,n,xi));
  }

  K2(reqstkref){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQrySecuInstruments(req,n,xi));
  }

  K2(reqstksnap){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQrySecuDepthMarketData(req,n,xi));
  }

  K2(subopt){ 
    if(!run) R ki(-1);
    CHSNsqReqOptDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqOptDepthMarketDataSubscribe(req,n,xi));
  }

  K2(cxlopt){ 
    if(!run) R ki(-1);
    CHSNsqReqOptDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqOptDepthMarketDataCancel(req,n,xi));
  }

  K2(reqoptref){ 
    if(!run) R ki(-1);
    CHSNsqReqOptDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQryOptInstruments(req,n,xi));
  }

  K2(reqoptsnap){ 
    if(!run) R ki(-1);
    CHSNsqReqOptDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQryOptDepthMarketData(req,n,xi));
  }

  K2(substkplus){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqSecuDepthMarketDataPlusSubscribe(req,n,xi));
  }

  K2(cxlstkplus){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqSecuDepthMarketDataPlusCancel(req,n,xi));
  }

  K2(reqstkrebuild){ 
    if(!run) R ki(-1);
    CHSNsqReqSecuTransactionRebuildField req;
    strcpy(req.ExchangeID,kK(y)[0]->s);
    req.ChannelNo=kK(y)[1]->i;
    req.BeginSeqNo=kK(y)[2]->j;
    req.EndSeqNo=kK(y)[3]->i;
    req.RebuildType=kK(y)[4]->g;
    R ki(pQuoteApi->ReqSecuTransactionRebuild(&req,xi));
  }


  K2(reqhktref){ 
    if(!run) R ki(-1);
    CHSNsqReqHktDepthMarketDataField req[10000];
    I n=kK(y)[0]->i;
    strcpy(req[0].ExchangeID,kK(y)[1]->s); 
    R ki(pQuoteApi->ReqQryHktInstruments(req,n,xi));
  }

  
}
