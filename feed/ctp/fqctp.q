.module.fqctp:2018.03.30;

txload "core/fqbase";
txload "feed/ctp/ctpbase";

`initctpq`freectpq`ctpqrun`userLoginQ`subscribe{x set `extfqctp 2:(x;y);}' 2 1 1 2 2;

.enum.CTPMDKey:`TradingDay`InstrumentID`ExchangeID`ExchangeInstID`LastPrice`PreSettlementPrice`PreClosePrice`PreOpenInterest`OpenPrice`HighestPrice`LowestPrice`Volume`Turnover`OpenInterest`ClosePrice`SettlementPrice`UpperLimitPrice`LowerLimitPrice`PreDelta`CurrDelta`UpdateTime`UpdateMillisec`BidPrice1`BidVolume1`AskPrice1`AskVolume1`BidPrice2`BidVolume2`AskPrice2`AskVolume2`BidPrice3`BidVolume3`AskPrice3`AskVolume3`BidPrice4`BidVolume4`AskPrice4`AskVolume4`BidPrice5`BidVolume5`AskPrice5`AskVolume5`AveragePrice;
.enum.CTPQRKey:`TradingDay`InstrumentID`ForQuoteSysID`ForQuoteTime`ActionDay;

//.enum.ctpex:mirror .enum.exmap:`G`A`B`C`D!`CCFX`XSGE`XDCE`XZCE`XINE; 

insu2exch:{[x]exec first ex from .db.QX where esym=x};insu2cont:{[x]"i"$exec first i from .db.QX where esym=x}; 

\d .temp
QREF:QUEUE:L13:L12:L11:L:C:();MDSub:QTSub:()!();
\d .

ctpqconn:{[x;y]if[not any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`run]:initctpq[.conf.ctp.mdfront;.conf.me];1b;};
ctpqdisc:{[x;y]if[any .z.T within/: .conf.ctp.openrange;:()]if[((.z.D>d0)|(.z.T>.conf.ctp.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];.exit.fqctp[];1b;};

.init.fqctp:{[x]ctpqconn[`;.z.P];};
.exit.fqctp:{[x]savedb[];.ctrl.ctp[`run]:freectpq[];.upd.FrontDisconnectQ[];};

ctpqlogin:{[]if[(not 1b~.ctrl.ctp`ConnectQ)|(1b~.ctrl.ctp`LoginQ);:()];ctpcall[`userLoginQ;.conf.ctp`broker`user`pass`cltver];};

.timer.fqctp:{[x]ctpqlogin[];if[any .z.T within/:.conf.ctp.openrange;dosubscribe[]];batchpub[];};

dosubscribe:{[]if[(1b~.ctrl.ctp`SubscribeQ)|(not 1b~.ctrl.ctp`LoginQ)|(0=count .db.QX);:()];d:select from $[count sl:.conf`ctpsublist;select from .db.QX where product in sl;.db.QX] where ((opendate<=.z.D)&(settledate>=.z.D))|null settledate;if[.conf`skipspsyms;d:delete from d where 3<=count each string product];sl:$[count ssl:.conf`ctpsymlist;fs2s each ssl;exec fs2s each sym from d];{.temp.MDSub[x]:0b} each sl;if[.conf.ctp.debug;.temp.mdsl:sl];{[sl]sm:`$"," sv string sl;subscribe[sm;0i];} each 0N 100#sl;sl:$[count ssl:.conf`ctpsymlist;ssl;exec fs2s each sym from $[count sl:.conf`ctpsublist;select from .db.QX where product in sl;.db.QX] where assetclass=`Option,opendate<=.z.D,settledate>=.z.D];{.temp.QTSub[x]:0b} each sl;if[.conf.ctp.debug;.temp.qtsl:sl];{[sl]sm:`$"," sv string sl;subscribe[sm;1i];} each 0N 100#sl;.ctrl.ctp[`SubscribeQ`SubscribeTimeQ]:(1b;.z.P);};

.upd.FrontConnectQ:{[x].ctrl.ctp[`ConnectQ`ConntimeQ]:(1b;.z.P);};

.upd.FrontDisconnectQ:{[x].ctrl.ctp[`ConnectQ`LoginQ`SubscribeQ`DiscReasonQ`DisctimeQ]:(0b;0b;0b;x[0];.z.P);};

.upd.UserLoginQ:{[x]y:x[2];if[0=count y;:()];.ctrl.ctp[`LoginQ`LoginTimeQ`FrontID_Q`QSessionID_Q`QMaxOrderRef_Q]:(1b;.z.P),y;}; 

.upd.MDSub:{[x].temp.MDSub[`$x]:1b;};
.upd.QTSub:{[x].temp.QTSub[`$x]:1b;};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[`quote;.temp.QUEUE];.temp.QUEUE:()};

fix0w:{[x]?[1e300<abs[x];0n;x]};

.upd.RDUpdate:{[x]if[`ctp<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;dosubscribe[];};

.upd.DepthMD:{[x]y:.enum.CTPMDKey!x;if[.conf.ctp.debug;.temp.L11,:enlist y];if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0:"D"$ds:y`TradingDay;pubm[`ALL;`MarketOpen;.conf.me;ds];.db.fqopendate:d0];d:update upd_serial:"I"${(string x) except ".:"}each sys_recv_time from select contract_id:insu2cont each `$InstrumentID,upd_serial:0n,sys_recv_time:UpdateTime {"T"$x,".",string y}' UpdateMillisec,exchCode:insu2exch each `$InstrumentID,varity_code:`$InstrumentID,deliv_date:`,openPrice:OpenPrice,lastPrice:LastPrice,highestPrice:HighestPrice,lowestPrice:LowestPrice,doneVolume:`float$Volume,chgPrice:0n,upperLimitPrice:UpperLimitPrice,lowerLimitPrice:LowerLimitPrice,hisHighestPrice:0w,hisLowestPrice:-0w,openInterest:OpenInterest,preSettlePrice:PreSettlementPrice,preClosePrice:PreClosePrice,settlePrice:SettlementPrice,turnover:Turnover,preOpenInterest:PreOpenInterest,closePrice:ClosePrice,preDelta:PreDelta,currDelta:CurrDelta,bidPrice1:BidPrice1,bidVolume1:`float$BidVolume1,bidPrice2:BidPrice2,bidVolume2:`float$BidVolume2,bidPrice3:BidPrice3,bidVolume3:`float$BidVolume3,bidPrice4:BidPrice4,bidVolume4:`float$BidVolume4,bidPrice5:BidPrice5,bidVolume5:`float$BidVolume5,askPrice1:AskPrice1,askVolume1:`float$AskVolume1,askPrice2:AskPrice2,askVolume2:`float$AskVolume2,askPrice3:AskPrice3,askVolume3:`float$AskVolume3,askPrice4:AskPrice4,askVolume4:`float$AskVolume4,askPrice5:AskPrice5,askVolume5:`float$AskVolume5 from enlist y;d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from select sym:{[x;y;z]`$(string x),'(string y),'".",/:(string z)}[varity_code;deliv_date;exchCode],time:sys_recv_time,price:fix0w lastPrice,cumqty:fix0w doneVolume,vwap:fix0w turnover%doneVolume,high:fix0w highestPrice,low:fix0w lowestPrice,o5px:fix0w askPrice5,o5sz:fix0w askVolume5,o4px:fix0w askPrice4,o4sz:fix0w askVolume4,o3px:fix0w askPrice3,o3sz:fix0w askVolume3,o2px:fix0w askPrice2,o2sz:fix0w askVolume2,ask:fix0w askPrice1,asize:fix0w askVolume1,bid:fix0w bidPrice1,bsize:fix0w bidVolume1,b2px:fix0w bidPrice2,b2sz:fix0w bidVolume2,b3px:fix0w bidPrice3,b3sz:fix0w bidVolume3,b4px:fix0w bidPrice4,b4sz:fix0w bidVolume4,b5px:fix0w bidPrice5,b5sz:fix0w bidVolume5,openint:fix0w openInterest,settlepx:fix0w settlePrice,open:fix0w openPrice,pc:fix0w preClosePrice,sup:fix0w upperLimitPrice,inf:fix0w lowerLimitPrice,recvtime:.z.P,exlocaltime:.z.P from d;d:delete from d where (0>cumqty);if[count d;if[.conf.ctp.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:`timestamp$d0+time,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$(),quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[`quote;d2]]];};

.upd.QuoteReq:{[x]d:select sym:{[x]` sv x,exec first ex from .db.QX where esym=x} each `$InstrumentID,reqid:`$ForQuoteSysID,reqtime:`timestamp$("D"$TradingDay)+("T"$ForQuoteTime),actiondate:"D"$ActionDay from z:enlist y:.enum.CTPQRKey!x;.temp.L13,:z;pub[`quotereq;d];}



