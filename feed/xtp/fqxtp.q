.module.fqxtp:2023.06.10;

txload "core/fqbase";
txload "feed/xtp/xtpbase";

`initxtpq`freextpq`xtpqrun`xtpver`submkt`unsubmkt`qrymkt`submktbook`unsubmktbook`submkttick`unsubmkttick`submktopt`unsubmktopt`submktbookopt`unsubmktbookopt`submkttickopt`unsubmkttickopt`subsyms`unsubsyms`qrypxsyms`subsymsbook`unsubsymsbook`subsymstick`unsubsymstick {x set `extfqxtp 2:(x;y);}' 2 1 1 1,(13#1),7#2;
\d .enum
`XTP_TBT_ENTRUST`XTP_TBT_TRADE set' 1 2i; /XTP_TBT_TYPE:1(逐笔委托)2(逐笔成交)
`XTP_MARKETDATA_V2_INDEX`XTP_MARKETDATA_V2_OPTION`XTP_MARKETDATA_V2_ACTUAL`XTP_MARKETDATA_V2_BOND set' til 4;
XTPMDKey:`exchange_id`ticker`last_price`pre_close_price`open_price`high_price`low_price`close_price`pre_total_long_positon`total_long_positon`pre_settl_price`settl_price`upper_limit_price`lower_limit_price`pre_delta`curr_delta`data_time`qty`turnover`avg_price`bp`ap`bq`aq`b1`a1`bm`am`trades_count`ticker_status;
XTPMDStk:XTPMDKey,`total_bid_qty`total_ask_qty`ma_bid_price`ma_ask_price`ma_bond_bid_price`ma_bond_ask_price`yield_to_maturity`iopv`etf_buy_count`etf_sell_count`etf_buy_qty`etf_buy_money`etf_sell_qty`etf_sell_money`total_warrant_exec_qty`warrant_lower_price`warrant_upper_price`cancel_buy_count`cancel_sell_count`cancel_buy_qty`cancel_sell_qty`cancel_buy_money`cancel_sell_money`total_buy_count`total_sell_count`duration_after_buy`duration_after_sell`num_bid_orders`num_ask_orders`pre_iopv`r1`r2;
XTPMDOpt:XTPMDKey,`auction_price`auction_qty`last_enquiry_time;
\d .

.enum.xtpexQ:mirror .enum.exxtpQ:1 2 3i!`XSHG`XSHE`BOTH; 
.enum.acxtp:0 1 2 3 4 5 6i!`AShare`Index`Fund`Bond`Option`TShare`Unknown;

\d .temp
L2M:L2O:L2Q:QREF:QUEUE:L16:L15:L14:L13:L12:L11:L10:L:C:();TKSub:BKSub:MDSub:()!();
\d .

quotetbl:$[1b~.conf[`usel2quote];`l2quote;`quote];

xtpqconn:{[x;y]if[not any .z.T within/: .conf.xtp.openrange;:()];if[1i~.ctrl.xtp[`runQ];:()];.ctrl.xtp[`conntimeQ]:.z.P;.ctrl.xtp[`runQ]:r:initxtpq[(.conf.xtp.cltid;.conf.xtp.tmpath;`int$`fatal`error`warning`info`debug`trace?.conf.xtp.loglevel;.conf.xtp.bufsize;.conf.xtp.hbint;.conf.xtp.udpseq);(.conf.xtp.qsvrip;.conf.xtp.qsport;.conf.xtp.user;.conf.xtp.pass;.conf.xtp.usetcp)];1b;};
xtpqdisc:{[x;y]if[any .z.T within/: .conf.xtp.openrange;:()];if[not 1i~.ctrl.xtp[`runQ];:()];.ctrl.xtp[`runQ]:freextpq[];if[((.z.D>d0)|(.z.T>.conf.xtp.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b;};

.init.fqxtp:{[x]xtpqconn[`;.z.P];.ctrl.xtp[`inittime]:.z.P;};
.exit.fqxtp:{[x].ctrl.xtp[`runQ]:freextpq[];};

.timer.fqxtp:{[x]if[any .z.T within/:.conf.xtp.openrange;dosubscribe[]];batchpub[];batchpubl2[];};

dosubscribe:{[]if[(1b~.ctrl.xtp`SubscribeQ)|(not 1b~.ctrl.xtp`LoginQ)|(not 1b~.ctrl.xtp`TickEndQ);:()];sl:.conf.xtpsymlist;$[0=count sl;[submkt[3i];submkttick[3i];submktbook[3i]];[if[0<count sl1:sl where `XSHG=fs2e each sl;subsyms[1i;fs2s each sl1];subsymstick[1i;fs2s each sl1];subsymsbook[1i;fs2s each sl1]];if[0<count sl2:sl where `XSHE=fs2e each sl;subsyms[2i;fs2s each sl2];subsymstick[2i;fs2s each sl2];subsymsbook[2i;fs2s each sl2]]]];.ctrl.xtp[`SubscribeQ`SubscribeTimeQ]:(1b;.z.P);};

.upd.DisconnectedQ:{[x].ctrl.xtp[`ConnectQ`LoginQ`TickEndQ`SubscribeQ`DiscReasonQ`DisctimeQ]:(0b;0b;0b;0b;x[0];.z.P);};

.upd.LoginFailQ:{[x].ctrl.xtp[`LoginQ`LoginTimeQ`LoginErrQ`ErrCodeQ`ErrMsgQ]:(0b;.z.P),x;}; 
.upd.LoginQ:{[x].ctrl.xtp[`LoginQ`logintimeQ`ApiVersionQ`TradingDayQ]:(1b;.z.P),x;qrymkt[1i];qrymkt[2i];};

.upd.XTPErrorQ:{[x].ctrl.xtp[`ErrTimeQ`ErrLastQ`ErrCodeQ`ErrMsgQ`ErrLastQ]:.z.P,x;};

.upd.Ticker:{[x].temp.X1:x;y:`exchange_id`ticker`ticker_name`ticker_type`pre_close_price`upper_limit_price`lower_limit_price`price_tick`buy_qty_unit`sell_qty_unit!x[1];s:`$y`ticker;e:.enum.exxtpQ y`exchange_id;.db.QX[sv[`] s,e;`date1`ex`esym`name`assetclass`pc`sup`inf`pxunit`qtyminl`qtymins`qtylot]:(.z.D;e;s;`$y`ticker_name;.enum.acxtp y`ticker_type),(y`pre_close_price`upper_limit_price`lower_limit_price`price_tick),`float$y`buy_qty_unit`sell_qty_unit`sell_qty_unit;if[x[0];.ctrl.xtp[sv[`] `TickEnd,e]:1b];if[(1b~.ctrl.xtp[`TickEnd.XSHG])&(1b~.ctrl.xtp[`TickEnd.XSHE]);.ctrl.xtp[`TickEndQ]:1b;updaterd[]];}; 

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,pxunit,qtylot,qtyminl,qtymins from .db.QX where date1=.z.D;pubm[`ALL;`RDUpdate;`xtp;string path];};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[quotetbl;.temp.QUEUE];.temp.QUEUE:()};

enqueuel2:{[t;x]$[t=`Q;.temp.L2Q,:x;t=`O;.temp.L2O,:x;.temp.L2M,:x];};
enqueuel2q:enqueuel2[`Q];enqueuel2o:enqueuel2[`O];enqueuel2m:enqueuel2[`M];
batchpubl2:{[]if[(not 1b~.conf.batchpubl2);:()];if[0<count .temp.L2Q;pub[`l2queue;.temp.L2Q];.temp.L2Q:()];if[0<count .temp.L2O;pub[`l2order;.temp.L2O];.temp.L2O:()];if[0<count .temp.L2M;pub[`l2match;.temp.L2M];.temp.L2M:()];};

.upd.DepthMD:{[x].temp.X:x;y:.enum[`XTPMDStk]!1_x;if[.conf.xtp.debug;.temp.L11,:enlist y];t0:sum dt:"DT"$0 8 cut string y`data_time;if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0:dt[0];pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from select sym:{[x;y]`$x,'".",/:string y}[ticker;.enum.exxtpQ exchange_id],time:dt[1],price:last_price,cumqty:`float$qty,vwap:turnover%`float$qty,high:high_price,low:low_price,bid:first each bp,ask:first each ap,bsize:first each bq,asize:first each aq,bidQ:bp,askQ:ap,bsizeQ:bq,asizeQ:aq,openint:settl_price,settlepx:iopv,open:open_price,pc:pre_close_price,sup:upper_limit_price,inf:lower_limit_price,mode:`$ticker_status,recvtime:.z.P,exlocaltime:.z.P,b1,a1,bm,am,tnum:trades_count,bnum:total_buy_count,bqty:`float$total_bid_qty,bwap:ma_bid_price,bcnum:`long$cancel_buy_count,bcqty:cancel_buy_qty,bcamt:cancel_buy_money,bpnum:`long$num_bid_orders,bwtime:`time$duration_after_buy,anum:total_sell_count,aqty:`float$total_ask_qty,awap:ma_ask_price,acnum:`long$cancel_sell_count,acqty:cancel_sell_qty,acamt:cancel_sell_money,apnum:`long$num_ask_orders,awtime:`time$duration_after_sell,ebnum:`long$etf_buy_count,ebqty:etf_buy_qty,ebamt:etf_buy_money,esnum:`long$etf_sell_count,esqty:etf_sell_qty,esamt:etf_sell_money,yield:yield_to_maturity,execqty:total_warrant_exec_qty,winf:warrant_lower_price,wsup:warrant_upper_price,bbwap:ma_bond_bid_price,bawap:ma_bond_ask_price from enlist y;d:delete from d where (0>cumqty);if[count d;if[.conf.xtp.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d3:select sym,bid,ask,bsize,asize,bm,am,b1,a1,extime:t0 from d where 0<bm|am;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime:t0,bidQ,askQ,bsizeQ,asizeQ,quoopt:n#enlist "",tnum,b0num:bm,b0qtyQ:b1,bnum,bqty,bwap,bcnum,bcqty,bcamt,bpnum,bwtime,a0num:am,a0qtyQ:a1,anum,aqty,awap,acnum,acqty,acamt,apnum,awtime,ebnum,ebqty,ebamt,esnum,esqty,esamt,yield,execqty,winf,wsup,bbwap,bawap,flag:` from d;$[1b~.conf.batchpub;enqueue[d2];pub[quotetbl;d2]]];if[0=count d3;:()];d4:(select sym,side:.enum.BUY,price:bid,size:bsize,num:`long$bm,qtyQ:b1,extime from d3),select sym,side:.enum.SELL,price:ask,size:asize,num:`long$am,qtyQ:a1,extime from d3;$[1b~.conf.batchpubl2;enqueuel2q[d4];pub[`l2queue;d4]];}; /d:delete open,pc,sup,inf,b1,a1,bm,am,extime from d;

.upd.DepthMDOpt:{[x]temp.X1:x;t:x[0];x:1_x;y:(.enum``XTPMDOpt!x),`yield_to_maturity`iopv!0n 0n;}

.upd.Price:{[x]b:x[0];x:x[1];if[.conf.xtp.debug;.temp.L13,:enlist y:`exchange_id`ticker`last_price!x];};
.upd.Book:{[x]if[.conf.xtp.debug;.temp.L16,:enlist y:`exchange_id`ticker`last_price`qty`turnover`trades_count`bp`ap`bq`aq`data_time!x];};

.upd.TickOrder:{[x].temp.x1:x;t:x[0];x:1_x;y:`exchange_id`ticker`seq`data_time`channel_no`seq1`price`qty`side`ord_type`order_no!x;if[.conf.xtp.debug;.temp.L14,:enlist y];d:select sym:{[x;y]`$x,'".",/:string y}[ticker;.enum.exxtpQ exchange_id],side,typ:ord_type,price,`float$qty,gid:channel_no,oid:seq1,origid:order_no,bizidx:0N,extime:{[x]sum "DT"$0 8 cut string x} each data_time,flag:` from enlist y;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};

.upd.TickMatch:{[x]t:x[0];x:1_x;y:`exchange_id`ticker`seq`data_time`channel_no`seq1`price`qty`money`bid_no`ask_no`trade_flag!x;if[.conf.xtp.debug;.temp.L15,:enlist y];d:select sym:{[x;y]`$x,'".",/:string y}[ticker;.enum.exxtpQ exchange_id],side:.enum.NULL,typ:trade_flag,price,`float$qty,amt:money,gid:channel_no,mid:seq1,bid:bid_no,aid:ask_no,bizidx:seq,extime:{[x]sum "DT"$0 8 cut string x} each data_time,flag:` from enlist y;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};

.upd.MDSub:{[x]x:x[1];.temp.MDSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:1b;};
.upd.MDUnSub:{[x]x:x[1];.temp.MDSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:0b;};

.upd.BookSub:{[x]x:x[1];.temp.BKSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:1b;};
.upd.BookUnSub:{[x]x:x[1];.temp.BKSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:0b;};

.upd.TickSub:{[x]x:x[1];.temp.TKSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:1b;};
.upd.TickUnSub:{[x]x:x[1];.temp.TKSub[sv[`] (`$x[1]),.enum.exxtpQ x[0]]:0b;};

.upd.MDSubAll:{[x].temp.MDSub[.enum.exxtpQ x[0]]:1b;};
.upd.MDUnSubAll:{[x].temp.MDSub[.enum.exxtpQ x[0]]:0b;};

.upd.BookSubAll:{[x].temp.BKSub[.enum.exxtpQ x[0]]:1b;};
.upd.BookUnSubAll:{[x].temp.BKSub[.enum.exxtpQ x[0]]:0b;};

.upd.TickSubAll:{[x].temp.TKSub[.enum.exxtpQ x[0]]:1b;};
.upd.TickUnSubAll:{[x].temp.TKSub[.enum.exxtpQ x[0]]:0b;};

.upd.MDSubAllOpt:{[x].temp.MDSub[sv[`] `OPT,.enum.exxtpQ x[0]]:1b;};
.upd.MDUnSubAllOpt:{[x].temp.MDSub[sv[`] `OPT,.enum.exxtpQ x[0]]:0b;};

.upd.BookSubAllOpt:{[x].temp.BKSub[sv[`] `OPT,.enum.exxtpQ x[0]]:1b;};
.upd.BookUnSubAllOpt:{[x].temp.BKSub[sv[`] `OPT,.enum.exxtpQ x[0]]:0b;};

.upd.TickSubAllOpt:{[x].temp.TKSub[sv[`] `OPT,.enum.exxtpQ x[0]]:1b;};
.upd.TickUnSubAllOpt:{[x].temp.TKSub[sv[`] `OPT,.enum.exxtpQ x[0]]:0b;};

.upd.Resub:{[x]sl:where .temp.MDSub;if[0<count sl1:sl where `XSHG=fs2e each sl;sl1s:fs2s each sl1;unsubsyms[1i;sl1s];unsubsymstick[1i;sl1s];unsubsymsbook[1i;sl1s]];if[0<count sl2:sl where `XSHE=fs2e each sl;sl2s:fs2s each sl2;unsubsyms[2i;sl2s];unsubsymstick[2i;sl2s];unsubsymsbook[2i;sl2s]];sl:-9!x`vbin;if[0<count sl1:sl where `XSHG=fs2e each sl;sl1s:fs2s each sl1;subsyms[1i;sl1s];subsymstick[1i;sl1s];subsymsbook[1i;sl1s]];if[0<count sl2:sl where `XSHE=fs2e each sl;sl2s:fs2s each sl2;subsyms[2i;sl2s];subsymstick[2i;sl2s];subsymsbook[2i;sl2s]];};

//----ChangeLog----
//2023.06.10:.upd.TickOrder和.upd.TickMatch增加对flag列初始化,.upd.DepthMD增加对l2quote扩充列初始化
