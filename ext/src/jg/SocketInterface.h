
#ifndef __SOCKET_INTERFACE_H__
#define __SOCKET_INTERFACE_H__

#include <string>
#include <functional>


#define	_use_net_per_test_		0


/************************************************************************/
/* 用于连接参数                                                         */
/************************************************************************/
typedef unsigned long long SOCKET_ID;

/************************************************************************
名称：SSL 验证模式
描述：SSL 验证模式选项，SSL_VM_PEER 可以和后面两个选项组合一起
************************************************************************/
enum EnSSLVerifyMode
{
	SSL_VM_NONE					= 0x00,	// SSL_VERIFY_NONE
	SSL_VM_PEER					= 0x01,	// SSL_VERIFY_PEER
	SSL_VM_FAIL_IF_NO_PEER_CERT = 0x02,	// SSL_VERIFY_FAIL_IF_NO_PEER_CERT
	SSL_VM_CLIENT_ONCE			= 0x04,	// SSL_VERIFY_CLIENT_ONCE
};

#if _use_net_per_test_
struct STPerParamData
{
	__int64 iQpTime;
	__int64 iPkgCnt;


	STPerParamData()
	{
		iQpTime = 0;
		iPkgCnt = 0;
	}

	~STPerParamData(){}
};
#endif


/************************************************************************/
/* ITcpServer中的监听基类，需自己接收数据解包。							*/
/* 使用时需继承该类，将类指针通过TcpServer_Creator传入库内部            */
/* 需保证在通讯未停止前，该类实例未销毁						            */
/************************************************************************/
class ITcpServerListener
{
public:
	ITcpServerListener(){};
	virtual ~ITcpServerListener(){};
	/************************************************************************/
	/* 接收连接                                                             */
	/************************************************************************/
	virtual bool OnAccept(SOCKET_ID ulSocketId, const std::string& strIp, unsigned short uPort) = 0;
#if _use_net_per_test_
	/************************************************************************/
	/* 接收网络数据                                                         */
	/************************************************************************/
	virtual void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
	/************************************************************************/
	/* 已发送数据回馈                                                       */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
#else
	virtual void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;

	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
#endif
	/************************************************************************/
	/* 关闭链接                                                             */
	/************************************************************************/
	virtual void OnClose(SOCKET_ID ulSocketId) = 0;
	/************************************************************************/
	/* 错误回调                                                                     */
	/************************************************************************/
	virtual void OnError(SOCKET_ID ulSocketId, const std::string& strErrorInfo) = 0;
	/************************************************************************/
	/* 握手成功回调                                                                     */
	/************************************************************************/
	virtual void OnHandShake(SOCKET_ID ulSocketId) = 0;
};


/************************************************************************/
/* ITcpServer中的扩展监听类，继承该类,接收到数据返回完整指令包,
不需要用户自己解包接收的数据*/
/* 使用时需继承该类，将类指针通过TcpServer_Creator传入库内部            */
/* 需保证在通讯未停止前，该类实例未销毁						            */
/************************************************************************/
class ITcpPackServerListener : public ITcpServerListener
{
public:
	ITcpPackServerListener(){};
	virtual ~ITcpPackServerListener(){};
	/************************************************************************/
	/* 接收连接                                                             */
	/************************************************************************/
	virtual bool OnAccept(SOCKET_ID ulSocketId, const std::string& strIp, unsigned short uPort) = 0;
#if _use_net_per_test_
	/************************************************************************/
	/* 接收网络数据                                                         */
	/************************************************************************/
	void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam){};
	/************************************************************************/
	/* 已发送数据回馈                                                       */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
#else
	//该接收数据回调不会收到数据，由OnPack()接收数据包
	void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen){};
	//接收一个完整指令包
	virtual void OnPacket(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;

	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
#endif
	/************************************************************************/
	/* 关闭链接                                                             */
	/************************************************************************/
	virtual void OnClose(SOCKET_ID ulSocketId) = 0;
	/************************************************************************/
	/* 错误回调                                                                     */
	/************************************************************************/
	virtual void OnError(SOCKET_ID ulSocketId, const std::string& strErrorInfo) = 0;
	/************************************************************************/
	/* 握手成功回调                                                                     */
	/************************************************************************/
	virtual void OnHandShake(SOCKET_ID ulSocketId) = 0;
};

/************************************************************************/
/* TCPServer服务操作类型，使用TcpServer_Creator获取或者销毁             */
/************************************************************************/
class ITcpServer
{
public:
	/************************************************************************/
	/* 启动通讯服务并执行监听网络操作                                       */
	/* port为监听端口					                                    */
	/* ip为监听IP、域名、计算机名称					                        */
	/* true表示启动成功，false表示失败，									*/
	/* 如（virtual void OnError(const std::string& strError)）返回错误，	*/
	/* 则整个通讯出错														*/
	/************************************************************************/
	virtual bool Start(unsigned short port, const std::string& ip = std::string()) = 0;
	/************************************************************************/
	/* 停止通讯操作                                                         */
	/* true表示停止成功，false表示失败，									*/
	/************************************************************************/
	virtual bool Stop() = 0;
	/************************************************************************/
	/************************************************************************/
	/* 设置服务线程个数（至少大于1）                                        */
	/************************************************************************/
	virtual bool SetWorkThreadNum(unsigned int uiNum) = 0;
	/* 向指定连接发送数据，为异步操作                                       */
	/* 异步执行成功可在异步回调OnSend中获取该数据							*/
	/* 异步执行失败可在异步回调OnError中获取错误信息						*/
	/* ulSocketId为OnAccept返回连接标识                                     */
	/* pData为发送数据首地址				                                */
	/* nLen为发送数据长度													*/
	/* true表示启动成功，false表示失败，									*/
	/************************************************************************/
	virtual bool Send(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
	/************************************************************************/
	/* 关闭指定连接，为异步操作	                                            */
	/* 异步执行成功可在异步回调OnError中获取判断该连接是否断开				*/
	/* ulSocketId为OnAccept返回连接标识                                     */
	/* true表示启动成功，false表示失败，									*/
	/************************************************************************/
	virtual bool CloseSocket(SOCKET_ID ulSocketId) = 0;
	/************************************************************************/
	/* 关闭所有连接                                                          */
	/************************************************************************/
	virtual void CloseAllSocket() = 0;
	/* 设置SSL 参数                                                         */
	/************************************************************************/
	/* sz_ca_cert ca证书													*/
	/* sz_private_key 服务器证书私钥										*/
	/* sz_dh_file    dh随机数文件											*/
	/* sz_us_ca_cert 服务器证书				                                */
	/* szKeyPwd   证书私钥密码												*/
	/* bSSLVerifyNone true标识不用ca校验，false表示用ca证书校验服务器证书   */
	virtual void SetSSLParamer(const char* sz_ca_cert, const char* sz_private_key = nullptr, const char* sz_dh_file = nullptr, const char* sz_us_ca_cert = nullptr, const char* szKeyPwd = nullptr, bool bSSLVerifyNone = false) = 0;
public:
	virtual ~ITcpServer(){};
};

/************************************************************************/
/* ITcpClient中的监听基类，接收数据需要自己解包							*/
/* 使用时需继承该类，将类指针通过TcpClient_Creator传入库内部            */
/* 需保证在通讯未停止前，该类实例未销毁						            */
/************************************************************************/
class ITcpClientListener
{
public:
	ITcpClientListener(){};
	virtual ~ITcpClientListener(){};
	/************************************************************************/
	/* 连接成功回调                                                        */
	/************************************************************************/
	virtual void OnConnect(SOCKET_ID ulSocketId, const std::string& strRemoteIP, unsigned short uRemotePort, const std::string& strLocalIP, unsigned short uLocalPort) = 0;
#if _use_net_per_test_
	/************************************************************************/
	/* 接收网络数据回调                                                         */
	/************************************************************************/
	virtual void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
	/************************************************************************/
	/* 发送数据成功回调                                                     */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
#else
	/************************************************************************/
	/* 接收网络数据回调                                                         */
	/************************************************************************/
	virtual void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
	/************************************************************************/
	/* 发送数据成功回调                                                     */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
#endif
	/************************************************************************/
	/* 已关闭套接字回调                                                             */
	/************************************************************************/
	virtual void OnClose(SOCKET_ID ulSocketId) = 0 ;
	/************************************************************************/
	/* 错误回调                                                                     */
	/************************************************************************/
	virtual void OnError(SOCKET_ID ulSocketId,const std::string& strErrorInfo) = 0;
	/************************************************************************/
	/* 握手成功回调                                                                     */
	/************************************************************************/
	virtual void OnHandShake(SOCKET_ID ulSocketId) = 0 ;
};

/************************************************************************/
/* ITcpClient中的监听基类，继承该基类接收数据,回调一个完整的指令包   	*/
/* 使用时需继承该类，将类指针通过TcpClient_Creator传入库内部            */
/* 需保证在通讯未停止前，该类实例未销毁						            */
/************************************************************************/
class ITcpPackClientListener
{
public:
	ITcpPackClientListener(){};
	virtual ~ITcpPackClientListener(){};
	/************************************************************************/
	/* 连接成功回调                                                        */
	/************************************************************************/
	virtual void OnConnect(SOCKET_ID ulSocketId, const std::string& strRemoteIP, unsigned short uRemotePort, const std::string& strLocalIP, unsigned short uLocalPort) = 0;
#if _use_net_per_test_
	/************************************************************************/
	/* 接收网络数据回调                                                         */
	/************************************************************************/
	void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam){};
	/************************************************************************/
	/* 发送数据成功回调                                                     */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen, const STPerParamData& tPerParam) = 0;
#else
	/************************************************************************/
	/* 该回调函数不会接收到数据，由OnPack()返回数据。                                                       */
	/************************************************************************/
	void OnRecieve(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) {};
	/************************************************************************/
	/* 发送数据成功回调                                                     */
	/************************************************************************/
	virtual void OnSend(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
#endif
	/************************************************************************/
	/* 已关闭套接字回调                                                             */
	/************************************************************************/
	virtual void OnClose(SOCKET_ID ulSocketId) = 0;
	/************************************************************************/
	/* 错误回调                                                                     */
	/************************************************************************/
	virtual void OnError(SOCKET_ID ulSocketId, const std::string& strErrorInfo) = 0;
	/************************************************************************/
	/* 握手成功回调                                                                     */
	/************************************************************************/
	virtual void OnHandShake(SOCKET_ID ulSocketId) = 0;
	/************************************************************************/
	/* 回调一个完整指令包                                                               */
	/************************************************************************/
	virtual void OnPacket(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;
};

/************************************************************************/
/* TcpClient服务操作类型，使用TcpClient_Creator获取或者销毁             */
/************************************************************************/
class ITcpClient
{
public:
	/************************************************************************/
	/* 启动通讯服务并执行监听网络操作                                       */
	/* true表示启动成功，false表示失败，									*/
	/* 如（virtual void OnError(const std::string& strError)）返回错误，	*/
	/* 则整个通讯出错														*/
	/************************************************************************/
	virtual bool Start() = 0;

	/************************************************************************/
	/* 停止通讯操作                                                         */
	/* true表示停止成功，false表示失败，									*/
	/************************************************************************/
	virtual bool Stop() = 0;
	/************************************************************************/
	/* 设置服务线程个数（至少大于1）                                        */
	/************************************************************************/
	virtual bool SetWorkThreadNum(unsigned int uiNum) = 0;

	/************************************************************************/
	/* 创建客户连接并不执行连接操作                                         */
	/* 返回连接标识，0表示失败												*/
	/************************************************************************/
	virtual SOCKET_ID CreateClient() = 0;

	/************************************************************************/
	/* 销毁连接																*/
	/* 返回true表示成功，false表示失败										*/
	/************************************************************************/
	virtual bool DestroyClient(SOCKET_ID ulSocketId = 0) = 0;
	/************************************************************************/
	/* 连接服务，为异步操作													*/
	/* 异步执行成功可在异步回调OnConnect中获取连接参数						*/
	/* 异步执行失败可在异步回调OnError中获取错误信息						*/
	/* ulSocketId为CreateClient返回参数										*/
	/* uServerPort为远程服务端口											*/
	/* strServerIp为远程服务IP、域名、计算器名称（不可使用127.0.0.1）		*/
	/* strLocalIp为本机IP、域名、计算器名称（不可使用127.0.0.1）			*/
	/* bAsyncConnect（当前仅支持异步连接操作）								*/
	/* 返回true表示成功，false表示失败										*/
	/************************************************************************/
	virtual bool Connect(SOCKET_ID ulSocketId, unsigned short uServerPort,
		const std::string& strServerIp, bool bdomain ,const std::string &strLocalIp/* = std::string()*/, bool bAsyncConnect/* = true*/) = 0;

	/************************************************************************/
	/* 向指定连接发送数据，为异步操作                                       */
	/* 异步执行成功可在异步回调OnSend中获取该数据							*/
	/* 异步执行失败可在异步回调OnError中获取错误信息						*/
	/* ulSocketId为OnAccept返回连接标识                                     */
	/* pData为发送数据首地址				                                */
	/* nLen为发送数据长度													*/
	/* true表示启动成功，false表示失败，									*/
	/************************************************************************/
	virtual bool Send(SOCKET_ID ulSocketId, const char* pData, unsigned int nLen) = 0;

	/************************************************************************/
	/* 关闭指定连接，为异步操作	                                            */
	/* 异步执行成功可在异步回调OnError中获取判断该连接是否断开				*/
	/* ulSocketId为CreateClient返回连接标识                                 */
	/* true表示启动成功，false表示失败，									*/
	/************************************************************************/
	virtual bool Disconnect(SOCKET_ID ulSocketId = 0) = 0;
	/************************************************************************/
	/* 设置SSL 参数                                                                    */
	/************************************************************************/
	virtual bool SetSSLParamer(const char* sz_ca_cert, const char* sz_private_key = nullptr, const char* sz_dh_file = nullptr, const char* sz_us_ca_cert = nullptr, const char* szKeyPwd = nullptr) = 0;
public:
	virtual ~ITcpClient(){};
};

#endif //__SOCKET_INTERFACE_H__