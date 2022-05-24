#include "kcomm.h"
#include <queue>

#include "TDFAPI.h"
#include "NonMDMsgDecoder.h"
#include "TDFAPIInner.h"

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
  k(0,"ontdf",L,(K)0);
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
  //k(-c,"ontdf",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};


ZV RecvData(THANDLE hTdf, TDF_MSG* pMsgHead){
  K L=knk(0);
  
  if (!pMsgHead->pData)R;

  unsigned int n = pMsgHead->pAppHead->nItemCount;
  unsigned int s = pMsgHead->pAppHead->nItemSize;
  
  if ((!n)||(!s))R ;

  switch(pMsgHead->nDataType){
  case MSG_DATA_MARKET:
    {
      TDF_MARKET_DATA *p1=(TDF_MARKET_DATA*)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_MARKET_DATA &p=p1[i];
	K pa=ktn(KJ,10),qa=ktn(KJ,10),pb=ktn(KJ,10),qb=ktn(KJ,10);
	for(int j=0;j<10;j++){kJ(pa)[j]=p.nAskPrice[j];kJ(qa)[j]=p.nAskVol[j];kJ(pb)[j]=p.nBidPrice[j];kJ(qb)[j]=p.nBidVol[j];}
	jk(&L,knk(35,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTradingDay),ki(p.nTime),ki(p.nStatus),kj(p.nPreClose),kj(p.nOpen),kj(p.nHigh),kj(p.nLow),kj(p.nMatch),pa,qa,pb,qb,ki(p.nNumTrades),kj(p.iVolume),kj(p.iTurnover),kj(p.nTotalBidVol),kj(p.nTotalAskVol),kj(p.nWeightedAvgBidPrice),kj(p.nWeightedAvgAskPrice),ki(p.nIOPV),ki(p.nYieldToMaturity),kj(p.nHighLimited),kj(p.nLowLimited),kpn((S)p.chPrefix,4),ki(p.nSyl1),ki(p.nSyl2),ki(p.nSD2),ki(p.nTradeFlag),kj(p.iAfterPrice),ki(p.nAfterVolume),kj(p.iAfterTurnover),ki(p.nAfterMatchItems)));
      }
      mpub(knk(2,ks("DATA_MARKET"),L));	 
    }
    break;
   case MSG_DATA_FUTURE:
     {
       TDF_FUTURE_DATA*p1 =(TDF_FUTURE_DATA*)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_FUTURE_DATA &p=p1[i];
	K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
	for(int j=0;j<5;j++){kJ(pa)[j]=p.nAskPrice[j];kJ(qa)[j]=p.nAskVol[j];kJ(pb)[j]=p.nBidPrice[j];kJ(qb)[j]=p.nBidVol[j];}
	jk(&L,knk(30,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTradingDay),ki(p.nTime),ki(p.nStatus),kj(p.iPreOpenInterest),kj(p.nPreClose),kj(p.nPreSettlePrice),kj(p.nOpen),kj(p.nHigh),kj(p.nLow),kj(p.nMatch),kj(p.iVolume),kj(p.iTurnover),kj(p.iOpenInterest),kj(p.nClose),kj(p.nSettlePrice),kj(p.nHighLimited),kj(p.nLowLimited),ki(p.nPreDelta),ki(p.nCurrDelta),pa,qa,pb,qb,kj(p.nAuctionPrice),ki(p.nAuctionQty),kj(p.nAvgPrice),kp((S)p.chOriginalCode)));
      }
      mpub(knk(2,ks("DATA_FUTURE"),L));	        
     }
     break;

   case MSG_DATA_INDEX:
     {
       TDF_INDEX_DATA* p1=(TDF_INDEX_DATA*)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_INDEX_DATA &p=p1[i];
	jk(&L,knk(13,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTradingDay),ki(p.nTime),ki(p.nStatus),kj(p.nOpenIndex),kj(p.nHighIndex),kj(p.nLowIndex),kj(p.nLastIndex),kj(p.iTotalVolume),kj(p.iTurnover),kj(p.nPreCloseIndex)));
      }
      mpub(knk(2,ks("DATA_INDEX"),L));	               
     }
     break;
   case MSG_DATA_TRANSACTION:
     {
       TDF_TRANSACTION *p1=(TDF_TRANSACTION *)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_TRANSACTION &p=p1[i];
	jk(&L,knk(15,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTime),ki(p.nIndex),kj(p.nPrice),ki(p.nVolume),kj(p.nTurnover),ki(p.nBSFlag),kc(p.chOrderKind),kc(p.chFunctionCode),ki(p.nAskOrder),ki(p.nBidOrder),ki(p.nChannel),kj(p.nBizIndex)));
      }
      mpub(knk(2,ks("DATA_TRANSACTION"),L));	                      
     }
     break;
   case MSG_DATA_ORDERQUEUE:
     {
       TDF_ORDER_QUEUE* p1=(TDF_ORDER_QUEUE*)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_ORDER_QUEUE &p=p1[i];
	I n1=p.nABItems;
	K ql=ktn(KI,n1);
	for(int j=0;j<n1;j++)kJ(ql)[j]=p.nABVolume[j];
	jk(&L,knk(9,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTime),ki(p.nSide),kj(p.nPrice),ki(p.nOrders),ki(n1),ql));
      }
      mpub(knk(2,ks("DATA_ORDERQUEUE"),L));	        
     }
     break;
  case MSG_DATA_ORDER:
    {
      TDF_ORDER* p1=(TDF_ORDER*)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TDF_ORDER &p=p1[i];
	jk(&L,knk(12,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nTime),ki(p.nOrder),kj(p.nPrice),ki(p.nVolume),kc(p.chOrderKind),kc(p.chFunctionCode),ki(p.nChannel),kj(p.nOrderOriNo),kj(p.nBizIndex)));
      }
      mpub(knk(2,ks("DATA_ORDER"),L));	                      
    }
    break;
  case MSG_DATA_BROKERQUEUE:
    {
      TD_BrokerQueue *p1=(TD_BrokerQueue *)pMsgHead->pData;
      for(int i=0;i<n;i++){
	const TD_BrokerQueue &p=p1[i];
	I na=p.nAskBrokers,nb=p.nBidBrokers;
	K qa=ktn(KH,na),qb=ktn(KH,nb);
	for(int j=0;j<na;j++)kH(qa)[j]=p.sAskBroker[j];
	for(int j=0;j<nb;j++)kH(qb)[j]=p.sBidBroker[j];
	jk(&L,knk(9,kp((S)p.szWindCode),kp((S)p.szCode),ki(p.nActionDay),ki(p.nAskTime),ki(p.nBidTime),ki(na),ki(nb),qa,qb));
      }
      mpub(knk(2,ks("DATA_BROKERQUEUE"),L));	        
    }
    break;
  default:
    break;
  }
}

ZV RecvSys(THANDLE hTdf, TDF_MSG* pSysMsg){
  if (!pSysMsg ||! hTdf)return;
  
  switch (pSysMsg->nDataType){
  case MSG_SYS_DISCONNECT_NETWORK:
    {
      mpub(knk(2,ks("SYS_DISCONNECT_NETWORK"),knk(0)));
    }
    break;
  case MSG_SYS_CONNECT_RESULT:
    {
      TDF_CONNECT_RESULT* p = (TDF_CONNECT_RESULT*)pSysMsg->pData;
      if(p)mpub(knk(2,ks("SYS_CONNECT_RESULT"),knk(6,ki(p->nConnResult),ki(p->nConnectionID),kp((S)p->szIp),kp((S)p->szPort),kp((S)p->szUser),kp((S)p->szPwd))));
    }
    break;
  case MSG_SYS_LOGIN_RESULT:
    {
      TDF_LOGIN_RESULT* p = (TDF_LOGIN_RESULT*)pSysMsg->pData;
      if(p){
	I n=p->nMarkets;
	K L1=knk(0),L2=ktn(KI,n);
	DO(n,kI(L2)[i]=p->nDynDate[i];jk(&L1,kp((S)p->szMarket[i])););
	mpub(knk(2,ks("SYS_LOGIN_RESULT"),knk(5,ki(p->nLoginResult),kp((S)p->szInfo),ki(n),L1,L2)));
      }
    }
    break;
  case MSG_SYS_CODETABLE_RESULT:
    {
      TDF_CODE_RESULT* p = (TDF_CODE_RESULT*)pSysMsg->pData;
      if(p){
	I n=p->nMarkets;
	K L1=knk(0),L2=ktn(KI,n),L3=ktn(KI,n);
	DO(n,kI(L2)[i]=p->nCodeCount[i];kI(L3)[i]=p->nCodeDate[i];jk(&L1,kp((S)p->szMarket[i])));
	mpub(knk(2,ks("SYS_CODETABLE_RESULT"),knk(5,kp((S)p->szInfo),ki(n),L1,L2,L3)));
      }
    }
    break;
  case MSG_SYS_SINGLE_CODETABLE_RESULT:
    {
      TDF_SINGLE_CODE_RESULT* p = (TDF_SINGLE_CODE_RESULT*)pSysMsg->pData;
      if(p){
	I n=1;
	K L1=knk(0),L2=ktn(KI,n),L3=ktn(KI,n);
	DO(n,kI(L2)[i]=p->nCodeCount;kI(L3)[i]=p->nCodeDate;jk(&L1,kp((S)p->szMarket)));
	mpub(knk(2,ks("SYS_SINGLE_CODETABLE_RESULT"),knk(5,kp(""),ki(n),L1,L2,L3)));
      }
    }
    break;
  case MSG_SYS_QUOTATIONDATE_CHANGE:
    {
      TDF_QUOTATIONDATE_CHANGE* p = (TDF_QUOTATIONDATE_CHANGE*)pSysMsg->pData;
      if(p)mpub(knk(2,ks("SYS_QUOTATIONDATE_CHANGE"),knk(3,kp((S)p->szMarket),ki(p->nOldDate),ki(p->nNewDate))));
    }
    break;
  case MSG_SYS_MARKET_CLOSE:
    {
      TDF_MARKET_CLOSE* p = (TDF_MARKET_CLOSE*)pSysMsg->pData;
      if(p)mpub(knk(2,ks("SYS_MARKET_CLOSE"),knk(3,kp((S)p->szMarket),ki(p->nTime),kp((S)p->chInfo))));
    }
    break;
    case MSG_SYS_HEART_BEAT:
      {
	mpub(knk(2,ks("SYS_HEART_BEAT"),knk(0)));
      }
      break;
    default:
        //assert(0);
        break;
    }
}

Z THANDLE hTDF = NULL;
 
extern "C"{
  K2(inittdf){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
    TDF_OPEN_SETTING_EXT settings = {0};
    TDF_ERR nErr = TDF_ERR_SUCCESS;
      
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

    TDF_SetEnv(TDF_ENVIRON_DISTRIBUTION, 0);
    TDF_SetLogPath(kK(y)[5]->s);
    
    memset(&settings, 0, sizeof(settings));
    settings.nServerNum = kK(x)[0]->i; //�������ã� ��Ч���������ø�������ǰ�汾Ӧ<=2)
    strncpy(settings.siServer[0].szIp, kK(x)[1]->s, sizeof(settings.siServer[0].szIp)-1);
    sprintf(settings.siServer[0].szPort, "%d",kK(x)[2]->i);
    strncpy(settings.siServer[0].szUser, kK(x)[3]->s, sizeof(settings.siServer[0].szUser)-1);
    strncpy(settings.siServer[0].szPwd,  kK(x)[4]->s, sizeof(settings.siServer[0].szPwd)-1);
    if(1<settings.nServerNum){
      strncpy(settings.siServer[1].szIp, kK(x)[5]->s, sizeof(settings.siServer[1].szIp)-1);
      sprintf(settings.siServer[1].szPort, "%d",kK(x)[6]->i);
      strncpy(settings.siServer[1].szUser, kK(x)[7]->s, sizeof(settings.siServer[1].szUser)-1);
      strncpy(settings.siServer[1].szPwd,  kK(x)[8]->s, sizeof(settings.siServer[1].szPwd)-1);      
    }
    
    settings.pfnMsgHandler = RecvData; //����������Ϣ�ص�����
    settings.pfnSysMsgNotify = RecvSys;//����ϵͳ��Ϣ�ص�����
	      
    settings.szMarkets =kK(y)[0]->s;    //��Ҫ���ĵ��г��б�
    settings.szSubScriptions = kK(y)[1]->s; //"600030.SH"; //600030.SH;104174.SH;103493.SH";    //��Ҫ���ĵĹ�Ʊ,Ϊ������ȫ�г�
    settings.nTime = kK(y)[2]->i;//�����ʱ�䣬��ʽHHMMSS��Ϊ0������ʵʱ���飬Ϊ0xffffffff��ͷ����
    settings.nTypeFlags = kK(y)[3]->g; //�����Ʒ��
    settings.nCodeTypeFlags = kK(y)[4]->g;

    if(NULL==(hTDF = TDF_OpenExt(&settings, &nErr))) R ki(nErr);    
    
    R ki(run);
  }

  K1(freetdf){
    if(!run) R ki(-1);

    if(NULL!=hTDF)TDF_Close(hTDF);

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(tdfrun){
    R ki(run);
  } 

  K1(tdfver){
    R kp((S)TDF_Version()); 
  } 

  K1(sub){ //
    if(!run) R ki(-1);
    if(NULL==hTDF)R ki(-2);

    R ki(TDF_SetSubscription(hTDF,(S)kK(x)[0]->s,(SUBSCRIPTION_STYLE)kK(x)[1]->j));
  }

  K1(codetable){
    K L=knk(0);
    TDF_CODE* p1;unsigned int n1;
    TDF_GetCodeTable(hTDF,xs,&p1, &n1);
    for(int j=0;j<n1;j++){
      TDF_CODE& c = p1[j];
      jk(&L,knk(9,kp((S)c.szWindCode),kp((S)c.szMarket),kp((S)c.szCode),kp((S)c.szENName),kp((S)c.szCNName),ki(c.nType),kp((S)c.szWindType),ki(c.nRecord),ki(c.nLotSize)));
      //O("WindCode=(%s),Market=(%s),Code=(%s),ENName=(%s),CNName=(%s),Type=(%d),WindType=(%s),nRecord=(%d),nLotSize=(%d)\n",c.szWindCode,c.szMarket,c.szCode,c.szENName,c.szCNName,c.nType,c.szWindType,c.nRecord,c.nLotSize);
    }
    TDF_FreeArr(p1);
    R L;
  }
}