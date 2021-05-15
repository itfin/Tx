#ifndef __JGDFDAPI_DATADEF_H__
#define __JGDFDAPI_DATADEF_H__
#include "JGDataTypesDef.h"

#ifndef VHANDLE
typedef void* VHANDLE;									///< �����ʶ
#endif // !VHANDLE

#define JGAPI_SERVERINFO_MAX	4						///< ������������

#pragma pack(push, 1)

/*-----------------------------------------------ö�ٶ���----------------------------------------------------------*/
///< ��Ϣ���Ͷ�Ӧ�Ľṹ�������
enum DFDAPI_MSG_ID
{
	MSG_INVALID = -100,
	
	///< ϵͳ��Ϣ
	MSG_SYS_DISCONNECT_NETWORK,							///< ����Ͽ��¼�, ��Ӧ�Ľṹ��ΪNULL
	MSG_SYS_CONNECT_RESULT,								///< �����������ӵĽ��
	MSG_SYS_LOGIN_RESULT,								///< ��½Ӧ��
	MSG_SYS_CODETABLE_RESULT,							///< ����������յ�����Ϣ��ɻ�ȡ��Ӧ�����,����Ϣ��ʾ������Ȩ�г�������ȡ
	MSG_SYS_QUOTATIONDATE_CHANGE,						///< �������ڱ��֪ͨ����ȡ����
	MSG_SYS_MARKET_CLOSE,								///< ���У���ȡ����
	MSG_SYS_HEART_BEAT,									///< ������������Ϣ, ��Ӧ�Ľṹ��ΪNULL
	MSG_SYS_MARKET_EVENT,								///< �г��¼�֪ͨ��Ϣ(���г����̣�ת����),�յ����¼������̻��߿��պ�ɻ�ȡ���պ���Ȩ��Ϣ
	
	//�����г������֪ͨ.����ĳЩ��С�г����ݻص�ʱ��ͬʱ����������г��Ŵ����������������ݽ�MSG_SYS_CODETABLE_RESULT�ȵ���
	//���Ӹ���Ϣ��֪ͨÿһ�г�������������ͻ��ɾݴ�ѡ���ʱ��������
	MSG_SYS_SINGLE_CODETABLE_RESULT,					///< �����г�����������յ�����Ϣ��ɻ�ȡ��Ӧ�ĵ����г������
	MSG_SYS_QUOTEUNIT_CHANGE,							///< �۲�仯
	MSG_SYS_PACK_OVER,									///< ��ǰ������������

	///< ������Ϣ
	MSG_DATA_INDEX,										///< ָ������
	MSG_DATA_MARKET,									///< ��������
	MSG_DATA_FUTURE,									///< �ڻ�����
	MSG_DATA_HKEX,										///< �۹�����
	MSG_DATA_TRANSACTION,								///< ��ʳɽ�
	MSG_DATA_ORDERQUEUE,								///< ί�ж���
	MSG_DATA_ORDER,										///< ���ί��
	MSG_DATA_BBQTRANSACTION,							///< BBQ��ȯ�ɽ�����
	MSG_DATA_BBQBID,									///< BBQ��ȯ��������
	MSG_DATA_NON_MD,									///< ��������Ϣ
	MSG_DATA_OTC_OPTION,								///< ������Ȩ
	MSG_DATA_BROKERQUEUE,								///< �����̶���(�۹�)

	MSG_SH_ETF_LIST,									///< �յ�����ETF�嵥��Ϣ.
	MSG_SZ_ETF_LIST,									///< �յ�����ETF�嵥��Ϣ.
	MSG_UPDATE_ETFLIST,									///< ETF�嵥�и���,���������������»�ȡ.
	MSG_HKEX_BASICINFO,									///< �۹ɻ�����Ϣ����,���ȡ.

	MSG_DATA_OPTION,									///< ��Ȩ����
	MSG_OPTION_BASICINFO,								///< ��Ȩ������Ϣ����,���ȡ.
};

///< ������������ 
enum DFDAPI_SET_ENVIRONMENT
{
	DFDAPI_ENVIRON_HEART_BEAT_INTERVAL,					///< Heart Beat�����������, ��ֵΪ0���ʾĬ��ֵ10����
	//DFDAPI_ENVIRON_MISSED_BEAT_COUNT,					///< ���û���յ����������������ֵ����û�յ������κ����ݣ����ж�Ϊ���ߣ���ֵ0ΪĬ�ϴ���2��
	DFDAPI_ENVIRON_OPEN_TIME_OUT,						///< �ڵ�DFDAPI_Open�ڼ䣬����ÿһ�����ݰ��ĳ�ʱʱ�䣨����������DFDAPI_Open�����ܵ����ȴ�ʱ�䣩����ֵΪ0��Ĭ��30��
	DFDAPI_ENVIRON_USE_PACK_OVER,
	DFDAPI_ENVIRON_HEART_BEAT_FLAG,						///< �������ݷ��ͷ�ʽ��0: ȡ������������ 1��û�����ݷ��͵�ʱ�����������ݣ�2���й��ɷ����������ݣ�
	DFDAPI_ENVIRON_SOURCE_MODE,							///< ˫������Դģʽ,ֵ�ο�DFDAPI_SOURCE_SETTINGö����
	DFDAPI_ENVIRON_SOURCE_MODE_VALUE,					///< ˫������Դģʽ�²�����ֵ
	DFDAPI_ENVIRON_OUT_LOG,								///< 1����ǰĿ¼�´���log�������ڵ�ǰ·����log�ļ���ʱ������log�ļ�����
	DFDAPI_ENVIRON_SNAPSHOT_ENENT,						///< 1�����Ϳ����¼�������֪ͨ�����ղ����͵��ص�����������ֱ�ӷ��Ϳ��յ��ص��������޿���֪ͨ
	DFDAPI_ENVIRON_ORIGINAL_VOL,						///< ԭʼ�ṹ��Ч��1��ָ���ɽ����ͳɽ���ĵ�λΪ�ɺ�Ԫ��Ĭ��Ϊ100�ɺ�100Ԫ
	DFDAPI_ENVIRON_BREAKPOINT,							///< 1.����Ͽ���ϵ�������else.�������¿���
	DFDAPI_ENVIRON_PUSHMODE,							///< 0:����Ĭ�϶������ͣ�1:����Ĭ�϶������͡�
};

///< ������ �����������
enum DFDAPI_ERR_CODE
{
	DFDAPI_ERR_UNKOWN = -400,							///< δ֪����
	DFDAPI_ERR_UNINITIALIZE = -399,						///< �ӿڻ���δ��ʼ��
	DFDAPI_ERR_INITIALIZE_FAILURE = -200,				///< ��ʼ��socket����ʧ��
	DFDAPI_ERR_NETWORK_ERROR,							///< �������ӳ�������
	DFDAPI_ERR_INVALID_PARAMS,							///< ���������Ч
	DFDAPI_ERR_VERIFY_FAILURE,							///< ��½��֤ʧ�ܣ�ԭ��Ϊ�û�������������󣻳�����½����
	DFDAPI_ERR_NO_AUTHORIZED_MARKET,					///< ����������г���û����Ȩ
	DFDAPI_ERR_NO_CODE_TABLE,							///< ����������г����춼û�д����
	DFDAPI_ERR_NO_BASICINFO,							///< ����������г�������Ϣ����Ϊ��.
	DFDAPI_ERR_SUCCESS = 0,								///< �ɹ�
};

//�������������
enum DFDAPI_PROXY_TYPE
{
	DFDAPI_PROXY_SOCK4,
	DFDAPI_PROXY_SOCK4A,
	DFDAPI_PROXY_SOCK5,
	DFDAPI_PROXY_HTTP11,
};

enum SUBSCRIPTION_STYLE
{
	SUBSCRIPTION_SET = 0,								///< ���ö������飬�ٴ����ö���ʱ���Զ�ȡ��֮ǰ���ж��Ĵ���.
	SUBSCRIPTION_ADD = 1,								///< ���Ӷ��Ĵ���
	SUBSCRIPTION_DEL = 2,								///< ɾ�����Ĵ���
};


/*-----------------------------------------------��Ϣͷ------------------------------------------------------------*/
///< Ӧ��ͷ
struct DFDAPI_APP_HEAD
{
	int	nHeadSize;										///< ����¼�ṹ��С
	int	nItemCount;										///< ��¼����
	int	nItemSize;										///< ��¼��С
};

///< ������Ϣ�ṹ
struct DFDAPI_CALLBACK_MSG
{
	int  	                nDataType;					///< �������� 
	int			            nDataLen;					///< ���ݳ��ȣ�������DFDAPI_APP_HEAD�ĳ��ȣ�
	int			            nServerTime;				///< ����������ʱ�������ȷ������HHMMSSmmm��
	int                     nConnectId;					///< ����ID
	DFDAPI_APP_HEAD*        pAppHead;					///< Ӧ��ͷ
	void*                   pData;						///< ����ָ��
};
/*-----------------------------------------------��Ϣͷ------------------------------------------------------------*/



/*-----------------------------------------------�ص�����----------------------------------------------------------*/
/*
* ���ݻص�
* @param vHandle �ص�ʵ����ʶ
* @param pMsg �ص���Ϣ������֪ͨ�û��յ���������գ���ʳɽ������ί�У�ί�ж��е�����
*/
#ifdef _WIN32
typedef void(__stdcall *dfdapi_data_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#else
typedef void(*dfdapi_data_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#endif

/*
* ֪ͨ�ص�
* @param vHandle �ص�ʵ����ʶ
* @param pMsg �ص���Ϣ������֪ͨ�û��յ�������Ͽ��¼������ӣ���������������������
*/
#ifdef _WIN32
typedef void(__stdcall *dfdapi_notice_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#else
typedef void(*dfdapi_notice_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#endif
/*-----------------------------------------------�ص�����----------------------------------------------------------*/




///< ETF�嵥�ļ�����.
struct DFDAPI_ETFLISTFILE
{
	char szMarket[4];
	char szCode[12];
	char szFileName[32];
	int nFileLen;
	char *pFileData;
};


//��ϸ����	���Ͷ���
//0x01	������ָ��
//0x03	����ָ��
//0x04	����ָ��
//0x05	ϵͳ����ָ��
//0x06	�û�����ָ��
//0x07	�ڻ�ָ��
//0x08	ָ���ֻ�
//
//0x10	A��
//0x11	��С���
//0x12	��ҵ���
//0x16	B��
//0x17	H��
//0x1a	US
//0x1b	US ADR
//0x1e	��չ����Ʊ(��)
//
//0x20	����
//0x21	δ���п��Ż��𣨿���ʽ�������꣩
//0x22	���п��Ż���LOF����
//0x23	�����Ϳ���ʽָ������ETF����
//0x25	��չ������(��)
//0x26	�ּ��ӻ���
//0x27	���ʽ����
//
//
//0x30	����ծȯ����ծ��
//0x31	��ҵծȯ
//0x32	����ծȯ��֤ȯ�ʲ�����
//0x33	��תծȯ
//0x34	��ת�ɷ���ծ
//0x35	�ط�ծ
//0x36	��˾ծ
//0x37	��ծ
//0x38	˽ļծ
//
//0x40	��ծ�ع�
//0x41	��ծ�ع�
//0x42	ծȯ��Ѻʽ�ع�
//
//0x60	Ȩ֤
//0x61	�Ϲ�Ȩ֤
//0x62	�Ϲ�Ȩ֤
//0x64	�Ϲ�Ȩ֤(B��)
//0x65	�Ϲ�Ȩ֤(B��)
//0x66	ţ֤��moo - cow��
//0x67	��֤��bear��
//
//0x70	ָ���ڻ�
//0x71	��Ʒ�ڻ�
//0x72	��Ʊ�ڻ�
//0x73	ͬҵ��������ڻ�
//0x74	������ծȯ(Exchange Fund Note Futures)
//0x75	�ڻ�ת�ֻ�����(Exchange For Physicals)
//0x76	�ڻ�ת���ڽ���(Exchange of Futures For Swaps)
//0x78	ָ���ڻ�����CX
//0x79	ָ���ڻ�����CC
//0x7a	��Ʒ�ڻ�����CX
//0x7b	��Ʒ�ڻ�����CC
//0x7c	��Ʊ�ڻ�����CX
//0x7d	��Ʊ�ڻ�����CC
//0x7e	���ֲ����
//0x7f	���ڲ����
//
//0x80	��������
//0x81	�������
//0x82	�������
//
//0x90	�Ϲ���Ȩ
//0x91	�Ϲ���Ȩ
//0x92	ָ���Ϲ���Ȩ
//0x93	ָ���Ϲ���Ȩ
//0x94	��Ʒ�Ϲ���Ȩ
//0x95	��Ʒ�Ϲ���Ȩ
//
//0xd0	��������
//0xd1	��������(HK)
//0xd2	��������(Interal)
//
//0xe0	�����(noble metal)
//
//0xf0	����
//0xf1	A���¹��깺
//0xf2	A������

///< �������Ϣ.
struct DFDAPI_CODEINFO
{
	char szWindCode[32];									///< 000001.SZ;600000.SH;IH1711.CFF;
	char szSecurityID[16];									///< �������֤ȯ����.
	char szSecurityCode[24];								///< ������ԭʼ֤ȯ����.
	char szMarket[8];										///< SZ;SH;CFF;SHO;SZO;
	char szENName[32];										///< Ӣ������.
	char szCNName[32];										///< ֤ȯ����.
	int nType;												///< ֤ȯ����.
};

///< ���ӽ����MSG_SYS_CONNECT_RESULT
struct DFDAPI_CONNECT_RESULT
{
	char szIp[32];
	char szPort[8];
	char szUser[64];
	char szPwd[64];
	unsigned int nConnResult;								///< Ϊ0���ʾ���ӳɹ�����0���ʾ����ʧ��
	int nConnectionID;										///< ����ID
};

///< ��¼Ӧ��MSG_SYS_LOGIN_RESULT
struct DFDAPI_LOGIN_RESULT
{
	unsigned int nLoginResult;								///< Ϊ0���ʾ��֤�ɹ�����0���ʾ��½��֤ʧ��
	char szInfo[256];										///< ��½����ı�
	int nMarkets;											///< �г�����
	char szMarket[256][8];									///< �г����� SZ, SH, CF, SHF, CZC, DCE
	int nDynDate[256];										///< ��̬��������
};

///< ϵͳ��Ϣ��MSG_SYS_CODETABLE_RESULT ��Ӧ�Ľṹ
struct DFDAPI_CODE_RESULT
{
	char szInfo[128];										///< ��������ı�
	int nMarkets;											///< �г�����
	char szMarket[256][8];									///< �г�����
	int nCodeCount[256];									///< ���������
	int nCodeDate[256];										///< ���������
};



///< ������գ�MSG_DATA_MARKET.
struct DFDAPI_MARKET_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< ԭʼCode
	int			nActionDay;									///< ҵ������(��Ȼ��)
	int			nTradingDay;								///< ������
	int			nTime;										///< ʱ��(HHMMSSmmm)
	int			nStatus;									///< ״̬
    T_I64		nPreClose;									///< ǰ���̼�
    T_I64		nOpen;										///< ���̼�
    T_I64		nHigh;										///< ��߼�
    T_I64		nLow;										///< ��ͼ�
    T_I64		nMatch;										///< ���¼�
    T_I64		nAskPrice[10];								///< ������
    T_I64		nAskVol[10];								///< ������
    T_I64		nBidPrice[10];								///< �����
    T_I64		nBidVol[10];								///< ������
	int			nNumTrades;									///< �ɽ�����
    T_I64		iVolume;									///< �ɽ�����
    T_I64		iTurnover;									///< �ɽ��ܽ��
    T_I64		nTotalBidVol;								///< ί����������
    T_I64		nTotalAskVol;								///< ί����������
    T_I64		nWeightedAvgBidPrice;						///< ��Ȩƽ��ί��۸�
    T_I64		nWeightedAvgAskPrice;						///< ��Ȩƽ��ί���۸�
	int			nIOPV;										///< IOPV��ֵ��ֵ
	int			nYieldToMaturity;							///< ����������
    T_I64		nHighLimited;								///< ��ͣ��
    T_I64		nLowLimited;								///< ��ͣ��
	char		chPrefix[4];								///< ֤ȯ��Ϣǰ׺
	int			nSyl1;										///< ��ӯ��1
	int			nSyl2;										///< ��ӯ��2
	int			nSD2;										///< ����2���Ա���һ�ʣ�
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< ָ��������գ�MSG_DATA_INDEX.
struct DFDAPI_INDEX_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< ԭʼCode
	int         nActionDay;									///< ҵ������(��Ȼ��)
	int         nTradingDay;								///< ������
	int         nTime;										///< ʱ��(HHMMSSmmm)
	int			nStatus;									///< ״̬��20151223����
    T_I64		nOpenIndex;									///< ����ָ��
    T_I64 	nHighIndex;									///< ���ָ��
    T_I64 	nLowIndex;									///< ���ָ��
    T_I64 	nLastIndex;									///< ����ָ��
    T_I64	    iTotalVolume;								///< ���������Ӧָ���Ľ�������
    T_I64	    iTurnover;									///< ���������Ӧָ���ĳɽ����
    T_I64		nPreCloseIndex;								///< ǰ��ָ��
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< �ڻ�������գ�MSG_DATA_FUTURE.
struct DFDAPI_FUTURE_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< ԭʼCode
	int         nActionDay;									///< ҵ������(��Ȼ��)
	int         nTradingDay;								///< ������
	int			nTime;										///< ʱ��(HHMMSSmmm)	
	int			nStatus;									///< ״̬
    T_I64		iPreOpenInterest;							///< ��ֲ�
	T_I64		nPreClose;									///< �����̼�
	unsigned int	nPreSettlePrice;						///< �����
	T_I64		nOpen;										///< ���̼�	
	T_I64		nHigh;										///< ��߼�
	T_I64		nLow;										///< ��ͼ�
	T_I64		nMatch;										///< ���¼�
	T_I64		iVolume;									///< �ɽ�����
	T_I64		iTurnover;									///< �ɽ��ܽ��
	T_I64		iOpenInterest;								///< �ֲ�����
	T_I64		nClose;										///< ������
	unsigned int	nSettlePrice;							///< �����
	T_I64		nHighLimited;								///< ��ͣ��
	T_I64		nLowLimited;								///< ��ͣ��
	int			nPreDelta;									///< ����ʵ��
	int			nCurrDelta;									///< ����ʵ��
	T_I64		nAskPrice[5];								///< ������
	T_I64		nAskVol[5];									///< ������
	T_I64		nBidPrice[5];								///< �����
	T_I64		nBidVol[5];									///< ������
	T_I64		nAuctionPrice;								///< �������жϲο���
	int			nAuctionQty;								///< �������жϼ��Ͼ�������ƥ����	
	int			nAvgPrice;									///< ֣�����ڻ�����
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< ��Ȩ������գ�MSG_DATA_OPTION.
struct DFDAPI_OPTION_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< ԭʼCode
	int			nDate;										///< ��������(YYYYMMDD).
	int			nTime;										///< ����ʱ��(HHMMSSmmm).	
	T_I64		iTotalLongPosition;							///< ��ǰ��Լδƽ���� N12 ����λ�� ���ţ���.
	T_I64		iTradeVolume;								///< �ܳɽ����� N16.
	double		dTotalValueTraded;							///< �ɽ���� N16(2) ����ȷ���֣�.
	unsigned int	nPreSettlePrice;						///< ���ս���� N11(4) ����ȷ��0.1�壩.
	unsigned int	nOpenPrice;								///< ���տ��̼� N11(4) ����ȷ��0.1�壩.
	unsigned int	nAuctionPrice;							///< ��̬�ο��۸� N11(4) ���������жϲο��ۣ���ȷ��0.1�壩.
	T_I64		iAuctionQty;								///< ����ƥ������ N12.
	unsigned int	nHighPrice;								///< ��߼� N11(4) ����ȷ��0.1�壩.
	unsigned int	nLowPrice;								///< ��ͼ� N11(4) ����ȷ��0.1�壩.
	unsigned int	nTradePrice;							///< ���¼� N11(4) �����³ɽ��ۣ���ȷ��0.1�壩.
	unsigned int	arrnBidPrice[5];						///< ����� N11(4) ����ǰ����ۣ���ǰ���żۣ�����ȷ��0.1�壩.
	T_I64		arriBidVolume[5];							///< ������ N12.
	unsigned int	arrnAskPrice[5];						///< ������ N11(4) ����ǰ�����ۣ���ǰ���żۣ�����ȷ��0.1�壩.
	T_I64		arriAskVolume[5];							///< ������ N12.
	unsigned int	nSettlePrice;							///< ���ս���� N11(4) ***��������Ȩ����Ŀǰȡ���˽���۵ķ���***.
	char		szTradingPhaseCode[4];						///< ��Ʒʵʱ�׶μ���־ C4 

	int			nRFValue;									///< �۲���¼۶Աȼ���һ���۸񣩣���ȷ��0.1�壩.
	T_I64		iNumTrades;									///< �ɽ�����.
	unsigned int	nSecurityClosePx;						///< ��Լǰ���̼� N11(4) (�������̼ۣ��Ҷ��룬��ȷ����).
	unsigned int	nHighLimitedPrice;						///< �Ƿ����޼۸� N11(4) (������Ȩ��ͣ�۸񣬾�ȷ��0.1��).
	unsigned int	nLowLimitedPrice;						///< �������޼۸� N11(4) (������Ȩ��ͣ�۸񣬾�ȷ��0.1��).
};

///< ��ʳɽ�MSG_DATA_TRANSACTION.
struct DFDAPI_TRANSACTION
{
	char		szWindCode[32];								///< 600001.SH.
	char		szCode[32];									///< ԭʼCode.
	int			nActionDay;									///< ��Ȼ��.
	int 		nTime;										///< �ɽ�ʱ��(HHMMSSmmm).
	int 		nChannelNo;									///< �ɽ�ͨ��.
	T_I64		iTradeIndex;								///< �ɽ����.
	T_I64		iAskOrder;									///< ������ί�����.
	T_I64		iBidOrder;									///< ����ί�����.
	unsigned int unPrice;									///< �ɽ��۸�.
	T_I64 	iVolume;									///< �ɽ�����.
	T_I64		iTurnover;									///< �ɽ����.
	int			nBSFlag;									///< ��������(��'B', ����'A', ������' ')
	char		chOrderKind;								///< �ɽ����
	char		chFunctionCode;								///< �ɽ�����
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч.
};

///< ���ί��MSG_DATA_ORDER.
struct DFDAPI_ORDER_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< ԭʼCode
	int 		nActionDay;									///< ί������(YYMMDD)
	int 		nTime;										///< ί��ʱ��(HHMMSSmmm)
	int			nChannelNo;									///< Ƶ������(�ɽ�ͨ��).
	T_I64		iApplSeqNum;								///< ί�����.
	unsigned int unPrice;									///< ί�м۸�
	unsigned int unVolume;									///< ί������
	char		chOrderKind;								///< ί�����
	char		chFunctionCode;								///< ί�д���('B','S','C')
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< ί�ж���MSG_DATA_ORDERQUEUE.
struct DFDAPI_AB50_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< ԭʼCode
	int			nActionDay;									///< ��Ȼ��
	int 		nTime;										///< ʱ��(HHMMSSmmm)
	int			nSide;										///< ��������('B':Bid 'A':Ask)
	T_I64		nPrice;										///< ί�м۸�
	int 		nOrders;									///< ��������
	int 		nABItems;									///< ��ϸ����
	int 		nABVolume[200];								///< ������ϸ
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< �۹�������գ�MSG_DATA_HKEX.
struct DFDAPI_HKEX_DATA
{
	char szWindCode[32];									///< 600001.SH 
	char szCode[32];										///< ԭʼCode
	int nDate;												///< ��������(YYYYMMDD).
	int nTime;					       		 				///< ������Ƭ(HHMMSSmmm).
	int	nStatus;					   						///< ��Ʒʵʱ�׶μ���־.
	unsigned int unPreClosePx;								///< ǰ���̼�.*10000
	unsigned int unNominalPrice;							///< ���̼�.*10000
	unsigned int unOpenPrice;								///< ���̼�.*10000
	unsigned int unHighPrice;								///< ��߼�.*10000
	unsigned int unLowPrice;								///< ��ͼ�.*10000
	unsigned int unTradePrice;								///< ���¼�.*10000
	long long llTotalVolume;		    					///< �ɽ�����.
	double dTotalAmount;									///< �ɽ��ܽ��.
	unsigned int arrnAskPrice[10];							///< ί����.*10000
	long long arriAskVolume[10];							///< ί����.
	long long arriTotalAskOty[10];							///< ί����ί�б���.
	unsigned int arrnBidPrice[10];							///< ί���.*10000
	long long arriBidVolume[10];							///< ί����.
	long long arriTotalBuyOty[10];							///< ί����ί�б���.
	unsigned int unTradeVolume;								///< ˲ʱ�ɽ���.
	unsigned int unSpread;									///< �۲�.*10000
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< ������Ϣ�� DFDAPI_Close�����������󣬴�ָ����Ч
};

///< �۹ɴ��������Ϣ
struct DFDAPI_BASICINFO_HKEX
{
	char szWindCode[32];									///< 00001.HK 
	char szCode[32];										///< ԭʼCode
	int nDate;												///< ����(YYYYMMDD).
	char szISIN[16];										///< ISIN
	char szSymbol[32];										///< ����֤ȯ���
	char szSymbolEn[16];									///< Ӣ��֤ȯ���
	char szSecurityDesc[32];								///< Ӣ��ȫ��
	char szUnderlyingSecurityID[8];							///< ����֤ȯ����
	char szMarketID[8];										///< �г����� MAIN- ����  GEM-��ҵ��	ETS - ���佻��֤ȯ   NASD - Nasdaq AMX�г�
	char szSecurityType[8];									///< ֤ȯ��� BOND - Bond ծȯ BWRT - Basket Warrant һ����Ȩ֤		EQTY - Equity  �ɱ�			TRST - Trust  ����
	char szCurrency[4];										///< ��������
	int nAmountTimes;										///< ���ҵ�λ ���ҵ�λ��ʾǰ���̼۸��ֶεĵ�λ�������ҵ�λȡֵΪ0ʱ��ǰ���̼۸�=ǰ���̼۸��ֶ�ȡֵ��10��0���ݣ������ҵ�λȡֵΪ1ʱ��ǰ���̼۸�=ǰ���̼۸��ֶ�ȡֵ��10��1���ݣ��������ơ�
	double dPerValue;										///< ��ֵ
	char szPerValueCurrency[4];								///< ��ֵ��������
	double dInterest;										///< ��Ϣ
	int nIssueDate;											///< ��������
	unsigned int unRoundLot;								///< ������λ
	unsigned int unPreClosePx;								///< ǰ���̼۸� * 10000
	char szText[50];										///< ��ע
	char SecurityStatusFlag[12];							///< ��Ʒ״̬��Ϣ ���ֶ�Ϊ8λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո񡣵�1λ���޶��塣��2λ���޶��塣��3λ����0����ʾ�Ǳ��֤ȯ����1����ʾ���֤ȯ��
	char szDataSource[8];									///< �������ݵ���Դ�������һλ���㣬��ʾ�������ͨ������ڶ�λ���㣬��ʾ���Ի���ͨ��
};

///< ��Ȩ������Ϣ
struct DFDAPI_BASICINFO_OPTION
{
	int nDate;												///< ����(YYYYMMDD).
	char szWindCode[32];									///< 00001.HK 
	char szCode[32];										///< ԭʼCode
	char szContractID[24];									///< [sh][sz]��Լ���״��� C19.
	char szContractSymbol[24];								///< [sh][sz]��Ȩ��Լ��� C20.
	char szUnderlyingSecurityID[8];							///< [sh][sz]���֤ȯ���� C6.
	char szUnderlyingSymbol[16];							///< [sh]����֤ȯ֤ȯ���� C8 .
	char szUnderlyingType[4];								///< [sh]���֤ȯ���� C3 (EBS�CETF��ASH�CA��)			///< [sz](ȡֵΪ29-������Ȩ��,30 -ETF��Ȩ)).
	char chOptionType;										///< [sh][sz]ŷʽ��ʽ C1 (��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A�� ��B��-��Ľ��ʽ).
	char chCallOrPut;										///< [sh][sz]�Ϲ��Ϲ� C1 �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��.
	long long iContractMultiplierUnit;						///< [sh][sz]��Լ��λ N11 (������Ȩ��Ϣ������ĺ�Լ��λ).
	unsigned int nExercisePrice;							///< [sh][sz]��Ȩ��Ȩ�� N11(4) (������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ���ȷ��0.1��).
	int  nStartDate;										///< [sh]�׸�������(YYYYMMDD) C8.
	int  nEndDate;											///< [sh][sz]�������(YYYYMMDD) C8.
	int  nExerciseDate;										///< [sh][sz]��Ȩ��Ȩ��(YYYYMMDD) C8.
	int  nDeliveryDate;										///< [sh]��Ȩ������(YYYYMMDD) C8.
	int  nExpireDate;										///< [sh][sz]��Ȩ������(YYYYMMDD) C8.
	char chUpdateVersion;									///< [sh]��Լ�汾�� C1.							///< [sz]���ʽ(DeliveryType) 'S'=֤ȯ���� 'C='�ֽ����
	long long iTotalLongPosition;							///< [sh][sz]��ǰ��Լδƽ���� N12 (��λ�� ���ţ�).
	unsigned int nSecurityClosePx;							///< [sh]��Լǰ���̼� N11(4) (�������̼ۣ��Ҷ��룬��ȷ����).
	unsigned int nSettlePrice;								///< [sh][sz]��Լǰ����� N11(4) (���ս���ۣ�������Ȩ��Ϣ��Ϊ������Ľ���ۣ���Լ����������д�ο��ۣ����Ҷ��룬��ȷ��0.1��).
	unsigned int nUnderlyingClosePx;						///< [sh]���֤ȯǰ���̼� N11(4) (��Ȩ���֤ȯ��Ȩ��Ϣ�������ǰ���̼۸��Ҷ��룬��ȷ��0.1��).
	char chPriceLimitType;									///< [sh]�ǵ����������� C1 (��N�����ǵ�����������). 	///< [sz]���ֶδ���������ͣ�ListType�� 1=Ʒ���¹�. 2=���ڼӹ�. 3=�����ӹ�. 4=�����ӹ�.
	unsigned int nUpLimitDailyPrice;						///< [sh][sz]�Ƿ����޼۸� N11(4) (������Ȩ��ͣ�۸񣬾�ȷ��0.1��).
	unsigned int nDownLimitDailyPrice;						///< [sh][sz]�������޼۸� N11(4) (������Ȩ��ͣ�۸񣬾�ȷ��0.1��).
	double dMarginUnit;										///< [sh]��λ��֤�� N16(2) (���ճ���һ�ź�Լ����Ҫ�ı�֤����������ȷ����).		///< [sz]������ÿ�ű�֤��(SellMargin)
	double dMarginRatioParam1;								///< [sh][sz]��֤������������һ N3 (��֤������������λ��%).
	double dMarginRatioParam2;								///< [sh][sz]��֤�������������� N3 (��֤������������λ��%).
	long long iRoundLot;             						///< [sh]������ N12 һ�ֶ�Ӧ�ĺ�Լ��.						///<[sz]��������(AdjustTimes).
	long long iLmtOrdMinFloor;       						///< [sh]�����޼��걨���� N12 (�����޼��걨���걨�������ޡ�).	///< [sz]����������(BuyQtyUpperLimit).
	long long iLmtOrdMaxFloor;       						///< [sh]�����޼��걨���� N12 (�����޼��걨���걨�������ޡ�).	///< [sz]����������(SellQtyUpperLimit).
	long long iMktOrdMinFloor;       						///< [sh]�����м��걨���� N12 (�����м��걨���걨�������ޡ�).	///< [sz]��������λ(BuyQtyUnit).
	long long iMktOrdMaxFloor;       						///< [sh]�����м��걨���� N12 (�����м��걨���걨�������ޡ�).	///< [sz]��������λ(SellQtyUnit).

	char szSecurityStatusFlag[8];							///< [sh][sz]. ֤ȯ״̬.

	///�Ϻ���sh����Ȩ��Լ״̬��Ϣ��ǩ C8 (���ֶ�Ϊ8λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո�).
	///��1λ����0����ʾ�ɿ��֣���1����ʾ�����������֣��������ҿ��֣������뿪�֡�
	///��2λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ�
	///��3λ����0����ʾδ�ٽ������գ���1����ʾ���뵽���ղ���10�������ա�
	///��4λ����0����ʾ����δ����������1����ʾ���10���������ں�Լ������������
	///��5λ����A����ʾ�����¹��Ƶĺ�Լ����E����ʾ�����ĺ�Լ����D����ʾ����ժ�Ƶĺ�Լ��

	///���ڡ�sz��֤ȯ״̬,������������ж��״̬ͬʱ������һ�������У����Ե�ǰ����Ϊÿ���ֽ���һ��״̬��
	///�������0ֵ���ֽ�ֵ��ʾ�����������һ���ֽ���0���ʾ���봦������״̬.
	///1-ͣ��
	///2-��Ȩ
	///3-��Ϣ
	///4-ST
	///5-*ST
	///6-��������
	///7-��˾������
	///8-�ָ���������
	///9-����ͶƱ
	///10-����������
	///11-��ͣ����
	///12-�����ɷ�����
	///13-��Լ����

	unsigned int nTickSize;          						///< [sh]��С���۵�λ N11(4) ��λ��Ԫ����ȷ��0.1��(����ͨѶ���۸����ʹ���) .
};

///< ��Ȩ�����
struct DFDAPI_OPTION_CODE
{
	//DFDAPI_CODEINFO basicCode;
	char szContractID[32];									///< ��Ȩ��Լ����
	char szUnderlyingSecurityID[32];						///< ���֤ȯ����
	char chCallOrPut;										///< �Ϲ��Ϲ�C1 �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
	int  nExerciseDate;										///< ��Ȩ��Ȩ�գ�YYYYMMDD    
	//�����ֶ�
	char chUnderlyingType;									///< ���֤ȯ����C3 0-A�� 1-ETF (EBS �C ETF�� ASH �C A ��)
	char chOptionType;										///< ŷʽ��ʽC1 ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
	char chPriceLimitType;									///< �ǵ�����������C1 ��N����ʾ���ǵ�����������, ��R����ʾ���ǵ�����������
	int  nContractMultiplierUnit;							///< ��Լ��λ,������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
	T_I64  nExercisePrice;								///< ��Ȩ��Ȩ��,������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
	int  nStartDate;										///< ��Ȩ�׸�������,YYYYMMDD
	int  nEndDate;											///< ��Ȩ�������/��Ȩ�գ�YYYYMMDD
	int  nExpireDate;										///< ��Ȩ�����գ�YYYYMMDD
};

union DFDAPI_EXCODE_INFO
{
	struct DFDAPI_OptionCodeInfo							///< futures options ר�� (nType >= 0x90 && nType <= 0x95),����Ȩ�����ֶ���Ч
	{
		char chContractID[32];								///< ��Ȩ��Լ����C19
		char szUnderlyingSecurityID[32];					///< ���֤ȯ����
		char chUnderlyingType;								///< ���֤ȯ����C3    0-A�� 1-ETF (EBS �C ETF�� ASH �C A ��)
		char chOptionType;									///< ŷʽ��ʽC1        ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
		char chCallOrPut;									///< �Ϲ��Ϲ�C1        �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
		char chPriceLimitType;								///< �ǵ�����������C1 ��N����ʾ���ǵ�����������, ��R����ʾ���ǵ�����������
		int  nContractMultiplierUnit;						///< ��Լ��λ,         ������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
		T_I64  nExercisePrice;							///< ��Ȩ��Ȩ��,       ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
		int  nStartDate;									///< ��Ȩ�׸�������,YYYYMMDD
		int  nEndDate;										///< ��Ȩ�������/��Ȩ�գ�YYYYMMDD
		int  nExerciseDate;									///< ��Ȩ��Ȩ�գ�YYYYMMDD
		int  nExpireDate;									///< ��Ȩ�����գ�YYYYMMDD
	}Option;
};

//struct DFDAPI_CODE_INFO
//{
//	int  nMarketID;											///< ������ID,��������
//	int  nDataLevel;										///< ����Level
//	int  nFlag;												///< ������Դ
//	int  nType;												///< ֤ȯ����
//	char chCode[32];										///< ֤ȯ����
//	char chName[64];										///< ����֤ȯ����
//	DFDAPI_EXCODE_INFO exCodeInfo;
//	char chWindType[8];										///< windType : FUR(�ڻ�),����
//	int nLotSize;											///< ��������,�۹���Ч
//};

struct DFDAPI_SZBaseETF
{
	char szVersion[8];										///< �汾��.
	int nMarketType;										///< �г�����.
	int nETFType;											///< ETF���ͣ��μ�MDData_inner::EETFType����.
	char szSecurityID[16];									///< ETF����.
	char szPurchaseAndRedem[16];							///< �깺��ش���.
	char szSecuritySymbol[32];								///< ETF��ơ�SZ��.
	char szFundManagementCompany[64];						///< ����˾����.
	char szUnderlyingSecurityID[16];						///< ���ָ������.
	int nUnderlyingSecurityMarketType;						///< ���ָ�������г�����.
	unsigned int unCreationRedemptionUnit;					///< ��С�깺��ص�λ,��Ӧ�� ETF ������Ŀǰֻ��Ϊ������.
	double dEstimateCashComponent;							///< Ԥ���ֽ���.
	double dMaxCashRatio;									///< ����ֽ��������.
	char chPublish;											///< �Ƿ񷢲� IOPV,Y=��,N = ��.
	char chCreation;										///< �Ƿ������깺,Y=��,N = ��.
	char chRedemption;										///< �Ƿ��������,Y=��,N = ��.
	unsigned int unRecordNum;								///< ���гɷ�֤ȯ��Ŀ.
	unsigned int unTotalRecordNum;							///< ���гɷ�֤ȯ��Ŀ.
	int nTradingDay;										///< ������.
	int nPreTradingDay;										///< ǰ������.
	double dCashComponent;									///< �ֽ����, T-X ���깺��ػ�׼��λ���ֽ����.
	double dNAVperCU;										///< �깺��ػ�׼��λ��ֵ, T - X ���깺��ػ�׼��λ��ֵ.
	double dNAV;											///< ��λ��ֵ,T-X �ջ���ĵ�λ��ֵ.
	double dDividendPerCU;									///< T ���깺��ػ�׼��λ�ĺ������.
	int nCreationLimit;										///< �����ۼƿ��깺�Ļ���ݶ���	�ޣ�Ϊ 0 ��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nRedemptionLimit;									///< �����ۼƿ���صĻ���ݶ����ޣ�Ϊ 0 ��ʾû�����ƣ� Ŀǰֻ��Ϊ����.
	int nCreationLimitPerUser;								///< ����֤ȯ�˻������ۼƿ��깺�Ļ���ݶ����ޣ�Ϊ 0 ��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nRedemptionLimitPerUser;							///< ����֤ȯ�˻������ۼƿ���صĻ���ݶ����ޣ�Ϊ 0 ��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nNetCreationLimit;									///< ���쾻�깺�Ļ���ݶ����ޣ�Ϊ 0��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nNetRedemptionLimit;								///< ���쾻��صĻ���ݶ����ޣ�Ϊ 0��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nNetCreationLimitPerUser;							///< ����֤ȯ�˻����쾻�깺�Ļ���ݶ����ޣ�Ϊ 0 ��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
	int nNetRedemptionLimitPerUser;							///< ����֤ȯ�˻����쾻��صĻ���ݶ����ޣ�Ϊ 0 ��ʾû�����ƣ�Ŀǰֻ��Ϊ����.
};

struct DFDAPI_SZBaseETFComponent
{
	int nMarketType;										///< �г�����.
	char szSecurityID[16];									///< ֤ȯ����.
	char szSecuritySymbol[32];								///< ֤ȯ���.
	unsigned int unComponentShare;							///< �ɷ�����.
	double dPremiumRatio;									///< ��۱���.���ֶ�ֻ���ֽ������־Ϊ��1��ʱ����Ч.
	double dCreationCashSubstitute;							///< �깺������.���ֶ�ֻ�е������־Ϊ��2��ʱ����Ч.
	double dRedemptionCashSubstitute;						///< ���������;���ڿ羳 ETF�����г� ETF���ƽ� ETF ���ֽ�ծȯ ETF�����ֶ�Ϊ 0.0000;���ֶ�ֻ�е������־Ϊ��2��ʱ����Ч.

	///< 0 = ��ֹ�ֽ������������֤ȯ��
	///< 1 = ���Խ����ֽ����������֤ȯ��֤ȯ����ʱ�������ֽ������
	///< 2 = �������ֽ����
	char chSubstituteFlag;									///< �ֽ������־.
};


struct DFDAPI_SHBaseETF
{
	int nMarketType;										///< �г�����.
	int nETFType;											///< ETF���ͣ��μ�MDData_inner::EETFType����.
	char szSecurityID[16];									///< ETFһ���г��깺��ش���.
	char szPurchaseAndRedem[16];							///< �깺��ش���.
	unsigned int unCreationRedemptionUnit;					///< ��С�깺��ص�λ,��Ӧ�� ETF ����.
	double dMaxCashRatio;									///< ����ֽ��������.
	char chPublish;											///< �Ƿ񷢲� IOPV,Y=��,N = ��.��Y��ʾ����IOPV��ͨ�����鷢����N��ʾ������IOPVҲ����ͨ�����鷢��)
	char chCreation;										///< �Ƿ������깺,Y=��,N = ��.
	char chRedemption;										///< �Ƿ��������,Y=��,N = ��.
	unsigned int unRecordNum;								///< �ɷ�֤ȯ����.
	double dEstimateCashComponent;							///< Ԥ���ֽ���.
	int nTradingDay;										///< ������.
	int nPreTradingDay;										///< ǰ������.
	double dCashComponent;									///< �ֽ����, T-X ���깺��ػ�׼��λ���ֽ����.
	double dNAVperCU;										///< �깺��ػ�׼��λ��ֵ, T - X ���깺��ػ�׼��λ��ֵ.
	double dNAV;											///< ��λ��ֵ,T-X �ջ���ĵ�λ��ֵ.
};

struct DFDAPI_SHBaseETFComponent
{
	int nMarketType;										///< �г�����.
	char szSecurityID[16];									///< ֤ȯ����.
	char szSecuritySymbol[32];								///< ֤ȯ���.
	unsigned int unComponentShare;							///< �ɷ�����.
	double dPremiumRatio;									///< ��۱���.�����־Ϊ1��3��5ʱ�����ֶα����ȡֵ��ΧΪ[0, 1��.
	double dCashSubstitute;									///< ����ܽ����.�����־Ϊ2��3��4��5��6ʱ���ֶα���ұ�����ڵ���0.

	///< 0��ʾ��֤ȯΪ����֤ȯ����ֹ�ֽ������������֤ȯ��
	///< 1��ʾ��֤ȯΪ����֤ȯ�����Խ����ֽ����������֤ȯ��֤ȯ����Ļ����ֽ������
	///< 2��ʾ��֤ȯΪ����֤ȯ���������ֽ������
	///< 3��ʾ��֤ȯΪ����֤ȯ���˲��ֽ������
	///< 4��ʾ��֤ȯΪ����֤ȯ�������ֽ������
	///< 5��ʾ�ǻ����г��ɷ�֤ȯ�˲��ֽ������
	///< 6��ʾ�ǻ����г��ɷ�֤ȯ�����ֽ������
	char chSubstituteFlag;									///< �ֽ������־.
};


/*------------------------------------------------��������------------------------------------------------------------------*/
//������������Ϣ
struct DFDAPI_SERVER_INFO
{
	char szIp[32];											///< IP
	short nPort;											///< �˿�
	char szUser[64];										///< �û���
	char szPwd[64];											///< ����
	bool bDoMain;											///< �Ƿ�ʹ������
};

struct DFDAPI_OPEN_CONNECT_SET
{
	DFDAPI_SERVER_INFO	ServerInfo[JGAPI_SERVERINFO_MAX];	///< ��������Ϣ
	unsigned int unServerNum;								///< ����������
	dfdapi_data_callback data_fun;							///< ������Ϣ����ص�
	dfdapi_notice_callback notice_fun;						///< ϵͳ��Ϣ֪ͨ�ص�
	///< �������� ע�⣺�������г������ģ�����ÿ���г����붩���г�����룬ֻ�����г������ʹ��г�ȫ������
	const char* szMarkets;									///< �г����ģ�����"SZ;SH;CF;SHF;DCE;SHF"����Ҫ���ĵ��г��б��ԡ�;���ָ�.
	const char* szSubScriptions;							///< ���붩�ģ�����"600000.sh;IH1711.cf;000001.sz"����Ҫ���ĵĹ�Ʊ���ԡ�;���ָ�.
	const char* szTypeFlags;								///< �������Ͷ��ģ�֧�ֶ���3������TRANSACTION;ORDER;ORDERQUEUE����ע�⣺���������κ�ʱ�򶼷��ͣ�����Ҫ����! �μ�enum DATA_TYPE_FLAG.
	unsigned int nTime;										///< Ϊ0������ʵʱ���飬Ϊ0xffffffff��ͷ����.
	unsigned int nConnectionID;								///< ����ID�����ӻص���Ϣ�ĸ��ӽṹ DFDAPI_CONNECT_RESULT�� ��������ID����ϢͷҲ�������ID.
};

struct DFDAPI_PROXY_SET
{
	DFDAPI_PROXY_TYPE nProxyType;							///< ��������
	char szProxyHostIp[32];									///< ����IP
	char szProxyPort[8];									///< ����˿�
	char szProxyUser[32];									///< �����û���
	char szProxyPwd[32];									///< ��������
};
/*------------------------------------------------��������------------------------------------------------------------------*/

#pragma pack(pop)
#endif