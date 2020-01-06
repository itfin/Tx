\l Tx/conf/qtx/cfha.q
\l Tx/conf/qtx/cfxtp.q

\d .conf
me:`fextp;
id:`310;
feedtype:`fe;

ha.backupfe:`fextp1;
ha.backupft:`ft1;

sub.tp.ordnew:me,ha.backupfe;
sub.tp.ordcxl:me,ha.backupfe;
sub.tp.ordqry:me,ha.backupfe;
sub.tp.exerpt:ha.backupft;

sub.tp.quotereq:`;
sub.tp.sysmsg:`ALL,me;

xtp.cltid:1001i;

xtp.ordmax:0w;
xtp.debug:1b;
\d .

\d .db

TASK[`XTPTCONN;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:55;1D;0;4;`xtptconn);
TASK[`XTPTDISC;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+16:05;1D;0;4;`xtptdisc);

\d .


