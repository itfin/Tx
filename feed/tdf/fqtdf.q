.module.fqtdf:2023.08.14;

txload "core/fqbase";

`inittdf`freetdf`tdfrun`tdfver`sub`codetable {x set `extfqtdf 2:(x;y);}' 2,5#1;

\d .enum
SnapshotKey:`WindCode`Code`ActionDay`TradingDay`Time`Status`PreClose`Open`High`Low`Match`AskPrice`AskVol`BidPrice`BidVol`NumTrades`Volume`Turnover`TotalBidVol`TotalAskVol`WeightedAvgBidPrice`WeightedAvgAskPrice`IOPV`YieldToMaturity`HighLimited`LowLimited`Prefix`Syl1`Syl2`SD2`TradeFlag`AfterPrice`AfterVolume`AfterTurnover`AfterMatchItems;
FutureSnapshotKey:`WindCode`Code`ActionDay`TradingDay`Time`Status`PreOpenInterest`PreClose`PreSettlePrice`Open`High`Low`Match`Volume`Turnover`OpenInterest`Close`SettlePrice`HighLimited`LowLimited`PreDelta`CurrDelta`AskPrice`AskVol`BidPrice`BidVol`AuctionPrice`AuctionQty`AvgPrice`OriginalCode;
IndexSnapshotKey:`WindCode`Code`ActionDay`TradingDay`Time`Status`Open`High`Low`Match`Volume`Turnover`PreClose;
`SUBSCRIPTION_SET`SUBSCRIPTION_ADD`SUBSCRIPTION_DEL`SUBSCRIPTION_FULL set' til 4;
exmap:(`$("HK-2-0";"HKF-1-0";"SGE-1-0";"CF-2-0";"SHF-1-0";"SH-2-0";"SZ-2-0"))!$[1b~.conf.tdf`usehkex;`HKEX;`XHKG],`XHKF`XAUX`CCFXW`XSGEW`XSHG`XSHE;

\d .

\d .temp
L2M:L2O:L2Q:QREF:QUEUE:L18:L17:L16:L15:L14:L13:L12:L11:L10:L:C:();TKSub:BKSub:MDSub:()!();
\d .

isl2:1b~.conf[`usel2quote];quotetbl:$[isl2;`l2quote;`quote];

.ctrl.tdf:.enum.nulldict;

ontdf:{[x]if[.conf.tdf.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};

tdfconn:{[x;y]if[not any .z.T within/: .conf.tdf.openrange;:()];if[1i~.ctrl.tdf[`runQ];:()];.ctrl.tdf[`conntimeQ`TDFVersion]:(.z.P;tdfver[]);.ctrl.tdf[`runQ]:r:inittdf[.conf.tdf[`servercnt],{(first each x),last each x} .conf.tdf`serverip`serverport`user`pass;.conf.tdf`submkts`subsyms`subtime`subtype`subcode`logdir];1b};

tdfdisc:{[x;y]if[any .z.T within/: .conf.tdf.openrange;:()];if[not 1i~.ctrl.tdf[`runQ];:()];.ctrl.tdf[`runQ]:freetdf[];if[((.z.D>d0)|(.z.T>.conf.tdf.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b};

.init.fqtdf:{[x].roll.fqtdf[];tdfconn[`;.z.P];};
.exit.fqtdf:{[x].ctrl.tdf[`runQ]:freetdf[];};

.roll.fqtdf:{[x].ctrl.tdf[`codeget`codefull`codegettime]:(0b;0b;0Np);};

.timer.fqtdf:{[x]if[(1b~.ctrl.tdf`codefull)&not 1b~.ctrl.tdf`codeget;updcode[`;`]];if[any .z.T within/:.conf.tdf.openrange;dosubscribe[]];batchpub[];batchpubl2[];};

dosubscribe:{[];};

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,pxunit,qtylot,qtyminl,qtymins from .db.QX where date1=.z.D;pubm[`ALL;`RDUpdate;`tdf;string path];};
enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[quotetbl;distinct .temp.QUEUE];.temp.QUEUE:()};

enqueuel2:{[t;x]$[t=`Q;.temp.L2Q,:x;t=`O;.temp.L2O,:x;.temp.L2M,:x];};
enqueuel2q:enqueuel2[`Q];enqueuel2o:enqueuel2[`O];enqueuel2m:enqueuel2[`M];
batchpubl2:{[]if[(not 1b~.conf.batchpubl2);:()];if[0<count .temp.L2Q;pub[`l2queue;distinct .temp.L2Q];.temp.L2Q:()];if[0<count .temp.L2O;pub[`l2order;distinct .temp.L2O];.temp.L2O:()];if[0<count .temp.L2M;pub[`l2match;distinct .temp.L2M];.temp.L2M:()];};

imphkbroker:{[]`:/kdb/HKBRKR set `num xcols ungroup update `$utf82gbk each string name,`$utf82gbk each string sname from flip `code`name`sname`esname`num!flip {[x]x:x[1];(first `$1_flip 4#x),`$1_flip 4_x} each  2_.[;0 1 0 1] xmlparse read0 `:/q/ref/hk/HKBrokerList2.xml;}; /µ¼Èë¸Û¹ÉÈ¯ÉÌÏ¯Î»ºÅ±í

.upd.SYS_DISCONNECT_NETWORK:{[x]lwarn[`tdf_disconnected;()];.ctrl.tdf[`disctime]:.z.P;};

.upd.SYS_CONNECT_RESULT:{[x]lwarn[`tdf_connected;()];.ctrl.tdf[`conntime`ConnResult`ConnectionID`Ip`Port`User`Pwd]:.z.P,x;};

.upd.SYS_LOGIN_RESULT:{[x]lwarn[`tdf_login;()];.ctrl.tdf[`logintime`LoginResult`LoginMsg`mktdate]:(.z.P;x[0];`$gbk2utf8 x 1;(`$x 3)!x 4);};

updcode:{[x;y]if[.z.P<.ctrl.tdf[`codegettime]+00:01^tfill .conf.tdf[`retryinterval];:()];.ctrl.tdf[`codegettime]:.z.P;.temp.ct:y:codetable each x:exec ex from .ctrl.tdf.M;if[any (count each y)<exec num from .ctrl.tdf.M;:()];.ctrl.tdf[`C]:update ssym:esym {[x;y]sv[`]x,`$first vs["-"] string y}' ex,sym:esym {[x;y]sv[`] {[x;y]x:string[x];`$$[("0"=first[x])&not y in `XSHG`XSHE;string "I"$x;x]}[x;y],y}' .enum.exmap ex from update `$wsym,`$ex,`$esym,`$wtyp from flip `wsym`ex`esym`name`cname`typ`wtyp`seq`qtylot!flip raze y;.db.CodeMap:exec (`u#wsym)!sym from .ctrl.tdf[`C];.db.SubMap:exec (`u#sym)!ssym from .ctrl.tdf[`C];1b;.ctrl.tdf[`codeget]:1b;};

.upd.SYS_CODETABLE_RESULT:{[x]lwarn[`tdf_full_codetable;x];.temp.x10:x;y:`$x[2];.ctrl.tdf[`codeget`codefull`codetime`CodeMsg`M]:(0b;1b;.z.P;`$gbk2utf8 x[0];([]ex:y;num:x[3];today:"D"$string x[4]));updcode[`;`];};

.upd.SYS_QUOTATIONDATE_CHANGE:{[x]lwarn[`tdf_date_change;x];};
.upd.SYS_MARKET_CLOSE:{[x]lwarn[`tdf_market_close;x];};

.upd.SYS_HEART_BEAT:{[x].ctrl.tdf[`hbtime]:.z.P;};

.upd.SYS_SINGLE_CODETABLE_RESULT:{[x]lwarn[`tdf_single_codetable;x];};

.upd.DATA_MARKET:{[x].temp.x11:x;y:flip .enum.SnapshotKey!flip x;if[.conf.tdf.debug;.temp.L11,:y];d0:"D"$string y[0;`ActionDay];if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];d:update extime:d0+time from select sym:.db.CodeMap `$WindCode,time:"T"$pad0[-9] each string Time,price:1e-4*Match,cumqty:`float$Volume,vwap:Turnover%Volume,high:1e-4*High,low:1e-4*Low,bid:1e-4*first each BidPrice,ask:1e-4*first each AskPrice,bsize:`float$first each BidVol,asize:`float$first each AskVol,bidQ:1e-4*{10#x,10#0n} each BidPrice,askQ:1e-4*{10#x,10#0n} each AskPrice,bsizeQ:`float${10#x,10#0n} each BidVol,asizeQ:`float${10#x,10#0n} each AskVol,openint:`float$NumTrades,settlepx:1e-4*IOPV,open:1e-4*Open,pc:1e-4*PreClose,sup:1e-4*HighLimited,inf:1e-6*LowLimited,mode:`$Prefix,recvtime:.z.P from y;d:delete from d where (0>cumqty);if[count d;if[.conf.tdf.debug;.temp.L10,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;.temp.d2:d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime,bidQ,askQ,bsizeQ,asizeQ,quoopt:n#enlist "" from d;if[isl2;.temp.nd2:d2:update tnum:0N,b0num:0N,b0qtyQ:{`float$()} each i,bnum:0N,bqty:0n,bwap:0n,bcnum:0N,bcqty:0n,bcamt:0n,bpnum:0N,bwtime:0Nt,a0num:0N,a0qtyQ:{`float$()} each i,anum:0N,aqty:0n,awap:0n,acnum:0N,acqty:0n,acamt:0n,apnum:0N,awtime:0Nt,ebnum:0N,ebqty:0n,ebamt:0n,esnum:0N,esqty:0n,esamt:0n,yield:0n,execqty:0n,winf:0n,wsup:0n,bbwap:0n,bawap:0n,flag:` from d2];$[1b~.conf.batchpub;enqueue[d2];pub[quotetbl;d2]]];};

.upd.DATA_FUTURE:{[x].temp.x12:x;y:flip .enum.FutureSnapshotKey!flip x;if[.conf.tdf.debug;.temp.L12,:y];.upd.DATA_MARKET flip value flip .enum.SnapshotKey#/:y,\:`NumTrades`TotalBidVol`TotalAskVol`WeightedAvgBidPrice`WeightedAvgAskPrice`IOPV`YieldToMaturity`Prefix`Syl1`Syl2`SD2`TradeFlag`AfterPrice`AfterVolume`AfterTurnover`AfterMatchItems!(0Ni;0N;0N;0N;0N;0Ni;0Ni;`char$4#0;0Ni;0Ni;0Ni;0Ni;0N;0Ni;0N;0Ni);}; //(.enum.SnapshotKey except .enum.FutureSnapshotKey)#first 0#.temp.L11

.upd.DATA_INDEX:{[x].temp.x13:x;y:flip .enum.IndexSnapshotKey!flip x;if[.conf.tdf.debug;.temp.L13,:y];.upd.DATA_MARKET flip value flip .enum.SnapshotKey#/:y,\:`AskPrice`AskVol`BidPrice`BidVol`NumTrades`TotalBidVol`TotalAskVol`WeightedAvgBidPrice`WeightedAvgAskPrice`IOPV`YieldToMaturity`HighLimited`LowLimited`Prefix`Syl1`Syl2`SD2`TradeFlag`AfterPrice`AfterVolume`AfterTurnover`AfterMatchItems!(4#enlist `long$()),(0Ni;0N;0N;0N;0N;0Ni;0Ni;0N;0N;`char$4#0;0Ni;0Ni;0Ni;0Ni;0N;0Ni;0N;0Ni);}; //(.enum.SnapshotKey except .enum.IndexSnapshotKey)#first 0#.temp.L11

.upd.DATA_ORDERQUEUE:{[x].temp.x15:x;y:flip `WindCode`Code`ActionDay`Time`Side`Price`Orders`ABItems`ABVolume!flip x;if[.conf.tdf.debug;.temp.L15,:y];d:select sym:.db.CodeMap `$WindCode,side:`char$Side,price:1e-4*Price,size:0n,num:`long$Orders,qtyQ:`float$ABItems#'ABVolume,extime:("D"$string ActionDay)+"T"$pad0[-9] each string Time from y;$[1b~.conf.batchpubl2;enqueuel2q[d];pub[`l2queue;d]];};

.upd.DATA_ORDER:{[x].temp.x16:x;y:flip `WindCode`Code`ActionDay`Time`Order`Price`Volume`OrderKind`FunctionCode`Channel`OrderOriNo`BizIndex!flip x;if[.conf.tdf.debug;.temp.L16,:y];d:select sym:.db.CodeMap `$WindCode,side:FunctionCode,typ:OrderKind,price:1e-4*Price,qty:`float$Volume,gid:Channel,oid:`long$Order,origid:OrderOriNo,bizidx:BizIndex,extime:("D"$string ActionDay)+"T"$pad0[-9] each string Time,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};

.upd.DATA_TRANSACTION:{[x].temp.x14:x;y:flip `WindCode`Code`ActionDay`Time`Index`Price`Volume`Turnover`BSFlag`OrderKind`FunctionCode`AskOrder`BidOrder`Channel`BizIndex!flip x;if[.conf.tdf.debug;.temp.L14,:y];d:select sym:.db.CodeMap `$WindCode,side:`char$BSFlag,typ:OrderKind,price:1e-4*Price,qty:`float$Volume,amt:`float$Turnover,gid:Channel,mid:`long$Index,bid:`long$BidOrder,aid:`long$AskOrder,bizidx:BizIndex,extime:("D"$string ActionDay)+"T"$pad0[-9] each string Time,flag:` from y;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};

.upd.DATA_BROKERQUEUE:{[x].temp.x17:x;y:flip `WindCode`Code`ActionDay`AskTime`BidTime`AskBrokers`BidBrokers`AskBroker`BidBroker!flip x;if[.conf.tdf.debug;.temp.L17,:y];d:(select sym:.db.CodeMap `$WindCode,side:"B",price:0n,size:0n,num:`long$BidBrokers,qtyQ:`float$BidBroker,extime:("D"$string ActionDay)+"T"$pad0[-9] each string BidTime from select from y where 0<BidTime),select sym:.db.CodeMap `$WindCode,side:"S",price:0n,size:0n,num:`long$AskBrokers,qtyQ:`float$AskBroker,extime:("D"$string ActionDay)+"T"$pad0[-9] each string AskTime from select from y where 0<AskTime;$[1b~.conf.batchpubl2;enqueuel2q[d];pub[`l2queue;d]];};

//.upd.ReSub:{[x]sub[(`$x`msg;.enum.SUBSCRIPTION_SET)];};
//.upd.ReSubAdd:{[x]sub[(`$x`msg;.enum.SUBSCRIPTION_ADD)];};
//.upd.ReSubAdd:{[x]sub[(`$sv[";"] string (distinct .db.SubMap -9!x`vbin) except `;.enum.SUBSCRIPTION_ADD)];};
.upd.ReSubAdd:{[x] if[count sl:(distinct .db.SubMap -9!x`vbin) except `;sub[(`$sv[";"] string sl;.enum.SUBSCRIPTION_ADD)]]};
//.upd.ReSubDel:{[x]sub[(`$x`msg;.enum.SUBSCRIPTION_DEL)];};
//.upd.ReSubFull:{[x]sub[(`$x`msg;.enum.SUBSCRIPTION_FULL)];};

//----ChangeLog----
//2023.08.14:新增updcode函数以支持在非回调线程里多次重复获取码表直至成功，对应修改.upd.SYS_CODETABLE_RESULT函数和.timer.fqtdf/.roll.tdf/.init.tdf函数
//2023.06.09:.upd.DATA_ORDER和.upd.DATA_TRANSACTION增加对flag列初始化,.upd.DATA_MARKET增加对l2quote扩充列初始化
