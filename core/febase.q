.module.febase:2017.01.25;

\d .db
feclosedate:feopendate:0Np;
\d .

idfe2ft:{[x]exec first id from .db.O where feoid=x};
qidfe2ft:{[x]exec first id from .db.QT where feqid=x};

.upd.exerpt:.ha.exerpt';

.roll.fe:{[x]delete from `.db.O where end|tif<>.enum`GOOD_TILL_CANCEL;update `u#id from `.db.O;};

rejectord:{[x;y;z]if[null .db.O[x;`ft];:()];.db.O[x;`rtime`status`reason`msg]:(.z.P;.enum`REJECTED;y;z);pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`corderid`reason`msg`rptopt!(.db.O[x;`ft];.enum`NEW;x;.enum`REJECTED;0f;0f;`;`;.enum`NULL;`;`;y;z;"")];}; /[oid;reason;msg]

rejectcxlrpl:{[src;oid;cid;reason;msg;isrpl]pub[`cxlrej;enlist `sym`oid`cid`cstatus`cordid`reason`msg`isrpl!(src;oid;cid;.enum`REJECTED;newid[];reason;msg;isrpl)];};rejectcxl:rejectcxlrpl[;;;;;0b];rejectrpl:rejectcxlrpl[;;;;;1b];

execrpt:{[k]r:.db.O[k];if[null x:r`ft;:()];pub[`exerpt;enlist `sym`typ`oid`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason`msg`rptopt!(x;.enum`NEW;k),r[`status`cumqty`avgpx`feoid`ordid`cstatus`cfeoid`cordid`reason],(cfill r`msg;cfill r`rptopt)];};

ackquote:{[k]r:.db.QT[k];if[null r`sym;:()];pub[`quoteack;enlist `sym`typ`qid`status`bcumqty`acumqty`bavgpx`aavgpx`feqid`quoteid`cid`cstatus`cfeqid`cquoteid`reason`msg`rptopt!(r`ft;.enum`NEW;k),r[`status`bcumqty`acumqty`bavgpx`aavgpx`feqid`quoteid`cid`cstatus`cfeqid`cquoteid`reason],(cfill r`msg;cfill r`rptopt)];};
