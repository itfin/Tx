\l Tx/conf/git/cfha.q
\l Tx/conf/git/cfctp.q

\d .conf
me:`fectp;
id:`300;
feedtype:`fe;
ha.backupfe:`fectp1;
ha.backupft:`ft1;

sub.tp.ordnew:me,ha.backupfe;
sub.tp.ordcxl:me,ha.backupfe;
sub.tp.exerpt:ha.backupft;

sub.tp.quotereq:`;
sub.tp.sysmsg:`ALL,me;

ctp.ordmax:0w;
ctp.debug:1b;
\d .

\d .db
TASK[`CTPTCONN;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:55;1D;0;4;`ctptconn);
TASK[`CTPTDISC;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+16:05;1D;0;4;`ctptdisc);
TASK[`CTPTCONN_YP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:53;1D;0;4;`ctptconn);
TASK[`CTPTDISC_YP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+02:55;1D;0;4;`ctptdisc);
\d .


