.module.ftbase:2023.08.21;

txload "core/rcbase";

.enum.quotefields:cols[quote] except `sym;

.init.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysinit];x;());()];} each tsl[];.db.pO:exec id from .db.O where not end;resetfqstate[];if[1b~.conf[`autoloadhdb];loadhdb[]];};
.exit.ft:{[x] {[x].[{(x)[y;z]};(.db.Ts[x;`event;`sysexit];x;());()];} each tsl[];};

.timer.ft:{[x]if[(.db.ftdate<d)|(.z.T>.conf.dayendtime)&.db.ftdate=d:.z.D;.db.ftdate0:.db.ftdate;.db.ftdate:nextworkday[.db.ftdate];if[.conf.me in $[`rollft in key .conf;.conf[`rollft];`ft`ft1];beginofday[.db.ftdate]]];{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`timer];x;y);()];}[;x] each tsl[];if[not 1b~.conf[`checkfqtime];:()];checkfqstate[];};

istrading:{[t;s]if[not (z:fs2e s) in tkey .conf.ex;:0b];any t within/:.conf.ex[z;`session]+\: -00:01 00:01};

.timer.ftsim:{[x]if[not .conf.feedtype=`ftsim;:()];t:`time$t0:x;{[t0;t;k]x:.db.O[k];s:x`sym;if[not istrading[t;s];:()];if[null .db.O[k;`rtime];.db.O[k;`rtime]:.z.P];p:0f;n:0;$[.enum[`PENDING_CANCEL]=x`cstatus;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`exchid`cstatus`cfeoid`cordid`cexchid`reason`msg`rptopt!(.enum`NEW;k;.enum[`CANCELED];x`cumqty;x`avgpx;`;`;`;.enum[`CANCELED];`;`;`;0;"";"")];[r:.db.QX[s];if[0>=r`price;r[`price]:avg r`bid`ask];if[($[1b~.conf`fillwith0qty;0n;0]>=r`cumqty)&(not fs2e[s] in `FOREX`METAL)&(not s like "SP*")&(not s like "IPS*")&(not 1b~.conf[`fillauction]);:()];p0:x`price;p1:r`price;$[(1b~.conf[`filldelay])&.db.QX[s;`extime]=x`qtime;();((.enum[`BUY]=x`side)&p0>=$[0<r`ask;r`ask;0w])|((.enum[`SELL]=x`side)&p0<=r`bid)|(x[`typ]=.enum`MARKET);[px:$[.enum[`BUY]=x`side;p0&p1|r`ask;p0|p1&r`bid];lqty:(x`qty)-0f^x`cumqty;fqty:lqty&$[1b~.conf[`fillfull];0w;r $[.enum[`BUY]=x`side;`asize;`bsize]];cq:fqty+0f^x`cumqty;ap:0f^(prd[x`cumqty`avgpx]+fqty*px)%cq;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`exchid`cstatus`cfeoid`cordid`cexchid`reason`msg`rptopt!(.enum`NEW;k;.enum $[cq=x`qty;`FILLED;`PARTIALLY_FILLED];cq;ap;newid[];newid[];`paper;x`cstatus;`;`;`;0;"";"")]];x[`tif]=.enum.IMMEDIATE_OR_CANCEL;.upd.exerpt[enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`exchid`cstatus`cfeoid`cordid`cexchid`reason`msg`rptopt!(.enum`NEW;k;.enum[`CANCELED];x`cumqty;x`avgpx;`;`;`;.enum[`CANCELED];`;`;`;0;"";"")];()]]];}[t0;t] each exec id from .db.O where not end,status in .enum`PENDING_NEW`NEW`PARTIALLY_FILLED;}; /(r`price)| (r`price)&

.roll.ft:{[x]if[1b~.conf[`waithdb];while[.z.D>d:.ctrl.conn.hdb.h ({last date};());system "sleep 10"];.ctrl[`hdbdate`hdbtime]:(d;.z.P)];{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`dayroll];x;y);()];}[;x] each tsl[];.[.conf.histdb;(.conf.me;`M);,;.db.M];delete from `.db.M;gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;`O);,;select from .db.O where end|tif<>gtc];delete from `.db.O where end|tif<>gtc;delete from `.db.QT;{update `u#id from x;} each `.db.O`.db.M`.db.QT;delete from `.db.P where 1e-10>=abs[0f^lqty]+abs[0f^sqty];update flqty:0f,fsqty:0f,lqty0:0f,sqty0:0f,flqty0:0f,fsqty0:0f from `.db.P;.[.conf.histdb;(.conf.me;`P);,;update today:.z.D from 0!.db.P];n:count[.db.QX];update pc:(0.5*(0f^bid)+0f^(ask))^price,price:0n,bid:0n,ask:0n,bsize:0n,asize:0n,cumqty:0f,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$() from `.db.QX;.db.pO:0#.db.pO;if[1b~.conf[`autoloadhdb];loadhdb[]];if[not 1b~.conf[`checkfqtime];:()];resetfqstate[];};

resetfqstate:{[x]if[not `fq in key .conf;:()];setstate[;`OK] each tkey .conf.fq;.ctrl.LastFqTime:(`symbol$())!`timestamp$();};
checkfqstate:{[x]if[not `fq in key .conf;:()];fql:tkey .conf.fq;t1:fql#exec max srctime by src from .db.QX;t0:t1^fql#.ctrl.LastFqTime;{[x;y;z]setstate[z] ?[(y[z]>x[z]+.conf.fq[z;`maxhalt])&(any y[z] within/: .conf.fq[z;`session]);`Halt;`OK]}[t0;fql!count[fql]#.z.P] each fql;.ctrl.LastFqTime:t1;};

realsyms:{[x;y]$[11h<>abs type sl:.db.Ts[x;`syms];y;0=count sl;y;y inter sl]}; /[tsid;syms]
tsl:{[]x:.db.enablets inter key .db.Ts;x where {1b~.db.Ts[x;`active]} each x};
getfe:{[x]$[x in key .conf.acc;.conf.acc[x;`sym];`]};

newordex:{[sd;pe;t;s;q;p;m;x]if[0b~.db`ftactive;:`];$[0>type t;[ts:.db.Ts[t];a:ts`acc];[ts:.db.Ts[t 0];a:ts[`accx;t[1]];t:t[0]]];if[1b~ts`stop;:`];if[null x`tif;x[`tif]:.enum`DAY];if[null x`typ;x[`typ]:.enum $[null p;`MARKET;`LIMIT]];fe:getfe[a];k:newid[];.db.O[k;`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt`ntime`qtime`f0`f1`status`cumqty`avgpx`lastqty`lastpx]:(.conf.me;t;a;fe;sfill .conf.acc[a;`acc1];m;s;sd;pe;x`tif;x`typ;q;p;dictstr `tif`typ _x;now[];.db.QX[s;`extime];.db.QX[s;`bid];.db.QX[s;`ask];.enum`PENDING_NEW;0f;0f;0f;0f);{[x;k;y]if[not null z:x[y];.db.O[k;y]:z];}[x;k] each `acc1`tsexec`upid`slot`style`expiretime;if[@[riskassert;k;0b];.db.O[k;`end`status`reason`msg]:(1b;.enum`REJECTED;1i;"Reject_by_Risk_Check");ordexerpt[k];:`];if[(not null fe)&(`ft=.conf.feedtype);pub[`ordnew;enlist `sym`oid`ft`ts`acc`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt!(fe;k),.db.O[k;`ft`ts`acc`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]]];frzqty[k;q];.db.pO,:k;k}; /[side;posefct;ts|(ts;acc);sym;qty;price;ref;exdict] if[p<0;x[`tif]:.enum`GOOD_TILL_CANCEL;p:neg[p]];used by tws,error for SP
neword:newordex[;;;;;;;.enum.nulldict];

openlong:neword[.enum`BUY;.enum`OPEN];closelong:neword[.enum`SELL;.enum`CLOSE];tcloselong:neword[.enum`SELL;.enum`CLOSETODAY];ycloselong:neword[.enum`SELL;.enum`CLOSEYESTODAY];
openshort:neword[.enum`SELL;.enum`OPEN];closeshort:neword[.enum`BUY;.enum`CLOSE];tcloseshort:neword[.enum`BUY;.enum`CLOSETODAY];ycloseshort:neword[.enum`BUY;.enum`CLOSEYESTODAY];
stdrepo:neword[.enum`SELL_SHORT;.enum`OPEN];revrepo:neword[.enum`SELL_SHORT_EXEMPT;.enum`OPEN];
mopenlong:neword[.enum`BUY;.enum`MARGIN_OPEN];mcloselong:neword[.enum`SELL;.enum`MARGIN_CLOSE]; /margin buy/sell

fakord:newordex[;;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fokord:newordex[;;;;;;;``tif!(::;.enum.FILL_OR_KILL)];

fakopenlong:newordex[.enum`BUY;.enum`OPEN;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakcloselong:newordex[.enum`SELL;.enum`CLOSE;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];faktcloselong:newordex[.enum`SELL;.enum`CLOSETODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakycloselong:newordex[.enum`SELL;.enum`CLOSEYESTODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fakopenshort:newordex[.enum`SELL;.enum`OPEN;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakcloseshort:newordex[.enum`BUY;.enum`CLOSE;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];faktcloseshort:newordex[.enum`BUY;.enum`CLOSETODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fakycloseshort:newordex[.enum`BUY;.enum`CLOSEYESTODAY;;;;;;``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];

cxlordex:{[x;y;z]r:.db.O[x];if[y<>r`ts;:()];if[(0b~.db`ftactive)|(null r`sym)|(not (null r`cid)|(r[`cn]<ifill .conf`maxcxlcnt))|(r`end)|(r[`tif]=.enum.IMMEDIATE_OR_CANCEL);:()];k:newid[];x0:r`x0;if[not null z;if[0=count x0;x0:(.enum.nulldict;::)];if[101=type x0[0;`cxlref];x0[0;`cxlref]:`symbol$()];x0[0;`cxlref],:z];.db.O[x;`cid`cstatus`ctime`t0`cn`x0`s3]:(k;.enum`PENDING_CANCEL;now[];.db.QX[r`sym;`extime];1i+0i^r`cn;x0;`$"." sv string "i"$0x0 vs .z.a);if[@[riskassertcxl;x;0b];.db.O[x;`cstatus`reason`msg]:(.enum`REJECTED;1i;"Reject_by_Risk_Check");:()];if[(not null r`fe)&`ft=.conf.feedtype;pub[`ordcxl;enlist `sym`oid`feoid`cid`ordopt!(r`fe;x;r`feoid;k;"",r`ordopt)]];}; /[oid;ts;cref]

cxlord:{[x]cxlordex[x;.db.O[x;`ts];`];};cxlordx:{[x;y]cxlordex[x;.db.O[x;`ts];y];};

qryord:{[x]r:.db.O[x];if[(0b~.db`ftactive)|(null r`sym);:()];if[not null r`fe;pub[`ordqry;enlist `sym`oid`feoid`ordopt!(r`fe;x;r`feoid;r`ordopt)]];};
qryfund:{[x]pubmx[.conf.acc[x;`sym];`QueryFund;.conf.me;string x;-8!sfill .conf.acc[x;`acc2]];}; /[acc]返回结果在.upd.FundUpdate处理(acc2为资产单元)
qryasset:{[x]pubmx[.conf.acc[x;`sym];`QueryAsset;.conf.me;string x;-8!sfill .conf.acc[x;`acc2]];}; /[acc]返回结果在.upd.AssetUpdate处理(acc2为资产单元)
qrypos:{[x]pubmx[.conf.acc[x;`sym];`QueryPos;.conf.me;string x;-8!sfill .conf.acc[x;`acc1]];}; /[acc] 返回结果在.upd.PosUpdate处理(acc1为组合|资产单元)
qryoda:{[x]pubmx[.conf.acc[x;`sym];`QueryOrdAcc;.conf.me;string x;-8!sfill .conf.acc[x;`acc1]];}; /[acc] 返回结果在.upd.OrdUpdate处理(acc1为组合|资产单元)
qrymat:{[x]pubmx[.conf.acc[x;`sym];`QueryMatAcc;.conf.me;string x;-8!sfill .conf.acc[x;`acc1]];}; /[acc] 返回结果在.upd.MatUpdate处理(acc1为组合|资产单元)
qryfundpeer:{[x]pubmx[.conf.acc[x;`sym];`QueryFundPeer;.conf.me;string x;-8!sfill .conf.acc[x;`acc2]];}; /[acc]双中心查对方节点资金,返回结果在.upd.FundPeerUpdate处理(acc2为资产单元)
allocfund:{[x;y]pubmx[.conf.acc[x;`sym];`FundAlloc;.conf.me;string x;-8!(sfill .conf.acc[x;`acc2];y)];}; /[acc;amt]双中心划入对方节点资金,返回结果在.upd.FundAllocUpdate处理(acc2为资产单元)

fe2acc:{[x] first where x=(`_ .conf.acc)[;`sym]}; /[fe]
assetclass:{[x]e:fs2e x;s:fs2s x;$[e=`XSHE;$[8=count string s;`Option;s like "[03]0*";`AShare;s like "20*";`BshareSZ;s like "1[568]*";`Fund;s like "[02]3*";`Warrant;s like "1[12]*";`BondSZ;s like "13*";`RepoSZ;`AShare];e=`XSHG;$[8=count string s;`Option;s like "60[013]*";`AShare;s like "900*";`BshareSS;s like "5[018]*";`Fund;s like "80*";`Warrant;s like "1*";`BondSS;s like "20[124]*";`RepoSS;`AShare];e=`XHKG;`HShare;`Future^.db.QX[x;`assetclass]]}; /[sym]资产类别`Ashare`Fund`Warrant`BshareSZ`BshareSS`BondSZ`BondSS`RepoSZ`RepoSS`Future

vtime:{[x;y]z:.conf.dayendtime;x:?[x>=z;x-24:00:00;x];y:?[y>=z;y-24:00:00;y];((0|(y&x 7)-x 6)-0|(y&x 9)-x 8)+((0|(y&x 3)-x 2)-0|(y&x 5)-x 4)+(0|(y&x 1)-x 0)}; /将物理时间换算成交易时间
vtimex:{[x;y]vtime[.conf.ex[x;`openNT`closeNT`openAM`closeAM`openAMrest`closeAMrest`openPM`closePM`openPMrest`closePMrest];`time$y]}; /物理时间换算为逻辑交易时间

isfut:{[x]assetclass[x] in `Future`Combination}; /[sym]
isopt:{[x]`Option=assetclass[x]}; /[sym]
isdrv:{[x]isfut[x]|isopt[x]};     /[sym]

ishk:{[x]y:fs2e x; y in `XHKG`XHKE};

iscnfut:{[x]isfut[x]&.db.QX[x;`margintype]<>`US}; /[sym]
iscnopt:{[x]isopt[x]&.db.QX[x;`margintype]<>`US}; /[sym]
iscndrv:{[x]iscnfut[x]|iscnopt[x]};     /[sym]

iswarrant:{[x]{(x within 580001 580999)|(x within 30001 39999)} "I"$string fs2s x}; /x:sym
isfund:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "5*"))|((e=`XSHE)&(f like "1[5-8]*"))}; /[sym]基金
isbond:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "[0-1][1-3]*"))|((e=`XSHE)&(f like "1[1-2]*"))}; /[sym]债券
isrepo:{[x]e:fs2e x;f:fs2s x;((e=`XSHG)&(f like "204*"))|((e=`XSHE)&(f like "131*"))}; /[sym]回购

ist0:{[x](x in .conf.t0list)|((isfut[x]|isopt[x]|ishk[x])&not .db.QX[x;`product] in .conf.t1list)}; /is T+0?,x:sym

getsess:{[ex;dend;nend]0 -00:00:00.001+/:$[ex=`CCFX;(09:30 11:30;13:00,dend);null nend;(09:00 10:15;10:30 11:30;13:30 15:00);nend>21:00;(09:00 10:15;10:30 11:30;13:30 15:00;21:00,nend);(00:00,nend;09:00 10:15;10:30 11:30;13:30 15:00;21:00 24:00)]}; /[ex;dend;nend]取交易时段列表
trdsess:{[x]$[isfut[x];.db.PD[.db.QX[x;`product];`sess];.conf.ex[fs2e x;`session]]}; /[sym]取合约交易时段列表 
trddate:{[x]w:weekday d:`date$x;t:`time$x;d+?[(t>08:30)&(t<17:30);0;?[t>=17:30;?[w<4;1;3];?[w<5;0;2]]]}; /[time]取交易日期,支持向量入参
trdtime:{[x;y]t0:.conf.dayendtime;s:trdsess[x];s0:s where s[;0]<t0;s1:s where s[;0]>t0;tn:$[count[s1];sum 00:00:00.001+s1[;1]-s1[;0];00:00:00.000];?[y>t0;$[count s1;sum each 0|(y&\:00:00:00.001+s1[;1])-\:s1[;0];y];tn+sum each 0|(y&\:00:00:00.001+s0[;1])-\:s0[;0]]}; /[sym;timelist]将合约物理时间转换为连续交易的累计时间
trddatetime:{[x;y]trddate[y]+trdtime[x;y]}; /[sym;timestamp list]将物理时间戳转为逻辑时间戳
sesstotal:{[x]s:trdsess[x];sum (`time$1)+s[;1]-s[;0]}; /[sym] 日交易时段总长

openordn:{[x]exec count i from .db.O where ts=x,not end};
openordsn:{[x;y]exec count i from .db.O where ts=x,sym=y,not end};

availpos:{[s;x]y:x[2];z:s=.enum`SELL;(0f^.db.P[x;$[z;`lqty;`sqty]])-(0f^.db.P[x;$[z;`flqty;`fsqty]])+$[ist0[y];0f;0f^.db.P[x;$[z;`lqty0;`sqty0]]]} /[side;(tid;acc;sym)]仓位可用/平数
availlongpos:availpos[.enum`SELL];availshortpos:availpos[.enum`BUY];
availt0pos:{[s;x]z:s=.enum`SELL;(0f^.db.P[x;$[z;`lqty0;`sqty0]])-0f^.db.P[x;$[z;`flqty0;`fsqty0]]}; /[side;(tid;acc;sym)]本日仓位可用/平数

netposx:{[t;a;s](0f^.db.P[(t;a;s);`lqty])+0f^.db.P[(t;a;s);`sqty]}; /[tid;acc;sym]
netpos:{[t;s]netposx[t;.db.Ts[t;`acc];s]}; /[tid;sym] 
sumpos:{[t;s]exec sum (0f^lqty)+0f^sqty from .db.P where ts=x,sym=y}; /[tid;acc;sym]

pxunit:{[x]1e-4^.conf.ac[assetclass x;`pxunit]^.db.QX[x;`pxunit]}; /[sym]
qtyunit:{[x]if[x like "688*.XSHG";:200f];1e2^.db.QX[x;`qtylot]^.conf.ac[assetclass x;`qtylot]}; /[sym]  
qtyceil:{[x]1e6^.conf.ac[assetclass x;`qtymax]^.db.QX[x;`qtymax]}; /[sym]

getqtymin:{[x]qtyunit[x[0]]}; /[(代码;方向)]

getqtymax:{[x]qtyceil[x[0]]}; /[(代码;方向)]
roundpx:{[x;y;z]if[(e:fs2e x) in `XHKG`XHKE;:roundpxhk[y;z]];w:pxunit[x];w*$[y=.enum[`BUY];{ceiling x-1e-2};y=.enum[`SELL];{floor x+1e-2};{floor x+0.5}]z%w}; //对委托价格按价格单位进行向对手方取整[sym;BS;px]

get_last_price:{[x]$[0<p:.db.QX[x;`price];p;.db.QX[x;`pc]]}; /x:fsym

getordpx1:{[x;y;z]h:.db.QX[x];if[0=count h`price;:0n];if[null h`price;h[`price]:avg h`bid`ask];nu:neg u:pxunit[x];p0:{$[x<0w;x;0f]} h`inf;p1:{$[x>0;x;0w]} h`sup;o5:p1&u+o4:p1&u+o3:p1&u+o2:p1&u+o1:max h`ask`bid;mp:avg (h`ask`bid) except 0f;b5:p0|nu+b4:p0|nu+b3:p0|nu+b2:p0|nu+b1:min (p0|h`bid`ask) except 0f;p:$[y=.enum[`BUY];$[`MOSTAGGRESSIVE=z;o5;`MOREAGGRESSIVE=z;o4;`AGGRESSIVE=z;o3;`LESSAGGRESSIVE=z;o2;`LEASTAGGRESSIVE=z;o1;`NEUTRAL=z;mp;`LEASTPASSIVE=z;b1;`LESSPASSIVE=z;b2;`PASSIVE=z;b3;`MOREPASSIVE=z;b4;`MOSTPASSIVE=z;b5;h`price];$[`MOSTAGGRESSIVE=z;b5;`MOREAGGRESSIVE=z;b4;`AGGRESSIVE=z;b3;`LESSAGGRESSIVE=z;b2;`LEASTAGGRESSIVE=z;b1;`NEUTRAL=z;mp;`LEASTPASSIVE=z;o1;`LESSPASSIVE=z;o2;`PASSIVE=z;o3;`MOREPASSIVE=z;o4;`MOSTPASSIVE=z;o5;h`price]];p:$[(p<pxunit[x])|(p=0w);h`price;p];roundpx[x;y;p]}; //[fsym;side;style] 只有1档行情时的处理 

getordpx:{[x;y;z]h:.db.QX[x];if[0=count h`bidQ;:getordpx1[x;y;z]];if[0=count h`price;:0n];if[null h`price;h[`price]:avg h`bid`ask];o5:max h[`askQ;4],o4:max h[`askQ;3],o3:max h[`askQ;2],o2:max h[`askQ;1],o1:max h`ask`bid;mp:avg (h`ask`bid) except 0f;b5:min (h[`bidQ;enlist 4] except 0f),b4:min (h[`bidQ;enlist 3] except 0f),b3:min (h[`bidQ;enlist 2] except 0f),b2:min (h[`bidQ;enlist 1] except 0f),b1:min (h`bid`ask) except 0f;p:$[y=.enum[`BUY];$[`MOSTAGGRESSIVE=z;o5;`MOREAGGRESSIVE=z;o4;`AGGRESSIVE=z;o3;`LESSAGGRESSIVE=z;o2;`LEASTAGGRESSIVE=z;o1;`NEUTRAL=z;mp;`LEASTPASSIVE=z;b1;`LESSPASSIVE=z;b2;`PASSIVE=z;b3;`MOREPASSIVE=z;b4;`MOSTPASSIVE=z;b5;h`price];$[`MOSTAGGRESSIVE=z;b5;`MOREAGGRESSIVE=z;b4;`AGGRESSIVE=z;b3;`LESSAGGRESSIVE=z;b2;`LEASTAGGRESSIVE=z;b1;`NEUTRAL=z;mp;`LEASTPASSIVE=z;o1;`LESSPASSIVE=z;o2;`PASSIVE=z;o3;`MOREPASSIVE=z;o4;`MOSTPASSIVE=z;o5;h`price]];p:$[(p<pxunit[x])|(p=0w);h`price;p];roundpx[x;y;p]}; //[fsym;side;style] 取合适的委托价格:`MOSTAGGRESSIVE:取当前卖(买)五价为买(卖)价,即力求即刻成交;`MOREAGGRESSIVE:卖(买)四价;`AGGRESSIVE:卖(买)三价;`LESSAGGRESSIVE:卖(买)二价;`LEASTAGGRESSIVE:卖(买)一价,即对方最优;`NEUTRAL:取当前买卖一价之均价;`LEASTPASSIVE:取当前买(卖)一价为买(卖)价,即在本方最优价格上排队;`LESSPASSIVE:买(卖)二价;`PASSIVE:买(卖)三价;`MOREPASSIVE:买(卖)四价;`MOSTPASSIVE:买(卖)五价.对接近涨跌停的特殊情形进行兼容性处理(20110428)
getbuypx:getordpx[;.enum[`BUY];];getsellpx:getordpx[;.enum[`SELL];];

ishidden:{[x;y;z]h:.db.QX[x];$[y~.enum`BUY;z<h`bid;z>h`ask]}; /[sym;side;px] 判断价格是否低于买一价格(买入方向)或高于卖一价格(卖出方向)
pxcmp:{$[x=.enum`BUY;1;-1]*signum y-z}; /[side;p0;p1]p0劣于/等于/优于p1返回1/0/-1

uproundqty_kcb:{[x;y]$[y<=0f;0f;y<=200f;200f;`float$ceiling y-1e-2]}; //[(代码;方向);数量]对科创板委托数量按委托单位进行向上取整,200股起,1股递增
uproundqty:{[x;y]if[x[0] like "688*.XSHG";:uproundqty_kcb[x;y]];qm:getqtymin[x];qm*ceiling (y-1e-2)%qm}; //[(代码;方向);数量]对委托数量按委托单位进行向上取整

roundqty_kcb:{[x;y]$[y<200f;0f;`float$floor y+1e-2]}; //[(代码;方向);数量]对科创板委托数量按委托单位进行向下取整,200股起,1股递增
roundqty:{[x;y]if[x[0] like "688*.XSHG";:roundqty_kcb[x;y]];qm:getqtymin[x];qm*floor (y+1e-2)%qm}; //[(代码;方向);数量]对委托数量按委托单位进行向下取整

roundv1:{[x;y]n:count y;i:0;do[n-1;q:roundqty[x] y[i];y[i+1]+:y[i]-q;y[i]:q;i+:1];y};        //[(代码;方向);数量数组]对数量数组进行向下取整加尾处理
roundv:{[x;y]qm:getqtymin[x];"f"$qm*deltas "i"$(sums y)%qm};        //[(代码;方向);数量数组]对数量数组进行四舍五入取整处理
nonneg:{[x]n:count x;i:n-1;do[n-1;if[0>v:x[i];x[i-1]+:v;x[i]:0f];i-:1];x}; /[数量数组]对数量数组从尾部进行非负化

ordexptime:{[x;y]z:.conf.EX fs2e y;`timestamp$(`date$now[])+{[x;y]$[(x>y`closeAM)&(x<y`openPM);x+(y`openPM)-y`closeAM;x]}[;z]((z`openAM)|`time$now[])+`time$x}; /[offset;fsym] 计算委托过期时刻

roundpxhk:{[x;y]z:.conf.hkticks;z $[x=.enum`BUY;binr;bin][z;y+$[x=.enum`BUY;-1e-10;1e-10]]}; /[BS;px]

isvalidnum:{[x]not (`float$x) in 0n -0w 0w};

limit_orderx:{[h;sd;accno;x;y;q;p;m]if[not isvalidnum[p]&isvalidnum[q];:`symbol$()];p:roundpx[y;sd] `float$p;acc:$[null accno;.db.Ts[x;`acc];@[;accno] .db.Ts[x;`accx]];oq:q-cq:q&abs availpos[sd;x,acc,y];ctq:cq&abs availt0pos[sd;x,acc,y];k0:k1:k2:`;pecy:$[(1b~.conf.usecloseyestoday)&(fs2e[y] in .conf.closetodayexlist);"Y";.enum`CLOSE];t:$[null accno;x;(x;accno)];if[0<cq;$[(0<ctq)&(1b~.conf.useclosetoday)&(fs2e[y] in .conf.closetodayexlist);[k0:newordex[sd;.enum`CLOSETODAY;t;y;ctq;p;m;h];if[0<clq:cq-ctq;k1:newordex[sd;pecy;t;y;clq;p;m;h]]];k1:newordex[sd;pecy;t;y;cq;p;m;h]]];if[0<oq;k2:newordex[sd;.enum`OPEN;t;y;oq;p;m;h]];(k0,k1,k2) except `}; /[sided;accno;ts;sym;qty;price;tag]

limit_order:limit_orderx[.enum`nulldict];
xlimit_buyx:limit_orderx[;.enum`BUY];xlimit_sellx:limit_orderx[;.enum`SELL];xlimit_buy:xlimit_buyx[;0N];xlimit_sell:xlimit_sellx[;0N];
limit_buyx:limit_order[.enum`BUY];limit_sellx:limit_order[.enum`SELL];limit_buy:limit_buyx[0N];limit_sell:limit_sellx[0N];limit_buy0:limit_buyx[0];limit_sell0:limit_sellx[0];limit_buy1:limit_buyx[1];limit_sell1:limit_sellx[1];etf_create:limit_order[.enum`ETFCreation;0N];etf_redeem:limit_order[.enum`ETFRedemption;0N];
fak_buy:xlimit_buy[``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];fak_sell:xlimit_sell[``tif!(::;.enum.IMMEDIATE_OR_CANCEL)];
fok_buy:xlimit_buy[``tif!(::;.enum.FILL_OR_KILL)];fok_sell:xlimit_sell[``tif!(::;.enum.FILL_OR_KILL)];

//.upd.quote:{[x]y:update recvtime:.z.P from select by sym from x;ljt:.conf[`quoteljtime];.db.QX:$[17h<>type ljt;uj;.z.T within ljt;lj;uj][.db.QX;y];{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from y] each tsl[];};

//.upd.quote:{[x]y:update recvtime:.z.P from select by sym from x;ljt:.conf[`quoteljtime];.db.QX:.db.QX lj y;{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from y] each tsl[];};

.upd.quote:{[x]$[0=count .db.QX;.db.QX:.db.QX uj x;{[x;y].db.QX[y`sym;x]:y x}[.enum.quotefields] each update dsttime:.z.P from x];{[x;y]z:realsyms[x;y];if[count z;.[{(x)[y;z]};(.db.Ts[x;`event;`quote];x;z);()]];}[;exec sym from x] each tsl[];};

.upd.quoteref:{[x].db.QX[x`sym;`pc`open`sup`inf]:x`pc`open`sup`inf;}'; //.upd.quoteref:{[x].db.QX:.db.QX uj select by sym from x;}; /VERY SLOW

.upd.tsparam:{[x]y:x`typ;z:x`ts;k:x`item;if[not z in key .db.Ts;:()];if[not k in key .db.Ts[z];:()];$[y="S";.db.Ts[z;k]:-9!x`vbin;y="G";if[x[`sym]=.conf.me;pub[`tsparam;enlist `sym`typ`user`ts`item`vbin`msg!(x`src;"A";x`user;z;k;-8!.db.Ts[z;k];"")]];()];}';

.upd.cxlrej:{[x]if[null k:x`oid;:()];r:.db.O[k];if[null r`sym;:()];if[not (.enum`BROKER_ERROR_CXL)~rs:x`reason;.db.O[k;`lastqty`lastpx`cstatus`reason]:(0f;0f;.enum`REJECTED;rs)];if[count m:x`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m];.[{(x)[y;z]};(.db.Ts[x;`event;`cxlrej];r`ts;k);()]}';

.upd.ordnew:.ft.ordnew:{[x]if[not x[`ft] in .conf.ha.backupft;:()];.ha.ordnew[x];frzqty[k;.db.O[k:x`oid;`qty]];}'; /msg from backupfe
.upd.ordcxl:.ft.ordcxl:.ha.ordcxl';

.upd.Alarm:{[x]{[x;y].[{(x)[y;z]};(.db.Ts[x;`event;`alarm];x;y);()];}[;x] each tsl[];};

realbarsyms:{[x;y]$[11h<>abs type sl:.db.Ts[x;`barsyms];`symbol$();0=count sl;`symbol$();y inter sl]}; /[tsid;syms]
.upd.bar:{[x]if[1b~.conf.keepbar;bar,:update dsttime:.z.P from x];sl:exec distinct sym from x;{[tid;sl;t]z:realbarsyms[tid;sl];if[count z;{[tid;t].[{(x)[y;z]};(.db.Ts[tid;`event;`bar];tid;t);()]}[tid] each select from t where sym in z];}[;sl;x] each tsl[];};

chkerrfix:{[x]r:.db.O k:x`oid;if[(0=r`avgpx)&(r[`cumqty]=x`cumqty)&(0<p:x`avgpx);.db.O[k;`avgpx`cumamt]:p,p*getmultiple[r`sym]*r`cumqty];if[0<n:count m:x`msg;if[not m~neg[n]#r`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m]];}; //(x[`typ]=.enum`CORRECT)&恒生部成部撤状态更正
setcs:{[x]r:.db.O k:x`oid;s:x`status;if[.enum[`CANCELED]=s;.db.O[k;`cstatus]:s;if[null r`ctime;.db.O[k;`ctime]:now[]]];if[r[`cstatus]<>.enum`PENDING_CANCEL;:()];.db.O[k;`cfeoid`cordid`cexchid]:x`cfeoid`cordid`cexchid;if[s in .enum`REJECTED`FILLED`DONE_FOR_DAY;.db.O[k;`cstatus]:.enum`REJECTED];if[(x[`typ]=.enum`CORRECT)&(x[`cstatus]=.enum`NULL);.db.O[k;`cstatus]:.enum`NULL];};

frzqty:{[k;q]r:.db.O[k];pe:r`posefct;sd:r`side;tid:r`ts;acc:r`acc;fs:r`sym;sq:$[sd=.enum`SELL;1f;-1f]*q;if[pe in .enum`CLOSE`CLOSETODAY`CLOSEYESTODAY`MARGIN_CLOSE;ff:$[sd=.enum`SELL;`flqty;`fsqty];q1:.db.P[(tid;acc;fs);ff]:sq+q0:0f^.db.P[(tid;acc;fs);ff];ldebug[`frzqty;(k;q;fs;ff;sq;q0;q1)];if[pe=.enum`CLOSETODAY;ff:$[sd=.enum`SELL;`flqty0;`fsqty0];.db.P[(tid;acc;fs);ff]:sq+0f^.db.P[(tid;acc;fs);ff]]];};

execrej:{[k;x].db.O[k;`reason`msg]:x`reason`msg;frzqty[k;neg .db.O[k;`qty]];@[riskstatrej;k;()];};

newmatch:{[k;q;p]r:.db.O[k];.db.M[k1:newid[];`sym`price`qty`mtime`maker]:(r`sym;p;q;now[];k);if[not (t:r[`ts]^r`tsexec) in key .db.Ts;:()];if[99h<>type .db.Ts[t;`event];:()];.[{(x)[y;z]};(.db.Ts[t;`event;`match];t;k1);()];};

getmultiple:{[x]1f|.db.QX[x;`multiplier]}; /取合约乘数,特殊情况为港股权证乘数一般为0.1,但不适用于成交金额计算,故此处用1f|而不是1f^

getmargincoef:{[x;y]1f^.db.QX[x;$[y=.enum`BUY;`rmarginl;`rmargins]]}; /[fsym,side]保证金比例 /$[isfut[x];0.2;1f]

calcsettledate:{[x;y;z](7*x)+d+mod[;7] 7+y-d-`week$d:`date$z}; /[第几个(0-3);星期几(0-6);合约月份]

getsettledate:{[x].db.QX[x;`settledate]}; /[fsym]取结算日期

getsettlepx:{[x].db.QX[x;`settlepx]}; /[fsym]取结算价

getunderlying:{[x].db.QX[x;`underlying]}; /[fsym]取期权标的

getputcall:{[x]$[x like "IO*";`$(string x) 7;`]^.db.QX[x;`putcall]}; /[fsym]取期权putcall

getstrike:{[x]$[x like "IO*";"F"$(string x) 9+til 4;0n]^.db.QX[x;`strikepx]}; /[fsym]取期权strike

ccfxoptmargin:{[r0;r1;mp;pc;sp;px;up](px*mp)+(r0*$[`C=pc;up;sp]*mp*r1)|(up*mp*r1)-0|mp*$[`C=pc;1;-1]*sp-up}; /[最低保障系数;保证金比例;合约乘数;putcall;strike;期权结算价;标的结算价]

getccfxoptmargin:{[x]y:x[0];px:abs x[4]%x[3]*getmultiple[y];abs x[3]*ccfxoptmargin[0.667;0.15;getmultiple[y];getputcall[y];getstrike[y];px;get_last_price[getunderlying[y]]]};

getccfxeodoptmargin:{[x]ccfxoptmargin[0.667;0.15;getmultiple[x];getputcall[x];getstrike[x];getsettlepx[x];getsettlepx[getunderlying[x]]]}; /[fsym]计算单张期权合约日终结算保证金

geteodoptmargin:{[x]getccfxeodoptmargin[x]};

getoptmargin:{[x]getccfxoptmargin[x]};

getfutmargin:{[s;f]getmargincoef[f;s]*getmultiple[f]*getsettlepx[f]}; /[(s)ide;(f)sym]计算期货一手保证金

getfutmarginl:getfutmargin[.enum`BUY];getfutmargins:getfutmargin[.enum`SELL];

getmargin:{[x]y:x[0];0f^$[x[2]<>.enum`OPEN;0f;`US=.db.QX[y;`margintype];x[3]*.db.QX[y;`rmarginmq];($[(x[1]=.enum`BUY)|isfut[x[0]];abs;neg] x[4]*getmargincoef[x[0];x[1]])+$[(x[1]=.enum`SELL)&isopt[x[0]];getoptmargin[x];0f]]}; /[(证券代码;买卖方向;开平标志;成交数量;成交金额[买-卖+])]交易保证金计算(期货交易和买入现货/期权为正值，融券卖出和期权卖出为负值)+行权保证金(恒正)

getfee:{[x]r:.db.QX s:x[0];oc:x[2];qty:x[3];amt:x[4];ex:fs2e s;neg (0f^r $[oc=.enum`OPEN;`rfeetaxom;oc=.enum`CLOSE;`rfeetaxcm;`rfeetaxctm])|abs[qty*0f^r $[oc=.enum`OPEN;`rfeetaxoq;oc=.enum`CLOSE;`rfeetaxcq;`rfeetaxcqt]]+abs[amt*$[ex in `XHKG;3.1e-3;0f]^r $[oc=.enum`OPEN;`rfeetaxoa;oc=.enum`CLOSE;`rfeetaxca;`rfeetaxcat]]}; /[(证券代码;买卖方向;开平标志;成交数量;成交金额)]分笔交易手续费计算(负值) 

getfrozen:{[x]$[x[2]<>.enum`OPEN;0f;getfee[x]]-getmargin[x]}; /[证券代码;买卖方向;开平标志;成交数量;成交金额]交易冻结资金计算(负值)

frozenfund:{[x;y]exec sum {[x;z;w;u;v] `float$getfrozen each flip (x;z;w;u;v*getmultiple each x)}[sym;side;posefct;qty-0f^cumqty;price*0f^qty-cumqty] from .db.O where acc=y,ts=x,posefct=.enum[`OPEN],not end}; /[ts;acc]逻辑账户冻结保证金计算

frozensymfund:{[x]exec sum {[x;z;w;u;v] `float$getfrozen each flip (x;z;w;u;v*getmultiple each x)}[sym;side;posefct;qty-0f^cumqty;price*0f^qty-cumqty] from .db.O where ts=(x 0),acc=(x 1),sym=(x 2),posefct=.enum[`OPEN],not end}; /[(ts;acc;sym)]逻辑账户某品种冻结保证金计算

availfund:{[x]0|((sum 0f^ffill each .db.Ts[x;`fundavl`pnlavl])*$[null .db.Ts[x;`stop];1;0])+frozenfund[x;.db.Ts[x;`acc]]}; /[ts]逻辑账户可用保证金计算

settleord:{[k;q;a]r:.db.O k;f:getfee[r[`sym`side`posefct],(q;a)];.db.O[k;`cumamt`cumfee]:(0f^r`cumamt`cumfee)+a,f;pk:r`ts`acc`sym;isb:.enum[`BUY]=r`side;sqty:q*qsign:$[isb;1;-1];iso:r[`posefct] in .enum`OPEN`MARGIN_OPEN;isl:(isb&iso)|((not isb)&(not iso));nq1:sqty+nq0:(0f^.db.P[pk;$[isl;`lqty;`sqty]]);.db.P[pk;$[isl;`lqty;`sqty]]:nq1;$[iso;$[sqty>0;.db.P[pk;`lqty0]:(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:(0f^.db.P[pk;`sqty0])+sqty];$[r[`posefct]=.enum`CLOSETODAY;$[sqty<0;.db.P[pk;`lqty0]:0|(0f^.db.P[pk;`lqty0])+sqty;.db.P[pk;`sqty0]:0&(0f^.db.P[pk;`sqty0])+sqty];$[(sqty<0)&(.db.P[pk;`lqty0]>.db.P[pk;`lqty]);.db.P[pk;`lqty0]:.db.P[pk;`lqty];(sqty>0)&(.db.P[pk;`sqty0]<.db.P[pk;`sqty]);.db.P[pk;`sqty0]:.db.P[pk;`sqty];()]]];}; /[OID;lastshares;lastamt] 新增成交清算

ordexerpt:{[k]r:.db.O[k];if[not (t:r[`ts]^r`tsexec) in key .db.Ts;:()];if[99h<>type .db.Ts[t;`event];:()];.[{(x)[y;z]};(.db.Ts[t;`event;`exerpt];t;k);()];}; /[oid]触发策略的委托回调

.upd.exerpt:.ft.exerpt:{[x].temp.x:x;r:.db.O k:x`oid;if[`COMB~r`special;:.upd.comback[x]];s:x`status;sy:r`sym;if[(null sy)|((s=.enum`PENDING_NEW)&(s<>r`status)&(r[`status]<>.enum`NULL));:()];if[(r[`end])&(x[`cumqty]<=r`cumqty);chkerrfix[x];:()];if[null x`cumqty;x[`cumqty]:0f];if[null x`avgpx;x[`avgpx]:0f];if[(x`cumqty)<r`cumqty;lwarn[`cumqty_decrease;(k;r`cumqty;x`cumqty;x`src;x`seq)];:()];if[(x[`cumqty]~r`qty)&(s<>.enum`FILLED);s:.enum`FILLED];.db.O[k;`status`end`rtime`feoid`ordid`exchid`rptopt]:(s;s in .enum`REJECTED`FILLED`DONE_FOR_DAY`CANCELED`REPLACED`EXPIRED;now[];x`feoid;x`ordid;x`exchid;x`rptopt);if[.db.O[k;`end];.db.pO:.db.pO except k];if[count m:x`msg;.db.O[k;`msg],:$[count r`msg;"=>";""],m];setcs[x];$[s=.enum`NEW;();s=.enum`REJECTED;execrej[k;x];[lq:(0f^x`cumqty)-0f^r`cumqty;la:(prd 0f^x`cumqty`avgpx)-prd 0f^r`cumqty`avgpx;lp:0f^la% lq;if[0>lq;lwarn[`neg_lastshares;(k;r`cumqty;x`cumqty;lq;x`src;x`seq)];:()];if[0<lq;settleord[k;lq;la*$[.enum[`BUY]=r`side;-1;1]*getmultiple[sy]];.db.O[k;`ftime]:now[];newmatch[k;lq;lp]];if[0f<lq;frzqty[k;neg lq]];.db.O[k;`cumqty`lastqty`lastpx]:(x`cumqty;lq;lp);if[(0>=r`avgpx)|(0<x`avgpx);if[s in .enum`CANCELED`EXPIRED;frzqty[k;neg r[`qty]-0f^x`cumqty]];.db.O[k;`avgpx]:x`avgpx]]];ordexerpt[k];}'; /`t1`f2`f3 ,.db.QX[sy;`extime`bid`ask]

.upd.exenoe:{[x]r:.db.O k:x`oid;if[not null r`sym;:()];.db.O[k;`special`ntime`status`tif`typ`ft`ts`acc`fe`acc1`ref`sym`side`posefct`qty`price]:(`NOE;now[];.enum`PENDING_NEW;.enum`DAY;.enum`LIMIT),x`ft`ts`acc`src`acc1`ref`osym`side`posefct`cumqty`avgpx;frzqty[k;x`cumqty];x[`feoid`cstatus`cfeoid`cordid`reason]:(`;.enum`NULL;`;`;0N);.upd.exerpt enlist x;}';

.upd.RDUpdate:{[x].db.QX:.db.QX uj get `$x`msg;update `u#sym from `.db.QX;};

.upd.AssetUpdate:{[x]fe:x`ref;acc:fe2acc[fe]^`$x`msg;assetinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`Asset]:assetinfo;};

.upd.FundUpdate:{[x]fe:x`ref;acc:fe2acc[fe]^`$x`msg;fundinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`Fund]:fundinfo;};

.upd.PosUpdate:{[x]fe:x`ref;acc:`$x`msg;posinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`Pos]:posinfo;};

.upd.OrdUpdate:{[x]fe:x`ref;acc:`$x`msg;ordinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`Ord]:ordinfo;};

.upd.MatUpdate:{[x]fe:x`ref;acc:`$x`msg;matinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`Mat]:matinfo;};

.upd.FundPeerUpdate:{[x]fe:x`ref;acc:fe2acc[fe]^`$x`msg;fundinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`FundPeer]:fundinfo;};

.upd.FundAllocUpdate:{[x]fe:x`ref;acc:fe2acc[fe]^`$x`msg;fundinfo:-9!x`vbin;if[99h<>type .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[not ` in key .temp[`AccSnap];.temp[`AccSnap]:.enum`nulldict];if[99h<>type .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];if[not ` in key .temp.AccSnap[acc];.temp.AccSnap[acc]:.enum`nulldict];.temp.AccSnap[acc;`FundAlloc]:fundinfo;};

noeexec:{[sno;fta;s;sd;pe;q;p;m]if[not isvalidnum[p]&isvalidnum[q];:`symbol$()];k:newid[];ft:fta[0];ts:fta[1];$[2<count fta;acc:.db.Ts[ts;`accx][fta[2]];acc:.db.Ts[ts;`acc]];$[(`ft=.conf.feedtype)&(not 1b~.conf[`simnoe]);pub[`exenoe];.upd.exenoe]enlist `sym`typ`oid`ft`ts`acc`acc1`ref`osym`side`posefct`status`cumqty`avgpx`ordid`exchid`msg`rptopt!(ft;.enum`NEW;k;ft;ts;acc;`;`$m;s;sd;pe;.enum`FILLED;q;p;sno;sno;"";"");k}; /提交一笔NOE上报记录 noeexec[`20200102001;`ftdc4`8508_femm_510390;`510390.XSHG;.enum`SELL;.enum`CLOSE;140600f;4.245;"865577+865585"]

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

simfill:{[k]r:.db.O[k];.upd.exerpt enlist `typ`oid`status`cumqty`avgpx`feoid`ordid`exchid`cstatus`cfeoid`cordid`cexchid`reason`msg`rptopt!(.enum`NEW;k;.enum`FILLED;r`qty;r`price;newid[];newid[];`paper;.enum.NULL;`;`;`;0;"";"");};

cpos:{[x;y]exec sum cumqty*?[side=.enum`BUY;1;-1] from (select from .hdb.O where cumqty>0,ts=x,sym=y),(select from .db.O where cumqty>0,ts=x,sym=y)}; /[tid;sym] calulated pos from .db.O to verify with .db.P

hisbars:{[typ;x;D;f]($[typ in `D`W`N;daybars;minbars])[typ;x;D;f]}; /[sym;d0.d1;bartype(`M|`D|`W|`N);barfreq]gen hist bars from tick quote

daybars:{[typ;x;D;f]sess:trdsess[x];select t:00:00,first o,max h,min l,last c,sum v,sum a,last p by xbar[f] (?[`N=typ;`date$`month$;?[`W=typ;`week$;::]]) d from (.ctrl.conn.hdb.h[({[x;D;sess]0!select o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:last cumqty*vwap,p:last openint by d:date from quote where date within D,sym=x,(0<low)&(low<=price)&(price<=high),any (`time$time) within/: sess};x;D;sess)],$[not .db.sysdate within D;();`d xcols update d:.db.sysdate from .ctrl.conn.rdb.h[({[x;sess]select o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:last cumqty*vwap,p:last openint from quote where sym=x,(0<low)&(low<=price)&(price<=high),any (`time$time) within/:sess};x;sess)]]) where not null o};

minbars:{[typ;x;D;f]sess:trdsess[x];delete seq from update v:deltas v,a:deltas a by d from `d`seq xasc .ctrl.conn.hdb.h[({[x;D;f;sess]0!select seq:first i,o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:last cumqty*vwap,p:last openint by d:date,t:xbar[f] `minute$time from quote where date within D,sym=x,(0<low)&(low<=price)&(price<=high),any (`time$time) within/:sess};x;D;f;sess)],$[not .db.sysdate within D;();`d xcols update d:.db.sysdate from .ctrl.conn.rdb.h[({[x;f;sess]0!select seq:first i,o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:last cumqty*vwap,p:last openint by t:xbar[f] `minute$time from quote where sym=x,(0<low)&(low<=price)&(price<=high),any (`time$time) within/:sess};x;f;sess)]]};

histrds:{[x;D](select d:trddate ftime,t:`time$ftime,avgpx,side from .hdb.O where sym=x,cumqty>0,(trddate ftime) within D),$[not .db.sysdate within D;();select d:trddate ftime,t:`time$ftime,avgpx,side from .db.O where sym=x,cumqty>0]};


loadetf:{[x;y]{.[`.db;enlist x;:;get ` sv .conf[`tempdb],x];} each `ETF`ETFPF`ETFER;sl:exec sym from .db.ETFPF where not sym in exec sym from .db.QX;if[count sl;{[x].db.QX[x;`ticker]:`} each sl];update `.db.QX$sym from `.db.ETFPF;1b};

//getiopvex:{[x;y]$[.db.ETF[y;`trday]<>.z.D;0n;(.db.ETF[y;`cueu]+exec sum (?[qty<=0;0f;qty]*?[sym like "1*";10;1]*{[x;y;z;u;v;b;a]p:$[x=1;a;x>1;v[;x-1];x=-1;b;x<-1;u[;abs[x]-1];y];?[p>0;p;?[y>0;y;z]]}[x;sym.price;sym.pc;sym.bidQ;sym.askQ;sym.bid;sym.ask]*1f^sym.multiplier)+?[qty>=0;0f;camt] from .db.ETFPF where etfsym=y,sym<>`159900.XSHE)%.db.ETF[y;`cu]]}; /上海基金份额参考净值＝[∑(替代标志为0/1/3成分证券最新替代金额)+∑(替代标志为2/4/5/6的成分证券对应资金)+预估现金]/最小申购赎回单位对应的ETF份数(0-沪市不可被替代;1-沪市可以被替代;2-沪市必须被替代;3-深市退补现金替代;4-深市必须现金替代;5-非沪深市场成分证券退补现金替代;6-非沪深市场成份证券必须现金替代),对可转债ETF,申赎清单中债券单位是手,需要再乘10,另外还涉及行情可能为净价而非全价的误差,行情中的settlepx更准确,要注意特别处理.为加强异常处理,去掉 .db.QX[y;`settlepx]^
//getiopv:getiopvex[0];

getiopvex:{[x;y]$[.db.ETF[y;`trday]<>.z.D;0n;(.db.ETF[y;`cueu]+exec sum ?[cctype in "2468";camt;?[cctype in "01357";qty*?[sym like "1*";10;1]*{[x;y;z;u;v;b;a]p:$[x=1;a;x>1;v[;x-1];x=-1;b;x<-1;u[;abs[x]-1];y];?[p>0;p;?[y>0;y;z]]}[x;sym.price;sym.pc;sym.bidQ;sym.askQ;sym.bid;sym.ask]*1f^sym.multiplier;0n]] from .db.ETFPF where etfsym=y,sym<>`159900.XSHE)%.db.ETF[y;`cu]]};

getiopv:getiopvex[0];

//getiopvhkex:{[x;y;z]$[.db.ETF[y;`trday]<>.z.D;0n;(.db.ETF[y;`cueu]+exec sum (z*?[qty<=0;0f;qty]*?[sym like "1*";10;1]*{[x;y;z;u;v;b;a]p:$[x=1;a;x>1;v[;x-1];x=-1;b;x<-1;u[;abs[x]-1];y];?[p>0;p;?[y>0;y;z]]}[x;sym.price;sym.pc;sym.bidQ;sym.askQ;sym.bid;sym.ask]*1f^sym.multiplier)+?[qty>=0;0f;camt] from .db.ETFPF where etfsym=y,sym<>`159900.XSHE)%.db.ETF[y;`cu]]}; /上海基金份额参考净值＝[∑(替代标志为0/1/3成分证券最新替代金额)+∑(替代标志为2/4/5/6的成分证券对应资金)+预估现金]/最小申购赎回单位对应的ETF份数(0-沪市不可被替代;1-沪市可以被替代;2-沪市必须被替代;3-深市退补现金替代;4-深市必须现金替代;5-非沪深市场成分证券退补现金替代;6-非沪深市场成份证券必须现金替代),对可转债ETF,申赎清单中债券单位是手,需要再乘10,另外还涉及行情可能为净价而非全价的误差,行情中的settlepx更准确,要注意特别处理.为加强异常处理,去掉 .db.QX[y;`settlepx]^
//getiopvhk:getiopvhkex[0];

getiopvhkex:{[x;y;z]$[.db.ETF[y;`trday]<>.z.D;0n;(.db.ETF[y;`cueu]+exec sum ?[cctype in "2468";camt;z*?[cctype in "01357";qty*?[sym like "1*";10;1]*{[x;y;z;u;v;b;a]p:$[x=1;a;x>1;v[;x-1];x=-1;b;x<-1;u[;abs[x]-1];y];?[p>0;p;?[y>0;y;z]]}[x;sym.price;sym.pc;sym.bidQ;sym.askQ;sym.bid;sym.ask]*1f^sym.multiplier;0n]] from .db.ETFPF where etfsym=y,sym<>`159900.XSHE)%.db.ETF[y;`cu]]};

getiopvhk:getiopvhkex[0];

qryordtask:{[x;y]qryord each exec id from .db.O where not end,cn>1;1b};

cxlall:{[x]n:.conf.maxcxlcnt;.conf.maxcxlcnt:0W;$[null x;cxlord each exec id from .db.O where not end;cxlord each exec id from .db.O where not end,ts=x];.conf.maxcxlcnt:n;};
qryall:{[x]$[null x;qryord each exec id from .db.O where not end;qryord each exec id from .db.O where not end,ts=x];};

qryrepoacc:{[x;y].temp.AccSnap:.enum.nulldict;qryfund .conf[`repo;`acc];1b};
dorepotask:{[x;y]s0:`204001.XSHG;s1:`131810.XSHE;h0:.db.QX[s0];h1:.db.QX[s1];amt:.temp.AccSnap[.conf[`repo;`acc];`Fund][0;.conf[`repo;`field]];qu0:1000f;qu1:h1`qtylot;fv:100f;a0:fv*q0:qu0*floor amt%fv*qu0;a1:amt-a0;q1:qu1*floor a1%fv*qu1;if[0<q0;revrepo[.conf[`repo;`ts];s0;q0;last h0`bidQ;`repo1daysh]];if[0<q1;revrepo[.conf[`repo;`ts];s1;q1;last h1`bidQ;`repo1daysz]];1b};  

.roll.ftl2:{[x].db.Lm:.db.Vm:(`u#`long$())!`float$();.db.Bm:.db.Am:()!();.db.Wm:(`u#`long$())!();.db.Tm:(`u#`long$())!();.db.Pm:(`u#`symbol$())!`timestamp$();.db.CBBO:([`u#sym:`symbol$()] extime:`timestamp$();bp:`float$();bq:`float$();op:`float$();oq:`float$());.db.L2seq:1;};  //Vm(委托序号->委托价格),Lm(委托序号->剩余数量),Wm(委托序号->未处理成交列表),Tm(未处理成交表),Pm(代码->交易所时间戳)

.upd.l2quote:.upd.quote;

newl2seq:{[]:.db.L2seq+:1};

imptradex:{[t;x]e:fs2e y:x`sym;if[.db.Pm[y]<x`extime;.db.Pm[y]:x`extime];if[not y in key .db.Am;.db.Am[y]:.db.Bm[y]:(`u#`float$())!`float$()];q:x`qty;if[0<u:x`aid;u:x[`gid]+100000j*u];if[0<v:x`bid;v:x[`gid]+100000j*v];z:newl2seq[];wu:(u>0)&null .db.Vm[u];wv:(v>0)&null .db.Vm[v];if[$[`XSHG=e;wu&wv;wu|wv];if[not t;.db.Tm[z]:x;if[wu;.db.Wm[u],:z];if[wv;.db.Wm[v],:z]];:()];if[(0<u)&(0<=p:.db.Vm[u]);.db.Lm[u]-:q;if[0>=.db.Am[y;p]-:q;.db.Am[y] _:p];if[count .db.Wm[u];.db.Wm[u]:.db.Wm[u] except z;if[0=count .db.Wm[u];.db.Wm _:u]]];if[(0<v)&(0<=p:.db.Vm[v]);.db.Lm[v]-:q;if[0>=.db.Bm[y;p]-:q;.db.Bm[y] _:p];if[count .db.Wm[v];.db.Wm[v]:.db.Wm[v] except z;if[0=count .db.Wm[v];.db.Wm _:v]]];};  //逐笔成交处理.wu(成交先于卖单委托),wv(成交先于买单委托) if[(0<u)&0>=.db.Lm[u];.db.Lm _:u;.db.Vm _:u];if[(0<v)&0>=.db.Lm[v];.db.Lm _:v;.db.Vm _:v]; `$(string u),"_",(string v)

imptrade:imptradex[0b];impoldtrade:imptradex[1b];

impshcxl:{[x]y:x`sym;q:x`qty;u:x[`gid]+100000j*x`oid;if[0<=p:.db.Vm[u];.db.Lm[u]-:q;$[x[`side] in "1B";if[0>=.db.Bm[y;p]-:q;.db.Bm[y] _:p];if[0>=.db.Am[y;p]-:q;.db.Am[y] _:p]]];};  //上海撤单委托处理

.upd.l2order:{[x].temp.x3:x;e:fs2e y:x`sym;if[.db.Pm[y]<x`extime;.db.Pm[y]:x`extime];if["D"=x`typ;impshcxl x;:()];z:x[`gid]+100000j*x`oid;if[not y in key .db.Am;.db.Am[y]:.db.Bm[y]:(`u#`float$())!`float$()];w:x`side;p:x`price;q:x`qty;if[x[`typ] in "1U";p:0f];.db.Vm[z]:p;.db.Lm[z]:q;$[w in "1B";[.db.Bm[y;p]:q+0f^.db.Bm[y;p]];w in "2S";[.db.Am[y;p]:q+0f^.db.Am[y;p]];[]];if[count r:.db.Wm[z];impoldtrade each .db.Tm r];}'; //逐笔委托处理 

.upd.l2match:{[x].temp.x4:x;imptrade each x;};

.upd.l2queue:{[x]s:x`side;y:x`sym;if[x[`extime]<.db.QX[y;`extime];:()];.db.QX[y;$[s="B";`bid`bsize`bnum`bqtyQ;`ask`asize`anum`aqtyQ]]:x`price`size`num`qtyQ;}';

getcbbo:{[x]if[.db.CBBO[x;`extime]>=y:.db.Pm[x];:.db.CBBO[x;`extime`bp`bq`op`oq]];bq:.db.Bm[x] bp:first desc (key .db.Bm[x]) except 0f;oq:.db.Am[x] op:first asc  (key .db.Am[x]) except 0f;:.db.CBBO[x;`extime`bp`bq`op`oq]:(y;bp;bq;op;oq);}; //[sym]取交易所时间戳和计算出的最新最优盘口

ems_algordex:{[sd;x;y;q;p;m;a;h]pe:.enum $[sd=.enum`BUY;`OPEN;`CLOSE];h:``algo`algotype`algopara!(`;1b;a;h);newordex[sd;pe;x;y;q;p;m;h]};

ems_algord:{[sd;x;y;q;p;m;a;t]ems_algordex[sd;x;y;q;p;m;a;`start_time`end_time!`second$.z.T+0,t]};ems_algobuy:ems_algord[.enum`BUY];ems_algosell:ems_algord[.enum`SELL];

\
.db.TASK[`LOADETF;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+09:10;1D;0;4;`loadetf);
.db.TASK[`QRYORD;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+09:10;0D00:00:30;0;4;`qryordtask);
.db.TASK[`QRYREPOACC;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+14:58:00;1D;0;4;`qryrepoacc);
.db.TASK[`DOREPOTASK;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+14:58:30;1D;0;4;`dorepotask);

//----ChangeLog----
//2023.08.21:更新qtyunit函数以支持算法正常拆单
//2023.08.06:新增ems_algordex/ems_algord/ems_algobuy/ems_algosell函数以支持下卖方算法单
//2023.07.27:cxlordex修正用k不正确的替换x的bug
//2023.07.11:增加qryfundpeer和.upd.FundPeerUpdate函数;增加allocfund和.upd.FundAllocUpdate函数
//2023.07.05:增加qrymat和.upd.MatUpdate函数
//2023.06.16:.timer.ftsim函数修正未添加exchid和cexchid的bug
//2023.05.17:.upd.l2order增加对市价单置p=0,.timer.ftsim增加对IPS单过滤
//2023.04.27:setcs和.upd.exerpt增加对exchid和cexchid的支持
//2023.03.20:.upd.l2order函数中统一使用`origid,深市不再区别使用`oid
