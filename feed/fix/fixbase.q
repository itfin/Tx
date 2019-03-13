.module.fixbase:2019.01.30;

txload "feed/socket";

`fixcrc`initfixdict`freefixdict`decodefix`initfastdict`freefastdict`decodefast {x set `extfix 2:(x;y);}' 7#1;

fixfree:{[]freefixdict[];if[.fix.FixOpt`UseFast;freefastdict[]];};
\d .temp
MSG:([]rtime:`timestamp$();mtime:`timestamp$();src:`symbol$();dst:`symbol$();seq:`long$();mtype:`symbol$();m:()); /FIX消息表
\d .
lmfix:{[t;y;z;w;u;v].temp.MSG,:enlist(t;.z.P;y;z;w;u;enlist v);}; /trace msg [timestamp;src;dst;seq;mtype;msg]
\d .fix
FIX:()!();
SOH:"\001";DEL:"=";
SESSCTRLMSG:`A`5`0`1`2`4;
FixTypeMap:`INT`FLOAT`CHAR`PRICE`BOOLEAN`QTY`AMT!"IFCFCFF"; //fix数据类型到q语言数据类型的映射 
StatusPrecedenceMap:`PENDING_CANCEL`PENDING_REPLACE`DONE_FOR_DAY`CALCULATED`FILLED`STOPPED`SUSPENDED`CANCELED`EXPIRED`PARTIALLY_FILLED`REPLACED`NEW`REJECTED`PENDING_NEW`ACCEPTED_FOR_BIDDING`!12 11 10 9 8 7 6 5 5 4 3 2 2 2 1 0;  //委托状态优先级映射
MarketPhase:`BEFORE_OPEN`OPEN_AUCTION`OPEN_AM`CLOSE_AM`OPEN_PM`CLOSE_AUCTION`MARKET_CLOSED`TEMP_CLOSE`TEMP_AUCTION; //市场时段枚举
\d .
fieldqtype:{{$[null x;`;x]} .fix.FixTypeMap[.fix.Fields[x;`ftype]]};  //提取指定字段的q语言类型
fieldname:{[x]y:.fix.Fields[x;`name];$[null y;`$string x;y]};           //提取指定字段的符号名 
subdict:{[x]y:fieldqtype[x];(!/) value exec id:y$string val,name:desp from .fix.Enums where fid=x}; //提取指定字段的枚举值正映射

initmaps:{[]
	map2vars[`.fix] .fix.SideMap:mirror .fix.SideD:subdict[54];                                  //委托方向正逆映射
	map2vars[`.fix] .fix.TimeInForceMap:mirror .fix.TimeInForceD:subdict[59];                    //委托有效期正逆映射
	map2vars[`.fix] .fix.OrdTypeMap:mirror .fix.OrdTypeD:subdict[40];                            //委托类型正逆映射
	map2vars[`.fix] .fix.OrdStatusMap:mirror .fix.OrdStatusD:subdict[39];                        //委托状态正逆映射
	map2vars[`.fix] .fix.ExecTypeMap:mirror .fix.ExecTypeD:subdict[150];                         //执行报告类别正逆映射
	map2vars[`.fix] .fix.ExecTransTypeMap:mirror .fix.ExecTransTypeD::subdict[20];                //执行报告事务类别正逆映射
	map2vars[`.fix] .fix.HandlInstMap:mirror .fix.HandlInstD:subdict[21];                        //委托路由方式正逆映射
	map2vars[`.fix] .fix.OrdRejReasonMap:mirror .fix.OrdRejReasonD:subdict[103];                 //委托拒绝原因正逆映射
	map2vars[`.fix] .fix.CxlRejReasonMap:mirror .fix.CxlRejReasonD:subdict[102];                 //撤单拒绝原因正逆映射
	map2vars[`.fix] .fix.DKReasonMap:mirror .fix.BusinessRejectReasonD:subdict[127];             //DK原因正逆映射
	map2vars[`.fix] .fix.ExecInstMap:mirror .fix.ExecInstD:subdict[18];                          //委托执行方式正逆映射
	map2vars[`.fix] .fix.SessionRejectReasonMap:mirror .fix.SessionRejectReasonD:subdict[373];   //会话消息拒绝原因正逆映射
	map2vars[`.fix] .fix.BusinessRejectReasonMap:mirror .fix.BusinessRejectReasonD:subdict[380]; //业务消息拒绝原因正逆映射
	};

.init.fix:{[x]system "d .fix";system"l ",1_"/" sv string .conf.fix[`fixdb`idiom];system "d .";
	map2vars[`.fix] .fix.FieldMap:(!/)value exec name,id from .fix.Fields;        //字段逆映射
	map2vars[`.fix] .fix.MessageMap:(!/)value exec name,id from .fix.Messages;    //消息类型逆映射
	initmaps[];
	initfixdict[];if[.fix.FixOpt`UseFast;initfastdict[]];
	.fix.RouterFieldMap:(.fix`OnBehalfOfCompID`DeliverToCompID`SenderSubID`TargetSubID`OnBehalfOfSubID`DeliverToSubID`SenderLocationID`TargetLocationID`OnBehalfOfLocationID`DeliverToLocationID)!.fix`DeliverToCompID`OnBehalfOfCompID`TargetSubID`SenderSubID`DeliverToSubID`OnBehalfOfSubID`TargetLocationID`SenderLocationID`DeliverToLocationID`OnBehalfOfLocationID;
     .ctrl.sessionmap:{.conf.fix.session[x;`selfid`peerid]!x} tkey .conf.fix.session;	
 };

realstatus:{[x]y:$[x 2;w:.fix[`SUSPENDED];" "];rs:{$[.fix.StatusPrecedenceMap[.fix.OrdStatus[x]]>=.fix.StatusPrecedenceMap[.fix.OrdStatus[y]];x;y]};rs[rs[x 0;x 1];y]}; //取执行状态与撤单状态与挂起状态中较大者为当前委托状态 

packmsg_simple:{[x]raze (key x) {[x;y]x:string x;y:raze string y;$[(0=count x)|(0=count y);"";x,.fix.DEL,y,.fix.SOH]}' (value x)};

packmsg:{[x]raze (key x) packfield' (value x)};
packfield:{[x;y]x:string x;y:$[0=count y;"";0>type y;$[(null y)|(y~.enum`NULL);"";packvalue y];packvalue y];$[(0=count x)|(0=count y);"";x,.fix.DEL,y]};
packvalue:{[x]$[not (type x) in 0 98h;(raze string x),.fix.SOH;(string count x),.fix.SOH,raze packmsg each x]};
 
smfixrseq:{[x;r;y;z;w]if[(not .ctrl.tcpconn[x;`status]~`Logon)&(not y in .fix`Logon`ExecutionReport`OrderCancelReject);lwarn[`SendFIXMsgNotLogon;(x;.ctrl.tcpconn[x;`status];y;z;w;r)];:()];t0:.z.P;u:(1+0j^.ctrl.tcpconn[x;`selfseq])^w;$[null w;.ctrl.tcpconn[x;`selfseq]:u;[z:((.fix`PossDupFlag`OrigSendingTime)!(`Y;utctime[])),z]];if[count r;z:r[0],z];m:{x,packmsg[(enlist .fix`CheckSum)!enlist fixcrc[x]]} {packmsg[(.fix`BeginString`BodyLength)!(x;count y)],y}[.fix.FixOpt`FixVersion] packmsg[(.fix`MsgType`SenderCompID`TargetCompID`MsgSeqNum`SendingTime)!(y;.conf.fix.session[x;`selfid];.conf.fix.session[x;`peerid];u;utctime[])],packmsg[z];r:smtcp[x;m];.ctrl.tcpconn[x;`selftime]:.z.P;lmfix[t0;.conf.fix.session[x;`selfid];.conf.fix.session[x;`peerid];u;y;z];r}; /[peerid;routetbl;msgtype;msghash;msgseq] 
smfixr:smfixrseq[;;;;0Nj];smfixseq:smfixrseq[;()];smfix:smfixseq[;;;0Nj];

trimmsg:{[x]x:(1+x?.fix.SOH)_x;i:x?.fix.SOH;h:i#x;x:(1+i)_x;n:"I"$last .fix.DEL vs h;n#x};

decodefix1:{[x]h:()!();while[count x;i:x?.fix.DEL;fi:"I"$i#x;x:(1+i)_x;ft:.fix.Fields[fi;`ftype];i:$[`DATA=ft;"I"$last value h;x?.fix.SOH];v:i#x;x:(1+i)_x;h,:(enlist fi)!enlist v];h};

decodefix2:{[x]h:();while[count x;i:x?.fix.DEL;fi:"I"$i#x;x:(1+i)_x;ft:.fix.Fields[fi;`ftype];i:$[`DATA=ft;"I"$last value h;x?.fix.SOH];v:i#x;x:(1+i)_x;h,:(enlist (fi;v))];h};

toutc:{{x[0 1 2 3 5 6 8 9],"-",11_x}string `datetime$x-`time$08:00}; /将本地时间转化为utc字符串
fromutc:{08:00+"Z"$string x}; /将utc字符串转化为本地时间
utctime:{toutc[.z.Z]};      /将当前时间格式化为FIX GMT时间戳字符串
vm:{[x]d:`f xkey select f,fname:.fix.Fields[;`name] each f,v,vname:.fix.Enums[;`desp] each (f,'{$[10h=abs (type x);`$x;`$string x]} each v) from flip `f`v!(key x;value x)}; //分解察看fix消息字符串
backroute:{[x]rk:(key .fix.RouterFieldMap) inter (key x);$[count rk;enlist .fix.RouterFieldMap[rk]!x[rk];()]}; //fix应答消息头路由信息[fixmsghash]

fixclose:{[x]if[0<h:.ctrl.tcpconn[x;`h];lwarn[`TCPCloseSockFixDisc;(x;h)];sockclose[h];.ctrl.tcpconn[x;`h`status`disctime`testtime`rbuf`sbuf]:(-1;`Disconnected;now[];now[];"";"")];};
fixdisc:{[x;y]smfix[x;`5;(enlist .fix`Text)!(enlist y)];lwarn[`FixDisc;(x;y)];.ctrl.tcpconn[x;`status`logouttime]:(`LogoutHalf;now[]);}; /logout&disconnect tcp
onsockconn:{[x]if[not x in tkey .conf.fix.session;:()];.ctrl.tcpconn[x;`status`selftime`peertime`logontime]:(`Connected;0Np;0Np;0Np);};

onsockmsg:{[x;y].temp.X0:(x;y);w:x`w;if[(9<=n:count b:.ctrl.tcpconn[w;`rbuf])&(y like "8=FIX.4.2*");lwarn[`FixBufferClear;(w;n;b)];.ctrl.tcpconn[w;`rbuf]:""];b:$[null w;"";.ctrl.tcpconn[w;`rbuf]],y;r:decodefix b;$[-6h~type n:r[0];[linfo[`FixMsgErr;(x;n;r[1];count r)];b:n _ b;r:r[2]];[b:""]];if[not null w;$[(9<=count b)&(not b like "8=FIX.4.2*");fixdisc[w;`FixMsgHeadMissing];.ctrl.tcpconn[w;`rbuf]:b]];.upd.FIX[x] each r;};

doseqreset:{[x]{[x;he]if[(not .ctrl.tcpconn[he;`status]~`Logon)|(`server~.conf.fix.session[he;`mode]);:()];if[(`date$.ctrl.tcpconn[he;`selftime])>=.z.D;:()];.ctrl.tcpconn[he;`status`selfseq`selftime]:(`LogonHalf;0j;0Np);smfix[he;`A;(.fix`EncryptMethod`HeartBtInt`ResetSeqNumFlag)!(0;.conf.fix.hbint;`Y)]}[x] each (tkey .conf.fix.session) inter (tkey .ctrl.tcpconn);};

dofixhb:{[x]{[x;he]if[not .ctrl.tcpconn[he;`status]~`Logon;:()];if[(`second$x)<(`second$.ctrl.tcpconn[he;`selftime])+00:00:01*.conf.fix.hbint;:()];smfix[he;`0;()!()]}[x] each (tkey .conf.fix.session) inter (tkey .ctrl.tcpconn);};

dologon:{[x]{[x;he]if[(`client<>.conf.fix.session[he;`mode])|(not .ctrl.tcpconn[he;`status]~`Connected);:()];.ctrl.tcpconn[he;`status]:`LogonHalf;$[((`date$x)<>`date$.ctrl.tcpconn[he;`peertime])|((`date$x)<>`date$.ctrl.tcpconn[he;`logontime]);[.ctrl.tcpconn[he;`selfseq`selftime]:(0j;0Np);smfix[he;`A;(.fix`EncryptMethod`HeartBtInt`ResetSeqNumFlag)!(0;.conf.fix.hbint;`Y)]];smfix[he;.fix`Logon;(.fix`EncryptMethod`HeartBtInt)!(0;.conf.fix.hbint)]]}[x] each (tkey .conf.fix.session) inter (tkey .ctrl.tcpconn);}; 

//
.exit.fix:{[x]fixfree[];linfo[`FixExit;(.conf.me;now[])];};

.timer.fix:{[x]doseqreset[];dofixhb[x];dologon[x];}; /日期更新则重置序列号
//
onfix:{[x;y;z;u].temp.X:(x;y;z;u);r:.[{.fix.FIX[x][y;z]};(x;y;z);`trap];($[`trap~r;lerr;ldebug])[`fix;(x;y;u;z)];};

.upd.FIX:{[s;m].temp.X1:(s;m);t0:.z.P;t:`$m[.fix`MsgType];sid:`$m[.fix`SenderCompID];tid:`$m[.fix`TargetCompID];u:`long$m[.fix`MsgSeqNum];pdf:1b~m[.fix`PossDupFlag];r:backroute[m];if[null sess:.ctrl.sessionmap tid,sid;lwarn[`UnknownFixSession;(s;m)];:()];if[0>.ctrl.tcpconn[sess;`h];.ctrl.tcpconn[sess;`h`status`conntime`ipaddr]:(s`h;`Connected;.z.P;s`a)];lmfix[t0;sid;tid;u;t;m];v:0j^.ctrl.tcpconn[sess;`peerseq];if[(not .ctrl.tcpconn[sess;`status] in `Logon`LogoutHalf)&(t<>.fix`Logon);lwarn[`RecvNonLogonWhenLogout;(sess;.ctrl.tcpconn[sess;`status];t;u;pdf)];:()];$[u<>1j+v;$[((t=.fix`Logon)&((1b~m[.fix`ResetSeqNumFlag])|(v=0j)|((u<1j+v)&(.conf.fix.session[sess;`custom]=`hs))))|((t=.fix`SequenceReset)&(not pdf)|((t=.fix`Logout)&(.conf.fix.session[sess;`custom]=`hs)));();[if[not .ctrl.tcpconn[sess;`isgap];.ctrl.tcpconn[sess;`isgap]:1b;lwarn[`FixSeqError;(sess;t;`LastSeq;v;`MsgSeq;u;`PossDupFlag;pdf;$[u<1+v;$[pdf;`MsgResend;`SeqTooLow];`SeqGapMsgLost])]];if[(u<1+v)&not pdf;fixdisc[sess;`SeqTooLow];.ctrl.tcpconn[sess;`peertime]:0Np;:()];if[u>1+v;if[t in `A`2;onfix[t;sess;m;u]];if[not (null .ctrl.tcpconn[sess;`peerseq])&(.conf.fix.session[sess;`custom]=`hs);smfixr[sess;r;.fix`ResendRequest;(.fix`BeginSeqNo`EndSeqNo)!(1+v;0j)]]];:()]];if[1b~.ctrl.tcpconn[sess;`isgap];.ctrl.tcpconn[sess;`isgap]:0b;linfo[`FixSeqSync;(sess;u;v)]]];.ctrl.tcpconn[sess;`peerseq`peertime`pmsgtime]:(u;.z.P;("n"$08:00)+"p"$"Z"$m[.fix`SendingTime]);if[pdf&t in .fix.SESSCTRLMSG except `4;lwarn[`FixDupAdminMsg;(sess;t;m)]:()];$[(tid<>`$dtc)&(count dtc:m[.fix`DeliverToCompID]);[lwarn[`UnSupportRouterMsg;(sess;t;m)];smfixr[sess;r;.fix`Reject;(.fix`RefSeqNum`SessionRejectReason`Text)!(m[.fix`MsgSeqNum];.fix`VALUE_IS_INCORRECT;"Unsupported 3rd Routered Message!")]];not t in key .fix.Messages;[lwarn[`ErrorMsgType;(sess;t;m)];smfixr[sess;r;.fix`Reject;(.fix`RefSeqNum`SessionRejectReason`Text)!(m[.fix`MsgSeqNum];.fix`InvalidMsgType;"Error Message Type!")]];not t in key .fix.FIX;[lwarn[`UnSupportMsg;(sess;t;m)];smfixr[sess;r;.fix`BusinessMessageReject;(.fix`BusinessRejectReason`RefMsgType`Text`RefSeqNum)!(.fix`UNSUPPORTED_MESSAGE_TYPE;t;"Unsupported Message Type:",string t;m[.fix`MsgSeqNum])]];onfix[t;sess;m;u]];};

.fix.FIX[`A]:{[x;y].temp.X2:(x;y);rsflag:(1b~y[.fix`ResetSeqNumFlag])|(((1j=`long$y[.fix`MsgSeqNum])|(ntd[]>`date$.ctrl.tcpconn[x;`logontime]))&(.conf.fix.session[x;`custom]=`hs));r:(.fix`EncryptMethod`HeartBtInt`ResetSeqNumFlag)!(0^ifill y[.fix`EncryptMethod];y[.fix`HeartBtInt];$[1b~y[.fix`ResetSeqNumFlag];`Y;`N]);if[`server~.conf.fix.session[x;`mode];.ctrl.tcpconn[x;`selfseq`hbint]:($[rsflag;0j;.ctrl.tcpconn[x;`selfseq]];y[.fix`HeartBtInt]);smfixr[x;backroute[y];`A;r]];.ctrl.tcpconn[x;`status`logontime`testtime]:(`Logon;.z.P;0Np);}; /`Logon(admin) 

.fix.FIX[`5]:{[x;y]if[(count t:y[.fix`Text])&(.conf.fix.session[x;`custom]=`hs);if[t like "MsgSeqNum too low, expecting *";ls:"J"${x 4}" " vs t;if[`server~.conf.fix.session[x;`mode];.ctrl.tcpconn[x;`logontime`lostseq`selfseq]:(0Np;ls;ls-1)];lwarn[`FIXHS;(ls;.ctrl.tcpconn[x;`selfseq`peerseq`status])]]];$[.ctrl.tcpconn[x;`status]=`LogoutHalf;[fixclose[x]];.ctrl.tcpconn[x;`status]=`Logon;[smfixr[x;backroute[y];`5;()!()];.ctrl.tcpconn[x;`status`logouttime`selftime]:(`Logout;now[];0Np)];()];}; /Logout(admin) 

.fix.FIX[`0]:{[x;y];if[not null .ctrl.tcpconn[x;`testtime];.ctrl.tcpconn[x;`testtime]:0Np];}; /Heartbeat(admin)

.fix.FIX[`1]:{[x;y]smfixr[x;backroute[y];`0;(enlist .fix`TestReqID)!enlist y[.fix`TestReqID]];}; /TestRequest(admin)

.fix.FIX[`2]:{[x;y]sb:1j^`long$y[.fix`BeginSeqNo];se:(u:0j^.ctrl.tcpconn[x;`selfseq])^{$[x<=0;0n;x]}`long$y[.fix`EndSeqNo];d1:select seq,mtype,m from .temp.MSG where dst=x,seq within (sb,se),{not `Y~x[0][.fix`PossDupFlag]} each m;N:{0^1+last -1_where x>next x} exec seq from d1;d:`seq xasc N _d1;$[(sb<>exec first seq from d)|(se<>exec last seq from d);smfixseq[x;.fix`SequenceReset;(enlist .fix`NewSeqNo)!(enlist 1j+u);sb];[t:exec mtype in .fix.SESSCTRLMSG from d;{[x;d]y:d[0];z:y`mtype;w:y`seq;$[z in .fix.SESSCTRLMSG;smfixseq[x;`4;(.fix`GapFillFlag`NewSeqNo)!(`Y;1+(last d)`seq);w];smfixseq[x;z;first y`m;w]];}[x] each (distinct 0,where (not t)|not prev t) cut d]];}; /ResendRequest(admin)[for SESSCTRLMSG,use Sequence Reset-Gap Fill msg replace original msg]  

.fix.FIX[`3]:{[x;y]lwarn[`fix_recvReject;(x;y[.fix`RefSeqNum`RefTagID`RefMsgType`SessionRejectReason`Text])];}; /Reject(admin)

.fix.FIX[`4]:{[x;y]u:`long$y[.fix`NewSeqNo];if[not 1b~y[.fix`GapFillFlag];lwarn[`FixSeqResetReset;(x;.ctrl.tcpconn[x;`peerseq];u)]];$[u>0j^.ctrl.tcpconn[x;`peerseq];.ctrl.tcpconn[x;`peerseq]:u-1;fixdisc[x;`FixResetSeqTooLow]];}; /SequenceReset(admin)

.fix.FIX[`j]:{[x;y]lwarn[`fix_recv_BusinessRej;(x;y[.fix`RefMsgType`Text`BusinessRejectReason])];}; /BusinessMessageReject:写警报日志

.fix.FIX[`Q]:{[x;y]lwarn[`fix_recv_DK;(x;y[.fix`ExecID];`$("orderid:",(string y[.fix`OrderID]),",symbol:",(string y[.fix`Symbol]),",side:",(string y[.fix`Side]),",text:",(string y[.fix`Text]));`int$y[.fix`DKReason])];}; /DontKnowTrade:写警报日志

tracefixord:{[x]d:select mtime,src,dst,seq,mtype, first each m from .temp.MSG where mtype in `D`F`G`H`8`9,{y in {$[-11h=type x;x;`$x]} each x[0;.fix`ClOrdID`OrigClOrdID]}[;x]each m;{show "[****FIX****]",-3!x`mtype`seq`mtime`src`dst;show vm x`m;}each d;};