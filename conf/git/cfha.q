\l Tx/conf/git/cfbase.q

\d .conf
ha.node:`ha;
ha.backup:`ha1;

dbhome:` sv dbbase,app,ha.node;
feeddb:` sv dbhome,`feeddb;
histdb:` sv dbhome,`histdb;
tempdb:` sv dbhome,`tempdb;
tickdb:` sv dbhome,`tickdb;

pubto:`tp;
conn.tp.addr:ha.portbase.tp+ha.ha.portoffset; /`:unix://5010
\d .
