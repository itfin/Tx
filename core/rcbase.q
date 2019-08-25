.module.rcbase:2019.07.30; /风控检查(可能在ft或fe中加载)

riskassert:{[x]0b}; /风控检查委托默认处理函数
riskassertcxl:{[x]0b}; /风控检查撤单默认处理函数
riskstatrej:{[x];}; /风控检查委托拒绝默认处理函数

.ctrl.snaptime:`ST1s`ST5s`ST20s`ST1m!(0Nv;0Nv;0Nv;0Nu);

.roll.rcbase:{[x]if[0b~.conf.checkrisk;:()];.db.RS:0#.db.RS;.db.RN:0#.db.RN;}; /日终清空流速/流量计数
.timer.rcbase:{[x]if[0b~.conf.checkrisk;:()];t:`time$x;s:`second$t;s5:5 xbar s;s20 :20 xbar s;m:`minute$t;if[s<>.ctrl.snaptime`ST1s;update no1s:0,nc1s:0 from `.db.RS;.ctrl.snaptime[`ST1s]:s];if[s5<>.ctrl.snaptime`ST5s;update no5s:0,nc5s:0 from `.db.RS;.ctrl.snaptime[`ST5s]:s5];if[s20<>.ctrl.snaptime`ST20s;update no20s:0,nc20s:0 from `.db.RS;.ctrl.snaptime[`ST20s]:s20];if[m<>.ctrl.snaptime`ST1m;update no1m:0,nc1m:0 from `.db.RS;.ctrl.snaptime[`ST1m]:m];}; /定时重置流速计数器

risklimit:{[x;y;s;z]if[null v:.db.RL[(x;y;s);z];v:?[`.db.RL;((=;`ts;`x);(=;`acc;`y);(|;((/:;like);`s;($:;`sym));(^:;`sym));(~:;(^:;`z)));();(min;z)]];0f^v}; /[ts;acc;sym;field]

chkqty:{[ispos;x;y;s;sd;pe;q;p]if[pe<>.enum`OPEN;:0b];pm:abs 0f^risklimit[x;y;s;$[sd=.enum`BUY;$[ispos=2;`maxprdlong;ispos=1;`maxlong;`maxlongday];$[ispos=2;`maxprdshort;ispos=1;`maxshort;`maxshortday]]];pc:abs 0f^$[ispos=2;$[sd=.enum`BUY;exec sum 0f^lqty from .db.P where ts=x,acc=y,.db.QX[s;`product]=.db.QX[;`product] each sym;exec sum 0f^sqty from .db.P where ts=x,acc=y,.db.QX[s;`product]=.db.QX[;`product] each sym];.db.P[(x;y;s);$[sd=.enum`BUY;$[ispos;`lqty;`lqty0];$[ispos;`sqty;`sqty0]]]];pm<=pc+exec sum qty-0f^cumqty from .db.O where not end,ts=x,acc=y,sym=s,side=sd,posefct=.enum[`OPEN]};

chkmaxday:chkqty[0];    /检查当日最大开仓
chkmaxpos:chkqty[1];    /检查本代码最大持仓
chkmaxprdpos:chkqty[2]; /检查本品种最大持仓

chkmaxord:{[x;y;s;sd;pe;q;p]if[pe<>.enum`OPEN;:0b];q>0f^risklimit[x;y;s;$[sd=.enum`BUY;`maxlongord;`maxshortord]]}; /检查单笔最大开仓
chkmaxordqty:{[x;y;s;sd;pe;q;p]q>0f^risklimit[x;y;s;$[sd=.enum`BUY;`maxordbuy;`maxordsell]]}; /检查单笔最大买卖数量

chkmaxspeed:{[x;y;s;sd;pe;q;p](.db.RS[(x;y);`no1s]>=.db.RL[(x;y;`);`maxno1s])|(.db.RS[(x;y);`no5s]>=.db.RL[(x;y;`);`maxno5s])|(.db.RS[(x;y);`no20s]>=.db.RL[(x;y;`);`maxno20s])|(.db.RS[(x;y);`no1m]>=.db.RL[(x;y;`);`maxno1m])};  /检查交易流速限制 
chkmaxcxlspeed:{[x;y;s;sd;pe;q;p](.db.RS[(x;y);`nc1s]>=.db.RL[(x;y;`);`maxnc1s])|(.db.RS[(x;y);`nc5s]>=.db.RL[(x;y;`);`maxnc5s])|(.db.RS[(x;y);`nc20s]>=.db.RL[(x;y;`);`maxnc20s])|(.db.RS[(x;y);`nc1m]>=.db.RL[(x;y;`);`maxnc1m])};  /检查交易流速限制 
chkmaxfund:{[x;y;s;sd;pe;q;p]if[pe<>.enum`OPEN;:0b];if[p<=0f;p:.db.QX[s;$[sd=.enum`BUY;`sup;`inf]]];om:abs getfrozen[(s;sd;pe;q;q*p*getmultiple[s])];pm:0f|0f^ffill .db.Ts[x;`margin];fm:abs frozenfund[x;y];(om>availfund[x])|.db.RL[(x;y;`);`maxfund]<om+fm+pm}; /检查总可用资金限制

chkmaxfundord:{[x;y;s;sd;pe;q;p]if[pe<>.enum`OPEN;:0b];if[p<=0f;p:.db.QX[s;$[sd=.enum`BUY;`sup;`inf]]];om:abs getfrozen[(s;sd;pe;q;q*p*getmultiple[s])];om>.db.RL[(x;y;`);`maxfundord]}; /检查单笔委托资金使用

chkmaxordcnt:{[x;y;s;sd;pe;q;p]any {(1+0^.db.RN[x;`nord])>0^risklimit[x[0];x[1];x[2];`maxnord]} each (x,y),/:(s,`)}; /检查最大委托笔数
chkmaxcxlcnt:{[x;y;s;sd;pe;q;p]any {(1+0^.db.RN[x;`ncxl])>0^risklimit[x[0];x[1];x[2];`maxncxl]} each (x,y),/:(s,`)}; /检查最大撤单笔数
chkmaxrejcnt:{[x;y;s;sd;pe;q;p]any {(1+0^.db.RN[x;`nrej])>0^risklimit[x[0];x[1];x[2];`maxnrej]} each (x,y),/:(s,`)}; /检查最大拒绝笔数

rsincr:{[x;y;s]{[x].db.RS[x;`no1s`no5s`no20s`no1m]:1+0^.db.RS[x;`no1s`no5s`no20s`no1m]} each (x,y;``);{[x].db.RN[x;`nord]:1+0^.db.RN[x;`nord]} each (x,y,s;``,s;```);}; /[ts;acc;sym]委托流速/流量计数器增加
rsincrcxl:{[x;y;s]{[x].db.RS[x;`nc1s`nc5s`nc20s`nc1m]:1+0^.db.RS[x;`nc1s`nc5s`nc20s`nc1m]}each (x,y;``);{[x].db.RN[x;`ncxl]:1+0^.db.RN[x;`ncxl]} each (x,y,s;``,s;```);}; /[ts;acc;sym]撤单流速/流量计数器增加

riskassertx:{[cxlchk;k]if[0b~.conf.checkrisk;:0b];r:.db.O[k];x:r`ts;y:r`acc;s:r`sym;sd:r`side;pe:r`posefct;q:r`qty;p:r`price;R:$[cxlchk;select from .db.R where active,rid.valid,rid.cxlchk;select from .db.R where active,rid.valid,not rid.cxlchk];L:();L,:rl:exec rid from R where x=ts,y=acc;L,:rl1:exec rid from R where x=ts,null acc,not rid in L;L,:rl2:exec rid from R where null ts,null acc,not rid in L;if[(0=count L)&(1b~.conf.rcusewhitelst)&not cxlchk;lwarn[`RiskCheckNotInWhitelst;(k;x;y)];:1b];i:0;do[count rl;ru:rl[i];if[(.db.RR[ru;`func])[x;y;s;sd;pe;q;p];lwarn[`RiskTrigger;(k;x;y;ru;s;sd;pe;q;p)];:1b];i+:1];i:0;do[count rl1;ru:rl1[i];if[(.db.RR[ru;`func])[x;`;s;sd;pe;q;p];lwarn[`RiskTrigger;(k;x;`;ru;s;sd;pe;q;p)];:1b];i+:1];i:0;do[count rl2;ru:rl2[i];if[(.db.RR[ru;`func])[`;`;s;sd;pe;q;p];lwarn[`RiskTrigger;(k;`;`;ru;s;sd;pe;q;p)];:1b];i+:1];($[cxlchk;rsincrcxl;rsincr])[x;y;s];0b}; /[check ordcxl;oid] 当风控规则激活时进行风控检查,决定是否放行委托/撤单

riskassert:riskassertx[0b];riskassertcxl:riskassertx[1b];
riskstatrej:{[k]r:.db.O[k];{[x].db.RN[x;`nrej]:1+0^.db.RN[x;`nrej]} each (r`ts`acc`sym;``,r`sym;```);}; /[oid]委托拒绝统计
riskstatexe:{[k]if[.db.O[k;`status]<>.enum`REJECTED;:()];riskstatrej[k];}; /[oid]委托回报统计

\

\d .db
RR:([rid:`symbol$()]valid:`boolean$();cxlchk:`boolean$();class:`symbol$();func:`symbol$();text:`symbol$()); /风控规则
R:([ts:`symbol$();acc:`symbol$();rid:`.db.RR$()]active:`boolean$());            /风控开关
RL:([ts:`symbol$();acc:`symbol$();sym:`symbol$()]maxlong:`float$();maxshort:`float$();maxlongday:`float$();maxshortday:`float$();maxlongord:`float$();maxshortord:`float$();maxordbuy:`float$();maxordsell:`float$();maxfund:`float$();maxfundord:`float$();maxprdlong:`float$();maxprdshort:`float$();maxno1s:`long$();maxno5s:`long$();maxno20s:`long$();maxno1m:`long$();maxnc1s:`long$();maxnc5s:`long$();maxnc20s:`long$();maxnc1m:`long$();maxnord:`long$();maxncxl:`long$();maxnrej:`long$()); /风控参数
RS:([ts:`symbol$();acc:`symbol$()]no1s:`long$();no5s:`long$();no20s:`long$();no1m:`long$();nc1s:`long$();nc5s:`long$();nc20s:`long$();nc1m:`long$());  /流速计数
RN:([ts:`symbol$();acc:`symbol$();sym:`symbol$()]nord:`long$();ncxl:`long$();nrej:`long$());  /流量计数
\d .

//fe配置
.db.RR,:((`maxspeed;1b;0b;`speed;`chkmaxspeed;`$"委托流速限额");(`maxcxlspeed;1b;1b;`speed;`chkmaxcxlspeed;`$"撤单流速限额");(`maxordcnt;1b;0b;`cnt;`chkmaxordcnt;`$"委托笔数限额");(`maxcxlcnt;1b;1b;`cnt;`chkmaxcxlcnt;`$"撤单笔数限额");(`maxrejcnt;1b;0b;`cnt;`chkmaxrejcnt;`$"拒绝笔数限额"));
.db.R[``,/:`maxspeed`maxcxlspeed`maxordcnt`maxcxlcnt`maxrejcnt;`active]:1b;

.db.RL[```;`maxno1s`maxno5s`maxno20s`maxno1m`maxnc1s`maxnc5s`maxnc20s`maxnc1m`maxnord`maxncxl`maxnrej]:100 500 2000 6000 300 1500 6000 18000 1000000 3000000 100000; /production
.db.RL[``,`$"*[XC]?[^HK][EX]";`maxncxl]:460; /production

//.db.RL[```;`maxno1s`maxno5s`maxno20s`maxno1m`maxnc1s`maxnc5s`maxnc20s`maxnc1m`maxnord`maxncxl`maxnrej]:2 2 2 2 2 2 2 2 5 2 1; /test-min

//.db.RL[```;`maxno1s`maxno5s`maxno20s`maxno1m`maxnc1s`maxnc5s`maxnc20s`maxnc1m`maxnord`maxncxl`maxnrej]:0W; /test-max


//ft配置

.db.RR,:((`maxprdpos;1b;0b;`qty;`chkmaxprdpos;`$"同品种总持仓限额");(`maxpos;1b;0b;`qty;`chkmaxpos;`$"总持仓限额");(`maxday;1b;0b;`qty;`chkmaxday;`$"当日开仓限额");(`maxord;1b;0b;`qty;`chkmaxord;`$"单笔开仓限额");(`maxordqty;1b;0b;`qty;`chkmaxordqty;`$"单笔数量限额");(`maxspeed;1b;0b;`speed;`chkmaxspeed;`$"委托流速限额");(`maxcxlspeed;1b;1b;`speed;`chkmaxcxlspeed;`$"撤单流速限额");(`maxfund;0b;0b;`fund;`chkmaxfund;`$"可用资金限额");(`maxfundord;0b;1b;`fund;`chkmaxfundord;`$"单笔资金限额");(`maxordcnt;1b;0b;`cnt;`chkmaxordcnt;`$"委托笔数限额");(`maxcxlcnt;1b;1b;`cnt;`chkmaxcxlcnt;`$"撤单笔数限额");(`maxrejcnt;1b;0b;`cnt;`chkmaxrejcnt;`$"拒绝笔数限额"));

.db.R[``,/:`maxord`maxordqty`maxfundord;`active]:1b;

.db.RL[(```);`maxfundord]:1000000f; /production

.db.RL[(```);`maxfundord]:200f; /test


.db.R[```maxspeed;`active]:1b;
.db.R[```maxordcnt;`active]:1b;
.db.R[`oacd`sim`maxpos;`active]:1b;
.db.R[`oacd`sim`maxprdpos;`active]:1b;
.db.R[`oacd`sim,/:`maxday`maxord`maxordqty;`active]:1b;
.db.RL[(```);`maxno1s`maxno5s`maxno20s`maxno1m]:100 500 2000 6000;

.db.R,:((`qtx;`;`maxpos;1b);(`qtx;`;`maxday;1b);(`qtx;`;`maxspeed;1b);(`qtx;`;`maxfund;1b);(`oacd;`;`maxpos;1b);(`oacd;`;`maxday;1b);(`;`;`maxspeed;1b);(`oacd;`;`maxfund;1b));

.db.RL[(```);`maxno1s`maxno5s`maxno20s`maxno1m]:1 5 10 20;
.db.RL[(```);`maxnord`maxncxl]:1000 1000;
.db.RL[(`qtx`,`$"*");`maxnord`maxncxl]:5000 5000;

.db.RL[(`oacd`sim,`$"IF*");`maxlong`maxshort`maxprdlong`maxprdshort`maxlongday`maxshortday`maxlongord`maxshortord`maxordbuy`maxordsell]:2f;

.db.RL[(`qtx``IF1909.CCFX);`maxno1s`maxno5s`maxno20s`maxno1m]:1 5 10 20;


.db.RL,:((`qtx;`;`IF1909.CCFX;100f;100f;100f;100f;10f;10f;0n;0n;0n;0n;0N;0N;0N;0N);(`qtx;`;`;0n;0n;0n;0n;0n;0n;1e6;1e6;0N;0N;0N;0N);(`;`;`;0n;0n;0n;0n;0n;0n;0n;0n;5;10;20;30);(`oacd;`;`IF1909.CCFX;100f;100f;100f;100f;10f;10f;0n;0n;0N;0N;0N;0N);(`oacd;`;`;0n;0n;0n;0n;0n;0n;1e7;1e6;0N;0N;0N;0N);(`oacd;`;`;0n;0n;0n;0n;0n;0n;0n;0n;5;10;20;30));


