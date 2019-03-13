#include "kcomm.h"
#include "uthash.h"

#if !(defined(WIN32)||defined(WIN64))
typedef unsigned char BYTE;
typedef  int __int32;
typedef  long long __int64;
typedef  unsigned int __uint32;
typedef  unsigned long long __uint64;
#else
typedef  unsigned int __uint32;
typedef  unsigned __int64 __uint64;
#endif

V  checksum(char*buf,int bufLen,char*crc){
  long idx;
  unsigned int cks;
  for( idx = 0L, cks = 0; idx < bufLen; cks += (unsigned int)buf[ idx++ ] );
  sprintf(crc,"%03d", (unsigned int)( cks % 256 ) );
  crc[3]=0;
}

K1(fixcrc){
  char tmpBuf[ 4 ];
  checksum(kC(x),x->n,tmpBuf);
  return(ks(tmpBuf));
}

#define MAXTAGLEN 64
#define PMAPSIZE 8
#define MAXFIELD 128
#define MAXBUFLEN 16384
#define MAXMSGTYPE 64
#define MAXFIXFIELDCNT 1024

#define FIX_DICT_INIT_ERROR -4000
#define FIX_DICT_FREE_ERROR -4001

#define FAST_DICT_INIT_ERROR -8000
#define FAST_DICT_FREE_ERROR -8001

#define FAST_DECODE_DICT_ERROR -9000
#define FAST_DECODE_BYTES_ERROR -9001
#define FAST_DECODE_BVECTOR_ERROR -9101
#define FAST_DECODE_INT32_ERROR -9201
#define FAST_DECODE_INT64_ERROR -9301
#define FAST_DECODE_STRING_ERROR -9401
#define FAST_DECODE_BYTEVECTOR_ERROR -9401
#define FAST_DECODE_TID_NOTFOUND_ERROR -9501


typedef  BYTE  PMAP[PMAPSIZE];

typedef enum tagFIXTYPE{
  FIXNULL=0,
  FIXBOOLEAN,
  FIXINT,
  FIXFLOAT,
  FIXCHAR,
  FIXSTRING,
  FIXMULTIPLEVALUESTRING,
  FIXDATA,
  FIXPRICE,
  FIXQTY,
  FIXAMT,
  FIXCURRENCY,
  FIXPRICEOFFSET,
  FIXEXCHANGE,
  FIXUTCTIMEONLY,
  FIXUTCDATE,
  FIXLOCALMKTDATE,
  FIXUTCTIMESTAMP,
  FIXDAYOFMONTH,
  FIXMONTHYEAR,
}FIXTYPE;

typedef struct tagFixMsg{
  char msgtype[MAXTAGLEN];
  UT_hash_handle hh; 	
}FIXMsg;

typedef struct tagFIXField{
  int id;		
  FIXTYPE type;	
  UT_hash_handle hh; 	
}FIXField;

typedef struct tagGroupField{
  int id;		
  UT_hash_handle hh; 	
}GroupField;

typedef struct tagFIXGroup{
  UT_hash_handle hh; 			
  char msgtype[MAXTAGLEN];
  int fieldid;		
  int delimid;		
  GroupField* gField;
}FIXGroup;

typedef struct tagFixDict{
  BYTE RDEL;
  BYTE FDEL;
  int F0ID;
  int F1ID;
  int F2ID;
  int FnID;
  int FastID;

  FIXMsg *FastMsg;
  FIXField *Field;
  int keylenGroup;
  FIXGroup *Group; 
}FixDict;

static FixDict fixDict;
static int fixDictInit=0;

K1(initfixdict){
  int i,j,f,m,n,gn,fastid;
  FIXField *pField;
  FIXGroup *pGroup;
  GroupField*pGField;
  FIXMsg *pMsg;
  K k0,k1,k2,k3;
  
  if(fixDictInit) R ki(-1);
  fixDict.RDEL=1;
  fixDict.FDEL='=';
  fixDict.F0ID=8;
  fixDict.F1ID=9;
  fixDict.F2ID=35;
  fixDict.FnID=10;

  fixDict.FastMsg=NULL;
  fixDict.FastID=0;
  k0=k(0,"0i^.fix.FixOpt`FastField",(K)0);
  if((NULL==k0)||((-KI)!=k0->t))R ki(FIX_DICT_INIT_ERROR);
  fastid=k0->i;
  if(0<fastid){
    fixDict.FastID=fastid;
    //k1=k(0,"value exec first opval by tid from FastFields where slot=0",(K)0);
    k1=k(0,"(distinct exec .fix.MessageMap name from .fix.FastTemplate) except `",(K)0); //2011.09.22修改,获得Fast消息列表,上述注释掉代码只适用于上交所
    m=k1->n;
    for(i=0;i<m;i++){
      pMsg=malloc(sizeof(FIXMsg));
      strncpy(pMsg->msgtype,kS(k1)[i],sizeof(pMsg->msgtype));
      HASH_ADD_STR(fixDict.FastMsg,msgtype,pMsg);
    }
    r0(k1);
  }
  r0(k0);

  k0=k(0,"value exec id,(``BOOLEAN`INT`FLOAT`CHAR`STRING`MULTIPLEVALUESTRING`DATA`PRICE`QTY`AMT`CURRENCY`PRICEOFFSET`EXCHANGE`UTCTIMEONLY`UTCDATE`LOCALMKTDATE`UTCTIMESTAMP`DAYOFMONTH`MONTHYEAR!`int$til 20)ftype from .fix.Fields",(K)0);
  if((NULL==k0)||(0!=k0->t)||(2!=k0->n))R ki(FIX_DICT_INIT_ERROR);
  k1=kK(k0)[0];k2=kK(k0)[1];
  m=k1->n;
  fixDict.Field=NULL;
  for(i=0;i<m;i++){
    pField=malloc(sizeof(FIXField));
    pField->id=kI(k1)[i];
    HASH_ADD_INT(fixDict.Field,id,pField);
    pField->type=kI(k2)[i];
    //printf("FixField:i=%d,id=%d,type=%d\n",i,pField->id,pField->type); 
  }
  r0(k0);

  k0=k(0,"value exec string mtype,.fix.FieldMap fname from .fix.Relations where isgroup",(K)0);
  if((NULL==k0)||(0!=k0->t)||(2!=k0->n))R ki(FIX_DICT_INIT_ERROR);

  k1=kK(k0)[0];k2=kK(k0)[1];
  m=k1->n;
  fixDict.Group=NULL;
  for(i=0;i<m;i++){
    pGroup=malloc(sizeof(FIXGroup));
    kstrncpy(pGroup->msgtype,kK(k1)[i],MAXTAGLEN);
    pGroup->fieldid=n=kI(k2)[i];
    //printf("msgtype=%s,fieldid=%d\n",pGroup->msgtype,pGroup->fieldid);
    fixDict.keylenGroup =offsetof(FIXGroup,fieldid)+sizeof(n)-offsetof(FIXGroup,msgtype);
    for(f=strlen(pGroup->msgtype);f<sizeof(pGroup->msgtype);f++){pGroup->msgtype[f]=0;} //to behave as hashkey
    HASH_ADD(hh,fixDict.Group,msgtype,fixDict.keylenGroup,pGroup);
    k3=k(0,"{[x;y]exec .fix.FieldMap fname from .fix.Relations where mtype=`$x,y in/: .fix.FieldMap parent}",kp(pGroup->msgtype),ki(pGroup->fieldid),(K)0);
    gn=k3->n;
    pGroup->delimid=-1;pGroup->gField=NULL;
    if(0<n){
      pGroup->delimid=n=kI(k3)[0];
      for(j=0;j<gn;j++){
	pGField=malloc(sizeof(GroupField));
	pGField->id=kI(k3)[j];
	HASH_ADD_INT(pGroup->gField,id,pGField);
      }
    }
    r0(k3);
    //printf("AddGroup:msgtype=%s,fieldid=%d,delimid=%d,groupsize=%d\n",pGroup->msgtype,pGroup->fieldid,pGroup->delimid,gn);
  }
  r0(k0);

  R ki(++fixDictInit);
}

K1(freefixdict){
  FIXMsg *pMsg,*pMRoot=fixDict.FastMsg;
  FIXField *pField,*pFRoot=fixDict.Field;
  FIXGroup *pGroup,*pGRoot=fixDict.Group;
  GroupField*pGField,*pGFRoot;

  if(!fixDictInit) R ki(FIX_DICT_FREE_ERROR);
  while(pMRoot){
    pMsg=pMRoot;          
    HASH_DEL(pMRoot,pMsg);  
    free(pMsg);            
  }
  while(pFRoot){
    pField=pFRoot;          
    HASH_DEL(pFRoot,pField);  
    free(pField);            
  }
  while(pGRoot){
    pGroup=pGRoot;          
    HASH_DEL(pGRoot,pGroup);  
    pGFRoot=pGroup->gField;
    while(pGFRoot){
      pGField=pGFRoot;          
      HASH_DEL(pGFRoot,pGField);  
      free(pGField);            
    }
    free(pGroup);            
  }
  R ki(--fixDictInit);
}

int decodeFieldID(BYTE *buf,int size,int *fid){
  int i=0,len=0,k=0;
  BYTE *pB;
  BYTE b[MAXTAGLEN];

  //O("[%d]{%c}(%c%c%c%c%c%c%c)\n",size,fixDict.FDEL,buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6]);
  pB=memchr(buf+i,fixDict.FDEL,size-i);
  //for(k=0;k<size;k++){
  //  O("k=%d\n",k);
  //  if((fixDict.FDEL)==*(buf+k))break;
  //}
  //pB=(k==size)?NULL:(buf+k);
  //O("pB=%d\n",pB);
  if(NULL==pB) return -1;
  len=pB-(buf+i);
  if(len>=MAXTAGLEN)return -2; 
  memcpy(b,buf+i,len);b[len]=0;i+=++len;
  *fid=atoi(b);
  return i;
}

int decodeNormalValue(BYTE *buf,int size,BYTE *b){
  int i=0,len=0;
  BYTE *pB;
  pB=memchr(buf+i,fixDict.RDEL,size-i);
  if(NULL==pB) return -3;
  len=pB-(buf+i);
  if(len>=MAXBUFLEN)return -4; 
  memcpy(b,buf+i,len);b[len]=0;i+=++len;
  return i;
}

int decodeFixValue(BYTE *buf,int size,FIXField* pField,char *msgtype,int *pVi,K*pLk,K*pLv){
  int i=0,j=0,f=0,s=0,fid=pField->id,er=0;
  FIXGroup* pGroup;
  FIXMsg* pMsg;

  K kv;
  BYTE bd[MAXBUFLEN];
  struct {
    char msgtype[MAXTAGLEN];
    int fieldid;
  } groupkey;

  //printf("type:%d\n",pField->type);

  if(FIXDATA==pField->type){
    if(fixDict.FastID==pField->id){
      HASH_FIND_STR(fixDict.FastMsg,msgtype,pMsg);
      if(NULL!=pMsg){
	kv=knk(0);
	s=decodeFastStream(buf+i,*pVi,&kv,&er);
	if(s<*pVi)printf("decodeFastStream error!msgtype=%s,fastsize=%d,decodesize=%d,errcode=%d\n",msgtype,*pVi,s,er);
      }else kv=kpn(buf+i,*pVi);
    }else{
      kv=kpn(buf+i,*pVi);
    }
    i+=(*pVi)+1;
    //printf("[DATA]size=%d,i=%d,Vi=%d,t=%d,n=%d\n",size,i,*pVi,kv->t,kv->n);
  }else{
    i+=s=decodeNormalValue(buf+i,size-i,bd);if(s<0) R s;	
    switch(pField->type){
    case FIXINT:
      *pVi=atoi(bd);
      strncpy(groupkey.msgtype,msgtype,sizeof(groupkey.msgtype));
      for(f=strlen(groupkey.msgtype);f<sizeof(groupkey.msgtype);f++){groupkey.msgtype[f]=0;}
      groupkey.fieldid=fid;
      HASH_FIND(hh,fixDict.Group,&groupkey.msgtype,fixDict.keylenGroup,pGroup);
      if(NULL==pGroup){
	kv=ki(*pVi);
      }else{
	kv=knk(0);
	//O("gpkey:{%s,%d}-->%d\n",groupkey.msgtype,groupkey.fieldid,pGroup);
	i+=s=decodeGroupField(buf+i,size-i,pGroup,*pVi,&kv);if(s<0){r0(kv);R s;}
	//O("find group,msgtype=%s,fieldid=%d,gn=%d,size=%d\n",msgtype,fid,(*pVi),kv->n);
      }
      break;
    case FIXFLOAT:
    case FIXPRICE:
    case FIXPRICEOFFSET:
    case FIXQTY:
    case FIXAMT:
      kv=kf(atof(bd));
      break;
    case FIXBOOLEAN:
      kv=kb('Y'==bd[0]);
      break;
    case FIXCHAR:
      kv=kc(bd[0]);
      break;
    case FIXSTRING:
      kv=kp(bd);
      break;
    case FIXMULTIPLEVALUESTRING:
      kv=kp(bd);
      break;
    case FIXCURRENCY:
    case FIXEXCHANGE:
      kv=ks(ss(bd));
      break;
    case FIXDAYOFMONTH:
	kv=ki(atoi(bd));
	break;
    case FIXUTCTIMEONLY:
    case FIXUTCDATE:
    case FIXLOCALMKTDATE:
    case FIXUTCTIMESTAMP:
    case FIXMONTHYEAR:
    default:
      kv=kp(bd);
    }
  }
  ja(pLk,&fid);jk(pLv,kv);
  return i;
}

int decodeGroupField(char *buf,int size,FIXGroup* pGroup,int No,K*pL){
  int i=0,j=0,s=0,did=pGroup->delimid,fid=0,Vi=0,isgroupfield,isfirst=1;
  K Lk,Lv,k1;
  FIXField* pField;
  GroupField *pGField;
  Lk=ktn(KI,0);Lv=knk(0);
  //printf("decodegf:No=%d,size=%d\n",No,size);
  if(0<No){
    while(1){
      s=decodeFieldID(buf+i,size-i,&fid);if(s<0){r0(Lk);r0(Lv);R s;}
      HASH_FIND_INT(fixDict.Field,&fid,pField);if(NULL==pField) {O("Unknown group field:%d!\n",fid);r0(Lk);r0(Lv);return -9;}
      if(isfirst&&fid!=did)did=fid; /*组内第一个tag*/
      isfirst=0;
      //printf("fid=%d,did=%d,j=%d\n",fid,did,j);    
      if(did==fid){
	if(j<No){
	  if(j>0){
	    jk(pL,xD(Lk,Lv));
	    Lk=ktn(KI,0);Lv=knk(0);
	  }
	  j++;
	}else{r0(Lk);r0(Lv);R -777;}
      }else{
	HASH_FIND_INT(pGroup->gField,&fid,pGField);
	//printf("%d->%d[%d]\n",fid,pGField,j);
	if(NULL==pGField){
	  if(j!=No){r0(Lk);r0(Lv);R -888;}
	  break;
	}
      }
      i+=s;
      i+=s=decodeFixValue(buf+i,size-i,pField,pGroup->msgtype,&Vi,&Lk,&Lv);if(s<0){r0(Lk);r0(Lv);R s;}
      //printf("i=%d,s=%d,buf[0]=%x\n",i,s,*(buf+i));
    }
    jk(pL,xD(Lk,Lv));
  }else{
    jk(pL,Lk);r0(Lv);
  }
  return i;
}
 
int decodeFixStream(BYTE *buf,int size,K *L,int *per){
  unsigned int i=0,fid=0,len=0,bodylen=0,pos=0,pos1,si=0,crclen=0;
  int s=0;
  int Vi=0;
  long Vl=0; 
  BYTE *pB,*ptr,*msghead;
  BYTE RD=fixDict.RDEL;
  BYTE FD=fixDict.FDEL;
  BYTE b[MAXTAGLEN];
  char BeginString[MAXTAGLEN];
  char MsgType[MAXTAGLEN];
  BYTE bd[MAXBUFLEN];
  C crc[ 4 ];

  K Lk,Lv;
  FIXField tmpField,*pField;

   while(i<size){
    //pos1=i+=12;
    msghead=buf+i;crclen=i;
    i+=s=decodeFieldID(buf+i,size-i,&fid);if(s<0){*per=s;R si;}  /*BeginString*/
    if(!fixDict.F0ID==fid){*per=-5;R si;}
    i+=s=decodeNormalValue(buf+i,size-i,bd);if(s<0){*per=s;R si;}
    //O("size=%d,s=%d,i=%d\n",size,s,i);
    strncpy(BeginString,bd,sizeof(BeginString));
    i+=s=decodeFieldID(buf+i,size-i,&fid);if(s<0){*per=s;R si;}  /*BodyLength*/
    if(!fixDict.F1ID==fid){*per=-6;R si;}
    i+=s=decodeNormalValue(buf+i,size-i,bd);if(s<0){*per=s;R si;}
    bodylen=atoi(bd);
    if(bodylen>size-i){*per=-7;R si;}
    pos=i+bodylen;
    crclen=pos-crclen;
    i+=s=decodeFieldID(buf+i,size-i,&fid);if(s<0){*per=s;R si;}  /*MsgType*/
    if(!fixDict.F2ID==fid){*per=-8;R si;}
    i+=s=decodeNormalValue(buf+i,size-i,bd);if(s<0){*per=s;R si;}
    strncpy(MsgType,bd,sizeof(MsgType));

    Lk=ktn(KI,0);Lv=knk(0);
    ja(&Lk,&fid);jk(&Lv,kp(MsgType));

    while(i<pos){
      i+=s=decodeFieldID(buf+i,size-i,&fid);if(s<0){*per=s;r0(Lk);r0(Lv);R si;}
      HASH_FIND_INT(fixDict.Field,&fid,pField);
      if(NULL==pField){
	//O("Unknown Fix Field:%d!\n",fid);
	tmpField.id=fid;tmpField.type=FIXSTRING;pField=&tmpField;
      };
      //printf("decoding field:%d\n",fid);
      i+=s=decodeFixValue(buf+i,size-i,pField,MsgType,&Vi,&Lk,&Lv);if(s<0){*per=s;r0(Lk);r0(Lv);R si;}
    }
    i+=s=decodeFieldID(buf+i,size-i,&fid);if(s<0){*per=s;r0(Lk);r0(Lv);R si;} /*CheckSum*/
    if(!fixDict.FnID==fid){*per=-10;r0(Lk);r0(Lv);R si;}
    i+=s=decodeNormalValue(buf+i,size-i,bd);if(s<0){*per=s;r0(Lk);r0(Lv);R si;}
    if(3!=strlen(bd)){*per=-11;r0(Lk);r0(Lv);R si;}
    checksum(msghead,crclen,crc);
    if(!strcmp(bd,crc)){
      jk(L,xD(Lk,Lv));
    }else{
      O("fix crc err!crclen=%d,bd=%s,crc=%s\n",crclen,bd,crc);
      jk(L,xD(Lk,Lv));
    }
    
    si=i;
    //jk(L,kpn(buf+pos1,i-pos1));
  }
  return si;
}

K1(decodefix){
  int i=0,n=x->n,r=0,er=0;
  K L=knk(0);

  if(0==fixDictInit)return ki(-1);
  r=decodeFixStream(kG(x),n,&L,&er);
  return (r==n)?L:knk(3,ki(r),ki(er),L);
}

typedef enum tagTYPE{
  Null=0,
  String,
  Int32,
  uInt32,
  Int64,
  uInt64,
  ByteVector,
  Sequence,
}TYPE;

typedef enum tagOP{
  None=0,
  Constant,
  Default,
  Copy,
  Increment,
  Delta,
  Tail,
}OP;

typedef enum tagPresence{
  Mandatory=0,
  Optional
}Presence;

typedef struct tagL2VAL{
  TYPE vt;
  int bytecount;
  union {
    __int32 I4;
    __int64 I8;
    char String[MAXBUFLEN];
  } val;
}L2VAL;

typedef struct tagL2_FAST_Field{
  __int32 id;		//Field indentified
  OP op;		//Field encoding operator
  TYPE type;		//Field data type
  Presence presence;  //Field presence:0 mandatory 1 optional
  __int32 slot;	             //Template slot position
  __int32 shift;	             //decimalPlaces
  L2VAL opVal;	//Field operator init value
  L2VAL value;	//Field current/previous value
  struct tagL2_FAST_MSG* pSequence;
}L2_FAST_Field;

typedef struct tagL2_FAST_MSG{
  PMAP pmap;	//presence map
  __int32 TID;		//template identifier
  __int32 SlotCount;  	 //slot count
  __int32 FieldCount;  	 //field count
  L2_FAST_Field Field[MAXFIELD];
  UT_hash_handle hh; 
}L2_FAST_MSG;

typedef struct tagL2_FAST_Decoding{
  int msgcount;
  L2_FAST_MSG *TMsg;
}L2_FAST_Decoding;

static L2_FAST_Decoding fastDict;
static int fastDictInit=0;
ZI         resetTemplate=0;

int DecodeBytes(BYTE* buf,BYTE* b,int size){
  int i;
  for (i=0;i<size;i++){
      if (buf[i]>=0x80){
	b[i]=buf[i] & 0x7f;
	//O("i=%d,buf=%#0hhx,b=%#0hhx\n",i,buf[i],b[i]);
	return i+1;
      }else  
	b[i]=buf[i];
      //O("i=%d,buf=%#0hhx,b=%#0hhx\n",i,buf[i],b[i]);
  }
  printf("DecodeBytes ERROR:buf=%x,b=%x,size=%d,buf[0]=%#0hhx,buf[1]=%#0hhx,buf[2]=%#0hhx\n",buf,b,size,buf[0],buf[1],buf[2]);
  return FAST_DECODE_BYTES_ERROR;
}

int DecodeInt32(BYTE* buf,L2VAL *pVal,Presence presence){
  BYTE b[8];
  BYTE sign_mask=0x00;
  int size=DecodeBytes(buf,b,6);
  int i;

  if (size>0){
    if (pVal->vt==Int32)sign_mask=0x40;
    if (b[0] & sign_mask)
      pVal->val.I4=-1;
    else  
      pVal->val.I4=0;
    for (i = 0 ; i< size ; i ++) pVal->val.I4= (pVal->val.I4<< 7) | b[i];
    
    if (presence==Optional) {
      if (pVal->val.I4>0)
	pVal->val.I4--;
      else if (pVal->val.I4==0)
	pVal->vt=Null;
    }
  }
  return size;
}

int DecodeInt64(BYTE* buf,L2VAL *pVal,Presence presence){
  BYTE b[12];
  BYTE sign_mask=0x00;
  int size=DecodeBytes(buf,b,10);
  int i;

  if (size>0){
    if (pVal->vt==Int64)	sign_mask=0x40;
    if (b[0] & sign_mask) 
      pVal->val.I8=-1;
    else
      pVal->val.I8=0;
    for (i = 0 ; i< size ; i ++)pVal->val.I8= (pVal->val.I8<< 7) | b[i];
    if (presence==Optional) {
      if (pVal->val.I8>0)	
	pVal->val.I8--;
      else if (pVal->val.I8==0)	
	pVal->vt=Null;
    }
  }
  return size;
}

int DecodeString(BYTE* buf,L2VAL *pVal,Presence presence){
  BYTE b[MAXBUFLEN];
  int size=DecodeBytes(buf,b,MAXBUFLEN);
  if (size>0){
    memcpy(pVal->val.String,b,size);
    pVal->val.String[size]=0;
    if (presence==Optional){
      if (size==1 && pVal->val.String[0]==0)	pVal->vt=Null;
    }
  }
  return size;
}

int DecodeByteVector(BYTE* buf,L2VAL *pVal,Presence presence){
  BYTE b[MAXBUFLEN];
  BYTE *ptr=buf;
  int n=0,size=0,len=0;
  L2VAL Val;
  Val.vt=uInt32;
  size=DecodeInt32(ptr+n,&Val,presence);
  //printf("[BVEC]buf[0]=%#0hhx,buf[1]=%#0hhx,presence=%d,vt=%d,I4=%d\n",ptr[0],ptr[1],presence,Val.vt,Val.val.I4);
  if(size<0) return FAST_DECODE_BVECTOR_ERROR;
  if(Null==Val.vt){
    pVal->vt=Null;
    return size;
  }else{
    pVal->bytecount=n=Val.val.I4;
    memcpy(pVal->val.String,ptr+size,n);
    n+=size;
    R n;
  }
  R n;
}

int Fast_Decode_Field_Value(BYTE* buf,L2_FAST_Field* pField){
  int size=0;
  pField->value.vt=pField->type;
  switch (pField->type)
    {
    case Int32:
    case uInt32:
      size=DecodeInt32(buf,&pField->value,pField->presence);
      if (size<0) return FAST_DECODE_INT32_ERROR;
      break;
    case Int64:
    case uInt64:
        size=DecodeInt64(buf,&pField->value,pField->presence);
      if (size<0) return FAST_DECODE_INT64_ERROR;
      break;
    case String:
        size=DecodeString(buf,&pField->value,pField->presence);
      if (size<0) return FAST_DECODE_STRING_ERROR;
      break;
    case ByteVector:
        size=DecodeByteVector(buf,&pField->value,pField->presence);
      if (size<0) return FAST_DECODE_BYTEVECTOR_ERROR;
      break;
    }
  return size;
}

int GetPMAPSlot(PMAP pmap,int slot){
  int i=(int)(slot)/7;
  int j=(slot)-7*i;
  int mask=0x40>>j;
  int sig=(pmap[i])&mask;
  //if(slot<0)R 1;
  //O("slot=%d,sig=%d\n",slot,sig);
  R sig;
}

int DecodeNormalField(PMAP pmap,L2_FAST_Field*pField,BYTE*buf,K*pLk,K*pLv){
  int size=0;
  L2VAL val;
  double tmp=0.0,tmp1=0.0,tmp2=0.0;

  switch (pField->op){
  case None:
    size=Fast_Decode_Field_Value(buf,pField);
    break;
  case Constant:
    if (pField->presence==Mandatory || GetPMAPSlot(pmap,pField->slot))
      memcpy(&pField->value,&pField->opVal,sizeof(L2VAL));
    else
      pField->value.vt=Null;
    break;
  case Default:
    if (GetPMAPSlot(pmap,pField->slot))
	size=Fast_Decode_Field_Value(buf,pField);
    else
      memcpy(&pField->value,&pField->opVal,sizeof(L2VAL));
    break;

  case Copy:
    if (GetPMAPSlot(pmap,pField->slot)){
      size=Fast_Decode_Field_Value(buf,pField);
    }else{   
      if(resetTemplate)memcpy(&pField->value,&pField->opVal,sizeof(L2VAL)); 
      else{}
    }
    break;
  case Increment:
    if (GetPMAPSlot(pmap,pField->slot)){
      size=Fast_Decode_Field_Value(buf,pField);
    }else{
      if(resetTemplate)memcpy(&pField->value,&pField->opVal,sizeof(L2VAL)); 
      else if(pField->value.vt==Null) {}	
      else if (pField->value.vt==Int32 || pField->value.vt==uInt32)
	pField->value.val.I4++;
      else if (pField->value.vt==Int64 || pField->value.vt==uInt64)
	pField->value.val.I8++;
      else {}
    }
    break;
  case Delta:
    memcpy(&val,&pField->value,sizeof(L2VAL)); /*保存前值*/

    size=Fast_Decode_Field_Value(buf,pField);
    if (pField->value.vt==Null) {}	
    else if (pField->value.vt==Int32 || pField->value.vt==uInt32){
      if(resetTemplate)val.val.I4=0; /*重置前值?if(0!=pField->value.val.I4)*/
      pField->value.val.I4+=val.val.I4;
    }
    else if (pField->value.vt==Int64 || pField->value.vt==uInt64){
      if(resetTemplate)val.val.I8=0; /*重置前值?if(0!=pField->value.val.I8)*/
      pField->value.val.I8+=val.val.I8;
    }
    else {}
  break;

  case Tail:
  default:
    break;
  }

  switch(pField->value.vt){
  case Int32:
  case uInt32:
    
    ja(pLk,&pField->id);
    jk(pLv,(0<pField->shift)?(kf(((Int32==pField->value.vt)?(pField->value.val.I4):(__uint32)pField->value.val.I4)/pow(10.,pField->shift))):ki(pField->value.val.I4));
    break;
  case Int64:
  case uInt64:
    ja(pLk,&pField->id);
    jk(pLv,(0<pField->shift)?(kf(((Int64==pField->value.vt)?pField->value.val.I8:(__uint64)pField->value.val.I8)/pow(10.,pField->shift))):kj(pField->value.val.I8));
    break;
  case String:
    ja(pLk,&pField->id);
    jk(pLv,kp(pField->value.val.String));
    break;
  case ByteVector:
    ja(pLk,&pField->id);
    jk(pLv,kpn(pField->value.val.String,pField->value.bytecount));
    break;
  case Null:
  default:  
    break;
  }
  return size;
}

int DecodeSequenceField(PMAP pmap,L2_FAST_Field* pField,BYTE* buf,K*pLk,K*pLv){
  int n=0,s=0,fn=0,gn=0,sn=0,i=0,j=0,f=0,sid=0;
  K L,Lk,Lv;

  BYTE *ptr=buf;
  L2_FAST_MSG *pMsg=pField->pSequence;
  L2_FAST_Field *pSeqField;
  L2VAL Val;
  fn=pMsg->FieldCount;
  sn=pMsg->SlotCount;
  pSeqField=&((pMsg->Field)[0]);
  sid=pSeqField->id;
  //if((Mandatory==pSeqField->presence)||GetPMAPSlot(pmap,pSeqField->slot)){ //上海注释掉此行代码
  Val.vt=Int32;
  n+=s=DecodeInt32(ptr+n,&Val,pSeqField->presence);if(s<0) R s;
  gn=(Null==Val.vt)?0:Val.val.I4;
  //printf("[SEQ]fn=%d,sn=%d,sid=%d,presence=%d,slot=%d,gn=%d\n",fn,sn,sid,pSeqField->presence,pSeqField->slot,gn);
  L=knk(0);
  for(i=0;i<gn;i++){
    Lk=ktn(KI,0);Lv=knk(0);
    if(0<sn){
      n+=s=DecodeBytes(ptr+n,(BYTE*)pMsg->pmap,PMAPSIZE);if(s<0){r0(L);r0(Lk);r0(Lv);R s;}
      for(f=s;f<PMAPSIZE;f++)(pMsg->pmap)[f]=0;
      //printf("s=%d,n=%d:PMAP:%#0x %#0x %#0x\n",s,n,pMsg->pmap[0],pMsg->pmap[1],pMsg->pmap[2]);
    }
    for(j=1;j<fn;j++){
      pSeqField=&(pMsg->Field[j]);
      n+=s=DecodeField(pMsg->pmap,pSeqField,ptr+n,&Lk,&Lv);if(s<0){r0(L);r0(Lk);r0(Lv);R s;}
      //printf("gi=%d,s=%d,n=%d,fieldidx=%d,slot=%d,tid=%d,fid=%d,ftype=%d,presence=%d,op=%d\n",i,s,n,j,pSeqField->slot,-1,pSeqField->id,pSeqField->type,pSeqField->presence,pSeqField->op);
    }
    jk(&L,xD(Lk,Lv));
  }
  ja(pLk,&sid);jk(pLv,L);
  //}else{} //上海注释掉此行代码
  return n;
}


int DecodeField(PMAP pmap,L2_FAST_Field*pField,BYTE*buf,K*pLk,K*pLv){
  if (pField->type==Sequence){
    return DecodeSequenceField(pmap,pField,buf,pLk,pLv);
  }else{
    return DecodeNormalField(pmap,pField,buf,pLk,pLv);
  }
}

int DecodeFastMsg(BYTE *buf,K*pL){
  BYTE *ptr=buf;
  PMAP pmap;
  int tid,n=0,s=0,i=0,ip=1;
  L2_FAST_MSG *pMsg;
  L2_FAST_Field *pField;
  L2VAL Val,*pVal;
  K Lk,Lv;

  n+=s=DecodeBytes(ptr,(BYTE*)pmap,PMAPSIZE);if(s<0)R s;
  //printf("s=%d,n=%d:PMAP:%#0x %#0x %#0x\n",s,n,pmap[0],pmap[1],pmap[2]);
  for(i=s;i<PMAPSIZE;i++)pmap[i]=0;
  Val.vt=uInt32; /*上海是Int32,深圳是uInt32*/
  n+=s=DecodeInt32(ptr+n,&Val,Mandatory);if(s<0)R s;
  tid=Val.val.I4;
  HASH_FIND_INT(fastDict.TMsg,&tid,pMsg);
  //printf("buf=%x,s=%d,n=%d:TID=%d,pMsg=%x\n",buf,s,n,tid,pMsg);
  if(NULL==pMsg){printf("TID %d not found!\n",tid);R FAST_DECODE_TID_NOTFOUND_ERROR;};
  //printf("FieldCount=%d:SlotCount=%d\n",pMsg->FieldCount,pMsg->SlotCount);
  Lk=ktn(KI,0);Lv=knk(0);
  for(i=0;i<pMsg->FieldCount;i++){ /*上海i=1(Field[0]=35),深圳i=0*/
    pField=&(pMsg->Field[i]);
    //printf("n=%d,i=%d,slot=%d,tid=%d,fid=%d,ftype=%d,presence=%d,op=%d\n",n,i,pField->slot,tid,pField->id,pField->type,pField->presence,pField->op);
    n+=s=DecodeField(pmap,pField,ptr+n,&Lk,&Lv);
    //printf("s=%d,n=%d,fieldidx=%d,slot=%d,tid=%d,fid=%d,ftype=%d,presence=%d,op=%d\n",s,n,i,pField->slot,tid,pField->id,pField->type,pField->presence,pField->op);
    pVal=&(pField->value);
    
    /*
    switch(pVal->vt){
    case Null:printf("value=Null\n");break;
    case uInt32:  
    case Int32:printf("value(I4)=%d\n",pVal->val.I4);break;
    case uInt64:  
    case Int64:printf("value(I8)=%d\n",pVal->val.I8);break;
    case String:printf("value(str)=%s\n",pVal->val.String);break;
    default:
      printf("valtype=%d\n",pVal->vt);
    }
    */
 
    if(s<0){r0(Lk);r0(Lv);R s;}
  }
  if(0<Lk->n){
    jk(pL,xD(Lk,Lv));
  }else{
    r0(Lk);r0(Lv);
  }
  return n;
}

int decodeFastStream(BYTE *buf,int size,K*pL,int *per){
  int i=0,r=0;
  BYTE *ptr=buf;
  resetTemplate=1;
  while(i<size){
    r=DecodeFastMsg(ptr+i,pL);
    if(resetTemplate)resetTemplate--;
    if(r>=0)i+=r;else {*per=r;break;}
  }
  return i;
}

K1(decodefast){
  int n=x->n,s=0,er=0;
  K L=knk(0);
  if(!fastDictInit) return ki(FAST_DECODE_DICT_ERROR);
  s=decodeFastStream(kG(x),n,&L,&er);
  return (s==n)?L:knk(3,ki(s),ki(er),L);
}

L2_FAST_MSG *initSequence(int tid,char* seqname){
  int i,j,m,n,slot,sid;
  TYPE typ;
  L2_FAST_MSG *pMsg=malloc(sizeof(L2_FAST_MSG));
  L2_FAST_Field *pField;
  K k0,k1,k2,k3;
  BYTE bd[MAXBUFLEN];
  k1=k(0,"{[x;y]exec first sid from .fix.FastSequence where tid=x,name=y}",ki(tid),ks(ss(seqname)),(K)0);
  pMsg->TID=sid=k1->i;
  r0(k1);

  k1=k(0,"{[x;y]exec slot from .fix.FastSeqFields where tid=x,sid=y}",ki(tid),ki(sid),(K)0);
  pMsg->FieldCount=n=k1->n;
  slot=0;
  for(j=0;j<n;j++){
    pField=&((pMsg->Field)[j]);
    k2=k(0,"{[x;y;z]value exec first id,(``string`int32`uint32`int64`uint64`unicodestring`sequence`length!(til 8),2)lower first ftype,(``optional!til 2)first presence,first 0i^decimal,(``constant`default`copy`increment`delta`tail!til 7)first op,string first opval,first name from .fix.FastSeqFields where tid=x,sid=y,slot=z}",ki(tid),ki(sid),ki(j),(K)0);
    pField->id=(kK(k2)[0])->i;
    pField->type=typ=(kK(k2)[1])->i;
    if(Sequence==typ){
      pField->pSequence=initSequence(tid,kK(k2)[6]->s);
      pField->slot=-1; 	
    }else{
      pField->presence=(kK(k2)[2])->i;
      pField->shift=(kK(k2)[3])->i;
      pField->op=(kK(k2)[4])->i;
      if((0==j)||(None==pField->op)||(Delta==pField->op)||(Constant==pField->op)&&(Mandatory==pField->presence))
	pField->slot=-1;
      else pField->slot=slot++;
      k3=kK(k2)[5];
      if(0==k3->n){
	pField->opVal.vt=Null;
      }else{
	kstrncpy(bd,k3,MAXBUFLEN);
	pField->opVal.vt=typ;
	if((Int32==typ)||(uInt32==typ)){
	  pField->opVal.val.I4=atoi(bd);
	}else if((Int64==typ)||(uInt64==typ)){
	  pField->opVal.val.I8=atol(bd);
	}else if(String==typ){
	  strncpy(pField->opVal.val.String,bd,MAXTAGLEN);
	}
      }
    }
    r0(k2);
  }
  r0(k1);
  pMsg->SlotCount=slot;
  return pMsg;
}
 
K1(initfastdict){
  int i,j,m,n,tid,slot,seqid;
  TYPE typ;
  L2_FAST_MSG *pMSG;
  L2_FAST_Field *pField;
  K k0,k1,k2,k3;
  BYTE bd[MAXBUFLEN];
  if(fastDictInit) R ki(FAST_DICT_INIT_ERROR);
  k0=k(0,"exec id from .fix.FastTemplate",(K)0);
  fastDict.msgcount=m=k0->n;
  fastDict.TMsg=NULL;
  for(i=0;i<m;i++){
    pMSG=malloc(sizeof(L2_FAST_MSG));
    pMSG->TID=tid=kI(k0)[i];
    HASH_ADD_INT(fastDict.TMsg,TID,pMSG);
    k1=k(0,"{exec slot from .fix.FastFields where tid=x}",ki(tid),(K)0);
    pMSG->FieldCount=n=k1->n;
    slot=1;
    for(j=0;j<n;j++){
      pField=&((pMSG->Field)[j]);
      k2=k(0,"{[x;y]value exec first id,(``string`int32`uint32`int64`uint64`unicodestring`sequence!til 8)lower first ftype,(``optional!til 2)first presence,first 0i^decimal,(``constant`default`copy`increment`delta`tail!til 7)first op,string first opval,first name from .fix.FastFields where tid=x,slot=y}",ki(tid),ki(j),(K)0);
      pField->id=(kK(k2)[0])->i;
      pField->type=typ=(kK(k2)[1])->i;
      if(Sequence==typ){
	pField->pSequence=initSequence(tid,(kK(k2)[6])->s);
	pField->slot=-1; 	
      }else{
	pField->presence=(kK(k2)[2])->i;
	pField->shift=(kK(k2)[3])->i;
	pField->op=(kK(k2)[4])->i;
	if((None==pField->op)||(Delta==pField->op)||(Constant==pField->op)&&(Mandatory==pField->presence)) //上海有(0==j)||,存疑
	  pField->slot=-1;
	else pField->slot=slot++;
	k3=kK(k2)[5];
	if(0==k3->n){
	  pField->opVal.vt=Null;
	}else{
	  kstrncpy(bd,k3,MAXBUFLEN);
	  pField->opVal.vt=typ;
	  if((Int32==typ)||(uInt32==typ)){
	    pField->opVal.val.I4=atoi(bd);
	  }else if((Int64==typ)||(uInt64==typ)){
	    pField->opVal.val.I8=atol(bd);
	  }else if(String==typ){
	    strncpy(pField->opVal.val.String,bd,MAXTAGLEN);
	  }
	}

      }
      r0(k2);
      //printf("tid=%d,slot=%d,id=%d,type=%d,presence=%d,shift=%d,op=%d\n",pMSG->TID,pField->slot,pField->id,pField->type,pField->presence,pField->shift,pField->op);
    }
    pMSG->SlotCount=slot;
    r0(k1);
  }
  r0(k0);
  /*
    m = HASH_COUNT(fastDict.TMsg);
    printf("there are %d Templates,root=%x\n",m,fastDict.TMsg);
    for(pMSG=fastDict.TMsg; pMSG != NULL; pMSG=pMSG->hh.next) {
    printf("TID=%d,fc=%d,sc=%d,ptr=%x\n",pMSG->TID,pMSG->FieldCount,pMSG->SlotCount,pMSG);
    }
    printf("sizeof(TYPE)=%d\n",sizeof(TYPE));
    printf("sizeof(OP)=%d\n",sizeof(OP));
    printf("sizeof(Presence)=%d\n",sizeof(Presence));
    printf("sizeof(L2VAL)=%d\n",sizeof(L2VAL));
    printf("sizeof(L2_FAST_Field)=%d\n",sizeof(L2_FAST_Field));
    printf("sizeof(L2_FAST_MSG)=%d\n",sizeof(L2_FAST_MSG));
    printf("sizeof(PMAP)=%d\n",sizeof(PMAP));
  */
  return ki(++fastDictInit);
}

void freefastmsg(L2_FAST_MSG *pMSG){
  int i=0,n=pMSG->FieldCount;
  L2_FAST_Field * pField;
  L2_FAST_MSG *pMsg;
  //printf("[Sequence]tid=%d,fieldcount=%d\n",pMSG->TID,pMSG->FieldCount);
  for(i=0;i<n;i++){
    pField=&(pMSG->Field[i]);
    //printf("fieldslot=%d,fid=%d,type=%d,presence=%d,shift=%d,op=%d\n",i,pField->id,pField->type,pField->presence,pField->shift,pField->op);

    if(NULL!=pField->pSequence){
      pMsg=pField->pSequence;
      freefastmsg(pMsg);
      free(pMsg);
    }
  }
}

K1(freefastdict){
  int i=0,j=0,m=fastDict.msgcount,n=0;
  L2_FAST_MSG *pMSG,*pTMsg=fastDict.TMsg;
  L2_FAST_Field * pField;
  if(!fastDictInit) R ki(FAST_DICT_FREE_ERROR);
  while(pTMsg){
    pMSG =pTMsg;          
    HASH_DEL(pTMsg,pMSG);  
    n=pMSG->FieldCount;
    for(j=0;j<n;j++){
    pField=&(pMSG->Field[j]);
      if(NULL!=pField->pSequence)freefastmsg(pField->pSequence);
    }
    free(pMSG);            
  }
  R ki(--fastDictInit);
}

