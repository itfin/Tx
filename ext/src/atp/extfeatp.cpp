#include "kcomm.h"
#include <queue>

#include <atomic>
#include <map>
#include <set>
#include "atp_trade_api.h"

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
ZI loglevel=0;

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
  k(0,"onatp",L,(K)0);
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

Z ATPTradeAPI *pTradeApi;

#define MSGPUB(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));
//#define MSGPUBERR(r,s) if(r){error_info=pTradeApi->GetApiLastError();mpub(knk(2,ks("XTPErrorT"),knk(3,ki(error_info->error_id),kp(error_info->error_msg),kp(s))));}

class CTradeHandler : public ATPTradeHandler{
public: 
  CTradeHandler(){} 
  ~CTradeHandler(){}
  
  virtual void OnConnected(const std::string &reason) {MSGPUB("Connected",knk(1,kp((S)reason.c_str())))}
  virtual void OnConnectFailure(const std::string &reason) {MSGPUB("ConnectFailure",knk(1,kp((S)reason.c_str())))}
  virtual void OnConnectTimeOut(const std::string &reason) {MSGPUB("ConnectTimeOut",knk(1,kp((S)reason.c_str())))}
  virtual void OnHeartbeatTimeout(const std::string &reason) {MSGPUB("HeartbeatTimeOut",knk(1,kp((S)reason.c_str())))}
  virtual void OnLogin(const std::string &reason) {MSGPUB("Login",knk(1,kp((S)reason.c_str())))} 
  virtual void OnLogout(const std::string &reason) {MSGPUB("Logout",knk(1,kp((S)reason.c_str())))}
  virtual void OnEndOfConnection(const std::string &reason) {MSGPUB("EndOfConnection",knk(1,kp((S)reason.c_str())))}
  virtual void OnError(const std::string &reason) {MSGPUB("Error",knk(1,kp((S)reason.c_str())))}
  virtual void OnClosed(const std::string &reason) {MSGPUB("Closed",knk(1,kp((S)reason.c_str())))}
  virtual void OnLog(ATPLogLevel level, const std::string &message) {if(loglevel<=level)MSGPUB("Log",knk(2,ki(level),kp((S)message.c_str())))}

  virtual void OnRspCustLoginResp(const ATPRspCustLoginRespOtherMsg &m){MSGPUB("CustLogin",knk(2,ki(m.permisson_error_code),kp((S)pTradeApi->GetErrorInfo(m.permisson_error_code,2).c_str())))}
  virtual void OnRspCustLogoutResp(const ATPRspCustLogoutRespOtherMsg &m){MSGPUB("Custogout",knk(2,ki(m.permisson_error_code),kp((S)pTradeApi->GetErrorInfo(m.permisson_error_code,2).c_str())))}
  
  virtual void OnRspOrderStatusInternalAck(const ATPRspOrderStatusAckMsg &m){ // 订单下达内部响应
    MSGPUB("OrderStatusInternalAck",knk(36,kc(m.partition),kj(m.index),kc(m.business_type),kj(m.cl_ord_no),kp((S)m.security_id),kh(m.market_id),kc(m.exec_type),kc(m.ord_status),kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.price),kj(m.order_qty),kj(m.leaves_qty),kj(m.cum_qty),kc(m.side),kj(m.transact_time),kp((S)m.user_info),kp((S)m.order_id),kp((S)m.cl_ord_id),kp((S)m.extra_data.c_str()),kj(m.client_seq_id),kj(m.orig_cl_ord_no),kj(m.frozen_trade_value),kj(m.frozen_fee),kh(m.reject_reason_code),kp((S)m.ord_rej_reason),kc(m.order_type),kc(m.time_in_force),kc(m.position_effect),kc(m.covered_or_uncovered),kp((S)m.account_sub_code),kc(m.quote_flag),kp((S)m.security_symbol),kp((S)m.secondary_order_id),kj(m.parent_cl_ord_no)))
  }
  
  virtual void OnRspOrderStatusAck(const ATPRspOrderStatusAckMsg &m){ // 订单下达交易所确认
    MSGPUB("OrderStatusAck",knk(36,kc(m.partition),kj(m.index),kc(m.business_type),kj(m.cl_ord_no),kp((S)m.security_id),kh(m.market_id),kc(m.exec_type),kc(m.ord_status),kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.price),kj(m.order_qty),kj(m.leaves_qty),kj(m.cum_qty),kc(m.side),kj(m.transact_time),kp((S)m.user_info),kp((S)m.order_id),kp((S)m.cl_ord_id),kp((S)m.extra_data.c_str()),kj(m.client_seq_id),kj(m.orig_cl_ord_no),kj(m.frozen_trade_value),kj(m.frozen_fee),kh(m.reject_reason_code),kp((S)m.ord_rej_reason),kc(m.order_type),kc(m.time_in_force),kc(m.position_effect),kc(m.covered_or_uncovered),kp((S)m.account_sub_code),kc(m.quote_flag),kp((S)m.security_symbol),kp((S)m.secondary_order_id),kj(m.parent_cl_ord_no)))    
  }
  
  virtual void OnRspCashAuctionTradeER(const ATPRspCashAuctionTradeERMsg &m){  // 成交回报
    MSGPUB("CashAuctionTrade",knk(32,kc(m.partition),kj(m.index),kc(m.business_type),kj(m.cl_ord_no),kp((S)m.security_id),kh(m.market_id),kc(m.exec_type),kc(m.ord_status),kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.price),kj(m.order_qty),kj(m.leaves_qty),kj(m.cum_qty),kc(m.side),kj(m.transact_time),kp((S)m.user_info),kp((S)m.order_id),kp((S)m.cl_ord_id),kp((S)m.exec_id),kj(m.last_px),kj(m.last_qty),kj(m.total_value_traded),kj(m.fee),kj(m.client_seq_id),kp((S)m.extra_data.c_str()),kc(m.cash_margin),kj(m.orig_cl_ord_no),kh(m.reject_reason_code),kp((S)m.ord_rej_reason),kj(m.parent_cl_ord_no)))        
  }

  virtual void OnRspRepoAuctionTradeER(const ATPRspRepoAuctionTradeERMsg &m){
    MSGPUB("RepoAuctionTrade",knk(32,kc(m.partition),kj(m.index),kc(m.business_type),kj(m.cl_ord_no),kp((S)m.security_id),kh(m.market_id),kc(m.exec_type),kc(m.ord_status),kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.price),kj(m.order_qty),kj(m.leaves_qty),kj(m.cum_qty),kc(m.side),kj(m.transact_time),kp((S)m.user_info),kp((S)m.order_id),kp((S)m.cl_ord_id),kp((S)m.exec_id),kj(m.last_px),kj(m.last_qty),kj(m.total_value_traded),kj(m.fee),kj(m.client_seq_id),kp((S)m.extra_data.c_str()),kc(' '),kj(m.orig_cl_ord_no),kh(m.reject_reason_code),kp((S)m.ord_rej_reason),kj(m.maturity_date)))        
  } // 回购成交回报

  virtual void OnRspBizRejection(const ATPRspBizRejectionOtherMsg &m){ // 订单下达内部拒绝
    MSGPUB("BizRejection",knk(7,kj(m.client_seq_id),kp((S)m.user_info),kp((S)m.extra_data.c_str()),kj(m.transact_time),ki(m.api_msg_type),kh(m.reject_reason_code),kp((S)m.business_reject_text)))        
  }

  virtual void OnRspFundQueryResult(const ATPRspFundQueryResultMsg &m){ //资金查询
    MSGPUB("FundQueryResult",knk(21,kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.branch_id),kp((S)m.account_id),kj(m.client_seq_id),kh(m.query_result_code),kp((S)m.user_info),kp((S)m.extra_data.c_str()),kj(m.leaves_value),kj(m.init_leaves_value),kj(m.available_t0),kj(m.available_t1),kj(m.available_t2),kj(m.available_t3),kj(m.available_tall),kj(m.frozen_all),kc(m.te_partition_no),kj(m.credit_sell_frozen),kj(m.credit_sell_occupied),kj(m.credit_sell_pre_occupied),kj(m.init_credit_sell)))        
  }

  virtual void OnRspOrderQueryResult(const ATPRspOrderQueryResultMsg &m){ //委托查询
    K L=knk(0);for (auto& it:m.order_array)jk(&L,knk(30,kc(it.business_type),kp((S)it.security_id),kp((S)it.security_symbol),kh(it.market_id),kp((S)it.account_id),kc(it.side),kc(it.ord_type),kc(it.ord_status),kj(it.transact_time),kj(it.order_price),kj(it.exec_price),kj(it.order_qty),kj(it.leaves_qty),kj(it.cum_qty),kj(it.cl_ord_no),kp((S)it.order_id),kp((S)it.cl_ord_id),kj(it.client_seq_id),kj(it.orig_cl_ord_no),kj(it.frozen_trade_value),kj(it.frozen_fee),kp((S)it.currency),kh(it.reject_reason_code),kp((S)it.ord_rej_reason),kj(it.order_entrusted_amt),kj(it.order_cum_transaction_amt),kc(it.exec_type),kh(it.security_type),kj(it.canceled_qty),kc(it.order_flag)));
    MSGPUB("OrderQueryResult",knk(11,kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.client_seq_id),kh(m.query_result_code),kp((S)m.user_info),kp((S)m.extra_data.c_str()),kj(m.last_index),kj(m.total_num),kp((S)m.client_feature_code.c_str()),L))        
  }

  virtual void OnRspShareQueryResult(const ATPRspShareQueryResultMsg &m){ //持仓查询
    K L=knk(0);for (auto& it:m.order_array)jk(&L,knk(18,kp((S)it.security_id),kp((S)it.security_symbol),kh(it.market_id),kp((S)it.account_id),kp((S)it.fund_account_id),kp((S)it.branch_id),kj(it.init_qty),kj(it.leaves_qty),kj(it.available_qty),kj(it.profit_loss),kj(it.market_value),kj(it.cost_price),kp((S)it.currency),kj(it.init_crd_sell_buy_share_qty),kj(it.init_crd_sell_occupied_amt),kj(it.cur_crd_sell_occupied_qty),kj(it.cur_crd_sell_occupied_amt),kh(it.security_type)));
    MSGPUB("ShareQueryResult",knk(10,kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.client_seq_id),kh(m.query_result_code),kp((S)m.user_info),kp((S)m.extra_data.c_str()),kj(m.last_index),kj(m.total_num),L))        
  }
  
  virtual void OnRspTradeOrderQueryResult(const ATPRspTradeOrderQueryResultMsg &m){ //成交查询
    K L=knk(0);for (auto& it:m.order_array)jk(&L,knk(20,kc(it.business_type),kp((S)it.security_id),kp((S)it.security_symbol),kh(it.market_id),kp((S)it.account_id),kc(it.side),kc(it.ord_type),kc(it.exec_type),kp((S)it.exec_id),kj(it.cl_ord_no),kp((S)it.order_id),kp((S)it.cl_ord_id),kj(it.transact_time),kj(it.last_px),kj(it.last_qty),kj(it.total_value_traded),kj(it.fee),kp((S)it.currency),kj(it.client_seq_id),kh(it.security_type)));
    MSGPUB("TradeOrderQueryResult",knk(10,kp((S)m.cust_id),kp((S)m.fund_account_id),kp((S)m.account_id),kj(m.client_seq_id),kh(m.query_result_code),kp((S)m.user_info),kp((S)m.extra_data.c_str()),kj(m.last_index),kj(m.total_num),L))        
  }
  
  virtual void OnRspQuoteStatusAck(const ATPRspQuoteStatusAckMsg &msg){}
  virtual void OnRspNoLegsStatusInternalAck(const ATPRspNoLegsStatusAckMsg &msg){}
  virtual void OnRspNoLegsStatusAck(const ATPRspNoLegsStatusAckMsg &msg){}
  virtual void OnRspOptionAuctionTradeER(const ATPRspOptionAuctionTradeERMsg &msg){}
  virtual void OnRspCreditTradeER(const ATPRspCreditTradeERMsg &msg){}
  virtual void OnRspMarginRepayTradeER(const ATPRspMarginRepayTradeERMsg &msg){}
  virtual void OnRspETFRedemptionTradeER(const ATPRspETFRedemptionTradeERMsg &msg){}
  virtual void OnRspBondDistributionTradeER(const ATPRspBondDistributionTradeERMsg &msg){}
  virtual void OnRspStructuredFundTradeER(const ATPRspStructuredFundTradeERMsg &msg){}
  virtual void OnRspLOFTradeER(const ATPRspLOFTradeERMsg &msg){}
  virtual void OnRspTibAfterHourAuctionTradeER(const ATPRspTibAfterHourAuctionTradeERMsg &msg){}
  virtual void OnRspPledgeInOrOutTradeER(const ATPRspPledgeInOrOutTradeERMsg &msg){}
  virtual void OnRspMaxOrderQueryResult(const ATPRspMaxOrderQueryResultMsg &msg){}
  virtual void OnRspQueryContractSpecificationsQueryResult(const ATPRspQueryContractSpecificationsResultMsg &msg){}
  virtual void OnRspQueryCreditAmountQueryResult(const ATPRspQueryCreditAmountResultMsg &msg){}
  virtual void OnRspQueryMarginUseableQueryResult(const ATPRspQueryMarginUseableResultMsg &msg){}
  virtual void OnRspQueryFundLiabilityQueryResult(const ATPRspQueryFundLiabilityResultMsg &msg){}
  virtual void OnRspQueryShareLiabilityQueryResult(const ATPRspQueryShareLiabilityResultMsg &msg){}
  virtual void OnRspQueryContractSpecificationsManagerQueryResult(const ATPRspQueryContractSpecificationsManagerResultMsg &msg){}
  virtual void OnRspQueryMarginUnderlyingQueryResult(const ATPRspQueryMarginUnderlyingResultMsg &msg){}
  virtual void OnRspQueryCreditInfoQueryResult(const ATPRspQueryCreditInfoResultMsg &msg){}
  virtual void OnRspQueryFundAssetsInfoQueryResult(const ATPRspQueryFundAssetsInfoResultMsg &msg){}
  virtual void OnRspQuoteOrderQueryResult(const ATPRspQuoteQueryResultMsg &msg){}
  virtual void OnRspCombinationPositionQueryResult(const ATPRspCombinationQueryResultMsg &msg){}
  virtual void OnRspEtfTradeOrderQueryResult(const ATPRspETFTradeOrderQueryResultMsg &msg){}
  virtual void OnRspAccountContractShareQueryResult(const ATPRspAccountContractShareQueryResultMsg &msg){}
  virtual void OnRspAccountContractFundQueryResult(const ATPRspAccountContractFundQueryResultMsg &msg){}
  virtual void OnRspCollectQueryResult(const ATPRspCollectQueryResultMsg &msg){}
  virtual void OnRspTIBIPOQtyQueryResult(const ATPRspTIBIPOQtyQueryResultMsg &msg){}
  virtual void OnRspCoverMaxOrderQtyResultQueryResult(const ATPRspCoverMaxOrderQtyResultQueryResultMsg &msg){}
  virtual void OnRspSyncBizFinish(const ATPRspSyncBizFinishOtherMsg &msg){}
  virtual void OnRspExtFundTransferResult(const ATPRspExtFundTransferResultOtherMsg &msg){}
  virtual void OnRspExtRepayResult(const ATPRspExtRepayResultOtherMsg &msg){}
  virtual void OnRspAfterHoursPricingTradeER(const ATPRspAfterHoursPricingTradeERMsg &msg){}
  virtual void OnRspBlockTradeTransactionTradeER(const ATPRspBlockTradeTransactionTradeERMsg &msg){}
  virtual void OnRspBlockTradePricingTradeER(const ATPRspBlockTradePricingTradeERMsg &msg){}
  virtual void OnRspExtOptionFundTransferResult(const ATPRspOptionFundTransferResultOtherMsg &msg){}
  virtual void OnRspExtQueryResultExerciseProfitLoss(const ATPRspExtQueryResultExerciseProfitLossMsg &msg){}
  virtual void OnRspHKStocksThroughAuctionTradeER(const ATPRspHKStocksThroughAuctionTradeERMsg &msg){}
  virtual void OnRspExtQueryResultCombinExerciseMaxOrderQty(const ATPRspExtQueryResultCombinExerciseMaxOrderQtyMsg &msg){}
  virtual void OnRspExtQueryResultCombinExerciseProfitLoss(const ATPRspExtQueryResultCombinExerciseProfitLossMsg &msg){}
  virtual void OnRspExternalInsTETransFundResp(const ATPRspExternalInsTETransFundRespMsg &msg){}
  virtual void OnRspOptionExternalInsTETransFundResp(const ATPRspOptionExternalInsTETransFundRespMsg &msg){}
  virtual void OnRspCustPasswdModifyResult(const ATPRspCustPasswdModifyResultMsg &msg){}
  virtual void OnRspExtFundQueryResult(const ATPRspExtFundQueryResultMsg &msg){}
  virtual void OnRspBatchOrderStatusAck(const ATPRspBatchOrderStatusAckMsg &msg){}
  virtual void OnRspBatchOrderQueryResult(const ATPRspBatchOrderQueryResultMsg &msg){}
  virtual void OnRspCombinationOrderQueryResult(const ATPRspCombinationQueryResultMsg &msg){}
  virtual void OnRspExternalQueryOptionMarginRiskInfoMsg(const ATPRspExternalQueryOptionMarginRiskInfoMsg &msg){}
  virtual void OnRspExternalQueryOptionSecurityInfoMsg(const ATPRspExternalQueryOptionSecurityInfoMsg &msg){}
  virtual void OnRspExternalQueryOptionUnderlyingSecurityInfoMsg(const ATPRspExternalQueryOptionUnderlyingSecurityInfoMsg &msg){}
  virtual void OnRspExternalQueryOptionMdSnapShotArrayInfoMsg(const ATPRspExternalQueryOptionMdSnapShotArrayInfoMsg &msg){}
  virtual void OnRspExternalQueryLockedAccountContractQtyMsg(const ATPRspExternalQueryLockedAccountContractQtyMsg &msg){}
  virtual void OnRspOptionOrderQueryResult(const ATPRspOptionOrderQueryResultMsg &msg){}
  virtual void OnRspOptionTradeOrderQueryResult(const ATPRspOptionTradeOrderQueryResultMsg &msg){}
  virtual void OnRspLockedAccountContractQtyQueryResult(const ATPRspExtQueryResultLockedAccountContractQtyMsg &msg){}
  virtual void OnRspThirdPartPassThroughResult(const ATPRspThirdPartPassThroughResultMsg &msg){}
  virtual void OnRspQueryResultMarginTPAResult(const ATPRspQueryMarginTradingPrivateAmoutResultMsg &msg){}
  virtual void OnRspQuerySecuritiesLendingPrivateAmountQueryResult(const ATPRspQuerySecuritiesLendingPrivateAmountResultMsg &msg){}
  virtual void OnRspBankSecuritiesFundTransferResult(const ATPRspBankSecuritiesFundTransferResultOtherMsg &msg){}
  virtual void OnRspExtRealtimeFundQueryResult(const ATPRspExtRealtimeFundQueryResultMsg &msg){}
  virtual void OnRspExtQueryResultNewShareInfo(const ATPRspExtQueryResultNewShareInfoMsg &msg){}
  virtual void OnRspExtQueryResultSecurityInfo(const ATPRspExtQueryResultSecurityInfoMsg &msg){}
  virtual void OnRspExtQueryResultShareEx(const ATPRspExtQueryResultShareExMsg &msg){}
  virtual void OnRspExtQueryResultAssetEx(const ATPRspExtQueryResultAssetExMsg &msg){}
  virtual void OnRspAlgoParentExecReport(const ATPRspAlgoParentExecReportMsg &msg){}
  virtual void OnRspExternalQueryResultAlgoParent(const ATPRspExternalQueryResultAlgoParentMsg &msg){}
  virtual void OnRspExternalQueryResultAlgoOrder(const ATPRspExternalQueryResultAlgoOrderMsg &msg){}
};

Z CTradeHandler * pTradeSpi;

extern "C"{
  K2(initatp){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
    std::map<int32_t, int32_t> report_sync;
      
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

    pTradeApi = new ATPTradeAPI();
    if(NULL==pTradeApi) R ki(-10004);
    
    pTradeSpi = new CTradeHandler();

    ATPRetCodeType ec = ATPTradeAPI::Init();
    if (ec != ErrorCode::kSuccess) R ki(-ec);

    ATPConnectProperty prop;
    prop.user = kK(x)[0]->s;                    // 网关用户名
    prop.password = kK(x)[1]->s;            // 网关用户密码
    k0=kK(x)[2];
    prop.locations = {kS(k0)[0],kS(k0)[1]};      // 网关主备节点的地址+端口
    prop.heartbeat_interval_milli = kK(x)[3]->i;  // 发送心跳的时间间隔，单位：毫秒
    prop.connect_timeout_milli = kK(x)[4]->i;     // 连接超时时间，单位：毫秒
    prop.reconnect_time = kK(x)[5]->i;              // 重试连接次数
    prop.client_name = kK(x)[6]->s;         // 客户端程序名字
    prop.client_version = kK(x)[7]->s;           // 客户端程序版本
    prop.report_sync = report_sync;        // 回报同步数据分区号+序号，首次是空，断线重连时填入的是接受到的最新分区号+序号
    prop.mode =kK(x)[8]->i;                         // 模式0-同步回报模式，模式1-快速登录模式，不同步回报

    loglevel=y->i;
    
    ec = pTradeApi->Connect(prop,pTradeSpi);
    if (ec != ErrorCode::kSuccess)R ki(-ec);
    
    R ki(run);
  }

  K1(freeatp){
    if(!run) R ki(-1);

    ATPRetCodeType ec = pTradeApi->Close();
    if (ec!=ErrorCode::kSuccess) R ki(-ec);
    
    ATPTradeAPI::Stop();
    pTradeApi=NULL;
    delete pTradeSpi;
    pTradeSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(atprun){
    R ki(run);
  }

  K1(atplogvel){
    loglevel=xi;
    R ki(loglevel);
  }

  K2(atpLogin){
    ATPReqCustLoginOtherMsg login_msg;
    strcpy(login_msg.fund_account_id,kK(y)[0]->s); // 资金账户ID
    strcpy(login_msg.password,kK(y)[1]->s); 
    strcpy(login_msg.cust_id, kK(y)[2]->s);  
    strcpy(login_msg.branch_id,kK(y)[3]->s);
	
    // 客户号密码,密码sdk会自动加密， 无效特殊处理
    login_msg.login_mode = ATPCustLoginModeType::kFundAccountIDMode; // 登录模式，资金账号登录
    login_msg.client_seq_id = xj;        // 客户系统消息号
    login_msg.order_way = kK(y)[4]->g;     // 委托方式，自助委托
    login_msg.client_feature_code = kK(y)[5]->s; // 终端识别码
    login_msg.login_mode = kK(y)[6]->g; // 登录方式
    login_msg.extra_data = kK(y)[7]->s; // 补充字段
	
	
    ATPRetCodeType ec = pTradeApi->ReqCustLoginOther(&login_msg);
    if (ec != ErrorCode::kSuccess)R ki(ec);
    R ki(ErrorCode::kSuccess);
  }

  K2(atpLogout){    
    ATPReqCustLogoutOtherMsg logout_msg;
    strcpy(logout_msg.fund_account_id,kK(y)[0]->s);  // 资金账户ID
    logout_msg.client_seq_id = xj;               // 客户系统消息号
    logout_msg.client_feature_code = kK(y)[1]->s;      // 终端识别码

    ATPRetCodeType ec = pTradeApi->ReqCustLogoutOther(&logout_msg);
    if (ec != ErrorCode::kSuccess)R ki(ec);

    R ki(ErrorCode::kSuccess);
  }
  
  K2(insertOrder){
    if(!run) R kj(-1);

    ATPReqCashAuctionOrderMsg* p = new ATPReqCashAuctionOrderMsg;
    strcpy(p->cust_id,kK(y)[0]->s);  
    strcpy(p->fund_account_id,kK(y)[1]->s);
    strcpy(p->password,kK(y)[2]->s); // 客户密码
    p->order_way = kK(y)[3]->g;     // 委托方式，自助委托
    p->client_feature_code = kK(y)[4]->s;         // 终端识别码
    strcpy(p->account_id,kK(y)[5]->s);
    p->client_seq_id = kK(y)[6]->j; //客户委托号
    snprintf(p->user_info,17,"%ld",p->client_seq_id);
    strcpy(p->security_id,kK(y)[7]->s);  
    p->market_id = kK(y)[8]->h;
    p->side =kK(y)[9]->g;
    p->order_type = kK(y)[10]->g;  // 订单类型，限价
    p->price = kK(y)[11]->j;  // 委托价格 N13(4)，10.0000元
    p->order_qty = kK(y)[12]->j;  // 申报数量（股票为股、基金为份、上海债券为手，其他为张）N15(2)，100.00股
    p->extra_data=kK(y)[13]->s;
    
    ATPRetCodeType r = pTradeApi->ReqCashAuctionOrder(p);
    R(kj(r));  
  }

  K2(insertRepo){
    if(!run) R kj(-1);

    ATPReqRepoAuctionOrderMsg* p = new ATPReqRepoAuctionOrderMsg;
    strcpy(p->cust_id,kK(y)[0]->s);  
    strcpy(p->fund_account_id,kK(y)[1]->s);
    strcpy(p->password,kK(y)[2]->s); // 客户密码
    p->order_way = kK(y)[3]->g;     // 委托方式，自助委托
    p->client_feature_code = kK(y)[4]->s;         // 终端识别码
    strcpy(p->account_id,kK(y)[5]->s);
    p->client_seq_id = kK(y)[6]->j; //客户委托号
    snprintf(p->user_info,17,"%ld",p->client_seq_id);
    strcpy(p->security_id,kK(y)[7]->s);  
    p->market_id = kK(y)[8]->h;
    p->side =kK(y)[9]->g;
    p->price = kK(y)[11]->j;  // 委托价格 N13(4)，10.0000元
    p->order_qty = kK(y)[12]->j;  // 申报数量（股票为股、基金为份、上海债券为手，其他为张）N15(2)，100.00股
    p->extra_data=kK(y)[13]->s;
    
    ATPRetCodeType r = pTradeApi->ReqRepoAuctionOrder(p);
    R(kj(r));  
  }

  K2(cancelOrder){
    if(!run) R kj(-1);
    ATPReqCancelOrderMsg* p = new ATPReqCancelOrderMsg;
    strcpy(p->cust_id,kK(y)[0]->s);            // 客户号ID
    strcpy(p->fund_account_id,kK(y)[1]->s); // 资金账户ID
    p->order_way = kK(y)[2]->g;                                  // 委托方式，自助委托
    p->client_feature_code = kK(y)[3]->s;         // 终端识别码
    strcpy(p->account_id,kK(y)[4]->s);
    p->orig_cl_ord_no = kK(y)[5]->j;
    p->client_seq_id = kK(y)[6]->j;                     // 用户系统消息序号
    
    ATPRetCodeType r = pTradeApi->ReqCancelOrder(p); 
    R(kj(r));
  }

  K2(queryOrder){
    if(!run) R kj(-1);

    ATPReqOrderQueryMsg* p = new ATPReqOrderQueryMsg;

    strcpy(p->cust_id,kK(y)[0]->s);            // 客户号ID
    strcpy(p->fund_account_id,kK(y)[1]->s); // 资金账户ID
    strcpy(p->account_id,kK(y)[2]->s);
    p->business_abstract_type = kK(y)[3]->g;
    p->market_id = kK(y)[4]->h;
    p->cl_ord_no=kK(y)[5]->j;
    p->client_seq_id =xj;                     // 用户系统消息序号

    p->query_index=kK(y)[6]->j;
	
    ATPRetCodeType r = pTradeApi->ReqOrderQuery(p);
    delete p;
    
    R(ki(r));
  }

  K2(queryPos){
    if(!run) R kj(-1);
    ATPReqShareQueryMsg* p = new ATPReqShareQueryMsg;

    strcpy(p->cust_id, kK(y)[0]->s);           // 客户号ID
    strcpy(p->fund_account_id, kK(y)[1]->s); // 资金账户ID
    p->client_seq_id = xj;                   // 用户系统消息序号
    //p->account_id_array

    APIAccountIDUnit  aiu;
    strcpy(aiu.account_id, kK(y)[3]->s);
    strcpy(aiu.branch_id, kK(y)[2]->s);
    strcpy(aiu.fund_account_id, kK(y)[1]->s);
    p->account_id_array.push_back(aiu);
    strcpy(aiu.account_id, kK(y)[4]->s);
    p->account_id_array.push_back(aiu);

    p->query_index=kK(y)[5]->j;
    ATPRetCodeType r = pTradeApi->ReqShareQuery(p);      
    R(ki(r));
  }

  K2(queryAsset){
    if(!run) R kj(-1);

    ATPReqFundQueryMsg* p = new ATPReqFundQueryMsg;

    strcpy(p->cust_id,kK(y)[0]->s);            // 客户号ID
    strcpy(p->fund_account_id,kK(y)[1]->s); // 资金账户ID
    strcpy(p->branch_id,kK(y)[2]->s);
    strcpy(p->account_id,kK(y)[3]->s);
    strcpy(p->currency, ATPCurrencyConst::kCNY);
    p->client_seq_id = xj;                    // 用户系统消息序号

    ATPRetCodeType r = pTradeApi->ReqFundQuery(p);
      
    R(ki(r));
  }


  K2(queryTrade){
    if(!run) R kj(-1);

    ATPReqTradeOrderQueryMsg* p = new ATPReqTradeOrderQueryMsg;

    strcpy(p->cust_id,kK(y)[0]->s);            // 客户号ID
    strcpy(p->fund_account_id,kK(y)[1]->s); // 资金账户ID
    strcpy(p->branch_id,kK(y)[2]->s);
    strcpy(p->account_id,kK(y)[3]->s);
    p->market_id = kK(y)[4]->h;
    p->business_abstract_type = BusinessAbstractTypeConst::kCash;
    p->client_seq_id = xj;                    // 用户系统消息序号

    p->query_index=kK(y)[5]->j;

    ATPRetCodeType r = pTradeApi->ReqTradeOrderQuery(p);
    delete p;
    
    R(ki(r));
  }

  /*  
  K3(queryAllTrade){
    if(!run) R kj(-1);
    int r=0;
    
    XTPQueryTraderReq req;
    strcpy(req.ticker,kK(z)[0]->s);
    req.begin_time=kK(z)[1]->j;
    req.end_time=kK(z)[2]->j;  
    
    r=pTradeApi->QueryTrades(&req,xj,y->i);
    XTPPUBERR(r,"queryAllTrade")
    
    R(ki(r));
  }

  K3(transFund){
    if(!run) R kj(-1);

    XTPFundTransferReq req;
    strcpy(req.fund_account,kK(z)[0]->s);
    strcpy(req.password,kK(z)[1]->s);
    req.amount=kK(z)[2]->f;
    req.transfer_type=(XTP_FUND_TRANSFER_TYPE)kK(z)[3]->i;  
      
    uint64_t r=pTradeApi->FundTransfer(&req,xj);
    XTPPUBERR(!r,"transFund")
      
    R(kj(r));
  }

  K3(qryFundTrans){
    if(!run) R kj(-1);

    XTPQueryFundTransferLogReq req;
    req.serial_id=kK(z)[0]->j;
      
    int r=pTradeApi->QueryFundTransfer(&req,xj,y->i);
    XTPPUBERR(r,"qryFundTrans")
      
    R(ki(r));
  }

  K3(qryETF){
    if(!run) R kj(-1);

    XTPQueryETFBaseReq req;
    req.market=(XTP_MARKET_TYPE)kK(z)[0]->i;
    strcpy(req.ticker,kK(z)[1]->s);
      
    int r=pTradeApi->QueryETF(&req,xj,y->i);
    XTPPUBERR(r,"qryETF")
      
    R(ki(r));
  }

  K3(qryETFPCF){
    if(!run) R kj(-1);

    XTPQueryETFComponentReq req;
    req.market=(XTP_MARKET_TYPE)kK(z)[0]->i;
    strcpy(req.ticker,kK(z)[1]->s);
      
    int r=pTradeApi->QueryETFTickerBasket(&req,xj,y->i);
    XTPPUBERR(r,"qryETFPCF")
      
    R(ki(r));
  }

  K3(qryIPO){
    if(!run) R kj(-1);

    int r=pTradeApi->QueryIPOInfoList(xj,y->i);
    XTPPUBERR(r,"qryIPO")
      
    R(ki(r));
  }

  K3(qryIPOQuota){
    if(!run) R kj(-1);

    int r=pTradeApi->QueryIPOQuotaInfo(xj,y->i);
    XTPPUBERR(r,"qryIPOQuota")
    
    R(ki(r));
  }

  K3(qryOption){
    if(!run) R kj(-1);

    XTPQueryOptionAuctionInfoReq req;
    req.market=(XTP_MARKET_TYPE)kK(z)[0]->i;
    strcpy(req.ticker,kK(z)[1]->s);
      
    int r=pTradeApi->QueryOptionAuctionInfo(&req,xj,y->i);
    XTPPUBERR(r,"qryOption")
      
    R(ki(r));
  }
*/

}
