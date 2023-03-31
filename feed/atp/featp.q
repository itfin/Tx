.module.featp:2022.07.13;

txload "core/febase";
txload "feed/atp/atpbase";

`initatp`freeatp`atprun`atplogvel`atpLogin`atpLogout`insertOrder`insertRepo`cancelOrder`queryOrder`queryPos`queryAsset`queryTrade {x set `extfeatp 2:(x;y);}' 2 1 1 1,9#2;

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

if[1b~.conf.atp`kdencode;`encodepass {x set `kdencode 2:(x;y);}' 2;.conf.atp[`pass_plain]:.conf.atp`pass;.conf.atp.pass:`$encodepass[.conf.atp`kdkey;.conf.atp`pass]];

\d .enum
`kCashBAT`kBrokerageOption`kMargin set' `char$1 2 3; /BusinessAbstractType
`kNULL`kShangHai`kShenZhen set' 0 101 102h; /ATPMarketIDConst
`kGFD`kIOC`kFOK`kAtCrossing set' "0349"; /ATPTimeInForce
`kAll`kBuy`kSell`kRepo`kAntiRepo`kSwap`kPutBack`kTenderOffer`kDisTenderOffer`kPutBackRevoke`kActivation`kCancellation`kPurchase`kRedeem`kLoan`kBorrow`kPhysicalPurchase`kPhysicalRedemption`kOpen`kMerge`kQuery`kDesignationTransfer`kReverDsignationTransfer`kLock`kUnLock`kDisposal`kDisposalReturn`kPledgeIn`kPledgeOut`kSellRepay`kBuyRedeliver`kFinancingBuy`kLoanSell`kReDeliver`kGageIn`kGageOut`kMarginOffset`kShortSaleOffset`kSourceSecurityIn`kSourceSecurityOut`kExtraSecurityOut set' "0123456789ACDEFGPROMQJKZY@%HINUBSTVLWX$*#"; /ATPSide
`kCash`kOpen`kClose set' "123"; /ATPCashMargin
`kFixedNew`kLocalOptimalNew`kCountPartyOptimalTransferFixed`kImmediateDealTransferCancel`kFullDealOrCancel`kOptimalFiveLevelFullDealTransferCancel`kOptimalFiveLevelImmediateDealTransferFixed`kMarketTransferFixed`kFixedFullDealOrCancel`kSzBiddingFixed`kShBiddingFixed set' "abcdefghijk"; /ATPOrdType
`kNewET`kInternal`kCancelledET`kRejectET`kTrade`kGold set' "0148FJ"; /ATPExecType
`kNew`kPartiallyFilled`kFilled`kPartiallyFilledPartiallyCancelled`kCancelled`kPartiallyCancelled`kReject`kUnSend`kSended`kWaitCancelled`kPartiallyFilledWaitCancelled`kProcessed set' `char$0 1 2 3 4 5 8 9 10 11 12 13; /ATPOrdStatus
orderkey:`partition`index`business_type`cl_ord_no`security_id`market_id`exec_type`ord_status`cust_id`fund_account_id`account_id`price`order_qty`leaves_qty`cum_qty`side`transact_time`user_info`order_id`cl_ord_id`extra_data`client_seq_id`orig_cl_ord_no`frozen_trade_value`frozen_fee`reject_reason_code`ord_rej_reason`order_type`time_in_force`position_effect`covered_or_uncovered`account_sub_code`quote_flag`security_symbol`secondary_order_id`parent_cl_ord_no;
tradekey:`partition`index`business_type`cl_ord_no`security_id`market_id`exec_type`ord_status`cust_id`fund_account_id`account_id`price`order_qty`leaves_qty`cum_qty`side`transact_time`user_info`order_id`cl_ord_id`exec_id`last_px`last_qty`total_value_traded`fee`client_seq_id`extra_data`cash_margin`orig_cl_ord_no`reject_reason_code`ord_rej_reason`parent_cl_ord_no;
ordrejkey:`client_seq_id`user_info`extra_data`transact_time`api_msg_type`reject_reason_code`business_reject_text;
fundkey:`cust_id`fund_account_id`branch_id`account_id`client_seq_id`query_result_code`user_info`extra_data`leaves_value`init_leaves_value`available_t0`available_t1`available_t2`available_t3`available_tall`frozen_all`te_partition_no`credit_sell_frozen`credit_sell_occupied`credit_sell_pre_occupied`init_credit_sell;
poskey:`security_id`security_symbol`market_id`account_id`fund_account_id`branch_id`init_qty`leaves_qty`available_qty`profit_loss`market_value`cost_price`currency`init_crd_sell_buy_share_qty`init_crd_sell_occupied_amt`cur_crd_sell_occupied_qty`cur_crd_sell_occupied_amt`security_type;
ordqrykey:`business_type`security_id`security_symbol`market_id`account_id`side`ord_type`ord_status`transact_time`order_price`exec_price`order_qty`leaves_qty`cum_qty`cl_ord_no`order_id`cl_ord_id`client_seq_id`orig_cl_ord_no`frozen_trade_value`frozen_fee`currency`reject_reason_code`ord_rej_reason`order_entrusted_amt`order_cum_transaction_amt`exec_type`security_type`canceled_qty`order_flag;
trdqrykey:`business_type`security_id`security_symbol`market_id`account_id`side`ord_type`exec_type`exec_id`cl_ord_no`order_id`cl_ord_id`transact_time`last_px`last_qty`total_value_traded`fee`currency`client_seq_id`security_type;

qryreskey:`cust_id`fund_account_id`account_id`client_seq_id`query_result_code`user_info`extra_data`last_index`total_num;

\d .
.enum.statusatp:.enum[`kNew`kPartiallyFilled`kFilled`kPartiallyFilledPartiallyCancelled`kCancelled`kPartiallyCancelled`kReject`kUnSend`kSended`kWaitCancelled`kPartiallyFilledWaitCancelled`kProcessed]!.enum[`NEW`PARTIALLY_FILLED`FILLED`CANCELED`CANCELED`CANCELED`REJECTED`NEW`NEW`PENDING_CANCEL`PENDING_CANCEL`NEW];

atpconn:{[x;y]if[not any .z.T within/: .conf.atp.openrange;:()];.ctrl.atp[`Run]:initatp[.conf.atp`gwuser`gwpass`gwaddr`hbint`conntmout`reconncnt`appname`appver`mode;.conf.atp.loglevel];1b;};
atpdisc:{[x;y]if[any .z.T within/: .conf.atp.openrange;:()];.ctrl.atp[`Run]:freeatp[];1b};

.init.featp:{[x]atpconn[`;.z.P];};
.exit.featp:{[x]atpdisc[`;.z.P];};
.timer.featp:{[x]if[not (1b~.ctrl.atp`Connected)&(1b~.ctrl.atp`GWLogin);:()];atplogin[]}; 

//insu2exch:{$[x like "IF*";`G;`]};insu2cont:{[x]"I"$(string 100 sv "i"$-4_x),-4#x};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

atplogin:{[]if[(1b~.ctrl.atp`Login)|(1b~.ctrl.atp`PassErr);:()];atpcall[`atpLogin;.conf.atp[`fund_account`pass`cust_id`branch_id`order_way`authcode`login_mode`extra];};
atplogout:{[]if[not 1b~.ctrl.atp`Login;:()];atpcall[`atpLogout;.conf.atp`fund_account`authcode];};

.upd.Connected:{[x].ctrl.atp[`Connected`Conntime]:(1b;.z.P);};
.upd.ConnectFailure:{[x].ctrl.atp[`Connected`ConnErr`ConnErrMsg]:(0b;`Failure;x[0]);};
.upd.ConnectTimeOut:{[x].ctrl.atp[`Connected`ConnErr`ConnErrMsg]:(0b;`TimeOut;x[0]);};
.upd.HeartbeatTimeOut:{[x].ctrl.atp[`Connected`ConnErr`ConnErrMsg]:(0b;`HBTimeOut;x[0]);};
.upd.EndOfConnection:{[x].ctrl.atp[`Connected`ConnErr`ConnErrMsg]:(0b;`EndOfConnection;x[0]);};
.upd.Closed:{[x].ctrl.atp[`Connected`Disctime`ConnErr`ConnErrMsg]:(0b;.z.P;`Closed;x[0]);};

.upd.Login:{[x].ctrl.atp[`GWLogin`GWLogintime]:(1b;.z.P);};
.upd.Logout:{[x].ctrl.atp[`GWLogin`GWLogouttime`GWErrMsg]:(0b;.z.P;x[0]);};

.upd.Error:{[x].ctrl.atp[`ErrMsg`ErrTime]:(x[0];.z.P);lwarn[`atperror;x];};
.upd.Log:{[x]linfo[`atplog;x];};

.upd.CustLogin:{[x]linfo[`atpcustlogin;x];$[0=x[0];.ctrl.atp[`Login`Logintime]:(1b;.z.P);.ctrl.atp[`Login`LoginErr`LoginErrTime]:(0b;x[1];.z.P)];};
.upd.CustLogout:{[x]linfo[`atpcustlogout;x];.ctrl.atp[`Login`Logouttime]:(0b;.z.P);};

.upd.ordnew:.fe.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[count opt:x`ordopt;h:strdict opt;if[`COMB~h`special;:.upd.combnew[x]]];if[not null .db[.ctrl.O;k;`sym];:()];k1:`$string k0:newseq[];.db[.ctrl.O;k;`feoid`ntime`status`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.atp`Login)&(.conf.atp.ordmax>count .db[.ctrl.O]);rejectord[k;1i;"ATP_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;sd:x[`side];atpcall[$[sd=.enum`SELL_SHORT_EXEMPT;`insertRepo;`insertOrder];(.conf.atp`cust_id`fund_account`pass`order_way`authcode,$[ex=`XSHE;`sz_account;`sh_account]),(k0;esym;.enum $[ex=`XSHE;`kShenZhen;`kShangHai];.enum $[sd=.enum`BUY;`kBuy;sd=.enum`SELL;`kSell;sd=.enum`SELL_SHORT_EXEMPT;`kAntiRepo;`kAll];.enum`kFixedNew;floor 1e-6+1e4*x`price;floor 1e-6+1e2*x`qty;sv[`;x`ft`ts`oid])];}'; 

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null r`ordid;:()];k1:`$string k0:newseq[];.db[.ctrl.O;k;`cfeoid`cid`cstatus]:(k1;x`cid;.enum`PENDING_CANCEL);ex:fs2e r`sym;atpcall[`cancelOrder;(.conf.atp`cust_id`fund_account`order_way`authcode,$[ex=`XSHE;`sz_account;`sh_account]),("J"$string r`ordid;k0)];}'; 

.upd.ordqry:.fe.ordqry:{[x].upd.QueryOrder[x`oid];}';

.upd.BizRejection:{[x].temp.x7:x;.temp.L7,:enlist y:.enum.ordrejkey!x;z:exec first id from .db[.ctrl.O] where feoid=`$string y`client_seq_id;if[null z;:()];.db[.ctrl.O;z;`rtime`status`reason`msg]:(now[];.enum`REJECTED;`int$y`reject_reason_code;y`business_reject_text);execrpt[z];};

.upd.OrderStatusInternalAck:{[x].temp.x4:x;.temp.L8,:enlist y:.enum.orderkey!x;$[0<w:y`orig_cl_ord_no;[z:exec first id from .db[.ctrl.O] where ordid=`$string[w];r:.db[.ctrl.O;z];if[not null r`sym;.db[.ctrl.O;z;`cordid`rtime]:(`$string y`cl_ord_no;now[])]];[z:exec first id from .db[.ctrl.O] where feoid=`$string[y`client_seq_id];r:.db[.ctrl.O;z];if[not null r`sym;.db[.ctrl.O;z;`ordid`rtime`status`reason`msg]:(`$string y`cl_ord_no;now[];s:.enum.statusatp y`ord_status;`int$y`reject_reason_code;y`ord_rej_reason)]]];execrpt[z];};

.upd.OrderStatusAck:{[x].temp.x5:x;.temp.L8,:enlist y:.enum.orderkey!x;z:$[0<w:y`orig_cl_ord_no;exec first id from .db[.ctrl.O] where ordid=`$string[w];exec first id from .db[.ctrl.O] where ordid=`$string[y`cl_ord_no]];r:.db[.ctrl.O;z];if[null r`sym;:()];cq:1e-2*y`cum_qty;if[cq<r`cumqty;:()];.db[.ctrl.O;z;`status`reason`msg]:(s:.enum.statusatp y`ord_status;`int$y`reject_reason_code;y`ord_rej_reason);if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];if[not .db[.ctrl.O;z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.RepoAuctionTrade:.upd.CashAuctionTrade:{[x].temp.x6:x;.temp.L9,:enlist y:.enum.tradekey!x;z:exec first id from .db[.ctrl.O] where ordid=`$string y`cl_ord_no;r:.db[.ctrl.O;z];if[null r`sym;:()];lp:1e-4*y`last_px;lq:1e-2*y`last_qty;cq:lq+q0:0f^r`cumqty;ap:((lp*lq)+q0*p0:0f^r`avgpx)%cq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;s:.enum.statusatp y`ord_status;if[not r[`status]=.enum`CANCELED;.db[.ctrl.O;z;`status]:.enum $[cq=r`qty;`FILLED;s=.enum`CANCELED;`CANCELED;`PARTIALLY_FILLED]];execrpt[z];}; 

.upd.QueryOrder:{[k]if[null k;:.upd.QueryAllOrder[]];.temp.L4:();r:.db[.ctrl.O;k];if[(null r`sym)|null w:r`ordid;:()];ex:fs2e r`sym;r:atpcall[`queryOrder;(.conf.atp`cust_id`fund_account,$[ex=`XSHE;`sz_account;`sh_account]),(.enum`kCashBAT;.enum $[ex=`XSHE;`kShenZhen;`kShangHai];"J"$string[w];0)];};
.upd.QueryAllOrder:{[x].temp.L4:();r:atpcall[`queryOrder;(.conf.atp`cust_id`fund_account),(`;.enum`kCashBAT;.enum`kNULL;0;0)];}; 

.upd.QueryFund:{[x].temp.FundDst:x`ref;.temp.L2:();r:atpcall[`queryAsset;.conf.atp`cust_id`fund_account`branch_id`sz_account];};

.upd.QueryPos:{[x].temp.x3:x;.temp[`PosDst`PosAcc]:x`ref`msg;.temp.L3:();r:atpcall[`queryPos;(.conf.atp`cust_id`fund_account`branch_id`sz_account`sh_account),0];};

.upd.QueryMatch:{[x].temp.L5:();r:atpcall[`queryTrade;(.conf.atp`cust_id`fund_account`branch_id),(`;.enum`kNULL;0)];};

.upd.FundQueryResult:{[x].temp.x10:x;y:.enum.fundkey!x;.temp.L2,:enlist y;if[not null .temp[`FundDst];pubmx[.temp[`FundDst];`FundUpdate;.conf.me;"";-8!.temp.L2]];};

.upd.OrderQueryResult:{[x].temp.x8:x;if[0=count x[10];:()];.temp.L4,:y:flip .enum.ordqrykey!flip x[10];{[y]z:exec first id from .db[.ctrl.O] where feoid=`$string[y`client_seq_id];r:.db[.ctrl.O;z];if[null r`sym;:()];s:.enum.statusatp y`ord_status;cq:1e-2*y`cum_qty;ap:1e-4*y`exec_price;rq:r`cumqty;rs:r`status;if[null r`ordid;.db[.ctrl.O;z;`ordid]:`$string y`cl_ord_no];if[(cq<rq)|(cq=rq)&(s=rs);:()];if[cq>rq;.db[.ctrl.O;z;`cumqty`avgpx]:cq,ap];if[(s<>rs)&s in .enum`REJECTED`CANCELED`FILLED;.db[.ctrl.O;z;`status]:s];if[(0<cq)&.db[.ctrl.O;z;`status] in .enum`NULL`PENDING_NEW`NEW;.db[.ctrl.O;z;`status]:.enum`PARTIALLY_FILLED];execrpt[z];} each select from y where orig_cl_ord_no<=0;z:.enum.qryreskey!9#x;if[(n:1+z`last_index)<z`total_num;atpcall[`queryOrder;(.conf.atp`cust_id`fund_account),(`;.enum`kCashBAT;.enum`kNULL;0;n)]];};

.upd.TradeOrderQueryResult:{[x].temp.x9:x;if[0=count x[9];:()];.temp.L5,:y:flip .enum.trdqrykey!flip x[9];z:.enum.qryreskey!9#x;if[(n:1+z`last_index)<z`total_num;atpcall[`queryTrade;(.conf.atp`cust_id`fund_account`branch_id),(`;.enum`kNULL;n)]];};

.upd.ShareQueryResult:{[x].temp.x11:x;if[0=count x[9];:()];.temp.L3,:y:flip .enum.poskey!flip x[9];z:.enum.qryreskey!9#x;$[(n:1+z`last_index)<z`total_num;atpcall[`queryPos;(.conf.atp`cust_id`fund_account`branch_id`sz_account`sh_account),n];[.temp.P:1!select from (select sym:(`$security_id) {sv[`]x,$[y=102;`XSHE;`XSHG]}'market_id,lqty:1e-2*leaves_qty,sqty:0f,aqty:1e-2*available_qty from .temp.L3) where lqty>0;if[not null .temp[`PosDst];pubmx[.temp[`PosDst];`PosUpdate;.conf.me;.temp`PosAcc;-8!.temp.P]]]];};
