.module.socket:2019.09.04;

`udpsend`sockopen`sockclose`sockopt`sockcheck`tcpsend`udpsendto`tcprecv`udprecvfrom`getsockbuf`setsockbuf`errmsg {x set `extsocket 2:(x;y);}' (5#1),2 2,5#1;

udplisten:{[x]sockopen[x,enlist 0i]};tcpconnasync:{[x]sockopen[x,enlist 1i]};tcplistenasync:{[x]sockopen[x,enlist 2i]};tcpconn:{[x]sockopen[x,enlist 3i]};tcplisten:{[x]sockopen[x,enlist 4i]};

.ctrl.tcpconn:.enum`nulldict;
.ctrl.tcpin:()!();
.temp.sockrecv:()!();
.temp.socksend:()!();
.tcppc:.enum`nulldict;

.timer.socket:{[x]chktcpconn[];chktcpasync[];};
.exit.socket:{[x]disctcpconn[];};

chktcpconn:{[]if[not `tcpconn in key `.conf;:()];{[x]if[0h=type r:.conf.tcpconn[x;`connrange];if[not any .z.T within/: `time$r;:()]];b:$[not x in key .ctrl.tcpconn;1b;0>=.ctrl.tcpconn[x;`h];1b;0b];a:1b~.conf[`connasync];if[b;h:@[$[a;tcpconnasync;tcpconn];.conf.tcpconn[x]`addr;-1];if[0<h;.ctrl.tcpconn[x]:`h`c`conntime`sbuf`rbuf!(h;not a;.z.P;"";"")];if[not a;onsockconn[x]]];} each tkey .conf.tcpconn;}; /

chktcpasync:{[]{[x]r:.ctrl.tcpconn[x];if[not (0<h:r[`h])& not r`c;:()];$[.z.P<r[`conntime]+00:01:00^tfill .conf[`tcpconntmout];sockcheck[h];[sockclose[h];.ctrl.tcpconn[x;`h`disctime]:(-1i;.z.P);if[not 1b~r[`e];lwarn[`TCPConnectTimeout;(x;h)];.ctrl.tcpconn[x;`e]:1b]]]} each tkey .ctrl.tcpconn;};

disctcpconn:{[]if[not `tcpconn in key `.ctrl;:()];{[x]if[0<h:.ctrl.tcpconn[x]`h;sockclose[h]];} each tkey .ctrl.tcpconn;};

sockcberr:{[s;r]lwarn[`TCPSelectErr;(s;r)];};

listencb:{[s;r;ip;port]linfo[`TCPAccept;(s;r;ip;port)];.ctrl.tcpin[r]:(ip;port);};

sockcbsend:{[s]ldebug[`sockcbsend;s];x:.ctrl.tcpconn[;`h]?s;if[(0>=s)|(null x);:()];if[not .ctrl.tcpconn[x;`c];.ctrl.tcpconn[x;`connected`c`e]:(.z.P;1b;0b);linfo[`TCPConnected;(x;s)];onsockconn[x]];};

sockcbrecv:{[s;ip;port;r;buf]ldebug[`sockcbrecv;(s;ip;port;r;buf)];if[1b~.conf[`sockdebug];.temp.sockrecv[s],:buf];if[(port=0)&(2=count sa:.ctrl.tcpin[s]);ip:sa[0];port:sa[1]];x:.ctrl.tcpconn[;`h]?s;$[0>r;lwarn[`SockErr;(r;x;.conf[x;`addr];.ctrl.tcpin[s])];0=r;[lwarn[`TCPRecvClose;s];.tcppc[;s];if[not null x;.ctrl.tcpconn[x;`disctime`h`c]:(.z.P;-1;0b);onsockdisc[x]]];onsockmsg[`w`h`a!(x;s;`$":" sv (ip;string port));buf]];};

sendtcpblk:{[x;y]s:.ctrl.tcpconn[x;`h];if[(s<0)|not .ctrl.tcpconn[x;`c];lerr[`TCPSendNoLink];:-1];n:0;z:(0N,131072^jfill .conf[`tcpwinsize])#y;i:0;do[count z;pn:count z[i];r:tcpsend[s;z[i]];if[1b~.conf[`sockdebug];.temp.socksend[s],:(r|0)#z[i]];if[r<0;lwarn[`TCPSendErr;(x;r)];if[not r in -11 -10035 -10057;lerr[`TCPSendClose;s];sockclose[s];.tcppc[;s];.ctrl.tcpconn[x;`disctime`h`c]:(.z.P;-1;1b)];onsockdisc[x];:n];n+:r;if[r<pn;lwarn[`TCPSendPart;(x;r;pn)];:n];i+:1];n};

smtcp:{[x;y]y:$[()~y;"";10h<>type y;string y;y];y:{$[()~x;"";x]} (.ctrl.tcpconn[x;`sbuf]),y;if[0=n:count y;:()];r:sendtcpblk[x;y];.ctrl.tcpconn[x;`sbuf]:$[r<n;(r|0) _ y;""];r};

onsockmsg:{[x;y]};
onsockconn:{[x]}; /if[(.ctrl.tcpconn[x;`c])&(0<count .ctrl.tcpconn[x;`sbuf]);smtcp[x;""]];
onsockdisc:{[x]};
