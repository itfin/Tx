.module.atpbase:2021.11.02;

.ctrl.atp:.enum.nulldict;

atpcall:{[x;y]k:`int$newseq[];.temp.C,:enlist (.z.P;x;k;y);((value x)[k;y,$[0=type y;();enlist (::)]];k)};
onatp:{[x]if[.conf.atp.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};
