#include <EXTERN.h>
#include <perl.h>

#include "kcomm.h"

static PerlInterpreter *my_perl=NULL;

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

EXTERN_C void xs_init(pTHX){
  static const char file[] = __FILE__;
  dXSUB_SYS;
  PERL_UNUSED_CONTEXT;
  
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}

void q2p(K,SV*);

K1(perlinit){
 int argc=3; 
 char *argv[] = { "", "-e", "0" };
 char **env=NULL;

 PERL_SYS_INIT3(&argc,&argv,&env);
 my_perl = perl_alloc();
 perl_construct( my_perl );
 PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
 perl_parse(my_perl,xs_init,argc,argv,(char **)NULL);
 perl_run(my_perl);
 R ki(0);
}

K1(perlfree){
  if(NULL==my_perl){krr("PerlInterpreter not init.");R (K)0;}
  perl_destruct(my_perl);
  perl_free(my_perl);
  PERL_SYS_TERM();
  my_perl=NULL;
  R ki(0);
} 

K p2q(SV* v){
  STRLEN len=0;
  S str=NULL;
  SV *v1=NULL,*v2=NULL;
  AV *av=NULL;
  HV *hv=NULL;
  svtype st=SVt_NULL;
  K k1,k2;
  I32 i=0,sl=0,m=0,t=0;

  if(SvIOK(v)){
    R ki(SvIV(v));
  }else if(SvNOK(v)){
    R kf(SvNV(v));
  }else if(SvPOK(v)){
    str=SvPV(v,len);
    R kpn(str,len);
  }else if(SvROK(v)){
    v1=SvRV(v);
    st=SvTYPE(v1);
    if(st==SVt_PVAV){ /*ARRAY ref*/
      av=(AV*)v1;
      k1=knk(0);
      sl=av_len(av)+1;
      m=1;
      for(i=0;i<sl;i++){
	k2=p2q(*av_fetch(av,i,0));
	if(k2==(K)0) R k2;
	jk(&k1,k2);
	if(0==i){t=k2->t;m=0;}else if(t!=k2->t){m=1;}else{}
      }
      if((!m)&&(t<0)){
	k2=ktn(-t,0);
	for(i=0;i<sl;i++)ja(&k2,&(kK(k1)[i]->k));
	R k2;
      }else{}
      R k1;
    }else if(st==SVt_PVHV){ /*HASH ref*/
      hv=(HV*)v1;
      k1=ktn(KS,0);
      k2=knk(0);
      hv_iterinit(hv);
      while(v2=hv_iternextsv(hv,&str,&sl)){
	js(&k1,str);
	jk(&k2,p2q(v2));
      }
      R xD(k1,k2);
    }else R p2q(v1);
  }else{}

  R knk(0);
}

K2(perleval){
  C buf[LONGBUFLEN];
  if(NULL==my_perl){krr("PerlInterpreter not init.");R (K)0;}
  kstrncpy(buf,x,sizeof(buf));
  R p2q(perl_eval_pv(buf,y->i));
}

K1(perlload){
  C buf[LONGBUFLEN];
  SV *name=NULL;
  if(NULL==my_perl){krr("PerlInterpreter not init.");R (K)0;}
  kstrncpy(buf,x,sizeof(buf));
  q2p(x,name);
  load_module(0,name,(SV*)NULL,(SV*)NULL);
  R (K)0;  
}


void qi2p(K x,I i,SV* v){
  int qt=xt;

  if((KB==qt)||(KG==qt)||(KC==qt)){
    sv_setiv(v,xG[i]);    
  }else if(KH==qt){
    sv_setiv(v,xH[i]);    
  }else if(KI==qt){
    sv_setiv(v,xI[i]);    
  }else if(KJ==qt){
    sv_setiv(v,xJ[i]);    
  }else if(KE==qt){
    sv_setnv(v,xE[i]);    
  }else if(KF==qt){
    sv_setnv(v,xF[i]);    
  }else if(KS==qt){
    sv_setpv(v,xS[i]);    
  }else if(0==qt){
    q2p(xK[i],v);
  }else{}
}

void q2p(K x,SV* v){
  int qt=xt,qn=xn,i;
  AV *av=NULL;
  HV *hv=NULL;
  SV *sv=NULL,*sv1=NULL;
  K Lk=NULL,Lv=NULL;

  if(((-KB)==qt)||((-KG)==qt)||((-KC)==qt)){
    sv_setiv(v,xg);    
  }else if((-KH)==qt){
    sv_setiv(v,xh);    
  }else if((-KI)==qt){
    sv_setiv(v,xi);    
  }else if((-KJ)==qt){
    sv_setiv(v,xj);    
  }else if((-KE)==qt){
    sv_setnv(v,xe);    
  }else if((-KF)==qt){
    sv_setnv(v,xf);    
  }else if((-KS)==qt){
    sv_setpv(v,xs);    
  }else if((KG==qt)||(KC==qt)){
    sv_setpvn(v,xG,qn);
  }else if(KB==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSViv(xG[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KH==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSViv(xH[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KI==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSViv(xI[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KJ==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSViv(xJ[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KE==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSVnv(xE[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KF==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSVnv(xF[i]));
    sv_setsv(v,newRV((SV*)av));
  }else if(KS==qt){
    av=newAV();
    for(i=0;i<qn;i++)av_push(av,newSVpv(xS[i],0));
    sv_setsv(v,newRV((SV*)av));
  }else if(99==qt){ /*Dict*/
    hv=newHV();
    Lk=xK[0];Lv=xK[1];
    for(i=0;i<Lk->n;i++){
      sv=newSV(0);sv1=newSV(0);
      qi2p(Lk,i,sv);
      qi2p(Lv,i,sv1);
      hv_store_ent(hv,sv,sv1,0);
    }
    sv_setsv(v,newRV((SV*)hv));
  }else if(0==qt){  /*List*/
    av=newAV();
    for(i=0;i<qn;i++){
      sv=newSV(0);
      q2p(xK[i],sv);
      av_push(av,sv);
    }
    sv_setsv(v,newRV((SV*)av));
  }else{}
}

K2(perlset){
  SV *v=NULL;

  if(NULL==my_perl){krr("PerlInterpreter not init.");R (K)0;}
  v=get_sv(xs, GV_ADD);
  q2p(y,v);
  R ki(0);
}
