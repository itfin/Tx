\l Tx/conf/qtx/cfha.q
\l Tx/conf/qtx/cfxtp.q

\d .conf
me:`fqxtp;
id:`610;
feedtype:`fq;
sub.tp.sysmsg:`ALL,me;
xtpsublist:`symbol$();
xtpsymlist:get `:/kdb/500etflist; /`600000.XSHG`600030.XSHG`000002.XSHE`300001.XSHE; /`symbol$(); /`600000.XSHG`600030.XSHG`000002.XSHE`300001.XSHE
batchpub:1b;
skipspsyms:0b;

xtp.cltid:1000i;
\d .

\d .db
TASK[`XTPQCONN;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+08:55;1D;0;4;`xtpqconn);
TASK[`XTPQDISC;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+16:05;1D;0;4;`xtpqdisc);
\d .


