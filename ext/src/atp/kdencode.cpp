#include "kcomm.h"
#include "KDEncodeCli.h"

extern "C"{
  K2(encodepass){
  unsigned char dst[4096];
  memset(dst,0,sizeof(dst));
  int r=KDEncode(KDCOMPLEX_ENCODE,(unsigned char *)y->s,strlen(y->s),dst,sizeof(dst),(unsigned char *)xs,strlen(xs));
  R kp((S)dst);  
  }
}
