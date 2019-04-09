\l Tx/conf/cfftbase.q
\l Tx/conf/qtx/cfha.q

\d .conf
me:`ftsim;
id:`290;
feedtype:`ftsim;

conn.rdb.addr:5011; /`:unix://5011;
conn.hdb.addr:5012; /`:unix://5012;

sub.tp.quote:`;
sub.tp.quoteref:`;
sub.tp.quotereq:`;


sub.tp.sysmsg:me,`ALL;
sub.tp.syslog:`;

acc.sim.sym:`;
filldelay:1b;

maxcxlcnt:10;
t0list:`symbol$();
t1list:`symbol$();
useclosetoday:1b;
closetodayexlist:`XSGE`XDCE`XZCE;
usecloseyestoday:0b;

\d .
