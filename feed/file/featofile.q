.module.featofile:2023.08.16;

txload "core/febase";

.ctrl.atofile:.enum.nulldict;
.ctrl.atofile.FUND:();
.ctrl.atofile.POS:();

.ctrl.O:$[`ft=.conf.feedtype;`O1;`O];

\d .enum
OrderAlgoKey:`ExternalId`ClientName`Symbol`Side`OrderQty`OrdType`EffTime`ExpTime`LimAction`AftAction`AlgoParam`UnitId`ProductId;
CancelOrderAlgoKey:`QuoteId`CxlType;
ReportOrderAlgoKey:`ExternalId`QuoteId`ClientName`Symbol`SecType`SecExch`Side`TransTime`OrderQty`OrdType`Price`EffTime`ExpTime`LimAction`AftAction`AlgoParam`CumQty`LeavesQty`OutstaQty`AvgPx`OrdStatus`CxlType`BasketId`Text`UpdateTime`UnitId`ProductId;
SubOrderAlgoKey:`ExternalId`QuoteId`ClOrdId`OrderId`ClientName`TransTime`OrdStatus`Symbol`Side`SecType`SecExch`Price`OrdType`OrderQty`CumQty`LeavesQty`AvgPx`UpdateTime`Text`UnitId`ProductId;
ReportBalanceKey:`ClientName`EnBalance`CrBalance`AssetAmt`MarketAmt`UpdateTime`UnitId`ProductId;
ReportPositionKey:`ClientName`Exchange`Symbol`CurrentQ`EnableQty`ShortQty`UpdateTime`UnitId`ProductId;

`MARKET_TYPE_INVALID`MARKET_TYPE_SZ`MARKET_TYPE_SH`MARKET_TYPE_CFE`MARKET_TYPE_SHF`MARKET_TYPE_DCE`MARKET_TYPE_ZCE`MARKET_TYPE_INE set' `int$til 8;  /AtoMarketType
`SIDE_INVALID`SIDE_BUY`SIDE_SELL`SIDE_CLOSE_BUY`SIDE_SHORT_SELL`SIDE_SHORT_BUY`SIDE_CLOSE_SELL`SIDE_DIRECT_CLOSE_SELL`SIDE_DIRECT_CLOSE_BUY`SIDE_REVERSE_REPO`SIDE_NEW_STOCK_SUB`SIDE_NEW_BOND_SUB set' `int$-1,1+til 11; /AtoSide
`ALGO_TYPE_INVALID`ALGO_TYPE_TWAP_PLUS`ALGO_TYPE_TWAP_CORE`ALGO_TYPE_VWAP_PLUS`ALGO_TYPE_VWAP_CORE`ALGO_TYPE_POV_CORE`ALGO_TYPE_PASSTHRU set' `int$-1 101 103 102 104 105 201; /AtoAlgoTypeId
`FILE_ORDER_STATUS_INVALID`FILE_ORDER_STATUS_NEW`FILE_ORDER_STATUS_PARTFILLED`FILE_ORDER_STATUS_FILLED`FILE_ORDER_STATUS_CANCELED`FILE_ORDER_STATUS_PENDINGCANCEL`FILE_ORDER_STATUS_REJECTED`FILE_ORDER_STATUS_SUSPENDED`FILE_ORDER_STATUS_PENDINGNEW set' `int$-1 0 1 2 4 6 8 9 10; /AtoFileOrderStatus
\d .

.enum.atoex:mirror .enum.atoexmap:.enum[`MARKET_TYPE_SZ`MARKET_TYPE_SH`MARKET_TYPE_CFE`MARKET_TYPE_SHF`MARKET_TYPE_DCE`MARKET_TYPE_ZCE`MARKET_TYPE_INE]!`XSHE`XSHG`CCFX`XSGE`XDCE`XZCE`XINE;
.enum.atoside:mirror .enum.atosidemap:.enum[`SIDE_BUY`SIDE_SELL]!.enum`BUY`SELL;

.enum.atofilestatusmap:.enum[`FILE_ORDER_STATUS_INVALID`FILE_ORDER_STATUS_NEW`FILE_ORDER_STATUS_PARTFILLED`FILE_ORDER_STATUS_FILLED`FILE_ORDER_STATUS_CANCELED`FILE_ORDER_STATUS_PENDINGCANCEL`FILE_ORDER_STATUS_REJECTED`FILE_ORDER_STATUS_SUSPENDED`FILE_ORDER_STATUS_PENDINGNEW]!.enum`NULL`NEW`PARTIALLY_FILLED`FILLED`CANCELED`PENDING_CANCEL`REJECTED`SUSPENDED`PENDING_NEW;

dbfread:{[x]h:()!();h[`ver`nrec`hlen`rlen`ftag]:first each("x ihh b";1 3 4 2 2 2 1) 1: (x;0;15);if[h[`ftag];:()];f:("sc xx ";11 1 4 1 1 14) 1: (x;32;h[`hlen]-33);flip (f 0)!("S"^("CN"!"SF")f 1) {x$y}' (" ",(count f 1)#"*";1,$[.z.K<3;`int;`long]$f 2) 1: (x;h[`hlen];h[`nrec]*h[`rlen])}; /[`:/tmp/f.dbf],f:fields def[字段名;类型(BCDGN);字段长度;字段精度]
dbfadd:{[x;y].temp.x:x;.temp.y:y;h:()!();h[`ver`nrec`hlen`rlen`ftag]:first each("x ihh b";1 3 4 2 2 2 1) 1: (x;0;15);if[h[`ftag];:()];f:("sc xx ";11 1 4 1 1 14) 1: (x;32;h[`hlen]-33);if[not key[y]~f[0];:()];z:read1[x];z[4+til 4]:reverse 0x0 vs `int$1+h`nrec;x 1: `byte$z," ",raze neg[`long$f[2]]$'tostring each value y;}; /[`:/tmp/f.dbf;f;data;`a`b!1 2],f:fields def[字段名;类型(BCDGN);字段长度;字段精度] 

.init.featofile:{[x].roll.featofile[x];};
.exit.featofile:{[x];};
.roll.featofile:{[x].ctrl.atofile[`NewFile`CxlFile`ExeFile`ExeSubFile`FundFile`PosFile]:hsym `$(string[.conf.ato.filescandir],"/"),/:string[`OrderAlgo`CancelOrderAlgo`ReportOrderAlgo`SubOrderAlgo`ReportBalance`ReportPosition],\:"_",except[string[.z.D];"."],".dbf";.ctrl.atofile[`ExeLast]:(`symbol$())!`timestamp$();};

atotime:{sum "DT"$' (8#;8_)@\: string x};

.timer.featofile:{[x]d:dbfread .ctrl.atofile.ExeFile;{[x].temp.x:x;y:x`ExternalId;z:exec first id from .db.O where s0=y;if[null z;:()];r:.db[.ctrl.O;z];cq:`float$x`CumQty;if[cq<r`cumqty;:()];s:.enum.atofilestatusmap `int$x`OrdStatus;if[(s in .enum`PENDING_NEW`NEW`PARTIALLY_FILLED)&3=`int$x`CxlType;s:.enum`EXPIRED];.db[.ctrl.O;z;`ordid`msg`rtime`rptopt]:(x`QuoteId;string x`Text;.z.P;.j.j `LeavesQty`OutstaQty`OrdStatus`CxlType#x);if[0<cq;ap:x`AvgPx;lq:cq-q0:0f^r`cumqty;ca:0f^ap*cq;lp:(ca-q0*p0:0f^r`avgpx)%lq;.db[.ctrl.O;z;`cumqty`avgpx`lastqty`lastpx]:cq,ap,lq,lp;if[not s in .enum`CANCELED`EXPIRED;s:.enum $[cq=r`qty;`FILLED;`PARTIALLY_FILLED]]];.db[.ctrl.O;z;`status]:s;if[s=.enum`CANCELED;.db[.ctrl.O;z;`cstatus]:s];execrpt[z];} each select from d where  (.ctrl.atofile.ExeLast ExternalId)<atotime each UpdateTime;.ctrl.atofile[`ExeLast]:exec ExternalId!`timestamp$atotime each UpdateTime from d;}; 

\d .temp
IL:L15:L14:L13:L12:L11:L10:L9:L8:L7:L6:L5:L4:L3:L2:L1:L0:L:C:();
DelayedCancel:(`symbol$())!`float$();
\d .

/ato msg
/Tx msg

.upd.ordnew:.fe.ordnew:{[x].temp.x9:x;if[x[`sym]<>.conf.me;:.ha.ordnew[x]];k:x`oid;h:$[count opt:x`ordopt;strdict opt;(`symbol$())!()];if[not null .db[.ctrl.O;k;`sym];:()];k1:newidl[];.db[.ctrl.O;k;`feoid`ntime`status`x0`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(k1;.z.P;.enum`PENDING_NEW;enlist .enum.nulldict),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;if[not .conf.ato.ordmax>count .db[.ctrl.O];rejectord[k;1i;"ATO_Not_Ready_Or_Toomany_Orders"];:()];esym:fs2s x`osym;ex:fs2e x`osym;pua:"IJS"$'string vs[`]x`acc1;ae:.enum.atoex ex;as:.enum.atoside x`side;k2:sv[`;x`ft`ts`oid];.db[.ctrl.O;k;`s0]:k2;$[1b~h`algo;[.db[.ctrl.O;k;`special]:`algo;y:`int$h`algotype;ap:h[`algopara];z:$[y=201;`price`PriceTypeI!(x`price;0i^ifill ap`PriceTypeI);(`price`UpLimitF`DownLimitF,$[y=105;`max_percentage;`costBPF],`basket_id)!(x`price;0f^ffill ap`UpLimitF;0f^ffill ap`DownLimitF;0f^ffill ap $[y=105;`max_percentage;`costBPF];$[y=105;`;k1])];if[0>=ffill z`price;z:`price _z];if[0>=ffill z`UpLimitF;z:`UpLimitF _z];if[0>=ffill z`DownLimitF;z:`DownLimitF _z];if[0>=ffill z`costBPF;z:`costBPF _z];if[0>=ifill z`PriceTypeI;z:`PriceTypeI _z];if[null z`basket_id;z:`basket_id _z];tl:"J"$except[;":.T"] each string `datetime$vtd[]+"T"$string ap`start_time`end_time;r:`ExternalId`ClientName`Symbol`Side`OrderQty`OrdType`EffTime`ExpTime`LimAction`AftAction`AlgoParam`UnitId`ProductId!(k2;pua[2];sv[`]esym,$[ex=`XSHE;`SZ;`SH];as;x`qty;y;tl 0;tl 1;0;0;{sv[": "] key[x] {string[x],"=",string y}' value[x]} z;pua[1];pua[0]);dbfadd[.ctrl.atofile.NewFile;r]];[]];}'; 

.upd.ordcxl:.fe.ordcxl:{[x]if[x[`sym]<>.conf.me;:.ha.ordcxl[x]];k:x`oid;r:.db[.ctrl.O;k];if[(null r`sym)|null r`ordid;:()];.db[.ctrl.O;k;`cid`cstatus]:(x`cid;.enum`PENDING_CANCEL);h:$[count r[`x0];r[`x0;0];strdict r`rptopt];dbfadd[.ctrl.atofile.CxlFile;`QuoteId`CxlType!(r`ordid;1)];}'; 