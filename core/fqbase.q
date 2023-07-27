.module.fqbase:2017.01.25;

.db.fqclosedate:.db.fqopendate:0Np;

\d .temp
LastRef:Last:();
L2M:L2O:L2Q:QREF:QUEUE:L19:L18:L17:L16:L15:L14:L13:L12:L11:L10:L:C:();TKSub:BKSub:MDSub:()!();
\d .

quotetbl:$[1b~isl2:.conf[`usel2quote];`l2quote;`quote];

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[quotetbl;distinct .temp.QUEUE];.temp.QUEUE:()};

enqueuel2:{[t;x]$[t=`Q;.temp.L2Q,:x;t=`O;.temp.L2O,:x;.temp.L2M,:x];};
enqueuel2q:enqueuel2[`Q];enqueuel2o:enqueuel2[`O];enqueuel2m:enqueuel2[`M];
batchpubl2:{[]if[(not 1b~.conf.batchpubl2);:()];if[0<count .temp.L2Q;pub[`l2queue;distinct .temp.L2Q];.temp.L2Q:()];if[0<count .temp.L2O;pub[`l2order;distinct .temp.L2O];.temp.L2O:()];if[0<count .temp.L2M;pub[`l2match;distinct .temp.L2M];.temp.L2M:()];};
