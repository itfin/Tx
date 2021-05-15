//BaiDu TTS engine

.lib.BDTTSAPPKEY:"tTVgLF4uUt78U636QrT1EUjI";
.lib.BDTTSAPPSECRET:"5Godp401IkoGFisFlZL1Ahbd01ixtXSv";
.lib.BDTTSTOKEN:"";
.lib.BDTTSEXPIRE:0Np;

getbdtoken:{[x;y]if[count[.lib.BDTTSTOKEN]&.z.P<.lib.BDTTSEXPIRE;:.lib.BDTTSTOKEN];t:.z.P;.lib.r:r:.j.k .Q.hg "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=",x,"&client_secret=",y;z:r`access_token;.lib.BDTTSTOKEN:z;.lib.BDTTSEXPIRE:t+0D00:00:01*`long$r`expires_in;z};

getbdaudioex:{[x;y;z].Q.hg "http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=123456&per=1&spd=5&pit=5&vol=9&aue=3&tok=",getbdtoken[x;y],"&tex=",.h.hu z};
getbdaudio:getbdaudioex[.lib.BDTTSAPPKEY;.lib.BDTTSAPPSECRET];

ttsread:{[x]`:/tmp/bdtts.mp3 1: `byte$getbdaudio[x];system "mpg321 -q /tmp/bdtts.mp3"};

\

ttsread["test tts text"];