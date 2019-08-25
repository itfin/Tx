.module.fabase:2017.08.17;

ccfx_rank:{[x;y]z:"http://www.cffex.com.cn/sj/ccpm/",((string `month$y) except "."),"/",(-2#string y),"/",(string x),".xml";s:wget[z];d:xmlparse[s];t:flip `instrumentId`tradingDay`dataTypeId`rank`shortname`volume`varVolume`partyid`productid!"SDJJSFFSS"$'flip {x where 9=count each x} d[0;1;;1;;1];t} /[product;date]{dataTypeId|0->成交量;1->持买单量;2->持卖单量}


rankinit:{[].db.T:raze @[ccfx_rank[`IH];;()] each .ctrl.conn.hdb.h `date;.temp.S:update s:?[lc>0;?[sc<0;1;0];?[sc>0;-1;0]] from (select lc:sum varVolume by tradingDay from .db.T where dataTypeId=1) lj select sc:sum varVolume by tradingDay from .db.T where dataTypeId=2;};

rankupd:{[x;y].db.T,:@[ccfx_rank[`IH];;()] .z.D;.temp.S:update s:?[lc>0;?[sc<0;1;0];?[sc>0;-1;0]] from (select lc:sum varVolume by tradingDay from .db.T where dataTypeId=1) lj select sc:sum varVolume by tradingDay from .db.T where dataTypeId=2;1b};

jsl_div:{[]r:.j.k wget "https://www.jisilu.cn/data/stock/dividend_rate_list_hk/";select sym:`$(,\:)[(string "I"$stock_id);".XHKG"],mv:"F"$total_value,"F"$price,cumqty:"F"$volume,"F"$pe,"F"$pb,roe:1e-2*"F"$(-1_) each roe_ttm,div1:1e-2*"F"$(-1_) each dividend_rate,div2:1e-2*"F"$(-1_) each dividend_rate2,div3:1e-2*"F"$(-1_) each dividend_rate3,div4:1e-2*"F"$(-1_) each dividend_rate4,epsg:1e-2*"F"${[x]y:(2+0^ss[x;"\">"][0])_ x;ss[y;"%"]#y} each eps_growth_ttm,divt:"F"$accu_dividend,shares:"F"$total_shares from r[`rows;`cell]};


\
.db.TASK[`RANKUPD;`firetime`firefreq`weekmin`weekmax`handler]:(`timestamp$.z.D+16:00:00;1D;0;4;`rankupd);

t:select last y by sym,d from select from (delete from (update y:(0n,1_deltas log c) by sym from delete t from select from BARD1 where d>=2016.07.08) where null y) where 231<(count;i) fby sym,250<(min;n) fby sym;ns:count s:asc exec distinct sym from t;nd:count d:asc exec distinct d from t;my:(ns,nd)#0f^raze t[;`y] s cross d;


Needs["JLink`"];

InstallJava[CommandLine -> "java", ClassPath -> "/q/java/c.jar"];


c = JavaNew["kx.c", "localhost", 7777];
d = c@k["`$string d"];
s = c@k["\"J\"$(-5_) each (string s)"];
my= c@k["my"];
r=FindClusters[my -> s, DistanceFunction -> WarpingDistance];

c1=Correlation[Transpose[my]];
g1 = WeightedAdjacencyGraph[s, c1];
t1=FindSpanningTree[g1]; //,EdgeWeight -> -1*PropertyValue[{g1, #}, EdgeWeight] & /@ EdgeList[g1]

