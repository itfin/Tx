.module.ftbase:2018.12.05;

.init.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysinit];x;());()];} each tsl[];};
.exit.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysexit];x;());()];} each tsl[];};

.timer.ft:{[x]if[(.db.ftdate<d)|(.z.T>.conf.dayendtime)&.db.ftdate=d:.z.D;.db.ftdate:nextworkday[.db.ftdate];if[.conf.me in $[`rollft in key .conf;.conf[`rollft];`ft`ft1];beginofday[.db.ftdate]]];{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`timer];x;y);()];}[;x] each tsl[];};

istrading:{[t;s]if[not (z:fs2e s) in tkey .conf.ex;:0b];any t within/:.conf.ex[z;`session]+\: -00:01 00:01};

.timer.ftsim:{[x]if[`ftsim<>.conf.feedtype ;:()];t:`time$t0:x;{[t0;t;k]x:.db.O[k];s:x`sym;if[not istrading[t;s];:()];p:0f;n:0;$[.enum[`PENDING_CANCEL]=x`cstatus;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum[`CANCELED];0f;0f;`;`;.enum[`CANCELED];`;`;0;"";"")];[r:.db.QX[s];if[0>=r`price;r[`price]:avg r`bid`ask];if[(0>=r`cumqty)&(not fs2e[s] in `FOREX`METAL)&(not s like "SP*");:()];if[$[.conf.filldelay;t0>x`ntime;1b]&(((.enum[`BUY]=x`side)&(x`price)>=$[0<r`ask;r`ask;0w])|((.enum[`SELL]=x`side)&(x`price)<=r`bid)|(x[`typ]=.enum`MARKET));[px:$[.enum[`BUY]=x`side;(r`price)|r`ask;(r`price)&r`bid];qty:x`qty;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(.enum`NEW;k;.enum[`FILLED];qty;px;`;`;x`cstatus;`;`;0;"";"")]]]]];}[t0;t] each exec id from .db.O where not end;}; /(r`price)| (r`price)&

.roll.ft:{[x]{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`dayroll];x;y);()];}[;x] each tsl[];.[.conf.histdb;(.conf.me;`M);,;.db.M];delete from `.db.M;gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;`O);,;select from .db.O where end|tif<>gtc];delete from `.db.O where end|tif<>gtc;delete from `.db.QT;{update `u#id from x;} each `.db.O`.db.M`.db.QT;delete from `.db.P where 0>=abs[0f^lqty]+abs[0f^sqty];update flqty:0f,fsqty:0f,lqty0:0f,sqty0:0f,flqty0:0f,fsqty0:0f from `.db.P;.[.conf.histdb;(.conf.me;`P);,;update today:.z.D from 0!.db.P];update pc:(0.5*(0f^bid)+0f^(ask))^price,price:0n,bid:0n,ask:0n,cumqty:0f from `.db.QX;};

realsyms:{[x;y]$[11h<>abs type sl:.db.Ts[x;`syms];y;0=count sl;y;y inter sl]}; /[tsid;syms]
tsl:{[]x:.db.enablets inter key .db.Ts;x where {1b~.db.Ts[x;`active]} each x};
getfe:{[x]$[x in key .conf.acc;.conf.acc[x;`sym];`]};

newordex:{[sd;pe;t;s;q;p;m;x]if[0b~.db`ftactive;:`];$[0>type t;[ts:.db.Ts[t];a:ts`acc];[ts.db.Ts[t 0];a:ts[`accx;t[1]];t:t[0]]];if[1b~ts`stop;:`];if[null x`tif;x[`tif]:.enum`DAY];if[null x`typ;x[`typ]:.enum $[null p;`MARKET;`LIMIT]];fe:getfe[a];k:newid[];.db.O[k;`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt`ntime`status]:(.conf.me;t;a;fe;sfill .conf.acc[a;`acc1];m;s;sd;pe;x`tif;x`typ;q;p;dictstr `tif`typ _x;now[];.enum`PENDING_NEW);if[not null fe;pub[`ordnew;enlist `sym`oid`ft`ts`acc`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt!(fe;k),.db.O[k;`ft`ts`acc`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]]];frzqty[k;q];k}; /[side;posefct;ts|(ts;acc);sym;qty;price;ref;exdict] if[p<0;x[`tif]:.enum`GOOD_TILL_CANCEL;p:neg[p]];used by tws,error for SP
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

isfut:{[x]assetclass[x] in `Future`Combination}; /[sym]
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

newmatch:{[k;q;p]r:.db.O[k];.db.M[k1:newid[];`sym`price`qty`mtime`maker]:(r`sym;p;q;now[];k);if[not (t:r`ts) in key .db.Ts;:()];if[-99h<>type .db.Ts[t;`event];:()];.[{(x)[y;z]};(.db.Ts[t;`event;`match];t;k1);()];};

getmultiple:{[x]1f^.db.QX[x;`multiplier]};

getfee:{[x]r:.db.QX s:x[0];oc:x[2];qty:x[3];amt:x[4];ex:fs2e s;neg (0f^r $[oc=.enum`OPEN;`rfeetaxom;oc=.enum`CLOSE;`rfeetaxcm;`rfeetaxctm])|abs[qty*0f^r $[oc=.enum`OPEN;`rfeetaxoq;oc=.enum`CLOSE;`rfeetaxcq;`rfeetaxcqt]]+abs[amt*$[ex in `XHKG;2.5e-3;0f]^r $[oc=.enum`OPEN;`rfeetaxoa;oc=.enum`CLOSE;`rfeetaxca;`rfeetaxcat]]}; /[(证券代码;买卖方向;开平标志;成交数量;成交金额)]分笔交易手续费计算(负值) 

settleord:{[k;q;a]r:.db.O k;f:getfee[r[`sym`side`posefct],(q;a)];.db.O[k;`cumamt`cumfee]:(0f^r`cumamt`cumfee)+a,f;pk:r`ts`acc`sym;isb:.enum[`BUY]=r`side;sqty:q*qsign:$[isb;1;-1];iso:r[`posefct]=.enum`OPEN;isl:(isb&iso)|((not isb)&(not iso));nq1:sqty+nq0:(0f^.db.P[pk;$[isl;`lqty;`sqty]]);.db.P[pk;$[isl;`lqty;`sqty]]:nq1;$[iso;$[sqty>0;.db.P[pk;`lqty0]:(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:(0f^.db.P[pk;`sqty0])+sqty];$[r[`posefct]=.enum`CLOSETODAY;$[sqty<0;.db.P[pk;`lqty0]:0|(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:0&(0f^.db.P[pk;`sqty0])+sqty];$[(sqty<0)&(.db.P[pk;`lqty0]>.db.P[pk;`lqty]);.db.P[pk;`lqty0]:.db.P[pk;`lqty];(sqty>0)&(.db.P[pk;`sqty0]<.db.P[pk;`sqty]);.db.P[pk;`sqty0]:.db.P[pk;`sqty];()]]];}; /[OID;lastshares;lastamt] 新增成交清算

.upd.exerpt:{[x]r:.db.O k:x`oid;if[`COMB~r`special;:.upd.comback[x]];s:x`status;if[(null r`sym)|((s=.enum`PENDING_NEW)&(s<>r`status)&(r[`status]<>.enum`NULL));:()];if[(r[`end])&(x[`cumqty]<=r`cumqty);chkerrfix;:()];if[null x`cumqty;x[`cumqty]:0f];if[null x`avgpx;x[`avgpx]:0f];if[(x`cumqty)<r`cumqty;lwarn[`cumqty_decrease;(k;r`cumqty;x`cumqty;x`src;x`seq)];:()];if[(x[`cumqty]~r`qty)&(s<>.enum`FILLED);s:.enum`FILLED];.db.O[k;`status`end`rtime`feoid`ordid`rptopt]:(s;s in .enum`REJECTED`FILLED`DONE_FOR_DAY`CANCELED`REPLACED;now[];x`feoid;x`ordid;x`rptopt);if[count m:x`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m];setcs[x];$[s=.enum`NEW;();s=.enum`REJECTED;execrej[k;x];[lq:(0f^x`cumqty)-0f^r`cumqty;la:(prd 0f^x`cumqty`avgpx)-prd 0f^r`cumqty`avgpx;lp:0f^la% lq;if[0>lq;lwarn[`neg_lastshares;(k;r`cumqty;x`cumqty;lq;x`src;x`seq)];:()];if[0<lq;settleord[k;lq;la*$[.enum[`BUY]=r`side;-1;1]*getmultiple[r`sym]];.db.O[k;`ftime]:now[];newmatch[k;lq;lp]];if[0f<lq;frzqty[k;neg lq]];.db.O[k;`cumqty`lastqty`lastpx]:(x`cumqty;lq;lp);if[(0>=r`avgpx)|(0<x`avgpx);if[.enum[`CANCELED]=s;frzqty[k;neg r[`qty]-0f^x`cumqty]];.db.O[k;`avgpx]:x`avgpx]]];if[not (t:r`ts) in key .db.Ts;:()];if[99h<>type .db.Ts[t;`event];:()];.[{(x)[y;z]};(.db.Ts[t;`event;`exerpt];t;k);()];}';

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

saverdb:{[x;y]savedb[];1b};

recoverdb:{[]r:.ctrl.conn.rdb.h;delete from `.db.O;delete from `.db.M;{[x].db.O[x`oid;`end`status`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ntime]:(0b;.enum`NEW),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`srctime;} each r `ordnew;.upd.exerpt r `exerpt;};

recoverfill:{[x]r:.db.O[x];.upd.exerpt enlist `time`sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt`src`srctime`srcseq`dsttime!(0Nn;.conf.me;.enum`NEW;x;.enum`FILLED;r`qty;r`price),r[`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt],(.conf.me;0Np;0N;0Np);};

cpos:{[x;y]exec sum cumqty*?[side=.enum`BUY;1;-1] from (select from .hdb.O where cumqty>0,ts=x,sym=y),(select from .db.O where cumqty>0,ts=x,sym=y)}; /[tid;sym] calulated pos from .db.O to verify with .db.P