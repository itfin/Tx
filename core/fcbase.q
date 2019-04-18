/runq Tx/core/base.q -conf cffc0 -code "txload \"core/fcbase\"" -p 5000

.module.fcbase:2017.01.25;

.ctrl.Cmd:()!();
.ctrl.H:()!();
.ctrl.poweroff:0b;
.ctrl.poweroffbegin:0Np;
.ctrl.shutdowntime:0Np;

//.init.fc:{[]conntx[];};

starttx:{[]startmod each .conf.modules;};
stoptx:{[]stopmod each reverse .conf.modules;};
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

connmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];p:(y:.conf[x])`port;.ctrl.H[x]:@[hopen;$[(a:y`ip) in ``127.0.0.1,.conf.ha[.conf.ha.node;`ip];`$"::",":" sv string p,$[x like "fu*";.conf.me,.conf.fcpass;.conf.appuser,.conf.apppass];`$":",":" sv string a,p,$[x like "fu*";.conf.me,.conf.fcpass;.conf.appuser,.conf.apppass]];-1]};

stopmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];0N!"stopping ",string[x],"...";if[(0=count .ctrl.H[x])|-1~.ctrl.H[x];connmod[x]];if[0<h:.ctrl.H[x];@[h;"exit 0";()];.ctrl.H[x]:-1];0N!"done.\n";};

startmod:{[x]if[not x in .conf.modules,.conf.modules1;:`err_name];0N!"starting ",string[x],"...";system modstartcmd x;system "sleep 0.25";connmod[x];0N!$[0<.ctrl.H[x];"Done.";"Failed."];};

modstartcmd:{[x]p:(y:.conf[x])`port;z:string x;r:not (a:y`ip) in ``127.0.0.1,.conf.ha[.conf.ha.node;`ip];:.ctrl.Cmd[x]:$[r;"ssh root@",(string a)," '";""],"sh -c cd ",.conf.wd," && taskset -c ",("," sv string raze y`cpu)," nohup ",.conf.qbin," ",($[r;ssr[;"'";"'\"'\"'"];::] cfill y[`args]),.conf.qcl,(cfill y[`qcl])," -p ",(string p)," </dev/null >/tmp/",z,".",(string .conf.app)," 2>&1&",$[r;"'&";""]};

stopnode:{[x]if[x in .conf.ha.nodelist;stopmod each .conf.ha[x;`modules]];};
startnode:{[x]if[x in .conf.ha.nodelist;startmod each .conf.ha[x;`modules]];};

gcall:{[x;y]if[0=count H:{x where 0<x} .ctrl.H;:()];neg[H]@\:(`.Q.gc;());1b};

ping:{[x]y:string x;z:system "ping -c 1 ",y;raze z};
pingok:@[ping;;()];

doshutdown:{[]if[null .ctrl.shutdowntime;.ctrl.shutdowntime:.z.P];stopnode .conf.ha.node;system "poweroff";};

checkpower:{[x;y].ctrl.powerchkbegin:.z.P;z:pingok .conf.powerchkip;.ctrl[`powerchkend`powerchkres]:(.z.P;z);$[count z;if[1b~.ctrl[`poweroff];.ctrl[`poweroff`poweroffbegin]:(0b;0Np)];$[0b~.ctrl[`poweroff];.ctrl[`poweroff`poweroffbegin]:(1b;.z.P);if[.z.P>.ctrl.poweroffbegin+.conf.powertmout;doshutdown[]]]];1b};

rmoldapifiles:{[x;y]{[x]y:"D"$-10#string x;if[y<.z.D-10;system "rm -f ",1_string sv[`;.conf.tickdb,x]]} each (key .conf.tickdb) except `api;1b};

comparedb:{[x;y]if[not (~/) .ctrl.H[`ft`ft1] @\: `.db.P;alert["system error!";"pos diff!"];:0b];1b};

\
