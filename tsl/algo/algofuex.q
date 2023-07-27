.module.tsalgofuex:2022.06.10; /算法交易期货修正

txload "tsl/algo/algobase";
txload "tsl/algo/algolib";

/对于期货品种.db.PD记载了交易时段信息,由tsl/tslib.q的pdstat函数负责更新,由core/ftbase.q里的getsess函数负责计算.trdtime可以将物理时间换算为合约的逻辑交易时间,sesstotal可以计算合约的日总交易时长

time2bucket:{[x;y]e:fs2e first x;$[e in `XSHE`XSHG`XHKG;time2bucket_stk[e;y];time2bucket_fut[x;y]]}; /[sym;srctime list]将物理时间折算为分钟桶号,开盘集合竞价桶号为0,收盘集合竞价桶号为0W,其他时间为分钟序号

time2bucket_stk:{[x;y]y:`second$y;cn:x in `XSHE`XSHG;y:(0|(y&$[cn;15:00;16:10])-13:00)+0|(y&$[cn;11:30;12:00])-09:30;?[y=00:00:00;0;?[y>$[cn;03:57:00;05:30:00];0W;1+`int$`minute$y]]}; /[sym;time]A股时间折算桶号:0,1,...,237,0W,港股时间折算桶号0,1,...,330,0W

time2bucket_fut:{[x;y]x:first x;y:trdtime[x] y;?[y=00:00:00;0;1+`int$`minute$y]}; /[sym;time]期货时间折算桶号:0,1,...,555

bucketnum:{[x]e:fs2e[x];$[e in `XSHE`XSHG;239;e in `XHKG;332;1+`int$`minute$sesstotal[x]]};

bucket2time:{[x;y]e:fs2e x;$[e in `XSHE`XSHG`XHKG;bucket2time_stk[e;y];bucket2time_fut[x;y]]}; /[sym;bucket]由桶号换算为物理起止时间

bucket2time_stk:{[x;y]cn:x in `XSHE`XSHG;$[y=0;$[cn;09:15:00.000 09:24:59.999;09:05:00.000 09:19:59.999];y=0W;$[cn;14:57:00.000 14:59:59.999;16:00:00.000 16:07:59.999];00:00:00.000 00:00:59.999+$[y<=$[cn;120;150];`time$09:30+y-1;`time$13:00+y-$[cn;121;151]]]}; /[ex;bucket] 股票换算

bucket2time_fut:{[x;y]s:trdsess[x];ns:s where .conf.dayendtime<s[;0];ds:neg[count[ns]]_s;s:ns,ds;b:1+0,-1_sums 1+`int$`minute$(-/)reverse flip s;$[y=0;00:00:00.000 00:04:00.000+$[count ns;20:55:00.000;08:55:00.000];[i:b bin y;00:00:00.000 00:00:59.999+s[i;0]+00:01*(y-b[i])]]}; /[sym;bucket] 期货换算

bucketstarttime:(')[first;bucket2time];bucketstoptime:(')[last;bucket2time];  /[sym;bucket] 

walltime:{[x;y]s:trdsess[x];ns:s where .conf.dayendtime<s[;0];ds:neg[count[ns]]_s;s:ns,ds;b:0,-1_sums 1+`int$`minute$(-/)reverse flip s;i:b bin c:`int$z:`minute$y;s[i;0]+(`minute$c-b[i])+y-z}; /[sym;timelist]将合约逻辑时间(连续交易的累计时间)转换为物理时间(挂钟时间)

algo_updhvpn:{[x;n]if[0>h:.ctrl.conn[`hdb;`h];:()];`.db.PD`.db.QX`.conf.ex`.conf.dayendtime`time2bucket`time2bucket_stk`time2bucket_fut`fs2e`fs2s`fs2se`trdtime`trdsess`isfut`assetclass ({[h;x;y]h (set;x;y);}[h])' (.db.PD;.db.QX;.conf.ex;.conf.dayendtime;time2bucket;time2bucket_stk;time2bucket_fut;fs2e;fs2s;fs2se;trdtime;trdsess;isfut;assetclass);L:h({[x;n]d1:x&max date;d0:{first ((neg x)&count y)#y}[n] date where date<=d1;t:ungroup select bucket:time2bucket[sym;time],cumqty,amt:cumqty*vwap,price,bid,ask by date,sym from quote where date within (d0,d1),0<cumqty&price;L:(ungroup delete from (select tr:(deltas cumqty)%(last cumqty),bucket,amt:deltas amt,yield:{0f,1_ x} deltas log price by date,sym from select last cumqty,last amt,last price by date,sym,bucket from t) where ({(15<=max deltas x except 0W)} each bucket)|(0.09<max each tr);select last amt,last price,spread:{avg x where (x>0f)&(x<0w)} (-1+ask%bid) by date,sym from t)};x;n);d:L[0];z:select sum yield by date,sym,bar:30 xbar 1000&bucket from d;u:exec distinct flip (date;bar) from z;a:exec 0f^((flip (date;bar))!yield)u by sym from z;.temp.HCOV:`syms`covm!(key a;8*.math.cvm value a);.temp.HSSAM:0!select tr,amt by sym,bucket from d;.temp.HSVP:delete buckettime from update `p#sym,bucketstart:first each buckettime,bucketstop:last each buckettime from update buckettime:bucket2time'[sym;bucket] from `sym`bucket xkey ungroup select tr:tr%sum tr,bucket,amt,trls:trls%sum trls,sizels by sym from select sym,bucket,tr:sym ({avg x#z,x#1%bucketnum[y]}[n])' tr,amt:avg each amt,trls:0f,sizels:0f from .temp.HSSAM;.temp.HSD:update `u#sym from select avg amt,avg spread,yield:avg -1+1_ratios price,stddev:sqrt var -1+1_ratios price by sym from 0!L[1];{sv[`;.conf.tempdb,x] set .temp[x];} each `HCOV`HSSAM`HSVP`HSD;};

tzoffset:{[o;x]{?[x>=24:00;x-24:00;?[x<00:00;x+24:00;x]]}`time$(o*01:00)+x}; /[timestamp array|time array]时区平移
t12:tz8to12:tzoffset[4]; /平移为东12时区时间以保证取时间分量单调
t8:tz12to8:tzoffset[-4]; /[timestamp array]还原为平移为东8时区时间

istradingx:{[x;s]if[not (z:fs2e s) in tkey .conf.ex;:0b];d:`date$x;d0:.db.ftdate0;d1:.db.ftdate;t:`time$x;t0:.conf.dayendtime;y:$[d1>d0+3;d=d1;d1=d0+3;(d=d1)|((d=d0)&(t>t0))|(d=d0+1)&(t<=02:30);d1=d0+1;(d=d1)|(t>t0);0b];if[not y;:y];any t within/:.conf.ex[z;`session]+\: -00:01 00:01}; /[timestamp;sym](长假[无夜盘];周一;周二~周五)

chkoaordexp:{[x;y]if[(t12 now[])>t12 .db.Ts[.conf.algots]`EODTIME;{.db.O1[x;`end`status`msg]:(1b;.enum`DONE_FOR_DAY;"EODTimeReached");execrptoa[x];} each exec id from .db.O1 where status in .enum`NEW`PARTIALLY_FILLED];if[`BB~.db.Ts[.conf.algots]`OMSTYPE;:()];{.db.O1[x;`end`status`msg]:(1b;.enum`EXPIRED;"EndTimeReached");execrptoa[x];} each exec id from .db.O1 where status in .enum`NEW`PARTIALLY_FILLED,cstatus=.enum`NULL,cumqty=sentqty,{[x;y]if[0>=count y;:0b];z:"P"$cfill y[0;`EndTime];(not null z)&(x>z)}[y] each para;}; /[]2012.03.26增加对Bloomberg OMS不回母单过期处理

execstat:{[isrt;x]r:$[isrt;.db.O1;.hdb.O1][x];st:(r`ntime)|{$[null x;-0Wp;x]}"P"$cfill (r`para)[0;`StartTime];et:(r`ftime)&{$[null x;0Wp;x]}"P"$cfill (r`para)[0;`EndTime];s:r`sym;h:$[isrt;.ctrl.conn.rdb.h ({[x]value exec price,`time$time,cumqty,vwap*cumqty from quote where sym=x};r`sym);.ctrl.conn.hdb.h ({[d;s]value first select price,`time$time,cumqty,cumqty*vwap by sym from quote where date=d,sym=s};`date$t12 r`ntime;s)];lmp:r`price;f:$[0>=lmp;0n<=;.enum[`BUY]=r`side;lmp>=;lmp<=];h:value exec t,sums q,sums a from (select p,t,deltas q,deltas a from flip `p`t`q`a!h) where f p;k:where t12[h 0] within t12[st,et];h1:0f^h[1 2;-1+k 0];hs:h1 0;ha:h1 1;h:h[;k];vwap:{x[;where x[1]>0]}(`int$`second$trdtime[s] h[0];(h[2]-ha)%(h[1]-hs)*$[`XZCE=fs2e r`sym;1f;getmultiple[r`sym]];(h[1]-hs)%(last h[1])-hs;h[1]-hs);trade:value exec `int$`second$trdtime[s] ftime,(sums cumqty*avgpx)%(sums cumqty),(sums cumqty)%sum cumqty from `ftime xasc select from $[isrt;.db.O;.hdb.O] where upid=x,cumqty>0f,ftime<=et;(vwap;trade;r`algo)}; /value first select price,time,cumqty,cumqty*vwap by fsym from HQ where (date=`date$r`ntime),(sym=r`sym)

oaexecd:{[isrt;x;y]d:execstat[isrt;x];pm:last d[0;1];pr:first d[0;1];pa:last d[1;1];bp:$[$[isrt;.db.O1[x;`side];exec first side from .db.O1 where id=x]=.enum`BUY;1e4;-1e4]*-1+pa%pm,pr;s:$[isrt;.db.O1[x;`sym];exec first sym from .db.O1 where id=x];`h`t!(`ArrivalPx`MktPx`AlgoPx`Cost0`Cost1!.math.r3 (pr,pm,pa,bp);update t:string `minute$walltime[s] `time$`second$ t from select from (0!(select .math.r3 last p0,.math.r3 last q0 by t:y xbar t from flip`t`p0`q0`q!d[0]) lj (select .math.r3 last p1,.math.r3 last q1 by t:y xbar t from flip`t`p1`q1!d[1])) where not null p1)};   

oadetaild:{[isrt;x;y]y:`long$y;toa:$[isrt;.db.O1;.hdb.O1];to:$[isrt;.db.O;.hdb.O];d0:`date$04:00+ toa[x;`ntime];z:toa[x;`sym];tq:$[isrt;.ctrl.conn.rdb.h ({[x]select `time$time,bid,ask,cumqty from quote where sym=x};z);.ctrl.conn.hdb.h ({[d;s]select `time$time,bid,ask,cumqty from quote where date=d,sym=s};d0;z)];(update datestr:string walltime[z] `time$date,date:d0+`time$date from 0!select last bid,last ask,sum qty by date:y xbar `second$trdtime[z] time from (select time,bid,ask,qty:deltas cumqty from tq) where  0<bid&ask),\: update date:d0+`time$date from select cumqty wavg avgpx,sum cumqty by y xbar `second$date from select date:trdtime[z] ftime,avgpx,cumqty from to where upid=x,cumqty>0,avgpx>0}; 



getbuckets:{[x;y;z]ap:`$cfill x[`para][0;`ExcludeAuctions];st:"P"$cfill x[`para][0;`StartTime];et:"P"$cfill x[`para][0;`EndTime];s:x[`sym];if[y&0=exec count i from .temp.HSVP where sym=s;ex:fs2e s;s:$[`XSHG~ex;`600000.XSHG;`XSHE~ex;`000001.XSHE;`000300.XSHG^exec first sym from .temp.HSVP where (fs2e each sym)=ex]];m:.db.Ts[.conf.algots][`SLICEFREQ]^"I"$cfill x[`para][0;`SliceFreq];api:$[(x[`algo] in ``IS)|ap=`$"1 4";();ap=`1;enlist 0W;ap=`4;enlist 0;0 0W];$[`ls=z;[d:select first bucketstart,last bucketstop,tr:sum trls by seq:1+m xbar i from select from .temp.HSVP where sym=s,bucket>0,bucket<0W;d,:select seq:bucket,bucketstart,bucketstop,tr:trls from .temp.HSVP where sym=s,bucket in api];`arma=z;[d:select first bucketstart,last bucketstop,tr:sum trarma by seq:1+m xbar i from select from .temp.HSVP where sym=s,bucket>0,bucket<0W;d,:select seq:bucket,bucketstart,bucketstop,tr:trarma from .temp.HSVP where sym=s,bucket in api];[d:select first bucketstart,last bucketstop,sum tr by seq:1+m xbar i from select from .temp.HSVP where sym=s,bucket>0,bucket<0W;d,:select seq:bucket,bucketstart,bucketstop,tr from .temp.HSVP where sym=s,bucket in api]];st:$[null st;-0Wp;st]|x[`ntime];et:$[null et;0Wt;et];t0:tz8to12[st];t1:tz8to12[et];value exec tz12to8 truestart,tr,tz12to8 truestop,seq,br from update tr:tr*br from update br:(truestop-truestart)%(b1-b0) from update truestart:t0|b0,truestop:t1&b1 from select from `b0 xasc (update b0:tz8to12 bucketstart,b1:tz8to12 bucketstop from d) where b1>t0,b0<t1}; /[.db.O1记录;TWAP类型标志;模型]如为上市首日新股，对TWAP/VOLPCT单历史交易分布用本市场其它股票代替(20110613)

diceplan:{[upid;x;y;z]u:.db.O1[upid;`sym`side];cutoff12:(tz8to12 last y[2])-(`time$.db.Ts[.conf.algots][`CUTOFFSET]^"T"$cfill .db.O1[upid;`para][0;`CutOffset]);m:?[{(x=0)|(x=0W)}y[3];1;1|`int$(1+ randsymm each (count y[4])#0f|1f&(ffill .db.Ts[.conf.algots]`DICERANDN)^"F"$cfill .db.O1[upid;`para][0;`DiceRandN])*(.db.Ts[.conf.algots][`DICEFREQ]^"I"$cfill .db.O1[upid;`para][0;`DiceFreq])*y[4]];x:roundv[u] (,/)x($[`EQU=z;{{y*x%sum y}[x] (y#x%y)*(1+randsymm each y#0f|1f&(ffill .db.Ts[.conf.algots]`DICERANDQ)^"F"$cfill .db.O1[z;`para][0;`DiceRandQ])}[;;upid];{x,(y-1)#0f}])'m;r:(,/)y[1]{y#x%y}'m;sl:flip raze (flip y[0 2]){x[0]+`time$((x[1]-x[0])%y)*(0f,'(0.5*1+ randsymm each y#0f|1f&(ffill .db.Ts[.conf.algots]`DICERANDT)^"F"$cfill .db.O1[z;`para][0;`DiceRandT]),'1f)+til y}[;;upid]'m;t:tz12to8 cutoff12&tz8to12 sl[1];if[count t;t[0]:y[0;0]];s:raze m#'y[3];(t;x;r;s;sl[0];sl[2])}; /[upid;vl;d;算法],d:(bucket实际开始时间;bucket实际权重;bucket实际结束时间;bucket序号;bucket完整度权重),m:每bucket拆分笔数,x:每笔实际委托量,r:每笔子单时间片历史权重,t:每笔子单计划下单时间,s:bucket序号;slice起始时间;slice结束时间

intradayvol:{[x;y;z]if[0>=r:.ctrl.conn.rdb.h;:0n];r ({[x;y;z](exec last cumqty from quote where sym=x,t12[`time$time]<=t12[z])-0f^exec last cumqty from quote where sym=x,t12[`time$time]<=t12[y]};x;y;z)}; /[fsym;starttime;endtime]取当日区间成交量

intradayvolpx:{[x;y;z;u;v]if[0>=r:.ctrl.conn.rdb.h;:0n];d:update q:deltas q from r({[x;y]select t:`time$time,q:cumqty,p:price from quote where sym=x,t12[`time$time] within t12[y]};x;(y,z));$[u="1";exec sum q from d where p<=v;exec sum q from d where p>=v]}; /[sym;starttime;endtime;side;px]取当日区间限价内成交量

intradayvwap:{[x;y;z]if[0>=r:.ctrl.conn.rdb.h;:0n];h:value r({exec `time$time,cumqty,vwap from quote where sym=x};x);k:where t12[h[0]] within t12[(y,z)];$[count k;((0e^prd h[1 2;last k])-(0e^prd h[1 2;-1+first k]))%((0e^h[1;last k])-(0e^h[1;-1+first k]));0n]}; /[sym;starttime;endtime]取当日区间内成交均价

dvolpred:{[x]y:.temp.HSD[x;`amt]%get_last_price[x];if[0>=r:.ctrl.conn.rdb.h;:y];fb:value exec max bucketstop,sum tr from .temp.HSVP where sym=x,t12[bucketstop]<=t12[now[]];z:r({[x;y]exec last cumqty from quote where t12[(`time$time)]<=t12[y],sym=x};x;fb[0]);$[0<z;z%fb[1];y]}; /[sym]全日成交量预测 

/[upid]执行计划处理:对到时的子任务bin根据报价策略和流控因子生成小单进行处理(超时的小单系统会自动进行撤单再追单1次,如追单不成功则计入下一子任务)
execplan:{[x]
 if[0=n:count .db.O1[x;`plan][0];:()]; /无计划可供执行,退出
 s:.db.O1[x;`sym];ag:.db.O1[x;`algo];
 t:`time$dt:now[];if[not istradingx[dt;s];:()]; /当前非交易时段
 i:.db.O1[x;`snap][0]; /当前计划待处理bin下标
 if[(nf:i<count .db.O1[x;`plan][0])&(.db.O1[x;`plan][0;i]>t);:()]; /未到拆单时刻,退出 if[(0<i&.db.Ts[.conf.algots]`GOAHEAD)&(ag<>`VOLPCT);goahead[x;i]];
 if[(i=0)&(0<getgoahead[x])&(ag<>`VOLPCT);goahead[x;1]];
 sd:.db.O1[x;`side];lp:.db.O1[x;`price];if[0=0f^p:getordpx[s;sd;$[.db.O1[x;`plan][3;i] in 0N 0 0W;`MOSTAGGRESSIVE;$[ag~`VOLPCT;`LEASTAGGRESSIVE;.db.O1[x;`style]]^`$cfill .db.O1[x;`para][0;`ChildStyle]]];if[not 1b~.db.Ax[x;`AlerNulltPrice];alertoa[x;.enum`INFO;.enum`USERATTENTIONREQ;`PriceNotAvail];.db.Ax[x;`AlerNulltPrice]:1b];:()]; /取不到行情价格,告警后退出
 qtyadjust[x;p];planadjust[x];
 psp:getordpx[s;sd;`LEASTPASSIVE];if[(0<lp)&(0>=pxcmp[sd;lp;psp])&(not ag in `VOLPCT);limitadjust[x]]; /2011.09.22增加限价单超限调整 
 if[.db.O1[x;`cumqty]>.db.O1[x;`qty]-$[sd=.enum`SELL;1f;getqtymin[.db.O1[x;`sym`side]]];.db.O1[x;`end]:1b;:()];  /无单可拆,退出
 /imadjust[x]; /add AIM/PIM adjusting enhencement to gaming VWAP benchmark(20110701)
 sq:0f^.db.O1[x;`sentqty]; /母单总共已发委托
 cq:sq-.db.O1[x;`snap][1]; /母单在当前计划已发委托(.db.O1[x;`snap][1]为改单原始发单量)
 pr:$[ag in `VWAP`TWAP`VOLPCT;"F"$string `$cfill .db.O1[x;`para][0;`ParticipationRate];0f]; /参与率流控因子

 vm:$[pr<=0;0w; /无流控
 1e-2*pr*$[0=i;(.temp.HSD[s;`amt]%get_last_price[s])*.db.O1[x;`plan][2;0]; /i=0(计划未开始)时,用历史成交均量*i桶历史日内相对换手作为当日前i桶成交量预测
 	  nf;(1+.db.O1[x;`plan][2;i]% sum .db.O1[x;`plan][2;til i])*$[(0<.db.O1[x;`price])&(not "A"~cfill .db.O1[x;`para][0;`ReferenceVolume]);intradayvolpx[;;;sd;lp];intradayvol][.db.O1[x;`sym];.db.O1[x;`plan][4;0];.db.O1[x;`plan][4;i]]; /计划执行中
          $[(0<.db.O1[x;`price])&(not "A"~cfill .db.O1[x;`para][0;`ReferenceVolume]);intradayvolpx[;;;sd;.db.O1[x;`price]];intradayvol][.db.O1[x;`sym];(`time$.db.O1[x;`ntime])^`time$"Z"$cfill .db.O1[x;`para][0;`StartTime];(.conf.ex[fs2e .db.O1[x;`sym];`closePM])^`time$"Z"$cfill .db.O1[x;`para][0;`EndTime]] /        
	] /i>0时,用前i-1桶总成交量*(前i桶历史日内相对换手)%(前i-1桶历史日内相对换手)作为当日前i桶成交量预测
 ];
 v:0|$[nf; /计划尚未拆完,处理当前bin
 ((sum .db.O1[x;`plan][1;til 1+i+$[ag~`VOLPCT;0;getgoahead[x]]])&vm)-cq; /根据计划/流控/已发单量计算待发单量 /while[i+1<count .db.O1[x;`plan][0];if[.db.O1[x;`plan][0;i+1]>t;i:i+1]];
 (.db.O1[x;`qty]&vm)-sq /计划已拆完,处理已撤未补的尾单 
 ]; /完成对待下单量的计算

 
 if[(0<lp)&(0>=pxcmp[sd;lp;psp]);v&:0|("F"$string `$cfill .db.O1[x;`para][0;`MaxShow])-(.db.O1[x;`sentqty]-.db.O1[x;`cumqty])];
 if[0<cpr:"F"$string `$cfill .db.O1[x;`para][0;`MaxChildVolPct];rv:`$cfill .db.O1[x;`para][0;`RefChildVol];v&:1e-2*cpr*bookrefsize[s;sd;rv]];
 if[not null bid:.db.O1[x;`upid];if[0<ma:0f^"F"$cfill .db.O1[bid;`para][0;$[sd=.enum`BUY;`MaxBuy;`MaxSell]];v&:0f|(ma-0f^$[sd=.enum`BUY;1;-1]*.db.O1[bid;`cumamt])%p]]; /2013.05.02
 v:$[(sd=.enum`SELL)&(((-/).db.O1[x;`qty`cumqty])<getqtymin[(s;sd)]);{floor x+1e-2};roundqty[(s;sd)]] v;

 if[(v>0)&(not violateoddlotrule[x;v])&(not violateminamtrule[x;v;p]);newsox[x;(`$(string x),"_",(string i),"_",(string newid[]));v;p;i;(getqtymax[s,sd])&{$[x>0;x;0w]} 0f^"F"$string `$cfill .db.O1[x;`para][0;`MaxChildVol]]]; /下单,零股卖出除尾单外不下单(20120312)
 if[nf;.db.O1[x;`snap]:((i+1),1_.db.O1[x;`snap])]; /推进到下一计划bin
 if[(i>0)&(0<getgoahead[x])&(ag<>`VOLPCT);goahead[x;i+1]];
 }; 


ICEBERG:{[x]if[(10#cfill pt:.db.O1[x;`para][0;`Text])~"[strategy]";if[not ()~e:applyparatx[x;10_pt];rejectoa[x;.enum`BROKER_OPTION;`$e,":",pt]];:()];chktext[x];if[.db.O1[x;`typ] in .enum`STOP`STOP_LIMIT;:rejectoa[x;.enum`BROKER_OPTION;`StopOrderUnSupport]];if[0>=p:"F"$string `$cfill .db.O1[x;`para][0;`ReferencePrice];rejectoa[x;.enum`BROKER_OPTION;`Invalid_ReferencePrice];:()];if[0>=ds:roundqty[.db.O1[x;`sym`side]] 0f^"F"$string `$cfill .db.O1[x;`para][0;`DisplaySize];rejectoa[x;.enum`BROKER_OPTION;`Invalid_DisplaySize];:()];fs:.db.O1[x;`sym];sd:.db.O1[x;`side];if[(.db.O1[x;`typ]~.enum`LIMIT)&(0<pxcmp[sd;p;.db.O1[x;`price]]);rejectoa[x;.enum`BROKER_OPTION;`PriceBetterThanReferencePrice];:()];t:now[];if[t<"P"$cfill .db.O1[x;`para][0;`StartTime];:()];if[t>0Wt^"P"$cfill .db.O1[x;`para][0;`EndTime];.db.O1[x;`end]:1b;:()];if[not istradingx[t;fs];:()];ei:`M^.db.O1[x;`execinst];if[0=0f^px:getordpx[fs;sd;$[ei in `R`T;`LEASTPASSIVE;ei in `P`6;`LEASTAGGRESSIVE;`NEUTRAL]];:()];if[(`6=ei)&0<=pxcmp[sd;p;px];:()];if[.db.O1[x;`sentqty]>.db.O1[x;`cumqty];if[(ei in `R`P)&(0>pxcmp[sd;pl;px])&(0<pl:lastsubordpx[x]);cxloachildren[x]];:()];if[ei in `M`R`P`T;p:$[.db.O1[x;`side]=.enum`BUY;p &;p |] px];qtyadjust[x;p];sq:0f^.db.O1[x;`sentqty];if[.db.O1[x;`cumqty]>.db.O1[x;`qty]-getqtymin[.db.O1[x;`sym`side]];.db.O1[x;`end]:1b;:()];lq:roundqty[.db.O1[x;`sym`side]] .db.O1[x;`qty]-sq;k:.db.QX[.db.O1[x;`sym];`cumqty];if[0>=k;:()];v:roundqty[.db.O1[x;`sym`side]] lq&ds*(1+randsymm 0f|1f&ffill .db.Ts[.conf.algots]`DICERANDQ);if[v>0;j:$[()~.db.O1[x;`snap];0;.db.O1[x;`snap][0]];thre:(getqtymax[fs,sd])&{$[x>0;x;0w]} 0f^"F"$string `$cfill .db.O1[x;`para][0;`MaxChildVol];newsoxfixl[x;`$(string x),"_",(string j),"_",(string newid[]);v;p;j;thre];.db.O1[x;`snap]:(j+1;k;v)];}; /update expiretime:0Np from `O where upid=x,slot=j lfupd[`O;((=;`upid;enlist x);(=;`slot;j));0b;(enlist `expiretime)!enlist 0Np];

\
newalgord[(`ag2212.XSGE;`;.enum`OPEN);.enum`BUY;1000f;.enum`MARKET;0f;`8515_twap`99008890.9900889022;`TWAP;`StartTime`EndTime!string 2022.06.09 2022.06.10+21:00 15:00];
newalgord[(`ag2212.XSGE;`;.enum`OPEN);.enum`BUY;1000f;.enum`MARKET;0f;`8515_twap`99008890.9900889022;`VWAP;`StartTime`EndTime!string 2022.06.09 2022.06.10+21:00 15:00];
newalgord[(`ag2212.XSGE;`;.enum`OPEN);.enum`BUY;1000f;.enum`MARKET;0f;`8515_twap`99008890.9900889022;`IS;`StartTime`EndTime!string 2022.06.09 2022.06.10+21:00 15:00];
newalgord[(`ag2212.XSGE;`;.enum`OPEN);.enum`BUY;1000f;.enum`MARKET;0f;`8515_twap`99008890.9900889022;`VOLPCT;`ParticipationRate`StartTime`EndTime!string 3,2022.06.09 2022.06.10+21:00 15:00];
newalgord[(`ag2212.XSGE;`;.enum`OPEN);.enum`BUY;1000f;.enum`MARKET;0f;`8515_twap`99008890.9900889022;`ICEBERG;`DisplaySize`ReferencePrice`StartTime`EndTime!string 8,4747,2022.06.09 2022.06.10+21:00 15:00];