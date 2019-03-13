.module.fqxshg:2018.04.02;

txload "core/fqbase";
\d .temp
LASTSS:LASTHK:();
\d .

.timer.fqxshg:{[x]d:.z.D;t:.z.T;if[(5<={x-`week$x}d)|(d in .conf.holiday)|(t<09:05:00)|(t within 11:40:00 12:50:00)|(t within 16:15:00 16:45:00)|((.z.D=.db.fqclosedate)&(t>15:00:00));:()];$[d>.db.fqopendate;.upd.MKTOPEN[];(t>16:45:00)&(d>.db.fqclosedate);.upd.MKTCLOSE[];.upd.MKTTICK[]];};

updaterd:{[x;y]d:@[getrd;::;()];if[count d;.db.QX:.db.QX uj d;(path:` sv .conf.tempdb,.conf.me,`RD) set d;pubm[`ALL;`RDUpdate;`xshg;string path]];1b};

/local msg
.upd.MKTOPEN:{[x].temp.LASTSS:.temp.LASTHK:();.db.fqopendate:.z.D;updaterd[`;`];};

.upd.MKTCLOSE:{[x].db.fqclosedate:.z.D;};

.upd.MKTTICK:{[x]d:@[gethq;::;()];if[n:count d;pub[`quote;select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:.z.D+time,bidQ:flip (bid;b2px;b3px;b4px;b5px),askQ:flip (ask;o2px;o3px;o4px;o5px),bsizeQ:flip (bsize;b2sz;b3sz;b4sz;b5sz),asizeQ:flip (asize;o2sz;o3sz;o4sz;o5sz),quoopt:n#enlist "" from d]];};

readsshq_txt:{[]x:read0 .conf.sshqtxt;y:"|"vs x[0];z:("|"vs) each -1_1_x;dt:"Z"$y[6];ssmeta:`date`time!`date`time$dt;m:group `$z[;0];ssidx:flip `sym`name`cumqty`vwap`pc`open`high`low`price`settlepx`tradephase`time`bid`bsize`ask`asize`b2px`b2sz`o2px`o2sz`b3px`b3sz`o3px`o3sz`b4px`b4sz`o4px`o4sz`b5px`b5sz`o5px`o5sz!32#1_flip z[m `MD001],\:20#"";ssstk:flip `sym`name`cumqty`vwap`pc`open`high`low`price`settlepx`bid`bsize`ask`asize`b2px`b2sz`o2px`o2sz`b3px`b3sz`o3px`o3sz`b4px`b4sz`o4px`o4sz`b5px`b5sz`o5px`o5sz`tradephase`time!32#1_flip z raze m[`MD002`MD003];ssfund:flip `sym`name`cumqty`vwap`pc`open`high`low`price`settlepx`bid`bsize`ask`asize`b2px`b2sz`o2px`o2sz`b3px`b3sz`o3px`o3sz`b4px`b4sz`o4px`o4sz`b5px`b5sz`o5px`o5sz`piopv`iopv`tradephase`time!34#1_flip z raze m[`MD004];sshq:update vwap:vwap%cumqty from select sym:`$(sym,\:".XSHG"),`$name,"F"$pc,"F"$open,"F"$price,"F"$cumqty,"F"$vwap,"F"$high,"F"$low,"F"$o5px,"F"$o5sz,"F"$o4px,"F"$o4sz,"F"$o3px,"F"$o3sz,"F"$o2px,"F"$o2sz,"F"$ask,"F"$asize,"F"$bid,"F"$bsize,"F"$b2px,"F"$b2sz,"F"$b3px,"F"$b3sz,"F"$b4px,"F"$b4sz,"F"$b5px,"F"$b5sz,openint:0n,"F"$settlepx from (delete tradephase,time from ssidx),delete tradephase,time from ssstk,(delete piopv,iopv from update settlepx:iopv from ssfund);(ssmeta;sshq)}; /(FASTtxt行情) MD001(指数),MD002(AB股),MD003(债券),MD004(基金)

readhkhq:{[t]x:`char$read1 .conf.hkhqtxt;p0:ss[x;"MD401"];p1:ss[x;"MD404"];p2:ss[x;"MD405"];p3:ss[x;"TRAILER"];i0:p0[0];i1:first p3;y:"|"vs i0#x;dt:"Z"$y[6];hkmeta:`date`time!`date`time$dt;hkstk:update sym:sv[`] each (,\:)[sym;`XHKG] from flip `sym`name`cumqty`vwap`pc`settlepx`high`low`price`bid`bsize`ask`asize`state`time!(("  S   S F F F F F F F F F F F S T";5 1 5 1 32 1 15 1 16 1 16 1 11 1 11 1 11 1 11 1 11 1 11 1 12 1 11 1 12 1 8 1 12) 0: x[i0+til i1-i0]);hkhq:update vwap:vwap%cumqty from select sym,name,pc,open:0n,time,price,cumqty,vwap,high,low,o5px:0n,o5sz:0n,o4px:0n,o4sz:0n,o3px:0n,o3sz:0n,o2px:0n,o2sz:0n,ask,asize,bid,bsize,b2px:0n,b2sz:0n,b3px:0n,b3sz:0n,b4px:0n,b4sz:0n,b5px:0n,b5sz:0n,openint:0n,settlepx from hkstk;$[t;select sym,name,pc,open from hkhq;[d:delete name,pc,open from hkhq;d0:(delete time from d) except .temp.LASTHK;.temp.LASTHK:$[0=count .temp.LASTHK;d0;0!(1!.temp.LASTHK),1!d0];select from d where sym in exec sym from d0]]}; /(港股行情) MD401(港股行情)MD404(融断VCM)MD405(收盘集合竞价CAS)


readsshq:{[x]d:readsshq_txt[];ssmeta:d[0];sshq:d[1];$[x;select sym,name,pc,open from sshq;[sshq:delete from (delete name,pc,open from sshq) where not (cumqty>0)|(price>0)|(bid>0)|(ask>0);L:flip value flip sshq;sshq:flip (cols sshq)!(flip L except .temp.LASTSS);.temp.LASTSS:L;{[x;y]$[x;select from y;delete from y]}[ssmeta[`date]=.z.D] `sym`time xcols update time:ssmeta[`time] from sshq]]}; /上海行情

getrd:{[]t:readsshq[1],readhkhq[1];(uj/) (1!t;1!@[readssxx;();t])};

gethq:{[]delete from (readsshq[0],@[readhkhq;0;()]) where sym in .conf.blacklist}; 


readssxx:{[]`sym xcols delete financetype1 from update date1:.z.D,sym:{`$(string x),".XSHG"} each esym,ex:`XSHG,sup:sup,inf:inf,pc:pc,financetype:?[financetype=`T;?[financetype1=`T;`All;`Cash];?[financetype1=`T;`Stock;`]],outstanding:listshares+outstanding,totalshares:listshares+outstanding+totalshares,pxlimitrule:(`N`R`S!``NoLimit`RepoType)pxlimitrule,secclass:{$["N"=x[0];`Open;"D"=x[1];$["R"=x[2];`SplitDiv;`Split];$["R"=x[2];`Divend;`]]} each string secclass,secstatus:{$["S"=x[3];`ST;"P"=x[3];`PT;`]} each string secclass,assetclass:(``ES`EU`D!``Stock`Fund`Bond)cficode from flip `esym`isin`time1`name`ticker`underlying`ex1`cficode`sectype`currency`listshares`outstanding`totalshares`opendate`state`qtyminl`qtymins`qtylot`qtymax`pc`pxunit`pxlimitrule`sup`inf`sharebonus`bonus`financetype`financetype1`secclass`remark!("SST",(7#"S"),(3#"F"),"DS",(6#"F"),"S",(4#"F"),4#"S";"|") 0: `$ssr[string .conf.ssxxtxt;"MMDD";(string .z.D)[5 6 8 9]]};

\
.db.TASK[`UPDATERD;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+09:29:40;1D;0;4;`updaterd);