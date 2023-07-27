\d .conf
maxcxlcnt:5;
t0list:`511010.XSHG`518800.XSHG`518880.XSHG`159934.XSHE`159937.XSHE`159985.XSHE`511380.XSHG`159980.XSHE`159920.XSHE`513090.XSHG`513690.XSHG`513550.XSHG`513330.XSHG`159892.XSHE`518850.XSHG;
t1list:`symbol$();
useclosetoday:1b;
closetodayexlist:`XSGE`XINE;
usecloseyestoday:0b;
symblacklist:`symbol$();
keepbar:0b;
checkrisk:0b;
rcusewhitelst:0b;
simnoe:0b;
autoloadhdb:0b;
checkfqtime:0b;

fq.fqctp.session:(00:00:02 02:00:00;09:00:02 11:30:00;13:00:02 15:00:00;21:00:02 24:00:00);
fq.fqctp.maxhalt:00:00:02;

fq.fqxshe.session:(09:20:00 09:25:00;09:30:05 11:30:00;13:00:05 15:00:00);
fq.fqxshe.maxhalt:00:00:10;

fq.fqxshgtxt.session:(09:20:00 09:25:00;09:30:05 11:30:00;13:00:05 15:00:00);
fq.fqxshgtxt.maxhalt:00:00:10;

fq.fqtdf.session:(09:30:00 11:30:00;13:00:05 15:00:00);
fq.fqtdf.maxhalt:00:00:10;

\d .


\d .db
ftalive:0b;
ftdate:.z.D;
enablets:`symbol$();
Ts:.enum.nulldict; 
\d .
