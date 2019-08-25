VERSION[`OGWPUSH]:"2016.03.16";

//runq std.q -p 9011 -P 15 -c 65 140 -g 1 -me OS_GWPUSH -debug 0 -code 'qload "ogwpush.q";init[];start_timer[];'

qload "oscomm.q";

//SysOpt[`QryPageNum`optId`optPwd`optMode`OptAcc`OptAccPwd`OptRegId`OptTrdPwd`StkAcc`StkAccPwd`StkRegId`StkTrdPwd`CltMAC`GWOS`BatchNum]:(500;`000898;`666666;`W1;`000000000899;`666666;`0000000898;`666666;`000000000898;`666666;`0000000898;`666666;`12345678;`OS_GW`::9010:guosen:guosen;1);

SysOpt[`QryPageNum`optId`optPwd`optMode`OptAcc`OptAccPwd`OptRegId`OptTrdPwd`StkAcc`StkAccPwd`StkRegId`StkTrdPwd`FutAcc`FutAccPwd`FutRegId`FutTrdPwd`CltMAC`GWOSID`GWOSADDR`BatchNum`AsyncMode]:(500;`00001^`$CmdOpt`optid;`666666^`$CmdOpt`optpwd;`W1^`$CmdOpt`optmode;`000000003001^`$CmdOpt`optacc;`666666^`$CmdOpt`optaccpwd;`0899024792^`$CmdOpt`optregid;`666666^`$CmdOpt`opttrdpwd;`000000002001^`$CmdOpt`stkacc;`666666^`$CmdOpt`stkaccpwd;`0899024792^`$CmdOpt`stkregid;`666666^`$CmdOpt`stktrdpwd;`000000002001^`$CmdOpt`futacc;`666666^`$CmdOpt`futaccpwd;`0899024792^`$CmdOpt`futregid;`666666^`$CmdOpt`futtrdpwd;`12345678;`$CmdOpt`gwosid;`$CmdOpt`gwosaddr;1;0^"I"$CmdOpt`asyncmode);

`initgwdp`freegwdp`callgwdp{x set `qgwdp 2:(x;y);}' 1 1 3;

SYSINIT[`OGWPUSH]:{[x]system "cd /q/l",$[.z.o=`l32;"32";"64"];initgwdp[];};
SYSEXIT[`OGWPUSH]:{[x]freegwdp[];};

L:();
LastTime:0Nt;

gwexmap:mirror exmap:"021356FSDZXY"!`XSHG`XSHG`XSHE`XSHE`XHKG`GFZR`CCFX`XSGE`XDCE`XZCE`XSHG`XSHE; 
gwsidemap:mirror sidemap:`B`S!.enum`BUY`SELL;
gwposefctmap:mirror posefctmap:`OPEN`CLOSE!.enum`OPEN`CLOSE;
gwotypemap:mirror otypemap:`LIMIT`ANY!.enum`LIMIT`MARKET;
statusmap:`00`01`02`03`04`05`06`07`08`09`10!.enum`NEW`NEW`FILLED`REJECTED`PENDING_CANCEL`CANCELED`PARTIALLY_FILLED`CANCELED`PENDING_CANCEL`CANCELED`REJECTED;
fstatusmap:`NEW`ALLTRD`P_TRD_Q`P_TRD_NQ`N_TRD_Q`N_TRD_NQ`CANCEL`DELETE_N`DELETE_S_I`DELETE_S_E`DELETE_F!.enum`NEW`FILLED`PARTIALLY_FILLED`PARTIALLY_FILLED`NEW`NEW`PENDING_CANCEL`PENDING_CANCEL`CANCELED`CANCELED`PENDING_CANCEL;

gwex:{[x]y:fs2e x;x:fs2s x;$[y=`XSHE;$[8=count string x;"Y";"1"];y=`XSHG;$[8=count string x;"X";"0"];gwexmap y]};

gwcall:{[x;y;z]t0:.z.P;r:callgwdp[x;y;z];L,:enlist (t0;.z.P;x;y;z;r);r};

chkconn:{[]{[x]z:$[3<=count x;x[2];()];y:x[1];x:x[0];if[{(null x)|x=`Disconnected}WHO[x;`status];smkx[`;`CONNECT;`peer`addr`role!(x;y;`QuoteServer)];smkx[`;`REGSELF;`peer`role`x0!(x;`PushService;z)]]}  SysOpt`GWOSID`GWOSADDR;};

TIMEOUT[`OGWPUSH]:{[x]chkconn[];if[0>=h:WHO[y:SysOpt`GWOSID;`h];:()];if[.z.T within 09:00 17:10;$[0<SysOpt`AsyncMode;[smkx[y;`QryUnfinishedOrder;()!()]];if[.z.T>00:00:00.500+LastTime;@[UPD[`AckUnfinishedOrder];h (`getunfinishedorders;0);()];LastTime::.z.T]]];};

UPD[`AckUnfinishedOrder]:{[x]L1::t:x`data;show -3!(`timer;.z.P;count t);{[h;x]@[qryoptorders;;show] each 0N 1#x;}[WHO[`OS_GW;`h]] select from t where (gwex each fsym) in\: "XY";{[h;x]@[qryfutorders;;show] each 0N 1#x;}[WHO[`OS_GW;`h]] select from t where (gwex each fsym) in\: "FU";@[qrystkorders;;show] each (0N,SysOpt`BatchNum)#select from t where (gwex each fsym) in\: "01";}; /t1:select from t where not (gwex each fsym) in\: "01";i:0;do[count t1;qryfutorders enlist t1 [i];i:i+1];

qrystkorders:{[x]if[0=count x;:()];r:gwcall[`00800010;(count x),{[x]`optId`optPwd`optMode`acctId`acctPwd`queryType`contractNum!SysOpt[`optId`optPwd`optMode],(SysOpt`StkAcc;SysOpt`StkAccPwd;`0;x`orderid)} each x;`exchId`contractNum`acctId`regId`regName`orderType`stkId`stkName`orderPrice`orderQty`orderAmt`knockQty`withdrawQty`orderTime`offerTime`occurtime`orderputtingQty`validFlag`sendFlag`withdrawFlag`withdrawOrderFlag`statusDesc`statusId`memo`str1`orderUnitDesc`exteriorAcctId`batchNum`totalOrderQty`totalKnockQty`totalWithdrawQty`totalOrderputtingQty`tradeCurrencyId`exchRate`oddFlag`settleOrderAmt];if[3=count r;:()];r:r[0];if[0<cq:"F"$(last r)`knockQty;r1:gwcall[`00800030;(count x),{[x]`optId`optPwd`optMode`acctId`acctPwd`queryType`contractNum!SysOpt[`optId`optPwd`optMode`StkAcc`StkAccPwd],(`3;x`orderid)} each x;`exchId`contractNum`acctId`regId`regName`orderType`tradingResultTypeDesc`stkId`stkName`knockPrice`knockQty`totalwithdrawqty`knockCode`knockAmt`fullKnockAmt`accuredInterestAmt`knockTime`reckoningAmt`postQty`orderPrice`orderQty`optMode`str1`occurTime`exteriorAcctId`totalOrderQty`totalKnockQty`tradeCurrencyId`exchRate];if[3=count r1;:()];r1:r1[0];r:r ij select last knockPrice by contractNum from r1];smkx[SysOpt`GWOSID;`OnStkOrders;(enlist `data)!enlist x ij select by orderid:`$contractNum from r];};

qryfutorders:{[x]X::x;if[0=count x;:()];r:gwcall[`20800010;(count x),{[x]`optId`optPwd`optMode`acctId`acctPwd`contractNum!SysOpt[`optId`optPwd`optMode],(SysOpt`FutAcc;SysOpt`FutAccPwd;x`orderid)} each x;`acctId`regName`regId`exchId`stkId`stkName`F_orderStatus`contractNum`orderId`serialNum`actionFlag`F_offSetFlag`bsFlag`orderQty`knockQty`knockAmt`F_orderPriceType`futureOrderPrice`averagePrice`F_forceCloseReason`orderTime`validFlag`CoveredFlag`F_MatchCondition`exchErrorCode`exchErrorMsg];show -3!.z.P,r;if[3=count r;:()];R::r:r[0];smkx[y:SysOpt`GWOSID;`OnFutOrders;(enlist `data)!enlist x ij select by orderid:`$contractNum from r];:();show select [-5] from MSG where mtype=`OnFutOrders;};

qryoptorders:{[x]X::x;if[0=count x;:()];r:gwcall[`20800010;(count x),{[x]`optId`optPwd`optMode`acctId`acctPwd`contractNum!SysOpt[`optId`optPwd`optMode],(SysOpt`OptAcc;SysOpt`OptAccPwd;x`orderid)} each x;`acctId`regName`regId`exchId`stkId`stkName`F_orderStatus`contractNum`orderId`serialNum`actionFlag`F_offSetFlag`bsFlag`orderQty`knockQty`knockAmt`F_orderPriceType`futureOrderPrice`averagePrice`F_forceCloseReason`orderTime`validFlag`CoveredFlag`F_MatchCondition`exchErrorCode`exchErrorMsg];show -3!.z.P,r;if[3=count r;:()];R::r:r[0];smkx[y:SysOpt`GWOSID;`OnFutOrders;(enlist `data)!enlist x ij select by orderid:`$contractNum from r];:();show select [-5] from MSG where mtype=`OnFutOrders;};

\

