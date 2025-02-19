.module.feldp:2024.08.28;

txload "core/febase";

`ldpapiver`ldplockfree`ldperrmsg`startstat`stopstat`exportstat`freeldp`ldprun`initldp`reqAuthenticate`reqUserLogin`reqQryStkAcct`reqOrderInsert`reqOrderAction`reqQryHold`reqQryFund`reqQryOrder`reqQryTrade`reqFundAlloc`reqQryFundPeer`reqLockStockApply`reqCompactDirectRepay`reqLockCompactSettle`reqQryLockStockQuote`reqQryLockCompact`reqQryMargin {x set `extfeldp 2:(x;y);}' (8#1),18#2;

.conf.ldp.pagesize:1000i;
.conf.ldp.bypassrtntrade:1b;

.ctrl.ldp.api:(0N,til[count[.conf.ldp.user]])!enlist[::],(count[.conf.ldp.user])#enlist .enum.nulldict;
.ctrl.ldp.usermap:{x!til count x} .conf.ldp.user;

ldpcall:{[i;x;y]k:newseq[];.temp.r:r:(value x)[`int$k,i;y,$[0=type y;();enlist (::)]];.temp.C,:enlist (r;.z.P;i;k;x;y);(r;k;i)};
onldp:{[x].temp.X:x;if[.conf.ldp.debug;.temp.L,:(enlist .z.P),/:x];@[{[x](.upd[x[0]])[x[1];x[2]]};;{[x]lerr[`onldp;(.z.P;x)]}] each x;};

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
`HS_EI_SSE`HS_EI_SZSE`HS_EI_TZASE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE`HS_EI_GFEX`HS_EI_SSEHK`HS_EI_SZSEHK set' `1`2`9`G`S`F1`F2`F3`F4`F5`F6`G`S; /HSExchangeID
(HSCTENUMS:`HS_CT_Limit`HS_CT_LimitFOK`HS_CT_LimitFAK`HS_CT_LimitStopLoss`HS_CT_LimitStopProfit`HS_CT_Market`HS_CT_MarketFOK`HS_CT_MarketFAK`HS_CT_MarketFAKV`HS_CT_MarketStopLoss`HS_CT_MarketStopProfit`HS_CT_MarketToLimit`HS_CT_Market5FAK`HS_CT_Market5ToLimit`HS_CT_Market1ToLimit`HS_CT_Market1FAK`HS_CT_Market1FOK`HS_CT_MarketSelfToLimit`HS_CT_CounterPartyBest`HS_CT_LimitFAKV`HS_CT_LimitPFP`HS_CT_HkAtCrossingLimitGFD`HS_CT_HkAtCrossingLimitFOK`HS_CT_HkDayLimit`HS_CT_TAS`HS_CT_BJSGZLimit`HS_CT_BlockIntention`HS_CT_BlockPricing`HS_CT_BlockConfirm`HS_CT_BlockMutualConfirm`HS_CT_BlockAFC`HS_CT_BlockAFW) set' `int$1+til 32; /HSOrderCommand
`HS_OD_Buy`HS_OD_Sell`HS_OD_Apply`HS_OD_MarthSecu`HS_OD_BondConv`HS_OD_BondCall`HS_OD_PledgeIn`HS_OD_PledgeOut`HS_OD_Repos`HS_OD_ReverseRepos`HS_OD_EtfSubs`HS_OD_EtfPur`HS_OD_EtfRed`HS_OD_BondCallCan`HS_OD_LofSubs`HS_OD_LofPur`HS_OD_LofRed`HS_OD_LofTrams`HS_OD_FundSplit`HS_OD_FundMerger`HS_OD_FundConv`HS_OD_CurrFundPur`HS_OD_CurrFundRed`HS_OD_CreditBuy`HS_OD_CreditSell`HS_OD_CollateralIn`HS_OD_CollateralOut`HS_OD_MarginBuy`HS_OD_ShortSell`HS_OD_SellRepay`HS_OD_BuyRepay`HS_OD_HoldRepay`HS_OD_HkBuyRound`HS_OD_HkSellRound`HS_OD_HkSellOddLot`HS_OD_CBPOF_OFC`HS_OD_CBPOF_OFR`HS_OD_ReitsFundSubs`HS_OD_OFundSubs`HS_OD_BorrowSell set' `int$(1+til 14),(16+til 9),33+til 17; /HSOrderDirection
`HS_OP_Secu`HS_OP_SecuAfof`HS_OP_SecuCbp`HS_OP_SecuHk`HS_OP_Crdt`HS_OP_CrdtAfof`HS_OP_CrdtCbp`HS_OP_SecuBt set' `int$1+til 8; /HSOrderPartition
`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed set' "0123456789DUVW"; /HSOrderStatus
`HS_OCR_OrderInserted`HS_OCR_OrderReported`HS_OCR_OrderConfirmed`HS_OCR_OrderTraded`HS_OCR_OrderAbandoned`HS_OCR_CancelInserted`HS_OCR_CancelReported`HS_OCR_CancelConfirmed`HS_OCR_CancelFailed set' "012345678"; /HSOrderAssStatus

`HS_OF_Open`HS_OF_Close`HS_OF_Delivery`HS_OF_CloseToday`HS_OF_CloseSingle set' "12346"; /HSOffsetFlag
`HS_CID_CNY`HS_CID_USD`HS_CID_HKD set' "012"; /HSCurrencyID
`HS_TD_In`HS_TD_Out set' "01"; /HSTransDirection
`HS_LCS_INEFFECTIVE`HS_LCS_EFFECTIVE`HS_LCS_EXPIRED set' "012"; /HSLockCompactStatus

ErrorKey:`RequestID`IsLast`ErrSrc`ErrorID`ErrorMsg;
OrderKey:`TradingDay`AccountID`OrderPartition`BrokerOrderID`SessionID`OrderRef`ExchangeID`StockAccount`StockCode`Direction`OrderPrice`OrderVolume`OrderStatus`OrderCommand`ReportTime`ErrorMsg`TradeVolume`BatchNo`WithdrawVolume`OrderTime`BrokerWithdrawOrderID`FrozenBalance`FrozenFare`BranchID`OrderAssStatus`WithdrawOrderStatus`OccurTime`ClientOrderID`StockName`TradePrice`BusinessBalance`StockType`OrderID`CashgroupProp`ExtOrderRef`TotalBusinessFare`SequenceNumber`UserApplicationType`RenewFlag`StrategyId`TotalRealBuyBalance`TotalRealSellBalance`SystemNo`ErrorNo;

TradeKey:`TradingDay`AccountID`OrderPartition`BrokerOrderID`SessionID`OrderRef`ExchangeID`StockAccount`StockCode`Direction`OrderCommand`TradeStatus`TradeID`TradeVolume`TradePrice`TradeTime`ErrorMsg`BatchNo`BrokerWithdrawOrderID`BusinessBalance`BranchID`OrderStatus`OccurTime`ClientOrderID`StockName`OrderPrice`OrderID`ExtOrderRef`TotalBusinessFare`SequenceNumber`RealBuyAmount`RealBuyBalance`RealSellAmount`RealSellBalance`UserApplicationType`RenewFlag`StrategyId`SystemNo`SumCashBalance`CompactID;

InsertKey:`OrderPartition`BrokerOrderID`SessionID`OrderRef`BatchNo`ClientOrderID`OrderID`ExtOrderRef;
ActionKey:`OrderPartition`BrokerOrderID`OrigOrderPartition`OrigBrokerOrderID`OrigSessionID`OrigOrderRef`OrigClientOrderID`OrderID`OrigBatchNo`OrigExtOrderRef;

FundKey:`CurrencyID`CurrentBalance`BeginBalance`AvailableBalance`FetchBalance`MarketValue`TotalAsset`CorrectBalance;
HoldKey:`AccountID`ExchangeID`StockAccount`StockCode`StockName`StockType`CurrentVolume`AvailableVolume`AvBuyPrice`AssetPrice`AchvProfit`BeginVolume`RealBuyVolume`RealSellVolume`UncomeBuyVolume`UncomeSellVolume`FloatProfit`MarketValue`LastPrice`DelistDate`CorrectVolume`ETFPurRedAvailableVolume`FrozenVolume`CostBalance`FinCompactAmount`FinUncomeAmount`FinCurrentAmount`FinMarketValue`CsfcSloAmount`SloMarketValue`SumBuyAmount`SumBuyBalance`SumSellAmount`SumSellBalance`StockNameShort`RealBuyBalance`RealSellBalance;
FundPeerKey:`CurrentBalance`AvailableBalance`CurrencyID;
FundAllocKey:`TransSerialID`FundUnused;

MarKey:`EnableBalance`BorrowSellSurplusBalance`BorrowSellSurplusBalance`EnableLockMargin`EnableBorrowMargin`OccuredBorrowStockInterest`OccuredLockStockInterest`TodayBorrowStockInterest`TodayLockStockInterest`LockCompactProfitLoss; /保证金查询结果
MQKey:`PositionSn`ExchangeID`StockCode`StockName`LockStockQuoteID`AvailableVolume`LimitDays`LockYearRate`BorrowYearRate`MinInterestDays`EarlyRecallMode; /报价查询结果
LockKey:`BatchNo`CompactID`ErrorNo`CompactRef; /锁券申请结果
RepayKey:`CompactID`OrderVolume`PostVolume; /直接还券结果
CompactKey:`ExchangeID`StockCode`CompactID`StockName`LockCompactStatus`RetEndDate`LockYearRate`BorrowYearRate`MinInterestDays`LockedVolume`BorrowedVolume`RepaidVolume`EnableBorrowVolume`EnableRepayVolume`EnableBuyVolume`LockCompactProfitLoss`TodayBorrowStockInterest`OccuredBorrowStockInterest`TodayLockStockInterest`OccuredLockStockInterest`EnableDirectReturnVolume`TodayTotalBuyVolume`InitialPositionVolume`CreateDate`BatchNo`CompactRef`ErrorMsg; /锁券合约主推
MLKey:`PositionSn,CompactKey; /锁券查询结果


\d .

.enum.ldpexmap:.enum[`HS_EI_SSE`HS_EI_SZSE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE]!`XSHG`XSHE`XHKG`XHKE`XZCE`XDCE`XSGE`CCFX`XINE;
.enum.ldpex:mirror .enum.ldpexmap;

.enum.ldpstatusmap:.enum[`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed]!.enum`PENDING_NEW`PENDING_NEW`NEW`PENDING_CANCEL`PENDING_CANCEL`CANCELED`CANCELED`PARTIALLY_FILLED`FILLED`REJECTED`REJECTED_CANCEL`PENDING_CANCEL`NEW`NEW;

.enum.ldpctmap:.enum[.enum.HSCTENUMS]!.enum.HSCTENUMS;

.enum.ldplockstatusmap:.enum[`HS_LCS_INEFFECTIVE`HS_LCS_EFFECTIVE`HS_LCS_EXPIRED]!.enum`PENDING_NEW`NEW`EXPIRED;

sectype:{[x;y]$[y in `F1`F2`F3`F4`F5`F6;$[(x like "IO*")|(x like "*-*")|(x like "*[0-9]C[0-9]*")|(x like "*[0-9]P[0-9]*");`OPT;x like "SP*";`FUTSP;`FUT];y in `1`2;$[8=count string x;`OPT;`STK];y in `G`S;`STKHK;`STK]}; /[sym;hsex]

ldpside:{[x;y].enum $[y=.enum`MARGIN_OPEN;`HS_OD_BorrowSell;y=.enum`MARGIN_CLOSE;`HS_OD_BuyRepay;y=.enum`MARGIN_REPAY;`HS_OD_HoldRepay;(x=.enum`SELL_SHORT_EXEMPT)&y=.enum`OPEN;`HS_OD_ReverseRepos;x=.enum`BUY;`HS_OD_Buy;`HS_OD_Sell]};

ldpposefct:{[x;y]$[x=.enum`OPEN;.enum`HS_OF_Open;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`HS_OF_CloseToday;.enum`HS_OF_Close]}; /[posefct;ex]

ldpconn:{[x;y]if[not any .z.T within/: .conf.ldp.openrange;:()];.ctrl.ldp[`Run]:initldp[.conf.ldp`apiflow`fens`submodel;.conf.ldp`user];1b;};
ldpdisc:{[x;y]if[any .z.T within/: .conf.ldp.openrange;:()];savedb[];.ctrl.ldp[`Run]:freeldp[];1b};

.init.feldp:{[x]ldpconn[`;.z.P];};
.exit.feldp:{[x]ldpdisc[`;.z.P];};
.timer.feldp:{[x];}; 
.roll.feldp:{[x];};
.disp.feldp:{.ctrl.ldp};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
DelayedRtn:(`symbol$())!`float$();
\d .

ldpmemo:{[x]y:padx[" ";29] string sv[`;`,x`ts`oid];`$(19#y),"9",(y 19+til 8),"00",y[27 28]};
decmemo:{[x]y:except[;" "] x til[count x] except 19 28 29;L:vs[".";y];`$(L[0];L[1];L[2],".",L[3])};
idfe2ft:{[x]exec first id from .db.O where feoid=`$x[0],id=@[decmemo[x[1]];2]};

/ldp msg
.upd.FrontConnected:{[i;x].temp.i:i;.temp.x:x;.ctrl.ldp.api[i]:`user`Connect`Conntime!(.conf.ldp.user[i];1b;.z.P);ldpcall[i;`reqAuthenticate;.conf.ldp.user[i],.conf.ldp.appid[i],.conf.ldp.auth[i]];};

.upd.FrontDisconnected:{[i;x].ctrl.ldp.api[i;`Connect`Login`DiscReason`Disctime]:(0b;0b;x;.z.P);lwarn[`ldp_disconnect;(i;x)];};

.upd.RspAuthenticate:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`AuthTime`AccountID`AppID`AuthCode]:.z.P,y;ldpcall[i;`reqUserLogin;(.conf.ldp.user[i];.conf.ldp.pass[i]),.conf.ldp`apptype`appinfo`macaddr`ipsddr`userinfo];};

.upd.RspUserLogin:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`Login`LoginTime`BranchID`AccountID`AssetProp`UserName`TradingDay`OrderRef`SessionID`UserID`CorpRiskLevel`UserNameLong]:(1b;.z.P),y;};

.upd.LdpError:{[i;x].temp.Y:x;.temp.L1,:enlist .enum.ErrorKey!(2#x),x[2];h:2#x;y:x[2];s:`$y[0];if[s<>`RspOrderAction;lwarn[`LdpError;x]];$[s=`RspOrderInsert;if[not null k:exec first id from .db[.ctrl.O] where j0=h[0];if[.db[.ctrl.O;k;`status] in .enum`NEW`PENDING_NEW;.db[.ctrl.O;k;`end`status`rtime`reason`msg]:(1b;.enum`REJECTED;.z.P),1_y];execrpt[k]];s=`RspOrderAction;if[not null k:exec first id from .db[.ctrl.O] where j1=h[0];if[.db[.ctrl.O;k;`cstatus] in .enum`PENDING_CANCEL;.db[.ctrl.O;k;`cstatus`rtime`reason`msg]:(.enum`REJECTED;.z.P),1_y];rejcrpt[k]];s=`RspLockStockApply;if[not null k:exec first id from .db[.ctrl.O] where j0=h[0];.db.O[k;`status`rtime`reason`msg]:(.enum`REJECTED;.z.P),1_y;execrpt[k];];s=`RspLockCompactSettle;if[not null k:exec first id from .db[.ctrl.O] where j1=h[0];if[.db[.ctrl.O;k;`cstatus] in .enum`PENDING_CANCEL;.db[.ctrl.O;k;`cstatus`rtime`reason`msg]:(.enum`REJECTED;.z.P),1_y];rejcrpt[k]];s=`RspCompactDirectRepay;[if[not null k:exec first id from .db[.ctrl.O] where j2=h[0];if[.db[.ctrl.O;k;`cstatus] in .enum`PENDING_REPLACE;.db[.ctrl.O;k;`cstatus`rtime`reason`msg]:(.enum`REJECTED;.z.P),1_y];rejrrpt[k]];if[not null k:exec first id from .db[.ctrl.O] where j0=h[0];.db[.ctrl.O;k;`status`rtime`reason`msg]:(.enum`REJECTED;.z.P),1_y];execrpt[k]];()];};

.upd.RspQryStkAcct:{[i;x]};

.upd.RspOrderInsert:{[i;x]x:x[2];if[0=count x;:()];.temp.L6,:enlist y:.enum.InsertKey!x;z:idfe2ft y`OrderRef`ExtOrderRef;if[null z;:()];.db[.ctrl.O;z;`rtime`status`rptopt`ordid`s0`s1`j2`j3]:(now[];.enum`NEW;dictstr .db[.ctrl.O;z;`x0;0]),(`$y`BrokerOrderID`ExtOrderRef),(`$string y[`ClientOrderID]),`long$y`OrderPartition`SessionID;execrpt[z];};

.upd.RspOrderAction:{[i;x]x:x[2];if[0=count x;:()];.temp.L7,:enlist y:.enum.ActionKey!x;z:idfe2ft y`OrigOrderRef`OrigExtOrderRef;if[null z;:()];.db[.ctrl.O;z;`cordid`cexchid`s3]:(`$y`BrokerOrderID;`$y`OrderID;`$string y`OrderPartition);};

.upd.RspQryFund:{[i;x]h:2#x;x:x[2];if[count x;.temp.L2,:enlist y:.enum.FundKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L2]];};

.upd.RspQryHold:{[i;x]h:2#x;x:x[2];if[count x;.temp.L3,:enlist y:.enum.HoldKey!x];if[(h[1])&not null z:.temp[`PosDst];pubmx[z;`PosUpdate;.conf.me;.temp[`PosAcc];-8!1!select sym:(`$StockCode) {sv[`]x,(`1`2!`XSHG`XSHE) y}' `$ExchangeID ,lqty:CurrentVolume,sqty:0f from .temp.L3]];};

.upd.RspQryFundPeer:{[i;x]h:2#x;x:x[2];if[count x;.temp.L18,:enlist y:.enum.FundPeerKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundPeerUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L18]];};

.upd.RspFundAlloc:{[i;x]h:2#x;x:x[2];if[count x;.temp.L19,:enlist y:.enum.FundAllocKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundAllocUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L19]];};

.upd.RspQryOrder:{[i;x]h:2#x;x:x[2];if[count x;.temp.L4,:enlist y:.enum.OrderKey!x];if[(h[1])&not null z:.temp[`OrdDst];pubmx[z;`OrdUpdate;.conf.me;.temp[`OrdAcc];-8!.temp.L4];if[not null z;.temp[`OrdDst]:`]];if[null z;.upd.RtnOrderTrade[i;x]];}; /

.upd.RspQryTrade:{[i;x]h:2#x;x:x[2];if[count x;.temp.L5,:enlist y:.enum.TradeKey!x];if[(h[1])&not null z:.temp[`MatDst];pubmx[z;`MatUpdate;.conf.me;.temp[`MatAcc];-8!.temp.L5];if[not null z;.temp[`MatDst]:`]];};

.upd.RtnOrderX:{[t;i;x].temp.L8,:enlist y:.enum.OrderKey!x;z:idfe2ft y`OrderRef`ExtOrderRef;r:.db[.ctrl.O;z];if[null r`sym;:()];t0:now[];st0:r`status;lq:0f^r`cumqty;lp:0f^r`avgpx;cq:y`TradeVolume;ca:y`BusinessBalance;st:.enum.ldpstatusmap y`OrderStatus;has:y`OrderAssStatus;if[(null .db[.ctrl.O;z;`t0])&has=.enum`HS_OCR_OrderConfirmed;.db[.ctrl.O;z;`t0]:t0];.db[.ctrl.O;z;`rtime`ordid]:(t0;`$y`BrokerOrderID);if[(null r`exchid)&not null k1:`$y`OrderID;.db[.ctrl.O;z;`exchid]:k1];if[(null r`cexchid)&has=.enum`HS_OCR_CancelConfirmed;.db[.ctrl.O;z;`cexchid]:`$y`OrderID];if[count m:y`ErrorMsg;.db[.ctrl.O;z;`msg]:m];.db[.ctrl.O;z;`rptopt],:"-",has;if[st=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:st];if[(not t)&(st=.enum`CANCELED)&(lq<cq);lwarn[`cxl_delay;(z;lq;cq)];.temp.DelayedCancel[z]:cq;:()];if[st in .enum`NEW`REJECTED`CANCELED;.db[.ctrl.O;z;`status]:st];if[t&lq<cq;.db[.ctrl.O;z;`ftime`lastqty`lastpx`cumqty`avgpx`status]:(t0;cq-lq;(ca-lp*lq)%(cq-lq);cq;ca%cq;$[st in .enum`PARTIALLY_FILLED`FILLED`CANCELED;st;.enum`PARTIALLY_FILLED])];if[t|not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];}; /t:是否在Order回报里更新成交信息

.upd.RtnOrder:.upd.RtnOrderX[.conf.ldp.bypassrtntrade];.upd.RtnOrderTrade:.upd.RtnOrderX[1b];

.upd.RtnTrade:{[i;x].temp.L9,:enlist y:.enum.TradeKey!x;if[1b~.conf.ldp`bypassrtntrade;:()];z:idfe2ft y`OrderRef`ExtOrderRef;r:.db[.ctrl.O;z];if[null fs:r`sym;:()];st0:r`status;cs0:r`cstatus;q:y`TradeVolume;p:y`TradePrice;lq:0f^r`cumqty;lp:0f^r`avgpx;cq:q+lq;.db[.ctrl.O;z;`ftime`lastqty`lastpx`cumqty`avgpx]:(now[];q;p;cq;((q*p)+(lq*lp))%cq);ldebug[`trade;(z;`$y`OrderRef;lq;q;r`cumqty)];st:.enum $[cq<r`qty;`PARTIALLY_FILLED;`FILLED];if[(st=.enum`FILLED)|(st=.enum`PARTIALLY_FILLED)&st0 in .enum`PENDING_NEW`NEW;.db[.ctrl.O;z;`status]:st];if[(cs0=.enum`CANCELED)&(st0<>.enum`CANCELED);if[.db[.ctrl.O;z;`cumqty]>=.temp.DelayedCancel[z];.db[.ctrl.O;z;`status]:.enum`CANCELED]];execrpt[z];}; /

//j0:reqid,j1:cxlreqid;j2:OrderPartition,j3:SessionID;s0:ExtOrderRef,s1:ClientOrderID

.upd.ordnew:.fe.ordnew:{[x].temp.x31:x;if[x[`sym]<>.conf.me;:.ha.ordnew[x]];if[null i:.ctrl.ldp.usermap u:x`acc1;:()];k:x`oid;if[count opt:x`ordopt;h:strdict opt;if[`LOCK~h`special;:.upd.locknew[x]]];k1:newidl0[];sid:.ctrl.ldp.api[i;`SessionID];.db[.ctrl.O;k;`feoid`ntime`status`j2`j3`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;`long$.enum`HS_OP_Secu;`long$sid;enlist .enum.nulldict,`ApiIdx`SessionID!i,sid),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ldp.api[i;`Login])&(.conf.ldp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"LDP_Not_Ready_Or_Toomany_Orders"];:()];if[@[riskassert;k;0b];rejectord[k;2i;"Reject_by_Tx_Risk_Check"];:()];esym:fs2s x`osym;ex:fs2e x`osym;hsex:.enum.ldpex ex;st:sectype[esym;hsex];it:`int$tif:x[`tif];if[.enum.MARGIN_REPAY=x`posefct;:newrepay[k]];r:ldpcall[i;`reqOrderInsert;(hsex;esym;.enum $[st=`STKHK;`HS_CT_LimitPFP;tif~.enum`IMMEDIATE_OR_CANCEL;`HS_CT_LimitFAK;it in .enum`HS_CT_MarketFOK`HS_CT_MarketFAK`HS_CT_Market5FAK`HS_CT_Market5ToLimit`HS_CT_MarketSelfToLimit`HS_CT_CounterPartyBest;.enum.ldpctmap it;`HS_CT_Limit];ldpside[x`side;x`posefct];x`price;x`qty;`;k1;0x00;`;ldpmemo[x];0i)];$[0<>r[0];[lerr[`reqOrderInsert;r];.db[.ctrl.O;k;`status`reason`msg]:(.enum`REJECTED;r[0];"api call reqOrderInsert rejected.");execrpt[k]];.db[.ctrl.O;k;`j0]:r[1]];}';


/$[ex=`XSHG;.conf.ldp.stkaccsh[i];.conf.ldp.stkaccsz[i]] .conf.ldp.userinfo，20231019:`$sublist[32] string sv[`;x`ft`ts`oid]

.upd.ordcxl:.fe.ordcxl:{[x].temp.x32:x;if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];if[@[riskassertcxl;k;0b];rejcxl[k;1i;"Reject_by_Risk_Check"];:()];if[`LOCK~r`special;:.upd.lockcxl[x]];.db[.ctrl.O;k;`cid`cstatus`ctime]:(x`cid;.enum`PENDING_CANCEL;.z.P);h:$[count r[`x0];r[`x0;0];strdict {(x?"-")#x} r`rptopt];r:ldpcall[i;`reqOrderAction;(.enum`HS_OP_Secu;r`ordid;h[`SessionID]^`int$r`j3;r`feoid;0j;.conf.ldp.apptype;.conf.ldp.userinfo;fs2s r`sym)];$[0<>r[0];[lerr[`reqOrderAction;r];.db[.ctrl.O;k;`cstatus`reason`msg]:(.enum`REJECTED;r[0];"api call reqOrderAction rejected.");rejcrpt[k]];.db[.ctrl.O;k;`j1]:r[1]];}';  /(OrderPartition=1;BrokerOrderID;SessionID;OrderRef;ClientOrderID=0;UserApplicationType;UserStationInfo;StockCode)

.upd.ordrpl:{[x].temp.x33:x;k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];if[`LOCK~r`special;:.upd.lockrtn[x]];}';

/Tx msg
.upd.QueryOrder:{[k].temp.L4:();.temp[`OrdDst]:`;r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];h:$[count r[`x0];r[`x0;0];strdict {(x?"-")#x} r`rptopt];ldpcall[i;`reqQryOrder;(.enum[`HS_OP_Secu]^`int$r`j2;r`ordid;`int$h[`SessionID]^r`j3;r`feoid;0^"J"$string r`s1)];}; /(OrderPartition;BrokerOrderID;SessionID;OrderRef;ClientOrderID)
.upd.ordqry:.fe.ordqry:{[x].upd.QueryOrder[x`oid];}';

.upd.QueryFund:{[x].temp.x11:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L2:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryFund;.enum`HS_CID_CNY];};

.upd.QueryPos:{[x].temp.x12:x;.temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryHold;2#`];};

.upd.QueryOrdAcc:{[x].temp.x13:x;.temp[`OrdDst`OrdAcc]:x`ref`msg;.temp.L4:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryOrder;(0i;`;0i;`;0)];};

.upd.QueryMatAcc:{[x].temp.x14:x;.temp[`MatDst`MatAcc]:x`ref`msg;.temp.L5:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryTrade;(0i;`;0i;`;0)];};

.upd.QueryFundPeer:{[x].temp.x15:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L18:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryFundPeer;(0i;.enum`HS_CID_CNY)];};

.upd.FundAlloc:{[x].temp.x16:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L19:();y:-9!x`vbin;if[null i:.ctrl.ldp.usermap u:y[0];:()];ldpcall[i;`reqFundAlloc;(.enum`HS_TD_In;.enum`HS_CID_CNY;y[1];0i)];};

//融券接口
.upd.QueryMargin:{[x].temp.x21:x;.temp[`MarDst`MarAcc]:x`ref`msg;.temp.L21:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryMargin;()];};
.upd.RspQryMargin:{[i;x]h:2#x;x:x[2];if[count x;.temp.L21,:enlist y:.enum.MarKey!x];if[(h[1])&not null z:.temp[`MarDst];pubmx[z;`MarginUpdate;.conf.me;.temp[`MarAcc];-8!.temp.L21]];};

.upd.QueryMarginQuote:{[x].temp.x22:x;.temp[`MQDst`MQAcc]:x`ref`msg;.temp.L22:();.temp[`MQPage`MQNum`MQPsn]:(0;0;0);if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];r:ldpcall[i;`reqQryLockStockQuote;(.temp`MQPsn;.conf.ldp.pagesize;`;`;`)];.temp[`MQReq]:r[1];};

.upd.RspQryLockStockQuote:{[i;x].temp.X22:x;h:2#x;x:x[2];if[n:count x;.temp.L22,:update page:.temp[`MQPage] from enlist y:.enum.MQKey!x;.temp.MQNum+:n];if[h[1];n1:.temp`MQNum;psn:$[n1;exec max PositionSn from .temp.L22;-1];if[((0=n1)|(psn<=.temp`MQPsn))&not null z:.temp[`MQDst];pubmx[z;`MarginQuoteUpdate;.conf.me;.temp[`MQAcc];-8!.temp.L22]];if[n1;if[psn>.temp`MQPsn;r:ldpcall[i;`reqQryLockStockQuote;(psn;.conf.ldp.pagesize;`;`;`)];.temp.MQPage+:1;.temp[`MQReq`MQNum`MQPsn]:(r[1];0;psn);]]];};

.upd.locknew:{[x].temp.x23:x;if[not null .db[.ctrl.O;k:x`oid;`sym];:()];k1:newidl0[];.db[.ctrl.O;k;`special`feoid`ntime`status`ft`ts`acc`acc1`sym`side`posefct`qty`price`ref]:(`LOCK;k1;.z.P;.enum`NEW),x`ft`ts`acc`acc1`osym`side`posefct`qty`price`ref;if[null i:.ctrl.ldp.usermap u:x`acc1;:()];k2:newidl[];r:ldpcall[i;`reqLockStockApply;enlist ("I"$string k1;x`qty;x`ref;x`price;k2)];$[0<>r[0];[lerr[`locknew;r];.db[.ctrl.O;k;`status`reason`msg]:(.enum`REJECTED;r[0];"api call reqBatchLockStockApply rejected.")];.db[.ctrl.O;k;`j0`s2]:(r[1];k2)];execrpt[k];}; /融券单票锁定

.upd.lockcxl:{[x].temp.x27:x;y:.db[.ctrl.O;k:x`oid];if[null y`sym;:()];if[null i:.ctrl.ldp.usermap u:y`acc1;:()];r:ldpcall[i;`reqLockCompactSettle;y`ordid];$[0<>r[0];[lerr[`lockcxl;r];.db[.ctrl.O;k;`cstatus`reason`msg]:(.enum`REJECTED;r[0];"api call reqLockStockCompactSettlement rejected.")];.db[.ctrl.O;k;`cstatus`j1]:(.enum`PENDING_CANCEL;r[1])];execrpt[k];}; /锁券了结

.upd.lockrtn:{[x].temp.x28:x;y:.db[.ctrl.O;k:x`oid];if[null s:y`sym;:()];if[null i:.ctrl.ldp.usermap u:y`acc1;:()];r:ldpcall[i;`reqCompactDirectRepay;(.enum.ldpex fs2e s;fs2s s;y`ordid;x`qty)];$[0<>r[0];[lerr[`lockrtn;r];.db[.ctrl.O;k;`cstatus`reason`msg]:(.enum`REJECTED;r[0];"api call reqDirectReturnStock rejected.")];.db[.ctrl.O;k;`cstatus`j2]:(.enum`PENDING_REPLACE;r[1])];execrpt[k];}; /直接还券(指定锁券合约还券)

.upd.RspLockStockApply:{[i;x].temp.X23:x;h:2#x;x:x[2];y:flip .enum.LockKey!flip x;{[x]if[null k:exec first id from .db.O where feoid=`$string x`BatchNo;:()];r:x`ErrorNo;.db.O[k;`ordid`status`reason]:(z:`$x`CompactID;.enum $[r;`REJECTED;`NEW];r);if[0<q:.temp.DelayedRtn[z];.db.O[k;`cumqty]:q;];execrpt[k];} each y;};

.upd.RspLockCompactSettle:{[i;x].temp.X25:x;h:2#x;x:x[2];y:x[0];if[null k:exec first id from .db.O where ordid=`$y;:()];if[not .enum.REJECTED=.db.O[k;`status];.db.O[k;`status]:.enum`CANCELED;execrpt[k]];};

.upd.RspCompactDirectRepay:{[i;x].temp.X26:x;h:2#x;x:x[2];y:flip .enum.RepayKey!flip x;{[x]if[null k:exec first id from .db.O where ordid=`$x`CompactID;:()];.db.O[k;`avgpx]:x`PostVolume;execrpt[k]} each y;if[null k:exec first id from .db.O where j0=h[0];:()];.db.O[k;`status`cumqty`avgpx]:(.enum.FILLED;exec sum OrderVolume from y;exec sum PostVolume from y);execrpt[k];};

.upd.QueryMarginLock:{[x].temp.x24:x;.temp[`MLDst`MLAcc]:x`ref`msg;.temp.L24:();.temp[`MLPage`MLNum`MLPsn]:(0;0;0);if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryLockCompact;(.temp`MLPsn;.conf.ldp.pagesize;`;`;`;0i;`)];.temp[`MLReq]:r[1];};

.upd.RspQryLockCompact:{[i;x].temp.X24:x;h:2#x;x:x[2];if[n:count x;.temp.L24,:update page:.temp.MLPage from enlist y:.enum.MLKey!x;.temp.MLNum+:n];if[h[1];n1:.temp`MLNum;psn:$[n1;exec max PositionSn from .temp.L24;-1];if[(0=n1)|(psn<=.temp`MLPsn)&not null z:.temp[`MLDst];pubmx[z;`MarginLockUpdate;.conf.me;.temp[`MLAcc];-8!.temp.L24]];if[n1;if[psn>.temp`MLPsn;r:ldpcall[i;`reqQryLockCompact;(psn;.conf.ldp.pagesize;`;`;`;0i;`)]];.temp.MLPage+:1;.temp[`MLReq`MLNum`MLPsn]:(r[1];0);psn]];};

.upd.RtnLockCompact:{[i;x].temp.X27:x;y:.enum.CompactKey!x;z:`$y`CompactID;w:`$y`CompactRef;if[null k:exec first id from .db.O where (ordid=z)|s2=w;.temp.DelayedRtn[z]:y`LockedVolume;:()];.db.O[k;`rptopt`status`cumqty`avgpx`msg]:(dictstr y;.enum.ldplockstatusmap y`LockCompactStatus),y`LockedVolume`BorrowedVolume`ErrorMsg;execrpt[k];};

newrepay:{[k]y:.db[.ctrl.O;k];if[null s:y`sym;:()];if[null i:.ctrl.ldp.usermap u:y`acc1;:()];r:ldpcall[i;`reqCompactDirectRepay;(.enum.ldpex fs2e s;fs2s s;`;y`qty)];$[0<>r[0];[lerr[`newrepay;r];.db[.ctrl.O;k;`cstatus`reason`msg]:(.enum`REJECTED;r[0];"api call reqDirectReturnStock rejected.")];.db[.ctrl.O;k;`status`j0]:(.enum`NEW;r[1])];execrpt[k];}; /[repay oid]非指定锁券合约还券


//----ChangeLog----
//2024.08.28:.upd.RtnOrderX增加对O表t0字段的赋值逻辑用以统计交易所确认时延
//2024.08.13:ldpmemo去掉对ft的编码以节约总编码长度,仅保留占位符
//2024.08.02:.upd.ordcxl增加ctime赋值
//2024.08.01:.upd.RspQryHold返回字段改为P表字段以便在ft里chkpos任务正常运行
//2024.07.23:.upd.ordnew/ordcxl增加对风控检查函数的调用
//2024.07.16:.upd.QueryOrder增加默认值填充以兼容feldp崩溃后从ft同步回来的O表;.upd.ordcxl/QueryOrder修正解析rptopt字段的bug
//2024.07.12:.upd.RtnOrderX更正有新成交且ldp订单状态为待撤的status
//2024.07.10:RtnOrderX更新exchid去掉has=.enum`HS_OCR_OrderConfirmed的条件以兼容在交易所确认前先收到撤单的情形;.upd.ordnew增加对O表`j2`j3初始化;.upd.RspOrderAction修正重复赋值`s1的bug;.upd.QueryOrder增加对s1为空的保护;RtnOrderX/RtnTrade调整更新status为`FILLED`PARTIALLY_FILLED的逻辑(bypassrtntrade时在RtnOrder否则在RtnTrade)
//2024.07.08:修复.upd.FrontDisconnected中的bug并增加告警;.conf.ldp.submodel从1(断点续传)变更为2(不续传)以防接口重启后回报重复处理;新增.conf.ldp.bypassrtntrade参数控制新成交处理是在rtnTrade还是rtnOrder(无法正常处理逆回购)
//2024.07.05:新增.upd.RtnOrderX用于支持在委托回报中同时兼容更新成交数量(对应单笔委托查询)和不更新成交数量(统一在成交回报里更新)
//2024.07.04:新增decmemo函数解析备注字段以支持过滤客户端委托的回报消息(OrdRef会与api委托重复);重定义idfe2ft函数并对应修改.upd.RspOrderInsert/RspOrderAction/RtnOrder/RtnTrade
//2024.04.17:.upd.lockrtn增加保护,代码和市场不再送空
//2024.04.11:.upd.locknew将CompactRef保存至O表`s2,.upd.RtnLockCompact增加使用s2的匹配和`ErrorMsg保存至O表msg
//2024.04.09:TradeKey新增`SumCashBalance`CompactID(对应修改extfeldp.cpp的OnRspQryTrade/OnRtnTrade);LockKey新增`CompactRef/.upd.locknew增加送全局id(对应修改extfeldp.cpp的reqLockStockApply/OnRspLockStockApply);CompactKey新增`CompactRef`ErrorMsg/.upd.QueryMarginLock新增过滤条件CreateDate和CompactRef送空/.upd.RspQryLockCompact(对应修改extfeldp.cpp的reqQryLockCompact/OnRspQryLockCompact/OnRtnLockCompact)
//2024.03.26:新增ldpmemo函数支持恒生备注字段兼容性处理并相应修改.upd.ordnew
//2023.12.18:无锁券ID快速还券接口:.upd.lockrtn支持送市场+代码/.upd.RspCompactDirectRepay支持多笔流水(extfeldp.cpp对应修改/reqCompactDirectRepay/OnRspCompactDirectRepay);新增newrepay
//2023.12.04:
//2023.11.28:新增导入reqBatchLockStockApply`reqDirectReturnStock`reqLockStockCompactSettlement`reqPageQryLockStockQuote`reqPageQryLockStockCompact`reqQryMarginFundReal共6个接口函数;新增.upd.QueryMargin和.upd.RspQryMarginFundReal函数;新增.upd.locknew/.upd.RspBatchLockStockApply/.upd.RspLockStockCompactSettlement函数,.upd.ordnew/.upd.ordcxl/.upd.ordrpl增加对`LOCK支持,更新.upd.LdpError,新增.upd.QueryMarginLock/.upd.RspPageQryLockStockCompact函数;新增.upd.RtnLockCompact函数

//2023.11.23:增加.enum`HS_OD_BorrowSell枚举和ldpside函数,.upd.ordnew相应更改side映射
//2023.10.20:.upd.LdpError的告警输出过滤掉撤单拒绝
//2023.10.19:.upd.ordnew去掉对ExtOrderRef的赋值,否则ldp回补到i2有问题
//2023.08.29:.upd.ordnew和.upd.ordcxl增加对api返回值的检查处理,新增.disp.feldp函数
