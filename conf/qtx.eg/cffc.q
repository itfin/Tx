\l Tx/conf/qtx/cfha.q
\l Tx/conf/qtx/cffcbase.q
\d .conf
me:`fc;
id:`990;

ui.title:"Tx主控台(Qtx)";
ui.lib:"fcui.js";

\d .

\d .db
TASK[`START_D;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:55;1D;0;4;`startdaily);
TASK[`STOP_D;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+16:55;1D;0;4;`stopdaily);      /需要等到交易日切换后再退出
TASK[`START_N;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:45;1D;0;4;`startnightly);
TASK[`STOP_N;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+02:45;1D;1;5;`stopnightly);

TASK[`GCALL0;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:30;1D;0;6;`gcall);
TASK[`GCALL1;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+12:30;1D;0;6;`gcall);
TASK[`GCALL2;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+19:30;1D;0;6;`gcall);
TASK[`CLEARAPIFILE;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+22:00;1D;0;6;`rmoldapifiles);
TASK[`HB;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+00:00;`timespan$00:01;0;4;`hball);
TASK[`NH;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+00:05;`timespan$00:01;0;4;`nhall);
\d .
