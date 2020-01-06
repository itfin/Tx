\l Tx/conf/cfftbase.q
\l Tx/conf/qtx/cfha.q

\d .conf
me:`ftbt;
id:`280;
feedtype:`ftbacktest;

ui.title:"Tx²ßÂÔÒýÇæ(BT-qtx)";
ui.lib:"ftui.js";

conn.rdb.addr:5011; /`:unix://5011;
conn.hdb.addr:5012; /`:unix://5012;

pubto:`;

sub.tp.sysmsg:`symbol$();

acc.sim.sym:`;
acc.ctp.sym:`;
acc.tws.sym:`;

maxcxlcnt:10;
t0list:`symbol$();
t1list:`symbol$();
useclosetoday:1b;
closetodayexlist:`XSGE`XDCE`XZCE;
usecloseyestoday:0b;

loglevel:`debug;
\d .
