.module.ctpbase:2016.12.29;

.ctrl.ctp:.enum.nulldict;

ctpcall:{[x;y]k:newseq[];.temp.C,:enlist (.z.P;k;x;y);(value x)[k;y,$[0=type y;();enlist (::)]]};
onctp:{[x]if[.conf.ctp.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};
