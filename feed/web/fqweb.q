.module.qweb:2017.07.14;

txload "core/fqbase";

.timer.qweb:{[x]d:.z.D;t:.z.T;if[(5<={x-`week$x}d)|(d in .conf.holiday)|not any t within/:.conf.fq.timerrange;:()];fl:exec sym from .db.QX where not null esym,(sym like "*XSHG")|(sym like "*XSHE");ht:.conf`webhqtype;if[0=count .temp.d:d:@[$[`xl~ht;webhq_xl;`tx~ht;webhq_tx;webhq_wy];fl;()];:()];lwarn[`nrec;count d];d1:(d0:delete pc,open,time from d) except .temp.Last;.temp.Last:d0;if[n:count d2:select from d where sym in exec sym from d1;pub[`quote;select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:.z.D+time,bidQ:flip (bid;b2px;b3px;b4px;b5px),askQ:flip (ask;o2px;o3px;o4px;o5px),bsizeQ:flip (bsize;b2sz;b3sz;b4sz;b5sz),asizeQ:flip (asize;o2sz;o3sz;o4sz;o5sz),quoopt:n#enlist "" from d2]];d1:(d0:select sym,pc,open from d) except .temp.LastRef;.temp.LastRef:d0;if[n:count d2:select from d0 where sym in exec sym from d1;pub[`quoteref;update sup:0w,inf:-0w,refopt:n#enlist "" each i from d2]];};

webhq_wy_1:{[x]r:httpget1["api.money.126.net";"/data/feed/",("," sv {[x]$[x like "*XSHG";"0";"1"],6#string x} each x),",money.api?callback=_"];t:{delete share from x} each value .j.k -2_ 2_ r;select sym:`${(1_x),$[x[0]="0";".XSHG";".XSHE"]} each code,pc:yestclose,open,time:`time$"Z"$time,price,cumqty:volume,vwap:turnover%volume,high,low,o5px:ask5,o5sz:askvol5,o4px:ask4,o4sz:askvol4,o3px:ask3,o3sz:askvol3,o2px:ask2,o2sz:askvol2,ask:ask1,asize:askvol1,bid:bid1,bsize:bidvol1,b2px:bid2,b2sz:bidvol2,b3px:bid3,b3sz:bidvol3,b4px:bid4,b4sz:bidvol4,b5px:bid5,b5sz:bidvol5,openint:0n,settlepx:0n from t}; /网易行情[一次最多取500多个代码]http://api.money.126.net/data/feed/0600000,1000001,money.api?callback=_

webhq_xl_1:{[x]r:httpget1["hq.sinajs.cn";"/list=","," sv {[x]$[x like "*XSHG";"sh";x like "*XSHE";"sz";"hk"],{?[x;"."]#x}string x} each x];t:flip `sym`name`open`pc`price`high`low`b1px1`o1px1`cumqty`cumamt`bsize`bid`b2sz`b2px`b3sz`b3px`b4sz`b4px`b5sz`b5px`asize`ask`o2sz`o2px`o3sz`o3px`o4sz`o4px`o5sz`o5px`date`time`status!flip {[x]y:x like "*str_hk*";(`$x[13+til $[y;5;6]],".",$[y;"XHKG";x[12]="h";"XSHG";x[12]="z";"XSHE"]),"," vs $[y;19;20]_x} each ";" vs -1_ r except "\"\n";select sym,"F"$pc,"F"$open,"T"$time,"F"$price,"F"$cumqty,vwap:("F"$cumamt)%("F"$cumqty),"F"$high,"F"$low,"F"$o5px,"F"$o5sz,"F"$o4px,"F"$o4sz,"F"$o3px,"F"$o3sz,"F"$o2px,"F"$o2sz,"F"$ask,"F"$asize,"F"$bid,"F"$bsize,"F"$b2px,"F"$b2sz,"F"$b3px,"F"$b3sz,"F"$b4px,"F"$b4sz,"F"$b5px,"F"$b5sz,openint:0n,settlepx:0n from t};  /新浪行情[一次最多取900多个代码]:http://hq.sinajs.cn/list=sh600000,sz000002,hk00799

webhq_tx_1:{[x]r:httpget1["qt.gtimg.cn";"/q=","," sv {[x]$[x like "*XSHG";"sh";"sz"],6#string x} each x];t:flip `sym`typ`name`code`price`pc`open`cumqty1`waipan`neipan`bid`bsize`b2px`b2sz`b3px`b3sz`b4px`b4sz`b5px`b5sz`ask`asize`o2px`o2sz`o3px`o3sz`o4px`o4sz`o5px`o5sz`bilist`dtime`zd`zdf`high`low`snap`cumqty`cumamt`hsl`pe`nop`h1`l1`zhenf`ltsz`zsz`pb`sup`inf`nop1!flip {[x](`$x[4+til 6],".",$[x[3]="h";"XSHG";"XSHE"]),"~" vs 11_x} each ";" vs -1_ r except "\"\n";select sym,"F"$pc,"F"$open,`time$"Z"${(8#x),"T",8_x} each dtime,"F"$price,("F"$cumqty)*1e2,vwap:("F"$cumamt)%("F"$cumqty),"F"$high,"F"$low,"F"$o5px,("F"$o5sz)*1e2,"F"$o4px,("F"$o4sz)*1e2,"F"$o3px,("F"$o3sz)*1e2,"F"$o2px,("F"$o2sz)*1e2,"F"$ask,("F"$asize)*1e2,"F"$bid,("F"$bsize)*1e2,"F"$b2px,("F"$b2sz)*1e2,"F"$b3px,("F"$b3sz)*1e2,"F"$b4px,("F"$b4sz)*1e2,"F"$b5px,("F"$b5sz)*1e2,openint:0n,settlepx:0n from t}; /腾讯行情[一次只能最多取64个代码]:http://qt.gtimg.cn/q=sz000559,sz000913,sz002048,sz002085,sz002126,sz002284,sz002434,sz002472,sz002488

webhq_tx:{[x]raze webhq_tx_1 each 0N 64#x};

webhq_xl:{[x]raze webhq_xl_1 each 0N 800#x};

webhq_wy:{[x]raze webhq_wy_1 each 0N 500#x};

hgtlist_old:{[]r:httpget1["www.sse.com.cn";"/market/sseindex/indexlist/s/i000159/const_list.shtml"];`$(r ss[r;"&PRODUCTID="]+\:11+til 6),\:".XSHG"};

hgtlist:{[]c:system "wget -O - http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfra/chinaconnect/Documents/SSE_Securities_c.csv |iconv -f UTF-16 -t GBK";`$(@[;1] flip vs["\t"] each 5_c),\:".XSHG"};

sgtlist:{[]c:system "wget -O - http://sc.hkex.com.hk/TuniS/www.hkex.com.hk/chi/market/sec_tradinfra/chinaconnect/Documents/SZSE_Securities_c.csv |iconv -f UTF-16 -t GBK";`$(@[;1] flip vs["\t"] each 5_c),\:".XSHE"};

updhsgt:{[x;y]fl:hgtlist[];delete from `.db.QX where ex=`SEHKNTL,not sym in fl;nl:fl except exec sym from .db.QX where ex=`SEHKNTL;{[x]y:fs2s x;.db.QX[x;`ex`esym`ticker`sectype`currency`qtylot`rfeetaxoa`rfeetaxca]:(`SEHKNTL;y;y;`STK;`CNH;100f;8e-4;1.8e-3);} each nl;fl:sgtlist[];delete from `.db.QX where ex=`SEHKSZSE,not sym in fl;nl:fl except exec sym from .db.QX where ex=`SEHKSZSE;{[x]y:fs2s x;.db.QX[x;`ex`esym`ticker`sectype`currency`qtylot`rfeetaxoa`rfeetaxca]:(`SEHKSZSE;y;y;`STK;`CNH;100f;8e-4;1.8e-3);} each nl;(path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,ticker,sectype,currency,qtylot,rfeetaxoa,rfeetaxca from .db.QX;pubm[`ALL;`RDUpdate;`web;string path];1b}; /

\
.db.TASK[`UPDHSGT;`firetime`firefreq`handler]:(\"p\"$.z.D+08:55:00;1D;`upghsgt);



