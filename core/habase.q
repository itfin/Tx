.module.habase:2017.10.25;

.ha.ordnew:{[x]k:x`oid;if[not null .db.O[k;`sym];:()];.db.O[k;`ntime`status`cumqty`avgpx`lastqty`lastpx`rptopt`msg`ft`ts`acc`fe`acc1`ref`sym`side`posefct`tif`typ`qty`price`ordopt]:(.z.P;.enum`PENDING_NEW;0f;0f;0f;0f;"";""),x`ft`ts`acc`sym`acc1`ref`osym`side`posefct`tif`typ`qty`price`ordopt;};

.ha.ordcxl:{[x]k:x`oid;if[(null .db.O[k;`sym])|.db.O[k;`cid]~c:x`cid;:()];.db.O[k;`ctime`cid`cstatus]:(.z.P;c;.enum`PENDING_CANCEL);};

.ha.exerpt:{[x]r:.db.O k:x`oid;if[null r`sym;:()];.db.O[k;`status`cumqty`avgpx`feoid`ordid`cstatus`cordid`reason`msg`rptopt]:x`status`cumqty`avgpx`feoid`ordid`cstatus`cordid`reason`msg`rptopt;};

//.ha.exenoe:{[x]r:.db.O k:x`oid;if[not null r`sym;:()];.db.O[k;`ft`ts`acc`fe`acc1`ref`sym`side`posefct`status`cumqty`avgpx`ordid`msg`rptopt]:x`ft`ts`acc`src`acc1`ref`osym`side`posefct`status`cumqty`avgpx`ordid`msg`rptopt;};

.ha.quotenew:{[x]};

.ha.quotecxl:{[x]};

