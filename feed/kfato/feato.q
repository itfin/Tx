.module.feato:2023.08.06;

txload "core/febase";

`initato`freeato`atorun`atoLogin`reqStockPosition`reqQueryAsset`subscribeReport`unSubscribeReport`reqQueryOrderActual`reqQueryDealActual`reqCreateOrderActual`reqCancelOrderActual`reqQueryInstruction`reqInstructionCreate`reqInstructionReplace`reqInstructionControl`reqQueryRiskWarn {x set `extfeato 2:(x;y);}' 2 1 1,14#2;

.ctrl.ato:.enum.nulldict;
.ctrl.ato.sub:.enum.nulldict;
.ctrl.ato.FUND:();
.ctrl.ato.POS:();

atocall:{[x;y]k:newseq[];.temp.r:r:(value x)[`int$k;y,$[0=type y;();enlist (::)]];.temp.C,:enlist (r;.z.P;k;x;y);(r;k)};
onato:{[x].temp.X:x;if[.conf.ato.debug;.temp.L,:(enlist .z.P),/:x];{[x](.upd[x[0]])[x[1]]} each x;};

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
LoginKey:`operatorNo`operatorName`organId`organName`productId`productName`productStatus`unitId`unitName`unitStatus`accountId`accountUser`accountName`accountType`accountStatus`accountConfStatus`marketType`stkAcctCode`stkAcctName`stkAcctStatus`primaryFlag;
PositionKey:`organId`productId`unitId`accountId`accountUser`stkAcctCode`marketType`symbol`positionType`initQty`currentQty`algoEnableQty`orderEnableQty`costAmt`incomeAmt`interestIncome`interestCostAmt`positionStr`positionValue;
AssetKey:`organId`productId`unitId`accountId`prevNetAsset`prevCumAsset`cumAsset`netAsset`securityFund`orderEnableAmt`cashAmt`stockAsset`fundAsset`bondAsset`repoAsset`otherAsset`productShare`unitShare`perNav`prevPerNav`positionStr;
OrderKey:`operatorNo`organId`accountId`accountUser`productId`unitId`algoTypeId`sysQuoteId`sysOrderId`clOrderId`brokerOrderId`marketType`symbol`side`pxType`orderPx`orderQty`transacTime`orderStatus`securityType`cumQty`cumAmt`leavesQty`cancelTime`updateTime`opstation`basketId`sysQuoteBatchId`sysOrderBatchId`stkAcctCode`cancelQty`assetType`reportDate`reportTime`tradeDate`tradeTime`allFee`dealBondAccrInterest`remark`externalId;
TradeKey:`operatorNo`accountUser`accountId`productId`unitId`algoTypeId`brokerOrderId`sysQuoteId`sysOrderId`clOrderId`marketType`symbol`side`pxType`orderPx`orderQty`orderStatus`securityType`dealQty`dealPx`dealTime`basketId`sysQuoteBatchId`sysOrderBatchId`stkAcctCode`assetType`allFee`dealBondAccrInterest`sysDealId`externalId`dealDate`dealId;
InstructionKey:`operatorNo`productId`unitId`accountId`accountUser`algoTypeId`symbol`marketType`effectiveTime`expireTime`securityType`assetType`basketId`sysQuoteBatchId`sysQuoteId`tradeDate`transacTime`algoParam`taskQty`cumQty1`cumQty2`outstandingQty1`outstandingQty2`leavesQty1`leavesQty2`taskAmt`cumAmt1`cumAmt2`algoStatus`orderCancelQty`orderFailQty`rspAlgoInfo`externalId;
FundChgKey:`productId`accountId`unitId`accountUser`currencyType`initAmt`orderEnableAmt`algoEnableAmt;
PositionChgKey:`productId`accountId`unitId`accountUser`marketType`symbol`stkAcctCode`positionType`costAmt`initQty`currentQty`orderEnableQty`algoEnableQty`currencyType`securityType;
OrderQryKey:`orderBatchId`sysOrderId`sysQuoteBatchId`sysQuoteId`operatorNo`tradeDate`tradeTime`organId`productId`unitId`accountId`accountUser`stkAcctCode`marketType`symbol`securityType`assetType`reportDate`reportTime`brokerOrderId`side`pxType`orderPx`orderQty`orderAmt`orderStatus`cancelQty`dealAmt`dealQty`allFee`dealBondAccrInterest`basketId`rspOrderInfo`positionStr`externalId;
DealQryKey:`operatorNo`sysDealId`dealId`accountUser`accountId`productId`unitId`algoTypeId`brokerOrderId`sysQuoteId`sysOrderId`marketType`symbol`side`securityType`dealQty`dealPx`dealDate`dealTime`dealAmt`stkAcctCode`assetType`allFee`dealBondAccrInterest`positionStr`externalId;
OrderCreateKey:`errCode`errMsg`createDate`createTime`orderBatchId`sysOrderId`riskBusinId`riskWarnFlag`warnOperation;
OrderCancelKey:`errCode`errMsg`sysOrderId`cancelId`riskBusinId`riskWarnFlag`warnOperation;
InstructionQryKey:`sysQuoteBatchId`sysQuoteId`operatorNo`organId`productId`unitId`accountId`accountUser`tradeDate`algoTypeId`algoTypeName`marketType`symbol`basketId`algoParam`effectiveTime`expireTime`securityType`assetType`transacTime`taskQty`taskAmt`cumQty1`cumQty2`outstandingQty1`outstandingQty2`leavesQty1`leavesQty2`cumAmt1`cumAmt2`algoStatus`orderCancelQty`orderFailQty`cancelQty`rspAlgoInfo`positionStr`externalId;
InstructionCreateKey:`errCode`errMsg`externalId`basketId`sysQuoteBatchId`sysQuoteId`riskBusinId`riskWarnFlag`warnOperation;
InstructionControlKey:InstructionReplaceKey:`errCode`errMsg`updateDate`updateTime`sysQuoteId;
RiskWarnKey:`riskWarnId`riskBusinId`riskRuleId`riskTypeId`organId`riskWarnLevel`productId`unitId`accountId`symbol`marketType`side`currencyType`riskControlBiz`compareDirection`symbolCollect`layerCollect`warnLevel`warnOperation`setValue`calcValue`numeratorValue`denominatorValue`riskGroupId`commandId`sysQuoteId`sysOrderId`operatorNo`remark`ruleRemark`setRuleInfo`createTime`displayUnit;

`MARKET_TYPE_INVALID`MARKET_TYPE_SZ`MARKET_TYPE_SH`MARKET_TYPE_CFE`MARKET_TYPE_SHF`MARKET_TYPE_DCE`MARKET_TYPE_ZCE`MARKET_TYPE_INE set' `int$til 8;  /AtoMarketType
`CURRENCY_TYPE_CNY set' 1i; /AtoCurrencyType
`PRICE_TYPE_INVALID`PRICE_TYPE_LIMIT`PRICE_TYPE_BEST_OR_CANCEL`PRICE_TYPE_BEST5_OR_LIMIT`PRICE_TYPE_BEST5_OR_CANCEL`PRICE_TYPE_ALL_OR_CANCEL`PRICE_TYPE_FORWARD_BEST`PRICE_TYPE_REVERSE_BEST_LIMIT`PRICE_TYPE_LIMIT_OR_CANCEL  set' `int$til 9; /AtoOrderPriceType
`SIDE_INVALID`SIDE_BUY`SIDE_SELL`SIDE_CLOSE_BUY`SIDE_SHORT_SELL`SIDE_SHORT_BUY`SIDE_CLOSE_SELL`SIDE_DIRECT_CLOSE_SELL`SIDE_DIRECT_CLOSE_BUY`SIDE_REVERSE_REPO`SIDE_NEW_STOCK_SUB`SIDE_NEW_BOND_SUB set' `int$til 12; /AtoSide
`ORDER_STATUS_INVALID`ORDER_STATUS_PENDINGNEW`ORDER_STATUS_NEW`ORDER_STATUS_PARTFILLED`ORDER_STATUS_FILLED`ORDER_STATUS_CANCELED`ORDER_STATUS_PENDINGCANCEL`ORDER_STATUS_STOPPED`ORDER_STATUS_PARTCANCELED`ORDER_STATUS_INSIDE_STOPPED`ORDER_STATUS_INSIDE_CANCELED`ORDER_STATUS_WAITNEW`ORDER_STATUS_IN_PROGRESS set' `int$til 13; /AtoOrderStatus
`CANCEL_STATUS_INVALID`CANCEL_STATUS_PENDINGNEW`CANCEL_STATUS_NEW`CANCEL_STATUS_SUCCESS`CANCEL_STATUS_FAIL set' `int$til 5; /AtoCancelStatus
`ALGO_STATUS_PENDINGNEW`ALGO_STATUS_NEW`ALGO_STATUS_PARTFILLED`ALGO_STATUS_FILLED`ALGO_STATUS_CANCELED`ALGO_STATUS_PENDINGCANCEL`ALGO_STATUS_STOPPED`ALGO_STATUS_REJECTED`ALGO_STATUS_SUSPENDED`ALGO_STATUS_EXPIRED`ALGO_STATUS_PARTCANCELED`ALGO_STATUS_FORCECANCELED`ALGO_STATUS_FORCEPARTCANCELED`ALGO_STATUS_PENDINGSUSPEND`ALGO_STATUS_PENDINGSTART`ALGO_STATUS_PENDINGNOOPEN`ALGO_STATUS_NOOPENED`ALGO_STATUS_PENDINGMODIFY`ALGO_STATUS_PENDINGNEWSUB`ALGO_STATUS_NOSEND`ALGO_STATUS_PENDINGEXPIRED set' `int$(1+til[19]),23 24; /AtoAlgoStatus
`OPER_TYPE_CANCELED`OPER_TYPE_NOOPENED`OPER_TYPE_MODIFY`OPER_TYPE_SUSPEND`OPER_TYPE_RESTART set' `int$1+til 5; /AtoOperationType
`ALGO_TYPE_TWAP_PLUS`ALGO_TYPE_TWAP_CORE`ALGO_TYPE_VWAP_PLUS`ALGO_TYPE_VWAP_CORE`ALGO_TYPE_POV_CORE`ALGO_TYPE_PASSTHRU set' `int$1+til 6; /AtoAlgoTypeId
`SECU_TYPE_STOCK`SECU_TYPE_DEPO_RECEIPTS`SECU_TYPE_NOTIONAL_BONDS`SECU_TYPE_ENTERPRISE_BONDS`SECU_TYPE_CONVERTIBLE_BOND`SECU_TYPE_CORPORATE_BONDS`SECU_TYPE_DEBT_FINANCED`SECU_TYPE_GOVERNMENT_DEBT`SECU_TYPE_SUBPRIME_MORTGAGE`SECU_TYPE_EQUITY_FUND`SECU_TYPE_HYBRID_FUND`SECU_TYPE_BOND_FUND`SECU_TYPE_PRESERVATION_FUND`SECU_TYPE_MONEY_FUND`SECU_TYPE_OTHER_FUNDS`SECU_TYPE_ISI_FUND`SECU_TYPE_REPO_ASSETS`SECU_TYPE_STOCK_INDEX_FUTURES`SECU_TYPE_BOND_FUTURES`SECU_TYPE_COMMODITY_FUTURES`SECU_TYPE_CALL_OPTIONS`SECU_TYPE_PUT_OPTIONS`SECU_TYPE_DEPO_RIGHTS`SECU_TYPE_DEPO_NUMBER`SECU_TYPE_DEPO_SUBSCRIPTION`SECU_TYPE_DEPO_VOTE`SECU_TYPE_RIGHTS`SECU_TYPE_DISTRIBUTION`SECU_TYPE_PLACEMENT`SECU_TYPE_DEBT`SECU_TYPE_STOCK_PURCHASE`SECU_TYPE_RIGHT_SUBSCRIBE`SECU_TYPE_RIGHT_PUT`SECU_TYPE_VOTE`SECU_TYPE_A_RIGHTS_ISSUE`SECU_TYPE_BOND_TO_SELL_BACK`SECU_TYPE_STANDARD_BOND`SECU_TYPE_BOND_PURCHASE`SECU_TYPE_PRE_ISSUE_BONDS`SECU_TYPE_BOND_ISSUANCE`SECU_TYPE_BOND_UNDERWRITING`SECU_TYPE_SECURITIES_LENDING`SECU_TYPE_BOND_SUBSCRIBERS`SECU_TYPE_BOND_COLLATERAL`SECU_TYPE_BOND_ETF_PLEDGE`SECU_TYPE_DEBT_EQUITY`SECU_TYPE_INDEX`SECU_TYPE_CASH_ASSETS  set' `int$1+til 48; /AtoSecurityType
(TOPICLST:`TOPIC_REPORT_DEAL`TOPIC_REPORT_ORDER`TOPIC_REPORT_INSTRUCTION`TOPIC_REPORT_FUND`TOPIC_REPORT_POSITION`TOPIC_REPORT_ASSET) set' `$("ato.report.deal";"ato.report.order";"ato.report.instruction";"ato.adjust.fund";"ato.adjust.position";"ato.adjust.asset"); /TOPIC_REPORT

\d .

.enum.atoex:mirror .enum.atoexmap:.enum[`MARKET_TYPE_SZ`MARKET_TYPE_SH`MARKET_TYPE_CFE`MARKET_TYPE_SHF`MARKET_TYPE_DCE`MARKET_TYPE_ZCE`MARKET_TYPE_INE]!`XSHE`XSHG`CCFX`XSGE`XDCE`XZCE`XINE;

.enum.atostatusmap:.enum[`ORDER_STATUS_PENDINGNEW`ORDER_STATUS_NEW`ORDER_STATUS_PARTFILLED`ORDER_STATUS_FILLED`ORDER_STATUS_CANCELED`ORDER_STATUS_PENDINGCANCEL`ORDER_STATUS_STOPPED`ORDER_STATUS_PARTCANCELED`ORDER_STATUS_INSIDE_STOPPED`ORDER_STATUS_INSIDE_CANCELED`ORDER_STATUS_WAITNEW`ORDER_STATUS_IN_PROGRESS]!.enum`PENDING_NEW`NEW`PARTIALLY_FILLED`FILLED`CANCELED`PENDING_CANCEL`REJECTED`CANCELED`REJECTED`CANCELED`PENDING_NEW`PENDING_NEW;
.enum.atoalgostatusmap:.enum[`ALGO_STATUS_PENDINGNEW`ALGO_STATUS_NEW`ALGO_STATUS_PARTFILLED`ALGO_STATUS_FILLED`ALGO_STATUS_CANCELED`ALGO_STATUS_PENDINGCANCEL`ALGO_STATUS_STOPPED`ALGO_STATUS_REJECTED`ALGO_STATUS_SUSPENDED`ALGO_STATUS_EXPIRED`ALGO_STATUS_PARTCANCELED`ALGO_STATUS_FORCECANCELED`ALGO_STATUS_FORCEPARTCANCELED`ALGO_STATUS_PENDINGSUSPEND`ALGO_STATUS_PENDINGSTART`ALGO_STATUS_PENDINGNOOPEN`ALGO_STATUS_NOOPENED`ALGO_STATUS_PENDINGMODIFY`ALGO_STATUS_PENDINGNEWSUB`ALGO_STATUS_NOSEND`ALGO_STATUS_PENDINGEXPIRED]!.enum`PENDING_NEW`NEW`PARTIALLY_FILLED`FILLED`CANCELED`PENDING_CANCEL`REJECTED`REJECTED`SUSPENDED`EXPIRED`CANCELED`CANCELED`CANCELED`NULL`NULL`NULL`NULL`PENDING_REPLACE`PENDING_NEW`PENDING_NEW`PENDING_NEW;

.enum.atoside:mirror .enum.atosidemap:.enum[`SIDE_BUY`SIDE_SELL]!.enum`BUY`SELL;

sectype:{[x;y]$[y in .enum`MARKET_TYPE_CFE`MARKET_TYPE_SHF`MARKET_TYPE_DCE`MARKET_TYPE_ZCE`MARKET_TYPE_INE;$[(x like "IO*")|(x like "*-*")|(x like "*[0-9]C[0-9]*")|(x like "*[0-9]P[0-9]*");`OPT;x like "SP*";`FUTSP;`FUT];y in `1`2;$[8=count string x;`OPT;`STK];y in `G`S;`STKHK;`STK]}; /[sym;hsex]

atoposefct:{[x;y]$[x=.enum`OPEN;.enum`OPEN;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`CLOSETODAY;.enum`CLOSE]}; /[posefct;ex]

atoid2oid:{[x]exec first id from .db[.ctrl.O] where ordid=(`$string x)}; /,.z.D=`date$ntime

atoconn:{[x;y]if[not any .z.T within/: .conf.ato.openrange;:()];.ctrl.ato[`Run]:initato[.conf.ato`cfgdir;()];1b;};
atodisc:{[x;y]if[any .z.T within/: .conf.ato.openrange;:()];savedb[];.ctrl.ato[`Run]:freeato[];1b};

.init.feato:{[x]atoconn[`;.z.P];};
.exit.feato:{[x]atodisc[`;.z.P];};
.timer.feato:{[x];}; 
.roll.feato:{[x];};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

/ato msg
.upd.OnDisconnect:{[x].ctrl.ato[`Connect`Login`Disctime]:(0b;0b;.z.P);};
.upd.OnConnect:{[x].ctrl.ato[`Connect`Login`Xonntime]:(1b;0b;.z.P);.ctrl.ato[`LoginReq]:atocall[`atoLogin;.conf.ato`user`pass`ip`mac`info];};

.upd.AtoError:{[x]y:x[0];z:x[1];.ctrl.ato[`ErrTime`ErrReq`ErrFun`ErrCode`ErrMsg]:.z.P,y,z;};

.upd.OnSubTopic:{[x].temp.x3:x;.ctrl.ato.sub[(x[0];x[1];`$x[2])]:.z.P;}; /ato.report.deal,ato.report.order,ato.report.instruction,ato.adjust.fund,ato.adjust.position,ato.adjust.asset

.upd.OnRspLogin:{[x].temp.x0:x;.ctrl.ato[`Logintime`Login`User]:(.z.P;1b;U:flip .enum.LoginKey!flip x[1]);.ctrl.ato[`ACMap]:exec flip[(accountId;marketType)]!`$stkAcctCode from U;{[x]z:vs[`] x[1];atocall[`subscribeReport;("I"$string z[2];"J"$string z[1];x[0])];} each  .enum[.enum.TOPICLST] cross {sv[`] `$string x}each exec flip (productId;unitId;accountId) from  .ctrl.ato.User;};

.upd.OnRspQueryAsset:{[x].temp.x1:x;.temp.L2:flip .enum.AssetKey!flip x[1];if[(count x[1])&not null z:.temp[`FundDst];pubmx[z;`FundUpdate;.conf.me;.temp[`FundAcc];-8!.temp.L2]];};

.upd.OnRspCreateOrderActual:{[x].temp.x2:x;y:.enum.OrderCreateKey!first x[1];z:x[0];if[not null k:exec first id from .db.O where j0=z;$[0<>w:y`errCode;.db.O[k;`status`reason`msg]:(.enum`REJECTED;w;utf82gbk y`errMsg);.db.O[k;`status]:.enum`PENDING_NEW];.db.O[k;`ordid`j2]:(`$string y`sysOrderId;y`orderBatchId);execrpt[k]];};

.upd.OnRspInstructionCreate:{[x].temp.x2:x;y:.enum.InstructionCreateKey!first x[1];z:x[0];if[not null k:exec first id from .db.O where j0=z;$[0<>w:y`errCode;.db.O[k;`status`reason`msg]:(.enum`REJECTED;w;utf82gbk y`errMsg);.db.O[k;`status]:.enum`PENDING_NEW];.db.O[k;`ordid`j2`s1`s2]:(`$string y`sysQuoteId;y`sysQuoteBatchId;`$y`basketId;`$y`externalId);execrpt[k]];};

.upd.OnRspCancelOrderActual:{[x].temp.x3:x;y:.enum.OrderCancelKey!first x[1];z:x[0];if[not null k:exec first id from .db.O where j1=z;$[0<>w:y`errCode;.db.O[k;`cstatus`reason`msg]:(.enum`REJECTED;w;utf82gbk y`errMsg);.db.O[k;`cordid]:`$string y`cancelId];execrpt[k]];};

.upd.OnRspInstructionReplace:.upd.OnRspInstructionControl:{[x].temp.x3:x;y:.enum.InstructionControlKey!first x[1];z:x[0];if[not null k:exec first id from .db.O where j1=z;$[0<>w:y`errCode;.db.O[k;`cstatus`reason`msg]:(.enum`REJECTED;w;utf82gbk y`errMsg);[]];execrpt[k]];};

.upd.OnRtnOrderReport:{[x].temp.x10:x;y:.enum.OrderKey!x;.temp.L10,:enlist y;z:atoid2oid y`sysOrderId;r:.db[.ctrl.O;z];if[null r`sym;:()];cq:`float$y`cumQty;if[cq<r`cumqty;:()];s:.enum.atostatusmap y`orderStatus;.db[.ctrl.O;z;`msg`exchid`s3`rtime]:(y`remark;`$y`brokerOrderId;`$y`clOrderId;.z.P);if[s in .enum`NEW`CANCELED`REJECTED;.db[.ctrl.O;z;`status]:s];if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.OnRtnTradeReport:{[x].temp.x11:x;y:.enum.TradeKey!x;.temp.L11,:enlist y;z:atoid2oid y`sysOrderId;r:.db[.ctrl.O;z];if[null r`sym;:()];lp:y`dealPx;lq:`float$y`dealQty;cq:lq+q0:0f^r`cumqty;ap:((lp*lq)+q0*p0:0f^r`avgpx)%cq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;if[not r[`status]=.enum`CANCELED;.db[.ctrl.O;z;`status]:.enum $[cq=r`qty;`FILLED;`PARTIALLY_FILLED]];execrpt[z];};

.upd.OnRtnInstructionReport:{[x].temp.x12:x;y:.enum.InstructionKey!x;.temp.L12,:enlist y;z:atoid2oid y`sysQuoteId;r:.db[.ctrl.O;z];if[null r`sym;:()];cq:`float$y`cumQty1;if[cq<r`cumqty;:()];s:.enum.atoalgostatusmap y`algoStatus;.db[.ctrl.O;z;`msg`rtime`rptopt]:(y`rspAlgoInfo;.z.P;.j.j `cumQty2`cumAmt2`outstandingQty1`outstandingQty2`leavesQty1`leavesQty2`taskAmt`cumAmt1`cumAmt2`algoStatus#y);if[0<cq;ca:y`cumAmt1;lq:cq-q0:0f^r`cumqty;ap:ca%cq;lp:(ca-q0*p0:0f^r`avgpx)%lq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;if[not s=.enum`CANCELED;s:.enum $[cq=r`qty;`FILLED;`PARTIALLY_FILLED]]];.db[.ctrl.O;z;`status]:s;if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];execrpt[z];};

.upd.OnRtnFundReport:{[x].temp.x8:x;y:.enum.FundChgKey!x;.ctrl.ato.FUND,:5!enlist y;};
.upd.OnRtnPositionReport:{[x].temp.x9:x;y:.enum.PositionChgKey!x;.ctrl.ato.POS,:6!enlist y;};

.upd.OnRspQueryOrderActual:{[x].temp.x13:x;y:.enum.OrderQryKey!first x[1];.temp.L13,:enlist y;z:atoid2oid y`sysOrderId;r:.db[.ctrl.O;z];if[null r`sym;:()];cq:`float$y`dealQty;if[cq<r`cumqty;:()];s:.enum.atostatusmap y`orderStatus;.db[.ctrl.O;z;`msg`exchid`rtime]:(y`remark;`$y`brokerOrderId;.z.P);if[s in .enum`NEW`CANCELED`REJECTED;.db[.ctrl.O;z;`status]:s];if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];if[cq>q0:0f^r`cumqty;ap:(ca:y`dealAmt)%cq;lq:cq-q0;lp:(ca-q0*0f^r`avgpx)%lq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;if[not r[`status]=.enum`CANCELED;.db[.ctrl.O;z;`status]:.enum $[cq=r`qty;`FILLED;`PARTIALLY_FILLED]]];execrpt[z];};

.upd.OnRspQueryOrderInstruction:{[x].temp.x14:x;y:.enum.InstructionQryKey!first x[1];.temp.L14,:enlist y;.upd.OnRtnInstructionReport value .enum.InstructionKey#y;};

/Tx msg
.upd.ordnew:.fe.ordnew:{[x].temp.x9:x;if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;h:$[count opt:x`ordopt;strdict opt;(`symbol$())!()];if[not null .db[.ctrl.O;k;`sym];:()];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ato`Login)&(.conf.ato.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"ATO_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;pua:"IJI"$'string vs[`]x`acc1;ae:.enum.atoex ex;as:.enum.atoside x`side;ac:.ctrl.ato[`ACMap] pua[2];k2:sv[`;x`ft`ts`oid];$[1b~h`algo;[.db[.ctrl.O;k;`special]:`algo;y:`int$h`algotype;z:`side`task_qty`account_id`limit_action`after_action!(as;x`qty;pua[2];0;0),$[0<p:x`price;enlist `price!rnlist p;()];tl:"J"$except[;":.T"] each string `datetime$vtd[]+"T"$string h[`algopara]`start_time`end_time;r:atocall[`reqInstructionCreate;enlist (y;pua[0];pua[1];pua[2];k1;k2;esym;ae;ac;tl 0;tl 1;`$.j.j z)]];[r:atocall[`reqCreateOrderActual;enlist (k1;k2;0;0i;pua[0];pua[1];pua[2];ac;ae;esym;as;`long$x`qty;x`price;$[(0<x[`price])|(esym like "SP*");.enum`PRICE_TYPE_LIMIT;.enum`PRICE_TYPE_REVERSE_BEST_LIMIT])]]];.db[.ctrl.O;k;`j0]:r[1];}'; 

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[null r`sym;:()];.db[.ctrl.O;k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];r:$[`algo=r`special;atocall[`reqInstructionControl;enlist ("J"$string r`ordid;.enum`OPER_TYPE_CANCELED)];atocall[`reqCancelOrderActual;enlist ("J"$string r`ordid;.conf.ato`info)]];.db[.ctrl.O;k;`j1]:r[1];}'; 

.upd.ordqry:.fe.ordqry:{[x]r:.db[.ctrl.O;x`oid];z:"J"$string r`ordid;atocall[$[`algo=r`special;`reqQueryInstruction;`reqQueryOrderActual];(`;1;`;`;`;`;`;`;`;`;`;z)];}';

.upd.QueryFund:{[x].temp.x11:x;.temp[`FundDst`FundAcc]:x`ref`msg;.temp.L2:();atocall[`reqQueryAsset;(`;2000i;1i;`;`)];};

.upd.QueryPos:{[x].temp.x12:x;.temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();atocall[i;`reqQryHold;2#`];};

.upd.QueryOrdAcc:{[x].temp.x13:x;.temp[`OrdDst`OrdAcc]:x`ref`msg;.temp.L4:();if[null i:.ctrl.ato.usermap u:-9!x`vbin;:()];atocall[i;`reqQryOrder;(0i;`;0i;`;0)];};

.upd.QueryMatAcc:{[x].temp.x14:x;.temp[`MatDst`MatAcc]:x`ref`msg;.temp.L5:();if[null i:.ctrl.ato.usermap u:-9!x`vbin;:()];atocall[i;`reqQryTrade;(0i;`;0i;`;0)];};

