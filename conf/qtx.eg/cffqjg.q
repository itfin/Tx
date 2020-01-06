\l Tx/conf/qtx/cfha.q
\l Tx/conf/qtx/cfjg.q

\d .conf
me:`fqjg;
id:`620;
feedtype:`fq;
sub.tp.sysmsg:`ALL,me;

jg.mkts:`$"SZ;SH;CFF;SHF;DCE;CZC;SHO;SZO;HKEX";
jg.subs:`; /`$"000001.SZ;601857.SH;399001.SZ;600000.SH;";
jg.flags:`$"TRANSACTION;ORDER;ORDERQUEUE";
jg.timeoffset:0;

batchpub:1b;
skipspsyms:0b;

\d .

\d .db

\d .


