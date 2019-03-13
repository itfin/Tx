.module.gwbase:2016.12.29;

`initgwdp`freegwdp`callgwdp{x set `extgwdp 2:(x;y);}' 1 1 3;

.temp.L:();gwcall:{[x;y;z]t0:.z.P;r:callgwdp[x;y;z];.temp.L,:enlist (t0;.z.P;x;y;z;r);r};

qrygwdp:{[x;y;z]p:1;r:gwcall[x;y,`maxRowNum`packNum!`$string .conf.gw.qrypagenum,p;z];if[1<count r;:r];R:r:r[0];n:count r;while[n=.conf.gw.qrypagenum;p+:1;r:callgwdp[x;y,`maxRowNum`packNum!`$string .conf.gw.qrypagenum,p;z];if[1<count r;:r];R,:r:r[0];n:count r];(R;p)};

.enum.exmapgw:"021356FSDZXY"!`XSHG`XSHG`XSHE`XSHE`XHKG`GFZR`CCFX`XSGE`XDCE`XZCE`XSHG`XSHE; 

.init.gw:{[x]system "cd /q/l",$[.z.o=`l32;"32";"64"];initgwdp[];};
.exit.gw:{[x]freegwdp[];};
