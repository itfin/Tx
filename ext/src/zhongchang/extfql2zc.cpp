#include "kcomm.h"
#include <queue>

#include "sipv2_i.h"
#include "sipui2_i.h"

#include "tshmarket.h"
#include "tszmarket.h"
#include "tszmatch.h"

#define CODEBUFLEN 12240000

#define PIPE_CAPACITY 65536
#define b9 
#define d9 

ZI run=0,p[2];ZC b[2*PIPE_CAPACITY];

#if defined(WIN32)||defined(WIN64)
#include <process.h>
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

//extern "C" K2(userLoginQ); 
//extern "C" K1(subscribeMarketData); 
Z int c;

ZK onmq(I i){
  K L=knk(0);
  //O("onmq:%d\n",0);

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
  k(0,"onl2zc",L,(K)0);
  R ki(0);
}

Z V mpub(K x){

  LOCK;
  mq.push(b9(1,x));

  /*
    while (!fq.empty()){
    r0(fq.front());
    fq.pop();
    }
  */
  //k(-c,"onl2hr",x,(K)0);
  UNLOCK;    
  write(p[1],&b,1);
};

UIHANDLE hSip=0;

static const char* GetErrDes(T_I32 icode) {
    static const char* pnull = "NULL";
    static const struct MSGCODE {
        T_I32		icode;	///< 错误码
        const char* sdes;	///< 错误描述
    }errcode[] =
    {
        //公用
        { SIPE_OK, "OK" },
        { SIPE_ERR, "ERROR" },
        { SIPE_ERRHANDLE, "INVALID_SIPHANDLE" },

        //TCP通讯层
        { SIPE_TCPCONNECTERR, "SIPE_TCPCONNECTERR" },
        { SIPE_PROXY_CONNECTERR, "SIPE_PROXY_CONNECTERR" },
        { SIPE_PROXY_AUTHERR, "SIPE_PROXY_AUTHERR" },
        { SIPE_DISCONNECT, "SIPE_DISCONNECT" },
        { SIPE_TCPIOERR, "SIPE_TCPIOERR" },

        //TCP消息层
        { SIPE_TCPMSGERR, "SIPE_TCPMSGERR" },
        { SIPE_TIMEOUT, "SIPE_TIMEOUT" },

        //消息传输层错误
        { SIPE_PKGFMT, "SIPE_PKGFMT" },

        //协议层
        { SIPE_PKGCODE, "SIPE_PKGCODE" },
        { SIPE_PKGDATA, "SIPE_PKGDATA" },
        { SIPE_ASYNCONNECTOK, "SIPE_ASYNCONNECTOK" },
        { SIPE_ASYNCONNECTERR, "SIPE_ASYNCONNECTERR" },

        //应用层
        { SIPE_VERSION, "SIPE_VERSION" },
        { SIPE_NOUSER, "SIPE_NOUSER" },
        { SIPE_USERAUTH, "SIPE_USERAUTH" },
        { SIPE_NOPOWER, "SIPE_NOPOWER" },
        { SIPE_NOTAG, "SIPE_NOTAG" },
        { SIPE_NODATA, "SIPE_NODATA" },
        { SIPE_MSGTYPE, "SIPE_MSGTYPE" },
        { SIPE_MSGSIZE, "SIPE_MSGSIZE" },

        { SIPE_DATALINE, "SIPE_DATALINE" },
        { SIPE_DSLCONFULL, "SIPE_DSLCONFULL" },

        { SIPE_TAGMSGSEQNO, "SIPE_TAGMSGSEQNO" },

        { SIPE_IPERR, "SIPE_IPERR" },
        { SIPE_MACERR, "SIPE_MACERR" },

        { SIPE_CONNECTFULL, "SIPE_CONNECTFULL" },
        { SIPE_SSCFULL, "SIPE_SSCFULL" },
        { SIPE_USERLOCKED,"SIPE_USERLOCKED" },
        { SIPE_USEREXDATE ,"SIPE_USEREXDATE" },

        { SIPE_ERRARGS, "SIPE_ERRARGS" },
        { SIPE_DSLMAINEXIST, "SISIPE_DSLMAINEXIST" },
        { SIPE_SVRMEMERR, "SIPE_SVRMEMERR" },

        // { SIPE_USEREXDATE ,"SIPE_USEREXDATE"},

        { SIPE_SVREXIST, "SIPE_SVREXIST" },

        { SIPE_TDAUSERERR, "SIPE_TDAUSERERR" },
        { SIPE_TAGNOTSUBSCRIPT, "SIPE_TAGNOTSUBSCRIPT" },
        { SIPE_TDAUSERFULL, "SIPE_TDAUSERFULL" },
        { SIPE_TDANOUSERID, "SIPE_TDANOUSERID" },
        { SIPE_SYSTAG, "SIPE_SYSTAG" },
        { SIPE_NOSVR, "SIPE_NOSVR" },
        { SIPE_CTRLCODE, "SIPE_CTRLCODE" },
        { SIPE_CTRLOPTFULL, "SIPE_CTRLOPTFULL" },
        { SIPE_COOKIE, "SIPE_COOKIE" }
    };
    T_U32 i, un = sizeof(errcode) / sizeof(MSGCODE);
    for (i = 0; i < un; i++)
        if (errcode[i].icode == icode)
            return errcode[i].sdes;
    return pnull;
}

K DoMsg(S code,J seq,I t,I len,S data){
  K v=knk(0);
   switch(t){
  case 1004:
    {
      PSH_StockMarketDataL2 p=(PSH_StockMarketDataL2)data;
      K pa=ktn(KJ,10),qa=ktn(KJ,10),pb=ktn(KJ,10),qb=ktn(KJ,10);
      DO(10,kJ(pa)[i]=p->uAskPrice[i];kJ(qa)[i]=p->uAskVol[i];kJ(pb)[i]=p->uBidPrice[i];kJ(qb)[i]=p->uBidVol[i];)
	v=knk(2,kp("StockMarketDataL2"),knk(31,kp(code),kj(seq),kj(p->nActionDay),kj(p->nTime),kj(p->nStatus),kj(p->uPreClose),kj(p->uOpen),kj(p->uHigh),kj(p->uLow),kj(p->uMatch),pa,qa,pb,qb,kj(p->uNumTrades),kj(p->iVolume),kj(p->iTurnover),kj(p->iTotalBidVol),kj(p->iTotalAskVol),kj(p->uWeightedAvgBidPrice),kj(p->uWeightedAvgAskPrice),kj(p->nIOPV),kj(p->nYieldToMaturity),kj(p->uHighLimited),kj(p->uLowLimited),kpn(p->sPrefix,4),kj(p->nSyl1),kj(p->nSyl2),kj(p->nSD2),kpn(p->sTradingPhraseCode,8),kj(p->nPreIOPV)));
    }
  case 2004:    
    {
      PSZ_StockMarketDataL2 p=(PSZ_StockMarketDataL2)data;
      K pa=ktn(KJ,10),qa=ktn(KJ,10),pb=ktn(KJ,10),qb=ktn(KJ,10);
      DO(10,kJ(pa)[i]=p->uAskPrice[i];kJ(qa)[i]=p->uAskVol[i];kJ(pb)[i]=p->uBidPrice[i];kJ(qb)[i]=p->uBidVol[i];)
	v=knk(2,kp("StockMarketDataL2"),knk(31,kp(code),kj(seq),kj(p->nActionDay),kj(p->nTime),kj(p->nStatus),kj(p->uPreClose),kj(p->uOpen),kj(p->uHigh),kj(p->uLow),kj(p->uMatch),pa,qa,pb,qb,kj(p->uNumTrades),kj(p->iVolume),kj(p->iTurnover),kj(p->iTotalBidVol),kj(p->iTotalAskVol),kj(p->uWeightedAvgBidPrice),kj(p->uWeightedAvgAskPrice),kj(p->nIOPV),kj(p->nYieldToMaturity),kj(p->uHighLimited),kj(p->uLowLimited),kpn(p->sPrefix,4),kj(p->nSyl1),kj(p->nSyl2),kj(p->nSD2),kpn(p->sTradingPhraseCode,8),kj(p->nPreIOPV)));      
    }
    break;
  case 1009:
    {
      PSH_StockStepData p=(PSH_StockStepData)data;
      v=knk(2,kp("StockStepDataSH"),knk(13,kp(code),kj(seq),kj(p->nActionDay),kj(p->iBizIndex),kj(p->nChannel),kj(p->nTickTime),kc(p->cType),kj(p->iBuyOrderNo),kj(p->iSellOrderNo),kj(p->nPrice),kj(p->iQty),kj(p->iTradeMoney),kpn(p->sTickBSflag,8)));      
    }
    break;
  case 2009:
    {
      PSZ_StockStepData p=(PSZ_StockStepData)data;
      if(1==p->type){
	PSZ_StockStepTrade p1=(PSZ_StockStepTrade)&p->data;
	v=knk(2,kp("StockStepTradeSZ"),knk(14,kp(code),kj(seq),kj(p1->nActionDay),kj(p1->usChannelNo),kj(p1->i64ApplSeqNum),kpn(p1->sMDStreamID,3),kj(p1->i64BidApplSeqNum),kj(p1->i64OfferApplSeqNum),kpn(p1->sSecurityID,8),kpn(p1->sSecurityIDSource,4),kj(p1->i64LastPx),kj(p1->i64LastQty),kc(p1->cExecType),kj(p1->i64TransactTime)));
      }else{
	PSZ_StockStepOrder p2=(PSZ_StockStepOrder)&p->data;
	v=knk(2,kp("StockStepOrderSZ"),knk(13,kp(code),kj(seq),kj(p2->nActionDay),kj(p2->usChannelNo),kj(p2->i64ApplSeqNum),kpn(p2->sMDStreamID,3),kpn(p2->sSecurityID,8),kpn(p2->sSecurityIDSource,4),kj(p2->i64Price),kj(p2->i64OrderQty),kc(p2->cSide),kj(p2->i64TransactTime),kc(p2->sExtendFields[0])));
      }
    }
    break;
  default:
    v=knk(2,kp("UnknownMsg"),knk(4,kp(code),kj(seq),kj(t),kj(len)));
    break;
  }
  
  O("code=%s,seq=%d,type=%d,len=%d,data=%d\n",code,seq,t,len,(J)data);
  R v;
}

ZV RecvData(TPKG_SIP* pPkg, CBPARAM pParam){
  K L=knk(0);
  T_U16 t,n;
  G *p;
  TPKG_SIP_TAGERR *ep;
  TPKG_SIP_TAGMSGS *dp;
  TPKG_SIP_SST *sp;
  T_U32 m;
  if(!pPkg)R;
  t=pPkg->PkgCode;
  n=pPkg->PkgSize;
  p=pPkg->PkgData;
  O("[RecvData]t=%d,n=%d,p=%d\n",t,n,p);
  switch(t){
  case CPKG_LOCAL_ERR:// 本地错误(1)
  case CPKG_PKGERR:// 应用层报错(2)
    {
      sp=(TPKG_SIP_SST*)pPkg;
      mpub(knk(2,kp((S)((t==CPKG_LOCAL_ERR)?"CPKG_LOCAL_ERR":"CPKG_PKGERR")),knk(3,kj(sp->ErrCode),kp((S)sp->Des),kp((S)GetErrDes(sp->ErrCode)))));
      O("[CPKGERR]ec=%d,es=%s\n",sp->ErrCode,sp->Des);
    }
    break;
  case CPKG_SVRPUTMSG: /*tag data(10014)*/
    {
      T_SIPTAGMSG *mp;
      T_U16 ml=0;
      K mv;
      dp=(TPKG_SIP_TAGMSGS *)pPkg;
      m=dp->MsgNum;
      mp=(T_SIPTAGMSG *)dp->Bytes;
      O("[CPKG_SVRPUTMSG]m=%d,mc=%s,ms=%d,ml=%d,mp=%d,mt=%d\n",m,mp->Code,mp->SeqNum,mp->MsgDataSize,mp->MsgType);
      DO(m,ml=(I)mp->MsgDataSize;mv=DoMsg((S)mp->Code,mp->SeqNum,(I)mp->MsgType,ml,(S)mp->MsgData);if(0<mv->n)jk(&L,mv);mp=(T_SIPTAGMSG *)((char*)mp+40+ml));	
      mpub(knk(2,kp("CPKG_SVRPUTMSG"),L));	
    }
    break;
       
  case CPKG_SSCTAGERRNOTIFY: /*tag error(10012)*/
    {
      SIP_TAGERR *te;
      ep=(TPKG_SIP_TAGERR *)pPkg;
      m=ep->TagNum;
      te=ep->TagErr;
      DO(m,jk(&L,knk(3,kp(te->TagCode),kj(te->Errcode),kp((S)GetErrDes(te->Errcode))));te++);
      mpub(knk(2,kp("CPKG_SSCTAGERRNOTIFY"),L));	
    }
    break;
  default:
    break;
  }
  
}

extern "C"{
  K2(sipconn){
    K k0,k1,kv;
    S key;
    I n=0,i=0,f=0,r=0;
    char buf[1024];

      
    if(run) R ki(-10001);

    if(pipe(p)) R ki(-10009);

#if defined(WIN32)||defined(WIN64)
#else
    if(-1==(f = fcntl(p[0],F_GETFL,0)))R ki(-10002);
    f |= O_NONBLOCK;
    if (fcntl(p[0],F_SETFL,f)==-1) R ki(-10003);
#endif

    run++;
    INITLOCK;
    sd1(p[0],onmq);

    if(0>=(hSip=UI_Open(RecvData,NULL))) R ki(-1);
    if(0!=UI_Connect(hSip,kK(x)[0]->s, kK(x)[1]->h,(const S)kK(x)[2]->s,(const S)kK(x)[3]->s,kK(y)[0]->i,kK(y)[1]->g))R ki(-2);
 
    R ki(run);
  }

  K1(sipdisc){
    if(!run) R ki(-1);
    UI_Disconnect(hSip);
    UI_Close(hSip);
    run--;
    R ki(run);    
  }
  
  K1(siprun){
    R ki(run);
  }

  K1(sipisconn){
    R kb(UI_IsConnect(hSip));
  }

  K1(sipsub){
    if(!run) R ki(-1);
    T_SSCTAG tag[10000];
    int n=(10000<xn)?10000:xn;
    DO(n,strncpy(tag[i].sTag,kS(x)[i],24));
    DO(n,tag[i].cMode=SSC_MODE_INC;tag[i].uSeqNo=-1;);
    R ki(UI_SubscribeTags(hSip,tag,n));
    R ki(0);
  }

  K1(sipunsub){
    if(!run) R ki(-1);
    T_SSCTAG tag[10000];
    int n=(10000<xn)?10000:xn;
    DO(n,strncpy(tag[i].sTag,kS(x)[i],24));
    R ki(UI_UnSubscribeTags(hSip,tag,n));
  }

  K1(sipunsuball){
    if(!run) R ki(-1);

    R ki(UI_UnSubscribeAll(hSip));
  }
  
  K1(sipsnapshot){
    if(!run) R ki(-1);

    R ki(0);
  }

  K1(siphistory){
    if(!run) R ki(-1);

    R ki(0);
  }

  K1(sipgetcode){
    if(!run) R ki(-1);
    I r;
    char buf[CODEBUFLEN];
    unsigned int l=CODEBUFLEN;
    memset(buf,0,l);
    r=UI_GetCode(hSip,NULL,NULL,&buf[0],&l);
    O("r=%d,l=%d\n",r,l);
    if(SIPE_OK==r){
      R kp(buf);
    }else{
      R ki(r);
    }  
    R ki(0);
  }
}
