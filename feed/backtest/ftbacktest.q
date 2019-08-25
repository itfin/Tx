.module.ftbacktest:2019.07.01;
txload "core/ftbase";

.ctrl[`btdate`bttime]:(0Nd;0Nt);
.hdb.O:0#.db.O;
now:{sum .ctrl`btdate`bttime};ntd:{.ctrl`btdate};
trddate:{`date$x};

autofill:{if[`ftbacktest<>.conf.feedtype;:()];{[k]x:.db.O[k];cq:x`qty;ap:x`price;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum`FILLED;cq;ap;`;`;.enum`NULL;`;`;0;"";"")];} each exec id from .db.O where not end;};

btadd:{[gid;sid;sver;p;c;s;D;f]k:newid[];.db.B[k;`gid`sid`sver`cp`cash`xsym`d0`d1`btyp`freq`addtime]:(gid;sid;sver;p;c;s;D[0];D[1];f[0];f[1];.z.P);k}; /[回测组id;策略id;策略版本;回测参数]创建新回测案例

btrun:{[bid].db.B[bid;`begintime]:.z.P;r:.db.B[bid];resetft[];initts[bid];.temp.bars:bars:0!hisbars[r`btyp;r`xsym;r`d0`d1;r`freq];.db.B[bid;`nday`nbar]:(exec count distinct bard from bars;count bars);if[0=count bars;:()];{.ctrl[`btdate`bttime]:(x`bard;`time$x`bart);.db.QX[.db.Ts[`bt;`xsym];`bid`ask]:x`low`high;(.db.Ts[`bt;`event;`barx])[`bt;x];autofill[];} each bars;btclosepos[`bt;last bars];.temp.date:asc exec distinct bard from bars;btstat[bid];.db.B[bid;`endtime]:.z.P;}; 

resetft:{[].db.P:0#.db.P;.db.O:0#.db.O;.db.M:0#.db.M;.temp.date:.ctrl.conn.hdb.h `date;cleartemp[];};

tofun:{$[count x;value "{[x;y]",x,"}";y]}
initts:{[bid]r:.db.B[bid];rs:.db.S[r`sid`sver];x:`bt;.db.Ts[x]:.enum.nulldict;.db.Ts[x;`active`acc`accx`stop`event]:(1b;`bt;`symbol$();0b;.enum.nulldict);.db.Ts[x;`event;`timer`quote`exerpt`match`dayroll`sysinit`sysexit`bar`barx]:(tofun[rs`timer;`];tofun[rs`quote;`];tofun[rs`exerpt;`];tofun[rs`match;`];tofun[rs`dayroll;`];tofun[rs`sysinit;`];tofun[rs`sysexit;`];tofun[rs`bar;`];tofun[rs`barx;`]);.db.Ts[x;`xsym]:s:r`xsym;.db.Ts[x;`Cp]:value $[count r`cp;r`cp;rs`cp];.db.Ts[x],:value rs`para;};

btclosepos:{[x;b]r:.db.Ts[x];y:r`xsym;q:netpos[x;y];if[0=abs[q];:()];($[q>0;limit_sell;limit_buy])[x;y;abs[q];$[q>0;b`low;b`high];`eobt];autofill[];};

btstat:{[x].temp.GT:`ti xasc select sym,ti,n,qty,enter,leave,ep,lp,netpnl:pnl+fee,pnl,fee,cash,hold:{[x;y;z](sesstotal[x]*(-/).temp.date?`date$y,z)+(-/)trdtime[x;y,z]}'[sym;leave;enter],delta:lp-ep,yield:1e2*pnl%cash from .temp.d:select from (select n:count i,sf:sum pmqty,max qty,enter:first ntime,leave:last ntime,ep:(neg first amt)%(first qty)*(getmultiple first sym),lp:(last amt)%(last qty)*(getmultiple first sym),pnl:sum amt,fee:sum fee,cash:max amt by sym,ti from ungroup select pmqty,qty,cumqty,price,ntime,amt:cumamt,fee:cumfee,ti:(sums {(not x)&-1_1b,x} 0=sums pmqty) by sym from update pmqty:?[.enum[`BUY]=side;1;-1]*cumqty from select from .db.O where cumqty>0) where n>1,0=sf;.temp.GTS:select n:count i,pnl:sum pnl,maxwin:max pnl,maxloss:min pnl,win:sum 0<pnl,loss:sum 0>pnl by sym from .temp.GT;pnl:exec sum `float$netpnl from .temp.GT;.db.B[x;`ntrd`pnl`yield`mdd`res]:(count[.temp.GT];pnl;pnl%.db.B[x;`cash];.math.mdd .db.B[x;`cash]+sums exec `float$netpnl from .temp.GT;`O`GT`GTS!(.db.O;.temp.GT;.temp.GTS))}; /[bid]

newalgo:{[x]y:(x[0];"J"$x[1]);if[not null .db.S[y;`pubdate];:`r`errmsg!(-1;"algo id exist.")];.db.S[y;`author`pubdate`class`updatetime`info]:(x[2];.z.D;x[3];.z.P;x[4]);`r`errmsg!(0;"")};



\

.db.S:([id:`symbol$();version:`long$()]expire:`boolean$();author:`symbol$();pubdate:`date$();class:`symbol$();updatetime:`timestamp$();timer:();quote:();exerpt:();match:();dayroll:();sysinit:();sysexit:();bar:();barx:();cp:();para:();info:()); /[策略信息表](策略ID;策略版本;作者;发布日期;策略类型;更新时间;定时器触发器;行情触发器;回报触发器;成交触发器;日期切换触发器;系统启动触发器;系统退出触发器;系统K线触发器;策略K线触发器;默认参数;备注)

.db.B:([id:`symbol$()]gid:`symbol$();sid:`symbol$();sver:`long$();cp:();cash:`float$();xsym:`symbol$();d0:`date$();d1:`date$();btyp:`symbol$();freq:`long$();addtime:`timestamp$();begintime:`timestamp$();endtime:`timestamp$();pnl:`float$();yield:`float$();mdd:`float$();nday:`long$();nbar:`long$();ntrd:`long$();res:()); /[回测案例表](回测ID;回测组ID;策略ID;策略版本;策略参数;初始资金;交易标的;回测开始日期;回测结束日期;回测K线类型(`D|`M);回测K线频率(日数或分钟数);回测创建时间;回测运行时间;回测结束时间;总损益;收益率;最大回撤;回测天数;回测K线数;交易次数;回测结果)

.db.S,:enlist (`emacross;1;0b;`test;.z.D;`trend;.z.P;"";"";"";"";"";"";"";"";"";"`N0`N1!5 15";"`HB`n`HV`ma0`ma1!(();0;();0f;0f)";"");

btadd[`;`emacross;1;"";1e6;`IC1907.CCFX;2019.06.01 2019.06.30;(`M;1)];

