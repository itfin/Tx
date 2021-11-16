//tslib.q:标准化的策略组件函数或辅助函数

.module.tslib:2019.09.23;

//libpeg:自动撤补单功能,要求策略存在参数.db.Ts[x;`Cp;TRDTIME`tmout`tmout1`tmout2`urge]:(交易时段列表;委托超时撤单时间间隔;补单时间间隔1(超过则至少urge=1);补单时间间隔2(超过则至少urge=2);紧急程度{0W;打对手涨跌停价;[3,n]:打对手盘口+[1,n-2]跳,2:打对手盘口,1:本方盘口+1跳;0:挂本方盘口})
//在策略的ont事件中调用oexpire_libpeg,ono事件中调用opeg_libpeg,策略下单后对oid调用pegord_libpeg

pegord_libpeg:{[x].db.O[x;`special]:`PEG;x}; /[oid]

ordpxex_libpeg:{[x;y;z;w]pu:pxunit[y];pb:.db.QX[y;`bid];pa:.db.QX[y;`ask];ps:.db.QX[y;`sup];pi:.db.QX[y;`inf];b:z=.enum`BUY;$[0W=w;$[b;ps;pi];2<w;$[b;ps&pa+pu*(w-2);pi|pb-pu*(w-2)];2~w;$[b;pa;pb];1~w;roundpx[y;z;$[b;pb+pu;pa-pu]];$[b;pb;pa]]}; /[tid;sym;side;urge]计算补单价格

oexpire_libpeg:{[x;y]if[not any (`time$y) within/:.db.Ts[x;`Cp;`TRDTIME];:()];cxlord each exec id from .db.O where ts=x,not end,special=`PEG,.db.Ts[x;`Cp;`tmout]<y-ntime;}; /[tid;.z.P]对超时委托进行撤单

opeg_libpeg:{[x;y]r:.db.O[y];if[(.enum[`CANCELED]=r[`status])&(`PEG=r[`special]);s:r[`sym];sd:r[`side];z:r`origid;cp:.db.Ts[x;`Cp];w:cp[`urge];k:limit_order[sd;0N;r`ts;s;roundqty[(s;sd);r[`qty]-r[`cumqty]];ordpxex_libpeg[x;s;sd;$[(null z)|(.z.P<.db.O[z;`ntime]+cp[`tmout1]);w;.z.P<.db.O[z;`ntime]+cp[`tmout2];1|w;2|w]];r[`ref]];{[x;y].db.O[x;`special`origid]:(`PEG;y^.db.O[y;`origid])}[;y] each k];};  /[tid;oid]对需要补单的撤单委托进行补单操作


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

tsstat:{[x;y]d0:y[0];d1:y[1];td:vtd[];.temp.date:(.ctrl.conn.hdb.h `date),vtd[];.temp.t:update ti0:sums {(not x)&-1_1b,x} 0=sums q0,ti1:sums {(not x)&-1_1b,x} 0=sums q1 by ts,sym from update q0:?[not eot;pmqty;?[(0=mod[gi;2])&(0=spmqty);0f;pmqty-spmqty]],q1:?[not eot;0f;?[(0=mod[gi;2])&(0=spmqty);pmqty;spmqty]] from update gi:({$[y=0;0;x+1]}\)[0;eot] by ts,sym from update eot:(spmqty=0)|(-1=signum[spmqty]*signum[spmqty^prev spmqty]) by ts,sym from update spmqty:sums pmqty by ts,sym from update pmqty:?[.enum[`BUY]=side;1;-1]*cumqty from (select from .hdb.O where ts in x,cumqty>0,(`date$ntime) within y),select from .db.O where ts in x,cumqty>0,(`date$ntime) within y;.temp.GT:`enter xasc select ts,sym,ti,n,cumqty,enter,leave,ep,lp,netpnl:pnl+fee,pnl,fee,cash,hold:{[x;y;z](sesstotal[x]*(-/).temp.date?`date$y,z)+(-/)trdtime[x;y,z]}'[sym;lqt;eqt],delta:lp-ep,yield:1e2*pnl%cash,ref,j1 from select from (select n:count i,sf:sum pmqty,max cumqty,enter:first ntime,leave:last ntime,eqt:first qtime,lqt:last qtime,ep:(neg first amt)%(first cumqty)*(getmultiple first sym),lp:(last amt)%(last cumqty)*(getmultiple first sym),pnl:sum amt,fee:sum fee,cash:max amt,last ref,first j1 by ts,sym,ti from update cumqty*r,amt*r,fee*r from (select ts,sym,r:abs[q0]%cumqty,pmqty:q0,cumqty,price,ntime,qtime,amt:cumamt,fee:cumfee,ref,j1,ti:ti0 from .temp.t where q0<>0),select ts,sym,r:abs[q1]%cumqty,pmqty:q1,cumqty,price,ntime,qtime,amt:cumamt,fee:cumfee,ref,j1,ti:neg ti1 from .temp.t where q1<>0) where n>1,0=sf;.temp.GTS:select n:count i,pnl:sum pnl,maxwin:max pnl,maxloss:min pnl,avgwin:avg (0f|pnl) except 0f,avgloass:avg (0f&pnl) except 0f,medwin:med (0f|pnl) except 0f,medloass:med (0f&pnl) except 0f,win:sum 0<pnl,loss:sum 0>pnl by ts,sym from .temp.GT;}; /[ts;(d0,d1)]

rdbeval:{[x].ctrl.conn.rdb.h[x]};hdbeval:{[x].ctrl.conn.hdb.h[x]};
