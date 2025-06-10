.module.fectp:2025.03.04;

txload "core/febase";
txload "feed/ctp/ctpbase";

`initctpt`freectpt`ctptrun`ctpver`ctpsysinfo`userAuthT`userLoginT`qrySettlementInfoConfirm`settlementInfoConfirm`orderInsert`orderAction`qryMaxOrderVolume`qryInstrument`qryTradingAccount`qryInvestorPosition`qryOrder`qryTrade`qryInvestor`qryTradingCode`qryInstrumentCommissionRate`qryInstrumentMarginRate`qryExchange`qryInvestorPositionDetail`qryNotice`qryInvestorPositionCombineDetail`qryEWarrantOffset`qryTransferSerial`qryTradingNotice`qryBrokerTradingParams`qryBrokerTradingAlgos`forQuoteInsert`quoteInsert`quoteAction`combActionInsert`qryCombInstrumentGuard`qryCombAction`qryOptionInstrCommRate`qryOptionInstrTradeCost`qryInstrumentOrderCommRate`qrySettlementInfo {x set $[1b~.conf.ctp`testmode;`extfectp_test;`extfectp] 2:(x;y);}' 3 1 1 1,36#2;

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
`D_Buy`D_Sell set' "01"; /TFtdcDirectionType
`OF_Open`OF_Close`OF_ForceClose`OF_CloseToday`OF_CloseYesterday`OF_ForceOff`OF_LocalForceClose set' "0123456"; /TThostFtdcOffsetFlagType
`HF_Speculation`HF_Arbitrage`HF_Hedge set' "123"; /TFtdcHedgeFlagType
`CC_Immediately`CC_Touch`CC_TouchProfit`CC_ParkedOrder`CC_LastPriceGreaterThanStopPrice`CC_LastPriceGreaterEqualStopPrice`CC_LastPriceLesserThanStopPrice`CC_LastPriceLesserEqualStopPrice`CC_AskPriceGreaterThanStopPric`CC_AskPriceGreaterEqualStopPrice`CC_AskPriceLesserThanStopPrice`CC_AskPriceLesserEqualStopPrice`CC_BidPriceGreaterThanStopPrice`CC_BidPriceGreaterEqualStopPrice`CC_BidPriceLesserThanStopPrice`CC_BidPriceLesserEqualStopPrice set' "123456789ABCDEFH"; /TThostFtdcContingentConditionType

`PD_Net`PD_Long`PD_Short set' "123"; /TFtdcPosiDirectionType
`PC_Futures`PC_Options`PC_Combination`PC_Spot`PC_EFP`PC_SpotOption set' "123456"; /TFtdcProductClassType
`PSD_Today`PSD_History set' "12"; /TFtdcPositionDateType
`OPT_AnyPrice`OPT_LimitPrice`OPT_BestPrice`OPT_LastPrice`OPT_LastPricePlusOneTicks`OPT_LastPricePlusTwoTicks`OPT_LastPricePlusThreeTicks`OPT_AskPrice1`OPT_AskPrice1PlusOneTicks`OPT_AskPrice1PlusTwoTicks`OPT_AskPrice1PlusThreeTicks`OPT_BidPrice1`OPT_BidPrice1PlusOneTicks`OPT_BidPrice1PlusTwoTicks`OPT_BidPrice1PlusThreeTicks set' "123456789ABCDEF"; /TFtdcOrderPriceTypeType
`TC_IOC`TC_GFS`TC_GFD`TC_GTD`TC_GTC`TC_GFA set' "123456"; /TFtdcTimeConditionType
`VC_AV`VC_MV`VC_CV set' "123"; /TFtdcVolumeConditionType
`FCC_NotForceClose`FCC_LackDeposit`FCC_ClientOverPositionLimit`FCC_MemberOverPositionLimit`FCC_NotMultiple`FCC_Violation`FCC_Other`FCC_PersonDeliv set' "01234567"; /TThostFtdcForceCloseReasonType
`OSS_InsertSubmitted`OSS_CancelSubmitted`OSS_ModifySubmitted`OSS_Accepted`OSS_InsertRejected`OSS_CancelRejected`OSS_ModifyRejected set' "0123456"; /TThostFtdcOrderSubmitStatusType
`OSRC_Participant`OSRC_Administrator set' "01"; /TFtdcOrderSourceType
`OST_AllTraded`OST_PartTradedQueueing`OST_PartTradedNotQueueing`OST_NoTradeQueueing`OST_NoTradeNotQueueing`OST_Canceled`OST_Unknown`OST_NotTouched`OST_Touched set' "012345abc"; /TThostFtdcOrderStatusType
`ORDT_Normal`ORDT_DeriveFromQuote`ORDT_DeriveFromCombination`ORDT_Combination`ORDT_ConditionalOrder`ORDT_Swap set' "012345"; /TThostFtdcOrderTypeType
`ER_Broker`ER_Host`ER_Maker set' "123"; /TThostFtdcTradingRoleType
`TRDT_Common`TRDT_OptionsExecution`TRDT_OTC`TRDT_EFPDerived`TRDT_CombinationDerived  set' "01234"; /TThostFtdcTradeTypeType
`PSRC_LastPrice`PSRC_Buy`PSRC_Sell set' "012"; /TThostFtdcPriceSourceType
`TSRC_NORMAL`TSRC_QUERY set' "01"; /TThostFtdcTradeSourceType
`AF_Delete`AF_Modify set' "03" ; /TThostFtdcActionFlagType
`CIDT_Speculation`CIDT_Arbitrage`CIDT_Hedge set' "123"; /TFtdcClientIDTypeType
`IS_BeforeTrading`IS_NoTrading`IS_Continous`IS_AuctionOrdering`IS_AuctionBalance`IS_AuctionMatch`IS_Closed set' "0123456"; /TThostFtdcInstrumentStatusType
`CMDR_Comb`CMDR_UnComb set' "01"; /TThostFtdcCombDirectionType

`ORPT_PreSettlementPrice`ORPT_OpenPrice`ORPT_MaxPreSettlementPrice set' "145"; /TThostFtdcOptionRoyaltyPriceTypeType(1昨结4开仓价5最新价与昨结孰大)
`AG_All`AG_OnlyLost`AG_OnlyGain`AG_None set' "1234"; /TThostFtdcAlgorithmType(1浮盈浮亏均计2仅计浮盈3仅计浮亏4浮盈浮亏均不计)
`ICP_Include`ICP_NotInclude set' "02"; /TThostFtdcIncludeCloseProfitType(0包含平仓盈利2不含平仓盈利)
`MPT_PreSettlementPrice`MPT_SettlementPrice`MPT_AveragePrice`MPT_OpenPrice set' "1234"; /TThostFtdcMarginPriceTypeType(1昨结2最新3成交均价4开仓价)
`HPA_Base`HPA_DCE`HPA_CZCE set' "123"; /TThostFtdcHandlePositionAlgoIDType
`FMRA_Base`FMRA_DCE`FMRA_CZCE set' "123"; /TThostFtdcFindMarginRateAlgoIDType
`HTAA_Base`HTAA_DCE`HTAA_CZCE set' "123"; /TThostFtdcHandleTradingAccountAlgoIDType

InstrumentKey:`InstrumentID`ExchangeID`InstrumentName`ExchangeInstID`ProductID`ProductClass`DeliveryYear`DeliveryMonth`MaxMarketOrderVolume`MinMarketOrderVolume`MaxLimitOrderVolume`MinLimitOrderVolume`VolumeMultiple`PriceTick`CreateDate`OpenDate`ExpireDate`StartDelivDate`EndDelivDate`InstLifePhase`IsTrading`PositionType`PositionDateType`LongMarginRatio`ShortMarginRatio`MaxMarginSideAlgorithm`reserve4`StrikePrice`OptionsType`UnderlyingMultiple`CombinationType`InstrumentID`ExchangeInstID`ProductID`UnderlyingInstrID;

ctptexmap:`CFFEX`SHFE`DCE`CZCE`INE`GFEX!`CCFX`XSGE`XDCE`XZCE`XINE`GFEX;
ctpstatusmap:"ab310425c"!.enum`PENDING_NEW`NEW`NEW`PARTIALLY_FILLED`FILLED`PENDING_CANCEL`PENDING_CANCEL`CANCELED`ACCEPTED_FOR_BIDDING;
ctpsubmitstatusmap:"0123456"!.enum`PENDING_NEW`PENDING_CANCEL`PENDING_REPLACE`NEW`REJECTED`REJECTED_CANCEL`REJECTED_REPLACE;

ctpclassmap:"123456"!`Future`Option`Combination`Spot`EFP`Option;
ctpphasemap:"0123"!`NotStart`Started`Pause`Expired;
\d .

.enum.ctptex:mirror .enum.ctptexmap;

ctpposefct:{[x;y]$[x=.enum`OPEN;.enum`OF_Open;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`OF_CloseToday;.enum`OF_Close]}; /[posefct;ex]

ctptconn:{[x;y]if[not any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`Run]:initctpt[.conf.ctp.tdfront;.conf.me;0i];1b;};
ctptdisc:{[x;y]if[any .z.T within/: .conf.ctp.openrange;:()];savedb[];.ctrl.ctp[`Run]:freectpt[];.upd.FrontDisconnectT[];1b};

.init.fectp:{[x]ctptconn[`;.z.P];fixrolldatetask[`;`];};
.exit.fectp:{[x]ctptdisc[`;.z.P];};
.timer.fectp:{[x]if[not 1b~.ctrl.ctp`ConnectT;:()];ctptlogin[];if[(1b~.ctrl.ctp`LoginT)&(.z.T within .conf.ctp.qryrange);qrymargin[];qryfee[]];}; 
.roll.fectp:{[x].ctrl.ctp[`Confirm]:0b;};

//insu2exch:{$[x like "IF*";`G;`]};insu2cont:{[x]"I"$(string 100 sv "i"$-4_x),-4#x};

\d .temp
IL:L18:L17:L16:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

ctptlogin:{[]if[(1b~.ctrl.ctp`LoginT)|(1b~.ctrl.ctp`PassErr);:()];.ctrl.ctp.Userinfo:ctpcall[`ctpsysinfo;.conf.ctp`broker`user];if[0=count .ctrl.ctp.Userinfo;lwarn[`sysinfo;"信息采集失败,请开放相关权限!"]];ctpcall[`userAuthT;.conf.ctp`broker`user`prdinfo`authocde`cltver];};

confirmsettlement:{[]ctpcall[`settlementInfoConfirm;.conf.ctp`broker`user];};
qrysettlement:{[x]ctpcall[`qrySettlementInfo;.conf.ctp[`broker`user],`$string[x] except "."];};

qrymargin:{[]if[null x:exec first esym from .db.QX where assetclass=`Future,settledate>.z.D,null rmarginl,4>=count each string product;:()];ctpcall[`qryInstrumentMarginRate;(.conf.ctp`broker`user),x,"1"];};
qryfee:{[]if[not null x:exec first esym from .db.QX where assetclass=`Future,settledate>.z.D,null rfeetaxoa,4>=count each string product;ctpcall[`qryInstrumentCommissionRate;(.conf.ctp`broker`user),x]];if[not null x:exec first esym from .db.QX where assetclass=`Option,settledate>.z.D,null rfeetaxoa,4>=count each string product;ctpcall[`qryOptionInstrCommRate;(.conf.ctp`broker`user),x]];};

resetqx:{[]delete from `.db.QX where assetclass=`Future;};

.upd.FrontConnectT:{[x].ctrl.ctp[`ConnectT`ConntimeT]:(1b;.z.P);lwarn[`ctptconn;(.z.P;.ctrl.ctp`DisctimeT)];};

.upd.FrontDisconnectT:{[x].ctrl.ctp[`ConnectT`LoginT`DiscReasonT`DisctimeT]:(0b;0b;x[0];.z.P);lwarn[`ctptdisc;(.z.P;.ctrl.ctp`ConntimeT;x[0])];};

.upd.AuthenticateT:{[x]y:x[2];if[0=count y;:()];.ctrl.ctp[`AppID`AppType]:y[3 4];ctpcall[`userLoginT;.conf.ctp`broker`user`pass`prdinfo];};

.upd.UserLoginT:{[x]y:x[2];if[0=count y;:()];.ctrl.ctp[`LoginT`LoginTimeT`FrontID`SessionID`MaxOrderRef]:(1b;.z.P),y;$[1b~.ctrl.ctp[`Confirm];ctpcall[`qrySettlementInfoConfirm;.conf.ctp`broker`user];confirmsettlement[]];};

.upd.ordnew:.fe.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[count opt:x`ordopt;h:strdict opt;if[`COMB~h`special;:.upd.combnew[x]]];if[not null .db[.ctrl.O;k;`sym];:()];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict,`FrontID`SessionID!.ctrl.ctp[`FrontID`SessionID]),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ctp`LoginT)&(.conf.ctp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"CTP_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;ctpcall[`orderInsert;(.conf.ctp`broker`user),(esym;k1;$[x[`side]=.enum`BUY;.enum`D_Buy;.enum`D_Sell];`int$x`qty;$[(0<x[`price])|(esym like "SP*")|(esym like "IPS*");.enum`OPT_LimitPrice;.enum`OPT_AnyPrice];x`price;$[x[`tif] in .enum`IMMEDIATE_OR_CANCEL`FILL_OR_KILL;.enum`TC_IOC;.enum`TC_GFD];$[x[`tif]=.enum`FILL_OR_KILL;.enum`VC_CV;.enum`VC_AV];`$ctpposefct[x[`posefct];ex];`$.enum`HF_Speculation;.enum.ctptex ex)];}'; 

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[null r`sym;:()];.db[.ctrl.O;k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];ctpcall[`orderAction;(.conf.ctp`broker`user),(fs2s r`sym;0;h`FrontID;h`SessionID;x`feoid;.enum.ctptex fs2e r`sym;`;.enum`AF_Delete)];}'; 

.upd.reqquote:{[x]if[x[`sym]<>.conf.me;:()];r:ctpcall[`forQuoteInsert;(.conf.ctp`broker`user),(fs2s x`qsym;newidl[];.enum.ctptex fs2e x`qsym)]}';

.upd.quotenew:{[x]if[x[`sym]<>.conf.me;:.ha.quotenew[x]];if[not null .db.QT[k:x`qid;`sym];:()];k1:newidl[];.db.QT[k;`feqid`ntime`status`qrid`bid`aid`ft`ts`acc`fe`acc1`ref`sym`bprice`aprice`bqty`aqty`bposefct`aposefct]:(k1;now[];.enum`PENDING_NEW),x`qrid`bid`aid`ft`ts`acc`sym`acc1`ref`qsym`bprice`aprice`bqty`aqty`bposefct`aposefct;kb:x`bid;ka:x`aid;fs:x`qsym;ex:fs2e fs;bp:x`bprice;ap:x`aprice;bq:x`bqty;aq:x`aqty;bpe:x`bposefct;ape:x`aposefct;x0:enlist .enum.nulldict,`FrontID`SessionID!.ctrl.ctp[`FrontID`SessionID];.db[.ctrl.O;kb;`special`origid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`typ`qty`price]:(`QT;k;now[];.enum`PENDING_NEW;x0;x`ft;x`ts;x`acc;x`sym;x`acc1;x`ref;fs;.enum`BUY;bpe;.enum`LIMIT;bq;bp);.db[.ctrl.O;ka;`special`origid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`typ`qty`price]:(`QT;k;now[];.enum`PENDING_NEW;x0;x`ft;x`ts;x`acc;x`sym;x`acc1;x`ref;fs;.enum`BUY;ape;.enum`LIMIT;aq;ap);.temp.r:r:ctpcall[`quoteInsert;(.conf.ctp`broker`user),(fs2s fs;k1;`int$aq;`int$bq;ap;bp;ctpposefct[ape;ex];ctpposefct[bpe;ex];.enum`HF_Speculation;.enum`HF_Speculation;.enum.ctptex ex)];.db.QT[k;`linkid]:`$string first r;ackquote[k];}'; /报价处理

.upd.quotecxl:{[x]if[x[`sym]<>.conf.me;:.ha.quotecxl[x]];if[null .db.QT[k:x`qid;`sym];:()];.db.QT[k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);r:.db[.ctrl.O;.db.QT[k;`bid]];h:$[count r[`x0];r[`x0;0];strdict r`rptopt];r:ctpcall[`quoteAction;(.conf.ctp`broker`user),(fs2s .db.QT[k;`sym];0;h`FrontID;h`SessionID;x`feqid;.enum.ctptex fs2e .db.QT[k;`sym];`;.enum`AF_Delete)];ackquote[k;()];}'; /撤销报价处理

.upd.combnew:{[x]if[not null .db[.ctrl.O;k:x`oid;`sym];:()];k1:newidl[];.db[.ctrl.O;k;`special`feoid`ntime`status`ft`ts`sym`side`posefct`qty]:(`COMB;k1;.z.P;.enum`NEW),x`ft`ts`osym`side`posefct`qty;r:ctpcall[`combActionInsert;(.conf.ctp`broker`user),(fs2s .db[.ctrl.O;k;`sym];k1;$[x[`side]=.enum`BUY;.enum`D_Buy;.enum`D_Sell];`int$x`qty;$[x[`posefct]=.enum`OPEN;.enum`CMDR_Comb;.enum`CMDR_UnComb];.enum`HF_Speculation;.enum.ctptex fs2e .db[.ctrl.O;k;`sym])];execrpt[k];}; /组合锁定解锁

.upd.OrderInsertErr:{[x]if[0=count x;:()];.temp.L6,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`UserForceClose`ErrorID`ErrorMsg!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db[.ctrl.O;z;`rtime`status`reason`msg]:(now[];.enum`REJECTED;y`ErrorID;y`ErrorMsg);execrpt[z];};
.upd.OrderInsert:{[x].upd.OrderInsertErr x[2];};

.upd.OrderActionErr:{[x]if[0=count x;:()];.temp.L7,:enlist y:`BrokerID`InvestorID`OrderActionRef`OrderRef`RequestID`FrontID`SessionID`ExchangeID`OrderSysID`ActionFlag`LimitPrice`VolumeChange`UserID`InstrumentID`ErrorID`ErrorMsg!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db[.ctrl.O;z;`cstatus`reason`msg]:(.enum`REJECTED;y`ErrorID;y`ErrorMsg);r:.db[.ctrl.O;z];rejectcxl[r`ft;z;r`cid;r`reason;r`msg];};
.upd.OrderAction:{[x].upd.OrderActionErr x[2];}; /

.upd.Order:{[x].temp.L8,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x;z:idfe2ft `$y`OrderRef;z1:`;if[(null .db[.ctrl.O;z;`sym])&(0<w:y`RequestID);if[not null k:exec first id from .db.QT where linkid=`$string w;z1:z;z:.db.QT[k;$[.enum[`D_Buy]=y`Direction;`bid;`aid]]]];if[null .db[.ctrl.O;z;`sym];:()];st:.enum[`ctpstatusmap] y`OrderStatus;.db[.ctrl.O;z;`x0]:enlist .db[.ctrl.O;z;`x0;0],`BrokerOrderSeq`TraderID`OrderLocalID!y`BrokerOrderSeq`TraderID`OrderLocalID;.db[.ctrl.O;z;`rtime`ordid`ex`esym`rptopt]:(now[];`$y`OrderSysID;`$y`ExchangeID;`$y`ExchangeInstID;dictstr .db[.ctrl.O;z;`x0;0]);if[count m:y`StatusMsg;.db[.ctrl.O;z;`msg]:m];if[st=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:st];if[(st=.enum`CANCELED)&((.db[.ctrl.O;z;`cumqty]|0f)<cq:`float$y`VolumeTraded);.temp.DelayedCancel[z]:cq;:()];.db[.ctrl.O;z;`status]:st;if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

//.upd.Order:{[x].temp.L8,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x;z:idfe2ft `$y`OrderRef;z1:`;w:`$y`OrderSysID;if[(null .db[.ctrl.O;z;`sym]);z1:z;z:exec first id from .db[.ctrl.O] where ordid=w];if[null .db[.ctrl.O;z;`sym];:()];st:.enum[`ctpstatusmap] y`OrderStatus;.db[.ctrl.O;z;`x0;0],:`BrokerOrderSeq`TraderID`OrderLocalID!y`BrokerOrderSeq`TraderID`OrderLocalID;.db[.ctrl.O;z;`rtime`status`ordid`ex`esym`origid`rptopt]:(now[];st;`$y`OrderSysID;`$y`ExchangeID;`$y`ExchangeInstID;z1;dictstr .db[.ctrl.O;z;`x0;0]);if[count m:y`StatusMsg;.db[.ctrl.O;z;`msg]:m];if[st=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:st];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.Trade:{[x].temp.L9,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`ExchangeID`TradeID`Direction`OrderSysID`ParticipantID`ClientID`TradingRole`ExchangeInstID`OffsetFlag`HedgeFlag`Price`Volume`TradeDate`TradeTime`TradeType`PriceSource`TraderID`OrderLocalID`ClearingPartID`BusinessUnit`SequenceNo`TradingDay`SettlementID`BrokerOrderSeq`TradeSource!x;z:idfe2ft `$y`OrderRef;w:`$y`OrderSysID;if[null .db[.ctrl.O;z;`sym];z:exec first id from .db[.ctrl.O] where ordid=w,(fs2e each sym)=.enum.ctptexmap `$y`ExchangeID];if[(null fs:.db[.ctrl.O;z;`sym]);:()];q:`float$y`Volume;p:y`Price;lq:0f^.db[.ctrl.O;z;`cumqty];lp:0f^.db[.ctrl.O;z;`avgpx];if[(fs like "SP*")|(fs like "IPS*");s0:`$y`InstrumentID;s1:first sl:`$"&" vs last " " vs string fs2s fs;s2:last sl;if[0=count .db[.ctrl.O;z;`x0];.db[.ctrl.O;z;`x0]:enlist .enum`nulldict];qfld:$[s0=s1;`lcumqty;`scumqty];pfld:$[s0=s1;`lavgpx;`savgpx];lq0:0f^ffill .db[.ctrl.O;z;`x0;0;qfld];.db[.ctrl.O;z;`x0]:enlist .db[.ctrl.O;z;`x0;0],(qfld,pfld)!(q+lq0;((q*p)+lq0*0f^ffill .db[.ctrl.O;z;`x0;0;pfld])%(q+lq0));$[(cq<=lq)|((0f^ffill .db[.ctrl.O;z;`x0;0;`lcumqty])<>cq:0f^ffill .db[.ctrl.O;z;`x0;0;`scumqty]);:();[q:cq-lq;p:((cq*(0f^ffill .db[.ctrl.O;z;`x0;0;`lavgpx])-0f^ffill .db[.ctrl.O;z;`x0;0;`savgpx])-lq*lp)%q]]];.db[.ctrl.O;z;`ftime`lastqty`lastpx`cumqty`avgpx]:(now[];q;p;q+lq;((q*p)+(lq*lp))%(q+lq));lwarn[`trade;(z;`$y`OrderRef;lq;q;.db[.ctrl.O;z;`cumqty])];if[(.db[.ctrl.O;z;`cstatus]=.enum`CANCELED)&(.db[.ctrl.O;z;`status]<>.enum`CANCELED);if[.db[.ctrl.O;z;`cumqty]>=.temp.DelayedCancel[z];.db[.ctrl.O;z;`status]:.enum`CANCELED]];execrpt[z];}; /对SP单进行特殊处理,前腿(买单)的cumqty/avgpx记入O表的lcumqty/lavgpx字段,后腿(卖单)的scumqty/savgpx记入O表的sentqty/takepx字段,当双腿的成交量一致时更新SP单的的对应信息并推送回报 

.upd.ForQuote:{[x].temp.IL,:enlist x;}; /询价

.upd.Quote:{[x].temp.IL,:enlist y:`BrokerID`InvestorID`InstrumentID`QuoteRef`UserID`AskPrice`BidPrice`AskVolume`BidVolume`RequestID`BusinessUnit`AskOffsetFlag`BidOffsetFlag`AskHedgeFlag`BidHedgeFlag`QuoteLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`NotifySequence`OrderSubmitStatus`TradingDay`SettlementID`QuoteSysID`InsertDate`InsertTime`CancelTime`QuoteStatus`ClearingPartID`SequenceNo`AskOrderSysID`BidOrderSysID`FrontID`SessionID`UserProductInfo`StatusMsg`ActiveUserID`BrokerQuoteSeq!x;k:qidfe2ft `$y`QuoteRef;if[null k;:()];qs:.enum[`ctpstatusmap] y`QuoteStatus;cs:.db.QT[k;`cstatus];qss:.enum.ctpsubmitstatusmap y`OrderSubmitStatus;if[qss=.enum`REJECTED;qs:qss];.db.QT[k;`status`cstatus`quoteid`rtime`msg]:(qs;cs;`$y`QuoteSysID;now[];y`StatusMsg);if[(not null z:`$y`AskOrderSysID)&null .db[.ctrl.O;.db.QT[k;`aid];`ordid];.db[.ctrl.O;.db.QT[k;`aid];`status`ordid]:(.enum`NEW;z)];if[(not null z:`$y`BidOrderSysID)&null .db[.ctrl.O;.db.QT[k;`bid];`ordid];.db[.ctrl.O;.db.QT[k;`bid];`status`ordid]:(.enum`NEW;z)];ackquote[k];}; /报价

.upd.ForQuoteInsertErr:{[x]if[0=count x;:()];}; /询价拒绝

.upd.QuoteInsertErr:{[x].temp.IL,:enlist x;if[null k:exec first id from .db.QT where linkid=`$string x[9];:()];.db.QT[k;`status`reason`msg`rtime]:(.enum`REJECTED;x[15];x[16];now[]);.db[.ctrl.O;.db.QT[k;`bid];`status`reason`msg`rtime]:.db.QT[k;`status`reason`msg`rtime];.db[.ctrl.O;.db.QT[k;`oid];`status`reason`msg`rtime]:.db.QT[k;`status`reason`msg`rtime];ackquote[k];}; /报价拒绝

.upd.QuoteActionErr:{[x]x:x[2];if[0=count x;:()];}; /撤销报价拒绝

.upd.QuoteAction:{[x]x:x[2];if[0=count x;:()];y:`BrokerID`InvestorID`QuoteActionRef`QuoteRef`RequestID`FrontID`SessionID`ExchangeID`QuoteSysID`ActionFlag`UserID`InstrumentID`ErrorID`ErrorMsg!x;k:qidfe2ft `$y`QuoteRef;if[null k;:()];.db.QT[k;`cstatus`reason`msg]:(.enum`REJECTED;y`ErrorID;y`ErrorMsg);ackquote[k];}; /撤销报价

.upd.CombAction:{[x]if[0=count x;:()];.temp.L11,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ActionLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`ActionStatus`NotifySequence`TradingDay`SettlementID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg!x;k:idfe2ft `$y`CombActionRef;if[(null .db[.ctrl.O;k;`sym])|.db[.ctrl.O;k;`end];:()];.db[.ctrl.O;k;`x0`ordid`status`msg]:(enlist .enum.nulldict,`FrontID`SessionID!y`FrontID`SessionID;`$y`ActionLocalID;{$[x=.enum`ACCEPTED_FOR_BIDDING;.enum`REJECTED;x]} .enum.ctpstatusmap y`ActionStatus;y`StatusMsg);if[.db[.ctrl.O;k;`status] in .enum`FILLED`REJECTED;.db[.ctrl.O;k;`end]:1b];execrpt[k];}; /组合申请确认

.upd.CombActionInsert:{[x]x:x[2];if[0=count x;:()];.temp.L12,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag!x;}; /组合申请委托(CTP直接拒绝时会返回)

.upd.CombActionInsertErr:{[x]if[0=count x;:()];.temp.L13,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ErrorID`ErrorMsg!x;k:idfe2ft `$y`CombActionRef;if[(null .db[.ctrl.O;k;`sym])|.db[.ctrl.O;k;`end];:()];.db[.ctrl.O;k;`end`status`reason`msg]:(1b;.enum`REJECTED;y`ErrorID;y`ErrorMsg);execrpt[k];}; /组合申请拒绝(CTP直接拒绝)

.upd.QryCombInstrumentGuard:{[x]x:x[2];if[0=count x;:()];.temp.L14,:enlist y:`BrokerID`InstrumentID`GuarantRatio!x;}; /查询组合合约安全系数

.upd.QryCombAction:{[x]x:x[2];if[0=count x;:()];.temp.L15,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ActionLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`ActionStatus`NotifySequence`TradingDay`SettlementID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg!x;}; /查询组合申请

.upd.QueryOrder:{[k].temp.L4:();if[null .db[.ctrl.O;k;`sym];:()];r:ctpcall[`qryOrder;(.conf.ctp`broker`user),(`;`;.db[.ctrl.O;k;`ordid];`;`)];};
.upd.ordqry:.fe.ordqry:{[x].upd.QueryOrder[x`oid];}';

.upd.QueryFund:{[x].temp.FundDst:x`ref;.temp.L2:();r:ctpcall[`qryTradingAccount;.conf.ctp`broker`user];};

.upd.QueryPos:{[x].temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();r:ctpcall[`qryInvestorPosition;(.conf.ctp`broker`user),`];};

.upd.QueryMatAcc:{[x].temp[`MatDst`MatAcc]:x`ref`msg;.temp.L5:();r:ctpcall[`qryTrade;(.conf.ctp`broker`user),5#`];};

.upd.QueryOrdAcc:{[x].temp[`OrdDst`OrdAcc]:x`ref`msg;.upd.QueryAllOrder[];};

.upd.QueryAllOrder:{[x].temp.L4:();r:ctpcall[`qryOrder;(.conf.ctp`broker`user),5#`];};

.upd.QueryMatch:{[x].temp.L5:();r:ctpcall[`qryTrade;(.conf.ctp`broker`user),5#`];};

.upd.QrySettlementInfoConfirm:{[x]y:x[2];if[0<count y;:()];confirmsettlement[];};

.upd.QueryInstrument:{[x].temp.L1:();r:ctpcall[`qryInstrument;4#`];};

.upd.SettlementInfoConfirm:{[x].ctrl.ctp[`Confirm]:1b;.upd.QueryInstrument[];};

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,product,multiplier,pxunit,qtylot,qtymax,qtymaxm,qtymaxl,qtymaxs,rmarginl,rmargins,rfeetaxoa,rfeetaxoq,rfeetaxca,rfeetaxcq,rfeetaxcat,rfeetaxcqt,settledate,opendate,createdate,lifephase,status from .db.QX;if[not 1b~.conf.ctp[`skipupdrd];pubm[`ALL;`RDUpdate;`ctp;string path]];};

.upd.QryInstrument:{[x]if[0=count x[2];:()];.temp.L1,:enlist y:.enum.InstrumentKey!x[2];fs:se2fs (s:`$y`InstrumentID),e:.enum.ctptexmap `$y`ExchangeID;if[null .db.QX[fs;`esym];.db.QX[fs;`ex`esym`name`assetclass`product`multiplier`pxunit`qtylot`qtymax`qtymaxm`settledate`opendate`createdate`lifephase`status]:(e;s;`$y`InstrumentName;.enum.ctpclassmap y`ProductClass;`$y`ProductID;`float$y`VolumeMultiple;y`PriceTick;`float$y`MinLimitOrderVolume;`float$y`MaxLimitOrderVolume;`float$y`MaxMarketOrderVolume;"D"$y`ExpireDate;"D"$y`OpenDate;"D"$y`CreateDate;.enum.ctpphasemap y`InstLifePhase;y`IsTrading)];if[x[1];updaterd[]];};

.upd.QryInstrumentCommissionRate:{[x]if[0=count x[2];:()];.temp.L0,:enlist y:`InstrumentID`InvestorRange`BrokerID`InvestorID`OpenRatioByMoney`OpenRatioByVolume`CloseRatioByMoney`CloseRatioByVolume`CloseTodayRatioByMoney`CloseTodayRatioByVolume!x[2];update rfeetaxoa:y`OpenRatioByMoney,rfeetaxoq:y`OpenRatioByVolume,rfeetaxca:y`CloseRatioByMoney,rfeetaxcq:y`CloseRatioByVolume,rfeetaxcat:y`CloseTodayRatioByMoney,rfeetaxcqt:y`CloseTodayRatioByVolume from `.db.QX where (product=`$y`InstrumentID)|esym=`$y`InstrumentID;}; /

.upd.QryInstrumentMarginRate:{[x]if[0=count x[2];:()];.temp.L10,:enlist y:`InstrumentID`InvestorRange`BrokerID`InvestorID`HedgeFlag`LongMarginRatioByMoney`LongMarginRatioByVolume`ShortMarginRatioByMoney`ShortMarginRatioByVolume`IsRelative!x[2];update rmarginl:y`LongMarginRatioByMoney,rmargins:y`ShortMarginRatioByMoney from `.db.QX where esym=`$y`InstrumentID;};

.upd.QryTradingAccount:{[x]if[0=count x[2];:()];.temp.L2,:enlist y:`BrokerID`AccountID`PreMortgage`PreCredit`PreDeposit`PreBalance`PreMargin`InterestBase`Interest`Deposit`Withdraw`FrozenMargin`FrozenCash`FrozenCommission`CurrMargin`CashIn`Commission`CloseProfit`PositionProfit`Balance`Available`WithdrawQuota`Reserve`TradingDay`SettlementID`Credit`Mortgage`ExchangeMargin`DeliveryMargin`ExchangeDeliveryMargin!x[2];if[x[1];pubmx[.temp.FundDst;`FundUpdate;.conf.me;"";-8!.temp.L2]];};

.upd.QryInvestorPosition:{[x]if[0=count x[2];:()];.temp.L3,:enlist y:`InstrumentID`BrokerID`InvestorID`PosiDirection`HedgeFlag`PositionDate`YdPosition`Position`LongFrozen`ShortFrozen`LongFrozenAmount`ShortFrozenAmount`OpenVolume`CloseVolume`OpenAmount`CloseAmount`PositionCost`PreMargin`UseMargin`FrozenMargin`FrozenCash`FrozenCommission`CashIn`Commission`CloseProfit`PositionProfit`PreSettlementPrice`SettlementPrice`TradingDay`SettlementID`OpenCost`ExchangeMargin`CombPosition`CombLongFrozen`CombShortFrozen`CloseProfitByDate`CloseProfitByTrade`TodayPosition`MarginRateByMoney`MarginRateByVolume!x[2];if[x[1];pubmx[.temp.PosDst;`PosUpdate;.conf.me;.temp.PosAcc;-8!1!select sym:{exec first sym from .db.QX where esym=x} each `$InstrumentID,lqty:0f|Position,sqty:0f&Position from .temp.L3 where 0<>Position]];};

.upd.QryOrder:{[x]if[0=count x[2];:()];.temp.L4,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x[2];if[x[1];.upd.Order each flip value flip .temp.L4;if[not null z:.temp`OrdDst;pubmx[z;`OrdUpdate;.conf.me;.temp`OrdAcc;-8!select feoid:`$OrderRef,ordid0:`$OrderSysID,cumqty0:`float$VolumeTraded,status0:.enum[`ctpstatusmap] OrderStatus,sym0:(`$InstrumentID) {sv[`]x,y}' .enum.ctptexmap `$ExchangeID,side0:("01"!.enum`BUY`SELL) Direction,posefct0:("013"!.enum`OPEN`CLOSE`CLOSETODAY) first each CombOffsetFlag,qty0:VolumeTotal,price0:LimitPrice from .temp.L4];.temp[`OrdDst]:`]];};

.upd.QryTrade:{[x]if[0=count x[2];:()];.temp.L5,:enlist `BrokerID`InvestorID`InstrumentID`OrderRef`UserID`ExchangeID`TradeID`Direction`OrderSysID`ParticipantID`ClientID`TradingRole`ExchangeInstID`OffsetFlag`HedgeFlag`Price`Volume`TradeDate`TradeTime`TradeType`PriceSource`TraderID`OrderLocalID`ClearingPartID`BusinessUnit`SequenceNo`TradingDay`SettlementID`BrokerOrderSeq`TradeSource!x[2];if[x[1];pubmx[.temp.MatDst;`MatUpdate;.conf.me;.temp.MatAcc;-8!.temp.L5]];};

.upd.QryTradingCode:{[x].temp.IL,:x};
.upd.QryExchange:{[x]};

.upd.CTPError:{[x].temp.X:x;if[x[2;0] in 63 75 15907 4060i;.ctrl.ctp[`PassErr]:1b];};


pushqx:{[x;y].ctrl.conn[`fq;`h] (set;`.db.QX;.db.QX);1b};

.upd.QryOptionInstrCommRate:{[x]if[0=count x[2];:()];.temp.L16,:enlist y:`reserve1`InvestorRange`BrokerID`InvestorID`OpenRatioByMoney`OpenRatioByVolume`CloseRatioByMoney`CloseRatioByVolume`CloseTodayRatioByMoney`CloseTodayRatioByVolume`StrikeRatioByMoney`StrikeRatioByVolume`ExchangeID`InvestUnitID`InstrumentID!x[2];update rfeetaxoa:y`OpenRatioByMoney,rfeetaxoq:y`OpenRatioByVolume,rfeetaxca:y`CloseRatioByMoney,rfeetaxcq:y`CloseRatioByVolume,rfeetaxcat:y`CloseTodayRatioByMoney,rfeetaxcqt:y`CloseTodayRatioByVolume from `.db.QX where (product=`$y`InstrumentID)|esym=`$y`InstrumentID;}; /

.upd.QryOptionInstrTradeCost:{[x]if[0=count x[2];:()];.temp.L17,:enlist y:`BrokerID`InvestorID`reserve1`HedgeFlag`FixedMargin`MiniMargin`Royalty`ExchFixedMargin`ExchMiniMargin`ExchangeID`InvestUnitID`InstrumentID!x[2];}; /

.upd.QryInstrumentOrderCommRate:{[x]if[0=count x[2];:()];.temp.L17,:enlist y:`reserve1`InvestorRange`BrokerID`InvestorID`HedgeFlag`OrderCommByVolume`OrderActionCommByVolume`ExchangeID`InvestUnitID`InstrumentID`OrderCommByTrade`OrderActionCommByTrade!x[2];}; /

.upd.QrySettlementInfo:{[x].temp.x99:x;if[0=count x:x[2];:()];.temp.y:y:`TradingDay`SettlementID`BrokerID`InvestorID`SequenceNo`Content`AccountID`CurrencyID!x;}; /

parsettlementfile:{[x]y:(-1_) each read0 x;z:("*Account Summary*";"*Transaction Record*";"*Position Closed*";"*Positions Detail*";"*Positions");d:(1_) each (raze where each y like\:/:z) cut y;r:`Summary`Transaction`Closed`Detail`Positions!enlist[(!/)flip 0N 2#raze {[x]y:except[;enlist ""] vs[" "] x[1];(except[;" /\243\272:"] x[0];"F"$y[0];except[;" /\243\272:"] raze 1_y;"F"$x[2])} each except[;enlist ""] each vs[8#" "] each -1_1_d 0],{flip (`$vs["|"] -1_1_except[;" /.()"] x[2])!flip vs["|"] each except[;" "] each {(-1_1_) each (first where like[;"-*"] each x)#x} 4_x} each 1_d;r[`Fee]:`sym`side xasc select sym,side,cumfee from update sym:esym {sv[`]x,y}' ex from select ex:((("能源中心";"上期所";"中金所";"大商所";"郑商所";"广期所"))!`XINE`XSGE`CCFX`XDCE`XZCE`GFEX) gbk2utf8 each Exchange,esym:`$Instrument,side:((("买";"卖"))!"12") gbk2utf8 each BS,cumfee:"F"$Fee from r`Transaction;r}; /[结算单文件路径]

.upd.QueryBrokerTradingParams:{[x]r:ctpcall[`qryBrokerTradingParams;.conf.ctp`broker`user];};
.upd.QryBrokerTradingParams:{[x].temp.x99:x;if[0=count x:x[2];:()];.temp.y:y:`BrokerID`InvestorID`MarginPriceType`Algorithm`AvailIncludeCloseProfit`CurrencyID`OptionRoyaltyPriceType`AccountID!x;}; /

.upd.QueryOptionInstrTradeCost:{[x]r:ctpcall[`qryOptionInstrTradeCost;(.conf.ctp`broker`user),(fs2s x`sym;.enum.ctptex fs2e x`sym;.enum.HF_Speculation;x`price;x`udlpx)];};

chkdayroll:{[x;y]if[.db.sysdate<z:.ctrl.conn.fqbar.h `.db.sysdate;.upd.BeginOfDay enlist[`msg]!enlist string z];1b};

syncmat:{[]d:select from ((select id,ts,fe,acc,sym,side,posefct,qty,price,status,cumqty,avgpx,feoid,ntime from .db.O where not end) lj select cumqty1:`float$sum Volume,avgpx1: Volume wavg Price by feoid:`$OrderRef from .temp.L5) where (cumqty<cumqty1);.db.O:.db.O lj 1!select feoid,cumqty:cumqty1,avgpx:avgpx1 from d;execrpt each exec id from d;}; /修复成交数据丢失 

//----ChangeLog----
//2025.03.04:新增syncmat函数.当ctp交易接口异常导致丟回报时,使用通过查询接口返回的委托/成交数据进行修正后再向fe推更新后的成交回报.调用前应先在fe执行qryoda/qrymat并等待结果返回
//2024.11.18:增加函数chkdayroll以在夜盘启动后检查dayroll是否完成(日盘收盘后的异常退出可能导致dayroll未生效).db.TASK[`CHKDROLL;`firetime`firefreq`weekmin`weekmax`handler]:(\"p\"$.z.D+20:50:00;1D;0;4;`chkdayroll);
//2024.11.15:增加函数.upd.QueryOrdAcc并对应修改.upd.QryOrder以支持ft查询全部委托列表
//2024.10.31:.upd.FrontConnectT/FrontDisconnectT增加日志记录
//2024.06.11:新增.upd.QueryBrokerTradingParams/QryBrokerTradingParams,更新.enum.InstrumentKey
//2024.05.20:增加qrySettlementInfo/.upd.QrySettlementInfo支持(目前没有有用信息返回);增加parsettlementfile函数
//2024.02.20:增加函数.upd.QueryMatAcc并修改函数.upd.QryTrade以支持查询当日成交,目前对于丢失当日回报的情况需要在查完成交后手工触发补回报处理例如.upd.Trade each flip value flip -1_1_.temp.L5
//2024.02.19：.upd.QryInvestorPosition更新返回格式以兼容ftbase的chkpos函数
//2024.02.02:新增ctpver函数
//2023.11.29:新增.upd.QryOptionInstrCommRate(extfectp.cpp增加qryOptionInstrCommRate/OnRspQryOptionInstrCommRate);新增.upd.QryOptionInstrTradeCost(extfectp.cpp增加qryOptionInstrTradeCost/OnRspQryOptionInstrTradeCost);新增.upd.QryInstrumentOrderCommRate(extfectp.cpp增加qryInstrumentOrderCommRate/OnRspQryInstrumentOrderCommRate);更新qryfee以支持查询期权手续费
//2023.09.25:ctptexmap增加广交所映射
//2019.12.02:初始版本

\
fectp的O表记录丢失后数据同步步骤(一般在非交易时段操作以免新成交回报使得查询结果过期)
1.在fe中从ft回补缺失的O表记录:e1 ".db.O,:f ({[x;y]select from .db.O where fe=x,not id in y};.conf.me;exec id from .db.O)"
2.在ft中运行f "(qryoda;qrymat)@\\: `ctp"查询ctp接口的全部委托和成交后做比对:f ".temp.ordiff:{select id,ts,acc,side,posefct,qty,price,cumqty,status,side0,posefct0,qty0,price0,cumqty0,status0,feoid,ordid,ordid0 from ((select from .db.O where acc=x) lj 1!.temp.AccSnap[x;`Ord]) where (cumqty0<>cumqty)|status<>status0} `ctp"
3.对上面丢成交回报的委托在fe中重新推送对应的成交回报:e1 ({[x].upd.Trade each flip value flip select from .temp.L5 where x[0]=`$OrderRef,x[1]<sums `float$Volume}';flip value f "exec feoid,cumqty from .temp.ordiff")
4.在ft中运行f "(qryoda;qrypos;qryfund)@\\: `ctp"重新查询后再做比对,确认.temp.ordiff为空且chkpos[`ctp]和chkfund[`ctp]均为1b