.module.xtpbase:2019.12.17;

.ctrl.xtp:.enum.nulldict;

xtpcall:{[x;y]k:`int$newseq[];sid:.ctrl.xtp[`SessionID];.temp.C,:enlist (.z.P;x;sid;k;y);(value x)[sid;k;y,$[0=type y;();enlist (::)]]};
onxtp:{[x]if[.conf.xtp.debug;.temp.L,:(enlist .z.P),/:x];@[{.upd[x[0]][x[1]]};;()] each x;};
