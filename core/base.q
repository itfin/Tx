.module.base:2025.02.19;

txload:{[x]@[system;"l Tx/",x,".q";@[system;"l Tx/",x,".q_";`$"txload_",x]];};
cfload:{[x]txload "conf/",x;};
txload "lib/handy";
txload "lib/extutil";
txload "lib/math";
txload "lib/userlib";

\l tick/u.q
.u.init[]; 

txload "core/api";
txload "core/p2p";
txload "core/enum";
txload "core/dotz";
txload "core/habase";

\d .ctrl
conn:.enum.nulldict;
sub:.enum.nulldict;
StateMap:(`symbol$())!`symbol$();
StateEnter:(`symbol$())!`timestamp$();
\d .

.temp:.enum.nulldict;

\d .db
seq0:seq:0;
sysdate:.z.D;
TASK:([id:`symbol$()] expire:`boolean$(); firetime:`timestamp$(); firefreq:`timespan$(); datemin:`date$(); datemax:`date$(); weekmin:`int$(); weekmax:`int$(); timemin:`time$(); timemax:`time$(); handler:(); lastfire:());

QX:([`u#sym:`symbol$()] ex:`symbol$(); esym:`symbol$(); name:`symbol$(); ticker:`symbol$(); status:`int$(); mode:`symbol$(); open:`float$(); vwap:`float$(); size:`float$(); sup:`float$(); inf:`float$(); pc:`float$(); scale:`float$(); date:`date$(); time:`timespan$(); price:`float$(); cumqty:`float$(); cumamt:`float$(); high:`float$(); low:`float$(); bid:`float$(); bsize:`float$(); ask:`float$(); asize:`float$(); bidQ:0#enlist`float$(); bsizeQ:0#enlist`float$(); askQ:0#enlist`float$(); asizeQ:0#enlist`float$(); bnum:`long$(); bqtyQ:0#enlist`float$(); anum:`long$(); aqtyQ:0#enlist`float$(); openint:`float$(); settlepx:`float$(); quoopt:(); refopt:();  recvtime:`timestamp$(); extime:`timestamp$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$(); nticks:`long$(); settledate:`date$(); settleperiod:`int$(); industry:`symbol$(); underlying:`symbol$(); assetclass:`symbol$(); product:`symbol$(); multiplier:`float$(); pxunit:`float$(); qtylot:`float$(); qtyscale:`float$(); qtyminl:`float$(); qtymins:`float$(); qtymax:`float$(); qtymaxm:`float$(); qtymaxl:`float$(); qtymaxs:`float$(); margintype:`symbol$(); rmarginl:`float$(); rmargins:`float$(); rmarginoq:`float$(); rmarginmq:`float$(); rmarginioq:`float$(); rmarginimq:`float$(); rfeetaxoa:`float$(); rfeetaxoq:`float$(); rfeetaxca:`float$(); rfeetaxcq:`float$(); rfeetaxcat:`float$(); rfeetaxcqt:`float$(); rfeetaxom:`float$(); rfeetaxcm:`float$(); rfeetaxctm:`float$(); date1:`date$(); time1:`time$(); opendate:`date$(); createdate:`date$(); lifephase:`symbol$(); currency:`symbol$(); putcall:`symbol$(); optexec:`symbol$(); optsettle:`symbol$(); strikepx:`float$(); isin:`symbol$(); cficode:`symbol$(); sectype:`symbol$(); secclass:`symbol$(); secstatus:`symbol$(); tradetype:`symbol$(); tradephase:`symbol$(); suspendtype:`symbol$(); state:`symbol$(); remark:`symbol$(); sec_key:`symbol$(); ex1:`symbol$(); cficode:`symbol$(); notice:`symbol$() ); /L1 Static

LOG:([]sym:`symbol$();typ:`symbol$();msg:0#enlist "";logtime:`timestamp$());

O:([`u#id:`symbol$()] ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); fe:`symbol$(); acc1:`symbol$(); ref:`symbol$(); sym:`symbol$(); side:`char$(); posefct:`char$(); tif:`char$(); typ:`char$(); qty:`float$(); price:`float$(); end:`boolean$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); lastqty:`float$(); lastpx:`float$(); feoid:`symbol$(); ordid:`symbol$(); exchid:`symbol$(); cstatus:`char$(); cn:`int$(); ntime:`timestamp$(); ctime:`timestamp$(); msg:(); cumamt:`float$(); cumfee:`float$(); qtime:`timestamp$(); jtime:`timestamp$(); ftime:`timestamp$(); rtime:`timestamp$(); reason:`int$(); ordopt:(); rptopt:(); cid:`symbol$(); cfeoid:`symbol$(); cordid:`symbol$(); cexchid:`symbol$(); qn:`int$(); special:`symbol$(); origid:`symbol$(); ex:`symbol$(); esym:`symbol$(); tsexec:`symbol$(); upid:`symbol$(); slot:`long$(); previd:`symbol$(); pending:`boolean$();style:`symbol$(); expiretime:`timestamp$(); t0:`timestamp$(); t1:`timestamp$(); s0:`symbol$(); s1:`symbol$(); s2:`symbol$(); s3:`symbol$(); j0:`long$(); j1:`long$(); j2:`long$();  j3:`long$(); f0:`float$(); f1:`float$(); f2:`float$(); f3:`float$(); x0:(); x1:(); x2:(); x3:()); /Order

M:([`u#id:`symbol$()] sym:`symbol$(); price:`float$(); qty:`float$(); mtime:`timestamp$(); maker:`symbol$(); taker:`symbol$()); /Match

P:([ts:`symbol$(); acc:`symbol$(); sym:`symbol$()] lqty:`float$();  sqty:`float$(); flqty:`float$(); fsqty:`float$(); lqty0:`float$(); sqty0:`float$(); flqty0:`float$(); fsqty0:`float$()); /Postion

QT:([id:`u#`symbol$()] qrid:`symbol$(); bid:`symbol$(); aid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); fe:`symbol$(); acc1:`symbol$(); ref:`symbol$();sym:`symbol$(); bprice:`float$(); aprice:`float$(); bqty:`float$(); aqty:`float$(); bposefct:`char$(); aposefct:`char$(); status:`char$(); bcumqty:`float$(); acumqty:`float$(); bavgpx:`float$(); aavgpx:`float$(); feqid:`symbol$(); quoteid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cfeqid:`symbol$(); cquoteid:`symbol$(); ntime:`timestamp$(); ctime:`timestamp$(); rtime:`timestamp$(); reason:`int$(); msg:(); rptopt:(); cn:`int$(); linkid:`symbol$()); /Quote

S:([mid:`symbol$();ref:`symbol$();state:`symbol$()]active:`boolean$();updtime:`timestamp$();entertime:`timestamp$();leavetime:`timestamp$()); /StateEvent

\d .

.init.base:{[x].ctrl.init:1b;loaddb[];.ctrl[`status`inittime]:(`Inited;.z.P);};
.timer.base:{[x]if[not `init in key `.ctrl;.init[;x];];chkconn[];chksub[];};
.roll.base:{[x]clearapi[];cleartemp[];.[.conf.histdb;(.conf.me;`LOG);,;.db.LOG];delete from `.db.LOG;.db.seq0:0^jfill .conf[`seq0base];.db.sysdate:x;}; /savedb[];

.base.boot:{[].ctrl[`boot`boottime]:(1b;.z.P);system "S ",string `int$.z.T;.base.cmdopt:first each .Q.opt .z.x;if[count cf:.base.cmdopt`conf;cfload cf];if[count cd:.base.cmdopt`code;@[value;cd;()]];};

.exit.base:{[x].ctrl[`status`exittime]:(`Exited;.z.P);savedb[];discconn[];};

loaddb:{[]if[count key x:` sv .conf[`feeddb`me];`.db set get x];};
savedb:{[](` sv .conf[`feeddb`me]) set .db;};
loadhdb:{[]if[count key x:` sv .conf[`histdb`me];`.hdb set get x];};
unloadhdb:{[]`.hdb set ()!();};
loadhist:{[x].[`.temp;enlist x;:;get ` sv .conf[`histdb],x];};
savehist:{[x]set[` sv .conf[`histdb],x;.temp[x]];};

//chkconn:{[]if[not `conn in key `.conf;:()];{[x]b:$[not x in key .ctrl.conn;1b;0>=.ctrl.conn[x;`h];1b;0b];if[b;h:@[hopen;.conf.conn[x]`addr;-1];if[0<h;.ctrl.conn[x]:`h`conntime!(h;.z.P)]];} each tkey .conf.conn;};

chkconn:{[]if[not `conn in key `.conf;:()];{[x]b:$[not x in key .ctrl.conn;1b;0>=.ctrl.conn[x;`h];1b;0b];if[b;h:@[hopen;(`${[x]y:string x;$[-7h=type x;"::",y;y],$[2<count ss[y;":"];"";.conf.appconn]} .conf.conn[x]`addr;(30+rand 50)^jfill .conf.conn[x]`tmout);-1];if[0<h;.ctrl.conn[x]:`h`conntime!(h;.z.P)]];} each tkey .conf.conn;};

discconn:{[];if[not `conn in key `.ctrl;:()];{[x]if[0<h:.ctrl.conn[x]`h;hclose[h]];} each tkey .ctrl.conn;};

chksub:{[]if[not `sub in key `.conf;:()];{[x]if[not x in key `.ctrl.conn;:()];if[0>=h:.ctrl.conn[x;`h];:()];b:$[not x in key .ctrl.sub;1b;not .ctrl.sub[x;`sub]];if[b;{x (".u.sub";z;.conf.sub[y;z])}[h;x] each tkey .conf.sub[x];.ctrl.sub[x]:`sub`subtime!(1b;.z.P)]} each tkey .conf.sub;};

pub:{[t;x]if[null d:.conf[`pubto];:()];h:.ctrl.conn[d;`h];$[-6h<>type h;();0>=h;();[neg[h] (".u.upd";t;value flip update src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np from x);.db.seq+:1]];};
pubmx:{[x;y;z;w;d]pub[`sysmsg;enlist `sym`typ`ref`msg`vbin!(x;y;z;w;d)];};pubm:pubmx[;;;;`byte$()]; /(sym;typ;ref;msg)

weekdayshift:{[d;x]y:weekday[x];x+$[d;$[y=4;3;y=5;2;1];neg $[y=0;3;y=6;2;1]]}; /[direction(>0:next;<=0:prev);.z.D]下(上)一工作日(扣除周末)
nextweekday:weekdayshift[1b]; /[.z.D]下一工作日(扣除周末)
prevweekday:weekdayshift[0b]; /[.z.D]上一工作日(扣除周末)

workdayshift:{[d;x]z:weekdayshift[d;x];w:.conf[`holidayreglist];$[z in $[11h=type w;.conf.holiday inter (inter/).conf[`regholiday] w;.conf.holiday];.z.s[d;z];z]}; /[direction(>0:.z.D]Tx平台全局下(上)一工作日(扣除周末及假日)
nextworkday:workdayshift[1b]; /[.z.D]下一工作日(扣除周末及假日)
prevworkday:workdayshift[0b]; /[.z.D]上一工作日(扣除周末及假日)

istrdatex:{[r;x]y:weekday[x];(y<5)&not x in .conf.regholiday[r]}; /[region;date]某交易区域当日是否为工作日
istrdate:istrdatecn:istrdatex[`cn];istrdatehk:istrdatex[`hk];

nextrdatex:{[r;x]z:nextweekday[x];$[z in .conf.regholiday[r];.z.s[r;z];z]}; /[region;date]某交易区域下一工作日
nextrdate:nextrdatecn:nextrdatex[`cn];nextrdatehk:nextrdatex[`hk];

prevtrdatex:{[r;x]z:prevweekday[x];$[z in .conf.regholiday[r];.z.s[r;z];z]}; /[region;date]某交易区域上一工作日
prevtrdate:prevtrdatecn:prevtrdatex[`cn];prevtrdatehk:prevtrdatex[`hk];

difftrdatex:{[r;x;y](1+x-y)-sum {[r;x](in [x;.conf.regholiday[r]])|5<=weekday[x]}[r] y+til [x-y]}; /[reginon;d1;d0]计算区间[d0,d1]共包含几个区域交易日
difftrdate:difftrdatecn:difftrdatex[`cn];difftrdatehk:difftrdatex[`hk];

beginofday:{[x]h:.ctrl.conn[.conf.pubto;`h];if[-6h<>type h;:()];if[x<=h[`.u.d];:()];neg[h] (`.u.beginofday;x);pubm[`ALL;`BeginOfDay;.conf.me;string x];};

sysalarm:{[x;y]pubm[`ALL;`Alarm;x;-3!y];}; /[ref;msg]

wlog:{[x;y;z]if[(`int$`.enum.loglevels$x)>`int$`.enum.loglevels$.conf.loglevel;:()];z:$[10h=type z;z;-3!z];.db.LOG,:(x;y;z;now[]);pub[`syslog;enlist `sym`typ`msg!(x;y;z)];};
lerr:wlog[`error];lwarn:wlog[`warn];linfo:wlog[`info];ldebug:wlog[`debug];llocal:{[y;z]x:`local;z:$[10h=type z;z;-3!z];.db.LOG,:(x;y;z;now[]);};

.upd.sysmsg:{[x]{.upd[x`typ][x]} each x;}; /sysmsg,:x;
.upd.syslog:{[x]}; /syslog,:x;

upd:{[t;x]$[t in tables[];[if[1b~.conf[`dumpapi];insert[t;update dsttime:.z.P from x]];.upd[t;x]];lerr[`unknown_msgtyp;t]];};

.disp.base:{[x](`me`id#.conf),`boottime`inittime#.ctrl};

display:{(,/) `_.disp[;]};

.timer.task:{[x]if[1b~.conf`disabletask;:()];{[x;now]y:.db.TASK[x;`firetime];d:`date$y;t:`time$y;w:d-`week$y;w0:.db.TASK[x;`weekmin];w1:.db.TASK[x;`weekmax];d0:.db.TASK[x;`datemin];d1:.db.TASK[x;`datemax];t0:.db.TASK[x;`timemin];t1:.db.TASK[x;`timemax];ff:.db.TASK[x;`firefreq];z:.db.TASK[x;`firetime]+ff;if[z<now;z+:ff*ceiling (now-z)%ff];if[(w>=w0)&((w<=w1)|(null w1))&(d>=d0)&((d<=d1)|(null d1))&(t>=t0)&((t<=t1)|(null t1));zp:.z.P;r:.[{$[0>type x;value;::]x} .db.TASK[x;`handler];(x;now);()];.db.TASK[x;`lastfire]:(zp;.z.P;r);if[not 1b~r;lwarn[`taskrun;(x;now;r)]]];$[(null z)|(not null d1)&(d1<`date$z);.db.TASK[x;`expire]:1b;.db.TASK[x;`firetime]:z];}[;x] each exec id from .db.TASK where not expire,not null handler,firetime<=x;};

.zpc.base:{[x]{if[x=.ctrl.conn[y;`h];.ctrl.conn[y;`h`disctime]:(-1;.z.P);if[y in key `.ctrl.sub;.ctrl.sub[y;`sub]:0b]]}[x] each tkey .ctrl.conn;};

.upd.BeginOfDay:{[x].ctrl[`rollstart]:.z.P;{@[.roll[x];y;()]}[;"D"$x`msg] each (reverse key .roll) except `;.Q.gc[];.ctrl[`rollend]:.z.P;savedb[];};

newseq:{[]:.db.seq+:1};newidl:{[]`$string newseq[]};newid:{[]` sv .conf.id,`$string newseq[]};newseq0:{[]:.db.seq0+:1};newidl0:{[]`$string newseq0[]};newid0:{[]` sv .conf.id,`$string newseq0[]};
fs2se:{[x]`$"." vs string x};se2fs:{[x]`$"." sv string x};fs2e:{last fs2se x};fs2s:{first fs2se x};
now:{.z.P};ntd:{.z.D};vtd:{.db.sysdate};
clearapi:{[]{delete from x;@[x;`sym;`g#];} each {x where 98h=type each value each x} tables[]};
cleartemp:{[]{[x]if[0<=type y:.temp[x];.temp[x]:0#y]} each key `.temp;};

setstate:{[x;y]if[(null y)|(y~y0:.ctrl.StateMap[x]);:()];t0:.ctrl.StateEnter[x];t:now[];$[y~`OK;if[not null y0;lwarn[`ExitAlarm;(x;y0;t0;t;t-t0)];sysalarm[`Leave;x]];[lwarn[`EnterAlarm;(x;y;t)];sysalarm[`Enter;x]]];.ctrl.StateMap[x]:y;.ctrl.StateEnter[x]:t;}; /[ID;State]

updstate:{[x;y;z]m:.conf.me;t0:.db.S[m,x,y;`entertime];t:now[];z0:.db.S[m,x,y;`active];.db.S[m,x,y;`active`updtime]:(z;t);if[z0&not z;.db.S[m,x,y;`leavetime]:t;lwarn[`LeaveState;(m;x;y;t0;t;t-t0)];sysalarm[`LeaveState;m,x,y]];if[(not z0)&z;.db.S[m,x,y;`entertime]:t;lwarn[`EnterState;(m;x;y;t)];sysalarm[`EnterState;m,x,y]];}; /[ref;state;active]

loadhdbtask:{[x;y]loadhdb[];1b};
unloadhdbtask:{[x;y]unloadhdb[];.Q.gc[];1b};
cleartemptask:{[x;y]cleartemp[];.Q.gc[];1b};
savedbtask:{[x;y]savedb[];1b};
fixrolldatetask:{[x;y]z:.z.D;$[.z.T<=.conf.dayendtime;if[.db.sysdate<z;.db.sysdate:z];if[.db.sysdate<=z;.db.sysdate:nextworkday[z]]];1b};

if[not `boot in key `.ctrl;.base.boot[]];

//----ChangeLog----
//2025.02.19:新增定义weekdayshift和workdayshift,并依此重新定义nextweekday/prevweekday/nextworkday/prevworkday
//2024.09.23:chkconn增加对addr已包含用户名的密码的兼容处理
//2024.05.30:.timer.task增加支持参数disabletask
//2024.05.15:修改nextworkday,将.conf[`holidayexlist`exholiday]替换为.conf[`holidayreglist`regholiday]并相应修改相关配置文件,新增nextweekday/prevweekday/nextrdatex/prevtrdatex/difftrdatex/istrdatex/并修改nextworkday/difftrdate函数
//2024.03.18:新增fixrolldatetask以支持dayroll处理失败的情形通过定时任务修复.db.sysdate
//2024.02.20:新增savedbtask函数以支持通过TASK任务盘中定时存盘降低因为进程崩溃丢失数据的风险
//2023.12.22:clearapi增加对key表过滤
//2023.04.27:O表新增exchid和cexchid两列
//2022.10.11:{nextworkday} add support for multiple exchanges. should add .conf.holidayexlist to cfbase.q  

\
.db.TASK[`SAVEDB;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+16:15;1D;0;4;`savedbtask);
.db.TASK[`SAVEDBNS;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+02:35;1D;1;5;`savedbtask);
.db.TASK[`FIXROLLDATE;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:56;1D;1;5;`fixrolldatetask);