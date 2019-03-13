/********************************************************************
    company:    北京睿智融科控股有限公司
    fileName:	XtStructs.h
    author:		xujun
    created:	8:11:2013   15:14
    purpose:	结构定义
*********************************************************************/
#ifndef XtStructs_2013_11_8_H
#define XtStructs_2013_11_8_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtDef.h"
#include "XtDataType.h"

namespace xti
{

    struct XT_API_EXPORT CAccountDetail
    {
        CAccountDetail();
        ~CAccountDetail();

        char        m_strAccountID[32];
        char        m_strStatus[32];            // 状态
        char        m_strTradingDate[16];

        double      m_dFrozenMargin;            // 外源性 股票的保证金就是冻结资金 股票不需要
        double      m_dFrozenCash;              // 内外源冻结保证金和手续费四个的和
        double      m_dFrozenCommission;        // 外源性冻结资金源
        double      m_dRisk;                    // 风险度
        double      m_dNav;                     // 单位净值
        double      m_dPreBalance;              // 期初权益
        double      m_dBalance;                 // 动态权益, 总资产
        double      m_dAvailable;               // 可用资金
        double      m_dCommission;              // 已用手续费
        double      m_dPositionProfit;          // 持仓盈亏
        double      m_dCloseProfit;             // 平仓盈亏
        double      m_dCashIn;                  // 出入金净值
        double      m_dCurrMargin;              // 当前占用保证金
        double      m_dInstrumentValue;         // 合约价值
        double      m_dDeposit;                 // 入金
        double      m_dWithdraw;                // 出金
        double      m_dCredit;                  // 信用额度
        double      m_dMortgage;                // 质押
        double      m_dStockValue;              // 股票总市值，期货没有
        double      m_dLoanValue;               // 债券总市值，期货没有
        double      m_dFundValue;               // 基金总市值，包括ETF和封闭式基金，期货没有
        double      m_dRepurchaseValue;         // 回购总市值，所有回购，期货没有
        double      m_dLongValue;               // 多单总市值，现货没有
        double      m_dShortValue;              // 空单总市值，现货没有
        double      m_dNetValue;                // 净持仓总市值，净持仓市值=多-空
        double      m_dAssureAsset;             // 净资产
        double      m_dTotalDebit;              // 总负债
    };

    struct XT_API_EXPORT CCreditAccountDetail
    {
        CCreditAccountDetail();
        ~CCreditAccountDetail();

        double      m_dPerAssurescaleValue;     //个人维持担保比例
        double      m_dEnableBailBalance;       //可用保证金
        double      m_dUsedBailBalance;         //已用保证金
        double      m_dAssureEnbuyBalance;      //可买担保品资金
        double      m_dFinEnbuyBalance;         //可买标的券资金
        double      m_dSloEnrepaidBalance;      //可还券资金
        double      m_dFinEnrepaidBalance;      //可还款资金
        double      m_dFinMaxQuota;             //融资授信额度
        double      m_dFinEnableQuota;          //融资可用额度
        double      m_dFinUsedQuota;            //融资已用额度
        double      m_dFinUsedBail;             //融资已用保证金额
        double      m_dFinCompactBalance;       //融资合约金额
        double      m_dFinCompactFare;          //融资合约费用
        double      m_dFinCompactInterest;      //融资合约利息
        double      m_dFinMarketValue;          //融资市值
        double      m_dFinIncome;               //融资合约盈亏
        double      m_dSloMaxQuota;             //融券授信额度
        double      m_dSloEnableQuota;          //融券可用额度
        double      m_dSloUsedQuota;            //融券已用额度
        double      m_dSloUsedBail;             //融券已用保证金额
        double      m_dSloCompactBalance;       //融券合约金额
        double      m_dSloCompactFare;          //融券合约费用
        double      m_dSloCompactInterest;      //融券合约利息
        double      m_dSloMarketValue;          //融券市值
        double      m_dSloIncome;               //融券合约盈亏
        double      m_dOtherFare;               //其它费用
        double      m_dUnderlyMarketValue;      //标的证券市值
        double      m_dFinEnableBalance;        //可融资金额
        double      m_dDiffEnableBailBalance;   //可用保证金调整值
        double      m_dBuySecuRepayFrozenMargin;//买券还券冻结资金
        double      m_dBuySecuRepayFrozenCommission; //买券还券冻结手续费
    };

    struct XT_API_EXPORT CNetValue
    {
        CNetValue();
        ~CNetValue();
        int         m_nProductId;       //迅投产品ID
        int         m_nTypes;           //产品类型 1-普通基金 2-分级基金
        double      m_dTotalNetValue;   //产品净资产, 产品净值
        double      m_dNetValue;        //母基金单位净值
        double      m_dBNetValue;       //B级基金单位净值
        int         m_nUpdateTime;      //更新时间
    };

    // 普通单、算法单： 一个单子对应一笔委托，推送一次
    // 组合单： 一个单子可能对应多笔委托，分多次推送
    struct XT_API_EXPORT COrderInfo
    {
        COrderInfo();
        ~COrderInfo();
        int                             m_nOrderID;          //指令ID
        int                             m_startTime;         //下达时间
        int                             m_endTime;           //结束时间
        EOrderCommandStatus             m_eStatus;           //状态
        double                          m_dTradedVolume;     //成交量
        char                            m_strMsg[256];       //指令执行信息
        char                            m_canceler[32];      //撤销者
    };

    struct XT_API_EXPORT COrderDetail
    {
        COrderDetail();
        ~COrderDetail();

        char                        m_strAccountID[32];
        char                        m_strExchangeID[16];    //交易所代码
        char                        m_strProductID[32];     //合约品种
        char                        m_strInstrumentID[32];  //合约代码
        double                      m_dLimitPrice;          //限价单的限价，就是报价
        char                        m_strOrderSysID[32];    //委托号
        int                         m_nTradedVolume;        //已成交量
        int                         m_nTotalVolume;         //当前总委托量
        double                      m_dFrozenMargin;        //冻结保证金
        double                      m_dFrozenCommission;    //冻结手续费
        double                      m_dAveragePrice;        //成交均价
        double                      m_dTradeAmount;         //成交额 期货=均价*量*合约乘数

        int                         m_nErrorID;
        char                        m_strErrorMsg[256];
        char                        m_strInsertDate[16];    //日期
        char                        m_strInsertTime[32];    //时间
        int                         m_nOrderID;             //指令ID
        EBrokerPriceType            m_nOrderPriceType;      //类型，例如市价单 限价单
        EEntrustBS                  m_nDirection;           //期货多空，该字段与m_eOffsetFlag一起判断期货的报单类型。股票无用
        EOffsetFlagType             m_eOffsetFlag;          //期货开平，股票买卖
        EHedgeFlagType              m_eHedgeFlag;           //投机 套利 套保
        EEntrustSubmitStatus        m_eOrderSubmitStatus;   //提交状态，股票里面不需要报单状态
        EEntrustStatus              m_eOrderStatus;         //委托状态
        EEntrustTypes               m_eEntrustType;         //委托类别
    };

    struct XT_API_EXPORT CDealDetail
    {
        CDealDetail();
        ~CDealDetail();
        
        char                m_strAccountID[32];
        char                m_strExchangeID[16];   //交易所代码
        char                m_strProductID[32];    //合约品种
        char                m_strInstrumentID[32]; //合约代码
        char                m_strTradeID[32];      //成交编号
        char                m_strOrderSysID[32];   //委托
        double              m_dAveragePrice;       //成交均价
        int                 m_nVolume;             //成交量 期货单位手 股票做到股
        char                m_strTradeDate[16];    //成交日期
        char                m_strTradeTime[32];    //成交时间
        double              m_dComssion;           //手续费
        double              m_dAmount;             //成交额 期货=均价*量*合约乘数
        int                 m_nOrderID;            //指令ID
        EEntrustBS          m_nDirection;          //期货多空，该字段与m_eOffsetFlag一起判断期货的报单类型。股票无用
        EOffsetFlagType     m_nOffsetFlag;         //期货开平 股票买卖
        EHedgeFlagType      m_nHedgeFlag;          //投机 套利 套保
        EBrokerPriceType    m_nOrderPriceType;     //类型，例如市价单 限价单
        EEntrustTypes       m_eEntrustType;        //委托类别
    };

    struct XT_API_EXPORT CPositionDetail
    {
        CPositionDetail();
        ~CPositionDetail();
        
        char        m_strAccountID[32];
        char        m_strExchangeID[16];    //市场代码
        char        m_strProductID[32];     //合约品种
        char        m_strInstrumentID[32];  //合约代码
        char        m_strOpenDate[16];
        char        m_strTradeID[32];       //最初开仓位的成交
        int         m_nVolume;              //持仓量 当前拥股
        double      m_dOpenPrice;           //开仓价
        char        m_strTradingDay[16];    //交易日
        double      m_dMargin;              //使用的保证金 历史的直接用ctp的，新的自己用成本价*存量*系数算  股票不需要
        double      m_dOpenCost;            //开仓成本 等于股票的成本价*第一次建仓的量，后续减持不影响，不算手续费 股票不需要
        double      m_dSettlementPrice;     //结算价 对于股票的当前价
        int         m_nCloseVolume;         //平仓量 等于股票已经卖掉的 股票不需要
        double      m_dCloseAmount;         //平仓额 等于股票每次卖出的量*卖出价*合约乘数（股票为1）的累加 股票不需要
        double      m_dFloatProfit;         //浮动盈亏 当前量*（当前价-开仓价）*合约乘数（股票为1）
        double      m_dCloseProfit;         //平仓盈亏 平仓额 - 开仓价*平仓量*合约乘数（股票为1） 股票不需要
        double      m_dMarketValue;         //市值 合约价值
        double      m_dPositionCost;        //持仓成本 股票不需要
        double      m_dPositionProfit;      //持仓盈亏 股票不需要
        double      m_dLastSettlementPrice; //最新结算价 股票不需要
        double      m_dInstrumentValue;     //合约价值 股票不需要
        bool        m_bIsToday;             //是否今仓
        int         m_nOrderID;             //指令ID
        int         m_nFrozenVolume;        //期货不用这个字段，冻结数量
        int         m_nCanUseVolume;        //期货不用这个字段，股票的可用数量
        int         m_nOnRoadVolume;        //期货不用这个字段，股票的在途数量
        int         m_nYesterdayVolume;     //期货不用这个字段，股票的股份余额
        double      m_dLastPrice;           //结算价 对于股票的当前价
        EHedgeFlagType      m_nHedgeFlag;   //投机 套利 套保
        EEntrustBS          m_nDirection;   //期货多空，该字段与m_eOffsetFlag一起判断期货的报单类型。股票无用
    };

    struct XT_API_EXPORT CPositionStatics
    {
        CPositionStatics();
        ~CPositionStatics();

        char        m_strAccountID[32];
        char        m_strExchangeID[16];
        char        m_strProductID[32];     //合约品种
        char        m_strInstrumentID[32];  //合约代码
        bool        m_bIsToday;             //是否今仓
        int         m_nPosition;            //持仓 需要
        double      m_dOpenCost;            //非任务平冻结
        double      m_dPositionCost;        //持仓成本 detail的汇总
        double      m_dAveragePrice;            //算法待找
        double      m_dPositionProfit;      //持仓盈亏 detail的汇总
        double      m_dFloatProfit;         //浮动盈亏 detail的汇总
        double      m_dOpenPrice;           //开仓均价 股票不需要
        int         m_nCanCloseVolume;         //可平
        double      m_dUsedMargin;          //已使用保证金
        double      m_dUsedCommission;      //已使用的手续费
        double      m_dFrozenMargin;        //冻结保证金
        double      m_dFrozenCommission;    //冻结手续费
        double      m_dInstrumentValue;     //合约价值
        int         m_nOpenTimes;           //开仓次数
        int         m_nOpenVolume;          //总开仓量 中间平仓不减
        int         m_nCancelTimes;         //撤单次数
        int         m_nFrozenVolume;        //期货不用这个字段，冻结数量
        int         m_nCanUseVolume;        //期货不用这个字段，股票的可用数量
        int         m_nOnRoadVolume;        //期货不用这个字段，股票的在途数量
        int         m_nYesterdayVolume;     //期货不用这个字段，股票的股份余额
        double      m_dSettlementPrice;     //市价 最新价
        double      m_dProfitRate;          //持仓盈亏比例
        EEntrustBS          m_nDirection;   //期货多空，该字段与m_eOffsetFlag一起判断期货的报单类型。股票无用
        EHedgeFlagType      m_nHedgeFlag;   //投机 套利 套保
    };

    struct XT_API_EXPORT COrderError
    {
        COrderError();
        ~COrderError();
        
        char        m_strAccountID[32];
        int         m_nErrorID;
        char        m_strErrorMsg[256];
        int         m_nOrderID;         //指令ID
        int         m_nRequestID;
    };

    struct XT_API_EXPORT CCancelError
    {
        CCancelError();
        ~CCancelError();
        
        char        m_strAccountID[32];
        int         m_nErrorID;
        char        m_strErrorMsg[256];
        int         m_nOrderID;         //指令ID
        int         m_nRequestID;
    };

    struct XT_API_EXPORT CPriceData
    {
        CPriceData();
        ~CPriceData();

        char        m_strTradingDay[16];        //交易日
        char        m_strExchangeID[16];        //交易所代码
        char        m_strInstrumentID[32];      //合约代码
        char        m_strInstrumentName[64];    //合约名称
        char        m_strExchangeInstID[16];    //合约在交易所的代码
        double      m_dLastPrice;               //最新价
        double      m_dUpDown;                  //涨跌
        double      m_dUpDownRate;              //涨跌幅
        double      m_dAveragePrice;            //当日均价
        int         m_nVolume;                  //数量
        double      m_dTurnover;                //成交金额
        double      m_dPreClosePrice;           //昨收盘
        double      m_dPreSettlementPrice;      //上次结算价
        double      m_dPreOpenInterest;         //昨持仓量
        double      m_dOpenInterest;            //持仓量
        double      m_dSettlementPrice;         //本次结算价
        double      m_dOpenPrice;               //今开盘
        double      m_dHighestPrice;            //最高价
        double      m_dLowestPrice;             //最低价
        double      m_dClosePrice;              //今收盘
        double      m_dUpperLimitPrice;         //涨停板价
        double      m_dLowerLimitPrice;         //跌停板价
        double      m_dPreDelta;                //昨虚实度
        double      m_dCurrDelta;               //今虚实度
        char        m_strUpdateTime[32];        //最后修改时间
        int         m_nUpdateMillisec;          //最后修改毫秒
        double      m_dBidPrice1;               //申买价一
        int         m_nBidVolume1;              //申买量一
        double      m_dAskPrice1;               //申卖价一
        int         m_nAskVolume1;              //申卖量一
        double      m_dBidPrice2;               //申买价二
        int         m_nBidVolume2;              //申买量二
        double      m_dAskPrice2;               //申卖价二
        int         m_nAskVolume2;              //申卖量二
        double      m_dBidPrice3;               //申买价三
        int         m_nBidVolume3;              //申买量三
        double      m_dAskPrice3;               //申卖价三
        int         m_nAskVolume3;              //申卖量三
        double      m_dBidPrice4;               //申买价四
        int         m_nBidVolume4;              //申买量四
        double      m_dAskPrice4;               //申卖价四
        int         m_nAskVolume4;              //申卖量四
        double      m_dBidPrice5;               //申买价五
        int         m_nBidVolume5;              //申买量五
        double      m_dAskPrice5;               //申卖价五
        int         m_nAskVolume5;              //申卖量五
        double      m_dPrePrice;                //前一次的价格
    };

    struct XT_API_EXPORT COrdinaryOrder
    {
        COrdinaryOrder();
        ~COrdinaryOrder();
        char            m_strAccountID[32];     // 资金账户ID，如果为子账户，则为子账户ID
        double          m_dPrice;               // 指定价，仅在报价方式为PRTP_FIX(指定价)时有效;
        double          m_dSuperPriceRate;      // 单笔超价百分比
        int             m_nVolume;              // 委托量, 直接还券的数量
        char            m_strMarket[32];        // 合约市场
        char            m_strInstrument[32];    // 委托合约.
        EPriceType      m_ePriceType;           // 报价方式： 指定价，最新价 对手价……
        EOperationType  m_eOperationType;       // 下单类型，开、平、买、卖…
        EHedgeFlagType  m_eHedgeFlag;           // 套利标志
        double          m_dOccurBalance;        //直接还款的金额 //仅直接还款用
        EXtOverFreqOrderMode m_eOverFreqOrderMode; //委托频率过快时的处理方式
    };

    struct XT_API_EXPORT CAlgorithmOrder
    {
        CAlgorithmOrder();
        ~CAlgorithmOrder();
        char                m_strAccountID[32];     //账号
        char                m_strMarket[32];        //市场
        char                m_strInstrument[32];    //合约
        double              m_dPrice;
        double              m_dSuperPriceRate;      //单笔超价比率
        int                 m_nSuperPriceStart;     //超价起始笔数
        double              m_dPriceRangeRate;      //波动区间  比率
        int                 m_nVolume;              //量
        double              m_dSingleVolumeRate;    //单比下单比率
        int                 m_nSingleNumMin;        //单比下单量最小值
        int                 m_nSingleNumMax;        //单比下单量最大值
        int                 m_nLastVolumeMin;       //尾单最小量
        double              m_dPlaceOrderInterval;  //下单间隔
        double              m_dWithdrawOrderInterval; //撤单间隔
        int                 m_nMaxOrderCount;       //最大下单次数，与下单间隔相对应
        int                 m_nValidTimeStart;      //有效开始时间 来自股票，待定
        int                 m_nValidTimeEnd;        //有效结束时间 来自股票，待定
        EOperationType      m_eOperationType;       //下单操作：开平、多空……
        EVolumeType         m_eSingleVolumeType;    //单笔下单基准
        EPriceType          m_ePriceType;           //报价方式：对手、最新……
        EHedgeFlagType      m_eHedgeFlag;           /// 套利标志
        EXtOverFreqOrderMode m_eOverFreqOrderMode; //委托频率过快时的处理方式
    };

    struct XT_API_EXPORT CGroupOrder
    {
        CGroupOrder();
        ~CGroupOrder();
        CAlgorithmOrder         m_orderParam;  //下单配置
        char        m_strMarket[500][32];      //市场列表
        char        m_strInstrument[500][32];  //证券代码
        int         m_nVolume[500];            //每只股票的下单量
        int         m_nOrderNum;               //股票只数
    };

    struct XT_API_EXPORT CStkCompacts
    {
        CStkCompacts();
        ~CStkCompacts();
        char            m_strAccountID[32];         //账号
        char            m_strExchangeID[32];        //交易所
        char            m_strInstrumentID[32];      //证券代码
        int             m_nOpenDate;                //合约开仓日期
        char            m_strCompactId[32];         //合约编号
        double          m_dCrdtRatio;               //融资融券保证金比例
        char            m_strEntrustNo[32];         //委托编号
        double          m_dEntrustPrice;            //委托价格
        int             m_nEntrustVol;              //委托数量
        int             m_nBusinessVol;             //合约开仓数量
        double          m_dBusinessBalance;         //合约开仓金额
        double          m_dBusinessFare;            //合约开仓费用
        EXTCompactType  m_eCompactType;             //合约类型
        EXTCompactStatus    m_eCompactStatus;       //合约状态
        double          m_dRealCompactBalance;      //未还合约金额
        int             m_nRealCompactVol;          //未还合约数量
        double          m_dRealCompactFare;         //未还合约费用
        double          m_dRealCompactInterest;     //未还合约利息
        double          m_dRepaidInterest;          //已还利息
        int             m_nRepaidVol;               //已还数量
        double          m_dRepaidBalance;           //已还金额
        double          m_dCompactInterest;         //合约总利息
        double          m_dUsedBailBalance;         //占用保证金
        double          m_dYearRate;                //合约年利率
        int             m_nRetEndDate;              //归还截止日
        char            m_strDateClear[32];         //了结日期
        double          m_dPrice;                   //最新价
        int             m_nOpenTime;                //开仓的时间，不展示，部分券商可能用的上
        int             m_nCancelVol;               //合约对应的委托的撤单数量
        EBrokerPriceType    m_nOrderPriceType;      //类型，例如市价单 限价单
        EOffsetFlagType   m_nOffsetFlag;            //操作,开平,买卖,操作
    };

    struct XT_API_EXPORT CStkSubjects
    {
        CStkSubjects();
        ~CStkSubjects();
        char                m_strAccountID[32];         //账号
        char                m_strExchangeID[32];        //市场
        char                m_strInstrumentID[32];      //合约
        double              m_dSloRatio;                //融资融券保证金比例
        EXTSubjectsStatus   m_eSloStatus;               //融券状态
        int                 m_nEnableAmount;            //融券可融数量
        double              m_dFinRatio;                //融资保证金比例
        EXTSubjectsStatus   m_eFinStatus;               //融资状态
        double              m_dAssureRatio;             //担保品折算比例
        EXTSubjectsStatus   m_eAssureStatus;            //是否可做担保
        double              m_dFinRate;                 //融资日利率
        double              m_dSloRate;                 //融券日利率
        double              m_dFinPenaltyRate;          //融资日罚息利率
        double              m_dSloPenaltyRate;          //融券日罚息利率
    };

    struct XT_API_EXPORT CCoveredStockPosition
    {
        CCoveredStockPosition();
        ~CCoveredStockPosition();

        char        m_strAccountID[32];         //账号
        char        m_strExchangeID[16];        //交易类别
        char        m_strExchangeName[16];      //市场名字
        char        m_strInstrumentID[32];      //合约代码
        char        m_strInstrumentName[64];    //合约名称
        int         m_nTotalAmount;             //总持仓量
        int         m_nLockAmount;              //锁定量
        int         m_nUnlockAmount;            //未锁定量
    };

    struct XT_API_EXPORT CProductData
    {
        CProductData();
        ~CProductData();
        int         m_nProductId;               // 迅投产品ID
        double      m_dTotalNetValue;           // 产品净资产, 产品净值
        double      m_dBalance;                 // 当前资金余额（期货的动态权益和证券的可用）
        double      m_dPreBalance;              // 期初资金余额（期货静态权益和证券的资金余额）
        double      m_dAvaliableFuture;         // 期货帐号的可用资金之和
        double      m_dCurrMargin;              // 期货账号占用保证金
        double      m_dBalancefuture;           // 期货动态权益之和
        double      m_dStockValue;              // 股票总市值
        double      m_dLoanValue;               // 债券总市值，期货没有
        double      m_dFundValue;               // 基金总市值，包括ETF和封闭式基金，期货没有
        double      m_dRepurchaseValue;         // 回购总市值，所有回购，期货没有
    };
}

#endif
