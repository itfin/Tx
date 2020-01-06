/////////////////////////////////////////////////////////////////////////
///@system 今古交易系统
///@company 深圳市今古科技有限公司
///@file JGtdcFutOptTraderApi.h
///@brief 定义了客户端期权接口
///@history 
///2018-06-13	ff	创建该文件
/////////////////////////////////////////////////////////////////////////


#if !defined(JGTDC_FUTOPTTRADER_API)
#define JGTDC_FUTOPTTRADER_API


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

class CJGtdcOptTraderSpi
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
	///< 用户登录应答
	virtual void OnRspOptionUserLogin(CJGtdcRspUserLogin* pRspUserLogin, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 用户登出应答
	virtual void OnRspOptionUserLogout(CJGtdcRspUserLogout* pRspUserLogout, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权合约查询应答
	virtual void OnRspOptionQryContract(CJGtdcOptionRspQryContract* pRspQryContract, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权委托下单应答
	virtual void OnRspOptionEntrust(CJGtdcOptionRspEntrust* pRspEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权委托撤单应答
	virtual void OnRspOptionCancel(CJGtdcOptionRspCancel* pRspCancel, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权最大交易数量查询应答
	virtual void OnRspOptionQryMax(CJGtdcOptionRspQryMax* pRspQryMax, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权备兑证券划转应答
	virtual void OnRspOptionCoveredTrans(CJGtdcOptionRspCoveredTrans* pRspCoveredTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权备兑可划转数量查询应答
	virtual void OnRspOptionQryCoveredMax(CJGtdcOptionRspQryCoveredMax* pRspQryCoveredMax, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权资金查询应答
	virtual void OnRspOptionQryFund(CJGtdcOptionRspQryFund* pRspQryFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权持仓查询应答
	virtual void OnRspOptionQryHold(CJGtdcOptionRspQryHold* pRspQryQryHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权委托查询应答
	virtual void OnRspOptionQryEntrust(CJGtdcOptionRspQryEntrust* pRspQryEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权可撤单查询应答
	virtual void OnRspOptionQryRevocEnt(CJGtdcOptionRspQryRevocEnt* pRspQryRevocEnt, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权增量成交查询应答
	virtual void OnRspOptionQryBusByPos(CJGtdcOptionRspQryBusByPos* pRspQryBusByPos, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权备兑持仓查询应答
	virtual void OnRspOptionQryCoveredHold(CJGtdcOptionRspQryCoveredHold* pRspQryCoveredHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权行权指派查询应答
	virtual void OnRspOptionQryExerciseAssign(CJGtdcOptionRspQryExerciseAssign* pRspQryExerciseAssign, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权备兑持仓不足查询应答
	virtual void OnRspOptionQryLackCoveredStock(CJGtdcOptionRspQryLackCoveredStock* pRspQryLackCoveredStock, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权可取资金查询应答
	virtual void OnRspOptionQryFetchFund(CJGtdcOptionRspQryFetchFund* pRspQryFetchFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权历史委托查询应答
	virtual void OnRspOptionQryHisEntrust(CJGtdcOptionRspQryHisEntrust* pRspQryHisEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权历史成交查询应答
	virtual void OnRspOptionQryHisBusiness(CJGtdcOptionRspQryHisBusiness* pRspQryHisBusiness, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权历史行权指派查询应答
	virtual void OnRspOptionQryHisExerciseAssign(CJGtdcOptionRspQryHisExerciseAssign* pRspQryHisExerciseAssign, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权增加自动行权应答
	virtual void OnRspOptionAddAutoExercise(CJGtdcOptionRspAddAutoExercise* pRspAddAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权修改自动行权应答
	virtual void OnRspOptionModAutoExercise(CJGtdcOptionRspModAutoExercise* pRspModAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权删除自动行权应答
	virtual void OnRspOptionDelAutoExercise(CJGtdcOptionRspDelAutoExercise* pRspDelAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权自动行权查询应答
	virtual void OnRspOptionQryAutoExercise(CJGtdcOptionRspQryAutoExercise* pRspQryAutoExercise, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权备兑可划转查询应答
	virtual void OnRspOptionQryCovered(CJGtdcOptionRspQryCovered* pRspQryCovered, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权昨日持仓查询应答
	virtual void OnRspOptionQryHisHold(CJGtdcOptionRspQryHisHold* pRspQryHisHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权结算单查询应答
	virtual void OnRspOptionQrySettlement(CJGtdcOptionRspQrySettlement* pRspQrySettlement, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权交割单查询应答
	virtual void OnRspOptionQryDelivery(CJGtdcOptionRspQryDelivery* pRspQryDelivery, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权调拨资金应答
	virtual void OnRspOptionTransferFund(CJGtdcOptionRspTransferFund* pRspTransferFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权个股组合拆分委托应答
	virtual void OnRspOptionShareCombSplitEntrust(CJGtdcOptionRspShareCombSplitEntrust* pRspShareCombSplitEntrust, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权个股组合持仓明细查询应答
	virtual void OnRspOptionQryShareCombSplitHold(CJGtdcOptionRspQryShareCombSplitHold* pQryShareCombSplitHold, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权个股可组合可拆分手数查询应答
	virtual void OnRspOptionQryShareCombSplitLots(CJGtdcOptionRspQryShareCombSplitLots* pRspQryShareCombSplitLots, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权个股客户资金变动流水历史查询应答
	virtual void OnRspOptionQryShareUserHisFundChange(CJGtdcOptionRspQryShareUserHisFundChange* pRspQryShareUserHisFundChange, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权结算单确认应答
	virtual void OnRspOptionSettlementConfrim(CJGtdcOptionRspSettlementConfrim* pRspSettlementConfrim, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者委托通知
	virtual void OnRtnOptionOrder(CJGtdcOptionRspQryEntrust* pRspQryEntrust, int nItems) { };
	///< 投资者成交通知
	virtual void OnRtnOptionTrade(CJGtdcOptionRspQryBusByPos* pRspQryBusByPos, int nItems) { };


	///< 投资者期权银行账号查询应答
	virtual void OnRspOptionQryBankAccount(CJGtdcOptionRspQryBankAccount* pRspQryBankAccount, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权银衍转账应答
	virtual void OnRspOptionBankTrans(CJGtdcOptionRspBankTrans* pRspBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权银衍转账查询应答
	virtual void OnRspOptionQryBankTrans(CJGtdcOptionRspQryBankTrans* pRspQryBankTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权银衍转账可转资金应答
	virtual void OnRspOptionQryBankMaxTrans(CJGtdcOptionRspQryBankMaxTrans* pRspQryBankMaxTrans, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权查询子账户及其资金应答
	virtual void OnRspOptionQryChildBankFund(CJGtdcOptionRspQryChildBankFund* pRspQryChildBankFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
	///< 投资者期权同名账户资金内转应答
	virtual void OnRspOptionQryInTransferFund(CJGtdcOptionRspInTransferFund* pRspInTransferFund, CJGtdcRspInfoField* pRspInfo, int nRequestID) { };
};


class TRADER_API_EXPORT CJGtdcOptTraderApi
{
public:
	///< 创建TraderApi
	static CJGtdcOptTraderApi* CreatetdcTraderApi();
	///< 获取接口版本
	static const char* GetVersion(int& nMajorVersion, int& nMinorVersion);
	///< 释放实例对象
	virtual void Release() = 0;
	///< 初始化环境
	virtual bool Init() = 0;
	///< 释放环境
	virtual bool Fini() = 0;
	///< 注册回调接口
	virtual void RegisterCallBack(CJGtdcOptTraderSpi* pSpi) = 0;
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
	///< 用户登入
	virtual int ReqOptionUserLogin(CJGtdcReqUserLogin* pReqLogin, int nRequestID) = 0;
	///< 用户账户信息
	// 外围分配内存空间 空间不足则返回 -2  无此账号或者客户号空值 返回-1 成功返回 0 
	// pszClientId 客户号 account 账户基础信息 pHolderInfo 股东信息 nHolderInfo 股东个数 
	virtual int GetUserAccount(const char* pszClientId, CJGtdcUserAccountInfo& account, CJGtdcUserHolderInfo* pHolderInfo, int& nHolderItem) = 0;
	///< 用户登出
	virtual int ReqOptionUserLogout(CJGtdcReqUserLogout* pReqLogout, int nRequestID) = 0;
	///< 投资者期权合约查询
	virtual int ReqOptionQryContract(CJGtdcOptionReqQryContract* pQryContract, int nRequestID) = 0;
	///< 投资者期权委托下单
	virtual int ReqOptionEntrust(CJGtdcOptionReqEntrust* pReqEntrust, int nItem, int nRequestID) = 0;
	///< 投资者期权委托撤单
	virtual int ReqOptionCancel(CJGtdcOptionReqCancel* pReqCancel, int nItem, int nRequestID) = 0;
	///< 投资者期权最大交易数量查询
	virtual int ReqOptionQryMax(CJGtdcOptionReqQryMax* pQryMax, int nRequestID) = 0;
	///< 投资者期权备兑证券划转
	virtual int ReqOptionCoveredTrans(CJGtdcOptionReqCoveredTrans* pReqCoveredTrans, int nRequestID) = 0;
	///< 投资者期权备兑可划转数量查询
	virtual int ReqOptionQryCoveredMax(CJGtdcOptionReqQryCoveredMax* pQryCoveredMax, int nRequestID) = 0;
	///< 投资者期权资金查询
	virtual int ReqOptionQryFund(CJGtdcOptionReqQryFund* pQryFund, int nRequestID) = 0;
	///< 投资者期权持仓查询
	virtual int ReqOptionQryHold(CJGtdcOptionReqQryHold* pQryQryHold, int nRequestID) = 0;
	///< 投资者期权委托查询
	virtual int ReqOptionQryEntrust(CJGtdcOptionReqQryEntrust* pQryEntrust, int nRequestID) = 0;
	///< 投资者期权可撤单查询
	virtual int ReqOptionQryRevocEnt(CJGtdcOptionReqQryRevocEnt* pQryRevocEnt, int nRequestID) = 0;
	///< 投资者期权增量成交查询
	virtual int ReqOptionQryBusByPos(CJGtdcOptionReqQryBusByPos* pQryBusByPos, int nRequestID) = 0;
	///< 投资者期权备兑持仓查询
	virtual int ReqOptionQryCoveredHold(CJGtdcOptionReqQryCoveredHold* pQryCoveredHold, int nRequestID) = 0;
	///< 投资者期权行权指派查询
	virtual int ReqOptionQryExerciseAssign(CJGtdcOptionReqQryExerciseAssign* pQryExerciseAssign, int nRequestID) = 0;
	///< 投资者期权备兑持仓不足查询
	virtual int ReqOptionQryLackCoveredStock(CJGtdcOptionReqQryLackCoveredStock* pQryLackCoveredStock, int nRequestID) = 0;
	///< 投资者期权可取资金查询
	virtual int ReqOptionQryFetchFund(CJGtdcOptionReqQryFetchFund* pQryFetchFund, int nRequestID) = 0;
	///< 投资者期权历史委托查询
	virtual int ReqOptionQryHisEntrust(CJGtdcOptionReqQryHisEntrust* pQryHisEntrust, int nRequestID) = 0;
	///< 投资者期权历史成交查询
	virtual int ReqOptionQryHisBusiness(CJGtdcOptionReqQryHisBusiness* pQryHisBusiness, int nRequestID) = 0;
	///< 投资者期权历史行权指派查询
	virtual int ReqOptionQryHisExerciseAssign(CJGtdcOptionReqQryHisExerciseAssign* pQryHisExerciseAssign, int nRequestID) = 0;
	///< 投资者期权增加自动行权
	virtual int ReqOptionAddAutoExercise(CJGtdcOptionReqAddAutoExercise* pAddAutoExercise, int nRequestID) = 0;
	///< 投资者期权修改自动行权
	virtual int ReqOptionModAutoExercise(CJGtdcOptionReqModAutoExercise* pModAutoExercise, int nRequestID) = 0;
	///< 投资者期权删除自动行权
	virtual int ReqOptionDelAutoExercise(CJGtdcOptionReqDelAutoExercise* pDelAutoExercise, int nRequestID) = 0;
	///< 投资者期权自动行权查询
	virtual int ReqOptionQryAutoExercise(CJGtdcOptionReqQryAutoExercise* pQryAutoExercise, int nRequestID) = 0;
	///< 投资者期权备兑可划转查询
	virtual int ReqOptionQryCovered(CJGtdcOptionReqQryCovered* pQryCovered, int nRequestID) = 0;
	///< 投资者期权昨日持仓查询
	virtual int ReqOptionQryHisHold(CJGtdcOptionReqQryHisHold* pQryHisHold, int nRequestID) = 0;
	///< 投资者期权结算单查询
	virtual int ReqOptionQrySettlement(CJGtdcOptionReqQrySettlement* pQrySettlement, int nRequestID) = 0;
	///< 投资者期权交割单查询
	virtual int ReqOptionQryDelivery(CJGtdcOptionReqQryDelivery* pQryDelivery, int nRequestID) = 0;
	///< 投资者期权调拨资金
	virtual int ReqOptionTransferFund(CJGtdcOptionReqTransferFund* pTransferFund, int nRequestID) = 0;
	///< 投资者期权个股组合拆分委托
	virtual int ReqOptionShareCombSplitEntrust(CJGtdcOptionReqShareCombSplitEntrust* pShareCombSplitEntrust, int nRequestID) = 0;
	///< 投资者期权个股组合持仓明细查询
	virtual int ReqOptionQryShareCombSplitHold(CJGtdcOptionReqQryShareCombSplitHold* pQryShareCombSplitHold, int nRequestID) = 0;
	///< 投资者期权个股可组合可拆分手数查询
	virtual int ReqOptionQryShareCombSplitLots(CJGtdcOptionReqQryShareCombSplitLots* pQryShareCombSplitLots, int nRequestID) = 0;
	///< 投资者期权个股客户资金变动流水历史查询
	virtual int ReqOptionQryShareUserHisFundChange(CJGtdcOptionReqQryShareUserHisFundChange* pQryShareUserHisFundChange, int nRequestID) = 0;
	///< 投资者期权结算单确认
	virtual int ReqOptionSettlementConfrim(CJGtdcOptionReqSettlementConfrim* pSettlementConfrim, int nRequestID) = 0;

	///< 投资者期权银行账号查询
	virtual int ReqOptionQryBankAccount(CJGtdcOptionReqQryBankAccount* pReqQryBankAccount, int nRequestID) = 0;
	///< 投资者期权银衍转账
	virtual int ReqOptionBankTrans(CJGtdcOptionReqBankTrans* pReqBankTrans, int nRequestID) = 0;
	///< 投资者期权银衍转账查询
	virtual int ReqOptionQryBankTrans(CJGtdcOptionReqQryBankTrans* pReqQryBankTrans, int nRequestID) = 0;
	///< 投资者期权银衍转账可转资金
	virtual int ReqOptionQryBankMaxTrans(CJGtdcOptionReqQryBankMaxTrans* pReqQryBankMaxTrans, int nRequestID) = 0;
	///< 投资者期权查询子账户及其资金
	virtual int ReqOptionQryChildBankFund(CJGtdcOptionReqQryChildBankFund* pReqQryChildBankFund, int nRequestID) = 0;
	///< 投资者期权同名账户资金内转
	virtual int ReqOptionQryInTransferFund(CJGtdcOptionReqInTransferFund* pReqInTransferFund, int nRequestID) = 0;
};


#endif /*  JGTDC_FUTOPTTRADER_API */