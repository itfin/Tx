.module.fqbar:2022.05.05;

.u.init[];

bartime:{[x].conf.barfreq*(`int$`second$x-00:00:00.000^tfill .conf[`bardelay]) div `int$.conf.barfreq};

.init.fqbar:.roll.fqbar:{.ctrl[`bd0`bt0]:(.z.D;bartime .z.T);.ctrl.volmap:(`u#`symbol$())!`float$();.ctrl.amtmap:(`u#`symbol$())!`float$();.ctrl.highmap:(`u#`symbol$())!`float$();.ctrl.lowmap:(`u#`symbol$())!`float$();};

.upd.l2quote:.upd.quote:{[x]quote,:x};

.timer.fqbar:{[x]bt1:bartime[x];bd1:.z.D;if[(bt1<=bt0:.ctrl.bt0)&(bd1<=.ctrl.bd0);:()];.ctrl[`bt0`bd0]:(bt1;bd1);if[0=count quote;:()];t:`time xcols delete h2,l2 from update time:`timespan$.z.P,v:v-0f^.ctrl.volmap sym,a:a-0f^.ctrl.amtmap sym,h:?[h2<>.ctrl.highmap sym;h2;h],l:?[l2<>.ctrl.lowmap sym;l2;l] from 0!select freq:.conf.barfreq,d:.db.sysdate,t:bt0,o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:(last vwap)*last cumqty,p:last openint,src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np,h2:last high,l2:last low by sym from quote where price>0;.u.pub[`bar;t];.ctrl.volmap,:exec last cumqty by sym from quote;.ctrl.amtmap,:exec last cumqty*vwap by sym from quote;.ctrl.highmap,:exec last high by sym from quote;.ctrl.lowmap,:exec last low by sym from quote;.db.seq+:1;quote::0#quote;};