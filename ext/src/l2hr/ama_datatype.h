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
        kINE        = 7,                ///< 上海国际能源交易中心
        kSSE        = 101,              ///< 上交所
        kSZSE       = 102,              ///< 深交所
        kHKEx       = 103,              ///< 港交所
        kMax        = 150               ///< 市场类型最大值
    };
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
    static const uint32_t kPathLen               = 255;      // 文件路径最大长度
    static const uint32_t kConfirmIdLen          = 8;        // 定价行情约定号 为空表示意向行情 否则为定价行情
    static const uint32_t kContactorLen          = 12;       // 联系人
    static const uint32_t kContactInfoLen        = 30;       // 联系方式
    static const uint32_t kTradingPhaseCodeLen   = 8;        // 交易状态标志
    static const uint32_t kContractIDLen         = 32;       // 合约交易代码
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
};
class SubscribeType
{
public:
    enum
    {
        kSet,                                               // 设置订阅
        kAdd,                                               // 添加订阅
        kDel,                                               // 删除订阅
        kCancelAll                                          // 取消所有订阅
    };
};

class SubscribeDataType
{
public:
    static const uint64_t kNone                                 = 0x000000000000;    ///< 订阅全部数据
    static const uint64_t kSnapshot                             = 0x000000000001;    ///< 订阅现货快照数据
    static const uint64_t kTickExecution                        = 0x000000000002;    ///< 订阅逐笔成交数据
    static const uint64_t kTickOrder                            = 0x000000000004;    ///< 订阅逐笔委托数据
    static const uint64_t kOrderQueue                           = 0x000000000008;    ///< 订阅委托队列数据
    static const uint64_t kIndexSnapshot                        = 0x000000000010;    ///< 订阅指数快照数据
    static const uint64_t kFutureSnapshot                       = 0x000000000020;    ///< 订阅期货连线数据
    static const uint64_t kOptionSnapshot                       = 0x000000000040;    ///< 订阅期权快照数据   
    static const uint64_t kHKTSnapshot                          = 0x000000000080;    ///< 订阅港股快照数据
    static const uint64_t kAfterHourFixedPriceSnapshot          = 0x000000000100;    ///< 订阅上交所盘后定价快照数据
    static const uint64_t kAfterHourFixedPriceTickExecution     = 0x000000000400;    ///< 订阅上交所盘后定价逐笔成交数据
    static const uint64_t kCSIIndexSnapshot                     = 0x000000000800;    ///< 订阅中证指数快照数据
    static const uint64_t kNEEQSnapshot                         = 0x000000001000;    ///< 订阅北交所快照数据
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

class EventCode
{
public:
    enum 
    {
        /*--------------------------与UMS会话层事件信息----------------------*/
        kUMSConnectSuccess                  = 1,                    // 连接UMS成功
        kUMSConnectFailed,                                          // 连接UMS失败
        kUMSLogonSuccess,                                           // 登录UMS成功
        kUMSLogonFailed,                                            // 登录UMS失败
        kUMSHeartbeatTimeout,                                       // 与UMS心跳超时
        
        /*--------------------------硬件加速通道相关事件----------------------*/
        kChannelRDMAInitSuccess,                                    // RDMA通道开启成功
        kChannelRDMAInitFailed,                                     // RDMA通道开启失败
        kChannelEXAInitSuccess,                                     // EXA通道开启成功
        kChannelEXAInitFailed,                                      // EXA通道开启失败
        kChannelPCAPInitSuccess,                                    // PCAP通道开启成功
        kChannelPCAPInitFailed,                                     // PCAP通道开启失败

        /*------------------------CTP硬件加速相关事件------------------------*/
        kCTPDASStreamStart,                                         // 通道数据流开始 
        kCTPDASStreamFinished,                                      // 通道数据流结束

        /*------------------------SzseBinary硬件加速相关事件------------------------*/
        kSzseBinaryDASStreamStart,                                  // 通道数据流开始
        kSzseBinaryDASStreamFinished,                               // 通道数据流结束

        /*------------------------SseLDDS硬件加速相关事件------------------------*/
        kSseLDDSDASStreamStart,                                     // 通道数据流开始
        kSseLDDSDASStreamFinished,                                  // 通道数据流结束

        /*------------------------AMI组播通道相关事件------------------------*/
        kChannelAMIInitSuccess,								        // AMI通道开启成功
        kChannelAMIInitFailed,								        // AMI通道开启失败

        /*------------------------TCP通道相关事件------------------------*/
        kChannelTCPInitSuccess,								        // TCP通道开启成功
        kChannelTCPInitFailed,								        // TCP通道开启失败
        kChannelTCPConnectSuccess,								    // TCP通道连接成功
        kChannelTCPConnectFailed,								    // TCP通道连接失败
        kChannelTCPLogonSuccess,								    // TCP通道登录成功
        kChannelTCPLogonFailed,								        // TCP通道登录失败
        kChannelTCPSessionClosed,								    // TCP通道连接断开
        kChannelTCPHeartbeatTimeout,								// TCP通道会话心跳失败
        kChannelTCPMarketDataDegrade,                              // TCP通道行情数据降级
        kChannelTCPMarketDataUpgrade,                              // TCP通道行情数据升级

        /*------------------------主备切换相关事件------------------------*/
        kSourceMasterSlaveChanged,                                  // 主备源切换
    };
};

}; // end of ama
}; // end of amd
#endif
