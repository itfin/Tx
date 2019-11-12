.module.febase:2019.07.31;

\d .db
feclosedate:feopendate:0Np;
\d .

idfe2ft:{[x]exec first id from .db.O where feoid=x};
qidfe2ft:{[x]exec first id from .db.QT where feqid=x};

.upd.exerpt:.fe.exerpt:.ha.exerpt';

.roll.fe:{[x]gtc:.enum`GOOD_TILL_CANCEL;.[.conf.histdb;(.conf.me;`O);,;select from .db.O where end|tif<>gtc];delete from `.db.O where end|tif<>gtc;update `u#id from `.db.O;};

rejectord:{[x;y;z]if[null .db.O[x;`ft];:()];.db.O[x;`rtime`status`reason`msg]:(.z.P;.enum`REJECTED;y;z);riskstatrej[x];pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`corderid`reason`msg`rptopt!(.db.O[x;`ft];.enum`NEW;x;.enum`REJECTED;0f;0f;`;`;.enum`NULL;`;`;y;z;"")];}; /[oid;reason;msg]

rejectcxlrpl:{[src;oid;cid;reason;msg;isrpl]pub[`cxlrej;enlist `sym`oid`cid`cstatus`cordid`reason`msg`isrpl!(src;oid;cid;.enum`REJECTED;newid[];reason;msg;isrpl)];};rejectcxl:rejectcxlrpl[;;;;;0b];rejectrpl:rejectcxlrpl[;;;;;1b];

execrpt:{[k]r:.db.O[k];if[null x:r`ft;:()];riskstatexe[k];pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(x;.enum`NEW;k),r[`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason],(cfill r`msg;cfill r`rptopt)];};

ackquote:{[k]r:.db.QT[k];if[null r`sym;:()];pub[`quoteack;enlist `sym`typ`qid`status`bcumqty`acumqty`bavgpx`aavgpx`feqid`quoteid`cid`cstatus`cfeqid`cquoteid`reason`msg`rptopt!(r`ft;.enum`NEW;k),r[`status`bcumqty`acumqty`bavgpx`aavgpx`feqid`quoteid`cid`cstatus`cfeqid`cquoteid`reason],(cfill r`msg;cfill r`rptopt)];};


rejcxl:{[k;r;m]h:.db.O[k];rejectcxl[h`ft;k;h`cid;r;m];};

riskassert:{[x]0b}; /风控检查委托请求默认处理函数
riskassertcxl:{[x]0b}; /风控检查撤单请求默认处理函数
riskstatrej:{[x];}; /风控检查委托拒绝默认处理函数
riskstatexe:{[x];}; /风控检查委托回报默认处理函数