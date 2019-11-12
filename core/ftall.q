.module.ftall:2018.04.16;

txload "core/ftbase";

.temp.M:();

pub:{[t;x]if[1b~.conf[`debug];.temp.M,:enlist (.z.P;t;x)];0 (".upd";t;`time xcols update src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np,time:`timespan$.z.T from x);.db.seq+:1;};

.upd.quote:{[x].db.QX:.db.QX lj y:select by sym from x;{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from y] each tsl[];}; //speedy by using lj

.upd.ordnew:.fe.ordnew;
.upd.ordcxl:.fe.ordcxl;

idfe2ft:{[x]exec first id from .db[.ctrl.O] where feoid=x};

.roll.fe:{[x]gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;.ctrl.O);,;select from .db[.ctrl.O] where end|tif<>gtc];$[`O=.ctrl.O;[delete from `.db.O where end|tif<>gtc;update `u#id from `.db.O];[delete from `.db.O1 where end|tif<>gtc;update `u#id from `.db.O1]];};

rejectord:{[x;y;z]if[null .db[.ctrl.O;x;`ft];:()];.db[.ctrl.O;x;`rtime`status`reason`msg]:(.z.P;.enum`REJECTED;y;z);riskstatrej[x];pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`corderid`reason`msg`rptopt!(.db[.ctrl.O;x;`ft];.enum`NEW;x;.enum`REJECTED;0f;0f;`;`;.enum`NULL;`;`;y;z;"")];}; /[oid;reason;msg]

execrpt:{[k]r:.db[.ctrl.O;k];if[null x:r`ft;:()];riskstatexe[k];pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(x;.enum`NEW;k),r[`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason],(cfill r`msg;cfill r`rptopt)];};

rejcxl:{[k;r;m]h:.db[.ctrl.O;k];rejectcxl[h`ft;k;h`cid;r;m];};
