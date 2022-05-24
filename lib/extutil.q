.module.extutil:2017.07.12;
tmpdir:{"/tmp/"};
isWIN:{0b};
xmlparse:`expat 2:(`xmlparse;1);
.ext.termtype:`qt; /`wxt

zs:{`d`P`L`G`D!(system"d"),v[1 2 3],enlist last v:value x};
k).q.dshow:{1@'`/:'("|"/:)@/:/:+:'(,').,:''((,:'w$k),'(((-1+#:'t),'w:|/#:'k:$:!:x)#'"");t:{$[(::)~x;"";.Q.S[(."\\c")-2 1;0j]x]}'x);}
z7:{[x;y;z;w]x:string x;system "7z a \"",w,z,x,".7z\" \"",y,x,"\"";}; /[date;srcdir;prefix;dstdir]
//z7syn:{fs:(-3_)each string key `$":",z7dir[];wd:fs where fs like "w*";qd:fs except wd;nd:date where date>max "D"$qd;z7[;hdbdir[];"";z7dir[]] each nd;};
rn:{[]n:string first 1?`8;tmpdir[],n};                                  /生成随机文件名(带路径，不带后缀)
jrun:{[x;y]y:"/j602/bin/",$[y;"jconsole";"jwd"];x:(" " sv  {"\"",x, "\""} each x);value $[isWIN[];"\\start ",y," -js ",x;"\\",y," -js ",(ssr[x;"`";"\\`"])," &"];};jr:jrun[;0b];jcr:jrun[;1b]; /[j语句数组;是否console方式]运行j小程序
gplot:{[x;y;z]w:840 640;if[1<count z;w:z[1];z:z[0]];(`$":",y,".cmd") 0: $[z;("set terminal png transparent nocrop enhanced font arial 8 size ","," sv string w;"set output '",y,".png'");$[isWIN[];();(enlist "set terminal ",string .ext.termtype)]],("set autoscale";"set grid"),x,enlist enlist "q";system $[isWIN[];"start \\bin\\gnuplot ";"gnuplot "],$[z;"";$[isWIN[];"-persist ";"-p "]],y,".cmd";$[z;y,".png";()]}; /[命令序列;临时文件名;是否] 执行gnuplot绘图

pd:{[x;y;e;f]z:rn[];if[not 0=type e;e:enlist e];xt:$[0=type x;$[0=type x 0;type x[0;0];type x 0];type x];
        $[xt in 13 14 17 18 19h;e,:(enlist "set xdata time"),("set timefmt ";"set format x "),\:"'",$[14h=xt;"%Y.%m.%d";13h=xt;"%Y.%m";17h=xt;"%H:%M";18h=xt;"%H:%M:%S";""],"'";()];
	/写入数据文件
	(`$":",z,".dat") 0: $[0=type x;
			    	     $[0=type x 0;
				     	      ({x,("";""),y}/) {{" " sv x} each string flip x} each x; /3d(datasets):((x;y);(t;o;h;l;c),...)
				     	      {" " sv x} each string flip x]; /2d:(x;y)或(t;o;h;l;c)
					      string x]; /1d:y
        /根据格式描述进行图元分组,用于3d+Multiplot					      					      
	gp:$[0=type y 0;
		    {(til count x),'(0^prev sums x),'x} count each y;
		    enlist 0,0,count x]; /((格式序号;数据起始位置;数据长度);...)
	if[not 0=type y 0;y:enlist y];
	cmd:e,{[x;y;z;w]u:z,".dat";
		x:x[(w 1)+til w 2];
		y:y w 0;
	"plot ", $[(0=type x 0);
	       "," sv (til count x) ({[x;y;z;w;u]x+:w 1;"'",y,"' i ",(string x)," u ",({":" sv string 1+ til x} u)," ",(z x&-1+count z)}[;u;$[0=type y;y;enlist y];w;])' count each x; /3d
	       "'",u,"' u ",({":" sv string 1+ til x} count $[0=type x;x;x[0]])," ",y] /1d|2d
	       }[x;y;z;] each gp;
	gplot[cmd;z;f]}; /[数据描述;格式描述;前缀语句;文件输出标志]调用gnuplot制图,gp:根据style分组
pds:pd[;;;0b];pdf:pd[;;;1b];pdfs:{[x;y;z;w]pd[x;y;z;(1b;w)]} /pds:屏幕输出,pdf:文件输出
/p?:[数据描述] pb:画饼图;pc:画点图;pl:画线图.pk:画K线图,[x]:1d.y;2d.(x;y).3d.((x;y);(t;o;h;l;c);...)
pb:pds[;"w boxes";"set key off"];pbf:pdf[;"with boxes";"set key off"];
pc:pds[;"w p";"set key off"];pcf:pdf[;"with p";"set key off"];
pl:pds[;"w lp ps 0.4 pt 6";"set key off"];plf:pdf[;"w lp ps 0.4 pt 6";"set key off"];plfs:{[s;x]pdfs[x;"w lp ps 0.4 pt 6";"set key off";s]} /文件输出版本 
pk:pds[;"w candlesticks";"set key off"]; 
pe:pds[;"w errorb";"set key off"];
pl2y:{if[0h<>type x[0];x:enlist each x];pds[x;("w lp ps 0.4 pt 6 axes x1y1";"w lp ps 0.4 pt 6 axes x1y2");("set y2tics";"set key bot center outside")]}; /eg:pl2y (til 10;til 20)
plyn:{pl {(til count x;x)} each x;}; plynf:{plf {(til count x;x)} each x}; /eg:plyn (til 10;2*til 20;3*til 30)
plxyn:('[pl;{(1#x),/:enlist each 1_x}]); /eg:plyn (til 10;2*til 20;3*til 30)
plyn01:{pl {[x]n:count x;((til n)%(n-1);x)} each x;};
pkv:{pds[(-1_x;x[0 5]);(enlist "w candlesticks";enlist "with boxes");("set key off";"set tmargin 0;set bmargin 0;set lmargin 10;set rmargin 3;";"set multiplot layout 2,1")]};

httpget1:{[host;location] r:(`$":http://",host)"GET ",location," HTTP/1.1\r\nHost:",host,"\r\n\r\n";i:first r ss "\r\n\r\n";(i+4) _ r}; /对于包含"\n"的二进制内容会有问题
wget:{system "wget -O ",tmpdir[],"wget.tmp --referer=\"",x,"\" \"",x,"\"";`char$read1 `$":",tmpdir[],"wget.tmp"};httpget:{wget "http://",x,y};
qcon:{[x]value ".z.pi:{[x]x:-1_x;$[(2#x)~2#\"\\\\\";[x:2_x;$[count x;1 .Q.s @[value;x;`lerr];system \"x .z.pi\"]];(1) ",(string x)," ({.Q.s @[value;x;`rerr]};x)];}"};

sendalert:{[x]if[(not ()~key `:/q/sh/sendalert)&(.z.o in `l32`l64);@[system;"/q/sh/sendalert '",x,"'&";()]];};
sendmsg:{[x]if[(not ()~key `:/q/sh/sendmsg)&(.z.o in `l32`l64);@[system;"/q/sh/sendmsg '",x,"'&";()]];};
md5s:{2_-3!-15!x};

emailx:{[s;xu;xp;f;t;u;m] system "/usr/bin/sendemail -q -l /tmp/sendemail.log",(" -s ",s),(" -xu ",xu),(" -xp ",xp),(" -f ",f),(" -t ",t),(" -u ",u),(" -m ",m);};

inline:{[x;y;z;c]u:md5s raze z;v:(string x),"_",(string y),"_",u;w:` sv `:/q/l64,`$v,".so";if[()~key w;s:` sv `:/tmp,`$v,".c";s 0: (enlist "#include\"kcomm.h\""),$[0<count hdrs:c`h;"#include ",/: hdrs;""],(enlist "K",(string y),"(",(string x),"){"),$[0=type z;z;enlist z],enlist enlist "}";system "/usr/bin/gcc -m64 -fPIC -shared -DJ64 -DKXVER=3 -I/q/c -lpthread ",$[0<count libs:c`l;" " sv "-l",/: string libs;""]," ",(1_string s)," -o ",(1_string w);];(`$v) 2: (x;y)}; /[fun;argc;fundef;`h`l!(headers;libs)]
osiconv:inline[`osiconv;4;"size_t n,n0=z->n,n1=w->n;S s1=z->G0,s2=w->G0;iconv_t cd=iconv_open(xs,y->s);n=iconv(cd,&s1,&n0,&s2,&n1);iconv_close(cd);R ki(n1);";`h`l!(enlist "<iconv.h>";())];
iconv:{[t;f;x]y:#[3*count[x];"\000"];n:osiconv[t;f;x;y];neg[n]_y};
gbk2utf8:iconv[`UTF8;`GBK];utf82gbk:iconv[`GBK;`UTF8];u162utf8:iconv[`$"UTF-16";`UTF8];u322utf8:iconv[`$"UTF-32";`UTF8];

/
pd复杂绘图示例:
0.画k线
pk value exec date,open,high,low,close from EOYX where fsym=`000001.XSHG
1.画k线+均线
pds[(value exec date,open,high,low,close from EOYX where fsym=`000001.XSHG;(value exec date,3 mavg close from EOYX where fsym=`000001.XSHG));("w candlesticks";"w lp ps 0.4 pt 6");("set key off")]
2.画k线+均线,成交量
pds[(value exec date,open,high,low,close from EOYX where fsym=`000001.XSHG;(value exec date,3 mavg close from EOYX where fsym=`000001.XSHG);(value exec date,amount from EOYX where fsym=`000001.XSHG));(("w candlesticks";"w lp ps 0.4 pt 6");enlist "with boxes");("set key off";"set tmargin 0;set bmargin 0;set lmargin 10;set rmargin 3;set xrange [1991:2011]";"set multiplot layout 2,1")]
3.画k线+均线,成交量,OBV
pds[(value exec date,open,high,low,close from EOYX where fsym=`000001.XSHG;(value exec date,3 mavg close from EOYX where fsym=`000001.XSHG);(value exec date,amount from EOYX where fsym=`000001.XSHG);(value exec date,sums amount*signum 0f^close-prev close from EOYX where fsym=`000001.XSHG));(("w candlesticks";"w lp ps 0.4 pt 6");enlist "with boxes";enlist "w lp ps 0.4 pt 6") ;("set key off";"set tmargin 0;set bmargin 0;set lmargin 10;set rmargin 3;set xrange [1991:2011]";"set multiplot layout 3,1")]

f:inline[`test;1;"R ki(xi+1);"];
g:inline[`test1;1;"K v=k(0,\"f\",r1(x),(K)0);R ki(1+v->i);"];
h:inline[`test2;1;"C b[8];kstrncpy(b,x,8);R ks(b);"];



