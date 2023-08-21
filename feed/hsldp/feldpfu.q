.module.feldpfu:2023.08.17;

txload "core/febase";

`ldpapiver`ldperrmsg`freeldp`ldprun`initldp`reqAuthenticate`reqSubmitUserSystemInfo`reqUserLogin`reqOrderInsert`reqOrderAction`reqQryPosition`reqQryTradingAccount`reqQryOrder`reqQryTrade`ctpsysinfo {x set $[1b~.conf.ldp.futestmode;`extfeldpfutest;`extfeldpfu] 2:(x;y);}' (4#1),(10#2),1; 

.ctrl.ldp.api:(0N,til[count[.conf.ldp.user]])!enlist[::],(count[.conf.ldp.user])#enlist .enum.nulldict;
.ctrl.ldp.usermap:{x!til count x} .conf.ldp.user;

ldpcall:{[i;x;y]k:newseq[];.temp.r:r:(value x)[`int$k,i;y,$[0=type y;();enlist (::)]];.temp.C,:enlist (r;.z.P;i;k;x;$[x=`reqSubmitUserSystemInfo;();y]);(r;k;i)};
onldp:{[x].temp.X:x;if[.conf.ldp.debug;.temp.L,:(enlist .z.P),/:x];@[{[x](.upd[x[0]])[x[1];x[2]]};;()] each x;};

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
`HS_EI_SSE`HS_EI_SZSE`HS_EI_TZASE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE`HS_EI_GFEX`HS_EI_SSEHK`HS_EI_SZSEHK set' `1`2`9`G`S`F1`F2`F3`F4`F5`F6`G`S; /HSExchangeID
`HS_CT_Limit`HS_CT_LimitFOK`HS_CT_LimitFAK`HS_CT_LimitStopLoss`HS_CT_LimitStopProfit`HS_CT_Market`HS_CT_MarketFOK`HS_CT_MarketFAK`HS_CT_MarketFAKV`HS_CT_MarketStopLoss`HS_CT_MarketStopProfit`HS_CT_MarketToLimit`HS_CT_Market5FAK`HS_CT_Market5ToLimit`HS_CT_Market1ToLimit`HS_CT_Market1FAK`HS_CT_Market1FOK`HS_CT_MarketSelfToLimit`HS_CT_CounterPartyBest`HS_CT_LimitFAKV`HS_CT_LimitPFP`HS_CT_HkAtCrossingLimitGFD`HS_CT_HkAtCrossingLimitFOK`HS_CT_HkDayLimit`HS_CT_TAS`HS_CT_BJSGZLimit`HS_CT_BlockIntention`HS_CT_BlockPricing`HS_CT_BlockConfirm`HS_CT_BlockMutualConfirm`HS_CT_BlockAFC`HS_CT_BlockAFW set' `int$1+til 32; /HSOrderCommand
`HS_OP_Secu`HS_OP_SecuAfof`HS_OP_SecuCbp`HS_OP_SecuHk`HS_OP_Crdt`HS_OP_CrdtAfof`HS_OP_CrdtCbp`HS_OP_SecuBt set' `int$1+til 8; /HSOrderPartition
`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed set' "0123456789DUVW"; /HSOrderStatus
`HS_OF_Open`HS_OF_Close`HS_OF_Delivery`HS_OF_CloseToday`HS_OF_CloseSingle set' "12346"; /HSOffsetFlag
`HS_CID_CNY`HS_CID_USD`HS_CID_HKD set' "012"; /HSCurrency
`HS_HT_Speculation`HS_HT_Hedge`HS_HT_Arbitrage`HS_HT_MarketMaker`HS_HT_Covered set' "01234"; /HSHedgeType
`HS_SOF_Normal`HS_SOF_Swap set' "01"; /HSSwapOrderFlag
`HS_DC_Buy`HS_DC_Sell`HS_DC_Loan`HS_DC_Borrow set' "12FG"; /HSDirection 

OrderKey:`AccountID`OrderSysID`BrokerOrderID`SessionID`OrderRef`ExchangeID`InstrumentID`Direction`OffsetFlag`HedgeType`OrderPrice`OrderVolume`OrderStatus`TradeVolume`CancelVolume`TradePrice`TradingDay`InsertDate`InsertTime`ReportTime`OrderCommand`MinVolume`SpringPrice`SwapOrderFlag`ForceCloseReason`ErrorMsg`UnderlyingInstrID`OrderSource`CombPositionID`ExchangeAccountID`SeatIndex;

TradeKey:`AccountID`TradeID`OrderSysID`BrokerOrderID`SessionID`OrderRef`ExchangeID`InstrumentID`Direction`OffsetFlag`HedgeType`TradeVolume`TradePrice`TradingDay`TradeTime`UnderlyingInstrID`CombPositionID`TradeCommission`ExchangeAccountID;

InsertKey:`AccountID`OrderSysID`BrokerOrderID`SessionID`OrderRef`InstrumentID`ExchangeID`Direction`OffsetFlag`HedgeType`OrderPrice`OrderVolume`OrderStatus`OrderCommand`InsertTime`MinVolume`SpringPrice`SwapOrderFlag`CombPositionID`ExchangeAccountID`SeatIndex;
ActionKey:`AccountID`OrderSysID`ExchangeID`SessionID`OrderRef`OrderStatus`InsertTime`OrderActionRef;

FundKey:`AccountID`YdBalance`YdPositionMargin`YdFundEquity`FundEquity`OptionsMarketValue`Equity`AvailableBalance`WithdrawBalance`Margin`FrozenMargin`ExerciseFrozenMargin`RiskDegree`Premium`FrozenPremium`Commission`FrozenCommission`CloseProfit`PositionProfit`CloseProfitByDate`PositionProfitByDate`Deposit`Withdraw`FundMortgage`WarrantMortgage`FrozenBalance`UnFrozenBalance`CurrencyID`HedgeRiskDegree`ShUsedBuyQuota`SzUsedBuyQuota`ShAvailableBuyQuota`SzAvailableBuyQuota;

HoldKey:`AccountID`ExchangeID`InstrumentID`Direction`HedgeType`YdPositionVolume`PositionVolume`TodayPositionVolume`AvailablePositionVolume`TodayAvailablePositionVolume`PositionMargin`Premium`Commission`OpenFrozenVolume`CloseFrozenVolume`CombVolume`ExerciseFrozenVolume`FrozenMargin`ExerciseFrozenMargin`FrozenPremium`FrozenCommission`OpenVolume`CloseVolume`OpenBalance`CloseBalance`OpenCost`PositionCost`PositionProfit`CloseProfit`OptionsMarketValue`UnderlyingInstrID`TASPositionVolume;

\d .

.enum.ldpexmap:.enum[`HS_EI_SSE`HS_EI_SZSE`HS_EI_SHHKSE`HS_EI_SZHKSE`HS_EI_CZCE`HS_EI_DCE`HS_EI_SHFE`HS_EI_CFFEX`HS_EI_INE]!`XSHG`XSHE`XHKG`XHKE`XZCE`XDCE`XSGE`CCFX`XINE;
.enum.ldpex:mirror .enum.ldpexmap;

.enum.ldpstatusmap:.enum[`HS_OS_NotReported`HS_OS_ToBeReported`HS_OS_Reported`HS_OS_ReportedToBeCancel`HS_OS_PartsTradedToBeCancel`HS_OS_CanceledWithPartsTraded`HS_OS_Canceled`HS_OS_PartsTraded`HS_OS_Traded`HS_OS_Abandoned`HS_OS_CancelFailed`HS_OS_ConfirmedToBeCancel`HS_OS_Confirmed`HS_OS_ToBeConfirmed]!.enum`PENDING_NEW`PENDING_NEW`NEW`PENDING_CANCEL`PENDING_CANCEL`CANCELED`CANCELED`PARTIALLY_FILLED`FILLED`REJECTED`REJECTED_CANCEL`PENDING_CANCEL`NEW`NEW;

sectype:{[x;y]$[y in `F1`F2`F3`F4`F5`F6;$[(x like "IO*")|(x like "*-*")|(x like "*[0-9]C[0-9]*")|(x like "*[0-9]P[0-9]*");`OPT;x like "SP*";`FUTSP;`FUT];y in `1`2;$[8=count string x;`OPT;`STK];y in `G`S;`STKHK;`STK]}; /[sym;hsex]

ldpposefct:{[x;y]$[x=.enum`OPEN;.enum`HS_OF_Open;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`HS_OF_CloseToday;.enum`HS_OF_Close]}; /[posefct;ex]

ldpconn:{[x;y]if[not any .z.T within/: .conf.ldp.openrange;:()];.ctrl.ldp[`Run]:initldp[.conf.ldp`apiflow`usefens`front`submodel`licfile`safelevel`commpass`certfile`certpass;.conf.ldp`user];1b;};
ldpdisc:{[x;y]:();if[any .z.T within/: .conf.ldp.openrange;:()];savedb[];.ctrl.ldp[`Run]:freeldp[];1b};

.init.feldp:{[x]ldpconn[`;.z.P];};
.exit.feldp:{[x]ldpdisc[`;.z.P];system "kill -9 ",string .z.i;};
.timer.feldp:{[x];}; 
.roll.feldp:{[x];};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

/ldp msg
.upd.FrontConnected:{[i;x].temp.i:i;.temp.x:x;.ctrl.ldp.api[i]:`user`Connect`Conntime!(.conf.ldp.user[i];1b;.z.P);ldpcall[i;`reqAuthenticate;.conf.ldp.acc[i],.conf.ldp.pass[i],.conf.ldp.appid[i],.conf.ldp.auth[i]];};

.upd.FrontDisconnected:{[i;x].ctrl.ldp.api[i;`Connect`Login`DiscReason`Disctime]:(0b;0b;y[0];.z.P);};

.upd.RspAuthenticate:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`AuthTime`AccountID`AppID`AuthCode]:.z.P,y;ldpcall[i;`reqSubmitUserSystemInfo;(`$string .z.P;.conf.ldp`pubaddr;`$ctpsysinfo[];`;0x00)];};

.upd.RspSubmitUserSystemInfo:{[i;x]ldpcall[i;`reqUserLogin;(.conf.ldp.user[i];.conf.ldp.pass[i]),.conf.ldp`apptype`appinfo`macaddr`ipsddr`userinfo];};

.upd.RspUserLogin:{[i;x]y:x[2];if[0=count y;:()];.ctrl.ldp.api[i;`Login`LoginTime`BranchID`AccountID`UserName`TradingDay`PreTradingDay`BillConfirmFlag`SessionID`UserApplicationType`UserApplicationInfo`RiskLevel`LastMacAddress`LastIPAddress`LastLoginTime`CZCETime`DCETime`SHFETime`CFFEXTime`INETime`MaxOrderRef`UserID`GFEXTime]:(1b;.z.P),y;};

.upd.LdpError:{[i;x].temp.X:x;h:2#x;y:x[2];s:`$y[0];lwarn[`LdpError;.temp.X];if[s=`RspErrorOrderInsert;if[not null k:exec first id from .db[.ctrl.O] where j0=h[0];if[.db[.ctrl.O;k;`status] in .enum`NEW`PENDING_NEW;.db[.ctrl.O;k;`end`status`rtime`reason`msg]:(1b;.enum`REJECTED;.z.P),1_y];execrpt[k]]];};

.upd.RspErrorOrderInsert:{[i;x]x:x[2];if[0=count x;:()];.temp.L6,:enlist y:.enum.InsertKey!x;z:exec first id from .db.O where ordid=`$y`OrderSysID;if[null z;:()];.db[.ctrl.O;z;`rtime`status`rptopt`ordid`exchid`s0`j0`j1`j2`j3]:(now[];.enum`NEW;dictstr .db[.ctrl.O;z;`x0;0]),(`$y`BrokerOrderID`OrderID`ExtOrderRef),y[`ClientOrderID],`long$y`OrderPartition`SessionID`BatchNo;execrpt[z];};

.upd.RspOrderAction:{[i;x]x:x[2];if[0=count x;:()];.temp.L7,:enlist y:.enum.ActionKey!x;z:exec first id from .db.O where ordid=`$y`OrderSysID;if[null z;:()];.db[.ctrl.O;z;`cordid]:`$y`OrderActionRef;};

.upd.RspQryTradingAccount:{[i;x]h:2#x;x:x[2];if[count x;.temp.L2,:enlist y:.enum.FundKey!x];if[(h[1])&not null z:.temp[`FundDst];pubmx[z;`FundUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L2]];};

.upd.RspQryPosition:{[i;x]h:2#x;x:x[2];if[count x;.temp.L3,:enlist y:.enum.HoldKey!x];if[(h[1])&not null z:.temp[`PosDst];pubmx[z;`PosUpdate;.conf.me;.temp[`PosAcc];-8!.temp.L3]];};

.upd.RspQryOrder:{[i;x]h:2#x;x:x[2];if[count x;.temp.L4,:enlist y:.enum.OrderKey!x];if[(h[1])&not null z:.temp[`OrdDst];pubmx[z;`OrdUpdate;.conf.me;.temp[`OrdAcc];-8!.temp.L4];if[not null z;.temp[`OrdDst]:`]];}; /.upd.RtnOrder[i;x];

.upd.RspQryTrade:{[i;x]h:2#x;x:x[2];if[count x;.temp.L5,:enlist y:.enum.TradeKey!x];if[(h[1])&not null z:.temp[`MatDst];pubmx[z;`MatUpdate;.conf.me;.temp[`MatAcc];-8!.temp.L5];if[not null z;.temp[`MatDst]:`]];};

.upd.RtnOrder:{[i;x].temp.L8,:enlist y:.enum.OrderKey!x;z:idfe2ft `$y`OrderRef;if[null .db[.ctrl.O;z;`sym];:()];st:.enum.ldpstatusmap y`OrderStatus;.db[.ctrl.O;z;`rtime`ordid`exchid]:(now[];`$y`BrokerOrderID;`$y`OrderSysID);if[count m:y`ErrorMsg;.db[.ctrl.O;z;`msg]:m];if[st=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:st];if[(st=.enum`CANCELED)&((.db[.ctrl.O;z;`cumqty]|0f)<cq:y`TradeVolume);.temp.DelayedCancel[z]:cq;:()];if[st in .enum`NEW`REJECTED`CANCELED;.db[.ctrl.O;z;`status]:st];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.RtnTrade:{[i;x].temp.L9,:enlist y:.enum.TradeKey!x;z:idfe2ft `$y`OrderRef;r:.db[.ctrl.O;z];if[(null fs:r`sym);:()];q:y`TradeVolume;p:y`TradePrice;lq:0f^r`cumqty;lp:0f^r`avgpx;if[(fs like "SP*")|(fs like "IPS*");s0:`$y`InstrumentID;s1:first sl:`$"&" vs last " " vs string fs2s fs;s2:last sl;if[0=count r`x0;.db[.ctrl.O;z;`x0]:enlist .enum`nulldict];qfld:$[s0=s1;`lcumqty;`scumqty];pfld:$[s0=s1;`lavgpx;`savgpx];lq0:0f^ffill .db[.ctrl.O;z;`x0;0;qfld];.db[.ctrl.O;z;`x0]:enlist .db[.ctrl.O;z;`x0;0],(qfld,pfld)!(q+lq0;((q*p)+lq0*0f^ffill .db[.ctrl.O;z;`x0;0;pfld])%(q+lq0));$[(cq<=lq)|((0f^ffill .db[.ctrl.O;z;`x0;0;`lcumqty])<>cq:0f^ffill .db[.ctrl.O;z;`x0;0;`scumqty]);:();[q:cq-lq;p:((cq*(0f^ffill .db[.ctrl.O;z;`x0;0;`lavgpx])-0f^ffill .db[.ctrl.O;z;`x0;0;`savgpx])-lq*lp)%q]]];.db[.ctrl.O;z;`ftime`lastqty`lastpx`cumqty`avgpx]:(now[];q;p;cq:q+lq;((q*p)+(lq*lp))%(q+lq));lwarn[`trade;(z;`$y`OrderRef;lq;q;cq)];if[(r[`cstatus]=.enum`CANCELED)&(r[`status]<>.enum`CANCELED);if[cq>=.temp.DelayedCancel[z];.db[.ctrl.O;z;`status]:.enum`CANCELED]];if[(r[`status]<>.enum`FILLED)&r[`qty]=cq;.db[.ctrl.O;z;`status]:.enum`FILLED];if[(r[`status] in .enum`PENDING_NEW`NEW)&(0<cq)&r[`qty]>cq;.db[.ctrl.O;z;`status]:.enum`PARTIALLY_FILLED];execrpt[z];}; /对SP单进行特殊处理,前腿(买单)的cumqty/avgpx记入O表的lcumqty/lavgpx字段,后腿(卖单)的scumqty/savgpx记入O表的sentqty/takepx字段,当双腿的成交量一致时更新SP单的的对应信息并推送回报 

.upd.ordnew:.fe.ordnew:{[x].temp.x20:x;if[x[`sym]<>.conf.me;:.ha.ordnew[x]];if[(null i:.ctrl.ldp.usermap u:x`acc1);:()];k:x`oid;if[count opt:x`ordopt;h:strdict opt];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict,`ApiIdx`SessionID!i,.ctrl.ldp.api[i;`SessionID]),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ldp.api[i;`Login])&(.conf.ldp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"LDP_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;hsex:.enum.ldpex ex;st:sectype[esym;hsex];r:ldpcall[i;`reqOrderInsert;(k1;hsex;esym;.enum $[x[`side]=.enum`BUY;`HS_DC_Buy;`HS_DC_Sell];ldpposefct[x`posefct;ex];.enum`HS_HT_Speculation;x`price;x`qty;.enum $[st=`STKHK;`HS_CT_LimitPFP;x[`tif]~.enum`IMMEDIATE_OR_CANCEL;`HS_CT_LimitFAK;`HS_CT_Limit];0f;0f;.enum`HS_SOF_Normal;`;`;0i)];.db[.ctrl.O;k;`j0`j1]:1_r;}'; 

.upd.ordcxl:.fe.ordcxl:{[x].temp.x21:x;if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];k1:newidl[];.db[.ctrl.O;k;`cfeoid`cid`cstatus]:(k1;x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];ldpcall[i;`reqOrderAction;(r`ordid;.enum.ldpex fs2e r`sym;h`SessionID;r`feoid;k1)];}'; 

/Tx msg
.upd.QueryOrder:{[k].temp.L4:();r:.db[.ctrl.O;k];if[(null r`sym)|null i:.ctrl.ldp.usermap u:r`acc1;:()];ldpcall[i;`reqQryOrder;(`int$r`j1;r`ordid;`int$j2;r`feoid;r`j0)];};
.upd.ordqry:.fe.ordqry:{[x].upd.QueryOrder[x`oid];}';

.upd.QueryFund:{[x].temp.x11:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L2:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryTradingAccount;()];};

.upd.QueryPos:{[x].temp.x12:x;.temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryPosition;2#`];};

.upd.QueryOrdAcc:{[x].temp.x13:x;.temp[`OrdDst`OrdAcc]:x`ref`msg;.temp.L4:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryOrder;4#`];};

.upd.QueryMatAcc:{[x].temp.x14:x;.temp[`MatDst`MatAcc]:x`ref`msg;.temp.L5:();if[null i:.ctrl.ldp.usermap u:-9!x`vbin;:()];ldpcall[i;`reqQryTrade;3#`];};


.z.exit:{[x].exit[;x];};