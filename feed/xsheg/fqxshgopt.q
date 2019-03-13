.module.fqxshgopt:2017.07.19;

txload "core/fqbase";

.timer.fqxshgopt:{[]d:.z.D;t:.z.T;if[(5<={x-`week$x}d)|(d in .conf.holiday)|(t<09:05:00)|(t within 11:40:00 12:50:00)|(t within 15:10:00 16:45:00)|((d=.db.fqclosedate)&(t>16:45:00));:()];$[d>.db.fqopendate;.upd.MKTOPEN[];(t>16:45:00)&(d>.db.fqclosedate);.upd.MKTCLOSE[];.upd.MKTTICK[]];};

.upd.MKTOPEN:{[x].temp.LastRef:.temp.Last:();d:@[getrd;::;()];.db.fqopendate:.z.D;if[count d;.db.QX:.db.QX uj d;(path:` sv .conf.tempdb,.conf.me,`RD) set d;pubm[`ALL;`RDUpdate;`xshgopt;string path]];};

.upd.MKTCLOSE:{[x].db.fqclosedate:.z.D;};

.upd.MKTTICK:{[x]d:@[gethq;::;()];if[n:count d[0];pub[`quote;select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime:.z.D+time,bidQ:flip (bid;b2px;b3px;b4px;b5px),askQ:flip (ask;o2px;o3px;o4px;o5px),bsizeQ:flip (bsize;b2sz;b3sz;b4sz;b5sz),asizeQ:flip (asize;o2sz;o3sz;o4sz;o5sz),quoopt:n#enlist "" from d[0]]];};

gethq:{[]x:read0 .conf.mkttxt;y:"|"vs x[0];z:-1_1_x;dt:"Z"$y[6];if[.z.D<>`date$dt;:()];t:update sym:`$(,\:)[sym;".XSHG"],vwap%cumqty from flip `sym`openint`cumqty`vwap`pc`open`aucpx`aucqty`high`low`price`bid`bsize`ask`asize`b2px`b2sz`o2px`o2sz`b3px`b3sz`o3px`o3sz`b4px`b4sz`o4px`o4sz`b5px`b5sz`o5px`o5sz`settlepx`mode`time`time1!("*",(31#"F"),"STT")$'1_flip ("|"vs) each z;t1:select sym,time,price,cumqty,vwap,high,low,o5px,o5sz,o4px,o4sz,o3px,o3sz,o2px,o2sz,ask,asize,bid,bsize,b2px,b2sz,b3px,b3sz,b4px,b4sz,b5px,b5sz,openint,settlepx,mode,recvtime:.z.P,exlocaltime:.z.P,virtualtime:0Np,isnormalsession:1b from t;d1:select sym,pc,open from t;t2:t1 except .temp.Last;.temp.Last:t1;d2:d1 except .temp.LastRef;.temp.LastRef:d1;(t2;1!d2)};

getrd:{[x]r:1!`sym xcols update sym:` sv/:esym(,)\:`XSHG,underlying:` sv/:underlying(,)\:`XSHG,date:.z.D,qtymaxm:50f,openint,pc,sup,inf from flip `esym`isin`name`underlying`product`optexec`putcall`multiplier`strikepx`opendate`date1`settledate`valuedate`paymentdate`lifephase`openint`pc`accuvalue`eps`pxlimitrule`sup`inf`bonus`rmarginl`rmargins`qtylot`qtyminl`qtymax`qtymins`qtymaxs`pxunit`secstatus!(" ",(4#"S")," SSSFF",(5#"D"),"S",(4#"F"),"S",(11#"F"),"S";"|") 0: hsym `$ssr[string .conf.reftxt;"MMDD";(string .z.D)[5 6 8 9]];$[1<exec count distinct settledate from r;r;()]};



