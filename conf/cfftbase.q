\d .conf
maxcxlcnt:10;
t0list:`511010.XSHG`518800.XSHG`518880.XSHG`159934.XSHE`159937.XSHE`159985.XSHE`511380.XSHG;
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
\d .


\d .db
ftalive:0b;
ftdate:.z.D;
enablets:`symbol$();
Ts:.enum.nulldict; 
\d .
