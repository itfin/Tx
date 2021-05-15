/runq Tx/core/base.q -conf cffc0 -code "txload \"core/fcbase\"" -p 5000

.module.fcbase:2021.04.13;

\d .temp
NS:([]stime:`timestamp$();id:`symbol$();cpu:`float$();mem:`float$();swap:`float$();disk:`float$();cores:());
MS:([]stime:`timestamp$();id:`symbol$();delay:`float$();mem:`float$());
\d .

\d .ctrl
Cmd:()!();
H:()!();
poweroff:0b;
poweroffbegin:0Np;
shutdowntime:0Np;
sysstart:sysstop:0Np;
NOD:([id:`symbol$()]backup:`symbol$();ip:`symbol$();portoffset:`long$();cpufreq:`float$();cpucores:`long$();mem:`float$();swap:`float$();diskdev:`symbol$();disk:`float$();uptime:`timestamp$();cpuuse:`float$();memuse:`float$();swapuse:`float$();diskuse:`float$();coreuse:());
MOD:([id:`symbol$()]mtyp:`symbol$();node:`symbol$();ip:`symbol$();port:`long$();cores:();h:`long$();pid:`long$();starttime:`timestamp$();stoptime:`timestamp$();hbsent:`timestamp$();hbpeer:`timestamp$();hbrecv:`timestamp$();mem:`float$());
\d .

.init.fc:{[]initnod[];initmod[];conntx[];}; /

nod_init:{[x].ctrl.NOD[x;`ip`portoffset`backup]:.conf.ha[x;`ip`portoffset`backup];s:nodecmd[x;"lscpu"];.ctrl.NOD[x;`cpufreq`cpucores]:(1e-3*"F"$last vs[2#" "]  s[15];"J"$last vs[2#" "]  s[4]);s:nodecmd[x;"free"];.ctrl.NOD[x;`mem`swap]:(1%1024 xexp 2)*{"F"$@[;1] vs[" ";x] except enlist ""} each s[1 2];s:nodecmd[x;"df -l --output=source,size"];r:(!/)"SF"$flip {vs[" ";x] except enlist ""} each 1_s;.ctrl.NOD[x;`diskdev`disk]:(first where r=max r;(1%1024 xexp 3)*max r);s:nodecmd[x;"uptime -s"];.ctrl.NOD[x;`uptime]:"P"$first s;}; /-t ext4

initnod:{[]@[nod_init;;()] each .conf.ha.nodelist;};

mod_init:{[x] .ctrl.MOD[x;`mtyp`node`cores`ip`port]:($[x in .conf.module_tick;$[x like "tp*";`tp;x like "rdb*";`rdb;`hdb];$[x in .conf.module_ft;`ft;x in .conf.module_ft;`ft;x in .conf.module_fq;`fq;x in .conf.module_fe;`fe;x in .conf.module_fu;`fu;x in .conf.module_fa;`fa;`fp]];exec first id from .ctrl.NOD where ip=.conf[x;`ip];{$[0>type x;enlist x;x]} .conf[x;`cpu]),.conf[x;`ip`port]}; 

initmod:{[]@[mod_init;;()] each .conf.modules;};

starttx:{[].db.txstart:.z.P;startmod each .conf.modules;};
stoptx:{[]stopmod each reverse .conf.modules;.db.txstop:.z.P;};
conntx:{[]connmod each .conf.modules;};

starttick:{[]startmod each .conf.module_tick;};
stoptick:{[]stopmod each reverse .conf.module_tick;};

startfeed:{[]startmod each .conf.module_feed;};
stopfeed:{[]stopmod each reverse .conf.module_feed;};

startctp:{[x;y]startmod each .conf.module_ctp;1b};
stopctp:{[x;y]stopmod each reverse .conf.module_ctp;system "rm -rf /tmp/CTP*";1b};

starttws:{[]startmod each .conf.module_tws;};
stoptws:{[]stopmod each reverse .conf.module_tws;};

startgw:{[x;y]startmod each .conf.module_gw;};
stopgw:{[x;y]stopmod each .conf.module_gw;};

startdaily:{[x;y] {if[(1b~.conf[x;`daily])&not .z.D in .conf.holiday;startmod x]} each .conf.modules;1b};
stopdaily:{[x;y] {if[(1b~.conf[x;`daily])&not .z.D in .conf.holiday;stopmod x]} each reverse .conf.modules;system "rm -rf /tmp/CTP*";1b};

startnightly:{[x;y] {if[(1b~.conf[x;`nightly])&not .z.D in .conf.holiday;startmod x]} each .conf.modules;1b};
stopnightly:{[x;y] {if[(1b~.conf[x;`nightly])&not .z.D in .conf.holiday;stopmod x]} each reverse .conf.modules;system "rm -rf /tmp/CTP*";1b};

connmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];p:(y:.conf[x])`port;.ctrl.MOD[x;`h]:.ctrl.H[x]:h:@[hopen;$[(a:y`ip) in ``127.0.0.1,.conf.ha[.conf.ha.node;`ip];`$"::",":" sv string p,$[x like "fu*";.conf.me,.conf.fcpass;x like "*sim*";`simuser`simpass;.conf.appuser,.conf.apppass];`$":",":" sv string a,p,$[x like "fu*";.conf.me,.conf.fcpass;x like "*sim*";`simuser`simpass;.conf.appuser,.conf.apppass]];-1];if[h>0;.ctrl.MOD[x;`pid]:h `.z.i;];};

stopmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];0N!"stopping ",string[x],"...";if[(0=count .ctrl.H[x])|-1~.ctrl.H[x];connmod[x]];if[0<h:.ctrl.H[x];@[h;"exit 0";()];.ctrl.H[x]:-1;.ctrl.MOD[x;`h`stoptime]:(-1;.z.P)];0N!"done.\n";};

startmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];0N!"starting ",string[x],"...";system modstartcmd x;system "sleep 0.25";connmod[x];if[0<h:.ctrl.H[x];.ctrl.MOD[x;`starttime]:.z.P];0N!$[0<h;"Done.";"Failed."];};

modstartcmd:{[x]p:(y:.conf[x])`port;z:string x;r:not (a:y`ip) in ``127.0.0.1,.conf.ha[.conf.ha.node;`ip],$[(::)~b:.conf.ha[.conf.ha.node;`ipx];`symbol$();b];:.ctrl.Cmd[x]:$[r;"ssh root@",(string a)," '";""],"sh -c cd ",.conf.wd," && ",cfill[y`env],$[`bsd~.conf[`ostype];" cpuset -l ";" taskset -c "],("," sv string raze mod[;$[r;1000;.ctrl.NOD[.conf.ha.node;`cpucores]]] y`cpu)," nohup ",.conf.qbin," ",($[r;ssr[;"'";"'\"'\"'"];::] cfill y[`args]),$[1<count y`qclfull;y`qclfull;.conf.qcl,(cfill y[`qcl])]," -p ",$[1b~y`bindip;string[a],":";1b~.conf[`bindlocal];"127.0.0.1:";""],(string p)," </dev/null >>/tmp/",z,".",(string .conf.app)," 2>&1&",$[r;"'&";""]};

nodecmd:{[x;y].temp.cmd:cmd:$[x~.conf.ha.node;y;"ssh root@",(string .conf.ha[x;`ip])," 'sh -c \"",y,"\"'"];system cmd}; /[½Úµãid;shell ÃüÁî]

.zpc.fcbase:{[x]m:exec first id from .ctrl.MOD where h=x;if[not null m;.ctrl.MOD[m;`h`stoptime]:(-1;.z.P);.ctrl.H[m]:-1];};

stopnode:{[x]if[x in .conf.ha.nodelist;stopmod each .conf.ha[x;`modules]];};
startnode:{[x]if[x in .conf.ha.nodelist;startmod each .conf.ha[x;`modules]];};

gcall:{[x;y]if[0=count H:{x where 0<x} .ctrl.H;:()];neg[H]@\:(`.Q.gc;());1b};

hball:{[x;y]{.ctrl.MOD[x;`hbsent]:.z.P;neg[.ctrl.MOD[x;`h]] ({[x]t:.z.P;neg[.z.w] ({[x;y;z]w:.z.P;.ctrl.MOD[x;`hbpeer`hbrecv`mem]:(y;w;z);d:1e-9*w-u:.ctrl.MOD[x;`hbsent];.temp.MS,:enlist (w;x;d;z);if[d>=.conf`maxdelay;lwarn[`delaytoolong;(x;d;u;y;w)]]};x;t;1e-6*.Q.w[]`heap)};x)} each exec id from .ctrl.MOD where 0<h;1b}; /mod heartbeat

nhall:{[x;y]{s:nodecmd[x;"mpstat -P ALL 1 1"];cu:1-1e-2*"F"$last flip {x where 13=count each x} {vs[" ";x] except enlist ""}each 3_s;s:nodecmd[x;"df -l -t ext4 --output=source,size,avail|grep ",string .ctrl.NOD[x;`diskdev]];du:1-last ratios "F"$-2#(vs[" "] s[0]) except enlist "";s:nodecmd[x;"free"];mu:{last ratios "F"$2#(1_vs[" "] x) except enlist ""}each 1_s;.temp.NS,:enlist (.z.P;x),.ctrl.NOD[x;`cpuuse`memuse`swapuse`diskuse`coreuse]:(cu[0];mu[0];mu[1];du;1_cu);if[any all each .conf[`maxcoreuse]<= flip first value flip select [neg[.conf.corechklen]]  cores from .temp.NS where id=x;lwarn[`cputoohigh;(x;cu)]]} each exec id from .ctrl.NOD;1b}; /nodehealth

ping:{[x]y:string x;z:system "ping -c 1 ",y;raze z};
pingok:@[ping;;()];

doshutdown:{[]if[null .ctrl.shutdowntime;.ctrl.shutdowntime:.z.P];stopnode .conf.ha.node;system "poweroff";};

checkpower:{[x;y].ctrl.powerchkbegin:.z.P;z:pingok .conf.powerchkip;.ctrl[`powerchkend`powerchkres]:(.z.P;z);$[count z;if[1b~.ctrl[`poweroff];.ctrl[`poweroff`poweroffbegin]:(0b;0Np)];$[0b~.ctrl[`poweroff];.ctrl[`poweroff`poweroffbegin]:(1b;.z.P);if[.z.P>.ctrl.poweroffbegin+.conf.powertmout;doshutdown[]]]];1b};

rmoldapifiles:{[x;y]{[x]y:"D"$-10#string x;if[y<.z.D-10;system "rm -f ",1_string sv[`;.conf.tickdb,x]]} each (key .conf.tickdb) except `api;1b};

comparedb:{[x;y]if[not (~/) .ctrl.H[`ft`ft1] @\: `.db.P;alert["system error!";"pos diff!"];:0b];1b};

chkmodstatus:{[x]if[not .z.T within 08:58 15:00;:()];{[x]lerr[`modoffline;enlist x]} each exec id from .ctrl.MOD where 0>=h;}; /check modules online status

chkfestatus:{[x]if[not .z.T within 09:00 15:00;:()];if[0>=h:.ctrl.MOD[`feufx;`h];:()];if[not 1b~h (`.ctrl.ufx;`login);lerr[`ufxloginfail;()]];}; /check ufx login

chkfqstatus:{[x]t:.z.T;if[(not t within 09:00 15:00)|t within 11:30 13:00:03;:()];if[0>=h:.ctrl.MOD[`rdb;`h];:()];r:h ({[x]exec `time$last time by src from quote};());{[r;t;x]if[r[x]<t-00:00:02;lwarn[`quotehalt;(x;t;r`x)]]}[r;t] each enlist `fqctp;if[t<09:30;:()];{[r;t;x]if[r[x]<t-00:00:10;lwarn[`quotehalt;(x;t;r`x)]]}[r;t] each `fqxshe`fqxshg`fqxshgopt;}; /check fqsrc quote timestamp

chktpzw:{[x]t:.z.T;if[(not t within 09:00 15:00)|t within 11:30 13:00:03;:()];if[0>=h:.ctrl.MOD[`tp;`h];:()];if[.conf.maxzwlen<n:h ({sum sum each .z.W};());lwarn[`tpzwfull;(t;n)]];};

chkordstatus:{[x]t:.z.P;if[not (`time$t) within 09:00 15:00;:()];if[0>=h:.ctrl.MOD[`ft;`h];:()];{lwarn[`ordrejerr;x]} each h ({[x]exec {[x;y;z;w] sv["|"] string[x,y,z],enlist w}'[ft;ts;id;msg] from .db.O where status=.enum.REJECTED,ntime>=x};t-00:01:00);{lwarn[`ordcxlerr;x]} each h ({[x;y]flip exec (ft;ts;id) from .db.O where not end,not null ctime,ctime<x,ctime>=y};t-00:00:02;t-00:01:00);{lwarn[`ordnewerr;x]} each h ({[x;y]flip exec (ft;ts;id) from .db.O where not end,null ctime,null ordid,ntime<x,ntime>=y};t-00:00:02;t-00:01:00);}; /check ord cxl/new error

chketfstatus:{[x]:();if[not .z.T within 09:24 15:00;:()];if[0>=h:.ctrl.MOD[`fqxshe;`h];:()];el:h `.conf.etflist;if[0>=h:.ctrl.MOD[`ftdc4;`h];:()];r:h ({[x]exec last trday by sym from .db.ETF};());{[r;d;x]if[r[x]<>d;lwarn[`etfpcfdate;(x;d;r[x])]]}[r;.z.D] each el;}; /check etf pcf trday

chkmaxcxl:{[x]if[not .z.T within 09:00 15:00;:()];if[0>=h:.ctrl.MOD[`feufx;`h];:()];if[(r0:.conf.maxcxlratio)<=r1:h ({exec (max ncxl)%(exec last maxncxl from .db.RL) from .db.RN where sym like string exec last sym from .db.RL};());lwarn[`maxcxl;(.z.P;r0;r1)]];};

hc10:{[x;y]chkmodstatus[];chkfestatus[];chkfqstatus[];chkordstatus[];chketfstatus[];chktpzw[];chkmaxcxl[];1b}; /10s health check

chk300idx:{[x;y]r:.ctrl.H[`ft] ({x!{-1+(%/).db.QX[x;`price`pc]} each x};`000300.XSHG`510330.XSHG`159919.XSHE);if[0.005<=max[r]-min[r];lwarn[`300idxpriceerror;r]];1b};

chkonline:{[x;y]startmod each exec id from .ctrl.MOD where h<0,id in .conf.modules;1b};

\
.db.TASK[`CHK300;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+09:30:10;1D;0;4;`chk300idx);
.db.TASK[`CHKONLINE;`firetime`firefreq`weekmin`weekmax`timemin`timemax`handler]:(`timestamp$.z.D+08:55:00;`timespan$00:01;0;4;`time$08:56;`time$16:54;`chkonline);