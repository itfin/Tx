.module.fql2hr:2021.04.06;

txload "core/fqbase";

`initama`freeama`amarun`amaver`sub {x set `extfql2hr 2:(x;y);}' 2 1 1 1 1;

\d .enum
`kNone`kNEEQ`kSHFE`kCFFEX`kDCE`kCZCE`kINE`kSSE`kSZSE`kHKEx`kMax set' 0,(2+til[6]),(101+til[3]),150; /MarketType
`kFailure`kInited`kUnInited`kNullSpi`kSuccess set' (-100+til[4]),0; /ErrorCode
`kMasterSlaveA`kMasterSlaveB`kRegularDataFilter set' til[3]; /HighAvailableMode
`kRDMA`kEXA`kAMI`kTCP`kPCAP`kMDDP set' `long$2 xexp til[6]; /ChannelMode
`kSet`kAdd`kDel`kCancelAll set' til[4]; /SubscribeType
`kSnapshot`kTickExecution`kTickOrder`kOrderQueue`kIndexSnapshot`kFutureSnapshot`kOptionSnapshot`kHKTSnapshot`kAfterHourFixedPriceSnapshot`kAfterHourFixedPriceTickExecution`kCSIIndexSnapshot`kNEEQSnapshot set' `long$2 xexp til[12]; /SubscribeDataType

SnapshotKey:`market_type`security_code`orig_time`trading_phase_code`pre_close_price`open_price`high_price`low_price`last_price`close_price`pb`qb`pa`qa`num_trades`total_volume_trade`total_value_trade`total_bid_volume`total_offer_volume`weighted_avg_bid_price`weighted_avg_offer_price`IOPV`yield_to_maturity`high_limited`low_limited`price_earning_ratio1`price_earning_ratio2`change1`change2`channel_no`md_stream_id`instrument_status`pre_close_iopv`alt_weighted_avg_bid_price`alt_weighted_avg_offer_price`etf_buy_number`etf_buy_amount`etf_buy_money`etf_sell_number`etf_sell_amount`etf_sell_money`total_warrant_exec_volume`war_lower_price`war_upper_price`withdraw_buy_number`withdraw_buy_amount`withdraw_buy_money`withdraw_sell_number`withdraw_sell_amount`withdraw_sell_money`total_bid_number`total_offer_number`bid_trade_max_duration`offer_trade_max_duration`num_bid_orders`num_offer_orders`last_trade_time;
OrderQueueKey:`market_type`security_code`order_time`side`order_price`order_volume`num_of_orders`items`v`channel_no`md_stream_id;
TickExecutionKey:`market_type`security_code`exec_time`channel_no`appl_seq_num`exec_price`exec_volume`value_trade`bid_appl_seq_num`offer_appl_seq_num`side`exec_type`md_stream_id`biz_index;
TickOrderKey:`market_type`security_code`channel_no`appl_seq_num`order_time`order_price`order_volume`side`order_type`md_stream_id`orig_order_no`biz_index;
IndexSnapshotKey:`market_type`security_code`orig_time`trading_phase_code`pre_close_index`open_index`high_index`low_index`last_index`close_index`total_volume_trade`total_value_trade`channel_no`md_stream_id;
OptionSnapshotKey:`market_type`security_code`orig_time`pre_settle_price`pre_close_price`open_price`auction_price`auction_volume`high_price`low_price`last_price`close_price`high_limited`low_limited`pb`qb`pa`qa`settle_price`total_long_position`total_volume_trade`total_value_trade`trading_phase_code`channel_no`md_stream_id`last_trade_time`ref_price;
FutureSnapshotKey:`market_type`security_code`action_day`orig_time`exchange_inst_id`last_price`pre_settle_price`pre_close_price`pre_open_interest`open_price`high_price`low_price`total_volume_trade`total_value_trade`open_interest`close_price`settle_price`high_limited`low_limited`pre_delta`curr_delta`pb`qb`pa`qa`average_price`trading_day;
HKTSnapshotKey:`market_type`security_code`orig_time`pre_close_price`nominal_price`high_price`low_price`last_price`pb`qb`pa`qa`total_volume_trade`total_value_trade`trading_phase_code`channel_no`md_stream_id`ref_price`high_limited`low_limited`bid_price_limit_up`bid_price_limit_down`offer_price_limit_up`offer_price_limit_down;

exmap:101 102 103 3 4 5 6 7i!`XSHG`XSHE`XHKG`XSGE`CCFX`XDCE`XZCE`XINE;

loglevel:til[6]!`debug`debug`info`warn`error`error; /LogLevel
evtlevel:1 2 3!`info`warn`error; /EventLevel
evtcode:(1+til[30])!`kUMSConnectSuccess`kUMSConnectFailed`kUMSLogonSuccess`kUMSLogonFailed`kUMSHeartbeatTimeout`kChannelRDMAInitSuccess`kChannelRDMAInitFailed`kChannelEXAInitSuccess`kChannelEXAInitFailed`kChannelPCAPInitSuccess`kChannelPCAPInitFailed`kCTPDASStreamStart`kCTPDASStreamFinished`kSzseBinaryDASStreamStart`kSzseBinaryDASStreamFinished`kSseLDDSDASStreamStart`kSseLDDSDASStreamFinished`kChannelAMIInitSuccess`kChannelAMIInitFailed`kChannelTCPInitSuccess`kChannelTCPInitFailed`kChannelTCPConnectSuccess`kChannelTCPConnectFailed`kChannelTCPLogonSuccess`kChannelTCPLogonFailed`kChannelTCPSessionClosed`kChannelTCPHeartbeatTimeout`kChannelTCPMarketDataDegrade`kChannelTCPMarketDataUpgrade`kSourceMasterSlaveChanged;

\d .

\d .temp
L2M:L2O:L2Q:QREF:QUEUE:L18:L17:L16:L15:L14:L13:L12:L11:L10:L:C:();TKSub:BKSub:MDSub:()!();
\d .

quotetbl:$[1b~.conf[`usel2quote];`l2quote;`quote];

.ctrl.l2hr:.enum.nulldict;

onl2hr:{[x]if[.conf.l2hr.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};


l2hrconn:{[x;y]if[not any .z.T within/: .conf.l2hr.openrange;:()];if[1i~.ctrl.l2hr[`runQ];:()];.ctrl.l2hr[`conntimeQ`AMAVersion]:(.z.P;amaver[]);.ctrl.l2hr[`runQ]:r:initama[.conf.l2hr`user`pass`servercnt`localip`serverip`serverport`subscribe_full`thread_safe`loglevel`channel_mode`tcp_compress_mode`ha_mode`output_mon_data`keep_order`keep_order_timeout_ms;()];1b};

l2hrdisc:{[x;y]if[any .z.T within/: .conf.l2hr.openrange;:()];if[1i~.ctrl.l2hr[`runQ];:()];.ctrl.l2hr[`runQ]:freeama[];if[((.z.D>d0)|(.z.T>.conf.l2hr.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b};

.init.fql2hr:{[x]l2hrconn[`;.z.P];};
.exit.fql2hr:{[x].ctrl.l2hr[`runQ]:freeama[];};

.timer.fql2hr:{[x]if[any .z.T within/:.conf.l2hr.openrange;dosubscribe[]];batchpub[];batchpubl2[];};

dosubscribe:{[]if[(1b~.ctrl.l2hr`SubscribeQ)|(not 1i~.ctrl.l2hr`runQ);:()];r:1b;if[(not .conf.l2hr`subscribe_full)&0<count[sl:.conf.l2hr`subs];r:sub each sl];.ctrl.l2hr[`SubscribeQ`SubscribeTimeQ`SubscribeResult]:(1b;.z.P;r);};

.upd.Log:{[x]wlog[.enum.loglevel x 0;`amalog;x[1]];};

.upd.Indicator:{[x];};

.upd.Event:{[x]wlog[.enum.evtlevel x 0;.enum.evtcode x 1;x[2]];};

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,pxunit,qtylot,qtyminl,qtymins from .db.QX where date1=.z.D;pubm[`ALL;`RDUpdate;`l2hr;string path];};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[quotetbl;.temp.QUEUE];.temp.QUEUE:()};

enqueuel2:{[t;x]$[t=`Q;.temp.L2Q,:x;t=`O;.temp.L2O,:x;.temp.L2M,:x];};
enqueuel2q:enqueuel2[`Q];enqueuel2o:enqueuel2[`O];enqueuel2m:enqueuel2[`M];
batchpubl2:{[]if[(not 1b~.conf.batchpubl2);:()];if[0<count .temp.L2Q;pub[`l2queue;.temp.L2Q];.temp.L2Q:()];if[0<count .temp.L2O;pub[`l2order;.temp.L2O];.temp.L2O:()];if[0<count .temp.L2M;pub[`l2match;.temp.L2M];.temp.L2M:()];};

.upd.MDSnapshot:{[x].temp.x11:x;y:flip .enum.SnapshotKey!flip x;if[.conf.l2hr.debug;.temp.L11,:y];t0:sum dt:"DT"$0 8 cut string y[0;`orig_time];if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0:dt[0];pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];d:select sym:{[x;y]`$x,".",string y}'[security_code;.enum.exmap market_type],time:dt[1],price:1e-6*last_price,cumqty:1e-2*total_volume_trade,vwap:1e-3*total_value_trade%total_volume_trade,high:1e-6*high_price,low:1e-6*low_price,bid:1e-6*first each pb,ask:1e-6*first each pa,bsize:1e-2*first each qb,asize:1e-2*first each qa,bidQ:1e-6*(10#) each pb,askQ:1e-6*(10#) each pa,bsizeQ:1e-2*(10#) each qb,asizeQ:1e-2*(10#) each qa,openint:`float$num_trades,settlepx:1e-6*IOPV,open:1e-6*open_price,pc:1e-6*pre_close_price,sup:1e-6*high_limited,inf:1e-6*low_limited,mode:`$trading_phase_code,recvtime:.z.P,extime:{[x]sum "DT"$0 8 cut string x} each orig_time from y;d:delete from d where (0>cumqty);if[count d;if[.conf.l2hr.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime,bidQ,askQ,bsizeQ,asizeQ,quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[quotetbl;d2]]];};

.upd.MDIndexSnapshot:{[x].temp.x10:x;y:flip .enum.IndexSnapshotKey!flip x;if[.conf.l2hr.debug;.temp.L10,:y];.upd.MDSnapshot {(10#x),(4#enlist `long$()),0N,x[10 11],(12#0N),x[12 13],enlist[""],(20#0N),(4#0Ni),0N} each x;};

.upd.MDOptionSnapshot:{[x].temp.x16:x;y:flip .enum.OptionSnapshotKey!flip x;if[.conf.l2hr.debug;.temp.L16,:y];.upd.MDSnapshot {(10#x),(4#enlist `long$()),0N,x[10 11],(12#0N),x[12 13],enlist[""],(20#0N),(4#0Ni),0N} each x;};

.upd.MDFutureSnapshot:{[x].temp.x17:x;y:flip .enum.FutureSnapshotKey!flip x;if[.conf.l2hr.debug;.temp.L17,:y];.upd.MDSnapshot {(10#x),(4#enlist `long$()),0N,x[10 11],(12#0N),x[12 13],enlist[""],(20#0N),(4#0Ni),0N} each x;};

.upd.MDHKTSnapshot:{[x].temp.x18:x;y:flip .enum.HKTSnapshotKey!flip x;if[.conf.l2hr.debug;.temp.L18,:y];.upd.MDSnapshot {(10#x),(4#enlist `long$()),0N,x[10 11],(12#0N),x[12 13],enlist[""],(20#0N),(4#0Ni),0N} each x;};

.upd.MDOrderQueue:{[x].temp.x13:x;y:flip .enum.OrderQueueKey!flip x;if[.conf.l2hr.debug;.temp.L13,:y];d:select sym:{[x;y]`$x,".",string y}'[security_code;.enum.exmap market_type],side,price:1e-6*order_price,size:1e-2*order_volume,num:`long$num_of_orders,qtyQ:1e-2*items#'v,extime:{[x]sum "DT"$0 8 cut string x} each order_time from y;$[1b~.conf.batchpubl2;enqueuel2q[d];pub[`l2queue;d]];};

.upd.MDTickOrder:{[x].temp.x14:x;y:flip .enum.TickOrderKey!flip x;if[.conf.l2hr.debug;.temp.L14,:y];d:select sym:{[x;y]`$x,".",string y}'[security_code;.enum.exmap market_type],side,typ:order_type,price:1e-6*order_price,qty:1e-2*order_volume,gid:channel_no,oid:appl_seq_num,origid:orig_order_no,bizidx:biz_index,extime:{[x]sum "DT"$0 8 cut string x} each order_time from y;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};

.upd.MDTickExecution:{[x].temp.x15:x;y:flip .enum.TickExecutionKey!flip x;if[.conf.l2hr.debug;.temp.L15,:y];d:select sym:{[x;y]`$x,".",string y}'[security_code;.enum.exmap market_type],side,typ:exec_type,price:1e-6*exec_price,qty:1e-2*exec_volume,amt:1e-5*value_trade,gid:channel_no,mid:appl_seq_num,bid:bid_appl_seq_num,aid:offer_appl_seq_num,bizidx:biz_index,extime:{[x]sum "DT"$0 8 cut string x} each exec_time from y;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};

