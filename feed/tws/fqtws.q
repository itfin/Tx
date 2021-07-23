.module.fqtws:2018.05.04;

txload "core/fqbase";
txload "feed/tws/twsbase";

.timer.fqtws:{[x]batchpub[];dosubscribe[];cxloldhisreq[];};

\d .ctrl
hisbartime:HisReqMap:DepthMap:BarReqMap:TickerMap:()!();
hisbarsymlst:HBAR:();
mhisbartime:0Np;
skipsyms:mhisbarsymlst:();
histretry:0;
histdates:`date$();
\d .
.roll.fqtws:{[x]update price:0n,bid:0n,ask:0n,cumqty:0f from `.db.QX;update status:0i from `.db.QX where ex=`SEHK,status<9;};

dosubscribe:{[]if[(not `Logon~.ctrl.tws`status)|(null .ctrl.tws`peertime)|(.z.P<00:00:10+.ctrl.tws`logontime);:()];sl0:value .ctrl.TickerMap;sl1:(exec sym from .db.QX where (not null sym)&((sectype<>`FUT)|settledate>=.z.D)&((null status)&(not ex in `SEHK`SEHKNTL`SEHKSZSE))),exec sym from `status xdesc select from .db.QX where (status>0)&ex=`SEHK;unsubtws each sl0 except sl1;if[(0<n:.conf.tws.rtsubmax-count .ctrl.TickerMap)&count sl:sl1 except sl0;subtwsdata each sublist[n&.conf.tws.batchcnt] sl;.ctrl.tws.subtime:.z.P];subtwsdepth each .conf.tws.depthsyms except value .ctrl.DepthMap;};

cleartemp:{[]};

tws_disc:{[]cleartemp[];.ctrl.tws.subtime:0Np;.ctrl.DepthMap:.ctrl.TickerMap:()!();};

subtws:{[f;x]y:newseq[];$[`tws_req_mkt_data=f;.ctrl.TickerMap[y]:x;`tws_req_real_time_bars=f;.ctrl.BarReqMap[y]:x;.ctrl.DepthMap[y]:x];(f)[y;`symbol`sectype`expiry`exchange`currency`localsymbol`whattoshow!.db.QX[x;`esym`sectype],(`$sublist[6] (string .db.QX[x;`settledate]) except "."),.db.QX[x;`ex`currency`ticker],$[`CASH=.db.QX[x;`sectype];`MIDPOINT;`TRADES]];}; /[fsym]
subtwsdata:subtws[`tws_req_mkt_data];subtwsdepth:subtws[`tws_req_mkt_depth];subtwsbars:subtws[`tws_req_real_time_bars];
subtwsall:{[x]subtwsdata[x];subtwsbars[x];}; /subtwsdepth[x];

unsubtws:{[x]tws_cancel_mkt_data each I:where x=.ctrl.TickerMap;.ctrl.TickerMap:I _.ctrl.TickerMap;};

tws_tick_price:{[x]if[null y:.ctrl.TickerMap "J"$x`tickerid;:()];ex:fs2e y;z:"J"$x`ticktype;.db.QX[y;`time`recvtime`nticks,$[z=.enum`BID;`bid`bsize;z=.enum`ASK;`ask`asize;z=.enum`HIGH;`high`size;z=.enum`LOW;`low`size;z=.enum`LAST;`price`size;`settlepx`size]]:(`timespan$.z.T;.z.P;1+0^.db.QX[y;`nticks]),"F"$x`price`size;};

tws_tick_size:{[x]if[null y:.ctrl.TickerMap "J"$x`tickerid;:()];ex:fs2e y;z:"J"$x`ticktype;.db.QX[y;`time`recvtime`nticks,$[z=.enum`BID_SIZE;`bsize;z=.enum`ASK_SIZE;`asize;z=.enum`VOLUME;`cumqty;z=.enum`OPEN_INTEREST;`openint;`size]]:(`timespan$.z.T;.z.P;1+0^.db.QX[y;`nticks]),"F"$x`size;};

tws_market_depth:{[x]if[null y:.ctrl.DepthMap "J"$x`reqid;:()];l:"J"$x`position;op:"J"$x`operation;sd:"J"$x`side;px:"F"$x`price;qty:"F"$x`size;pfd:$[sd=0;`askQ;`bidQ];qfd:$[sd=0;`asizeQ;`bsizeQ];$[op=0;[L:.db.QX[y;pfd];.db.QX[y;pfd]:l#L,px,l _L;L:.db.QX[y;qfd];.db.QX[y;qfd]:l#L,qty,l _L];op=1;[.db.QX[y;pfd;l]:px;.db.QX[y;qfd;l]:qty];op=2;[.db.QX[y;pfd]_:l;.db.QX[y;qfd]_:l];()];}; /l:0,1,...;op:0(insert),1(update),2(delete),sd:0(ask),1(bid)

tws_tick_generic:{[x];};

tws_tick_string:{[x];};

tws_tick_option_computation:{[x]if[null y:.ctrl.TickerMap "J"$x`tickerid;:()];v:"F"$x`impvol;if[(v>0)|.enum[`LAST]=z:"J"$x`ticktype;.db.QX[y;`time`recvtime`nticks`openint]:(`timespan$.z.T;.z.P;1+0^.db.QX[y;`nticks]),v];};

.upd.RDUpdate:{[x]if[`tws<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;dosubscribe[];};

tws_sub_hk:{[z]if[(`SEHK<>.db.QX[z;`ex])|9<=.db.QX[z;`status];:()];.db.QX[z;`status]:9i;};
tws_unsub_hk:{[z]if[`SEHK<>.db.QX[z;`ex];:()];.db.QX[z;`status]:0i;unsubtws[z];};

.upd.Sub:{[x]tws_sub_hk x`ref;};
.upd.UnSub:{[x]tws_unsub_hk x`ref;};

.upd.SubBatch:{[x]nl:-9!x`vbin;ol:exec sym from .db.QX where ex=`SEHK,status=9i;tws_unsub_hk each ol except nl;tws_sub_hk each nl except ol;};

batchpub:{[]n:count d:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime,bidQ,askQ,bsizeQ,asizeQ from .db.QX where not null sym,0<nticks;if[n;pub[`quote;update bidQ:?[0=count each bidQ;n#enlist `float$();bidQ],askQ:?[0=count each askQ;n#enlist `float$();askQ],bsizeQ:?[0=count each bsizeQ;n#enlist `float$();bsizeQ],asizeQ:?[0=count each asizeQ;n#enlist `float$();asizeQ],quoopt:n#enlist "" from d];update nticks:0 from `.db.QX];}; /if[.db.fqopendate<d0:.db.sysdate;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];

.enum.BarSizeMap:`s1`s5`s10`s15`s30`m1`m2`m3`m5`m10`m15`m20`m30`h1`h2`h3`h4`h8`d1`w1`m1!`$("1 secs";"5 secs";"10 secs";"15 secs";"30 secs";"1 min";"2 mins";"3 mins";"5 mins";"10 mins";"15 mins";"20 mins";"30 mins";"1 hour";"2 hours";"3 hours";"4 hours";"8 hours";"1 day";"1W";"1M");
.enum.DurationMap:`s1`s5`s10`s15`s30`m1`m2`m3`m5`m10`m15`m20`m30`h1`h2`h3`h4`h8`d1`w1`m1!`$("1800 S";"7200 S";"7200 S";"14400 S";"1 D";"2 D";"2 D";"2 D";"2 D";"2 D";"1 W";"1 W";"1 W";"1 M";"1 M";"1 M";"1 M";"1 M";"1 Y";"1 Y";"1 Y");
reqtwshisbarsx:{[x;y;z;d]w:newseq[];.ctrl.HisReqMap[w]:`s`t!(x;.z.P);tws_req_historical_data[w;`symbol`sectype`expiry`exchange`currency`localsymbol`whattoshow`enddatetime`barsizesetting`durationstr!.db.QX[x;`esym`sectype],(`$sublist[6] (string .db.QX[x;`settledate]) except "."),.db.QX[x;`ex`currency`ticker],($[`CASH=.db.QX[x;`sectype];`MIDPOINT;`TRADES];`$((string `date$y) except ".")," ",string `second$y;.enum.BarSizeMap z;$[count d;d;.enum.DurationMap z])];}; /[fsym;endtime;freq;duration]
reqtwshisbars:reqtwshisbarsx[;;;""];

tws_historical_data:{[x]y:.ctrl.HisReqMap[k:"J"$x`reqid;`s];if[not null y;d:flip x`bars;d[0]:ssr[;"  ";" "] each d[0];z:d[7]~\:"true";d[7]:d[8];.ctrl.HBAR,:3!`sym xcols update sym:y from flip `d`t`o`h`l`c`q`w`n`g!{((`date$x[0]);(`time$x[0])),1_x} ("ZFFFFFFJ"$'8#d),enlist z];.ctrl.HisReqMap:(enlist k) _ .ctrl.HisReqMap;}; 

lsthisbar:{[i;f;x;y]if[i;.ctrl.hisbartime[f]:.z.D+16:00:00;.ctrl.HBAR:();.ctrl.HisReqMap:()!();.ctrl.skipsyms:`symbol$();];.ctrl.hisbarsymlst:asc (exec sym from .db.QX where ex=`SEHK,status<10,`STK=sectype) except .ctrl.skipsyms,$[0=count .ctrl.HBAR;();exec distinct sym from .ctrl.HBAR];1b};

lsthisbard1:lsthisbar[1b;`d1];lsthisbars30:lsthisbar[1b;`s30];
rlsthisbard1:lsthisbar[0b;`d1];rlsthisbars30:lsthisbar[0b;`s30];

reqhisbar:{[f;d;x;y]if[(0=n:count L:.ctrl.hisbarsymlst)|(null t:.ctrl.hisbartime[f]);:()];m:n&.conf.tws.batchcnt&(.conf.tws.hisreqmax-count .ctrl.HisReqMap);if[0>=m;:()];l:m#L;.ctrl.hisbarsymlst:m _L;reqtwshisbarsx[;t;f;d] each l;1b};
reqhisbard1:reqhisbar[`d1;""];reqhisbars30:reqhisbar[`s30;""];reqhisbard0:reqhisbar[`d1;"1 D"]; 

mreqhisbars30:{[x;y];if[null t:.ctrl.mhisbartime;:()];if[0=n:count L:.ctrl.mhisbarsymlst;d0:`date$t;r:.ctrl.histretry;hb:.ctrl.HBAR;$[($[0=count hb;0;count exec distinct sym from .ctrl.HBAR where d=d0,not null sym]=count[(exec distinct sym from .temp.BARD1 where d=d0) except .ctrl.skipsyms])|(r>.conf.tws.histrymax);$[d0<=first .ctrl.histdates;[.ctrl.mhisbartime:0Np];[savehisbars30m[`;`];.ctrl.HBAR:();.ctrl.histretry:0;d1:{x -1+x?y}[.ctrl.histdates;d0];.ctrl.mhisbartime:d1+16:00;.ctrl.skipsyms:`symbol$();.ctrl.HisReqMap:()!();.ctrl.mhisbarsymlst:exec distinct sym from .temp.BARD1 where d=d1]];[.ctrl.histretry+:1;.ctrl.mhisbarsymlst:(exec distinct sym from .temp.BARD1 where d=d0) except .ctrl.skipsyms,$[0=count hb;();exec distinct sym from hb where d=d0]]];:()];m:n&.conf.tws.batchcnt&(.conf.tws.hisreqmax-count .ctrl.HisReqMap);if[0>=m;:()];l:m#L;.ctrl.mhisbarsymlst:m _L;reqtwshisbars[;t;`s30] each l;1b}; 

mreqhisbard1:{[x;y];if[null t:.ctrl.mhisbartime;:()];if[0=n:count L:.ctrl.mhisbarsymlst;d0:`date$t;r:.ctrl.histretry;hb:.ctrl.HBAR;$[($[0=count hb;0;count exec distinct sym from .ctrl.HBAR where d=d0,not null sym]=count[(asc exec sym from .db.QX where ex=`SEHK,status<10) except .ctrl.skipsyms])|(r>.conf.tws.histrymax);$[d0<=first .ctrl.histdates;[.ctrl.mhisbartime:0Np];[savehisbarsd1m[`;`];.ctrl.HBAR:();.ctrl.histretry:0;d1:{x -1+x?y}[.ctrl.histdates;d0];.ctrl.mhisbartime:d1+16:00;.ctrl.skipsyms:`symbol$();.ctrl.HisReqMap:()!();.ctrl.mhisbarsymlst:asc exec sym from .db.QX where ex=`SEHK,status<10]];[.ctrl.histretry+:1;.ctrl.mhisbarsymlst:(asc exec sym from .db.QX where ex=`SEHK,status<10) except .ctrl.skipsyms,$[0=count hb;();exec distinct sym from hb where d=d0]]];:()];m:n&.conf.tws.batchcnt&(.conf.tws.hisreqmax-count .ctrl.HisReqMap);if[0>=m;:()];l:m#L;.ctrl.mhisbarsymlst:m _L;reqtwshisbars[;t;`d1] each l;1b}; 

savehisbar:{[f;x;y]if[0=count .ctrl.HBAR;:()];p:` sv .conf.histdb,`$"BAR",upper string f;set[p;`sym`d`t xasc upsert[@[get;p;()];.ctrl.HBAR]];1b};

savehisbard1:savehisbar[`d1];savehisbars30:savehisbar[`s30];savehisbars30m:savehisbar[`s30m];savehisbarsd1m:savehisbar[`d1m];

tws_err_msg:{[x].temp.ERR:x;y:"J"$x`id;z:"J"$x`reason;if[z in 420;.ctrl.BarReqMap:(enlist y) _ .ctrl.BarReqMap;:()];if[z in 162 200 322 366;k:.ctrl.HisReqMap[y;`s];if[(z in 162 200 366)&not(null k)|k in .ctrl.skipsyms;.ctrl.skipsyms,:k];.ctrl.HisReqMap:(enlist y) _ .ctrl.HisReqMap];}; /162:无数据返回，200:无证券定义,366:无数据 

cxloldhisreq:{[]t:.z.P;{[x;y]if[.z.P>.ctrl.HisReqMap[y;`t]+.conf.tws.hisreqtmout;tws_cancel_historical_data[y];.ctrl.HisReqMap:(enlist y) _ .ctrl.HisReqMap]}[t] each key .ctrl.HisReqMap;};

tws_real_time_bars:{[x]y:.ctrl.BarReqMap "J"$x`reqid;z:unixdate["I"$x`time];d:enlist y,(`date$z),(`time$z),("F"$x`open`high`low`close`volume`average),("J"$x`count),0b;pubmx[`ALL;`Bar;`tws;"";-8!d];};

rtbarsubinit:{[x;y]tws_cancel_real_time_bars each key .ctrl.BarReqMap;.ctrl.BarReqMap:()!();1b};
rtbarsubloop:{[x;y]if[(not `Logon~.ctrl.tws`status)|(null .ctrl.tws`peertime)|(.z.P<00:00:10+.ctrl.tws`logontime);:()];sl0:value .ctrl.BarReqMap;sl1:(exec sym from .db.QX where (not null sym)&((sectype<>`FUT)|settledate>=.z.D)&((null status)&(not ex in `SEHK`SEHKNTL`SEHKSZSE))),exec sym from `status xdesc select from .db.QX where (status>0)&ex=`SEHK;if[(0<n:.conf.tws.rtsubmax-count .ctrl.BarReqMap)&count sl:sl1 except sl0;subtwsbars each sublist[n&.conf.tws.rtbarbatchcnt] sl;.ctrl.tws.rtbarsubtime:.z.P];1b}; /10min订阅不超过60,每10秒订阅1个


\

reqtwshisbars[`EURUSD.FOREX;.z.P;`d1];

.db.TASK[`RSTRTBAR;`firetime`firefreq`handler]:(`timestamp$.z.D+08:00:00;1D;`rtbarsubinit); /初始化当日5秒行情订阅列表
.db.TASK[`REQRTBAR;`firetime`firefreq`timemin`timemax`handler]:(`timestamp$.z.D+08:01:00;0D00:00:10;08:01;16:00;`rtbarsubloop); /在流控限速下循环订阅当日5秒行情

.db.TASK[`LSTHISBARS30;`firetime`firefreq`handler]:(`timestamp$.z.D+16:08:00;1D;`lsthisbars30); /初始化30秒线历史下载代码列表
.db.TASK[`REQHISBARS30;`firetime`firefreq`timemin`timemax`handler]:(`timestamp$.z.D+16:09:00;0D00:00:01;16:00;16:45;`reqhisbars30); /在限速下循环请求30秒数据
.db.TASK[`R0LSTHISBARS30;`firetime`firefreq`handler]:(`timestamp$(1+.z.D)+16:18:00;1D;`rlsthisbars30); /再次初始化遗漏30秒线历史下载代码列表
.db.TASK[`R1LSTHISBARS30;`firetime`firefreq`handler]:(`timestamp$(1+.z.D)+16:28:00;1D;`rlsthisbars30); /三次初始化遗漏30秒线历史下载代码列表
.db.TASK[`SAVEHISBARS30;`firetime`firefreq`handler]:(`timestamp$.z.D+16:40;1D;`savehisbars30); /存盘30秒线历史下载

.db.TASK[`LSTHISBARD1;`firetime`firefreq`handler]:(`timestamp$.z.D+17:08:00;1D;`lsthisbard1);  /初始化日线历史下载代码列表
.db.TASK[`REQHISBARD1;`firetime`firefreq`timemin`timemax`handler]:(`timestamp$.z.D+17:09:00;0D00:00:01;17:00;17:45`reqhisbard0); /在流控限速下循环请求日线数据
.db.TASK[`R0LSTHISBARD1;`firetime`firefreq`handler]:(`timestamp$.z.D+17:18:00;1D;`rlsthisbard1); /再次初始化遗漏日线历史下载代码列表
.db.TASK[`R1LSTHISBARD1;`firetime`firefreq`handler]:(`timestamp$.z.D+17:28:00;1D;`rlsthisbard1); /三次初始化遗漏日线历史下载代码列表
.db.TASK[`SAVEHISBARD1;`firetime`firefreq`handler]:(`timestamp$.z.D+17:40;1D;`savehisbard1);   /存盘日线历史下载

.db.TASK[`MREQHISBARS30;`firetime`firefreq`handler]:(.z.P;0D00:00:01;`mreqhisbars30);
.db.TASK[`MREQHISBARD1;`firetime`firefreq`handler]:(.z.P;0D00:00:01;`mreqhisbard1);

batchpub:{[]n:count d:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime from .db.QX where not null sym,0<nticks;if[n;pub[`quote;update bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$(),quoopt:n#enlist "" from d];update nticks:0 from `.db.QX];}; /if[.db.fqopendate<d0:.db.sysdate;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];

.ctrl.histdates:asc exec distinct d from .temp.BARD1 where (d<=2016.11.08)&(d>2016.01.01)
.ctrl.mhisbarsymlst:exec distinct sym from .temp.BARD1 where d=last .ctrl.histdates

.ctrl.histdates:1988.11.28 1989.11.23 1990.11.18 1991.11.13 1992.11.08 1993.11.03 1994.10.28 1995.10.23 1996.10.18 1997.10.13 1998.10.08 1999.10.03 2000.09.28 2001.09.23 2002.09.18 2003.09.13 2004.09.08 2005.09.03 2006.08.28 2007.08.23 2008.08.18 2009.08.13 2010.08.08 2011.08.03 2012.07.28 2013.07.23 2014.07.18 2015.07.13 
.ctrl.skipsyms:`symbol$()
.ctrl.mhisbartime:(last .ctrl.histdates)+16:00
.ctrl.mhisbarsymlst:asc exec sym from .db.QX where ex=`SEHK,status<10

//.db.QX中status为空的非港A股代码自动订阅