#include "kcomm.h"
#include <queue>
#include "JGDFDAPI.h"

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

#define JGCAll(f,r) if(DFDAPI_ERR_SUCCESS!=f) R ki(r); 

Z VHANDLE g_handle = nullptr;

ZV OnRecvData(VHANDLE h, DFDAPI_CALLBACK_MSG* m){
  if (NULL==m||NULL==m->pAppHead){R;}
  int n=m->pAppHead->nItemCount,w=m->pAppHead->nItemSize;
  if (0>=n||0>=w){R;}
  
  switch (m->nDataType){
  case MSG_DATA_INDEX:{
    DFDAPI_INDEX_DATA *p=(DFDAPI_INDEX_DATA *)m->pData;
    DO(n,mpub(knk(2,ks("Index"),knk(14,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTradingDay),ki(p->nTime),ki(p->nStatus),kj(p->nOpenIndex),kj(p->nHighIndex),kj(p->nLowIndex),kj(p->nLastIndex),kj(p->iTotalVolume),kj(p->iTurnover),kj(p->nPreCloseIndex))));p=(DFDAPI_INDEX_DATA *)(S)p+w);
  }break;
  case MSG_DATA_MARKET:{
    DFDAPI_MARKET_DATA *p=(DFDAPI_MARKET_DATA *)m->pData;
    for(int _j=0;_j<n;_j++){
      K pa=ktn(KJ,10),qa=ktn(KJ,10),pb=ktn(KJ,10),qb=ktn(KJ,10);
      DO(10,kJ(pa)[i]=p->nAskPrice[i];kJ(qa)[i]=p->nAskVol[i];kJ(pb)[i]=p->nBidPrice[i];kJ(qb)[i]=p->nBidVol[i]);
      mpub(knk(2,ks("MDepth"),knk(31,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTradingDay),ki(p->nTime),ki(p->nStatus),kj(p->nPreClose),kj(p->nOpen),kj(p->nHigh),kj(p->nLow),kj(p->nMatch),pa,qa,pb,qb,ki(p->nNumTrades),kj(p->iVolume),kj(p->iTurnover),kj(p->nTotalBidVol),kj(p->nTotalAskVol),kj(p->nWeightedAvgBidPrice),kj(p->nWeightedAvgAskPrice),ki(p->nIOPV),ki(p->nYieldToMaturity),kj(p->nHighLimited),kj(p->nLowLimited),kp(p->chPrefix),ki(p->nSyl1),ki(p->nSyl2),ki(p->nSD2))));
      p=(DFDAPI_MARKET_DATA *)(S)p+w;
    }
  }break;
  case MSG_DATA_FUTURE:{
    DFDAPI_FUTURE_DATA *p=(DFDAPI_FUTURE_DATA *)m->pData;
    for(int _j=0;_j<n;_j++){
      K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->nAskPrice[i];kJ(qa)[i]=p->nAskVol[i];kJ(pb)[i]=p->nBidPrice[i];kJ(qb)[i]=p->nBidVol[i]);
      mpub(knk(2,ks("MDepthFut"),knk(30,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTradingDay),ki(p->nTime),ki(p->nStatus),kj(p->iPreOpenInterest),kj(p->nPreClose),ki(p->nPreSettlePrice),kj(p->nOpen),kj(p->nHigh),kj(p->nLow),kj(p->nMatch),kj(p->iVolume),kj(p->iTurnover),kj(p->iOpenInterest),kj(p->nClose),ki(p->nSettlePrice),kj(p->nHighLimited),kj(p->nLowLimited),ki(p->nPreDelta),ki(p->nCurrDelta),pa,qa,pb,qb,kj(p->nAuctionPrice),ki(p->nAuctionQty),ki(p->nAvgPrice))));
      p=(DFDAPI_FUTURE_DATA *)(S)p+w;
    }    
  }break;
  case MSG_DATA_HKEX:{
    DFDAPI_HKEX_DATA *p=(DFDAPI_HKEX_DATA *)m->pData;
    for(int _j=0;_j<n;_j++){
      K pa=ktn(KI,10),qa=ktn(KJ,10),na=ktn(KJ,10),pb=ktn(KI,10),qb=ktn(KJ,10),nb=ktn(KJ,10);
      DO(10,kI(pa)[i]=p->arrnAskPrice[i];kJ(qa)[i]=p->arriAskVolume[i];kJ(na)[i]=p->arriTotalAskOty[i];kI(pb)[i]=p->arrnBidPrice[i];kJ(qb)[i]=p->arriBidVolume[i];kJ(nb)[i]=p->arriTotalBuyOty[i];)
      mpub(knk(2,ks("MDepthHK"),knk(22,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nDate),ki(p->nTime),ki(p->nStatus),ki(p->unPreClosePx),ki(p->unNominalPrice),ki(p->unOpenPrice),ki(p->unHighPrice),ki(p->unLowPrice),ki(p->unTradePrice),kj(p->llTotalVolume),kf(p->dTotalAmount),pa,qa,na,pb,qb,nb,ki(p->unTradeVolume),ki(p->unSpread))));
      p=(DFDAPI_HKEX_DATA *)(S)p+w;
    }    
  }break;
  case MSG_DATA_TRANSACTION:{
    DFDAPI_TRANSACTION *p=(DFDAPI_TRANSACTION *)m->pData;
    DO(n,mpub(knk(2,ks("Transaction"),knk(15,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTime),ki(p->nChannelNo),kj(p->iTradeIndex),kj(p->iAskOrder),kj(p->iBidOrder),ki(p->unPrice),kj(p->iVolume),kj(p->iTurnover),ki(p->nBSFlag),kc(p->chOrderKind),kc(p->chFunctionCode))));p=(DFDAPI_TRANSACTION *)(S)p+w);    
  }break;
  case MSG_DATA_ORDERQUEUE:{
    DFDAPI_AB50_DATA *p=(DFDAPI_AB50_DATA *)m->pData;
    DO(n,K qq=ktn(KI,200);for(int j=0;j<200;j++)kI(qq)[j]=p->nABVolume[j];mpub(knk(2,ks("OQueue"),knk(10,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTime),ki(p->nSide),kj(p->nPrice),ki(p->nOrders),ki(p->nABItems),qq)));p=(DFDAPI_AB50_DATA *)(S)p+w);
  }break;
  case MSG_DATA_ORDER:{
    DFDAPI_ORDER_DATA *p=(DFDAPI_ORDER_DATA *)m->pData;
    DO(n,mpub(knk(2,ks("OrderQ"),knk(11,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nActionDay),ki(p->nTime),ki(p->nChannelNo),kj(p->iApplSeqNum),ki(p->unPrice),ki(p->unVolume),kc(p->chOrderKind),kc(p->chFunctionCode))));p=(DFDAPI_ORDER_DATA *)(S)p+w);        
  }break;
  case MSG_DATA_BBQTRANSACTION:{
    
  }break;
  case MSG_DATA_BBQBID:{
    
  }break;
  case MSG_DATA_NON_MD:{
    
  }break;
  case MSG_DATA_OTC_OPTION:{
    
  }break;
  case MSG_DATA_BROKERQUEUE:{
    
  }break;
  case MSG_SH_ETF_LIST:{
    
  }break;
  case MSG_SZ_ETF_LIST:{
    
  }break;
  case MSG_UPDATE_ETFLIST:{
    
  }break;
  case MSG_HKEX_BASICINFO:{
    DFDAPI_BASICINFO_HKEX *p=(DFDAPI_BASICINFO_HKEX *)m->pData;
    DO(n,mpub(knk(2,ks("HKInfo"),knk(22,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nDate),kp(p->szISIN),kp(p->szSymbol),kp(p->szSymbolEn),kp(p->szSecurityDesc),kp(p->szUnderlyingSecurityID),kp(p->szMarketID),kp(p->szSecurityType),kp(p->szCurrency),ki(p->nAmountTimes),kf(p->dPerValue),kp(p->szPerValueCurrency),kf(p->dInterest),ki(p->nIssueDate),ki(p->unRoundLot),ki(p->unPreClosePx),kp(p->szText),kp(p->SecurityStatusFlag),kp(p->szDataSource))));p=(DFDAPI_BASICINFO_HKEX *)(S)p+w);        
  }break;
  case MSG_DATA_OPTION:{
    DFDAPI_OPTION_DATA *p=(DFDAPI_OPTION_DATA *)m->pData;
    for(int _j=0;_j<n;_j++){
      K pa=ktn(KI,5),qa=ktn(KJ,5),pb=ktn(KI,5),qb=ktn(KJ,5);
      DO(5,kI(pa)[i]=p->arrnAskPrice[i];kJ(qa)[i]=p->arriAskVolume[i];kI(pb)[i]=p->arrnBidPrice[i];kJ(qb)[i]=p->arriBidVolume[i]);
      mpub(knk(2,ks("MDepthOpt"),knk(26,ki(*(I*)h),kp(p->szWindCode),kp(p->szCode),ki(p->nDate),ki(p->nTime),kj(p->iTotalLongPosition),kj(p->iTradeVolume),kf(p->dTotalValueTraded),ki(p->nPreSettlePrice),ki(p->nOpenPrice),ki(p->nAuctionPrice),kj(p->iAuctionQty),ki(p->nHighPrice),ki(p->nLowPrice),ki(p->nTradePrice),pb,qb,pa,qa,ki(p->nSettlePrice),kp(p->szTradingPhaseCode),ki(p->nRFValue),kj(p->iNumTrades),ki(p->nSecurityClosePx),ki(p->nHighLimitedPrice),ki(p->nLowLimitedPrice))));
      p=(DFDAPI_OPTION_DATA *)(S)p+w;
    }
  }break;
  case MSG_OPTION_BASICINFO:{
    DFDAPI_BASICINFO_OPTION *p=(DFDAPI_BASICINFO_OPTION *)m->pData;
    DO(n,mpub(knk(2,ks("OptInfo"),knk(36,ki(*(I*)h),ki(p->nDate),kp(p->szWindCode),kp(p->szCode),kp(p->szContractID),kp(p->szContractSymbol),kp(p->szUnderlyingSecurityID),kp(p->szUnderlyingSymbol),kp(p->szUnderlyingType),kc(p->chOptionType),kc(p->chCallOrPut),kj(p->iContractMultiplierUnit),ki(p->nExercisePrice),ki(p->nStartDate),ki(p->nEndDate),ki(p->nExerciseDate),ki(p->nDeliveryDate),ki(p->nExpireDate),kc(p->chUpdateVersion),kj(p->iTotalLongPosition),ki(p->nSecurityClosePx),ki(p->nSettlePrice),ki(p->nUnderlyingClosePx),kc(p->chPriceLimitType),ki(p->nUpLimitDailyPrice),ki(p->nDownLimitDailyPrice),kf(p->dMarginUnit),kf(p->dMarginRatioParam1),kf(p->dMarginRatioParam2),kj(p->iLmtOrdMinFloor),kj(p->iLmtOrdMaxFloor),kj(p->iMktOrdMinFloor),kj(p->iMktOrdMaxFloor),kp(p->szSecurityStatusFlag),ki(p->nTickSize))));p=(DFDAPI_BASICINFO_OPTION *)(S)p+w);            
  }break;
  default:break;  
  }
}

ZV OnRecvSys(VHANDLE h, DFDAPI_CALLBACK_MSG* m){
  if (NULL==m||NULL==m->pAppHead){R;}
  switch (m->nDataType){
  case MSG_SYS_DISCONNECT_NETWORK:mpub(knk(2,ks("DisconnectQ"),knk(0)));break;
  case MSG_SYS_CONNECT_RESULT:{
    DFDAPI_CONNECT_RESULT* p = (DFDAPI_CONNECT_RESULT*)m->pData;
    if(NULL!=p)mpub(knk(2,ks("ConnectQ"),knk(6,kp(p->szIp),kp(p->szPort),kp(p->szUser),kp(p->szPwd),ki(p->nConnResult),ki(p->nConnectionID))));
  }break;
  case MSG_SYS_LOGIN_RESULT:{
    DFDAPI_LOGIN_RESULT* p = (DFDAPI_LOGIN_RESULT*)m->pData;
    int n=p->nMarkets;
    K L=knk(0),L1=ktn(KI,n);
    DO(n,jk(&L,kp(p->szMarket[i]));kI(L1)[i]=p->nDynDate[i]);
    if(NULL!=p)mpub(knk(2,ks("LoginQ"),knk(5,ki(p->nLoginResult),kp(p->szInfo),ki(n),L,L1)));    
  }break;
  case MSG_SYS_CODETABLE_RESULT:{
    DFDAPI_CODE_RESULT* p = (DFDAPI_CODE_RESULT*)m->pData;
    int n=p->nMarkets;
    K L=knk(0),L1=ktn(KI,n),L2=ktn(KI,n);
    DO(n,jk(&L,kp(p->szMarket[i]));kI(L1)[i]=p->nCodeCount[i];kI(L2)[i]=p->nCodeDate[i]);
    if(NULL!=p)mpub(knk(2,ks("CodeQ"),knk(5,kp(p->szInfo),ki(n),L,L1,L2)));    
  }break;
  case MSG_SYS_HEART_BEAT:mpub(knk(2,ks("HeartbeatQ"),knk(0)));break;
  case MSG_SYS_MARKET_EVENT:{
    
  }break;
  case MSG_SYS_SINGLE_CODETABLE_RESULT:{
    
  }break;   
  case MSG_SYS_QUOTEUNIT_CHANGE:{
    
  }break;
  default:break;  
  }
}


extern "C"{
  K2(initjgq){ //(ctrlparam(tmout;hbint;pushmode;mkts;subs;flags;timeoffset;connid),(ip;port;user;pwd))
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];

    DFDAPI_OPEN_CONNECT_SET *ocs=new DFDAPI_OPEN_CONNECT_SET;
    DFDAPI_ERR_CODE *ec=new DFDAPI_ERR_CODE;
      
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

    JGCAll(DFDAPI_Init(),-20001);
    JGCAll(DFDAPI_SetEnv(DFDAPI_ENVIRON_OPEN_TIME_OUT,kK(x)[0]->i),-20000);
    JGCAll(DFDAPI_SetEnv(DFDAPI_ENVIRON_HEART_BEAT_INTERVAL,kK(x)[1]->i),-20001);
    JGCAll(DFDAPI_SetEnv(DFDAPI_ENVIRON_PUSHMODE,kK(x)[2]->i),-20002);

    n=kK(y)[0]->n;
    memset(ocs,0,sizeof(DFDAPI_OPEN_CONNECT_SET));
    memset(ec,0,sizeof(DFDAPI_ERR_CODE));
    ocs->unServerNum=n;
    ocs->data_fun=OnRecvData;
    ocs->notice_fun=OnRecvSys;
    ocs->szMarkets=kK(x)[3]->s;
    ocs->szSubScriptions=kK(x)[4]->s;
    ocs->szTypeFlags=kK(x)[5]->s;
    ocs->nTime=kK(x)[6]->i;
    ocs->nConnectionID=kK(x)[7]->i;

    DO(n,strcpy(ocs->ServerInfo[i].szIp,kS(kK(y)[0])[i]))
    DO(n,ocs->ServerInfo[i].nPort=kH(kK(y)[1])[i])
    DO(n,strcpy(ocs->ServerInfo[i].szUser,kS(kK(y)[2])[i]))
    DO(n,strcpy(ocs->ServerInfo[i].szPwd,kS(kK(y)[3])[i]))
    DO(n,ocs->ServerInfo[i].bDoMain=false)
    
    if(NULL==(g_handle=DFDAPI_OpenConnect(ocs,ec))){
      R ki(-20003);
    }
      

    R ki(run);
  }

  K1(freejgq){
    if(!run) R ki(-1);
    
    DFDAPI_Exit();

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(jgqrun){
    R ki(run);
  }   
}
