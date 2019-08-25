.module.fubase:2017.01.25;

txload "core/ftbase";

.zpc.fu:{[x]if[null k:exec first id from .db.U where h=x;:()];.db.U[k;`online`h`logouttime]:(0b;-1;.z.P);};

.z.pw:{[x;y].temp.x:x;.temp.y:y;a:`$"." sv string "i"$0x0 vs .z.a;if[(null .db.U[x;`name])|.db.U[x;`passwd]<>`$y;:0b];if[(.z.w<>h)&(0<h:.db.U[x;`h]);hclose[h]];.db.U[x;`online`h`logintime`loginip]:(1b;.z.w;.z.P;a);1b}; /[usr;pwd]

.z.ps:.z.pg:{[x]if[null u:.z.u;:value x];r:.db.U[u;`role];if[not r in ``admin;f:x[0];if[-11h<>type f;'errtype];if[not f in .db.R[r;`func];'noright];.db.U[u;`calltime`callfunc]:(.z.P;f)];value x};

.upd.tsparam:{[x]y:x`typ;z:x`ts;k:x`item;if[not z in key .db.Ts;:()];if[not k in key .db.Ts[z];:()];if[y="A";.db.Ts[z;k]:-9!x`vbin];}';

tsupd:{[x;y;z;m]if[null ft:.db.S[x;`ftlocal];:()];if[not .z.u in .db.S[x;`users];:()];if[not y in .db.SG[.db.S[x;`sgroup];`items];:()];pub[`tsparam;enlist `sym`typ`user`ts`item`vbin`msg!(ft;"S";.z.u;x;y;-8!z;m)];pub[`tsparam;enlist `sym`typ`user`ts`item`vbin`msg!(ft;"G";.z.u;x;y;`byte$();"")];}; /[ts;item;val;msg]

futest:{[x]1+x};
\

.db.R,:(`admin;`admin;`symbol$());.db.R,:(`user;`user;`futest`tsupd);
.db.U[`fc;`name`role`passwd]:`fc`admin`fc123;.db.U[`xuzq;`name`role`passwd]:`xuzq`admin`123;.db.U[`test;`name`role`passwd]:`test`user`456;
.db.SG,:(`zqg;`zqg;`xuzq;`stop`stoptype);
.db.S,:(`zq;`zq;`zqg;`ft;`ft;`ft`ft1;`xuzq`test);.db.S,:(`zq1;`zq1;`zqg;`ft;`ft;`ft`ft1;`xuzq`test);.db.S,:(`zq2;`zq2;`zqg;`ft;`ft;`ft`ft1;`xuzq`test);