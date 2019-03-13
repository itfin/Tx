.module.uibase:2019.01.08;

\d .h
ty[`htm]:"text/html;charset=gbk"; 
k).z.ph:{BH::x[1];x:uh$[@x;x;*x];if[(#x)>n:x?"?";x:n#x];$[~#x;hy[`htm]fram[$.z.f;x]("?";"?",*x:$."\\v");x~,"?";hp@{hb["?",x]x}'$."\\v";"?["~2#x;hp jx["J"$2_x]R;"?"=*x;@[{hp jx[0j]R::1_x};x;he];"="=*x;@[{hy[`htm]@. 1_x};x;he];"?"in x;@[{hy[t]@`/:tx[t:`$-3#n#x]@.(1+n:x?"?")_x};x;he];#r:@[1::;`$":",p:HOME,"/",x:(x?"?")#x;""];hy[`$(-$[(#x)>k:(|x)?".";k;0])#x]"c"$r;hn["404 Not Found";`txt]p,": not found"]}; 
k)hta:{,/("<";$x;,/" ",'($!y),'?[`checked=!y;(#y)#"";(#y)#"="],'{$[10h=abs[@x];"\"",x,"\"";$x]}'. y;">")};

k)css:{[x]""/: {hta[`link;`rel`type`href!("stylesheet";"text/css";x)]}' x};
k)jsload:{""/: {htac[`script;`type`src!("text/javascript";x);""]}' x};
k)jscode:{htac[`script;(,`type)!,"text/javascript";x]};
Td:htc[`td];Tr:htc[`tr];Th:htac[`th];Thead:htc[`thead];Tbody:htc[`tbody];Tbl:htac[`table];

cdata:{"<![CDATA[",x,"]]>"};
k)jv:{[x]$[10=abs t:@x;"'",x,"'";-11h=t;$x;-1h=t;$[x=1b;"true";"false"];-14h=t;"new Date (",($ `year$x),",",($ -1+`mm$x),",",($ `dd$x),")";-15h=t;"new Date (",($ `year$x),",",($ -1+`mm$x),",",($ `dd$x),",",($ `hh$x),",",($ `uu$x),",",($ `ss$x),",",($ {x-y*x div y}[;1000] `int$`time$x),")";-12h=t;jv "z"$x;-13h=t;jv "d"$x;-19h=t;jv .z.D+x;t in -17 -18h;jv `time$x;$x]}; /value to javascript

k)xv:{[x]$[99=t:@x;""/: (!x){[x;y]$[99=t:@y;htac[x;`.DATA. _y;xv y`.DATA.];(~0>t)&(~10=t);""/: ('[htc[x];xv])' y;htc[x] xv[y]]}' (. x);(0h=t)|(98h=t);""/: xv' x;-1h=t;$[x=1b;"true";"false"];10h=t;x;$x]}; /value to xml

input:htac[`input;;""];
button:{input[`type`value`onclick!(`button;x;y)]};

k)jsfunc:{($x),"=function(",(","/:$$[0>@y;,y;y]),"){",z,"};"};


k)txuimain:{[x;y]htc[`html](htc[`head] (htc[`title] "Tx交易平台"),css[("/themes/default/easyui.css";"themes/icon.css";"css/codemirror.css";"css/mycss.css")],jsload[("js/functional.min.js";"js/swfobject.js";"js/amstock.js";"js/jquery-1.4.4.min.js";"js/jquery.easyui.min.js";"js/jquery.json-2.3.min.js";"js/jquery.timers.js";"js/jquery.flot.min.js";"js/jquery.flot.time.min.js";"js/jquery.flot.categories.min.js";"js/jquery.flot.pie.min.js";"js/jsxgraphcore.js";"js/d3.v2.min.js";"js/echarts-gbk.js";"js/codemirror.js";"js/c.js";"js/gbk.js";"js/txlib.js";"js/txui.js")],jscode["var host='",(* ":" \: .h.BH`Host),"';wsUri='ws://'+'",(.h.BH`Host),"';$(function(){mkmenu(",($x),");initws(wsUri);});$(document).everyTime(1000,function(i){var x=$('input[name=ufreq]:checked').val();if((x==undefined)||(x==0))return;if(0==i%x){recall();$('#updtime').val(now());}});"]),algobody:htac[`body;(,`class)!,"easyui-layout"]htac[`div;(`region`border`style)!("north";"false";"height:55px;background:#B3DFDA;");htc[`center]htc[`h2]"Tx交易平台"],htac[`div;(`region`split`title`style)!("west";"true";"功能导航";"width:250px;padding:10px;");htac[`ul;(,`id)!,`menu;""]],htac[`div;(`id`region`border`style)!(`tip;"south";"false";"height:30px;background:#A9FACD;");"版本号:0.01",htac[`div;(`id`style)!(`now11;"");""]],htac[`div;(`id`region`class)!(`main;"center";"easyui-layout");(htac[`div;(`id`region`border`style)!(`ctrl;"north";"true";"height:25px;");""],htac[`div;(`id`region`border`split`style)!(`plot;"south";"false";"true";"height:350px;");""],htac[`div;(`id`region`border)!(`grid;"center";"false");""])]}; 

txhome:txuimain[0];
\d .

.ctrl.wsconn:.enum.nulldict;

sendws:{[x;y]neg[x] -8!y;};

.z.ws:{[x]h:.z.w;who:`$"ws_",string h;if[not h~.ctrl.wsconn[who;`h];.ctrl.wsconn[who]:.enum`nulldict;.ctrl.wsconn[who;`h`selfseq`peerseq]:(h;0N;0N)];y:-9!x;.temp.ws:(h;x;y);if[y[0]~`uim;z:y[2];if[10h=type z;y[2]:value z];if[(0h=type z)&(2=count z)&(count[first z]=count[last z]);y[2]:z[0]!z[1]];y[2]:(`who`seq!(who;0N)),y[2]];if[not (::)~r:value y;sendws[h;r]];}; /show (h;y);

.z.wc:.z.pc;

.uim.WebReg:{[x]h:.z.w;y:x`who;.ctrl.wsconn[y;`h`proto`name`role`status`conntime`ipaddr`x0`selfseq`peerseq]:(h;`ws;x`name;x`role;`Registered;.z.P;`$"." sv string "i"$0x0 vs .z.a;{$[0h=type x;x;0h<type x;(x;::);null x;();(x;::)]}x`x0;0j^.ctrl.wsconn[y;`selfseq];(x`seq)^.ctrl.wsconn[y;`peerseq]);smws[y;`RegAck;(enlist `status)!enlist `RegOK];};

.uim.WebCall:{[x]y:x`who;smws[y;`CallRes;`cid`res!(x`cid;value x`exp)];};

uim:{[x;y]t0:.z.P;z:y`who;w:y`seq;r:.[{[x;y].uim[x;y]};(x;y);`trap];($[`trap~r;lerr;ldebug])[`uim;(z;w;x;r;count y`data;1e-6*`long$.z.P-t0)];};

smws:{[x;y;z].temp.smws:(x;y;z);if[not x in key .ctrl.wsconn;lwarn[`SmWsNoPeer;x];:()];h:.ctrl.wsconn[x;`h];if[0>h;if[not 1b~.ctrl.wsconn[x;`errmode];.ctrl.wsconn[x;`errmode]:1b;lwarn[`SmWsNoLink;(x;h)]];:()];t0:.z.P;u:0N;if[0<h;.ctrl.wsconn[x;`selftime];now[]];z:(`who`seq!(.conf.me,u)),`who`seq _ z;sendws[h;(`uim;y;z)];0}; /[target;mess;body] 


