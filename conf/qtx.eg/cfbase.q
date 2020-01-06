\l Tx/conf/exac.q
\l Tx/conf/holiday.q

\d .conf
dbbase:`:/kdb/txdb;
app:`qtx;
appuser:`qtxuser;
apppass:`qtxpass;
appconn:":",(string appuser),":",(string apppass);

ha.nodelist:enlist `ha;
ha.api.fe:`ordnew`ordcxl;
ha.api.ft:`exerpt`exenoe;
ha.api.fu:enlist `tsparam;

ha.portbase.fc:5000;
ha.portbase.tp:5010;
ha.portbase.ft:7010;
ha.portbase.fq:6010;
ha.portbase.fe:9010;
ha.portbase.fu:10010;
ha.portbase.fa:11010;
ha.portbase.fp:12010;
ha.portstep:10;


ha.ha.ip:`0.0.0.0;
ha.ha.portoffset:0;
ha.ha.backup:`ha1;


ha.ha.tick:`tp`rdb`hdb;
ha.ha.ft:`ft`ftsim;
ha.ha.fe:`fectp`fextp`fejg;
ha.ha.fq:`fqctp`fqxtp`fqjg;
ha.ha.fu:`symbol$();

ha.ha1.ip:`127.0.0.1;
ha.ha1.portoffset:100;
ha.ha1.backup:`ha;

ha.ha1.tick:`tp1`rdb1`hdb1;
ha.ha1.ft:enlist `ft1;
ha.ha1.fe:`fectp1;
ha.ha1.fq:`fqctp1;
ha.ha1.fu:`symbol$();

skipdb:0b;
dumpapi:0b;
loglevel:`warn;
dayendtime:20:00;
\d .
