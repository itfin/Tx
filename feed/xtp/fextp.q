.module.fextp:2019.12.17;

txload "core/febase";
txload "feed/xtp/xtpbase";

`initxtpt`freextpt`xtptrun`insertOrder`cancelOrder`queryOrder`queryAllOrder`queryTrade`queryAllTrade`queryPos`queryAsset`transFund`qryFundTrans`qryETF`qryETFPCF`qryIPO`qryIPOQuota`qryOption {x set `extfextp 2:(x;y);}' 2 1 1,15#3;

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
`XTP_MKT_INIT`XTP_MKT_SZ_A`XTP_MKT_SH_A`XTP_MKT_UNKNOWN set' `int$til 4;  /XTP_MARKET_TYPE:0(初始化值或者未知)1(深圳A股)2(上海A股)3(未知交易市场类型)

`XTP_PRICE_LIMIT`XTP_PRICE_BEST_OR_CANCEL`XTP_PRICE_BEST5_OR_LIMIT`XTP_PRICE_BEST5_OR_CANCEL`XTP_PRICE_ALL_OR_CANCEL`XTP_PRICE_FORWARD_BEST`XTP_PRICE_REVERSE_BEST_LIMIT`XTP_PRICE_LIMIT_OR_CANCEL`XTP_PRICE_TYPE_UNKNOWN  set' `int$1+til 9;   /XTP_PRICE_TYPE:1(限价单-沪|深|沪期权<除普通股票业务外，其余业务均使用此种类型>)2(即时成交剩余转撤销,市价单-深|沪期权)3(最优五档即时成交剩余转限价,市价单-沪)4(最优5档即时成交剩余转撤销,市价单-沪深)5(全部成交或撤销,市价单-深|沪期权)6(本方最优,市价单-深)7(对方最优剩余转限价,市价单-深|沪期权)8(期权限价申报FOK)9(未知或者无效价格类型)

`XTP_SIDE_BUY`XTP_SIDE_SELL`XTP_SIDE_PURCHASE`XTP_SIDE_REDEMPTION`XTP_SIDE_SPLIT`XTP_SIDE_MERGE`XTP_SIDE_COVER`XTP_SIDE_FREEZE`XTP_SIDE_MARGIN_TRADE`XTP_SIDE_SHORT_SELL`XTP_SIDE_REPAY_MARGIN`XTP_SIDE_REPAY_STOCK`XTP_SIDE_STOCK_REPAY_STOCK`XTP_SIDE_SURSTK_TRANS`XTP_SIDE_GRTSTK_TRANSIN`XTP_SIDE_GRTSTK_TRANSOUT`XTP_SIDE_UNKNOWN set' `char$1 2 7 8 9 10 11 12 21 22 23 24 26 27 28 29 30;    /XTP_SIDE_TYPE:1(买<新股申购,ETF买,配股,信用交易中担保品买>)2(卖<逆回购,ETF卖,信用交易中担保品卖>)7(申购)8(赎回)9(拆分)10(合并)11(备兑)12(锁定<对应开平标识为开>|解锁<对应开平标识为平>)21(融资买入)22(融券卖出)23(卖券还款)24(买券还券)26(现券还券)27(余券划转)28(担保品转入)29(担保品转出)30(未知或者无效买卖方向)

`XTP_POSITION_EFFECT_INIT`XTP_POSITION_EFFECT_OPEN`XTP_POSITION_EFFECT_CLOSE`XTP_POSITION_EFFECT_FORCECLOSE`XTP_POSITION_EFFECT_CLOSETODAY`XTP_POSITION_EFFECT_CLOSEYESTERDAY`XTP_POSITION_EFFECT_FORCEOFF`XTP_POSITION_EFFECT_LOCALFORCECLOSE`XTP_POSITION_EFFECT_CREDIT_FORCE_COVER`XTP_POSITION_EFFECT_CREDIT_FORCE_CLEAR`XTP_POSITION_EFFECT_CREDIT_FORCE_DEBT`XTP_POSITION_EFFECT_CREDIT_FORCE_UNCOND`XTP_POSITION_EFFECT_UNKNOWN  set' `char$til 13; /XTP_POSITION_EFFECT_TYPE:0(初始值或未知值开平标识,现货适用)1(开)2(平)3(强平)4(平今)5(平昨)6(强减)7(本地强平)8(信用业务追保强平)9(信用业务清偿强平)10(信用业务合约到期强平)11(信用业务无条件强平)12(未知的开平标识类型)

`XTP_BUSINESS_TYPE_CASH`XTP_BUSINESS_TYPE_IPOS`XTP_BUSINESS_TYPE_REPO`XTP_BUSINESS_TYPE_ETF`XTP_BUSINESS_TYPE_MARGIN`XTP_BUSINESS_TYPE_DESIGNATION`XTP_BUSINESS_TYPE_ALLOTMENT`XTP_BUSINESS_TYPE_STRUCTURED_FUND_PURCHASE_REDEMPTION`XTP_BUSINESS_TYPE_STRUCTURED_FUND_SPLIT_MERGE`XTP_BUSINESS_TYPE_MONEY_FUND`XTP_BUSINESS_TYPE_OPTION`XTP_BUSINESS_TYPE_EXECUTE`XTP_BUSINESS_TYPE_FREEZE`XTP_BUSINESS_TYPE_UNKNOWN set' `int$til 14;     /XTP_BUSINESS_TYPE:0(普通股票业务>股票买卖,ETF买卖等>)1(新股申购业务<对应的price type需选择限价类型>)2(回购业务<对应的price type为限价,side为卖>)3(ETF申赎业务)4(融资融券业务<暂未支持>)5(转托管<未支持>)6(配股业务<对应的price type需选择限价类型,side为买>)7(分级基金申赎业务)8(分级基金拆分合并业务)9(货币基金业务<暂未支持>)10(期权业务)11(行权)12(锁定解锁,暂不支持)13(未知类型)

`XTP_ORDER_STATUS_INIT`XTP_ORDER_STATUS_ALLTRADED`XTP_ORDER_STATUS_PARTTRADEDQUEUEING`XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING`XTP_ORDER_STATUS_NOTRADEQUEUEING`XTP_ORDER_STATUS_CANCELED`XTP_ORDER_STATUS_REJECTED`XTP_ORDER_STATUS_UNKNOWN set' `int$til 8; /XTP_ORDER_STATUS_TYPE:0(初始化)1(全部成交)2(部分成交)3(部分撤单)4(未成交)5(已撤单)6(已拒绝)7(未知订单状态)
`XTP_ORDT_Normal`XTP_ORDT_DeriveFromQuote`XTP_ORDT_DeriveFromCombination`XTP_ORDT_Combination`XTP_ORDT_ConditionalOrder`XTP_ORDT_Swap  set' "012345";  /TXTPOrderTypeType:0(正常)1(报价衍生)2(组合衍生)3(组合报单)4(条件单)5(互换单)

`XTP_FUND_TRANSFER_OUT`XTP_FUND_TRANSFER_IN`XTP_FUND_INTER_TRANSFER_OUT`XTP_FUND_INTER_TRANSFER_IN`XTP_FUND_TRANSFER_UNKNOWN set' `int$til 5; /XTP_FUND_TRANSFER_TYPE:0(转出 从XTP转出到柜台)1(转入 从柜台转入XTP)2(跨节点转出 从本XTP节点1,转出到对端XTP节点2)3(跨节点转入 从对端XTP节点2,转入到本XTP节点1)4(未知类型)

`XTP_POSITION_DIRECTION_NET`XTP_POSITION_DIRECTION_LONG`XTP_POSITION_DIRECTION_SHORT`XTP_POSITION_DIRECTION_COVERED set' `int$til 4; /XTP_POSITION_DIRECTION_TYPE:0(净)1(多<期权则为权利方>)2(空<期权则为义务方>)3(备兑<期权则为备兑义务方>)

`XTP_ACCOUNT_NORMAL`XTP_ACCOUNT_CREDIT`XTP_ACCOUNT_DERIVE`XTP_ACCOUNT_UNKNOWN set' `int$til 4; /XTP_ACCOUNT_TYPE:0(普通账户)1(信用账户)2(衍生品账户)3(未知账户类型)

`XTP_FUND_OPER_PROCESSING`XTP_FUND_OPER_SUCCESS`XTP_FUND_OPER_FAILED`XTP_FUND_OPER_SUBMITTED`XTP_FUND_OPER_UNKNOWN set' `int$til 5; /XTP_FUND_OPER_STATUS:0(XTP已收到，正在处理中)1(成功)2(失败)3(已提交到集中柜台处理)4(未知) 

`ERT_CASH_FORBIDDEN`ERT_CASH_OPTIONAL`ERT_CASH_MUST`ERT_CASH_RECOMPUTE_INTER_SZ`ERT_CASH_MUST_INTER_SZ`ERT_CASH_RECOMPUTE_INTER_OTHER`ERT_CASH_MUST_INTER_OTHER`EPT_INVALID set' `int$til 8; /ETF_REPLACE_TYPE:0(禁止现金替代)1(可以现金替代)2(必须现金替代)3(深市退补现金替代)4(深市必须现金替代)5(非沪深市场成分证券退补现金替代)6(表示非沪深市场成份证券必须现金替代)7(无效值)

`XTP_TICKER_TYPE_STOCK`XTP_TICKER_TYPE_INDEX`XTP_TICKER_TYPE_FUND`XTP_TICKER_TYPE_BOND`XTP_TICKER_TYPE_OPTION`XTP_TICKER_TYPE_TECH_STOCK`XTP_TICKER_TYPE_UNKNOWN set' til 7; /XTP_TICKER_TYPE:0(普通股票)1(指数)2(基金)3(债券)4(期权)5(科创板股票<上海>)6(未知类型)

`XTP_OPT_CALL`XTP_OPT_PUT set' `int$1+til 2; /XTP_OPT_CALL_OR_PUT_TYPE:1(认购)2(认沽)
`XTP_OPT_EXERCISE_TYPE_EUR`XTP_OPT_EXERCISE_TYPE_AME set' `int$1+til 2; /XTP_OPT_EXERCISE_TYPE_TYPE:1(欧式)2(美式)

XTPReqHead:`session_id`error_id`error_msg;
XTPQryHead:`request_id`is_last,XTPReqHead;
XTPOrderKey:`order_xtp_id`order_client_id`order_cancel_xtp_id`ticker`market`price`quantity`price_type`side`position_effect`business_type`qty_traded`qty_left`insert_time`update_time`cancel_time`trade_amount`order_local_id`order_status`order_submit_status`order_type;
XTPTradeKey:`order_xtp_id`order_client_id`ticker`market`exec_id`price`quantity`trade_time`trade_amount`report_index`order_exch_id`trade_type`side`position_effect`business_type`branch_pbu;
XTPTransKey:`serial_id`transfer_type`amount`oper_status`transfer_time;

\d .

.enum.xtpexT:mirror .enum.exxtpT:.enum[`XTP_MKT_SH_A`XTP_MKT_SZ_A]!`XSHG`XSHE;
.enum.xtpside:mirror .enum.sidextp:.enum[`XTP_SIDE_BUY`XTP_SIDE_SELL]!.enum[`BUY`SELL];
.enum.xtpposefct:mirror .enum.posefctxtp:.enum[`XTP_POSITION_EFFECT_INIT`XTP_POSITION_EFFECT_OPEN`XTP_POSITION_EFFECT_CLOSE`XTP_POSITION_EFFECT_CLOSETODAY`XTP_POSITION_EFFECT_CLOSEYESTERDAY]!.enum[`NULL`OPEN`CLOSE`CLOSETODAY`CLOSEYESTODAY];
.enum.statusxtp:.enum[`XTP_ORDER_STATUS_INIT`XTP_ORDER_STATUS_ALLTRADED`XTP_ORDER_STATUS_PARTTRADEDQUEUEING`XTP_ORDER_STATUS_PARTTRADEDNOTQUEUEING`XTP_ORDER_STATUS_NOTRADEQUEUEING`XTP_ORDER_STATUS_CANCELED`XTP_ORDER_STATUS_REJECTED`XTP_ORDER_STATUS_UNKNOWN]!.enum`PENDING_NEW`FILLED`PARTIALLY_FILLED`CANCELED`NEW`CANCELED`REJECTED`NULL;

\d .temp
QREF:QUEUE:L23:L22:L21:L20:L19:L18:L17:L16:L15:L14:L13:L12:L11:L10:L:C:();MDSub:QTSub:()!();
\d .

xtpid2oid:{[x]exec first id from .db[.ctrl.O] where ordid=x,.z.D=`date$ntime};

xtptconn:{[x;y]if[not any .z.T within/: .conf.xtp.openrange;:()];if[1i~.ctrl.xtp[`runT];:()];.ctrl.xtp[`conntimeT]:.z.P;.ctrl.xtp[`runT]:r:initxtpt[(.conf.xtp.cltid;.conf.xtp.tmpath;`int$`fatal`error`warning`info`debug`trace?.conf.xtp.loglevel;.conf.xtp.cltver;.conf.xtp.authocde;.conf.xtp.hbint);(.conf.xtp.osvrip;.conf.xtp.osport;.conf.xtp.user;.conf.xtp.pass;.conf.xtp.usetcp)];1b;};
xtptdisc:{[x;y]if[any .z.T within/: .conf.xtp.openrange;:()];if[1i~.ctrl.xtp[`runT];:()];.ctrl.xtp[`runT]:freextpt[];1b;};

.init.ftxtp:{[x]xtptconn[`;.z.P];};
.exit.ftxtp:{[x].ctrl.xtp[`runT]:freextpt[];};

.timer.ftxtp:{[x]if[any .z.T within/:.conf.xtp.openrange;];};

.upd.DisconnectedT:{[x].ctrl.xtp[`ConnectT`LoginT`DiscReasonT`DisctimeT]:(0b;0b;x[0];.z.P);};

.upd.LoginFailT:{[x].ctrl.xtp[`LoginT`LoginTimeT`LoginErrT`ErrCodeT`ErrMsgT]:(0b;.z.P;1b),x;}; 
.upd.LoginT:{[x].ctrl.xtp[`LoginT`logintimeT`SessionID`ApiVersionT`TradingDayT`ServerRestart]:(1b;.z.P),x;};

.upd.XTPErrorT:{[x].ctrl.xtp[`ErrTimeT`ErrCodeT`ErrMsgT`ErrFun]:.z.P,x;};

.upd.RDUpdate:{[x]if[`xtp<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;};

.upd.ordnew:.fe.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[count opt:x`ordopt;h:strdict opt];if[not null .db[.ctrl.O;k;`sym];:()];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.xtp`LoginT)&(.conf.xtp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"XTP_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;.db[.ctrl.O;k;`j0]:r:xtpcall[`insertOrder;(1+rand 5i;esym;.enum.xtpexT ex;x`price;`long$x`qty;$[(0<x[`price])|(esym like "SP*");.enum`XTP_PRICE_LIMIT;.enum`XTP_PRICE_BEST5_OR_CANCEL];.enum.xtpside x`side;.enum.xtpposefct x`posefct;.enum`XTP_BUSINESS_TYPE_CASH)];if[0<r;.db[.ctrl.O;k;`ordid]:`$string r];}'; 

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[null r`sym;:()];.db[.ctrl.O;k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];r:xtpcall[`cancelOrder;"J"$string r`ordid];if[0<r;.db[.ctrl.O;k;`cordid]:`$string r];}'; 

.upd.ordqry:.fe.ordqry:{[x]r:.db[.ctrl.O;x`oid];xtpcall[`queryOrder;"J"$string r`ordid];}';

transfund:{[x;y]xtpcall[`transFund;(.conf.xtp.user;.conf.xtp.pass;`float$y;x)]} /[transtype;amount]
transout:transfund[.enum.`XTP_FUND_TRANSFER_OUT];transin:transfund[.enum.`XTP_FUND_TRANSFER_IN];

.upd.Order:{[x].temp.L10,:enlist y:(.enum[`XTPReqHead],.enum.XTPOrderKey)!x;z:xtpid2oid `$string y`order_xtp_id;r:.db[.ctrl.O;z];if[null r`sym;:()];cq:`float$y`qty_traded;if[cq<r`cumqty;:()];.db[.ctrl.O;z;`status`reason`msg]:(s:.enum.statusxtp y`order_status;y`error_id;y`error_msg);if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.Trade:{[x].temp.L11,:enlist y:(`session_id,.enum.XTPTradeKey)!x;z:xtpid2oid `$string y`order_xtp_id;r:.db[.ctrl.O;z];if[null r`sym;:()];lp:y`price;lq:`float$y`quantity;cq:lq+q0:0f^r`cumqty;ap:((lp*lq)+q0*p0:0f^r`avgpx)%cq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;if[not r[`status]=.enum`CANCELED;.db[.ctrl.O;z;`status]:.enum $[cq=r`qty;`FILLED;`PARTIALLY_FILLED]];execrpt[z];};

.upd.OrderCxlErr:{[x].temp.L12,:enlist y:(.enum[`XTPReqHead],`order_xtp_id`order_cancel_xtp_id)!x;z:xtpid2oid `$string y`order_xtp_id;if[null .db[.ctrl.O;z;`sym];:()];.db[.ctrl.O;z;`cstatus`reason`msg]:(.enum`REJECTED;y`error_id;y`error_msg);};

.upd.FundTrans:{[x].temp.L13,:enlist y:(.enum[`XTPReqHead],.enum`XTPTransKey)!x;};

.upd.QryOrder:{[x]b:x[0];x:x[1];.temp.L14,:enlist y:(.enum[`XTPQryHead],.enum.XTPOrderKey)!x;if[0<>y`error_id;:()];z:xtpid2oid `$string y`order_xtp_id;r:.db[.ctrl.O;z];if[null r`sym;:()];cq:`float$y`qty_traded;if[cq<r`cumqty;:()];.db[.ctrl.O;z;`status`cumqty]:(s:.enum.statusxtp y`order_status;cq);if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];execrpt[z];};

.upd.QryTrade:{[x]b:x[0];x:x[1];.temp.L15,:enlist y:(.enum[`XTPQryHead],.enum.XTPTradeKey)!x;};

.upd.QryPos:{[x]b:x[0];x:x[1];.temp.L16,:enlist y:(.enum[`XTPQryHead],`ticker`ticker_name`market`total_qty`sellable_qty`avg_price`unrealized_pnl`yesterday_position`purchase_redeemable_qty`position_direction`executable_option`lockable_position`executable_underlying`locked_position`usable_locked_position)!x;.db.P[``,sv[`] (`$y[`ticker]),.enum.exxtpT y`market;`lqty`lqty0]:`float$0|y[`total_qty]-0,y`yesterday_position;};

.upd.QryAsset:{[x]b:x[0];x:x[1];.temp.L17,:enlist y:(.enum[`XTPQryHead],`total_asset`buying_power`security_asset`fund_buy_amount`fund_buy_fee`fund_sell_amount`fund_sell_fee`withholding_amount`account_type`frozen_margin`frozen_exec_cash`frozen_exec_fee`pay_later`preadva_pay`orig_banlance`banlance`deposit_withdraw`trade_netting`captial_asset`force_freeze_amount`preferred_amount`repay_stock_aval_banlance)!x;if[not null .temp[`FundDst];pubmx[.temp[`FundDst];`FundUpdate;.conf.me;"";-8!.temp.L17]];};

.upd.QryFundTrans:{[x]b:x[0];x:x[1];.temp.L18,:enlist y:(.enum[`XTPQryHead],.enum`XTPTransKey)!x;};

.upd.QryETF:{[x]b:x[0];x:x[1];.temp.L19,:enlist y:(.enum[`XTPQryHead],`market`etf`subscribe_redemption_ticker`unit`subscribe_status`redemption_status`max_cash_ratio`estimate_amount`cash_component`net_value`total_amount)!x;};

.upd.QryETFPCF:{[x]b:x[0];x:x[1];.temp.L20,:enlist y:(.enum[`XTPQryHead],`market`ticker`component_ticker`component_name`quantity`component_market`replace_type`premium_ratio`amount)!x;};

.upd.QryIPO:{[x]b:x[0];x:x[1];.temp.L21,:enlist y:(.enum[`XTPQryHead],`market`ticker`ticker_name`ticker_type`price`unit`qty_upper_limit)!x;};

.upd.QryIOOQuota:{[x]b:x[0];x:x[1];.temp.L22,:enlist y:(.enum[`XTPQryHead],`market`quantity`tech_quantity)!x;};

.upd.QryOption:{[x]b:x[0];x:x[1];.temp.L23,:enlist y:(.enum[`XTPQryHead],`ticker`security_id_source`symbol`contract_id`underlying_security_id`underlying_security_id_source`list_date`last_trade_date`ticker_type`day_trading`call_or_put`delivery_day`delivery_month`exercise_type`exercise_begin_date`exercise_end_date`exercise_price`qty_unit`contract_unit`contract_position`prev_close_price`prev_clearing_price`lmt_buy_max_qty`lmt_buy_min_qty`lmt_sell_max_qty`lmt_sell_min_qty`mkt_buy_max_qty`mkt_buy_min_qty`mkt_sell_max_qty`mkt_sell_min_qty`price_tick`upper_limit_price`lower_limit_price`sell_margin`margin_ratio_param1`margin_ratio_param2)!x;};

.upd.QueryFund:{[x].temp.FundDst:x`ref;.temp.L17:();xtpcall[`queryAsset;()];};

qryallorder:{[]xtpcall[`queryAllOrder;(`;0;0)];};
qrytrade:{[x]xtpcall[`queryTrade;x];};
qryalltrade:{[]xtpcall[`queryAllTrade;(`;0;0)];};
qrypos:{[]xtpcall[`queryPos;`];};
qryasset:{[]xtpcall[`queryAsset;()];};
qryfundtrans:{[]xtpcall[`qryFundTrans;0];};
qryetf:{[]xtpcall[`qryETF;(0i;`)];};
qryetfpcf:{[x]y:fs2se x;xtpcall[`qryETFPCF;(.enum.xtpexT y[1];y[0])];};
qryipo:{[]xtpcall[`qryIPO;()];};
qryipoquota:{[]xtpcall[`qryIPOQuota;()];};
qryopt:{[]xtpcall[`qryOption;(0i;`)];};