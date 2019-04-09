\l Tx/conf/cfftbase.q
\l Tx/conf/qtx/cfha.q

\d .conf
me:`ft;
id:`0;
feedtype:`ft;
ha.backupft:`ft1;
ha.backupfe:`fectp1`fetws1;

conn.rdb.addr:5011; /`:unix://5011;
conn.hdb.addr:5012; /`:unix://5012;

sub.tp.quote:`;
sub.tp.quoteref:`;
sub.tp.quotereq:`;

sub.tp.ordnew:ha.backupfe;
sub.tp.ordcxl:ha.backupfe;

sub.tp.exerpt:me,ha.backupft;
sub.tp.exenoe:me,ha.backupft;
sub.tp.cxlrej:me;

sub.tp.tsparam:me,ha.backupft;

sub.tp.sysmsg:me,`ALL;
sub.tp.syslog:`;

acc.sim.sym:`fesim;
acc.ctp.sym:`fesim;
acc.ctp1.sym:`fectp1;
acc.ctp2.sym:`fectp2;


maxcxlcnt:10;
t0list:`symbol$();
t1list:`symbol$();
useclosetoday:1b;
closetodayexlist:`XSGE`XDCE`XZCE;
usecloseyestoday:0b;
\d .
