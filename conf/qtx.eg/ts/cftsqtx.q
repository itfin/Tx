\d .db

Ts.qtx.active:1b;
Ts.qtx.acc:`ctp;
Ts.qtx.accx:`symbol$();
Ts.qtx.stop:0b;
Ts.qtx.stoptype:`;

Ts.qtx.event.timer:`ont_grid;
Ts.qtx.event.quote:`onq_grid;
Ts.qtx.event.exerpt:`ono_grid;
Ts.qtx.event.sysinit:`oni_grid;
Ts.qtx.event.sysexit:`one_grid;
Ts.qtx.event.dayroll:`ond_grid;

Ts.qtx.mode:`MANUAL;
Ts.qtx.xsym:`IF1905.CCFX;
Ts.qtx.TRDTIME:enlist 00:00 24:00;
Ts.qtx.RATIO:0.0125;
Ts.qtx.ANCHORPX:1217.657;
Ts.qtx.ANCHORUP:1232.878;
Ts.qtx.ANCHORDN:1202.436;
Ts.qtx.OIDUP:`;
Ts.qtx.OIDDN:`;
Ts.qtx.POSSUP:-60f;
Ts.qtx.POSINF:-64f;
Ts.qtx.LONGOFFSET:0f;
Ts.qtx.SHORTOFFSET:0f;
Ts.qtx.GRIDSIZE:1f;
Ts.qtx.PRICESCALE:-1f;
Ts.qtx.SPREADMAX:0.5f;
Ts.qtx.SHORTSTOPRANGE:1308 1313f;
Ts.qtx.LONGSTOPRANGE:1095 1100f;

\d .
