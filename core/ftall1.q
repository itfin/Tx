.module.ftall:2018.04.16;

txload "core/fqbase";
txload "core/febase";
txload "feed/ctp/ctpbase";

pub:{[t;x].temp.Z,:enlist (t;x);0 (".upd";t;`time xcols update src:.conf.me,srctime:.z.P,srcseq:.db.seq,dsttime:0Np,time:0Nn from x);.db.seq+:1;};

.init.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysinit];x;());()];} each tsl[];};
.exit.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysexit];x;());()];} each tsl[];};

.timer.ft:{[x]if[(.db.ftdate<d)|(.z.T>.conf.dayendtime)&.db.ftdate=d:.z.D;.db.ftdate:nextworkday[d];beginofday[.db.ftdate]];{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`timer];x;y);()];}[;x] each tsl[];};

istrading:{[t;s]if[not (z:fs2e s) in tkey .conf.ex;:0b];any t within/:.conf.ex[z;`session]+\: -00:01 00:01};

.roll.ft:{[x]{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`dayroll];x;y);()];}[;x] each tsl[];.[.conf.histdb;(.conf.me;`M);,;.db.M];delete from `.db.M;gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;`O);,;select from .db.O where end|tif<>gtc];delete from `.db.O where end|tif<>gtc;delete from `.db.QT;{update `u#id from x;} each `.db.O`.db.M`.db.QT;update flqty:0f,fsqty:0f,lqty0:0f,sqty0:0f,flqty0:0f,fsqty0:0f from `.db.P;update pc:(0.5*(0f^bid)+0f^(ask))^price,price:0n,bid:0n,ask:0n,cumqty:0f from `.db.QX;};

realsyms:{[x;y]$[11h<>abs type sl:.db.Ts[x;`syms];y;0=count sl;y;y inter sl]}; /[tsid;syms]
tsl:{[]x:.db.enablets inter key .db.Ts;x where {1b~.db.Ts[x;`active]} each x};
getfe:{[x]$[x in key .conf.acc;.conf.acc[x;`sym];`]};

newordex:{[sd;pe;t;s;q;p;m;x]if[0b~.db`ftactive;:`];$[0>type t;[ts:.db.Ts[t];a:ts`acc];[ts.db.Ts[t 0];a:ts[`accx;t[1]];t:t[0]]];if[1b~ts`stop;:`];if[null x`tif;x[`tif]:.enum`DAY;if[p<0;x[`tif]:.enum`GOOD_TILL_CANCEL;p:neg[p]]];if[null x`typ;x[`typ]:.enum $[null p;`MARKET;`LIMIT]];fe:getfe[a];k:newid[];.db.O[k;`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt`ntime`status]:(.conf.me;t;a;fe;sfill .conf.acc[a;`acc1];m;s;sd;pe;x`tif;x`typ;q;p;dictstr `tif`typ _x;now[];.enum`PENDING_NEW);if[not null fe;pub[`ordnew;enlist `sym`oid`ft`ts`acc`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt!(fe;k),.db.O[k;`ft`ts`acc`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]]];frzqty[k;q];k}; /[side;posefct;ts|(ts;acc);sym;qty;price;ref;exdict]
neword:newordex[;;;;;;;.enum.nulldict];

openlong:neword[.enum`BUY;.enum`OPEN];closelong:neword[.enum`SELL;.enum`CLOSE];tcloselong:neword[.enum`SELL;.enum`CLOSETODAY];ycloselong:neword[.enum`SELL;.enum`CLOSEYESTODAY];
openshort:neword[.enum`SELL;.enum`OPEN];closeshort:neword[.enum`BUY;.enum`CLOSE];tcloseshort:neword[.enum`BUY;.enum`CLOSETODAY];ycloseshort:neword[.enum`BUY;.enum`CLOSEYESTODAY];

fakord:newordex[;;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fokord:newordex[;;;;;;;``tif!(::;.enum.FILL_OR_KILL)];

fakopenlong:newordex[.enum`BUY;.enum`OPEN;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakcloselong:newordex[.enum`SELL;.enum`CLOSE;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];faktcloselong:newordex[.enum`SELL;.enum`CLOSETODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakycloselong:newordex[.enum`SELL;.enum`CLOSEYESTODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fakopenshort:newordex[.enum`SELL;.enum`OPEN;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakcloseshort:newordex[.enum`BUY;.enum`CLOSE;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];faktcloseshort:newordex[.enum`BUY;.enum`CLOSETODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakycloseshort:newordex[.enum`BUY;.enum`CLOSEYESTODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];

cxlordex:{[x;y;z]r:.db.O[x];if[y<>r`ts;:()];if[(0b~.db`ftactive)|(null r`sym)|(not (null r`cid)|(r[`cn]<ifill .conf`maxcxlcnt))|(r`end);:()];k:newid[];x0:r`x0;if[not null z;if[0=count x0;x0:enlist .enum.nulldict];if[101=type x0[0;`cxlref];x0[0;`cxlref]:`symbol$()];x0[0;`cxlref],:z];.db.O[x;`cid`cstatus`ctime`cn`x0]:(k;.enum`PENDING_CANCEL;now[];1i+0i^r`cn;x0);if[not null r`fe;pub[`ordcxl;enlist `sym`oid`feoid`cid`ordopt!(r`fe;x;r`feoid;k;r`ordopt)]];}; /[oid;ts;cref]

cxlord:{[x]cxlordex[x;.db.O[x;`ts];`];};

qryord:{[x]r:.db.O[x];if[(0b~.db`ftactive)|(null r`sym);:()];if[not null r`fe;pub[`ordqry;enlist `sym`oid`feoid`ordopt!(r`fe;x;r`feoid;r`ordopt)]];};

assetclass:{[x]e:fs2e x;s:fs2s x;$[e=`XSHE;$[8=count string s;`Option;s like "[03]0*";`AShare;s like "20*";`BshareSZ;s like "1[568]*";`Fund;s like "[02]3*";`Warrant;s like "1[12]*";`BondSZ;s like "13*";`RepoSZ;`AShare];e=`XSHG;$[8=count string s;`Option;s like "60[013]*";`AShare;s like "900*";`BshareSS;s like "5[01]*";`Fund;s like "80*";`Warrant;s like "1*";`BondSS;s like "20[124]*";`RepoSS;`AShare];e=`XHKG;`HShare;`Future^.db.QX[x;`assetclass]]}; /[sym]资产类别`Ashare`Fund`Warrant`BshareSZ`BshareSS`BondSZ`BondSS`RepoSZ`RepoSS`Future

isfut:{[x]`Future=assetclass[x]}; /[sym]
isopt:{[x]`Option=assetclass[x]}; /[sym]
isdrv:{[x]isfut[x]|isopt[x]};     /[sym]

ishk:{[x]y:fs2e x; y in `XHKG`XHKE};

iscnfut:{[x]isfut[x]&QX[x;`margintype]<>`US}; /[sym]
iscnopt:{[x]isopt[x]&QX[x;`margintype]<>`US}; /[sym]
iscndrv:{[x]iscnfut[x]|iscnopt[x]};     /[sym]

iswarrant:{[x]{(x within 580001 580999)|(x within 30001 39999)} "I"$string fs2s x}; /x:sym
isfund:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "5*"))|((e=`XSHE)&(f like "1[5-8]*"))}; /[sym]基金
isbond:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "[0-1][1-3]*"))|((e=`XSHE)&(f like "1[1-2]*"))}; /[sym]债券
isrepo:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "204*"))|((e=`XSHE)&(f like "131*"))}; /[sym]回购

ist0:{[x](x in .conf.t0list)|((isfut[x]|isopt[x]|ishk[x])&not .db.QX[x;`product] in .conf.t1list)}; /is T+0?,x:sym

openordn:{[x]exec count i from .db.O where ts=x,not end};
openordsn:{[x;y]exec count i from .db.O where ts=x,sym=y,not end};

availpos:{[s;x]y:x[2];z:s=.enum`SELL;(0f^.db.P[x;$[z;`lqty;`sqty]])-(0f^.db.P[x;$[z;`flqty;`fsqty]])+$[ist0[y];0f;0f^.db.P[x;$[z;`lqty0;`sqty0]]]} /[side;(tid;acc;sym)]仓位可用/平数
availlongpos:availpos[.enum`SELL];availshortpos:availpos[.enum`BUY];
availt0pos:{[s;x]z:s=.enum`SELL;(0f^.db.P[x;$[z;`lqty0;`sqty0]])-0f^.db.P[x;$[z;`flqty0;`fsqty0]]}; /[side;(tid;acc;sym)]本日仓位可用/平数

pxunit:{[x]1e-2^.conf.ac[assetclass x;`pxunit]^.db.QX[x;`pxunit]}; /[sym]
qtyunit:{[x]1e2^.db.QX[x;`qtylot]^.conf.ac[assetclass x;`qtylot]}; /[sym]  
qtyceil:{[x]1e6^.conf.ac[assetclass x;`qtymax]^QX[x;`qtymax]}; /[sym]

getqtymin:{[x]qtyunit[x[0]]}; /[(代码;方向)] 
getqtymax:{[x]qtyceil[x[0]]}; /[(代码;方向)]
roundpx:{[x;y;z]if[(e:fs2e x) in `XHKG`XHKE;:roundpxhk[y;z]];w:pxunit[x];w*$[y=.enum[`BUY];{ceiling x-1e-2};y=.enum[`SELL];{floor x+1e-2};{floor x+0.5}]z%w}; //对委托价格按价格单位进行向对手方取整[sym;BS;px]
roundqty:{[x;y]qm:getqtymin[x];qm*floor (y+1e-2)%qm}; //[(代码;方向);数量]对委托数量按委托单位进行向下取整

roundpxhk:{[x;y]z:.conf.hkticks;z $[x=.enum`BUY;binr;bin][z;y+$[x=.enum`BUY;-1e-10;1e-10]]}; /[BS;px]

limit_orderx:{[h;sd;accno;x;y;q;p;m]p:roundpx[y;sd] `float$p;acc:$[null accno;.db.Ts[x;`acc];@[;accno] .db.Ts[x;`accx]];oq:q-cq:q&abs availpos[sd;x,acc,y];ctq:cq&abs availt0pos[sd;x,acc,y];k0:k1:k2:`;t:$[null accno;x;(x;accno)];if[0<cq;$[(0<ctq)&(1b~.conf.useclosetoday)&(fs2e[y] in .conf.closetodayexlist);[k0:newordex[sd;.enum`CLOSETODAY;t;y;ctq;p;m;h];if[0<clq:cq-ctq;k1:newordex[sd;$[1b~.conf.usecloseyestoday;"Y";.enum`CLOSE];t;y;clq;p;m;h]]];k1:newordex[sd;.enum`CLOSE;t;y;cq;p;m;h]]];if[0<oq;k2:newordex[sd;.enum`OPEN;t;y;oq;p;m;h]];(k0,k1,k2) except `}; /[sided;accno;ts;sym;qty;price;tag]

limit_order:limit_orderx[.enum`nulldict];
xlimit_buyx:limit_orderx[;.enum`BUY];xlimit_sellx:limit_orderx[;.enum`SELL];xlimit_buy:xlimit_buyx[;0N];xlimit_sell:xlimit_sellx[;0N];
limit_buyx:limit_order[.enum`BUY];limit_sellx:limit_order[.enum`SELL];limit_buy:limit_buyx[0N];limit_sell:limit_sellx[0N];
fak_buy:xlimit_buy[``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fak_sell:xlimit_sell[``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fok_buy:xlimit_buy[``tif!(::;.enum.FILL_OR_KILL)];fok_sell:xlimit_sell[``tif!(::;.enum.FILL_OR_KILL)];

.upd.quote:{[x].db.QX:.db.QX uj y:select by sym from x;{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from y] each tsl[];};
.upd.quoteref:{[x].db.QX:.db.QX uj select by sym from x;};

.upd.tsparam:{[x]y:x`typ;z:x`ts;k:x`item;if[not z in key .db.Ts;:()];if[not k in key .db.Ts[z];:()];$[y="S";.db.Ts[z;k]:-9!x`vbin;y="G";if[x[`sym]=.conf.me;pub[`tsparam;enlist `sym`typ`user`ts`item`vbin`msg!(x`src;"A";x`user;z;k;-8!.db.Ts[z;k];"")]];()];}';

.upd.cxlrej:{[x]if[null k:x`oid;:()];r:.db.O[k];if[null r`sym;:()];if[not (.enum`BROKER_ERROR_CXL)~rs:x`reason;.db.O[k;`lastqty`lastpx`cstatus`reason]:(0f;0f;.enum`REJECTED;rs)];if[count m:x`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m];.[{(x)[y;z]};(.db.Ts[x;`event;`cxlrej];r`ts;k);()]}';

.upd.ordnew:{[x]if[not x[`ft] in .conf.ha.backupft;:()];.ha.ordnew[x];frzqty[k;.db.O[k:x`oid;`qty]];}'; /msg from backupfe
.upd.ordcxl:.ha.ordcxl';

chkerrfix:{[x]r:.db.O k:x`oid;if[(x[`typ]=.enum`CORRECT)&(0=r`avgpx)&(r[`cumqty]=x`cumqty)&(0<p:x`avgpx);.db.O[k;`avgpx]:p];};
setcs:{[x]r:.db.O k:x`oid;s:x`status;if[.enum[`CANCELED]=s;.db.O[k;`cstatus]:s;if[null r`ctime;.db.O[k;`ctime]:now[]]];if[r[`cstatus]<>.enum`PENDING_CANCEL;:()];.db.O[k;`cfeoid`cordid]:x`cfeoid`cordid;if[s in .enum`REJECTED`FILLED`DONE_FOR_DAY;.db.O[k;`cstatus]:.enum`REJECTED];if[(x[`typ]=.enum`CORRECT)&(x[`cstatus]=.enum`NULL);.db.O[k;`cstatus]:.enum`NULL];};

frzqty:{[k;q]r:.db.O[k];pe:r`posefct;sd:r`side;tid:r`ts;acc:r`acc;fs:r`sym;sq:$[sd=.enum`SELL;1f;-1f]*q;if[pe in .enum`CLOSE`CLOSETODAY;ff:$[sd=.enum`SELL;`flqty;`fsqty];q1:.db.P[(tid;acc;fs);ff]:sq+q0:0f^.db.P[(tid;acc;fs);ff];ldebug[`frzqty;(k;q;fs;ff;sq;q0;q1)];if[pe=.enum`CLOSETODAY;ff:$[sd=.enum`SELL;`flqty0;`fsqty0];.db.P[(tid;acc;fs);ff]:sq+0f^.db.P[(tid;acc;fs);ff]]];};

execrej:{[k;x].db.O[k;`reason`msg]:x`reason`msg;frzqty[k;neg .db.O[k;`qty]];};

newmatch:{[k;q;p]r:.db.O[k];.db.M[k1:newid[];`sym`price`qty`mtime`maker]:(r`sym;p;q;now[];k);t:r`ts;.[{(x)[y;z]};(.db.Ts[t;`event;`match];t;k1);()];};

getmultiple:{[x]1f^.db.QX[x;`multiplier]};

getfee:{[x]r:.db.QX s:x[0];oc:x[2];qty:x[3];amt:x[4];ex:fs2e s;neg (0f^r $[oc=.enum`OPEN;`rfeetaxom;oc=.enum`CLOSE;`rfeetaxcm;`rfeetaxctm])|abs[qty*0f^r $[oc=.enum`OPEN;`rfeetaxoq;oc=.enum`CLOSE;`rfeetaxcq;`rfeetaxcqt]]+abs[amt*$[ex in `XHKG;2.5e-3;0f]^r $[oc=.enum`OPEN;`rfeetaxoa;oc=.enum`CLOSE;`rfeetaxca;`rfeetaxcat]]}; /[(证券代码;买卖方向;开平标志;成交数量;成交金额)]分笔交易手续费计算(负值) 

settleord:{[k;q;a]r:.db.O k;f:getfee[r[`sym`side`posefct],(q;a)];.db.O[k;`cumamt`cumfee]:(0f^r`cumamt`cumfee)+a,f;pk:r`ts`acc`sym;isb:.enum[`BUY]=r`side;sqty:q*qsign:$[isb;1;-1];iso:r[`posefct]=.enum`OPEN;isl:(isb&iso)|((not isb)&(not iso));nq1:sqty+nq0:(0f^.db.P[pk;$[isl;`lqty;`sqty]]);.db.P[pk;$[isl;`lqty;`sqty]]:nq1;$[iso;$[sqty>0;.db.P[pk;`lqty0]:(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:(0f^.db.P[pk;`sqty0])+sqty];$[r[`posefct]=.enum`CLOSETODAY;$[sqty<0;.db.P[pk;`lqty0]:0|(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:0&(0f^.db.P[pk;`sqty0])+sqty];$[(sqty<0)&(.db.P[pk;`lqty0]>.db.P[pk;`lqty]);.db.P[pk;`lqty0]:.db.P[pk;`lqty];(sqty>0)&(.db.P[pk;`sqty0]<.db.P[pk;`sqty]);.db.P[pk;`sqty0]:.db.P[pk;`sqty];()]]];}; /[OID;lastshares;lastamt] 新增成交清算

.upd.exerpt:{[x]r:.db.O k:x`oid;if[`COMB~r`special;:.upd.comback[x]];s:x`status;if[(null r`sym)|((s=.enum`PENDING_NEW)&(s<>r`status)&(r[`status]<>.enum`NULL));:()];if[(r[`end])&(x[`cumqty]<=r`cumqty);chkerrfix;:()];if[null x`cumqty;x[`cumqty]:0f];if[null x`avgpx;x[`avgpx]:0f];if[(x`cumqty)<r`cumqty;lwarn[`cumqty_decrease;(k;r`cumqty;x`cumqty;x`src;x`seq)];:()];if[(x[`cumqty]~r`qty)&(s<>.enum`FILLED);s:.enum`FILLED];.db.O[k;`status`end`rtime`feoid`ordid`rptopt]:(s;s in .enum`REJECTED`FILLED`DONE_FOR_DAY`CANCELED`REPLACED;now[];x`feoid;x`ordid;x`rptopt);if[count m:x`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m];setcs[x];$[s=.enum`NEW;();s=.enum`REJECTED;execrej[k;x];[lq:(0f^x`cumqty)-0f^r`cumqty;la:(prd 0f^x`cumqty`avgpx)-prd 0f^r`cumqty`avgpx;lp:0f^la% lq;if[0>lq;lwarn[`neg_lastshares;(k;r`cumqty;x`cumqty;lq;x`src;x`seq)];:()];if[0<lq;settleord[k;lq;la*$[.enum[`BUY]=r`side;-1;1]*getmultiple[r`sym]];.db.O[k;`ftime]:now[];newmatch[k;lq;lp]];if[0f<lq;frzqty[k;neg lq]];.db.O[k;`cumqty`lastqty`lastpx]:(x`cumqty;lq;lp);if[(0>=r`avgpx)|(0<x`avgpx);if[.enum[`CANCELED]=s;frzqty[k;neg r[`qty]-0f^x`cumqty]];.db.O[k;`avgpx]:x`avgpx]]];t:r`ts;.[{(x)[y;z]};(.db.Ts[t;`event;`exerpt];t;k);()];}';

.upd.exenoe:{[x]r:.db.O k:x`oid;if[not null r`sym;:()];.db.O[k;`special`ntime`status`tif`typ`ft`ts`acc`fe`acc1`ref`sym`side`posefct`qty`price]:(`NOE;.z.P;.enum`PENDING_NEW;.enum`DAY;.enum`LIMIT),x`ft`ts`acc`src`acc1`ref`osym`side`posefct`cumqty`avgpx;frzqty[k;x`cumqty];x[`feoid`cstatus`cfeoid`cordid`reason]:(`;.enum`NULL;`;`;0N);.upd.exerpt enlist x;}';

.upd.RDUpdate:{[x].db.QX:.db.QX uj get `$x`msg;};

noeexec:{[sno;fta;s;sd;pe;q;p;m]k:newid[];ft:fta[0];ts:fta[1];$[2<count fta;acc:.db.Ts[ts;`accx][fta[2]];acc:.db.Ts[ts;`acc]];pub[`exenoe;enlist `sym`typ`oid`ft`ts`acc`acc1`ref`osym`side`posefct`status`cumqty`avgpx`ordid`msg`rptopt!(ft;.enum`NEW;k;ft;ts;acc;`;`;s;sd;pe;.enum`FILLED;q;p;sno;m;"")];k}; /提交一笔NOE上报记录

.upd.quoteack:{[x]s:x`status;cs:x`cstatus;if[null k:x`qid;:()];kb:.db.QT[k;`bid];ka:.db.QT[k;`aid];$[s=.enum`NEW;[.db.QT[k;`status`feqid`quoteid`rtime]:(s;x`feqid;x`quoteid;now[])];s=.enum`REJECTED;[.db.QT[k;`status`rtime`reason`msg]:(s;now[];x`reason;x`msg);.db.O[kb;`end`status`rtime`reason`msg]:(1b;s;now[];x`reason;x`msg);frzqty[kb;neg .db.O[kb;`qty]];.db.O[ka;`end`status`rtime`reason`msg]:(1b;s;now[];x`reason;x`msg);frzqty[ka;neg .db.O[ka;`qty]]];s=.enum`PENDING_CANCEL;[.db.QT[k;`rtime`cfeqid`cquoteid]:(now[];x`cfeqid;x`cquoteid)];s=.enum`CANCELED;[.db.QT[k;`status`rtime`cstatus]:(s;now[];s)];[]];if[cs=.enum`REJECTED;.db.QT[k;`cstatus`rtime`reason`msg]:(s;now[];x`reason;x`msg)];}'; /报价状态回报 .db.O[kb;`status`rtime]:(s;now[]);.db.O[ka;`status`rtime]:(s;now[])

reqquote:{[x;y]pub[`reqquote;enlist `sym`qsym`qrid!(getfe[.db.Ts[x;`acc]];y;newid[])];}; /[ts;sym]发送询价请求

.upd.quotereq:{[x]quotereq,:x;{[x;y]if[count y;.[{(x)[y;z]};(.db.Ts[x;`event;`quotereq];x;y);()]];}[;x] each tsl[];};

newquote:{[x;y;z;bp;ap;bq;aq;w]if[0b~.db`ftactive;:`];k:newid[];kb:newid[];ka:newid[];ft:.conf.me;acc:.db.Ts[x;`acc];fe:getfe[acc];acc1:sfill .conf.acc[acc;`acc1];bpe:.enum $[bq<=neg availshortpos[(x;acc),z];`CLOSE;`OPEN];ape:.enum $[aq<=availlongpos[(x;acc),z];`CLOSE;`OPEN];.db.O[kb;`special`origid`status`ntime`ft`ts`acc`fe`acc1`ref`sym`side`posefct`qty`typ`price]:(`QT;k;.enum`PENDING_NEW;now[];ft;x;acc;fe;acc1;w;z;.enum`BUY;bpe;bq;.enum`LIMIT;bp);frzqty[kb;.db.O[kb;`qty]];.db.O[ka;`special`origid`status`ntime`ft`ts`acc`fe`acc1`ref`sym`side`posefct`qty`typ`price]:(`QT;k;.enum`PENDING_NEW;now[];ft;x;acc;fe;acc1;w;z;.enum`SELL;ape;aq;.enum`LIMIT;ap);frzqty[ka;.db.O[ka;`qty]];.db.QT[k;`qrid`bid`aid`ft`ts`acc`fe`acc1`ref`sym`bprice`aprice`bqty`aqty`bposefct`aposefct`status`ntime]:(y;kb;ka;ft;x;acc;fe;acc1;w;z;bp;ap;bq;aq;bpe;ape;.enum`PENDING_NEW;now[]);pub[`quotenew;enlist `sym`qid`qrid`ft`ts`acc`acc1`ref`qsym`bid`aid`bprice`aprice`bqty`aqty`bposefct`aposefct!(.db.QT[k;`fe];k),.db.QT[k;`qrid`ft`ts`acc`acc1`ref`sym`bid`aid`bprice`aprice`bqty`aqty`bposefct`aposefct]];k}; /[tid;qrid;sym;bpx;opx;bsz;osz;ref] 发送报价请求

cxlquote:{[x]if[(null .db.QT[x;`sym])|.db.QT[x;`cn]>=ifill .conf`maxcxlcnt;:()];k:newid[];.db.QT[x;`cid`cstatus`ctime`cn]:(k;.enum`PENDING_CANCEL;now[];1+0^.db.QT[x;`cn]);pub[`quotecxl;enlist `sym`qid`feqid`cid!(.db.QT[x;`fe];x;.db.QT[x;`feqid];.db.QT[x;`cid])];}; /[qid] 报价撤单

/支持中金所组合持仓锁定和解锁
newcomb:{[x;y;sd;pe;q;z]k:newid[];acc:.db.Ts[x;`acc];fe:getfe[acc];acc1:sfill .conf.acc[acc;`acc1];.db.O[k;`special`status`ntime`ft`ts`acc`fe`acc1`ref`sym`side`posefct`qty`ordopt]:(`COMB;.enum`PENDING_NEW;now[];.conf.me;x;acc;fe;acc1;z;y;sd;pe;q;"special=`COMB");pub[`ordnew;enlist `sym`oid`ft`ts`acc`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt!(fe;k),.db.O[k;`ft`ts`acc`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]];}; /[tid;sym;side;posefct;qty;ref]发送锁定(OPEN)和解锁(CLOSE)请求

.upd.comback:{[x]k:x`oid;st:x`status;if[(null .db.O[k;`sym])|.db.O[k;`end];:()];.db.O[k;`rtime`status`ordid`msg]:(now[];st),x`ordid`msg;if[st in .enum`FILLED`REJECTED;.db.O[k;`end];1b];if[st=.enum`FILLED;combpos . .db.O[k;`ts`acc`sym`side`posefct`qty]];}; /组合锁定应答处理

combpos:{[x;acc;y;sd;pe;q]fs:fs2s y;ex:fs2e y;z:"&" vs string fs;u:`. sv (`$z[0]),ex;v:`. sv (`$z[1]),ex;s1:$[sd=.enum`BUY;1;-1];s2:s1*$[((u like "*C*")|(`Future=assetclass[u]))&(v like "*P*");-1 -1;1 -1];fy:$[s1>0;`lqty;`sqty];fu:$[s2[0]>0;`lqty;`sqty];fv:$[s2[1]>0;`lqty;`sqty];q*:$[pe=.enum`OPEN;1;-1];q0:0f^.db.P[(x;acc;y);fy];.db.P[(x;acc;y);fy]:$[q0<0;-1;1]*abs[q0]+q;q0:0f^.db.P[(x;acc;u);fu];.db.P[(x;acc;u);fu]:$[q0<0;-1;1]*abs[q0]+neg[q];}; /[tid;sym;side;posefct;qty]处理持仓的锁定和解锁,组合类型(0)双空:期权跨/勒式组合(空C+空P)或合成看涨期权空头(空F+空P),(1)多空:对锁(多F+空F),备兑看涨(多F+空C),牛市看涨价差(多C[S_]+空C[S^]),熊市看涨价差(多C[S^]+空C[S_]),熊市看跌价差(多P[S^]+空P[S_]),牛市看跌价差(多P[S_]+空P[S^])


`initctpq`freectpq`ctpqrun`userLoginQ`subscribe{x set `extfqctp 2:(x;y);}' 2 1 1 2 2;

.enum.CTPMDKey:`TradingDay`InstrumentID`ExchangeID`ExchangeInstID`LastPrice`PreSettlementPrice`PreClosePrice`PreOpenInterest`OpenPrice`HighestPrice`LowestPrice`Volume`Turnover`OpenInterest`ClosePrice`SettlementPrice`UpperLimitPrice`LowerLimitPrice`PreDelta`CurrDelta`UpdateTime`UpdateMillisec`BidPrice1`BidVolume1`AskPrice1`AskVolume1`BidPrice2`BidVolume2`AskPrice2`AskVolume2`BidPrice3`BidVolume3`AskPrice3`AskVolume3`BidPrice4`BidVolume4`AskPrice4`AskVolume4`BidPrice5`BidVolume5`AskPrice5`AskVolume5`AveragePrice;
.enum.CTPQRKey:`TradingDay`InstrumentID`ForQuoteSysID`ForQuoteTime`ActionDay;

//.enum.ctpex:mirror .enum.exmap:`G`A`B`C`D!`CCFX`XSGE`XDCE`XZCE`XINE; 

insu2exch:{[x]exec first ex from .db.QX where esym=x};insu2cont:{[x]"i"$exec first i from .db.QX where esym=x}; 

\d .temp
QREF:QUEUE:L12:L11:L:C:();MDSub:QTSub:()!();
\d .

ctpqconn:{[x;y]if[not any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`run]:initctpq[.conf.ctp.mdfront;.conf.me];1b;};
ctpqdisc:{[x;y]if[any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`run]:freectpq[];.upd.FrontDisconnectQ[];if[((.z.D>d0)|(.z.T>.conf.ctp.mktclosetime)&(.z.D=d0))&(.db.fqclosedate<d0:.db.fqopendate);pubm[`ALL;`MarketClose;.conf.me;string d0];.db.fqclosedate:d0];1b;};

.init.fqctp:{[x]ctpqconn[`;.z.P];};
.exit.fqctp:{[x].ctrl.ctp[`run]:freectpq[];.upd.FrontDisconnectQ[];};

ctpqlogin:{[]if[(not 1b~.ctrl.ctp`ConnectQ)|(1b~.ctrl.ctp`LoginQ);:()];ctpcall[`userLoginQ;.conf.ctp`broker`user`pass`cltver];};

.timer.fqctp:{[x]ctpqlogin[];if[any .z.T within/:.conf.ctp.openrange;dosubscribe[]];batchpub[];};

dosubscribe:{[]if[(1b~.ctrl.ctp`SubscribeQ)|(not 1b~.ctrl.ctp`LoginQ)|(0=count .db.QX);:()];d:select from $[count sl:.conf`ctpsublist;select from .db.QX where product in sl;.db.QX] where ((opendate<=.z.D)&(settledate>=.z.D))|null settledate;if[.conf`skipspsyms;d:delete from d where 3<=count each string product];sm:`$"," sv string sl:$[count ssl:.conf`ctpsymlist;fs2s each ssl;exec fs2s each sym from d];{.temp.MDSub[x]:0b} each sl;subscribe[sm;0];sm:`$"," sv string sl:$[count ssl:.conf`ctpsymlist;ssl;exec fs2s each sym from $[count sl:.conf`ctpsublist;select from .db.QX where product in sl;.db.QX] where assetclass=`Option,opendate<=.z.D,settledate>=.z.D];{.temp.QTSub[x]:0b} each sl;subscribe[sm;1i];.ctrl.ctp[`SubscribeQ`SubscribeTimeQ]:(1b;.z.P);};

.upd.FrontConnectQ:{[x].ctrl.ctp[`ConnectQ`ConntimeQ]:(1b;.z.P);};

.upd.FrontDisconnectQ:{[x].ctrl.ctp[`ConnectQ`LoginQ`SubscribeQ`DiscReasonQ`DisctimeQ]:(0b;0b;0b;x[0];.z.P);};

.upd.UserLoginQ:{[x]y:x[2];if[0=count y;:()];.ctrl.ctp[`LoginQ`LoginTimeQ`FrontID_Q`QSessionID_Q`QMaxOrderRef_Q]:(1b;.z.P),y;}; 

.upd.MDSub:{[x].temp.MDSub[`$x]:1b;};
.upd.QTSub:{[x].temp.QTSub[`$x]:1b;};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[`quote;.temp.QUEUE];.temp.QUEUE:()};

fix0w:{[x]?[1e300<abs[x];0n;x]};

.upd.RDUpdate:{[x]if[`ctp<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;dosubscribe[];};

.upd.DepthMD:{[x]y:.enum.CTPMDKey!x;if[.conf.ctp.debug;.temp.L11,:enlist y];if[.db.fqopendate<d0:"D"$ds:y`TradingDay;pubm[`ALL;`MarketOpen;.conf.me;ds];.db.fqopendate:d0];.temp.d0:d:update upd_serial:"I"${(string x) except ".:"}each sys_recv_time from select contract_id:insu2cont each `$InstrumentID,upd_serial:0n,sys_recv_time:UpdateTime {"T"$x,".",string y}' UpdateMillisec,exchCode:insu2exch each `$InstrumentID,varity_code:`$InstrumentID,deliv_date:`,openPrice:OpenPrice,lastPrice:LastPrice,highestPrice:HighestPrice,lowestPrice:LowestPrice,doneVolume:`float$Volume,chgPrice:0n,upperLimitPrice:UpperLimitPrice,lowerLimitPrice:LowerLimitPrice,hisHighestPrice:0w,hisLowestPrice:-0w,openInterest:OpenInterest,preSettlePrice:PreSettlementPrice,preClosePrice:PreClosePrice,settlePrice:SettlementPrice,turnover:Turnover,preOpenInterest:PreOpenInterest,closePrice:ClosePrice,preDelta:PreDelta,currDelta:CurrDelta,bidPrice1:BidPrice1,bidVolume1:`float$BidVolume1,bidPrice2:BidPrice2,bidVolume2:`float$BidVolume2,bidPrice3:BidPrice3,bidVolume3:`float$BidVolume3,bidPrice4:BidPrice4,bidVolume4:`float$BidVolume4,bidPrice5:BidPrice5,bidVolume5:`float$BidVolume5,askPrice1:AskPrice1,askVolume1:`float$AskVolume1,askPrice2:AskPrice2,askVolume2:`float$AskVolume2,askPrice3:AskPrice3,askVolume3:`float$AskVolume3,askPrice4:AskPrice4,askVolume4:`float$AskVolume4,askPrice5:AskPrice5,askVolume5:`float$AskVolume5 from enlist y;.temp.d1:d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from select sym:{[x;y;z]`$(string x),'(string y),'".",/:(string z)}[varity_code;deliv_date;exchCode],time:sys_recv_time,price:fix0w lastPrice,cumqty:fix0w doneVolume,vwap:fix0w turnover%doneVolume,high:fix0w highestPrice,low:fix0w lowestPrice,o5px:fix0w askPrice5,o5sz:fix0w askVolume5,o4px:fix0w askPrice4,o4sz:fix0w askVolume4,o3px:fix0w askPrice3,o3sz:fix0w askVolume3,o2px:fix0w askPrice2,o2sz:fix0w askVolume2,ask:fix0w askPrice1,asize:fix0w askVolume1,bid:fix0w bidPrice1,bsize:fix0w bidVolume1,b2px:fix0w bidPrice2,b2sz:fix0w bidVolume2,b3px:fix0w bidPrice3,b3sz:fix0w bidVolume3,b4px:fix0w bidPrice4,b4sz:fix0w bidVolume4,b5px:fix0w bidPrice5,b5sz:fix0w bidVolume5,openint:fix0w openInterest,settlepx:fix0w settlePrice,open:fix0w openPrice,pc:fix0w preClosePrice,sup:fix0w upperLimitPrice,inf:fix0w lowerLimitPrice,recvtime:.z.P,exlocaltime:.z.P from d;.temp.d:d:delete from d where (0>cumqty);if[count d;if[.conf.ctp.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:`timestamp$d0+time,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$(),quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[`quote;d2]]];};

.upd.QuoteReq:{[x]d:select sym:{[x]` sv x,exec first ex from .db.QX where esym=x} each `$InstrumentID,reqid:`$ForQuoteSysID,reqtime:`timestamp$("D"$TradingDay)+("T"$ForQuoteTime),actiondate:"D"$ActionDay from z:enlist y:.enum.CTPQRKey!x;.temp.L12,:z;pub[`quotereq;d];}
$[.z.o=`l64;`initctpt`freectpt`ctptrun`userLoginT`qrySettlementInfoConfirm`settlementInfoConfirm`orderInsert`orderAction`qryMaxOrderVolume`qryInstrument`qryTradingAccount`qryInvestorPosition`qryOrder`qryTrade`qryInvestor`qryTradingCode`qryInstrumentCommissionRate`qryInstrumentMarginRate`qryExchange`qryInvestorPositionDetail`qryNotice`qryInvestorPositionCombineDetail`qryEWarrantOffset`qryTransferSerial`qryTradingNotice`qryBrokerTradingParams`qryBrokerTradingAlgos`forQuoteInsert`quoteInsert`quoteAction`combActionInsert`qryCombInstrumentGuard`qryCombAction {x set `extfectp 2:(x;y);}' 3 1 1,30#2;`initctpt`freectpt`ctptrun`userLoginT`qrySettlementInfoConfirm`settlementInfoConfirm`orderInsert`orderAction`qryMaxOrderVolume`qryInstrument`qryTradingAccount`qryInvestorPosition`qryOrder`qryTrade`qryInvestor`qryTradingCode`qryInstrumentCommissionRate`qryInstrumentMarginRate`qryExchange`qryInvestorPositionDetail`qryNotice`qryInvestorPositionCombineDetail`qryEWarrantOffset`qryTransferSerial`qryTradingNotice`qryBrokerTradingParams`qryBrokerTradingAlgos`forQuoteInsert`quoteInsert`quoteAction {x set `extfectp 2:(x;y);}' 2 1 1,27#2];

\d .enum
`D_Buy`D_Sell set' "01"; /TFtdcDirectionType
`OF_Open`OF_Close`OF_ForceClose`OF_CloseToday`OF_CloseYesterday`OF_ForceOff`OF_LocalForceClose set' "0123456"; /TThostFtdcOffsetFlagType
`HF_Speculation`HF_Arbitrage`HF_Hedge set' "123"; /TFtdcHedgeFlagType
`CC_Immediately`CC_Touch`CC_TouchProfit`CC_ParkedOrder`CC_LastPriceGreaterThanStopPrice`CC_LastPriceGreaterEqualStopPrice`CC_LastPriceLesserThanStopPrice`CC_LastPriceLesserEqualStopPrice`CC_AskPriceGreaterThanStopPric`CC_AskPriceGreaterEqualStopPrice`CC_AskPriceLesserThanStopPrice`CC_AskPriceLesserEqualStopPrice`CC_BidPriceGreaterThanStopPrice`CC_BidPriceGreaterEqualStopPrice`CC_BidPriceLesserThanStopPrice`CC_BidPriceLesserEqualStopPrice set' "123456789ABCDEFH"; /TThostFtdcContingentConditionType

`PD_Net`PD_Long`PD_Short set' "123"; /TFtdcPosiDirectionType
`PC_Futures`PC_Options`PC_Combination`PC_Spot`PC_EFP`PC_SpotOption set' "123456"; /TFtdcProductClassType
`PSD_Today`PSD_History set' "12"; /TFtdcPositionDateType
`OPT_AnyPrice`OPT_LimitPrice`OPT_BestPrice`OPT_LastPrice`OPT_LastPricePlusOneTicks`OPT_LastPricePlusTwoTicks`OPT_LastPricePlusThreeTicks`OPT_AskPrice1`OPT_AskPrice1PlusOneTicks`OPT_AskPrice1PlusTwoTicks`OPT_AskPrice1PlusThreeTicks`OPT_BidPrice1`OPT_BidPrice1PlusOneTicks`OPT_BidPrice1PlusTwoTicks`OPT_BidPrice1PlusThreeTicks set' "123456789ABCDEF"; /TFtdcOrderPriceTypeType
`TC_IOC`TC_GFS`TC_GFD`TC_GTD`TC_GTC`TC_GFA set' "123456"; /TFtdcTimeConditionType
`VC_AV`VC_MV`VC_CV set' "123"; /TFtdcVolumeConditionType
`FCC_NotForceClose`FCC_LackDeposit`FCC_ClientOverPositionLimit`FCC_MemberOverPositionLimit`FCC_NotMultiple`FCC_Violation`FCC_Other`FCC_PersonDeliv set' "01234567"; /TThostFtdcForceCloseReasonType
`OSS_InsertSubmitted`OSS_CancelSubmitted`OSS_ModifySubmitted`OSS_Accepted`OSS_InsertRejected`OSS_CancelRejected`OSS_ModifyRejected set' "0123456"; /TThostFtdcOrderSubmitStatusType
`OSRC_Participant`OSRC_Administrator set' "01"; /TFtdcOrderSourceType
`OST_AllTraded`OST_PartTradedQueueing`OST_PartTradedNotQueueing`OST_NoTradeQueueing`OST_NoTradeNotQueueing`OST_Canceled`OST_Unknown`OST_NotTouched`OST_Touched set' "012345abc"; /TThostFtdcOrderStatusType
`ORDT_Normal`ORDT_DeriveFromQuote`ORDT_DeriveFromCombination`ORDT_Combination`ORDT_ConditionalOrder`ORDT_Swap set' "012345"; /TThostFtdcOrderTypeType
`ER_Broker`ER_Host`ER_Maker set' "123"; /TThostFtdcTradingRoleType
`TRDT_Common`TRDT_OptionsExecution`TRDT_OTC`TRDT_EFPDerived`TRDT_CombinationDerived  set' "01234"; /TThostFtdcTradeTypeType
`PSRC_LastPrice`PSRC_Buy`PSRC_Sell set' "012"; /TThostFtdcPriceSourceType
`TSRC_NORMAL`TSRC_QUERY set' "01"; /TThostFtdcTradeSourceType
`AF_Delete`AF_Modify set' "03" ; /TThostFtdcActionFlagType
`CIDT_Speculation`CIDT_Arbitrage`CIDT_Hedge set' "123"; /TFtdcClientIDTypeType
`IS_BeforeTrading`IS_NoTrading`IS_Continous`IS_AuctionOrdering`IS_AuctionBalance`IS_AuctionMatch`IS_Closed set' "0123456"; /TThostFtdcInstrumentStatusType
`CMDR_Comb`CMDR_UnComb set' "01"; /TThostFtdcCombDirectionType

ctpexmap:`CFFEX`SHFE`DCE`CZCE`INE!`CCFX`XSGE`XDCE`XZCE`XINE;
ctpstatusmap:"ab310425c"!.enum`PENDING_NEW`NEW`NEW`PARTIALLY_FILLED`FILLED`PENDING_CANCEL`PENDING_CANCEL`CANCELED`ACCEPTED_FOR_BIDDING;
ctpsubmitstatusmap:"0123456"!.enum`PENDING_NEW`PENDING_CANCEL`PENDING_REPLACE`NEW`REJECTED`REJECTED_CANCEL`REJECTED_REPLACE;

ctpclassmap:"123456"!`Future`Option`Combination`Spot`EFP`Option;
ctpphasemap:"0123"!`NotStart`Started`Pause`Expired;
\d .

ctpposefct:{[x;y]$[x=.enum`OPEN;.enum`OF_Open;(x=.enum`CLOSETODAY)&(y in `XSGE`XINE);.enum`OF_CloseToday;.enum`OF_Close]}; /[posefct;ex]

ctptconn:{[x;y]if[not any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`Run]:initctpt[.conf.ctp.tdfront;.conf.me;0i];1b;};
ctptdisc:{[x;y]if[any .z.T within/: .conf.ctp.openrange;:()];.ctrl.ctp[`Run]:freectpt[];.upd.FrontDisconnectT[];1b};

.init.fectp:{[x]ctptconn[`;.z.P];};
.exit.fectp:{[x]ctptdisc[`;.z.P];};
.timer.fectp:{[x]if[not 1b~.ctrl.ctp`ConnectT;:()];ctptlogin[];if[(1b~.ctrl.ctp`LoginT)&(.z.T within .conf.ctp.qryrange);qrymargin[];qryfee[]];}; 
.roll.fectp:{[x].ctrl.ctp[`Confirm]:0b;};

//insu2exch:{$[x like "IF*";`G;`]};insu2cont:{[x]"I"$(string 100 sv "i"$-4_x),-4#x};

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

ctptlogin:{[]if[(1b~.ctrl.ctp`LoginT)|(1b~.ctrl.ctp`PassErr);:()];ctpcall[`userLoginT;.conf.ctp`broker`user`pass`cltver];};

confirmsettlement:{[]ctpcall[`settlementInfoConfirm;.conf.ctp`broker`user];};

qrymargin:{[]if[null x:exec first esym from .db.QX where assetclass=`Future,null rmarginl,4>=count each string product;:()];ctpcall[`qryInstrumentMarginRate;(.conf.ctp`broker`user),x,"1"];};
qryfee:{[]if[null x:exec first esym from .db.QX where assetclass=`Future,null rfeetaxoa,4>=count each string product;:()];ctpcall[`qryInstrumentCommissionRate;(.conf.ctp`broker`user),x];};

resetqx:{[]delete from `.db.QX where assetclass=`Future;};

.upd.FrontConnectT:{[x].ctrl.ctp[`ConnectT`ConntimeT]:(1b;.z.P);};

.upd.FrontDisconnectT:{[x].ctrl.ctp[`ConnectT`LoginT`DiscReasonT`DisctimeT]:(0b;0b;x[0];.z.P);};

.upd.UserLoginT:{[x]y:x[2];if[0=count y;:()];.ctrl.ctp[`LoginT`LoginTimeT`FrontID`SessionID`MaxOrderRef]:(1b;.z.P),y;$[1b~.ctrl.ctp[`Confirm];ctpcall[`qrySettlementInfoConfirm;.conf.ctp`broker`user];confirmsettlement[]];};

.upd.ordnew:{[x]if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[count opt:x`ordopt;h:strdict opt;if[`COMB~h`special;:.upd.combnew[x]]];k1:newidl[];.db.O[k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict,`FrontID`SessionID!.ctrl.ctp[`FrontID`SessionID]),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not (1b~.ctrl.ctp`LoginT)&(.conf.ctp.ordmax>count .db.O);rejectord[k;1i;"CTP_Not_Ready"];:()];esym:fs2s x`osym;ctpcall[`orderInsert;(.conf.ctp`broker`user),(esym;k1;$[x[`side]=.enum`BUY;.enum`D_Buy;.enum`D_Sell];`int$x`qty;$[(0<x[`price])|(esym like "SP*");.enum`OPT_LimitPrice;.enum`OPT_AnyPrice];x`price;$[x[`tif] in .enum`IMMEDIATE_OR_CANCEL`FILL_OR_KILL;.enum`TC_IOC;.enum`TC_GFD];$[x[`tif]=.enum`FILL_OR_KILL;.enum`VC_CV;.enum`VC_AV];`$ctpposefct[x[`posefct];fs2e x`osym];`$.enum`HF_Speculation)];}'; 

.upd.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db.O[k];if[null r`sym;:()];.db.O[k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];ctpcall[`orderAction;(.conf.ctp`broker`user),(fs2s r`sym;0;h`FrontID;h`SessionID;x`feoid;`;`;.enum`AF_Delete)];}'; 

.upd.reqquote:{[x]if[x[`sym]<>.conf.me;:()];r:ctpcall[`forQuoteInsert;(.conf.ctp`broker`user),(fs2s x`qsym;newidl[])]}';

.upd.quotenew:{[x]if[x[`sym]<>.conf.me;:.ha.quotenew[x]];if[not null .db.QT[k:x`qid;`sym];:()];k1:newidl[];.db.QT[k;`feqid`ntime`status`qrid`bid`aid`ft`ts`acc`fe`acc1`ref`sym`bprice`aprice`bqty`aqty`bposefct`aposefct]:(k1;now[];.enum`PENDING_NEW),x`qrid`bid`aid`ft`ts`acc`sym`acc1`ref`qsym`bprice`aprice`bqty`aqty`bposefct`aposefct;kb:x`bid;ka:x`aid;fs:x`qsym;ex:fs2e fs;bp:x`bprice;ap:x`aprice;bq:x`bqty;aq:x`aqty;bpe:x`bposefct;ape:x`aposefct;x0:enlist .enum.nulldict,`FrontID`SessionID!.ctrl.ctp[`FrontID`SessionID];.db.O[kb;`special`origid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`typ`qty`price]:(`QT;k;now[];.enum`PENDING_NEW;x0;x`ft;x`ts;x`acc;x`sym;x`acc1;x`ref;fs;.enum`BUY;bpe;.enum`LIMIT;bq;bp);.db.O[ka;`special`origid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`typ`qty`price]:(`QT;k;now[];.enum`PENDING_NEW;x0;x`ft;x`ts;x`acc;x`sym;x`acc1;x`ref;fs;.enum`BUY;ape;.enum`LIMIT;aq;ap);.temp.r:r:ctpcall[`quoteInsert;(.conf.ctp`broker`user),(fs2s fs;k1;`int$aq;`int$bq;ap;bp;ctpposefct[ape;ex];ctpposefct[bpe;ex];.enum`HF_Speculation;.enum`HF_Speculation)];.db.QT[k;`linkid]:`$string first r;ackquote[k];}'; /报价处理

.upd.quotecxl:{[x]if[x[`sym]<>.conf.me;:.ha.quotecxl[x]];if[null .db.QT[k:x`qid;`sym];:()];.db.QT[k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);r:.db.O[.db.QT[k;`bid]];h:$[count r[`x0];r[`x0;0];strdict r`rptopt];r:ctpcall[`quoteAction;(.conf.ctp`broker`user),(fs2s .db.QT[k;`sym];0;h`FrontID;h`SessionID;x`feqid;`;`;.enum`AF_Delete)];ackquote[k;()];}'; /撤销报价处理

.upd.combnew:{[x]if[not null .db.O[k:x`oid;`sym];:()];k1:newidl[];.db.O[k;`special`feoid`ntime`status`ft`ts`sym`side`posefct`qty]:(`COMB;k1;.z.P;.enum`NEW),x`ft`ts`osym`side`posefct`qty;r:ctpcall[`combActionInsert;(.conf.ctp`broker`user),(fs2s .db.O[k;`sym];k1;$[x[`side]=.enum`BUY;.enum`D_Buy;.enum`D_Sell];`int$x`qty;$[x[`posefct]=.enum`OPEN;.enum`CMDR_Comb;.enum`CMDR_UnComb];.enum`HF_Speculation)];execrpt[k];}; /组合锁定解锁

.upd.OrderInsertErr:{[x]if[0=count x;:()];.temp.L6,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`UserForceClose`ErrorID`ErrorMsg!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db.O[z;`rtime`status`reason`msg]:(now[];.enum`REJECTED;y`ErrorID;y`ErrorMsg);execrpt[z];};
.upd.OrderInsert:{[x].upd.OrderInsertErr x[2];};

.upd.OrderActionErr:{[x]if[0=count x;:()];.temp.L7,:enlist y:`BrokerID`InvestorID`OrderActionRef`OrderRef`RequestID`FrontID`SessionID`ExchangeID`OrderSysID`ActionFlag`LimitPrice`VolumeChange`UserID`InstrumentID`ErrorID`ErrorMsg!x;z:idfe2ft `$y`OrderRef;if[null z;:()];.db.O[z;`cstatus`reason`msg]:(.enum`REJECTED;y`ErrorID;y`ErrorMsg);r:.db.O[z];rejectcxl[r`ft;z;r`cid;r`reason;r`msg];};
.upd.OrderAction:{[x].upd.OrderActionErr x[2];}; /

.upd.Order:{[x].temp.L8,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x;z:idfe2ft `$y`OrderRef;z1:`;if[(null .db.O[z;`sym])&(0<w:y`RequestID);if[not null k:exec first id from .db.QT where linkid=`$string w;z1:z;z:.db.QT[k;$[.enum[`D_Buy]=y`Direction;`bid;`aid]]]];if[null .db.O[z;`sym];:()];st:.enum[`ctpstatusmap] y`OrderStatus;.db.O[z;`x0;0],:`BrokerOrderSeq`TraderID`OrderLocalID!y`BrokerOrderSeq`TraderID`OrderLocalID;.db.O[z;`rtime`ordid`ex`esym`rptopt]:(now[];`$y`OrderSysID;`$y`ExchangeID;`$y`ExchangeInstID;dictstr .db.O[z;`x0;0]);if[count m:y`StatusMsg;.db.O[z;`msg]:m];if[st=.enum`CANCELED;.db.O[z;`cstatus]:st];if[(st=.enum`CANCELED)&((.db.O[z;`cumqty]|0f)<cq:`float$y`VolumeTraded);.temp.DelayedCancel[z]:cq;:()];.db.O[z;`status]:st;if[not .db.O[z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

//.upd.Order:{[x].temp.L8,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x;z:idfe2ft `$y`OrderRef;z1:`;w:`$y`OrderSysID;if[(null .db.O[z;`sym]);z1:z;z:exec first id from .db.O where ordid=w];if[null .db.O[z;`sym];:()];st:.enum[`ctpstatusmap] y`OrderStatus;.db.O[z;`x0;0],:`BrokerOrderSeq`TraderID`OrderLocalID!y`BrokerOrderSeq`TraderID`OrderLocalID;.db.O[z;`rtime`status`ordid`ex`esym`origid`rptopt]:(now[];st;`$y`OrderSysID;`$y`ExchangeID;`$y`ExchangeInstID;z1;dictstr .db.O[z;`x0;0]);if[count m:y`StatusMsg;.db.O[z;`msg]:m];if[st=.enum`CANCELED;.db.O[z;`cstatus]:st];if[not .db.O[z;`status] in .enum`PARTIALLY_FILLED`FILLED;execrpt[z]];};

.upd.Trade:{[x].temp.L9,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`ExchangeID`TradeID`Direction`OrderSysID`ParticipantID`ClientID`TradingRole`ExchangeInstID`OffsetFlag`HedgeFlag`Price`Volume`TradeDate`TradeTime`TradeType`PriceSource`TraderID`OrderLocalID`ClearingPartID`BusinessUnit`SequenceNo`TradingDay`SettlementID`BrokerOrderSeq`TradeSource!x;z:idfe2ft `$y`OrderRef;w:`$y`OrderSysID;if[null .db.O[z;`sym];z:exec first id from .db.O where ordid=w];if[(null fs:.db.O[z;`sym]);:()];q:`float$y`Volume;p:y`Price;lq:0f^.db.O[z;`cumqty];lp:0f^.db.O[z;`avgpx];if[(fs like "SP*")|(fs like "IPS*");s0:`$y`InstrumentID;s1:first sl:`$"&" vs last " " vs string fs2s fs;s2:last sl;if[0=count .db.O[z;`x0];.db.O[z;`x0]:enlist .enum`nulldict];qfld:$[s0=s1;`lcumqty;`scumqty];pfld:$[s0=s1;`lavgpx;`savgpx];.db.O[z;`x0;0;qfld]:q+lq0:0f^.db.O[z;`x0;0;qfld];.db.O[z;`x0;0;pfld]:((q*p)+lq0*0f^.db.O[z;`x0;0;pfld])%(q+lq0);$[(cq<=lq)|(.db.O[z;`x0;0;`lcumqty]<>cq:.db.O[z;`x0;0;`scumqty]);:();[q:cq-lq;p:((cq*.db.O[z;`x0;0;`lavgpx]-.db.O[z;`x0;0;`savgpx])-lq*lp)%q]]];.db.O[z;`ftime`lastqty`lastpx`cumqty`avgpx]:(now[];q;p;q+lq;((q*p)+(lq*lp))%(q+lq));lwarn[`trade;(z;`$y`OrderRef;lq;q;.db.O[z;`cumqty])];if[(.db.O[z;`cstatus]=.enum`CANCELED)&(.db.O[z;`status]<>.enum`CANCELED);if[.db.O[z;`cumqty]>=.temp.DelayedCancel[z];.db.O[z;`status]:.enum`CANCELED]];execrpt[z];}; /对SP单进行特殊处理,前腿(买单)的cumqty/avgpx记入O表的commamt/stoppx字段,后腿(卖单)的cumqty/avgpx记入O表的sentqty/takepx字段,当双腿的成交量一致时更新SP单的的对应信息并推送回报 

.upd.ForQuote:{[x].temp.IL,:enlist x;}; /询价

.upd.Quote:{[x].temp.IL,:enlist y:`BrokerID`InvestorID`InstrumentID`QuoteRef`UserID`AskPrice`BidPrice`AskVolume`BidVolume`RequestID`BusinessUnit`AskOffsetFlag`BidOffsetFlag`AskHedgeFlag`BidHedgeFlag`QuoteLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`NotifySequence`OrderSubmitStatus`TradingDay`SettlementID`QuoteSysID`InsertDate`InsertTime`CancelTime`QuoteStatus`ClearingPartID`SequenceNo`AskOrderSysID`BidOrderSysID`FrontID`SessionID`UserProductInfo`StatusMsg`ActiveUserID`BrokerQuoteSeq!x;k:qidfe2ft `$y`QuoteRef;if[null k;:()];qs:.enum[`ctpstatusmap] y`QuoteStatus;cs:.db.QT[k;`cstatus];qss:.enum.ctpsubmitstatusmap y`OrderSubmitStatus;if[qss=.enum`REJECTED;qs:qss];.db.QT[k;`status`cstatus`quoteid`rtime`msg]:(qs;cs;`$y`QuoteSysID;now[];y`StatusMsg);if[(not null z:`$y`AskOrderSysID)&null .db.O[.db.QT[k;`aid];`ordid];.db.O[.db.QT[k;`aid];`status`ordid]:(.enum`NEW;z)];if[(not null z:`$y`BidOrderSysID)&null .db.O[.db.QT[k;`bid];`ordid];.db.O[.db.QT[k;`bid];`status`ordid]:(.enum`NEW;z)];ackquote[k];}; /报价

.upd.ForQuoteInsertErr:{[x]if[0=count x;:()];}; /询价拒绝

.upd.QuoteInsertErr:{[x].temp.IL,:enlist x;if[null k:exec first id from .db.QT where linkid=`$string x[9];:()];.db.QT[k;`status`reason`msg`rtime]:(.enum`REJECTED;x[15];x[16];now[]);.db.O[.db.QT[k;`bid];`status`reason`msg`rtime]:.db.QT[k;`status`reason`msg`rtime];.db.O[.db.QT[k;`oid];`status`reason`msg`rtime]:.db.QT[k;`status`reason`msg`rtime];ackquote[k];}; /报价拒绝

.upd.QuoteActionErr:{[x]x:x[2];if[0=count x;:()];}; /撤销报价拒绝

.upd.QuoteAction:{[x]x:x[2];if[0=count x;:()];y:`BrokerID`InvestorID`QuoteActionRef`QuoteRef`RequestID`FrontID`SessionID`ExchangeID`QuoteSysID`ActionFlag`UserID`InstrumentID`ErrorID`ErrorMsg!x;k:qidfe2ft `$y`QuoteRef;if[null k;:()];.db.QT[k;`cstatus`reason`msg]:(.enum`REJECTED;y`ErrorID;y`ErrorMsg);ackquote[k];}; /撤销报价

.upd.CombAction:{[x]if[0=count x;:()];.temp.L11,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ActionLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`ActionStatus`NotifySequence`TradingDay`SettlementID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg!x;k:idfe2ft `$y`CombActionRef;if[(null .db.O[k;`sym])|.db.O[k;`end];:()];.db.O[k;`x0`ordid`status`msg]:(enlist .enum.nulldict,`FrontID`SessionID!y`FrontID`SessionID;`$y`ActionLocalID;{$[x=.enum`ACCEPTED_FOR_BIDDING;.enum`REJECTED;x]} .enum.ctpstatusmap y`ActionStatus;y`StatusMsg);if[.db.O[k;`status] in .enum`FILLED`REJECTED;.db.O[k;`end]:1b];execrpt[k];}; /组合申请确认

.upd.CombActionInsert:{[x]x:x[2];if[0=count x;:()];.temp.L12,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag!x;}; /组合申请委托(CTP直接拒绝时会返回)

.upd.CombActionInsertErr:{[x]if[0=count x;:()];.temp.L13,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ErrorID`ErrorMsg!x;k:idfe2ft `$y`CombActionRef;if[(null .db.O[k;`sym])|.db.O[k;`end];:()];.db.O[k;`end`status`reason`msg]:(1b;.enum`REJECTED;y`ErrorID;y`ErrorMsg);execrpt[k];}; /组合申请拒绝(CTP直接拒绝)

.upd.QryCombInstrumentGuard:{[x]x:x[2];if[0=count x;:()];.temp.L14,:enlist y:`BrokerID`InstrumentID`GuarantRatio!x;}; /查询组合合约安全系数

.upd.QryCombAction:{[x]x:x[2];if[0=count x;:()];.temp.L15,:enlist y:`BrokerID`InvestorID`InstrumentID`CombActionRef`UserID`Direction`Volume`CombDirection`HedgeFlag`ActionLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`ActionStatus`NotifySequence`TradingDay`SettlementID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg!x;}; /查询组合申请

.upd.QueryOrder:{[k].temp.L4:();if[null .db.O[k;`sym];:()];r:ctpcall[`qryOrder;(.conf.ctp`broker`user),(`;`;.db.O[k;`ordid];`;`)];};

.upd.QrFund:{[x]r:ctpcall[`qryTradingAccount;.conf.ctp`broker`user];};

.upd.QueryPos:{[x].temp.L3:();r:ctpcall[`qryInvestorPosition;(.conf.ctp`broker`user),`];};

.upd.QueryAllOrder:{[x].temp.L4:();r:ctpcall[`qryOrder;(.conf.ctp`broker`user),5#`];};

.upd.QueryMatch:{[x].temp.L5:();r:ctpcall[`qryTrade;(.conf.ctp`broker`user),5#`];};

.upd.QrySettlementInfoConfirm:{[x]y:x[2];if[0<count y;:()];confirmsettlement[];};

.upd.QueryInstrument:{[x].temp.L1:();r:ctpcall[`qryInstrument;4#`];};

.upd.SettlementInfoConfirm:{[x].ctrl.ctp[`Confirm]:1b;.upd.QueryInstrument[];};

updaterd:{[](path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,assetclass,product,multiplier,pxunit,qtylot,qtymax,qtymaxm,qtymaxl,qtymaxs,rmarginl,rmargins,rfeetaxoa,rfeetaxoq,rfeetaxca,rfeetaxcq,rfeetaxcat,rfeetaxcqt,settledate,opendate,createdate,lifephase,status from .db.QX;pubm[`ALL;`RDUpdate;`ctp;string path];};

.upd.QryInstrument:{[x]if[0=count x[2];:()];.temp.L1,:enlist y:`InstrumentID`ExchangeID`InstrumentName`ExchangeInstID`ProductID`ProductClass`DeliveryYear`DeliveryMonth`MaxMarketOrderVolume`MinMarketOrderVolume`MaxLimitOrderVolume`MinLimitOrderVolume`VolumeMultiple`PriceTick`CreateDate`OpenDate`ExpireDate`StartDelivDate`EndDelivDate`InstLifePhase`IsTrading`PositionType`PositionDateType`LongMarginRatio`ShortMarginRatio!x[2];fs:se2fs (s:`$y`InstrumentID),e:.enum.ctpexmap `$y`ExchangeID;if[null .db.QX[fs;`esym];.db.QX[fs;`ex`esym`name`assetclass`product`multiplier`pxunit`qtylot`qtymax`qtymaxm`settledate`opendate`createdate`lifephase`status]:(e;s;`$y`InstrumentName;.enum.ctpclassmap y`ProductClass;`$y`ProductID;`float$y`VolumeMultiple;y`PriceTick;`float$y`MinLimitOrderVolume;`float$y`MaxLimitOrderVolume;`float$y`MaxMarketOrderVolume;"D"$y`ExpireDate;"D"$y`OpenDate;"D"$y`CreateDate;.enum.ctpphasemap y`InstLifePhase;y`IsTrading)];if[x[1];updaterd[]];};

.upd.QryInstrumentCommissionRate:{[x]if[0=count x[2];:()];.temp.L0,:enlist y:`InstrumentID`InvestorRange`BrokerID`InvestorID`OpenRatioByMoney`OpenRatioByVolume`CloseRatioByMoney`CloseRatioByVolume`CloseTodayRatioByMoney`CloseTodayRatioByVolume!x[2];update rfeetaxoa:y`OpenRatioByMoney,rfeetaxoq:y`OpenRatioByVolume,rfeetaxca:y`CloseRatioByMoney,rfeetaxcq:y`CloseRatioByVolume,rfeetaxcat:y`CloseTodayRatioByMoney,rfeetaxcqt:y`CloseTodayRatioByVolume from `.db.QX where (product=`$y`InstrumentID)|esym=`$y`InstrumentID;};

.upd.QryInstrumentMarginRate:{[x]if[0=count x[2];:()];.temp.L10,:enlist y:`InstrumentID`InvestorRange`BrokerID`InvestorID`HedgeFlag`LongMarginRatioByMoney`LongMarginRatioByVolume`ShortMarginRatioByMoney`ShortMarginRatioByVolume`IsRelative!x[2];update rmarginl:y`LongMarginRatioByMoney,rmargins:y`ShortMarginRatioByMoney from `.db.QX where esym=`$y`InstrumentID;};

.upd.QryTradingAccount:{[x]if[0=count x[2];:()];.temp.L2,:enlist y:`BrokerID`AccountID`PreMortgage`PreCredit`PreDeposit`PreBalance`PreMargin`InterestBase`Interest`Deposit`Withdraw`FrozenMargin`FrozenCash`FrozenCommission`CurrMargin`CashIn`Commission`CloseProfit`PositionProfit`Balance`Available`WithdrawQuota`Reserve`TradingDay`SettlementID`Credit`Mortgage`ExchangeMargin`DeliveryMargin`ExchangeDeliveryMargin!x[2];};

.upd.QryInvestorPosition:{[x]if[0=count x[2];:()];.temp.L3,:enlist `InstrumentID`BrokerID`InvestorID`PosiDirection`HedgeFlag`PositionDate`YdPosition`Position`LongFrozen`ShortFrozen`LongFrozenAmount`ShortFrozenAmount`OpenVolume`CloseVolume`OpenAmount`CloseAmount`PositionCost`PreMargin`UseMargin`FrozenMargin`FrozenCash`FrozenCommission`CashIn`Commission`CloseProfit`PositionProfit`PreSettlementPrice`SettlementPrice`TradingDay`SettlementID`OpenCost`ExchangeMargin`CombPosition`CombLongFrozen`CombShortFrozen`CloseProfitByDate`CloseProfitByTrade`TodayPosition`MarginRateByMoney`MarginRateByVolume!x[2];if[x[1];];};

.upd.QryOrder:{[x]if[0=count x[2];:()];.temp.L4,:enlist y:`BrokerID`InvestorID`InstrumentID`OrderRef`UserID`OrderPriceType`Direction`CombOffsetFlag`CombHedgeFlag`LimitPrice`VolumeTotalOriginal`TimeCondition`GTDDate`VolumeCondition`MinVolume`ContingentCondition`StopPrice`ForceCloseReason`IsAutoSuspend`BusinessUnit`RequestID`OrderLocalID`ExchangeID`ParticipantID`ClientID`ExchangeInstID`TraderID`InstallID`OrderSubmitStatus`NotifySequence`TradingDay`SettlementID`OrderSysID`OrderSource`OrderStatus`OrderType`VolumeTraded`VolumeTotal`InsertDate`InsertTime`ActiveTime`SuspendTime`UpdateTime`CancelTime`ActiveTraderID`ClearingPartID`SequenceNo`FrontID`SessionID`UserProductInfo`StatusMsg`UserForceClose`ActiveUserID`BrokerOrderSeq`RelativeOrderSysID!x[2];if[x[1];.upd.Order each flip value flip L4];};

.upd.QryTrade:{[x]if[0=count x[2];:()];.temp.L5,:enlist `BrokerID`InvestorID`InstrumentID`OrderRef`UserID`ExchangeID`TradeID`Direction`OrderSysID`ParticipantID`ClientID`TradingRole`ExchangeInstID`OffsetFlag`HedgeFlag`Price`Volume`TradeDate`TradeTime`TradeType`PriceSource`TraderID`OrderLocalID`ClearingPartID`BusinessUnit`SequenceNo`TradingDay`SettlementID`BrokerOrderSeq`TradeSource!x[2];if[x[1];];};

.upd.QryTradingCode:{[x]};
.upd.QryExchange:{[x]};
.upd.CTPError:{[x].temp.X:x;if[1|x[2;0] in 48 75i;.ctrl.ctp[`PassErr]:1b];};
