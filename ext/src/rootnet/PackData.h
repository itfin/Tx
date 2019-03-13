#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 4290 )
#endif

#include "GWDictionary.h"

#include <map>
#include <string>
using namespace std;
namespace GWDPApi
{
class CPackData
{
public:
	CPackData();
	//~CPackData();
	
	//包头初始化
	void HeadInit();

	//清空缓冲
	void Clear();

	//清空发送包数据
	void ClearSendPackage();

	//清空应答包数据
	void ClearRecvPackage();

	//设置请求功能号
    void SetFunctionCode(const char* sFuncCode);

	//设置包头flag
	//flags = 0	在首次查询或者其他操作。
	//flags = 2 	表示连续请求的后续请求（请求时使用），一般用于查询请求的“下一页”时使用。
    void SetFlags(short Flag);

    //设置包头Serialno
    void SetSerialno(const char* sSerialno);

	//设置请求参数，iRecNo表示请求域号，sFieldName表示数据项的字典名称，sFieldValue表示具体的参数值
    bool SetValue(int iRecNo, const char * sFieldName, const char * sFieldValue);

	//设置二进制数据的请求参数，iRecNo表示请求域号，sFieldName表示数据项的字典名称，sFieldValue表示具体的参数值
    bool SetValueBin(int iRecNo, const char * sFieldName, long lpBuff, int lLen);

	//获取解析后的应答数据的某个字段的值，iRecNo表示域号，sFieldName表示请求的字段名称
    string GetValue(int iRecNo, const char * sFieldName);

	//获取二进制数据字段的长度
    long GetBinLength(int iRecNo, const char * sFieldName);

	//获取二进制数据字段的内容
    char* GetValueBin(int iRecNo, const char * sFieldName);

	//获取请求包的长度
    long GetPackageLen();

	//设置应答参数，iRecNo表示请求域号，sFieldName表示数据项的字典名称，sFieldValue表示具体的参数值
	bool SetRespValue(int iRecNo, const char * sFieldName, const char * sFieldValue);
	
	//把缓冲数据解析成一个一个的字段，供访问
    bool ChangeToStruct(char* lpRevBuf,int lLen);

	//把设置的请求包字典组织成请求数据报文
    char* ChangeToStream();

	//计算请求包长度
    long CalculateLengthInt();

	//设置请求包头信息
    void SetPktHead(char* Buff);

	//获取请求报文的功能号
    string GetFunctionCode();

	//获取请求报文的flag标志
    short GetFlag();

	//获取解析后的应答数据的某个字段的值，iRecNo表示域号，sFieldName表示请求的字段名称
    string GetReqValue(int iRecNo, const char * sFieldName);

	//校验包头
	bool CheckHeadVerify(char* chHeadBuf);

	//生成并填充包头校验位
	void CalculateHeadVerify(char* chHeadBuf);

	//
	int CRC(int crc, int c);

	//
	short CRC16(char* lpszData,long nDataLen);

	//获取MAC地址
	void GetMac_Windows();
	void GetMac_Linux();

	//清除应答包中的BIN数据缓冲
	void ReleaseRspBinBuf();
		
public:
	// 数据包类型
	enum StockDataType
	{
		// 发送数据包类型
		Send = 0,
			
        // 接收数据包类型
        Receive = 1
    };

	typedef struct
	{
		short	pktlen;
		char	flag;
		char	MAC[12];
		char	serial[8];
		char	optcode[8];
		char	checksum[2];
	}HEAD;
	
	typedef struct
	{
		//bin类型值
		char* Buff;
		
		//bin类型长度
        int iBuffLen;
	}FieldValue;

    typedef std::map<string/*DictName*/, std::pair<string/*strValue*/,FieldValue/*DictType*/> > FIELDS;	

	typedef struct
	{
		//域长度
		short RecordLen;
		
		//域中的字段
		FIELDS Fields; 
	}RECORD;

	//数据报文包头
	HEAD m_oPackHead;

	//MAC地址
	string  m_strMac;

	//数据包长度，由于包头定义包长度为ushort，长度只能是65535，实际传输包长度可能大于65535，
	//计算包长度时不能用包头中的长度，增加一个变量保存包长,计算时遍历每个字段计算包长度
    int m_iReqPackLen;

	//请求数据包（列表）
	//key=recordNo
	//key1=dictId
	//string=value
	typedef std::map<int/*RecordNo*/ , RECORD/*Record*/> RequestData;
	RequestData m_oReqData;

	//应答数据包（列表）
	//key=recordNo
	//key1=dictId
	//string=value
    typedef std::map<int/*RecordNo*/ , RECORD> ResponsData;
	ResponsData m_oRspData;

};
}