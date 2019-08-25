//tslib.q:标准化的策略组件函数

.module.tslib:2019.06.19;

//libpeg:自动撤补单功能,要求策略存在参数.db.Ts[x;`Cp;TRDTIME`tmout`tmout1`tmout2`urge]:(交易时段列表;委托超时撤单时间间隔;补单时间间隔1(超过则至少urge=1);补单时间间隔2(超过则至少urge=2);紧急程度{0W;打对手涨跌停价;[3,n]:打对手盘口+[1,n-2]跳,2:打对手盘口,1:本方盘口+1跳;0:挂本方盘口})
//在策略的ont事件中调用oexpire_libpeg,ono事件中调用opeg_libpeg,策略下单后对oid调用pegord_libpeg

pegord_libpeg:{[x].db.O[x;`special]:`PEG;x}; /[oid]

ordpxex_libpeg:{[x;y;z;w]pu:pxunit[y];pb:.db.QX[y;`bid];pa:.db.QX[y;`ask];ps:.db.QX[y;`sup];pi:.db.QX[y;`inf];b:z=.enum`BUY;$[0W=w;$[b;ps;pi];2<w;$[b;ps&pa+pu*(w-2);pi|pb-pu*(w-2)];2~w;$[b;pa;pb];1~w;roundpx[y;z;$[b;pb+pu;pa-pu]];$[b;pb;pa]]}; /[tid;sym;side;urge]计算补单价格

oexpire_libpeg:{[x;y]if[not any (`time$y) within/:.db.Ts[x;`Cp;`TRDTIME];:()];cxlord each exec id from .db.O where ts=x,not end,special=`PEG,.db.Ts[x;`Cp;`tmout]<y-ntime;}; /[tid;.z.P]对超时委托进行撤单

opeg_libpeg:{[x;y]r:.db.O[y];if[(.enum[`CANCELED]=r[`status])&(`PEG=r[`special]);s:r[`sym];sd:r[`side];z:r`origid;cp:.db.Ts[x;`Cp];w:cp[`urge];k:limit_order[sd;0N;r`ts;s;roundqty[(s;sd);r[`qty]-r[`cumqty]];ordpxex_libpeg[x;s;sd;$[(null z)|(.z.P<.db.O[z;`ntime]+cp[`tmout1]);w;.z.P<.db.O[z;`ntime]+cp[`tmout2];1|w;2|w]];r[`ref]];{[x;y].db.O[x;`special`origid]:(`PEG;y^.db.O[y;`origid])}[;y] each k];};  /[tid;oid]对需要补单的撤单委托进行补单操作

//libbar:自动根据策略订阅的Bar频率将系统Bar合成为策略需要的n周期bar后再回调策略的barx事件,要求策略存在标的代码.db.Ts[x;xsym]控制参数.db.Ts[x;`Cp;barfreq]和缓存区.db.Ts[x;`BBUF]:()
//在策略的event中bar事件触发器设置为onb_libbar,另外设置barx时间触发器为策略逻辑
onb_libbar:{[x;b].temp.b:b;r:.db.Ts[x];y:r`xsym;sess:trdsess[y];t:b`bart;if[not any t within/:sess;:()];bf:b`freq;sf:`long$`second$r[`Cp;`barfreq];bx:r[`event;`barx];if[sf<=bf;:(bx)[x;b]];n:sf div bf;bt:xbar[sf] t;if[n1:count r`BBUF;if[count[r`BBUF]&bt>xbar[sf] (last r`BBUF)`bart;(bx)[x;synbar_libbar[x]]]];.db.Ts[x;`BBUF],:enlist b;if[n<=n1+1;(bx)[x;synbar_libbar[x]]];}; /[tid;bar]

synbar_libbar:{[x]b:exec last time,first sym,freq:`second$.db.Ts[x;`Cp;`barfreq],first bard,first bart,first open,max high,min low,last close,sum vol,sum amt,last src,last srctime,last srcseq,last dsttime from .db.Ts[x;`BBUF];.db.Ts[x;`BBUF]:0#.db.Ts[x;`BBUF];b}; /[tid] 