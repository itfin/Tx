.module.fqxshe:2018.04.23;

txload "core/fqbase";
txload "lib/extutil";
txload "feed/socket";

.temp.L:();.temp.B:"";

crc:{`char$0x0 vs `int$mod[;256] sum x};
packcrc:{[x]x,crc[x]};

padx:{[f;n;x]n#x,(0|n-count[x])#f};
pad:padx[" "];padf:padx[0n];

tobe:{[x]`char$raze 0x0 vs/: x}; /int to big endian

logonmsg:packcrc[tobe[1 92i],pad[20;string .conf.selfid],pad[20;string .conf.peerid],tobe[`int$.conf.hbint],pad[16;string .conf.passwd],pad[32;string .conf.verid]];hbmsg:packcrc[tobe[3 0i]];

onsockconn:{[x].ctrl.tcpconn[x;`status`selftime`peertime`logontime]:(`Connected;0Np;0Np;0Np);};

mdgw_logon:{[]x:.conf.mdgwid;if[(0<h:.ctrl.tcpconn[x;`h])&.ctrl.tcpconn[x;`status]=`Connected;.ctrl.tcpconn[x;`status]:`LogonHalf;smtcp[x;logonmsg]];};

mdgw_hb:{[];};

BIN:()!();
BIN[1i]:{[x]x:.conf.mdgwid;if[.ctrl.tcpconn[x;`status]=`LogonHalf;.ctrl.tcpconn[x;`status`logontime]:(`Logon;.z.P)];}; /Logon
BIN[2i]:{[x]lwarn[`MDGW_Logout;first each (4 200;"is") 1: x];if[0<h:.ctrl.tcpconn[.conf.mdgwid;`h];hclose[h]];}; /Logout
BIN[3i]:{[x].ctrl.tcpconn[.conf.mdgwid;`peertime]:.z.P;}; /HeatBeat
BIN[8i]:{[x];}; /BusiRej

BIN[390095i]:{[x];}; /频道心跳
BIN[390094i]:{[x];}; /重传消息
BIN[390093i]:{[x];}; /用户报告
BIN[390090i]:{[x];}; /频道统计

BIN[390019i]:{[x];}; /市场状态
BIN[390013i]:{[x];}; /证券状态
BIN[390012i]:{[x];}; /公告

snapshot:{[x]h:first each (8 2 3 8 4 8 8 8 8 8;"jhssssjjjj") 1: 65#x;if[not h[2] in `010`040`630`900;:`];dt:"DT"$'0 8 cut string h[0];z:` sv h[3],$[h[4]=`102;`XSHE;`XHKE];h[6 7 8 9]*:1e-4 1 1e-2 1e-4;.db.QX[z;`recvtime`extime`nticks`vwap`state`pc`cumqty`cumamt]:(.z.P;dt[0]+`timespan$dt[1];1+0^.db.QX[z;`nticks];h[9]%h[8]),h[5 6 8 9];z}; /快照头,单一代码

BIN[300111i]:{[x].temp.X1:x;if[null z:snapshot[x];:()];n:`long$0x0 sv `byte$x[65+til 4];.db.QX[z;`bidQ`askQ`bsizeQ`asizeQ]:4#enlist `float$();{[z;x]r:first each (2 8 8 2 8 4;"sjjhji") 1:x;t:r[0];r[1 2]*:1e-6 1e-2;l:r[3];$[t in `0`1;[if[l=1;.db.QX[z;((`0`1;`1`1)!(`bid`bsize;`ask`asize))t,`$string l]:r[1 2]];k:$[t=`0;`bidQ;`askQ];if[l>count d:.db.QX[z;k];.db.QX[z;k]:padf[l;d]];.db.QX[z;k;l-1]:r[1];k:$[t=`0;`bsizeQ;`asizeQ];if[l>count d:.db.QX[z;k];.db.QX[z;k]:padf[l;d]];.db.QX[z;k;l-1]:r[2]];t in `2`4`7`8`9`x8`xe`xf`xg;.db.QX[z;(`2`4`7`8`9`x8`xe`xf`xg!`price`open`high`low`vwap`settlepx`sup`inf`openint) t]:r[1];()]}[z] each (n,32)#69_x;}; /竞价快照(Level-1 32byte定长记录,Level-2不适用)t:买卖,r[3]档位 

BIN[306311i]:{[x].temp.X2:x;if[null z:snapshot[x];:()];if[null .db.QX[z;`assetclass];.db.QX[z;`assetclass]:`SGT];n1:`long$0x0 sv `byte$x[65+til 4];{[z;x]r:first each (2 8 8 2;"sjjh") 1:x;t:r[0];r[1 2]*:1e-6 1e-2;$[t in `0`1;.db.QX[z;((`0`1;`1`1)!(`bid`bsize;`ask`asize))t,`$string r[3]]:r[1 2];t in `2`7`8`xh`xe`xf`xi;.db.QX[z;(`2`7`8`xh`xe`xf`xi!`price`high`low`settlepx`sup`inf`openint) t]:r[1];()]}[z] each (n1,20)#69_x;n2:0x0 sv `byte$x[69+(20*n1)+til 4];if[n2;.db.QX[z;`tradephase`notice]:(`VCM;"-" sv string first each (8 8;"jj") 1: x[69+(20*n1)+4+til 16])];}; /港股快照

BIN[309011i]:{[x].temp.X3:x;if[null z:snapshot[x];:()];n:`long$0x0 sv `byte$x[65+til 4];{[z;x]r:first each (2 8;"sj") 1:x;t:r[0];r[1]*:1e-6;$[t in `3`xa`xb`xc`xd;.db.QX[z;(`3`xa`xb`xc`xd!`price`pc`open`high`low) t]:r[1];()]}[z] each (n,10)#69_x;}; /指数快照

BIN[300611i]:{[x];}; /盘后定价快照
BIN[309111i]:{[x];}; /成交量统计快照

BIN[300192i]:{[x];}; /竞价逐笔委托
BIN[300592i]:{[x];}; /协议逐笔委托
BIN[300792i]:{[x];}; /融券逐笔委托

BIN[300191i]:{[x];}; /竞价逐笔成交
BIN[300591i]:{[x];}; /协议逐笔成交
BIN[300791i]:{[x];}; /融券逐笔成交


decodeszv5binstream:{[x]l:0;y:x;while[1;if[8>m:count y;:l];h:(4 4;"ii") 1: 8#y;if[(0>(t:h[0;0])|n:h[1;0]);:-1];if[m<n2:4+n1:8+n;:l];z:n1#y;y:n1 _y;c:4#y;if[not c~crc[z];:-2];y:4_y;l+:n2;z:8_z;if[.conf.dumpmsg;.temp.L,:enlist (t;z)];BIN[t;z]];};

onsockmsg:{[x;y].temp.X:(x;y);if[.conf.dumpmsg;.temp.B,:y];w:x`w;b:$[null w;"";.ctrl.tcpconn[w;`rbuf]],y;r:decodeszv5binstream b;if[not null w;$[0>r;hclose[.ctrl.tcpconn[w;`h]];.ctrl.tcpconn[w;`rbuf]:r _b]];}; 

.timer.fqxshe:{[x]if[not .z.T within .conf.onlinetime;:()];mdgw_logon[x];mdgw_hb[x];batchpub[];};

getreffile:{[t;x]$[t;xmlparse;::] read0 ` sv .conf.refpath,`$string[x],"_",((string .z.D) except "."),$[t;".xml";".txt"]}; /t:0(txt),1(xml) 
getrefxml:getreffile[1];getreftxt:getreffile[0];

get_securityswitch:{[x]d:getrefxml[`securityswitch];t:raze @[{[x]y:` sv (`$x[0;1]),$[`102=`$x[1;1];`XSHE;`XHKE];`sym xcols update sym:y from flip `switch`status!flip `$x[2;1;;1;;1]};;()] each d[0;1;;1];select notice: `$"|" sv switch {[x;y] (string x),"=",(string y)}' status  by sym from t}; /证券业务开关信息

get_cashauctionparams:{[x]d:getrefxml[`cashauctionparams];1!`sym xcols update sym: sv[`] each (,\:)[sym;`XSHE],qtylot:qtyminl  from flip `sym`qtymaxl`qtymaxs`qtyminl`qtymins`pxunit!"SFFFFF"$'flip d[0;1;;1;0 2 3 4 5 6;1]}; /现货集中竞价交易业务参考信息 

get_securities:{[x]d:getrefxml[`securities];1!`sym`ex xcols update sym: sv[`] each (,\:)[sym;`XSHE],ex:`XSHE from flip `sym`name`isin`underlying`opendate`sectype`currency`tradetype`pc`totalshares`outstanding`facevalue!"SSSSDSSSFFFF"$'flip d[0;1;;1;0 3 4 5 7 8 9 11 12 14 15 16;1]}

get_hkexreff04:{[x]d:(" SSS SSSSSFF FDFFS";"|") 0: getreftxt[`hkexreff04];1!`sym`ex xcols update sym: sv[`] each (,\:)[sym;`XHKE],ex:`XHKE from flip `sym`isin`name`ticker`underlying`secclass`sectype`currency`scale`facevalue`accuvalue`opendate`qtylot`pc`remark!d};

getrd:{[](get_securityswitch[] lj get_cashauctionparams[] lj get_securities[]) lj @[get_hkexreff04;();()]};

qxsnap:{[]1!select sym,ex,esym,name,ticker,assetclass,product,multiplier,currency,strikepx,putcall,sectype,pxunit,qtylot,qtymax,qtymaxm,qtymaxl,qtymaxs,margintype,rmarginl,rmargins,rmarginoq,rmarginmq,rfeetaxoa,rfeetaxoq,rfeetaxca,rfeetaxcq,rfeetaxcat,rfeetaxcqt,rfeetaxom,rfeetaxcm,rfeetaxctm,settledate,opendate,createdate,lifephase,sec_key,underlying,isin,ex1,cficode,notice,remark from .db.QX where not null name};

batchpub:{[]if[.db.fqopendate<d0:.db.sysdate;.db.fqopendate:d0;.temp.L:.temp.Last:.temp.LastRef:();.db.QX:0#.db.QX;d:@[getrd;::;()];if[count d;.db.QX:.db.QX uj d;(path:` sv .conf.tempdb,.conf.me,`RD) set qxsnap[];pubm[`ALL;`RDUpdate;`xshe;string path]];.[updetf;(`;`);()]];n:count d:(select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode,extime,bidQ,askQ,bsizeQ,asizeQ from .db.QX where not null sym,0<nticks) except .temp.Last;if[n;.temp.Last:$[0=count .temp.Last;d;0!(1!.temp.Last),1!d];pub[`quote;update bidQ:?[0=count each bidQ;n#enlist `float$();bidQ],askQ:?[0=count each askQ;n#enlist `float$();askQ],bsizeQ:?[0=count each bsizeQ;n#enlist `float$();bsizeQ],asizeQ:?[0=count each asizeQ;n#enlist `float$();asizeQ],quoopt:n#enlist "" from d]];d2:(select sym,pc,open,0w^sup,0f^inf from .db.QX where not null sym,0<nticks) except .temp.LastRef;if[n:count d2;.temp.LastRef:$[0=count .temp.LastRef;d2;0!(1!.temp.LastRef),1!d2];pub[`quoteref;update refopt:n#enlist"" from d2]];update nticks:0 from `.db.QX;};

//`Version`SecurityID`SecurityIDSource`Symbol`FundManagementCompany`UnderlyingSecurityID`UnderlyingSecurityIDSource`CreationRedemptionUnit`EstimateCashComponent`MaxCashRatio`Publish`Creation`Redemption`RecordNum`TotalRecordNum`TradingDay`PreTradingDay`CashComponent`NAVperCU`NAV`DividendPerCU`CreationLimit`RedemptionLimit`CreationLimitPerUser`RedemptionLimitPerUser`NetCreationLimit`NetRedemptionLimit`NetCreationLimitPerUser`NetRedemptionLimitPerUser
//`UnderlyingSecurityID`UnderlyingSecurityIDSource`UnderlyingSymbol`ComponentShare`SubstituteFlag`PremiumRatio`CreationCashSubstitute`RedemptionCashSubstitute

loadpcfsz:{[x]m:getrefxml[`$"pcf_",string fs2s x];r:(!/)flip m[0;1];d:"D"$r`TradingDay;.db.ETF[x;`trday`cu`cueu`cutc`cunv`cudv`nav`ctmax`rdmax`cashrmax`pubok`ctok`rdok`cashct`pfnumlocal`pfnum`pretrday`underlying`etftype`name`companyname`version]:(d;"F"$r`CreationRedemptionUnit;"F"$r`EstimateCashComponent;0n;"F"$r`NAVperCU;"F"$r`DividendPerCU;"F"$r`NAV;"F"$r`CreationLimit;"F"$r`RedemptionLimit;"F"$r`MaxCashRatio;"B"$r`Publish;"B"$r`Creation;"B"$r`Redemption;0b;"J"$r`RecordNum;"J"$r`TotalRecordNum;"D"$r`PreTradingDay;sv[`;(`$r`UnderlyingSecurityID),`XSHE];`1;`;`;`$r`Version);delete from `.db.ETFPF where etfsym=x;.db.ETFPF,:select etfsym:x,sym:{`$x,$[x like "m*";".XDCE";x like "6*";".XSHG";".XSHE"]} each UnderlyingSecurityID,qty:"F"$ComponentShare,cctype:first each SubstituteFlag,ccprem:"F"$PremiumRatio,camt:"F"$CreationCashSubstitute,ramt:"F"$RedemptionCashSubstitute,trday:d from {(!/) flip x[1]} each r`Components;};

loadpcfsh:{[x]y:fs2se[x];c:`char$read1 ` sv (.conf.refpathsh),`$(string y[0]),(-4#(string .z.D) except "."),".etf";i0:1+c?"\n";i1:first c ss "TAGTAG";i2:first c ss "ENDENDEND";c:(i0,i1,i2)_c;h:(!/)"S=\n" 0: ssr [;"maxCashratio";"MaxCashRatio"] ssr [;"Estimatecashcomponent";"EstimateCashComponent"] ssr[;"Recordnum";"RecordNum"] c[0] except "\r";.db.ETF[x;`trday`cu`cueu`cutc`cunv`cudv`nav`ctmax`rdmax`cashrmax`pubok`ctok`rdok`cashct`pfnumlocal`pfnum`pretrday`underlying`etftype`name`companyname`version]:"DFFFFFFFFFBBBBIIDSSSSS"$' h[`TradingDay`CreationRedemptionUnit`EstimateCashComponent`CashComponent`NAVperCU`DividendPerCU`NAV`CreationLimit`RedemptionLimit`MaxCashRatio`Publish,$[x=`XSHE;`Creation`Redemption;`CreationRedemption`CreationRedemption],`CashCreation`RecordNum`TotalRecordNum`PreTradingDay`UnderlyingIndex`Type`FundName`FundManagementCompany`Version];delete from `.db.ETFPF where etfsym=x;.db.ETFPF,:`etfsym xcols update etfsym:x,sym:{[x]se2fs x,$[x like "6*";`XSHG;`XSHE]} each sym,ramt:camt^ramt,trday:.db.ETF[x;`trday] from flip `sym`qty`cctype`ccprem`camt`ramt!("S FCFFF";"|") 0: (8_c[1]);};

loadpcf:{[x]e:fs2e x;$[e=`XSHE;loadpcfsz;loadpcfsh] x;};

updetf:{[x;y]loadpcf each .conf.etflist;{set[` sv .conf[`tempdb],x;.db[x]];} each `ETF`ETFPF;1b};

.disp.fqxshe:{.ctrl.tcpconn};
\
d:flip `sym`isin`name`name1`name2`underlying`block`stype`currency`scale`facevalue`facecurr`interest`listdate`qtylot`pc`remark!(" ",(9#"S"),"FF","SFDFFS";"|") 0: read0 `:hkexreff04_20170621.txt

52 3#6_first flip ("SS",160#"F";"|") 0: read0 `:hkexzxjc_20170621.txt

.db.ETF:([`u#sym:`symbol$()]trday:`date$();cu:`float$();cueu:`float$();cutc:`float$();cunv:`float$();cudv:`float$();nav:`float$();ctmax:`float$();rdmax:`float$();cashrmax:`float$();pubok:`boolean$();ctok:`boolean$();rdok:`boolean$();cashct:`boolean$();pfnumlocal:`long$();pfnum:`long$();pretrday:`date$();underlying:`symbol$();etftype:`symbol$();name:`symbol$();companyname:`symbol$();version:`symbol$()); /ETF Meta

.db.ETFPF:([etfsym:`symbol$();sym:`symbol$()]qty:`float$();cctype:`char$();ccprem:`float$();camt:`float$();ramt:`float$();trday:`date$()); /ETF Portfolio

.db.TASK[`UPDETF;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+09:05;1D;0;4;`updetf);