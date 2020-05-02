.module.ftbacktest:2020.01.02;
txload "core/ftbase";

.hdb.O:0#.db.O;.hdb.M:0#.db.M;.hdb.P:0!0#update today:.z.D from .db.P;

.timer.ft:{[x];};
.roll.ft:{[x]{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`dayroll];x;y);()];}[;x] each tsl[];.hdb.M,:.db.M;delete from `.db.M;gtc:.enum`GOOD_TILL_CANCEL;.hdb.O,:select from .db.O where end|tif<>gtc;delete from `.db.O where end|tif<>gtc;delete from `.db.QT;{update `u#id from x;} each `.db.O`.db.M`.db.QT;delete from `.db.P where 0>=abs[0f^lqty]+abs[0f^sqty];update flqty:0f,fsqty:0f,lqty0:0f,sqty0:0f,flqty0:0f,fsqty0:0f from `.db.P;.hdb.P,:update today:.z.D from 0!.db.P;n:count[.db.QX];update pc:(0.5*(0f^bid)+0f^(ask))^price,price:0n,inf:0f,sup:0w,bid:0n,ask:0n,bsize:0n,asize:0n,cumqty:0f,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$() from `.db.QX;};

.ctrl[`btdate`bttime]:(0Nd;0Nt);
now:{sum .ctrl`btdate`bttime};ntd:{.ctrl`btdate};
trddate:{`date$x};

autofill:{if[`ftbacktest<>.conf.feedtype;:()];{[k]x:.db.O[k];cq:x`qty;ap:x`price;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum`FILLED;cq;ap;`;`;.enum`NULL;`;`;0;"";"")];} each exec id from .db.O where not end;};

simfill:{[x;y]t:`time$t0:x;{[t0;t;y;k]x:.db.O[k];s:x`sym;if[not istrading[t;s];:()];if[null .db.O[k;`rtime];.db.O[k;`rtime]:now[]];p:0f;n:0;$[.enum[`PENDING_CANCEL]=x`cstatus;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum[`CANCELED];x`cumqty;x`avgpx;`;`;.enum[`CANCELED];`;`;0;"";"")];[r:.db.QX[s];if[0>=r`price;r[`price]:avg r`bid`ask];if[(0>=r`cumqty)&(not fs2e[s] in `FOREX`METAL)&(not s like "SP*");:()];p0:x`price;p1:r`price;if[(((.enum[`BUY]=x`side)&p0>=$[0<r`ask;r`ask;0w])|((.enum[`SELL]=x`side)&p0<=r`bid)|(x[`typ]=.enum`MARKET));[px:$[.enum[`BUY]=x`side;p0&p1|r`ask;p0|p1&r`bid];lqty:(x`qty)-0f^x`cumqty;fqty:lqty&$[y;0w;r $[.enum[`BUY]=x`side;`asize;`bsize]];cq:fqty+0f^x`cumqty;ap:0f^(prd[x`cumqty`avgpx]+fqty*px)%cq;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum $[cq=x`qty;`FILLED;`PARTIALLY_FILLED];cq;ap;`;`;x`cstatus;`;`;0;"";"")]]]]];}[t0;t;y] each exec id from .db.O where not end,status in .enum`PENDING_NEW`NEW`PARTIALLY_FILLED;}; /[time;fullfill]

btadd:{[gid;sid;sver;p;c;s;D;f].temp.X:(gid;sid;sver;p;c;s;D;f);s:value "`",string s;k:newid[];t:f[0];.db.B[k;`gid`sid`sver`cp`para`cash`xsym`syms`d0`d1`btyp`freq`addtime]:(gid;sid;sver;p[0];p[1];c;$[t=`T;`;first s];$[t=`T;$[1<count s;s;enlist s];`symbol$()];D[0];D[1];f[0];f[1];.z.P);k}; /[回测组id;策略id;策略版本;回测参数]创建新回测案例

btrun:{[bid]if[`T=.db.B[bid;`btyp];:btrunticks[bid]];.db.B[bid;`begintime]:.z.P;r:.db.B[bid];resetft[];initts[bid];.temp.bars:bars:0!hisbars[r`btyp;r`xsym;r`d0`d1;r`freq];.db.B[bid;`nday`nbar]:(exec count distinct bard from bars;count bars);if[0=count bars;:()];{.ctrl[`btdate`bttime]:(x`bard;`time$x`bart);.db.QX[.db.Ts[`bt;`xsym];`bid`ask]:x`low`high;(.db.Ts[`bt;`event;`barx])[`bt;x];autofill[];} each bars;btclosepos[`bt;last bars];.temp.date:asc exec distinct bard from bars;.roll.ft[.ctrl.btdate+1];btstat[bid];.db.B[bid;`endtime]:.z.P;}; 

btrunticks:{[bid].db.B[bid;`begintime]:.z.P;r:.db.B[bid];resetft[];initts[bid];sl:r`syms;dl:r`d0`d1;tt:flip .db.Ts.bt.Cp[`TRDTIME];rt:(td:.ctrl.conn.tp.h[`.u.d]) within dl;.temp.quote:qq:update ticktime:srctime from `srctime xasc .ctrl.conn.hdb.h[({[x;y;z]$[0=count y;select from quote where date in x,any each (`time$time) within\:z,0<cumqty&bid&ask;select from quote where date within x,sym in y,any each (`time$time) within\:z,0<cumqty&bid&ask]};dl;sl;tt)],$[rt;.ctrl.conn.rdb.h[({[x;y]`date xcols update date:x from $[count[y];select from quote where sym in y,any each (`time$time) within\:z,0<cumqty&bid&ask;select from quote where any each (`time$time) within\:z,0<cumqty&bid&ask]};td;sl;tt)];()];.db.B[bid;`nday`nbar]:(exec count distinct date from qq;count qq);if[0=count qq;:()];.ctrl.btdate:dl[0]-1;{[x]x:flip .temp.x:x;r:x[0];d0:r`date;t:r`srctime;if[d0>.ctrl.btdate;.roll.ft[d0]];.ctrl[`btdate`bttime]:(d0;t);.db.QX:.db.QX uj 1!delete date from x;(.db.Ts[`bt;`event;`quote])[`bt;exec distinct sym from x];(.db.Ts[`bt;`event;`timer])[`bt;t];simfill[t;1b];} each `ticktime xgroup qq;btclose[`bt];.roll.ft[.ctrl.btdate+1];.temp.date:asc exec distinct date from qq;btstat[bid];.db.B[bid;`endtime]:.z.P;};

resetft:{[].hdb.P:0#.hdb.P;.db.P:0#.db.P;.hdb.O:.db.O:0#.db.O;.hdb.M:.db.M:0#.db.M;.db.LOG:0#.db.LOG;.temp.date:.ctrl.conn.hdb.h `date;cleartemp[];};

tofun:{$[count x;value "{[x;y]",x,"}";y]}
initts:{[bid]r:.db.B[bid];rs:.db.S[r`sid`sver];x:`bt;.db.Ts[x]:.enum.nulldict;.db.Ts[x;`active`acc`accx`stop`event]:(1b;`bt;`symbol$();0b;.enum.nulldict);.db.Ts[x;`event;`timer`quote`exerpt`match`dayroll`sysinit`sysexit`bar`barx]:(tofun[rs`timer;`];tofun[rs`quote;`];tofun[rs`exerpt;`];tofun[rs`match;`];tofun[rs`dayroll;`];tofun[rs`sysinit;`];tofun[rs`sysexit;`];tofun[rs`bar;`];tofun[rs`barx;`]);.db.Ts[x;`xsym]:s:r`xsym;.db.Ts[x;`Cp]:value $[count r`cp;r`cp;rs`cp];.db.Ts[x],:value $[count r`para;r`para;rs`para];};

btclosepos:{[x;b]r:.db.Ts[x];y:r`xsym;q:netpos[x;y];if[0=abs[q];:()];h:.db.QX[y];($[q>0;limit_sell;limit_buy])[x;y;abs[q];$[q>0;b`low;b`high];`eobt];autofill[];};

btclose:{[x]cxlall[`bt];simfill[now[];1b];{[s]if[0<lq:0f^.db.P[`bt`bt,s;`lqty];limit_sell[`bt;s;lq;.db.QX[s;`bid];`eot]];if[0>sq:0f^.db.P[`bt`bt,s;`sqty];limit_buy[`bt;s;neg[sq];.db.QX[s;`ask];`eot]];} each exec sym from .db.P where 0<lqty|neg[sqty];simfill[now[];1b];};

btstat:{[x].temp.GT:`ti xasc select sym,ti,n,qty,enter,leave,ep,lp,netpnl:pnl+fee,pnl,fee,cash,hold:{[x;y;z](sesstotal[x]*(-/).temp.date?`date$y,z)+(-/)trdtime[x;y,z]}'[sym;leave;enter],delta:lp-ep,yield:1e2*pnl%cash from .temp.d:select from (select n:count i,sf:sum pmqty,max qty,enter:first ntime,leave:last ntime,ep:(neg first amt)%(first qty)*(getmultiple first sym),lp:(last amt)%(last qty)*(getmultiple first sym),pnl:sum amt,fee:sum fee,cash:max amt by sym,ti from ungroup select pmqty,qty,cumqty,price,ntime,amt:cumamt,fee:cumfee,ti:(sums {(not x)&-1_1b,x} 0=sums pmqty) by sym from update pmqty:?[.enum[`BUY]=side;1;-1]*cumqty from select from .hdb.O where cumqty>0) where n>1,0=sf;.temp.GTS:select n:count i,pnl:sum pnl,maxwin:max pnl,maxloss:min pnl,win:sum 0<pnl,loss:sum 0>pnl by sym from .temp.GT;pnl:exec sum `float$netpnl from .temp.GT;.db.B[x;`ntrd`pnl`yield`mdd`res]:(count[.temp.GT];pnl;pnl%.db.B[x;`cash];.math.mdd .db.B[x;`cash]+sums exec `float$netpnl from .temp.GT;`O`GT`GTS!(.hdb.O;.temp.GT;.temp.GTS))}; /[bid]

newalgo:{[x]y:(x[0];"J"$x[1]);if[not null .db.S[y;`pubdate];:`r`errmsg!(-1;"algo id exist.")];.db.S[y;`author`pubdate`class`updatetime`info]:(x[2];.z.D;x[3];.z.P;x[4]);`r`errmsg!(0;"")};

\

.db.S:([id:`symbol$();version:`long$()]expire:`boolean$();author:`symbol$();pubdate:`date$();class:`symbol$();updatetime:`timestamp$();timer:();quote:();exerpt:();match:();dayroll:();sysinit:();sysexit:();bar:();barx:();cp:();para:();info:()); /[策略信息表](策略ID;策略版本;作者;发布日期;策略类型;更新时间;定时器触发器;行情触发器;回报触发器;成交触发器;日期切换触发器;系统启动触发器;系统退出触发器;系统K线触发器;策略K线触发器;默认参数;备注)

.db.B:([id:`symbol$()]gid:`symbol$();sid:`symbol$();sver:`long$();cp:();para:();cash:`float$();xsym:`symbol$();syms:();d0:`date$();d1:`date$();btyp:`symbol$();freq:`long$();addtime:`timestamp$();begintime:`timestamp$();endtime:`timestamp$();pnl:`float$();yield:`float$();mdd:`float$();nday:`long$();nbar:`long$();ntrd:`long$();res:()); /[回测案例表](回测ID;回测组ID;策略ID;策略版本;策略参数;交易参数;初始资金;交易标的(BAR回测);交易标的列表(TICK回测);回测开始日期;回测结束日期;回测K线类型(`D|`M);回测K线频率(日数或分钟数);回测创建时间;回测运行时间;回测结束时间;总损益;收益率;最大回撤;回测天数;回测K线数;交易次数;回测结果)

.db.S,:enlist (`emacross;1;0b;`test;.z.D;`trend;.z.P;"";"";"";"";"";"";"";"";"";"`N0`N1!5 15";"`HB`n`HV`ma0`ma1!(();0;();0f;0f)";"");

btadd[`;`emacross;1;"";1e6;`IC1907.CCFX;2019.06.01 2019.06.30;(`M;1)];


btadd[`;`gridx;1;"";1e6;`ni2002.XSGE`cu2002.XSGE`FG005.XZCE`eg2005.XDCE`MA005.XZCE;2019.12.26 2020.01.02;(`;0)];
