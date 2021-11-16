#include "kcomm.h"
#include <queue>
#include "xtp_quote_api.h"

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

Z XTP::API::QuoteApi *pQuoteApi;

ZC FRONTLIST[BUFLEN];
ZC BROKER[SYMSIZE];
ZC USER[SYMSIZE];
ZC PASSWORD[SYMSIZE];
ZC SYMLIST[BUFLEN];

Z XTPRI *error_info;
#define XTPPUBERR(r,s) if(r){error_info=pQuoteApi->GetApiLastError();mpub(knk(2,ks("XTPErrorQ"),knk(3,ki(error_info->error_id),kp(error_info->error_msg),kp(s))));}

#define XTPPUB(x,y) mpub(knk(2,ks(x),knk(2,kb(is_last),(NULL==p)?knk(0):y)));
#define XTPPUB1(x,y) mpub(knk(2,ks(x),(NULL==p)?knk(0):y));

#define RETURNONERR(s) if((NULL!=error_info)&&(0!=error_info->error_id)){mpub(knk(2,ks("XTPErrorQ"),knk(4,ki(error_info->error_id),kp(error_info->error_msg),kp(s),kb(is_last))));R;}
#define RETURNONERR1(s) if((NULL!=error_info)&&(0!=error_info->error_id)){mpub(knk(2,ks("XTPErrorQ"),knk(4,ki(error_info->error_id),kp(error_info->error_msg),kp(s),kb(true))));R;}

class CQuoteHandler : public XTP::API::QuoteSpi{
public: 
  CQuoteHandler(){} 
  ~CQuoteHandler(){} 

  virtual void OnDisconnected(int reason){mpub(knk(2,ks("DisconnectedQ"),knk(1,ki(reason))));}
  
  virtual void OnError(XTPRI *error_info,bool is_last){RETURNONERR("OnError")}

  virtual void OnSubMarketData(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnSubMarketData");
    XTPPUB("MDSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }
  virtual void OnUnSubMarketData(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnUnSubMarketData");
    XTPPUB("MDUnSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }

  virtual void OnDepthMarketData(XTPMD *p, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count){
    K bp=ktn(KF,10),bq=ktn(KF,10),ap=ktn(KF,10),aq=ktn(KF,10),b1=ktn(KJ,bid1_count),a1=ktn(KJ,ask1_count);
    
    DO(10,kF(bp)[i]=p->bid[i])
      DO(10,kF(ap)[i]=p->ask[i])
      DO(10,kF(bq)[i]=p->bid_qty[i])
      DO(10,kF(aq)[i]=p->ask_qty[i])
      DO(bid1_count,kJ(b1)[i]=bid1_qty[i])
      DO(ask1_count,kJ(a1)[i]=ask1_qty[i])
      
      
      if(XTP_MARKETDATA_ACTUAL==p->data_type){  
	mpub(knk(2,ks("DepthMD"),knk(61,ki((I)p->data_type),ki((I)p->exchange_id),kp(p->ticker),kf(p->last_price),kf(p->pre_close_price),kf(p->open_price),kf(p->high_price),kf(p->low_price),kf(p->close_price),kf(p->pre_total_long_positon),ki(p->total_long_positon),kf(p->pre_settl_price),kf(p->settl_price),kf(p->upper_limit_price),kf(p->lower_limit_price),kf(p->pre_delta),kf(p->curr_delta),kj(p->data_time),kj(p->qty),kf(p->turnover),kf(p->avg_price),bp,ap,bq,aq,b1,a1,ki(max_bid1_count),ki(max_ask1_count),kj(p->trades_count),kp(p->ticker_status),kj(p->stk.total_bid_qty),kj(p->stk.total_ask_qty),kf(p->stk.ma_bid_price),kf(p->stk.ma_ask_price),kf(p->stk.ma_bond_bid_price),kf(p->stk.ma_bond_ask_price),kf(p->stk.yield_to_maturity),kf(p->stk.iopv),ki(p->stk.etf_buy_count),ki(p->stk.etf_sell_count),kf(p->stk.etf_buy_qty),kf(p->stk.etf_buy_money),kf(p->stk.etf_sell_qty),kf(p->stk.etf_sell_money),kf(p->stk.total_warrant_exec_qty),kf(p->stk.warrant_lower_price),kf(p->stk.warrant_upper_price),ki(p->stk.cancel_buy_count),ki(p->stk.cancel_sell_count),kf(p->stk.cancel_buy_qty),kf(p->stk.cancel_sell_qty),kf(p->stk.cancel_buy_money),kf(p->stk.cancel_sell_money),kj(p->stk.total_buy_count),kj(p->stk.total_sell_count),ki(p->stk.duration_after_buy),kf(p->stk.duration_after_sell),ki(p->stk.num_bid_orders),ki(p->stk.num_ask_orders),kf(p->stk.pre_iopv))));
      }else if(XTP_MARKETDATA_OPTION==p->data_type){
	mpub(knk(2,ks("DepthMD"),knk(34,ki((I)p->data_type),ki((I)p->exchange_id),kp(p->ticker),kf(p->last_price),kf(p->pre_close_price),kf(p->open_price),kf(p->high_price),kf(p->low_price),kf(p->close_price),kf(p->pre_total_long_positon),ki(p->total_long_positon),kf(p->pre_settl_price),kf(p->settl_price),kf(p->upper_limit_price),kf(p->lower_limit_price),kf(p->pre_delta),kf(p->curr_delta),kj(p->data_time),kj(p->qty),kf(p->turnover),kf(p->avg_price),bp,ap,bq,aq,b1,a1,ki(max_bid1_count),ki(max_ask1_count),kj(p->trades_count),kp(p->ticker_status),kf(p->opt.auction_price),kj(p->opt.auction_qty),kj(p->opt.last_enquiry_time))));	
      }else{}
  }

  virtual void OnOrderBook(XTPOB *p){
    K bp=ktn(KF,10),bq=ktn(KF,10),ap=ktn(KF,10),aq=ktn(KF,10);
    DO(10,kF(bp)[i]=p->bid[i]);
    DO(10,kF(ap)[i]=p->ask[i]);
    DO(10,kF(bq)[i]=p->bid_qty[i]);
    DO(10,kF(aq)[i]=p->ask_qty[i]);
      
    mpub(knk(2,ks("Book"),knk(11,ki(p->exchange_id),kp(p->ticker),kf(p->last_price),kj(p->qty),kf(p->turnover),kj(p->trades_count),bp,ap,bq,aq,kj(p->data_time))));
  }
  virtual void OnTickByTick(XTPTBT *p){
    if(XTP_TBT_ENTRUST==p->type){
      mpub(knk(2,ks("TickOrder"),knk(12,ki(p->type),ki(p->exchange_id),kp(p->ticker),kj(p->seq),kj(p->data_time),ki(p->entrust.channel_no),kj(p->entrust.seq),kf(p->entrust.price),kj(p->entrust.qty),kc(p->entrust.side),kc(p->entrust.ord_type),kj(p->entrust.order_no))));
    }else{
      mpub(knk(2,ks("TickMatch"),knk(13,ki(p->type),ki(p->exchange_id),kp(p->ticker),kj(p->seq),kj(p->data_time),ki(p->trade.channel_no),kj(p->trade.seq),kf(p->trade.price),kj(p->trade.qty),kf(p->trade.money),kj(p->trade.bid_no),kj(p->trade.ask_no),kc(p->trade.trade_flag))));      
    }
  }
  
  virtual void OnSubOrderBook(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnSubOrderBook");
    XTPPUB("BookSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }
  virtual void OnUnSubOrderBook(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnUnSubOrderBook");
    XTPPUB("BookUnSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }
  virtual void OnSubTickByTick(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnSubTickByTick");
    XTPPUB("TickSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }
  virtual void OnUnSubTickByTick(XTPST *p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnUnSubTickByTick");
    XTPPUB("TickUnSub",knk(2,ki(p->exchange_id),kp(p->ticker)));        
  }
  virtual void OnQueryAllTickers(XTPQSI* p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnQueryAllTickers");
    XTPPUB("Ticker",knk(10,ki(p->exchange_id),kp(p->ticker),kp(p->ticker_name),ki(p->ticker_type),kf(p->pre_close_price),kf(p->upper_limit_price),kf(p->lower_limit_price),kf(p->price_tick),ki(p->buy_qty_unit),ki(p->sell_qty_unit)));    
  }

  virtual void OnQueryTickersPriceInfo(XTPTPI* p, XTPRI *error_info, bool is_last){
    RETURNONERR("OnQueryTickersPriceInfo");
    XTPPUB("Price",knk(3,ki(p->exchange_id),kp(p->ticker),kf(p->last_price)));        
  }

  virtual void OnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllMarketData");
    XTPPUB1("MDSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllMarketData");
    XTPPUB1("MDkUnSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllOrderBook");
    XTPPUB1("BookSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllOrderBook");
    XTPPUB1("BookkUnSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllTickByTick");
    XTPPUB1("TickSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllTickByTick");
    XTPPUB1("TickkUnSubAll",knk(1,ki(exchange_id)));        
  }
  virtual void OnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllOptionMarketData");
    XTPPUB1("MDSubAllOpt",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllOptionMarketData(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllOptionMarketData");
    XTPPUB1("MDkUnSubAllOpt",knk(1,ki(exchange_id)));        
  }
  virtual void OnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllOptionOrderBook");
    XTPPUB1("BookSubAllOpt",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllOptionOrderBook(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllOptionOrderBook");
    XTPPUB1("BookkUnSubAllOpt",knk(1,ki(exchange_id)));        
  }
  virtual void OnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnSubscribeAllOptionTickByTick");
    XTPPUB1("TickSubAllOpt",knk(1,ki(exchange_id)));        
  }
  virtual void OnUnSubscribeAllOptionTickByTick(XTP_EXCHANGE_TYPE exchange_id, XTPRI *error_info){
    RETURNONERR1("OnUnSubscribeAllOptionTickByTick");
    XTPPUB1("TickkUnSubAllOpt",knk(1,ki(exchange_id)));        
  }
};

Z CQuoteHandler * pQuoteSpi;

extern "C"{
  K2(initxtpq){
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
    setm(1);
    sd1(p[0],onmq);
    pQuoteApi = XTP::API::QuoteApi::CreateQuoteApi(kK(x)[0]->i,kK(x)[1]->s,(XTP_LOG_LEVEL)kK(x)[2]->i);
    if(NULL==pQuoteApi) R ki(-10004);
          
    pQuoteSpi = new CQuoteHandler();
    pQuoteApi->RegisterSpi(pQuoteSpi);

    pQuoteApi->SetUDPBufferSize(kK(x)[3]->i);
    pQuoteApi->SetHeartBeatInterval(kK(x)[4]->i);
    pQuoteApi->SetUDPSeqLogOutPutFlag(0<kK(x)[5]->g);

    O("[Login](%s,%d,%s,%s,%d)\n",kK(y)[0]->s, kK(y)[1]->i,kK(y)[2]->s,kK(y)[3]->s,(0<kK(y)[4]->i)?XTP_PROTOCOL_TCP:XTP_PROTOCOL_UDP);
    r=pQuoteApi->Login(kK(y)[0]->s, kK(y)[1]->i,kK(y)[2]->s,kK(y)[3]->s,(0<kK(y)[4]->i)?XTP_PROTOCOL_TCP:XTP_PROTOCOL_UDP);
    if(r){errinfo=pQuoteApi->GetApiLastError();mpub(knk(2,ks("LoginFailQ"),knk(3,ki(r),ki(errinfo->error_id),kp(errinfo->error_msg))));R ki(-11000);}
    mpub(knk(2,ks("LoginQ"),knk(2,kp((S)pQuoteApi->GetApiVersion()),kp((S)pQuoteApi->GetTradingDay()))));
    R ki(run);
  }

  K1(freextpq){
    if(!run) R ki(-1);

    pQuoteApi->Logout();
    pQuoteApi->RegisterSpi(NULL);
    pQuoteApi->Release();
    pQuoteApi=NULL;
    delete pQuoteSpi;
    pQuoteSpi=NULL;

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(xtpqrun){
    R ki(run);
  } 
  K1(xtpver){
    R kp((S)pQuoteApi->GetApiVersion());
  }
    
  K1(submkt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllMarketData((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submkt")
    R ki(r);
  }

  K1(unsubmkt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllMarketData((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmkt")
    R ki(r);
  }

  K1(qrymkt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->QueryAllTickers((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"qrymkt")
    R ki(r);
  }

  K2(subsyms){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->SubscribeMarketData(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"subsyms")
    R ki(r);
  }

  K2(unsubsyms){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->UnSubscribeMarketData(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubsyms")
    R ki(r);
  }
  
  K2(qrypxsyms){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->QueryTickersPriceInfo(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"qrysyms")
    R ki(r);
  }
  K2(subsymsbook){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->SubscribeOrderBook(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"subsymsbook")
    R ki(r);
  }

  K2(unsubsymsbook){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->UnSubscribeOrderBook(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubsymsbook")
    R ki(r);
  }
  
  K2(subsymstick){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->SubscribeTickByTick(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"subsymstick")
    R ki(r);
  }

  K2(unsubsymstick){ //([x:market,y:esym list]x->1:SH,2:SZ)
    I r=pQuoteApi->UnSubscribeTickByTick(kS(y),y->n,(XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubsymstick")
    R ki(r);
  }

  K1(submktbook){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllOrderBook((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submktbook")
    R ki(r);
  }

  K1(unsubmktbook){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllOrderBook((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmktbook")
    R ki(r);
  }

  K1(submkttick){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllTickByTick((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submkttick")
    R ki(r);
  }

  K1(unsubmkttick){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllTickByTick((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmkttick")
    R ki(r);
  }


  K1(submktopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllOptionMarketData((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submktopt")
    R ki(r);
  }

  K1(unsubmktopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllOptionMarketData((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmktopt")
    R ki(r);
  }

  K1(submktbookopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllOptionOrderBook((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submktbookopt")
    R ki(r);
  }

  K1(unsubmktbookopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllOptionOrderBook((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmktbookopt")
    R ki(r);
  }

  K1(submkttickopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->SubscribeAllOptionTickByTick((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"submkttickopt")
    R ki(r);
  }

  K1(unsubmkttickopt){ //([x:market]1:SH,2:SZ,3:All)
    I r=pQuoteApi->UnSubscribeAllOptionTickByTick((XTP_EXCHANGE_TYPE)xi);
    XTPPUBERR(r,"unsubmkttickopt")
    R ki(r);
  }
  
  
}
