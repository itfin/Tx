#include <XtDataType.h>
#include <XtTraderApi.h>
#include <iostream>
#include <string>

using namespace xti;

#ifndef API_CALL_BACK_H_
#define API_CALL_BACK_H_
namespace xti
{
    enum AccoutType
    {
        CB_AT_DEFAULT,
        CB_AT_FUTURE = 1,          //期货账号
        CB_AT_STOCK = 2,           //股票账号
        CB_AT_CREDIT = 3,          //信用账号
        CB_AT_STOCK_OPTION = 6,    //股票期权账号
    };


    class Callback : public XtTraderApiCallback
    {
    public:
        // 参数为(服务器地址:端口，用户名，密码，资金账号，报单次数)
        Callback(const std::string& address, const std::string& username, const std::string& password, const std::string& fundAccountId, int orderNum);
        ~Callback();
        // 创建api实例，并进行初始化
        int init();
        // 等待线程结束（需要客户主动结束程序）
        void join();

        // 普通单测试
        // @param   fundAccountType 资金账号类型，支持现货、期货、期权、etf、信用等
        // @param   accountId 资金账号
        // @param   times 报单次数
        void testOrdinaryOrder(AccoutType fundAccountType, const std::string& accountId,  int times = 1);
        void testFutureOrdinaryOrder(const std::string& accountId,  int times);
        void testStockOrdinaryOrder(const std::string& accountId,  int times);
        void testCreditOrdinaryOrder(const std::string& accountId,  int times);
        void testStockOptionOrdinaryOrder(const std::string& accountId,  int times);


        // 算法单测试
        // @param   fundAccountType 资金账号类型，支持现货、期货、期权、etf、信用等
        // @param   accountId 资金账号
        void testAlgorithmOrder(AccoutType fundAccountType, const std::string& accoundId);

        // 组合单测试
        // @param   accountId 资金账号
        //@remark  目前组合单只支持股票业务
        void testGroupOrder(const std::string& accoundId);

        // 撤委托
        void testCancekOrder(AccoutType fundAccountType, const char* accountId);

        // 建立连接的回调
        // @param   success 反馈是否成功与服务器建立连接
        // @param   errorMsg 反馈连接失败时具体的错误信息
        virtual void onConnected(bool success, const char* errorMsg);

        // 用户登录的回馈
        // @param   userName 用户名
        // @param   password 用户对应的密码
        // @param   nRequestId 客户自己维护的请求号
        // @param   error 反馈登录信息，error的isSuccess可判断是否登录成功
        virtual void onUserLogin(const char* userName, const char* password, int nRequestId, const XtError& error);

        // 三种报单方式的回调
        // @param   nRequestId 客户自己维护的请求号
        // @param   orderID 服务器反馈的指令号，成功为大于0的整数，失败统一为-1
        // @param   error 反馈报单信息，error的isSuccess可判断是否报单成功
        virtual void onOrder(int nRequestId, int orderID, const XtError& error);

        // 撤单方式的回调
        // @param   nRequestId 客户自己维护的请求号
        // @param   error 反馈报单信息，error的isSuccess可判断是否报单成功
        virtual void onCancel(int nRequestId, const XtError& error);

        // 用户退出登录的回调，暂时无用
        virtual void onUserLogout(const std::string& userName, const std::string& password, int nRequestId, const XtError& error); 


        // 查询资金账号的各个记录信息
        
        // 查询资金账号的信息
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 资金账号的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求的结果一般只有一条资金账号信息
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqAccountDetail(const char* accountID, int nRequestId, const CAccountDetail* data, bool isLast, const XtError& error);
        
        // 查询信用资金账号的信息，当资金账号是信用类型的时候，请求资金账号会返回两条数据
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 信用的资金账号的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求的结果一般只有一条资金账号信息，其余类型的账号无返回
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqCreditAccountDetail(const char* accountID, int nRequestId, const CCreditAccountDetail* data, bool isLast, const XtError& error);

        // 委托记录明细的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 委托记录具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求当日委托的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqOrderDetail(const char* accountID, int nRequestId, const COrderDetail* data, bool isLast, const XtError& error);
        
        // 成交记录明细的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 成交记录的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求当日成交的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqDealDetail(const char* accountID, int nRequestId, const CDealDetail* data, bool isLast, const XtError& error);

        // 持仓明细的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 持仓明细的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求当日持仓明细的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqPositionDetail(const char* accountID, int nRequestId, const CPositionDetail* data, bool isLast, const XtError& error);
        
        // 持仓统计的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 持仓统计的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求当日持仓统计的结果可能有多条记录。持仓统计一般比持仓明细的记录数要少。
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqPositionStatics(const char* accountID, int nRequestId, const CPositionStatics* data, bool isLast, const XtError& error);

        // 信用业务
        // 信用负债合约的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 信用负债合约的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求负债合约的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqStksubjects(const char* accountID, int nRequestId, const CStkSubjects* data, bool isLast, const XtError& error);

        // 信用标的的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 信用标的的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求信用标的的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqStkcompacts(const char* accountID, int nRequestId, const CStkCompacts* data, bool isLast, const XtError& error);

        // 股票期权的备兑持仓的回调
        // @param   accountID 资金账户
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 备兑持仓的具体信息，具体可参考XtStructs.h
        // @param   isLast 是否为返回最后一条记录，一次请求备兑持仓的结果可能有多条记录
        // @param   error 反馈这次查询请求是否有错误
        virtual void onReqCoveredStockPosition(const char* accountID, int nRequestId, const CCoveredStockPosition* data, bool isLast, const XtError& error);

        // 查询产品接口
        virtual void onReqProductData(int nRequestId, const CProductData* data, bool isLast, const XtError& error);

        // 请求行情的回调
        // @param   nRequestId 客户自己维护的请求号
        // @param   data 具体的行情信息，具体可参考XtStructs.h
        virtual void onReqPriceData(int nRequestId, const CPriceData* data, const XtError& error);


        // 主推的接口
        // 资金账号的主推信息
        // @param   accountID 资金账户
        // @param   status 表明这个资金账号目前在迅投系统的登录状态
        // @param   brokerType 表明这个资金账号的类型，1:期货，2:股票，3:信用，6:股票期权
        // @param   errorMsg 如果有错误，通过errorMsg反馈错误信息
        virtual void onRtnLoginStatus(const char* accountID, EBrokerLoginStatus status, int brokerType, const char* errorMsg);

        // 指令状态的主推信息
        // @param   data 具体信息有COrderInfo携带
        virtual void onRtnOrder(const COrderInfo* data);

        // 委托回报的主推信息
        // @param   data COrderDetail
        virtual void onRtnOrderDetail(const COrderDetail* data);

        // 成交回报的主推信息
        // @param   data 具体信息有CDealDetail携带
        virtual void onRtnDealDetail(const CDealDetail* data);

        // 委托错误的主推信息
        // @param   data 具体信息有COrderError携带
        virtual void onRtnOrderError(const COrderError* data);

        // 委托回报的主推信息
        // @param   data 具体信息有CDealDetail携带
        virtual void onRtnCancelError(const CCancelError* data);

        // 获得主推的结算状态
        // @param   accountID 资金账户
        // @param   status 表明这个资金账号今日是否结算
        // @param   errorMsg 如果有错误，通过errorMsg反馈错误信息
        virtual void onRtnDeliveryStatus(const char* accountID, bool status, const char* errorMsg);

        // 资金账号的主推信息
        // @param   accountID 资金账户
        // @param   accountDetail 具体信息有CAccountDetail携带
        virtual void onRtnAccountDetail(const char* accountID, const CAccountDetail* accountDetail);

        // 信用资金账号信息的主推信息
        // @param   accountID 资金账户
        // @param   accountDetail 具体信息有CAccountDetail携带
        virtual void onRtnCreditAccountDetail(const char* accountID, const CCreditAccountDetail* data);

        // 委托回报的主推信息
        // @param   data 具体信息有CNetValue携带
        virtual void onRtnNetValue(const CNetValue* data);

    private:
        int             m_nRequestId;
        std::string     m_strAddress;
        std::string     m_strUserName;
        std::string     m_strPassWord;
        std::string     m_strFundAccountId;
        int             m_nOrderTimes;
        XtTraderApi*    m_client;
    };
}
#endif   // API_CALL_BACK_H_
