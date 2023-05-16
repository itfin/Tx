//Tx主控台管理界面
//version:2019.06.10

Functional.install();

mkmenu=function(x){
    $('#menu').tree({data:[
	{text:'设置',attributes:{func:'showconf(x)'}}, 
	{text:'总控台',children:[ 
	    {text:'监控汇总',attributes:{func:'dashboardreq(x)'}}, 
	    {text:'节点状态',attributes:{func:'nodereq(x)'}},
	    {text:'模块状态',attributes:{func:'modulereq(x)'}},
	    {text:'行情状态',attributes:{func:'quotereq(x)'}},
	    {text:'交易状态',attributes:{func:'tradereq(x)'}}, 
	    {text:'系统消息',attributes:{func:'sysmsgreq(x)'}}, 
	    {text:'系统告警',attributes:{func:'logreq(x)'}}, 
	]}, 
	{text:'各ft模块',attributes:{func:'ftlistreq(x)'}}, 
    ],onClick:function(x){eval(x.attributes.func);}});
};

var ALERTLIST=[];

go=function(x){$('#ctrl').html('');$('#plot').html('');$('#grid').html('<iframe style="width:100%;height:100%;frameborder:0;border:0;;" src="'+x.attributes.url+'">');};

popup=function(x){window.open('http://'+host+':'+x+'/=.h.txhome%5b%5d','_blank');}

ftlistreq=function(x){wscall('flip value flip select id,port from .ctrl.MOD where mtyp=`ft,h>0',ftlistres,{node:x});}

ftlistres=function(x,y){
    var data=map("{text:x[0],attributes:{func:'popup('+x[1]+')'}}",y);
    //    alert($.toJSON(data[0]));
    if(x.node.children == undefined)$('#menu').tree('append',{parent:x.node.target,data:data,});
};

//设置
showconf=function(){
    var x=$('input[name=ufreq]:checked').val();
    $('#ctrl').html('自动刷新:<input type=radio name=ufreq value=0 '+(((x==undefined)||(x==0))?'checked':'')+'>无<input type=radio name=ufreq value=1 '+((x==1)?'checked':'')+'>1秒<input type=radio name=ufreq value=5 '+((x==5)?'checked':'')+'>5秒<input type=radio name=ufreq value=30 '+((x==30)?'checked':'')+'>30秒<input type=radio name=ufreq value=60 '+((x==60)?'checked':'')+'>60秒<input type=radio name=ufreq value=120 '+((x==120)?'checked':'')+'>120秒,最近刷新:<input type=text id=updtime size=10></input>'); 
}

//仪表盘
dashboardreq=function(){wscall(["{cm:exec (n,'c)!m from select sv[`] ((n[0],`$string c[0]),distinct m) by n,c from flip `m`n`c!flip raze exec (id,'node) {x,/:y}'cores from .ctrl.MOD;`nodkey`cpu`mem`modkey`delay`mmem`corekey`ccpu!(string `t,.conf.ha.nodelist;value flip 0!(uj/) {1!(`t,x) xcol select string `minute$stime,cpu from .temp.NS where id=x,5>weekday `date$stime} each .conf.ha.nodelist;value flip 0!(uj/) {1!(`t,x) xcol select string `minute$stime,mem from .temp.NS where id=x,5>weekday `date$stime} each .conf.ha.nodelist;string `t,.conf.modules;value flip 0!(uj/) {1!(`t,x) xcol select string `minute$stime,delay from .temp.MS where id=x,5>weekday `date$stime} each .conf.modules;value flip 0!(uj/) {1!(`t,x) xcol select string `minute$stime,mem from .temp.MS where id=x,5>weekday `date$stime} each .conf.modules;value cm;value flip 0!(uj/) {1!(`t,sv[`] x[0],`$string x[1]) xcol select string `minute$stime,cpu from (ungroup select stime,id,c:{til count[x]} each cores,cpu:cores from .temp.NS) where id=x[0],c=x[1],5>weekday `date$stime} each key cm)}",'`'],dashboardres,{target:'grid'});}
dashboardres=function(x,y){
    $('#main').layout('panel','south').panel('resize',{height:'50px'});$('#main').layout('resize');
	
    $('#'+x.target).html('<div id=db0 style="width:1200px; height: 750px;">');
    var d=y.NS;
    var chart1=echarts.init($('#db0')[0]);
    var option1={title:[{left:'13%',top:'10%',textAlign:'center',text:'cpu'},{left:'46%',top:'10%',textAlign:'center',text:'mem'},{left:'79%',top:'10%',textAlign:'center',text:'delay'},{left:'15%',top:'55%',textAlign:'center',text:'mmem'},{left:'65%',top:'55%',textAlign:'center',text:'mcpu'}],legend:{},tooltip:{},dataset:[{dimensions:y.nodkey,source:y.cpu,sourceHeader:false},{dimensions:y.nodkey,source:y.mem,sourceHeader:false},{dimensions:y.modkey,source:y.delay,sourceHeader:false},{dimensions:y.modkey,source:y.mmem,sourceHeader:false},{dimensions:y.corekey,source:y.ccpu,sourceHeader:false}],grid:[{left:'3%',top:'13%',width:'30%',height:'38%'},{left:'36%',top:'13%',width:'30%',height:'38%'},{left:'69%',top:'13%',width:'28%',height:'38%'},{left:'5%',top:'58%',width:'42%',height:'36%'},{left:'55%',top:'58%',width:'42%',height:'36%'}],xAxis:[{type: 'category',gridIndex:0},{type: 'category',gridIndex:1},{type: 'category',gridIndex:2},{type: 'category',gridIndex:3},{type: 'category',gridIndex:4}],yAxis:[{gridIndex:0},{gridIndex:1},{gridIndex:2},{gridIndex:3},{gridIndex:4}],series:map("{datasetIndex:0,type:'line',seriesLayoutBy:'row'}",y.nodkey).concat(map("{datasetIndex:1,type:'line',seriesLayoutBy:'row',xAxisIndex:1,yAxisIndex:1}",y.nodkey)).concat(map("{datasetIndex:2,type:'line',seriesLayoutBy:'row',xAxisIndex:2,yAxisIndex:2}",y.modkey)).concat(map("{datasetIndex:3,type:'line',seriesLayoutBy:'row',xAxisIndex:3,yAxisIndex:3}",y.modkey)).concat(map("{datasetIndex:4,type:'line',seriesLayoutBy:'row',xAxisIndex:4,yAxisIndex:4}",y.corekey))};    
    chart1.setOption(option1);
};


//本地告警
logreq=function(){wscall(['{[x].ctrl.MOD[`rdb;`h] ({[x]desc select [neg[x]] seq:i,string `time$time,src,sym,typ,sublist[400] each msg from syslog where sym in `error`warn};200)}','`'],logres,{target:'grid'});}
logres=function(x,y){
    $('#'+x.target).html('<div id=loglst>');
    $('#loglst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'time',title:'时间',width:80,sortable:true},{field:'seq',title:'序号',width:80,sortable:true},{field:'src',title:'来源',width:80,sortable:true},{field:'sym',title:'级别',width:80,sortable:true},{field:'typ',title:'类别',width:280,sortable:true},{field:'msg',title:'信息',width:880,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#loglst').datagrid('loadData',{total:y.length,rows:y});
};

//节点状态
nodereq=function(){wscall('select id,backup,ip,portoffset,cpufreq,cpucores,mem,swap,diskdev,disk,string uptime,cpuuse*1e2,memuse*1e2,swapuse*1e2,diskuse*1e2,{sv[" "] except[;" "] each .Q.fmt[6;2] each desc x} each coreuse*1e2 from .ctrl.NOD',noderes,{target:'grid'});}
noderes=function(x,y){
    $('#'+x.target).html('<div id=nodelst>');
    $('#nodelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'id',title:'节点ID',width:80,sortable:true},{field:'backup',title:'备份节点',width:60,sortable:true},{field:'ip',title:'节点IP',width:100,sortable:true},{field:'portoffset',title:'端口偏移',width:60,sortable:true},{field:'cpufreq',title:'CPU主频(GHz)',width:80,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'cpucores',title:'CPU核数',width:60,sortable:true},{field:'mem',title:'物理内存(G)',width:90,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'swap',title:'交换文件(G)',width:90,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'diskdev',title:'数据盘设备',width:100,sortable:true},{field:'disk',title:'数据盘容量(T)',width:90,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'uptime',title:'启动时间',width:150,sortable:true},{field:'cpuuse',title:'CPU使用(%)',width:90,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'memuse',title:'内存使用(%)',width:90,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'swapuse',title:'SWAP使用(%)',width:90,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'diskuse',title:'磁盘使用(%)',width:90,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'coreuse',title:'各核使用(%)',width:400,sortable:true}]]});
    $('#nodelst').datagrid('loadData',{total:y.length,rows:y});
};

//模块状态
modulereq=function(){wscall(['{[x]`node xasc select id,mtyp,node,ip,port,string cores,h,pid,string starttime,string stoptime,string hbsent,string hbpeer,string hbrecv,delay:1e-9*hbrecv-hbsent,mem from .ctrl.MOD}','`'],moduleres,{target:'grid',alert:true});}
moduleres=function(x,y){
    $('#main').layout('panel','south').panel('resize',{height:'400px'});$('#main').layout('resize');
    
    $('#'+x.target).html('<div id=modlst>');
    $('#modlst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'',title:'操作',width:80,sortable:true,formatter:function(x,r){return '<a href="javascript:void(0)" onclick="ctrlmod('+((r.h>0)?0:1)+',\'`'+r.id+'\')">'+((r.h>0)?'停止':'启动')+'</a>';}},{field:'id',title:'模块ID',width:80,sortable:true},{field:'mtyp',title:'类型',width:40,sortable:true},{field:'node',title:'节点',width:40,sortable:true},{field:'ip',title:'IP',width:100,sortable:true},{field:'port',title:'端口',width:40,sortable:true},{field:'cores',title:'绑定核',width:40,sortable:true},{field:'h',title:'句柄',width:40,sortable:true},{field:'pid',title:'进程号',width:40,sortable:true},{field:'starttime',title:'启动时间',width:180,sortable:true},{field:'stoptime',title:'停止时间',width:180,sortable:true},{field:'hbsent',title:'心跳发送',width:180,sortable:true},{field:'hbpeer',title:'心跳接收',width:180,sortable:true},{field:'hbrecv',title:'心跳确认',width:180,sortable:true},{field:'delay',title:'心跳耗时(s)',width:80,sortable:true,formatter:function(x){return x.toFixed(4);}},{field:'mem',title:'内存占用(M)',width:80,sortable:true,formatter:function(x){return x.toFixed(1);}}]],rowStyler:function(index,r){if (r.h<0)return 'background-color:#6293BB;color:#fff;';else if(r.delay>1) return 'background-color:green;color:#fff;';},onClickRow:function(index,r){if((r.h<0)||(r.mtyp=='tp')||(r.mtyp=='rdb')||(r.mtyp=='hdb')) return;dispreq(r.id);}});  
    $('#modlst').datagrid('loadData',{total:y.length,rows:y});
};

ctrlmod=function(x,y){if(!confirm('确认对模块'+y+'进行'+((x>0)?'启动':'停止')+'操作?')) return;wscall([((x>0)?'startmod':'stopmod'),y],ctrlmodres,{'x':x,'y':y});}
ctrlmodres=function(x,y){$('#plot').html('模块'+x.y+((x.x>0)?'启动':'停止')+'完成.');modulereq();}


//模块摘要
dispreq=function(x){wscall(['{[x]h:`_ .ctrl.H[x] (`display;());flip `k`v!(key h;(-3!) each value h)}','`'+x],dispres,{target:'plot'});}

dispres=function(x,y){
    $('#'+x.target).html('<div id=disp></div>');
    $('#disp').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'k',title:'摘要项',width:160,sortable:true},{field:'v',title:'摘要值',width:1000,sortable:true}]]});
    $('#disp').datagrid('loadData',{total:y.length,rows:y});
};

//行情信息
quotereq=function(){wscall('raze {update node:.ctrl.MOD[x;`node] from .ctrl.MOD[x;`h] "0!(select string `time$last time,n:count i by src from quote),select string `time$last time,n:count i by src from l2quote"} each exec id from .ctrl.MOD where mtyp=`rdb,h>0',quoteres,{target:'grid'});}
quoteres=function(x,y){
    $('#'+x.target).html('<div id=quotelst>');
    $('#quotelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'src',title:'行情源模块',width:80,sortable:true},{field:'time',title:'最后更新时间',width:200,sortable:true},{field:'n',title:'记录条数',width:200,sortable:true},{field:'node',title:'节点ID',width:60,sortable:true}]]});
    $('#quotelst').datagrid('loadData',{total:y.length,rows:y});
};

//交易信息
tradereq=function(){wscall('raze {update node:.ctrl.MOD[x;`node] from .ctrl.MOD[x;`h] "0!((select no:count i,lo:string `time$last time by fe:sym from ordnew) lj (select nc:count i,lc:string `time$last time by fe:sym from ordcxl)) lj select nr:count i,lr:string `time$last time by fe:src from exerpt"} each exec id from .ctrl.MOD where mtyp=`rdb,h>0',traderes,{target:'grid'});}
traderes=function(x,y){
    $('#'+x.target).html('<div id=tradelst>');
    $('#tradelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'fe',title:'执行模块',width:80,sortable:true},{field:'no',title:'委托笔数',width:60,sortable:true},{field:'lo',title:'末笔委托时间',width:200,sortable:true},{field:'nc',title:'撤单笔数',width:60,sortable:true},{field:'lc',title:'末笔撤单时间',width:200,sortable:true},{field:'nr',title:'回报条数',width:60,sortable:true},{field:'lr',title:'末笔回报时间',width:200,sortable:true},{field:'node',title:'节点ID',width:80,sortable:true}]]});
    $('#tradelst').datagrid('loadData',{total:y.length,rows:y});
};

//
sysmsgreq=function(){wscall('raze {update node:.ctrl.MOD[x;`node] from .ctrl.MOD[x;`h] "select string `time$time,sym,typ,ref,msg,src,string srctime,srcseq from sysmsg where 0=count each vbin"} each exec id from .ctrl.MOD where mtyp=`rdb,h>0',sysmsgres,{target:'grid'});}
sysmsgres=function(x,y){
    $('#'+x.target).html('<div id=msglst>');
    $('#msglst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'time',title:'时间',width:80,sortable:true},{field:'sym',title:'接收者',width:80,sortable:true},{field:'typ',title:'类别',width:80,sortable:true},{field:'ref',title:'关联项',width:80,sortable:true},{field:'src',title:'发送者',width:80,sortable:true},{field:'srctime',title:'发送时间',width:180,sortable:true},{field:'srcseq',title:'发送序号',width:80,sortable:true},{field:'msg',title:'信息',width:480,sortable:true},{field:'node',title:'所在节点',width:80,sortable:true}]]});
    $('#msglst').datagrid('loadData',{total:y.length,rows:y});
};

