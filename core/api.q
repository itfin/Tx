.module.api:2023.08.17;

/������������ϢsymΪ֤ȯ����,������־��ϢsymΪ��־����,������������ϢsymΪ���շ�id(`ALLΪȫϵͳ�㲥)
tailcols:`src`srctime`srcseq`dsttime;

quote:([]time:`timespan$();sym:`symbol$(); bid:`float$(); ask:`float$(); bsize:`float$(); asize:`float$(); price:`float$(); high:`float$(); low:`float$(); vwap:`float$(); cumqty:`float$(); openint:`float$(); settlepx:`float$(); mode:`symbol$(); extime:`timestamp$(); bidQ:(); askQ:(); bsizeQ:(); asizeQ:(); quoopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /�������

quoteref:([]time:`timespan$(); sym:`symbol$(); pc:`float$(); open:`float$(); sup:`float$(); inf:`float$(); refopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /�ο����ݸ���

quotereq:([]time:`timespan$(); sym:`symbol$(); reqid:`symbol$(); reqtime:`timestamp$(); actiondate:`date$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ѯ����������

ordnew:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); tif:`char$(); typ:`char$(); qty:`float$(); price:`float$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ί������ 

ordcxl:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); cid:`symbol$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /��������

exerpt:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); feoid:`symbol$(); ordid:`symbol$(); exchid:`symbol$(); cstatus:`char$(); cfeoid:`symbol$(); cordid:`symbol$(); cexchid:`symbol$(); reason:`long$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ִ�б���

exenoe:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); oid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); osym:`symbol$(); side:`char$(); posefct:`char$(); status:`char$(); cumqty:`float$(); avgpx:`float$(); ordid:`symbol$(); exchid:`symbol$();  msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /NOEִ�б���

cxlrej:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cordid:`symbol$(); reason:`long$(); msg:(); isrpl:`boolean$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /�����ܾ� 

ordqry:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); ordopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /�鵥����

ordrpl:([]time:`timespan$(); sym:`symbol$(); oid:`symbol$(); feoid:`symbol$(); cid:`symbol$(); ordopt:(); qty:`float$(); price:`float$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /�ĵ�����

reqquote:([]time:`timespan$(); sym:`symbol$(); qsym:`symbol$(); qrid:`symbol$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ѯ������

quotenew:([]time:`timespan$(); sym:`symbol$(); qid:`symbol$(); qrid:`symbol$(); ft:`symbol$(); ts:`symbol$(); acc:`symbol$(); acc1:`symbol$(); ref:`symbol$(); qsym:`symbol$(); bid:`symbol$(); aid:`symbol$(); bprice:`float$(); aprice:`float$(); bqty:`float$(); aqty:`float$(); bposefct:`char$(); aposefct:`char$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /����ί��

quoteack:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); qid:`symbol$(); status:`char$(); bcumqty:`float$(); acumqty:`float$(); bavgpx:`float$(); aavgpx:`float$(); feqid:`symbol$(); quoteid:`symbol$(); cid:`symbol$(); cstatus:`char$(); cfeqid:`symbol$(); cquoteid:`symbol$(); reason:`long$(); msg:(); rptopt:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /����Ӧ��

quotecxl:([]time:`timespan$(); sym:`symbol$(); qid:`symbol$(); feqid:`symbol$(); cid:`symbol$(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /���۳���

sysconf:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); user:`symbol$(); item:`symbol$(); vbin:(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ϵͳ��������(typ:U����Q��ѯAӦ��)

tsparam:([]time:`timespan$(); sym:`symbol$(); typ:`char$(); user:`symbol$(); ts:`symbol$(); item:`symbol$(); vbin:(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$());  /���Բ�������(typ:U����Q��ѯAӦ��)

sysmsg:([]time:`timespan$(); sym:`symbol$(); typ:`symbol$(); ref:`symbol$(); msg:(); vbin:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ϵͳ�¼�

syslog:([]time:`timespan$(); sym:`symbol$(); typ:`symbol$(); msg:(); src:`symbol$(); srctime:`timestamp$(); srcseq:`long$(); dsttime:`timestamp$()); /ϵͳ��־

l2quote:(tailcols _quote) uj ([]tnum:`long$();b0num:`long$();b0qtyQ:();bnum:`long$();bqty:`float$();bwap:`float$();bcnum:`long$();bcqty:`float$();bcamt:`float$();bpnum:`long$();bwtime:`time$();a0num:`long$();a0qtyQ:();anum:`long$();aqty:`float$();awap:`float$();acnum:`long$();acqty:`float$();acamt:`float$();apnum:`long$();awtime:`time$();ebnum:`long$();ebqty:`float$();ebamt:`float$();esnum:`long$();esqty:`float$();esamt:`float$();yield:`float$();execqty:`float$();winf:`float$();wsup:`float$();bbwap:`float$();bawap:`float$();flag:`symbol$()) uj tailcols#quote; /L2�������(�ɽ�����;��һ�������;��һǰ50��ί����������;��һ��������;��һǰ50��ί����������;�������;��������;ί�����;���볷������;���볷������;���볷�����;����ί�м�λ��;����ί�гɽ����ȴ�ʱ��;��������;��������;ί������;������������;������������;�����������;����ί�м�λ��;����ί�гɽ����ȴ�ʱ��;ETF�깺����;ETF�깺����;ETF�깺���;ETF��ر���;ETF�������;ETF��ؽ��;ծȯ����������;Ȩ֤��Ȩ����;ծȯί�����;ծȯί������;�ع���Ȩ����/Ȩ֤��ͼ�;IOPV�߾���/Ȩ֤��߼�)
l2queue:([]time:`timespan$();sym:`symbol$();side:`char$();price:`float$();size:`float$();num:`long$();qtyQ:();extime:`timestamp$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 1������
l2order:([]time:`timespan$();sym:`symbol$();side:`char$();typ:`char$();price:`float$();qty:`float$();gid:`int$();oid:`long$();origid:`long$();bizidx:`long$();extime:`timestamp$();flag:`symbol$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 ���ί��
l2match:([]time:`timespan$();sym:`symbol$();side:`char$();typ:`char$();price:`float$();qty:`float$();amt:`float$();gid:`int$();mid:`long$();bid:`long$();aid:`long$();bizidx:`long$();extime:`timestamp$();flag:`symbol$();src:`symbol$();srctime:`timestamp$();srcseq:`long$();dsttime:`timestamp$()); /Level-2 ��ʳɽ�

//----ChangeLog----
//2023.08.17:exenoe������exchid��
//2023.04.27:exerpt������exchid��cexchid����
//2023.06.07:l2order/l2match����flag��,l2quote��quote��������¼Ӵ�tnum��flag��һϵ����
//2023.06.09:����l2quote�������Խ����������pub��bug
\
1.���޸�api��ṹ֮����Ҫ��dbmaint.q���fixtable����Ϊ��ʷ�������Ӷ�Ӧ��
\l dbmaint.q
fixtable[`:/kdb/txdb/usr/ha/tickdb/api;`exerpt;`:/kdb/txdb/usr/ha/tickdb/api/2023.05.16/exerpt]
2.���޸�O��ʱ����Ҫ�ֹ����¸�ft/fe��O��Ͷ�Ӧģ��histĿ¼�����ʷO��