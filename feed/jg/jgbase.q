.module.jgbase:2019.12.17;

.ctrl.jg:.enum.nulldict;

jgcall:{[x;y]k:`int$newseq[];.temp.C,:enlist (.z.P;x;k;y);((value x)[k;y,$[0=type y;();enlist (::)]];k)};
onjg:{[x]if[.conf.jg.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};
