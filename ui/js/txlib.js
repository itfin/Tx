sw=screen.width;sh=screen.height;gw=sw-160;gh=(sh-100)/2;

function selectElement(element) {
    if (window.getSelection) {
        var sel = window.getSelection();
        sel.removeAllRanges();
        var range = document.createRange();
	range.selectNode(element);
        range.selectNodeContents(element);
        sel.addRange(range);
    } else if (document.selection) {
        var textRange = document.body.createTextRange();
        textRange.moveToElementText(element);
        textRange.select();
    }
}

function jsfill(x){
    return '""'+x+'""';
}

function fill(x,y){
    if (y==undefined) y = '`';
    if((x==undefined)) return y;
    return x;
}

function pad(l,i,s) {
    var o = i.toString();
    if (!s) { s = '0'; }
    while (o.length < l) {
	o = s + o;
    }
    return o;
}

function now(){
    var d = new Date();
    var h=d.getHours();
    var m=d.getMinutes();
    var s=d.getSeconds();

    return pad(2,h)+':'+pad(2,m)+':'+pad(2,s);
}

var ws,wsUri;
var CALL={};
var CALLTIME={};
var CID=1;

sendws=function(x){ws.send(serialize(x));};

var LASTCALL=[];

wscall=function(expr,cb,opt){
    LASTCALL=[expr,cb,opt];
    var x=''+CID;
    $('#tip').html('Waiting...');
    CALL[x]=cb.curry(opt);
    CALLTIME[x]=new Date();
    sendws(['`uim','`WebCall',{'cid':x,'exp':expr}]);
    CID++;
};

recall=function(){
    var expr=LASTCALL[0];
    var cb=LASTCALL[1];
    var opt=LASTCALL[2];
    wscall(expr,cb,opt);
};

dispatch=function(x){
    var m,r;
//    $('#tip').html('Finished.');
//    $('#tip').html($.toJSON(x));
    if((3==x.length)&&('uim'==x[0])){
	m=x[1];r=x[2];
	if(m=='RegAck'){
	    $('#tip').html('Reg ok.');
	}else if(m=='CallRes'){
	    if(r.errno){
		$('#tip').html('[ERROR]'+r.errmsg+'!');
	    }else{
		var t0=new Date();
		CALL[r.cid](r.res);
		var t1=new Date();
		$('#tip').html('['+now()+']('+((t0-CALLTIME[r.cid])/1000)+','+((t1-t0)/1000)+')Finished.');
	    }
	}else{
	    $('#tip').html('Unsupport msgtype:'+m+'!');
	}
    }else{
	$('#tip').html('Unknown error!');
    }
};

initws=function(x){
    ws=new WebSocket(x);
    ws.binaryType='arraybuffer';
    ws.onopen=function(e){sendws(['`uim','`WebReg',{role:'`GUI'}]);};
    ws.onclose=function(e){$('#tip').html('WSclosed.');}; 
    ws.onerror=function(e){$('#tip').html('WSerror.');}; 
    ws.onmessage=function(e){var d=e.data;if(d)dispatch(deserialize(d));};
}

qtime2date=function(x){
    var d=new Date();
    d.setUTCHours(x.substr(0,2),x.substr(3,2),x.substr(6,2));
    return d;
}

qdate2date=function(x){
    return (10==x.length)?(new Date(Date.parse(x.replace(/\./g,'-')))):(new Date());
}

date2qdate=function(x){
    return x.getFullYear()+'.'+pad(2,(1+x.getMonth()))+'.'+pad(2,x.getDate());
}

dateprev=function(x,y){
    return  new Date(x-y*24*60*60*1000);
}

function transpose(a){
  return Object.keys(a[0]).map(function(c){return a.map(function(r){return r[c];});});
}

CodeMirror.defineMode("q",function(config){
  var indentUnit=config.indentUnit,
      curPunc,
      keywords=buildRE(["abs","acos","aj","aj0","all","and","any","asc","asin","asof","atan","attr","avg","avgs","bin","by","ceiling","cols","cor","cos","count","cov","cross","csv","cut","delete","deltas","desc","dev","differ","distinct","div","do","each","ej","enlist","eval","except","exec","exit","exp","fby","fills","first","fkeys","flip","floor","from","get","getenv","group","gtime","hclose","hcount","hdel","hopen","hsym","iasc","idesc","if","ij","in","insert","inter","inv","key","keys","last","like","list","lj","load","log","lower","lsq","ltime","ltrim","mavg","max","maxs","mcount","md5","mdev","med","meta","min","mins","mmax","mmin","mmu","mod","msum","neg","next","not","null","or","over","parse","peach","pj","plist","prd","prds","prev","prior","rand","rank","ratios","raze","read0","read1","reciprocal","reverse","rload","rotate","rsave","rtrim","save","scan","select","set","setenv","show","signum","sin","sqrt","ss","ssr","string","sublist","sum","sums","sv","system","tables","tan","til","trim","txf","type","uj","ungroup","union","update","upper","upsert","value","var","view","views","vs","wavg","where","where","while","within","wj","wj1","wsum","xasc","xbar","xcol","xcols","xdesc","xexp","xgroup","xkey","xlog","xprev","xrank"]),
      E=/[|/&^!+:\\\-*%$=~#;@><,?_'\"\[\(\]\)\s{}]/;
  function buildRE(w){return new RegExp("^("+w.join("|")+")$");}
  function tokenBase(stream,state){
    var sol=stream.sol(),c=stream.next();
    curPunc=null;
    if(sol)
      if(c=="/")
        return(state.tokenize=tokenLineComment)(stream,state);
      else if(c=="\\"){
        if(stream.eol()||/\s/.test(stream.peek()))
          return stream.skipToEnd(),/^\\\s*$/.test(stream.current())?(state.tokenize=tokenCommentToEOF)(stream, state):state.tokenize=tokenBase,"comment";
        else
          return state.tokenize=tokenBase,"builtin";
      }
    if(/\s/.test(c))
      return stream.peek()=="/"?(stream.skipToEnd(),"comment"):"whitespace"; 
    if(c=='"')
      return(state.tokenize=tokenString)(stream,state);
    if(c=='`')
      return stream.eatWhile(/[A-Z|a-z|\d|_|:|\/|\.]/),"symbol";
    if(("."==c&&/\d/.test(stream.peek()))||/\d/.test(c)){
      var t=null;
      stream.backUp(1);
      if(stream.match(/^\d{4}\.\d{2}(m|\.\d{2}([D|T](\d{2}(:\d{2}(:\d{2}(\.\d{1,9})?)?)?)?)?)/)
      || stream.match(/^\d+D(\d{2}(:\d{2}(:\d{2}(\.\d{1,9})?)?)?)/)
      || stream.match(/^\d{2}:\d{2}(:\d{2}(\.\d{1,9})?)?/)
      || stream.match(/^\d+[ptuv]{1}/))
        t="temporal";
      else if(stream.match(/^0[NwW]{1}/)
      || stream.match(/^0x[\d|a-f|A-F]*/)
      || stream.match(/^[0|1]+[b]{1}/)
      || stream.match(/^\d+[chijn]{1}/)
      || stream.match(/-?\d*(\.\d*)?(e[+\-]?\d+)?(e|f)?/))
        t="number";
      return(t&&(!(c=stream.peek())||E.test(c)))?t:(stream.next(),"error");
    }
    if(/[A-Z|a-z]|\./.test(c))
      return stream.eatWhile(/[A-Z|a-z|\.|_|\d]/),keywords.test(stream.current())?"keyword":"variable";
    if(/[|/&^!+:\\\-*%$=~#;@><\.,?_']/.test(c))
      return null;
    if(/[{}\(\[\]\)]/.test(c))
      return null;
  //  console.log("Bad char "+c+" in "+stream.current());
    return"error";
  }
  function tokenLineComment(stream,state){return stream.skipToEnd(),/\/\s*$/.test(stream.current())?(state.tokenize=tokenBlockComment)(stream,state):(state.tokenize=tokenBase),"comment";}
  function tokenBlockComment(stream,state){
    var f=stream.sol()&&stream.peek()=="\\";
    stream.skipToEnd();
    if(f&&/^\\\s*$/.test(stream.current()))
      state.tokenize=tokenBase;
    return"comment";
  }
  function tokenCommentToEOF(stream,state){return stream.skipToEnd(),"comment";}
  function tokenString(stream,state){
    var escaped=false,next,end=false;
    while((next=stream.next())){
      if(next=="\""&&!escaped){end=true;break;}
      escaped=!escaped&&next=="\\";
    }
    if(end)state.tokenize=tokenBase;
    return"string";
  }
  function pushContext(state,type,col){state.context={prev:state.context,indent:state.indent,col:col,type:type};}
  function popContext(state){state.indent=state.context.indent;state.context=state.context.prev;}
  return{
    startState:function(base){
      return{tokenize:tokenBase,
             context:null,
             indent:0,
             col:0};
    },
    token:function(stream,state){
      if(stream.sol()){
        if(state.context&&state.context.align==null)
          state.context.align=false;
        state.indent=stream.indentation();
      }
      //if (stream.eatSpace()) return null;
      var style=state.tokenize(stream,state);
      if(style!="comment"&&state.context&&state.context.align==null&&state.context.type!="pattern"){
        state.context.align=true;
      }
      if(curPunc=="(")pushContext(state,")",stream.column());
      else if(curPunc=="[")pushContext(state,"]",stream.column());
      else if(curPunc=="{")pushContext(state,"}",stream.column());
      else if(/[\]\}\)]/.test(curPunc)){
        while(state.context&&state.context.type=="pattern")popContext(state);
        if(state.context&&curPunc==state.context.type)popContext(state);
      }
      else if(curPunc=="."&&state.context&&state.context.type=="pattern")popContext(state);
      else if(/atom|string|variable/.test(style)&&state.context){
        if(/[\}\]]/.test(state.context.type))
          pushContext(state,"pattern",stream.column());
        else if(state.context.type=="pattern"&&!state.context.align){
          state.context.align=true;
          state.context.col=stream.column();
        }
      }
      return style;
    },
    indent:function(state,textAfter){
      var firstChar=textAfter&&textAfter.charAt(0);
      var context=state.context;
      if(/[\]\}]/.test(firstChar))
        while (context&&context.type=="pattern")context=context.prev;
      var closing=context&&firstChar==context.type;
      if(!context)
        return 0;
      else if(context.type=="pattern")
        return context.col;
      else if(context.align)
        return context.col+(closing?0:1);
      else
        return context.indent+(closing?0:indentUnit);
    }
  };
});
CodeMirror.defineMIME("text/x-q","q");

