.module.twsbase:2017.07.08;

txload "feed/socket";

\d .enum
(MsgOut:`REQ_MKT_DATA`CANCEL_MKT_DATA`PLACE_ORDER`CANCEL_ORDER`REQ_OPEN_ORDERS`REQ_ACCT_DATA`REQ_EXECUTIONS`REQ_IDS`REQ_CONTRACT_DATA`REQ_MKT_DEPTH`CANCEL_MKT_DEPTH`REQ_NEWS_BULLETINS`CANCEL_NEWS_BULLETINS`SET_SERVER_LOGLEVEL`REQ_AUTO_OPEN_ODERS`REQ_ALL_OPEN_ORDERS`REQ_MANAGED_ACCTS`REQ_FA`REPLACE_FA`REQ_HISTORICAL_DATA`EXERCISE_OPTIONS`REQ_SCANNER_SUBSCRIPTION`CANCEL_SCANNER_SUBSCRIPTION`REQ_SCANNER_PARAMETERS`CANCEL_HISTORICAL_DATA`REQ_CURRENT_TIME`REQ_REAL_TIME_BARS`CANCEL_REAL_TIME_BARS`REQ_FUNDAMENTAL_DATA`CANCEL_FUNDAMENTAL_DATA`REQ_CALC_IMPLIED_VOLAT`REQ_CALC_OPTION_PRICE`CANCEL_CALC_IMPLIED_VOLAT`CANCEL_CALC_OPTION_PRICE`REQ_GLOBAL_CANCEL`REQ_MARKET_DATA_TYPE`REQ_POSITIONS`REQ_ACCOUNT_SUMMARY`CANCEL_ACCOUNT_SUMMARY`CANCEL_POSITIONS`VERIFY_REQUEST`VERIFY_MESSAGE`QUERY_DISPLAY_GROUPS`SUBSCRIBE_TO_GROUP_EVENTS`UPDATE_DISPLAY_GROUP`UNSUBSCRIBE_FROM_GROUP_EVENTS`START_API) set' (1+til 25),(49+til 11),61+til 11; /tws_outgoing_ids


(MsgIn:`TWS_LOGON`TICK_PRICE`TICK_SIZE`ORDER_STATUS`ERR_MSG`OPEN_ORDER`ACCT_VALUE`PORTFOLIO_VALUE`ACCT_UPDATE_TIME`NEXT_VALID_ID`CONTRACT_DATA`EXECUTION_DATA`MARKET_DEPTH`MARKET_DEPTH_L2`NEWS_BULLETINS`MANAGED_ACCTS`RECEIVE_FA`HISTORICAL_DATA`BOND_CONTRACT_DATA`SCANNER_PARAMETERS`SCANNER_DATA`TICK_OPTION_COMPUTATION`TICK_GENERIC`TICK_STRING`TICK_EFP`CURRENT_TIME`REAL_TIME_BARS`FUNDAMENTAL_DATA`CONTRACT_DATA_END`OPEN_ORDER_END`ACCT_DOWNLOAD_END`EXECUTION_DATA_END`DELTA_NEUTRAL_VALIDATION`TICK_SNAPSHOT_END`MARKET_DATA_TYPE`COMMISSION_REPORT`POSITION_DATA`POSITION_END`ACCOUNT_SUMMARY`ACCOUNT_SUMMARY_END`VERIFY_MESSAGE_API`VERIFY_COMPLETED`DISPLAY_GROUP_LIST`DISPLAY_GROUP_UPDATED`VERIFY_AND_AUTH_MESSAGE_API`VERIFY_AND_AUTH_COMPLETED) set' 0,(1+til 21),(45+til 3),(49+til 11),61+til 10; /tws_incoming_ids

(TickType:`BID_SIZE`BID`ASK`ASK_SIZE`LAST`LAST_SIZE`HIGH`LOW`VOLUME`CLOSE`BID_OPTION_COMPUTATION`ASK_OPTION_COMPUTATION`LAST_OPTION_COMPUTATION`MODEL_OPTION`OPEN`LOW_13_WEEK`HIGH_13_WEEK`LOW_26_WEEK`HIGH_26_WEEK`LOW_52_WEEK`HIGH_52_WEEK`AVG_VOLUME`OPEN_INTEREST`OPTION_HISTORICAL_VOL`OPTION_IMPLIED_VOL`OPTION_BID_EXCH`OPTION_ASK_EXCH`OPTION_CALL_OPEN_INTEREST`OPTION_PUT_OPEN_INTEREST`OPTION_CALL_VOLUME`OPTION_PUT_VOLUME`INDEX_FUTURE_PREMIUM`BID_EXCH`ASK_EXCH`AUCTION_VOLUME`AUCTION_PRICE`AUCTION_IMBALANCE`MARK_PRICE`BID_EFP_COMPUTATION`ASK_EFP_COMPUTATION`LAST_EFP_COMPUTATION`OPEN_EFP_COMPUTATION`HIGH_EFP_COMPUTATION`LOW_EFP_COMPUTATION`CLOSE_EFP_COMPUTATION`LAST_TIMESTAMP`SHORTABLE`FUNDAMENTAL_RATIOS`RT_VOLUME`HALTED`BID_YIELD`ASK_YIELD`LAST_YIELD`CUST_OPTION_COMPUTATION`TRADE_COUNT`TRADE_RATE`VOLUME_RATE`LAST_RTH_TRADE`NOT_SET) set' til 59; /TickType Enum

`NEWS_MSG`EXCHANGE_AVAIL_MSG`EXCHANGE_UNAVAIL_MSG set' 1 2 3; /TWS New Bulletins constants

MsgInLen:(value each MsgIn)!0 5 3 10 3 62 4 18 1 1 30 28 6 7 4 1 2 4 30 1 2 10 3 3 9 1 9 2 1 0 1 1 4 1 2 6 14 0 5 1 1 2 2 2 0 0; /接收消息至少字段数(不含版本号)
MsgInMap:(value each MsgIn)!MsgIn;TickTypeMap:(value each TickType)!TickType;

//secType:`STK`OPT`FUT`IND`FOP`CASH`BAG`WAR /STK - stocks, FUT - futures, FOP - options on futures, OPT - options, IND - indexes, CASH -cash (ideal FX) WAR- warrant
//secIdType:`SIN`CUSIP`SEDOL`RIC
//right:`P`PUT`C`CALL
//ScanCode:`TOP_PERC_GAIN`TOP_PERC_LOSE`MOST_ACTIVE`NOT_YET_TRADED_TODAY`MOST_ACTIVE_USD`MOST_ACTIVE_AVG_USD`HALTED`LIMIT_UP_DOWN`HOT_BY_PRICE`HOT_BY_VOLUME`HIGH_DIVIDEND_YIELD_IB`TOP_TRADE_COUNT`TOP_TRADE_RATE`TOP_PRICE_RANGE`HOT_BY_PRICE_RANGE`TOP_VOLUME_RATE`TOP_OPEN_PERC_GAIN`TOP_OPEN_PERC_LOSE`HIGH_OPEN_GAP`LOW_OPEN_GAP`TOP_AFTER_HOURS_PERC_GAIN`TOP_AFTER_HOURS_PERC_LOSE`HIGH_OPT_IMP_VOLAT`LOW_OPT_IMP_VOLAT`TOP_OPT_IMP_VOLAT_GAIN`TOP_OPT_IMP_VOLAT_LOSE`HIGH_OPT_IMP_VOLAT_OVER_HIST`LOW_OPT_IMP_VOLAT_OVER_HIST`OPT_VOLUME_MOST_ACTIVE`OPT_OPEN_INTEREST_MOST_ACTIVE`HIGH_OPT_VOLUME_PUT_CALL_RATIO`LOW_OPT_VOLUME_PUT_CALL_RATIO`HIGH_OPT_OPEN_INTEREST_PUT_CALL_RATI`LOW_OPT_OPEN_INTEREST_PUT_CALL_RATIO`HOT_BY_OPT_VOLUME`TOP_STOCK_BUY_IMBALANCE_ADV_RATIO`TOP_STOCK_SELL_IMBALANCE_ADV_RATIO`TOP_STOCK_BUY_REG_IMBALANCE_ADV_RATIO`TOP_STOCK_SELL_REG_IMBALANCE_ADV_RATIO`HIGH_SYNTH_BID_REV_NAT_YIELD`LOW_SYNTH_ASK_REV_NAT_YIELD`HIGH_VS_13W_HL`LOW_VS_13W_HL`HIGH_VS_26W_HL`LOW_VS_26W_HL`HIGH_VS_52W_HL`LOW_VS_52W_HL`FIRST_TRADE_DATE_ASC`FIRST_TRADE_DATE_DESC`HIGH_GROWTH_RATE`LOW_GROWTH_RATE`HIGH_PE_RATIO`LOW_PE_RATIO`HIGH_QUICK_RATIO`LOW_QUICK_RATIO`HIGH_RETURN_ON_EQUITY`LOW_RETURN_ON_EQUITY`HIGH_PRICE_2_BOOK_RATIO`LOW_PRICE_2_BOOK_RATIO
//reportType:`ReportSnapshot`ReportsFinSummary`ReportRatios`ReportsFinStatements`RESC`CalendarReport

NUL:"\000";
\d .

\d .temp
BUF:"";
CMD:"";
C:();
L:();
\d .

.ctrl.tws:.enum`nulldict;

.exit.twsbase:{[x]linfo[`TWSExit;(.conf.me;now[])];};
.timer.twsbase:{[x]tws_logon[];};
.tcppc.twsbase:{[h]x:.conf.tws.id;if[not x in key .ctrl.tcpconn;:()];r:.ctrl.tcpconn[x];if[h=r`h;.ctrl.tws[`status`peertime`logontime`subtime]:(`;0Np;0Np;0Np)];tws_disc[];};

tws_disc:{[]};

tws_logon:{[]x:.conf.tws.id;if[not x in key .ctrl.tcpconn;:()];r:.ctrl.tcpconn[x];if[(0<h:r`h)&(1b~r`c)&(null .ctrl.tws[`status])&.z.P>00:00:01+r[`connected];.ctrl.tws[`status`versionC]:(`LogonHalf;cv:.conf.tws.cltver);smtws[cv;x;()]];};

smtws:{[y;x;z]smtcp[x] m:(.enum.NUL sv {$[10h=type x;x;string x]} each y,raze over z),.enum.NUL;if[.conf.tws.debug;.temp.C,:enlist (.z.P;m);.temp.CMD,:m];}; /[msgid(int);twsid;fields]

twsmsg:{[x]if[1>=n:count y:where x=.enum.NUL;:0];mid:$[`LogonHalf~.ctrl.tws[`status];.enum`TWS_LOGON;"I"$y[0]#x];if[not mid in key .enum.MsgInLen;:-1];if[n<n1:2+.enum.MsgInLen[mid];:0];if[0>n2:.tws[.enum.MsgInMap mid][z:.enum.NUL vs y[n-1]#x];:0];if[.conf.tws.debug;.temp.L,:enlist (.z.P;.enum.MsgInMap mid;(n1+n2)#z)];1+y[n1+n2-1]}; /[msgbuf]尝试读取一条完整tws消息,如成功返回该消息字节数,如果消息不完整返回0,出现解码错误则返回-1

/logon_callback
tws_afterlogon:{req_current_time[1];};
/quote_callback
tws_tick_price:tws_tick_size:tws_market_depth:tws_tick_generic:tws_tick_string:tws_tick_option_computation:tws_real_time_bars:tws_historical_data:{};
/order_callback
tws_err_msg:tws_order_status:tws_open_order:tws_open_order_end:tws_execution_data:tws_execution_data_end:tws_commission_report:tws_acct_value:tws_acct_update_time:tws_acct_download_end:tws_contract_data:tws_contract_data_end:tws_position_data:tws_position_end:tws_portfolio_value:tws_scanner_parameters:tws_scanner_data:tws_fundamental_data:{};

/消息入参为(msgid;ver;field0,field1,...)

.tws.TWS_LOGON:{[x].ctrl.tws[`status`logontime`versionS`idiom`acct`port]:(`Logon;.z.P;`$x[0];`$x[1];.enum.nulldict;.enum.nulldict);start_api[(1;.conf.tws.cltid)];tws_afterlogon[];$[`9=`$x[1];2;0]}; /登陆消息(为收到的第一条虚消息,无消息号)[ver=76](conntime),向TWS发送API实例号

.tws.TICK_PRICE:{[x]@[tws_tick_price;y:`tickerid`ticktype`price`size`canautoexecute!5#2_x;()];0}; /{1}行情委托价量更新[Ver=6](tickerId;tickTypeInt;price;size;canAutoExecute)

.tws.TICK_SIZE:{[x]@[tws_tick_size;y:`tickerid`ticktype`size!3#2_x;()];0}; /{2}行情委托数量更新[Ver=6](tickerId;tickTypeInt;size)

.tws.ORDER_STATUS:{[x]@[tws_order_status;.temp.x:`oid`status`filled`remaining`avgfillprice`permid`parentid`lastfillprice`clientid`whyheld!10#2_x;()];0}; /{3}委托状态更新[Ver=6](orderId;status;filled;remaining;avgFillPrice;permId;parentId;lastFillPrice;clientId;whyHeld)

.tws.ERR_MSG:{[x]id:`$x[2];ec:`$x[3];txt:`$x[4];lwarn[`TWSError;(id;ec;txt)];if[0<"I"$string id;tws_err_msg[`id`reason`text!3#2_x]];0}; /{4}错误或通知消息(为收到的第三条消息)[Ver=2](委托ID/请求ID;错误号;错误信息)

.tws.OPEN_ORDER:{[x]n:count x;dnt:not null `$x[62];if[n<1+k:62+1+n1:$[dnt;8;0]+8;:-1];clc:0^"I"$x[k];if[n<1+k1:1+k+8*clc;:-1];oclc:0^"I"$x[k1];if[n<1+k2:1+k1+oclc;:-1];srp:0^"I"$x[k2];if[n<1+k3:k2+(2*srp)+3;:-1];spi:0^"I"$x[k3];if[n<1+k4:1+k3+7*spi;:-1];ht:not null `$x[k4];if[n<1+k5:k4+ht+5;:-1];ucp:0^"I"$x[k5];if[n<1+k6:1+k5+3*ucp;:-1];as:not null `$x[k6];$[as;[if[n<1+k7:1+k6;:-1];apc:0^"I"$x[k7];if[n<1+k8:k7+2*apc;:-1]];k8:k6];if[n<1+k9:k8+10;:-1];@[tws_open_order;.temp.Y::`orderid`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`currency`localsymbol`tradingclass`action`totalquantity`ordertype`lmtprice`auxprice`tif`ocagroup`account`openclose`orderoriginin`orderref`clientid`permid`outsiderth`hidden`discretionaryamt`goodaftertime`sharesallocation`fagroup`famethod`fapercentage`faprofile`goodtilldate`rule80a`percentoffset`settlingfirm`shortsaleslot`designatedlocation`exemptcode`auctionstrategy`startingprice`stockrefprice`delta`stockrangelower`stockrangeupper`displaysize`blockorder`sweeptofill`allornone`minqty`ocatype`etradeonly`firmquoteonly`nbbopricecap`parentid`triggermethod`volatility`volatilitytype`deltaneutralordertype`deltaneutralauxprice`deltaneutralconid`deltaneutralsettlingfirm`deltaneutralclearingaccount`deltaneutralclearingintent`deltaneutralopenclose`deltaneutralshortsale`deltaneutralshortsaleslot`deltaneutraldesignatedlocation`continuousupdate`referencepricetype`trailstopprice`trailingpercent`basispoints`basispointstype`combolegsdescrip`combolegscount`ordercombolegscount`smartcomboroutingparamscount`scaleinitlevelsize`scalesubslevelsize`scalepriceincrement`hedgetype`optoutsmartrouting`clearingaccount`clearingintent`notheld`undercomppresent`algostrategy`whatif`status`initmargin`maintmargin`equitywithloan`commission`mincommission`maxcommission`commissioncurrency`warningtext!100#2_x;()];k9-63}; /{5}委托确认消息[Ver=32](orderId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;currency;localSymbol;tradingClass;action;totalQuantity;orderType;lmtPrice;auxPrice;tif;ocaGroup;account;openClose;orderOriginIn;orderRef;clientId;permId;outsideRth;hidden;discretionaryAmt;goodAfterTime;sharesAllocation;faGroup;faMethod;faPercentage;faProfile;goodTillDate;rule80A;percentOffset;settlingFirm;shortSaleSlot;designatedLocation;exemptCode;auctionStrategy;startingPrice;stockRefPrice;delta;stockRangeLower;stockRangeUpper;displaySize;blockOrder;sweepToFill;allOrNone;minQty;ocaType;eTradeOnly;firmQuoteOnly;nbboPriceCap;parentId;triggerMethod;volatility;volatilityType;deltaNeutralOrderType;deltaNeutralAuxPrice{;(deltaNeutralConId;deltaNeutralSettlingFirm;deltaNeutralClearingAccount;deltaNeutralClearingIntent;deltaNeutralOpenClose;deltaNeutralShortSale;deltaNeutralShortSaleSlot;deltaNeutralDesignatedLocation)};continuousUpdate;referencePriceType;trailStopPrice;trailingPercent;basisPoints;basisPointsType;comboLegsDescrip;comboLegsCount{;comboLegsCount*(conId;ratio;action;exchange;openClose;shortSaleSlot;designatedLocation;exemptCode)};orderComboLegsCount;{orderComboLegsCount*(price)};smartComboRoutingParamsCount{;smartComboRoutingParamsCount*(tag;value)};scaleInitLevelSize;scaleSubsLevelSize;scalePriceIncrement{;scalePriceAdjustValue;scalePriceAdjustInterval;scaleProfitOffset;scaleAutoReset;scaleInitPosition;scaleInitFillQty;scaleRandomPercent};hedgeType{;hedgeParam};optOutSmartRouting;clearingAccount;clearingIntent;notHeld;underCompPresent{;conId;delta;price};algoStrategy{;algoParamsCount;algoParamsCount*(tag;value)};whatIf;status;initMargin;maintMargin;equityWithLoan;commission;minCommission;maxCommission;commissionCurrency;warningText)

.tws.ACCT_VALUE:{[x]@[tws_acct_value;`key`val`cur`acc!4#2_x;()];0}; /{6}[Ver=2](key;val;cur;accountName)

.tws.PORTFOLIO_VALUE:{[x]@[tws_portfolio_value;`conid`symbol`sectype`expiry`strike`right`multiplier`primaryexchange`currency`localsymbol`tradingclass`position`marketprice`marketvalue`averagecost`unrealizedpnl`realizedpnl`accountname!18#2_x;()];0}; /{7}[Ver=8](conId;symbol;secType;expiry;strike;right;multiplier;primaryExchange;currency;localSymbol;tradingClass;position;marketPrice;marketValue;averageCost;unrealizedPNL;realizedPNL;accountName)

.tws.ACCT_UPDATE_TIME:{[x].ctrl.tws[`peertime]:.z.D+"T"$x[2];@[tws_acct_update_time;x[2];()];0}; /{8}[Ver=1](accountTime)

.tws.NEXT_VALID_ID:{[x].ctrl.tws[`peerseq]:"J"$x[2];0}; /{9}下一笔委托ID消息(为收到的第三条消息)[Ver=1](下一笔委托号)

.tws.CONTRACT_DATA:{[x]n:count x;if[(n<32+2*ns)&(0<ns:"I"$x[31]);:-1];@[tws_contract_data;`reqid`symbol`sectype`expiry`strike`right`exchange`currency`localsymbol`marketname`tradingclass`conid`mintick`multiplier`ordertypes`validexchanges`pricemagnifier`underconid`longname`primaryexchange`contractmonth`industry`category`subcategory`timezoneid`tradinghours`liquidhours`evrule`evmultiplier!29#2_x;()];2*ns}; /{10}[Ver=8](reqId;symbol;secType;expiry;strike;right;exchange;currency;localSymbol;marketName;tradingClass;conId;minTick;multiplier;orderTypes;validExchanges;priceMagnifier;underConId;longName;primaryExchange;contractMonth;industry;category;subcategory;timeZoneId;tradingHours;liquidHours;evRule;evMultiplier;secIdListCount{;secIdListCount*(tag;value)})

.tws.EXECUTION_DATA:{[x]@[tws_execution_data;`reqid`oid`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`currency`localsymbol`tradingclass`execid`time`acctnumber`exchange`side`shares`price`permid`clientid`liquidation`cumqty`avgprice`orderref`evrule`evmultiplier!28#2_x;()];0}; /{11}[Ver=10](reqId;orderId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;currency;localSymbol;tradingClass;execId;time;acctNumber;exchange;side;shares;price;permId;clientId;liquidation;cumQty;avgPrice;orderRef;evRule;evMultiplier)

.tws.MARKET_DEPTH:{[x]@[tws_market_depth;`reqid`position`operation`side`price`size!6#2_x;()];0}; /{12}[Ver=?](reqid;position;operation;side;price;size)

.tws.MARKET_DEPTH_L2:{[x];0}; /{13}[Ver=?](id;position;marketMaker;operation;side;price;size)

.tws.NEWS_BULLETINS:{[x];0}; /{14}[Ver=?](msgId;msgType;newsMessage;originatingExch)

.tws.MANAGED_ACCTS:{[x].ctrl.tws[`custom]:`$x[2];0}; /{15}登陆帐号消息(为收到的第二条消息)[Ver=1](accountsList)

.tws.RECEIVE_FA:{[x];0}; /{16}[Ver=?](faDataTypeInt;cxml)

.tws.HISTORICAL_DATA:{[x]n:count x;if[(n<6+9*ns)&(0<ns:"J"$x[5]);:-1];@[tws_historical_data;`reqid`startdatestr`enddatestr`itemcount`bars!(4#2_x),enlist (ns,9)#6_x;()];9*ns}; /{17}[Ver=3](reqId;startDateStr;endDateStr;itemCount{;itemCount*(date;open;high;low;close;volume;average;hasGaps;barCount)})

.tws.BOND_CONTRACT_DATA:{[x];n:count x;if[(n<32+2*ns)&(0<ns:"I"$x[31]);:-1];2*ns}; /{18}[Ver=?](reqId;symbol;secType;cusip;coupon;maturity;issueDate;ratings;bondType;couponType;convertible;callable;putable;descAppend;exchange;currency;marketName;tradingClass;conId;minTick;orderTypes;validExchanges;nextOptionDate;nextOptionType;nextOptionPartial;notes;longName;evRule;evMultiplier;secIdListCount{;secIdListCount*(tag;value)})

.tws.SCANNER_PARAMETERS:{[x]@[tws_scanner_parameters;(enlist `paramxml)!2_x;()];0}; /{19}[Ver=1](xml)

.tws.SCANNER_DATA:{[x]n:count x;if[(n<4+16*ns)&(0<ns:"J"$x[3]);:-1];@[tws_scanner_data;`tickerid`data!(x[2];flip `rank`conid`symbol`sectype`expirey`strike`right`exchange`currency`localsym`marketname`tradingclass`distance`benchmark`projection`legstr!flip (ns,16)#4_x);()];16*ns}; /{20}[Ver=3](tickerId;numberOfElements{;numberOfElements*(rank;conId;symbol;secType;expiry;strike;right;exchange;currency;localSymbol;marketName;tradingClass;distance;benchmark;projection;legsStr)})

.tws.TICK_OPTION_COMPUTATION:{[x]@[tws_tick_option_computation;`tickerid`ticktype`impvol`delta`optpx`div`gamma`vega`theta`undpx!10#2_x;()];0}; /{21}期权价格计算值[Ver=6](tickerId;tickTypeInt;impliedVol;delta;optPrice;pvDividend;gamma;vega;theta;undPrice)

.tws.TICK_GENERIC:{[x]@[tws_tick_generic;`tickerid`ticktype`value!3#2_x;()];0}; /{45}通用行情更新[Ver=6](tickerId;tickTypeInt;value)

.tws.TICK_STRING:{[x]@[tws_tick_string;`tickerid`ticktype`value!3#2_x;()];0}; /{46}字符串行情更新[Ver=?](tickerId;tickTypeInt;value)

.tws.TICK_EFP:{[x];0}; /{47}EFP行情更新[Ver=?](tickerId;tickTypeInt;basisPoints;formattedBasisPoints;impliedFuturesPrice;holdDays;futureExpiry;dividendImpact;dividendsToExpiry)

.tws.CURRENT_TIME:{[x].ctrl.tws[`peertime]:`timestamp$unixdate["I"$x[2]];0}; /{49}[Ver=1](time)

.tws.REAL_TIME_BARS:{[x]@[tws_real_time_bars;`reqid`time`open`high`low`close`volume`average`count!9#2_x;()];0}; /{50}[Ver=3](reqId;time;open;high;low;close;volume;average;count)

.tws.FUNDAMENTAL_DATA:{[x]@[tws_fundamental_data;`reqid`xml!2#2_x;()];0}; /{51}[Ver=1](reqId;data)

.tws.CONTRACT_DATA_END:{[x]@[tws_contract_data_end;x[2];()];0}; /{52}[Ver=1](reqId)

.tws.OPEN_ORDER_END:{[x]@[tws_open_order_end;();()];0}; /{53}[Ver=1]()

.tws.ACCT_DOWNLOAD_END:{[x]@[tws_acct_download_end;x[2];()];0}; /{54}[Ver=1](account)

.tws.EXECUTION_DATA_END:{[x]@[tws_execution_data_end;x[2];()];0}; /{55}[Ver=1](reqId)

.tws.DELTA_NEUTRAL_VALIDATION:{[x];0}; /{56}[Ver=?](reqId;conId;delta;price)

.tws.TICK_SNAPSHOT_END:{[x];0}; /{57}[Ver=?](reqId)

.tws.MARKET_DATA_TYPE:{[x];0}; /{58}[Ver=?](reqId;marketDataType)

.tws.COMMISSION_REPORT:{[x]@[tws_commission_report;`execId`commission`currency`realizedPNL`yield`yieldRedemptionDate!6#2_x;()];0}; /{59}[Ver=1](execId;commission;currency;realizedPNL;yield;yieldRedemptionDate)

.tws.POSITION_DATA:{[x]@[tws_position_data;`account`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`currency`localsymbol`tradingclass`position`avgcost!14#2_x;()];0}; /{61}[Ver=3](account;conId;symbol;secType;expiry;strike;right;multiplier;exchange;currency;localSymbol;tradingClass;position;avgCost)

.tws.POSITION_END:{[x]@[tws_position_end;();()];0}; /{62}[Ver=1]()

.tws.ACCOUNT_SUMMARY:{[x];0}; /{63}[Ver=?](reqId;account;tag;value;curency)

.tws.ACCOUNT_SUMMARY_END:{[x];0}; /{64}[Ver=?](reqId)

.tws.VERIFY_MESSAGE_API:{[x];0}; /{65}[Ver=?](apiData)

.tws.VERIFY_COMPLETED:{[x];0}; /{66}[Ver=?](isSuccessful;errorText)

.tws.DISPLAY_GROUP_LIST:{[x];0}; /{67}[Ver=?](reqId;groups)

.tws.DISPLAY_GROUP_UPDATED:{[x];0}; /{68}[Ver=?](reqId;contractInfo)

.tws.VERIFY_AND_AUTH_MESSAGE_API:{[x];0}; /{69}[Ver=?]()

.tws.VERIFY_AND_AUTH_COMPLETED:{[x];0}; /{70}[Ver=?]()

onsockmsg:{[x;y]w:x`w;if[.conf.tws.debug;.temp.BUF,:y];.temp.B:b:$[null w;"";.ctrl.tcpconn[w;`rbuf]],y;while[0<n:twsmsg[b];b:n _b];if[not null w;.ctrl.tcpconn[w;`rbuf]:$[0=n;b;""]];}; /b(待处理字节流)

{set[lower x;smtws[.enum[x];.conf.tws.id]];} each .enum.MsgOut; 

/quote_req
tws_req_mkt_data:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`primaryexchange`currency`localsymbol`tradingclass`undercomp`genericticks`snapshot`mktdataoptionsstr!`0````0````````0``0`;z,:((key z)inter key y)#y;req_mkt_data[11,x,value z];}; /[tickerid;contracthash]
tws_cancel_mkt_data:{[x]cancel_mkt_data[2,x];}; /[tickerid]

tws_req_mkt_depth:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`currency`localsymbol`tradingclass`numrows`mktdepthoptionsstr!0,````0```````100`;z,:((key z)inter key y)#y;req_mkt_depth[5,x,value z];}; /[tickerid;contracthash]
tws_cancel_mkt_depth:{[x]cancel_mkt_depth[1,x];}; /[tickerid]

tws_req_real_time_bars:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`primaryexchange`currency`localsymbol`tradingclass`barsize`whattoshow`userth`realtimebarsoptionsstr!`0````0`````USD```5`MIDPOINT`0`;z,:((key z)inter key y)#y;req_real_time_bars[3,x,value z];}; /[tickerid;contracthash]
tws_cancel_real_time_bars:{[x]cancel_real_time_bars[1,x];}; /[tickerId]

tws_req_historical_data:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`primaryexchange`currency`localsymbol`tradingclass`includeexpired`enddatetime`barsizesetting`durationstr`userth`whattoshow`formatdate`chartoptionsstr!`0````0`````USD```0````0`MIDPOINT`1`;z,:((key z)inter key y)#y;req_historical_data[6,x,value z];}; /[tickerid;contracthash]
tws_cancel_historical_data:{[x]cancel_historical_data[1,x];}; /[tickerId]

/order_req
tws_place_order:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`primaryexchange`currency`localsymbol`tradingclass`secidtype`secid`action`totalquantity`ordertype`lmtprice`auxprice`tif`ocagroup`account`openclose`orderoriginin`orderref`transmit`parentid`blockorder`sweeptofill`displaysize`triggermethod`outsiderth`hidden`sharesallocation`discretionaryamt`goodaftertime`goodtilldate`fagroup`famethod`fapercentage`faprofile`shortsaleslot`designatedlocation`exemptcode`ocatype`rule80a`settlingfirm`allornone`minqty`percentoffset`etradeonly`firmquoteonly`nbbopricecap`auctionstrategy`startingprice`stockrefprice`delta`stockrangelower`stockrangeupper`overridepercentageconstraints`volatility`volatilitytype`deltaneutralordertype`deltaneutralauxprice`continuousupdate`referencepricetype`trailstopprice`trailingpercent`scaleinitlevelsize`scalesubslevelsize`scalepriceincrement`scaletable`activestarttime`activestoptime`hedgetype`optoutsmartrouting`clearingaccount`clearingintent`notheld`undercomppresent`algostrategy`algoid`whatif`miscoptionsstr!0,````0``````````````0`````0``1`0`0`0`0`0`0`0``0```````0`,(`$"-1"),`0```0```1`1``0``````0`````0```````````0```0`0```0`;z,:((key z)inter key y)#y;place_order[42,x,value z];}; /[orderid;orderhash] tws_place_order[newseq[];`symbol`secType`expiry`exchange`currency`action`totalQuantity`orderType`lmtPrice`openClose!`XINA50`FUT`201510];
tws_cancel_order:{cancel_order[1,x];}; /[orderid]

tws_req_contract_data:{[x;y]z:`conid`symbol`sectype`expiry`strike`right`multiplier`exchange`currency`localsymbol`tradingclass`includeexpired`secidtype`secid!`0````0````USD```0``;z,:((key z)inter key y)#y;req_contract_data[7,x,value z];}; /[tickerid;contracthash]

tws_req_acct_data:{[x]req_acct_data[2,x,`];} /[ifsubupdates]
tws_req_executions:{[x]req_executions[3,x,```````];}; /[reqid]
tws_req_positions:{[x]req_positions[1,x,``];}; /[reqid]
tws_req_scanner_parameters:{[x]req_scanner_parameters[1];};

tws_req_scanner_subscription:{[x;y]z:`numberOfRows`instrument`locationCode`scanCode`abovePrice`belowPrice`aboveVolume`marketCapAbove`marketCapBelow`moodyRatingAbove`moodyRatingBelow`spRatingAbove`spRatingBelow`maturityDateAbove`maturityDateBelow`couponRateAbove`couponRateBelow`excludeConvertible`averageOptionVolumeAbove`scannerSettingPairs`stockTypeFilter`scannerSubscriptionOptionsStr!`50`STOCK.HK`STK.HK.SEHK`TOP_PERC_GAIN``````````````````;z,:((key z)inter key y)#y;req_scanner_subscription[4,x,value z];}; /[tickerid;reqhash]

tws_cancel_scanner_subscription:{[x]cancel_scanner_subscription[1,x];};

tws_req_fundamental_data:{[x;y]z:`conid`symbol`sectype`exchange`primaryexchange`currency`localsymbol`reporttype!````````ReportsFinSummary;z,:((key z)inter key y)#y;req_fundamental_data[2,x,value z];}; /[tickerid;reqhash]




\
req_mkt_data[(11;newseq[];(`0`XINA50`FUT`201703`0```SGX``USD```0``0`))]; /{1}[ver=11](reqid;contract:(conid;symbol;sectype;expiry;strike;right;multiplier;exchange;primary_exch;currency;local_symbol;tradingclass{;num_combolegs;num_combolegs*(co_conid;co_ratio;co_action;co_exchange)};underComp{;(conId;delta;price)};genericTicks;snapshot;mktDataOptionsStr))-->req_mkt_data[(11;newseq[];(`0`IBM`STK``0```SMART``USD```0,(`$"100,101,104,105,106,107,165,221,225,233,236,258,293,294,295,318"),`0`))];
cancel_mkt_data[(2;`10)]; /{2}[ver=2](reqid)
place_order[(42;newseq[];`0`XINA50`FUT`201510`0```SGX``USD````;`BUY`1`LMT`9400`0````O`0``1`0`0`0`0`0`0`0``0```````0`,(`$"-1"),`0```0```1`1``0``````0`````0```````````0```0`0```0`)]; /{3}[ver=42](orderid;con:((conid;symbol;sectype;expiry;strike;right;multiplier;exchange;primaryExchange;currency;local_symbol;tradingclass;secIdType;secId);ord:(action;totalQuantity;orderType;lmtPrice;auxPrice;tif;ocaGroup;account;openClose;origin;orderRef;transmit;parentId;blockOrder;sweepToFill;displaySize;triggerMethod;outsideRth;hidden{;comboLegsCount;comboLegsCount*(conId;ratio;action;exchange;openClose;shortSaleSlot;designatedLocation;exemptCode);orderComboLegsCount;orderComboLegsCount*(price);smartComboRoutingParamsCount;smartComboRoutingParamsCount*(tag;value)};sharesAllocation;discretionaryAmt;goodAfterTime;goodTillDate;faGroup;faMethod;faPercentage;faProfile;shortSaleSlot;designatedLocation;exemptCode;ocaType;rule80A;settlingFirm;allOrNone;minQty;percentOffset;eTradeOnly;firmQuoteOnly;nbboPriceCap;auctionStrategy;startingPrice;stockRefPrice;delta;stockRangeLower;stockRangeUpper;overridePercentageConstraints;volatility;volatilityType;deltaNeutralOrderType;deltaNeutralAuxPrice{;deltaNeutralConId;deltaNeutralSettlingFirm;deltaNeutralClearingAccount;deltaNeutralClearingIntent;deltaNeutralOpenClose;deltaNeutralShortSale;deltaNeutralShortSaleSlot;deltaNeutralDesignatedLocation};continuousUpdate;referencePriceType;trailStopPrice;trailingPercent;scaleInitLevelSize;scaleSubsLevelSize;scalePriceIncrement{;scalePriceAdjustValue;scalePriceAdjustInterval;scaleProfitOffset;scaleAutoReset;scaleInitPosition;scaleInitFillQty;scaleRandomPercent};scaleTable;activeStartTime;activeStopTime;hedgeType{;hedgeParam};optOutSmartRouting;clearingAccount;clearingIntent;notHeld;underComp{;conId;delta;price};algoStrategy{algoParamsCount;algoParamsCount*(tag;value)};algoId;whatIf;miscOptionsStr))
cancel_order[(1;100001)]; /{4}[ver=1](orderid)
req_open_orders[1]; /{5}[ver=1]
AV:();req_acct_data[(2;1;`)]; /{6}[ver=2](subscribe;acctCode)
req_executions[(3;newseq[];```````)]; /{7}[ver=3](reqId;clientId;acctCode;time;symbol;secType;exchange;side)
req_ids[(1;2)]; /{8}[ver=1](numIds)
req_contract_data[(7;newseq[];`0`XINA50`FUT`201510`0```SGX`USD```0``)]; /{9}[ver=7](reqid[];(conid;symbol;sectype;expiry;strike;right;multiplier;exchange;currency;local_symbol;tradingclass;includeExpired;secIdType;secId)) -->req_contract_data[(7;newseq[];`0`IBM`STK``0```SMART``USD````)];
req_mkt_depth[(5;newseq[];`0`XINA50`FUT`201510`0```SGX`USD```100`)]; /{10}[ver=5](tickerId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;currency;localSymbol;tradingClass;numRows;mktDepthOptionsStr)-->req_mkt_depth[(5;newseq[];``EUR`CASH``0```IDEALPRO`USD```20`)]; 
cancel_mkt_depth[(1;`10006)]; /{11}[ver=1](tickerId)
req_news_bulletins[(1;1)]; /{12}[ver=1](ifallMsgs)
cancel_news_bulletins[1]; /{13}[ver=1]()
set_server_loglevel[(1;1)]; /{14}[ver=1](logLevel)
req_auto_open_orders[(1;1)]; /{15}[ver=1](bAutoBind)
req_all_open_orders[1]; /{16}[ver=1]()
req_managed_accts[1]; /{17}[ver=1]()
req_fa[(1;1)]; /{18}[ver=1](pFaDataType)
replace_fa[]; /{19}[ver=1](pFaDataType;cxml)
req_historical_data[(6;newseq[];`0`XINA50`FUT`201510`0```SGX``USD```0,(`$("20150924 15:00:00";"1 day";"1 M")),`1`TRADES`1`)]; /{20}[ver=6](tickerId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;primaryExchange;currency;localSymbol;tradingClass;includeExpired;endDateTime;barSizeSetting;durationStr;useRTH;whatToShow;formatDate;{comboLegsCount;comboLegsCount*(conId;ratio;action;exchange)};chartOptionsStr),{barSizeSetting:1 secs/5 secs/10 secs/15 secs/30 secs/1 min/2 mins/3 mins/5 mins/10 mins/15 mins/20 mins/30 mins/1 hour/2 hours/3 hours/4 hours/8 hours/1 day/1W/1M},{durationStr:n S/D/W/M/Y}
exercise_options[]; /{21}[ver=2](tickerId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;currency;localSymbol;tradingClass;exerciseAction;exerciseQuantity;account;override)
req_scanner_subscription[]; /{22}[ver=4](tickerId;numberOfRows;instrument;locationCode;scanCode;abovePrice;belowPrice;aboveVolume;marketCapAbove;marketCapBelow;moodyRatingAbove;moodyRatingBelow;spRatingAbove;spRatingBelow;maturityDateAbove;maturityDateBelow;couponRateAbove;couponRateBelow;excludeConvertible;averageOptionVolumeAbove;scannerSettingPairs;stockTypeFilter;scannerSubscriptionOptionsStr)
cancel_scanner_subscription[]; /{23}[ver=1](tickerId)
req_scanner_parameters[1]; /{24}[ver=1]()
cancel_historical_data[]; /{25}[ver=1](tickerId)
req_current_time[1]; /{49}[ver=1]
req_real_time_bars[(3;newseq[];`0`XINA50`FUT`201510`0```SGX``USD```5`TRADES`1`)]; /{50}[ver=3](tickerId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;primaryExchange;currency;localSymbol;tradingClass;barSize;whatToShow;useRTH;realTimeBarsOptionsStr)=>req_real_time_bars[(3;newseq[];`0`EUR`CASH``0```IDEALPRO``USD`EUR.USD``5`TRADES`1`)];
cancel_real_time_bars[(1;`10017)]; /{51}[ver=1](tickerId)
req_fundamental_data[]; /{52}[ver=2](reqid;conId;symbol;secType;exchange;primaryExchange;currency;localSymbol;reportType)
cancel_fundamental_data[]; /{53}[ver=1](reqid)
req_calc_implied_volat[]; /{54}[ver=2](reqId;conId;symbol;secType;expiry;strike;right;multiplier;exchange;primaryExchange;currency;localSymbol;tradingClass;optionPrice;underPrice)
req_calc_option_price[]; /{55}[ver=2](reqid;conId;symbol;secType;expiry;strike;right;multiplier;exchange;primaryExchange;currency;localSymbol;tradingClass;volatility;underPrice)
cancel_calc_implied_volat[]; /{56}[ver=1](reqid)
cancel_calc_option_price[]; /{57}[ver=1](reqid)
req_global_cancel[]; /{58}[ver=1]()
req_market_data_type[]; /{59}[ver=1](marketDataType)
req_positions[(1;newseq[];``)]; /{61}[ver=1](reqId;groupName;tags)
req_account_summary[(1;newseq[];`All;`$"AccountType,NetLiquidation,TotalCashValue,SettledCash,AccruedCash,BuyingPower,EquityWithLoanValue,PreviousEquityWithLoanValue,GrossPositionValue,RegTEquity,RegTMargin,SMA,InitMarginReq,MaintMarginReq,AvailableFunds,ExcessLiquidity,Cushion,FullInitMarginReq,FullMaintMarginReq,FullAvailableFunds,FullExcessLiquidity,LookAheadNextChange,LookAheadInitMarginReq,LookAheadMaintMarginReq,LookAheadAvailableFunds,LookAheadExcessLiquidity,HighestSeverity,DayTradesRemaining,Leverage")]; /{62}[ver=1](reqId;groupName;tags)
cancel_account_summary[]; /{63}[ver=1](reqid)
cancel_positions[]; /{64}[ver=1]()
verify_request[]; /{65}[ver=1](apiName;apiVersion)
verify_message[]; /{66}[ver=1](apiData)
query_display_groups[]; /{67}[ver=1](reqId)
subscribe_to_group_events[]; /{68}[ver=1](reqId;groupId)
update_display_group[]; /{69}[ver=1](reqId;contractInfo)
unsubscribe_from_group_events[]; /{70}[ver=1](reqId)
start_api[(1;12345)] /{71}[ver=1](clientId)


/order:(action;totalQuantity;orderType;lmtPrice;auxPrice;tif;ocaGroup;account;openClose;origin;orderRef;transmit;parentId;blockOrder;sweepToFill;displaySize;triggerMethod;outsideRthhidden{;comboLegsCount;comboLegsCount*(conId;ratio;action;exchange;openClose;shortSaleSlot;designatedLocation;exemptCode);orderComboLegsCount;orderComboLegsCount*(price);smartComboRoutingParamsCount;smartComboRoutingParamsCount*(tag;value)};sharesAllocation;discretionaryAmt;goodAfterTime;goodTillDate;faGroup;faMethod;faPercentage;faProfile;shortSaleSlot;designatedLocation;exemptCode;ocaType;rule80A;settlingFirm;allOrNone;minQty;percentOffset;eTradeOnly;firmQuoteOnly;nbboPriceCap;auctionStrategy;startingPrice;stockRefPrice;delta;stockRangeLower;stockRangeUpper;overridePercentageConstraints;volatility;volatilityType;deltaNeutralOrderType;deltaNeutralAuxPrice{;deltaNeutralConId;deltaNeutralSettlingFirm;deltaNeutralClearingAccount;deltaNeutralClearingIntent;deltaNeutralOpenClose;deltaNeutralShortSale;deltaNeutralShortSaleSlot;deltaNeutralDesignatedLocation};continuousUpdate;referencePriceType;trailStopPrice;trailingPercent;scaleInitLevelSize;scaleSubsLevelSize;scalePriceIncrement{;scalePriceAdjustValue;scalePriceAdjustInterval;scaleProfitOffset;scaleAutoReset;scaleInitPosition;scaleInitFillQty;scaleRandomPercent};scaleTable;activeStartTime;activeStopTime;hedgeType{;hedgeParam};optOutSmartRouting;clearingAccount;clearingIntent;notHeld;underComp{;conId;delta;price};algoStrategy{algoParamsCount;algoParamsCount*(tag;value)};whatIf;miscOptionsStr)
