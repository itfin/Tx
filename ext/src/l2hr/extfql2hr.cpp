#include "kcomm.h"
#include <queue>

#include <ama.h>

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
  k(0,"onl2hr",L,(K)0);
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
  //k(-c,"onl2hr",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};

class CQuoteHandler : public amd::ama::IAMDSpi{
public:
    // 定义日志回调处理方法
  virtual void OnLog(const int32_t& level,const char* log,uint32_t len) override{mpub(knk(2,ks("Log"),knk(2,ki(level),kpn((S)log,len))));}

    // 定义监控回调处理方法
  virtual void OnIndicator(const char* indicator,uint32_t len) override{mpub(knk(2,ks("Indicator"),knk(2,kpn((S)indicator,len),ki(0))));}

    // 定义事件回调处理方法  level 对照 EventLevel 数据类型 code 对照 EventCode 数据类型
  virtual void OnEvent(uint32_t level, uint32_t code, const char* event_msg, uint32_t len) override{mpub(knk(2,ks("Event"),knk(3,ki(level),ki(code),kpn((S)event_msg,len))));}

    // 定义快照数据回调处理方法
  virtual void OnMDSnapshot(amd::ama::MDSnapshot* p0,uint32_t cnt) override {
    amd::ama::MDSnapshot* p=p0;
    K L=knk(0);    
	
    for (uint32_t _i = 0; _i < cnt; ++_i){
      K pa=ktn(KJ,10),qa=ktn(KJ,10),pb=ktn(KJ,10),qb=ktn(KJ,10);
      DO(10,kJ(pa)[i]=p->offer_price[i];kJ(qa)[i]=p->offer_volume[i];kJ(pb)[i]=p->bid_price[i];kJ(qb)[i]=p->bid_volume[i]);
	  
      jk(&L,knk(57,ki(p->market_type),kp(p->security_code),kj(p->orig_time),kp(p->trading_phase_code),kj(p->pre_close_price),kj(p->open_price),kj(p->high_price),kj(p->low_price),kj(p->last_price),kj(p->close_price),pb,qb,pa,qa,kj(p->num_trades),kj(p->total_volume_trade),kj(p->total_value_trade),kj(p->total_bid_volume),kj(p->total_offer_volume),kj(p->weighted_avg_bid_price),kj(p->weighted_avg_offer_price),kj(p->IOPV),kj(p->yield_to_maturity),kj(p->high_limited),kj(p->low_limited),kj(p->price_earning_ratio1),kj(p->price_earning_ratio2),kj(p->change1),kj(p->change2),ki(p->channel_no),kp(p->md_stream_id),kp(p->instrument_status),kj(p->pre_close_iopv),kj(p->alt_weighted_avg_bid_price),kj(p->alt_weighted_avg_offer_price),kj(p->etf_buy_number),kj(p->etf_buy_amount),kj(p->etf_buy_money),kj(p->etf_sell_number),kj(p->etf_sell_amount),kj(p->etf_sell_money),kj(p->total_warrant_exec_volume),kj(p->war_lower_price),kj(p->war_upper_price),kj(p->withdraw_buy_number),kj(p->withdraw_buy_amount),kj(p->withdraw_buy_money),kj(p->withdraw_sell_number),kj(p->withdraw_sell_amount),kj(p->withdraw_sell_money),kj(p->total_bid_number),kj(p->total_offer_number),ki(p->bid_trade_max_duration),ki(p->offer_trade_max_duration),ki(p->num_bid_orders),ki(p->num_offer_orders),kj(p->last_trade_time)));
      p++;
    }
    mpub(knk(2,ks("MDSnapshot"),L));
        /* 手动释放数据内存, 否则会造成内存泄露 */
        amd::ama::IAMDApi::FreeMemory(p0);
  }

  virtual void OnMDIndexSnapshot(amd::ama::MDIndexSnapshot* p0, uint32_t cnt)  override{
    amd::ama::MDIndexSnapshot* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      jk(&L,knk(14,ki(p->market_type),kp(p->security_code),kj(p->orig_time),kp(p->trading_phase_code),kj(p->pre_close_index),kj(p->open_index),kj(p->high_index),kj(p->low_index),kj(p->last_index),kj(p->close_index),kj(p->total_volume_trade),kj(p->total_value_trade),ki(p->channel_no),kp(p->md_stream_id)));
      p++;
    }
    
    mpub(knk(2,ks("MDIndexSnapshot"),L));
    amd::ama::IAMDApi::FreeMemory(p0);
  }

  // 定义逐笔成交数据回调处理方法
  virtual void OnMDTickExecution(amd::ama::MDTickExecution* p0,uint32_t cnt) override{
    amd::ama::MDTickExecution* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      jk(&L,knk(14,ki(p->market_type),kp(p->security_code),kj(p->exec_time),ki(p->channel_no),kj(p->appl_seq_num),kj(p->exec_price),kj(p->exec_volume),kj(p->value_trade),kj(p->bid_appl_seq_num),kj(p->offer_appl_seq_num),kc(p->side),kc(p->exec_type),kp(p->md_stream_id),kj(p->biz_index)));	  
      p++;
    }
    mpub(knk(2,ks("MDTickExecution"),L));
	     
        /* 手动释放数据内存, 否则会造成内存泄露 */
    amd::ama::IAMDApi::FreeMemory(p0);
  }

  virtual void OnMDTickOrder(amd::ama::MDTickOrder* p0, uint32_t cnt) override{
    amd::ama::MDTickOrder* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      jk(&L,knk(12,ki(p->market_type),kp(p->security_code),ki(p->channel_no),kj(p->appl_seq_num),kj(p->order_time),kj(p->order_price),kj(p->order_volume),kc(p->side),kc(p->order_type),kp(p->md_stream_id),kj(p->orig_order_no),kj(p->biz_index)));
      p++;
    }

    mpub(knk(2,ks("MDTickOrder"),L));
    amd::ama::IAMDApi::FreeMemory(p0);
  }
  
  
  virtual void OnMDOrderQueue(amd::ama::MDOrderQueue* p0, uint32_t cnt) override{
    amd::ama::MDOrderQueue* p=p0;
    K L=knk(0);    
    for (uint32_t _i = 0; _i < cnt; ++_i){
      K v=ktn(KJ,50);
      DO(50,kJ(v)[i]=p->volume[i]);
      jk(&L,knk(11,ki(p->market_type),kp(p->security_code),kj(p->order_time),kc(p->side),kj(p->order_price),kj(p->order_volume),ki(p->num_of_orders),ki(p->items),v,ki(p->channel_no),kp(p->md_stream_id)));
      p++;
    }
    mpub(knk(2,ks("MDOrderQueue"),L));
    amd::ama::IAMDApi::FreeMemory(p0);
  }
  
  virtual void OnMDOptionSnapshot(amd::ama::MDOptionSnapshot* p0, uint32_t cnt)  override{
    amd::ama::MDOptionSnapshot* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->offer_price[i];kJ(qa)[i]=p->offer_volume[i];kJ(pb)[i]=p->bid_price[i];kJ(qb)[i]=p->bid_volume[i]);
	  
      jk(&L,knk(27,ki(p->market_type),kp(p->security_code),kj(p->orig_time),kj(p->pre_settle_price),kj(p->pre_close_price),kj(p->open_price),kj(p->auction_price),kj(p->auction_volume),kj(p->high_price),kj(p->low_price),kj(p->last_price),kj(p->close_price),kj(p->high_limited),kj(p->low_limited),pb,qb,pa,qa,kj(p->settle_price),kj(p->total_long_position),kj(p->total_volume_trade),kj(p->total_value_trade),kp(p->trading_phase_code),ki(p->channel_no),kp(p->md_stream_id),kj(p->last_trade_time),kj(p->ref_price)));
      p++;
    }

    mpub(knk(2,ks("MDOptionSnapshot"),L));
    amd::ama::IAMDApi::FreeMemory(p0);
  }

  virtual void OnMDFutureSnapshot(amd::ama::MDFutureSnapshot* p0, uint32_t cnt)  override{
    amd::ama::MDFutureSnapshot* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->offer_price[i];kJ(qa)[i]=p->offer_volume[i];kJ(pb)[i]=p->bid_price[i];kJ(qb)[i]=p->bid_volume[i]);
	  
      jk(&L,knk(27,ki(p->market_type),kp(p->security_code),ki(p->action_day),kj(p->orig_time),kp(p->exchange_inst_id),kj(p->last_price),kj(p->pre_settle_price),kj(p->pre_close_price),kj(p->pre_open_interest),kj(p->open_price),kj(p->high_price),kj(p->low_price),kj(p->total_volume_trade),kj(p->total_value_trade),kj(p->open_interest),kj(p->close_price),kj(p->settle_price),kj(p->high_limited),kj(p->low_limited),kj(p->pre_delta),kj(p->curr_delta),pb,qb,pa,qa,kj(p->average_price),ki(p->trading_day)));

      p++;
    }

    mpub(knk(2,ks("MDFutureSnapshot"),L));
    
    amd::ama::IAMDApi::FreeMemory(p0);
  }

  virtual void OnMDHKTSnapshot(amd::ama::MDHKTSnapshot* p0, uint32_t cnt)  override{
    amd::ama::MDHKTSnapshot* p=p0;
    K L=knk(0);    

    for (uint32_t _i = 0; _i < cnt; ++_i){
      K pa=ktn(KJ,5),qa=ktn(KJ,5),pb=ktn(KJ,5),qb=ktn(KJ,5);
      DO(5,kJ(pa)[i]=p->offer_price[i];kJ(qa)[i]=p->offer_volume[i];kJ(pb)[i]=p->bid_price[i];kJ(qb)[i]=p->bid_volume[i]);
	  
      jk(&L,knk(24,ki(p->market_type),kp(p->security_code),kj(p->orig_time),kj(p->pre_close_price),kj(p->nominal_price),kj(p->high_price),kj(p->low_price),kj(p->last_price),pb,qb,pa,qa,kj(p->total_volume_trade),kj(p->total_value_trade),kp(p->trading_phase_code),ki(p->channel_no),kp(p->md_stream_id),kj(p->ref_price),kj(p->high_limited),kj(p->low_limited),kj(p->bid_price_limit_up),kj(p->bid_price_limit_down),kj(p->offer_price_limit_up),kj(p->offer_price_limit_down)));
      p++;
    }

    mpub(knk(2,ks("MDHKTSnapshot"),L));
    amd::ama::IAMDApi::FreeMemory(p0);
  }
};


Z CQuoteHandler QuoteSpi;

extern "C"{
  K2(initama){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];
    amd::ama::Cfg cfg; // 准备AMA配置

      
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
    
    strcpy(cfg.username, kK(x)[0]->s);
    strcpy(cfg.password, kK(x)[1]->s);
    
    cfg.ums_server_cnt = kK(x)[2]->i;
    DO(cfg.ums_server_cnt,strcpy(cfg.ums_servers[i].local_ip, kS(kK(x)[3])[i]);strcpy(cfg.ums_servers[i].server_ip,kS(kK(x)[4])[i]);cfg.ums_servers[i].server_port = kI(kK(x)[5])[i]);

    cfg.is_subscribe_full = 0<kK(x)[6]->g; //设置默认订阅: true 代表默认全部订阅, false 代表默认全部不订阅
    cfg.is_thread_safe = 0<kK(x)[7]->g;
    cfg.min_log_level = kK(x)[8]->i; // 设置日志最小级别：Info级, AMA内部日志通过 OnLog 回调函数返回

    cfg.channel_mode = kK(x)[9]->j; //amd::ama::ChannelMode::kTCP
    cfg.tcp_compress_mode = kK(x)[10]->i;  //TCP传输数据方式: 0 不压缩 1 华锐自定义压缩 2 zstd压缩(仅TCP模式有效)
    
    cfg.ha_mode =kK(x)[11]->i;
    
    cfg.is_output_mon_data = 0<kK(x)[12]->g;   
    cfg.keep_order = 0<kK(x)[13]->g;
    cfg.keep_order_timeout_ms =kK(x)[14]->i;
    
    if (amd::ama::IAMDApi::Init(&QuoteSpi, cfg)!= amd::ama::ErrorCode::kSuccess){
        amd::ama::IAMDApi::Release();
        R ki(-10010);
    }

    
    R ki(run);
  }

  K1(freeama){
    if(!run) R ki(-1);

    amd::ama::IAMDApi::Release();

    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }

  K1(amarun){
    R ki(run);
  } 

  K1(amaver){
    R kp((S)amd::ama::IAMDApi::GetVersion());
  } 

  K1(sub){ //
    amd::ama::SubscribeItem sub[1];
    memset(sub, 0, sizeof(sub));

    sub[0].market = kK(x)[1]->i;
    sub[0].flag =kK(x)[2]->j;
    strcpy(sub[0].security_code,kK(x)[3]->s);
    
    R ki(amd::ama::IAMDApi::SubscribeData(kK(x)[0]->i,sub,1));
  }  
  
}
