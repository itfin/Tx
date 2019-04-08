\l Tx/conf/git/cfha.q
\l Tx/conf/git/cfctp.q

\d .conf
me:`fqctp;
id:`600;
feedtype:`fq;
sub.tp.sysmsg:`ALL,me;
ctpsublist:`symbol$();
ctpsymlist:`symbol$();
batchpub:1b;
skipspsyms:0b;
\d .

\d .db
TASK[`CTPQCONN;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+08:55;1D;0;4;`ctpqconn);
TASK[`CTPQDISC;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+16:05;1D;0;4;`ctpqdisc);
TASK[`CTPQCONN_YP;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+20:53;1D;0;4;`ctpqconn);
TASK[`CTPQDISC_YP;`firetime`firefreq`weekmin`weekmax`handler]:("p"$.z.D+02:55;1D;0;4;`ctpqdisc);
\d .


