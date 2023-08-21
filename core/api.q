.module.api:2023.08.17;

/对于行情类消息sym为证券代码,对于日志消息sym为日志级别,对于其他类消息sym为接收方id(`ALL为全系统广播)
tailcols:`src`srctime`srcseq`dsttime;

quote:([]time:`timespan$();sym:`symbol$(); bid:`float$(); ask:`float$(); bsize:`float$(); asize:`float$(); price:`float$(); high:`float$(); low:`float$(); vwap:`float$(); cumqty:`float$(); openint:`float$(); settlepx:`float$(); mode:`symbol$(); extime:`timestamp$(); bidQ:(); askQ:(); bsizeQ:(); asizeQ:(); quoopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /行情快照

quoteref:([]time:`timespan$(); sym:`symbol$(); pc:`float$(); open:`float$(); sup:`float$(); inf:`float$(); refopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /参考数据更新

quotereq:([]time:`timespan$(); sym:`symbol$(); reqid:`symbol$(); reqtime:`timestamp$(); actiondate:`date$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /询价请求行情

ordnew:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); tif:`char$(); typ:`char$(); qty:`float$(); price:`float$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /委托请求 

ordcxl:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); cid:`symbol$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /撤单请求

exerpt:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); feoid:`symbol$(); ordid:`symbol$(); exchid:`symbol$(); cstatus:`char$(); cfeoid:`symbol$(); cordid:`symbol$(); cexchid:`symbol$(); reason:`long$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /执行报告

exenoe:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); ordid:`symbol$(); exchid:`symbol$();  msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /NOE执行报告

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

l2quote:(tailcols _quote) uj ([]tnum:`long$();b0num:`long$();b0qtyQ:();bnum:`long$();bqty:`float$();bwap:`float$();bcnum:`long$();bcqty:`float$();bcamt:`float$();bpnum:`long$();bwtime:`time$();a0num:`long$();a0qtyQ:();anum:`long$();aqty:`float$();awap:`float$();acnum:`long$();acqty:`float$();acamt:`float$();apnum:`long$();awtime:`time$();ebnum:`long$();ebqty:`float$();ebamt:`float$();esnum:`long$();esqty:`float$();esamt:`float$();yield:`float$();execqty:`float$();winf:`float$();wsup:`float$();bbwap:`float$();bawap:`float$();flag:`symbol$()) uj tailcols#quote; /L2行情快照(成交笔数;买一买入笔数;买一前50笔委托数量数组;卖一卖出笔数;卖一前50笔委托数量数组;买入笔数;买入总量;委买均价;买入撤单笔数;买入撤单数量;买入撤单金额;买入委托价位数;买入委托成交最大等待时间;卖出笔数;卖出总量;委卖均价;卖出撤单笔数;卖出撤单数量;卖出撤单金额;卖出委托价位数;卖出委托成交最大等待时间;ETF申购笔数;ETF申购数量;ETF申购金额;ETF赎回笔数;ETF赎回数量;ETF赎回金额;债券到期收益率;权证行权数量;债券委买均价;债券委卖均价;回购加权均价/权证最低价;IOPV高精度/权证最高价)
l2queue:([]time:`timespan$();sym:`symbol$();side:`char$();price:`float$();size:`float$();num:`long$();qtyQ:();extime:`timestamp$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 1档队列
l2order:([]time:`timespan$();sym:`symbol$();side:`char$();typ:`char$();price:`float$();qty:`float$();gid:`int$();oid:`long$();origid:`long$();bizidx:`long$();extime:`timestamp$();flag:`symbol$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 逐笔委托
l2match:([]time:`timespan$();sym:`symbol$();side:`char$();typ:`char$();price:`float$();qty:`float$();amt:`float$();gid:`int$();mid:`long$();bid:`long$();aid:`long$();bizidx:`long$();extime:`timestamp$();flag:`symbol$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 逐笔成交

//----ChangeLog----
//2023.08.17:exenoe表新增exchid列
//2023.04.27:exerpt表新增exchid和cexchid两列
//2023.06.07:l2order/l2match新增flag列,l2quote在quote表基础上新加从tnum到flag的一系列列
//2023.06.09:调整l2quote的列序以解决不能正常pub的bug
\
1.当修改api表结构之后需要用dbmaint.q里的fixtable函数为历史分区增加对应列
\l dbmaint.q
fixtable[`:/kdb/txdb/usr/ha/tickdb/api;`exerpt;`:/kdb/txdb/usr/ha/tickdb/api/2023.05.16/exerpt]
2.当修改O表时，需要手工更新各ft/fe的O表和对应模块hist目录里的历史O表