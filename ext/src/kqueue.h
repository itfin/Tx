#pragma once
#define _USE_LOCKFREE_QUEUE 1

#if defined(_USE_LOCKFREE_QUEUE)
#include "concurrentqueue.h"
#else
#include <queue>
#endif

#include "kcomm.h"

#define PIPE_CAPACITY 65536
#define QUEUE_SIZE 65536
#define b9
#define d9

ZK onmq(I i);

ZI p[2];ZC b[2*PIPE_CAPACITY];

#if defined(WIN32)||defined(WIN64)
#include <process.h>
ZI pipe(I*p){R !CreatePipe((PHANDLE)p+0,(PHANDLE)p+1,0,0);}
ZI dwBytes;
#define read(x,y,z) ReadFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL) 
#define write(x,y,z) WriteFile((HANDLE)x,y,z,(LPDWORD)&dwBytes,NULL); 
#define close(x) CloseHandle((HANDLE)x)
#if defined(_USE_LOCKFREE_QUEUE)
#define INITLOCK 
#define FREELOCK 
#else
Z CRITICAL_SECTION g_CS;
#define INITLOCK InitializeCriticalSection(&g_CS)
#define FREELOCK DeleteCriticalSection(&g_CS)
#define LOCK EnterCriticalSection(&g_CS)
#define UNLOCK LeaveCriticalSection(&g_CS)
#endif
#else
#if defined(_USE_LOCKFREE_QUEUE)
#else
Z pthread_mutex_t g_mutex=PTHREAD_MUTEX_INITIALIZER;
#define LOCK pthread_mutex_lock(&g_mutex)
#define UNLOCK pthread_mutex_unlock(&g_mutex)
#endif
#define INITLOCK 
#define FREELOCK 
#endif

#if defined(_USE_LOCKFREE_QUEUE)
Z moodycamel::ConcurrentQueue<K> mq(QUEUE_SIZE);
Z moodycamel::ProducerToken ptok(mq);
Z moodycamel::ConsumerToken ctok(mq);
#define ONMQ(kcb) ZK onmq(I i){K L=knk(0);read(i,&b,PIPE_CAPACITY);K x; while (mq.try_dequeue(ctok,x)){jk(&L,x);}k(0,kcb,L,(K)0);R ki(0);} ////ZK onmq(I i){K L=knk(0);read(i,&b,PIPE_CAPACITY);K x; while (mq.try_dequeue(ctok,x)){jk(&L,x);}k(0,"onkmq",L,(K)0);R ki(0);}
Z V mpub(K x){mq.enqueue(ptok,x);write(p[1],&b,1);};
#else
Z std::queue<K> mq;
Z std::queue<K> fq;
#define ONMQ(kcb) ZK onmq(I i){ K L=knk(0);read(i,&b,PIPE_CAPACITY);LOCK;while (!mq.empty()){jk(&L,d9(mq.front()));mq.pop();}UNLOCK;k(0,kcb,L,(K)0);R ki(0);}
Z V mpub(K x){LOCK;mq.push(b9(1,x));UNLOCK;write(p[1],&b,1);};
#endif

ZI kqinit(){
  I f=0;
  if(pipe(p)) R -10009;

#if defined(WIN32)||defined(WIN64)
#else
  if(-1==(f = fcntl(p[0],F_GETFL,0)))R -10002;
  f |= O_NONBLOCK;
  if (fcntl(p[0],F_SETFL,f)==-1) R -10003;
#endif
  INITLOCK;
  sd1(p[0],onmq);

  R 0;    
}

ZV kqfree(){
    sd0(p[0]);
    close(p[0]);close(p[1]);
    FREELOCK;
}
