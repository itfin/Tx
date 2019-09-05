/恒生柜台交易接口程序(T2SDK)

.module.feufx:2019.06.04;

txload "core/febase";

`initt2`freet2`connt2`connt2sub`t2call`topiclist`hsdc_encrypt`hsdc_getsysteminfo`hsdc_getdetailerror`hsdc_version`t2addr`t2mac {x set $[1b~.conf.ufx.futestmode;`extfeufxtest;`extfeufx] 2: (x;y)}' 1 1 2 3 3 1 2 1 1 1 1 1; 

.enum.hsexmap:`1`2`3`4`7`9`k`35`o!`XSHG`XSHE`XSGE`XZCE`CCFX`XDCE`XINE`XHKG`XHKE;.enum.ex2hs:mirror .enum.hsexmap;
.enum.hssidemap:"12"!.enum`BUY`SELL;.enum.side2hs:mirror .enum.hssidemap;
.enum.hsposefctmap:"124"!.enum`OPEN`CLOSE`CLOSETODAY;.enum.posefct2hs:mirror .enum.hsposefctmap;
.enum.hsstatusmap:"123456789abcdABCDEF"!.enum`PENDING_NEW`PENDING_NEW`PENDING_NEW`NEW`REJECTED`PARTIALLY_FILLED`FILLED`CANCELED`CANCELED`PENDING_CANCEL`PENDING_NEW`REJECTED`CANCELED`PENDING_CANCEL`PENDING_CANCEL`PENDING_CANCEL`PENDING_CANCEL`PENDING_CANCEL`CANCELED;

callsync:t2call[;;0i];callasync:t2call[;;1i];

.ctrl.ufx:.enum.nulldict;
.ctrl.tcpconn:.enum.nulldict;
.ctrl.tcpconn[.conf.ufx.t2name]:.enum.nulldict;
.ctrl.tcpconn[.conf.ufx.subname]:.enum.nulldict;

.temp.C:.temp.L:();

.temp.MSG:([id:`int$()]funcid:`symbol$();senttime:`timestamp$();recvtime:`timestamp$();src:`symbol$();req:();sentfill:`boolean$();sentcode:`int$();sentspan:`timespan$();senttry:`int$();msgid:();corrid:();peertime:`datetime$();recvfill:`boolean$();recvcode:`int$();recvspan:`timespan$();recvtry:`int$();ans:();src:`symbol$();oid:`symbol$();internal:`boolean$()); /ufx Msg

onhst2:{[x].temp.L,:(enlist .z.T),/:x;{.upd[x[0]][x[1]]} each x;};

.init.feufx:{[x].ctrl.ufx.Run:initt2[];}
.exit.feufx:{[x]freet2[];};

.disp.feufx:{.ctrl.ufx};

connHS:{[x;y]c:connt2[(`t2sdk`servers;`t2sdk`license_file;`t2sdk`if_error_log;`t2sdk`logdir;`t2sdk`if_sendRecv_log;`t2sdk`writedata;`t2sdk`lang;`t2sdk`send_queue_size;`safe`safe_level;`)!(.conf.ufx.servers;.conf.ufx.licfile;.conf.ufx.errlog;.conf.ufx.logdir;.conf.ufx.msglog;.conf.ufx.dumpmsg;`1033;`1000;`none;0b);1000i*$[`SYNC~.conf.ufx.mode;1i;-1i]];if[c<>0;.ctrl.tcpconn[.conf.ufx.t2name]:`h`status`lostseq!(-1;`Disconnected;c);:()];.ctrl.tcpconn[.conf.ufx.t2name;`h`isvr`proto`hbint`hbsent`status`conntime]:(0W;1b;`ufx;.conf.ufx.hbint;.z.P;$[`SYNC~.conf.ufx.mode;`Connected;`Connecting];.z.P);};  /.conf.ufx.licno;

connHSsub:{[x;y]c:connt2sub[(`t2sdk`servers;`t2sdk`license_file;`t2sdk`if_error_log;`t2sdk`logdir;`t2sdk`if_sendRecv_log;`t2sdk`writedata;`t2sdk`lang;`t2sdk`send_queue_size;`safe`safe_level;`mc`client_name;`subcribe`biz_name;`subcribe`topic_name;`subcribe`is_rebuilt;`subcribe`is_replace;`)!(.conf.ufx.subservers;.conf.ufx.licfile;.conf.ufx.errlog;.conf.ufx.logdir;.conf.ufx.msglog;.conf.ufx.dumpmsg;`1033;`1000;`none;.conf.ufx.subuser;.conf.ufx.subuser;.conf.ufx.topic;`false;`false;0b);`login_operator_no`operator_no`password!(.conf.ufx.user;.conf.ufx.user;.conf.ufx.pass);1000i];if[c<>0;.ctrl.tcpconn[.conf.ufx.subname]:`h`status`lostseq!(-1;`Disconnected;c);:()];.ctrl.tcpconn[.conf.ufx.subname;`h`isvr`proto`hbint`hbsent`status`conntime]:(0W;1b;`ufx;.conf.ufx.hbint;.z.P;`Connected;.z.P);}; /`t2sdk`license_no; .conf.ufx.licno;

/api msg
sectype:{[x;y]$[y in `3`4`7`9`k;$[(x like "IO*")|(x like "*-*")|(x like "*[0-9]C[0-9]*")|(x like "*[0-9]P[0-9]*");`OPT;x like "SP*";`FUTSP;`FUT];y in `1`2;$[8=count string x;`OPT;`STK];y in `35`o;`STKHK;`STK]}; /[sym;hsex]

.upd.ordnew:{[x].temp.x0:x;if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;if[count opt:x`ordopt;h:strdict opt];x[`qty`price]:`float$x`qty`price;k1:newidl[];.db.O[k;`feoid`ntime`status`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[@[riskassert;k;0b];rejectord[k;1i;"Reject_by_Risk_Check"];:()];acL:vs[`] x`acc1;ac0:acL[0];ac:acL[1];se:fs2se x`osym;se[1]:.enum.ex2hs se[1];st:sectype[se[0];se[1]];pe:.enum.posefct2hs x`posefct;ct:`0;if["4"~pe;pe:"2";ct:`1];hsfunc[(`STK`STKHK`FUT`OPT`FUTSP!91001 91021 91004 91005 91013i)st;`src`oid`req!(x`src;k;(`user_token`account_code`combi_no`market_no`stock_code`entrust_direction`price_type`entrust_price`entrust_amount`extsystem_id`third_reff`mac_address`ip_address`hd_volserial,$[st in `STK`STKHK;();`futures_direction`close_direction])!(.ctrl.ufx.token;ac0;ac;se[1];se[0];.enum.side2hs x`side;$[st=`STKHK;`g;`0];x`price;x`qty;k1;x`ts;.conf.ufx.macaddr;.conf.ufx.ipaddr;.conf.ufx.disksn),$[st in `STK`STKHK;();(pe;ct)])]}'; 

.upd.ordcxl:{[x].temp.x1:x;if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;if[(null k)|(null .db.O[k;`ordid]);:()];if[@[riskassertcxl;k;0b];rejcxl[k;1i;"Reject_by_Risk_Check"];:()];.db.O[k;`cstatus]:.enum`PENDING_CANCEL;execrpt[k];acL:vs[`] .db.O[k;`acc1];ac0:acL[0];ac:acL[1];se:fs2se .db.O[k;`sym];se[1]:.enum.ex2hs se[1];st:sectype[se[0];se[1]];hsfunc[(`STK`STKHK`FUT`OPT`FUTSP!91114 91117 91119 91120 91121i)st;`src`oid`req!(x`src;k;`user_token`account_code`combi_no`entrust_no!(.ctrl.ufx.token;ac0;ac;.db.O[k;`ordid]))];}';

.upd.ordqry:{[x]qryordex[x`src;x`oid];}';

qryordex:{[src;k]if[null k1:.db.O[k;`feoid];:()];k2:.db.O[k;`ordid];se:fs2se .db.O[k;`sym];acL:vs[`] .db.O[k;`acc1];ac0:acL[0];ac:acL[1];se[1]:.enum.ex2hs se[1];st:sectype[se[0];se[1]];hsfunc[(`STK`STKHK`FUT`OPT`FUTSP!32001 32009 32003 32004 32008i)st;`src`oid`req!(src;k;(`user_token`account_code`combi_no,$[null k2;`extsystem_id;`entrust_no])!(.ctrl.ufx.token;ac0;ac;$[null k2;k1;k2]))];};
qryord:qryordex[`];

qryfutopt:{[x;y]hsfunc[$[x;30012i;30010i];`src`oid`req!(`;`;`user_token`request_num!(.ctrl.ufx.token;10000i))];};
qryfut:qryfutopt[0];qryopt:qryfutopt[1];

qryposex:{[x;y;z;w]hsfunc[$[0=x;31001i;1=x;31003i;31004i];`src`oid`req!(y;z;`user_token`combi_no!(.ctrl.ufx.token;w))];};
qryposstk:qryposex[0;`;`];qryposfut:qryposex[1;`;`];qryposopt:qryposex[2;`;`];

qrycomb:{[x]hsfunc[30003i;`src`oid`req!(`;`;(enlist `user_token)!enlist .ctrl.ufx.token)];};

.upd.QueryPos:{[x]y:x`ref;z:`$x`msg;.temp.P:();.temp.nQPack:0;qryposex[;y;z;-9!x`vbin] each 0 1;};

/fe msg
errcode:{[r]z:r[0;0;`ErrorCode];$[10h=type z;"I"$z;z]}; /恒生业务消息的错误码字段,从第一个结果集的第一行提取,注意不同业务消息的类型不统一 
errmsg:{[r]r[0;0;`ErrorMsg]};

.upd.Hello:{[x]hsfunc[10000;`src`req!(`;(enlist `user_token)!enlist .ctrl.ufx.token)];};
.upd.Login:{[x]hsfunc[10001;`src`req!(`;(`operator_no`password`mac_address`op_station`ip_address`authorization_id`app_id`authorize_code`port_id!(.conf.ufx.user;.conf.ufx.pass;.conf.ufx.macaddr;.conf.ufx.disksn;.conf.ufx.ipaddr;.conf.ufx.licno;.conf.ufx.appid;.conf.ufx.authcode;"I"$last vs[":"] t2addr[]);`counter_id`terminal_no`data_scale`service_errcode!`2,(`$hsdc_getsysteminfo[]),`0))];}; /

.upd.OnConnect:{.ctrl.tcpconn[$[x;`sub;`t2];`status`conntime]:(`Connected;.z.P);};
.upd.OnSafeConnect:{};
.upd.OnRegister:{.ctrl.ufx[`Registered]:1b;};
.upd.OnClose:{.ctrl.tcpconn[$[x;`sub;`t2];`h`status`disctime]:(-1;`Disconnected;.z.P);};

.upd.OnReceivedBiz:{[x]k:x[0];y:x[1];r:x[2];.temp.MSG[k;`ans`recvtime]:(enlist r;now[]);if[(0h=type r)&(0<count r);.upd[.temp.MSG[k;`funcid];`src`oid`res!(.temp.MSG[k;`src];.temp.MSG[k;`oid];r)];if[not errcode[r] in 0 0N;lwarn[`HST2Res;(x;r)]]];};

cxlrej:{[k]rejcxl[k;.db.O[k;`reason];.db.O[k;`msg]];};
ordrej:{[k]rejectord[k;.db.O[k;`reason];.db.O[k;`msg]];};

.upd.SubRecv:{[x].temp.x10:x;y:x[1;0;0];z:`$string y`batch_no;u:`$string y`entrust_no;v:`${$[10h=type x;x;string x]}y`cancel_entrust_no;w:.enum.hssidemap first y`entrust_direction;a:`$string y`extsystem_id;if[null k:exec first id from .db.O where (ordid in ((u,v) except `))|(feoid=a);:()];if[null .db.O[k;`ordid];.db.O[k;`ordid]:u];se:fs2se fs:.db.O[k;`sym];se[1]:.enum.ex2hs se[1];st:sectype[se[0];se[1]];hs:`$y`msgtype;$[hs in `a`b`d;[];hs=`c;[.db.O[k;`status`reason`msg]:(.enum`REJECTED;-1i;y`revoke_cause);ordrej[k]];hs=`f;[.db.O[k;`cstatus`reason`msg]:(.enum`REJECTED;-1i;y`revoke_cause);cxlrej[k]];[$[hs=`e;[cq:`float$y`cancel_amount;.db.O[k;`status`cumqty]:(.enum`CANCELED;.db.O[k;`qty]-cq)];[cq:`float$y`total_deal_amount;ca:`float$y`total_deal_balance;.db.O[k;`status`cumqty`avgpx]:(.enum$[cq=.db.O[k;`qty];`FILLED;`PARTIALLY_FILLED];cq;ca%cq*$[st in `FUT`OPT`FUTSP;1f^.db.QX[fs;`multiplier];1f])]];execrpt[k]]];}; /a委托下达b委托确认g委托成交c委托拒绝d委托撤单e委托撤成f委托撤废

.timer.feufx:{[x]s:.ctrl.tcpconn[.conf.ufx.t2name];if[0>=h:ifill s`h;connHS[`;`]];if[0<h;if[(1b~.ctrl.ufx[`Registered])&(not 1b~.ctrl.ufx[`login])&not 1b~.ctrl.ufx[`loginfail];.ctrl.ufx[`loginfail]:1b;.upd.Login[]];if[((s[`hbsent]+`timespan$`second$s[`hbint])<x)&1b~.ctrl.ufx[`login];.upd.Hello[()];.ctrl.tcpconn[.conf.ufx.t2name;`hbsent]:now[]]];s:.ctrl.tcpconn[.conf.ufx.subname];if[0>=h:ifill s`h;connHSsub[`;`]];}; 

hsfunc:{[x;y].temp.X:(x;y);fid:`$string x;req:y`req;$[`SYNC~.conf.ufx.mode;[k:newseq[];.temp.MSG[k;`src`funcid`req`oid`senttime]:(y`src;fid;enlist req;y`oid;now[]);.temp.r:r:callsync[x;req];.temp.MSG[k;`ans`recvtime]:(enlist r;now[]);if[(0h=type r)&(0<count r);.upd[fid][`src`oid`res!(y`src;y`oid;r)]];if[not errcode[r] in 0 0N;lwarn[`UfxErr;(x;k;r)]]];[r:callasync[x;req];$[r>0;.temp.MSG[r;`src`funcid`req`oid`senttime]:(y`src;fid;enlist req;y`oid;now[]);lwarn[`callasync_error;(r;x;req)]]]];if[r~-1;.ctrl.tcpconn[.conf.ufx.t2name;`h`status]:(-1;`Disconnected)];}; /[funcid;req]

/hs msg
.upd[`10000]:{[x].temp.x9:x;r:x`res;if[not (ec:errcode[r]) in 0 0N;.ctrl.ufx[`token`login`loginfail`errcode`errmsg`errtime]:(`;0b;0b;ec;errmsg[r];.z.P);:()];.ctrl.ufx.hbrecvtime:.z.P;}; /Heartbeat

.upd[`10001]:{[x].temp.x2:x;r:x`res;if[not ec:errcode[r] in 0 0N;.ctrl.ufx[`login`loginfail`errcode`errmsg]:01b,ec,errmsg[r];:()];.ctrl.ufx[`token`login`loginfail`logintime]:(`$raze r[1;0;`user_token];1b;0b;now[]);qryfut[];}; /Login

.upd[`91013]:.upd[`91005]:.upd[`91004]:.upd[`91021]:.upd[`91001]:{[x].temp.x3:x;k:x`oid;r:x`res;z:errcode[r];$[not z in 0 0N;.db.O[k;`end`status`reason`msg]:(1b;.enum`REJECTED;z;errmsg[r]);.db.O[k;`status`ordid]:(.enum`NEW;`$string r[1;0;`entrust_no])];execrpt[k];}; /ordnew

.upd[`91121]:.upd[`91120]:.upd[`91119]:.upd[`91117]:.upd[`91114]:{[x].temp.x4:x;k:x`oid;if[null .db.O[k;`sym];:()];r:x`res;z:errcode[r];m:errmsg[r];if[not z in 0 0N;[.db.O[k;`cstatus`reason`msg]:(.enum`REJECTED;z;m);rejcxl[k;z;m];:()]];if[1>=count r;:()];h:r[1;0];if[.db.O[k;`ordid]<>`$string h`entrust_no;:()];if[1<>z:"I"$h`success_flag;.db.O[k;`cstatus`reason`msg]:(.enum`REJECTED;z;h`fail_cause);rejcxl[k;z;h`fail_cause];:()];.db.O[k;`cstatus]:.enum`PENDING_CANCEL;}; /ordcxl

.upd[`32008]:.upd[`32004]:.upd[`32003]:.upd[`32009]:.upd[`32001]:{[x].temp.x5:x;k:x`oid;r:x`res;z:errcode[r];if[(not z in 0 0N)|(1>=count[r])|null .db.O[k;`sym];:()];h:r[1;0];if[.db.O[k;`ordid]<>`$string h`entrust_no;:()];s:.enum.hsstatusmap first h`entrust_state;cq:h`deal_amount;ca:h`deal_balance;ap:h`deal_price;xq:h`withdraw_amount;xm:h`withdraw_cause;q:.db.O[k;`qty];if[(0<xq)&(q=cq+xq)&s<>.enum`CANCELED;s:.enum`CANCELED];st:s;cs:$[s in .enum`PENDING_CANCEL`CANCELED;s;.enum`NULL];if[s=.enum`PENDING_CANCEL;st:$[0=cq;.enum`NEW;cq<q;.enum`PARTIALLY_FILLED;.enum`FILLED]];.db.O[k;`status`cstatus`cumqty`cumamt`avgpx`msg]:(st;cs;cq;ca;ap;xm);execrpt[k];}; /ordqry

.upd[`30010]:{.temp.x6:x;d:1!`sym xcols update sym:esym {sv[`]x,y}' ex,product:{[x]y:string x;`$first[ss[y;"[0-9]"]]#y} each esym from select ex:.enum.hsexmap `$market_no,esym:`$stock_code,name:`$stock_name,secclass:`$future_kind_name,multiplier:multiple,settledate:"D"$string last_trade_date,time1:"T"$string last_trade_time,date1:"D"$string settlement_date,pxunit:price_interval from x[`res;1];.db.QX:.db.QX uj d;(path:` sv .conf.tempdb,.conf.me,`RD) set d;pubm[`ALL;`RDUpdate;`ufx;string path];}; /futqry

.upd[`30012]:{.temp.x7:x;d:1!`sym xcols update sym:esym {sv[`]x,y}' ex from select ex:.enum.hsexmap `$market_no,esym:`$stock_code,name:`$stock_name,secclass:`$target_type,multiplier:multiple,date1:"D"$string last_trade_date,settledate:"D"$string exercise_date,isin:`$optcontract_id,putcall:`$option_type,strikepx:exercise_price,optexec:(`1`2`3!`E`A`B) `$apply_style,tradetype:`$contract_version,tradephase:`$compact_status from x[`res;1];.db.QX:.db.QX uj d;}; /optqry

.upd[`31001]:{[x].temp.x11:x;.temp.P,:1!select from (select sym:(`$stock_code) {sv[`]x,y}'.enum.hsexmap `$market_no,lqty:current_amount,sqty:0f from .temp.x11[`res;1]) where lqty>0;.temp.nQPack+:1;if[(not null x`src)&(.temp.nQPack>=2);pubmx[x`src;`PosUpdate;.conf.me;string x`oid;-8!.temp.P]];};
.upd[`31003]:{[x].temp.x12:x;if[1<count[.temp.x12[`res]];.temp.P,:(1!select from (select sym:(`$stock_code) {sv[`]x,y}'.enum.hsexmap `$market_no,lqty:current_amount,sqty:0f from .temp.x12[`res;1] where `1=`$position_flag) where lqty>0) uj (1!select from (select sym:(`$stock_code) {sv[`]x,y}'.enum.hsexmap `$market_no,lqty:0f,sqty:neg current_amount from .temp.x12[`res;1] where `2=`$position_flag) where sqty<0)];.temp.nQPack+:1;if[(not null x`src)&(.temp.nQPack>=2);pubmx[x`src;`PosUpdate;.conf.me;string x`oid;-8!.temp.P]];};
.upd[`31004]:{[x].temp.x13:x;};
.upd[`30003]:{[x].temp.x14:x;};

\
connHS[`;`];
r:callsync[10001;`operator_no`password`mac_address`op_station`ip_address`authorization_id!(.conf.ufx.user;.conf.ufx.pass;.conf.ufx.macaddr;.conf.ufx.devicesn;.conf.ufx.ipaddr;.conf.ufx.licno)];
r:callsync[91001;`user_token`account_code`combi_no`market_no`stock_code`entrust_direction`price_type`entrust_price`entrust_amount!(.ctrl.ufx.token;`19;`19_000;"2";`000408;"1";"0";7.98;100i)]




\




 
rejcxl:{[k]if[null w:O[k;`clt];:()];smkx[w;`CxlRej;`id`reason`text!O[k;`ctlid`reason`text]];}; / 

connHS:{[x;y]c:connt2[(`t2sdk`servers;`t2sdk`license_no;`t2sdk`lang;`t2sdk`send_queue_size;`safe`safe_level;`)!(y;SysOpt`GWLICNO;`1033;`1000;`none;0b);1000i*$[`SYNC~SysOpt`MODE;1i;-1i]];if[c<>0;WHO[x;`h`status`lostseq]:(-1;`Disconnected;c);:()];WHO[x;`h`isvr`proto`hbint`hbsent`status`conntime]:(0W;1b;`hst2;60;.z.P;$[`SYNC~SysOpt`MODE;`Connected;`Connecting];.z.P);smkx[`;`Login;()!()];}; /license_file`$"/fat/ZGCLJY-HSDZ-UFX-0000_3rd.dat"!;`safe`client_id;`safe`comm_pwd!SysOpt`GWCLT;encodepwd[SysOpt`GWPASS;0];




\

SysOpt[`MODE`GWNAME`GWADDR`GWCLT`GWPASS`GWLICNO`PUSHNAME`PUSHADDR`CLTMACADDRESS`CLTSTATION`CLTIP]:(
	`ASYNC;
	`HST2;
	`$CmdOpt`gwaddr;
	`$CmdOpt`gwclt;
	CmdOpt`gwpass;
	`$CmdOpt`gwlicno;
	`HST2Sub;
	`$CmdOpt`pushaddr;
	`$CmdOpt`cltmacaddress;
	`$CmdOpt`cltstation;
	`$CmdOpt`cltip	
	); 

hsfunc[30003;`src`aid`oid`req!(`;`;`;(enlist `user_token)!enlist string WHO[SysOpt`GWNAME;`selfaltid])] /组合查询
hsfunc[35001;`src`aid`oid`req!(`;`;`;`user_token`account_code`combi_no!(string WHO[SysOpt`GWNAME;`selfaltid];`720304;`7204_000))] /组合持仓查询
hsfunc[35004;`src`aid`oid`req!(`;`;`;`user_token`account_code`combi_no!(string WHO[SysOpt`GWNAME;`selfaltid];`720304;`7204_000))] /组合资金查询

hsfunc[35006;`src`aid`oid`req!(`;`;`;`user_token`account_code`combi_no!(string WHO[SysOpt`GWNAME;`selfaltid];"720304";"7204_000"))] /组合委托查询
hsfunc[35010;`src`aid`oid`req!(`;`;`;`user_token`account_code`combi_no!(string WHO[SysOpt`GWNAME;`selfaltid];`720304;`7204_000))] /组合成交查询


/login:{[x;y]callsync[200;`version`op_branch_no`op_station`op_entrust_way`branch_no`input_content`content_type`account_content`password!(`3.5;0;`127.0.0.1;7;0;1;0;x;y)]};


/r0:login["192000398";"111111"];
/r:callsync[100;`version`op_branch_no`op_station`op_entrust_way!(`3.5;0;`127.0.0.1;7)]
/r1:callsync[405;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`moneytype!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";0)]
/r2:callsync[403;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`query_mode!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";`;`;`;`;0;`;0)]
/r3:callsync[407;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`exchange_type`query_direction`request_num`position_str!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";`;`;0;`)]
/r4:callsync[401;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`sort_direction`locate_entrust_no`action_in!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";`;`;`;`;0;`;`;0;0)]
/r5:callsync[402;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`serial_no`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`query_mode!(`3.5;0;`127.0.0.1;7;0;0;"192000398";"111111";`;`;`;`;0;`;0)]
/r6:callsync[209;`version`op_branch_no`op_station`op_entrust_way`branch_no`input_content`content_type`account_content!(`3.5;0;`127.0.0.1;7;0;1;0;"192000398")]
/r7:callsync[302;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`stock_account`entrust_bs`exchange_type`stock_code`entrust_price`entrust_amount`bank_no`client_rights`entrust_prop!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";"A100000001";`1;`1;`600000;12.78;1000;0;`;0)]
/r8:callsync[302;`version`op_branch_no`op_station`op_entrust_way`branch_no`fund_account`password`stock_account`entrust_bs`exchange_type`stock_code`entrust_price`entrust_amount`bank_no`client_rights`entrust_prop!(`3.5;0;`127.0.0.1;7;0;"192000398";"111111";"1000000001";`1;`2;`002001;25.78;1000;0;`;0)]

\
r:callsync[8;`plugin_id`function_id!(`com.hundsun.fbase.f2core;100i)]


r:callsync[91001;`user_token`account_code`combi_no`market_no`stock_code`entrust_direction`price_type`entrust_price`entrust_amount!(`27949052160001;`100080;`1080001;enlist "1";`600000;enlist "1";"0";8.5;100i)]

UPD[`200]:{[x]z:x`aid;r:x`res;A[z;`login`fundbal`fundavl`name]:1b,"ffS"$r[0;`current_balance`enable_balance`client_name];smkx[x`src;`LoginAck;`aid`status!(z;`LoginOK)];smkx[`;`QrSeat;(enlist `aid)!enlist z];}; /Login
UPD[`407]:{[x]z:x`aid;r:x`res;A[z;`x0]:enlist select id:first `$stock_account,seat:first `$seat_no by ex:`$exchange_type from r;}; /QrSeat
UPD[`405]:{[x]z:x`aid;r:x`res;A[z;`fundbal`fundavl]:"FF"$r[0;`current_balance`enable_balance];smkx[x`src;`FundRpt;`aid`status`fundbal`fundavl`fundfrz`margin`mv`pnl`fundchg`risk`marginlong`marginshort`frzlong`frzshort`pnlopen`pnlclose!(z;`QrOK),A[z;`fundbal`fundavl`fundfrz`margin`mv`pnl`fundchg`risk`marginlong`marginshort`frzlong`frzshort`pnlopen`pnlclose]];}; /QrFund

UPD[`401]:{[x]k:x`oid;R401::r:x`res;if[null k;:()];sno:`$r[0;`entrust_no];if[sno<>O[k;`orderid];lwarn[`SnoUnequal;(k;O[k;`orderid];sno)]];s:hsstatusmap first r[0;`entrust_status];d:0f^"F"$r[0][`business_amount`withdraw_amount`business_price];os:O[k;`status`cancelstatus`cumqty];$[s~.enum`PENDING_CANCEL;O[k;`cancelstatus]:s;s~.enum`CANCELED;O[k;`status`cancelstatus]:s;O[k;`status]:s];amt:d[2]*d[0];lqty:0f^d[0]-O[k;`cumqty];O[k;`reporttime`cumqty`cancelqty`leavesqty`avgpx`lastshares`lastpx`cumamt]:(.z.P;d[0];d[1];O[k;`qty]-sum d[0 1];d[2];lqty;(amt-0f^prd O[k;`cumqty`avgpx])%lqty;amt);if[0=O[k;`leavesqty];O[k;`finished]:1b];if[not os~O[k;`status`cancelstatus`cumqty];execrpt[k;()]];}; /QueryOrder
UPD[`402]:{[x]y:x`aid;R402::r:x`res;}; /QueryMatch
UPD[`403]:{[x]y:x`aid;R403::r:x`res;if[1>count r;:()];smkx[x`src;`PosRpt;`aid`data!(y;select fsym:(`$stock_code) {[x;y]se2fs x,y}' (hsexmap `$exchange_type),qty:"F"$current_amount,avlqty:"F"$enable_amount from r)];}; /QueryPos

UPD[`304]:{k:x`oid;if[null k;:()];r:x`res;O[k;`corderid]:`$r[0;`entrust_no];}; /CancelOrder
UPD[`302]:{[x]k:x`oid;r:x`res;O[k;`status`orderid]:(.enum`NEW;`$r[0;`entrust_no]);}; /NewOrderSingle

UPD[`Login]:{[x]y:x`aid;A[y;`branch`account`pwd]:x`branch`acc`pwd;hsfunc[200;`src`aid`req!(x`who;y;())];}; 
UPD[`QrSeat]:{[x]hsfunc[407;`src`aid`req!(x`who;x`aid;`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`query_mode!(`;`;`;`;0;`;0))];};
UPD[`QrFund]:{[x]hsfunc[405;`src`aid`req!(x`who;x`aid;(enlist `moneytype)!enlist 0)];};

UPD[`QueryOrder]:{[x]k:exec first id from O where cltid=x`id;if[null k;:()];queryord[k];};

UPD[`NewOrderSingle]:{[x]y:x`aid;k:newid[];x[`qty`price]:`float$x`qty`price;O[k;`createtime`status`cumqty`cancelqty`avgpx`lastshares`avgpx`account`clt`cltid`fsym`side`posefct`qty`leavesqty`price]:(.z.P;.enum`PENDING_NEW;0f;0f;0f;0f;0f),x`aid`who`id`fsym`side`posefct`qty`qty`price;ex:ex2hs fs2e x`fsym;hsfunc[302;`src`aid`oid`req!(x`who;y;k;`stock_account`entrust_bs`exchange_type`stock_code`entrust_price`entrust_amount`bank_no`client_rights`entrust_prop!(A[y;`x0][0;ex;`id];side2hs x`side;ex;fs2s x`fsym;x`price;x`qty;0;`;0))];execrpt[k;()];}; 

UPD[`CancelOrder]:{[x]k:exec first id from O where cltid=x`id;if[(null k)|(null O[k;`orderid]);:()];y:O[k;`account];O[k;`cancelstatus]:.enum`PENDING_CANCEL;execrpt[k;()];hsfunc[304;`src`aid`oid`req!(x`who;y;k;`entrust_no`batch_flag!(O[k;`orderid];0))];};

UPD[`QueryAllOrder]:{[x]hsfunc[401;`src`aid`oid`req!(x`who;x`aid;`;`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`sort_direction`locate_entrust_no`action_in!(`;`;`;`;0;`;`;`;0))];};
UPD[`QueryMatch]:{[x]hsfunc[402;`src`aid`oid`req!(x`who;x`aid;`;(`serial_no`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`query_mode)!(`;`;`;`;`;0;`;0))];};
UPD[`QueryPos]:{[x]hsfunc[403;`src`aid`oid`req!(x`who;x`aid;`;(`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`query_mode)!(`;`;`;`;0;`;0))];};


queryord:{[k]y:O[k;`account];if[null O[k;`orderid];:()];hsfunc[401;`src`aid`oid`req!(O[k;`clt];O[k;`account];k;`exchange_type`stock_account`stock_code`query_direction`request_num`position_str`sort_direction`locate_entrust_no`action_in!(`;`;`;`;1;`;`;O[k;`orderid];0))];};

execrpt:{[k]if[null w:O[k;`clt];:()];smkx[w;`ExecRpt;`aid`id`cid`orderid`corderid`status`cancelstatus`suspend`cumqty`avgpx`lastshares`lastpx`cancelqty`leavesqty!O[k;`account`cltid`cltcid`orderid`corderid`status`cancelstatus`suspend`cumqty`avgpx`lastshares`lastpx`cancelqty`leavesqty]];};
