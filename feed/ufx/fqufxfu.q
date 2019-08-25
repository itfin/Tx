/恒生柜台交易接口程序(T2SDK)

.module.fqufxfu:2019.06.05;

txload "core/fqbase";

`initt2`freet2`connt2`connt2sub`t2call`subcall`topiclist`hsdc_encrypt`hsdc_getsysteminfo`hsdc_getdetailerror`hsdc_version`t2addr`t2mac {x set `extfeufx 2: (x;y)}' 1 1 2 3 3 4 1 2 1 1 1 1 1; 

.enum.hsqhexmap:`F1`F2`F3`F4`F5!`XZCE`XDCE`XSGE`CCFX`XINE;.enum.ex2hs:mirror .enum.hsqhexmap;
callsync:t2call[;;0i];callasync:t2call[;;1i];

.ctrl.ufx:.enum.nulldict;
.ctrl.ufx[`subtime`updtime]:0Np;
.ctrl.tcpconn:.enum.nulldict;
.ctrl.tcpconn[.conf.ufx.t2name]:.enum.nulldict;
.ctrl.tcpconn[.conf.ufx.subname]:.enum.nulldict;

\d .temp
QREF:.QUEUE:C:L12:L2:L1:L:();N:0;
MSG:([id:`int$()]funcid:`symbol$();issuetype:`symbol$();senttime:`timestamp$();recvtime:`timestamp$();src:`symbol$();req:();sentfill:`boolean$();sentcode:`int$();sentspan:`timespan$();senttry:`int$();msgid:();corrid:();peertime:`datetime$();recvfill:`boolean$();recvcode:`int$();recvspan:`timespan$();recvtry:`int$();ans:();src:`symbol$();oid:`symbol$();internal:`boolean$()); /ufx Msg
\d .
onhst2:{[x].temp.L,:(enlist .z.T),/:x;{.upd[x[0]][x[1]]} each x;};

.init.fqufxfu:{[x].ctrl.ufx.Run:initt2[];}
.exit.fqufxfu:{[x]freet2[];};

.disp.fqufxfu:{.ctrl.ufx};

connHS:{[x;y]c:connt2[(`t2sdk`servers;`t2sdk`license_file;`t2sdk`if_error_log;`t2sdk`logdir;`t2sdk`if_sendRecv_log;`t2sdk`writedata;`t2sdk`lang;`t2sdk`send_queue_size;`safe`safe_level;`)!(.conf.ufx.servers;.conf.ufx.licfile;.conf.ufx.errlog;.conf.ufx.logdir;.conf.ufx.msglog;.conf.ufx.dumpmsg;`1033;`1000;`none;0b);1000i*$[`SYNC~.conf.ufx.mode;1i;-1i]];if[c<>0;.ctrl.tcpconn[.conf.ufx.t2name]:`h`status`lostseq!(-1;`Disconnected;c);:()];.ctrl.tcpconn[.conf.ufx.t2name;`h`isvr`proto`hbint`hbsent`status`conntime]:(0W;1b;`ufx;.conf.ufx.hbint;.z.P;$[`SYNC~.conf.ufx.mode;`Connected;`Connecting];.z.P);};  /.conf.ufx.licno;

connHSsub:{[x;y]c:connt2sub[(`t2sdk`servers;`t2sdk`license_file;`t2sdk`if_error_log;`t2sdk`logdir;`t2sdk`if_sendRecv_log;`t2sdk`writedata;`t2sdk`lang;`t2sdk`send_queue_size;`safe`safe_level;`mc`client_name;`subcribe`biz_name;`subcribe`topic_name;`subcribe`is_rebuilt;`subcribe`is_replace;`)!(.conf.ufx.subservers;.conf.ufx.licfile;.conf.ufx.errlog;.conf.ufx.logdir;.conf.ufx.msglog;.conf.ufx.dumpmsg;`1033;`1000;`none;.conf.ufx.subuser;.conf.ufx.subuser;.conf.ufx.topic;`false;`false;0b);`login_operator_no`operator_no`password!(.conf.ufx.user;.conf.ufx.user;.conf.ufx.pass);1000i];if[c<>0;.ctrl.tcpconn[.conf.ufx.subname]:`h`status`lostseq!(-1;`Disconnected;c);:()];.ctrl.tcpconn[.conf.ufx.subname;`h`isvr`proto`hbint`hbsent`status`conntime]:(0W;1b;`ufx;.conf.ufx.hbint;.z.P;`Connected;.z.P);}; /`t2sdk`license_no; .conf.ufx.licno;

/api msg
qrysess:{[]:();hsfunc[331480i;`src`oid`req!(`;`;`fund_account`password`password_type!(.conf.ufx.user;.conf.ufx.pass;`2))];};
qryauth:{[]hsfunc[331481i;`src`oid`req!(`;`;`fund_account`app_id`session_id`encrypted_session_id!(.conf.ufx.user;.conf.ufx.appid;.ctrl.ufx.sessionid;hsdc_encrypt[.conf.ufx.authcode;.ctrl.ufx.sessionid]))];}; 
sendinfo:{[]hsfunc[331482i;`src`oid`req!(`;`;`fund_account`app_id`session_id`app_abnormal_type`app_sys_info`app_sys_info_integrity!(.conf.ufx.user;.conf.ufx.appid;.ctrl.ufx.sessionid;"0"),hsdc_getsysteminfo[])];};

qryqx:{[].ctrl.ufx.qryqx:0b;.temp.L1:();.temp.N:0;hsfunc[330851i;`src`oid`req!(`;`;`user_token`fund_account`request_num!(.ctrl.ufx.token;.conf.ufx.user;10000i))];};

subsym:{[x]subfunc[620001i;33100i;`src`req!(`;(`branch_no`fund_account`op_branch_no`op_entrust_way`op_station`issue_type`futu_code)!(.conf.ufx.branch;.conf.ufx.user;.conf.ufx.branch;`7;.conf.ufx.disksn;33100i;x))];} /[订阅单品种] `client_id`password`user_token!.conf.ufx.user;.conf.ufx.pass;.ctrl.ufx.token;

subspsym:{[x]subfunc[620001i;33102i;`src`req!(`;(`branch_no`fund_account`op_branch_no`op_entrust_way`op_station`issue_type`arbit_code)!(.conf.ufx.branch;.conf.ufx.user;.conf.ufx.branch;`7;.conf.ufx.disksn;33102i;x))];};

subqx:{[].ctrl.ufx[`subqx`subtime]:(1b;.z.P);subsym each $[count .conf.subprdlist;exec esym from .db.QX where settledate>=.z.D,product in .conf.subprdlist;exec esym from .db.QX where settledate>=.z.D];}; /订阅全市场

subhb:{[x]subfunc[620000i;12i;`src`req!(`;`branch_no`fund_account!(.conf.ufx.branch;.conf.ufx.user))];};

doqryqx:{[]if[(not 1b~.ctrl.ufx`login)|(0b~.ctrl.ufx`qryqx)|(1b~.ctrl.ufx`qryqx);:()];qryqx[];};
dosubqx:{[]if[(not 1b~.ctrl.ufx`qryqx)|1b~.ctrl.ufx`subqx;:()];subqx[];};

trysub:{[x;y]if[(not any .z.T within/:.conf.subtimerange)|not `Connected~.ctrl.tcpconn[`t2;`status];:()];if[(.z.P>.conf.trysubfreq+.ctrl.ufx.subtime)|.z.P>.conf.updtmout+.ctrl.ufx.updtime;subqx[]];1b};

/fq msg
errcode:{[r]z:r[0;0;`ErrorCode];$[10h=type z;"I"$z;z]}; /恒生业务消息的错误码字段,从第一个结果集的第一行提取,注意不同业务消息的类型不统一 
errmsg:{[r]r[0;0;`ErrorMsg]};

.upd.Hello:{[x]subfunc[620000i;12i;`src`req!(`;(enlist `user_token)!enlist .ctrl.ufx.token)];}; /if[1b~.ctrl.ufx[`subqx];subqx[]];:(); /hsfunc[620000;`src`req!(`;(enlist `user_token)!enlist .ctrl.ufx.token)];
.upd.Login:{[x]if[not 1b~.ctrl.ufx.canlogin;:()];hsfunc[331100;`src`req!(`;`op_branch_no`op_entrust_way`op_station`password`input_content`account_content`content_type`terminal_version`client_ip`client_mac!(.conf.ufx.branch;`7;.conf.ufx.disksn;.conf.ufx.pass;`1;.conf.ufx.user;`0;`Tx;.conf.ufx.ipaddr;.conf.ufx.macaddr))];};

.upd.OnConnect:{.ctrl.tcpconn[$[x;`sub;`t2];`status`conntime]:(`Connected;.z.P);qrysess[];};
.upd.OnSafeConnect:{};
.upd.OnRegister:{.ctrl.ufx[`Registered]:1b;};
.upd.OnClose:{.ctrl.tcpconn[$[x;`sub;`t2];`h`status`disctime]:(-1;`Disconnected;.z.P);.ctrl.ufx[`qryqx`subqx]:0b;};

.upd.OnReceivedBiz:{[x]k:x[0];y:x[1];r:x[2];if[0=k;.upd.OnReceivedBizMsg[x];:()];.temp.MSG[k;`ans`recvtime]:(enlist r;now[]);if[0h=type r;.upd[.temp.MSG[k;`funcid];`oid`res!(.temp.MSG[k;`oid];r)];if[not errcode[r] in 0 0N;lwarn[`HST2Res;(x;r)]]];};

.upd.OnReceivedBizMsg:{[x].temp.x4:x;k:x[0];y:x[1];r:x[2];if[r~();:()];.temp.L2,:enlist r;z:r[0];if[98h<>type z;:()];if[(not `QH~ first cols z)|0=count z;:()];.ctrl.ufx.updtime:.z.P;($[z[0;`QH] like "SP*";on_spquote;on_quote])[raze value flip z];};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[`quote;.temp.QUEUE];.temp.QUEUE:()};
fix0w:{[x]?[1e300<abs[x];0n;x]};

.upd.RDUpdate:{[x]if[`ufx<>x`ref;:()];.db.QX:.db.QX uj get `$x`msg;};

on_quote:{[x]d:{[x]`quote_type`quote_length`update_time`quote_index`futu_exch_type`futu_product_type`futu_code`pre_square_price`pre_close_price`pre_bear_amount`pre_delta`futu_open_price`futu_last_price`high_buy_price`high_buy_amount`low_sell_price`low_sell_amount`futu_high_price`futu_low_price`uplimited_price`downlimited_price`average_price`change_direction`business_amount`bear_amount`business_balance`futu_close_price`square_price`curr_date`curr_delta`buy_price2`buy_amount2`buy_price3`buy_amount3`buy_price4`buy_amount4`buy_price5`buy_amount5`sale_price2`sale_amount2`sale_price3`sale_amount3`sale_price4`sale_amount4`sale_price5`sale_amount5!("SJTJSSS",39#"F")$'vs["\001";x]} each x;if[not `fqopendate in key .db;.db.fqopendate:0Nd];if[.db.fqopendate<d0:.z.D;pubm[`ALL;`MarketOpen;.conf.me;string d0];.db.fqopendate:d0];d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from select sym:futu_code {sv[`] x,y}' .enum.hsqhexmap futu_exch_type,time:update_time,price:fix0w futu_last_price,cumqty:fix0w business_amount,vwap:fix0w business_balance%business_amount,high:fix0w futu_high_price,low:fix0w futu_low_price,o5px:fix0w sale_price5,o5sz:fix0w sale_amount5,o4px:fix0w sale_price4,o4sz:fix0w sale_amount4,o3px:fix0w sale_price3,o3sz:fix0w sale_amount3,o2px:fix0w sale_price2,o2sz:fix0w sale_amount2,ask:fix0w low_sell_price,asize:fix0w low_sell_amount,bid:fix0w high_buy_price,bsize:fix0w high_buy_amount,b2px:fix0w buy_price2,b2sz:fix0w buy_amount2,b3px:fix0w buy_price3,b3sz:fix0w buy_amount3,b4px:fix0w buy_price4,b4sz:fix0w buy_amount4,b5px:fix0w buy_price5,b5sz:fix0w buy_amount5,openint:average_price,settlepx:fix0w square_price,open:fix0w futu_open_price,pc:fix0w pre_close_price,sup:fix0w uplimited_price,inf:fix0w downlimited_price,recvtime:.z.P,exlocaltime:.z.P from d;d:delete from d where 0>cumqty;if[count d;if[.conf.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:`timestamp$d0+time,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$(),quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[`quote;d2]]];};  

on_spquote:{[x].temp.x1:x;d:{[x]`arbit_code`weave_type`first_code`second_code`x1`futu_buy_price`buy_amount`total_buy_amount`futu_sell_price`sell_amount`total_sale_amount`futu_high_price`futu_low_price`uplimited_price`downlimited_price`futu_exch_type`x2`x3!("SCSS",(11#"F"),"SSS")$'vs["\001"] x} each x;d:update virtualtime:0Np,isnormalsession:time within 08:00 16:00 from select sym:arbit_code {sv[`] x,y}' .enum.hsqhexmap futu_exch_type,time:.z.T,price:0n,cumqty:0n,vwap:0n,high:fix0w futu_high_price,low:fix0w futu_low_price,o5px:0n,o5sz:0n,o4px:0n,o4sz:0n,o3px:0n,o3sz:0n,o2px:0n,o2sz:0n,ask:fix0w futu_sell_price,asize:fix0w sell_amount,bid:fix0w futu_buy_price,bsize:fix0w buy_amount,b2px:0n,b2sz:0n,b3px:0n,b3sz:0n,b4px:0n,b4sz:0n,b5px:0n,b5sz:0n,openint:0n,settlepx:0n,open:0n,pc:0n,sup:fix0w uplimited_price,inf:fix0w downlimited_price,recvtime:.z.P,exlocaltime:.z.P from d;if[count d;if[.conf.debug;.temp.L12,:d];d1:select sym,pc,open,sup,inf from d;if[n:count d2:d1 except .temp.QREF;pub[`quoteref;update refopt:n#enlist"" from d2];.temp.QREF,:d2];d:delete open,pc,sup,inf from d;n:count d;d2:select sym,bid,ask,bsize,asize,price,high,low,vwap,cumqty,openint,settlepx,mode:`,extime:.z.P,bidQ:n#enlist `float$(),askQ:n#enlist `float$(),bsizeQ:n#enlist `float$(),asizeQ:n#enlist `float$(),quoopt:n#enlist "" from d;$[1b~.conf.batchpub;enqueue[d2];pub[`quote;d2]]];};

.timer.feufx:{[x]s:.ctrl.tcpconn[.conf.ufx.t2name];if[0>=h:ifill s`h;connHS[`;`]];trysub[`;`];:();if[0<h;if[(1b~.ctrl.ufx[`Registered])&(not 1b~.ctrl.ufx[`login])&not 1b~.ctrl.ufx[`loginfail];.ctrl.ufx[`loginfail]:1b;.upd.Login[]];if[((s[`hbsent]+`timespan$`second$s[`hbint])<x)&1b~.ctrl.ufx[`login];.upd.Hello[()];.ctrl.tcpconn[.conf.ufx.t2name;`hbsent]:now[]]];s:.ctrl.tcpconn[.conf.ufx.subname];doqryqx[];dosubqx[];}; /if[0>=h:ifill s`h;connHSsub[`;`]]; 

hsfunc:{[x;y].temp.X:(x;y);fid:`$string x;req:y`req;$[`SYNC~.conf.ufx.mode;[k:newseq[];.temp.MSG[k;`src`funcid`req`oid`senttime]:(y`src;fid;enlist req;y`oid;now[]);.temp.r:r:callsync[x;req];.temp.MSG[k;`ans`recvtime]:(enlist r;now[]);if[(0h=type r)&(0<count r);.upd[fid][`oid`res!(y`oid;r)]];if[not errcode[r] in 0 0N;lwarn[`UfxErr;(x;k;r)]]];[r:callasync[x;req];if[r>0;.temp.MSG[r;`src`funcid`req`oid`senttime]:(y`src;fid;enlist req;y`oid;now[])]]];if[r~-1;.ctrl.tcpconn[.conf.ufx.t2name;`h`status]:(-1;`Disconnected)];}; /[funcid;req]

subfunc:{[x;z;y].temp.X:(x;y;z);fid:`$string x;req:y`req;it:`$string z;$[`SYNC~.conf.ufx.mode;[k:newseq[];.temp.MSG[k;`src`funcid`req`issuetype`oid`senttime]:(y`src;fid;it;enlist req;y`oid;now[]);.temp.r:r:subcall[x;req;0i;z];.temp.MSG[k;`ans`recvtime]:(enlist r;now[]);if[(0h=type r)&(0<count r);.upd[fid][`oid`res!(y`oid;r)]];if[not errcode[r] in 0 0N;lwarn[`UfxErr;(x;k;r)]]];[r:subcall[x;req;1i;z];if[r>0;.temp.MSG[r;`src`funcid`issuetype`req`oid`senttime]:(y`src;fid;it;enlist req;y`oid;now[])]]];if[r~-1;.ctrl.tcpconn[.conf.ufx.t2name;`h`status]:(-1;`Disconnected)];}; /[funcid;issuetype;req]

/hs msg
.upd[`620000]:{[x].temp.x9:x;r:x`res;if[not (ec:errcode[r]) in 0 0N;.ctrl.ufx[`token`login`loginfail`errcode`errmsg`errtime]:(`;0b;0b;ec;errmsg[r];.z.P);:()];.ctrl.ufx.hbrecvtime:.z.P;}; /Heartbeat

.upd[`331100]:{[x].temp.x2:x;r:x`res;if[not ec:errcode[r] in 0 0N;.ctrl.ufx[`login`loginfail`errcode`errmsg]:01b,ec,errmsg[r];:()];.ctrl.ufx[`token`login`loginfail`logintime]:(`$raze r[0;0;`user_token];1b;0b;now[]);}; /Login

.upd[`330851]:{[x].temp.x3:x;r:x`res;.temp.N+:1;d:r[0];$[count d;[.temp.L1,:d;pos:exec last position_str from d;d:1!`sym xcols update sym:esym {sv[`]x,y}' ex from select ex:.enum.hsqhexmap `$futu_exch_type,esym:`$futu_code,name:`$futu_name,product:`$except[;"0"] each futucode_type,multiplier:`float$amount_per_hand,pxunit:futu_price_step,assetclass:("12"!`Future`Option) futu_product_type,strikepx:fopt_strike_price,putcall:("012"!``C`P) fopt_type,underlying:`$underlying_code,settledate:"D"$string expire_date from d;.db.QX:.db.QX uj d;if[10>=.temp.N;hsfunc[330851i;`src`oid`req!(`;`;`user_token`fund_account`request_num`position_str!(.ctrl.ufx.token;.conf.ufx.user;10000i;`$pos))]]];[.ctrl.ufx.qryqx:1b;(path:` sv .conf.tempdb,.conf.me,`RD) set 1!select sym,ex,esym,name,product,multiplier,pxunit,assetclass,strikepx,putcall,underlying,settledate from .db.QX;pubm[`ALL;`RDUpdate;`ufxfu;string path];]];}; /qryqx

.upd[`620001]:{[x].temp.x7:x;}; /Sub

.upd[`331480]:{[x].temp.x11:x;.ctrl.ufx.sessionid:x[`res;0;0;`session_id];qryauth[];}; /Sess
.upd[`331481]:{[x].temp.x12:x;sendinfo[];}; /Auth
.upd[`331482]:{[x].temp.x13:x;.ctrl.ufx.canlogin:1b;}; /Info

