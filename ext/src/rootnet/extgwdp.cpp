#include "kcomm.h"
#include "Package.h"
using namespace GWDPApi;

Z CPackage oPkt;

extern "C"{
  K1(initgwdp){R ki(oPkt.Init());}

  K1(freegwdp){R ki(oPkt.UnInit());}

  K3(callgwdp){
    K yL=NULL,Lk=NULL,Lv=NULL,L1=NULL,L=NULL;
    I m=0,n=z->n,t=y->t,yn=y->n,i=0,j=0;
    C buf[10];

    oPkt.ClearSendPackage();
    oPkt.SetFunctionCode(xs);
    oPkt.SetFlags(0);
    if(XD==t){
      Lk=kK(y)[0];
      Lv=kK(y)[1];
      oPkt.SetValue(0,"recordCnt","1");
      DO(Lk->n,oPkt.SetValue(1,kS(Lk)[i],kS(Lv)[i]));
    }else{
      memset(buf,0,sizeof(buf));
      sprintf(buf,"%d",yn-1);
      oPkt.SetValue(0,"recordCnt",buf);
      for(j=1;j<yn;j++){
	yL=kK(y)[j];
	if(XD==yL->t){
	  Lk=kK(yL)[0];
	  Lv=kK(yL)[1];
	  DO(Lk->n,oPkt.SetValue(j,kS(Lk)[i],kS(Lv)[i]));
	}
      }
    }

    if(!oPkt.ExchangeMessage()){
      string strErrCode = oPkt.GetValue(0,"errorCode");
      string strErrMsg  = oPkt.GetValue(0,"failinfo");
      R knk(3,ki(-1),ks((S)strErrCode.c_str()),ks((S)strErrMsg.c_str()));
    }

    char chLog[200] = {0};
    string strSucc = oPkt.GetValue(0,"successflg");
    if(strSucc.compare("0")!=0){
      string strErrCode = oPkt.GetValue(0,"errorCode");
      string strErrMsg  = oPkt.GetValue(0,"failinfo");
      R knk(3,ki(-1),ks((S)strErrCode.c_str()),ks((S)strErrMsg.c_str()));
    }
	
    m=atoi(oPkt.GetValue(0,"recordCnt"));
    L=knk(0);
    L1=knk(0);
    DO(n,jk(&L1,knk(0)));
    DO(m,for(j=0;j<n;j++){string str=oPkt.GetValue(i+1,kS(z)[j]);jk(&kK(L1)[j],kp((S)str.c_str()));});
    jk(&L,xT(xD(r1(z),L1)));
    R L;
  }

}
