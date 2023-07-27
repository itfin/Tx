.module.feldp:2023.07.01;

txload "core/febase";

`ldpapiver`ldperrmsg`startstat`stopstat`exportstat`freeldp`ldprun`initldp`reqAuthenticate`reqUserLogin`reqQryStkAcct`reqOrderInsert`reqOrderAction`reqQryHold`reqQryFund`reqQryOrder`reqQryTrade`reqFundAlloc`reqQryFundPeer {x set `extfeldp 2:(x;y);}' (7#1),12#2;

.ctrl.ldp.api:(0N,til[count[.conf.ldp.user]])!enlist[::],(count[.conf.ldp.user])#enlist .enum.nulldict;
.ctrl.ldp.usermap:{x!til count x} .conf.ldp.user;

ldpcall:{[i;x;y]k:newseq[];.temp.r:r:(value x)[`int$k,i;y,$[0=type y;();enlist (::)]];.temp.C,:enlist (r;.z.P;i;k;x;y);(r;k;i)};
onldp:{[x].temp.X:x;if[.conf.ldp.debug;.temp.L,:(enlist .z.P),/:x];{[x](.upd[x[0]])[x[1];x[2]]} each x;};

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
`HS_EI_SSE`HS_EI_SZSE`HS_EI_TZASE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE`HS_EI_GFEX`HS_EI_SSEHK`HS_EI_SZSEHK set' `1`2`9`G`S`F1`F2`F3`F4`F5`F6`G`S; /HSExchangeID
(HSCTENUMS:`HS_CT_Limit`HS_CT_LimitFOK`HS_CT_LimitFAK`HS_CT_LimitStopLoss`HS_CT_LimitStopProfit`HS_CT_Market`HS_CT_MarketFOK`HS_CT_MarketFAK`HS_CT_MarketFAKV`HS_CT_MarketStopLoss`HS_CT_MarketStopProfit`HS_CT_MarketToLimit`HS_CT_Market5FAK`HS_CT_Market5ToLimit`HS_CT_Market1ToLimit`HS_CT_Market1FAK`HS_CT_Market1FOK`HS_CT_MarketSelfToLimit`HS_CT_CounterPartyBest`HS_CT_LimitFAKV`HS_CT_LimitPFP`HS_CT_HkAtCrossingLimitGFD`HS_CT_HkAtCrossingLimitFOK`HS_CT_HkDayLimit`HS_CT_TAS`HS_CT_BJSGZLimit`HS_CT_BlockIntention`HS_CT_BlockPricing`HS_CT_BlockConfirm`HS_CT_BlockMutualConfirm`HS_CT_BlockAFC`HS_CT_BlockAFW) set' `int$1+til 32; /HSOrderCommand
`HS_OD_Buy`HS_OD_Sell`HS_OD_Apply`HS_OD_MarthSecu`HS_OD_BondConv`HS_OD_BondCall`HS_OD_PledgeIn`HS_OD_PledgeOut`HS_OD_Repos`HS_OD_ReverseRepos`HS_OD_EtfSubs`HS_OD_EtfPur`HS_OD_EtfRed`HS_OD_BondCallCan`HS_OD_LofSubs`HS_OD_LofPur`HS_OD_LofRed`HS_OD_LofTrams`HS_OD_FundSplit`HS_OD_FundMerger`HS_OD_FundConv`HS_OD_CurrFundPur`HS_OD_CurrFundRed`HS_OD_CreditBuy`HS_OD_CreditSell`HS_OD_CollateralIn`HS_OD_CollateralOut`HS_OD_MarginBuy`HS_OD_ShortSell`HS_OD_SellRepay`HS_OD_BuyRepay`HS_OD_HoldRepay`HS_OD_HkBuyRound`HS_OD_HkSellRound`HS_OD_HkSellOddLot`HS_OD_CBPOF_OFC`HS_OD_CBPOF_OFR`HS_OD_ReitsFundSubs`HS_OD_OFundSubs set' `int$(1+til 14),(16+til 9),33+til 16; /HSOrderDirection
`HS_OP_Secu`HS_OP_SecuAfof`HS_OP_SecuCbp`HS_OP_SecuHk`HS_OP_Crdt`HS_OP_CrdtAfof`HS_OP_CrdtCbp`HS_OP_SecuBt set' `int$1+til 8; /HSOrderPartition
`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed set' "0123456789DUVW"; /HSOrderStatus
`HS_OCR_OrderInserted`HS_OCR_OrderReported`HS_OCR_OrderConfirmed`HS_OCR_OrderTraded`HS_OCR_OrderAbandoned`HS_OCR_CancelInserted`HS_OCR_CancelReported`HS_OCR_CancelConfirmed`HS_OCR_CancelFailed set' "012345678"; /HSOrderAssStatus

`HS_OF_Open`HS_OF_Close`HS_OF_Delivery`HS_OF_CloseToday`HS_OF_CloseSingle set' "12346"; /HSOffsetFlag
`HS_CID_CNY`HS_CID_USD`HS_CID_HKD set' "012"; /HSCurrencyID
`HS_TD_In`HS_TD_Out set' "01"; /HSTransDirection

OrderKey:`TradingDay`AccountID`OrderPartition`BrokerOrderID`SessionID`OrderRef`ExchangeID`StockAccount`StockCode`Direction`OrderPrice`OrderVolume`OrderStatus`OrderCommand`ReportTime`ErrorMsg`TradeVolume`BatchNo`WithdrawVolume`OrderTime`BrokerWithdrawOrderID`FrozenBalance`FrozenFare`BranchID`OrderAssStatus`WithdrawOrderStatus`OccurTime`ClientOrderID`StockName`TradePrice`BusinessBalance`StockType`OrderID`CashgroupProp`ExtOrderRef`TotalBusinessFare`SequenceNumber`UserApplicationType`RenewFlag`StrategyId`TotalRealBuyBalance`TotalRealSellBalance`SystemNo`ErrorNo;

TradeKey:`TradingDay`AccountID`OrderPartition`BrokerOrderID`SessionID`OrderRef`ExchangeID`StockAccount`StockCode`Direction`OrderCommand`TradeStatus`TradeID`TradeVolume`TradePrice`TradeTime`ErrorMsg`BatchNo`BrokerWithdrawOrderID`BusinessBalance`BranchID`OrderStatus`OccurTime`ClientOrderID`StockName`OrderPrice`OrderID`ExtOrderRef`TotalBusinessFare`SequenceNumber`RealBuyAmount`RealBuyBalance`RealSellAmount`RealSellBalance`UserApplicationType`RenewFlag`StrategyId`SystemNo;

InsertKey:`OrderPartition`BrokerOrderID`SessionID`OrderRef`BatchNo`ClientOrderID`OrderID`ExtOrderRef;
ActionKey:`OrderPartition`BrokerOrderID`OrigOrderPartition`OrigBrokerOrderID`OrigSessionID`OrigOrderRef`OrigClientOrderID`OrderID`OrigBatchNo`OrigExtOrderRef;

FundKey:`CurrencyID`CurrentBalance`BeginBalance`AvailableBalance`FetchBalance`MarketValue`TotalAsset`CorrectBalance;
HoldKey:`AccountID`ExchangeID`StockAccount`StockCode`StockName`StockType`CurrentVolume`AvailableVolume`AvBuyPrice`AssetPrice`AchvProfit`BeginVolume`RealBuyVolume`RealSellVolume`UncomeBuyVolume`UncomeSellVolume`FloatProfit`MarketValue`LastPrice`DelistDate`CorrectVolume`ETFPurRedAvailableVolume`FrozenVolume`CostBalance`FinCompactAmount`FinUncomeAmount`FinCurrentAmount`FinMarketValue`CsfcSloAmount`SloMarketValue`SumBuyAmount`SumBuyBalance`SumSellAmount`SumSellBalance`StockNameShort`RealBuyBalance`RealSellBalance;
FundPeerKey:`CurrentBalance`AvailableBalance`CurrencyID;
FundAllocKey:`TransSerialID`FundUnused;
\d .

.enum.ldpexmap:.enum[`HS_EI_SSE`HS_EI_SZSE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE]!`XSHG`XSHE`XHKG`XHKE`XZCE`XDCE`XSGE`CCFX`XINE;
.enum.ldpex:mirror .enum.ldpexmap;

.enum.ldpstatusmap:.enum[`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed]!.enum`PENDING_NEW`PENDING_NEW`NEW`PENDING_CANCEL`PENDING_CANCEL`CANCELED`CANCELED`PARTIALLY_FILLED`FILLED`REJECTED`REJECTED_CANCEL`PENDING_CANCEL`NEW`NEW;

.enum.ldpctmap:.enum[.enum.HSCTENUMS]!.enum.HSCTENUMS;

sectype:{[x;y]$[y in `F1`F2`F3`F4`F5`F6;$[(x like "IO*")|(x like "*-*")|(x like "*[0-9]C[0-9]*")|(x like "*[0-9]P[0-9]*");`OPT;x like "SP*";`FUTSP;`FUT];y in `1`2;$[8=count string x;`OPT;`STK];y in `G`S;`STKHK;`STK]}; /[sym;hsex]

ldpposefct:{[x;y]$[x=.enum`OPEN;.enum`HS_OF_Open;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`HS_OF_CloseToday;.enum`HS_OF_Close]}; /[posefct;ex]

ldpconn:{[x;y]if[not any .z.T within/: .conf.ldp.openrange;:()];.ctrl.ldp[`Run]:initldp[.conf.ldp`apiflow`fens`submodel;.conf.ldp`user];1b;};
ldpdisc:{[x;y]if[any .z.T within/: .conf.ldp.openrange;:()];savedb[];.ctrl.ldp[`Run]:freeldp[];1b};

.init.feldp:{[x]ldpconn[`;.z.P];};
.exit.feldp:{[x]ldpdisc[`;.z.P];};
.timer.feldp:{[x];}; 
.roll.feldp:{[x];};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

/ldp msg
.upd.FrontConnected:{[i;x].temp.i:i;.temp.x:x;.ctrl.ldp.api[i]:`user`Connect`Conntime!(.conf.ldp.user[i];1b;.z.P);ldpcall[i;`reqAuthenticate;.conf.ldp.user[i],.conf.ldp.appid[i],.conf.ldp.auth[i]];};

.upd.FrontDisconnected:{[i;x].ctrl.ldp.api[i;`Connect`Login`DiscReason`Disctime]:(0b;0b;y[0];.z.P);};

.upd.RspAuthenticate:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`AuthTime`AccountID`AppID`AuthCode]:.z.P,y;ldpcall[i;`reqUserLogin;(.conf.ldp.user[i];.conf.ldp.pass[i]),.conf.ldp`apptype`appinfo`macaddr`ipsddr`userinfo];};

.upd.RspUserLogin:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`Login`LoginTime`BranchID`AccountID`AssetProp`UserName`TradingDay`OrderRef`SessionID`UserID`CorpRiskLevel`UserNameLong]:(1b;.z.P),y;};

.upd.LdpError:{[i;x]lwarn[`LdpError;x];.temp.X:x;h:2#x;y:x[2];s:`$y[0];if[s=`RspOrderInsert;if[not null k:exec first id from .db[.ctrl.O] where j0=h[0];if[.db[.ctrl.O;k;`status] in .enum`NEW`PENDING_NEW;.db[.ctrl.O;k;`end`status`rtime`reason`msg]:(1b;.enum`REJECTED;.z.P),1_y];execrpt[k]]];};

.upd.RspQryStkAcct:{[i;x]};

.upd.RspOrderInsert:{[i;x]x:x[2];if[0=count x;:()];.temp.L6,:enlist y:.enum.InsertKey!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db[.ctrl.O;z;`rtime`status`rptopt`ordid`s0`j0`j1`j2`j3]:(now[];.enum`NEW;dictstr .db[.ctrl.O;z;`x0;0]),(`$y`BrokerOrderID`ExtOrderRef),y[`ClientOrderID],`long$y`OrderPartition`SessionID`BatchNo;execrpt[z];};

.upd.RspOrderAction:{[i;x]x:x[2];if[0=count x;:()];.temp.L7,:enlist y:.enum.ActionKey!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db[.ctrl.O;z;`cordid`cexchid`s1]:(`$y`BrokerOrderID;`$y`OrderID;`$string y`OrderPartition);};

.upd.RspQryFund:{[i;x]h:2#x;x:x[2];if[count x;.temp.L2,:enlist y:.enum.FundKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L2]];};

.upd.RspQryHold:{[i;x]h:2#x;x:x[2];if[count x;.temp.L3,:enlist y:.enum.HoldKey!x];if[(h[1])&not null z:.temp[`PosDst];pubmx[z;`PosUpdate;.conf.me;.temp[`PosAcc];-8!.temp.L3]];};

.upd.RspQryFundPeer:{[i;x]h:2#x;x:x[2];if[count x;.temp.L18,:enlist y:.enum.FundPeerKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundPeerUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L18]];};

.upd.RspFundAlloc:{[i;x]h:2#x;x:x[2];if[count x;.temp.L19,:enlist y:.enum.FundAllocKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundAllocUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L19]];};

.upd.RspQryOrder:{[i;x]h:2#x;x:x[2];if[count x;.temp.L4,:enlist y:.enum.OrderKey!x];if[(h[1])&not null z:.temp[`OrdDst];pubmx[z;`OrdUpdate;.conf.me;.temp[`OrdAcc];-8!.temp.L4];if[not null z;.temp[`OrdDst]:`]];}; /.upd.RtnOrder[i;x];

.upd.RspQryTrade:{[i;x]h:2#x;x:x[2];if[count x;.temp.L5,:enlist y:.enum.TradeKey!x];if[(h[1])&not null z:.temp[`MatDst];pubmx[z;`MatUpdate;.conf.me;.temp[`MatAcc];-8!.temp.L5];if[not null z;.temp[`MatDst]:`]];};

.upd.RtnOrder:{[i;x].temp.L8,:enlist y:.enum.OrderKey!x;z:idfe2ft `$y`OrderRef;r:.db[.ctrl.O;z];if[null r`sym;:()];st:.enum.ldpstatusmap y`OrderStatus;has:y`OrderAssStatus;.db[.ctrl.O;z;`rtime`ordid]:(now[];`$y`BrokerOrderID);if[(null r`exchid)&has=.enum`HS_OCR_OrderConfirmed;.db[.ctrl.O;z;`exchid]:`$y`OrderID];if[(null r`cexchid)&has=.enum`HS_OCR_CancelConfirmed;.db[.ctrl.O;z;`cexchid]:`$y`OrderID];if[count m:y`ErrorMsg;.db[.ctrl.O;z;`msg]:m];.db[.ctrl.O;z;`rptopt],:"-",has;if[st=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:st];if[(st=.enum`CANCELED)&((.db[.ctrl.O;z;`cumqty]|0f)<cq:y`TradeVolume);.temp.DelayedCancel[z]:cq;:()];st0:.db[.ctrl.O;z;`status];if[st in .enum`NEW`REJECTED`CANCELED`FILLED;.db[.ctrl.O;z;`status]:st];if[(st in .enum`PARTIALLY_FILLED)&st0 in .enum`PENDING_NEW`NEW;.db[.ctrl.O;z;`status]:st];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.RtnTrade:{[i;x].temp.L9,:enlist y:.enum.TradeKey!x;z:idfe2ft `$y`OrderRef;if[(null fs:.db[.ctrl.O;z;`sym]);:()];q:y`TradeVolume;p:y`TradePrice;lq:0f^.db[.ctrl.O;z;`cumqty];lp:0f^.db[.ctrl.O;z;`avgpx];if[(fs like "SP*")|(fs like "IPS*");s0:`$y`InstrumentID;s1:first sl:`$"&" vs last " " vs string fs2s fs;s2:last sl;if[0=count .db[.ctrl.O;z;`x0];.db[.ctrl.O;z;`x0]:enlist .enum`nulldict];qfld:$[s0=s1;`lcumqty;`scumqty];pfld:$[s0=s1;`lavgpx;`savgpx];lq0:0f^ffill .db[.ctrl.O;z;`x0;0;qfld];.db[.ctrl.O;z;`x0]:enlist .db[.ctrl.O;z;`x0;0],(qfld,pfld)!(q+lq0;((q*p)+lq0*0f^ffill .db[.ctrl.O;z;`x0;0;pfld])%(q+lq0));$[(cq<=lq)|((0f^ffill .db[.ctrl.O;z;`x0;0;`lcumqty])<>cq:0f^ffill .db[.ctrl.O;z;`x0;0;`scumqty]);:();[q:cq-lq;p:((cq*(0f^ffill .db[.ctrl.O;z;`x0;0;`lavgpx])-0f^ffill .db[.ctrl.O;z;`x0;0;`savgpx])-lq*lp)%q]]];.db[.ctrl.O;z;`ftime`lastqty`lastpx`cumqty`avgpx]:(now[];q;p;q+lq;((q*p)+(lq*lp))%(q+lq));ldebug[`trade;(z;`$y`OrderRef;lq;q;.db[.ctrl.O;z;`cumqty])];if[(.db[.ctrl.O;z;`cstatus]=.enum`CANCELED)&(.db[.ctrl.O;z;`status]<>.enum`CANCELED);if[.db[.ctrl.O;z;`cumqty]>=.temp.DelayedCancel[z];.db[.ctrl.O;z;`status]:.enum`CANCELED]];execrpt[z];}; /对SP单进行特殊处理,前腿(买单)的cumqty/avgpx记入O表的lcumqty/lavgpx字段,后腿(卖单)的scumqty/savgpx记入O表的sentqty/takepx字段,当双腿的成交量一致时更新SP单的的对应信息并推送回报 

.upd.ordnew:.fe.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];if[(null i:.ctrl.ldp.usermap u:x`acc1);:()];k:x`oid;if[count opt:x`ordopt;h:strdict opt];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict,`ApiIdx`SessionID!i,.ctrl.ldp.api[i;`SessionID]),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ldp.api[i;`Login])&(.conf.ldp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"LDP_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;hsex:.enum.ldpex ex;st:sectype[esym;hsex];it:`int$tif:x[`tif];r:ldpcall[i;`reqOrderInsert;(hsex;esym;.enum $[st=`STKHK;`HS_CT_LimitPFP;tif~.enum`IMMEDIATE_OR_CANCEL;`HS_CT_LimitFAK;it in .enum`HS_CT_MarketFOK`HS_CT_MarketFAK`HS_CT_Market5FAK`HS_CT_Market5ToLimit`HS_CT_MarketSelfToLimit`HS_CT_CounterPartyBest;.enum.ldpctmap it;`HS_CT_Limit];.enum $[x[`side]=.enum`BUY;`HS_OD_Buy;`HS_OD_Sell];x`price;x`qty;`;k1;0x00;`;`$sublist[32] string sv[`;x`ft`ts`oid];0i)];.db[.ctrl.O;k;`j0]:`int$r[1];}';  /$[ex=`XSHG;.conf.ldp.stkaccsh[i];.conf.ldp.stkaccsz[i]] .conf.ldp.userinfo

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];.db[.ctrl.O;k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];ldpcall[i;`reqOrderAction;(.enum`HS_OP_Secu;r`ordid;h`SessionID;r`feoid;0j;.conf.ldp.apptype;.conf.ldp.userinfo;fs2s r`sym)];}'; 

/Tx msg
.upd.QueryOrder:{[k].temp.L4:();r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];ldpcall[i;`reqQryOrder;(`int$r`j1;r`ordid;`int$j2;r`feoid;r`j0)];};
.upd.ordqry:.fe.ordqry:{[x].upd.QueryOrder[x`oid];}';

.upd.QueryFund:{[x].temp.x11:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L2:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryFund;.enum`HS_CID_CNY];};

.upd.QueryPos:{[x].temp.x12:x;.temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryHold;2#`];};

.upd.QueryOrdAcc:{[x].temp.x13:x;.temp[`OrdDst`OrdAcc]:x`ref`msg;.temp.L4:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryOrder;(0i;`;0i;`;0)];};

.upd.QueryMatAcc:{[x].temp.x14:x;.temp[`MatDst`MatAcc]:x`ref`msg;.temp.L5:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryTrade;(0i;`;0i;`;0)];};


.upd.QueryFundPeer:{[x].temp.x15:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L18:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryFundPeer;(0i;.enum`HS_CID_CNY)];};

.upd.FundAlloc:{[x].temp.x16:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L19:();y:-9!x`vbin;if[null i:.ctrl.ldp.usermap u:y[0];:()];ldpcall[i;`reqFundAlloc;(.enum`HS_TD_In;.enum`HS_CID_CNY;y[1];0i)];};
