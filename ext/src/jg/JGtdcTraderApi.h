/////////////////////////////////////////////////////////////////////////
///@system 今古交易系统
///@company 深圳市今古科技有限公司
///@file JGtdcUserApiStruct.h
///@brief 定义了客户端接口
///@history 
///2018-02-24	zl	创建该文件
/////////////////////////////////////////////////////////////////////////


#if !defined(JGTDC_TRADER_API)
#define JGTDC_TRADER_API


#if _MSC_VER > 1000
#pragma once 
#endif  // _MSC_VER

#include <string>

#include "JGtdcUserApiStruct.h"

#if defined(__WINDOWS__) || defined(WIN32) || defined(WIN64) || defined(_WINDOWS)
#ifndef LIB_TRADER_API_EXPORT
#define LIB_TRADER_API_EXPORT
#endif
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport) 
#else
#define TRADER_API_EXPORT __declspec(dllimport) 
#endif
#else /* End winows defines */
#undef  __stdcall
#define __stdcall 
#define TRADER_API_EXPORT 
#endif /* End linux defines */ 

class CJGtdcTraderSpi
{
public:
	///< 客户端与交易后台已成功连接调用
	virtual void OnFrontConnected() { };
	///< 客户端与交易后台连接断开时调用
	virtual void OnFrontDisConnected() { };
	///< 错误应答
	virtual void OnRspError(const char* pErrMsg){};
	///< 订阅推送数据应答
	virtual void OnRspSubscription(CJGtdcRspUserSubData* pRspSubData, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 用户登录应答
	virtual void OnRspUserLogin(CJGtdcRspUserLogin* pRspUserLogin, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 用户登出应答
	virtual void OnRspUserLogout(CJGtdcRspUserLogout* pRspUserLogout, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 报单录入应答
	virtual void OnRspOrderInsert(CJGtdcRspOrderInsert* pRspOrderInsert, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 报单撤销应答
	virtual void OnRspOrderCancel(CJGtdcRspOrderCancel* pRspOrderCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者可撤单查询应答
	virtual void OnRspQryCancel(CJGtdcRspQryCancel* pRspQryCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者委托查询应答
	virtual void OnRspQryOrder(CJGtdcRspQryOrder* pRspQryOrder, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者成交单查询应答
	virtual void OnRspQryTrade(CJGtdcRspQryTrade* pRspQryTrade, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者持仓查询
	virtual void OnRspQryHold(CJGtdcRspQryHold* pRspQryHold, CJGtdcRspInfoField* pRspInfo, int nRequestID){ };
	///< 投资者资金查询
	virtual void OnRspQryFund(CJGtdcRspQryFund* pRspQryFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者最大委托数查询应答
	virtual void OnRspQryMax(CJGtdcRspQryMax* pRspQryMax, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者交割单查询
	virtual void OnRspQryDelivery(CJGtdcRspQryDelivery* pRspQryDelivery, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者报单通知
	virtual void OnRtnOrder(CJGtdcRspQryOrder *pOrder,int nItems) { };
	///< 投资者成交通知
	virtual void OnRtnTrade(CJGtdcRspQryTrade *pTrade,int nItems) { };


	////////////////////////////////////融资融券专用///////////////////////////////////////////////////////////
	///< 投资者融资融券资产查询
	virtual void OnRspQryAssets(CJGtdcRspQryAssets* pRspQryAssets, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者融券可卖数量查询
	virtual void OnRspQryMaxLoan(CJGtdcRspQryMaxLoan* pRspQryMaxLoan, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者可融券私有卖出数量查询
	virtual void OnRspQryReserveCreditStock(CJGtdcRspQryReserveCreditStock *pRspQryReserve, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者直接还券
	virtual void OnRspStockBack(CJGtdcRspStockBack* pRspStockBack, CJGtdcRspInfoField* pRspInfo, int nRequestID){};
	///< 投资者直接还款
	virtual void OnRspMoneyBack(CJGtdcRspMoneyBack* pRspMoneyBack, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者融资负债状况查询
	virtual void OnRspQryFinance(CJGtdcRspQryFinance* pRspQryFinance, CJGtdcRspInfoField* pRspInfo, int nRequestID) {};
	///< 投资者融券负债状况查询
	virtual void OnRspQryShortSell(CJGtdcRspQryShortsell* pRspQryShortSell, CJGtdcRspInfoField* pRspInfo, int nRequestID){};
	///< 投资者担保品划转
	virtual void OnRspMortgageTrans(CJGtdcRspMortgageTrans* pRspMortgageTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者标的券查询
	virtual void OnRspQryObject(CJGtdcRspQryObject *pRspQryObject, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者信用账户与普通账户对应关系查询应答
	virtual void OnRspQryAccMatch(CJGtdcRspQryAccMatch *pRspQryAccMatch, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };

	////////////////////////港股通专用功能函数//////////////////////////////////////////////////////////////
	///< 投资者港股通可撤单查询
	virtual void OnRspQryHKCancel(CJGtdcRspQryCancel* pRspQryCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者港股通委托查询
	virtual void OnRspQryHKOrder(CJGtdcRspQryOrder* pRspQryOrder, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者港股通成交单查询
	virtual void OnRspQryHKTrade(CJGtdcRspQryTrade* pRspQryTrade, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者港股通持仓查询
	virtual void OnRspQryHKHold(CJGtdcRspQryHold* pRspQryHold, CJGtdcRspInfoField* pRspInfo, int nRequestID){ };
	///< 投资者港股通资金查询
	virtual void OnRspQryHKFund(CJGtdcRspQryFund* pRspQryFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者港股通汇率查询
	virtual void OnRspQryHKExRate(CJGtdcRspQryHKExRate* pRspQryHKExRate, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者港股通额度查询
	virtual void OnRspQryHKLimit(CJGtdcRspQryHKLimit* pRspQryHKLimit, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	////////////////////////////////////////////////////////////////////////////////////////////////////////
};


class /*TRADER_API_EXPORT*/ CJGtdcTraderApi
{
public:
	///< 创建TraderApi
	static CJGtdcTraderApi* CreatetdcTraderApi();
	///< 获取接口版本
	static const char* GetVersion(int& nMajorVersion,int& nMinorVersion);
	///< 释放实例对象
	virtual void Release() = 0 ;
	///< 初始化环境
	virtual bool Init() = 0 ;
	///< 释放环境
	virtual bool Fini() = 0 ;
 	///< 注册回调接口
	virtual void RegisterCallBack(CJGtdcTraderSpi* pSpi) = 0 ;
	///< 连接服务器 非域名 bdomain 入参 false  域名 bdomain 入参为 true  
	virtual bool Connect(const char* pszAddress,unsigned short uPort,bool bdomain = false ) =  0 ;
	///< 断开服务器
	virtual bool Disconnect() = 0 ;
	///< 开启并设置SSL参数，默认不开启 （在初始化Init前调用）
	virtual bool SetSSLParamer(const char* sz_ca_cert, const char* sz_private_key = nullptr, const char* sz_dh_file = nullptr, const char* sz_us_ca_cert = nullptr, const char* szKeyPwd = nullptr) = 0;
	///< 开启报单应答时序(报单应答后才会推送成交和委托数据)
	virtual void OpenOrderSequential(bool bOpen = false) = 0;
	///< 订阅推送数据
	virtual int ReqSubscription(CJGtdcReqUserSubData* pReqSubData, int nRequestID) = 0;
	///< 设置用户机器信息,登陆前调用（默认取本机信息）
	virtual void SetUserMachineInfo(CJGtdcMachineInfo *pUserMachineInfo) = 0;
	///< 用户登入(普通账户 bCredit 入参 false  信用账户 bCredit 入参 true )
	virtual int ReqUserLogin(CJGtdcReqUserLogin* pReqLogin, bool bCredit, int nRequestID) = 0;
	///< 用户账户信息
	// 外围分配内存空间 空间不足则返回 -2  无此账号或者客户号空值 返回-1 成功返回 0 
	// pszClientId 客户号 account 账户基础信息 pHolderInfo 股东信息 nHolderInfo 股东个数 
	virtual int GetUserAccount(const char* pszClientId,CJGtdcUserAccountInfo& account, CJGtdcUserHolderInfo* pHolderInfo, int& nHolderItem) = 0 ;
	///< 用户登出
	virtual int ReqUserLogout(CJGtdcReqUserLogout* pReqLogout, int nRequestID) = 0;
	///< 报单录入请求
	virtual int ReqOrderInsert(CJGtdcReqOrderInsert* pReqOrderInsert,int nItem, int nRequestID) = 0;
	///< 报单撤销请求
	virtual int ReqOrderCancel(CJGtdcReqOrderCancel* pReqOrderCancel,int nItem, int nRequestID) = 0;
	///< 投资者可撤单查询
	virtual int ReqQryCancel(CJGtdcReqQryCancel* pQryCancel, int nRequestID) = 0;
	///< 投资者委托查询
	virtual int ReqQryOrder(CJGtdcReqQryOrder* pQryOrder, int nRequestID) = 0;
	///< 投资者成交单查询
	virtual int ReqQryTrade(CJGtdcReqQryTrade* pQryTrade, int nRequestID) = 0;
	///< 投资者持仓查询
	virtual int ReqQryHold(CJGtdcReqQryHold* pQryHold, int nRequestID) = 0;
	///< 投资者资金查询
	virtual int ReqQryFund(CJGtdcReqQryFund* pReqFund, int nRequestID) = 0;
	///< 投资者最大委托数查询
	virtual int ReqQryMax(CJGtdcReqQryMax* pReqMax,int nRequestID) = 0 ;
	///< 投资者交割单查询
	virtual int ReqQryDelivery(CJGtdcReqQryDelivery* pReqQryDelivery, int nRequestID) = 0;
	
	////////////////////////融资融券专用功能函数///////////////////////////////////////////////////////////
	///< 投资者信用资产查询
	virtual int ReqQryAssets(CJGtdcReqQryAssets *pQryAssets, int nRequestID) = 0;
	///< 投资者可融券卖出数量查询
	virtual int ReqQryMaxLoan(CJGtdcReqQryMaxLoan *pQryMaxLoan, int nRequestID) = 0;
	///< 投资者可融券私有卖出数量查询
	virtual int ReqQryReserveCreditStock(CJGtdcReqQryReserveCreditStock *pQryReserve, int nRequestID) = 0;
	///< 投资者直接还券
	virtual int ReqStockBack(CJGtdcReqStockBack *pReqStockBack, int nRequestID) = 0;
	///< 投资者直接还款
	virtual int ReqMoneyBack(CJGtdcReqMoneyBack *pReqMoneyBack, int nRequestID) = 0;
	///< 投资者融资负债状况查询
	virtual int ReqQryFinance(CJGtdcReqQryFinance* pQryFinance, int nRequestID) = 0;
	///< 投资者融券负债状况查询
	virtual int ReqQryShortSell(CJGtdcReqQryShortsell* pQryShortSell, int nRequestID) = 0;
	///< 投资者担保品划转
	virtual int ReqMortgageTrans(CJGtdcReqMortgageTrans* pReqMortgageTrans, int nRequestID) = 0;
	///< 投资者标的券查询
	virtual int ReqQryObject(CJGtdcReqQryObject *pReqQryObject, int nRequestID) = 0;
	///< 投资者信用账户与普通账户对应关系查询
	virtual int ReqQryAccMatch(CJGtdcReqQryAccMatch *pReqQryAccMatch, int nRequestID) = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////港股通专用功能函数//////////////////////////////////////////////////////////////
	///< 投资者港股通可撤单查询
	virtual int ReqQryHKCancel(CJGtdcReqQryCancel* pQryCancel, int nRequestID) = 0;
	///< 投资者港股通委托查询
	virtual int ReqQryHKOrder(CJGtdcReqQryOrder* pQryOrder, int nRequestID) = 0;
	///< 投资者港股通成交单查询
	virtual int ReqQryHKTrade(CJGtdcReqQryTrade* pQryTrade, int nRequestID) = 0;
	///< 投资者港股通持仓查询
	virtual int ReqQryHKHold(CJGtdcReqQryHold* pQryHold, int nRequestID) = 0;
	///< 投资者港股通资金查询
	virtual int ReqQryHKFund(CJGtdcReqQryFund* pReqFund, int nRequestID) = 0;
	///< 投资者港股通汇率查询
	virtual int ReqQryHKExRate(CJGtdcReqQryHKExRate* pReqQryHKExRate, int nRequestID) = 0;
	///< 投资者港股通额度查询
	virtual int ReqQryHKLimit(CJGtdcReqQryHKLimit* pReqQryHKLimit, int nRequestID) = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////////////
};


#endif /*  JGTDC_TRADER_API */