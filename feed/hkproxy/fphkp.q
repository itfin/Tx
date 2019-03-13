.module.fphkp:2017.09.23;

txload "core/fpbase";

.temp.XHKEList:`symbol$();

mkhksym:{[x]`$string "I"$string first vs[`] x};

upd:{[t;x]insert[t;x];if[not (src:x[0;`src]) in key .conf.proxy.stp;:()];.temp.XHKEList:.temp.XHKEList union exec mkhksym each sym from x where sym like "*XHKE";x:delete hksym from update sym:(`$(string hksym),\:".XHKG") from select from (update hksym:mkhksym each sym from x) where (sym like "*XHKE")|(sym like "*XHKG")&not hksym in .temp.XHKEList;{[d;t;x]h:.ctrl.conn[d;`h];$[-6h<>type h;();0>=h;();[neg[h] (".u.upd";t;x)]];}[;t;value flip x] each .conf.proxy.tpl except .conf.proxy.stp src;};


