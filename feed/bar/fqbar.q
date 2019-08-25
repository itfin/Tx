.module.fqbar:2019.06.25;

.u.init[];

bartime:{[x].conf.barfreq*(`int$`second$x) div `int$.conf.barfreq};

.init.fqbar:.roll.fqbar:{.ctrl[`bd0`bt0]:(.z.D;bartime .z.T);.ctrl.volmap:(`u#`symbol$())!`float$();.ctrl.amtmap:(`u#`symbol$())!`float$();};

.upd.quote:{[x]quote,:x};

.timer.fqbar:{[x]bt1:bartime[x];bd1:.z.D;if[(bt1<=bt0:.ctrl.bt0)&(bd1<=.ctrl.bd0);:()];.ctrl[`bt0`bd0]:(bt1;bd1);if[0=count quote;:()];t:`time xcols update time:`timespan$.z.P,vol:vol-0f^.ctrl.volmap sym,amt:amt-0f^.ctrl.amtmap sym from 0!select freq:.conf.barfreq,bard:.db.sysdate,bart:bt0,open:first price,high:max price,low:min price,close:last price,vol:last cumqty,amt:(last vwap)*last cumqty,src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np by sym from quote where price>0;.u.pub[`bar;t];.ctrl.volmap,:exec last cumqty by sym from quote;.ctrl.amtmap,:exec last cumqty*vwap by sym from quote;.db.seq+:1;quote::0#quote;};