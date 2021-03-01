#include "kcomm.h"
#include <queue>

#include    <mds_api/mds_api.h>
#include    <mds_api/mds_async_api.h>
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

Z  MdsAsyncApiContextT     *pAsyncContext = (MdsAsyncApiContextT *) NULL;
Z  MdsAsyncApiChannelT     *pAsyncChannel = (MdsAsyncApiChannelT *) NULL;
Z  MdsApiClientEnvT        cliEnv = {NULLOBJ_MDSAPI_CLIENT_ENV};

Z int32 onmds_msg(MdsApiSessionInfoT *pSessionInfo,SMsgHeadT *pMsgHead, void *pMsgBody, void *pCallbackParams){
    MdsMktRspMsgBodyT   *p=(MdsMktRspMsgBodyT *) pMsgBody;
    
    switch (pMsgHead->msgId) {
    case MDS_MSGTYPE_L2_TRADE:
        /* 处理Level2逐笔成交消息 @see MdsL2TradeT */
        break;

    case MDS_MSGTYPE_L2_ORDER:
        /* 处理Level2逐笔委托消息 @see MdsL2OrderT */
        break;

    case MDS_MSGTYPE_L2_MARKET_DATA_SNAPSHOT:
        /* 处理Level2快照行情消息 @see MdsL2StockSnapshotBodyT */
        break;

    case MDS_MSGTYPE_L2_BEST_ORDERS_SNAPSHOT:
        /* 处理Level2委托队列消息(买一／卖一前五十笔委托明细) @see MdsL2BestOrdersSnapshotBodyT */
        break;

    case MDS_MSGTYPE_L2_MARKET_DATA_INCREMENTAL:
        /* 处理(上证)Level2快照行情的增量更新消息 @see MdsL2StockSnapshotIncrementalT */
        break;

    case MDS_MSGTYPE_L2_BEST_ORDERS_INCREMENTAL:
        /* 处理(上证)Level2委托队列的增量更新消息 @see MdsL2BestOrdersSnapshotIncrementalT */
        break;

    case MDS_MSGTYPE_L2_MARKET_OVERVIEW:
        /* 处理(上证)Level2市场总览消息 @see MdsL2MarketOverviewT */
        break;

    case MDS_MSGTYPE_MARKET_DATA_SNAPSHOT_FULL_REFRESH:
        /* 处理Level1快照行情消息 @see MdsStockSnapshotBodyT */
      {K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->mktDataSnapshot.stock.OfferLevels[i].Price;kJ(qa)[i]=p->mktDataSnapshot.stock.OfferLevels[i].OrderQty;kJ(pb)[i]=p->mktDataSnapshot.stock.BidLevels[i].Price;kJ(qb)[i]=p->mktDataSnapshot.stock.BidLevels[i].OrderQty);
      mpub(knk(2,ks("MARKET_DATA_SNAPSHOT_FULL_REFRESH"),knk(20,kc(p->mktDataSnapshot.head.exchId),ki(p->mktDataSnapshot.head.tradeDate),ki(p->mktDataSnapshot.head.updateTime),kp(p->mktDataSnapshot.stock.SecurityID),kp(p->mktDataSnapshot.stock.TradingPhaseCode),kj(p->mktDataSnapshot.stock.NumTrades),kj(p->mktDataSnapshot.stock.TotalVolumeTraded),kj(p->mktDataSnapshot.stock.TotalValueTraded),ki(p->mktDataSnapshot.stock.PrevClosePx),ki(p->mktDataSnapshot.stock.OpenPx),ki(p->mktDataSnapshot.stock.HighPx),ki(p->mktDataSnapshot.stock.LowPx),ki(p->mktDataSnapshot.stock.TradePx),ki(p->mktDataSnapshot.stock.IOPV),ki(p->mktDataSnapshot.stock.NAV),kj(p->mktDataSnapshot.stock.TotalLongPosition),pa,qa,pb,qb)));
      }
        break;

    case MDS_MSGTYPE_OPTION_SNAPSHOT_FULL_REFRESH:
        /* 处理期权快照行情消息 @see MdsStockSnapshotBodyT */
      {K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->mktDataSnapshot.option.OfferLevels[i].Price;kJ(qa)[i]=p->mktDataSnapshot.option.OfferLevels[i].OrderQty;kJ(pb)[i]=p->mktDataSnapshot.option.BidLevels[i].Price;kJ(qb)[i]=p->mktDataSnapshot.option.BidLevels[i].OrderQty);
      mpub(knk(2,ks("OPTION_SNAPSHOT_FULL_REFRESH"),knk(20,kc(p->mktDataSnapshot.head.exchId),ki(p->mktDataSnapshot.head.tradeDate),ki(p->mktDataSnapshot.head.updateTime),kp(p->mktDataSnapshot.option.SecurityID),kp(p->mktDataSnapshot.option.TradingPhaseCode),kj(p->mktDataSnapshot.option.NumTrades),kj(p->mktDataSnapshot.option.TotalVolumeTraded),kj(p->mktDataSnapshot.option.TotalValueTraded),ki(p->mktDataSnapshot.option.PrevClosePx),ki(p->mktDataSnapshot.option.OpenPx),ki(p->mktDataSnapshot.option.HighPx),ki(p->mktDataSnapshot.option.LowPx),ki(p->mktDataSnapshot.option.TradePx),ki(p->mktDataSnapshot.option.IOPV),ki(p->mktDataSnapshot.option.NAV),kj(p->mktDataSnapshot.option.TotalLongPosition),pa,qa,pb,qb)));
      }
        break;

    case MDS_MSGTYPE_INDEX_SNAPSHOT_FULL_REFRESH:
        /* 处理指数行情消息 @see MdsIndexSnapshotBodyT */
      mpub(knk(2,ks("INDEX_SNAPSHOT_FULL_REFRESH"),knk(15,kc(p->mktDataSnapshot.head.exchId),ki(p->mktDataSnapshot.head.tradeDate),ki(p->mktDataSnapshot.head.updateTime),kp(p->mktDataSnapshot.index.SecurityID),kp(p->mktDataSnapshot.index.TradingPhaseCode),kj(p->mktDataSnapshot.index.NumTrades),kj(p->mktDataSnapshot.index.TotalVolumeTraded),kj(p->mktDataSnapshot.index.TotalValueTraded),kj(p->mktDataSnapshot.index.PrevCloseIdx),kj(p->mktDataSnapshot.index.OpenIdx),kj(p->mktDataSnapshot.index.HighIdx),kj(p->mktDataSnapshot.index.LowIdx),kj(p->mktDataSnapshot.index.LastIdx),kj(p->mktDataSnapshot.index.CloseIdx),ki(p->mktDataSnapshot.index.StockNum))));      
        break;

    case MDS_MSGTYPE_SECURITY_STATUS:
        /* 处理(深圳)证券状态消息 @see MdsSecurityStatusMsgT */
        break;

    case MDS_MSGTYPE_TRADING_SESSION_STATUS:
        /* 处理(上证)市场状态消息 @see MdsTradingSessionStatusMsgT */
        break;

    case MDS_MSGTYPE_MARKET_DATA_REQUEST:
        /* 处理行情订阅请求的应答消息 @see MdsMktDataRequestRspT */
        break;

    case MDS_MSGTYPE_TEST_REQUEST:
        /* 处理测试请求的应答消息 @see MdsTestRequestRspT */
        break;

    case MDS_MSGTYPE_HEARTBEAT:
        /* 直接忽略心跳消息即可 */
        break;

    case MDS_MSGTYPE_COMPRESSED_PACKETS:
        /* 接收到了压缩后的行情数据!
         * 对接压缩行情需要使用 MdsApi_WaitOnMsgCompressible 等 Compressible 接口,
         * 对于异步API需要检查是否开启了 isCompressible 标志
         */
        SLOG_ERROR("Compressed packets?! " \
                "Please use WaitOnMsgCompressible interface. " \
                "msgId[0x%02X], server[%s:%d]",
                pMsgHead->msgId, pSessionInfo->channel.remoteAddr,
                pSessionInfo->channel.remotePort);
        return SPK_NEG(EFTYPE);

    default:
        SLOG_ERROR("Invalid message type, Ignored! " \
                "msgId[0x%02X], server[%s:%d]",
                pMsgHead->msgId, pSessionInfo->channel.remoteAddr,
                pSessionInfo->channel.remotePort);
        return EFTYPE;
    }
    return 0;
}

Z int32 onmds_ref(MdsApiSessionInfoT *pSessionInfo,SMsgHeadT *pMsgHead, void *pMsgBody, MdsQryCursorT *pQryCursor,void *pCallbackParams) {
  MdsStockStaticInfoT *p = (MdsStockStaticInfoT *) pMsgBody;
    mpub(knk(2,ks("StockStaticInfo"),knk(41,kc(p->exchId),kp(p->securityId),kp(p->securityName),kc(p->mdProductType),kc(p->oesSecurityType),kc(p->subSecurityType),kc(p->currType),ki(p->securityStatus),ki(p->securityAttribute),kc(p->suspFlag),kc(p->isDayTrading),kc(p->isRegistration),kc(p->isCrdCollateral),kc(p->isCrdMarginTradeUnderlying),kc(p->isCrdShortSellUnderlying),ki(p->upperLimitPrice),ki(p->lowerLimitPrice),ki(p->priceTick),ki(p->prevClose),ki(p->lmtBuyMaxQty),ki(p->lmtBuyMinQty),ki(p->lmtBuyQtyUnit),ki(p->mktBuyQtyUnit),ki(p->mktBuyMaxQty),ki(p->mktBuyMinQty),ki(p->lmtSellMaxQty),ki(p->lmtSellMinQty),ki(p->lmtSellQtyUnit),ki(p->mktSellQtyUnit),ki(p->mktSellMaxQty),ki(p->mktSellMinQty),kj(p->bondInterest),kj(p->parValue),kc(p->auctionLimitType),kc(p->auctionReferPriceType),ki(p->auctionUpDownRange),ki(p->listDate),ki(p->maturityDate),kj(p->outstandingShare),kj(p->publicFloatShare),kp(p->underlyingSecurityId))));
    
    return 0;
}


extern "C"{
  K2(initkrq){
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
    
    if (! __MdsApi_CheckApiVersion()) {
      SLOG_ERROR("API的头文件版本与库文件版本不匹配, 没有替换头文件或者没有重新编译? apiVersion[%s], libVersion[%s]", MDS_APPL_VER_ID, MdsApi_GetApiVersion());R ki(-4);
    } else {
        SLOG_INFO("API version: %s", MdsApi_GetApiVersion());
    }

    if (! MdsApi_InitAll(&cliEnv,xs,MDSAPI_CFG_DEFAULT_SECTION_LOGGER, MDSAPI_CFG_DEFAULT_SECTION,(char *) NULL, "qryServer",(char *) NULL, (char *) NULL, (char *) NULL, (char *) NULL)) {
            SLOG_ERROR("初始化客户端环境失败!");
	    R ki(-55);
    }

    pAsyncContext = MdsAsyncApi_CreateContext(xs);
    if (! pAsyncContext) {
        SLOG_ERROR("创建异步API的运行时环境失败!");
        R ki(-5);
    }

    pAsyncChannel = MdsAsyncApi_AddChannelFromFile(
						   pAsyncContext, "async_channel1",
						   xs, MDSAPI_CFG_DEFAULT_SECTION,
						   MDSAPI_CFG_DEFAULT_KEY_TCP_ADDR,
						   onmds_msg, NULL,
						   (F_MDSAPI_ASYNC_ON_CONNECT_T) NULL, NULL,
						   (F_MDSAPI_ASYNC_ON_DISCONNECT_T) NULL, NULL);
    if (! pAsyncChannel) {
      SLOG_ERROR("从配置文件中加载通道配置失败! channelTag[%s]","async_channel1");
      goto ON_ERROR;
    }

    if (! MdsAsyncApi_Start(pAsyncContext)) {
        SLOG_ERROR("启动异步API线程失败!");
        goto ON_ERROR;
    }
        
    R ki(run);
  ON_ERROR:
    MdsAsyncApi_ReleaseContext(pAsyncContext);
    R ki(-6);    
  }

  K1(freekrq){
    if(!run) R ki(-1);

    MdsAsyncApi_Stop(pAsyncContext);
    SPK_SLEEP_MS(50);

    SLOG_INFO("运行结束, 即将退出! totalPicked[%" __SPK_FMT_LL__ "d]",MdsAsyncApi_GetTotalPicked(pAsyncContext));

    /* 如果回调处理执行比较慢 (例如存在耗时较大的I/O操作, 导致处理能力小于1000条/每秒),
       可以通过以下方式等待回调线程等异步API线程安全退出 */
    while (! MdsAsyncApi_IsAllTerminated(pAsyncContext)) {
        SLOG_INFO("正在等待回调线程等异步API线程安全退出...");
        SPK_SLEEP_MS(1000);
    }

    MdsAsyncApi_ReleaseContext(pAsyncContext);

    MdsApi_DestoryAll(&cliEnv);
    
    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(krqrun){
    R ki(run);
  } 

  K1(krqref){
    R ki(MdsApi_QueryStockStaticInfoList(&cliEnv.qryChannel,xs, (char *) NULL, (MdsQryStockStaticInfoListFilterT *)NULL,onmds_ref, NULL));
  }   
}

