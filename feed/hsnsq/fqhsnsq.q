.module.fqhsnsq:2025.04.10;

txload "core/fqbase";
txload "lib/handy";

//`nsqver`nsqerr`initnsq`freensq`nsqrun`userLoginQ`subfut`cxlfut`reqfutref`reqfutsnap`substk`cxlstk`substkord`cxlstkord`reqstkref`reqstksnap`subopt`cxlopt`reqoptref`reqoptsnap`substkplus`cxlstkplus`reqstkrebuild`reqhktref {x set `extfqhsnsq 2:(x;y);}' 1 1 2 1 1,19#2;
`threadid`setpubfreq`getpubfreq`getlastpub`nsqver`nsqerr`initnsq`freensq`nsqrun`userLoginQ`subfut`cxlfut`reqfutref`reqfutsnap`substk`substkex`cxlstk`substkord`substkordex`cxlstkord`reqstkref`reqstksnap`subopt`cxlopt`reqoptref`reqoptsnap`substkplus`cxlstkplus`reqstkrebuild`reqhktref {x set `extfqhsnsq 2:(x;y);}' 1 1 1 1 1 1 2 1 1,21#2;
`sockopt`sockcheck`getsockbuf`setsockbuf`errmsg {x set `extsocket 2:(x;y);}' 5#1;

\d .enum
`HS_TRANS_All`HS_TRANS_Trade`HS_TRANS_Entrust set' "012"; /HSTransType
`HS_EI_SSE`HS_EI_SZSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE`HS_EI_SSEHK`HS_EI_SZSEHK set' `1`2`F1`F2`F3`F4`F5`G`S; /HSExchangeID
`HS_SET_UnKnown`HS_SET_Stock`HS_SET_Index`HS_SET_Fund`HS_SET_Bond`HS_SET_Option`HS_SET_ETFOption set' "0123456"; /HSSecurityType

(MODELST:`HS_IT_Init`HS_IT_CallAuction`HS_IT_Trinding`HS_IT_Pause`HS_IT_Close`HS_IT_ClosingCallAuction`HS_IT_Fusing`HS_IT_Halt`HS_IT_HaltAllDay`HS_IT_FuseToCallAuction`HS_IT_FuseToClose`HS_IT_AfterCloseTrade) set' "SCTBEUVP1MNA"; /HSInstrumentTradeStatus

MDKey:`ExchangeID`InstrumentID`LastPrice`PreClosePrice`OpenPrice`HighPrice`LowPrice`ClosePrice`UpperLimitPrice`LowerLimitPrice`TradeDate`UpdateTime`TradeVolume`TradeBalance`AveragePrice`pb`pa`qb`qa`TradesNum`InstrumentTradeStatus`TotalBidVolume`TotalAskVolume`MaBidPrice`MaAskPrice`MaBondBidPrice`MaBondAskPrice`YieldToMaturity`IOPV`EtfBuycount`EtfSellCount`EtfBuyVolume`EtfBuyBalance`EtfSellVolume`EtfSellBalance`TotalWarrantExecVolume`WarrantLowerPrice`WarrantUpperPrice`CancelBuyNum`CancelSellNum`CancelBuyVolume`CancelSellVolume`CancelBuyValue`CancelSellValue`TotalBuyNum`TotalSellNum`DurationAfterBuy`DurationAfterSell`BidOrdersNum`AskOrdersNum`PreIOPV`ChannelNo`BondLastAuctionPrice`BondAuctionVolume`BondAuctionBalance`BondLastTradeType`R1`MaxBid1Count`vb`MaxAsk1Count`va;
MDATPKey:`ExchangeID`InstrumentID`PreClosePrice`ClosePrice`TradeDate`UpdateTime`InstrumentTradeStatus`TradeVolume`TradeBalance`TradesNum`TotalBidVolume`TotalAskVolume`CancelBuyNum`CancelSellNum`CancelBuyVolume`CancelSellVolume`BidPrice1`AskPrice1`BidVolume1`AskVolume1`ChannelNo`R1`MaxBid1Count`vb`MaxAsk1Count`va;
OrderKey:`ExchangeID`InstrumentID`TransFlag`SeqNo`ChannelNo`TradeDate`TransactTime`OrdPrice`OrdVolume`OrdSide`OrdType`OrdNo`BizIndex`TrdVolume;
MatchKey:`ExchangeID`InstrumentID`TransFlag`SeqNo`ChannelNo`TradeDate`TransactTime`TrdPrice`TrdVolume`TrdMoney`TrdBuyNo`TrdSellNo`TrdBSFlag`BizIndex;
RefKey:`ExchangeID`InstrumentID`InstrumentName`SecurityType`PreClosePrice`UpperLimitPrice`LowerLimitPrice`PriceTick`BuyVolumeUnit`SellVolumeUnit`TradeDate;
\d .

.enum.ModeMap:.enum[.enum`MODELST]!.enum`MODELST;

.enum.nsqex:mirror .enum.exnsq:`1`2!`XSHG`XSHE; 

.ctrl.nsq:.enum.nulldict;

onhsnsq:{[x].ctrl.nsq[`cbtime`cblast`cbmem`cbcnt]:(.z.P;.ctrl.nsq`cbtime;-22!x;count x);if[.conf.hsnsq.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};

hsnsqconn:{[x;y]if[not any .z.T within/: .conf.hsnsq.openrange;:()];if[1i~.ctrl.nsq[`runQ];:()];.ctrl.nsq[`conntimeQ`H5Version]:(.z.P;nsqver[]);.ctrl.nsq[`runQ]:r:initnsq[`;.conf.hsnsq`logdir`cfgfile`ngroup`igroup];1b};

hsnsqdisc:{[x;y]if[any .z.T within/: .conf.hsnsq.openrange;:()];if[1i~.ctrl.nsq[`runQ];:()];.ctrl.nsq[`runQ]:freensq[];if[((.z.D>d0)|(.z.T>.conf.hsnsq.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b};

.init.fqhsnsq:{[x]setpubfreq[0^jfill .conf.hsnsq`pubfreq];hsnsqconn[`;.z.P];};
.exit.fqhsnsq:{[x].ctrl.nsq[`runQ]:freensq[];};

.timer.fqhsnsq:{[x]if[any .z.T within/:.conf.hsnsq.openrange;dosubscribe[]];batchpub[];batchpubl2[];};

dosubscribe:{[];};
getudpsock:{[]r:system "/usr/sbin/lsof -a -i udp -p ",string[.z.i];"I"$except[;"u"]@[;3]vs[" ";r[1]] except enlist ""};

nsqcall:{[x;y]k:newseq[];.temp.C,:enlist (.z.P;k;x;y);((value x)[k;y,$[0=type y;();enlist (::)]];k)};

.upd.FrontConnectQ:{[x].ctrl.nsq.ConnectTime:.z.P;.temp.x10:x;.ctrl.nsq.LoginQ:first nsqcall[`userLoginQ;.conf.hsnsq`user`pass];};
.upd.FrontDisconnectQ:{[x].ctrl.nsq[`DiscTime`DiscReason]:(.z.P;x[0]);.ctrl.nsq.LoginQ:-1;};

//.upd.UserLoginQ:{[x].ctrl.nsq.LoginTime:.z.P;m:.conf.hsnsq.mkt;r:nsqcall[`substk;(0;m)];.ctrl.nsq[`SubQ]:r[0];.temp.MDSub[m]:r[1];r:nsqcall[`substkord;(.enum`HS_TRANS_All;0;m)];.ctrl.nsq.SubO:r[0];.temp.TKSub[m]:r[1];};
//.upd.UserLoginQ:{[x].ctrl.nsq.LoginTime:.z.P;m:.conf.hsnsq.mkt;substk:`substk;substkarg:(0;m);substkord:`substkord;substkordarg:(.enum`HS_TRANS_All;0;m);if[(0<count sl:distinct raze .conf.hsnsq.subsymlist)&(`subsymlist in key .conf.hsnsq)&m=`1;sl:sl where (fs2e each sl)=`XSHG;sl:(10000&count sl)#sl;if[0<count sl;s:fs2s each sl;e:(count sl)#`1;substk:`substkex;substkarg:(count sl;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_All;count sl;s;e)];];if[(0<count sl:distinct raze .conf.hsnsq.subsymlist)&(`subsymlist in key .conf.hsnsq)&m=`2;sl:sl where (fs2e each sl)=`XSHE;sl:(10000&count sl)#sl;if[0<count sl;s:fs2s each sl;e:(count sl)#`2;substk:`substkex;substkarg:(count sl;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_All;count sl;s;e)];];r:nsqcall[substk;substkarg];.ctrl.nsq[`SubQ]:r[0];.temp.MDSub[m]:r[1];r:nsqcall[substkord;substkordarg];.ctrl.nsq.SubO:r[0];.temp.TKSub[m]:r[1];};
//.upd.UserLoginQ:{[x] .ctrl.nsq.LoginTime:.z.P;m:.conf.hsnsq.mkt;substk:`substk;substkarg:(0;m);substkord:`substkord;substkordarg:(.enum`HS_TRANS_All;0;m);if[(not `~.conf.hsnsq.subsymlist)&m=`1;sl:sl where (fs2e each sl:distinct raze .conf.hsnsq.subsymlist)=`XSHG;sl:(10000&count sl)#sl;if[0<n:count sl;s:fs2s each sl;e:n#`1;substk:`substkex;substkarg:(n;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_All;n;s;e)];];if[(not `~.conf.hsnsq.subsymlist)&m=`2;sl:sl where (fs2e each sl:distinct raze .conf.hsnsq.subsymlist)=`XSHE;sl:(10000&count sl)#sl;if[0<n:count sl;s:fs2s each sl;e:n#`2;substk:`substkex;substkarg:(n;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_All;n;s;e)];];r:nsqcall[substk;substkarg];.ctrl.nsq[`SubQ]:r[0];.temp.MDSub[m]:r[1];r:nsqcall[substkord;substkordarg];.ctrl.nsq.SubO:r[0];.temp.TKSub[m]:r[1];};

.upd.UserLoginQ:{[x].ctrl.nsq.LoginTime:.z.P;if[1b~.conf.hsnsq`skipcb;:()];m:.conf.hsnsq.mkt;sl:.conf.hsnsq.subsymlist;substk:`substk;substkarg:(0;m);substkord:`substkord;substkordarg:(.enum`HS_TRANS_Entrust;0;m);substkordarg1:(.enum`HS_TRANS_Trade;0;m);if[(not `~sl)&m=`1;sl:raze sl;sl:sl where (fs2e each sl)=`XSHG;if[0<n:count sl;s:fs2s each sl;e:n#`1;substk:`substkex;substkarg:(n;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_Entrust;n;s;e)];substkordarg1:(.enum`HS_TRANS_Trade;n;s;e)];if[(not `~sl)&m=`2;sl:raze sl;sl:sl where (fs2e each sl)=`XSHE;if[0<n:count sl;s:fs2s each sl;e:n#`2;substk:`substkex;substkarg:(n;s;e);substkord:`substkordex;substkordarg:(.enum`HS_TRANS_All;n;s;e)];];if[not 0b~.conf.hsnsq`subquote;r:nsqcall[substk;substkarg];.ctrl.nsq[`SubQ]:r[0];.temp.MDSub[m]:r[1]];if[not 0b~.conf.hsnsq`suborder;r:nsqcall[substkord;substkordarg];.ctrl.nsq.SubO:r[0];.temp.BKSub[m]:r[1]];if[not 0b~.conf.hsnsq`submatch;r:nsqcall[substkord;substkordarg1];.ctrl.nsq.SubM:r[0];.temp.TKSub[m]:r[1]];if[0<s:getudpsock[];.ctrl.nsq[`UdpSock]:s;sb:getsockbuf[s];if[sb[0]<2*.conf.hsnsq.udprbufsize;setsockbuf[`int$s,.conf.hsnsq`udprbufsize`udpwbufsize]]];};

.upd.RspSecuTransactionSubscribe:.upd.RspSecuDepthMarketDataSubscribe:{[x].temp.BKSub[x[0]]:1b;};
.upd.RspSecuTransactionCancel:.upd.RspSecuDepthMarketDataCancel:{[x].temp.BKSub[x[0]]:0b;};

.upd.DepthMD:{[x]if[1b~.conf.hsnsq`skipcb;:()];.temp.x0:x;z:enlist y:.enum.MDKey!x;if[1b~.conf.hsnsq.debug;.temp.L10,:z];.temp.d:d:select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],bid:first each pb,ask:first each pa,bsize:`float$first each qb,asize:`float$first each qa,price:LastPrice,high:HighPrice,low:LowPrice,vwap:AveragePrice,cumqty:`float$TradeVolume,openint:PreClosePrice,settlepx:IOPV,mode:`$string InstrumentTradeStatus,extime:("D"$string TradeDate)+"T"$pad0[-9] each string UpdateTime,bidQ:pb,askQ:pa,bsizeQ:`float$qb,asizeQ:`float$qa,quoopt:{""} each i,tnum:TradesNum,b0num:MaxBid1Count,b0qtyQ:`float$vb,bnum:TotalBuyNum,bqty:`float$TotalBidVolume,bwap:MaBidPrice,bcnum:CancelBuyNum,bcqty:`float$CancelBuyVolume,bcamt:CancelBuyValue,bpnum:BidOrdersNum,bwtime:`time$DurationAfterBuy,a0num:MaxAsk1Count,a0qtyQ:`float$va,anum:TotalSellNum,aqty:`float$TotalAskVolume,awap:MaAskPrice,acnum:CancelSellNum,acqty:`float$CancelSellVolume,acamt:CancelSellValue,apnum:AskOrdersNum,awtime:`time$DurationAfterSell,ebnum:`long$EtfBuycount,ebqty:`float$EtfBuyVolume,ebamt:EtfBuyBalance,esnum:`long$EtfSellCount,esqty:`float$EtfSellVolume,esamt:EtfSellBalance,yield:YieldToMaturity,execqty:`float$TotalWarrantExecVolume,winf:WarrantLowerPrice,wsup:WarrantUpperPrice,bbwap:MaBondBidPrice,bawap:MaBondAskPrice,flag:` from z;if[count d;$[1b~.conf.batchpub;enqueue[d];pub[quotetbl;d]]];d1:select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],pc:PreClosePrice,open:OpenPrice,sup:UpperLimitPrice,inf:LowerLimitPrice from z;if[(1b~.conf.hsnsq`pushref)&n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];};

.upd.DepthMDATP:{[x].temp.x1:x;z:enlist y:.enum.MDATPKey!x;if[1b~.conf.hsnsq.debug;.temp.L11,:z];};

.upd.TransactionEntrust_sh:{[x]if[1b~.conf.hsnsq`skipcb;:()];.temp.x2:x;z:enlist y:.enum.OrderKey!x;if[1b~.conf.hsnsq.debug;.temp.L12,:z];d:select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],side:OrdSide,typ:OrdType,price:OrdPrice,qty:`float$OrdVolume,gid:ChannelNo,oid:OrdNo,origid:SeqNo,bizidx:BizIndex,extime:("D"$string TradeDate)+"T"$pad0[-9] each string TransactTime,flag:` from z;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};

.upd.TransactionEntrust_sz:{[x]if[1b~.conf.hsnsq`skipcb;:()];.temp.x2:x;z:enlist y:.enum.OrderKey!x;if[1b~.conf.hsnsq.debug;.temp.L12,:z];m:.conf.hsnsq.mkt;d:select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],side:OrdSide,typ:OrdType,price:OrdPrice,qty:`float$OrdVolume,gid:ChannelNo,oid:SeqNo,origid:OrdNo,bizidx:BizIndex,extime:("D"$string TradeDate)+"T"$pad0[-9] each string TransactTime,flag:` from z;$[1b~.conf.batchpubl2;enqueuel2o[d];pub[`l2order;d]];};

.upd.TransactionEntrust:$[`1~.conf.hsnsq.mkt;.upd.TransactionEntrust_sh;.upd.TransactionEntrust_sz];

nsqmatch:{[t;z]select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],side:.enum.NULL,typ:TrdBSFlag,price:TrdPrice,qty:`float$TrdVolume,amt:TrdMoney,gid:ChannelNo,mid:SeqNo,bid:TrdBuyNo,aid:TrdSellNo,bizidx:BizIndex,extime:("D"$string TradeDate)+"T"$pad0[-9] each string TransactTime,flag:t from z};

.upd.TransactionTrade:{[x]if[1b~.conf.hsnsq`skipcb;:()];.temp.x3:x;z:enlist y:.enum.MatchKey!x;if[1b~.conf.hsnsq.debug;.temp.L13,:z];d:nsqmatch[`] z;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};

.upd.TransactionTradeATP:{[x].temp.x4:x;z:enlist y:.enum.MatchKey!x;if[1b~.conf.hsnsq.debug;.temp.L14,:z];d:nsqmatch[`A] z;$[1b~.conf.batchpubl2;enqueuel2m[d];pub[`l2match;d]];};

.upd.TransactionEntrustBond:{[x].temp.x5:x;};
.upd.TransactionTradeBond:{[x].temp.x6:x;};

.upd.RspQrySecuInstruments:{[x].temp.x7:x;z:enlist y:.enum[`RefKey]!x;.temp.d7:d:select sym:{[x;y]`$x,'".",/:string y}[InstrumentID;.enum.exnsq `$ExchangeID],name:`$InstrumentName,sectype:`$string SecurityType,pc:PreClosePrice,inf:LowerLimitPrice,sup:UpperLimitPrice,pxunit:PriceTick,qtyminl:`float$BuyVolumeUnit,qtymins:`float$SellVolumeUnit,date:"D"$string TradeDate from z;.db.QX:.db.QX uj 1!d;};

.upd.OnDebug:{[x].ctrl.nsq[`dbtid`dbcnt`dbmem`dbtime]:(x[0];count x[1];-22!x;.z.P);};

//----ChangeLog----
//2025.04.10:修正HSSecurityType定义的拼写错误
//2025.03.07:增加对配置参数skipcb的支持,增加引入threadid函数和新回调消息.upd.OnDebug,修改onhsnsq
//2025.03.03:修复.upd.UserLoginQ新引入的.temp字典名错误
//2025.02.28:新增导入setsockbuf函数和定义getudpsock函数以支持加大nsq的udp socket接收缓冲区的大小(配置最大支持128M不够,注意OS会再加倍);更新.upd.UserLoginQ以支持.conf.hsnsq`suborder`submatch以便将深圳逐笔委托和逐笔成交分开订阅同时加大缓冲区以避免丢包
//2025.02.27:更新.upd.UserLoginQ以支持.conf.hsnsq`subquote`subtrans以便将深圳快照和深圳逐笔分开订阅以避免丢包
//2025.02.25:更新kqueue.h,新增引入setpubfreq和getpubfreq/getlastpub函数以支持消息批量导入kdb,频率为间隔纳秒数,.init.fqhsnsq增加间隔频率设置
//2023.07.31:.upd.TransactionEntrust分成.upd.TransactionEntrust_sz和.upd.TransactionEntrust_sz以统一和逐笔成交关联
//2023.06.26:.upd.DepthMD增加对.conf.hsnsq`pushref的判断以兼容上海行情涨跌停价为0的问题
//2023.06.14:初始版本
