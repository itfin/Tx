\l Tx/conf/qtx/cfha.q
\l Tx/conf/qtx/cffcbase.q
\d .conf
me:`fc;
id:`990;

ui.title:"TxÖ÷¿ØÌ¨(Qtx)";
ui.lib:"fcui.js";

\d.

\d .db
TASK[`STOPCTP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:25;1D;0;6;`stopctp);
TASK[`STARTCTP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:30;1D;0;6;`startctp);
TASK[`STOPCTP_YP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:25;1D;0;6;`stopctp);
TASK[`STARTCTP_YP;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+20:30;1D;0;6;`startctp);
TASK[`GCALL0;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+08:30;1D;0;6;`gcall);
TASK[`GCALL1;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+12:30;1D;0;6;`gcall);
TASK[`GCALL2;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+19:30;1D;0;6;`gcall);
TASK[`CLEARAPIFILE;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+22:00;1D;0;6;`rmoldapifiles);
TASK[`HB;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+00:00;`timespan$00:01;0;4;`hball);
TASK[`NH;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+00:05;`timespan$00:01;0;4;`nhall);
\d .
