
//version:2019.01.10

//sw,sh�ֱ�Ϊ��Ļ�Ŀ�͸�(��ʾ������ֱ���),����Ҫ����������Ŀ��óߴ��ٷ���ҳ��body��layout:[bw,bh]
//body=top(north,25px)+left(west,200px)+bot(south,25px)+main(center,�Զ�fit,[bw-200,bh-50])
//main=ctrl(north,30)+plot(south)+grid(center,�Զ�fit)

//browser body rectangle(bw,bh)
//top(bw,25px)=autoupd(600px)+toolbar()+info(200px)
//bot(bw,25px)=tip(300px)+output()+clock(60px)
//left(200px)
//[main] rectangle(pw,bh-80)
////ctrl(pw,30px)
////plot(350px=>ph)
////[grid]rectangle(pw,ph)

Functional.install();

var data;
var ALERTBASECNT=0;
var init=0;
var editor;
var editor1;
var h_ctrl,h_plot; 
var bw=sw,bh=sh-50;
var pw=bw-200,ph=(bh-80)/2; //plot|grid panel size
var dw=pw-100,dh=ph-75;   //div size in plot|grid panel
var gh;
var otcrunall=[[],[]];
var isrt;

mkmenu=function(x,y){
    $('#menu').tree({data:[
	{text:'�ܿ�̨',children:[ 
	    {text:'�澯��־',attributes:{func:'logreq(x)'}},
	    {text:'�쳣ί��',attributes:{func:'errordreq(x)'}}, 
	    {text:'������Ϣ',attributes:{func:'quotereq(x)'}},
	    {text:'�����ϴ�',attributes:{func:'go(x)',url:'http://'+host+':8020/q/perl/upload.pl'}},
	    {text:'�ϴ�Ŀ¼',attributes:{func:'go(x)',url:'http://'+host+':8020/upload/'}},
	    {text:'����Ŀ¼',attributes:{func:'go(x)',url:'http://'+host+':8020/download/'}},
	    {text:'NOE����',attributes:{func:'noereq(x)'}},
	    {text:'NOEǿ����־',attributes:{func:'noefreq(x)'}},	    
	    {text:'��ϼ���',attributes:{func:'pfloadreq(x)'}},
	    {text:'��ϲ�ѯ',attributes:{func:'pfviewreq(x)'}},		
	    {text:'������',attributes:{func:'basismonreq(x)'}},		
	    {text:'�Գ���',attributes:{func:'hedgesnapreq(x)'}},
	]}, 
	{text:'���м��',children:[ 
	    {text:'���в���',attributes:{func:'etfmonmmreq(x)'}},
	    {text:'����ָ��',attributes:{func:'etfmonsumreq(x)'}},
	    {text:'�Գ����',attributes:{func:'etfmonfureq(x)'}},
	    {text:'���Ի���',attributes:{func:'etfmontsreq(x)'}},
	    {text:'���ز���',attributes:{func:'etfmonrlreq(x)'}},
	    {text:'����ͼ��',attributes:{func:'axshowreq(x)'}},
	    {text:'����ͼ��1',attributes:{func:'axshowreq1(x)'}},
	]},
	{text:'�����б�',attributes:{func:'tslistreq(x)'}},
	{text:'�㷨����',attributes:{func:'algoreq(x)'}},
	{text:'��ʷ�ز�',attributes:{func:'tsbtreq(x)'}},
	{text:'�������',children:[ 
	    {text:'�������',attributes:{func:'mktbrowsereq(x)'}},	    
	]},
	    (app=='usr')?{text:'�ڻ��о�',children:[ 
	    {text:'�ɽ���Ʒ�ֲַ�',attributes:{func:'futamtreq(x)'}},
	    {text:'��Լ��ʷ��ѯ',attributes:{func:'futexreq(x)'}},
	    {text:'������ʷ��ѯ',attributes:{func:'futbasisreq(x)'}},
	    {text:'�ڻ���ĳ�',attributes:{func:'ngxreq(x)'}},
	    ]}:{text:'����'},
    ],onClick:function(x){eval(x.attributes.func);}});
    autolayout();
    showconf();
    showtoolbar();
};


autolayout=function(x){
    $('#plot').panel('resize',{height:ph});
    $('#main').layout('resize');

//    gh=$('#grid').panel('options').height;

//    alert('bw='+bw+',bh='+bh+',ph='+ph+',gh='+gh+'!');
    
    h_ctrl=$('#ctrl').panel('options').height; //north of main
    h_plot=$('#plot').panel('options').height; //south of main
}

maxgrid=function(x){
//    $('#main').layout('panel','south').panel('resize',{height:'5px'});
//    $('#main').layout('panel','north').panel('resize',{height:'5px'});
    $('#ctrl').panel('resize',{height:'1px'});
    $('#plot').panel('resize',{height:'1px'});
    $('#main').layout('resize');
}

normgrid=function(x){
    $('#ctrl').panel('resize',{height:h_ctrl});
    $('#plot').panel('resize',{height:h_plot});
    $('#main').layout('resize');
}

//�����б�
tslistreq=function(x){wscall('(.conf.app;.db.enablets)',tslistres,{node:x});}

tslistres=function(x,y){
    var data=map("{text:x,children:[{text:'ί�в�ѯ',attributes:{func:'ordreqfun('+'\"`'+x+'\"'+',0)'}},{text:'�ɽ���ѯ',attributes:{func:'matreqfun('+'\"`'+x+'\"'+',0)'}},{text:'�ֲֲ�ѯ',attributes:{func:'posreqfun('+'\"`'+x+'\"'+',0)'}},{text:'��ʷί��',attributes:{func:'ordhisreqfun('+'\"`'+x+'\"'+',0)'}},{text:'��ʷ�ɽ�',attributes:{func:'mathisreqfun('+'\"`'+x+'\"'+',0)'}},{text:'���Բ���',attributes:{func:'tsparareq('+'\"`'+x+'\"'+',0)'}},{text:'���ݼ���',attributes:{func:'csvloadreq('+'\"`'+x+'\"'+',0)'}},{text:'���ݲ�ѯ',attributes:{func:'csvviewreq('+'\"`'+x+'\"'+',0)'}},{text:'�Գ����',attributes:{func:'otchedgereq('+'\"`'+x+'\"'+',0)'}},{text:'JUMP����',attributes:{func:'otcjumpreq('+'\"`'+x+'\"'+',0)'}},{text:'��ָ����',attributes:{func:'otctermstrureq('+'\"`'+x+'\"'+',0)'}},{text:'�ʲ�����',attributes:{func:'txpnlreq('+'\"`'+x+'\"'+',0)'}},{text:'���׷ֲ�',attributes:{func:'txtransreq('+'\"`'+x+'\"'+',0)'}},{text:'�����б�',attributes:{func:'txtradesreq('+'\"`'+x+'\"'+',0)'}},{text:'�ɽ�ϸ��',attributes:{func:'txdetailreq('+'\"`'+x+'\"'+',0)'}},{text:'��������',attributes:{func:'rsplotreq('+'\"`'+x+'\"'+',0)'}},{text:'������',attributes:{func:'gridmonreq('+'\"`'+x+'\"'+',0)'}}]}",y[1]);
    var z=map('"`"+x',y[1]);
    ordqry=ordreqfun.curry(z);matqry=matreqfun.curry(z);posqry=posreqfun.curry(z);ordhisqry=ordhisreqfun.curry(z);mathisqry=mathisreqfun.curry(z);
    data.unshift({text:'ȫ������',children:[{text:'ί�в�ѯ',attributes:{func:'ordqry(x)'}},{text:'�ɽ���ѯ',attributes:{func:'matqry(x)'}},{text:'�ֲֲ�ѯ',attributes:{func:'posqry(x)'}},{text:'��ʷί��',attributes:{func:'ordhisqry(x)'}},{text:'��ʷ�ɽ�',attributes:{func:'mathisqry(x)'}}]});
    //    alert($.toJSON(data[0]));
    if(x.node.children == undefined)$('#menu').tree('append',{parent:x.node.target,data:data,});
};

//�ز⹦��
tsbtreq=function(x){wscall('.conf.feedtype=`ftbacktest',tsbtres,{node:x});}
tsbtres=function(x,y){
    if(!y)return; 
    var data=[
    	    {text:'���Թ���',attributes:{func:'algomgr(x)'}},
	    {text:'�ز����',attributes:{func:'testmgr(x)'}},
	    {text:'����ɳ��',attributes:{func:'tempcode(x)'}},
    ];
    //    alert($.toJSON(x.node.children));
    if(x.node.children == undefined)$('#menu').tree('append',{parent:x.node.target,data:data,});
};

tempcode=function(x){
    $('#ctrl').html('<input type=button value="����" onclick="savecodetemp()"><input type=button value="У��" onclick="chkcode()">');
    $('#grid').html('');
    $('#plot').html('<textarea id=temp rows=10 cols=100></textarea>');
    $('#temp').text(localStorage.CODE_TEMP);
    editor = CodeMirror.fromTextArea(document.getElementById("temp"),{lineNumbers:true,textWrapping:true,matchBrackets:true,mode:"text/x-q"});
    //$('#plot').panel('maximize',{});
    editor.setSize('100%','100%');
    //$('#grid').panel('collapse',{});
}

savecodetemp=function(){
    localStorage.CODE_TEMP=editor.getValue();   
}

chkcode=function(){
    var c=editor.getSelection();
    if(c=='')c=editor.getValue();
    wscall(['{[x]r:@[value;".tmp.f:{[]",x,"};.tmp.f[];";::];`r`errmsg!$[10h=type r;(-1;r);(0;"")]}',' '+c],chkalgores,{'target':'plot'});
}
chkalgores=function(x,y){if(y.r<0){alert(y.errmsg);}else{alert('У��ͨ��.');}};

//�ⲿ��ַ
go=function(x){$('#ctrl').html('');$('#plot').html('');$('#grid').html('<iframe style="width:100%;height:100%;frameborder:0;border:0;" src="'+x.attributes.url+'">');};

//����������
showtoolbar=function(x){
    $('#toolbar').html('<div id="symlst"style="width:1200px;float:left;background:white;"><div><div style="widdth:300px;height:100%;margin:0 0 10 10px;float:right;background:green;padding:0 0px;"><a href="javascript:void(0)" class="easyui-linkbutton" data-options="plain:true" onclick="futamtreq()">�г�</a><a href="javascript:void(0)" class="easyui-linkbutton" data-options="plain:true" onclick="futbasisreq()">����</a><a href="javascript:void(0)" class="easyui-linkbutton" data-options="plain:true" onclick="futexreq()">��Ʒ</a></div>'); //width:700px;padding:0px;
}    

//�Զ���������
showconf=function(x){
    var x=$('input[name=ufreq]:checked').val();
    $('#autoupd').html('�Զ�ˢ��:<input type=radio name=ufreq value=0 '+(((x==undefined)||(x==0))?'checked':'')+'>��<input type=radio name=ufreq value=1 '+((x==1)?'checked':'')+'>1��<input type=radio name=ufreq value=5 '+((x==5)?'checked':'')+'>5��<input type=radio name=ufreq value=30 '+((x==30)?'checked':'')+'>30��<input type=radio name=ufreq value=60 '+((x==60)?'checked':'')+'>60��<input type=radio name=ufreq value=120 '+((x==120)?'checked':'')+'>120��,���ˢ��:<input type=text id=updtime size=10></input>'); 
}


//�澯��־
logreq=function(){wscall(['{[x]select string `time$logtime,sym,typ,msg from .db.LOG where sym in `error`warn}','`'],logres,{target:'grid'});}
logres=function(x,y){
    $('#'+x.target).html('<div id=loglst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#loglst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'logtime',title:'ʱ��',width:80,sortable:true},{field:'sym',title:'����',width:80,sortable:true},{field:'typ',title:'���',width:180,sortable:true},{field:'msg',title:'��Ϣ',width:880,sortable:true}]]});
    $('#loglst').datagrid('loadData',{total:y.length,rows:y});
};

//�쳣ί��
errordreq=function(){wscall(['{[x]select ts,acc,ref,id,side,posefct,sym,qty,price,status,cumqty,avgpx,string `time$ntime,string `time$ftime,string `time$ctime,cstatus,string `time$rtime,feoid,ordid,msg from (select from .db.O where (status=.enum`REJECTED)|((status=.enum`PENDING_NEW)&(.z.P>ntime+00:00:05))|((not end)&(not null ctime)&(.z.P>ctime+00:00:05)))}','`'],ordres,{target:'grid',alert:true});}


//������Ϣ
quotereq=function(){wscall(['{[x]0!asc select time:`$string max srctime by ex from .db.QX where not null ex}','`'],quoteres,{target:'grid'});}
quoteres=function(x,y){
    $('#'+x.target).html('<div id=quotelst>');
    $('#quotelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ex',title:'������ID',width:60,sortable:true},{field:'time',title:'������ʱ��',width:200,sortable:true}]]});
    $('#quotelst').datagrid('loadData',{total:y.length,rows:y});
};


//ί�в�ѯ
ordreqfun=function(x,y){wscall(['{[x]select ts,acc,ref,id,side,posefct,sym,qty,price,status,cumqty,avgpx,string `time$ntime,string `time$ftime,string `time$ctime,cstatus,string `time$rtime,feoid,ordid,msg from .db.O where ts in x}',x],ordres,{target:'grid'});}


ordres=function(x,y){
    $('#'+x.target).html('<div id=ordlst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#ordlst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,rowStyler:function(index,row){if((row.status=='0')||(row.status=='A')){return 'background-color:#6293BB;color:#fff;font-weight:bold;';}else if((row.status=='1')){return 'background-color:green;color:#fff;font-weight:bold;';}},columns:[[{field:'ts',title:'����ID',width:160,sortable:true},{field:'acc',title:'�����ʺ�',width:60,sortable:true},{field:'ref',title:'�µ���ע',width:150,sortable:true},{field:'id',title:'ί��ID',width:80,sortable:true},{field:'side',title:'����',width:30,sortable:true},{field:'posefct',title:'��ƽ',width:30,sortable:true},{field:'sym',title:'����',width:180,sortable:true},{field:'qty',title:'����',width:60,sortable:true},{field:'price',title:'�۸�',width:60,sortable:true},{field:'status',title:'״̬',width:40,sortable:true},{field:'cumqty',title:'�ɽ�����',width:60,sortable:true},{field:'avgpx',title:'�ɽ�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'ntime',title:'����ʱ��',width:80,sortable:true},{field:'ftime',title:'�ɽ�ʱ��',width:80,sortable:true},{field:'ctime',title:'����ʱ��',width:80,sortable:true},{field:'cstatus',title:'����״̬',width:40,sortable:true},{field:'rtime',title:'�ر�ʱ��',width:80,sortable:true},{field:'feoid',title:'�걨ID',width:80,sortable:true},{field:'ordid',title:'ȷ��ID',width:110,sortable:true},{field:'msg',title:'��ע',width:500,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#ordlst').datagrid('loadData',{total:y.length,rows:y});
    $('#ordlst').datagrid('scrollTo',y.length-1);
    if((ALERTBASECNT>0)&&(0==y.length)){ALERTBASECNT=0;};
    if((x.alert==true)&&(ALERTBASECNT!=y.length)){ALERTBASECNT=y.length;alert("�쳣ί�о���!");}
}

//�ɽ���ѯ
matreqfun=function(x,y){wscall(['{[x]select ts,acc,ref,id,sym,qty,price,string `time$mtime,maker,side,posefct,cumqty,avgpx,string `time$ntime,taker,msg from (.db.M lj 1!select maker:id,ts,acc,ref,side,posefct,cumqty,avgpx,ntime,cumamt,end,msg from .db.O) where ts in x}',x],matres,{target:'grid'});}


matres=function(x,y){
    $('#'+x.target).html('<div id=matlst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#matlst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'����ID',width:160,sortable:true},{field:'acc',title:'�����ʺ�',width:60,sortable:true},{field:'ref',title:'�µ���ע',width:100,sortable:true},{field:'id',title:'�ɽ�ID',width:80,sortable:true},{field:'sym',title:'����',width:180,sortable:true},{field:'qty',title:'�ɽ�����',width:60,sortable:true},{field:'price',title:'�ɽ��۸�',width:60,sortable:true},{field:'mtime',title:'�ɽ�ʱ��',width:80,sortable:true},{field:'maker',title:'ί��ID',width:80,sortable:true},{field:'side',title:'����',width:30,sortable:true},{field:'posefct',title:'��ƽ',width:30,sortable:true},{field:'cumqty',title:'�ܳɽ�����',width:60,sortable:true},{field:'avgpx',title:'�ܳɽ�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'ntime',title:'ί��ʱ��',width:80,sortable:true},{field:'msg',title:'��ע',width:300,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#matlst').datagrid('loadData',{total:y.length,rows:y});
    $('#matlst').datagrid('scrollTo',y.length-1);
}

//�ֲֲ�ѯ
posreqfun=function(x,y){wscall(['{[x]`ts xasc select ts,acc,sym,qty:(0f^lqty)+0f^sqty,0f^lqty,0f^sqty,0f^lqty0,0f^sqty0 from .db.P where ts in x}',x],posres,{target:'grid'});}


posres=function(x,y){
    $('#'+x.target).html('<div id=poslst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#poslst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'����ID',width:160,sortable:true},{field:'acc',title:'�ֲ��ʺ�',width:60,sortable:true},{field:'sym',title:'����',width:180,sortable:true},{field:'qty',title:'���ֲ�',width:60,sortable:true},{field:'lqty',title:'��ͷ�ֲ�',width:60,sortable:true},{field:'sqty',title:'��ͷ�ֲ�',width:60,sortable:true},{field:'lqty0',title:'���ն��',width:60,sortable:true},{field:'sqty0',title:'���տղ�',width:60,sortable:true}]]});
    $('#poslst').datagrid('loadData',{total:y.length,rows:y});
}

//��ʷί��
ordhisreqfun1=function(x,y){wscall(['{[x;y;z]d0:"D"$y;d1:"D"$z;select ts,acc,ref,id,side,posefct,sym,qty,price,status,cumqty,avgpx,date:string `date$ntime,string `time$ntime,string `time$ftime,string `time$ctime,cstatus,string `time$rtime,msg from .hdb.O where ts in x,(`date$ntime) within (d0,d1)}',x,$('input[name=d0]').val(),$('input[name=d1]').val()],ordhisres,{target:'grid'});} //

ordhisreqfun=function(x,y){
    $('#ctrl').html('��ʼ����:<input type=text id=d0 name=d0></input>,��������:<input type=text id=d1 name=d1><input type=button id=ordhisbut value="��ѯ"></input>');
    $('#ordhisbut').click(ordhisreqfun1.curry(x));
    $('#grid').html('');
    $('#plot').html('');
    $('#d0').datebox({required:true});
    $('#d1').datebox({required:true,});
    $('#d0').datebox('setValue','today');
    $('#d1').datebox('setValue','today');
}

ordhisres=function(x,y){
    $('#'+x.target).html('<div id=ordhislst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#ordhislst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'����ID',width:160,sortable:true},{field:'acc',title:'�����ʺ�',width:60,sortable:true},{field:'ref',title:'�µ���ע',width:60,sortable:true},{field:'id',title:'ί��ID',width:80,sortable:true},{field:'side',title:'����',width:30,sortable:true},{field:'posefct',title:'��ƽ',width:30,sortable:true},{field:'sym',title:'����',width:180,sortable:true},{field:'qty',title:'����',width:60,sortable:true},{field:'price',title:'�۸�',width:60,sortable:true},{field:'status',title:'״̬',width:40,sortable:true},{field:'cumqty',title:'�ɽ�����',width:60,sortable:true},{field:'avgpx',title:'�ɽ�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'date',title:'��������',width:80,sortable:true},{field:'ntime',title:'����ʱ��',width:80,sortable:true},{field:'ftime',title:'�ɽ�ʱ��',width:80,sortable:true},{field:'ctime',title:'����ʱ��',width:80,sortable:true},{field:'cstatus',title:'����״̬',width:40,sortable:true},{field:'rtime',title:'�ر�ʱ��',width:80,sortable:true},{field:'msg',title:'��ע',width:500,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#ordhislst').datagrid('loadData',{total:y.length,rows:y});

}

//��ʷ�ɽ�

mathisreqfun1=function(x,y){wscall(['{[x;y;z]d0:"D"$y;d1:"D"$z;select ts,acc,ref,id,sym,qty,price,string `time$mtime,maker,side,posefct,cumqty,avgpx,date:string `date$ntime,string `time$ntime,taker,msg from (.hdb.M lj 1!select maker:id,ts,acc,ref,side,posefct,cumqty,avgpx,ntime,cumamt,end,msg from .hdb.O) where ts in x,(`date$ntime) within (d0,d1)}',x,$('input[name=d0]').val(),$('input[name=d1]').val()],mathisres,{target:'grid'});}

mathisreqfun=function(x,y){
    $('#ctrl').html('��ʼ����:<input type=text id=d0 name=d0></input>,��������:<input type=text id=d1 name=d1><input type=button id=mathisbut value="��ѯ"></input>');
    $('#mathisbut').click(mathisreqfun1.curry(x));
    $('#grid').html('');
    $('#plot').html('');
    $('#d0').datebox({required:true});
    $('#d1').datebox({required:true,});
    $('#d0').datebox('setValue','today');
    $('#d1').datebox('setValue','today');
}

mathisres=function(x,y){
    $('#'+x.target).html('<div id=mathislst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#mathislst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'����ID',width:160,sortable:true},{field:'acc',title:'�����ʺ�',width:60,sortable:true},{field:'ref',title:'�µ���ע',width:60,sortable:true},{field:'id',title:'�ɽ�ID',width:80,sortable:true},{field:'sym',title:'����',width:180,sortable:true},{field:'qty',title:'�ɽ�����',width:60,sortable:true},{field:'price',title:'�ɽ��۸�',width:60,sortable:true},{field:'mtime',title:'�ɽ�ʱ��',width:80,sortable:true},{field:'maker',title:'ί��ID',width:80,sortable:true},{field:'side',title:'����',width:30,sortable:true},{field:'posefct',title:'��ƽ',width:30,sortable:true},{field:'cumqty',title:'�ܳɽ�����',width:60,sortable:true},{field:'avgpx',title:'�ܳɽ�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'date',title:'ί������',width:80,sortable:true},{field:'ntime',title:'ί��ʱ��',width:80,sortable:true},{field:'msg',title:'��ע',width:300,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#mathislst').datagrid('loadData',{total:y.length,rows:y});
}

//���Բ���

tsparareq=function(x,y){wscall(['{[x]k:(key .db.Ts[x]) except ``HedgeMap`ValTS`MU`SIGMA`HedgeMapList; flip `k`v!(k;(-3!) each .db.Ts[x;k])}',x],tsparares,{'target':'grid'});}

tsparares=function(x,y){
    $('#'+x.target).html('<div id=tspara style="align:center;width:'+dw+'px;height:'+dh+'px"></div>');
        $('#tspara').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'k',title:'������',width:160,sortable:true},{field:'v',title:'����ֵ',width:1000,sortable:true}]]});
    $('#tspara').datagrid('loadData',{total:y.length,rows:y});
};

//�Գ����orderbook����
csvloadreq=function(x,y){var t=now();if((t>='10:25:00')&&(t<='15:05:00')){if(!confirm('�����Ѿ�����10��25,ȷ�����¼�����?')) return;};wscall(['loadcsv',x,'`'],csvloadres,{'target':'ctrl'});}
csvloadres=function(x,y){$('#'+x.target).html('���ݼ���'+(y?'�ɹ�':'ʧ��')+'!');};

//�Գ����orderbook���ݲ�ѯ
csvviewreq=function(x,y){wscall(['{`date`data`raw!(string .db.Ts[x;`MapDate];{flip `price`pos!(key x;value x)} .db.Ts[x;`HedgeMap];flip {(key x;value x)} .db.Ts[x;`HedgeMap])}',x],csvviewres,{'t0':'ctrl','t1':'grid','t2':'plot'});}
csvviewres=function(x,y){
    $('#'+x.t0).html('��������:'+y.date);$('#'+x.t1).html('<div id=csvgrid>');$('#'+x.t2).html('<div id=flotarea style="width:600px;height:300px">');
    $('#csvgrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'price',title:'�۸�',width:80,sortable:true},{field:'pos',title:'��λ',width:80,sortable:true}]]});
    $('#csvgrid').datagrid('loadData',{total:y.data.length,rows:y.data});
    $.plot("#flotarea",[y.raw]);
};

//�Գ����
otchedgereq=function(x,y){wscall(['{[x]y:.db.Ts[x;`UDL];z:otc_hedgemap[x];g:(1_ key z)!1_ (deltas value z)*(key z)%(deltas key z)*100;traderlst:x;q:$[1b~.db.Ts[x;`BasketUDL];otc_hedgepospf[x];0f^exec sum ((0f^lqty)+0f^sqty) from .db.P where ts in traderlst,sym=y];p:otc_hedgepx[x];m:1f^.db.QX[y;`multiplier];fq:exec sum ((0f^lqty)+0f^sqty) from .db.P where ts in traderlst,sym<>y;bias:q-z[p];e:0.01*til 11;md:0<count z1:.db.Ts[x;`HedgeMapList];if[md;z0:map_hedgeoffset[x];z1:{`s#(x+key y)!value y}[z0] z1];`p`t`ON`X`Y`Y0`fardelta`delta`gamma`ddelta`pos`bias`udl`active`neggamma`mode`md`dL`warn!(p;z[p];exec sum cumqty from .db.O where sym like ((2#string y),"*"),posefct=.enum`OPEN;.math.r2 1e-4*abs bias*m*p;.math.r2 1e-4*1e6|abs[0.1*(q+fq)*m*p]|abs g[p]*p*2*m;`q`fq`m`p`g!(q;fq;m;p;g[p]);fq;flip (key z;value z);flip (key g;value g);flip (1e2*e;{p:key x;avg (p where (p<=y*1+0.5*z)&(p>=y*1-0.5*z))#x}[z;p] each e);enlist (`float$$[0>=p;.db.QX[y;`pc];p];0f)^p,q;.math.r2 bias;y;.db.Ts[x;`active];isneggamma[x];.db.Ts[x;`mode];md;$[md;(key z1),\'/:flip value z1;()];$[1b~.db.Ts[x;`BasketUDL];`$"Basket,STOP@",sv[","] string exec sym from ((select from .db.ETFPF where etfsym=y) lj select last price by sym from .db.QX) where price<=0;`])}',x],otchedgeres,{'target':'plot'});} //r2 (`float$$[0>=p:QX[y;`price];QX[y;`pc];p])^P[(x;T[x;`account];y);`price]

otchedgeres=function(x,y){
    $('#'+x.target).html('<div id=otcinfo></div><br><table><tr><td><div id=flotarea style="width:600px;height:300px"></div></td><td><div id=flotarea1 style="width:400px;height:300px"></div></td></tr></table>');
    $('#otcinfo').html('��������Լ�ֲֺϼ�:'+y.fardelta+',������Լ��̬�ֲ�:'+y.pos[0][1]+',��ȱ�ܽ���޶�:'+y.Y+'��,Ŀǰ���:'+y.X+'��,����ͬƷ���ۼƿ���:'+y.ON+'.'+'<br>'+'UDL:'+y.udl+'('+(y.active?'Enable':'Disable')+',Gamma<=0:'+(y.neggamma?'True':'False')+',Mode:'+y.mode+',Price:'+y.p+',Target:'+y.t+'),��ʾ��'+y.warn); //(q='+y.Y0.q+',fq='+y.Y0.fq+',m='+y.Y0.m+',p='+y.Y0.p+',g='+y.Y0.g+')
    if(y.md){
	$.plot("#flotarea",[{data:y.dL[0],lines:{show:true,lineWidth:1}},{data:y.dL[0],lines:{show:true,lineWidth:1},label:'0915'},{data:y.dL[1],lines:{show:true,lineWidth:1},label:'1030'},{data:y.dL[2],lines:{show:true,lineWidth:1},label:'1300'},{data:y.dL[3],lines:{show:true,lineWidth:1},label:'1400'},{data:y.dL[4],lines:{show:true,lineWidth:1},label:'1500'},{data:y.gamma,yaxis:2,lines:{show:true,lineWidth:1},label:'Gamma'},{data:y.delta,lines:{show:true,lineWidth:2},label:'Delta'},{data:y.pos,points:{show:true,fill:true,fillColor:'green',radius:3},label:'bias:'+y.bias}],{legend:{position:'nw',noColumns:8},yaxes:[{},{ position:'right'}]});
    }else{
	$.plot("#flotarea",[{data:y.gamma,yaxis:2,lines:{show:true,lineWidth:1},label:'Gamma'},{data:y.delta,lines:{show:true,lineWidth:1},label:'UDL:'+y.udl+'('+(y.active?'Enable':'Disable')+',Gamma<=0:'+(y.neggamma?'True':'False')+',Mode:'+y.mode+')'},{data:y.pos,points:{show:true,fill:true,fillColor:'red',radius:3},label:'bias:'+y.bias}],{legend:{position:'nw',noColumns:3},yaxes:[{},{position:'right'}]}); //min:-100,max:100,autoscaleMargin:0.05
    }
    $.plot("#flotarea1",[{data:y.ddelta,lines:{show:true,lineWidth:1},label:'Delta'}],{xaxis:{tickFormatter:function(x,y){return x+'%';}}});
};

//JUMP����
otcjumpreq=function(x,y){$.messager.prompt('����', '������Ŀ���λ:', function(r){if(r){wscall(['{[x;p]y:.db.Ts[x;`UDL];z:otc_hedgemap[x];q:sum 0f^.db.P[(x;.db.Ts[x;`acc];y);`lqty`sqty];floor abs q-z[p]}',x,parseFloat(r)],otcjumpres,{'target':'plot'});}});}
otcjumpres=function(x,y){$.messager.alert('JUMP','jump='+y+'.','info');};

//��ָ�ڻ��������޽ṹ
otctermstrureq=function(x,y){wscall(['{[x]y:{[x;y]z:asc key x;(z;1e2*(((x z)-y)%z%360)%y*1.2)}[exec (settledate-.z.D)!?[price>0;price;pc] from .db.QX where settledate>.z.D,product=.db.QX[.db.Ts[x;`UDL];`product];{$[x[0]>0;x[0];x[1]]} .db.QX[`000300.XSHG;`price`pc]];`ts`x0`x1`y0`y1!(flip y;y[0;0];last y[0];min y[1];max y[1])}',x],otctermstrures,{'target':'plot'});}

otctermstrures=function(x,y){
//    $('#'+x.target).html('<div id=flotarea style="width:600px;height:300px">');
//    $.plot("#flotarea",[{data:y.ts,points:{show:true,fill:true,fillColor:'red',radius:3},lines:{show:true,lineWidth:1}}]);

    $('#'+x.target).html('<div id=jsxbox style="width:800px;height:300px">');
    var X0=-10,X1=260,Y1=y.y1+2,Y0=Math.min(0,y.y0)-1;
    var brd = JXG.JSXGraph.initBoard('jsxbox',{showCopyright:false,showNavigation:false,axis:{ticks:{ticksDistance:0.1}},boundingbox:[X0,Y1,X1,Y0],originX:0,originY:0});  //
    brd.suspendUpdate();

    var p=y.ts.map(function(x){return brd.create('point',x,{style:6,frozen:true});});

//  var g = brd.create('functiongraph', [JXG.Math.Numerics.lagrangePolynomial(p),X0,X1], {strokeWidth:3});
//    var g = brd.create('curve', JXG.Math.Numerics.Neville(p), {strokecolor:'blue', strokeOpacity:0.6, strokeWidth:3}); 
//    var g = brd.create('spline', p, {strokecolor:'blue', strokeOpacity:0.6, strokeWidth:3}); 
//  var g = brd.create('curve', JXG.Math.Numerics.bspline(p,3), {strokecolor:'blue', strokeOpacity:0.6, strokeWidth:3}); 
    var g = brd.create('curve', JXG.Math.Numerics.CatmullRomSpline(p), {strokecolor:'blue', strokeOpacity:0.6, strokeWidth:3}); 

    [90,180].map(function(x){return brd.create('glider',[x,0,g], {style:6,strokeColor:'black',fillColor:'black'});});

    brd.unsuspendUpdate();
};


//NOE��ѯ
noereq=function(x){wscall('0!.db.NOE',noeres,{target:'grid'});}

noeres=function(x,y){
    $('#'+x.target).html('<div id=noelst>');
    $('#noelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'sno',title:'��ˮ��',width:100,sortable:true},{field:'ts',title:'����ID',width:160,sortable:true},{field:'sym',title:'����',width:80,sortable:true},{field:'sd',title:'����',width:30,sortable:true},{field:'pe',title:'��ƽ',width:30,sortable:true},{field:'q',title:'����',width:60,sortable:true},{field:'p',title:'�۸�',width:60,sortable:true},{field:'price',title:'�ο���',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'inf',title:'��ͼ�',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'sup',title:'��߼�',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'txt',title:'��ע',width:500,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#noelst').datagrid('loadData',{total:y.length,rows:y});
    $('#ctrl').html('<input type=button value="ȷ���ύ" onclick="noerptreq()"><input type=button value="���NOE��" onclick="noedelreq()">');
}

noerptreq=function(x){if(confirm('ȷ���ύ��?')){wscall('noerptall[1]',noerptres,{target:'grid'});}}
noedelreq=function(x){if(confirm('ȷ�������?')){wscall('delete from `NOE',noerptres,{target:'grid'});}}

noerptres=function(x,y){if(y>0){if(confirm('���ڼ۸��쳣NOE,�ٴ�ȷ���ύ��?')){wscall('noerptall[0]',noerptres,{target:'grid'});}else{noereq();}}else{noereq();}}

//NOEǿ�Ʋ�ѯ
noefreq=function(x){wscall('update string rtime from .db.NOEF',noefres,{target:'grid'});}
noefres=function(x,y){
    $('#'+x.target).html('<div id=noeflst>');
    $('#noeflst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'rtime',title:'�ϱ�ʱ��',width:120,sortable:true},{field:'sno',title:'��ˮ��',width:100,sortable:true},{field:'ts',title:'����ID',width:160,sortable:true},{field:'sym',title:'����',width:80,sortable:true},{field:'sd',title:'����',width:30,sortable:true},{field:'pe',title:'��ƽ',width:30,sortable:true},{field:'q',title:'����',width:60,sortable:true},{field:'p',title:'�۸�',width:60,sortable:true},{field:'price',title:'�ο���',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'inf',title:'��ͼ�',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'sup',title:'��߼�',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'txt',title:'��ע',width:500,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#noelst').datagrid('loadData',{total:y.length,rows:y});
    $('#ctrl').html('');
}

//���Ȩ�ؼ���
pfloadreq=function(){wscall(['{[x]@[loadpf;();0]}','`'],pfloadres,{'target':'ctrl'});}
pfloadres=function(x,y){$('#'+x.target).html('����Ȩ�ؼ���'+(y?'�ɹ�':'ʧ��')+'!');};
//���Ȩ�ز�ѯ
pfviewreq=function(){wscall(['{[](enlist `data)!enlist select etfsym,sym,qty from .db.ETFPF}','`'],pfviewres,{'t0':'ctrl','t1':'grid','t2':'plot'});}
pfviewres=function(x,y){
   $('#'+x.t1).html('<div id=csvgrid>');
    $('#csvgrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'etfsym',title:'���ID',width:120,sortable:true},{field:'sym',title:'�ɷֹɴ���',width:120,sortable:true},{field:'qty',title:'�ɷֹ�Ȩ��',width:120,sortable:true}]]});
    $('#csvgrid').datagrid('loadData',{total:y.data.length,rows:y.data});
};

//������
basismonreq=function(){wscall(['{[](enlist `data)!enlist `sym xasc update basisyearly:100*(basis%remainingyears)%idxprice,`$string settledate from update basis:price-idxprice,remainingyears:(settledate-.z.D)%365 from (select sym,price,settledate-2,product from .db.QX where ex=`CCFX,cumqty>0,product in `IF`IC`IH) lj 1!select product:(`000300.XSHG`000016.XSHG`000905.XSHG!`IF`IH`IC) sym,idxsym:sym,idxprice:price from .db.QX where sym in `000300.XSHG`000016.XSHG`000905.XSHG}','`'],basismonres,{'t0':'ctrl','t1':'grid','t2':'plot'});}
basismonres=function(x,y){
   $('#'+x.t1).html('<div id=csvgrid>');
    $('#csvgrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'sym',title:'�ڻ�����',width:120,sortable:true},{field:'price',title:'�ڻ��۸�',width:120,sortable:true},{field:'settledate',title:'������',width:120,sortable:true},{field:'product',title:'��Ʒ����',width:60,sortable:true},{field:'idxsym',title:'ָ������',width:120,sortable:true},{field:'idxprice',title:'�ֻ��۸�',width:120,sortable:true},{field:'basis',title:'����',width:120,sortable:true,formatter:function(x){return x.toFixed(4);}},{field:'remainingyears',title:'ʣ������',width:120,sortable:true,formatter:function(x){return x.toFixed(4);}},{field:'basisyearly',title:'�껯����(%)',width:120,sortable:true,formatter:function(x){return x.toFixed(4);}}]],rowStyler:function(index,row){if(row.product=='IF'){return 'background-color:#6293BB;color:#fff;';}}});
    $('#csvgrid').datagrid('loadData',{total:y.data.length,rows:y.data});
};

//�Գ����
hedgesnapreq=function(x,y){
wscall(['{[x]x:value group(!/) flip {(x;.db.QX[.db.Ts[x;`UDL];`product] in `IF`IC`IH)} each tsl[];(`idx`com!{[x]update biaspct:100*bias%abs[delta] from update bias:pos-delta from flip `clt`sym`pos`delta!(x;{.db.Ts[x;`UDL]} each x;{[x]y:string x;z:`$y;?[1b~.db.Ts[x;`BasketUDL];otc_hedgepospf[x];exec sum ((0f^lqty)+0f^sqty) from .db.P where ts in z]} each x;{[x]otc_hedgemap[x] otc_hedgepx[x]} each x)} each x),`idxstatus`comstatus!{[x]raze {[x]y:string x;z:enlist `$y; flip `id`active`manual`mode!flip {(x;.db.Ts[x;`active];`MANUAL~.db.Ts[x;`mode];.db.Ts[x;`mode])} each z} each x} each x}',otcrunall],hedgesnapres,{'target':'grid'});
}

hedgesnapres=function(x,y){
    $('#'+x.target).html('<table><tr><td>�ڻ��Գ����</td><td>���ɶԳ����</td></tr><tr width=1100 height=180><td><div style="width:550px;height: 180px;" id=idxhedgelst></td><td><div style="width:550px;height: 180px;" id=comhedgelst></td></tr><tr><td>�ڻ��Գ�״̬</td><td>���ɶԳ�״̬</td></tr><tr width=1100 height=280><td><div style="width:550px;height:280px;" id=idxhedgestatus></td><td><div style="width:550px;height:280px;" id=comhedgestatus></td></tr></table>');
    var d=y.idx;
    $('#idxhedgelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'clt',title:'����ID',width:100,sortable:true},{field:'sym',title:'�Գ���',width:100,sortable:true},{field:'pos',title:'ͬƷ���ֲܳ�',width:100,sortable:true},{field:'bias',title:'�Գ����',width:100,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'biaspct',title:'���ٷֱ�(%)',width:100,sortable:true,formatter:function(x){return x.toFixed(2);}}]]});
    $('#idxhedgelst').datagrid('loadData',{total:d.length,rows:d});
    d=y.idxstatus;
    $('#idxhedgestatus').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'id',title:'����ID',width:100,sortable:true},{field:'active',title:'�Ƿ񼤻�',width:100,sortable:true},{field:'manual',title:'�Ƿ��ֹ�',width:100,sortable:true},{field:'mode',title:'�Գ�ģʽ',width:100,sortable:true}]],rowStyler:function(index,row){if(!row.active){return 'background-color:red;';}else if(row.manual){return 'background-color:yellow;';}else return 'background-color:green;';}});
    $('#idxhedgestatus').datagrid('loadData',{total:d.length,rows:d});    
    d=y.com;
    $('#comhedgelst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'clt',title:'����ID',width:100,sortable:true},{field:'sym',title:'�Գ���',width:100,sortable:true},{field:'pos',title:'ͬƷ���ֲܳ�',width:100,sortable:true},{field:'bias',title:'�Գ����',width:100,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'biaspct',title:'���ٷֱ�(%)',width:100,sortable:true,formatter:function(x){return x.toFixed(2);}}]]});
    $('#comhedgelst').datagrid('loadData',{total:d.length,rows:d});
    d=y.comstatus;
    $('#comhedgestatus').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'id',title:'����ID',width:100,sortable:true},{field:'active',title:'�Ƿ񼤻�',width:100,sortable:true},{field:'manual',title:'�Ƿ��ֹ�',width:100,sortable:true},{field:'mode',title:'�Գ�ģʽ',width:100,sortable:true}]],rowStyler:function(index,row){if(!row.active){return 'background-color:red;';}else if(row.manual){return 'background-color:yellow;';}else return 'background-color:green;';}});
    $('#comhedgestatus').datagrid('loadData',{total:d.length,rows:d});
}

////���Լ�Ч����
txpnlreq=function(x,y){
    wscall(['{[x]exec x:`$(-13_) each string {x,y}[first enter;leave],y:{0f,x} sums netpnl from .temp.GT}',x],showasset,{'target':'plot'});
}

txtransreq=function(x,y){
    wscall(['{[x]exec x:ti,y:netpnl from `ti xasc .temp.GT}',x],showtrade,{'target':'plot'});
}

txtradesreq=function(x,y){
    wscall(['{[x]update string enter,string leave,string hold from `ti xasc .temp.GT}',x],showtradelist,{'target':'plot'});
}

txdetailreq=function(x,y){
    wscall(['{[x]sex:fs2e z:.db.Ts[x;`xsym];d0:vtd[];tq:.ctrl.conn.rdb.h ({[x]select `time$time,bid,ask,cumqty from quote where sym=x};z);(update date:d0+`time$date from 0!select last bid,last ask,sum qty by date:5000 xbar `time$vtimex[sex] time from (select time,bid,ask,qty:deltas cumqty from tq) where  0<bid&ask),\\: update date:d0+`time$date from select cumqty wavg avgpx,sum cumqty by 5000 xbar `time$date from select date:vtimex[sex] `time$ftime,avgpx,cumqty from .db.O where ts=x,sym=z,cumqty>0,avgpx>0}',x],detailplot,{'target':'plot'});
}

rsplotreq=function(x,y){
    wscall(['{[x]t:.db.Ts[x;`TBR];`seq`data`mark!(exec seq from t;flip value flip select o,c,l,h from t;flip value flip select i,px:?[level>0;h;l],level from t where level<>0)}',x],rsplotres,{'target':'plot'});
}

rsplotres=function(x,y){
    $('#'+x.target).html('<div id=kline style="width:'+dw+'px;height:'+dh+'px;">'); //$('#'+x.target).panel('options').height
    var chart1=echarts.init($('#kline')[0]);
    var option1={title:{text:x.sym},legend:{},tooltip:{},xAxis:{type:'category',data:y.seq},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.data,markPoint:{data:y.mark.map(function(x){return {coord:[x[0],x[1]],name:(x[2]<0)?'buy':'sell',symbol:(x[2]>0)?'emptytriangle':'triangle',symbolSize:10*Math.abs(x[2]),symbolRotate:(x[2]>0)?180:0,symbolOffset:[0,(x[2]>0)?'-50%':'50%'],itemStyle:{normal:{color:(x[2]<0)?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}}}]};    
    chart1.setOption(option1);
}

gridmonreq=function(x,y){
    wscall(['{[x]update (-3!) each closelongrange,(-3!) each closeshortrange,(-3!) each oidup,(-3!) each oiddn,(-3!) each switchtime,(-3!) each sampletime,(-3!) each cp,(-3!) each pxhist from 0!.db.Ts[x;`TP]}',x],gridmonres,{'target':'grid'});
}

gridmonres=function(x,y){
    $('#'+x.target).html('<div id=tplst>');
    $('#tplst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'sym',title:'������',width:120,sortable:true},{field:'stop',title:'ֹ��ֹͣ',width:60,sortable:true},{field:'logpx',title:'��������',width:60,sortable:true},{field:'pxbase',title:'��ʼ�ο��۸�',width:80,sortable:true},{field:'qtybase',title:'��ʼ�ֲ�',width:80,sortable:true},{field:'nup',title:'��������',width:60,sortable:true},{field:'ndn',title:'�µ�����',width:60,sortable:true},{field:'trend',title:'��ǰ����',width:60,sortable:true},{field:'nhd',title:'��������',width:60,sortable:true},{field:'pxhold',title:'����۸�',width:80,sortable:true},{field:'qtyhold',title:'��������',width:80,sortable:true},{field:'pxref',title:'��ǰ�ο��۸�',width:80,sortable:true},{field:'qtyref',title:'��ǰ���۳ֲ�',width:80,sortable:true},{field:'pxask',title:'�����ҵ��۸�',width:80,sortable:true},{field:'qtyask',title:'�����ҵ�����',width:80,sortable:true},{field:'pxbid',title:'�򵥹ҵ��۸�',width:80,sortable:true},{field:'qtybid',title:'�򵥹ҵ�����',width:80,sortable:true},{field:'stepup',title:'��������',width:60,sortable:true},{field:'stepdn',title:'���벽��',width:60,sortable:true},{field:'qtyups',title:'��������',width:60,sortable:true},{field:'qtydnl',title:'��������',width:60,sortable:true},{field:'posinf',title:'�ֲ�����',width:60,sortable:true},{field:'possup',title:'�ֲ�����',width:60,sortable:true},{field:'oidup',title:'����ί�����',width:80,sortable:true},{field:'oiddn',title:'��ί�����',width:80,sortable:true},{field:'switchtime',title:'���״̬�л�ʱ��',width:100,sortable:true},{field:'sampletime',title:'���¼۸����ʱ��',width:100,sortable:true},{field:'cp',title:'���Ʋ���',width:200,sortable:true},{field:'pxhist',title:'�۸��������',width:100,sortable:true},{field:'spreadmax',title:'ֹ��������������۲�',width:140,sortable:true},{field:'closelongrange',title:'���ֹ������',width:100,sortable:true},{field:'closeshortrange',title:'�ղ�ֹ������',width:100,sortable:true}]]});
    $('#tplst').datagrid('loadData',{total:y.length,rows:y});
}

////�ڻ��о�
//�ɽ���Ʒ�ֲַ�
function labelFormatter(label, series){return "<div style='font-size:8pt; text-align:center; padding:2px; color:white;'>" + label + "<br/>" + Math.round(series.percent) + "%</div>";}

futamtreq=function(){init=1;wscall(['{[x].temp.t0:t0:(.ctrl.conn.hdb.h "select cumamt:last cumqty*price,last price,last openint by sym from quote where date=last date,cumqty>0,src=`fqctp") lj 1!.ctrl.conn.hdb.h "{select sym,15 xbar dend+00:10,nend:15 xbar 00:10+nend0^nend1 from (select sym,dend:time from x where sess=09:00) lj (1!select sym,nend0:time from x where sess=21:00) lj  (1!select sym,nend1:time from x where sess=00:00)} select from (select last `minute$time by sym,sess:(`s#{x!x}`s#00:00 04:00 09:00 16:00 21:00 24:00) `minute$time from quote where date=last date,src=`fqctp,cumqty>(prev;cumqty) fby sym,0<bid|ask) where sess in 00:00 09:00 21:00";.temp.t1:t1:(select last multiplier,last product,last ex,last pxunit,last rmarginl,last rfeetaxoa,last rfeetaxoq,last name by sym from .db.QX where not null product,1<=multiplier) lj (select sp:last product by `${[x]y:3_x;(floor(count[y]-1)%2)#y} each string product from .db.QX where not null product,sym like "SP *"),select sp:last product by `${[x]y:4_x;(floor(count[y]-1)%2)#y} each string product from .db.QX where not null product,sym like "SPD *";.temp.T:t2:t0 ij t1;t:0!.db.PD:update feeunit:2*fee%pxunit*multiplier,sess:getsess\'[ex;dend;nend] from update sumpct:sums amtpct,rmarginl*1e2,margin:rmarginl*size,fee:rfeetaxoq+rfeetaxoa*size,feebp:1e4*(rfeetaxoa+rfeetaxoq%size) from update amtpct:1e2*cumamt%sum cumamt,seq:i+1,size:price*multiplier,bpunit:1e4*pxunit%price from desc (select sum cumamt*multiplier*1e-8,last ex,last sp,last multiplier,last pxunit by product from t2) lj select last sym,last price,last rmarginl,last rfeetaxoa,last rfeetaxoq,last name,last dend,last nend by product from t2 where openint=(max;openint) fby product;`data`raw!(update string dend,string nend from select from t where cumamt>1;select label:product,data:amtpct from t where not null sp)}','`'],futamtres,{t1:'plot',t2:'grid'});}

futamtres=function(x,y){
    $('#main').layout('panel','south').panel('resize',{height:ph});$('#main').layout('resize');

    $('#'+x.t1).html('<div id=futamtlst style="align:center;width:'+dw+'px;height:'+dh+'px">');$('#'+x.t2).html('<div id=futamtflot style="width:600px;height:300px">');
    $('#futamtlst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'product',title:'Ʒ��',width:30,sortable:true},{field:'ex',title:'������',width:40,sortable:true},{field:'cumamt',title:'�ճɽ�(��)',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'amtpct',title:'ռ��(%)',width:45,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'seq',title:'����',width:27,sortable:true},{field:'sumpct',title:'�ۼ�(%)',width:45,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'sp',title:'SP������',width:80,sortable:true},{field:'sym',title:'������Լ',width:80,sortable:true},{field:'name',title:'��Լ����',width:80,sortable:true,formatter:function(x){return togbk(x);}},{field:'price',title:'�������̼�',width:70,sortable:true},{field:'multiplier',title:'����',width:40,sortable:true},{field:'size',title:'��Լ��С',width:60,sortable:true},{field:'pxunit',title:'�۸�λ',width:52,sortable:true},{field:'bpunit',title:'��λ(%%)',width:40,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'rmarginl',title:'��֤��(%)',width:40,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'margin',title:'ÿ�ֱ�֤��',width:70,sortable:true,formatter:function(x){return x.toFixed(0);}},{field:'feebp',title:'�����ѱ���(%%)',width:88,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'fee',title:'ÿ��������',width:64,sortable:true,formatter:function(x){return x.toFixed(1);}},{field:'feeunit',title:'����������',width:64,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'dend',title:'��������',width:50,sortable:true},{field:'nend',title:'ҹ������',width:50,sortable:true}]],onClickRow:function(index,r){klinereq(r.sym);}}); //,onLoadSuccess:function(data){$("#futamtlst").datagrid("resize",{height:'300px'});}
    
    $('#futamtlst').datagrid('loadData',{total:y.length,rows:y.data});
    $("#futamtlst").datagrid("resize",{height:'300px'});
    
//        $.plot("#futamtflot",[y.raw]);
//    $.plot("#futamtflot",y.raw,{series:{pie:{show: true,radius:1,label:{show:true,radius: 2/3,formatter: labelFormatter,threshold: 0.02}}},legend:{show:false},grid:{hoverable: true,clickable: true}});
};

//K�߲�ѯ
klinereq=function(x){wscall(['{[x].temp.D:D:`date$-12 1+"M"${$[x[0]="0";"2";"1"],x} 3#(-3+y?".")_y:string x;.temp.t:t:0!.ctrl.conn.hdb.h ({[D;x]select o:first price,h:max price,l:min price,c:last price by d:date from quote where date within D,sym=x,date<>2019.06.07,not (date=2019.06.10)&(time within 00:00 08:55)|(time within 16:00 24:00),(0<l)&(l<=price)&(price<=h)};D;x);`date`data!(exec string d from t;flip value flip select o,c,l,h from t)}','`'+x],klineres,{sym:x,target:'grid'});}
klineres=function(x,y){
    $('#'+x.target).html('<div id=kline style="width:'+dw+'px;height:'+dh+'px;">'); //$('#'+x.target).panel('options').height
    var chart1=echarts.init($('#kline')[0]);
    var option1={title:{text:x.sym},legend:{},tooltip:{},xAxis:{data:y.date},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.data}]};    
    chart1.setOption(option1);
}

//������ʷ��ѯ
futbasisreq=function(x){wscall(['{[x]select id:sp,text:product from .db.PD where not null sp}','`'],futbasisreq0,{target:'ctrl'});} //
futbasisreq0=function(x,y){
    $('#ctrl').html('Ʒ��:<input id="cbproduct" style="width:50px">SPģʽ:<input type=text id=filter size=5 value="05-09"></input>SP����:<input id="cbbasis" style="width:200px">�۸�����:<input type=radio name=pxbp value=0 checked>����ֵ<input type=radio name=pxbp value=1>%�۸�,��ʼ����:<input type=text id=d0 name=d0 style="width:150px"></input>,��������:<input type=text id=d1 name=d1 style="width:150px"><input type=button id=futbasisbut value="��ѯ"></input>');
    $("#cbproduct").combobox({required:true,valueField:'id',textField:'text',onSelect: function(x){wscall(['{[x;y;z].temp.pd:`$y;F:$[count z;"*",/:vs["-";z],\'("&*";enlist "*");2#enlist enlist "*"];`data`pct!(desc select id:sym,text:sym from .db.QX where product=`$x,not null srctime,(sym like F[0])&(sym like F[1]);select label:(-2#) each (-5_) each string sym,data:sqrt cumamt from .temp.T where product=.temp.pd)}',x.id,x.text,$('#filter').val()],basislstres,{target:'cbbasis',t2:'grid'});}});
    $("#cbproduct").combobox("loadData", y);$("#cbproduct").combobox('select',y[0].id);
    
    $("#cbbasis").combobox({required:true,valueField:'id',textField:'text',onSelect: function(x){wscall(['{[x]`d0`d1!{sv["/"] string rotate[1] "I"$ vs["."] x} each string `date$-12 -1+"M"$"1",/:{3#(-3+x?y)_x}[x] each ".&"}',x.id],basisres,{target:'cbbasis',t2:'grid'});}});
    $('#futbasisbut').click(function(y){wscall(['{[x;w;y;z]d0:"D"$y;d1:"D"$z;r:$[0<"I"$w;1e-2*.db.PD[.temp.PD;`price];1];t:update bid%r,ask%r from .ctrl.conn.hdb.h ({[x;y;z]0!update tm:(1e-6*`timestamp$date+2000.01.01-1970.01.01)+`time$t from select med bid,med ask by date,t:5 xbar {?[x>20:00;x-20:00;?[x<03:00;x+04:00;x]]} `minute$time from quote where date within (y,z),sym=`$x,not null bid,not null ask};x;d0;d1);`bid`ask!(flip value flip select tm,bid from t;flip value flip select tm,ask from t)}',$('#cbbasis').combobox('getValue'),$('input[name=pxbp]:checked').val(),$('input[name=d0]').val(),$('input[name=d1]').val()],futbasisres,{target:'plot'});});
    $('#grid').html('');
    $('#plot').html('');
    $('#d0').datebox({required:true});
    $('#d1').datebox({required:true,});
    $('#d0').datebox('setValue','1/1/2016');
    $('#d1').datebox('setValue','today');
}
basislstres=function(x,y){
    $("#"+x.target).combobox("loadData", y.data);
    $("#"+x.target).combobox('select',y.data[0].id);$('#'+x.t2).html('<div id=flotbasis style="width:900px;height:250px">');
    $.plot("#flotbasis",y.pct,{series:{pie:{show: true,radius:1,label:{show:true,radius: 2/3,formatter: labelFormatter,threshold: 0.02}}},legend:{show:false},grid:{hoverable: true,clickable: true}});
}
basisres=function(x,y){$('#d0').datebox('setValue',y.d0);$('#d1').datebox('setValue',y.d1);}

futbasisres=function(x,y){
    $('#'+x.target).html('<div id=flotarea style="width:1000px;height:350px">');
    $.plot("#flotarea",[{data:y.bid,label:'bid',lines:{show:true,lineWidth:1},clickable:true,hoverable:true},{data:y.ask,label:'ask',lines:{show:true,lineWidth:1},clickable:true,hoverable:true}],{xaxis:{mode: "time",timeformat:"%m.%d"}});  //ticks:y.tick points:{show:true,radius:1},,points:{show:true,fill:true,radius:1} %Y.%m.%dD%H:%M
} 

//Ʒ�ִ����ѯ
futexreq=function(x){wscall(['{[x]select id:ex,text:ex from asc select count i by ex from .db.PD}','`'],futexlst,{target:'symlst'});}
futexlst=function(x,y){
    $('#'+x.target).html('������:<input id="cbex" style="width:80px"></input>Ʒ��:<input id="cbprd" style="width:70px"></input>��Լ:<input id="cbsym" style="width:120px">��ʼ����:<input type=text id=symd0 name=symd0 style="width:150px"></input>,��������:<input type=text id=symd1 name=symd1 style="width:150px">Ƶ��:<input id="cbfreq" style="width:80px"></input>����:<input id="cbtype" style="width:80px"></input><input type=button id=futsymbut value="��ѯ"></input>');

    $('#futsymbut').click(function(y){wscall(['{[x;d0;d1;f;typ]x:`$x;D:"D"$(d0;d1);f:"J"$f;typ:`$typ;.temp.t:t:$[`M=typ;delete t from update d:`$(-13_) each string d+t from minbars[typ;x;D;f];daybars[typ;x;D;f]];tr:histrds[x;D];.temp.tr:tr:delete t from $[`M=typ;update d:`$(-13_) each string d+xbar[f] `minute$t from tr;update d:`$string xbar[f] d from tr];`date`data`trade!(exec string d from t;flip value flip select o,c,l,h from t;flip value flip tr)}',$('#cbsym').combobox('getValue'),$('input[name=symd0]').val(),$('input[name=symd1]').val(),$('#cbfreq').combobox('getValue'),$('#cbtype').combobox('getValue')],futsymres,{target:'grid'});});

    $('#symd0').datebox({required:true});
    $('#symd1').datebox({required:true,});
    $('#symd0').datebox('setValue','1/1/2016');
    $('#symd1').datebox('setValue','today');

    $("#cbfreq").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbfreq").combobox("loadData",[{id:1,text:'1'},{id:5,text:'5'},{id:10,text:'10'},{id:15,text:'15'},{id:20,text:'20'},{id:30,text:'30'},{id:60,text:'60'}]);$("#cbfreq").combobox('select',1);    

    $("#cbtype").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbtype").combobox("loadData",[{id:"D",text:'����'},{id:"M",text:'������'}]);$("#cbtype").combobox('select',"D");    

    $("#cbex").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){wscall(['{[x]select id:product,text:product from .db.PD where ex=x}','`'+x.id],futprdlst,{});}});
    $("#cbex").combobox("loadData", y);$("#cbex").combobox('select',y[0].id);    
}

futprdlst=function(x,y){
    $("#cbprd").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){wscall(['{[x]select id:sym,text:sym from .temp.T where product=x}','`'+x.id],futsymlst,{});}});
    $("#cbprd").combobox("loadData", y);$("#cbprd").combobox('select',y[0].id);    
}

futsymlst=function(x,y){
    $("#cbsym").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){wscall(['{[x]`d0`d1!{sv["/"] string rotate[1] "I"$ vs["."] x} each string `date$-12 1+"M"${$[x[0]="0";"2";"1"],x} 3#(-3+y?".")_y:string x}','`'+x.id],futsymdates,{});}});
    $("#cbsym").combobox("loadData", y);$("#cbsym").combobox('select',y[0].id);    
}

futsymdates=function(x,y){$('#symd0').datebox('setValue',y.d0);$('#symd1').datebox('setValue',y.d1);}

futsymres=function(x,y){
    maxgrid();    
    $('#'+x.target).html('<div id=kline style="width:'+(pw-50)+'px;height:'+($('#'+x.target).panel('options').height-50)+'px;">');
    var chart1=echarts.init($('#kline')[0]);
    var option1={title:{text:x.sym},legend:{},tooltip:{axisPointer:{type:'cross'}},xAxis:{data:y.date},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.data,markPoint:{symbolSize:15,data:y.trade.map(function(x){return {coord:[x[0],x[1]],name:(x[2]=='1')?'buy':'sell',symbol:(x[2]=='2')?'emptytriangle':'triangle',symbolRotate:(x[2]=='2')?180:0,symbolOffset:[0,(x[2]=='2')?'50%':'-50%'],itemStyle:{normal:{color:(x[2]=='1')?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}}}]};    
    chart1.setOption(option1);    
}

//���Թ���
algomgr=function(x){
    normgrid();
    $('#ctrl').html('<input type=button value="�½�" onclick="newalgo()"><input type=button value="����" onclick="delalgo()"><input type=radio id=func name=func value="timer" onclick="chgalgo()">timer<input type=radio id=func name=func value="quote" onclick="chgalgo()">quote<input type=radio id=func name=func value="exerpt" onclick="chgalgo()">exerpt<input type=radio id=func name=func value="match" onclick="chgalgo()">match<input type=radio id=func name=func value="dayroll" onclick="chgalgo()">dayroll<input type=radio id=func name=func value="sysinit" onclick="chgalgo()">sysinit<input type=radio id=func name=func value="sysexit" onclick="chgalgo()">sysexit<input type=radio id=func name=func value="bar" onclick="chgalgo()">bar<input type=radio id=func name=func value="barx" onclick="chgalgo()">barx<input type=radio id=func name=func value="cp" onclick="chgalgo()" checked>cp<input type=radio id=func name=func value="para" onclick="chgalgo()" checked>para<input type=button value="��¡" onclick="copyalgo()"><input type=button value="�����°�" onclick="newversion()">');
    $('#grid').html('');$('#plot').html('');
    wscall('0!update string pubdate,string updatetime,cp,para from select from .db.S where not expire',algolist,{'target':'grid'});
};

algolist=function(x,y){
    $('#'+x.target).html('<div id=algogrid>');
    $('#algogrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,idField:'id',columns:[[{field:'id',title:'����ID',width:60,sortable:true},{field:'version',title:'���԰汾',width:60,sortable:true},{field:'author',title:'����',width:60,sortable:true},{field:'pubdate',title:'��������',width:70,sortable:true},{field:'class',title:'����',width:60,sortable:true},{field:'updatetime',title:'������',width:150,sortable:true},{field:'timer',title:'ʱ�䴥��',width:120,sortable:true},{field:'quote',title:'���鴥��',width:80,sortable:true},{field:'exerpt',title:'�ر�����',width:80,sortable:true},{field:'match',title:'�ɽ�����',width:80,sortable:true},{field:'dayroll',title:'�����л�����',width:80,sortable:true},{field:'sysinit',title:'��ʼ������',width:80,sortable:true},{field:'sysexit',title:'�˳�����',width:80,sortable:true},{field:'bar',title:'ϵͳK�ߴ���',width:80,sortable:true},{field:'barx',title:'����K�ߴ���',width:120,sortable:true},{field:'cp',title:'���Ʋ���',width:150,sortable:true},{field:'para',title:'��������',width:150,sortable:true},{field:'info',title:'��ע',width:60,sortable:true}]],onClickRow:function(x,y){chgalgo();}});
    $('#algogrid').datagrid('loadData',{total:y.length,rows:y});
}

newalgo=function(){
    $('#plot').html('����ID:<input type=text id=id size=10></input>,�汾:<input type=text id=version size=10></input>,����:<input type=text id=author size=10></input>,˵��:<input type=text id=memo size=10></input>,����:<select id=class name=class><option value="trendfollowing">trendfollowing</option><option value="swingtrading">swingtrading</option><option value="marketmaking">marketmaking</option><option value="other">other</option></select><input type=button value="ȷ��" onclick="newalgoreq()"></input>');
}

newalgoreq=function(){
    wscall(['{[x]y:(x[0];"J"$x[1]);if[not null .db.S[y;`pubdate];:`r`errmsg!(-1;"algo id exist.")];.db.S[y;`author`pubdate`class`updatetime`info]:(x[2];.z.D;x[3];.z.P;x[4]);`r`errmsg!(0;"")}',['`'+$('#id').val(),$('#version').val(),'`'+$('#author').val(),'`'+$('#class').val(),$('#memo').val()]],newalgores,{'target':'plot'});
}

newalgores=function(x,y){
    if(y.r<0){alert(y.errmsg);}else{alert('�����ɹ�.');algomgr();}
}

delalgo=function(){
    var s=$('#algogrid').datagrid('getSelected');
    if(s==undefined){
	alert("����ѡ��һ������.");
    }else{
	if(confirm('ȷ�����ϲ���['+s.id+','+s.version+']��?')){
	    wscall(['{[x;y]y:`long$y;.db.S[x,y;`expire]:1b;(x;y)}','`'+s.id,s.version],delalgores,{'target':'plot'});
	}
    }
}

delalgores=function(x,y){
    alert('����['+y[0]+','+y[1]+']���ϳɹ�.');algomgr();
}

chgalgo=function(){
    var s=$('#algogrid').datagrid('getSelected');
    if(s==undefined){
	alert("����ѡ��һ������.");
    }else{
	wscall(['{.db.S[(x;`long$y);z]}','`'+s.id,s.version,'`'+$('input[name=func]:checked').val()],chgalgores,{'target':'plot'});
    }
}

chgalgores=function(x,y){
    $('#'+x.target).html('<input type=button value="����" onclick="updatealgoreq()"><input type=button value="У��" onclick="chkalgoreq()"><hr><textarea id=code rows=10 cols=100></textarea><br>');
    $('#code').text(y);
    editor = CodeMirror.fromTextArea(document.getElementById("code"),{lineNumbers:true,textWrapping:true,matchBrackets:true,mode:"text/x-q"});
}

updatealgoreq=function(){
    var s=$('#algogrid').datagrid('getSelected');var c= editor.getValue();
    wscall(['{[x;v;y;z].db.S[(x;`long$v);`updatetime,y]:(.z.P;1_z);`r`errmsg!(0;"")}','`'+s.id,s.version,'`'+$('input[name=func]:checked').val(),' '+c],updatealgores,{'target':'plot'});
}

updatealgores=function(x,y){if(y.r<0){alert(y.errmsg);}else{alert('����ɹ�.');}};

chkalgoreq=function(){
    var s=$('#algogrid').datagrid('getSelected');var c= editor.getValue();
    wscall(['{[x]r:@[value;"{[x;y]",x,"}";::];`r`errmsg!$[10h=type r;(-1;r);(0;"")]}',' '+c],chkalgores,{'target':'plot'});
}
			    
chkalgores=function(x,y){if(y.r<0){alert(y.errmsg);}else{alert('У��ͨ��.');}};

copyalgo=function(){
    var s=$('#algogrid').datagrid('getSelected');
    if(s==undefined){
	alert("����ѡ��һ������.");
    }else{
	var cid=prompt("������Ҫ��¡�Ĳ���ID�Ͱ汾,�Զ��ŷָ�:");
	wscall(['{[x;y;z]w:"SJ"$\'vs[","]z;$[null .db.S[w;`pubdate];`r`errmsg!(-1;"algo["+z+"] do not exist.");[.db.S[(x;`long$y);`pubdate`updatetime`timer`quote`exerpt`match`dayroll`sysinit`sysexit`bar`barx`cp`para]:(.z.D;.z.P),.db.S[w;`timer`quote`exerpt`match`dayroll`sysinit`sysexit`bar`barx`cp`para];`r`errmsg!(0;"")]]}','`'+s.id,s.version,cid],copyalgores,{'target':'plot'});
    }
}

copyalgores=function(x,y){
    if(y.r<0){alert(y.errmsg);}else{alert('��¡�ɹ�.');algomgr();};
}

newversion=function(){
    var s=$('#algogrid').datagrid('getSelected');
    if(s==undefined){
	alert("����ѡ��һ������.");
    }else{
	wscall(['{[x]y:exec max version from .db.S where id=x;$[0>y;`r`errmsg!(-1;"algo["+x+"] do not exist.");[.db.S[(x;y+1)]:.db.S[(x;y)];.db.S[(x;y+1);`pubdate`updatetime]:(.z.D;.z.P);`r`errmsg`sid`sver!(0;"";x;y+1)]]}','`'+s.id],newversionres,{'target':'plot'});
    }
}

newversionres=function(x,y){
    if(y.r<0){alert(y.errmsg);}else{alert(y.sid+'�����ɹ��°汾:'+y.sver+'.');algomgr();};
}

//�ز����
testmgr=function(x){
    normgrid();
    $('#ctrl').html('<input type=button value="�½�" onclick="newtest()"><input type=button value="ɾ��" onclick="cxltest()"><input type=radio id=show name=show value="asset" onclick="chgshow()" checked>�ʲ�����<input type=radio id=show name=show value="gts" onclick="chgshow()">��Ʒ�ֻ���<input type=radio id=show name=show value="trade" onclick="chgshow()">���׷ֲ�<input type=radio id=show name=show value="tradelist" onclick="chgshow()">������ϸ<input type=radio id=show name=show value="orderlist" onclick="chgshow()">ί����ϸ<input type=radio id=show name=show value="cp" onclick="chgshow()">���Ʋ�����ϸ<input type=radio id=show name=show value="para" onclick="chgshow()">���ײ�����ϸ<input type=radio id=show name=show value="kline" onclick="chgshow()">K����ʾ<input type=button value="����" onclick="runtest()">');$('#grid').html('');$('#plot').html('');
    wscall('select id,gid,sid,sver,cp,cash,xsym:?[btyp=`T;`$(-3!) each {$[1<count[x];x;first x]} each syms;xsym],string d0,string d1,btyp,freq,string `datetime$addtime,string `datetime$begintime,string `datetime$endtime,pnl,yield,mdd,nday from .db.B',testlist,{'target':'grid'});
};

testlist=function(x,y){
    $('#'+x.target).html('<div id=testgrid>');
    $('#testgrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,idField:'id',columns:[[{field:'id',title:'�ز�ID',width:60,sortable:true},{field:'gid',title:'�ز���',width:50,sortable:true},{field:'sid',title:'����ID',width:60,sortable:true},{field:'sver',title:'���԰汾',width:60,sortable:true},{field:'cp',title:'���Բ���',width:60,sortable:true},{field:'cash',title:'��ʼ����',width:60,sortable:true},{field:'xsym',title:'���ױ��',width:270,sortable:true},{field:'d0',title:'��ʼ����',width:70,sortable:true},{field:'d1',title:'��������',width:70,sortable:true},{field:'btyp',title:'K������',width:80,sortable:true},{field:'freq',title:'K������',width:60,sortable:true},{field:'addtime',title:'����ʱ��',width:150,sortable:true},{field:'begintime',title:'����ʱ��',width:150,sortable:true},{field:'endtime',title:'����ʱ��',width:150,sortable:true},{field:'pnl',title:'������',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'yield',title:'������',width:60,sortable:true,formatter:function(x){return (100*x).toFixed(2)+'%';}},{field:'mdd',title:'���س�',width:60,sortable:true,formatter:function(x){return (100*x).toFixed(2)+'%';}}]],onClickRow:function(x,y){chgshow();}});
    $('#testgrid').datagrid('loadData',{total:y.length,rows:y});
}

newtest=function(){
    $('#plot').html('');
    wscall('update text:id from select distinct id from .db.S where not expire',testform,{'target':'plot'});
}

testform=function(x,y){
    $('#'+x.target).html('���Բ���:<input id="cbsid" style="width:120px"></input>�汾:<input id="cbsver" style="width:70px"></input>������:<input type=text id=gid size=10></input>,��ʼ����:<input type=text id=cash size=10 value=200000></input>���Ʋ���:<input type=button value="ʹ�ò���ȱʡ���Ʋ���" onclick="copyalgocpreq()"><br><textarea id=cp rows=3 cols=30></textarea><br>���ײ���:<input type=button value="ʹ�ò���ȱʡ���ײ���" onclick="copyalgoparareq()"><br><textarea id=para rows=8 cols=30></textarea><br>��ʼ����:<input id=btd0 name=btd0 style="width:150px"></input>,��������:<input id=btd1 name=btd1 style="width:150px">,K������:<input id="cbfreq" style="width:80px"></input>,K������:<input id="cbtype" style="width:80px"></input>,���Ա��:<br><textarea id=xsym rows=3 cols=150></textarea><br><input type=button value="ȷ��" onclick="createst()"></input>');
    editor = CodeMirror.fromTextArea(document.getElementById("cp"),{lineNumbers:true,matchBrackets:true,mode:"text/x-q"});editor.setSize(1000, 100);
    editor2 = CodeMirror.fromTextArea(document.getElementById("para"),{lineNumbers:true,matchBrackets:true,mode:"text/x-q"});editor.setSize(1000, 100);    
    editor1 = CodeMirror.fromTextArea(document.getElementById("xsym"),{lineNumbers:true,matchBrackets:true,mode:"text/x-q"});editor1.setSize(1000, 50);
    $('#btd0').datebox({required:true});
    $('#btd1').datebox({required:true,});
    $('#btd0').datebox('setValue','1/1/2016');
    $('#btd1').datebox('setValue','today');

    $("#cbfreq").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbfreq").combobox("loadData",[{id:1,text:'1'},{id:5,text:'5'},{id:10,text:'10'},{id:15,text:'15'},{id:20,text:'20'},{id:30,text:'30'},{id:60,text:'60'}]);$("#cbfreq").combobox('select',1);    

    $("#cbtype").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbtype").combobox("loadData",[{id:"D",text:'����'},{id:"M",text:'������'},{id:"T",text:'Tick����'}]);$("#cbtype").combobox('select',"D");    

    $("#cbsid").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){wscall(['{[x]select version,text:version from .db.S where id=x,not expire}','`'+x.id],sverlst,{});}});
    $("#cbsid").combobox("loadData", y);$("#cbsid").combobox('select',y[0].id);    

//    $('#d0').datebox({required:true,value:date2qdate(dateprev(new Date(),30)),formatter:function(x){m=1+x.getMonth();d=x.getDate();return x.getFullYear()+'.'+((m>=10)?m:'0'+m)+'.'+((d>=10)?d:'0'+d);}});
//    $('#d1').datebox({required:true,value:date2qdate(new Date()),formatter:function(x){m=1+x.getMonth();d=x.getDate();return x.getFullYear()+'.'+((m>=10)?m:'0'+m)+'.'+((d>=10)?d:'0'+d);}});
}

sverlst=function(x,y){
    $("#cbsver").combobox({required:true,valueField:'version',textField:'text'});
    $("#cbsver").combobox("loadData", y);$("#cbsver").combobox('select',y[0].version);    
}

copyalgocpreq=function(){wscall(['{.db.S[(x;"J"$y);`cp]}','`'+$('#cbsid').combobox('getValue'),$('#cbsver').combobox('getValue')],copyalgocpres,{});}
copyalgocpres=function(x,y){editor.setValue(y);}

copyalgoparareq=function(){wscall(['{.db.S[(x;"J"$y);`para]}','`'+$('#cbsid').combobox('getValue'),$('#cbsver').combobox('getValue')],copyalgoparares,{});}
copyalgoparares=function(x,y){editor2.setValue(y);}

createst=function(){
    wscall(['{btadd[x[0];x[1];"J"$x[2];(tostring x[3];tostring x[10]);"F"$x[4];tostring x[5];"D"$x[6 7];"SJ"$\'x[8 9]]}',['`'+$('#gid').val(),'`'+$('#cbsid').combobox('getValue'),$('#cbsver').combobox('getValue'),' '+editor.getValue(),$('#cash').val(),' '+editor1.getValue(),$('input[name=btd0]').val(),$('input[name=btd1]').val(),$('#cbtype').combobox('getValue'),$('#cbfreq').combobox('getValue'),' '+editor2.getValue()]],createtestres,{'target':'plot'});
}

createtestres=function(x,y){
    alert('�زⴴ���ɹ�,ID:'+y+'.');
    testmgr();
}

cxltest=function(){
    var s=$('#testgrid').datagrid('getSelected');
    if(s==undefined){alert("����ѡ��һ���ز�.");}else{
	wscall(['{delete from `.db.B where id=x}','`'+s.id],cxltestres,{'target':'plot'});
    }
}

cxltestres=function(x,y){if(y.r<0){alert(y.errmsg);}else{alert('ɾ���ɹ�.');testmgr();};}

runtest=function(){
    var s=$('#testgrid').datagrid('getSelected');
    if(s==undefined){alert("����ѡ��һ���ز�.");}
    else{
	var run=true;
	if(s.begintime!='')run=confirm("�ز��Ѿ����й�.�Ƿ�ǿ���ٴ����У�");
	if(run)wscall(['{[x]btrun[x];`r`errmsg:(0;"")}','`'+s.id],runtestres,{'target':'plot'});
    }
}

runtestres=function(x,y){if(y.r<0){alert(y.errmsg);}else{alert('���н���.');testmgr();};}

futsymres1=function(x,y){
    maxgrid();    
    $('#'+x.target).html('<div id=jsxbox style="width:'+(pw-50)+'px;height:'+($('#'+x.target).panel('options').height-50)+'px;">');
    var n=y.N;
    var X0=-10,X1=10+4*n,Y1=y.H,Y0=y.L;
    var brd = JXG.JSXGraph.initBoard('jsxbox',{showCopyright:false,showNavigation:false,axis:{ticks:{ticksDistance:0.1}},boundingbox:[X0,Y1,X1,Y0],originX:0,originY:0});  //
    brd.suspendUpdate();
    for(i=0;i<n;i++){
	x0=4*i;x1=x0+3;y0=y.data[i][0];y1=y.data[i][1];
	brd.create('polygon',[[x0,y0],[x1,y0],[x1,y1],[x0,y1]],{hasInnerPoints: true});
    }
    brd.unsuspendUpdate();
    
    //var chart1=echarts.init($('#kline')[0]);
    //var option1={title:{text:x.sym},legend:{},tooltip:{axisPointer:{type:'cross'}},xAxis:{data:y.date},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.data,markPoint:{symbolSize:15,data:y.trade.map(function(x){return {coord:[x[0],x[1]],name:(x[2]=='1')?'buy':'sell',symbol:(x[2]=='2')?'emptytriangle':'triangle',symbolRotate:(x[2]=='2')?180:0,symbolOffset:[0,(x[2]=='2')?'50%':'-50%'],itemStyle:{normal:{color:(x[2]=='1')?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}}}]};    
    //chart1.setOption(option1);    
}

chgshow=function(){
    var s=$('#testgrid').datagrid('getSelected');if(s==undefined){alert("����ѡ��һ���ز�.");return;}if(s.endtime=='')return;
    var t=$('input[name=show]:checked').val();
    if(t=='asset'){wscall(['{[x]exec x:`$(-13_) each string {x,y}[first enter;leave],y:.db.B[x;`cash]+{0,x} sums netpnl from .db.B[x;`res;`GT]}','`'+s.id],showasset,{'target':'plot'});}
    else if(t=='trade'){wscall(['{[x]exec x:ti,y:netpnl from `ti xasc .db.B[x;`res][`GT]}','`'+s.id],showtrade,{target:'plot'});}
    else if(t=='gts'){wscall(['{[x]0!.db.B[x;`res][`GTS]}','`'+s.id],showgts,{target:'plot'});}
    else if(t=='tradelist'){wscall(['{[x]update string enter,string leave,string hold from `ti xasc .db.B[x;`res;`GT]}','`'+s.id],showtradelist,{'target':'plot'});}
    else if(t=='orderlist'){wscall(['{[x]ordlist::select sym,side,posefct,qty,price,status,ref,s0,s1,cumqty,avgpx,cumamt,cumfee,string ntime,string ftime,string ctime from .db.B[x;`res;`O];save `:/q/html/tmp/ordlist.csv;ordlist}','`'+s.id],showorderlist,{'target':'plot'});}
    else if(t=='cp'){wscall(['{[x].db.B[x;`cp]}','`'+s.id],showcp,{'target':'plot'});}
    else if(t=='para'){wscall(['{[x].db.B[x;`para]}','`'+s.id],showpara,{'target':'plot'});}
    else if(t=='kline'){wscall(['{[bid]r:.db.B[bid];x:r`xsym;D:r`d0`d1;f:r`freq;typ:r`btyp;.temp.t:t:$[`M=typ;delete t from update d:`$(-13_) each string d+t from minbars[typ;x;D;f];daybars[typ;x;D;f]];tr:select d:`date$ftime,t:`time$ftime,avgpx,side from r[`res;`O] where sym=x,cumqty>0;.temp.tr:tr:delete t from $[`M=typ;update d:`$(-13_) each string d+xbar[f] `minute$t from tr;update d:`$string xbar[f] d from tr];`N`H`L`date`data`trade!(count[t];1.03*exec max h from t;0.97*exec min l from t;exec string d from t;flip value flip select o,c,l,h from t;flip value flip tr)}','`'+s.id],futsymres,{target:'grid'})}
    else{}
}

/*
chgshow0=function(){
    var s=$('#testgrid').datagrid('getSelected');if(s==undefined){alert("����ѡ��һ���ز�.");return;}if(s.endtime=='')return;
    var t=$('input[name=show]:checked').val();
    if(t=='asset'){wscall(['{[x]exec x:`$(-13_) each string {x,y}[first enter;leave],y:.db.B[x;`cash]+{0,x} sums netpnl from .db.B[x;`res;`GT]}','`'+s.id],showasset,{'target':'plot'});}
    else if(t=='trade'){wscall(['{[x]exec x:ti,y:netpnl from `ti xasc .db.B[x;`res][`GT]}','`'+s.id],showtrade,{target:'plot'});}
    else if(t=='tradelist'){wscall(['{[x]update string enter,string leave,string hold from `ti xasc .db.B[x;`res;`GT]}','`'+s.id],showtradelist,{'target':'plot'});}
    else if(t=='orderlist'){wscall(['{[x]select sym,side,posefct,qty,price,status,ref,cumqty,avgpx,cumamt,cumfee,string ntime,string ftime,string ctime from .db.B[x;`res;`O]}','`'+s.id],showorderlist,{'target':'plot'});}
    else if(t=='cp'){wscall(['{[x].db.B[x;`cp]}','`'+s.id],showcp,{'target':'plot'});}
    else if(t=='kline'){wscall(['{[bid]r:.db.B[bid];x:r`xsym;D:r`d0`d1;f:r`freq;typ:r`btyp;.temp.t:t:$[`M=typ;delete bart from update bard:`$(-13_) each string bard+bart from minbars[x;D;f];daybars[x;D;f]];tr:select d:`date$ftime,t:`time$ftime,avgpx,side from r[`res;`O] where sym=x,cumqty>0;.temp.tr:tr:delete t from $[`M=typ;update d:`$(-13_) each string d+xbar[f] `minute$t from tr;update d:`$string xbar[f] d from tr];`date`data`trade!(exec string bard from t;flip value flip select i,open,close,low,h from t;flip value flip tr)}','`'+s.id],futsymres1,{target:'grid'})}
    else{}
}
*/

showcp=function(x,y){
    $('#'+x.target).html('<textarea id=cp rows=10 cols=100></textarea>');$('#cp').text(y);
    editor = CodeMirror.fromTextArea(document.getElementById("cp"),{lineNumbers:true,textWrapping:true,matchBrackets:true,mode:"text/x-q"});
}

showpara=function(x,y){
    $('#'+x.target).html('<textarea id=para rows=10 cols=100></textarea>');$('#para').text(y);
    editor = CodeMirror.fromTextArea(document.getElementById("para"),{lineNumbers:true,textWrapping:true,matchBrackets:true,mode:"text/x-q"});
}

showgts=function(x,y){
    $('#'+x.target).html('<div id=gtsgrid>');
    $('#gtsgrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,idField:'ti',columns:[[{field:'sym',title:'���',width:100,sortable:true},{field:'n',title:'��������',width:60,sortable:true},{field:'pnl',title:'������',width:100,sortable:true},{field:'maxwin',title:'�����������',width:100,sortable:true},{field:'maxloss',title:'���������ʧ',width:100,sortable:true},{field:'win',title:'ӯ������',width:80,sortable:true},{field:'loss',title:'��������',width:80,sortable:true}]]});
    $('#gtsgrid').datagrid('loadData',{total:y.length,rows:y});
}

showtradelist=function(x,y){
    $('#'+x.target).html('<div id=tradegrid>');
    $('#tradegrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,idField:'ti',columns:[[{field:'ti',title:'�������',width:40,sortable:true},{field:'sym',title:'���',width:100,sortable:true},{field:'n',title:'���ױ���',width:60,sortable:true},{field:'qty',title:'����',width:60,sortable:true},{field:'enter',title:'����ʱ��',width:150,sortable:true},{field:'leave',title:'ƽ��ʱ��',width:150,sortable:true},{field:'ep',title:'�����۸�',width:80,sortable:true},{field:'lp',title:'�볡�۸�',width:80,sortable:true},{field:'pnl',title:'����',width:80,sortable:true},{field:'delta',title:'�۸��',width:80,sortable:true},{field:'yield',title:'������',width:80,sortable:true},{field:'cash',title:'�ɽ����',width:80,sortable:true},{field:'hold',title:'�ֲ�����',width:80,sortable:true}]]});
    $('#tradegrid').datagrid('loadData',{total:y.length,rows:y});
}

showorderlist=function(x,y){
    $('#'+x.target).html('<a href="/tmp/ordlist.csv"><h1>����csv</h1></a><br><div id=ordergrid>');
    $('#ordergrid').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,idField:'ti',columns:[[{field:'sym',title:'���',width:100,sortable:true},{field:'side',title:'��������',width:40,sortable:true},{field:'posefct',title:'��ƽ��־',width:40,sortable:true},{field:'qty',title:'����',width:60,sortable:true},{field:'price',title:'ί�м۸�',width:60,sortable:true},{field:'status',title:'ί��״̬',width:40,sortable:true},{field:'ref',title:'ί�б�ע',width:140,sortable:true},{field:'s0',title:'��ע1',width:100,sortable:true},{field:'s1',title:'��ע2',width:100,sortable:true},{field:'cumqty',title:'�ɽ�����',width:60,sortable:true},{field:'avgpx',title:'�ɽ�����',width:80,sortable:true},{field:'cumamt',title:'�ɽ����',width:80,sortable:true},{field:'cumfee',title:'����˰��',width:80,sortable:true},{field:'ntime',title:'����ʱ��',width:150,sortable:true},{field:'ftime',title:'�ɽ�ʱ��',width:150,sortable:true},{field:'ctime',title:'����ʱ��',width:150,sortable:true}]]});
    $('#ordergrid').datagrid('loadData',{total:y.length,rows:y});
}


showasset=function(x,y){
    $('#'+x.target).html('<div id=asset style="width:'+($('#'+x.target).panel('options').width-50)+'px;height:'+($('#'+x.target).panel('options').height-50)+'px;">');
    var chart1=echarts.init($('#asset')[0]);
    var option1={legend:{},tooltip:{},xAxis:{type: 'category',data:y.x},yAxis:{scale:true},series:[{type:'line',data:y.y}]};    
    chart1.setOption(option1);
}

showtrade=function(x,y){
    $('#'+x.target).html('<div id=trade style="width:'+($('#'+x.target).panel('options').width-50)+'px;height:'+($('#'+x.target).panel('options').height-50)+'px;">');
    var chart1=echarts.init($('#trade')[0]);
    var option1={legend:{},tooltip:{},xAxis:{type: 'category',data:y.x},yAxis:{},series:[{type:'bar',data:y.y,itemStyle:{normal:{color:function(params){return (params.value>=0)?'red':'green';}}}}]};    
    chart1.setOption(option1);
}

//�ز⹦��
algoreq=function(x){wscall('not null .conf[`algots]',algores,{node:x});}
algores=function(x,y){
    if(!y)return; 
    var data=[
    	    {text:'ĸ���б�',attributes:{func:'oalistreq(x)'}},
	    {text:'��ʷ��ѯ',attributes:{func:'oahistreq(x)'}},
    ];
    //    alert($.toJSON(x.node.children));
    if(x.node.children == undefined)$('#menu').tree('append',{parent:x.node.target,data:data,});
};


oalistreq=function(){
    isrt=1;
    $('#ctrl').html('�����鿴:<input type=radio name=gtype value=0 checked>����ͼ<input type=radio name=gtype value=1>�ɽ�ͼ<input type=radio name=gtype value=4>ĸ������<input type=radio name=gtype value=2>�ӵ��ܾ�<input type=radio name=gtype value=3>�ӵ���ϸ,��������:<input type=radio name=gfreq value=5>5��<input type=radio name=gfreq value=10>10��<input type=radio name=gfreq value=30>30��<input type=radio name=gfreq value=60  checked>60��<input type=radio name=gfreq value=120>120��<input type=radio name=gfreq value=300>300��<input type=button value="ȫѡ" onclick="oaexport()"></input>�Զ�ˢ��:<input type=radio name=ufreq value=0 checked>��<input type=radio name=ufreq value=10>10��<input type=radio name=ufreq value=30>30��<input type=radio name=ufreq value=60>60��<input type=radio name=ufreq value=120>120��,���ˢ��:<input type=text id=updtime size=10></input>');
    qryoalist();
}

oahistreq=function(){
    isrt=0;    
    $('#ctrl').html('��ʼ����:<input type=text id=d0 name=d0></input>,��������:<input type=text id=d1 name=d1></input><input type=button value="��ѯ" onclick="qryoalist()"></input>�����鿴:<input type=radio name=gtype value=0 checked>����ͼ<input type=radio name=gtype value=1>�ɽ�ͼ<input type=radio name=gtype value=4>ĸ������<input type=radio name=gtype value=2>�ӵ��ܾ�<input type=radio name=gtype value=3>�ӵ���ϸ,��������:<input type=radio name=gfreq value=5>5��<input type=radio name=gfreq value=10>10��<input type=radio name=gfreq value=30>30��<input type=radio name=gfreq value=60  checked>60��<input type=radio name=gfreq value=120>120��<input type=radio name=gfreq value=300>300��<input type=button value="ȫѡ" onclick="oaexport()"></input>');
    $('#grid').html('');
    $('#plot').html('');
    $('#d0').datebox({required:true}); //,value:date2qdate(dateprev(new Date(),30)),formatter:function(x){m=1+x.getMonth();d=x.getDate();return x.getFullYear()+'.'+((m>=10)?m:'0'+m)+'.'+((d>=10)?d:'0'+d);}
    $('#d1').datebox({required:true}); //,value:date2qdate(new Date()),formatter:function(x){m=1+x.getMonth();d=x.getDate();return x.getFullYear()+'.'+((m>=10)?m:'0'+m)+'.'+((d>=10)?d:'0'+d);}
    $('#d0').datebox('setValue','today');
    $('#d1').datebox('setValue','today');
}

qryoalist=function(x){
    $('#grid').html('');
    $('#plot').html('');
    wscall(['oatbld',isrt>0,qdate2date((isrt>0)?'':$('input[name=d0]').val()),qdate2date((isrt>0)?'':$('input[name=d1]').val())],oalist,{'target':'grid'});
};

oalist=function(x,y){
    $('#'+x.target).html('<div id=oagrid>');
    $('#oagrid').datagrid({fit:true,rowStyler:function(x,y){t=y.cstag;return (t>0)?('background:'+(((t==1)||(t==3))?'red':'green')):'';},singleSelect:true,remoteSort:false,pagination:false,idField:'id',columns:[[{field:'id',title:'ĸ��ID',width:100,sortable:true},{field:'hsid',title:'�������',width:60,sortable:true},{field:'sym',title:'֤ȯ����',width:100,sortable:true},{field:'algo',title:'�㷨',width:60,sortable:true},{field:'status',title:'״̬',width:60,sortable:true,formatter:function(x){return (x==0)?'�½�':((x==1)?'���ֳɽ�':((x==2)?'ȫ���ɽ�':((x==4)?'�������':((x==6)?'�����ѱ�':((x==8)?'�ܾ�':((x==3)?'�������':((x=='C')?'����':x)))))));}},{field:'cstag',title:'����',width:50,sortable:true,formatter:function(x){return (x==3)?'��ͣ����':((x==2)?'����':((x==1)?'��ͣ':'��'));}},{field:'side',title:'����',width:40,sortable:true,formatter:function(x){return (x==1)?'����':'����';}},{field:'qty',title:'ί������',width:80,sortable:true},{field:'price',title:'ĸ���޼�',width:60,sortable:true},{field:'sentqty',title:'��������',width:80,sortable:true},{field:'cumqty',title:'�������',width:80,sortable:true},{field:'avgpx',title:'�ɽ�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'leavesqty',title:'ʣ������',width:80,sortable:true},{field:'ntime',title:'����ʱ��',width:160,sortable:true},{field:'pct',title:'��ɱ���',width:60,sortable:true,formatter:function(x){return (100*x).toFixed(2)+'%';}},{field:'vwap',title:'�г�����',width:60,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'mktqty',title:'�г��ɽ�',width:60,sortable:true,formatter:function(x){return x.toFixed(0);}},{field:'bias',title:'ִ�в���',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'mno',title:'�ɽ�����',width:80,sortable:true},{field:'ctime',title:'����ʱ��',width:60,sortable:true},{field:'ftime',title:'���ɽ�',width:60,sortable:true}]],onClickRow:function(x,y){z=$('input[name=gtype]:checked').val();((z==4)?qryoapara:((z==3)?qrysublst:((z==2)?qrysubrej:((z==1)?qrydetail:qryexec))))(y.id,$('input[name=gfreq]:checked').val());}});
    $('#oagrid').datagrid('loadData',{total:y.length,rows:y});
    $('#updtime').val(now());
};


qrysubrej=function(x,y){
    wscall(['`subrejd','`'+x,isrt>0,qdate2date((isrt>0)?'':$('input[name=d0]').val()),qdate2date((isrt>0)?'':$('input[name=d1]').val())],showsubrej,{'target':'plot'});
}

showsubrej=function(x,y){
    $('#'+x.target).html('<div id=subrej>');
    $('#subrej').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'id',title:'�ӵ�ID',width:120,sortable:true},{field:'qty',title:'����',width:80,sortable:true},{field:'price',title:'�۸�',width:60,sortable:true},{field:'ref',title:'��ע',width:200,sortable:true},{field:'ntime',title:'����ʱ��',width:200,sortable:true},{field:'msg',title:'�ܾ�ԭ��',width:600,sortable:true,formatter:function(x){return togbk(x);}}]]});
    $('#subrej').datagrid('loadData',{total:y.length,rows:y});
};

qrysublst=function(x,y){
    wscall(['`sublstd','`'+x,isrt>0,qdate2date((isrt>0)?'':$('input[name=d0]').val()),qdate2date((isrt>0)?'':$('input[name=d1]').val())],showsublst,{'target':'plot'});
}

showsublst=function(x,y){
    $('#'+x.target).html('<div id=sublst>');
    $('#sublst').datagrid({fit:true,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'id',title:'�ӵ�ID',width:120,sortable:true},{field:'status',title:'״̬',width:80,sortable:true,formatter:function(x){return (x==0)?'�½�':((x==1)?'���ֳɽ�':((x==2)?'ȫ���ɽ�':((x==4)?'�������':((x==6)?'�����ѱ�':((x==8)?'�ܾ�':((x==3)?'�������':((x=='C')?'����':x)))))));}},{field:'qty',title:'����',width:80,sortable:true},{field:'price',title:'�۸�',width:60,sortable:true},{field:'ntime',title:'����ʱ��',width:160,sortable:true},{field:'cumqty',title:'�ɽ�����',width:100,sortable:true},{field:'avgpx',title:'�ɽ�����',width:100,sortable:true,formatter:function(x){return x.toFixed(3);}},{field:'ref',title:'��ע',width:200,sortable:true},{field:'ctime',title:'����ʱ��',width:100,sortable:true},{field:'ftime',title:'�ɽ�ʱ��',width:100,sortable:true}]]});
    $('#sublst').datagrid('loadData',{total:y.length,rows:y});
};

qryoapara=function(x,y){
    wscall(['`oaparad','`'+x,isrt>0,qdate2date((isrt>0)?'':$('input[name=d0]').val()),qdate2date((isrt>0)?'':$('input[name=d1]').val())],showoapara,{'target':'plot'});
}

showoapara=function(x,y){
    $('#'+x.target).html('<div id=oapara>');
    $('#oapara').html(togbk($.toJSON(y)));
};

oaexport=function(){
    selectElement(document.getElementById('grid'));
};


qrydetail=function(x,y){
    $('#plot').html('<div id=detailplot style="width:'+(pw-50)+'px;height:'+(ph-50)+'px;">');
    wscall(['`oadetaild',isrt>0,'`'+x,parseInt(y)],detailplot,{'target':'detailplot'});
}

detailplot=function(x,y){
    var chart=new AmCharts.AmStockChart();
    chart.pathToImages='/images/';

    var categoryAxesSettings = new AmCharts.CategoryAxesSettings();
    categoryAxesSettings.minPeriod = "fff";
    chart.categoryAxesSettings = categoryAxesSettings;
    chart.categoryAxesSettings.maxSeries = 0;
    
    var panelsSettings = new AmCharts.PanelsSettings();
    panelsSettings.usePrefixes = true;
    panelsSettings.panEventsEnabled = true;
  /*
    chart.panelsSettings.autoMargins = false;
    chart.panelsSettings.marginTop = "15";
    chart.panelsSettings.marginLeft = "25";
    chart.panelsSettings.marginBottom = "15";
    chart.panelsSettings.marginRight = "25";
    chart.panelsSettings.depth3D=1;
    chart.panelsSettings.angle=45;
*/
    chart.panelsSettings = panelsSettings;


    var dataSet1 = new AmCharts.DataSet();
    //dataSet1.color = "#b0de09";

    dataSet1.fieldMappings=[
	{fromField: "bid",toField: "low"}, 
	{fromField: "ask",toField: "high"}, 
	{fromField: "avgpx",toField: "close"}, 
	{fromField: "cumqty",toField: "volume"},
	{fromField: "qty",toField: "value"}
];

    dataSet1.dataProvider=y;
    dataSet1.categoryField="date";

    chart.dataSets = [dataSet1];

    var stockPanel1 = new AmCharts.StockPanel();
    stockPanel1.showCategoryAxis = false;
    stockPanel1.title = "Px";
    stockPanel1.percentHeight = 60;
    stockPanel1.panEventsEnabled = true;				
    stockPanel1.numberFormatter    = {precision:3, decimalSeparator:'.', thousandsSeparator:''};


    var graph0 = new AmCharts.StockGraph();
    graph0.valueField = "high";
    graph0.type = "step";
    graph0.lineThickness = 1;
    graph0.bullet = "round";
    graph0.bulletSize = 3;
    graph0.useDataSetColors = false;
    graph0.lineColor='#00ff00';
    stockPanel1.addStockGraph(graph0);

    var graph1 = new AmCharts.StockGraph();
    graph1.valueField = "low";
    graph1.type = "step";
    graph1.lineThickness = 1;
    graph1.bullet = "round";
    graph1.bulletSize = 3;
    graph1.useDataSetColors = false;
    graph1.lineColor='#ff0000';
    stockPanel1.addStockGraph(graph1);


    var graph2 = new AmCharts.StockGraph();
    graph2.valueField = "close";
    graph2.type = "step";
    graph2.lineThickness = 0;
    graph2.bullet = "round";
    graph2.bulletSize = 5;
    graph2.useDataSetColors = false;
    graph2.lineColor='#0000ff';
    stockPanel1.addStockGraph(graph2);

    var stockLegend1 = new AmCharts.StockLegend();
    //stockLegend1.valueTextRegular = " ";
    //stockLegend1.markerType = "square";         
    stockPanel1.stockLegend = stockLegend1;

    var stockPanel2 = new AmCharts.StockPanel();
    stockPanel2.title = "Qty";
    stockPanel2.percentHeight = 40;
    stockPanel2.panEventsEnabled = true;
  				
    var valueAxis1 = new AmCharts.ValueAxis();
    valueAxis1.axisColor = "#FF6600";
    valueAxis1.axisThickness = 2;
    valueAxis1.gridAlpha = 0;
   // valueAxis1.stackType='regular';
    stockPanel2.addValueAxis(valueAxis1);

                // second value axis (on the right) 
    var valueAxis2 = new AmCharts.ValueAxis();
    valueAxis2.position = "right"; // this line makes the axis to appear on the right
    valueAxis2.axisColor = "#FCD202";
    valueAxis2.gridAlpha = 0;
    valueAxis2.axisThickness = 2;
    stockPanel2.addValueAxis(valueAxis2);
    
    var graph3 = new AmCharts.StockGraph();
    graph3.valueField = "volume";
    graph3.type = "column";
//    graph3.cornerRadiusTop = 4;
    graph3.useDataSetColors = false;
//    graph3.fillAlphas = 1;
    graph3.lineColor='#0000ff';
    graph3.valueAxis = valueAxis1;
    stockPanel2.addStockGraph(graph3);



    var graph4 = new AmCharts.StockGraph();
    graph4.valueField = "value";
    graph4.type = "line";
    graph4.bullet = "round";
    graph4.bulletSize = 5;
    graph4.fillAlphas = 0.3;

    graph4.useDataSetColors = false;
    graph4.valueAxis = valueAxis2;
    stockPanel2.addStockGraph(graph4);

    var stockLegend2 = new AmCharts.StockLegend();
    stockPanel2.stockLegend = stockLegend2;

    chart.panels = [stockPanel1, stockPanel2];

    var scrollbarSettings = new AmCharts.ChartScrollbarSettings();
    scrollbarSettings.graph = graph1;
    scrollbarSettings.updateOnReleaseOnly = true;
    chart.chartScrollbarSettings = scrollbarSettings;

    var cursorSettings = new AmCharts.ChartCursorSettings();
    cursorSettings.valueBalloonsEnabled = true;
    chart.chartCursorSettings = cursorSettings;

    var periodSelector = new AmCharts.PeriodSelector();
    periodSelector.periods = [
	{period: "mm",count:1,label:"1m"},
	{period: "mm",count:2,label:"2m"},
	{period: "mm",count:3,label:"3m"},
	{period: "mm",count:5,label:"5m"},
	{period: "mm",count:10,label:"10m"},
	{period: "mm",count:15,label:"15m"},
	{period: "mm",count:30,label:"30m"},
	{period: "hh",count:1,label: "1h"},
	{period: "hh",count:2,label: "2h"},
	{period: "MAX",label: "MAX"}
    ];
    periodSelector.inputFieldsEnabled=false;
    chart.periodSelector = periodSelector;

    $('#'+x.target).html('');
    chart.write(x.target);
}

qryexec=function(x,y){
    $('#plot').html('<div id=execplot style="width:'+(pw-50)+'px;height:'+(ph-50)+'px;">');
    wscall(['`oaexecd',isrt>0,'`'+x,parseInt(y)],execplot,{'target':'execplot'});
}

execplot=function(x,y){
    var chart=new AmCharts.AmSerialChart();
    chart.pathToImages='/images/';
    chart.dataProvider=y.t;
    chart.addLabel(300,20,'����۸�:'+y.h.ArrivalPx+',�г��۸�:'+y.h.MktPx+',�㷨����:'+y.h.AlgoPx+',ִ�гɱ�(���VWAP/IS):'+y.h.Cost0+'/'+y.h.Cost1+' bps.','left',14,'#F00F00','','',true);
    chart.categoryField='t';
    chart.marginTop=50;
    chart.marginBottom=30;
    chart.marginLeft=55;
    chart.marginRight=55;
    chart.categoryAxis.gridThickness=0;
    chart.categoryAxis.gridCount=12;
    chart.numberFormatter={precision:3,decimalSeparator:'.',thousandsSeparator:''};
    var va1=new AmCharts.ValueAxis();
    va1.axisThickness=1;
    va1.gridThickness=0;
    va1.maximum=1;
    chart.addValueAxis(va1);
    var g1=new AmCharts.AmGraph();
    g1.valueAxis=va1;
    g1.valueField='q0';
    g1.type='line';
    g1.title='MktPct';
    g1.lineColor='red';
    g1.bullet='round';
    chart.addGraph(g1);
    var g2=new AmCharts.AmGraph();
    g2.valueAxis=va1;
    g2.valueField='q1';
    g2.type='line';
    g2.title='AlgoPct';
    g2.lineColor='blue';
    g2.bullet='round';
    chart.addGraph(g2);
    var va2=new AmCharts.ValueAxis();
    va2.position='right';
    va2.axisThickness=1;
    va2.gridThickness=0;
    chart.addValueAxis(va2);
    var g3=new AmCharts.AmGraph();
    g3.valueAxis=va2;
    g3.valueField='p0';
    g3.type='line';
    g3.title='MktPx';
    g3.lineColor='black';
    g3.bullet='round';
    chart.addGraph(g3);
    var g4=new AmCharts.AmGraph();
    g4.valueAxis=va2;
    g4.valueField='p1';
    g4.type='line';
    g4.title='AlgoPx';
    g4.lineColor='green';
    g4.bullet='round';
    chart.addGraph(g4);
    var lgd=new AmCharts.AmLegend();
    lgd.align='center';
    chart.addLegend(lgd);
    var cc=new AmCharts.ChartCursor();
    chart.addChartCursor(cc);
    $('#'+x.target).html('');
    chart.write(x.target);
}


mktbrowsereq=function(x,y){wscall('flip `id`text!2#enlist ($[`Bk in key .db;key .db[`Bk];`symbol$()],`pos`hk`fut)',mktbrowseres,{});}

quoteviewreq=function(x){wscall(['{[x;d0;d1;f;typ]x:`$x;D:"D"$(d0;d1);f:"J"$f;typ:`$typ;ex:fs2e x;.temp.t:t:updlevel tb .temp.t0:update lb:-8 xprev 13 mavg c,lrd:-5 xprev 8 mavg c,lg: -3 xprev 5 mavg c from 0!$[`XHKG=ex;$[`M=typ;select o:first o,h:max h,l:min l,c:last c,a:sum q*w by d,t:xbar[f] t from .temp.BARM1 where sym=x,d within D;select t:last `minute$t,o:first o,h:max h,l:min l,c:last c,a:sum q*w by d:xbar[f] (?[`N=typ;`date$`month$;?[`W=typ;`week$;::]]) d from .temp.BARD1 where sym=x,d within D];hisbars[typ;x;D;f]];`sym`name`seq`data`mark`amt`lb`lr`lg!(x;.db.QX[x;`name];$[`M=typ;exec `$(16#) each string d+t from t;exec `$string d from t];flip value flip select o,c,l,h from t;flip value flip select i,px:?[level>0;h;l],level from t where level<>0;exec a from t;exec lb from t;exec lrd from t;exec lg from t)}',x,$('input[name=symd0]').val(),$('input[name=symd1]').val(),$('#cbfreq').combobox('getValue'),$('#cbtype').combobox('getValue')],quoteviewres,{target:'grid',sym:x});} //delete lh,ll,rh,rl,lr,rr,top,bot from 

symchgres=function(x,y){
    $("#cbsym").combobox('select',y);    
}

mktbrowseres=function(x,y){
    $('#plot').panel('resize',{height:'1px'});
    $('#main').layout('resize');
    $('#ctrl').html('���:<input id="cbbk" style="width:80px"></input>����:<input id="cbsym" style="width:200px"></input>��ʼ����:<input type=text id=symd0 name=symd0 style="width:150px"></input>,��������:<input type=text id=symd1 name=symd1 style="width:150px">Ƶ��:<input id="cbfreq" style="width:80px"></input>����:<input id="cbtype" style="width:80px"></input><input type=button id=bksymbut value="��ѯ"></input><input type=button id=bkprevbut value="<="></input><input type=button id=bknextbut value="=>"><input type=button id=d0prevbut value="<-"></input><input type=button id=d0nextbut value="->"></input>����:<input id="cbstep" style="width:80px"><input type=button id=d1prevbut value="<-"></input><input type=button id=d1nextbut value="->"></input>');

    $('#bksymbut').click(function(){quoteviewreq($('#cbsym').combobox('getValue'))});   

    $('#symd0').datebox({required:true});
    $('#symd1').datebox({required:true,});
    $('#symd0').datebox('setValue','1/1/2016');
    $('#symd1').datebox('setValue','today');

    $("#cbfreq").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbfreq").combobox("loadData",[{id:1,text:'1'},{id:5,text:'5'},{id:10,text:'10'},{id:15,text:'15'},{id:20,text:'20'},{id:30,text:'30'},{id:60,text:'60'}]);$("#cbfreq").combobox('select',1);    

    $("#cbtype").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbtype").combobox("loadData",[{id:"N",text:'����'},{id:"W",text:'����'},{id:"D",text:'����'},{id:"M",text:'������'}]);$("#cbtype").combobox('select',"D");    

    $("#cbbk").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){wscall(['{[x]flip `id`text!2#enlist .temp.bksymlst:$[x=`pos;exec distinct sym from .db.P;x=`hk;exec sym from .db.QX where ex=`SEHK,not null src;x=`fut;exec sym from .db.PD;.db[`Bk;x]]}','`'+x.id],bksymlst,{});}});
    $("#cbbk").combobox("loadData", y);$("#cbbk").combobox('select',y[0].id);    

    $('#bkprevbut').click(function(){wscall(['{[x]y:.temp.bksymlst;y mod[;count y] -1+y?x}','`'+$('#cbsym').combobox('getValue')],symchgres,{});});
    $('#bknextbut').click(function(){wscall(['{[x]y:.temp.bksymlst;y mod[;count y] 1+y?x}','`'+$('#cbsym').combobox('getValue')],symchgres,{});});

    $("#cbstep").combobox({required:true,valueField:'id',textField:'text'});
    $("#cbstep").combobox("loadData",[{id:1,text:'1'},{id:5,text:'5'},{id:10,text:'10'},{id:15,text:'15'},{id:20,text:'20'},{id:30,text:'30'},{id:60,text:'60'}]);$("#cbstep").combobox('select',5);    

    $('#d0prevbut').click(function(){var ds=$('#symd0').datebox('getValue');var n=parseInt($('#cbstep').combobox('getValue'));var d=new Date(ds);d.setDate(d.getDate()-n);$('#symd0').datebox('setValue',(1+d.getMonth())+'/'+d.getDate()+'/'+d.getFullYear());$('#bksymbut').click();});
    $('#d0nextbut').click(function(){var ds=$('#symd0').datebox('getValue');var n=parseInt($('#cbstep').combobox('getValue'));var d=new Date(ds);d.setDate(d.getDate()+n);$('#symd0').datebox('setValue',(1+d.getMonth())+'/'+d.getDate()+'/'+d.getFullYear());$('#bksymbut').click();}); //

    $('#d1prevbut').click(function(){var ds=$('#symd1').datebox('getValue');var d=new Date(ds);d.setDate(d.getDate()-parseInt($('#cbstep').combobox('getValue')));$('#symd1').datebox('setValue',(1+d.getMonth())+'/'+d.getDate()+'/'+d.getFullYear());$('#bksymbut').click();});
    $('#d1nextbut').click(function(){var ds=$('#symd1').datebox('getValue');var d=new Date(ds);d.setDate(d.getDate()+parseInt($('#cbstep').combobox('getValue')));$('#symd1').datebox('setValue',(1+d.getMonth())+'/'+d.getDate()+'/'+d.getFullYear());$('#bksymbut').click();});

}

bksymlst=function(x,y){
    $("#cbsym").combobox({required:true,valueField:'id',textField:'text',onSelect:function(x){quoteviewreq(x.id);}}); //,onSelect:function(x){wscall(['{[x]select id:sym,text:sym from .temp.T where product=x}','`'+x.id],futsymlst,{});}
    $("#cbsym").combobox("loadData", y);$("#cbsym").combobox('select',y[0].id);    
}


quoteviewres=function(x,y){
    $('#'+x.target).html('<div id=kline style="width:'+(pw+80)+'px;height:'+(bh-220)+'px;">'); //$('#'+x.target).panel('options').height
    var chart1=echarts.init($('#kline')[0]);
    var option1={title:{text:y.sym+'('+y.name+')'},legend:{},tooltip:{trigger:'axis',axisPointer:{type:'cross'},backgroundColor:'rgba(245,245,245,0.8)',borderWidth:1,borderColor:'#ccc',padding:10,textStyle:{color:'#000'}},axisPointer:{link:{xAxisIndex:'all'},label:{backgroundColor:'#777'}},grid:[{left:'3%',right:'5%',height:'65%'},{left:'3%',right:'5%',top:'74%',height:'20%'}],xAxis:[{type:'category',data:y.seq},{type:'category',gridIndex:1,data:y.seq,axisLabel:{show: false}}],yAxis:[{scale:true},{scale:true,gridIndex:1,axisLine:{onZero:false},axisTick:{show:false},splitLine:{show:false},axisLabel:{show:true}}],dataZoom:[{show:true,xAxisIndex:[0,1],type:'slider',top:'96%',start:0,end:100},{type:'inside',xAxisIndex:[0,1]}],series:[{type:'k',data:y.data,markPoint:{data:y.mark.map(function(x){return {coord:[x[0],x[1]],name:(x[2]<0)?'buy':'sell',symbol:(x[2]>0)?'emptytriangle':'triangle',symbolSize:10*Math.abs(x[2]),symbolRotate:(x[2]>0)?180:0,symbolOffset:[0,(x[2]>0)?'-50%':'50%'],itemStyle:{normal:{color:(x[2]<0)?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}}},{name:'amt',type:'bar',xAxisIndex:1,yAxisIndex:1,data:y.amt}]}; //,{name:'lb',type:'line',data:y.lb,smooth:true,lineStyle:{normal:{color:'rgb(0,0,255)',opacity:1}}},{name:'lr',type:'line',data:y.lr,smooth:true,lineStyle:{normal:{color:'rgb(255,0,0)',opacity:1}}},{name:'lg',type:'line',data:y.lg,smooth:true,lineStyle:{normal:{color:'rgb(0,255,0)',opacity:1}}}
    chart1.setOption(option1);
}

//���м��
etfmonmmreq=function(x,y){wscall(['{[x]`UDL`s`D!(update string settleday,string extime from 0!.db.Ts[x;`UDL];update string time from 0!.db.Ts[x;`s];{flip `k`v!(key x;(-3!) each value x)} `lastont`active`STOP`ERRSTOP`openauct_pxhigh`openauct_pxlow`BULK`POSMAX`POSMIN#.db.Ts[x])}','`8508_femm_518880'],etfmonmmres,{target:'grid'});}
etfmonfureq=function(x,y){wscall(['{[x]update string askpx,string asksz,string bidpx,string bidsz,0^POSMAX,0^POSMIN,0^BULK,0^POS from 0!.db.Ts[x;`t]}','`8508_fehg_au'],etfmonfures,{target:'grid'});}
etfmontsreq=function(x,y){wscall(['{[x]update string tm,tdvalrt:(tdmktval%sum tdmktval where (not null tm)&tdmktval>0),ydvalrt:(ydmktval%sum ydmktval where (not null tm)&ydmktval>0) from delete trd from 0!stat_now[`;x;`]}','`dc2'],etfmontsres,{target:'grid'});}
etfmonsumreq=function(x,y){wscall(['{[x]y:0!.db.Ts[x;`DETAIL];`S`t`b`v1`v2`lag`cumqty1s`xiopv!({flip `k`v!(key x;(-3!) each value x)} .db.Ts[x;`Stat];string y`tm;y`ob;y`spread;y`mktsp;`float$y`lag;y`cumqty1s;y`xiopv)}','`8508_femm_518880'],etfmonsumres,{});}
etfmonrlreq=function(x,y){wscall('0!.db.RL',etfmonrlres,{});}

//`sym`divid`movpos`settleday`n`sup`inf`ask`bid`px`extime`d`d0`djump   `n`m`px`realpx`qty`leavesqty`id`time

etfmonmmres=function(x,y){
    $('#'+x.target).html('<table><tr><th><div id=mmudl style="align:center;width:'+dw+'px;height:100px"></th></tr><tr><td><div id=mmstat style="align:center;width:'+dw+'px;height:300px"></td></tr></table>');
    $('#mmudl').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'sym',title:'sym',width:160,sortable:true},{field:'divid',title:'divid',width:60,sortable:true},{field:'movpos',title:'movpos',width:180,sortable:true},{field:'settleday',title:'settleday',width:60,sortable:true},{field:'n',title:'n',width:60,sortable:true},{field:'sup',title:'sup',width:60,sortable:true},{field:'inf',title:'inf',width:60,sortable:true},{field:'ask',title:'ask',width:60,sortable:true},{field:'bid',title:'bid',width:60,sortable:true},{field:'px',title:'px',width:60,sortable:true},{field:'extime',title:'extime',width:200,sortable:true}]]});
    $('#mmudl').datagrid('loadData',{total:y.UDL.length,rows:y.UDL});

    $('#mmstat').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'k',title:'ͳ����',width:160,sortable:true},{field:'v',title:'ͳ��ֵ',width:600,sortable:true}]]});
    $('#mmstat').datagrid('loadData',{total:y.D.length,rows:y.D});

    $('#plot').html('<div id=mms style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#mms').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'n',title:'n',width:60,sortable:true},{field:'m',title:'m',width:60,sortable:true},{field:'px',title:'px',width:60,sortable:true},{field:'realpx',title:'realpx',width:60,sortable:true},{field:'qty',title:'qty',width:60,sortable:true},{field:'leavesqty',title:'leavesqty',width:60,sortable:true},{field:'id',title:'id',width:60,sortable:true},{field:'time',title:'time',width:160,sortable:true}]]});
    $('#mms').datagrid('loadData',{total:y.s.length,rows:y.s});
}

//`ts`TGT`UDL`STOP`ERRSTOP`TGTUDLQTY`POSMAX`POSMIN`BULK`POS0`TGTQTY0`UDLQTY0`POS`TGTQTY`UDLQTY`askpx`asksz`bidpx`bidsz

etfmonfures=function(x,y){
    $('#'+x.target).html('<div id=fulst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#fulst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'ts',width:160,sortable:true},{field:'TGT',title:'TGT',width:60,sortable:true},{field:'UDL',title:'UDL',width:180,sortable:true},{field:'STOP',title:'STOP',width:60,sortable:true},{field:'ERRSTOP',title:'ERRSTOP',width:60,sortable:true},{field:'TGTUDLQTY',title:'TGTUDLQTY',width:60,sortable:true},{field:'POSMAX',title:'POSMAX',width:60,sortable:true},{field:'POSMIN',title:'POSMIN',width:60,sortable:true},{field:'BULK',title:'BULK',width:60,sortable:true},{field:'POS0',title:'POS0',width:60,sortable:true},{field:'TGTQTY0',title:'TGTQTY0',width:200,sortable:true},{field:'UDLQTY0',title:'UDLQTY0',width:60,sortable:true},{field:'POS',title:'POS',width:60,sortable:true},{field:'TGTQTY',title:'TGTQTY',width:60,sortable:true},{field:'UDLQTY',title:'UDLQTY',width:60,sortable:true},{field:'askpx',title:'askpx',width:160,sortable:true},{field:'asksz',title:'asksz',width:160,sortable:true},{field:'bidpx',title:'bidpx',width:160,sortable:true},{field:'bidsz',title:'bidsz',width:160,sortable:true}]]});
    $('#fulst').datagrid('loadData',{total:y.length,rows:y}); //
}

//`tm`ts`acc`sym`pnl`pnl1`conmktval`xpnl`multi`px`pc`rl`lqty`sqty`ratio`lamt`samt`tdpos`ydpos`tdmktval`ydmktval`sendo`fillo`eff`conpos
etfmontsres=function(x,y){
    $('#'+x.target).html('<div id=tslst style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#tslst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'tm',title:'tm',width:160,sortable:true},{field:'ts',title:'ts',width:60,sortable:true},{field:'acc',title:'acc',width:180,sortable:true},{field:'sym',title:'sym',width:160,sortable:true},{field:'pnl',title:'pnl',width:100,sortable:true},{field:'pnl1',title:'pnl1',width:100,sortable:true},{field:'conmktval',title:'conmktval',width:100,sortable:true},{field:'xpnl',title:'xpnl',width:60,sortable:true},{field:'multi',title:'multi',width:60,sortable:true},{field:'px',title:'px',width:60,sortable:true},{field:'pc',title:'pc',width:200,sortable:true},{field:'rl',title:'rl',width:60,sortable:true},{field:'lqty',title:'lqty',width:60,sortable:true},{field:'sqty',title:'sqty',width:60,sortable:true},{field:'ratio',title:'ratio',width:60,sortable:true},{field:'lamt',title:'lamt',width:100,sortable:true},{field:'samt',title:'samt',width:100,sortable:true},{field:'tdpos',title:'tdpos',width:60,sortable:true},{field:'ydpos',title:'ydpos',width:60,sortable:true},{field:'tdmktval',title:'tdmktval',width:100,sortable:true},{field:'ydmktval',title:'ydmktval',width:100,sortable:true},{field:'tdvalrt',title:'tdvalrt',width:100,sortable:true},{field:'ydvalrt',title:'ydvalrt',width:100,sortable:true},{field:'sendo',title:'sendo',width:60,sortable:true},{field:'fillo',title:'fillo',width:60,sortable:true},{field:'eff',title:'eff',width:60,sortable:true},{field:'conpos',title:'conpos',width:100,sortable:true}]]});
    $('#tslst').datagrid('loadData',{total:y.length,rows:y});
}

etfmonsumres=function(x,y){
    $('#grid').html('<div id=etfsum style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#etfsum').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'k',title:'ͳ����',width:160,sortable:true},{field:'v',title:'ͳ��ֵ',width:600,sortable:true}]]});
    $('#etfsum').datagrid('loadData',{total:y.S.length,rows:y.S});

    $('#plot').html('<div id=etfplot style="width:'+(pw+80)+'px;height:'+(ph)+'px;">'); //$('#'+x.target).panel('options').height
    var chart1=echarts.init($('#etfplot')[0]);
    var option1={title:[{text:'spread',top:'0%'},{text:'lag(ms)',top:'21%'},{text:'cumqty1s',top:'47%'},{text:'xiopv',top:'67%'}],grid:[{left:'3%',right:'5%',top:'3%',height:'18%'},{left:'3%',right:'5%',top:'25%',height:'18%'},{left:'3%',right:'5%',top:'50%',height:'15%'},{left:'3%',right:'5%',top:'70%',height:'12%'}],xAxis:[{type:'category',data:y.t},{type:'category',gridIndex:1,data:y.t},{type:'category',gridIndex:2,data:y.t},{type:'category',gridIndex:3,data:y.t}],yAxis:[{type:'value'},{type:'value',gridIndex:1},{type:'value',gridIndex:2},{type:'value',gridIndex:3}],series:[{type:'line',data:y.v1,name:'spread'},{type:'line',data:y.v2},{type:'line',data:y.lag,xAxisIndex:1,yAxisIndex:1,name:'lag(ms)'},{type:'line',data:y.cumqty1s,xAxisIndex:2,yAxisIndex:2,name:'cumqty1s'},{type:'line',data:y.xiopv,xAxisIndex:3,yAxisIndex:3,name:'xiopv'}]}; 
    chart1.setOption(option1);
}

//`ts`acc`sym`maxlong`maxshort`maxlongday`maxshortday`maxlongord`maxshortord`maxordbuy`maxordsell`maxfund`maxfundord`maxprdlong`maxprdshort`maxno1s`maxno5s`maxno20s`maxno1m`maxnc1s`maxnc5s`maxnc20s`maxnc1m`maxnord`maxncxl`maxnrej

etfmonrlres=function(x,y){
    $('#grid').html('<div id=etfrl style="align:center;width:'+dw+'px;height:'+dh+'px">');
    $('#etfrl').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'ts',title:'ts',width:60,sortable:true},{field:'acc',title:'acc',width:60,sortable:true},{field:'sym',title:'sym',width:160,sortable:true},{field:'maxno1s',title:'maxno1s',width:160,sortable:true},{field:'maxno5s',title:'maxno5s',width:160,sortable:true},{field:'maxno20s',title:'maxno20s',width:160,sortable:true},{field:'maxno1m',title:'maxno1m',width:160,sortable:true},{field:'maxnc1s',title:'maxnc1s',width:160,sortable:true},{field:'maxnc5s',title:'maxnc5s',width:160,sortable:true},{field:'maxnc20s',title:'maxnc20s',width:160,sortable:true},{field:'maxnc1m',title:'maxnc1m',width:160,sortable:true},{field:'maxnord',title:'maxnord',width:160,sortable:true},{field:'maxncxl',title:'maxncxl',width:160,sortable:true},{field:'maxnrej',title:'maxnrej',width:160,sortable:true}]]});
    $('#etfrl').datagrid('loadData',{total:y.length,rows:y});
}

//����ͼ��
axshowreq=function(x,y){$('#ctrl').html('');$('#plot').html('');maxgrid();$('#grid').html('<iframe style="width:100%;height:100%;frameborder:0;border:0;" src="http://172.17.65.140:8090/ax">');;wscall(['{[x]h:hopen 8080;h ".gg.cheat.sheet[]"}',''],axshowres,{target:'grid'});}
axshowreq1=function(x,y){$('#ctrl').html('');$('#plot').html('');window.open("http://172.17.65.140:8090/ax/app/inspector/index.html#query=&va='Table'&winCacheID=0","");wscall(['{[x]h:hopen 8080;h ".gg.cheat.sheet[]"}',''],axshowres,{target:'grid'});}
axshowres=function(x,y){}


//��ĳط���
ngxreq=function(){wscall(['{.temp.date:`s#(.ctrl.conn.hdb.h `date),.db.sysdate;.temp.dmap:`s#.temp.date!.temp.date;update string nend,size*1e-4 from delete mbar from 0!ngx[] lj 1!select sym,cumamt from .temp.PD}','`'],ngxres,{t1:'plot',t2:'grid'});}

ngxres=function(x,y){
    $('#main').layout('panel','south').panel('resize',{height:ph});$('#main').layout('resize');

    $('#'+x.t1).html('Ƶ��:<input type=radio name=btyp value=C onclick="chgbtyp()">������Լ����<input type=radio name=btyp value=D checked onclick="chgbtyp()">����<input type=radio name=btyp value=M onclick="chgbtyp()">������,</input>��ʼ����:<input type=text id=ngxd0 name=ngxd0 style="width:150px"></input>,</input><input type=button id=d0prev value="<-" onclick="decd0()"></input></input><input type=button id=d0d1prev value="<=" onclick="decd0d1()"></input></input><input type=button id=d1prev value="-<" onclick="decd1()"></input><input type=text id=dmstep value=1 style="width:50px"><input type=button id=d1next value="->" onclick="incd1()"></input><input type=button id=d0d1next value="=>" onclick="incd0d1()"></input><input type=button id=d0next value=">-" onclick="incd0()"></input>,��������:<input type=text id=ngxd1 name=ngxd1 style="width:150px">ȥβ:<input type=text id="droptail" value=0 style="width:80px">,<input type=button id=dtprev value="<-" onclick="incdt()"></input><input type=text id=dtstep value=5 style="width:50px"><input type=button id=dtnext value="->" onclick="decdt()"></input>,��ͷ:<input type=text id="drophead" value=0 style="width:80px">,<input type=button id=dhprev value="<-" onclick="incdh()"></input><input type=text id=dhstep value=5 style="width:50px"><input type=button id=dhnext value="->" onclick="decdh()"></input>,��ʾ:<input type=radio name=ptyp value=K checked  onclick="ngxupd()">K��(�ֻ�:<input type=text id="cutpara" value="0.2 5" style="width:80px">, <input type=checkbox name=strd value="T" onclick="ngxupd()"/>��ʾ����)<input type=radio name=ptyp value=L onclick="ngxupd()">����<input type=button id=ngbuy value="����" onclick="ngbuy()"></input><input type=text id=ngpx value=0 style="width:80px"><input type=button id=ngsell value="����" onclick="ngsell()"></input><br><div id=ngxlst style="align:center;width:'+dw+'px;height:'+dh+'px">');$('#'+x.t2).html('<div id=ngxflot style="width:600px;height:300px">');
    $('#ngxlst').datagrid({fit:false,singleSelect:true,remoteSort:false,pagination:false,columns:[[{field:'sym',title:'�ڻ���Լ',width:80,sortable:true},{field:'product',title:'Ʒ��',width:30,sortable:true},{field:'name',title:'����',width:100,sortable:true,formatter:function(x){return togbk(x);}},{field:'nend',title:'ҹ�̽���',width:60,sortable:true},{field:'cumamt',title:'�ɽ����',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'size',title:'��Լ��С',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'feeunit',title:'������(%)',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'pos',title:'�ֲ�',width:60,sortable:true},{field:'cost',title:'�ɱ�',width:60,sortable:true},{field:'price',title:'�ּ�',width:60,sortable:true},{field:'pnl',title:'ӯ��',width:60,sortable:true},{field:'lcpx',title:'��ͷֹ��',width:60,sortable:true},{field:'scpx',title:'��ͷֹ��',width:60,sortable:true},{field:'dtr',title:'������',width:50,sortable:true},{field:'dS1',title:'��֧��1',width:80,sortable:true},{field:'dS0',title:'��֧��0',width:80,sortable:true},{field:'dR0',title:'������0',width:80,sortable:true},{field:'dR1',title:'������1',width:80,sortable:true},{field:'tr',title:'������',width:50,sortable:true},{field:'s1',title:'��֧��1',width:80,sortable:true},{field:'s0',title:'��֧��0',width:80,sortable:true},{field:'r0',title:'������0',width:80,sortable:true},{field:'r1',title:'������1',width:80,sortable:true},{field:'ltr',title:'ǰ������',width:50,sortable:true},{field:'ls1',title:'ǰ��֧��1',width:80,sortable:true},{field:'ls0',title:'ǰ��֧��0',width:80,sortable:true},{field:'lr0',title:'ǰ������0',width:80,sortable:true},{field:'lr1',title:'ǰ������1',width:80,sortable:true}]],onClickRow:function(index,r){ngxsymreq(r.sym);}}); //,{field:'pc',title:'����',width:60,sortable:true},{field:'ph',title:'���',width:60,sortable:true,formatter:function(x){return x.toFixed(2);}},{field:'pl',title:'���',width:60,sortable:true},{field:'pq0',title:'�򼯺ϳɽ�',width:80,sortable:true},{field:'pq',title:'��ɽ�',width:60,sortable:true},{field:'h5',title:'5�ոߵ�',width:80,sortable:true},{field:'l5',title:'5�յ͵�',width:60,sortable:true},{field:'qm',title:'5�վ���',width:60,sortable:true},{field:'q0m',title:'���Ͼ��۾���',width:60,sortable:true}
    
    $('#ngxlst').datagrid('loadData',{total:y.length,rows:y});
    $("#ngxlst").datagrid("resize",{height:'300px'});

    $('#ngxd0').datebox({required:true});
    $('#ngxd1').datebox({required:true});
    
    chgbtyp();
};


chgbtyp=function(){
    var t=$('input[name=btyp]:checked').val();
    if(t=='M'){
	$('#ngxd0').datebox('setValue','today');
    }else{
	$('#ngxd0').datebox('setValue','1/1/2020');
    }
    $('#ngxd1').datebox('setValue','today');
    ngxupd();
}


incdt=function(){$('#droptail').val(parseInt($('#droptail').val())+parseInt($('#dtstep').val()));ngxupd();}
decdt=function(){$('#droptail').val(Math.max(0,parseInt($('#droptail').val())-parseInt($('#dtstep').val())));ngxupd();}
incdh=function(){$('#drophead').val(parseInt($('#drophead').val())+parseInt($('#dhstep').val()));ngxupd();}
decdh=function(){$('#drophead').val(Math.max(0,parseInt($('#drophead').val())-parseInt($('#dhstep').val())));ngxupd();}

decd0=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(-n,0,d0,d1);}
incd0=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(n,0,d0,d1);}
decd1=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(0,-n,d0,d1);}
incd1=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(0,n,d0,d1);}

decd0d1=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(-n,-n,d0,d1);}
incd0d1=function(){var n=parseInt($('#dmstep').val());var d0=$('input[name=ngxd0]').val();var d1=$('input[name=ngxd1]').val();dtreq(n,n,d0,d1);}


dtreq=function(n0,n1,d0,d1){wscall(['{[n0;n1;d0;d1]n0:`long$n0;n1:`long$n1;d0:"D"$d0;d1:"D"$d1;d0:.temp.dmap d0;d1:.temp.dmap d1;d0:.temp.date n0+.temp.date?d0;d1:.temp.date n1+.temp.date?d1;`d0`d1!{x:string x;x[5 6],"/",x[8 9],"/",x til 4} each d0,d1}',n0,n1,d0,d1],dtres,{});}
dtres=function(x,y){$('#ngxd0').datebox('setValue',y.d0);$('#ngxd1').datebox('setValue',y.d1);ngxupd();}


ngorder=function(x,y){$("input[name=ufreq][value=0]").prop("checked","checked");var r=$('#ngxlst').datagrid('getSelected');if(r==undefined)return;s=r.sym;p=$('#ngpx').val();if(!confirm('ȷ��'+((x>0)?'����':'����')+s+'@'+p+'?')) return;wscall(['{[x;y]y:"F"$y;'+((x>0)?'nb':'ns')+'[x,y]}','`'+s,p],ngorderres,{})};
ngbuy=ngorder.curry(1);ngsell=ngorder.curry(-1);

ngorderres=function(x,y){$("input[name=ptyp][value=K]").prop("checked","checked");var r=$('#ngxlst').datagrid('getSelected');ngxupd();};

ngxupd=function(){var r=$('#ngxlst').datagrid('getSelected');if(r==undefined){}else{ngxsymreq(r.sym);}}

ngxsymreq=function(x){wscall(['{[x;y;d0;d1;z;w;cf]y:`$y;z:"J"$z;w:"J"$w;d0:"D"$d0;d1:"D"$d1;cf:"FJ"$\'vs[" "] cf;.temp.t:t:neg[w]_ z _$[y=`C;(`d`t xcols update t:00:00 from delete pd from select from .temp.cbar where d within (d0,d1),pd=.db.QX[x;`product]),$[not .db.sysdate within d0,d1;();`d xcols update d:.db.sysdate from .ctrl.conn.rdb.h[({[x]select t:{00:00} last i,o:first price,h:max price,l:min price,c:last price,v:last cumqty,a:last cumqty*vwap,p:last openint from quote where sym=x};x)]];0!hisbars[y;x;d0,d1;1]];.temp.c:c:cutcover2[cf[0];cf[1]] update h:o|c,l:o&c from t;.temp.tbr:tbr:delete lh,ll,rh,rl,lr,rr,top,bot from updlevel tb t;r:rst[tbr];.temp.tr:tr:histrds[x;d0,d1];`date`data`seq`tbr`mark`line`tr`trade`cline!(string $[y=`M;exec t from t;exec d from t];flip value flip select o,c,l,h from t;string $[y=`M;exec t from tbr;exec d from tbr];flip value flip select o,c,l,h from tbr;flip value flip select i,px:?[level>0;h;l],level from tbr where level<>0;r`lin;r`tr;flip value flip select seq,avgpx,side from ($[y=`M;update `minute$t from tr;update t:00:00 from tr]) lj 2!update seq:i from t;cline[c])}','`'+x,$('input[name=btyp]:checked').val(),$('input[name=ngxd0]').val(),$('input[name=ngxd1]').val(),$('#drophead').val(),$('#droptail').val(),$('#cutpara').val()],ngxsymres,{sym:x,target:'grid',btyp:$('input[name=btyp]:checked'),ptyp:$('input[name=ptyp]:checked').val(),strd:$('input[name=strd]:checked').val()});} //[x:sym,y:btyp,d0,d1:D,z:drophead,w:droptail,cf:cutpara]tr:histrds[y;d0,d1];.temp.tr:tr:delete t from $[`M=typ;update d:`$(-13_) each string d+xbar[1] `minute$t from tr;update d:`$string xbar[1] d from tr];

ngxsymres=function(x,y){
    $('#'+x.target).html('<div id=kline style="width:'+dw+'px;height:'+dh+'px;">'); //$('#'+x.target).panel('options').height
    var chart1=echarts.init($('#kline')[0]);
    var option1=(x.ptyp=='K')?{title:{text:x.sym+':'+y.tr},legend:{},tooltip:{trigger:'axis',axisPointer:{type: 'cross'}},xAxis:{data:y.date},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.data,markPoint:(x.strd=='T')?{symbolSize:15,data:y.trade.map(function(x){return {coord:[x[0],x[1]],name:(x[2]=='1')?'buy':'sell',symbol:(x[2]=='2')?'emptytriangle':'triangle',symbolRotate:(x[2]=='2')?180:0,symbolOffset:[0,(x[2]=='2')?'50%':'-50%'],itemStyle:{normal:{color:(x[2]=='1')?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}}:{},markLine:{symbol:['none', 'none'],data:y.cline.map(function(x){return [{coord:[x[0],x[1]]},{coord:[x[2],x[3]]}]})}}]}:{title:{text:x.sym+':'+y.tr},legend:{},tooltip:{trigger:'axis',axisPointer:{type: 'cross'}},xAxis:{type:'category',data:y.seq},yAxis:{scale:true},dataZoom:[{show:true,xAxisIndex:[0],type:'slider',top:'90%',start:0,end:100},{type:'inside'}],series:[{type:'k',data:y.tbr,markPoint:{data:y.mark.map(function(x){return {coord:[x[0],x[1]],name:(x[2]<0)?'buy':'sell',symbol:(x[2]>0)?'emptytriangle':'triangle',symbolSize:10*Math.abs(x[2]),symbolRotate:(x[2]>0)?180:0,symbolOffset:[0,(x[2]>0)?'-50%':'50%'],itemStyle:{normal:{color:(x[2]<0)?'blue':'green'}}}}),tooltip:{formatter:function(param){return param.name+'<br>'+param.data.coord[0]+'<br>'+param.data.coord[1];}}},markLine:{symbol:['none', 'none'],data:y.line.map(function(x){return [{coord:[x[0],x[1]]},{coord:[x[2],x[3]]}]})}}]}; //,symbol:'triangle'
    chart1.setOption(option1);
}

/*		
var tszq='`zq',tsctp='`ctp',tsqtx='`qtx',tsacd='`oacd';
var tsi51='`i51',tsi51a='`i51a',tsi90='`i90',tsi90a='`i90a',tsi91='`i91',tsi91a='`i91a',tsi91b='`i91b',tsi91c='`i91c',tsi10='`i10',tsi10a='`i10a',tsi10b='`i10b',tsi10c='`i10c',tsi10d='`i10d';
var mmlst=[tsi51,tsi51a,tsi90,tsi90a,tsi91,tsi91a,tsi91b,tsi91c,tsi10,tsi10a,tsi10b,tsi10c,tsi10d];


	    {text:'���̲���',children:[ 
		{text:'zq',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tszqordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tszqmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tszqposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tszqordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tszqmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tszqparareq(x)'}},		    
		]},
	    ]},
	    {text:'�ڻ�����',children:[ 
		{text:'qtx',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsqtxordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsqtxmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsqtxposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsqtxordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsqtxmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsqtxparareq(x)'}},		    
		]},
		{text:'acd',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsacdordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsacdmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsacdposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsacdordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsacdmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsacdparareq(x)'}},		    
		]},
		{text:'����ʯ����',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsimmordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsimmmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsimmposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsimmordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsimmmathisreq(x)'}},
		]},
		{text:'i1911&i2001',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi10ordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi10matreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi10posreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi10ordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi10mathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi10parareq(x)'}},		    
		]},
		{text:'i1911&i2001.a',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi10aordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi10amatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi10aposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi10aordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi10amathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi10aparareq(x)'}},		    
		]},
		{text:'i1911&i2001.b',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi10bordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi10bmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi10bposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi10bordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi10bmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi10bparareq(x)'}},		    
		]},
		{text:'i1911&i2001.c',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi10cordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi10cmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi10cposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi10cordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi10cmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi10cparareq(x)'}},		    
		]},
		{text:'i1911&i2001.d',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi10dordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi10dmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi10dposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi10dordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi10dmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi10dparareq(x)'}},		    
		]},
		{text:'i1905&i1907',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi51ordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi51matreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi51posreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi51ordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi51mathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi51parareq(x)'}},		    
		]},
		{text:'i1905&i1907.a',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi51aordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi51amatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi51aposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi51aordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi51amathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi51aparareq(x)'}},		    
		]},
		{text:'i1907&i1909',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi90ordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi90matreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi90posreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi90ordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi90mathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi90parareq(x)'}},		    
		]},
		{text:'i1907&i1909.a',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi90aordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi90amatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi90aposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi90aordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi90amathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi90aparareq(x)'}},		    
		]},
		{text:'i1909&i1911',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi91ordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi91matreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi91posreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi91ordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi91mathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi91parareq(x)'}},		    
		]},
		{text:'i1909&i1911.a',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi91aordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi91amatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi91aposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi91aordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi91amathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi91aparareq(x)'}},		    
		]},
		{text:'i1909&i1911.b',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi91bordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi91bmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi91bposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi91bordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi91bmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi91bparareq(x)'}},		    
		]},
		{text:'i1909&i1911.c',children:[
		    {text:'ί�в�ѯ',attributes:{func:'tsi91cordreq(x)'}},		
		    {text:'�ɽ���ѯ',attributes:{func:'tsi91cmatreq(x)'}},
		    {text:'�ֲֲ�ѯ',attributes:{func:'tsi91cposreq(x)'}},
		    {text:'��ʷί��',attributes:{func:'tsi91cordhisreq(x)'}},		
		    {text:'��ʷ�ɽ�',attributes:{func:'tsi91cmathisreq(x)'}},
		    {text:'���Բ���',attributes:{func:'tsi91cparareq(x)'}},		    
		]},
	    ]},

//tszq
tszqordreq=ordreqfun.curry(tszq);tszqmatreq=matreqfun.curry(tszq);tszqposreq=posreqfun.curry(tszq);
tszqordhisreq=ordhisreqfun.curry(tszq);tszqmathisreq=mathisreqfun.curry(tszq);tszqparareq=tsparareq.curry(tszq);

//tsctp
tsctpordreq=ordreqfun.curry(tsctp);tsctpmatreq=matreqfun.curry(tsctp);tsctpposreq=posreqfun.curry(tsctp);
tsctpordhisreq=ordhisreqfun.curry(tsctp);tsctpmathisreq=mathisreqfun.curry(tsctp);tsctpparareq=tsparareq.curry(tsctp);

//tsqtx
tsqtxordreq=ordreqfun.curry(tsqtx);tsqtxmatreq=matreqfun.curry(tsqtx);tsqtxposreq=posreqfun.curry(tsqtx);
tsqtxordhisreq=ordhisreqfun.curry(tsqtx);tsqtxmathisreq=mathisreqfun.curry(tsqtx);tsctpparareq=tsparareq.curry(tsqtx);

//tsacd
tsacdordreq=ordreqfun.curry(tsacd);tsacdmatreq=matreqfun.curry(tsacd);tsacdposreq=posreqfun.curry(tsacd);
tsacdordhisreq=ordhisreqfun.curry(tsacd);tsacdmathisreq=mathisreqfun.curry(tsacd);tsacdparareq=tsparareq.curry(tsacd);

//mmlst
tsimmordreq=ordreqfun.curry(mmlst);tsimmmatreq=matreqfun.curry(mmlst);tsimmposreq=posreqfun.curry(mmlst);
tsimmordhisreq=ordhisreqfun.curry(mmlst);tsimmmathisreq=mathisreqfun.curry(mmlst);

//i10
tsi10ordreq=ordreqfun.curry(tsi10);tsi10matreq=matreqfun.curry(tsi10);tsi10posreq=posreqfun.curry(tsi10);
tsi10ordhisreq=ordhisreqfun.curry(tsi10);tsi10mathisreq=mathisreqfun.curry(tsi10);tsi10parareq=tsparareq.curry(tsi10);

//i10a
tsi10aordreq=ordreqfun.curry(tsi10a);tsi10amatreq=matreqfun.curry(tsi10a);tsi10aposreq=posreqfun.curry(tsi10a);
tsi10aordhisreq=ordhisreqfun.curry(tsi10a);tsi10amathisreq=mathisreqfun.curry(tsi10a);tsi10aparareq=tsparareq.curry(tsi10a);

//i10b
tsi10bordreq=ordreqfun.curry(tsi10b);tsi10bmatreq=matreqfun.curry(tsi10b);tsi10bposreq=posreqfun.curry(tsi10b);
tsi10bordhisreq=ordhisreqfun.curry(tsi10b);tsi10bmathisreq=mathisreqfun.curry(tsi10b);tsi10bparareq=tsparareq.curry(tsi10b);

//i10c
tsi10cordreq=ordreqfun.curry(tsi10c);tsi10cmatreq=matreqfun.curry(tsi10c);tsi10cposreq=posreqfun.curry(tsi10c);
tsi10cordhisreq=ordhisreqfun.curry(tsi10c);tsi10cmathisreq=mathisreqfun.curry(tsi10c);tsi10cparareq=tsparareq.curry(tsi10c);

//i10d
tsi10dordreq=ordreqfun.curry(tsi10d);tsi10dmatreq=matreqfun.curry(tsi10d);tsi10dposreq=posreqfun.curry(tsi10d);
tsi10dordhisreq=ordhisreqfun.curry(tsi10d);tsi10dmathisreq=mathisreqfun.curry(tsi10d);tsi10dparareq=tsparareq.curry(tsi10d);

//i51
tsi51ordreq=ordreqfun.curry(tsi51);tsi51matreq=matreqfun.curry(tsi51);tsi51posreq=posreqfun.curry(tsi51);
tsi51ordhisreq=ordhisreqfun.curry(tsi51);tsi51mathisreq=mathisreqfun.curry(tsi51);tsi51parareq=tsparareq.curry(tsi51);

//i51a
tsi51aordreq=ordreqfun.curry(tsi51a);tsi51amatreq=matreqfun.curry(tsi51a);tsi51aposreq=posreqfun.curry(tsi51a);
tsi51aordhisreq=ordhisreqfun.curry(tsi51a);tsi51amathisreq=mathisreqfun.curry(tsi51a);tsi51aparareq=tsparareq.curry(tsi51a);

//i90
tsi90ordreq=ordreqfun.curry(tsi90);tsi90matreq=matreqfun.curry(tsi90);tsi90posreq=posreqfun.curry(tsi90);
tsi90ordhisreq=ordhisreqfun.curry(tsi90);tsi90mathisreq=mathisreqfun.curry(tsi90);tsi90parareq=tsparareq.curry(tsi90);

//i90a
tsi90aordreq=ordreqfun.curry(tsi90a);tsi90amatreq=matreqfun.curry(tsi90a);tsi90aposreq=posreqfun.curry(tsi90a);
tsi90aordhisreq=ordhisreqfun.curry(tsi90a);tsi90amathisreq=mathisreqfun.curry(tsi90a);tsi90aparareq=tsparareq.curry(tsi90a);

//i91
tsi91ordreq=ordreqfun.curry(tsi91);tsi91matreq=matreqfun.curry(tsi91);tsi91posreq=posreqfun.curry(tsi91);
tsi91ordhisreq=ordhisreqfun.curry(tsi91);tsi91mathisreq=mathisreqfun.curry(tsi91);tsi91parareq=tsparareq.curry(tsi91);

//i91a
tsi91aordreq=ordreqfun.curry(tsi91a);tsi91amatreq=matreqfun.curry(tsi91a);tsi91aposreq=posreqfun.curry(tsi91a);
tsi91aordhisreq=ordhisreqfun.curry(tsi91a);tsi91amathisreq=mathisreqfun.curry(tsi91a);tsi91aparareq=tsparareq.curry(tsi91a);

//i91b
tsi91bordreq=ordreqfun.curry(tsi91b);tsi91bmatreq=matreqfun.curry(tsi91b);tsi91bposreq=posreqfun.curry(tsi91b);
tsi91bordhisreq=ordhisreqfun.curry(tsi91b);tsi91bmathisreq=mathisreqfun.curry(tsi91b);tsi91bparareq=tsparareq.curry(tsi91b);

//i91c
tsi91cordreq=ordreqfun.curry(tsi91c);tsi91cmatreq=matreqfun.curry(tsi91c);tsi91cposreq=posreqfun.curry(tsi91c);
tsi91cordhisreq=ordhisreqfun.curry(tsi91c);tsi91cmathisreq=mathisreqfun.curry(tsi91c);tsi91cparareq=tsparareq.curry(tsi91c);

    $('#futsymbut').click(function(y){wscall(['{[x;d0;d1;f;typ]x:`$x;D:"D"$(d0;d1);f:"J"$f;typ:`$typ;.temp.t:t:(0!.ctrl.conn.hdb.h ({[D;x;f;typ]$[`D=typ;select o:first price,h:max price,l:min price,c:last price by d:xbar[f] date from quote where date within D,sym=x,date<>2019.06.07,not (date=2019.06.10)&(time within 00:00 08:55)|(time within 16:00 24:00),(0<low)&(low<=price)&(price<=high);delete d0,i0 from `d0`i0 xasc select d0:first date,i0:first i,o:first price,h:max price,l:min price,c:last price,t0:first `minute$time,t1:last `minute$time by d:date,t:xbar[f] `minute$time from quote where date within D,sym=x,date<>2019.06.07,not (date=2019.06.10)&(time within 00:00 08:55)|(time within 16:00 24:00),(0<low)&(low<=price)&(price<=high)]};D;x;f;typ)),$[`D=typ;0!select o:first open,h:max high,l:min low,c:last close by d:bard from bar where sym=x,bard within D;0!delete i from `i xasc select i:first i,o:first open,h:max high,l:min low,c:last close,t0:first `minute$bart,t1:last `minute$bart by d:bard,t:xbar[f] `minute$bart from bar where sym=x,bard within D];if[`M=typ;t:delete t,t1 from update d:`$(-13_) each string d+t from select from .temp.t where (any t0 within/:.db.PD[.db.QX[x;`product];`sess])|(any t1 within/:.db.PD[.db.QX[x;`product];`sess])];tr:(select d:trddate ftime,t:`time$ftime,avgpx,side from .hdb.O where sym=x,cumqty>0,(trddate ftime) within D),select d:trddate ftime,t:`time$ftime,avgpx,side from .db.O where sym=x,cumqty>0,(trddate ftime) within D;.temp.tr:tr:$[`M=typ;select `$(-13_) each string d+xbar[f] `minute$t,avgpx,side from tr;select d:`$string d,avgpx,side from tr];`date`data`trade!(exec string d from t;flip value flip select o,c,l,h from t;flip value flip tr)}',$('#cbsym').combobox('getValue'),$('input[name=symd0]').val(),$('input[name=symd1]').val(),$('#cbfreq').combobox('getValue'),$('#cbtype').combobox('getValue')],futsymres,{target:'grid'});});

*/









