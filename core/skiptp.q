pub:{[t;x]h:.ctrl.conn[.conf.pubto;`h];$[-6h<>type h;();0>=h;();[neg[h] (".upd";t;`time xcols update src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np,time:`timespan$.z.T from x);.db.seq+:1]];};
pubmx:{[x;y;z;w;d]pub[`sysmsg;enlist `sym`typ`ref`msg`vbin!(x;y;z;w;d)];};pubm:pubmx[;;;;`byte$()]; /(sym;typ;ref;msg)
if[`ft~.conf.feedtype;.upd.quote:{[x].db.QX:.db.QX lj y:select by sym from x;{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from y] each tsl[];};beginofday::{[x];pubm[`ALL;`BeginOfDay;.conf.me;string x];.upd.BeginOfDay[(enlist `msg)!enlist string x]};];

fqctpsyncqx:{[x;y]if[0>=z:.ctrl.conn[`ft1;`h];:()];.db.QX:z `.db.QX;1b};
