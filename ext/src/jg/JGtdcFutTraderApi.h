/////////////////////////////////////////////////////////////////////////
///@system 今古交易系统
///@company 深圳市今古科技有限公司
///@file JGtdcFutTraderApi.h
///@brief 定义了客户端期货，期权接口
///@history 
///2018-06-13	ff	创建该文件
/////////////////////////////////////////////////////////////////////////


#if !defined(JGTDC_FUTTRADER_API)
#define JGTDC_FUTTRADER_API


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

class CJGtdcFutTraderSpi
{
public:
	///< 客户端与交易后台已成功连接调用
	virtual void OnFrontConnected() { };
	///< 客户端与交易后台连接断开时调用
	virtual void OnFrontDisConnected() { };
	///< 错误应答
	virtual void OnRspError(const std::string& strError){};
	///< 订阅推送数据应答
	virtual void OnRspSubscription(CJGtdcRspUserSubData* pRspSubData, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货用户登录应答
	virtual void OnRspFutureUserLogin(CJGtdcFutureRspUserLogin* pRspUserLogin, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货用户登出应答
	virtual void OnRspFutureUserLogout(CJGtdcFutureRspUserLogout* pRspUserLogout, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货账单查询应答
	virtual void OnRspFuturQrySettlement(CJGtdcFutureRspQrySettlement* pRspQrySettlement, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货账单确认应答
	virtual void OnRspFutureConfirmSettle(CJGtdcFutureRspConfirmSettle* pRspConfirmSettle, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货合约查询应答
	virtual void OnRspFutureQryContract(CJGtdcFutureRspQryContract* pRspQryContract, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货委托下单应答
	virtual void OnRspFutureEntrust(CJGtdcFutureRspEntrust* pRspEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货委托撤单应答
	virtual void OnRspFutureCancel(CJGtdcFutureRspCancel* pRspCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货最大交易数量查询应答
	virtual void OnRspFutureQryMax(CJGtdcFutureRspQryMax* pRspQryMax, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货交易编码查询应答
	virtual void OnRspFutureQryHolder(CJGtdcFutureRspQryHolder* pRspQryHolder, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货资金查询应答
	virtual void OnRspFutureQryFund(CJGtdcFutureRspQryFund* pRspQryFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货持仓查询应答
	virtual void OnRspFutureQryHold(CJGtdcFutureRspQryHold* pRspQryHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货当日委托查询应答
	virtual void OnRspFutureQryEntrust(CJGtdcFutureRspQryEntrust* pRspQryEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货可撤单查询应答
	virtual void OnRspFutureQryRevocEnt(CJGtdcFutureRspQryRevocEnt* pRspQryRevocEnt, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货增量成交查询应答
	virtual void OnRspFutureQryBusByPos(CJGtdcFutureRspQryBusByPos* pRspQryBusByPos, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };

	///< 投资者期货银行账号查询应答
	virtual void OnRspFutureQryBankAccount(CJGtdcFutureRspQryBankAccount* pRspQryBankAccount, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货银衍转账应答
	virtual void OnRspFutureBankTrans(CJGtdcFutureRspBankTrans* pRspBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货银衍转账查询应答
	virtual void OnRspFutureQryBankTrans(CJGtdcFutureRspQryBankTrans* pRspQryBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货银衍转账可转资金应答
	virtual void OnRspFutureQryBankMaxTrans(CJGtdcFutureRspQryBankMaxTrans* pRspQryBankMaxTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货查询子账户及其资金应答
	virtual void OnRspFutureQryChildBankFund(CJGtdcFutureRspQryChildBankFund* pRspQryChildBankFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期货同名账户资金内转应答
	virtual void OnRspFutureQryInTransferFund(CJGtdcFutureRspInTransferFund* pRspInTransferFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };

};


class TRADER_API_EXPORT CJGtdcFutTraderApi
{
public:
	///< 创建TraderApi
	static CJGtdcFutTraderApi* CreatetdcTraderApi();
	///< 获取接口版本
	static const char* GetVersion(int& nMajorVersion, int& nMinorVersion);
	///< 释放实例对象
	virtual void Release() = 0;
	///< 初始化环境
	virtual bool Init() = 0;
	///< 释放环境
	virtual bool Fini() = 0;
	///< 注册回调接口
	virtual void RegisterCallBack(CJGtdcFutTraderSpi* pSpi) = 0;
	///< 连接服务器 非域名 bdomain 入参 false  域名 bdomain 入参为 true  
	virtual bool Connect(const char* pszAddress, unsigned short uPort, bool bdomain = false) = 0;
	///< 断开服务器
	virtual bool Disconnect() = 0;
	///< 开启并设置SSL参数，默认不开启 （在初始化Init前调用）
	virtual bool SetSSLParamer(const char* sz_ca_cert, const char* sz_private_key = nullptr, const char* sz_dh_file = nullptr, const char* sz_us_ca_cert = nullptr, const char* szKeyPwd = nullptr) = 0;
	///< 订阅推送数据
	virtual int ReqSubscription(CJGtdcReqUserSubData* pReqSubData, int nRequestID) = 0;
	///< 设置用户机器信息,登陆前调用（默认取本机信息）
	virtual void SetUserMachineInfo(CJGtdcMachineInfo *pUserMachineInfo) = 0;
	///< 投资者期货用户登入
	virtual int ReqFutureUserLogin(CJGtdcFutureReqUserLogin* pReqLogin, int nRequestID) = 0;
	///< 投资者期货用户登出
	virtual int ReqFutureUserLogout(CJGtdcFutureReqUserLogout* pReqLogout, int nRequestID) = 0;
	///< 投资者期货账单查询
	virtual int ReqFutureQrySettlement(CJGtdcFutureReqQrySettlement* pQrySettlement, int nRequestID) = 0;
	///< 投资者期货账单确认
	virtual int ReqFutureReqConfirmSettle(CJGtdcFutureReqConfirmSettle* pReqConfirmSettle, int nRequestID) = 0;
	///< 投资者期货合约查询
	virtual int ReqFutureQryContract(CJGtdcFutureReqQryContract* pQryContract, int nRequestID) = 0;
	///< 投资者期货委托下单
	virtual int ReqFutureReqEntrust(CJGtdcFutureReqEntrust* pReqEntrust, int nItem, int nRequestID) = 0;
	///< 投资者期货委托撤单
	virtual int ReqFutureReqCancel(CJGtdcFutureReqCancel* pReqCancel, int nItem, int nRequestID) = 0;
	///< 投资者期货最大交易数量查询
	virtual int ReqFutureQryMax(CJGtdcFutureReqQryMax* pQryMax, int nRequestID) = 0;
	///< 投资者期货交易编码查询
	virtual int ReqFutureQryHolder(CJGtdcFutureReqQryHolder* pQryHolder, int nRequestID) = 0;
	///< 投资者期货资金查询
	virtual int ReqFutureQryFund(CJGtdcFutureReqQryFund* pQryFund, int nRequestID) = 0;
	///< 投资者期货持仓查询
	virtual int ReqFutureQryHold(CJGtdcFutureReqQryHold* pQryHold, int nRequestID) = 0;
	///< 投资者期货当日委托查询
	virtual int ReqFutureQryEntrust(CJGtdcFutureReqQryEntrust* pQryEntrust, int nRequestID) = 0;
	///< 投资者期货可撤单查询
	virtual int ReqFutureQryRevocEnt(CJGtdcFutureReqQryRevocEnt* pQryRevocEnt, int nRequestID) = 0;
	///< 投资者期货增量成交查询
	virtual int ReqFutureQryBusByPos(CJGtdcFutureReqQryBusByPos* pQryBusByPos, int nRequestID) = 0;

	///< 投资者期货银行账号查询
	virtual int ReqFutureQryBankAccount(CJGtdcFutureReqQryBankAccount* pReqQryBankAccount, int nRequestID) = 0;
	///< 投资者期货银衍转账
	virtual int ReqFutureBankTrans(CJGtdcFutureReqBankTrans* pReqBankTrans, int nRequestID) = 0;
	///< 投资者期货银衍转账查询
	virtual int ReqFutureQryBankTrans(CJGtdcFutureReqQryBankTrans* pReqQryBankTrans, int nRequestID) = 0;
	///< 投资者期货银衍转账可转资金
	virtual int ReqFutureQryBankMaxTrans(CJGtdcFutureReqQryBankMaxTrans* pReqQryBankMaxTrans, int nRequestID) = 0;
	///< 投资者期货查询子账户及其资金
	virtual int ReqFutureQryChildBankFund(CJGtdcFutureReqQryChildBankFund* pReqQryChildBankFund, int nRequestID) = 0;
	///< 投资者期货同名账户资金内转
	virtual int ReqFutureQryInTransferFund(CJGtdcFutureReqInTransferFund* pReqInTransferFund, int nRequestID) = 0;
};


#endif /*  JGTDC_FUTTRADER_API */