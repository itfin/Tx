#include "kcomm.h"
#include <queue>
#include "X2AtoTradeApi.h"
#include "X2AtoTradeSpi.h"

#define ORD_POOL_SIZE 8192
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
  k(0,"onato",L,(K)0);
  R ki(0);
}

Z V mpub(K x){
  LOCK;
  mq.push(b9(1,x));
  UNLOCK;    
  write(p[1],&b,1);
};

Z  X2ClientTradeApi *pTradeApi;   

#define MPUB(x,y) mpub(knk(2,ks(x),y));

#define LPUB(x,y) mpub(knk(2,ks(x),knk(2,ki(nRequestID),(NULL==p)?knk(0):y)));

#define RETURNONATOERR(x) if(0!=rspInfo.errCode){MPUB("AtoError",knk(2,ki(nRequestID),knk(3,kp(x),ki(rspInfo.errCode),kp((S)rspInfo.errMsg))));R;}

class CTradeHandler : public X2ClientTradeSpi{
public: 
  CTradeHandler(){} 
  ~CTradeHandler(){}

  virtual void OnDisconnect(){MPUB("OnDisconnect",knk(0));}
  virtual void OnConnect(){MPUB("OnConnect",knk(0));}
  
  virtual void OnRspLogin(const AtoSDKLoginRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspLogin");
    K L=knk(0),v;
    DO(n,v=knk(21,ki(p->operatorNo),kp((S)p->operatorName),ki(p->organId),kp((S)p->organName),ki(p->productId),kp((S)p->productName),ki(p->productStatus),kj(p->unitId),kp((S)p->unitName),ki(p->unitStatus),ki(p->accountId),kp((S)p->accountUser),kp((S)p->accountName),ki(p->accountType),ki(p->accountStatus),ki(p->accountConfStatus),ki(p->marketType),kp((S)p->stkAcctCode),kp((S)p->stkAcctName),ki(p->stkAcctStatus),ki(p->primaryFlag));jk(&L,v);p++);
    LPUB("OnRspLogin",L);
  }
  
  virtual void OnRspStockPosition(const AtoSDKOperationalPositionRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspStockPosition");
    K L=knk(0),v;
    DO(n,v=knk(19,ki(p->organId),ki(p->productId),kj(p->unitId),ki(p->accountId),kp((S)p->accountUser),kp((S)p->stkAcctCode),ki(p->marketType),kp((S)p->symbol),ki(p->positionType),ki(p->initQty),ki(p->currentQty),ki(p->algoEnableQty),ki(p->orderEnableQty),kf(p->costAmt),kf(p->incomeAmt),kf(p->interestIncome),kf(p->interestCostAmt),kp((S)p->positionStr),kf(p->positionValue));jk(&L,v);p++);
    LPUB("OnRspStockPosition",L);    
  }
  
  virtual void OnRspQueryAsset(const AtoSDKQueryAssetRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspQueryAsset");
    K L=knk(0),v;
    DO(n,v=knk(21,ki(p->organId),ki(p->productId),kj(p->unitId),ki(p->accountId),kf(p->prevNetAsset),kf(p->prevCumAsset),kf(p->cumAsset),kf(p->netAsset),kf(p->securityFund),kf(p->orderEnableAmt),kf(p->cashAmt),kf(p->stockAsset),kf(p->fundAsset),kf(p->bondAsset),kf(p->repoAsset),kf(p->otherAsset),kj(p->productShare),kj(p->unitShare),kj(p->perNav),kj(p->prevPerNav),kp((S)p->positionStr));jk(&L,v);p++);
    LPUB("OnRspQueryAsset",L);    
  }

  virtual void OnRtnOrderReport(const AtoSDKOrderPush& d){
    MPUB("OnRtnOrderReport",knk(40,ki(d.operatorNo),ki(d.organId),ki(d.accountId),kp((S)d.accountUser),ki(d.productId),kj(d.unitId),ki(d.algoTypeId),kj(d.sysQuoteId),kj(d.sysOrderId),kp((S)d.clOrderId),kp((S)d.brokerOrderId),ki(d.marketType),kp((S)d.symbol),ki(d.side),ki(d.pxType),kf(d.orderPx),ki(d.orderQty),ki(d.transacTime),ki(d.orderStatus),ki(d.securityType),ki(d.cumQty),ki(d.cumAmt),ki(d.leavesQty),ki(d.cancelTime),ki(d.updateTime),kp((S)d.opstation),kp((S)d.basketId),kj(d.sysQuoteBatchId),kj(d.sysOrderBatchId),kp((S)d.stkAcctCode),ki(d.cancelQty),ki(d.assetType),ki(d.reportDate),ki(d.reportTime),ki(d.tradeDate),ki(d.tradeTime),kf(d.allFee),kf(d.dealBondAccrInterest),kp((S)d.remark),kp((S)d.externalId)));    
  }

  virtual void OnSubTopic(const X2Topic& d, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnSubTopic");
    MPUB("OnSubTopic",knk(3,ki(d.accountId),kj(d.unitId),kp((S)d.topicName)));    
  }

  virtual void OnRtnTradeReport(const AtoSDKDealPush& d){
    MPUB("OnRtnTradeReport",knk(32,ki(d.operatorNo),kp((S)d.accountUser),ki(d.accountId),ki(d.productId),kj(d.unitId),ki(d.algoTypeId),kp((S)d.brokerOrderId),kj(d.sysQuoteId),kj(d.sysOrderId),kp((S)d.clOrderId),ki(d.marketType),kp((S)d.symbol),ki(d.side),ki(d.pxType),kf(d.orderPx),ki(d.orderQty),ki(d.orderStatus),ki(d.securityType),ki(d.dealQty),kf(d.dealPx),ki(d.dealTime),kp((S)d.basketId),kj(d.sysQuoteBatchId),kj(d.sysOrderBatchId),kp((S)d.stkAcctCode),ki(d.assetType),kf(d.allFee),kf(d.dealBondAccrInterest),kj(d.sysDealId),kp((S)d.externalId),ki(d.dealDate),kp((S)d.dealId)));    
  }

  virtual void OnRtnInstructionReport(const AtoSDKAlgoPush& d){
    MPUB("OnRtnInstructionReport",knk(33,ki(d.operatorNo),ki(d.productId),kj(d.unitId),ki(d.accountId),kp((S)d.accountUser),ki(d.algoTypeId),kp((S)d.symbol),ki(d.marketType),kj(d.effectiveTime),kj(d.expireTime),ki(d.securityType),ki(d.assetType),kp((S)d.basketId),kj(d.sysQuoteBatchId),kj(d.sysQuoteId),ki(d.tradeDate),ki(d.transacTime),kp((S)d.algoParam),ki(d.taskQty),ki(d.cumQty1),ki(d.cumQty2),ki(d.outstandingQty1),ki(d.outstandingQty2),ki(d.leavesQty1),ki(d.leavesQty2),kf(d.taskAmt),kf(d.cumAmt1),kf(d.cumAmt2),ki(d.algoStatus),ki(d.orderCancelQty),ki(d.orderFailQty),kp((S)d.rspAlgoInfo),kp((S)d.externalId)));    
  }

  virtual void OnRtnFundReport(const AtoSDKChangeFundPush& d){
    MPUB("OnRtnFundReport",knk(8,ki(d.productId),ki(d.accountId),kj(d.unitId),kp((S)d.accountUser),ki(d.currencyType),kf(d.initAmt),kf(d.orderEnableAmt),kf(d.algoEnableAmt)));    
  }

  virtual void OnRtnPositionReport(const AtoSDKChangePositionPush& d){
    MPUB("OnRtnPositionReport",knk(15,ki(d.productId),ki(d.accountId),kj(d.unitId),kp((S)d.accountUser),ki(d.marketType),kp((S)d.symbol),kp((S)d.stkAcctCode),ki(d.positionType),kf(d.costAmt),ki(d.initQty),ki(d.currentQty),ki(d.orderEnableQty),kj(d.algoEnableQty),ki(d.currencyType),ki(d.securityType)));    
  }

  virtual void OnRspQueryOrderActual(const AtoSDKQueryOrderRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspQueryOrderActual");
    K L=knk(0),v;
    DO(n,v=knk(35,kj(p->orderBatchId),kj(p->sysOrderId),kj(p->sysQuoteBatchId),kj(p->sysQuoteId),ki(p->operatorNo),ki(p->tradeDate),ki(p->tradeTime),ki(p->organId),ki(p->productId),kj(p->unitId),ki(p->accountId),kp((S)p->accountUser),kp((S)p->stkAcctCode),ki(p->marketType),kp((S)p->symbol),ki(p->securityType),ki(p->assetType),ki(p->reportDate),ki(p->reportTime),kp((S)p->brokerOrderId),ki(p->side),ki(p->pxType),kf(p->orderPx),ki(p->orderQty),kf(p->orderAmt),ki(p->orderStatus),ki(p->cancelQty),kf(p->dealAmt),ki(p->dealQty),kf(p->allFee),kf(p->dealBondAccrInterest),kp((S)p->basketId),kp((S)p->rspOrderInfo),kp((S)p->positionStr),kp((S)p->externalId));jk(&L,v);p++);
    LPUB("OnRspQueryOrderActual",L);    
  }

  virtual void OnRspQueryDealActual(const AtoSDKQueryDealRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspQueryDealActual");
    K L=knk(0),v;
    DO(n,v=knk(26,ki(p->operatorNo),kj(p->sysDealId),kp((S)p->dealId),kp((S)p->accountUser),ki(p->accountId),ki(p->productId),kj(p->unitId),ki(p->algoTypeId),kp((S)p->brokerOrderId),kj(p->sysQuoteId),kj(p->sysOrderId),ki(p->marketType),kp((S)p->symbol),ki(p->side),ki(p->securityType),ki(p->dealQty),kf(p->dealPx),ki(p->dealDate),ki(p->dealTime),kf(p->dealAmt),kp((S)p->stkAcctCode),ki(p->assetType),kf(p->allFee),kf(p->dealBondAccrInterest),kp((S)p->positionStr),kp((S)p->externalId));jk(&L,v);p++);
    LPUB("OnRspQueryDealActual",L);    
  }

  virtual void OnRspCreateOrderActual(const AtoSDKOrderCreateRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspCreateOrderActual");
    K L=knk(0),v;
    DO(n,v=knk(9,ki(p->errCode),kp((S)p->errMsg),ki(p->createDate),ki(p->createTime),kj(p->orderBatchId),kj(p->sysOrderId),kj(p->riskBusinId),ki(p->riskWarnFlag),ki(p->warnOperation));jk(&L,v);p++);
    LPUB("OnRspCreateOrderActual",L);    
  }

  virtual void OnRspCancelOrderActual(const AtoSDKOrderCancelRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspCancelOrderActual");
    K L=knk(0),v;
    DO(n,v=knk(7,ki(p->errCode),kp((S)p->errMsg),kj(p->sysOrderId),kj(p->cancelId),kj(p->riskBusinId),ki(p->riskWarnFlag),ki(p->warnOperation));jk(&L,v);p++);
    LPUB("OnRspCancelOrderActual",L);    
  }

  virtual void OnRspQueryOrderInstruction(const AtoSDKQueryAlgoRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspQueryOrderInstruction");
    K L=knk(0),v;
    DO(n,v=knk(37,kj(p->sysQuoteBatchId),kj(p->sysQuoteId),ki(p->operatorNo),ki(p->organId),ki(p->productId),kj(p->unitId),ki(p->accountId),kp((S)p->accountUser),ki(p->tradeDate),ki(p->algoTypeId),kp((S)p->algoTypeName),ki(p->marketType),kp((S)p->symbol),kp((S)p->basketId),kp((S)p->algoParam),kj(p->effectiveTime),kj(p->expireTime),ki(p->securityType),ki(p->assetType),ki(p->transacTime),ki(p->taskQty),kf(p->taskAmt),ki(p->cumQty1),ki(p->cumQty2),ki(p->outstandingQty1),ki(p->outstandingQty2),ki(p->leavesQty1),ki(p->leavesQty2),kf(p->cumAmt1),kf(p->cumAmt2),ki(p->algoStatus),ki(p->orderCancelQty),ki(p->orderFailQty),ki(p->cancelQty),kp((S)p->rspAlgoInfo),kp((S)p->positionStr),kp((S)p->externalId));jk(&L,v);p++);
    LPUB("OnRspQueryOrderInstruction",L);    
  }

  virtual void OnRspInstructionCreate(const AtoSDKAlgoCreateRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspInstructionCreate");
    K L=knk(0),v;
    DO(n,v=knk(9,ki(p->errCode),kp((S)p->errMsg),kp((S)p->externalId),kp((S)p->basketId),kj(p->sysQuoteBatchId),kj(p->sysQuoteId),kj(p->riskBusinId),ki(p->riskWarnFlag),ki(p->warnOperation));jk(&L,v);p++);
    LPUB("OnRspInstructionCreate",L);    
  }

  virtual void OnRspInstructionReplace(const AtoSDKAlgoReplaceRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspInstructionReplace");
    K L=knk(0),v;
    DO(n,v=knk(5,ki(p->errCode),kp((S)p->errMsg),ki(p->updateDate),ki(p->updateTime),kj(p->sysQuoteId));jk(&L,v);p++);
    LPUB("OnRspInstructionReplace",L);    
  }

  virtual void OnRspInstructionControl(const AtoSDKAlgoOperationRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspInstructionControl");
    K L=knk(0),v;
    DO(n,v=knk(5,ki(p->errCode),kp((S)p->errMsg),ki(p->updateDate),ki(p->updateTime),kj(p->sysQuoteId));jk(&L,v);p++);
    LPUB("OnRspInstructionControl",L);    
  }

  virtual void OnRspRiskWarn(const AtoSDKWarnInfoRsp* p, int n, const X2RspInfoField& rspInfo, int nRequestID){
    RETURNONATOERR("OnRspRiskWarn");
    K L=knk(0),v;
    DO(n,v=knk(33,kj(p->riskWarnId),kj(p->riskBusinId),ki(p->riskRuleId),ki(p->riskTypeId),ki(p->organId),ki(p->riskWarnLevel),ki(p->productId),kj(p->unitId),ki(p->accountId),kp((S)p->symbol),ki(p->marketType),ki(p->side),ki(p->currencyType),ki(p->riskControlBiz),ki(p->compareDirection),ki(p->symbolCollect),ki(p->layerCollect),ki(p->warnLevel),ki(p->warnOperation),kf(p->setValue),kf(p->calcValue),kj(p->numeratorValue),kj(p->denominatorValue),ki(p->riskGroupId),kj(p->commandId),kj(p->sysQuoteId),kj(p->sysOrderId),ki(p->operatorNo),kp((S)p->remark),kp((S)p->ruleRemark),kp((S)p->setRuleInfo),ki(p->createTime),ki(p->displayUnit));jk(&L,v);p++);
    LPUB("OnRspRiskWarn",L);    
  }
};

Z CTradeHandler * pTradeSpi;;

extern "C"{
  K2(initato){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
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
    setm(1);
    sd1(p[0],onmq);

    pTradeApi=X2ClientTradeApi::CreateTradeApi();if(NULL==pTradeApi) R ki(-10004);
    pTradeSpi = new CTradeHandler();
    if(r=pTradeApi->RegisterSpi(pTradeSpi))R ki(-abs(r));
    if(r=pTradeApi->Init(xs)) R ki(-abs(r));
    
    R ki(run);
  }

  K1(freeato){
    if(!run) R ki(-1);
    
    pTradeApi->DisConnect();
    pTradeApi->RegisterSpi(NULL);pTradeApi->Release();
    delete pTradeSpi;delete pTradeApi;
    pTradeApi=NULL;pTradeSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(atorun){
    R ki(run);
  } 

  K2(atoLogin){
    if(!run) R ki(-1);
    
    AtoSDKLogin req;
    req.operatorNo=kK(y)[0]->i;
    strcpy(req.password,kK(y)[1]->s); 
    strcpy(req.ip,kK(y)[2]->s);
    strcpy(req.mac,kK(y)[3]->s); 
    strcpy(req.operInfo,kK(y)[4]->s); 

    R ki(pTradeApi->Login(req,xi));
  } 

  K2(reqStockPosition){
    if(!run) R ki(-1);
    
    AtoSDKOperationalPosition req;
    req.positionLevel=kK(y)[0]->i;
    strcpy(req.productIdStr,kK(y)[1]->s); 
    strcpy(req.unitIdStr,kK(y)[2]->s); 
    strcpy(req.accountIdStr,kK(y)[3]->s); 
    strcpy(req.marketTypeStr,kK(y)[4]->s); 
    strcpy(req.symbol,kK(y)[5]->s); 
    strcpy(req.securityTypeStr,kK(y)[6]->s); 
    strcpy(req.positionTypeStr,kK(y)[7]->s); 
    strcpy(req.positionStr,kK(y)[8]->s); 
    req.count=kK(y)[9]->i;

    R ki(pTradeApi->ReqStockPosition(req,xi));
  } 

  K2(reqQueryAsset){
    if(!run) R ki(-1);
    
    AtoSDKQueryAsset req;
    strcpy(req.positionStr,kK(y)[0]->s); 
    req.count=kK(y)[1]->i;
    req.assetLevel=kK(y)[2]->i;
    strcpy(req.productIdStr,kK(y)[3]->s); 
    strcpy(req.unitIdStr,kK(y)[4]->s); 

    R ki(pTradeApi->ReqQueryAsset(req,xi));
  } 

  K2(subscribeReport){
    if(!run) R ki(-1);
    
    X2Topic req;
    req.accountId=kK(y)[0]->i;
    req.unitId=kK(y)[1]->j;
    strcpy(req.topicName,kK(y)[2]->s); 

    R ki(pTradeApi->SubscribeReport(req,xi));
  } 

  K2(unSubscribeReport){
    if(!run) R ki(-1);
    
    X2Topic req;
    req.accountId=kK(y)[0]->i;
    req.unitId=kK(y)[1]->j;
    strcpy(req.topicName,kK(y)[2]->s); 

    R ki(pTradeApi->UnSubscribeReport(req,xi));
  } 

  K2(reqQueryOrderActual){
    if(!run) R ki(-1);
    
    AtoSDKQueryOrder req;
    strcpy(req.positionStr,kK(y)[0]->s); 
    req.count=kK(y)[1]->i;
    strcpy(req.productIdStr,kK(y)[2]->s); 
    strcpy(req.unitIdStr,kK(y)[3]->s); 
    strcpy(req.accountIdStr,kK(y)[4]->s); 
    strcpy(req.marketTypeStr,kK(y)[5]->s); 
    strcpy(req.symbol,kK(y)[6]->s); 
    strcpy(req.orderStatusStr,kK(y)[7]->s); 
    strcpy(req.sideStr,kK(y)[8]->s); 
    strcpy(req.orderPropStr,kK(y)[9]->s); 
    strcpy(req.filterOperatorNoStr,kK(y)[10]->s); 
    req.sysOrderId=kK(y)[11]->j;

    R ki(pTradeApi->ReqQueryOrderActual(req,xi));
  } 

  K2(reqQueryDealActual){
    if(!run) R ki(-1);
    
    AtoSDKQueryDeal req;
    strcpy(req.positionStr,kK(y)[0]->s); 
    req.count=kK(y)[1]->i;
    strcpy(req.productIdStr,kK(y)[2]->s); 
    strcpy(req.unitIdStr,kK(y)[3]->s); 
    strcpy(req.accountIdStr,kK(y)[4]->s); 
    strcpy(req.marketTypeStr,kK(y)[5]->s); 
    strcpy(req.symbol,kK(y)[6]->s); 
    strcpy(req.sideStr,kK(y)[7]->s); 
    strcpy(req.filterOperatorNoStr,kK(y)[8]->s); 
    req.sysOrderId=kK(y)[9]->j;

    R ki(pTradeApi->ReqQueryDealActual(req,xi));
  } 

  K2(reqCreateOrderActual){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKOrderCreate req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       strcpy(req[i].basketId,kK(z)[0]->s); 
       strcpy(req[i].externalId,kK(z)[1]->s); 
       req[i].sysQuoteId=kK(z)[2]->j;
       req[i].minEntustRatio=kK(z)[3]->i;
       req[i].productId=kK(z)[4]->i;
       req[i].unitId=kK(z)[5]->j;
       req[i].accountId=kK(z)[6]->i;
       strcpy(req[i].stkAcctCode,kK(z)[7]->s); 
       req[i].marketType=kK(z)[8]->i;
       strcpy(req[i].symbol,kK(z)[9]->s); 
       req[i].side=kK(z)[10]->j;
       req[i].orderQty=kK(z)[11]->j;
       req[i].orderPx=kK(z)[12]->f;
       req[i].pxType=kK(z)[13]->i;
       ); 
    R ki(pTradeApi->ReqCreateOrderActual(req,n,xi));
  } 

  K2(reqCancelOrderActual){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKOrderCancel req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       req[i].sysOrderId=kK(z)[0]->j;
       strcpy(req[i].operInfo,kK(z)[1]->s); 
       ); 
    R ki(pTradeApi->ReqCancelOrderActual(req,n,xi));
  } 

  K2(reqQueryInstruction){
    if(!run) R ki(-1);
    
    AtoSDKQueryAlgo req;
    strcpy(req.positionStr,kK(y)[0]->s); 
    req.count=kK(y)[1]->i;
    strcpy(req.productIdStr,kK(y)[2]->s); 
    strcpy(req.unitIdStr,kK(y)[3]->s); 
    strcpy(req.accountIdStr,kK(y)[4]->s); 
    strcpy(req.marketTypeStr,kK(y)[5]->s); 
    strcpy(req.symbol,kK(y)[6]->s); 
    strcpy(req.algoStatusStr,kK(y)[7]->s); 
    strcpy(req.sideStr,kK(y)[8]->s); 
    strcpy(req.algoPropStr,kK(y)[9]->s); 
    strcpy(req.filterOperatorNoStr,kK(y)[10]->s); 
    req.sysQuoteId=kK(y)[11]->j;

    R ki(pTradeApi->ReqQueryInstruction(req,xi));
  } 

  K2(reqInstructionCreate){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKAlgoCreate req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       req[i].algoTypeId=kK(z)[0]->i;
       req[i].productId=kK(z)[1]->i;
       req[i].unitId=kK(z)[2]->j;
       req[i].accountId=kK(z)[3]->i;
       strcpy(req[i].basketId,kK(z)[4]->s);
       strcpy(req[i].externalId,kK(z)[5]->s);
       strcpy(req[i].symbol,kK(z)[6]->s);
       req[i].marketType=kK(z)[7]->i;
       strcpy(req[i].stkAcctCode,kK(z)[8]->s);
       req[i].effectiveTime=kK(z)[9]->j;
       req[i].expireTime=kK(z)[10]->j;
       strcpy(req[i].algoParam,kK(z)[11]->s);
       ); 
    R ki(pTradeApi->ReqInstructionCreate(req,n,xi));
  } 

  K2(reqInstructionReplace){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKAlgoReplace req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       req[i].sysQuoteId=kK(z)[0]->j;
       req[i].effectiveTime=kK(z)[1]->j;
       req[i].expireTime=kK(z)[2]->j;
       strcpy(req[i].algoParam,kK(z)[3]->s);
       ); 
    R ki(pTradeApi->ReqInstructionReplace(req,n,xi));
  } 

  K2(reqInstructionControl){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKAlgoOperation req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       req[i].sysQuoteId=kK(z)[0]->j;
       req[i].operationType=kK(z)[1]->i;
       ); 
    R ki(pTradeApi->ReqInstructionControl(req,n,xi));
  } 

  K2(reqQueryRiskWarn){
    if(!run) R ki(-1);
    int n=MIN(y->n,ORD_POOL_SIZE);
    K z;
    AtoSDKWarnInfo req[ORD_POOL_SIZE];
    DO(n,z=kK(y)[i];
       req[i].riskBusinId=kK(z)[0]->j;
       ); 
    R ki(pTradeApi->ReqQueryRiskWarn(req,n,xi));
  } 


}
