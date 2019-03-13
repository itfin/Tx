.module.base:2018.01.05;

txload:{[x]@[system;"l Tx/",x,".q";`txload];};
cfload:{[x]txload "conf/",x;};
txload "lib/handy";
txload "lib/extutil";
txload "lib/math";

\l tick/u.q
.u.init[];

txload "core/api";
txload "core/enum";
txload "core/dotz";
txload "core/habase";

\d .ctrl
conn:.enum.nulldict;
sub:.enum.nulldict;
\d .

.temp:.enum.nulldict;

\d .db
seq:0;
sysdate:.z.D;
TASK:([id:`symbol$()] expire:`boolean$(); firetime:`timestamp$(); firefreq:`timespan$(); datemin:`date$(); datemax:`date$(); weekmin:`int$(); weekmax:`int$(); timemin:`time$(); timemax:`time$(); handler:(); lastfire:());

QX:([`u#sym:`symbol$()] ex:`symbol$(); esym:`symbol$(); name:`symbol$(); ticker:`symbol$(); status:`int$(); mode:`symbol$(); open:`float$(); vwap:`float$(); size:`float$(); sup:`float$(); inf:`float$(); pc:`float$(); scale:`float$(); date:`date$(); time:`timespan$(); price:`float$(); cumqty:`float$(); cumamt:`float$(); high:`float$(); low:`float$(); bid:`float$(); bsize:`float$(); ask:`float$(); asize:`float$(); bidQ:0#enlist`float$(); bsizeQ:0#enlist`float$(); askQ:0#enlist`float$(); asizeQ:0#enlist`float$(); openint:`float$(); settlepx:`float$(); quoopt:(); refopt:();  recvtime:`timestamp$(); extime:`timestamp$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); nticks:`long$(); settledate:`date$(); settleperiod:`int$(); industry:`symbol$(); underlying:`symbol$(); assetclass:`symbol$(); product:`symbol$(); multiplier:`float$(); pxunit:`float$(); qtylot:`float$(); qtyscale:`float$(); qtyminl:`float$(); qtymins:`float$(); qtymax:`float$(); qtymaxm:`float$(); qtymaxl:`float$(); qtymaxs:`float$(); margintype:`symbol$(); rmarginl:`float$(); rmargins:`float$(); rmarginoq:`float$(); rmarginmq:`float$(); rmarginioq:`float$(); rmarginimq:`float$(); rfeetaxoa:`float$(); rfeetaxoq:`float$(); rfeetaxca:`float$(); rfeetaxcq:`float$(); rfeetaxcat:`float$(); rfeetaxcqt:`float$(); rfeetaxom:`float$(); rfeetaxcm:`float$(); rfeetaxctm:`float$(); date1:`date$(); time1:`time$(); opendate:`date$(); createdate:`date$(); lifephase:`symbol$(); currency:`symbol$(); putcall:`symbol$(); optexec:`symbol$(); optsettle:`symbol$(); strikepx:`float$(); isin:`symbol$(); cficode:`symbol$(); sectype:`symbol$(); secclass:`symbol$(); secstatus:`symbol$(); tradetype:`symbol$(); tradephase:`symbol$(); suspendtype:`symbol$(); state:`symbol$(); remark:`symbol$(); sec_key:`symbol$(); ex1:`symbol$(); cficode:`symbol$(); notice:`symbol$() ); /L1 Static

LOG:([]sym:`symbol$();typ:`symbol$();msg:0#enlist "";logtime:`timestamp$());

O1:O:([`u#id:`symbol$()] ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); fe:`symbol$(); acc1:`symbol$(); ref:`symbol$(); sym:`symbol$(); side:`char$(); posefct:`char$(); tif:`char$(); typ:`char$(); qty:`float$(); price:`float$();end:`boolean$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); lastqty:`float$(); lastpx:`float$(); feoid:`symbol$(); ordid:`symbol$(); cstatus:`char$(); cn:`int$(); ntime:`timestamp$(); ctime:`timestamp$(); msg:(); cumamt:`float$(); cumfee:`float$(); qtime:`timestamp$(); jtime:`timestamp$(); ftime:`timestamp$(); rtime:`timestamp$(); reason:`int$(); ordopt:(); rptopt:(); cid:`symbol$(); cfeoid:`symbol$(); cordid:`symbol$(); qn:`int$(); special:`symbol$(); origid:`symbol$(); ex:`symbol$(); esym:`symbol$(); x0:()); /Order

M:([`u#id:`symbol$()] sym:`symbol$(); price:`float$(); qty:`float$(); mtime:`timestamp$(); maker:`symbol$(); taker:`symbol$()); /Match

P:([ts:`symbol$(); acc:`symbol$(); sym:`symbol$()] lqty:`float$();  sqty:`float$(); flqty:`float$(); fsqty:`float$(); lqty0:`float$(); sqty0:`float$(); flqty0:`float$(); fsqty0:`float$()); /Postion

QT:([id:`u#`symbol$()] qrid:`symbol$(); bid:`symbol$(); aid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); fe:`symbol$(); acc1:`symbol$(); ref:`symbol$();sym:`symbol$(); bprice:`float$(); aprice:`float$(); bqty:`float$(); aqty:`float$(); bposefct:`char$(); aposefct:`char$(); status:`char$(); bcumqty:`float$(); acumqty:`float$(); bavgpx:`float$(); aavgpx:`float$(); feqid:`symbol$(); quoteid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cfeqid:`symbol$(); cquoteid:`symbol$(); ntime:`timestamp$(); ctime:`timestamp$(); rtime:`timestamp$(); reason:`int$(); msg:(); rptopt:(); cn:`int$(); linkid:`symbol$()); /Quote

\d .

.init.base:{[x].ctrl.init:1b;loaddb[];.ctrl[`status`inittime]:(`Inited;.z.P);};
.timer.base:{[x]if[not `init in key `.ctrl;.init[;x];];chkconn[];chksub[];};
.roll.base:{[x]clearapi[];cleartemp[];.[.conf.histdb;(.conf.me;`LOG);,;.db.LOG];delete from `.db.LOG;.db.sysdate:x;savedb[];};

.base.boot:{[].ctrl[`boot`boottime]:(1b;.z.P);system "S ",string `int$.z.T;.base.cmdopt:first each .Q.opt .z.x;if[count cf:.base.cmdopt`conf;cfload cf];if[count cd:.base.cmdopt`code;@[value;cd;()]];};

.exit.base:{[x].ctrl[`status`exittime]:(`Exited;.z.P);savedb[];discconn[];};

loaddb:{[]if[count key x:` sv .conf[`feeddb`me];`.db set get x];};
savedb:{[](` sv .conf[`feeddb`me]) set .db;};
loadhdb:{[]if[count key x:` sv .conf[`histdb`me];`.hdb set get x];};
loadhist:{[x].[`.temp;enlist x;:;get ` sv .conf[`histdb],x];};
savehist:{[x]set[` sv .conf[`histdb],x;.temp[x]];};

//chkconn:{[]if[not `conn in key `.conf;:()];{[x]b:$[not x in key .ctrl.conn;1b;0>=.ctrl.conn[x;`h];1b;0b];if[b;h:@[hopen;.conf.conn[x]`addr;-1];if[0<h;.ctrl.conn[x]:`h`conntime!(h;.z.P)]];} each tkey .conf.conn;};

chkconn:{[]if[not `conn in key `.conf;:()];{[x]b:$[not x in key .ctrl.conn;1b;0>=.ctrl.conn[x;`h];1b;0b];if[b;h:@[hopen;({$[-7h=type x;`$"::",string x;x]} .conf.conn[x]`addr;(30+rand 50)^jfill .conf.conn[x]`tmout);-1];if[0<h;.ctrl.conn[x]:`h`conntime!(h;.z.P)]];} each tkey .conf.conn;};

discconn:{[];if[not `conn in key `.ctrl;:()];{[x]if[0<h:.ctrl.conn[x]`h;hclose[h]];} each tkey .ctrl.conn;};

chksub:{[]if[not `sub in key `.conf;:()];{[x]if[not x in key `.ctrl.conn;:()];if[0>=h:.ctrl.conn[x;`h];:()];b:$[not x in key .ctrl.sub;1b;not .ctrl.sub[x;`sub]];if[b;{x (".u.sub";z;.conf.sub[y;z])}[h;x] each tkey .conf.sub[x];.ctrl.sub[x]:`sub`subtime!(1b;.z.P)]} each tkey .conf.sub;};

pub:{[t;x]h:.ctrl.conn[.conf.pubto;`h];$[-6h<>type h;();0>=h;();[neg[h] (".u.upd";t;value flip update src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np from x);.db.seq+:1]];};
pubmx:{[x;y;z;w;d]pub[`sysmsg;enlist `sym`typ`ref`msg`vbin!(x;y;z;w;d)];};pubm:pubmx[;;;;`byte$()]; /(sym;typ;ref;msg)

nextworkday:{[x]y:weekday[x];z:x+$[y=4;3;y=5;2;1];$[z in .conf.holiday;.z.s[z];z]};

beginofday:{[x]h:.ctrl.conn[.conf.pubto;`h];if[-6h<>type h;:()];if[x<=h[`.u.d];:()];neg[h] (`.u.beginofday;x);pubm[`ALL;`BeginOfDay;.conf.me;string x];};

wlog:{[x;y;z]if[(`int$`.enum.loglevels$x)>`int$`.enum.loglevels$.conf.loglevel;:()];z:$[10h=type z;z;-3!z];.db.LOG,:(x;y;z;.z.P);pub[`syslog;enlist `sym`typ`msg!(x;y;z)];};
lerr:wlog[`error];lwarn:wlog[`warn];linfo:wlog[`info];ldebug:wlog[`debug];

.upd.sysmsg:{[x]sysmsg,:x;{.upd[x`typ][x]} each x;};
.upd.syslog:{[x]syslog,:x;};

upd:{[t;x]$[t in tables[];[if[1b~.conf[`dumpapi];insert[t;update dsttime:.z.P from x]];.upd[t;x]];lerr[`unknown_msgtyp;t]];};

.timer.task:{[x]{[x;now]y:.db.TASK[x;`firetime];d:`date$y;t:`time$y;w:d-`week$y;w0:.db.TASK[x;`weekmin];w1:.db.TASK[x;`weekmax];d0:.db.TASK[x;`datemin];d1:.db.TASK[x;`datemax];t0:.db.TASK[x;`timemin];t1:.db.TASK[x;`timemax];ff:.db.TASK[x;`firefreq];z:.db.TASK[x;`firetime]+ff;if[z<now;z+:ff*ceiling (now-z)%ff];if[(w>=w0)&((w<=w1)|(null w1))&(d>=d0)&((d<=d1)|(null d1))&(t>=t0)&((t<=t1)|(null t1));r:.[{$[0>type x;value;::]x} .db.TASK[x;`handler];(x;now);()];.db.TASK[x;`lastfire]:(.z.P;r)];$[(null z)|(not null d1)&(d1<`date$z);.db.TASK[x;`expire]:1b;.db.TASK[x;`firetime]:z];}[;x] each exec id from .db.TASK where not expire,not null handler,firetime<=x;};

.zpc.base:{[x]{if[x=.ctrl.conn[y;`h];.ctrl.conn[y;`h`disctime]:(-1;.z.P);if[y in key `.ctrl.sub;.ctrl.sub[y;`sub]:0b]]}[x] each tkey .ctrl.conn;};

.upd.BeginOfDay:{[x].ctrl[`rollstart]:.z.P;.roll[;"D"$x`msg];.Q.gc[];.ctrl[`rollend]:.z.P;};

newseq:{[]:.db.seq+:1};newidl:{[]`$string newseq[]};newid:{[]` sv .conf.id,`$string newseq[]};
fs2se:{[x]`$"." vs string x};se2fs:{[x]`$"." sv string x};fs2e:{last fs2se x};fs2s:{first fs2se x};
now:{.z.P};ntd:{.z.D};
clearapi:{[]{delete from x;@[x;`sym;`g#];} each tables[]};
cleartemp:{[]{[x]if[0<=type y:.temp[x];.temp[x]:0#y]} each key `.temp;};

if[not `boot in key `.ctrl;.base.boot[]];