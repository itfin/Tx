/********************************************************************
	company:    北京睿智融科控股有限公司
	fileName:	XtTraderApi.h
	author:		xujun    
	created:	8:11:2013   17:01	
	purpose:	
*********************************************************************/
#ifndef XtTraderApi_2013_11_8_H
#define XtTraderApi_2013_11_8_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtDef.h"
#include "XtError.h"
#include "XtStructs.h"

namespace xti
{
    class XtTraderApiCallback;

    class XT_API_EXPORT XtTraderApi
    {
    public:
        virtual ~XtTraderApi(){};
        static XtTraderApi* createXtTraderApi(const char* address);

        virtual void setCallback(XtTraderApiCallback* pCallback) = 0 ;

        virtual bool init() = 0;
        virtual void destroy() = 0;
        virtual void join() = 0;

        // nRequestId：数据请求ID，是数据请求和请求结果对应的标识
        // @remark 请求成功后的回调函数会传回请求函数的 nRequestId

        // 客户端用户登录
        // @remark 连接成功后，登录客户端用户
        virtual void userLogin(const char* userName, const char* password, int nRequestId, const char* machineInfo = NULL) = 0;

        // 客户端用户登出
        // /@remark 用户不再调用请求服务时，登出客户端用户
        virtual void userLogout(const char* userName, const char* password, int nRequestId) = 0;

        // 当前数据请求
        // @remark 只用资金帐号登录成功后才可以请求该帐号的相应数据
        // 请求账号资金信息
        virtual void reqAccountDetail(const char* accountID, int nRequestId) = 0;
        // 请求委托明细
        virtual void reqOrderDetail(const char* accountID, int nRequestId) = 0;
        virtual void reqOrderDetail(const char* accountID, int nRequestId, int nOrderID) = 0;
        // 请求成交明细
        virtual void reqDealDetail(const char* accountID, int nRequestId) = 0;
        virtual void reqDealDetail(const char* accountID, int nRequestId, int nOrderID) = 0;
        // 请求持仓明细
        virtual void reqPositionDetail(const char* accountID, int nRequestId) = 0;
        // 请求持仓统计
        virtual void reqPositionStatics(const char* accountID, int nRequestId) = 0;
        // 信用
        // 查询负债合约
        virtual void reqStkcompacts(const char* accountID, int nRequestId) = 0;
        // 查询标的
        virtual void reqStksubjects(const char* accountID, int nRequestId) = 0;
        // 期权 查询备兑持仓
        virtual void reqCoveredStockPosition(const char* accountID, int nRequestId) = 0;

        // 行情数据请求
        virtual void reqPriceData(const char* exchangeId, const char* instrumentId, int nRequestId) = 0;

        // 下单操作
        // @remark 普通单
        // @bReturnNow 为true，表示直接返回，但不能保证委托成功；为false时，保证委托成功才会返回
        virtual void order(const COrdinaryOrder* orderInfo, int nRequestId) = 0;
        // @remakr 组合单
        virtual void order(const CGroupOrder* orderInfo, int nRequestId) = 0;
        // @remark 算法单
        virtual void order(const CAlgorithmOrder* orderInfo, int nRequestId) = 0;

        // 撤单操作
        // @remark 终止某个单子的运行
        virtual void cancel(int orderID, int nRequestId) = 0;

        // 撤委托操作
        virtual void cancelOrder(const char* accountID, const char* orderSyeId, const char* exchangeId, const char* instrumentId, int nRequestId) = 0;

        virtual void reqProductData(int nRequestId) = 0;

    };

    class XT_API_EXPORT XtTraderApiCallback
    {
    public:
        virtual ~XtTraderApiCallback(){}
        // 相应请求的回调函数
        // @param   nRequestId 和请求函数中 nRequestId 想对应
        // @param   error 请求函数的返回是否成功，如果失败有错误信息
        // @remark  函数名组成：以 on 为前缀，加上相应请求函数的函数名称（请求函数首字母大写）

        // 连接服务器的回调函数
        // @param success   服务器连接是否成
        // @param errorMsg  如果服务器连接失败，存储错误信息
        virtual void onConnected(bool success, const char* errorMsg) {}
        // 客户端用户登录的回调函数
        virtual void onUserLogin(const char* userName, const char* password, int nRequestId, const XtError& error) {}
        // /客户端用户登出的回调函数
        virtual void onUserLogout(const char* userName, const char* password, int nRequestId, const XtError& error) {}

        // 下单的回调
        virtual void onOrder(int nRequestId, int orderID, const XtError& error) {}
        // 撤单的回调
        virtual void onCancel(int nRequestId, const XtError& error) {}
        // 撤委托的回调
        virtual void onCancelOrder(int nRequestId,  const XtError& error) {}

        // 请求当前数据的回调函数
        // @param data 请求数据的返回
        // @param isLast 请求数据可能有多条，需要多次回调该函数，标记是否是一次请求的最后一次回调
        virtual void onReqAccountDetail(const char* accountID, int nRequestId, const CAccountDetail* data, bool isLast, const XtError& error) {}
        virtual void onReqCreditAccountDetail(const char* accountID, int nRequestId, const CCreditAccountDetail* data, bool isLast, const XtError& error) {}
        virtual void onReqOrderDetail(const char* accountID, int nRequestId, const COrderDetail* data, bool isLast, const XtError& error) {}
        virtual void onReqDealDetail(const char* accountID, int nRequestId, const CDealDetail* data, bool isLast, const XtError& error) {}
        virtual void onReqPositionDetail(const char* accountID, int nRequestId, const CPositionDetail* data, bool isLast, const XtError& error) {}
        virtual void onReqPositionStatics(const char* accountID, int nRequestId, const CPositionStatics* data, bool isLast, const XtError& error) {}

        virtual void onReqStksubjects(const char* accountID, int nRequestId, const CStkSubjects* data, bool isLast, const XtError& error) {}
        virtual void onReqStkcompacts(const char* accountID, int nRequestId, const CStkCompacts* data, bool isLast, const XtError& error) {}
        virtual void onReqCoveredStockPosition(const char* accountID, int nRequestId, const CCoveredStockPosition* data, bool isLast, const XtError& error) {}
        virtual void onReqProductData(int nRequestId, const CProductData* data, bool isLast, const XtError& error) {}

        // 请求行情数据的回调
        virtual void onReqPriceData(int nRequestId, const CPriceData* data, const XtError& error) {}

        // 主推接口
        // 获得主推的用户登录状态
        // @param   status 主推资金账号的登录状态
        // @param   brokerType 主推资金账号的类型 
        // 1:期货账号, 2:股票账号, 3:信用账号, 4:贵金属账号, 5:期货期权账号, 6:股票期权账号, 7:沪港通账号, 10:全国股转账号
        virtual void onRtnLoginStatus(const char* accountID, EBrokerLoginStatus status, int brokerType, const char* errorMsg) {}
        // 获取主推的报单状态（指令）
        virtual void onRtnOrder(const COrderInfo* data){}
        // 获得主推的委托明细（委托）
        virtual void onRtnOrderDetail(const COrderDetail* data) {}
        // 获得主推的成交明细
        virtual void onRtnDealDetail(const CDealDetail* data) {}
        // 获得主推的委托错误信息
        virtual void onRtnOrderError(const COrderError* data) {}
        // 获得主推的撤销信息
        virtual void onRtnCancelError(const CCancelError* data) {}
        // 获得主推的结算状态
        virtual void onRtnDeliveryStatus(const char* accountID, bool status, const char* errorMsg) {}
        // 获得主推的资金账号信息
        virtual void onRtnAccountDetail(const char* accountID, const CAccountDetail* data) {}
        // 获得主推的信用资金账号信息
        virtual void onRtnCreditAccountDetail(const char* accountID, const CCreditAccountDetail* data) {}
        // 获得主推的产品净值信息
        virtual void onRtnNetValue(const CNetValue* data){}
    };
}

#endif