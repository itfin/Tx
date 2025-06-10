.module.fql2zc:2025.06.05;

txload "core/fqbase";

`sipconn`sipdisc`siprun`sipisconn`sipsub`sipunsub`sipunsuball`sipgetcode {x set `extfql2zc 2:(x;y);}' 2,7#1;

\d .enum
`SIPE_ERRHANDLE`SIPE_OK`SIPE_ERR`SIPE_TCPCONNECTERR`SIPE_PROXY_CONNECTERR`SIPE_PROXY_AUTHERR`SIPE_DISCONNECT`SIPE_TCPIOERR`TCPMSGERR`SIPE_TIMEOUT`SIPE_PGMERR`SIPE_MCBERR`SIPE_ASYNCONNECTOK`SIPE_ASYNCONNECTERR`SIPE_PKGFMT`SIPE_PKGCODE`SIPE_PKGDATA`SIPE_VERSION`SIPE_NOUSER`SIPE_USERAUTH`SIPE_NOPOWER`SIPE_NOTAG`SIPE_NODATA`SIPE_MSGTYPE`SIPE_MSGSIZE`SIPE_DATALINE`SIPE_DSLCONFULL`SIPE_CONNECTFULL`SIPE_SSCFULL`SIPE_USERLOCKED`SIPE_ERRARGS`SIPE_DSLMAINEXIST`SIPE_SVRMEMERR`SIPE_SVREXIST`SIPE_TDAUSERERR`SIPE_TAGNOTSUBSCRIPT`SIPE_TDAUSERFULL`SIPE_TDANOUSERID`SIPE_SYSTAG`SIPE_NOSVR`SIPE_CTRLCODE`SIPE_CTRLOPTFULL`SIPE_COOKIE set' -1,til[7],(10+til[2]),(13+til[4]),100,(110+til 2),(120+til[8]),(130+til[2]),(140+til[3]),(150+til[3]),180,(191+til[8]),200;
\d .

\d .temp
L2M:L2O:L2Q:QREF:QUEUE:L18:L17:L16:L15:L14:L13:L12:L11:L10:L:C:();TKSub:BKSub:MDSub:()!();UnknownMsg:`long$();
\d .

isl2:1b~.conf[`usel2quote];quotetbl:$[isl2;`l2quote;`quote];

.ctrl.l2zc:.enum.nulldict;

onl2zc:{[x]if[.conf.fq.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[`$x[0]][x[1]]};;()] each x;};

l2zcconn:{[x;y]if[not any .z.T within/: .conf.fq.openrange;:()];if[1i~.ctrl.l2zc[`runQ];:()];.ctrl.l2zc[`runQ]:r:sipconn[.conf.fq`serverip`serverport`user`pass;.conf.fq`mode`async];1b};

l2zcdisc:{[x;y]if[any .z.T within/: .conf.fq.openrange;:()];if[not 1i~.ctrl.l2zc[`runQ];:()];.ctrl.l2zc[`runQ]:sipdisc[];if[((.z.D>d0)|(.z.T>.conf.fq.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b};

.init.fql2zc:{[x].roll.fql2zc[];l2zcconn[`;.z.P];};
.exit.fql2zc:{[x].ctrl.l2zc[`runQ]:sipdisc[];};

.roll.fql2zc:{[x].ctrl.l2zc[`codeget`codefull`codegettime]:(0b;0b;0Np);};

.timer.fql2zc:{[x]if[(1b~.ctrl.l2zc`codefull)&not 1b~.ctrl.l2zc`codeget;updcode[`;`]];if[any .z.T within/:.conf.fq.openrange;dosubscribe[]];batchpub[];batchpubl2[];};

dosubscribe:{[];};

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,pxunit,qtylot,qtyminl,qtymins from .db.QX where date1=.z.D;pubm[`ALL;`RDUpdate;`l2zc;string path];};
enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[quotetbl;distinct .temp.QUEUE];.temp.QUEUE:()};

enqueuel2:{[t;x]$[t=`Q;.temp.L2Q,:x;t=`O;.temp.L2O,:x;.temp.L2M,:x];};
enqueuel2q:enqueuel2[`Q];enqueuel2o:enqueuel2[`O];enqueuel2m:enqueuel2[`M];
batchpubl2:{[]if[(not 1b~.conf.batchpubl2);:()];if[0<count .temp.L2Q;pub[`l2queue;distinct .temp.L2Q];.temp.L2Q:()];if[0<count .temp.L2O;pub[`l2order;distinct .temp.L2O];.temp.L2O:()];if[0<count .temp.L2M;pub[`l2match;distinct .temp.L2M];.temp.L2M:()];};


updcode:{[x;y]if[0<count r:sipgetcode[];.ctrl.l2zc[`codebuf]:.j.k r];.ctrl.l2zc[`codeget]:1b;};

ZCMSG:()!();
ZCMSG[`UnknownMsg]:{[x].temp.x00:x;if[not x[2] in .temp.UnknownMsg;.temp.UnknownMsg,:x[2]];};

zclbl2sym:{[x]{sv[`] x[1],(`SH`SZ!`XSHG`XSHE)x[0]}vs[`]x};

ZCMSG[`StockMarketDataL2]:{[x].temp.x01:x;y:enlist `code`seq`nActionDay`nTime`nStatus`uPreClose`uOpen`uHigh`uLow`uMatch`AskPrice`AskVol`BidPrice`BidVol`uNumTrades`iVolume`iTurnover`iTotalBidVol`iTotalAskVol`uWeightedAvgBidPrice`uWeightedAvgAskPrice`nIOPV`nYieldToMaturity`uHighLimited`uLowLimited`sPrefix`nSyl1`nSyl2`nSD2`sTradingPhraseCode`nPreIOPV!x;if[.conf.fq.debug;.temp.L11,:y];d0:"D"$string y[0;`nActionDay];if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];d:update extime:d0+time from select sym:zclbl2sym each `$code,time:"T"$pad0[-9] each string nTime,price:1e-4*uMatch,cumqty:`float$iVolume,vwap:iTurnover%iVolume,high:1e-4*uHigh,low:1e-4*uLow,bid:1e-4*first each BidPrice,ask:1e-4*first each AskPrice,bsize:`float$first each BidVol,asize:`float$first each AskVol,bidQ:1e-4*{10#x,10#0n} each BidPrice,askQ:1e-4*{10#x,10#0n} each AskPrice,bsizeQ:`float${10#x,10#0n} each BidVol,asizeQ:`float${10#x,10#0n} each AskVol,openint:`float$uNumTrades,settlepx:1e-4*nIOPV,open:1e-4*uOpen,pc:1e-4*uPreClose,sup:1e-4*uHighLimited,inf:1e-6*uLowLimited,mode:`$sPrefix,recvtime:.z.P from y;d:delete from d where (0>cumqty);if[count d;if[.conf.fq.debug;.temp.L10,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;.temp.d2:d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime,bidQ,askQ,bsizeQ,asizeQ,quoopt:n#enlist "" from d;if[isl2;.temp.nd2:d2:update tnum:0N,b0num:0N,b0qtyQ:{`float$()} each i,bnum:0N,bqty:0n,bwap:0n,bcnum:0N,bcqty:0n,bcamt:0n,bpnum:0N,bwtime:0Nt,a0num:0N,a0qtyQ:{`float$()} each i,anum:0N,aqty:0n,awap:0n,acnum:0N,acqty:0n,acamt:0n,apnum:0N,awtime:0Nt,ebnum:0N,ebqty:0n,ebamt:0n,esnum:0N,esqty:0n,esamt:0n,yield:0n,execqty:0n,winf:0n,wsup:0n,bbwap:0n,bawap:0n,flag:` from d2];$[1b~.conf.batchpub;enqueue[d2];pub[quotetbl;d2]]];};                                                                  /1004/2004:L2快照行情

ZCMSG[`StockStepDataSH]:{[x].temp.x02:x;y:enlist `code`seq`nActionDay`iBizIndex`nChannel`nTickTime`cType`iBuyOrderNo`iSellOrderNo`nPrice`iQty`iTradeMoney`sTickBSflag!x;if[.conf.fq.debug;.temp.L12,:y];$[x[6]~"T";[.temp.x10:x;d:select sym:zclbl2sym each `$code,side:first each sTickBSflag,typ:cType,price:1e-4*nPrice,qty:`float$iQty,amt:`float$iTradeMoney,gid:`int$nChannel,mid:iBizIndex,bid:iBuyOrderNo,aid:iSellOrderNo,bizidx:iBuyOrderNo,extime:("D"$string nActionDay)+"T"$pad0[-9] each string nTickTime,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]]];not x[6]~"S";[.temp.x11:x;d:select sym:zclbl2sym each `$code,side:first each sTickBSflag,typ:cType,price:1e-4*nPrice,qty:`float$iQty,gid:`int$nChannel,oid:iBizIndex,origid:iBizIndex,bizidx:iBizIndex,extime:("D"$string nActionDay)+"T"$pad0[-9] each string nTickTime,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]]];[]];}; /1009:上海逐笔合并

ZCMSG[`StockStepTradeSZ]:{[x].temp.x03:x;y:enlist `code`seq`nActionDay`usChannelNo`i64ApplSeqNum`sMDStreamID`i64BidApplSeqNum`i64OfferApplSeqNum`SecurityID`sSecurityIDSource`i64LastPx`i64LastQty`cExecType`i64TransactTime!x;if[.conf.fq.debug;.temp.L13,:y];d:select sym:zclbl2sym each `$code,side:.enum.NULL,typ:cExecType,price:1e-4*i64LastPx,qty:`float$i64LastQty,amt:0n,gid:`int$usChannelNo,mid:i64ApplSeqNum,bid:i64BidApplSeqNum,aid:i64OfferApplSeqNum,bizidx:i64ApplSeqNum,extime:("D"$string nActionDay)+"T"$pad0[-9] each string i64TransactTime,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};                              /2009:深圳逐笔成交

ZCMSG[`StockStepOrderSZ]:{[x].temp.x04:x;y:enlist `code`seq`nActionDay`usChannelNo`i64ApplSeqNum`sMDStreamID`SecurityID`sSecurityIDSource`i64Price`i64OrderQty`cSide`i64TransactTime`cType!x;if[.conf.fq.debug;.temp.L14,:y];d:select sym:zclbl2sym each `$code,side:cSide,typ:cType,price:1e-4*i64Price,qty:`float$i64OrderQty,gid:`int$usChannelNo,oid:i64ApplSeqNum,origid:i64ApplSeqNum,bizidx:i64ApplSeqNum,extime:("D"$string nActionDay)+"T"$pad0[-9] each string i64TransactTime,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};                              /2009:深圳逐笔委托

.upd.CPKG_LOCAL_ERR:{[x].temp.x1:x;$[x[0]=.enum.SIPE_ASYNCONNECTOK;[.ctrl.l2zc[`ConnectedQ`ConnectedTimeQ]:(1b;.z.P);.ctrl.l2zc[`SubResult]:sipsub .conf.fq.subsymlst;];x[0]=.enum.SIPE_DISCONNECT;[.ctrl.l2zc[`ConnectedQ`DisconnectedTimeQ]:(0b;.z.P);];[]];};
.upd.CPKG_PKGERR:{[x].temp.x2:x;};
.upd.CPKG_SSCTAGERRNOTIFY:{[x].temp.x3:x;};
.upd.CPKG_SVRPUTMSG:{[x].temp.x4:x;@[{ZCMSG[`$x[0]][x[1]]};;()] each x;};

//----ChangeLog----
//2025.06.05:初始版本
