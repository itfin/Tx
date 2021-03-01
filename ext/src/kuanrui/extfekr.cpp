#include "kcomm.h"
#include <queue>

#include    <oes_api/oes_api.h>
#include    <oes_api/oes_async_api.h>
#include    <oes_api/parser/oes_protocol_parser.h>
#include    <oes_api/parser/json_parser/oes_json_parser.h>
#include    <sutil/logger/spk_log.h>

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
  k(0,"onkr",L,(K)0);
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

Z OesAsyncApiContextT     *pAsyncContext = (OesAsyncApiContextT *) NULL;
Z OesAsyncApiChannelT     *pAsyncChannel = (OesAsyncApiChannelT *) NULL;
Z OesApiClientEnvT        cliEnv = {NULLOBJ_OESAPI_CLIENT_ENV};


Z int32 onrpt(OesApiSessionInfoT *pSessionInfo,SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesRspMsgBodyT      *pRspMsg = (OesRspMsgBodyT *) pMsgBody;
    OesRptMsgT          *p = &pRspMsg->rptMsg;

    SLOG_ASSERT(pSessionInfo && pMsgHead && pRspMsg);

    switch (pMsgHead->msgId) {
    case OESMSG_RPT_ORDER_INSERT:               /* OESί�������� (��ͨ����ؼ��) @see OesOrdCnfmT */
      mpub(knk(2,ks("ORDER_INSERT"),knk(9,ki(p->rptBody.ordInsertRsp.clSeqNo),kj(p->rptBody.ordInsertRsp.clOrdId),kc(p->rptBody.ordInsertRsp.ordStatus),kc(p->rptBody.ordInsertRsp.ordCnfmSts),ki(p->rptBody.ordInsertRsp.ordCnfmTime),kj(p->rptBody.ordInsertRsp.userInfo.i64),ki(p->rptBody.ordInsertRsp.cumQty),ki(p->rptBody.ordInsertRsp.canceledQty),ki(p->rptBody.ordInsertRsp.ordRejReason))));
      break;

    case OESMSG_RPT_BUSINESS_REJECT:            /* OESҵ��ܾ� (δͨ����ؼ���) @see OesOrdRejectT */
      mpub(knk(2,ks("BUSINESS_REJECT"),knk(3,ki(p->rptBody.ordRejectRsp.clSeqNo),ki(p->rptHead.ordRejReason),kj(p->rptBody.ordRejectRsp.userInfo.i64))));
      break;

    case OESMSG_RPT_ORDER_REPORT:               /* ������ί�лر� (����������ί�оܾ���ί��ȷ�Ϻͳ������֪ͨ) @see OesOrdCnfmT */
      mpub(knk(2,ks("ORDER_REPORT"),knk(9,ki(p->rptBody.ordCnfm.clSeqNo),kj(p->rptBody.ordCnfm.clOrdId),kc(p->rptBody.ordCnfm.ordStatus),kc(p->rptBody.ordCnfm.ordCnfmSts),ki(p->rptBody.ordCnfm.ordCnfmTime),kj(p->rptBody.ordCnfm.userInfo.i64),ki(p->rptBody.ordInsertRsp.cumQty),ki(p->rptBody.ordInsertRsp.canceledQty),ki(p->rptBody.ordInsertRsp.ordRejReason))));
      break;

    case OESMSG_RPT_TRADE_REPORT:               /* �������ɽ��ر� @see OesTrdCnfmT */
      mpub(knk(2,ks("TRADE_REPORT"),knk(4,ki(p->rptBody.trdCnfm.clSeqNo),kj(p->rptBody.trdCnfm.userInfo.i64),ki(p->rptBody.trdCnfm.cumQty),kj(p->rptBody.trdCnfm.cumAmt))));      
      break;

    case OESMSG_RPT_CASH_ASSET_VARIATION:       /* �ʽ�䶯��Ϣ @see OesCashAssetItemT */
      break;

    case OESMSG_RPT_STOCK_HOLDING_VARIATION:    /* �ֱֲ䶯��Ϣ (��Ʊ) @see OesStkHoldingItemT */
      break;

    case OESMSG_RPT_FUND_TRSF_REJECT:           /* �����ί����Ӧ-ҵ��ܾ� @see OesFundTrsfRejectT */
        break;

    case OESMSG_RPT_FUND_TRSF_REPORT:           /* �����ί��ִ�б��� @see OesFundTrsfReportT */
        break;

    case OESMSG_RPT_REPORT_SYNCHRONIZATION:     /* �ر�ͬ����Ӧ����Ϣ @see OesReportSynchronizationRspT */
        break;

    case OESMSG_RPT_MARKET_STATE:               /* �г�״̬��Ϣ @see OesMarketStateInfoT */
        break;

    case OESMSG_SESS_HEARTBEAT:                 /* ������Ϣ */
        break;

    case OESMSG_SESS_TEST_REQUEST:              /* ����������Ϣ */
        break;

    default:
        break;
    }

    return 0;
}


Z int32 onrsp(OesApiSessionInfoT *pSessionInfo,SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams) {
    OesRspMsgBodyT          *pRspMsg = (OesRspMsgBodyT *) pMsgBody;

    SLOG_ASSERT(pSessionInfo && pMsgHead && pMsgBody);

    switch (pMsgHead->msgId) {
    case OESMSG_SESS_HEARTBEAT:                 /* ������Ϣ */
        break;

    case OESMSG_SESS_TEST_REQUEST:              /* ����������Ϣ */
        break;

    case OESMSG_NONTRD_CHANGE_PASSWORD:         /* ��¼�����޸ĵ�Ӧ����Ϣ @see OesChangePasswordRspT */
        break;

    default:
        break;
    }

    return 0;
}

Z int32 onqry(OesApiSessionInfoT *pSessionInfo,SMsgHeadT *pMsgHead, void *pMsgBody, OesQryCursorT *pc,void *pCallbackParams) {
    OesOrdItemT *po =(OesOrdItemT*) pMsgBody;      
    OesStkHoldingItemT *ph=(OesStkHoldingItemT *)pMsgBody;
    
    switch (pMsgHead->msgId) {
    case OESMSG_QRYMSG_ORD:                 /* ί�в�ѯ */
      mpub((knk(2,ks("QRYMSG_ORD"),knk(11,ki(pc->seqNo),kb(pc->isEnd),ki(po->clSeqNo),kj(po->clOrdId),kc(po->ordStatus),kc(po->ordCnfmSts),ki(po->ordCnfmTime),kj(po->userInfo.i64),ki(po->cumQty),ki(po->canceledQty),ki(po->ordRejReason)))));
      break;
    case OESMSG_QRYMSG_STK_HLD:                 /* �ֲֲ�ѯ */
      mpub((knk(2,ks("QRYMSG_STK_HLD"),knk(12,ki(pc->seqNo),kb(pc->isEnd),kp(ph->invAcctId),kp(ph->securityId),kc(ph->mktId),kj(ph->originalHld),kj(ph->originalCostAmt),kj(ph->totalBuyHld),kj(ph->totalSellHld),kj(ph->sumHld),kj(ph->costPrice),ki(ph->sellAvlHld)))));
      break;
      
    default:
      break;
    }

    return 0;
}

extern "C"{
  K2(initkrt){
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

    if (! __OesApi_CheckApiVersion()) {
      SLOG_ERROR("API��ͷ�ļ��汾����ļ��汾��ƥ��, û���滻ͷ�ļ�����û�����±���? apiVersion[%s], libVersion[%s]",OES_APPL_VER_ID, OesApi_GetApiVersion());
      R ki(-4);
    } else {
      SLOG_INFO("API version: %s", OesApi_GetApiVersion());
    }
    OesApi_SetCustomizedDriverId(y->s);

    if (!OesApi_InitAll(&cliEnv, xs,OESAPI_CFG_DEFAULT_SECTION_LOGGER, OESAPI_CFG_DEFAULT_SECTION,(char *) NULL, (char *) NULL, "qryServer",0, (int32 *) NULL)){
      R ki(-44);
    }
      
    pAsyncContext = OesAsyncApi_CreateContext(xs);
    if (! pAsyncContext) {
        SLOG_ERROR("�����첽API������ʱ����ʧ��!");
        R ki(-5);
    }
    
    pAsyncChannel = OesAsyncApi_AddChannelFromFile(pAsyncContext, OESAPI_CHANNEL_TYPE_REPORT,"async_rpt_channel1",xs,OESAPI_CFG_DEFAULT_SECTION,OESAPI_CFG_DEFAULT_KEY_RPT_ADDR,onrpt, NULL,(F_OESAPI_ASYNC_ON_CONNECT_T) NULL, NULL,(F_OESAPI_ASYNC_ON_DISCONNECT_T) NULL, NULL);
    if (! pAsyncChannel) {SLOG_ERROR("�������ļ��м���ͨ������ʧ��! channelTag[%s]","async_rpt_channel1");goto ON_ERROR;}

    pAsyncChannel = OesAsyncApi_AddChannelFromFile(pAsyncContext, OESAPI_CHANNEL_TYPE_ORDER,"async_ord_channel1",xs,OESAPI_CFG_DEFAULT_SECTION,OESAPI_CFG_DEFAULT_KEY_ORD_ADDR,onrsp, NULL,(F_OESAPI_ASYNC_ON_CONNECT_T) NULL, NULL,(F_OESAPI_ASYNC_ON_DISCONNECT_T) NULL, NULL);
    if (! pAsyncChannel) {SLOG_ERROR("�������ļ��м���ͨ������ʧ��! channelTag[%s]","async_ord_channel1");goto ON_ERROR;}
    
    if (! OesAsyncApi_Start(pAsyncContext)) {
        SLOG_ERROR("�����첽API�߳�ʧ��!");
        goto ON_ERROR;
    }
        
    R ki(run);
  ON_ERROR:
    OesAsyncApi_ReleaseContext(pAsyncContext);
    R ki(-6);    
  }

  K1(freekrt){
    if(!run) R ki(-1);

    OesAsyncApi_Stop(pAsyncContext);
    SPK_SLEEP_MS(50);

    SLOG_INFO("���н���, �����˳�! totalPicked[%" __SPK_FMT_LL__ "d]",OesAsyncApi_GetTotalPicked(pAsyncContext));

    /* ����ص�����ִ�бȽ��� (������ں�ʱ�ϴ��I/O����, ���´�������С��1000��/ÿ��),
       ����ͨ�����·�ʽ�ȴ��ص��̵߳��첽API�̰߳�ȫ�˳� */
    while (! OesAsyncApi_IsAllTerminated(pAsyncContext)) {
        SLOG_INFO("���ڵȴ��ص��̵߳��첽API�̰߳�ȫ�˳�...");
        SPK_SLEEP_MS(1000);
    }

    OesAsyncApi_ReleaseContext(pAsyncContext);

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(krtrun){
    R ki(run);
  } 

  K2(orderInsert){
    if(!run) R ki(-1);

    OesOrdReqT          ordReq = {NULLOBJ_OES_ORD_REQ};
    
    ordReq.clSeqNo = kK(y)[0]->i;
    ordReq.mktId = kK(y)[1]->g;
    ordReq.ordType = kK(y)[2]->g;
    ordReq.bsType = kK(y)[3]->g;
    ordReq.ordQty = kK(y)[4]->i;
    ordReq.ordPrice = kK(y)[5]->i;
    strncpy(ordReq.securityId,kK(y)[6]->s,sizeof(ordReq.securityId) - 1);
    R ki(OesAsyncApi_SendOrderReq(pAsyncChannel, &ordReq));
 }

  K2(orderCancel){
    if(!run) R ki(-1);
    
    OesOrdCancelReqT    cancelReq = {NULLOBJ_OES_ORD_CANCEL_REQ};
    
    cancelReq.clSeqNo = kK(y)[0]->i;
    cancelReq.mktId = kK(y)[1]->g;
    cancelReq.origClOrdId = kK(y)[2]->j;
    
    R ki( OesAsyncApi_SendOrderCancelReq(pAsyncChannel, &cancelReq));
 }

  K2(qryOrder){
    if(!run) R ki(-1);
    int32 ret=0;
    OesOrdItemT  ord = {NULLOBJ_OES_ORD_ITEM};
    ret=OesApi_QuerySingleOrder(&cliEnv.qryChannel,kK(y)[0]->i,&ord);
    if(0>ret){
      R ki(ret);
   }
    k(0,"onkr",knk(1,knk(2,ks("ORDER_REPORT"),knk(9,ki(ord.clSeqNo),kj(ord.clOrdId),kc(ord.ordStatus),kc(ord.ordCnfmSts),ki(ord.ordCnfmTime),kj(ord.userInfo.i64),ki(ord.cumQty),ki(ord.canceledQty),ki(ord.ordRejReason)))),(K)0);
    R ki(ret);
 }
  
  K2(qryFund){
    if(!run) R ki(-1);
    int32 ret=0;
    OesCashAssetItemT  item = {NULLOBJ_OES_CASH_ASSET_ITEM};
    ret=OesApi_QuerySingleCashAsset(&cliEnv.qryChannel,kK(y)[0]->s,&item);
    if(0>ret){
      R ki(ret);
   }
    k(0,"onkr",knk(1,knk(2,ks("CASH_ASSET"),knk(9,kp(item.cashAcctId),kp(item.custId),kc(item.currType),kj(item.beginningBal),kj(item.totalBuyAmt),kj(item.totalSellAmt),kj(item.currentTotalBal),kj(item.currentAvailableBal),kj(item.currentDrawableBal)))),(K)0);
    R ki(ret);
 }

  K2(qryAllOrder){
    if(!run) R ki(-1);
    int32 ret=0;
    OesQryOrdFilterT    qryFilter = {NULLOBJ_OES_QRY_ORD_FILTER};
    ret=OesApi_QueryOrder(&cliEnv.qryChannel,&qryFilter,onqry,NULL);
    R ki(ret);
 }
  
  K2(qryHold){
    if(!run) R ki(-1);
    int32 ret=0;
    OesQryStkHoldingFilterT qryFilter = {NULLOBJ_OES_QRY_STK_HOLDING_FILTER};
    ret=OesApi_QueryStkHolding(&cliEnv.qryChannel,&qryFilter,onqry,NULL);
    R ki(ret);
 }
}

