/********************************************************************
	company:    北京睿智融科控股有限公司
	fileName:	XtDataType.h
	author:		xujun    
	created:	8:11:2013   15:13	
	purpose:	数据定义
*********************************************************************/
#ifndef XtDataType_2013_11_8_H
#define XtDataType_2013_11_8_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtDef.h"

namespace xti
{
    // enum defines

    enum XT_API_EXPORT EErrorType
    {
        XT_ERROR_SUCCESS = 0,                   // 无错误
        XT_ERROR_NET_DISCONNECTED = 200000,     // 未建立连接
        XT_ERROR_NOT_LOGINED = 200001,          // 未登录
        XT_ERROR_NOT_INITIALIZED = 200002,      // 初始化未完成
        XT_ERROR_TIME_OUT = 200003,             // 超时
        XT_ERROR_NOT_FIND_ACCOUNT = 200004,     // 未找到账号
        XT_ERROR_NOT_FIND_FUNCTION = 200005,    // 未找到处理函数
        XT_ERROR_INVALID_PARAM = 200006,        // 参数有误
        XT_ERROR_DEFAULT = 300000,              // 默认错误号
        XT_ERROR_UNKNOWN = 300001,              // 未知错误
        XT_ERROR_REPEAT_LOGIN = 300002,         // 重复登录
        XT_ERROR_LOGIN_MD5_NOT_MATCH = 300003,         // md5值不匹配
        XT_ERROR_LOGIN_API_VERSINO_TOO_LOW = 300004,   // api版本较低
        XT_ERROR_LOGIN_USER_NOT_ALLOWEDLOGIN = 300005, // 用户不允许登陆
        XT_ERROR_CREATECOMMOND_PARAM,                  // 创建指令时，解析参数失败
        XT_ERROR_CREATECOMMOND_QUOTE,                  // 创建指令时，获取行情数据失败
        XT_ERROR_CREATECOMMOND_PRICE_TYPE,             // 创建指令时，获取有关报价类型的价格失败（如最新价等）
        XT_ERROR_ORDER_FLOW_CONTROL,                   // 下单超过流量控制
        XT_ERROR_ORDER_NOT_AUTHORIZE_STOCK_FUTURE,     // 股票期货业务没有授权
        XT_ERROR_ORDER_NOT_AUTHORIZE_STOCKOPTION,      // 股票期权业务没有授权
        XT_ERROR_ORDER_NOT_AUTHORIZE_CREDIT,           // 信用业务没有授权
        XT_ERROR_ORDER_NOT_AUTHORIZE_GOLD,             // 黄金业务没有授权
    };

    enum XT_API_EXPORT EXTPlatForm
    {
        PLATFORM_ZTSP = 10001,          //中投实盘
        PLATFORM_ZTMN = 11001,          //中投模拟
        PLATFORM_ZJSP = 10002,          //中金实盘
        PLATFORM_CJSP = 10004,          //长江实盘
        PLATFORM_DFSP = 10003,          //东方实盘
        PLATFORM_DFMN = 11003,          //东方模拟
        PLATFORM_ZXSP = 10005,          //中信实盘
        PLATFORM_ZXMN = 11005,          //中信模拟
        PLATFORM_QLSP = 10006,          //齐鲁实盘
        PLATFORM_QLMN = 11006,          //齐鲁模拟
        PLATFORM_HUATAISP = 10007,      //华泰实盘
        PLATFORM_HUATAIMN = 11007,      //华泰模拟
        PLATFORM_GXSP = 10008,          //国信实盘
        PLATFORM_GXMN = 11008,          //国信模拟
        PLATFORM_XTGPMN = 11009,        //迅投自有股票
        PLATFORM_SWSP = 10010,          //申银万国实盘
        PLATFORM_SWMN = 11010,          //申银万国模拟
        PLATFORM_GTSP = 10011,          //国泰君安实盘
        PLATFORM_UFXSP = 10012,         //UFX实盘
        PLATFORM_UFXMN = 11012,         //UFX模拟
        PLATFORM_GZSP = 10013,          //广州证券实盘
        PLATFORM_GZMN = 11013,          //广州证券模拟
        PLATFORM_GDSP = 10014,          //光大证券实盘
        PLATFORM_GDMN = 11014,          //光大证券模拟
        PLATFORM_SXSP = 10015,          //山西证券实盘
        PLATFORM_SXMN = 11015,          //山西证券模拟
        PLATFORM_HAITONGSP = 10016,     //海通证券新API实盘
        PLATFORM_HAITONGMN = 11016,     //海通证券新API模拟
        PLATFORM_HAITONGSPXSP = 10017,  //海通证券SPX接口实盘
        PLATFORM_HAITONGSPXMN = 11017,  //海通证券SPX接口模拟
        PLATFORM_YHSP = 10018,          //银河证券KCXP实盘
        PLATFORM_YHMN = 11018,          //银河证券KCXP模拟
        PLATFORM_YHDDSP = 10019,        //银河证券顶点柜台实盘
        PLATFORM_YHDDMN = 11019,        //银河证券顶点柜台模拟
        PLATFORM_O32DB = 10020,         //O32虚拟broker
        PLATFORM_O32DBMN = 11020,       //O32虚拟broker模拟
        PLATFORM_XINGYESP = 10021,      //兴业证券CTP柜台实盘
        PLATFORM_XINGYEMN = 11021,      //兴业证券CTP柜台模拟
        PLATFORM_GUANGFASP = 10022,     //广发证券顶点柜台实盘
        PLATFORM_GUANGFAMN = 11022,     //广发证券顶点柜台模拟
        PLATFORM_DONGXINGSP = 10023,    //东兴证券顶点柜台实盘
        PLATFORM_DONGXINGMN = 11023,    //东兴证券顶点柜台模拟
        PLATFORM_XTGJHQ = 10000,        //迅投高级行情
        PLATFORM_MAX_STOCK = 19999,     //股票分界线
        PLATFORM_CTPSP = 20001,         //CTP期货实盘
        PLATFORM_CTPMN = 21001,         //CTP期货模拟
        PLATFORM_HHSP = 20002,          //华海期货实盘
        PLATFORM_HHMN = 21002,          //华海期货模拟
        PLATFORM_KSSP = 20010,          //金仕达期货实盘
        PLATFORM_KSMN = 21010,          //金仕达期货模拟
        PLATFORM_XTXHMN = 21009,        //迅投自有期货
        PLATFORM_ZGSP_FUTURE = 21111,   // 资管实盘
        PLATFORM_ZGMN_FUTURE = 21112,   // 资管模拟
        PLATFORM_MAX_FUTURE = 29999,    //期货分界线
    };


    enum XT_API_EXPORT EXTBrokerType
    {
        AT_FUTURE = 1,          //期货账号
        AT_STOCK = 2,           //股票账号
        AT_CREDIT = 3,          //信用账号
        AT_GOLD = 4,            //贵金属账号
        AT_FUTURE_OPTION = 5,   //期货期权账号
        AT_STOCK_OPTION = 6,    //股票期权账号
        AT_HUGANGTONG = 7,      //沪港通账号
        AT_NEW3BOARD = 10,      //全国股转账号
    };

    enum XT_API_EXPORT EPriceType
    {
        PRTP_INVALID = -1, 
        PRTP_SALE5,      //卖5
        PRTP_SALE4,      //卖4
        PRTP_SALE3,      //卖3
        PRTP_SALE2,      //卖2
        PRTP_SALE1,      //卖1
        PRTP_LATEST,     //最新价
        PRTP_BUY1,       //买1
        PRTP_BUY2,       //买2
        PRTP_BUY3,       //买3
        PRTP_BUY4,       //买4
        PRTP_BUY5,       //买5
        PRTP_FIX,        //指定价
        PRTP_MARKET,     //市价
        PRTP_HANG,       //挂单价 跟盘价
        PRTP_COMPETE,    //对手价
        _C_PRTP_COUNT,
    };

    enum XT_API_EXPORT EBrokerPriceType
    {
        BROKER_PRICE_ANY = 49,                  //市价
        BROKER_PRICE_LIMIT,                     //限价
        BROKER_PRICE_BEST,                      //最优价
        BROKER_PRICE_PROP_ALLOTMENT = 52,       //配股
        BROKER_PRICE_PROP_REFER,                //转托
        BROKER_PRICE_PROP_SUBSCRIBE,            //申购
        BROKER_PRICE_PROP_BUYBACK,              //回购
        BROKER_PRICE_PROP_PLACING,              //配售
        BROKER_PRICE_PROP_DECIDE,               //指定
        BROKER_PRICE_PROP_EQUITY,               //转股
        BROKER_PRICE_PROP_SELLBACK,             //回售
        BROKER_PRICE_PROP_DIVIDEND,             //股息
        BROKER_PRICE_PROP_SHENZHEN_PLACING,     //深圳配售确认
        BROKER_PRICE_PROP_CANCEL_PLACING,       //配售放弃
        BROKER_PRICE_PROP_WDZY,                 //无冻质押
        BROKER_PRICE_PROP_DJZY,                 //冻结质押
        BROKER_PRICE_PROP_WDJY,                 //无冻解押
        BROKER_PRICE_PROP_JDJY,                 //解冻解押
        BROKER_PRICE_PROP_ETF,                  //ETF申购
        BROKER_PRICE_PROP_VOTE,                 //投票
        BROKER_PRICE_PROP_YYSGYS,               //要约收购预售
        BROKER_PRICE_PROP_YSYYJC,               //预售要约解除
        BROKER_PRICE_PROP_FUND_DEVIDEND,        //基金设红
        BROKER_PRICE_PROP_FUND_ENTRUST = 79,    //基金申赎
        BROKER_PRICE_PROP_CROSS_MARKET,         //跨市转托
        BROKER_PRICE_PROP_EXERCIS,              //权证行权
        BROKER_PRICE_PROP_PEER_PRICE_FIRST,     //对手方最优价格
        BROKER_PRICE_PROP_L5_FIRST_LIMITPX,     //最优五档即时成交剩余转限价
        BROKER_PRICE_PROP_MIME_PRICE_FIRST,     //本方最优价格
        BROKER_PRICE_PROP_INSTBUSI_RESTCANCEL,  //即时成交剩余撤销
        BROKER_PRICE_PROP_L5_FIRST_CANCEL,      //最优五档即时成交剩余撤销
        BROKER_PRICE_PROP_FULL_REAL_CANCEL,     //全额成交并撤单
        BROKER_PRICE_PROP_FUND_CHAIHE = 90,     //基金拆合
        _C_BRPT_COUNT,
    };
    enum XT_API_EXPORT EVolumeType
    {
        VOLUME_INVALID = -1, 
        VOLUME_SALE12345,
        VOLUME_SALE1234,
        VOLUME_SALE123,
        VOLUME_SALE12,
        VOLUME_SALE1,
        VOLUME_BUY1, //买一
        VOLUME_BUY12,
        VOLUME_BUY123,
        VOLUME_BUY1234,
        VOLUME_BUY12345,
        VOLUME_FIX,
        VOLUME_LEFT,
        VOLUME_POSITION, //持仓数量
        _C_VOLUME_COUNT,
    };

    enum XT_API_EXPORT EOperationType
    {
        OPT_INVALID = -1, 
        // 期货业务
        OPT_OPEN_LONG = 0,              // 开多 0
        OPT_CLOSE_LONG_HISTORY,         // 平昨多 1
        OPT_CLOSE_LONG_TODAY,           // 平今多 2
        OPT_OPEN_SHORT,                 // 开空 3
        OPT_CLOSE_SHORT_HISTORY,        // 平昨空 4
        OPT_CLOSE_SHORT_TODAY,          // 平今空 5
        OPT_CLOSE_LONG_TODAY_FIRST,     // 平多，优先平今  6
        OPT_CLOSE_LONG_HISTORY_FIRST,   // 平多，优先平昨 7
        OPT_CLOSE_SHORT_TODAY_FIRST,    // 平空，优先平今 8
        OPT_CLOSE_SHORT_HISTORY_FIRST,  // 平空，优先平昨 9
        // 股票业务
        OPT_BUY = 18,                   //买入，针对股票 18
        OPT_SELL,                       //卖出，针对股票 19
        //信用交易
        OPT_FIN_BUY,                //融资买入
        OPT_SLO_SELL,               //融券卖出
        OPT_BUY_SECU_REPAY,         //买券还券
        OPT_DIRECT_SECU_REPAY,      //直接还券
        OPT_SELL_CASH_REPAY,        //卖券还款
        OPT_DIRECT_CASH_REPAY,      //直接还款
        //分级基金
        OPT_FUND_SUBSCRIBE,         //基金申购
        OPT_FUND_REDEMPTION,        //基金赎回
        OPT_FUND_MERGE,             //基金合并
        OPT_FUND_SPLIT,             //基金分拆
        //正回购
        OPT_PLEDGE_IN,              //质押入库
        OPT_PLEDGE_OUT,             //质押出库
        //期权业务
        OPT_OPTION_BUY_OPEN,        //买入开仓
        OPT_OPTION_SELL_CLOSE,      //卖出平仓
        OPT_OPTION_SELL_OPEN,       //卖出开仓
        OPT_OPTION_BUY_CLOSE,       //买入平仓
        OPT_OPTION_COVERED_OPEN,    //备兑开仓
        OPT_OPTION_COVERED_CLOSE,   //备兑平仓
        OPT_OPTION_CALL_EXERCISE,   //认购行权
        OPT_OPTION_PUT_EXERCISE,    //认沽行权
        OPT_OPTION_SECU_LOCK,       //证券锁定
        OPT_OPTION_SECU_UNLOCK,     //证券解锁
        //ETF业务
        OPT_ETF_PURCHASE = 1004,    //ETF申购
        OPT_ETF_REDEMPTION,         //ETF赎回
    };

    enum XT_API_EXPORT EOffsetFlagType
    {
        EOFF_THOST_FTDC_OF_INVALID = -1,        //未知
        EOFF_THOST_FTDC_OF_Open = 48,           //开仓
        EOFF_THOST_FTDC_OF_Close = 49,          //平仓
        EOFF_THOST_FTDC_OF_ForceClose = 50,     //强平
        EOFF_THOST_FTDC_OF_CloseToday = 51,     //平今
        EOFF_THOST_FTDC_OF_CloseYesterday = 52, //平昨
        EOFF_THOST_FTDC_OF_ForceOff = 53,       //强减
        EOFF_THOST_FTDC_OF_LocalForceClose = 54,//本地强平
        EOFF_THOST_FTDC_OF_PLEDGE_IN = 81,      //质押入库
        EOFF_THOST_FTDC_OF_PLEDGE_OUT = 66,     //质押出库
    };
    
    enum XT_API_EXPORT EHedgeFlagType
    {
        HEDGE_FLAG_SPECULATION = 49,  //投机
        HEDGE_FLAG_ARBITRAGE = 50,    //套利
        HEDGE_FLAG_HEDGE = 51,        //套保
    };

    enum XT_API_EXPORT EBrokerLoginStatus
    {
        BROKER_LOGIN_STATUS_INALID = -1, 
        BROKER_LOGIN_STATUS_OK = 0,         //可用，初始化完成
        BROKER_LOGIN_STATUS_WAITING_LOGIN,  //连接中
        BROKER_LOGIN_STATUS_LOGINING,       //登录中
        BROKER_LOGIN_STATUS_FAIL,           //失败
        BROKER_LOGIN_STATUS_INITING,        //在初始化中
        BROKER_LOGIN_STATUS_CORRECTING,     //数据刷新校正中
        BROKER_LOGIN_STATUS_CLOSED,         //收盘后
    };

    enum XT_API_EXPORT EEntrustBS
    {
        ENTRUST_BUY = 48,           //买入
        ENTRUST_SELL = 49,          //卖出
        ENTRUST_PLEDGE_IN = 81,     //质押入库
        ENTRUST_PLEDGE_OUT = 66,    //质押出库
    };

    enum XT_API_EXPORT EOrderCommandStatus
    {
        OCS_CHECKING = -1,      //风控检查中
        OCS_APPROVING,          //审批中
        OCS_REJECTED,           //已驳回
        OCS_RUNNING,            //运行中
        OCS_CANCELING,          //撤销中
        OCS_FINISHED,           //已完成
        OCS_STOPPED,            //已停止
        OCS_FROCE_COMPLETED,    //强制撤销
        OCS_CHECKFAILED,        //风控驳回
    };

    enum XT_API_EXPORT EEntrustTypes
    {
        ENTRUST_BUY_SELL = 48,      //买卖
        ENTRUST_QUERY,              //查询
        ENTRUST_CANCEL,             //撤单
        ENTRUST_APPEND,             //补单
        ENTRUST_COMFIRM,            //确认
        ENTRUST_BIG,                //大宗
        ENTRUST_FIN = 54,           //融资委托
        ENTRUST_SLO = 55,           //融券委托
        ENTRUST_CLOSE = 56,         //信用平仓
        ENTRUST_CREDIT_NORMAL = 57, //信用普通委托
        ENTRUST_CANCEL_OPEN = 58,   //撤单补单
    };

    enum XT_API_EXPORT EFutureTradeType
    {
        FUTRUE_TRADE_TYPE_COMMON = 48,      //普通成交
        FUTURE_TRADE_TYPE_OPTIONSEXECUTION, //期权成交ptionsExecution
        FUTURE_TRADE_TYPE_OTC,              //OTC成交
        FUTURE_TRADE_TYPE_EFPDIRVED,        //期转现衍生成交
        FUTURE_TRADE_TYPE_COMBINATION_DERIVED, //组合衍生成交
    };

    enum XT_API_EXPORT EEntrustStatus
    {
        ENTRUST_STATUS_WAIT_END = 0,        //委托状态已经在ENTRUST_STATUS_CANCELED或以上，但是成交数额还不够，等成交回报来
        ENTRUST_STATUS_UNREPORTED = 48,     //未报
        ENTRUST_STATUS_WAIT_REPORTING,      //待报
        ENTRUST_STATUS_REPORTED,            //已报
        ENTRUST_STATUS_REPORTED_CANCEL,     //已报待撤
        ENTRUST_STATUS_PARTSUCC_CANCEL,     //部成待撤
        ENTRUST_STATUS_PART_CANCEL,         //部撤
        ENTRUST_STATUS_CANCELED,            //已撤
        ENTRUST_STATUS_PART_SUCC,           //部成
        ENTRUST_STATUS_SUCCEEDED,           //已成
        ENTRUST_STATUS_JUNK,                //废单
        ENTRUST_STATUS_UNKNOWN,             //未知
    };
    enum XT_API_EXPORT EEntrustSubmitStatus
    {
        ENTRUST_SUBMIT_STATUS_InsertSubmitted = 48,  //已经提交
        ENTRUST_SUBMIT_STATUS_CancelSubmitted,       //撤单已经提交
        ENTRUST_SUBMIT_STATUS_ModifySubmitted,       //修改已经提交
        ENTRUST_SUBMIT_STATUS_OSS_Accepted,          //已经接受
        ENTRUST_SUBMIT_STATUS_InsertRejected,        //报单已经被拒绝
        ENTRUST_SUBMIT_STATUS_CancelRejected,        //撤单已经被拒绝
        ENTRUST_SUBMIT_STATUS_ModifyRejected,        //改单已经被拒绝
    };

    enum XT_API_EXPORT EXTSubjectsStatus
    {
        SUBJECTS_STATUS_NORMAL = 48,  //正常
        SUBJECTS_STATUS_PAUSE = 49,   //暂停
        SUBJECTS_STATUS_NOT,          //非标的
    };

    enum XT_API_EXPORT EXTCompactType
    {
        COMPACT_TYPE_ALL = 32,  //不限制
        COMPACT_TYPE_FIN = 48,  //融资
        COMPACT_TYPE_SLO = 49,  //融券
    };

    enum XT_API_EXPORT EXTCompactStatus
    {
        COMPACT_STATUS_ALL = 32,            //不限制
        COMPACT_STATUS_UNDONE = 48,         //未归还
        COMPACT_STATUS_PART_DONE = 49,      //部分归还
        COMPACT_STATUS_DONE = 50,           //已归还
        COMPACT_STATUS_DONE_BY_SELF = 51,   //自行了结
        COMPACT_STATUS_DONE_BY_HAND = 52,   //手工了结
        COMPACT_STATUS_NOT_DEBT = 53,       //未形成负债
    };

    enum XT_API_EXPORT EXtOverFreqOrderMode
    {
        OFQ_FORBID = 0, // 禁止
        OFQ_QUEUE = 1,  //队列
    };

}


#endif