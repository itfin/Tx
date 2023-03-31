.module.fetws:2022.04.21;

txload "core/febase";
txload "feed/tws/twsbase";
\d .temp
P:BaseReqMap:ScanMap:ConReqMap:TwsReqMap:()!();
\d .
.enum.TWSStatusMap:`PendingSubmit`PendingCancel`PreSubmitted`Submitted`Cancelled`ApiCancelled`Filled`Inactive!.enum`PENDING_NEW`PENDING_CANCEL`PENDING_NEW`NEW`CANCELED`CANCELED`FILLED`REJECTED;

qxsnap:{[]1!select sym,ex,esym,name,ticker,assetclass,product,multiplier,currency,strikepx,putcall,sectype,pxunit,qtylot,qtymax,qtymaxm,qtymaxl,qtymaxs,margintype,rmarginl,rmargins,rmarginoq,rmarginmq,rfeetaxoa,rfeetaxoq,rfeetaxca,rfeetaxcq,rfeetaxcat,rfeetaxcqt,rfeetaxom,rfeetaxcm,rfeetaxctm,settledate,opendate,createdate,lifephase,sec_key,underlying,isin,ex1,cficode,notice,remark from .db.QX where not null name};

pdnewmon:{[x;y]if[null fs0:exec last sym from .db.QX where product=x,settledate<y;:()];z:`$(string x),(string y)[2 3 5 6],".",string last ` vs fs0;.db.QX[z;`ex`esym`sectype`currency`margintype`rmarginl`rmargins`rmarginoq`rmarginmq`rfeetaxoq`rfeetaxcq]:.db.QX[fs0;`ex`esym`sectype`currency`margintype`rmarginl`rmargins`rmarginoq`rmarginmq`rfeetaxoq`rfeetaxcq];.db.QX[z;`settledate]:`date$y;reqtwscon[z];}; /[product;month] 滚动增加新月份合约 

.upd.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[not null .db.O[k;`sym];:()];k1:newidl[];.db.O[k;`feoid`ntime`status`cumqty`avgpx`lastqty`lastpx`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;0f;0f;0f;0f),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not `Logon~.ctrl.tws[`status];rejectord[k;1i;"TWS_Not_Logon"];:()];if[.conf.tws.ordmax<=count .db.O;rejectord[k;2i;"TWS_Ord_Toomany"];:()];r:.db.O[k];rq:.db.QX[z:r`sym];if[null rq`esym;rejectord[k;2i;"Fsym_Not_In_QX"];:()];tws_place_order[k1;`symbol`sectype`exchange`currency`localsymbol`right`expiry`strike`action`totalquantity`ordertype`lmtprice`openclose`tif`account!rq[`esym`sectype`ex`currency`ticker`putcall],($[null sd:rq`settledate;`;`$6#(string sd) except "."];`$string rq`strikepx;$[r[`side]=.enum`BUY;`BUY;`SELL];r[`qty];`LMT;r[`price];$[r[`posefct]=.enum`OPEN;`O;`C];$[r[`tif]~.enum`GOOD_TILL_CANCEL;`GTC;`];x`acc1)];}';

.upd.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db.O[k];if[null r`sym;:()];.db.O[k;`cstatus`cid]:(.enum`PENDING_CANCEL;x`cid);tws_cancel_order[r[`feoid]^x`feoid];}';

tws_err_msg:{[x]r:.db.O k:idfe2ft `$x`id;if[null r`sym;:tws_err_msg_1[x]];if[x[`text] like "Warning*";:()];.db.O[k;`msg]:x`text;execrpt[k];}; /if[x[`text] like "*rejected*";.db.O[k;`end`status`reason]:(1b;.enum`REJECTED;"I"$x`reason)];

tws_order_status:{[x]r:.db.O k:idfe2ft `$x`oid;if[r[`end]|(null r`sym);:()];if[null r[`ordid];.db.O[k;`ordid`acc1]:`$x`permid`clientid];st:.enum.TWSStatusMap`$x`status;cq:"F"$x`filled;lq:$[st in .enum`CANCELED`REJECTED;0f;"F"$x`remaining];ap:"F"$x`avgfillprice;if[(cq>0)&st=.enum`NEW;st:.enum`PARTIALLY_FILLED];.db.O[k;`status`cumqty`avgpx]:st,cq,ap;if[st=.enum`CANCELED;.db.O[k;`cstatus]:.enum`CANCELED];if[st in .enum`FILLED`CANCELED`REJECTED;.db.O[k;`end]:1b];execrpt[k];};

tws_open_order:{[x]};
tws_open_order_end:{[x]};

reqtwsexec:{[x]y:newseq[];.temp.TwsReqMap[y]:`Exec;tws_req_executions[y];}; /[]

tws_execution_data:{[x]k:idfe2ft `$x`oid;if[null .db.O[k;`sym];:()];if[null .db.O[k;`ordid];.db.O[k;`ordid`acc1]:`$x`permid`clientid];cq:"F"$x`cumqty;ap:"F"$x`avgprice;if[cq<=.db.O[k;`cumqty];:()];st:.enum $[0<lq:.db.O[k;`qty]-cq;`PARTIALLY_FILLED;`FILLED];.db.O[k;`status`cumqty`avgpx]:st,cq,ap;execrpt[k];};
tws_execution_data_end:{[x].temp.TwsReqMap["J"$x]:`End_of_Exec_Qry;}; /[reqid]

tws_commission_report:{[x]};

tws_acct_value:{[x].ctrl.tws.acct[`$(x`key),{$[count x;"_";""],x} x`cur]:{[x]y:"F"$x;$[null y;`$x;y]} x`val;}; /if[null y:exec first id from A;:()];z:`$x`key;v:"F"$x`val;$[z=`NetLiquidation;A[y;`fundbal]:v;z=`MaintMarginReq;A[y;`margin]:v;z=`FullAvailableFunds;A[y;`fundavl]:v;A[y;`x0],:enlist z,x`val`cur];

tws_portfolio_value:{[x]y:`$x`conid;if[null z:exec first sym from .db.QX where isin=y;:()];.ctrl.tws.port[z]:x;};

tws_acct_update_time:{[x].ctrl.tws.accttime:x;}; /[time]

tws_acct_download_end:{[x]}; /[acc] if[null k:exec first id from A where account like x;:()];smkx[A[k;`trader];`FundRpt;`aid`status`fundbal`fundavl`fundfrz`margin`mv`pnl`fundchg`risk`marginlong`marginshort`frzlong`frzshort`pnlopen`pnlclose!(k;`QrOK),A[k;`fundbal`fundavl`fundfrz`margin`mv`pnl`fundchg`risk`marginlong`marginshort`frzlong`frzshort`pnlopen`pnlclose]];

tws_acct_update_time:{[x].ctrl.tws.accttime:x;}; /[time]

reqtwscon:{[x]y:newseq[];.temp.ConReqMap[y]:x;tws_req_contract_data[y;`symbol`sectype`expiry`strike`right`exchange`currency`localsymbol`tradingclass!.db.QX[x;`esym`sectype],(`$sublist[6] (string .db.QX[x;`settledate]) except ".";`$string .db.QX[x;`strikepx]),.db.QX[x;`putcall`ex`currency`ticker],$[.db.QX[x;`sectype] in `WAR`OPT;.db.QX[x;`esym];`]];}; /[sym]

pubqx:{[](path:` sv .conf.tempdb,.conf.me,`RD) set qxsnap[];pubm[`ALL;`RDUpdate;`tws;string path];};

tws_contract_data:{[x]y:.temp.ConReqMap "J"$x`reqid;.db.QX[y;`esym`ex`sectype`currency`name`settledate`putcall`strikepx`ticker`pxunit`multiplier`cficode`product`sec_key`ex1`scale`isin`underlying`industry`assetclass`secclass`notice`cficode1`state`remark]:"SSSSSDSFSFFSSSSFSSSSSSSSS"$'x`symbol`exchange`sectype`currency`longname`expiry`right`strike`localsymbol`mintick`multiplier`marketname`tradingclass`timezoneid`validexchanges`pricemagnifier`conid`underconid`industry`category`subcategory`tradinghours`ordertypes`primaryexchange`contractmonth;pubqx[];};

tws_contract_data_end:{[x]}; /[reqid]

reqtwspos:{[x]y:newseq[];.temp.TwsReqMap[y]:`Pos;.temp.P:()!();tws_req_positions[y];}; /[]
tws_position_data:{[x]if[null z:exec first sym from .db.QX where isin=`$x`conid;:()];.temp.P[z]:`qty`avgcost!"F"$x`position`avgcost;};
tws_position_end:{[x]};

tws_scanner_parameters:{[x](path:` sv .conf.tempdb,.conf.me,`scanparam.xml) set x[`paramxml];};

tws_scanner_data:{[x].temp.DATA:x;r:.temp.ScanMap["J"$x`tickerid];pubmx[`ALL;`ScanRes;r`typ;"txscanres";-8!`$(,\:)[;".XHKG"] exec symbol from x`data];};

tws_fundamental_data:{[x].temp.x:x;k:"J"$x`reqid;h:.temp.BaseReqMap[k];(path:` sv .conf.tempdb,.conf.me,h[`typ],`$(string fs2s h`sym),".xml") set x[`xml];.temp.BaseReqMap:(enlist k) _ .temp.BaseReqMap;};

reqtwsscan:{[x]y:newseq[];tws_req_scanner_subscription[y;x];};

reqtwsbase:{[t;x]y:newseq[];.temp.BaseReqMap[y]:`sym`typ!(x;t);tws_req_fundamental_data[y;`symbol`sectype`exchange`currency`localsymbol`reporttype!.db.QX[x;`esym`sectype`ex`currency`ticker],t];};
reqtwsrptfinsum:reqtwsbase[`ReportsFinSummary];reqtwsrptowner:reqtwsbase[`ReportsOwnership];reqtwsrptsnap:reqtwsbase[`ReportSnapshot];reqtwsrptfin:reqtwsbase[`ReportsFinStatements];reqtwsrptresc:reqtwsbase[`RESC];reqtwsrptcal:reqtwsbase[`CalendarReport];

.upd.RDUpdate:{[x]if[`web<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;reqtwscon each exec sym from .db.QX where null name;};

tws_err_msg_1:{[x].temp.ERR:x;y:"J"$x`id;z:"J"$x`reason;if[(z in 200)&(y in key .temp.ConReqMap);.db.QX[.temp.ConReqMap[y];`status]:-1i;.temp.ConReqMap:(enlist y) _ .temp.ConReqMap;];if[z in 200 430;.temp.BaseReqMap:(enlist y) _ .temp.BaseReqMap];}; /

.upd.Scan:{[x]z:x`ref;y:newseq[];.temp.TwsReqMap[y]:`Scan;.temp.ScanMap[y]:`typ`src!z,x`src;tws_req_scanner_subscription[y;((enlist `scanCode)!enlist z),-9!x`vbin];};

.upd.ScanEnd:{[x]z:x`ref;{[x;y]if[x=.temp.ScanMap[y;`typ];tws_cancel_scanner_subscription[y]];}[z] each key .temp.ScanMap;};

parsexhkg:{[x]d:1_"<tr class=\"tr_normal\">" vs x;flip `sym`qtylot!flip {[x]y:"\r\n" vs x;({x (first ss[x;"\">"])+2+til 5} y[1];{k1:(first ss[x;"\">"])+2;k2:last ss[x;"<"];"F"$(x k1+til k2-k1) except ","} y[3])} each d};

updxhkg1:{[x;y]d:select sym:`$(,\:)[sym;".XHKG"],ex:`SEHK,esym:`$sym,sectype:`STK,currency:`HKD,qtylot from update string "F"$sym from (parsexhkg wget "http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfo/stockcode/eisdeqty_c.htm"),(parsexhkg wget "http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfo/stockcode/eisdgems_c.htm");nl:(exec sym from d) except exec sym from .db.QX;.db.QX:.db.QX uj 1!d;reqtwscon each exec sym from .db.QX where sym in nl;count nl}; /,(parsexhkg wget "http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfo/stockcode/eisdwarr_c.htm"),(parsexhkg wget "http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfo/stockcode/eisdcbbc_c.htm") 主板/创业板/权证/牛熊证

updxhkg:{[x;y].temp.d0:d:select sym:`$(,\:)[string sym;".XHKG"],ex:`SEHK,esym:?[sectype=`WAR;`;sym],name,ticker:sym,sectype:?[secstatus=(`$"Derivative Warrants");`WAR;`STK],currency:`HKD,qtylot,secstatus,secclass,sectype,isin from update sym:`$string "F"$string sym from d1:select from (d0:`sym`name`secstatus`secclass`qtylot`sectype`isin`datestr xcol ("SSSSFSS*SSSSSSSSFS";enlist "\t") 0: ssr[;",";""] each 2_system "wget -O /tmp/ListOfSecurities.xlsx https://www.hkex.com.hk/eng/services/trading/securities/securitieslists/ListOfSecurities.xlsx && xlsx2csv -d tab -i -s 1 /tmp/ListOfSecurities.xlsx") where secstatus in (`Equity,(`$"Exchange Traded Products"),(`$"Derivative Warrants"));nl:(exec sym from d) except exec sym from .db.QX;.db.QX:.db.QX uj 1!d;reqtwscon each exec sym from .db.QX where sym in nl,sectype=`STK;(path:` sv .conf.tempdb,.conf.me,`hklist) set d0;1b}; /,settledate:{"D"$sv["."] reverse vs["/"]x} each datestr

//updxhkgopt:{[x;y].temp.d:update underlying:`$(,\:)[string esym;".XHKG"] from update sym:`$(,\:)[string "I"$string sym;".XHKG"],esym:`$string "I"$string esym,putcall:?[`CALL=putcall;`C;`P],{"D"$"." sv reverse "-" vs x} each settledate from delete from (`sym`tradephase`suspendtype`esym`putcall`settledate`currency`strikepx xcol ("SSSSS*SF";enlist "\t") 0: -1_7_ system "wget -O - https://www.hkex.com.hk/eng/dwrc/search/dwAQList.csv|iconv -f UTF-16 -t ASCII") where `HKD<>currency;.db.QX:.db.QX lj 1!.temp.d;reqtwscon each exec sym from .db.QX where sectype=`WAR,not null esym,null ex1,null status;};

updxhkgdw:{[x;y].temp.d:update sym:`$(,\:)[string ticker;".XHKG"],esym:`$string "I"$string esym,putcall:?[`Call=putcall;`C;`P],{trddiff[`XHKG;-4] "D"$"." sv reverse "-" vs x} each settledate,{"D"$"." sv reverse "-" vs x} each opendate from delete issuer,dwtype from delete from (`ticker`issuer`esym`putcall`dwtype`opendate`settledate`currency`strikepx xcol ("SSSSS**SF";enlist "\t") 0: -3_2_ system "wget -O - https://www.hkex.com.hk/eng/dwrc/search/dwFullList.csv|iconv -f UTF-16 -t ASCII") where `HKD<>currency;.db.QX:.db.QX lj 1!.temp.d;reqtwscon each exec sym from .db.QX where sectype=`WAR,not null esym,null ex1,null status;1b}; /衍生品权证

reqbasetask:{[t;x;y]if[0=n:count L:.ctrl.symlst;:()];m:n&.conf.tws.batchcnt&(.conf.tws.basereqmax-count .temp.BaseReqMap);if[0>=m;:()];l:m#L;.ctrl.symlst:m _L;reqtwsbase[t] each l;1b};
reqrptsnaptask:reqbasetask[`ReportSnapshot];

updsnap:{[]d:delete from (flip `sym`qtymaxl`qtymaxs!flip {{[x;y]z:@[{(!/)flip .[;(0;1;::;0 1)] xmlparse x};2_read0 ` sv x,y;()];(`$ssr[;"xml";"XHKG"] string y;@[{"F"$@[;`SharesOut](!/)flip .[;(::;0 1)] @[;`CoGeneralInfo] x};z;0n];@[{@[;`ProjEPS] (!/)flip {(`$x[1;`FieldName];"F"$x[0;0;1])} each .[;(::;1 2)] @[;`ForecastData] x};z;0n])}[x] each key x} ` sv .conf.tempdb,.conf.me,`ReportSnapshot) where null qtymaxl;.db.QX:.db.QX lj 1!d;pubqx[];};

\

.db.TASK[`UPDXHKG;`firetime`firefreq`weekmin`weekmax`handler]:(\"p\"$.z.D+08:28:00;1D;0;4;`updxhkg);
.db.TASK[`UPDXHKGDW;`firetime`firefreq`weekmin`weekmax`handler]:(\"p\"$.z.D+08:30:00;1D;0;4;`updxhkgdw);

.db.TASK[`UPDXHKG;`firetime`firefreq`handler]:(\"p\"$.z.D+08:28:00;1D;`updxhkg);

.db.TASK[`REQSNAPTASK;`firetime`firefreq`timemin`timemax`handler]:(\"p\"$.z.D+00:00:00;0D00:00:01;00:00;15:55;`reqrptsnaptask);

reqtwsscan[`scanCode`abovePrice!`TOP_PERC_GAIN`2];
reqtwsscan[`scanCode`abovePrice!`HOT_BY_PRICE`0.1];

.db.QX[`600000.XSHG;`ex`esym`sectype`currency]:`SEHKNTL`600000`STK`CNH;

.db.QX[`799.SEHK;`ex`esym`sectype`currency]:`SEHK`799`STK`HKD;
.db.QX[`12885.XHKG;`ex`esym`sectype`currency`ticker`settledate`strikepx`putcall]:`SEHK`799`WAR`HKD`12885,(2018.08.08;16f;`C);


reqtwscon each exec sym from .db.QX where null name;

.db.QX:.db.QX uj 1!`sym xcols update sym:`$(,\:)[string esym;".XHKG"] from select ex:`SEHK,esym:`$string "I"$string sym,sectype:`STK,currency,qtylot,opendate from d where secclass=`MAIN,sectype=`EQTY,currency=`HKD /从深港通港股信息文件数据同步股票代码

.db.QX:.db.QX uj 1!`sym xcols update sym:`$(,\:)[string ticker;".XHKG"] from select ex:`SEHK,esym:`$string "I"$string underlying,ticker:`$string "I"$string sym,sectype:`WAR,currency,qtylot,opendate from d where secclass=`MAIN,sectype=`WRNT,currency=`HKD,underlying=`00799 /从深港通港股信息文件数据同步权证代码


.ctrl.symlst:exec distinct sym from .db.QX where ex=`SEHK,not sym in (`$ssr[;".xml";".XHKG"] each string key `:/kdb/txdb/usr/ha/tempdb/fetws/ReportSnapshot)

http://www.hkex.com.hk/eng/dwrc/search/dwAQList.csv