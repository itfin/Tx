\d .conf
maxcxlcnt:5;
t0list:`511010.XSHG`518800.XSHG`518880.XSHG`159934.XSHE`159937.XSHE`159985.XSHE`511380.XSHG`159980.XSHE;
t1list:`symbol$();
useclosetoday:1b;
closetodayexlist:enlist `XSGE;
usecloseyestoday:0b;
symblacklist:`symbol$();
keepbar:0b;
checkrisk:0b;
rcusewhitelst:0b;
simnoe:0b;
autoloadhdb:1b;
checkfqtime:0b;

fq.fqctp.session:(00:00 02:00;09:00 10:15;10:30 11:30;13:00 15:00;21:00 24:00);
fq.fqctp.maxhalt:00:00:02;

fq.fqxshe.session:(09:20 09:25;09:30 11:30;13:00 15:00);
fq.fqxshe.maxhalt:00:00:10;

fq.fqxshg.session:(09:20 09:25;09:30 11:30;13:00 15:00);
fq.fqxshg.maxhalt:00:00:10;
\d .


\d .db
ftalive:0b;
ftdate:.z.D;
enablets:`symbol$();
Ts:.enum.nulldict; 
\d .
