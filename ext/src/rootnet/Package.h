#ifdef _MSC_VER
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 4290 4251 4183)
#endif

#include "PackData.h"

#ifdef  WIN32
#ifdef __cplusplus 
#define DLL_EXPORT_C_DECL extern "C" __declspec(dllexport)
#define DLL_IMPORT_C_DECL extern "C" __declspec(dllimport)
#define DLL_EXPORT_DECL extern __declspec(dllexport)
#define DLL_IMPORT_DECL extern __declspec(dllimport)
#define DLL_EXPORT_CLASS_DECL __declspec(dllexport)
#define DLL_IMPORT_CLASS_DECL __declspec(dllimport)
#else
#define DLL_EXPORT_DECL __declspec(dllexport)
#define DLL_IMPORT_DECL __declspec(dllimport)
#endif
#else
#ifdef __cplusplus
#define DLL_EXPORT_C_DECL extern "C"
#define DLL_IMPORT_C_DECL extern "C"
#define DLL_EXPORT_DECL extern
#define DLL_IMPORT_DECL extern
#define DLL_EXPORT_CLASS_DECL
#define DLL_IMPORT_CLASS_DECL
#else
#define DLL_EXPORT_DECL extern
#define DLL_IMPORT_DECL extern
#endif
#endif

#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

typedef struct sockaddr SOCKADDR;
typedef u_int           SOCKET;

#include <map>
#include <string>
using namespace std;
namespace GWDPApi
{
class CPackData;
class DLL_EXPORT_CLASS_DECL CPackage
{
public:
	CPackage();
	virtual ~CPackage();

	//初始化
	bool Init();
	bool UnInit();
	bool Initialize();

	string  GetVersion();

	//设置请求功能号
	void SetFunctionCode(const char* strFunctionCode);

	//设置包头flag
	//flags = 0	在首次查询或者其他操作。
    //flags = 2 	表示连续请求的后续请求（请求时使用），一般用于查询请求的“下一页”时使用。
	void SetFlags(short nNewValue);

	//设置请求包序号
	void SetSerialno(const char* strSerialno);

	//设置请求参数，iRecNo表示请求域号，sFieldName表示数据项的字典名称，sFieldValue表示具体的参数值
	bool SetValue(int iRecNo, const char* sFieldName, const char* sFieldValue);

	//清空发送包数据
	void ClearSendPackage();

	bool ExchangeMessage();
	bool ExchangeMessageEx(char* byBuff, int lLen);
	
	//发送数据到服务器
    bool SendMessage(SOCKET socket, char* byteMessage,int iLen);

    //接收应答报文
    int ReceiveMessage(SOCKET socket,char* byRecvMsg,int iLen);

	//获取解析后的应答数据的某个字段的值，iRecNo表示域号，sFieldName表示请求的字段名称
	const char*  GetValue(int iRecNo,const char* sFieldName);

	//把缓冲数据解析成一个一个的字段，供访问
    bool ChangeToStruct(char* byBuf, int lLen);

	//把设置的请求包字典组织成请求数据报文
    char* ChangeToStream(bool bCompressFlag);

	//压缩后再组包
    char* CompressChangeToStream(char* byBuff);

private:
	//接收应答包的缓冲区
	char* m_pBuf;
	int m_nRawSize;
	int m_nBufSize;

	//加密类型
	string m_strEncryptType;

	//加密因子
	string m_strEncryptKey;
	string m_strAesGenKey;

	//导入授权文件
	bool LoadAuthFunc();

	//导入配置文件
	bool LoadGWConfig();

	//申请接收缓冲区
	char* _GetBuffer(int nBufSize = 2048);

	//判断是否最后包
	bool _IsLastPack(char* header);

	void socket_init();
	void socket_close( int s );

	//获取加密算法及密钥
	bool GetEncryptMode();

	//获取加密因子
	bool GetEncryptKey();

	//加密
	string Encrypt(char* password, char* plainText);

	//解密
	string decrypt(char* password, char* plainText);

//public:	
	//请求数据
	CPackData oReqData;
	
	//应答数据
	CPackData oRespData;
	
	SOCKET	m_oSocket;

	//授权功能号列表
    typedef std::map<string/*DictId*/, string/*value*/> AUTH_FUNC;	
	AUTH_FUNC m_oAuthFunc;

	typedef struct GWConfig{
		int iConnectSvr;
		int iTimeout;
		int iQueryTimeOut;
		string oGwSvrIp[5];
		int    iGwSvrPort[5];
		GWConfig()
		{
			iConnectSvr  = 0;
			iTimeout     = 30000;
			iQueryTimeOut= 30000;
			for(int i=0;i<5;i++)
			{
				oGwSvrIp[i] = "-1";
				iGwSvrPort[i] = 0;
			}
		}
	} ;

	//配置项
	GWConfig m_oGwCfg;
};
}