.module.fqctpudp:2019.09.05;

txload "core/fqbase";
txload "feed/socket";

.enum.ctpexmap:`CFFEX`SHFE`DCE`CZCE`INE!`CCFX`XSGE`XDCE`XZCE`XINE;

.ctrl.ctp.sock:0i;
.temp.QL:();
.temp.QUEUE:0#delete time,src,srctime,srcseq,dsttime from quote;
.temp.QREF:1!0#delete time,refopt,src,srctime,srcseq,dsttime from quoteref;

.enum.qcols:cols .temp.QUEUE;

.init.fqctpudp:{[x].ctrl.ctp.sockmap:mirror .ctrl.ctp.sock:(key .conf.udp.addrmap)!sockopen each value .conf.udp.addrmap;};
.exit.fqctpudp:{[x]sockclose each value .ctrl.ctp.sock;};
.timer.fqctp:{[x]batchpub[];};

enqueue:{[x].temp.QUEUE,:x};
batchpub:{[]if[(not 1b~.conf.batchpub)|(0=count .temp.QUEUE);:()];pub[`quote;.temp.QUEUE];.temp.QUEUE:0#.temp.QUEUE;};
fix0w:{[x]?[1e300<abs[x];0n;x]};

sockcbrecv:{[s;ip;port;r;buf]if[1b~.conf.udp[`debug];.temp.QL,:enlist (s;ip;port;r;.z.P;buf)];.temp.buf:buf;t:.ctrl.ctp.sockmap[s];.temp.d:d:$[t in `XSGE_L1`XSGE_L2;decode_xsge_new;t in `XINE_L1`XINE_L2;decode_xine_new;decode_old] buf;if[count[l]& not d[0;0] in l:.conf.ctpsymlist;:()];$[1b~.conf.batchpub;enqueue[enlist d[0]];pub[`quote;enlist .enum.qcols!d[0]]];if[not d[1;1+til 4]~.temp.QREF[d[1;0];`pc`open`sup`inf];pub[`quoteref;enlist `sym`oc`open`sup`inf`refopt!d[1],enlist ""];.temp.QREF,:enlist d[1]];};

decode_new:{[e;x]d:first each ("*s* hiscfc iffi ",(14#"f"),30#"fi ";9 31 8 2 2 4 31 1 8 1 3 4 8 8 4 4,(14#8),30#8 4 4) 1: x;s:sv[`]d[1],e;(s,(fix0w `float$d[27 37 28 38 11 15 16]),((%/) d[13 12]),(fix0w `float$d[12 14 19]),$[d[4]=5;`5;`1],(`timestamp$("D"$8#d[0])+d[3]+"T"$d[2]),$[d[4]=5;fix0w each `float$d 27 37 28 38 +\:2*til 5;4#enlist `float$()],enlist "";s,fix0w `float$d[23 17 20 21])}; /`TradingDay0`InstrumentID1`UpdateTime2`UpdateMillsec3`MarketDataDepth4`UnderlyingInstrumentID5`ProductClass6`StrikePrice7`OptionType8`VolumeMultiple9`PriceTick10`LastPrice11`Volume12`Turnover13`OpenInterest14`HighestPrice15`LowestPrice16`OpenPrice17`ClosePrice18`SettlementPrice19`UpperLimitPrice20`LowerLimitPrice21`PreSettlementPrice22`PreClosePrice23`PreOpenInterest24`PreDelta25`CurrDelta26`BidPrice127`BidVolume128`BidPrice229`BidVolume230`BidPrice331`BidVolume332`BidPrice433`BidVolume434`BidPrice535`BidVolume536`AskPrice137`AskVolume138`AskPrice239`AskVolume240`AskPrice341`AskVolume342`AskPrice443`AskVolume444`AskPrice545`AskVolume546!d

decode_xsge_new:decode_new[`XSGE];decode_xine_new:decode_new[`XINE];

decode_old:{[x]d:first each ("*sss",(7#"f"),"i ",(8#"f"),"* i",(30#"fi "),"f ";(4#9 31),(7#8),(2#4),(8#8),8 4 4,(30#8 4 4),8 16) 1: x;s:sv[`]d[1],.enum.ctpexmap d[2];(s,(fix0w `float$d[22 24 23 25 4 9 10],((%/)d[12 11]),d[11 13 15]),`0,(`timestamp$("D"$8#d[0])+d[21]+"T"$d[20]),(4#enlist `float$()),enlist "";s,fix0w `float$d[6 8 16 17])}; /`TradingDay0`InstrumentID1`ExchangeID2`ExchangeInstID3`LastPrice4`PreSettlementPrice5`PreClosePrice6`PreOpenInterest7`OpenPrice8`HighestPrice9`LowestPrice10`Volume11`Turnover12`OpenInterest13`ClosePrice14`SettlementPrice15`UpperLimitPrice16`LowerLimitPrice17`PreDelta18`CurrDelta19`UpdateTime20`UpdateMillisec21`BidPrice122`BidVolume123`AskPrice124`AskVolume125`BidPrice226`BidVolume227`AskPrice228`AskVolume229`BidPrice330`BidVolume331`AskPrice332`AskVolume333`BidPrice434`BidVolume435`AskPrice436`AskVolume437`BidPrice538`BidVolume539`AskPrice540`AskVolume541`AveragePrice42!d