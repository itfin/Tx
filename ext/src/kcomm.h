#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>

#if defined(WIN32)||defined(WIN64) 
#include <winsock2.h>
#include<windows.h>
#include<math.h>
extern int errno;
#define ERRNO (errno=WSAGetLastError())
#else
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)>(b))?(b):(a))
#define ERRNO errno
#endif

#include"k.h"

#define SHORTBUFLEN 16384
#define BUFLEN 65536
#define LONGBUFLEN 262144
#define BUFFSIZE 65536
#define SYMSIZE  1024

#define BUFF128K 131072
#define BUFF256K 262144
#define BUFF512K 524288
#define BUFF1M 1048576
#define BUFF2M 2097152
#define BUFF4M 4194304
#define BUFF8M 8388608
#define BUFF16M 16777216

#define K3(f) K f(K x,K y,K z)
#define K4(f) K f(K x,K y,K z,K w)
#define K5(f) K f(K x,K y,K z,K w,K u)
#define K6(f) K f(K x,K y,K z,K w,K u,K v)
#define xz xK[2]
#define xw xK[3]

#if defined(_DEBUG)
#define DBG O
#else
#define DBG(fmt,...) 
#endif


int kstrncpy(char*buf,K x,int n){
  int size=MIN(n-1,xn);
  memcpy(buf,kG(x),size);
  *(buf+size)=0;
  return size;
}
