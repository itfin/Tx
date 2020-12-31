#include "kcomm.h"
#include "t2sdk_interface.h"
#include "HsFutuSystemInfo.h"
#include "DataCollect.h"

#if defined(J64)
#define NewConnectionEx NewConnection
#define PRI_Create Create 
#define PRI_Connect Connect
#define PRI_GetErrorMsg GetErrorMsg
#define PRI_SendBiz SendBiz
#define PRI_RecvBiz RecvBiz
#else
#define NewConnectionEx NewConnection
#define PRI_Create Create 
#define PRI_Connect Connect
#define PRI_GetErrorMsg GetErrorMsg
#define PRI_SendBiz SendBiz
#define PRI_RecvBiz RecvBiz
#endif
#include <queue>

#define PIPE_CAPACITY 65536
#define b9 b9
#define d9 d9

ZI run=0,p[2];ZC b[2*PIPE_CAPACITY];

#if defined(WIN32)||defined(WIN64)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
ZI pipe(I*p){R !CreatePipe((PHANDLE)p+0,(PHANDLE)p+1,0,0);}
ZI dwBytes;
#define read(x,y,z) ReadFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL) 
#define write(x,y,z) WriteFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL); 
#define close(x) CloseHandle((HANDLE)x)
Z CRITICAL_SECTION g_CS;
#define INITLOCK InitializeCriticalSection(&g_CS)
#define FREELOCK DeleteCriticalSection(&g_CS)
#define LOCK EnterCriticalSection(&g_CS)
#define UNLOCK LeaveCriticalSection(&g_CS)
#else
Z pthread_mutex_t g_mutex=PTHREAD_MUTEX_INITIALIZER;
#define INITLOCK 
#define FREELOCK 
#define LOCK pthread_mutex_lock(&g_mutex)
#define UNLOCK pthread_mutex_unlock(&g_mutex)
#endif


Z std::queue<K> mq;
Z std::queue<K> fq;

Z CConfigInterface * lpConfig=NULL;
Z CConnectionInterface * lpConnection=NULL;

Z CConfigInterface * lpConfigSub=NULL;
Z CConnectionInterface * lpConnectionSub=NULL;
Z CSubscribeInterface* lpSub=NULL;

ZK onmq(I i){
  K L=knk(0);
  //  DBG("onmq:%d\n",pthread_self());

  read(i,&b,PIPE_CAPACITY);

  LOCK;
  while (!mq.empty()){
    jk(&L,d9(mq.front()));

    /*
      fq.push(mq.front());
    */

    mq.pop();
  }
  UNLOCK;    
  k(0,(S)"onhst2",L,(K)0);

  R ki(0);
}

Z V mpub(K x){
  //  DBG("mpub:%d\n",pthread_self());

  LOCK;
  mq.push(b9(1,x));

  /*
    while (!fq.empty()){
    r0(fq.front());
    fq.pop();
    }
  */

  UNLOCK;    
  write(p[1],&b,1);
};

/*
  K2(encodepwd){
    C buf[64];
    memset(buf,0,sizeof(buf));
    R ks(Encode(buf,xs,y->i));
  }
*/

  K decodepack(IF2UnPacker *lpUnPacker){
    K L=NULL,L0=NULL,L1=NULL;
    I i=0,t=0,j=0,k=0,n=0,m=0,nRS=0;
    int len=0;
    C typ=' ';
    V *ptr=NULL;
    S str=NULL;
    L=knk(0);

    if(NULL==lpUnPacker) R L;
    
    nRS=lpUnPacker->GetDatasetCount();
    for(i=0;i<nRS;++i){
      lpUnPacker->SetCurrentDatasetByIndex(i);
      n=lpUnPacker->GetColCount();
      m=(I)lpUnPacker->GetRowCount();
      DBG("RS[%d]nC=%d,nR=%d\n",i,n,m);
      if((m<=0)||(n<=0))continue;
      L0=ktn(KS,n);L1=knk(0);
    
      for (t=0;t<n;++t){
	str=(S)lpUnPacker->GetColName(t);
	typ=lpUnPacker->GetColType(t);
	DBG("Add fld[%d],name=%s,type=%c\n",t,str,typ);
	kS(L0)[t]=ss(str);
	switch (typ){
	case 'I':jk(&L1,ktn(KI,m));break;
	case 'C':jk(&L1,ktn(KC,m));break;
	case 'S':jk(&L1,knk(0));break;
	case 'F':jk(&L1,ktn(KF,m));break;
	case 'R':jk(&L1,knk(0));break;
	default: jk(&L1,knk(0));break;
	}
	DBG("fld[%d] head added!\n",t);
      }  
      for (j=0;j<m;++j){
	DBG("row=%d\n",j);
	for (k=0;k<n;++k){
	  typ=lpUnPacker->GetColType(k);
	  DBG("col=%d,typ=%c\n",k,typ);
	  switch (typ){
	  case 'I':
	    kI(kK(L1)[k])[j]=lpUnPacker->GetIntByIndex(k);break;
	  case 'C':
	    kC(kK(L1)[k])[j]=lpUnPacker->GetCharByIndex(k);break;
	  case 'S':
	    jk(&kK(L1)[k],kp((S)lpUnPacker->GetStrByIndex(k)));break;
	  case 'F':
	    kF(kK(L1)[k])[j]=lpUnPacker->GetDoubleByIndex(k);break;
	  case 'R':len=0;ptr=lpUnPacker->GetRawByIndex(k, &len);jk(&kK(L1)[k],kpn((S)ptr,len));break;
	  default:
	    jk(&kK(L1)[k],(K)0);break;
	  }
	  DBG("cell added!\n");
	}
	lpUnPacker->Next();
      }
      jk(&L,xT(xD(L0,L1)));
    }  
    R L;
  }


class CCallback : public CCallbackInterface{
public:
  unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv);
  unsigned long  FUNCTION_CALL_MODE AddRef();
  unsigned long  FUNCTION_CALL_MODE Release();
  void FUNCTION_CALL_MODE OnConnect(CConnectionInterface *lpConnection);
  void FUNCTION_CALL_MODE OnSafeConnect(CConnectionInterface *lpConnection);
  void FUNCTION_CALL_MODE OnRegister(CConnectionInterface *lpConnection);
  void FUNCTION_CALL_MODE OnClose(CConnectionInterface *lpConnection);
  void FUNCTION_CALL_MODE OnSent(CConnectionInterface *lpConnection, int hSend, void *reserved1, void *reserved2, int nQueuingData);
  void FUNCTION_CALL_MODE Reserved1(void *a, void *b, void *c, void *d);
  void FUNCTION_CALL_MODE Reserved2(void *a, void *b, void *c, void *d);
  int  FUNCTION_CALL_MODE Reserved3();
  void FUNCTION_CALL_MODE Reserved4();
  void FUNCTION_CALL_MODE Reserved5();
  void FUNCTION_CALL_MODE Reserved6();
  void FUNCTION_CALL_MODE Reserved7();
  void FUNCTION_CALL_MODE OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *lpUnPackerOrStr, int nResult);
  void FUNCTION_CALL_MODE OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult);
  void FUNCTION_CALL_MODE OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg);
};

unsigned long CCallback::QueryInterface(const char *iid, IKnown **ppv){	return 0;}
unsigned long CCallback::AddRef(){return 0;}
unsigned long CCallback::Release(){return 0;}

void CCallback::OnConnect(CConnectionInterface *lpConn){mpub(knk(2,ks((S)"OnConnect"),kb(lpConn==lpConnectionSub)));}
void CCallback::OnSafeConnect(CConnectionInterface *lpConn){mpub(knk(2,ks((S)"OnSafeConnect"),kb(lpConn==lpConnectionSub)));}
void CCallback::OnRegister(CConnectionInterface *lpConn){mpub(knk(2,ks((S)"OnRegister"),kb(lpConn==lpConnectionSub)));}
void CCallback::OnClose(CConnectionInterface *lpConn){mpub(knk(2,ks((S)"OnClose"),kb(lpConn==lpConnectionSub)));if(lpConn==lpConnectionSub)lpConnectionSub=NULL;else lpConnection=NULL;}
void CCallback::OnSent(CConnectionInterface *lpConn, int hSend, void *reserved1, void *reserved2, int nQueuingData){DBG("OnSent");}

void CCallback::OnReceivedBiz(CConnectionInterface *lpConnection, int hSend, const void *ptr, int nResult){
  K L;
  DBG("OnReceivedBiz");
  switch (nResult){
  case 0:
  case 1:
    {L=decodepack((IF2UnPacker *)ptr);break;}
  case 2:
    {L=kp((S)ptr); break;}
    default:
      {L=knk(0);}
    } 
  mpub(knk(2,ks((S)"OnReceivedBiz"),knk(3,ki(hSend),ki(nResult),L)));
}

void CCallback::OnReceivedBizEx(CConnectionInterface *lpConnection, int hSend, LPRET_DATA lpRetData, const void *lpUnpackerOrStr, int nResult){DBG("OnReceivedBizEx");}

void CCallback::OnReceivedBizMsg(CConnectionInterface *lpConnection, int hSend, IBizMessage* lpMsg){  
  K L;
  int nResult;
  
  DBG("OnReceivedBizMsg\n");
  if (lpMsg==NULL) R;
  nResult=lpMsg->GetReturnCode();
  DBG("nResult=%d\n",nResult);
  
  int iLen = 0;
  const void * lpBuffer = lpMsg->GetContent(iLen);
  IF2UnPacker * lpUnPacker = NewUnPacker((void *)lpBuffer, iLen);
  if (lpUnPacker != NULL){
    lpUnPacker->AddRef();//添加释放内存引用
    L=decodepack(lpUnPacker);
    lpUnPacker->Release();
  }else L=knk(0);
  mpub(knk(2,ks((S)"OnReceivedBizMsg"),knk(3,ki(hSend),ki(nResult),L)));
}

void CCallback::Reserved1(void *a, void *b, void *c, void *d){}
void CCallback::Reserved2(void *a, void *b, void *c, void *d){}
int  CCallback::Reserved3(){return 0;}
void CCallback::Reserved4(){}
void CCallback::Reserved5(){}
void CCallback::Reserved6(){}
void CCallback::Reserved7(){}

class CSubCallback : public CSubCallbackInterface{
  unsigned long  FUNCTION_CALL_MODE QueryInterface(const char *iid, IKnown **ppv){return 0;}
  unsigned long  FUNCTION_CALL_MODE AddRef(){return 0;}
  unsigned long  FUNCTION_CALL_MODE Release(){return 0;}
  void FUNCTION_CALL_MODE OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData);
  void FUNCTION_CALL_MODE OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo);
};

void CSubCallback::OnReceived(CSubscribeInterface *lpSub,int subscribeIndex, const void *lpData, int nLength,LPSUBSCRIBE_RECVDATA lpRecvData){
  K L;
  IF2UnPacker* lpUnPack = NewUnPacker((void*)lpData,nLength);

  if (lpUnPack){
    lpUnPack->AddRef();
    L=decodepack((IF2UnPacker *)lpUnPack);
    lpUnPack->Release();
  }
  mpub(knk(2,ks((S)"SubRecv"),knk(2,ki(subscribeIndex),L)));
}

 void CSubCallback::OnRecvTickMsg(CSubscribeInterface *lpSub,int subscribeIndex,const char* TickMsgInfo){DBG("RecvTickMsg");}

extern "C"{
  Z CCallback cb0;
  Z CCallback cb1;
  Z CSubCallback scb;

  V disct2(){
    if(NULL!=lpConnection)lpConnection->Release();lpConnection=NULL;
    if(NULL!=lpConfig)lpConfig->Release();
  }

  V disct2sub(){
    if(NULL!=lpConnectionSub)lpConnectionSub->Release();lpConnectionSub=NULL;
    if(NULL!=lpConfigSub)lpConfigSub->Release();
    if(NULL!=lpSub)lpSub->Release();
  }

  V pack0(IF2Packer* pack,K x){
    I i=0,n=0,vt=0;
    C t='R'; 
    K Lk=NULL,Lv=NULL,kv=NULL;
      
    Lk=xx;
    Lv=xy;
    n=Lk->n;
    vt=Lv->t;
    DBG("n=%d,kt=%d,vn=%d,vt=%d\n",n,Lk->t,Lv->n,vt);
    if(0<vt){
      switch(vt){
      case KI:t='I';break;
      case KF:t='F';break;
      case KC:t='C';break;
      case KS:t='S';break;
      default:t='R';break;  
      }
      for(i=0;i<n;i++){
	DBG("field=%s,t=%d\n",kS(Lk)[i],t);
	pack->AddField(kS(Lk)[i],t,2048,10);
      }
      for(i=0;i<n;i++){
	switch(vt){
	case KI:pack->AddInt(kI(Lv)[i]);break;
	case KF:pack->AddDouble(kF(Lv)[i]);break;
	case KC:pack->AddChar(kC(Lv)[i]);break;
	case KS:pack->AddStr(kS(Lv)[i]);break;
	default:pack->AddRaw(kG(kK(Lv)[i]),kv->n);break;  	  
	}	
      }
    }else{	  
      for(i=0;i<n;i++){
	if(0==Lv->t){
	  switch(kK(Lv)[i]->t){
	  case -KI:t='I';break;
	  case -KF:t='F';break;
	  case -KC:t='C';break;
	  case -KS:t='S';break;
	  default:t='R';break;  
	  }
	}
	pack->AddField(kS(Lk)[i],t);
	DBG("Add Field[%d]%s->%c,vt=%d\n",i,kS(Lk)[i],t,kK(Lv)[i]->t);
      }
      for(i=0;i<n;i++){
	kv=kK(Lv)[i];
	switch(kv->t){
	case -KI:pack->AddInt(kv->i);break;
	case -KF:pack->AddDouble(kv->f);break;
	case -KC:pack->AddChar(kv->g);break;
	case -KS:pack->AddStr(kv->s);break;
	default:pack->AddRaw(kG(kv),kv->n);break;  
	}
	DBG("Add Value[%d]%d\n",i,kv->t);
      }
    }
  }

  V dopack(IF2Packer* pack,K x){
    I t=0,n=0;

    pack->AddRef();
    pack->BeginPack();

    t=x->t;
    n=x->n;
    if(99==t){
      pack0(pack,x);
    }else if(0==t){
      //pack0(pack,kK(x)[0]);
      //pack->NewDataset("1");pack0(pack,kK(x)[1]);
      
      DO(n,if(0<i)pack->NewDataset(i+"");pack0(pack,kK(x)[i]))
    }else{}
    
    pack->EndPack();
    //DBG("pack ok!");
  }

  K1(initt2){
    I f=0;

    if(run) R ki(-8);

    if(pipe(p)) R ki(-9);

#if defined(WIN32)||defined(WIN64)
#else
    if(-1==(f = fcntl(p[0],F_GETFL,0)))R ki(-2);
    f |= O_NONBLOCK;
    if (fcntl(p[0],F_SETFL,f)==-1) R ki(-3);
#endif

    run++;
    INITLOCK; 
    sd1(p[0],onmq);
    R ki(run);
  }


  K1(freet2){
    if(!run) R ki(-1);

    disct2();
    disct2sub();

    INITLOCK; 
    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;

    run--;
    R ki(run);
  }


  K2(connt2){ //(tradeconfig,timeout):timeout>0(Sync),timeout<0(Async)
    K Lk=NULL,Lv=NULL,Ck=NULL,Cv=NULL;
    int r=0,t=0,f=0,tmout=abs(y->i);

    disct2();

    lpConfig = NewConfig();
    lpConfig->AddRef();
    Lk=xx;Lv=xy;
    
    for(int i=0;i<Lv->n;i++){
      Ck=kK(Lk)[i];Cv=kK(Lv)[i];t=Cv->t;
      if((-KI)==Cv->t){
	lpConfig->SetInt(kS(Ck)[0],kS(Ck)[1],Cv->i);
      }else if((-KS)==Cv->t){
	lpConfig->SetString(kS(Ck)[0],kS(Ck)[1],Cv->s);
      }else{}
    }

    lpConnection = NewConnectionEx(lpConfig);
    if(NULL==lpConnection) R ki(-1);
    
    lpConnection->AddRef();

    if(0<y->i){
      if(r=lpConnection->PRI_Create(NULL)) {O("PRI_Create:r=%d\n",r);O(lpConnection->PRI_GetErrorMsg(r));R ki(r);};
      if(r=lpConnection->PRI_Connect(tmout)) {O(lpConnection->PRI_GetErrorMsg(r));R ki(r);};
    }else{
      if(r=lpConnection->PRI_Create(&cb0)) {O("PRI_Create:r=%d\n",r);O(lpConnection->PRI_GetErrorMsg(r));R ki(r);};
      if(r=lpConnection->PRI_Connect(tmout)) {O(lpConnection->PRI_GetErrorMsg(r));R ki(r);};
    }
    
    R ki(0);
  }

  K3(connt2sub){ //(subconfig,sublogin,timeout)
    K Lk=NULL,Lv=NULL,Ck=NULL,Cv=NULL,L=NULL;
    int r=0,t=0,f=0,tmout=z->i;
    IF2Packer* pack = NULL;
    IF2UnPacker* unpack=NULL;
    Lk=xx;Lv=xy;

    disct2sub();

    lpConfigSub = NewConfig();
    lpConfigSub->AddRef();

    for(int i=0;i<Lv->n;i++){
      Ck=kK(Lk)[i];Cv=kK(Lv)[i];t=Cv->t;
      if((-KI)==Cv->t){
	lpConfigSub->SetInt(kS(Ck)[0],kS(Ck)[1],Cv->i);
      }else if((-KS)==Cv->t){
	lpConfigSub->SetString(kS(Ck)[0],kS(Ck)[1],Cv->s);
      }else{}
    }

    lpConnectionSub = NewConnectionEx(lpConfigSub);
    lpConnectionSub->AddRef();
    if(r=lpConnectionSub->PRI_Create(&cb1)) {O(lpConnectionSub->PRI_GetErrorMsg(r));R ki(r);};
    if(r=lpConnectionSub->PRI_Connect(tmout)) {O(lpConnectionSub->PRI_GetErrorMsg(r));R ki(r);};

    S bizName = (S)lpConfigSub->GetString("subcribe","biz_name","");
    lpSub = lpConnectionSub->NewSubscriber(&scb,bizName,5000);
    if (!lpSub){O("NewSubscribe Error: %s\n",lpConnectionSub->GetMCLastError());R ki(-1);}
    lpSub->AddRef();

    CSubscribeParamInterface* lpSubscribeParam = NewSubscribeParam();
    lpSubscribeParam->AddRef();
    char* topicName = (char*)lpConfigSub->GetString("subcribe","topic_name","");
    lpSubscribeParam->SetTopicName(topicName);
    char* isFromNow = (char*)lpConfigSub->GetString("subcribe","is_rebulid","");
    if (strcmp(isFromNow,"true")==0){lpSubscribeParam->SetFromNow(true);}else{lpSubscribeParam->SetFromNow(false);}
    char* isReplace = (char*)lpConfigSub->GetString("subcribe","is_replace","");
    if (strcmp(isReplace,"true")==0){lpSubscribeParam->SetReplace(true);}else{lpSubscribeParam->SetReplace(false);}

    //    char* lpApp = (S)"xuxinpeng";
    //lpSubscribeParam->SetAppData(lpApp,9);//添加附加数据

    //添加过滤字段
    int nCount = lpConfigSub->GetInt("subcribe","filter_count",0);
    for (int i=1;i<=nCount;i++){
      char lName[128]={0};

      sprintf(lName,"filter_name%d",i);
      char* filterName = (char*)lpConfigSub->GetString("subcribe",lName,"");
      char lValue[128]={0};
      sprintf(lValue,"filter_value%d",i);
      char* filterValue = (char*)lpConfigSub->GetString("subcribe",lValue,"");
      lpSubscribeParam->SetFilter(filterName,filterValue);
    }
    //添加发送频率
    lpSubscribeParam->SetSendInterval(lpConfigSub->GetInt("subcribe","send_interval",0));
    //添加返回字段
    nCount = lpConfigSub->GetInt("subcribe","return_count",0);
    for (int k=1;k<=nCount;k++){
      char lName[128]={0};
      sprintf(lName,"return_filed%d",k);
      char* filedName = (char*)lpConfigSub->GetString("subcribe",lName,"");
      lpSubscribeParam->SetReturnFiled(filedName);
    }

    int subscribeIndex = 0;
    //R ki(-999);

    if(XD==y->t){
      pack=NewPacker(2);
      dopack(pack,y);
    }
    int  iRet = lpSub->SubscribeTopic(lpSubscribeParam,5000,NULL,pack);
    if(iRet>0){subscribeIndex = iRet;printf("SubscribeTopic info:[%d] 成功\n",iRet);}
    else{printf("SubscribeTopic info:[%d] %s\n",iRet,lpConnectionSub->GetErrorMsg(iRet));}
    
    //free(pack->GetPackBuf());
    //R ki(-999);
    //pack->Release();

    /*    if(unpack){
      L=decodepack(unpack);
      unpack->Release();
      R L;
    }
    */
    R ki(0);
  }

  K3(t2call){ //(funcid,data|data array,mode)mode=0(sync)mode=1(async)
    IF2Packer* pack =NewPacker(2);
    I r=0;
    V* ptr=NULL;
    K L=NULL,rv=NULL;

    dopack(pack,y);
    //DBG("[t2call]mode=(%d)!",z->i);
    if ((r=lpConnection->PRI_SendBiz(xi, pack,z->i)) <=0){
      O(lpConnection->PRI_GetErrorMsg(r));
    }else{
      if(0==z->i){
	r=lpConnection->PRI_RecvBiz(r,&ptr);
	//DBG("pack recv:%d",r);
	switch (r){
	case 0:   /*业务数据OK,业务操作OK*/
	case 1:   /*业务数据OK,业务操作失败*/
	  L=decodepack((IF2UnPacker *)ptr);r=0;break;
	case 2:   /*返回非业务错误信息字符串*/
	  O((S)ptr);
	case 3:   /*业务包解包失败*/
	default:
	  O(lpConnection->PRI_GetErrorMsg(r));
	}
	rv=r?ki(r):L;
      }else{
	rv=ki(r);
      }
    }
    //DBG("unpack ok!");

    free(pack->GetPackBuf());
    pack->Release();
    R rv; 
  }

  K4(subcall){ //(funcid,data,mode,issuetype)mode=0(sync)mode=1(async)
    IF2Packer* pack =NewPacker(2);
    I r=0;
    V* ptr=NULL;
    K L=NULL,rv=NULL;
    IBizMessage* lpBizMessage=NewBizMessage();
    IBizMessage* lpBizMessageRsp=NULL;
    lpBizMessage->AddRef();
    lpBizMessage->SetFunction(xi);
    lpBizMessage->SetPacketType(0);
    lpBizMessage->SetIssueType(w->i);
    dopack(pack,y);
    lpBizMessage->SetKeyInfo(pack->GetPackBuf(),pack->GetPackLen());
    if ((r=lpConnection->SendBizMsg(lpBizMessage,z->i)) <=0){
      O(lpConnection->PRI_GetErrorMsg(r));
      rv=ki(r);
    }else{
      if(0==z->i){
	r=lpConnection->RecvBizMsg(r,&lpBizMessageRsp,1000,0);
	if(r){
	  O(lpConnection->PRI_GetErrorMsg(r));
	  rv=ki(r);
	}else{
	  int iLen=0;
	  const void * lpBuffer = lpBizMessageRsp->GetKeyInfo(iLen);
	  IF2UnPacker * lpUnPacker = NewUnPacker((void *)lpBuffer,iLen);
	  lpUnPacker->AddRef();
	  rv=decodepack(lpUnPacker);
	  lpUnPacker->Release();
	}
	pack->FreeMem(pack->GetPackBuf());
	pack->Release();
	lpBizMessage->Release();
      }else{
	rv=ki(r);
      }	
    }
    R rv;
  }

  K1(topiclist){
    IF2UnPacker *lup=NULL;
    K L=NULL;
    
    if(!lpSub) R ki(-1);
    lup=lpSub->GetTopic(true,0);
    if(!lup) R ki(-2);
    L=decodepack(lup);
    lup->Release();
    R L;
  }

  K2(hsdc_encrypt){
    int r=0;
    int n=0;
    char buf[BUFLEN];
    
    r=hundsun_encrypt((S)y->G0,y->n,buf,&n,x->s);
    
    if(0==r) R kpn((S)buf,n);

    R ki(r);
  }

  K1(hsdc_getsysteminfo){
    int r=0;
    char pszSysInfo[492];
    int iSysInfoLen;
    char pszSysInfoIntegrity[300];
    int iSysInfoIntegrityLen;
    
    r=hundsun_getsysteminfo(pszSysInfo,&iSysInfoLen,pszSysInfoIntegrity,&iSysInfoIntegrityLen);
    if(0==r) R knk(2,kpn((S)pszSysInfo,iSysInfoLen),kpn((S)pszSysInfoIntegrity,iSysInfoIntegrityLen));
    R ki(r);
  }

  K1(hsdc_getdetailerror){
    int r=0;
    
    char pszDetailInfo[492];
    int iDetailInfoLen;

    r=hundsun_getdetailerror(xs,pszDetailInfo,&iDetailInfoLen);
    if(0==r) R kpn((S)pszDetailInfo,iDetailInfoLen);
    R ki(r);    
  }

  K1(hsdc_version){
    R kp((S)hundsun_getversion());
  }

  K1(t2addr){
    if(NULL==lpConnection) R kp("");
    
    R kp((S)lpConnection->GetSelfAddress());
  }

  K1(t2mac){
    if(NULL==lpConnection) R kp("");

    R kp((S)lpConnection->GetSelfMac());    
  }

  K2(ctpsysinfo){
    char buf[SYMSIZE];
    I r=0,n=0;
    r=CTP_GetSystemInfo(buf,n);
    R r?kp(""):kpn((S)buf,n);
  }

}
