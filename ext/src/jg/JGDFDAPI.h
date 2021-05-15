#ifndef __JGDFDAPI_H__
#define __JGDFDAPI_H__

#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS)
#ifdef COM_JGDFDAPI_EXPORT
#define COM_JGDFDAPI __declspec(dllexport)
#else
#define COM_JGDFDAPI __declspec(dllimport)
#endif
#else
#define COM_JGDFDAPI __attribute((visibility("default")))
#endif

#include "JGDFDApi_DataDef.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*
	* 创建生成dump文件.如不需要该功能，可不调用.
	*/
	COM_JGDFDAPI void DFDAPI_CreateDumpFile();

	/*
	* 获取接口版本信息
	*/
	COM_JGDFDAPI const char* DFDAPI_GetVersion();


	/*
	* 初始化环境.
	* return 成功：DFDAPI_ERR_SUCCESS 失败：DFDAPI_ERR_UNINITIALIZE.
	*/
	COM_JGDFDAPI int DFDAPI_Init();


	/*
	* 设置环境变量 一个变量类型设置一次，可以不设置使用默认值，默认值参考DFDAPI_EnvSet
	* @param[in] eSetEnv 环境变量设置项
	* @param[in] unEnvValue 环境变量设置值
	* return 成功：DFDAPI_ERR_SUCCESS 未知参数：DFDAPI_ERR_INVALID_PARAMS
	*/
	int COM_JGDFDAPI DFDAPI_SetEnv(const DFDAPI_SET_ENVIRONMENT &eSetEnv, const unsigned int &unEnvValue);


	/*
	* 打开服务链接
	* @param[in] pConnectSet 连接参数设置，在调用期间会通过回调收到连接登录获取代码表结果消息
	* 如果断开连接会将错误码放入pErrCode
	* @param[in] pErrCode 错误码 
	* return 成功返回一个实例标识 否则返回NULL
	*/
	VHANDLE COM_JGDFDAPI DFDAPI_OpenConnect(DFDAPI_OPEN_CONNECT_SET *&pConnectSet, DFDAPI_ERR_CODE *pErrCode);


	/*
	* 通过代理打开服务链接[暂时未实现]
	* @param[in] pConnectSet 连接参数设置，在调用期间会通过回调收到连接登录获取代码表结果消息
	* 如果断开连接会将错误码放入pErrCode
	* @param[in] pProxySet 代理设置
	* @param[in] pErrCode 错误码
	* return 成功返回一个实例标识
	*/
	VHANDLE COM_JGDFDAPI DFDAPI_OpenConnectByProxy(DFDAPI_OPEN_CONNECT_SET *&pConnectSet, DFDAPI_PROXY_SET *&pProxySet, DFDAPI_ERR_CODE *pErrCode);
		
	
	/*
	* 获取指定市场代码表
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy返回实例标识
	* @param[in] szMarket格式为：market-level-source(SHF-1-0)
	* @param[in|out] pCodeTable 代码表数据
	* @param[in|out] pItems 代码表条数
	* return DFDAPI_ERR_SUCCESS:成功 其他:失败
	*/	
	int COM_JGDFDAPI DFDAPI_GetCodeTable(VHANDLE vHandle, const char* szMarket, DFDAPI_CODEINFO* &pCodeTable, unsigned int &nItems);

	
	/*
	* 获取期权基本信息
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy返回实例标识
	* @param[in|out] pBasicInfo 数据
	* @param[in|out] pItems 条数
	* return DFDAPI_ERR_SUCCESS:成功 其他:失败
	*/
	int COM_JGDFDAPI DFDAPI_GetOptionBasicInfoData(VHANDLE vHandle, const char* szMarket, DFDAPI_BASICINFO_OPTION* &pBasicInfo, unsigned int &nItems);

	/*
	* 释放内存
	*/
	void COM_JGDFDAPI DFDAPI_FreeArr(void *pArr);
	
	
	/*
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy返回实例标识
	* @param[in] szSubScriptions 订阅代码 nSubStyle为全市场订阅可空
	* @param[in] szSubScriptions 订阅类型 
	* return 0:订阅接口调用成功 其他:失败
	*/
	int COM_JGDFDAPI DFDAPI_SetSubscription(VHANDLE vHandle, const SUBSCRIPTION_STYLE& eSubStyle, const int& nItems, const DFDAPI_CODEINFO* pSubScriptions);
		
	
	/*
	* 获取ETF代码清单文件.
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy返回实例标识
	* return 0:接口调用成功 其他:失败
	*/
	int COM_JGDFDAPI DFDAPI_ReqETFListData(VHANDLE vHandle, DFDAPI_ETFLISTFILE** &ppETFListData, unsigned int* pItems);

	/*
	* 释放内存.
	* return 0:接口调用成功 其他:失败
	*/
	int COM_JGDFDAPI DFDAPI_FreeETFListData(DFDAPI_ETFLISTFILE** ppETFListData, const unsigned int& nItems);

	/*
	* 获取沪市ETF清单信息.获取成功之后需要调用DFDAPI_FreeArr()来释放pBaseETF和pBaseETFComp.
	*/
	int COM_JGDFDAPI DFDAPI_GetSHETFInfo(VHANDLE vHandle, DFDAPI_SHBaseETF* &pBaseETF, unsigned int &nETFItems,
		DFDAPI_SHBaseETFComponent* &pBaseETFComp, unsigned int &nCompItems);

	/*
	* 获取深市ETF清单信息.获取成功之后需要调用DFDAPI_FreeArr()来释放pBaseETF和pBaseETFComp.
	*/
	int COM_JGDFDAPI DFDAPI_GetSZETFInfo(VHANDLE vHandle, DFDAPI_SZBaseETF* &pBaseETF, unsigned int &nETFItems,
		DFDAPI_SZBaseETFComponent* &pBaseETFComp, unsigned int &nCompItems);

	/*
	* 关闭连接,并退出程序调用.
	*/
	void COM_JGDFDAPI DFDAPI_Exit();

	/*
	* 获取港股基本信息,需调用DFDAPI_FreeArr释放资源.
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy返回实例标识
	* @param[in|out] pBasicInfo 数据
	* @param[in|out] pItems 条数
	* return DFDAPI_ERR_SUCCESS:成功 其他:失败
	*/
	int COM_JGDFDAPI DFDAPI_GetHKexBasicInfoData(VHANDLE vHandle, DFDAPI_BASICINFO_HKEX* &pBasicInfo, unsigned int &nItems);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif