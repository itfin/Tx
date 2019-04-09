.module.tsgrid:2017.05.26;

//网格交易策略.策略参数[TRDTIME:,ANCHORSYM:,LONGSYM:,SHORTSYM:,GRIDSIZE,POSINF,POSSUP,RATIO,SHORTOFFSET,LONGOFFSET,PRICESCALE,SPREADMAX,SHORTSTOPRANGE,LONGSTOPRANGE],状态变量[ANCHORPX,ANCHORUP,ANCHORDON,OIDUP,OIDDN]
onq_grid:{[x;y];}; /[tid;symlist]

ont_grid:{[x;y]t:`time$y;wd:weekday[y];r:.db.Ts[x];acc:r`acc;z:r`xsym;pa:.db.QX[z;`ask];pb:.db.QX[z;`bid];if[(not any t within/: r`TRDTIME)|(wd=6)|((wd=5)&t>06:00)|((wd=0)&t<06:00)|(0>=pa&pb);:()];pm:-0w^first r`LONGSTOPRANGE;pM:0w^first r`SHORTSTOPRANGE;sm:r`SPREADMAX;$[((pb>pM)|(pa<pm))&(sm>=pa-pb);$[0<count il:exec id from .db.O where ts=x,not end,(ref in `up`dn)|00:00:05<.z.P-ntime;cxlord each il;[if[(pa within r`SHORTSTOPRANGE)&(sm>=pa-pb)&(0<q:neg .db.P[(x;acc;z);`sqty]);limit_buy[x;z;q;pa+sm;`stopcloseshort];.db.Ts[x;`mode]:`MANUAL];if[(pb within r`LONGSTOPRANGE)&(sm>=pa-pb)&(0<q:.db.P[(x;acc;z);`lqty]);limit_sell[x;z;q;pb-sm;`stopcloselong];.db.Ts[x;`mode]:`MANUAL];]];[pq:sum 0f^.db.P[(x;acc;z);`lqty`sqty];qu:r`GRIDSIZE;ps:1f^ffill r`PRICESCALE;pu:r[`ANCHORUP]+r[`SHORTOFFSET];if[(null r`OIDUP)&(pq>r`POSINF)&(pu<=0w^.db.QX[z;`sup]);.db.Ts[x;`OIDUP]:first limit_sell[x;z;qu;ps*pu;`up]];pd:r[`ANCHORDN]+r[`LONGOFFSET];if[(null r`OIDDN)&(pq<r`POSSUP)&(pd>=0f^.db.QX[z;`inf]);.db.Ts[x;`OIDDN]:first limit_buy[x;z;qu;ps*pd;`dn]]]];}; /[tid;.z.P]

ono_grid:{[x;y]r:.db.O[y];st:r`status;lb:r`ref;if[not (lb in `up`dn)&y in .db.Ts[x;`OIDUP`OIDDN];:()];$[st=.enum`CANCELED;.db.Ts[x;$[lb~`up;`OIDUP;`OIDDN]]:`;st=.enum`FILLED;[px:.db.Ts[x;$[lb~`up;`ANCHORUP;`ANCHORDN]];.db.Ts[x;`ANCHORPX`ANCHORUP`ANCHORDN]:px*1f*1+0 1 -1*.db.Ts[x;`RATIO];.db.Ts[x;$[lb~`up;`OIDUP;`OIDDN]]:`;cxlord[.db.Ts[x;$[lb~`up;`OIDDN;`OIDUP]]]];()];}; /[tid;oid]

ond_grid:{[x;y]if[(.db.O[k;`tif] in .enum`NULL`DAY)&(not null k:.db.Ts[x;`OIDUP]);.db.Ts[x;`OIDUP]:`];if[(.db.O[k;`tif] in .enum`NULL`DAY)&(not null k:.db.Ts[x;`OIDDN]);.db.Ts[x;`OIDDN]:`];};


\
noeexec[`20170201001;`ft`qtx;`XAUUSD.METAL;.enum`SELL;.enum`OPEN;66f;1232.436;"init"];
noeexec[`20170313002;`ft`qtx;`ZC701.XZCE;.enum`SELL;.enum`OPEN;1f;582.2;"init"];
