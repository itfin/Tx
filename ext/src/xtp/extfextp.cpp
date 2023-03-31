#include "kcomm.h"
#include <queue>
#include "xtp_trader_api.h"

#undef _XTPALGO

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
  k(0,"onxtp",L,(K)0);
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

Z XTP::API::TraderApi *pTradeApi;
ZJ sessid=0;
Z XTPRI *error_info;

#define XTPPUB(x,y) mpub(knk(2,ks(x),knk(2,kb(is_last),(NULL==p)?knk(0):y)));
#define XTPPUB1(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));
#define XTPPUBERR(r,s) if(r){error_info=pTradeApi->GetApiLastError();mpub(knk(2,ks("XTPErrorT"),knk(3,ki(error_info->error_id),kp(error_info->error_msg),kp(s))));}

class CTradeHandler : public XTP::API::TraderSpi{
public: 
  CTradeHandler(){} 
  ~CTradeHandler(){}

  virtual void OnDisconnected(uint64_t session_id, int reason) {mpub(knk(2,ks("DisconnectedT"),knk(2,kj(session_id),ki(reason))));}
  
  virtual void OnError(XTPRI *error_info) {if((NULL!=error_info)&&(0!=error_info->error_id)){O("ErrorCode=[%d], ErrorMsg=[%s]\n",error_info->error_id,error_info->error_msg);mpub(knk(2,ks("XTPErrorT"),knk(3,ki(error_info->error_id),kp(error_info->error_msg),kp("OnError"))));R;}};

  virtual void OnOrderEvent(XTPOrderInfo *p, XTPRI *error_info, uint64_t session_id) {
#if defined(_XTPALGO)        
    //    if(0!=pTradeApi->GetAlgorithmIDByOrder(p->order_xtp_id,p->order_client_id))R;
#endif    
    XTPPUB1("Order",knk(24,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->order_xtp_id),ki(p->order_client_id),kj(p->order_cancel_xtp_id),kp(p->ticker),ki(p->market),kf(p->price),kj(p->quantity),ki(p->price_type),kc(p->side),kc(p->position_effect),ki(p->business_type),kj(p->qty_traded),kj(p->qty_left),kj(p->insert_time),kj(p->update_time),kj(p->cancel_time),kf(p->trade_amount),kp(p->order_local_id),ki(p->order_status),ki(p->order_submit_status),ki(p->order_type)));  
  };

  virtual void OnTradeEvent(XTPTradeReport *p, uint64_t session_id){
#if defined(_XTPALGO)        
    //    if(0!=pTradeApi->GetAlgorithmIDByOrder(p->order_xtp_id,p->order_client_id))R;
#endif        
    XTPPUB1("Trade",knk(17,kj(session_id),kj(p->order_xtp_id),ki(p->order_client_id),kp(p->ticker),ki(p->market),kp(p->exec_id),kf(p->price),kj(p->quantity),kj(p->trade_time),kf(p->trade_amount),kj(p->report_index),kp(p->order_exch_id),ki(p->trade_type),kc(p->side),kc(p->position_effect),ki(p->business_type),kp(p->branch_pbu)));  
  };

  virtual void OnCancelOrderError(XTPOrderCancelInfo *p, XTPRI *error_info, uint64_t session_id) {
    XTPPUB1("OrderCxlErr",knk(5,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->order_xtp_id),kj(p->order_cancel_xtp_id)));
  };

  virtual void OnQueryOrder(XTPQueryOrderRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryOrder",knk(26,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->order_xtp_id),ki(p->order_client_id),kj(p->order_cancel_xtp_id),kp(p->ticker),ki(p->market),kf(p->price),kj(p->quantity),ki(p->price_type),kc(p->side),kc(p->position_effect),ki(p->business_type),kj(p->qty_traded),kj(p->qty_left),kj(p->insert_time),kj(p->update_time),kj(p->cancel_time),kf(p->trade_amount),kp(p->order_local_id),ki(p->order_status),ki(p->order_submit_status),ki(p->order_type)));  
  };

  virtual void OnQueryOrderByPage(XTPQueryOrderRsp *order_info, int64_t req_count, int64_t order_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

  virtual void OnQueryTrade(XTPQueryTradeRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryTrade",knk(21,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->order_xtp_id),ki(p->order_client_id),kp(p->ticker),ki(p->market),kp(p->exec_id),kf(p->price),kj(p->quantity),kj(p->trade_time),kf(p->trade_amount),kj(p->report_index),kp(p->order_exch_id),ki(p->trade_type),kc(p->side),kc(p->position_effect),ki(p->business_type),kp(p->branch_pbu)));
  };

  virtual void OnQueryTradeByPage(XTPQueryTradeRsp *trade_info, int64_t req_count, int64_t trade_sequence, int64_t query_reference, int request_id, bool is_last, uint64_t session_id) {};

  virtual void OnQueryPosition(XTPQueryStkPositionRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryPos",knk(20,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kp(p->ticker),kp(p->ticker_name),ki(p->market),kj(p->total_qty),kj(p->sellable_qty),kf(p->avg_price),kf(p->unrealized_pnl),kj(p->yesterday_position),kj(p->purchase_redeemable_qty),ki(p->position_direction),kj(p->executable_option),kj(p->lockable_position),kj(p->executable_underlying),kj(p->locked_position),kj(p->usable_locked_position)));
  };

  virtual void OnQueryAsset(XTPQueryAssetRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryAsset",knk(27,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kf(p->total_asset),kf(p->buying_power),kf(p->security_asset),kf(p->fund_buy_amount),kf(p->fund_buy_fee),kf(p->fund_sell_amount),kf(p->fund_sell_fee),kf(p->withholding_amount),ki(p->account_type),kf(p->frozen_margin),kf(p->frozen_exec_cash),kf(p->frozen_exec_fee),kf(p->pay_later),kf(p->preadva_pay),kf(p->orig_banlance),kf(p->banlance),kf(p->deposit_withdraw),kf(p->trade_netting),kf(p->captial_asset),kf(p->force_freeze_amount),kf(p->preferred_amount),kf(p->repay_stock_aval_banlance)));    
  };

  virtual void OnQueryStructuredFund(XTPStructuredFundInfo *fund_info, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {};

  virtual void OnQueryFundTransfer(XTPFundTransferNotice *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryFundTrans",knk(10,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->serial_id),ki(p->transfer_type),kf(p->amount),ki(p->oper_status),kj(p->transfer_time)));    
  };

  virtual void OnFundTransfer(XTPFundTransferNotice *p, XTPRI *error_info, uint64_t session_id) {
    XTPPUB1("FundTrans",knk(8,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kj(p->serial_id),ki(p->transfer_type),kf(p->amount),ki(p->oper_status),kj(p->transfer_time)));    
  };

  virtual void OnQueryETF(XTPQueryETFBaseRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryETF",knk(16,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->market),kp(p->etf),kp(p->subscribe_redemption_ticker),ki(p->unit),ki(p->subscribe_status),ki(p->redemption_status),kf(p->max_cash_ratio),kf(p->estimate_amount),kf(p->cash_component),kf(p->net_value),kf(p->total_amount)));    
  };

  virtual void OnQueryETFBasket(XTPQueryETFComponentRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryETFPCF",knk(14,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->market),kp(p->ticker),kp(p->component_ticker),kp(p->component_name),kj(p->quantity),ki(p->component_market),ki(p->replace_type),kf(p->premium_ratio),kf(p->amount)));    
  };

  virtual void OnQueryIPOInfoList(XTPQueryIPOTickerRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryIPO",knk(12,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->market),kp(p->ticker),kp(p->ticker_name),ki(p->ticker_type),kf(p->price),ki(p->unit),ki(p->qty_upper_limit)));    
  };

  virtual void OnQueryIPOQuotaInfo(XTPQueryIPOQuotaRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryIOOQuota",knk(8,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->market),ki(p->quantity),ki(p->tech_quantity)));    
  };

  virtual void OnQueryOptionAuctionInfo(XTPQueryOptionAuctionInfoRsp *p, XTPRI *error_info, int request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryOption",knk(41,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kp(p->ticker),ki(p->security_id_source),kp(p->symbol),kp(p->contract_id),kp(p->underlying_security_id),ki(p->underlying_security_id_source),ki(p->list_date),ki(p->last_trade_date),ki(p->ticker_type),ki(p->day_trading),ki(p->call_or_put),ki(p->delivery_day),ki(p->delivery_month),ki(p->exercise_type),ki(p->exercise_begin_date),ki(p->exercise_end_date),kf(p->exercise_price),kj(p->qty_unit),kj(p->contract_unit),kj(p->contract_position),kf(p->prev_close_price),kf(p->prev_clearing_price),kj(p->lmt_buy_max_qty),kj(p->lmt_buy_min_qty),kj(p->lmt_sell_max_qty),kj(p->lmt_sell_min_qty),kj(p->mkt_buy_max_qty),kj(p->mkt_buy_min_qty),kj(p->mkt_sell_max_qty),kj(p->mkt_sell_min_qty),kf(p->price_tick),kf(p->upper_limit_price),kf(p->lower_limit_price),kf(p->sell_margin),kf(p->margin_ratio_param1),kf(p->margin_ratio_param2)));    
  };

#if defined(_XTPALGO)    
  //  virtual void OnStrategyStateReport(XTPStrategyStateReportStruct* p, uint64_t session_id) {
    XTPPUB1("StrategyStateReport",knk(19,kj(session_id),ki(p->m_strategy_info.m_strategy_type),kc(p->m_strategy_info.m_strategy_state),kj(p->m_strategy_info.m_client_strategy_id),kj(p->m_strategy_info.m_xtp_strategy_id),kj(p->m_strategy_qty),kj(p->m_strategy_ordered_qty),kj(p->m_strategy_cancelled_qty),kj(p->m_strategy_execution_qty),kj(p->m_strategy_unclosed_qty),kf(p->m_strategy_asset),kf(p->m_strategy_ordered_asset),kf(p->m_strategy_execution_asset),kf(p->m_strategy_execution_price),kf(p->m_strategy_market_price),kf(p->m_strategy_price_diff),kf(p->m_strategy_asset_diff),ki(p->m_error_info.error_id),kp(p->m_error_info.error_msg)));  
    
  };
  
  virtual void OnInsertAlgoOrder(XTPStrategyInfoStruct* p, XTPRI *error_info, uint64_t session_id) {
    XTPPUB1("InsertAlgoOrder",knk(7,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->m_strategy_type),kc(p->m_strategy_state),kj(p->m_client_strategy_id),kj(p->m_xtp_strategy_id)));    
  };
  
  virtual void OnCancelAlgoOrder(XTPStrategyInfoStruct* p, XTPRI *error_info, uint64_t session_id) {
    XTPPUB1("CancelAlgoOrder",knk(7,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->m_strategy_type),kc(p->m_strategy_state),kj(p->m_client_strategy_id),kj(p->m_xtp_strategy_id)));    
  };
  
  virtual void OnQueryStrategy(XTPStrategyInfoStruct* p, char* strategy_param, XTPRI *error_info, int32_t request_id, bool is_last, uint64_t session_id) {
    XTPPUB("QryStrategy",knk(10,ki(request_id),kb(is_last),kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),ki(p->m_strategy_type),kc(p->m_strategy_state),kj(p->m_client_strategy_id),kj(p->m_xtp_strategy_id),kp(strategy_param)));        
  };

  virtual void OnALGOUserEstablishChannel(char* user, XTPRI* error_info, uint64_t session_id){
    XTPPUB1("ALGOUserEstablishChannel",knk(4,kj(session_id),ki((NULL==error_info)?0:error_info->error_id),kp((NULL==error_info)?(S)"":error_info->error_msg),kp(user)));
  };
  
  virtual void OnAlgoDisconnected(int reason) {};
  virtual void OnAlgoConnected() {};
#endif  
};

Z CTradeHandler * pTradeSpi;

extern "C"{
  K2(initxtpt){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
    XTPRI *errinfo;
      
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
    pTradeApi = XTP::API::TraderApi::CreateTraderApi(kK(x)[0]->i,kK(x)[1]->s,(XTP_LOG_LEVEL)kK(x)[2]->i);
    if(NULL==pTradeApi) R ki(-10004);
          
    pTradeSpi = new CTradeHandler();
    pTradeApi->RegisterSpi(pTradeSpi);

    pTradeApi->SubscribePublicTopic(XTP_TERT_QUICK);
    pTradeApi->SetSoftwareVersion(kK(x)[3]->s);
    pTradeApi->SetSoftwareKey(kK(x)[4]->s);    
    pTradeApi->SetHeartBeatInterval(kK(x)[5]->i);
    
    sessid=pTradeApi->Login(kK(y)[0]->s, kK(y)[1]->i,kK(y)[2]->s,kK(y)[3]->s,(0<kK(y)[4]->i)?XTP_PROTOCOL_TCP:XTP_PROTOCOL_UDP);
    if(!sessid){errinfo=pTradeApi->GetApiLastError();mpub(knk(2,ks("LoginFailT"),knk(2,ki(errinfo->error_id),kp(errinfo->error_msg))));R ki(-11000);}
    mpub(knk(2,ks("LoginT"),knk(4,kj(sessid),kp((S)pTradeApi->GetApiVersion()),kp((S)pTradeApi->GetTradingDay()),kb(pTradeApi->IsServerRestart(sessid)))));
    R ki(run);
  }

  K1(freextpt){
    if(!run) R ki(-1);

    pTradeApi->Logout(sessid);
    pTradeApi->RegisterSpi(NULL);
    pTradeApi->Release();
    pTradeApi=NULL;
    delete pTradeSpi;
    pTradeSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(xtptrun){
    R ki(run);
  }

  K1(xtperror){
    XTPRI *err=pTradeApi->GetApiLastError();
    R kp(err->error_msg);
  }
  
  K1(xtpver){
    R kp((S)pTradeApi->GetApiVersion());
  }
  
  K3(insertOrder){
    if(!run) R kj(-1);
    uint64_t r=0;
    
    XTPOrderInsertInfo req;
    req.order_client_id=kK(z)[0]->i;
    strcpy(req.ticker,kK(z)[1]->s);
    req.market=(XTP_MARKET_TYPE)kK(z)[2]->i;
    req.price=kK(z)[3]->f;
    req.quantity=kK(z)[4]->j;
    req.price_type=(XTP_PRICE_TYPE)kK(z)[5]->i;
    req.side=(XTP_SIDE_TYPE)kK(z)[6]->g;
    req.position_effect=(XTP_POSITION_EFFECT_TYPE)kK(z)[7]->g;
    req.business_type=(XTP_BUSINESS_TYPE)kK(z)[8]->i;
    r=pTradeApi->InsertOrder(&req,xj);
    XTPPUBERR(!r,"insertOrder")
    R(kj(r));  
  }

  K3(cancelOrder){
    if(!run) R kj(-1);
    uint64_t r=0;

    r=pTradeApi->CancelOrder(kK(z)[0]->j,xj);
    XTPPUBERR(!r,"cancelOrder")
    
    R(kj(r));
  }

  K3(queryOrder){
    if(!run) R kj(-1);
    int r=0;

    r=pTradeApi->QueryOrderByXTPID(kK(z)[0]->j,xj,y->i);
    XTPPUBERR(r,"queryOrder")
    
    R(ki(r));
  }

  K3(queryAllOrder){
    if(!run) R kj(-1);
    int r=0;
    
    XTPQueryOrderReq req;
    strcpy(req.ticker,kK(z)[0]->s);
    req.begin_time=kK(z)[1]->j;
    req.end_time=kK(z)[2]->j;  
    
    r=pTradeApi->QueryOrders(&req,xj,y->i);
    XTPPUBERR(r,"queryAllOrder")
    
    R(ki(r));
  }

  K3(queryTrade){
    if(!run) R kj(-1);
    int r=0;

    r=pTradeApi->QueryTradesByXTPID(kK(z)[0]->j,xj,y->i);
    XTPPUBERR(r,"queryTrade")
    
    R(ki(r));
  }

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

  K3(queryPos){
    if(!run) R kj(-1);
    
    int r=pTradeApi->QueryPosition(kK(z)[0]->s,xj,y->i);
    XTPPUBERR(r,"queryPos")
      
    R(ki(r));
  }

  K3(queryAsset){
    if(!run) R kj(-1);

    int r=pTradeApi->QueryAsset(xj,y->i);
    XTPPUBERR(r,"queryAsset")
      
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

#if defined(_XTPALGO)
  /*  
  K1(loginALGO){
    R ki(pTradeApi->LoginALGO(kK(x)[0]->s,kK(x)[1]->i,kK(x)[2]->s,kK(x)[3]->s,XTP_PROTOCOL_TCP,kK(x)[4]->s));
  }

  K2(establishAlgoChannel){
    R ki(pTradeApi->ALGOUserEstablishChannel(kK(x)[0]->s,kK(x)[1]->i,kK(x)[2]->s,kK(x)[3]->s,y->j));    
  }
  
  K3(insertOrderAlgo){
    if(!run) R kj(-1);
    uint64_t r=0;
    
    r=pTradeApi->InsertAlgoOrder(kK(z)[0]->i,kK(z)[1]->j,kK(z)[2]->s,xj);
    XTPPUBERR(!r,"insertOrderAlgo")
    R(kj(r));  
  }

  K3(cancelOrderAlgo){
    if(!run) R kj(-1);
    uint64_t r=0;

    r=pTradeApi->CancelAlgoOrder(true,kK(z)[0]->j,xj);
    XTPPUBERR(!r,"cancelAlgoOrder")
    
    R(kj(r));
  }

  K3(queryOrderAlgo){
    if(!run) R kj(-1);
    int r=0;

    r=pTradeApi->QueryStrategy(kK(z)[0]->i,kK(z)[1]->j,kK(z)[2]->j,xj,y->i);
    XTPPUBERR(r,"queryOrderAlgo")
    
    R(ki(r));
  }
  */
#endif
}
