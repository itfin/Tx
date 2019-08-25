.module.api:2016.12.29;

/对于行情类消息sym为证券代码,对于日志消息sym为日志级别,对于其他类消息sym为接收方id(`ALL为全系统广播)

quote:([]time:`timespan$();sym:`symbol$(); bid:`float$(); ask:`float$(); bsize:`float$(); asize:`float$(); price:`float$(); high:`float$(); low:`float$(); vwap:`float$(); cumqty:`float$(); openint:`float$(); settlepx:`float$(); mode:`symbol$(); extime:`timestamp$(); bidQ:(); askQ:(); bsizeQ:(); asizeQ:(); quoopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /行情快照

quoteref:([]time:`timespan$(); sym:`symbol$(); pc:`float$(); open:`float$(); sup:`float$(); inf:`float$(); refopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /参考数据更新

quotereq:([]time:`timespan$(); sym:`symbol$(); reqid:`symbol$(); reqtime:`timestamp$(); actiondate:`date$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /询价请求行情

ordnew:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); tif:`char$(); typ:`char$(); qty:`float$(); price:`float$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /委托请求 

ordcxl:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); cid:`symbol$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /撤单请求

exerpt:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); feoid:`symbol$(); ordid:`symbol$(); cstatus:`char$(); cfeoid:`symbol$(); cordid:`symbol$(); reason:`long$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /执行报告

exenoe:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); ordid:`symbol$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /NOE执行报告

cxlrej:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cordid:`symbol$(); reason:`long$(); msg:(); isrpl:`boolean$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /撤单拒绝 

ordqry:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /查单请求

ordrpl:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); cid:`symbol$(); ordopt:(); qty:`float$(); price:`float$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /改单请求

reqquote:([]time:`timespan$(); sym:`symbol$(); qsym:`symbol$(); qrid:`symbol$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /询价请求

quotenew:([]time:`timespan$(); sym:`symbol$(); qid:`symbol$(); qrid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); qsym:`symbol$(); bid:`symbol$(); aid:`symbol$(); bprice:`float$(); aprice:`float$(); bqty:`float$(); aqty:`float$(); bposefct:`char$(); aposefct:`char$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /报价委托

quoteack:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); qid:`symbol$(); status:`char$(); bcumqty:`float$(); acumqty:`float$(); bavgpx:`float$(); aavgpx:`float$(); feqid:`symbol$(); quoteid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cfeqid:`symbol$(); cquoteid:`symbol$(); reason:`long$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /报价应答

quotecxl:([]time:`timespan$(); sym:`symbol$(); qid:`symbol$(); feqid:`symbol$(); cid:`symbol$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /报价撤销

sysconf:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); user:`symbol$(); item:`symbol$(); vbin:(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /系统参数操作(typ:U更新Q查询A应答)

tsparam:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); user:`symbol$(); ts:`symbol$(); item:`symbol$(); vbin:(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$());  /策略参数操作(typ:U更新Q查询A应答)

sysmsg:([]time:`timespan$(); sym:`symbol$(); typ:`symbol$(); ref:`symbol$(); msg:(); vbin:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /系统事件

syslog:([]time:`timespan$(); sym:`symbol$(); typ:`symbol$(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /系统日志