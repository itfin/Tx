#include"kcomm.h"

int closesock(int s){
  int r=0;
#if defined(WIN32)||defined(WIN64)
   r=closesocket(s);
#else
   r=close(s);
#endif
   R r;
}

K1(udpsend){
   int n=0;
   struct sockaddr_in si_other;
   int s, i, slen=sizeof(si_other);
   char buf[BUFLEN];
   if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)R ki(-2);
   memset((char *) &si_other, 0, slen);
   si_other.sin_family = AF_INET;
   si_other.sin_port = htons(kK(x)[1]->h);
   kstrncpy((char *)&buf,kK(x)[0],BUFLEN);
#if defined(WIN32)||defined(WIN64)
   if(-1==(si_other.sin_addr.s_addr = inet_addr(buf)))R ki(-3);
#else
   if(inet_aton(buf, &si_other.sin_addr)==0) R ki(-3);
#endif
   n=sendto(s,kC(xz), xz->n, 0, (struct sockaddr*)&si_other, slen);
   closesock(s);
   R ki(n);
}

K1(sockopt){
  int s=x->i,r,i=0,n=0,l=sizeof(n),N=18;
  K L1=ktn(KS,N),L2=ktn(KI,N);
  struct linger lg;
  struct timeval  tv;
  r=getsockopt(s,IPPROTO_TCP,TCP_NODELAY,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("TCP_NODELAY");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;

#if defined(WIN32)||defined(WIN64)
#else
  r=getsockopt(s,IPPROTO_TCP,TCP_MAXSEG,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("TCP_MAXSEG");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_TCP,TCP_KEEPIDLE,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("TCP_KEEPIDLE");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_TCP,TCP_KEEPCNT,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("TCP_KEEPCNT");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_TCP,TCP_KEEPINTVL,(void*)&n,(int *)&l);
#endif
  r=getsockopt(s,SOL_SOCKET,SO_REUSEADDR,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_REUSEADDR");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_KEEPALIVE,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_KEEPALIVE");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  kS(L1)[i] = ss("TCP_KEEPINTVL");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_TYPE,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_TYPE");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_BROADCAST,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_BROADCAST");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_RCVBUF,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_RCVBUF");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_SNDBUF,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_SNDBUF");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_RCVLOWAT,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_RCVLOWAT");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_SNDLOWAT,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_SNDLOWAT");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_ERROR,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_ERROR");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  r=getsockopt(s,SOL_SOCKET,SO_OOBINLINE,(void*)&n,(int *)&l);
  kS(L1)[i] = ss("SO_OOBINLINE");kI(L2)[i]=(r<0)?ERRNO:n;n=0;i++;
  l=sizeof(lg);r=getsockopt(s,SOL_SOCKET,SO_LINGER,(void*)&lg,(int *)&l);
  kS(L1)[i] = ss("SO_LINGER");kI(L2)[i]=(r<0)?ERRNO:(lg.l_onoff>0)?lg.l_linger:lg.l_onoff;n=0;i++;
  l=sizeof(tv);r=getsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(void*)&tv,(int *)&l);
  kS(L1)[i] = ss("SO_RCVTIMEO");kI(L2)[i]=(r<0)?ERRNO:((1000*tv.tv_sec)+tv.tv_usec/1000);n=0;i++;
  l=sizeof(tv);r=getsockopt(s,SOL_SOCKET,SO_SNDTIMEO,(void*)&tv,(int *)&l);
  kS(L1)[i] = ss("SO_SNDTIMEO");kI(L2)[i]=(r<0)?ERRNO:((1000*tv.tv_sec)+tv.tv_usec/1000);n=0;i++;

  R xD(L1,L2);
}

K1 (getsockbuf){
  int s=x->i,r1=0,r2=0,n1=0,n2=0,s1=sizeof(n1),s2=sizeof(n2);
  printf("s=%d\n",s);
  r1=getsockopt(s,SOL_SOCKET,SO_RCVBUF,(void*)&n1,(int *)&s1);
  r2=getsockopt(s,SOL_SOCKET,SO_SNDBUF,(void*)&n2,(int *)&s2);
  return knk(7,ki(n1),ki(n2),ki(s1),ki(s2),ki(r1),ki(r2),ki(ERRNO));
}

K1 (setsockbuf){
  int s=0,n=16777216,r1=0,r2=0;
  printf("n=%d,t=%d\n",x->n,x->t);
  if(0>x->t){
    s=x->i;
  }else{
    s=kI(x)[0];n=kI(x)[1];
  }
  printf("s=%d,n=%d\n",s,n);
  r1=setsockopt(s,SOL_SOCKET,SO_RCVBUF,(const char*)&n,sizeof(int));
  r2=setsockopt(s,SOL_SOCKET,SO_SNDBUF,(const char*)&n,sizeof(int));
  return knk(3,ki(r1),ki(r2),ki(ERRNO));
}

K sockcallback(I s){
  struct timeval tv={0,0};
  fd_set RS,WS,ES;
  struct sockaddr_in sin;
  int r=0,slen=sizeof(sin);  
  char buf[BUFF128K];
  char addr[SYMSIZE];
  memset(buf,0,sizeof(buf));
  memset(addr,0,sizeof(addr));

  FD_ZERO(&RS);FD_SET(s,&RS);
  FD_ZERO(&WS);FD_SET(s,&WS);
  r=select(s+1,&RS,&WS,NULL,&tv);
  if(r==0){
    R ki(0);
  }
  if(r<0){
    r=-ERRNO;
    r0(k(0,"sockcberr",ki(s),ki(r),(K)0));
    R ki(r);
  }

  if(FD_ISSET(s,&WS)){
    r0(k(0,"sockcbsend",ki(s),(K)0));
  }
   
  if(FD_ISSET(s,&RS)){
#if defined(WIN32)||defined(WIN64)
    r=recvfrom(s, buf, sizeof(buf),0, (struct sockaddr *)&sin, &slen);
#else
    r=recvfrom(s, buf, sizeof(buf),MSG_DONTWAIT,(struct sockaddr *)&sin, &slen);
#endif
    if(slen)strncpy(addr,inet_ntoa(sin.sin_addr),sizeof(addr));
    if(r<0)r=-ERRNO;
    r0(k(0,"sockcbrecv",ki(s),kp(addr),ki(slen?ntohs(sin.sin_port):0),ki(r),((r>0)?kpn(buf,r):kp("")),(K)0));
    if(0==r) {sd0(s);closesock(s);} 
    }
  R ki(r);
}

K listencallback(I s){
   struct sockaddr_in sin;
   int r,slen=sizeof(sin);
   char buf[BUFLEN];
   r=accept(s,(struct sockaddr *)&sin, &slen);
   if(0<r){
     strncpy(buf,inet_ntoa(sin.sin_addr),sizeof(buf));
     r0(k(0,"listencb",ki(s),ki(r),kp(buf),ki(ntohs(sin.sin_port)),(K)0));
      sd1(-r,sockcallback);
   }
   R ki(r);
}

K1(sockcheck){
  int s=x->i;
  R sockcallback(s); 
}
 
K2(tcpsend){
  int s=x->i,r=0,n=y->n,e=0;
  r=send(s,kC(y),n,0);
  if(r>0){
    R ki(r);
  }else{
    e=ERRNO;
    //sprintf(buf,"r=%d,errno=%d",r,e);perror(buf);
    R ki(-e);
  }
}

K1(tcprecv){
  char buf[BUFLEN];
  int s=x->i,r=0,e=0;
  if(s<=0) R ki(-1);
  r=recv(s,buf,sizeof(buf),0);
  if(r>0){
    R kpn(buf,r);
  }else if(r=0){
    closesock(s);R ki(0);
  }else{
    e=ERRNO;
    //sprintf(buf,"r=%d,errno=%d",r,e);perror(buf);
    R ki(-e);
  }
}

I opensock(S ip,I port,I mode,I blen){
  int n=0,e=0,flag=1,keepidle=60,keepintvl=30,keepcnt=3;
  struct sockaddr_in si_other;
  int s, flags, slen=sizeof(si_other),r;
  int sockmode=mode; /*0:UDP,1:TCP client async,2:TCP server async,3:TCP client sync,4:TCP server sync*/
#if defined(WIN32)||defined(WIN64)
  u_long iMode = 1;
#endif
  if ((s=socket(AF_INET,((0==sockmode)?SOCK_DGRAM:SOCK_STREAM),(0==sockmode)?IPPROTO_UDP:IPPROTO_TCP))==-1) R -ERRNO;

  if(sockmode){
    setsockopt(s,IPPROTO_TCP,TCP_NODELAY,(char*)&flag,sizeof(flag));
    setsockopt(s,SOL_SOCKET,SO_KEEPALIVE,(char*)&flag,sizeof(flag));
  }

  if(0<blen){ /*Linux 2.6 have autotuning,but big buffer helps for non-blocking IO.*/
    setsockopt(s,SOL_SOCKET,SO_RCVBUF,(char*)&blen,sizeof(blen));
    setsockopt(s,SOL_SOCKET,SO_SNDBUF,(char*)&blen,sizeof(blen));
  }

#if defined(WIN32)||defined(WIN64)
  if(mode<3) ioctlsocket(s, FIONBIO, &iMode);
#else
  flags = fcntl(s, F_GETFL);
  if(mode<3)flags |= O_NONBLOCK;
  fcntl(s, F_SETFL, flags);
#endif

  memset((char *) &si_other, 0, slen);
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(port);
  if(0==strcmp(ip,"")){
    si_other.sin_addr.s_addr=htonl(INADDR_ANY);
  }else{
#if defined(WIN32)||defined(WIN64)
    if(-1==(si_other.sin_addr.s_addr = inet_addr(ip)))R (-ERRNO);
#else
      if(inet_aton(ip, &si_other.sin_addr)==0) R (-ERRNO);
#endif
  }
  if((1==sockmode)||(3==sockmode)){
    r=connect(s,(struct sockaddr *)&si_other,slen);
#if defined(WIN32)||defined(WIN64)
    if ((0>r)&&WSAEWOULDBLOCK!=(e=ERRNO)) R (-e);
#else
    if ((0>r)&&EINPROGRESS!=ERRNO) R (-ERRNO);
#endif
  }else{
    if(0>setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(char *)&flag,sizeof(flag)))R (-ERRNO);
    if(0>bind(s, (struct sockaddr *)&si_other, slen)) R (-ERRNO);
    if(0<sockmode){
      if(0>listen(s,100))R (-ERRNO);
    }
  }
  R s;
}

K1(sockopen){
  int s=0,t=0,n=16777216;
  t=xz->i;
  if(!((-KS)==xx->t)&&((-KI)==xy->t)&&((-KI)==xz->t))R ki(-1234);
  if(4==x->n){n=xw->i;};
  s=opensock(xx->s,xy->i,xz->i,n);
  if(0<s){
    if(2==t){
      sd1(-s,listencallback);
    }else if(2>t){
      sd1(-s,sockcallback);
    }
  }
  R ki(s);
}

K1(sockclose){
  int s=x->i;
  sd0(s);
  R ki(closesock(s));
}

K1(errmsg){
  R ks(strerror(xi));
}
 
