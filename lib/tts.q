//BaiDu TTS engine & XunfeiYun API(use https://github.com/asatirahul/cryptoq)

\l Tx/lib/cryptoq_binary.q
\l Tx/lib/cryptoq.q
\l Tx/lib/extutil.q

.lib.BDTTSAPPKEY:"tTVgLF4uUt78U636QrT1EUjI";
.lib.BDTTSAPPSECRET:"5Godp401IkoGFisFlZL1Ahbd01ixtXSv";
.lib.BDTTSTOKEN:"";
.lib.BDTTSEXPIRE:0Np;

.lib.XFAPPID:"a4cd2122";
.lib.XFAPISecret:"MmIxYzM5OGI0ODgzYzRhODJkNGNiODlh";
.lib.XFAPIKey:"b2804e74d36fbc804ac33c6f8dc1330f";

.lib.XFAPIHOST:"ws-api.xfyun.cn";
.lib.XFISEHOST:"ise-api.xfyun.cn";

.lib.XFTTSURL:"/v2/tts";
.lib.XFIATURL:"/v2/iat";
.lib.XFISEURL:"/v2/open-ise";
.lib.XFISEMAXLEN:20000;

.lib.XFFUN:0N;
.lib.XFWS:0Ni;
.lib.XFBUF:"";

.temp.C:.temp.L:();

getbdtoken:{[x;y]if[count[.lib.BDTTSTOKEN]&.z.P<.lib.BDTTSEXPIRE;:.lib.BDTTSTOKEN];t:.z.P;.lib.r:r:.j.k .Q.hg "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=",x,"&client_secret=",y;z:r`access_token;.lib.BDTTSTOKEN:z;.lib.BDTTSEXPIRE:t+0D00:00:01*`long$r`expires_in;z};

getbdaudioex:{[x;y;z].Q.hg "http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=123456&per=1&spd=5&pit=5&vol=9&aue=3&tok=",getbdtoken[x;y],"&tex=",.h.hu z};
getbdaudio:getbdaudioex[.lib.BDTTSAPPKEY;.lib.BDTTSAPPSECRET];

ttsread:{[x]`:/tmp/bdtts.mp3 1: `byte$getbdaudio[x];system "mpg321 -q ",p:"/tmp/bdtts.mp3";p};

cb_ws:cb_tts:cb_iat:cb_ise:{[x]};

.z.ws:{[x]h:.z.w;.temp.X:(h;x);.temp.L,:enlist (.z.P;h;x);$[10h=type x;$[0=.lib.XFFUN;on_xftts[x];1=.lib.XFFUN;on_xfiat[x];2=.lib.XFFUN;on_xfise[x];0N!x];cb_ws[x]];};

on_xftts:{[x].temp.x0:x;r:.j.k x;if[0<r`code;:()];st:r[`data;`status];.lib.XFBUF,:.cryptoq.b64_decode r[`data;`audio];if[2=st;`:/tmp/xftts.mp3 1: `byte$.lib.XFBUF;system "mpg321 -q /tmp/xftts.mp3"];cb_tts[x];};

on_xfiat:{[x].temp.x1:x;r:.j.k x;if[0<r`code;:()];st:r[`data;`status];re:r[`data;`result];.lib.XFBUF,:utf82gbk raze first each re[`ws;;`cw;`w];cb_iat[x];};

on_xfise:{[x].temp.x2:x;r:.j.k x;if[0<r`code;:()];st:r[`data;`status];if[st<>2;:()];.lib.XFBUF:.cryptoq.b64_decode r[`data;`data];cb_ise[x];};

rfc1123:{[x]y:string t:`datetime$x-`time$08:00;string[(til[7]!`Mon`Tue`Wed`Thu`Fri`Sat`Sun) (`date$t)-`week$t],", ",y[8 9]," ",string[(til[12]!`Jan`Feb`Mar`Api`May`Jun`Jul`Aug`Sep`Oct`Nov`Dec) -1+"J"$y[5 6]]," ",y[til 4]," ",y[11+til 8]," GMT"}; /将本地时间转化为rfc1123时间戳字符串(EEE, dd, MMM yyyy HH:mm:ss GMT),eg:Thu, 01 Aug 2019 01:53:21 GMT

urlencode:{[x]ssr[;":";"%3A"] ssr[;",";"%2C"] ssr[;" ";"+"] x};

xfinit:{[x].lib.XFFUN:x;.lib.XFBUF:"";rfcnow:rfc1123[.z.Z];host:(til[3]!.lib[`XFAPIHOST`XFAPIHOST`XFISEHOST]) x;path:(til[3]!.lib[`XFTTSURL`XFIATURL`XFISEURL]) x;sig:.cryptoq.b64_encode .cryptoq.hmac_sha256[.lib.XFAPISecret;"host: ",host,"\ndate: ",rfcnow,"\nGET ",path," HTTP/1.1"];auth:.cryptoq.b64_encode "api_key=\"",.lib.XFAPIKey,"\", algorithm=\"hmac-sha256\", headers=\"host date request-line\", signature=\"",sig,"\"";url:path,"?authorization=",auth,"&date=",urlencode[rfcnow],"&host=",host;r:(`$":ws://",host) c:"GET ",url," HTTP/1.1\r\nHost: ",host,"\r\n\r\n";.temp.C,:enlist (.z.P;x;c);.lib.XFWS:$[0<r[0];r[0];0Ni];r}; /[x:0->tts(语音合成),1->iat(语音听写),2->ise(语音评测)]

xftts:{[x]if[1=count x;x:enlist x];xfinit[0];if[0>=.lib.XFWS;:()];neg[.lib.XFWS] c:.j.j `common`business`data!(enlist[`app_id]!enlist .lib.XFAPPID;`aue`sfl`auf`vcn`tte!(`lame;1;`$"audio/L16;rate=16000";`xiaoyan;`utf8);`status`text!(2;.cryptoq.b64_encode gbk2utf8 x));.temp.C,:enlist (.z.P;`tts;c);}; /[text]语音合成

xfiat:{[lang;x]xfinit[1];if[0>=.lib.XFWS;:()];if[0>=count y:@[read1;x;()];:()];neg[.lib.XFWS] c:.j.j `common`business`data!(enlist[`app_id]!enlist .lib.XFAPPID;`domain`language`accent`vinfo`vad_eos!(`iat;lang;`mandarin;1;10000);`status`format`encoding`audio!(2;`$"audio/L16;rate=16000";`lame;.cryptoq.b64_encode `char$y));.temp.C,:enlist (.z.P;`iat;c);}; /[lang;mp3 file path]语音识别 neg[.lib.XFWS] .j.j enlist[`data]!enlist enlist[`status]!enlist[2];
xfiatcn:xfiat[`zh_cn];xfiaten:xfiat[`en_us];

xfise:{[lang;cat;text;x]xfinit[2];if[0>=.lib.XFWS;:()];if[0>=count y:@[read1;x;()];:()];neg[.lib.XFWS] c:.j.j `common`business`data!(enlist[`app_id]!enlist .lib.XFAPPID;`category`sub`ent`cmd`auf`aue`tte`text`ttp_skip`aus!(cat;`ise;lang;`ssb;`$"audio/L16;rate=16000";`lame;`gbk;text;1b;1);enlist[`status]!enlist[0]);.temp.C,:enlist (.z.P;`ise;c);b:.cryptoq.b64_encode `char$y;n:count B:(0N,.lib.XFISEMAXLEN)#b;au:((n-1)#1,n#2),4;st:((n-1)#1),2;{[x;y;z]neg[.lib.XFWS] c:.j.j `business`data!(`cmd`aus`aue!(`auw;x;`lame);`status`data!(y;z));.temp.C,:enlist (.z.P;`ise;c)}'[au;st;B];}; /[lang;text;mp3 file path]语音识别 
xfisecn:xfise[`cn_vip];xfiseen:xfise[`en_vip];iseenword:xfiseen[`read_word];iseensent:xfiseen[`read_sentence];

\

ttsread["test tts text"];

xftts["你好啊1234!"]
xfiatcn[`:/tmp/xftts.mp3];

iseensent["there was a gentleman live near my house";`:/tmp/read_sentence_en.mp3]
iseenword["[word]\nhouse";`:/tmp/read_word_en.mp3]; "F"$(.j.k .lib.XFBUF)[0;1;0;1;0;1;0;2]`accuracy_score