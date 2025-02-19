//tslib.q:标准化的策略组件函数或辅助函数

.module.tslib:2024.11.14;

//libpeg:自动撤补单功能,要求策略存在参数.db.Ts[x;`Cp;TRDTIME`tmout`tmout1`tmout2`urge`lmtref`lmtpct`pegrej`rejpegmax]:(交易时段列表;委托超时撤单时间间隔;补单时间间隔1(超过则至少urge=1);补单时间间隔2(超过则至少urge=2);紧急程度{0W;打对手涨跌停价;[3,n]:打对手盘口+[1,n-2]跳,2:打对手盘口,1:本方盘口+1跳;0:挂本方盘口};保护基准价;保护比例)
//在策略的ont事件中调用oexpire_libpeg,ono事件中调用opeg_libpeg,策略下单后对oid调用pegord_libpeg

pegord_libpeg:{[x].db.O[x;`special]:`PEG;x}; /[oid]

ordpxex_libpeg:{[x;y;z;w]pu:pxunit[y];pb:.db.QX[y;`bid];pa:.db.QX[y;`ask];ps:.db.QX[y;`sup];pi:.db.QX[y;`inf];b:z=.enum`BUY;$[0W=w;$[b;ps;pi];2<w;$[b;ps&pa+pu*(w-2);pi|pb-pu*(w-2)];2~w;$[b;pa;pb];1~w;roundpx[y;z;$[b;pb+pu;pa-pu]];$[b;pb;pa]]}; /[tid;sym;side;urge]计算补单价格

oexpire_libpeg:{[x;y]if[not any (`time$y) within/:.db.Ts[x;`Cp;`TRDTIME];:()];cxlord each exec id from .db.O where x=ts^tsexec,not end,special=`PEG,.db.Ts[x;`Cp;`tmout]<y-ntime;}; /[tid;.z.P]对超时委托进行撤单

opeg_libpeg:{[x;y]r:.db.O[y];cp:.db.Ts[x;`Cp];if[((.enum[`CANCELED]=r[`status])|(.enum[`REJECTED]=r[`status])&(1b~cp`pegrej)&(r[`slot]<0W^jfill cp`rejpegmax))&(`PEG=r[`special]);s:r[`sym];sd:r[`side];z:r`origid;w:cp[`urge];acc:r`acc;ts:r`ts;te:r`tsexec;k:limit_order[sd;$[acc=.db.Ts[ts;`acc];0N;.db.Ts[r`ts;`accx]?acc];$[null te;ts;ts,te];s;roundqty[(s;sd);r[`qty]-r[`cumqty]];ordpxex_libpeg[x;s;sd;$[(null z)|(.z.P<.db.O[z;`ntime]+cp[`tmout1]);w;.z.P<.db.O[z;`ntime]+cp[`tmout2];1|w;2|w]];r[`ref]];{[x;y;r].db.O[x;`special`origid`slot]:(`PEG;y^r`origid;1+0^r`slot)}[;y;r] each k];};  /[tid;oid]对需要补单的撤单委托进行补单操作

peg_buy:(')[pegord_libpeg';limit_buy];peg_sell:(')[pegord_libpeg';limit_sell];


//libbar:自动根据策略订阅的Bar频率将系统Bar合成为策略需要的n周期bar后再回调策略的barx事件,要求策略存在标的代码.db.Ts[x;xsym]控制参数.db.Ts[x;`Cp;barfreq]和缓存区.db.Ts[x;`BBUF]:()
//在策略的event中bar事件触发器设置为onb_libbar,另外设置barx时间触发器为策略逻辑
onb_libbar:{[x;b].temp.b:b;r:.db.Ts[x];y:r`xsym;sess:trdsess[y];t:b`t;if[not any t within/:sess;:()];bf:b`freq;sf:`long$`second$r[`Cp;`barfreq];bx:r[`event;`barx];if[sf<=bf;:(bx)[x;b]];n:sf div bf;bt:xbar[sf] t;if[n1:count r`BBUF;if[count[r`BBUF]&bt>xbar[sf] (last r`BBUF)`t;(bx)[x;synbar_libbar[x]]]];.db.Ts[x;`BBUF],:enlist b;if[n<=n1+1;(bx)[x;synbar_libbar[x]]];}; /[tid;bar]

synbar_libbar:{[x]b:exec last time,first sym,freq:`second$.db.Ts[x;`Cp;`barfreq],first d,first t,first o,max h,min l,last c,sum v,sum a,last p,last src,last srctime,last srcseq,last dsttime from .db.Ts[x;`BBUF];.db.Ts[x;`BBUF]:0#.db.Ts[x;`BBUF];b}; /[tid]

//libext:外接委托指令日终清除在kdb内的持仓(因不准确)
onr_libext:{[x;y]delete from `.db.P where ts=x;}; /[tid;z.D]

//libtask:定时委托条件单任务触发器
//.db.ORDTASK:([id:`symbol$()]expire:`boolean$();ts:`symbol$();sym:`symbol$();side:`char$();qty:`float$();price:`float$();datemin:`date$();datemax:`date$();timemin:`time$();timemax:`time$();condfun:();lastrun:());
//.db.TASK[`ORDTASK;`firetime`firefreq`weekmin`weekmax`handler]:(.z.D+`second$.z.T;0D00:00:01;0;4;`ordtimer_libtask);
ordcheck_libtask:{[x]m:`$"libtask_",string[x];r:.db.ORDTASK[x];d:vtd[];t:.z.T;y:r`ts;z:r`sym;w:r`side;q:r`qty;h:.db.QX[z];p:r`price;p:$[p in 0 0n;h $[w=.enum`BUY;`ask;`bid];p=-0w;h`inf;p=0w;h`sup;p];if[(d<r`datemin)|((d>d1)&not null d1:r`datemax)|(t<r`timemin)|((t>t1)&not null t1:r`timemax)|(0>=q)|(p<h`inf)|(p>h`sup)|0<exec count i from .db.O where ref=m;:()];if[not ()~cf:r`condfun;if[not 1b~cf[y;z];:()]];if[not any t within/:trdsess[z];:()];k:limit_order[w;0N;y;z;q;p;m];.db.ORDTASK[x;`lastrun]:(now[];k);if[(null d1)|d>=d1;.db.ORDTASK[x;`expire]:1b];};
ordtimer_libtask:{[x;y]ordcheck_libtask each exec id from .db.ORDTASK where not expire;1b};



//tsstat:从委托表将开平仓组合为交易并进行盈亏统计

pdstat:{[x].temp.t0:(.ctrl.conn.hdb.h "select cumamt:last cumqty*price,last price,last openint by sym from quote where date=last date,cumqty>0,src=`fqctp") lj 1!.ctrl.conn.hdb.h "{select sym,15 xbar dend+00:10,nend:15 xbar 00:10+nend0^nend1 from (select sym,dend:time from x where sess=09:00) lj (1!select sym,nend0:time from x where sess=21:00) lj  (1!select sym,nend1:time from x where sess=00:00)} select from (select last `minute$time by sym,sess:(`s#{x!x}`s#00:00 04:00 09:00 16:00 21:00 24:00) `minute$time from quote where date=last date,src=`fqctp,cumqty>(prev;cumqty) fby sym,bid>0,ask>0) where sess in 00:00 09:00 21:00";.temp.t1:(select last multiplier,last product,last ex,last pxunit,last rmarginl,last rfeetaxoa,last rfeetaxoq,last name by sym from .db.QX where not null product,1<=multiplier) lj (select sp:last product by `${[x]y:3_x;(floor(count[y]-1)%2)#y} each string product from .db.QX where not null product,sym like "SP *"),select sp:last product by `${[x]y:4_x;(floor(count[y]-1)%2)#y} each string product from .db.QX where not null product,sym like "SPD *";.temp.t2:.temp.t0 uj .temp.t1;t:0!.db.PD:update feeunit:2*fee%pxunit*multiplier,sess:getsess\'[ex;dend;nend] from update sumpct:sums amtpct,rmarginl*1e2,margin:rmarginl*size,fee:rfeetaxoq+rfeetaxoa*size,feebp:1e4*(rfeetaxoa+rfeetaxoq%size) from update amtpct:1e2*cumamt%sum cumamt,seq:i+1,size:price*multiplier,bpunit:1e4*pxunit%price from desc (select sum cumamt*multiplier*1e-8,last ex,last sp,last multiplier,last pxunit by product from .temp.t2) lj select last sym,last price,last rmarginl,last rfeetaxoa,last rfeetaxoq,last name,last dend,last nend by product from .temp.t2 where openint=(max;openint) fby product;};

holdtime:{[x;y;z]w:trddatetime[x] y,z;d:`date$w;$[d[0]=d[1];0D-(-/)`timespan$w;1D*-1+difftrdate[d 1;d 0]]}; /[sym;enter;leave]计算持仓区间长度  

tsstat:{[x;y]d0:y[0];d1:y[1];td:vtd[];.temp.date:(.ctrl.conn.hdb.h `date),vtd[];.temp.t:update ti0:sums {(not x)&-1_1b,x} 0=sums q0,ti1:sums {(not x)&-1_1b,x} 0=sums q1 by ts,sym from update q0:?[not eot;pmqty;?[(0=mod[gi;2])&(0=spmqty);0f;pmqty-spmqty]],q1:?[not eot;0f;?[(0=mod[gi;2])&(0=spmqty);pmqty;spmqty]] from update gi:({$[y=0;0;x+1]}\)[0;eot] by ts,sym from update eot:(spmqty=0)|(-1=signum[spmqty]*signum[spmqty^prev spmqty]) by ts,sym from update spmqty:sums pmqty by ts,sym from update pmqty:?[.enum[`BUY]=side;1;-1]*cumqty from (select from .hdb.O where ts in x,cumqty>0,(`date$ftime) within y),select from .db.O where ts in x,cumqty>0,(`date$ftime) within y;.temp.GT:`enter xasc select ts,sym,ti,n,cumqty,enter,leave,ep,lp,netpnl:pnl+fee,pnl,fee,cash,hold:holdtime'[sym;enter;leave],delta:lp-ep,yield:1e2*pnl%cash,ref,j1 from select from (select n:count i,sf:sum pmqty,max cumqty,enter:first ftime,leave:last ftime,eqt:first qtime,lqt:last qtime,ep:(neg first amt)%(first cumqty)*(getmultiple first sym),lp:(last amt)%(last cumqty)*(getmultiple first sym),pnl:sum amt,fee:sum fee,cash:first abs amt,last ref,first j1 by ts,sym,ti from update cumqty*r,amt*r,fee*r from (select ts,sym,r:abs[q0]%cumqty,pmqty:q0,cumqty,price,ftime,qtime,amt:cumamt,fee:cumfee,ref,j1,ti:ti0 from .temp.t where q0<>0),select ts,sym,r:abs[q1]%cumqty,pmqty:q1,cumqty,price,ftime,qtime,amt:cumamt,fee:cumfee,ref,j1,ti:neg ti1 from .temp.t where q1<>0) where n>1,0=sf;.temp.GTS:select n:count i,pnl:sum pnl,maxwin:max pnl,maxloss:min pnl,avgwin:avg (0f|pnl) except 0f,avgloss:avg (0f&pnl) except 0f,medwin:med (0f|pnl) except 0f,medloss:med (0f&pnl) except 0f,win:sum 0<pnl,loss:sum 0>pnl by ts,sym from .temp.GT;}; /[ts;(d0,d1)]

rdbeval:{[x].ctrl.conn.rdb.h[x]};hdbeval:{[x].ctrl.conn.hdb.h[x]};

//期权定价公式计算
pi:acos -1;
N_f:{abs (neg x>0f)+(1f%sqrt 2f*pi)*(exp -0.5*x*x)*t*0.31938153+t*-0.356563782+t*1.781477937+t*-1.821255978+1.330274429*t:1f%1f+0.2316419*abs x}; /N(0,1) cdf 
n_f:{(1% sqrt 2*pi)*(exp -.5*x*x)}; /N(0,1) pdf

bisec:{[e;f;x]while[(0<>v:f y:avg x)&(e<x[1]-x[0]);$[0>v*f x[0];x:x[0],y;x:y,x[1]]];y}; /[epsilon;f;(x0,x1)]二分法求根 f(x0)*f(x1)<0,find root of f

difftrdate:{[x;y](1+x-y)-sum {(in [x;.conf.holiday])|5<=weekday[x]}y+til [x-y]};

optinfox:{[m;x]y:fs2se[x];s:string[y[0]] except "-";e:y[1];i:last ss[s;"[CP]"];udl:se2fs (`$$[e=`CCFX;(string (`MO`IO`HO!`IM`IF`IH)`$2#s),2_i#s;i#s]),e;pc:`$s[i];sp:"F"$(i+1)_s;sd:.db.QX[x;`settledate];(`udl`pc`sp`sdate!(udl;pc;sp;sd)),$[m;`t`r`q`sn!(difftrdate[sd;.db.ftdate]%252;riskfreerate[udl];carryrate[udl];$[`C~pc;1;-1]);()]}; /[计算扩展信息标志;sym]由期货期权代码获取期权信息

optinfos:optinfox[0b];optinfo:optinfox[1b];

riskfreerate:{[x]$[`CCFX=fs2e x;0f^ffill .conf[`rrr];0f]};
carryrate:{[x]0f};

bspx:{[m;s;sn;p;sp;t;r;q]s:sn*s;df:exp neg r*t;F:p*f:exp (r-q)*t;N1:N_f d1:(0.5*a)+(log F%sp)%a:s*sqt:sqrt t;N2:neg N_f d2:d1-a;px:sn*df*(F*N1)+sp*N2;if[m;:px];delta:sn*df*N1*f;n1:n_f sn*d1;gamma:(e3:df*f*n1)%p*sn*a;`px`delta`gamma`theta`vega`rho`rho2!(px;delta;gamma;(px*neg (log df)%t)-((log[f]%t)*p*delta)+0.5*s*s*p*p*gamma;e3*p*sqt;sn*t*neg sp*df*N2;-1*t*p*delta)}; /BS公式计算期权价格和希腊字母(s:带号波动率{C正P负},df:)

bscalcx:{[m;s;x;y]p:.db.QX[y`udl;`price];bspx[m;s;y`sn;p;y`sp;y`t;y`r;y`q]}; /[s;sym;optinfo]由期货期权代码获取期权希腊字母

bscalc:bscalcx[0b];

bsiv:{[op;p;t;sn;sp;r;q]if[0>=p&op;:0n];s:bisec[1e-5;'[-[op];bspx[1b;;sn;p;sp;t;r;q]];0 2f];$[s<1.9;s;0n]}; /BS公式计算隐含波动率[optpx;futpx;t;sn;strikepx;r;q]
bsivx:{[x;y;op]p:.db.QX[y`udl;`price];bsiv[op;p;y`t;y`sn;y`sp;y`r;y`q]}; /[sym;optinfo;px]由期货期权代码和价格获取隐含波动率
bsivs:{[x;y]op:.db.QX[x;`price];bsivx[x;y;op]}; /[/[sym;optinfo]

bshvx:{[x;D]sqrt[252] * dev 1_deltas log .ctrl.conn.hdb.h ({[x;y]if[-7h=type y;y:(first;last)@\:neg[y+1]#date];exec price from select last price by date from quote where sym=x,date within y};x;D)}; /[sym;d0,d1]由期货代码和历史日期区间统计历史波动率
bshv:{[x]bshvx[x;60^jfill .conf[`hvnday]]};

opt_selsym:{[x;y;z]u:$[x;`C;`P];d:`sp xasc select from .db.OPT where udl=y,pc=u;p:(^/).db.QX[y;`pc`price];w:exec first sym  from d where abs[sp-p]=min abs[sp-p];spw:.db.OPT[w;`sp];(exec sublist[z[0]] sym from d where sp<spw),w,exec sublist[z[1]] sym from d where sp>spw}; /[iscall;期货合约;atm期权上下档位]
opt_selcall:opt_selsym[1b];opt_selput:opt_selsym[0b];

opt_updinfo:{[x;y].db.OPT:1!`sym xcols exec {update sym:x from optinfo each x} sym from .db.QX where assetclass=`Option,settledate>=.z.D;.ctrl[`optinfodate`optinfotime]:(.db.ftdate;now[]);1b};

//----ChangeLog----
//2024.11.14:tsstat更正列名拼写错误
//2024.10.31:opeg_libpeg增加对cp`pegrej开关的支持以支持拒单的补单
//2024.03.11:新增holdtime函数以修复tsstat函数持仓时长计算的bug
//2024.03.06:tsstat函数将ntime替换为ftime
//2024.01.15:补单策略opeg_libpeg增加对多账户和非空执行策略tsexec的支持;增加期权定价公式支持以通过定时任务生成.db.OPT:.db.TASK[`UPDINFO;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:30:00;1D;0;4;`opt_updinfo);