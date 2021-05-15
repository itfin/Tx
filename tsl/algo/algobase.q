//算法交易策略
.module.tsalgobase:2017.04.26;

txload "tsl/tslib";

//time2bucket:{[x]?[x=00:00:00;0;?[x>03:58:00;0W;?[x>=03:56:00;237;1+`int$`minute$x]]]}; /0:开盘集合竞价,1..237:各连续竞价分钟,0W:收盘集合竞价
//time2bucketss:{[x]?[x=00:00:00;0;1+`int$`minute$x]}; /[time] 0:开盘集合竞价,1..240:各连续竞价分钟

time2bucketss:time2bucketsz:{[x]?[x=00:00:00;0;?[x>03:58:00;0W;?[x>=03:56:00;237;1+`int$`minute$x]]]}; /0:开盘集合竞价,1..237:各连续竞价分钟,0W:收盘集合竞价
 
time2bucketex:{[x;y]$[x=`XSHE;time2bucketsz y;time2bucketss y]}; /[ex;time]根据市场和时刻计算所在桶

bucketstartcn:{[x]?[x=0;09:15:00.000;?[x=0W;14:57:00.000;?[x<=120;`time$09:30+x-1;`time$13:00+x-121]]]}; /[bucket]计算所在桶的起始时间
bucketstopcn:{[x]?[x=0;09:24:59.999;?[x=0W;14:59:59.999;00:00:59.999+?[x<=120;`time$09:30+x-1;`time$13:00+x-121]]]}; /[bucket]计算所在桶的结束时间

bucketstarthk:{[x]?[x=0;09:30:00.000;?[x<=150;`time$10:00+x-1;`time$14:30+x-151]]}; /[bucket]计算港股所在桶的起始时间
bucketstophk:{[x]?[x=0;09:59:59.999;00:00:59.999+?[x<=150;`time$10:00+x-1;`time$14:30+x-151]]}; /[bucket]计算港股所在桶的结束时间

bucketstartccfx:{[x]?[x=0;09:29:00.000;?[x<=120;`time$09:30+x-1;`time$13:00+x-121]]}; /[bucket]计算金融期货所在桶的起始时间
bucketstopccfx:{[x]?[x=0;09:29:59.999;00:00:59.999+?[x<=120;`time$09:30+x-1;`time$13:00+x-121]]}; /[bucket]计算金融期货所在桶的结束时间

bucketstartex:{[x;y]?[x=`XHKG;bucketstarthk y;?[x=`CCFX;bucketstartccfx y;bucketstartcn y]]}; /[ex;time]根据市场和桶号计算所在桶起始时间
bucketstopex:{[x;y]?[x=`XHKG;bucketstophk y;?[x=`CCFX;bucketstopccfx y;bucketstopcn y]]}; /[ex;time]根据市场和桶号计算所在桶结束时间

forcestring:{$[-11h=type x;string x;x]};

loadhvpdb:{[x;y]{.temp[x]:get sv[`;.conf.tempdb,x];} each `HCOV`HSSAM`HSVP`HSD;1b};

algo_updhvpn:{[x;n]if[0>h:.ctrl.conn[`hdb;`h];:()];L:h({[x;n]d1:x&max date;d0:{first ((neg x)&count y)#y}[n] date where date<=d1;t:select date,sym,bucket:{[s;x]?[x=00:00:00;0;?[(x>03:58:00)&s like\: "*XSH*";0W;?[(x>=03:56:00)&s like\: "*XSH*";237;240&1+`int$`minute$x]]]}[sym;{(0|(x&15:00)-13:00)+0|(x&11:30)-09:30} `second$time],cumqty,amt:cumqty*vwap,price,bid,ask from quote where date within (d0,d1),0<cumqty&price;(ungroup delete from (select tr:(deltas cumqty)%(last cumqty),bucket,amt:deltas amt,yield:{0f,1_ x} deltas log price by date,sym from select last cumqty,last amt,last price by date,sym,bucket from t) where ({(15<=max deltas x except 0W)} each bucket)|(0.09<max each tr);select last amt,last price,spread:{avg x where (x>0f)&(x<0w)} (-1+ask%bid) by date,sym from t)};x;n);d:L[0];z:select sum yield by date,sym,bar:30 xbar 240&bucket from d;u:exec distinct flip (date;bar) from z;a:exec 0f^((flip (date;bar))!yield)u by sym from z;.temp.HCOV:`syms`covm!(key a;8*.math.cvm value a);.temp.HSSAM:0!select tr,amt by sym,bucket from d;.temp.HSVP:update `p#sym,bucketstart:bucketstartex[fs2e each sym;bucket],bucketstop:bucketstopex[fs2e each sym;bucket] from  `sym`bucket xkey ungroup select tr:tr%sum tr,bucket,amt,trls:trls%sum trls,sizels by sym from select sym,bucket,tr:sym ({avg x#z,x#1%$[`XSHE=fs2e y;240;`XSHG=fs2e y;240;240]}[n])' tr,amt:avg each amt,trls:0f,sizels:0f from .temp.HSSAM;.temp.HSD:update `u#sym from select avg amt,avg spread,yield:avg -1+1_ratios price,stddev:sqrt var -1+1_ratios price by sym from 0!L[1];{sv[`;.conf.tempdb,x] set .temp[x];} each `HCOV`HSSAM`HSVP`HSD;};

onr_algo:{[x;y]gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;`O1);,;select from .db.O1 where end|tif<>gtc];delete from `.db.O1 where end|tif<>gtc;linfo[`AlgoWrapDay;(x;y;now[])];setstate[;`OK] each `QS`EMS;if[1b~.conf[`updhvp];algo_updhvpn[y;20^jfill .conf[`lookbackdays]]];}; /[ts;vtd]日终处理
onq_algo:{[x;y]if[not `OK~.ctrl.StateMap`EMS;:()];}; /[tid;syms] algoapply[x;now[]];

oni_algo:{[x;y]setstate[;`OK] each `QS`EMS;.temp.hO1:(`u#`symbol$())!`boolean$();.temp.hO:(`u#`symbol$())!`symbol$();{.temp.hO1[x]:1b;} each exec id from .db.O1 where not (status in .enum`FILLED`DONE_FOR_DAY`CANCELED`REPLACED`REJECTED)|(cstatus in .enum`CANCELED`REPLACED);{.temp.hO[x]:.db.O[x;`upid];} each exec id from .db.O where not (status in .enum`FILLED`DONE_FOR_DAY`CANCELED`REPLACED`REJECTED)|(cstatus in .enum`CANCELED`REPLACED);loadhvpdb[`;`];linfo[`AlgoInit;(x;now[])];}; /系统启动处理
one_algo:{[x;y]linfo[`AlgoExit;(x;now[])];}; /系统退出处理


/algo msg
.upd[`ExecRptAlgo]:{[x].temp.x00:x;};

.upd[`NewOrderAlgo]:{[x].temp.x01:x;he:x`src;coid:x`id;k:exec first id from .db.O1 where clt=he,cltid=coid;$[not null k;.upd[`ExecRptAlgo][`id`status`reason`msg!(coid;.enum`REJECTED;.enum`UNKNOWN_ORDER;"Already have order ",string coid)];[k:newid[];x[`qty`amt`price]:`float$x`qty`amt`price;if[not null a:x`amt;x[`qty]:roundqty[x`sym`side] a%get_last_price[x`sym]];.db.O1[k;`tsexec`ts`acc1`ordid`status`ntime`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style`clt`algo`plan`snap`cltid`handlinst`execinst`sym`side`typ`qty`amt`price`para`cltalt`cltsub`cltid2`cltacc`ex`sym`stoppx`posefct]:(.conf.algots;.conf.algots^x`ts;x`acc1;newid[];.enum`NEW;now[];0f;0f;0f;0f;0f;0f;0f;.db.Ts[.conf.algots;`DEFAULTSTYLE];he;x`algo;();()),x`id`handlinst`execinst`sym`side`typ`qty`amt`price`para`cltalt`cltsub`cltid2`cltacc`ex`sym`stoppx`posefct;.db.Ax[k]:.enum.nulldict;.db.Ax[k;`sids`ahead]:(();()!`symbol$());.upd[`ExecRptAlgo][`id`status`ordid!.db.O1[k;`cltid`status`ordid]]]];}; 

.upd[`CancelOrderAlgo]:{[x].temp.x02:x;he:(x`src)^x`clt;z:x`id;cid:x`cid;k:exec first id from .db.O1 where clt=he,cltid=z;$[null .db.O1[k;`sym];rejectcxloa[he;z;cid;.enum`UNKNOWN_ORDER_CXL;`Unknown];0=(-/).db.O1[k;`qty`cumqty];rejectcxloa[he;z;cid;.enum`TOO_LATE_TO_CANCEL;`Fill];.enum[`NULL]<>.db.O1[k;`cstatus];rejectcxloa[he;z;cid;.enum`ALREADY_PENDING;`Pending];[.db.O1[k;`cltcid`cstatus`cordid`ctime`pending`lastqty`lastpx]:(cid;.enum`PENDING_CANCEL;newid[];now[];1b;0f;0f);if[count t:x`msg;.db.O1[k;`msg]:t];execrptoa[k];$[.db.O1[k;`sentqty]=.db.O1[k;`cumqty];[.db.O1[k;`end`pending]:(1b;0b);$[0f<cxlqty:.db.O1[k;`qty]-.db.O1[k;`cumqty];[.db.O1[k;`status`cstatus]:(.enum`CANCELED;.enum`CANCELED);execrptoa[k]];[.db.O1[k;`cstatus]:.enum`REJECTED;rejectcxloa[he;z;cid;.enum`TOO_LATE_TO_CANCEL;`Fill]]]];cxloachildren[k]]]];};

.upd[`ReplaceOrderAlgo]:{[x].temp.x03:x;he:x`src;z:x`id;cid:x`cid;k:exec first id from .db.O1 where clt=he,cltid=z;if[null .db.O1[k;`sym];rejectrploa[he;z;cid;.enum`UNKNOWN_ORDER_CXL;`Unknown];:()];x[`qty`amt`price]:"f"$x`qty`amt`price;if[not null a:x`amt;x[`qty]:roundqty[x`sym`side] a%get_last_price[x`sym]];if[(.enum[`FILLED]=.db.O1[k;`status])&(not .db.O1[k;`qty]>x`qty);rejectrploa[he;z;cid;.enum`TOO_LATE_TO_CANCEL;`Fill];:()];if[.enum[`NULL]<>.db.O1[k;`cstatus];rejectrploa[he;z;cid;.enum`ALREADY_PENDING;`Pending];:()];if[(.db.O1[k;`cumqty]>x`qty)|(not .db.O1[k;`sym]~x`sym)|(not .db.O1[k;`side]~x`side)|(not .db.O1[k;`handlinst]~x`handlinst);rejectrploa[he;z;cid;.enum`BROKER_OPTION;`MismatchSymOrSideOrHandlInstOrQtyError];:()];mycid:newid[];.db.O1[k;`cid`cltcid`cstatus`cordid`pending`lastqty`lastpx]:(mycid;cid;.enum`PENDING_REPLACE;newid[];1b;0f;0f);execrptoa[k];.db.O1[k;`x0]:enlist x;$[.db.O1[k;`cumqty]<.db.O1[k;`sentqty];[cxloachildren[k]];[.db.O1[mycid;`ordid`status`ntime`plan`snap`cltid2`cltacc`tsexec`ts`acc1`ex`sym`cltsub`cltalt`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style`suspend`previd`clt`algo`cltid`handlinst`execinst`sym`side`typ`qty`amt`price`para`stoppx`posefct]:(.db.O1[k;`cordid];$[0<.db.O1[k;`cumqty];.enum`PARTIALLY_FILLED;.enum`NEW];now[];();();x`cltid2;x`cltacc),.db.O1[k;`tsexec`ts`acc1`ex`sym`cltsub`cltalt`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style],(((string x`ExecInst) like "*S*");k;he;x`algo),x`cid`handlinst`execinst`sym`side`typ`qty`amt`price`para`stoppx`posefct;.db.Ax[mycid]:.enum.nulldict;.db.Ax[mycid;`sids`ahead]:(();()!`symbol$());update upid:mycid from `.db.O where upid=k;.db.O1[k;`end`pending`status`cstatus`qty`amt`price`typ]:(1b;0b;.enum`REPLACED;.enum`REPLACED),x`qty`amt`price`typ;execrptoa[k]]];}; 

.upd[`NewOrderAlgoList]:{[x].temp.x04:x;he:x`src;coid:x`id;k:exec first id from .db.O1 where clt=he,cltid=coid;if[null k;k:newid[];.db.O1[k;`status`extype`slot`clt`cltid`cltalt`cltsub`cltid2`cltacc`algo`para]:(.enum`NEW;`LIST;x`totalsize;he;coid),x`cltalt`cltsub`cltid2`cltacc`algo`para;.db.Ax[k]:.enum.nulldict;.db.Ax[k;`full`sids`init]:(0b;();0b)];sids:{[listid;he;x]coid:x`id;k:exec first id from .db.O1 where clt=he,(cltid=coid)|(upid=listid)&(slot=x`slot);$[not null k;[.upd[`ExecRptAlgo][`sym`id`status`reason`msg!(he;coid;.enum`REJECTED;.enum`UNKNOWN_ORDER;`$"Already have order ",string coid)]];[k:newid[];x[`qty`amt`price]:"f"$x`qty`amt`price;if[not null a:x`amt;x[`qty]:roundqty[x`sym`side] a%get_last_price[x`sym]];.db.O1[k;`extype`upid`tsexec`ts`acc1`ordid`status`ntime`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style`clt`algo`plan`snap`slot`cltid`handlinst`execinst`sym`side`typ`qty`amt`price`para`cltalt`cltsub`cltid2`cltacc`ex`sym`stoppx`posefct]:(`LISTCHILD;listid;.conf.algots;.conf.algots^x`ts;x`acc1;newid[];.enum`NEW;now[];0f;0f;0f;0f;0f;0f;0f;.db.Ts[.conf.algots]`DEFAULTSTYLE;he;x`algo;();()),x`slot`id`handlinst`execinst`sym`side`typ`qty`amt`price`para`cltalt`cltsub`cltid2`cltacc`ex`sym`stoppx`posefct;.upd[`ExecRptAlgo][`sym`id`status`ordid!he,.db.O1[k;`cltid`status`ordid]]]];k}[k;he] each x`list;if[(not .db.Ax[k;`full])&(.db.O1[k;`slot]=max x[`list;;`slot]);.db.Ax[k;`full]:1b];if[0<count sids:sids except `;.db.Ax[k;`sids]:.db.Ax[k;`sids],sids];};

listrej:{[x;y;z].upd[`ListStatusAlgo][`sym`listid`type`status`msg!(x;y;.enum`RESPONSE;.enum`REJECT;forcestring z)];};

.upd[`CancelOrderAlgoList]:{[x].temp.x05:x;he:x`src;coid:x`id;k:exec first id from .db.O1 where clt=he,cltid=coid,extype=`LIST;if[null k;:listrej[he;coid;`UnknownListID]];if[.db.O1[k;`status]=.enum`CANCELED;:listrej[he;coid;`ListAlreadyCanceled]];if[.db.O1[k;`pending];:listrej[he;coid;`ListAlreadyCanceling]];.db.O1[k;`pending]:1b;y:.db.Ax[k;`sids];cxloasys[;x`msg] each y;};

.upd[`PauseCtrlOrderAlgo]:{[x]he:x`src;coid:x`id;ps:x`ps;k:exec first id from .db.O1 where clt=he,cltid=coid;if[(null k)|.db.O1[k;`pending]|.db.O1[k;`end]|(not (.enum`RUNNING) in ps,{$[x=.enum`NULL;.enum`RUNNING;x]} .db.O1[k;`usrpause]);:()];$[(ps in .enum`RUNNING`PAUSE)|(.db.O1[k;`sentqty]=.db.O1[k;`cumqty]);[.db.O1[k;`suspend`usrpause]:($[ps=.enum`RUNNING;0b;1b];ps);if[ps=.enum`RUNNING;.db.O1[k;`jn`plan`snap]:(0;();())];.upd[`PauseCtrlAckAlgo][`sym`id`ps!(he;coid;ps)]];[.db.O1[k;`pending`pendingwait]:(1b;`Pause);cxloachildren[k]]];};

.upd[`BrokerStatus]:{[x]s:x`status;setstate[`EMS;s];}; /子单通道状态查询结果

.upd[`ExecRptNOE]:{[x]upid:exec first id from .db.O1 where clt=x`src,cltid=x`oacltid;if[null upid;lwarn[`UnknownNOE;x`src`oacltid`id];:()];id:x`id;if[not null .db.O[id;`sym];lwarn[`ExistNOE;x`src`oacltid`id];:()];.db.O[id;`ntime`upid`slot`style`expiretime`ts`acc`cltid`posefct`status`cltid2`cltacc`cumqty`avgpx`cumamt`ordid`sym`side`qty`typ`price`ex`sym`msg]:(now[];upid;0Ni;.db.O1[upid;`style];`timestamp$(`date$now[])+{$[(x>.db.EX[`XSHG;`closeAM])&(x<.db.EX[`XSHG;`openPM]);x+(.db.EX[`XSHG;`openPM])-.db.EX[`XSHG;`closeAM];x]} (`time$now[])+`time$.db.Ts[.conf.algots]`NOETIMEOUT;.conf.algots;.db.Ts[.conf.algots;`acc];`;$[x[`side]=.enum.BUY;.enum.OPEN;.enum.CLOSE];.enum`NEW;.db.O1[upid;`cltid2];.db.O1[upid;`cltacc];0f;0f;0f),x`ordid`sym`side`qty`typ`price`ex`sym`msg;.db.O1[upid;`sentqty]:(x`qty)+0f^.db.O1[upid;`sentqty];.temp.hO[id]:upid;.upd[`ExecRpt][x];}; /NOE子单回报

/local msg

lst_cxl_child_end:{[k]x:.db.O1[k;`upid];.db.Ax[x;`sids]_:k;if[(0=count[.db.Ax[x;`sids]])&.db.O1[x;`pending];.db.O1[x;`pending`end`status]:(0b;1b;.enum`CANCELED);.db.Ax _:x;];};

/ATE functions
oa_cxl_pause:{[k].db.O1[k;`pending`pendingwait]:(0b;`);
 if[.db.O1[k;`cumqty]<.db.O1[k;`qty];.db.O1[k;`suspend`usrpause]:(1b;ps:.enum`PAUSEWITHCANCEL);.upd[`PauseCtrlAckAlgo][`sym`id`ps!(.db.O1[k;`clt];.db.O1[k;`cltid];ps)];];
 }; 

oa_cxl_cancel:{[k].db.O1[k;`end`pending]:(1b;0b);cxlqty:.db.O1[k;`qty]-.db.O1[k;`cumqty];if[`LISTCHILD=.db.O1[k;`extype];lst_cxl_child_end[k]];.db.Ax _:k;
 $[0f<cxlqty;[.db.O1[k;`status`cstatus]:(.enum`CANCELED;.enum`CANCELED);execrptoa[k]]; /撤单成功
 [.db.O1[k;`status`cstatus]:(.enum`FILLED;.enum`REJECTED);rejectcxloa[.db.O1[k;`clt];.db.O1[k;`cltid];.db.O1[k;`cid];.enum`TOO_LATE_TO_CANCEL;`Fill]] /rej
 ];};

oa_cxl_replace:{[k]x:.db.O1[k;`x0][0];mycid:.db.O1[k;`cid];he:.db.O1[k;`clt]; /原始改单请求
 $[.db.O1[k;`cumqty]<x`qty;
 [.db.O1[mycid;`ordid`status`ntime`plan`snap`ex`sym`cltsub`cltid2`cltacc`cltalt`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style`suspend`previd`clt`algo`cltid`handlinst`execinst`sym`side`typ`qty`price`para]:(.db.O1[k;`cordid];$[0<.db.O1[k;`cumqty];.enum`PARTIALLY_FILLED;.enum`NEW];now[];();()),.db.O1[k;`ex`sym`cltsub`cltid2`cltacc`cltalt`cumqty`cumamt`cumfee`avgpx`lastqty`lastpx`sentqty`style],(((string x`ExecInst) like "*S*");k;he;x`algo),x`cid`handlinst`execinst`sym`side`typ`qty`price`para;update upid:mycid from `.db.O where upid=k;.db.O1[k;`end`pending`status`cstatus`qty`price`typ]:(1b;0b;.enum`REPLACED;.enum`REPLACED),x`qty`price`typ;execrptoa[k]]; /改单成功 
 rejectrploa[he;x`id;x`cid;.enum`TOO_LATE_TO_CANCEL;`Fill] /改单拒绝
 ]  /改单处理结束
 ;};

oacxlrpl:{[k].db.O1[k;`lastqty`lastpx]:0f;
 $[`Pause=.db.O1[k;`pendingwait];oa_cxl_pause[k]; /大单请求暂停
 0=count .db.O1[k;`x0];oa_cxl_cancel[k]; /大单请求撤单
 oa_cxl_replace[k]]; /大单请求改单 	
 };

violateoddlotrule:{[x;y](.db.O1[x;`side]=.enum`SELL)&(z<qtyunit[.db.O1[x;`sym]])&(((-/).db.O1[x;`qty`cumqty])<>z)|(y<>z:.db.O1[x;`qty]-.db.O1[x;`sentqty])}; /[upid;qty]是否可能违反零股必须一次性卖出限制 
violateminamtrule:{[x;y;z](a>y*z)&(y<>.db.O1[x;`qty]-.db.O1[x;`sentqty])&(0<a:.db.Ts[.conf.algots;`MINAMT]^"F"$cfill .db.O1[x;`para][0;`MinAmt])}; /[upid;qty;px]是否可能违反最小交易金额限制(避免小额委托的报单成本)

ono_algo:{[x;y]k:.db.O[y;`upid];ag:.db.O1[k;`algo]; 
 if[(.db.O[y;`status] in .enum`FILLED`DONE_FOR_DAY`CANCELED`REPLACED`REJECTED)|(.db.O[y;`cstatus] in .enum`CANCELED`REPLACED);.temp.hO _:y];	
 if[.db.O[y;`status]=.enum[`REJECTED];.db.O1[k;`sentqty]-:.db.O[y;`qty];.db.O1[k;`jtime`jn]:(now[];1i+0i^.db.O1[k;`jn]);if[.db.O1[k;`jn]>=.db.Ts[.conf.algots]`MAXREJECT;info:`$"Auto Pause AlgoOrder For successive Rejected Child Orders.";$[`HS~.db.Ts[.conf.algots]`OMSTYPE;pauseoa[k;.enum`SEVERE;.enum`USERATTENTIONREQ;info];cxloasys[k;info]]]]; /子单被拒绝,当连续拒绝超过.db.Ts[.conf.algots][`MAXREJECT]时若OMS为恒生则主动暂停母单,若OMS为彭博则主动撤销母单(2012.03.26) ,string .db.O[y;`msg] 
 if[(.db.O[y;`status]=.enum[`CANCELED])&(0<nq:(-/).db.O[y;`qty`cumqty]);.db.O1[k;`sentqty]-:nq; /子单被撤单,20110428fix(将nq零股取整处理移置补单判断处)
    if[.db.O[y;`pending];nq1:roundqty[.db.O[y;`sym`side]] nq;
       if[(`OK~.ctrl.StateMap`EMS)&((null .db.O[y;`previd])|.db.O1[k;`end]|1b~.db.Ax[k;`alwayspeg])&(0<nq1)&(not violateoddlotrule[k;nq1])&(.db.O1[k;`cstatus]=.enum`NULL)&(.db.O1[k;`status] in .enum`NEW`PARTIALLY_FILLED);pnew:getordpx[.db.O[y;`sym];.db.O[y;`side];.db.O[y;`s2]];z:newso[k;`$(string .db.O[y;`ref]),"M";nq1;pnew;.db.O[y;`slot]];if[not null .db.O[z;`sym];.db.O[z;`previd]:y]];.db.O[y;`pending]:0b]; /追单(先撤单再补单)第二步:补单处理(为减轻系统压力，补单仍不成功的情形除拆单已结束外均不再继续补单，累积入下一拆单单元),如母单撤单则不追单(20110428)母单过期也不追单(20110627)零股除尾单外不追单(20120312)
 ];
 lqp:.db.O[y;`lastqty`lastpx];qp:.db.O1[k;`cumqty`avgpx];
 if[0<lqp[0];nq:qp[0]+lqp[0];ca:0f^((prd 0f^qp)+(prd 0f^lqp));ap:0f^ca%nq;lq:.db.O1[k;`qty]-nq;if[(`BB~.db.Ts[.conf.algots][`OMSTYPE])&(0f=roundqty[.db.O1[k;`sym`side]] lq);lq:0f];s:.enum[$[0f<lq;`PARTIALLY_FILLED;`FILLED]];
    .db.O1[k;`jn`ftime`cumqty`avgpx`cumamt`status`lastqty`lastpx]:(0i;now[];nq;ap;ca;s),lqp;execrptoa[k]; /当子单有成交时重置子单拒绝统计量,当买单零股不足100股时若开关IGNOREODDLOT打开则回完成(20120320)/直接回完成(20110506)
    if[not null bid:.db.O1[k;`upid];.db.O1[bid;`cumamt]:(0f^.db.O1[bid;`cumamt])+0f^$[.db.O1[k;`side]=.enum`BUY;1;-1]*prd lqp]; /2013.05.02
    if[(.db.O[y;`end])&(.db.O1[k;`cstatus]=.enum`NULL)&(not .db.O1[k;`suspend])&(ag in `ICEBERG`HUNTER);ag[k]];
 ]; /新成交,发母单执行报告,如子单已完成,根据算法类型有选择触发算法
 if[.db.O1[k;`pending]&(.db.O1[k;`sentqty]=.db.O1[k;`cumqty]);oacxlrpl[k]]; /大单撤单结束
 }; /[tid;oid]

checkems:{[]if[`ERROR~.ctrl.StateMap`EMS;:()];
 if[0W=mp:.db.Ts[.conf.algots]`MAXPENDING;:()];rl:mp^.db.Ts[.conf.algots]`RESUMELEVEL;np:exec count i from .db.O where id in key[.temp.hO],tsexec=.conf.algots,status="A";
 eb:0<exec count i from .db.O1 where id in key[.temp.hO],tsexec=.conf.algots,(cn>=1|.db.Ts[.conf.algots]`CXLCOUNT)|(qn>=1|.db.Ts[.conf.algots]`QRYCOUNT); /EMS not respond to order 
 if[(`OK~.ctrl.StateMap`EMS)&eb|(np>=mp);setstate[`EMS;`BUSY]];
 if[(`BUSY~.ctrl.StateMap`EMS)&(not eb)&(np<=rl);setstate[`EMS;`OK]];
 };

checkqs:{[x]t:`time$x;if[not max t within/: ((.db.Ts[.conf.algots]`ALARMQUOTELAG),0) +/: 0N 2#.conf.ex[`XSHG;`moo`mooend`openAM`closeAM`openPM`closePM];:()];tm:exec max time by fs2e each sym from .db.QX;ae:(t<.conf.ex[`XSHE;`moc])&(t-.conf.ex[`XSHE;`moo]|tm`XSHE)>.db.Ts[.conf.algots]`ALARMQUOTELAG;ag:(t-.conf.ex[`XSHG;`moo]|tm`XSHG)>.db.Ts[.conf.algots]`ALARMQUOTELAG;s:$[ae&ag;`QuoteStop;ae;`QuoteSZStop;ag;`QuoteSHStop;`OK];setstate[`QS;s];};

chkordexp:{[x;y]{[x]pa:.db.O1[.db.O[x;`upid];`price];p:.db.O[x;`price];sd:.db.O[x;`side];pn:getordpx[.db.O[x;`sym];sd;`AGGRESSIVE];if[((pa=p)&(0<pa))|((sd=.enum`BUY)&(pn<=p))|((sd=.enum`SELL)&(pn>=p));:()];.db.O[x;`ctime`pending`s1`s2]:(now[];1b;`peg;`AGGRESSIVE);cxlord x;} each exec id from .db.O where id in key[.temp.hO],tsexec=x,(status in .enum`PENDING_NEW`NEW`PARTIALLY_FILLED),((cstatus=.enum`NULL)&(not null expiretime)&(expiretime<y|rtime+.db.Ts[.conf.algots][`MINACKTOCXL]))|((cstatus in .enum`PENDING_CANCEL`REJECTED)&((ctime+`timespan$.db.Ts[.conf.algots]`CXLTMOUT)<y)&(cn<.db.Ts[.conf.algots]`CXLCOUNT));{[x;y]queryord x;.db.O[x;`qtime`qn]:(y;1i+0i^.db.O[x;`qn])}[;y] each exec id from .db.O where id in key[.temp.hO],tsexec=x,(((status=.enum[`PENDING_NEW])&((ntime+`timespan$.db.Ts[.conf.algots]`QRYTMOUT)<y))|((cstatus<>.enum[`NULL]&((ctime+`timespan$.db.Ts[.conf.algots]`QRYTMOUT)<y))))&((qtime+`timespan$.db.Ts[.conf.algots]`QRYTMOUT)<y)&(qn<.db.Ts[.conf.algots]`QRYCOUNT);}; /超时撤单处理,对限价母单且子单价格已为限价时不做撤单(20110428),对新订单未及时确认或撤单未及时拒绝且全部成交的可疑单发查询请求 

chkoaordexp:{[x;y]if[(`time$now[])>.db.Ts[.conf.algots]`EODTIME;{.db.O1[x;`end`status`msg]:(1b;.enum`DONE_FOR_DAY;"EODTimeReached");execrptoa[x];} each exec id from .db.O1 where status in .enum`NEW`PARTIALLY_FILLED];if[`BB~.db.Ts[.conf.algots]`OMSTYPE;:()];{.db.O1[x;`end`status`msg]:(1b;.enum`EXPIRED;"EndTimeReached");execrptoa[x];} each exec id from .db.O1 where status in .enum`NEW`PARTIALLY_FILLED,cstatus=.enum`NULL,cumqty=sentqty,{[x;y]if[0>=count y;:0b];z:"Z"$cfill y[0;`EndTime];(not null z)&(x>`time$z)}[`time$y] each para;}; /[]2012.03.26增加对Bloomberg OMS不回母单过期处理

algoapply:{[x;y]{[x;y]@[value .db.O1[x;`algo];x;()];.db.O1[x;`rtime`rn]:(y;1i+0i^.db.O1[x;`rn]);}[;y] each exec id from .db.O1 where not end,not suspend,not pending,not null algo,cstatus=.enum`NULL,status in .enum`NEW`PARTIALLY_FILLED;};

checkfuse:{[]if[(0>=fr:.db.Ts[.conf.algots]`FUSERATIO)|(0>=px:.db.QX[fs;`price])|(0>=pc:.db.QX[fs:.db.Ts[.conf.algots]`FUSESYM;`pc]);:()];if[px>=pc*1+fr;pauseoa[;.enum`SEVERE;.enum`MARKETMOVEMENT;`FUSE_BUY] each exec id from .db.O1 where status in .enum[`PENDING_NEW`NEW`PARTIALLY_FILLED],cstatus=.enum[`NULL],not suspend,side=.enum[`BUY]];if[px<=pc*1-fr;pauseoa[;.enum`SEVERE;.enum`MARKETMOVEMENT;`FUSE_SELL] each exec id from .db.O1 where status in .enum[`PENDING_NEW`NEW`PARTIALLY_FILLED],cstatus=.enum[`NULL],not suspend,side=.enum[`SELL]];}; /熔断检测,如果熔断对该方向上母单做暂停处理

ont_algo:{[x;y].db.Ts[x;`timertime]:y;if[(`time$y) within .conf.ex[`XSHG;`closeAM`openPM];:()];checkfuse[];checkqs[y];checkems[];if[not `OK~.ctrl.StateMap`EMS;:()];chkordexp[x;y];algoapply[x;y];chkoaordexp[x;y];}; /午休时段采用上交所午休区间

qtyadjust:{[x;y]if[not null a:.db.O1[x;`amt];if[0<>dq:.db.O1[x;`qty]-q:roundqty[.db.O1[x;`sym`side]] (0f^.db.O1[x;`cumqty])+(0|a-0f^.db.O1[x;`cumamt])%y;.db.O1[x;`qty]:q;:dq]];0}; /[母单ID;价格]对按金额委托动态调整委托数量

//isoutlimit:{[x]plim:.db.O1[x;`price];pmkt:getordpx[.db.O1[x;`sym];.db.O1[x;`side];`LEASTPASSIVE];(0<.db.O1[x;`price])&((.db.O1[x;`side]~.enum`BUY)&(pmkt>"e"$plim))|((.db.O1[x;`side]~.enum`SELL)&(pmkt<"e"$plim))}; /[母单ID]判断母单当前是否超出限价
//side;posefct;ts|(ts;acc);sym;qty;price;ref;exdict

//.upd[`NEWORDERSINGLE][];


newsubord:{[texp;pfix;upid;id;qty;price;slot]if[(qty<=0)|(price<0);lerr[`newsubord;(upid;`qtyorprice;`$"newsubord[",(string pfix),";",(string upid),";",(string id),";",(string qty),";",(string price),";",(string slot),"]";0)];:()];if[violateoddlotrule[upid;qty];lwarn[`newsubordcantsend;(upid;`oddlotmustsellallonce;.db.O1[upid;`side];(-/).db.O1[upid;`qty`cumqty];qty)];:()];if[.db.O1[upid;`typ] in .enum`LIMIT`STOP_LIMIT;plim:.db.O1[upid;`price];pmkt:getordpx[.db.O1[upid;`sym];.db.O1[upid;`side];`LEASTPASSIVE];if[((.db.O1[upid;`side]~.enum`BUY)&(price>plim))|((.db.O1[upid;`side]~.enum`SELL)&(price<plim));$[not pfix;price:plim;[linfo[`newsubordskip;(upid;`price_exceed_limit;.db.O1[upid;`side];price;plim;pmkt;pfix;qty;slot;id)];:()]]]];qtyadjust[upid;price];qty&:.db.O1[upid;`qty]-sq:0f^.db.O1[upid;`sentqty];.db.O1[upid;`sentqty]:qty+sq;k:newordex[.db.O1[upid;`side];.db.O1[upid;`posefct];.db.O1[upid;`ts];.db.O1[upid;`sym];qty;price;id;`acc1`tsexec`tif`typ`upid`slot`style`expiretime`ex`esym`cltid2`cltacc`handlinst`msg`stoppx`cltalt`cltsub!.db.O1[upid;`acc1`tsexec],($[slot<0;.db.O1[upid;`tif];.enum`DAY];$[slot<0;.db.O1[upid;`typ];$[price=0f;.enum`MARKET;.enum`LIMIT]];upid;slot;.db.O1[upid;`style];(`timestamp$(`date$now[])+{$[(x>.conf.ex[`XSHG;`closeAM])&(x<.conf.ex[`XSHG;`openPM]);x+(.conf.ex[`XSHG;`openPM])-.conf.ex[`XSHG;`closeAM];x]} (`time$now[])+`time$.db.Ts[.conf.algots][`DEFAULTTIMEOUT]^"T"$cfill .db.O1[upid;`para][0;`CxlTimeout])^texp;.db.O1[upid;`ex];.db.O1[upid;`esym];.db.O1[upid;`cltid2];.db.O1[upid;`cltacc];$[slot<0;.db.O1[upid;`handlinst];`];$[slot<0;`$cfill .db.O1[upid;`para][0;`Text];`];.db.O1[upid;`stoppx];.db.O1[upid;`cltalt];.db.O1[upid;`cltsub])];.temp.hO[k]:upid;k}; /创建新的小单:更新小单表,对柜台fix网关发NewOrderSingle.当母单有限价且子单报价超限时:若无报价只读限制则以限价报盘,否则放弃本次子单报盘. 2012.03.09去掉且限价在当前盘口有效(优于或等于本方最优价格)&(((.db.O1[upid;`side]~.enum`BUY)&(plim>=pmkt))|((.db.O1[upid;`side]~.enum`SELL)&(plim<=pmkt))) if[.db.O1[k;`typ]=.enum`LIMIT;plim:.db.O1[x;`price];if[((.db.O1[k;`side]=.enum`BUY)&())|((.db.O1[k;`side]=.enum`BUY)&());pnew:plim];if[ishidden[.db.O1[k;`sym];.db.O1[k;`side];pnew];:()]];

newso:newsubord[0Np;0b];newsofix:newsubord[0Np;1b];newsofixl:newsubord[0Wp;1b];

newsubordex:{[texp;pfix;upid;id;qty;price;slot;thre]fss:.db.O1[upid;`sym`side];thre:$[0<thre;roundqty[fss] thre;getqtymax[fss]];$[qty<=thre;newsubord[texp;pfix;upid;id;qty;price;slot];[n:-1+ceiling qty%thre;vl:(n#thre),qty-n*thre;{[texp;pfix;x;y;z;w]newsubord[texp;pfix;x;w 0;w 1;y;z]}[texp;pfix;upid;price;slot;] each ((`$((string id),"_"),/:string til n+1),'vl)]]}; //当委托数量超过上限时自动拆单 
newsox:newsubordex[0Np;0b];newsoxfix:newsubordex[0Np;1b];newsoxfixl:newsubordex[0Wp;1b];

cxloachildren:{[k]update pending:0b from `.db.O where upid=k,pending;cxlord each exec id from .db.O where id in key[.temp.hO],upid=k,status in "01A",cstatus=.enum[`NULL];}; //update pending:0b from `O where upid=k,pending

execrptoa:{[k].upd[`ExecRptAlgo][`sym`aid`id`cid`ordid`cordid`status`cstatus`suspend`cumqty`avgpx`lastqty`lastpx`cumamt`typ`qty`amt`price`msg`reason!.db.O1[k;`clt`acc`cltid`cltcid`ordid`cordid`status`cstatus`suspend`cumqty`avgpx`lastqty`lastpx`cumamt`typ`qty`amt`price`msg`reason]];};

rejectoa:{[x;y;z]if[null .db.O1[x;`sym];:()];.db.O1[x;`status`end`reason`msg]:(.enum`REJECTED;1b;y;z);execrptoa[x];};

alertoa:{[k;x;y;z]if[not `HS~.db.Ts[.conf.algots]`OMSTYPE;:()];.upd[`AlertRptAlgo][`sym`id`type`reason`msg!(.db.O1[k;`clt];.db.O1[k;`cltid];x;y;z)];}; /[upid;type(0 1 2 3!`None`Severe`Medium`Info);reason(1 2 3 4 5 6 7 8!`UserRequested`MarketMovement`NonAlgoSuitable`OtherCompliance`OnRecovery`EndTimeReached`UserAttentionReq`OnAlert);msg]

pauseoa:{[k;x;y;z]if[.db.O1[k;`suspend]|.db.O1[k;`pending]|.db.O1[k;`end];:()];.db.O1[k;`suspend`usrpause`msg]:(1b;.enum`PAUSE;z);.upd[`PauseRptAlgo][`sym`id`type`reason`msg!(.db.O1[k;`clt];.db.O1[k;`cltid];x;y;z)];};

cxloasys:{[k;t]if[.db.O1[k;`suspend]|.db.O1[k;`pending]|.db.O1[k;`end];:()];.upd[`CancelOrderAlgo][`clt`id`cid`msg!(.db.O1[k;`clt];.db.O1[k;`cltid];`;t)];};

cxlalloa:{[]cxloasys[;`manualcxlall] each exec id from .db.O1 where not end,status<>"2";};

rejectcxlrploa:{[src;id;cid;reason;msg;isrpl].upd[`CxlRejAlgo][`id`cid`cordid`reason`msg`isrpl!(id;cid;newid[];reason;forcestring msg;isrpl)];};

rejectcxloa:rejectcxlrploa[;;;;;0b];rejectrploa:rejectcxlrploa[;;;;;1b];

lastsubordpx:{[x]exec last price from .db.O where id in key[.temp.hO],upid=x,0<qty-0f^cumqty,cstatus=.enum[`NULL]}; /[upid]最新子单委托价格
lastsubordtime:{[x]`time$exec last ntime from .db.O where id in key[.temp.hO],upid=x}; /[upid]最新子单委托时间

newalgord:{[x;y;z;t;p;a;u;v]e:`;pe:$[2<count x;x[2];.enum`NULL];if[1<count x;e:x[1];x:x[0]];to:`;if[1<count a;to:a[0];a:a[1]];if[(p=0f)&(t=.enum`LIMIT);t:.enum`MARKET];.upd[`NewOrderAlgo][`src`id`ts`acc1`handlinst`execinst`sym`side`typ`qty`amt`price`algo`para`cltalt`cltsub`cltid2`cltacc`ex`sym`stoppx`posefct!(.conf.me;newid[];to;a;.enum`AUTOMATED_EXECUTION_ORDER_PUBLIC_BROKER_INTERVENTION_OK;e;x;y;t;z;0n;p;u;enlist v;`;`;`;`;fs2e x;fs2s x;$[t=.enum`STOP;p;0n];pe)];}; /[sym|(sym;execinst)|(sym;execinst;posefct);side;qty;ordtype;price;acc1|(tsorig;acc1);algo;parahash]

newalgolst:{[x;y;z;t;p;a;u;v].upd[`NewOrderAlgoList][`id`totalsize`algo`para`list!(newid[];-1+count x;u;enlist v;{[s;x;y;z;t;p;a]e:`;pe:$[2<count x;x[2];.enum`NULL];if[1<count x;e:x[1];x:x[0]];to:`;if[1<count a;to:a[0];a:a[1]];`src`id`ts`acc1`handlinst`execinst`sym`side`typ`qty`amt`price`cltalt`cltsub`cltid2`cltacc`ex`sym`slot`algo`para`stoppx`posefct!(.conf.me;newid[];to;a;.enum`AUTOMATED_EXECUTION_ORDER_PUBLIC_BROKER_INTERVENTION_OK;e;x;y;t;z;0n;p;`;`;`;`;fs2e x;fs2s x;s;`;();$[t=.enum`STOP;p;0n];pe)}'[til count x;x;y;z;t;p;a])];}; /[sym|(sym;execinst);side;qty;ordtype;price;acc;algo;para]

cxloalst:{[k;t]if[.db.O1[k;`suspend]|.db.O1[k;`pending]|.db.O1[k;`end];:()];.upd[`CancelOrderAlgoList][`clt`id`cid`msg!(.db.O1[k;`clt];.db.O1[k;`cltid];`;t)];};

execstat:{[isrt;x]r:$[isrt;.db.O1;.hdb.O1][x];st:(`time$r`ntime)|{$[null x;-0Wt;`time$x]}"Z"$cfill (r`para)[0;`StartTime];et:(`time$r`ftime)&{$[null x;0Wt;`time$x]}"Z"$cfill (r`para)[0;`EndTime];h:$[isrt;.ctrl.conn.rdb.h ({[x]value exec price,`time$time,cumqty,vwap*cumqty from quote where sym=x};r`sym);.ctrl.conn.hdb.h ({[d;s]value first select price,`time$time,cumqty,cumqty*vwap by sym from quote where date=d,sym=s};`date$r`ntime;r`sym)];lmp:r`price;f:$[0=lmp;0n<=;.enum[`BUY]=r`side;lmp>=;lmp<=];h:value exec t,sums q,sums a from (select p,t,deltas q,deltas a from flip `p`t`q`a!h) where f p;k:where (h 0) within (st,et);h1:0f^h[1 2;-1+k 0];hs:h1 0;ha:h1 1;h:h[;k];vwap:{x[;where x[1]>0]}(`int$`second$vtimex[fs2e r`sym;h 0];(h[2]-ha)%(h[1]-hs);(h[1]-hs)%(last h[1])-hs;h[1]-hs);trade:value exec `int$`second$(fs2e each sym) vtimex'`time$ftime,(sums cumqty*avgpx)%(sums cumqty),(sums cumqty)%sum cumqty from `ftime xasc select from $[isrt;.db.O;.hdb.O] where upid=x,cumqty>0f,ftime<=et;(vwap;trade;r`algo)}; /value first select price,time,cumqty,cumqty*vwap by fsym from HQ where (date=`date$r`ntime),(sym=r`sym)

mktvwap:{[isrt;x]d:execstat[isrt;x];0f^ffill last d[0;1]};
mktqty:{[isrt;x]d:execstat[isrt;x];0f^ffill last d[0;3]};
matchno:{[isrt;x]exec count i from $[isrt;.db.O;.hdb.O] where cumqty>0,upid=x};

oatbld:{[x;y;z]t:$[x;.db.O1;select from .hdb.O1 where (`date$ntime) within `date$(y,z)];update bias:0f^?[vwap=0;0f;?[side=.enum`BUY;1e4;-1e4]]*-1+avgpx%vwap from select id,hsid:cltid2,sym,algo,status,cstag:cstatus {y+2*x=.enum`PENDING_CANCEL}' suspend,side,qty,price,sentqty,cumqty,avgpx,leavesqty,string `datetime$ntime,string `second$ctime,string `second$ftime,pct:1-leavesqty%qty,vwap:`float$@[mktvwap[x];;0n] each id,mktqty:`float$@[mktqty[x];;0n] each id,mno:matchno[x] each id from update leavesqty:?[status in "01A";qty-cumqty;0f] from select from  t where extype<>`LIST}; 

subrejd:{[u;x;y;z]t:select from $[x;.db.O;select from .hdb.O where (`date$ntime) within (y,z)] where upid=u,status=.enum`REJECTED;select id,price,qty,ref,string `datetime$ntime,msg from t};

sublstd:{[u;x;y;z]t:select from $[x;.db.O;select from .hdb.O where (`date$ntime) within (y,z)] where upid=u;select id,status,price,qty,cumqty,avgpx,ref,string `datetime$ntime,string `time$ctime,string `time$ftime from t};

oaparad:{[u;x;y;z]t:select from $[x;.db.O1;select from .hdb.O1 where (`date$ntime) within (y,z)] where id=u;(first exec first para from t),exec first execinst,first msg from t};

oastatd:{[x;y;z;s]t:$[x;.db.O1;select from .hdb.O1 where (`date$ntime) within (y,z)];$[s=`STATUS;0!select v: count i by k:status from t;s=`ALGO;0!select v: count i by k:algo from t;0!select v:sum qty by k:algo from t]};

oaexecd:{[isrt;x;y]d:execstat[isrt;x];pm:last d[0;1];pr:first d[0;1];pa:last d[1;1];bp:$[$[isrt;.db.O1[x;`side];exec first side from .db.O1 where id=x]=.enum`BUY;1e4;-1e4]*-1+pa%pm,pr;`h`t!(`ArrivalPx`MktPx`AlgoPx`Cost0`Cost1!.math.r3 (pr,pm,pa,bp);update t:string `minute$`second$?[t<7200;09:30:00;11:00:00]+t from select from (0!(select .math.r3 last p0,.math.r3 last q0 by t:y xbar t from flip`t`p0`q0`q!d[0]) lj (select .math.r3 last p1,.math.r3 last q1 by t:y xbar t from flip`t`p1`q1!d[1])) where not null p1)};   

oadetaild:{[isrt;x;y]y:`long$y;toa:$[isrt;.db.O1;.hdb.O1];to:$[isrt;.db.O;.hdb.O];d0:`date$toa[x;`ntime];z:toa[x;`sym];tq:$[isrt;.ctrl.conn.rdb.h ({[x]select `time$time,bid,ask,cumqty from quote where sym=x};z);.ctrl.conn.hdb.h ({[d;s]select `time$time,bid,ask,cumqty from quote where date=d,sym=s};d0;z)];(update date:d0+`time$date from 0!select last bid,last ask,sum qty by date:y xbar `second$vtimex[`XSHG] time from (select time,bid,ask,qty:deltas cumqty from tq) where  0<bid&ask),\: update date:d0+`time$date from select cumqty wavg avgpx,sum cumqty by y xbar `second$date from select date:vtimex[`XSHG] `time$ftime,avgpx,cumqty from to where upid=x,cumqty>0,avgpx>0}; 

\
.db.Ts.algo:.enum.nulldict;
.db.Ts.algo[`active`acc`accx`stop`event]:(0b;`sim;`symbol$();0b;.enum.nulldict);
.db.Ts.algo.event[`timer`quote`exerpt`dayroll`sysinit`sysexit]:`ont_algo`onq_algo`ono_algo`onr_algo`oni_algo`one_algo;
.db.Ts.algo,:`CXLTMOUT`CXLCOUNT`DEFAULTTIMEOUT`NOETIMEOUT`MINACKTOCXL`DEFAULTSTYLE`SLICEFREQ`DICEFREQ`SAFESTYLE`SAFESLICEFREQ`SAFEDICEFREQ`CUTOFFSET`EODTIME`QRYTMOUT`QRYCOUNT`MAXPENDING`RESUMELEVEL`MAXREJECT`ALARMQUOTELAG`DICERANDN`DICERANDQ`DICERANDT`IMCOEF`OMSTYPE`GOAHEAD`MINAMT`FUSESYM`FUSERATIO`VwapModel!(00:02:00;3;00:00:05.000;00:01:00.000;00:00:03.000;`LEASTPASSIVE;1;6;`AGGRESSIVE;1;2;00:00:25.000;15:15:00.000;00:01:00.000;0N;0W;0N;0W;00:00:45.000;0f;0f;0f;0f;`;0;0f;`000300.XSHG;0f;`ma);


.db.Ax:.enum.nulldict;

.db.O1:(0#.db.O) uj ([`u#id:`symbol$()]pendingwait:`symbol$(); suspend:`boolean$(); usrpause:`char$(); rn:`int$(); jn:`int$(); amt:`float$(); sentqty:`float$(); style:`symbol$(); clt:`symbol$(); algo:`symbol$(); cltid:`symbol$(); cltcid:`symbol$(); handlinst:`char$(); execinst:`symbol$(); cltalt:`symbol$(); cltsub:`symbol$(); cltid2:`symbol$(); cltacc:`symbol$(); stoppx:`float$(); extype:`symbol$(); para:();  plan:(); snap:()); /AlgoOrder

.db.TASK[`loadhvpdb;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:30;1D;0;4;`loadhvpdb);

/
//volume profile update
volprof:{[]d0:first -10#date;d1:vtd[];HSSAM::0!select tr,size:100*size by sym,bucket from ungroup select tr:(deltas cumqty)%(last cumqty),bucket,size:deltas cumqty by date,sym from select last cumqty by date,sym,bucket from ungroup select date,sym,bucket:(fs2e each sym) time2bucketcn' `second$(fs2e each sym) vtimex'time,cumqty from HQ where date within (d0,d1);HSVP::`sym`bucket xkey ungroup select tr:tr%sum tr,bucket,size,trls:trls%sum trls,sizels by sym from select sym,bucket,tr:avg each tr,size:avg each size,trls:predls each tr,sizels:predls each size from HSSAM;update bucketstart:bucketstartcn bucket,bucketstop:bucketstopcn bucket from `HSVP;HSD::select avg size,avg spread,yield:avg -1+1_ratios price,stddev:sqrt var -1+1_ratios price by sym from select date,sym,size:last each cumqty,last each price,spread:{avg x where (x>0f)&(x<0w)}each (-1+o1px%b1px) from HQ where date within (d0,d1);savertbl each `HSSAM`HSVP`HSD;}; //hsvp:([sym;bucket(0~0W)]tr(日内相对换手);size(桶内平均成交股数);bucketstart(桶起始时刻);bucketstop(桶结束时刻)):分钟桶日内相对换手统计,hsd:计算平均日交易手数和买卖价差

vparma:{[x]d:"F"$ read0 `$":",tmpdir[],"arma.dat";HSVP::HSVP lj 2!flip `sym`bucket`trarma!(HSSAM`sym;HSSAM`bucket;d);savertbl `HSVP;}; //将arma模型预测结果导入

vprupd:{[]jcr("1!:44 '",tmpdir[],"'";"script 'c:/ia32/jtrader/qclient.ijs'";"load 'task'";"shell 'c:/bin/R/bin/R CMD BATCH c:/fix/src/modelrun.R c:/tmp/run.Rout'";"q=:conew 'cqclient'";"connect__q 'localhost';7777";"cmd__q 'vparma[]'";"exit ''")}; //生成ARMA预测模型结果
//pl (enlist til 240),/: enlist each value exec cumsize%max cumsize by date from (select last cumsize by date,`minute$vtimecs time from hq where date>=2008.01.01,sym=2600000) where 240=(count;i) fby date /察看历史完成度曲线

//web query functions
execstat:{[isrt;x]r:$[isrt;.db.O1[x];first select from .hdb.O1 where id=x];st:(`time$r`ntime)|{$[null x;-0Wt;`time$x]}"Z"$cfill (r`para)[0;`StartTime];et:(`time$r`ftime)&{$[null x;0Wt;`time$x]}"Z"$cfill (r`para)[0;`EndTime];h:$[isrt;Q[r`sym;`time`cumqty],enlist prd Q[r`sym;`cumqty`vwap];value first select time,cumqty,cumqty*vwap by sym from HQ where (date=`date$r`ntime),(sym=r`sym)];k:where (h 0) within (st,et);h1:0f^h[1 2;-1+k 0];hs:h1 0;ha:h1 1;h:h[;k];vwap:{x[;where x[1]>0]}(`int$`second$vtimex[fs2e r`sym;h 0];(h[2]-ha)%(h[1]-hs);(h[1]-hs)%(last h[1])-hs);trade:value exec `int$`second$(fs2e each sym) vtimex'`time$ftime,(sums cumqty*avgpx)%(sums cumqty),(sums cumqty)%sum cumqty from `ftime xasc $[isrt;O;HO] where upid=x,cumqty>0f;(vwap;trade;r`algo)}; //

algostat:{[isrt].tmp.AS::update bp:?[side="1";1e4;-1e-4]*-1+avgpx%vwap from select algo,sym,d0,`$string t0,`$string t1,id,side,avgpx,vwap:deltaamt%deltaqty from update deltaqty:k {y[x 1]-0f^y[x 0]}' cumqty,deltaamt:k {y[x 1]-0f^y[x 0]}' cumamt from update k:{{(-1+first x),last x}where x}each time within' (t0,'t1) from (select d0:`date$ntime,sym,side,algo,id,avgpx,t0:(`time$ntime)|{[x]{$[null x;-0Wt;`time$x]}"Z"$cfill x[0;`StartTime]} each para,t1:(`time$ftime)&{[x]{$[null x;0Wt;`time$x]}"Z"$cfill x[0;`EndTime]} each para from $[isrt;.db.O1;H.db.O1] where cumqty>0) lj (select first time,first cumqty,cumamt:first cumqty*vwap by d0:date,sym from $[isrt;update date:vtd[]&(last dtest) from Q where sym in exec distinct sym from .db.O1;select time,cumqty,vwap by date,sym from HQ where date in dtest,sym in syms]);};

getas:{[isrt;x;y;z]algostat[isrt];select from (update d0:`$string d0 from ({[x;y]$[null x;y;select from y where algo=x]}[x]) ({[x;y]$[null x;y;select from y where sym=x]}[y]) ({[x;y]$[null x;y;select from y where d0=x]}["D"$string z]) .tmp.AS) where not null vwap};


\
