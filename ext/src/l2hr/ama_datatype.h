/**
 * @file         ama_datatype.h
 * @author       郭光葵
 * @mail         guoguangkui@archforce.com.cn
 * @created time Thu 21 Sep 2017 09:52:50 AM CST
 *
 * Copyright (c) 2018 Archforce Financial Technology.  All rights reserved.
 * Redistribution and use in source and binary forms, with or without  modification, are not permitted.
 * For more information about Archforce, welcome to archforce.cn.
 */

#ifndef AMD_AMA_DATATYPE_H_
#define AMD_AMA_DATATYPE_H_

#include <stdint.h>
namespace amd { namespace ama {

#define ID_BT_INDEX                   "01000"   //指数
#define ID_BT_SHARES_A                "02001"   //主板A股	                  
#define ID_BT_SHARES_B                "02002"   //主板B股	                  
#define ID_BT_SHARES_G                "02003"   //创业板股	                  
#define ID_BT_SHARES_KCB              "02004"   //科创板股	                  
#define ID_BT_SHARES_LIST             "02005"   //股转系统挂牌股	            
#define ID_BT_SHARES_PRE              "02006"   //优先股	                    
#define ID_BT_SHARES_PZ_ZB            "02007"   //主板存托凭证	              
#define ID_BT_SHARES_PZ_CYB           "02008"   //创业板存托凭证	            
#define ID_BT_SHARES_PZ_KCB           "02009"   //科创板存托凭证	            
#define ID_BT_SHARES_OTE              "02999"   //其他股票	                  
#define ID_BT_FUND_ET                 "03001"   //交易型开放式指数基金（ETF） 
#define ID_BT_FUND_LO                 "03002"   //上市型开放式基金（LOF）	    
#define ID_BT_FUND_GR                 "03003"   //分级子基金	                
#define ID_BT_FUND_OPE                "03004"   //未上市开放基金（仅申赎）	  
#define ID_BT_FUND_CLOS               "03005"   //封闭式基金	                
#define ID_BT_FUND_REIT               "03006"   //基础设施基金（REITs）	      
#define ID_BT_FUND_OT                 "03999"   //其他基金	                  
#define ID_BT_BOND_CO                 "04001"   //可转债	                    
#define ID_BT_BOND_N                  "04002"   //国债（含地方债）	          
#define ID_BT_BOND_COM                "04003"   //公司债	                    
#define ID_BT_BOND_EN                 "04004"   //企业债	                    
#define ID_BT_BOND_P                  "04005"   //私募债	                    
#define ID_BT_BOND_PP_E	              "04006"   //可交换私募债	             	
#define ID_BT_BOND_COM_S              "04007"   //证券公司次级债	           	
#define ID_BT_BOND_S                  "04008"   //证券公司短期债	            
#define ID_BT_BOND_OT                 "04999"   //其他债券	                  
#define ID_BT_REPO_ZY                 "05001"   //质押式回购	                
#define ID_BT_REPO_BOND_MD            "05002"   //买断式债券回购	            
#define ID_BT_REPO_B                  "05003"   //报价回购	                  
#define ID_BT_OPTION_C_G              "06001"   //个股认购期权	              
#define ID_BT_OPTION_P_G              "06002"   //个股认沽期权	              
#define ID_BT_OPTION_C_ID             "06003"   //指数认购期权	              
#define ID_BT_OPTION_P_IDX            "06004"   //指数认沽期权
#define ID_BT_OPTION_C_CMD            "06005"   //商品认购期权
#define ID_BT_OPTION_P_CM             "06006"   //商品认沽期权
#define ID_BT_FUTURE                  "06007"   //期货
#define ID_BT_FUTURE_I                "06008"   //指数期货(规划中)
#define ID_BT_FUTURE_SY               "06009"   //组合
#define ID_BT_FUTURE_SP               "06010"   //即期
#define ID_BT_EFPs                    "06011"   //期转现
#define ID_BT_TAS                     "06012"   //TAS
#define ID_BT_Q                       "07001"   //权证	                      
#define ID_BT_X                       "07002"   //信托	                      
#define ID_BT_BB_G                    "07003"   //港股股本	                  
#define ID_BT_PLAN_CA                 "99001"   //集合资产管理计划	          
#define ID_BT_AB                      "99002"   //资产支持证券	              
#define ID_BT_C                       "99003"   //控制指令	   


/*
 * @brief property 配置项枚举
 */
namespace property
{
    /*
        设置各数据通道关键线程绑核参数，格式为CPU核的列表,比如"3,4"，表示使用第三与第四个 CPU，避免与非关键线程资源抢占影响性能.
        case 1: 设置的CPU核列表中数量小于实际关键线程数, 只会绑定部分关键线程，同时会有告警.
        case 2: 如果设置的CPU核列表中数量大于实际关键线程数,会随机绑定列表中的cpu.
        case 3: 建议绑核列表中的cpu先进行孤立,避免其他程序抢占cpu资源。
                (linux孤立CPU步骤:  1. 找到系统grub文件,一般路径为/etc/default/grub,具体路径以实际为准 
                                    2. sudo vi /etc/default/grub, 以孤立cpu 3,4为例, GRUB_CMDLINE_LINUX="isolcpus=3,4 nohz_full=3,4 rcu_nocbs=3,4"
                                    3. 生成新的grub引导文件: sudo grub2-mkconfig -o /boot/grub2/grub.cfg
                                    4. 重启系统,生效孤立配置)
        note: 绑核暂时只对linux 系统生效,windows 系统暂时不支持绑核操作
    */
    static const char* const kTCPThreadAffinity = "TCPThreadAffinity";              // 将TCP数据通道内关键处理线程绑定到CPU核(关键线程数量为2)
    static const char* const kUDPThreadAffinity = "UDPThreadAffinity";              // 将UDP数据通道内关键处理线程绑定到CPU核(关键线程数量为2)
    static const char* const kAMIThreadAffinity = "AMIThreadAffinity";              // 将AMI数据通道内关键处理线程绑定到CPU核(关键线程数量为3)
    static const char* const kFPGAThreadAffinity = "FPGAThreadAffinity";            // 将FPGA数据通道内关键处理线程绑定到CPU核(关键线程数量视实际情况而定)
                                                                                    // note: 正常启动原地递交模式单路FPGA关键线程数为1,其他情况按实际情况设置
    static const char* const kMDDPThreadAffinity = "MDDPThreadAffinity";            // 将MDDP数据通道内关键处理线程绑定到CPU核(单组播端口关键线程数量为1,其他情况按实际情况设置)
    static const char* const kOrderBookThreadAffinity = "OrderBookThreadAffinity";  // 将委托簿本地构建关键处理线程绑定到CPU核(关键线程数为设置的委托簿线程数量*2*市场数量)
};

class MarketType
{
public:

    /**
     * @brief 市场类型定义
     */
    enum 
    { 
        kNone       = 0,                ///< 表示全市场 
        kNEEQ       = 2,                ///< 北交所
        kSHFE       = 3,                ///< 上期所
        kCFFEX      = 4,                ///< 中金所
        kDCE        = 5,                ///< 大商所
        kCZCE       = 6,                ///< 郑商所
        kINE        = 7,                ///< 上期能源
        kNASDAQ     = 12,               ///< 纳交所
        kSSE        = 101,              ///< 上交所
        kSZSE       = 102,              ///< 深交所
        kHKEx       = 103,              /* < 港交所(港股通行情数据通过深交所和上交所的港股通获取, 市场类型为kSZSE/kSSE,
                                                商业港股行情对应的市场类型为kHKEx) */
        kCFETS      = 104,              ///< 银行间市场
        kMax        = 150               ///< 市场类型最大值
    };
};

class OrderBookType {
public:
    /**
     * @brief 委托簿构建类型定义
     */
    static const uint8_t kNone                                 = 0;   // 不开启委托簿
    static const uint8_t kLocalOrderBook                       = 1;   // 本地构建委托簿,向服务端请求同步初始状态(需要订阅相应的逐笔成交和逐笔委托)
    static const uint8_t kServerOrderBook                      = 2;   // 服务端远程TCP方式推送委托簿数据
};

class VarietyCategory {
public:
    /**
     * @brief 品种类型定义
     */
    static const uint8_t kNone                                 = 0;   // None
    static const uint8_t kStock                                = 1;   // 股票
    static const uint8_t kFund                                 = 2;   // 基金
    static const uint8_t kBond                                 = 3;   // 债券
    static const uint8_t kOption                               = 4;   // 期权
    static const uint8_t kIndex                                = 5;   // 指数
    static const uint8_t kHKT                                  = 6;   // 港股通
    static const uint8_t kFutureOption                         = 7;   // 期货期权
    static const uint8_t kCFETSRMB                             = 8;   // 银行间本币交易产品
    static const uint8_t kHKEx                                 = 9;   // 商业港股
    static const uint8_t kOthers                               = 255; // 其他
};

class LogLevel
{
public:
    /**
     * @brief 日志输出级别定义
     */
    enum { kTrace = 0, kDebug = 1, kInfo  = 2, kWarn  = 3, kError = 4, kFatal = 5, };
};

class ErrorCode
{
public:

    /**
     * @brief 函数返回值定义，请结合输出日志
     */
    enum
    {
        kFailure = -100,                                    // 失败
        kInited,                                            // 已初始化
        kUnInited,                                          // 未初始化
        kNullSpi,                                           // 未设置输出数据类指针
        kParamIllegal,                                      // 参数非法
        kSuccess = 0,                                       // 成功
    };
};

/**
 * @name 数据长度定义
 * @{ */
class ConstField
{
public:
    static const uint32_t kIPMaxLen              = 24;       // IP地址的最大长度
    static const uint32_t kUsernameLen           = 32;       // 用户名的最大长度
    static const uint32_t kUMSItemLen            = 8;        // 服务项信息的最大个数
    static const uint32_t kChannelExternCfgLen   = 16;       // 通道扩展配置的最大个数
    static const uint32_t kPasswordLen           = 64;       // 用户名的最大长度
    static const uint32_t kSecurityCodeLen       = 16;       // 证券代码最大长度
    static const uint32_t kFutureSecurityCodeLen = 32;       // 期货证券代码最大长度
    static const uint32_t kSecurityNameLen       = 32;       // 证券名称最大长度
    static const uint32_t kPositionLevelLen      = 10;       // 行情档位
    static const uint32_t kHKExPositionLevelLen  = 40;       // 行情档位
    static const uint32_t kPathLen               = 255;      // 文件路径最大长度
    static const uint32_t kConfirmIdLen          = 8;        // 定价行情约定号 为空表示意向行情 否则为定价行情
    static const uint32_t kContactorLen          = 12;       // 联系人
    static const uint32_t kContactInfoLen        = 30;       // 联系方式
    static const uint32_t kTradingPhaseCodeLen   = 8;        // 交易状态标志
    static const uint32_t kContractIDLen         = 48;       // 合约交易代码
    static const uint32_t kContractSymbolLen     = 32;       // 期权合约简称
    static const uint32_t kUnderlyingTypeLen     = 3;        // 标的证券类型
    static const uint32_t kSecurityStatusFlagLen = 8;        // 期权合约状态信息标签
    static const uint32_t kExChangeInstIDLen     = 31;
    static const uint32_t kMaxMarketType         = 255;
    static const uint32_t kTradingStatusLen      = 8;
    static const uint32_t kSecurityStatusLen     = 8;
    static const uint32_t kMDStreamIDMaxLen      = 6;
    static const uint32_t kTypesLen = 8;
    static const uint32_t kDateLen = 10;
    static const uint32_t kTimeLen = 10;
    static const uint32_t kSecurityAbbreviationLen = 64;       // 证券简称最大长度
    static const uint32_t kSymbolLen = 128;                    // 证券简称最大长度（包括中文简称）
    static const uint32_t kMaxTypesLen = 16;                   // 证券类型最大长度
    static const uint32_t kMDStreamIDLen = 6;
    static const uint32_t kUnitName = 128;
    static const uint32_t kSubTradingPhaseLen = 8;      //债券细分交易阶段个数最大值
    static const uint32_t kQuoteIDLen = 10;             //债券逐笔报价消息编号长度
    static const uint32_t kMemberIDLen = 6;             //债券逐笔交易场代码长度
    static const uint32_t kInvestorTypeLen = 2;         //债券逐笔交易主体类型长度
    static const uint32_t kInvestorIDLen = 10;          //债券逐笔交易主体代码长度
    static const uint32_t kInvestorNameLen = 120;       //债券逐笔客户名称长度
    static const uint32_t kTraderCodeLen = 8;           //债券逐笔交易员代码程度
    static const uint32_t kSecondaryOrderIDLen = 16;    //债券逐笔竞买场次编号
    static const uint32_t kCodeTableSecurityStatusMaxLen = 16;      //代码表证券状态字符最大长度
    static const uint32_t KSecurityMarketLen = 4;                   //证券所属市场长度
    static const uint32_t kConsSecurityCodeLen = 32;                //成份证券代码长度
    static const uint32_t kSymbolETFLen = 128;                      //基金名称长度
    static const uint32_t kManagmentETFLen = 128;                   //基金公司名称长度
    static const uint32_t KUnderlyingSecurityIDSource = 4;          //拟合指数代码源长度
    static const uint32_t KUnderlyingSecurityID = 4;                //成分股所属市场ID长度
    static const uint32_t KReserved = 30;                           //预留字段长度
    static const uint32_t AllCashAmount = 12;                       //全现金替代的总金额长度
    static const uint32_t AllCashAremiumRate = 7;                   //全现金替代的申购溢价比例长度
    static const uint32_t AllCashDiscountRate = 7;                  //全现金替代的赎回折价比例长度
    static const uint16_t DefaultMaxOBSubNum = 500;                 //委托簿默认最大订阅数量
    static const uint16_t DefaultMaxOBSnapshotSubNum = 3000;        //委托簿快照默认最大订阅数量
    static const uint16_t DefaultMaxOBOrderQueueSize = 50;          //每一档委托队列数量上限
    static const uint16_t DefaultMaxOBEntrySize = 20;               //委托簿档位数量上限
    static const uint16_t DefaultMaxOBDeliverIntervalMs = 50;       //委托簿最小推送间隔
    static const uint16_t DefaultMinOBSnapshotDeliverIntervalMs = 10; //委托簿快照最小推送间隔
    static const uint16_t RegularShare = 9;                         //对应回购标准券长度
    static const uint32_t kTradePlaceLen = 3;                       //交易场所长度 

    //银行间
    static const uint32_t kCFETSSecurityCodeLen = 32;               // 银行间证券代码最大长度
    static const uint32_t kExecIDLen = 64;                          // 成交编号最大长度
    static const uint32_t kSecurityGroupLen = 32;                   // 交易品种最大长度
    static const uint32_t kBenchmarkCurveNameLen = 32;              // 参考利率最大长度
    static const uint32_t kUnderlyingSecurityCodeLen = 32;          // 标的券代码最大长度
    static const uint32_t kUnderlyingSymbolLen = 24;                // 标的券名称最大长度
    static const uint32_t kTradeLimitDaysLen = 16;                  // 交易期限最大长度
    static const uint32_t kMsgTypeLen = 6;                          // 报文类型最大长度
    static const uint32_t kTransactionMethodLen = 6;                // 成交方向最大长度
    static const uint32_t kMarketIndicatorLen = 4;                  // 市场标识最大长度
    static const uint32_t kSettlTypeLen = 8;                        // 清算速度最大长度
    static const uint32_t kExecTypeLen = 4;                         // 成交方式最大长度
    static const uint32_t kSecurityTypeLen = 12;                    // 证券类型最大长度
    static const uint32_t kSettlCurrencyLen = 4;                    // 币种长度
    static const uint32_t kPartyIDLen = 32;                         // 交易账户21位代码长度
    static const uint32_t kMatchTypeLen = 4;                        // 报价方式最大长度
    static const uint32_t kPositionLevel6 = 6;                      // 报价档位
    static const uint32_t kDireciveLevelLen = 5;                    // 行情档位     
    static const uint32_t kQuoteEntryIDLen = 64;                    // 报价编号最大长度
    static const uint32_t kAccountSubjectTypeLen = 4;               // 成交方式最大长度
    static const uint32_t kAccountIDLen = 8;                        // 交易账户6位码
    static const uint32_t kTraderIDLen = 64;                        // 交易员ID
    
    static const uint32_t kDescLen = 48;                            // 债券类型长度
    static const uint32_t kSymLen = 111;                            // 工具简称长度
    static const uint32_t kIDLen = 51;                              // 工具代码长度
    static const uint32_t kRDISecurityCodeLen = 51;                 // RDI证券代码长度
    static const uint32_t kSecuritTypeCodeLen = 7;                  // 债券类型代码长度
    static const uint32_t kTermToMaturityStringLen = 16;            // 标准待偿期长度
    static const uint32_t kTermToMaturityLen = 48;                  // 待偿期长度
    static const uint32_t kIssuerCodeLen = 7;                       // 发行人代码长度
    static const uint32_t kCreditRatingAgencyLen = 101;             // 信用评级机构长度
    static const uint32_t kCrdRtgLen = 5;                           // 信用评级长度
    static const uint32_t kIssrLen = 121;                           // 发行机构简称中文长度
    static const uint32_t kEvntGrpLen = 7;                          // 行权类型长度
    static const uint32_t kCcyLen = 5;                              // 币种长度
    static const uint32_t kSecTypLen = 5;                           // 工具类型长度
    static const uint32_t kUndlyLen = 6;                            // 期限品种长度
    static const uint32_t kApplicableTrdgModelLen = 5;              // 适用交易方式长度
    static const uint32_t kDataLen = 48;                            // 日期长度

    // 港股
    static const uint32_t kDetailLen = 40;                          // 经纪明细数组长度
    static const uint32_t kBrokerNumLen = 5;                        // 席位号长度
    static const uint32_t kMarketLen = 3;                           // 市场类型
    static const uint32_t kDirLen = 3;                              // 交易方向长度

    // 美股
    static const uint32_t kUsaTradeStatusLen = 8;                   // 交易状态长度
    static const uint32_t kUsaExecTypeLen = 5;                      // 成交类型长度

    // 上海固收行情
    static const uint32_t kFixedIncomeOrderCodeLen = 11;            // 订单编号长度
    static const uint32_t kFixedIncomeQuoteIDLen = 16;              // 报价方长度
};
/**  @} */

class HighAvailableMode
{
public:
    enum 
    {
        kMasterSlaveA        = 0,                           // 主备切换模式的A模式，该模式下只要高优先级通道可用则一直使用，即使当前在低优先级时也立马切换高优先级
        kMasterSlaveB        = 1,                           // 主备切换模式的B模式，该模式下仅在每次出现切换时选择可用的高优先级的通道，否则不执行切换动作
        kRegularDataFilter   = 2                            // 规则数据过滤模式，该模式下对单独类型数据中的特征值做过滤，比如逐笔数据中根据通道号和逐笔序号执行数据过滤
    };
};

class ChannelMode
{
public:
    static const uint64_t kRDMA = 0x00000001;               // RDMA 抓包方式获取数据
    static const uint64_t kEXA  = 0x00000002;               // EXA 抓包方式获取数据
    static const uint64_t kAMI  = 0x00000004;               // AMI 组播方式获取数据
    static const uint64_t kTCP  = 0x00000008;               // TCP 流方式获取数据
    static const uint64_t kPCAP = 0x00000010;               // Libpcap 抓包方式获取数据
    static const uint64_t kMDDP = 0x00000020;               // Mddp 组播方式获取数据
    static const uint64_t kFPGA = 0x00000040;               // FPGA 方式获取数据
    static const uint64_t kUDP =  0x00000080;               // AMD组播方式获取数据
};

class SubscribeType
{
public:
    enum
    {
        kSet,                                               // 重新设置订阅(先取消所有旧订阅信息, 然后增加新订阅信息)
        kAdd,                                               // 增加订阅
        kDel,                                               // 删除订阅
        kCancelAll                                          // 取消所有订阅
    };
};

//权限订阅数据类型
class SubscribeDataType
{
public:
    static const uint64_t kNone                                 = 0x000000000000;    ///< 订阅全部数据
    static const uint64_t kSnapshot                             = 0x000000000001;    ///< 订阅现货快照数据
    static const uint64_t kTickExecution                        = 0x000000000002;    ///< 订阅逐笔成交数据
    static const uint64_t kTickOrder                            = 0x000000000004;    ///< 订阅逐笔委托数据
    static const uint64_t kOrderQueue                           = 0x000000000008;    ///< 订阅委托队列数据
    static const uint64_t kIndexSnapshot                        = 0x000000000010;    ///< 订阅指数快照数据
    static const uint64_t kFutureSnapshot                       = 0x000000000020;    ///< 订阅期货快照数据
    static const uint64_t kOptionSnapshot                       = 0x000000000040;    ///< 订阅期权快照数据   
    static const uint64_t kHKTSnapshot                          = 0x000000000080;    ///< 订阅港股通快照数据
    static const uint64_t kAfterHourFixedPriceSnapshot          = 0x000000000100;    ///< 订阅盘后定价快照数据
    static const uint64_t kAfterHourFixedPriceTickExecution     = 0x000000000400;    ///< 订阅上交所盘后定价逐笔成交数据
    static const uint64_t kCSIIndexSnapshot                     = 0x000000000800;    ///< 订阅中证指数快照数据
    static const uint64_t kNEEQSnapshot                         = 0x000000001000;    ///< 订阅北交所快照数据
    static const uint64_t kFundExpertSnapshot                   = 0x000000002000;    ///< 订阅基金通快照数据
    static const uint64_t kCFETSSnapshot                        = 0x000000004000;    ///< 订阅银行间CFETS快照
    static const uint64_t kCFETSTickExecution                   = 0x000000008000;    ///< 订阅银行间CFETS逐笔  
    static const uint64_t kHKExSnapshot                         = 0x000000010000;    ///< 订阅商业港股行情快照
    static const uint64_t kHKExTickExecution                    = 0x000000020000;    ///< 订阅商业港股行情逐笔
    static const uint64_t kCFETSPrivateMarket                   = 0x000000040000;    ///< 订阅银行间本币私有行情
    static const uint64_t kUsaSnapshot                          = 0x000000080000;    ///< 订阅美股快照行情
    static const uint64_t kFixedIncomeSnapshot                  = 0x000000100000;    ///< 订阅固定收益快照数据
    static const uint64_t kHKExConnectTurnoverSnapshot          = 0x000000200000;    ///< 订阅商业港股港股通成交额快照
    static const uint64_t kHKMarketStatus                       = 0x000000400000;    ///< 订阅港股通市场状态数据
    static const uint64_t kHKTRealtimeLimit                     = 0x000000800000;    ///< 订阅港股通实时额度数据
};

//品种订阅数据类型
class SubscribeSecuDataType
{
public:
    static const uint64_t kNone                                 = 0x000000000000;    ///< 订阅全部证券数据类别
    static const uint64_t kSnapshot                             = 0x000000000001;    ///< 订阅所有快照数据类别(eg:包括SubscribeDataType::kSnapshot在内的所有快照数据类型)
    static const uint64_t kTickExecution                        = 0x000000000002;    ///< 订阅所有逐笔成交数据(eg:包括SubscribeDataType::kTickExecution在内的所有逐笔成交数据类型)
    static const uint64_t kTickOrder                            = 0x000000000004;    ///< 订阅所有逐笔委托数据(eg:包括SubscribeDataType::kTickOrder在内的所有逐笔委托数据类型)
    static const uint64_t kOrderQueue                           = 0x000000000008;    ///< 订阅委托队列数据
};

//品种订阅品种类型
class SubscribeCategoryType
{
public:
    static const uint64_t kNone                                 = 0x000000000000;    ///< 订阅全部证券品种类别
    static const uint64_t kStock                                = 0x000000000001;    ///< 订阅股票证券品种类别
    static const uint64_t kFund                                 = 0x000000000002;    ///< 订阅基金证券品种类别
    static const uint64_t kBond                                 = 0x000000000004;    ///< 订阅债券证券品种类别
    static const uint64_t kIndex                                = 0x000000000008;    ///< 订阅指数证券品种类别
    static const uint64_t kHKT                                  = 0x000000000010;    ///< 订阅港股通证券品种类别
    static const uint64_t kOption                               = 0x000000000020;    ///< 订阅期权证券品种类别
    static const uint64_t kFutureOption                         = 0x000000000040;    ///< 订阅期货/期货期权证券品种类别
    static const uint64_t kCFETSRMB                             = 0x000000000080;    ///< 订阅银行间本币交易产品品种类别
    static const uint64_t kHKEx                                 = 0x000000000100;    ///< 订阅商业港股证券品种类别
    static const uint64_t kOthers                               = 0x100000000000;    ///< 订阅其他证券品种类别
};

//衍生数据订阅数据类型
class SubscribeDerivedDataType
{
public:
    static const uint32_t kOrderBook                            = 1;    ///< 订阅委托簿数据
    static const uint32_t kOrderBookSnapshot                    = 2;    ///< 订阅委托簿快照数据
    static const uint32_t kIOPVSnapshot                         = 3;    ///< 订阅IOPV快照数据
};

//委托簿订阅数据类型
class SubscribeOrderBookDataType
{
public:
    static const uint64_t kNone                                 = 0x000000000000;    ///< 订阅全部委托簿数据类型(kOrderBook,kOrderBookSnapshot)
    static const uint64_t kOrderBook                            = 0x000000000001;    ///< 订阅委托簿数据
    static const uint64_t kOrderBookSnapshot                    = 0x000000000002;    ///< 订阅委托簿快照数据
};

class EventLevel
{
public:
    /**
     * @brief 事件级别定义
     */
    enum
    {
        kInfo  = 1, ///< 普通事件
        kWarn  = 2, ///< 告警事件
        kError = 3  ///< 错误事件，比较严重，需要介入处理
    };
};

class TradingPhaseCode 
{
public:
    /**
     * @brief 华锐自定义trading_phase_code
     */
    static const uint16_t kStart                      = 1;          //启动（开市前）
    static const uint16_t kOpenAuction915             = 2;          //开盘集合竞价[09:15-09:20)
    static const uint16_t kOpenAuction920             = 3;          //开盘集合竞价[09:20-09:25)
    static const uint16_t kOpenAuction925             = 4;          //开盘集合竞价[09:25-09:30)
    static const uint16_t kContTrading                = 5;          //连续竞价
    static const uint16_t kLunchBreak                 = 6;          //休市
    static const uint16_t kCloseAuction               = 7;          //收盘集合竞价
    static const uint16_t kEndOfTrade                 = 8;          //闭市
    static const uint16_t kVolatility                 = 9;          //波动性中断
    static const uint16_t kHalt                       = 10;         //停牌（含全天停牌和临时停牌）
    static const uint16_t kOther                      = 99;         //其他
};



class EventCode
{
public:
    enum
    {
        /*--------------------------与UMS会话层事件信息------------------------------*/
        kUMSConnectSuccess                  = 1,                    // 连接UMS成功
        kUMSConnectFailed,                                          // 连接UMS失败
        kUMSLogonSuccess,                                           // 登录UMS成功
        kUMSLogonFailed,                                            // 登录UMS失败
        kUMSHeartbeatTimeout,                                       // 与UMS心跳超时

        /*--------------------------硬件加速通道相关事件-----------------------------*/
        kChannelRDMAInitSuccess,                                    // RDMA通道开启成功
        kChannelRDMAInitFailed,                                     // RDMA通道开启失败
        kChannelEXAInitSuccess,                                     // EXA通道开启成功
        kChannelEXAInitFailed,                                      // EXA通道开启失败
        kChannelPCAPInitSuccess,                                    // PCAP通道开启成功
        kChannelPCAPInitFailed,                                     // PCAP通道开启失败

        /*--------------------------CTP硬件加速相关事件-----------------------------*/
        kCTPDASStreamStart,                                         // 通道数据流开始
        kCTPDASStreamFinished,                                      // 通道数据流结束

        /*--------------------------SzseBinary硬件加速相关事件----------------------*/
        kSzseBinaryDASStreamStart,                                  // 通道数据流开始
        kSzseBinaryDASStreamFinished,                               // 通道数据流结束

        /*--------------------------SseLDDS硬件加速相关事件-------------------------*/
        kSseLDDSDASStreamStart,                                     // 通道数据流开始
        kSseLDDSDASStreamFinished,                                  // 通道数据流结束

        /*--------------------------AMI组播通道相关事件-----------------------------*/
        kChannelAMIInitSuccess,								        // AMI通道开启成功
        kChannelAMIInitFailed,								        // AMI通道开启失败

        /*--------------------------TCP通道相关事件---------------------------------*/
        kChannelTCPInitSuccess,								        // TCP通道开启成功
        kChannelTCPInitFailed,								        // TCP通道开启失败
        kChannelTCPConnectSuccess,								    // TCP通道连接成功
        kChannelTCPConnectFailed,								    // TCP通道连接失败
        kChannelTCPLogonSuccess,								    // TCP通道登录成功
        kChannelTCPLogonFailed,								        // TCP通道登录失败
        kChannelTCPSessionClosed,								    // TCP通道连接断开
        kChannelTCPHeartbeatTimeout,								// TCP通道会话心跳失败
        kChannelTCPMarketDataDegrade,                               // TCP通道行情数据降级
        kChannelTCPMarketDataUpgrade,                               // TCP通道行情数据升级

        /*--------------------------主备切换相关事件--------------------------------*/
        kSourceMasterSlaveChanged,                                  // 主备源切换

        /*--------------------------SFS 获取代码表相关事件--------------------------*/
        kSFSEngineInitSuccess,                                      // SFS 获取代码表模块初始化成功

        /*--------------------------AES 服务端委托薄相关事件------------------------*/
        kSzseOrderBookRejoinSuccess,                                    //深圳市场委托簿同步成功
        kSzseOrderBookRejoinFailed,                                     //深圳市场委托簿同步失败
        kSseOrderBookRejoinSuccess,                                     //上海市场委托簿同步成功
        kSseOrderBookRejoinFailed,                                      //上海市场委托簿同步失败
        kOrderBookRejonConnectFailed,                                   //连接上游aes组件失败
        kIncompleteData,                                                // 服务端委托簿以recover 方式重启，数据有可能不完整
        kOrderBookLogonSuccess,                                         // 服务端委托簿主动推送模式登陆成功(委托簿属于衍生数据，此信号后续会逐步弃用，用kDerivedDataLogonSuccess 信号代替)
        kOrderBookLogonFailed,                                          // 服务端委托簿主动推送模式登陆失败(委托簿属于衍生数据，此信号后续会逐步弃用，用kDerivedDataLogonFailed 信号代替)
        kDerivedDataLogonSuccess,                                       // 行情衍生数据服务端登陆成功
        kDerivedDataLogonFailed,                                        // 行情衍生数据服务端登陆失败       
        
        /*--------------------------FPGA通道相关事件-------------------------------*/
        kChannelFPGAInitSuccess,                                    // FPGA通道开启成功
        kChannelFPGAInitFailed,                                     // FPGA通道开启失败

        /*--------------------------UDP通道相关事件-------------------------*/
        kChannelUDPInitSuccess,								        // UDP通道开启成功
        kChannelUDPInitFailed,								        // UDP通道开启失败
        kChannelUDPConnectSuccess,								    // UDP通道连接成功
        kChannelUDPConnectFailed,								    // UDP通道连接失败
        kChannelUDPLogonSuccess,								    // UDP通道登录成功
        kChannelUDPLogonFailed,								        // UDP通道登录失败
        kChannelUDPSessionClosed,								    // UDP通道连接断开
        kChannelUDPHeartbeatTimeout,								// UDP通道会话心跳失败
        kChannelUDPMarketDataDegrade,                               // UDP通道行情数据降级
        kChannelUDPMarketDataUpgrade                                // UDP通道行情数据升级
    };
};

}; // end of ama
}; // end of amd
#endif
