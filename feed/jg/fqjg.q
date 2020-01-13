.module.fqjg:2019.12.26;

txload "core/fqbase";
txload "feed/jg/jgbase";

`initjgq`freejgq`jgqrun {x set `extfqjg 2:(x;y);}' 2 1 1;

\d .enum
JGMDStk:`h`szWindCode`szCode`nActionDay`nTradingDay`nTime`nStatus`nPreClose`nOpen`nHigh`nLow`nMatch`pa`qa`pb`qb`nNumTrades`iVolume`iTurnover`nTotalBidVol`nTotalAskVol`nWeightedAvgBidPrice`nWeightedAvgAskPrice`nIOPV`nYieldToMaturity`nHighLimited`nLowLimited`chPrefix`nSyl1`nSyl2`nSD2;
JGMDIdx:`h`szWindCode`szCode`nActionDay`nTradingDay`nTime`nStatus`nOpenIndex`nHighIndex`nLowIndex`nLastIndex`iTotalVolume`iTurnover`nPreCloseIndex;

JGMDFut:`h`szWindCode`szCode`nActionDay`nTradingDay`nTime`nStatus`iPreOpenInterest`nPreClose`nPreSettlePrice`nOpen`nHigh`nLow`nMatch`iVolume`iTurnover`iOpenInterest`nClose`nSettlePrice`nHighLimited`nLowLimited`nPreDelta`nCurrDelta`pa`qa`pb`qb`nAuctionPrice`nAuctionQty`nAvgPrice;

JGMDOpt:`h`szWindCode`szCode`nDate`nTime`iTotalLongPosition`iTradeVolume`dTotalValueTraded`nPreSettlePrice`nOpenPrice`nAuctionPrice`iAuctionQty`nHighPrice`nLowPrice`nTradePrice`pb`qb`pa`qa`nSettlePrice`szTradingPhaseCode`nRFValue`iNumTrades`nSecurityClosePx`nHighLimitedPrice`nLowLimitedPrice;
JGMDHK:`h`szWindCode`szCode`nDate`nTime`nStatus`unPreClosePx`unNominalPrice`unOpenPrice`unHighPrice`unLowPrice`unTradePrice`llTotalVolume`dTotalAmount`pa`qa`na`pb`qb`nb`unTradeVolume`unSpread;
\d .

mirror .enum.exjgQ:`SH`SZ`CFF`SHF`CZC`DCE`SHO`SZO`HKEX!`XSHG`XSHE`CCFX`XSGE`XZCE`XDCE`XSHG`XSHE`XHKG;

\d .temp
QSNAP:QREF:QUEUE:L16:L15:L14:L13:L12:L11:L:C:();TKSub:BKSub:MDSub:()!();
\d .

jgqconn:{[x;y]if[not any .z.T within/: .conf.jg.openrange;:()];if[1i~.ctrl.jg[`runQ];:()];.ctrl.jg[`conntimeQ`connid]:(.z.P;`int$newseq[]);.ctrl.jg[`runQ]:r:initjgq[.conf.jg[`contmout`hbint`pushmode`mkts`subs`flags`timeoffset],.ctrl.jg`connid;.conf.jg[`ip`port`user`pass]];1b;};
jgqdisc:{[x;y]if[any .z.T within/: .conf.jg.openrange;:()];if[1i~.ctrl.jg[`runQ];:()];.ctrl.jg[`runQ]:freejgq[];if[((.z.D>d0)|(.z.T>.conf.jg.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b;};

.init.fqjg:{[x]jgqconn[`;.z.P];};
.exit.fqjg:{[x].ctrl.jg[`runQ]:freejgq[];};
.roll.fqjg:{[x];};

dosubscribe:{[]};

.timer.fqjg:{[x]if[any .z.T within/:.conf.jg.openrange;jgqconn[`;`];dosubscribe[]];batchpub[];};

windcode2sym:{[x]y:vs[`]x;y[1]:.enum.exjgQ y[1];sv[`]y};
hksymmap:$[null .conf.jg[`hksymtype];windcode2sym;{[x]y:vs[`]x;y[1]:.enum.exjgQ y[1];y[0]:`$string "I"$string y[0];sv[`]y}];

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[`quote;.temp.QUEUE];.temp.QUEUE:()};

.upd.ConnectQ:{[x].ctrl.jg[`ConnectedTimeQ`qsip`qsport`qsuser`qspass`connres`connid]:.z.P,x;};
.upd.LoginQ:{[x].ctrl.jg[`LoginQ`LoginTimeQ`LoginResQ`LoginMsgQ`MktDateQ]:$[0=x[0];(1b;.z.P);(0b,0Np)],(x 0;`$x 1;(!/)x[3 4]);};
.upd.CodeQ:{[x].ctrl.jg[`CodeTime`CodeInfo`MktCode]:(.z.P;`$x[0];x[2]!x[3],'x[4]);};
.upd.HeartbeatQ:{[x]};

mdclean:{[d;d0].temp.d0:d0;d:d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from delete from d where (0>cumqty);if[count d;if[.conf.jg.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count[d];d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime:d0+time,bidQ,askQ,bsizeQ,asizeQ,quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[`quote;d2]]];} /if[0=n:count d1:(select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,bidQ,askQ,bsizeQ,asizeQ from d) except 0!.temp.QSNAP;:()];.temp.QSNAP,:1!d1;;

mdchkdate:{[d0]if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];};

.upd.MDepth:{[x].temp.X:x;y:.enum.JGMDStk!x;if[.conf.jg.debug;.temp.L11,:enlist y];d0:"D"$string y`nTradingDay;mdchkdate[d0];d:select sym:windcode2sym each `$szWindCode,time:"T"$pad0[-9] each string nTime,price:1e-4*nMatch,cumqty:`float$iVolume,vwap:iTurnover%iVolume,high:1e-4*nHigh,low:1e-4*nLow,bid:1e-4*first each pb,ask:1e-4*first each pa,bsize:`float$first each qb,asize:`float$first each qa,bidQ:1e-4*(5#) each pb,askQ:1e-4*(5#) each pa,bsizeQ:`float$(5#) each qb,asizeQ:`float$(5#) each qa,openint:`float$nNumTrades,settlepx:1e-4*nIOPV,open:1e-4*nOpen,pc:1e-4*nPreClose,sup:1e-4*nHighLimited,inf:1e-4*nLowLimited,mode:`$chPrefix,recvtime:.z.P,exlocaltime:.z.P from enlist y;mdclean[d;d0];};

.upd.Index:{[x].upd.MDepth (7#x),x[13],x[7+til 4],(4#enlist `long$()),0i,x[11 12],(4#0),(2#0i),(0;0;""),3#0i;};

.upd.MDepthFut:{[x].temp.X3:x;y:.enum.JGMDFut!x;if[.conf.jg.debug;.temp.L13,:enlist y];d0:"D"$string y`nTradingDay;mdchkdate[d0];d:select sym:windcode2sym each `$szWindCode,time:"T"$pad0[-9] each string nTime,price:1e-4*nMatch,cumqty:`float$iVolume,vwap:iTurnover%iVolume,high:1e-4*nHigh,low:1e-4*nLow,bid:1e-4*first each pb,ask:1e-4*first each pa,bsize:`float$first each qb,asize:`float$first each qa,bidQ:1e-4*(5#) each pb,askQ:1e-4*(5#) each pa,bsizeQ:`float$(5#) each qb,asizeQ:`float$(5#) each qa,openint:`float$iOpenInterest,settlepx:1e-4*nSettlePrice,open:1e-4*nOpen,pc:1e-4*nPreClose,sup:1e-4*nHighLimited,inf:1e-4*nLowLimited,mode:`,recvtime:.z.P,exlocaltime:.z.P from enlist y;mdclean[d;d0];};

.upd.MDepthOpt:{[x].temp.X4:x;y:.enum.JGMDOpt!x;if[.conf.jg.debug;.temp.L14,:enlist y];d0:"D"$string y`nTradingDay;mdchkdate[d0];d:select sym:windcode2sym each `$szWindCode,time:"T"$pad0[-9] each string nTime,price:1e-4*nTradePrice,cumqty:`float$iTradeVolume,vwap:dTotalValueTraded%iTradeVolume,high:1e-4*nHighPrice,low:1e-4*nLowPrice,bid:1e-4*first each pb,ask:1e-4*first each pa,bsize:`float$first each qb,asize:`float$first each qa,bidQ:1e-4*(5#) each pb,askQ:1e-4*(5#) each pa,bsizeQ:`float$(5#) each qb,asizeQ:`float$(5#) each qa,openint:`float$iNumTrades,settlepx:1e-4*nSettlePrice,open:1e-4*nOpenPrice,pc:1e-4*nPreSettlePrice,sup:1e-4*nHighLimitedPrice,inf:1e-4*nLowLimitedPrice,mode:`,recvtime:.z.P,exlocaltime:.z.P from enlist y;mdclean[d;d0];};

.upd.MDepthHK:{[x].temp.X5:x;y:.enum.JGMDHK!x;if[.conf.jg.debug;.temp.L15,:enlist y];d0:"D"$string y`nDate;mdchkdate[d0];d:select sym:hksymmap each `$szWindCode,time:"T"$pad0[-9] each string nTime,price:1e-4*unTradePrice,cumqty:`float$llTotalVolume,vwap:dTotalAmount%llTotalVolume,high:1e-4*unHighPrice,low:1e-4*unLowPrice,bid:1e-4*first each pb,ask:1e-4*first each pa,bsize:`float$first each qb,asize:`float$first each qa,bidQ:1e-4*(5#) each pb,askQ:1e-4*(5#) each pa,bsizeQ:`float$(5#) each qb,asizeQ:`float$(5#) each qa,openint:`float$unSpread,settlepx:1e-4*unNominalPrice,open:1e-4*unOpenPrice,pc:1e-4*unPreClosePx,sup:0w,inf:0f,mode:`,recvtime:.z.P,exlocaltime:.z.P from enlist y;mdclean[d;d0];};



