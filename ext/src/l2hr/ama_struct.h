/**
 * @file         ama_struct.h
 * @author       郭光葵
 * @mail         guoguangkui@archforce.com.cn
 * @created time Thu 21 Sep 2017 09:50:15 AM CST
 *
 * Copyright (c) 2018 Archforce Financial Technology.  All rights reserved.
 * Redistribution and use in source and binary forms, with or without  modification, are not permitted.
 * For more information about Archforce, welcome to archforce.cn.
 */

#ifndef AMD_AMA_STRUCT_H_
#define AMD_AMA_STRUCT_H_

#include "ama_datatype.h"

#pragma pack(push)
#pragma pack(1)

namespace amd { namespace ama {

/**
 * @name 连接UMS信息
 * @{ */
struct UMSItem
{
    char        local_ip[ConstField::kIPMaxLen];                    // 本地IP地址，为空默认为0.0.0.0
    char        server_ip[ConstField::kIPMaxLen];                   // 服务IP
    uint16_t    server_port;                                        // 服务端口
};
/**  @} */

/**
 * @name 配置定义
 * @{ */
struct Cfg
{
    //--------------------------------全局配置信息---------------------------------------------------------
    uint64_t    channel_mode;                                       // 通道模式的集合，请参考 ChannelMode，该配置为各通道模式的集合
    uint32_t    ha_mode;                                            // 高可用工作模式，请参考 HighAvailableMode
    int32_t     min_log_level;                                      // 日志最小级别，请参考 LogLevel
    bool        is_output_mon_data;                                 // 是否输出监控数据的配置，true-输出监控数据，false-不输出监控数据
    bool        is_thread_safe;                                     // 回调接口是否保证线程安全，true-启用线程安全模式执行回调接口，false-非线程安全模式执行回调接口

    bool        keep_order;                                         // 逐笔保序标志，true-开启保序，false-开启不保序
    uint32_t    keep_order_timeout_ms;                              // 逐笔保序超时时间（单位：毫秒），keep_order=true时有效
    bool        is_subscribe_full;                                  // 默认是否订阅全部数据，true-默认订阅全部，false-默认不订阅任何数据

    //-------------------------------UMS服务的连接信息------------------------------------------------------
    UMSItem     ums_servers[ConstField::kUMSItemLen];               // UMS的服务信息项，该信息不能超过10个
    uint32_t    ums_server_cnt;                                     // UMS的服务信息项个数, 小于1将启动失败
                                            
    char        username[ConstField::kUsernameLen];                 // 用户名
    char        password[ConstField::kPasswordLen];                 // 用户密码, 明文填入，密文使用

    uint32_t    tcp_compress_mode;                                  // TCP模式传输数据压缩标志，0:不压缩 1:自定义压缩 2:zstd压缩(仅TCP模式有效)

    Cfg()
    {
        channel_mode = 0;
        ha_mode = HighAvailableMode::kRegularDataFilter;
        min_log_level = LogLevel::kInfo;
        is_output_mon_data = false;
        is_thread_safe = false;
        keep_order = false;
        keep_order_timeout_ms = 3000;
        is_subscribe_full = false;
        ums_server_cnt = 0;
        tcp_compress_mode = 0;
    }
};
/**  @} */

/**
 * @name 订阅数据项定义
 * @{ */
struct SubscribeItem
{
    int32_t market;                                                 // 市场类型，参考 MarketType, 为0表示订阅所有支持的市场
    uint64_t flag;                                                  // 各数据类型的集合，为0表示订阅所有支持的数据类型
    char security_code[ConstField::kFutureSecurityCodeLen];         // 证券代码，为空表示订阅所有代码
};
/**  @} */

/**
 * @name 现货快照数据信息结构定义
 * @{ */
struct MDSnapshot
{
    int32_t market_type;                                                        // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                        // 证券代码
    int64_t orig_time;                                                          // 时间（YYYYMMDDHHMMSSsss)
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];               // 产品实时阶段及标志
    //************************************上海现货快照交易状态***************************************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第0位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，
    //‘E’表示闭市时段 ，‘P’表示临时停牌,
    //‘M’表示可恢复交易的熔断（盘中集合竞价）,‘N’表示不可恢复交易的熔断（暂停交易至闭市）
    //‘U’表示收盘集合竞价
    //第1位：‘0’表示此产品不可正常交易，‘1’表示此产品可正常交易。
    //第2位：‘0’表示未上市，‘1’表示已上市
    //第3位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。

    //************************************深圳现货快照交易状态***************************************************************
    //第 0位：‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int64_t pre_close_price;                                                    // 昨收价，实际值需除以1000000
    int64_t open_price;                                                         // 开盘价，实际值需除以1000000
    int64_t high_price;                                                         // 最高价，实际值需除以1000000
    int64_t low_price;                                                          // 最低价，实际值需除以1000000
    int64_t last_price;                                                         // 最新价，实际值需除以1000000
    int64_t close_price;                                                        // 收盘价，实际值需除以1000000
    int64_t bid_price[ConstField::kPositionLevelLen];                           // 申买价，实际值需除以1000000
    int64_t bid_volume[ConstField::kPositionLevelLen];                          // 申买量，实际值需除以100
    int64_t offer_price[ConstField::kPositionLevelLen];                         // 申卖价，实际值需除以1000000
    int64_t offer_volume[ConstField::kPositionLevelLen];                        // 申卖量，实际值需除以100
    int64_t num_trades;                                                         // 成交笔数
    int64_t total_volume_trade;                                                 // 成交总量，实际值需除以100
    int64_t total_value_trade;                                                  // 成交总金额，实际值需除以100000
    int64_t total_bid_volume;                                                   // 委托买入总量，实际值需除以100
    int64_t total_offer_volume;                                                 // 委托卖出总量，实际值需除以100
    int64_t weighted_avg_bid_price;                                             // 加权平均为委买价格，实际值需除以1000000
    int64_t weighted_avg_offer_price;                                           // 加权平均为委卖价格，实际值需除以1000000
    int64_t IOPV;                                                               // IOPV净值估产，实际值需除以1000000
    int64_t yield_to_maturity;                                                  // 到期收益率，实际值需除以1000
    int64_t high_limited;                                                       // 涨停价，实际值需除以1000000
    int64_t low_limited;                                                        // 跌停价，实际值需除以1000000
    int64_t price_earning_ratio1;                                               // 市盈率1，实际值需除以1000000
    int64_t price_earning_ratio2;                                               // 市盈率2，实际值需除以1000000
    int64_t change1;                                                            // 升跌1（对比昨收价），实际值需除以1000000
    int64_t change2;                                                            // 升跌2（对比上一笔），实际值需除以1000000
    int32_t channel_no;                                                         // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];
    char    instrument_status[ConstField::kTradingPhaseCodeLen];                // 当前品种交易状态
    int64_t pre_close_iopv;                                                      // 基金T-1日收盘时刻IOPV, 实际值需除以1000000
    int64_t alt_weighted_avg_bid_price;                                          // 债券加权平均委买价格, 实际值需除以1000000
    int64_t alt_weighted_avg_offer_price;                                        // 债券加权平均委卖价格, 实际值需除以1000000
    int64_t etf_buy_number;                                                      // ETF 申购笔数
    int64_t etf_buy_amount;                                                      // ETF 申购数量,实际值需除以100
    int64_t etf_buy_money;                                                       // ETF 申购金额,实际值需除以100000
    int64_t etf_sell_number;                                                     // ETF 赎回笔数
    int64_t etf_sell_amount;                                                     // ETF 赎回数量,实际值需除以100
    int64_t etf_sell_money;                                                      // ETF 赎回金额,实际值需除以100000
    int64_t total_warrant_exec_volume;                                           // 权证执行的总数量,实际值需除以100
    int64_t war_lower_price;                                                     // 债券质押式回购品种加权平均价, 实际值需除以1000000
    int64_t war_upper_price;                                                     // 权证涨停价格, 实际值需除以1000000
    int64_t withdraw_buy_number;                                                 // 买入撤单笔数
    int64_t withdraw_buy_amount;                                                 // 买入撤单数量,实际值需除以100
    int64_t withdraw_buy_money;                                                  // 买入撤单金额,实际值需除以100000
    int64_t withdraw_sell_number;                                                // 卖出撤单笔数
    int64_t withdraw_sell_amount;                                                // 卖出撤单数量,实际值需除以100
    int64_t withdraw_sell_money;                                                 // 卖出撤单金额,实际值需除以100000
    int64_t total_bid_number;                                                    // 买入总笔数
    int64_t total_offer_number;                                                  // 卖出总笔数
    int32_t bid_trade_max_duration;                                              // 买入委托成交最大等待时间
    int32_t offer_trade_max_duration;                                            // 卖出委托成交最大等待时间
    int32_t num_bid_orders;                                                      // 买方委托价位数
    int32_t num_offer_orders;                                                    // 卖方委托价位数
    int64_t last_trade_time;                                                     // 最近成交时间（为YYYYMMDDHHMMSSsss 仅上海00文件，LDDS生效）
};
/**  @} */

/**
 * @name 现货指数快照数据信息结构定义
 * @{ */
struct MDIndexSnapshot
{
    int32_t market_type;                                                        // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                        // 证券代码
    int64_t orig_time;                                                          // 时间（YYYYMMDDHHMMSSsss)
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];               // 产品实时阶段及标志（仅深圳有效）
    //************************************深圳指数快照交易状态***************************************************************
    //第 0位：‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int64_t pre_close_index;                                                     // 前收盘指数，实际值需除以1000000
    int64_t open_index;                                                          // 今开盘指数，实际值需除以1000000
    int64_t high_index;                                                          // 最高指数，实际值需除以1000000
    int64_t low_index;                                                           // 最低指数，实际值需除以1000000
    int64_t last_index;                                                          // 最新指数，实际值需除以1000000
    int64_t close_index;                                                         // 收盘指数 （仅上海有效），实际值需除以1000000
    int64_t total_volume_trade;                                                  // 参与计算相应指数的交易数量，实际值需除以100
    int64_t total_value_trade;                                                   // 参与计算相应指数的成交总金额，实际值需除以100000
    int32_t channel_no;                                                         // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                        // 行情类别
};
/**  @} */

/**
 * @name 现货逐笔委托数据信息结构定义
 * @{ */
struct MDTickOrder
{
    int32_t market_type;                                                // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                // 证券代码
    int32_t channel_no;                                                 // 频道号
    int64_t appl_seq_num;                                               // 频道索引
    int64_t order_time;                                                 // 时间（YYYYMMDDHHMMSSsss)
    int64_t order_price;                                                // 委托价格，实际值需除以1000000
    int64_t order_volume;                                               // 深圳市场:委托数量, 上海市场:剩余委托数量 ,实际值需除以100
    uint8_t side;                                                       // 买卖方向 (1-买 2-卖 G-借入 F-出借)
    uint8_t order_type;                                                 // 订单类别 (1-市价 2-限价 U-本方最优)
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                // 行情类别
    int64_t orig_order_no;                                              // 原始订单号 
    int64_t biz_index;                                                  // 业务序号 
};
/**  @} */

/**
 * @name 现货逐笔成交数据信息结构定义
 * @{ */
struct MDTickExecution
{
    int32_t market_type;                                                // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                // 证券代码
    int64_t exec_time;                                                  // 时间（YYYYMMDDHHMMSSsss)
    int32_t channel_no;                                                 // 频道号
    int64_t appl_seq_num;                                               // 频道编号
    int64_t exec_price;                                                 // 成交价格，实际值需除以1000000
    int64_t exec_volume;                                                // 成交数量，实际值需除以100
    int64_t value_trade;                                                // 成交金额，实际值需除以100000
    int64_t bid_appl_seq_num;                                           // 买方委托索引
    int64_t offer_appl_seq_num;                                         // 卖方委托索引
    uint8_t side;                                                       // 买卖方向（仅上海有效 B-外盘，主动买 S-内盘，主动卖 N-未知）
    uint8_t exec_type;                                                  // 成交类型（仅深圳有效 4-撤销 F-成交）
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                // 行情类别
    int64_t biz_index;                                                  // 业务序号
};
/**  @} */

/**
 * @name 现货委托队列数据信息结构定义
 * @{ */
struct MDOrderQueue
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t order_time;                                                     // 委托时间（YYYYMMDDHHMMSSsss）
    uint8_t side;                                                           // 买卖方向 (B-买 S-卖)
    int64_t order_price;                                                    // 委托价格，实际值需除以1000000
    int64_t order_volume;                                                   // 订单数量，实际值需除以100
    int32_t num_of_orders;                                                  // 总委托笔数 
    int32_t items;                                                          // 明细个数
    int64_t volume[50];                                                     // 订单明细
    int32_t channel_no;                                                     //频道号
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**@
 * @name 期权基本信息
 * @{ */
struct MDOptionBasicInfo
{
    int32_t market_type;                                                    // 市场类型
    char security_id[ConstField::kSecurityCodeLen];                         // 期权代码
    char contract_id[ConstField::kContractIDLen];                           // 合约交易代码
    char contract_symbol[ConstField::kContractSymbolLen];                   // 期权合约简称
    char underlying_security_id[ConstField::kSecurityCodeLen];              // 标的证券代码
    char underlying_symbol[ConstField::kSecurityNameLen];                   // 基础证券代码名称
    char underlying_type[ConstField::kUnderlyingTypeLen];                   // 标的证券类型 EBS - ETF, ASH - A股
    char option_type;                                                       // 欧式美式 若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
    char call_or_put;                                                       // 认购认沽  认购，则本字段为“C”；若为认沽，则本字段为“P”
    uint32_t contract_multiplieri_unit;                                     // 合约单位 N11 经过除权除息调整后的合约单位
    uint64_t exercise_price;                                                // 期权行权价 N11(4) 经过除权除息调整后的期权行权价，精确到0.0001元
    uint32_t start_date;                                                    // 首个交易日 期权首个交易日,YYYYMMDD
    uint32_t end_date;                                                      // 最后交易日 期权最后交易日/行权日，YYYYMMDD
    uint32_t exercise_date;                                                 // 期权行权日 期权行权日，YYYYMMDD
    uint32_t delivery_date;                                                 // 行权交割日 行权交割日，默认为行权日的下一个交易日，YYYYMMDD
    uint32_t expire_date;                                                   // 期权到期日 期权到期日，YYYYMMDD
    char update_version;                                                    // 期权合约的版本号
    uint64_t total_long_position;                                           // 当前合约未平仓数 N12 单位是 （张）
    uint64_t pre_close_price;                                               // 昨日收盘价 N11(4) 单位：元（精确到0.0001元）
    uint64_t pre_settl_price;                                               // 昨日结算价 N11(4) 如遇除权除息则为调整后的结算价（合约上市首日填写参考价），单位：元（精确到0.0001元）
    uint64_t underlying_pre_close_price;                                    // 期权标的证券除权除息调整后的前收盘价格 N11(4) 单位：元（精确到0.0001元）
    char price_limit_type;                                                  // 涨跌幅限制类型 ‘N’有涨跌幅限制类型
    uint64_t high_limited;                                                  // 当日期权涨停价格 N11(4) 单位：元（精确到0.0001元）
    uint64_t low_limited;                                                   // 当日期权跌停价格 N11(4) 单位：元（精确到0.0001元）
    uint64_t margin_unit;                                                   // 单位保证金 N16(2) 当日持有一张合约所需要的保证金数量，精确到分
    uint32_t margin_ratio_param1;                                           // 保证金计算比例参数一 N6(2) 保证金计算参数，单位：%
    uint32_t margin_ratio_param2;                                           // 保证金计算比例参数二 N6(2) 保证金计算参数，单位：%
    uint64_t round_lot;                                                     // 整手数 N12 一手对应的合约数
    uint64_t lmt_ord_min_floor;                                             // 单笔限价申报下限 N12 单笔限价申报的申报张数下限
    uint64_t lmt_ord_max_floor;                                             // 单笔限价申报上限 N12 单笔限价申报的申报张数上限
    uint64_t mkt_ord_min_floor;                                             // 单笔市价申报下限 N12 单笔市价申报的申报张数下限
    uint64_t mkt_ord_max_floor;                                             // 单笔市价申报上限 N12 单笔市价申报的申报张数上限
    uint64_t tick_size;                                                     // 最小报价单位 N11(4) 单位：元，精确到0.0001元
    char security_status_flag[ConstField::kSecurityStatusFlagLen];          // 期权合约状态信息标签 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                                            /*
                                                                                第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（不.包括备兑开仓）和买入开仓。
                                                                                第2位：‘0’表示未连续停牌，‘1’表示连续停牌。（预留，暂填0）
                                                                                第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足5个交易日。
                                                                                第4位：‘0’表示近期未做调整，‘1’表示最近5个交易日内合约发生过调整。
                                                                                第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约
                                                                            */
};
/**  @} */

/**
 * @name 期权快照数据信息结构定义
 * @{ */
struct MDOptionSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 期权代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    int64_t pre_settle_price;                                               // 昨结算价（仅上海有效），实际值需除以1000000
    int64_t pre_close_price;                                                // 昨收盘价（仅深交所有效），实际值需除以1000000
    int64_t open_price;                                                     // 今开盘价，实际值需除以1000000
    int64_t auction_price;                                                  // 动态参考价 (波动性中断参考价)，实际值需除以1000000
    int64_t auction_volume;                                                 // 虚拟匹配数量，实际值需除以100
    int64_t high_price;                                                     // 最高价，实际值需除以1000000
    int64_t low_price;                                                      // 最低价，实际值需除以1000000
    int64_t last_price;                                                     // 最新价，实际值需除以1000000
    int64_t close_price;                                                    // 收盘价 （仅上海有效），实际值需除以1000000
    int64_t high_limited;                                                   // 涨停价，实际值需除以1000000
    int64_t low_limited;                                                    // 跌停价，实际值需除以1000000
    int64_t bid_price[5];                                                   // 申买价，实际值需除以1000000
    int64_t bid_volume[5];                                                  // 申买量，实际值需除以100
    int64_t offer_price[5];                                                 // 申卖价，实际值需除以1000000
    int64_t offer_volume[5];                                                // 申买量，实际值需除以100
    int64_t settle_price;                                                   // 今日结算价，实际值需除以1000000
    int64_t total_long_position;                                            // 总持仓量，实际值需除以100
    int64_t total_volume_trade;                                             // 总成交数，实际值需除以100
    int64_t total_value_trade;                                              // 总成交额，实际值需除以100000
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 产品实时阶段及标志
    //************************************上海期权交易状态***************************************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第0位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，
    //‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌,
    //‘U’表示收盘集合竞价 ‘M’表示可恢复交易的熔断（盘中集合竞价）,‘N’表示不可恢复交易的熔断（暂停交易至闭市）
    //第1位：‘0’表示未连续停牌，‘1’表示连续停牌。（预留，暂填空格）
    //第2位：‘0’表示不限制开仓，‘1’表示限制备兑开仓，‘2’表示卖出开仓，‘3’表示限制卖出开仓、备兑开仓，‘4’表示限制买入开仓，‘5’表示限制买入开仓、备兑开仓，‘6’表示限制买入开仓、卖出开仓，‘7’表示限制买入开仓、卖出开仓、备兑开仓
    //第3位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。

    //************************************深圳期权交易状态***************************************************************
    //第 0位：S= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int32_t channel_no;                                                         // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                                                    // 行情类别
    int64_t last_trade_time;                                                // 最近成交时间（为YYYYMMDDHHMMSSsss 仅上海03文件，LDDS生效）
    int64_t ref_price;                                                      //参考价，实际值需除以1000000
};
/**  @} */

/**
 * @name 港股通快照行情
 * @{ */
struct MDHKTSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 港股代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    int64_t pre_close_price;                                                // 昨收价，实际值需除以1000000
    int64_t nominal_price;                                                  // 按盘价，实际值需除以1000000
    int64_t high_price;                                                     // 最高价，实际值需除以1000000
    int64_t low_price;                                                      // 最低价，实际值需除以1000000
    int64_t last_price;                                                     // 最新价，实际值需除以1000000
    int64_t bid_price[5];                                                      // 申买价，实际值需除以1000000
    int64_t bid_volume[5];                                                     // 申买量，实际值需除以100
    int64_t offer_price[5];                                                    // 申卖价，实际值需除以1000000
    int64_t offer_volume[5];                                                   // 申卖量，实际值需除以100
    int64_t total_volume_trade;                                             // 总成交数，实际值需除以100
    int64_t total_value_trade;                                              // 总成交额，实际值需除以100000
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 产品实时阶段及标志
    //************************************上海港股通交易状态***************************************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第 0位：‘0’表示正常，‘1’表示暂停交易。

    //************************************深圳港股通交易状态***************************************************************
    //第 0位：‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int32_t channel_no;                                                      // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                     // 行情类别
    int64_t ref_price;                                                       // 参考价格
    int64_t high_limited;                                                    // 涨停价
    int64_t low_limited;                                                     // 跌停价
    int64_t bid_price_limit_up;                                              // 买盘上限价，实际值需除以1000000  （仅深圳有效 暂时不支持）
    int64_t bid_price_limit_down;                                            // 买盘下限价，实际值需除以1000000  （仅深圳有效 暂时不支持）
    int64_t offer_price_limit_up;                                            // 卖盘上限价，实际值需除以1000000  （仅深圳有效 暂时不支持）
    int64_t offer_price_limit_down;                                          // 卖盘下限价，实际值需除以1000000  （仅深圳有效 暂时不支持）
};
/**  @} */


struct MDHKTVCM
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 港股代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    int64_t start_time;                                                     // 市调机制开始时间
    int64_t end_time;                                                       // 市调机制结束时间
    int64_t ref_price;                                                      // 市调机制参考价格
    int64_t low_price;                                                      // 市调机制最低价格
    int64_t high_price;                                                     // 市调机制最高价格
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};

/**
 * @name 盘后快照定义
 * @{ */
struct MDAfterHourFixedPriceSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间（为YYYYMMDDHHMMSSsss）
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 交易阶段代码
    //************************************上海盘后快照交易状态***************************************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第0位：‘I’表示启动（开市前）时段， ‘A’表示集中撮合时段，‘H’表示连续交易时段，‘D’表示闭市时段，‘F’表示停牌

    //************************************深圳盘后快照交易状态***************************************************************
    //第 0位：
    //‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int64_t close_price;                                                    // 今日收盘价（仅上海有效），实际值需除以1000000
    int64_t bid_price;                                                      // 申买价 （仅深圳有效），实际值需除以1000000
    int64_t bid_volume;                                                     // 申买量，实际值需除以100
    int64_t offer_price;                                                    // 申卖价 （仅深圳有效），实际值需除以1000000
    int64_t offer_volume;                                                   // 申卖量，实际值需除以100
    int64_t pre_close_price;                                                // 昨收价，实际值需除以1000000
    int64_t num_trades;                                                     // 成交笔数
    int64_t total_volume_trade;                                             // 成交总量，实际值需除以100
    int64_t total_value_trade;                                              // 成交总金额，实际值需除以100000
    int64_t total_bid_volume;                                               // 委托买入总量，实际值需除以100
    int64_t total_offer_volume;                                             // 委托卖出总量，实际值需除以100
    int32_t channel_no;                                                     // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
 * @name 盘后逐笔成交定义
 * @{ */
struct MDAfterHourFixedPriceTickExecution
{
    int32_t market_type;
    int64_t appl_seq_num;                                                   // 消息记录号
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t exec_time;                                                      // 成交时间 （YYYYMMDDHHMMSSsss）
    int64_t exec_price;                                                     // 委托价格，实际值需除以1000000
    int64_t exec_volume;                                                    // 委托数量，实际值需除以100
    int64_t value_trade;                                                    // 成交金额，实际值需除以100000
    int64_t bid_appl_seq_num;                                               // 买方委托索引
    int64_t offer_appl_seq_num;                                             // 卖方委托索引
    uint8_t side;                                                           // 买卖方向（仅上海有效 B-外盘，主动买 S-内盘，主动卖 N-未知）
    uint8_t exec_type;                                                      // 成交类型
    int32_t channel_no;                                                     // 频道代码
};
/**  @} */

/**
* @name MDFutureSnapshot 期货快照数据结构
* @{ */
struct MDFutureSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char security_code[ConstField::kFutureSecurityCodeLen];                 // 合约代码
    int32_t action_day;                                                     // 业务日期
    int64_t orig_time;                                                      // 交易日 YYYYMMDDHHMMSSsss(ActionDay + UpdateTime + UpdateMillisec)
    char exchange_inst_id[ConstField::kExChangeInstIDLen];                  // 合约在交易所的代码
    int64_t last_price;                                                     // 最新价，实际值需除以1000000
    int64_t pre_settle_price;                                               // 上次结算价，实际值需除以1000000
    int64_t pre_close_price;                                                // 昨收价，实际值需除以1000000
    int64_t pre_open_interest;                                              // 昨持仓量，实际值需除以100
    int64_t open_price;                                                     // 开盘价，实际值需除以1000000
    int64_t high_price;                                                     // 最高价，实际值需除以1000000
    int64_t low_price;                                                      // 最低价，实际值需除以1000000
    int64_t total_volume_trade;                                             // 数量，实际值需除以100
    int64_t total_value_trade;                                              // 总成交金额，实际值需除以100000
    int64_t open_interest;                                                  // 持仓量，实际值需除以100
    int64_t close_price;                                                    // 今收盘，实际值需除以1000000
    int64_t settle_price;                                                   // 本次结算价，实际值需除以1000000
    int64_t high_limited;                                                   // 涨停板价，实际值需除以1000000
    int64_t low_limited;                                                    // 跌停板价，实际值需除以1000000
    int64_t pre_delta;                                                      // 昨虚实度，实际值需除以1000000
    int64_t curr_delta;                                                     // 今虚实度，实际值需除以1000000
    int64_t bid_price[5];                                                   // 申买价，实际值需除以1000000
    int64_t bid_volume[5];                                                  // 申买量，实际值需除以100
    int64_t offer_price[5];                                                 // 申卖价，实际值需除以1000000
    int64_t offer_volume[5];                                                // 申卖量，实际值需除以100
    int64_t average_price;                                                  // 当日均价，实际值需除以1000000
    int32_t trading_day;                                                    // 交易日期
};
/**  @} */


/**
* @name MDCSIIndexSnapshot 中证指数行情信息
* @{ */
struct MDCSIIndexSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    int64_t last_index;                                                     // 最新指数，实际值需除以1000000
    int64_t open_index;                                                     // 今开盘指数，实际值需除以1000000
    int64_t high_index;                                                     // 最高指数，实际值需除以1000000
    int64_t low_index;                                                      // 最低指数，实际值需除以1000000
    int64_t close_index;                                                    // 收盘指数，实际值需除以1000000
    int64_t pre_close_index;                                                // 前收盘指数，实际值需除以1000000
    int64_t change;                                                         // 涨跌，实际值需除以1000000
    int64_t ratio_of_change;                                                // 涨跌幅，实际值需除以1000000
    int64_t total_volume_trade;                                             // 成交量，实际值需除以100
    int64_t total_value_trade;                                              // 总成交金额，实际值需除以100000
    int64_t exchange_rate;                                                  // 汇率，实际值需除以100000000
    char    currency_symbol;                                                // 币种标志（0-人民币 1-港币 2-美元 3-台币 4-日元）
    int64_t close_index2;                                                   // 当日收盘2，实际值需除以1000000
    int64_t close_index3;                                                   // 当日收盘3，实际值需除以1000000
    uint8_t index_market;                                                   // 指数市场
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别  JLLX
};
/**  @} */

/**
* @name MDIndicatorOfTradingVolumeSnapshot 成交量统计指标快照行情（仅深交所）
* @{ */
struct MDIndicatorOfTradingVolumeSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    int64_t total_volume_trade;                                             // 总成交数，实际值需除以100
    int64_t total_value_trade;                                              // 总成交额，实际值需除以100000
    int64_t pre_close_price;                                                // 昨收价，实际值需除以1000000
    uint32_t stock_num;                                                     // 统计量指标样本个数
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 产品实时阶段及标志
    //************************************深圳成交量统计指标快照交易状态***************************************************************
    //第 0位：‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int32_t channel_no;                                                     // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};

/**
* @name MDCnIndexSnapshot 国证指数快照行情 （仅深交所）
* @{ */
struct MDCnIndexSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间（YYYYMMDDHHMMSSsss)
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 产品实时阶段及标志
    //************************************深圳成交量统计指标快照交易状态***************************************************************
    //第 0位：‘S’= 启动（开市前）‘O’= 开盘集合竞价‘T’= 连续竞价‘B’= 休市‘C’= 收盘集合竞价‘E’= 已闭市‘H’= 临时停牌‘A’= 盘后交易‘V’=波动性中断
    //第 1位：‘0’= 正常状态 ‘1’= 全天停牌
    int64_t pre_close_index;                                                // 前收盘指数，实际值需除以1000000
    int64_t open_index;                                                     // 今开盘指数，实际值需除以1000000
    int64_t high_index;                                                     // 最高指数，实际值需除以1000000
    int64_t low_index;                                                      // 最低指数，实际值需除以1000000
    int64_t last_index;                                                     // 最新指数，实际值需除以1000000
    int64_t close_index;                                                    // 收盘指数，实际值需除以1000000
    int64_t close_index2;                                                   // 收盘指数2，实际值需除以1000000
    int64_t close_index3;                                                   // 收盘指数3，实际值需除以1000000
    int64_t total_volume_trade;                                             // 参与计算相应指数的交易数量，实际值需除以100
    int64_t total_value_trade;                                              // 参与计算相应指数的成交总金额，实际值需除以100000
    int32_t channel_no;                                                     // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDRefinancingTickOrder 转融通证券出借逐笔委托
* @{ */
struct MDRefinancingTickOrder
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int32_t channel_no;                                                     // 频道编号
    int64_t appl_seq_num;                                                   // 消息记录号
    int64_t order_time;                                                     // 委托时间 （YYYYMMDDHHMMSSsss）
    int64_t order_price;                                                    // 委托价格，实际值需除以1000000
    int64_t order_volume;                                                   // 委托数量，实际值需除以100
    uint8_t side;                                                           // 买卖方向 (1-买 2-卖 G-借入 F-出借)
    uint16_t expiration_days;                                               // 期限
    uint8_t expiration_type;                                                // 期限类型（1-固定期限）
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDRefinancingTickExecution 转融通证券出借逐笔成交
* @{ */
struct MDRefinancingTickExecution
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t exec_time;                                                      // 成交时间 YYYYMMDDHHMMSSsss
    int32_t channel_no;                                                     // 频道编号
    int64_t appl_seq_num;                                                   // 消息记录号
    int64_t exec_price;                                                     // 委托价格，实际值需除以1000000
    int64_t exec_volume;                                                    // 委托数量，实际值需除以100
    int64_t value_trade;                                                    // 成交金额，实际值需除以100000
    int64_t bid_appl_seq_num;                                               // 买方委托索引
    int64_t offer_appl_seq_num;                                             // 卖方委托索引
    uint8_t side;                                                           // 买卖方向
    uint8_t exec_type;                                                      // 成交类型（仅深圳有效 4-撤销 F-成交）
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDNegotiableTickOrder 协议交易逐笔委托
* @{ */
struct MDNegotiableTickOrder
{
    int32_t market_type;
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int32_t channel_no;                                                     // 频道编号
    int64_t appl_seq_num;                                                   // 消息记录号
    int64_t order_time;                                                     // 委托时间 （YYYYMMDDHHMMSSsss）
    int64_t order_price;                                                    // 委托价格，实际值需除以1000000
    int64_t order_volume;                                                   // 委托数量，实际值需除以100
    uint8_t side;                                                           // 买卖方向 (1-买 2-卖 G-借入 F-出借)
    char    confirm_id[ConstField::kConfirmIdLen];                          // 定价行情约定号; 为空表示是意向行情, 否则为定价行情
    char    contactor[ConstField::kContactorLen];                           // 联系人
    char    contact_info[ConstField::kContactInfoLen];                      // 联系方式
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDNegotiableTickExecution 协议交易逐笔成交
* @{ */
struct MDNegotiableTickExecution
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t exec_time;                                                      // 成交时间 YYYYMMDDHHMMSSsss
    int32_t channel_no;                                                     // 频道编号
    int64_t appl_seq_num;                                                   // 消息记录号
    int64_t exec_price;                                                     // 委托价格，实际值需除以1000000
    int64_t exec_volume;                                                    // 委托数量，实际值需除以100
    int64_t value_trade;                                                    // 成交金额，实际值需除以100000
    int64_t bid_appl_seq_num;                                               // 买方委托索引
    int64_t offer_appl_seq_num;                                             // 卖方委托索引
    uint8_t side;                                                           // 买卖方向
    uint8_t exec_type;                                                      // 成交类型（仅深圳有效 4-撤销 F-成交）
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDHKTRealtimeLimit 港股通实时额度
* @{ */
struct MDHKTRealtimeLimit
{
    int32_t market_type;                                                    // 市场类型
    int64_t orig_time;                                                      // 时间(YYYYMMDDHHMMSSsss)
    int64_t threshold_amount;                                               // 每日初始额度，实际值需除以100000
    int64_t pos_amt;                                                        // 日中剩余额度，实际值需除以100000
    char    amount_status;                                                  // 额度状态 (1-额度用完或其他原因全市场禁止买入 2-额度可用)
    int32_t channel_no;                                                     // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
* @name MDHKTProductStatus 港股通可接收订单并转发的产品状态数据
* @{ */
struct MDHKTProductStatus
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间(YYYYMMDDHHMMSSsss)
    char    trading_status1[ConstField::kTradingStatusLen];                 // 证券交易状态（整手订单）
    //************************************港股通整手订单************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第1位：‘0’表示限制买入，‘1’表示正常无此限制。
    //第2位：‘0’表示限制卖出，‘1’表示正常无此限制。
    char    trading_status2[ConstField::kTradingStatusLen];                 // 证券交易状态（零股订单）
    //************************************港股通零股订单************************************
    //该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
    //第1位：‘0’表示限制买入，‘1’表示正常无此限制。
    //第2位：‘0’表示限制卖出，‘1’表示正常无此限制。
    int32_t channel_no;                                                     // 频道代码
    char    md_stream_id[ConstField::kMDStreamIDMaxLen];                    // 行情类别
};
/**  @} */

/**
 * @name MDNEEQSecurityMarket 北交所证券行情
 * @{ */
struct MDNEEQSnapshot
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间 CCYYMMDD + HHMMSS * 1000
    int64_t pre_close_price;                                                // 昨收价，实际值需除以1000000
    int64_t open_price;                                                     // 开盘价，实际值需除以1000000
    int64_t last_price;                                                     // 最新价，实际值需除以1000000
    int64_t total_volume_trade;                                             // 成交总量，实际值需除以100
    int64_t total_value_trade;                                              // 成交总金额，实际值需除以100000
    int64_t num_trades;                                                     // 成交笔数
    int64_t high_price;                                                     // 最高价，实际值需除以1000000
    int64_t low_price;                                                      // 最低价，实际值需除以1000000
    int64_t price_earning_ratio1;                                           // 市盈率1，实际值需除以1000000
    int64_t price_earning_ratio2;                                           // 市盈率2，实际值需除以1000000
    int64_t change1;                                                        // 升跌1（对比昨收价），实际值需除以1000000
    int64_t change2;                                                        // 升跌2（对比上一笔)，实际值需除以1000000
    int64_t open_interest;                                                  // 合约持仓量，实际值需除以100
    int64_t bid_price[5];                                                   // 申买价，实际值需除以1000000
    int64_t bid_volume[5];                                                  // 申买量，实际值需除以100
    int64_t offer_price[5];                                                 // 申卖价，实际值需除以1000000
    int64_t offer_volume[5];                                                // 申卖量，实际值需除以100
    int64_t index_factor;                                                   // 指数因子，实际值需除以1000000
    char    trading_phase_code[ConstField::kTradingPhaseCodeLen];           // 交易阶段代码
    //************************************北交所证券行情状态***************************************************************
    //个位数存放收市行情标志（0：非收市行情；1：收市行情；2：盘后行情）
    //十位数存放正式行情与测试行情标志（0：正式行情；1：测试行情）
};
/**  @} */

/**
* @name MDNEEQSecurityInfo 北交所证券信息
* @{ */
struct MDNEEQSecurityInfo
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间 CCYYMMDD + HHMMSSss * 10
    //char    security_abbreviation[ConstField::kSecurityNameLen];            // 证券简称
    //char    english_abbreviation[ConstField::kSecurityNameLen];             // 英文简称
    char    underlying_security[ConstField::kSecurityCodeLen];              // 基础证券
    char    ISIN[ConstField::kSecurityCodeLen];                             // ISIN编码
    int32_t trading_unit;                                                   // 交易单位
    char    industry_type[ConstField::kTypesLen];                           // 行业种类
    char    currency[ConstField::kTypesLen];                                // 货币种类 (00-人民币，02-美元)
    int64_t par_value;                                                      // 每股面值，实际值需除以1000000
    int64_t general_capital;                                                // 总股本
    int64_t unrestricted_capital;                                           // 非限售股本
    int64_t last_year_earning;                                              // 上年每股收益，实际值需除以1000000
    int64_t cur_year_earning;                                               // 本年每股收益，实际值需除以1000000
    int64_t brokerage_rate;                                                 // 经手费率，实际值需除以1000000
    int64_t stamp_duty_rate;                                                // 印花税率，实际值需除以1000000
    int64_t transfer_fee_rate;                                              // 过户费率，实际值需除以1000000
    char    listing_date[ConstField::kDateLen];                             // 挂牌日期
    char    value_date[ConstField::kDateLen];                               // 起息日
    char    expiring_date[ConstField::kDateLen];                            // 到期日
    int64_t every_limited;                                                  // 每笔限量，实际值需除以100
    int32_t buy_amount_unit;                                                // 买数量单位，实际值需除以100
    int32_t sell_amount_unit;                                               // 卖数量单位，实际值需除以100
    int64_t mini_dec_amount;                                                // 最小申报数量，实际值需除以100
    int32_t price_level;                                                    // 价格档位，实际值需除以1000000
    int64_t first_trade_limit;                                              // 首笔交易限价参数，实际值需除以1000000
    int64_t follow_trade_limit;                                             // 后续交易限价参数，实际值需除以1000000
    uint8_t limit_param_nature;                                             // 限价参数性质
    int64_t high_limited;                                                   // 涨停价，实际值需除以1000000
    int64_t low_limited;                                                    // 跌停价，实际值需除以1000000
    int64_t block_trade_ceiling;                                            // 大宗交易价格上限，实际值需除以1000000
    int64_t block_trade_floor;                                              // 大宗交易价格下限，实际值需除以1000000
    char    component_mark;                                                 // 成分股标志
    int32_t conver_ratio;                                                   // 折合比例，实际值需除以1000000
    char    trade_status;                                                   // 交易状态
    char    security_level;                                                 // 证券级别
    char    trade_type;                                                     // 交易类型
    int64_t market_maker_num;                                               // 做市商数量，实际值需除以100
    char    suspen_sign;                                                    // 停牌标志
    char    ex_sign;                                                        // 除权除息标志
    char    net_vote_sign;                                                  // 网络投票标志
    char    other_buss_sign[ConstField::kTypesLen];                         // 其他业务标志
    char    record_update_time[ConstField::kTimeLen];                       // 记录更新时间
};
/**  @} */

/**
 * @name MDNEEQNonPublicTransDeclaredInfo 北交所非公开转让申报信息库
 * @{ */
struct MDNEEQNonPublicTransDeclaredInfo
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    int64_t orig_time;                                                      // 时间 CCYYMMDD + HHMMSS * 1000
    char    transaction_unit[ConstField::kTypesLen];                        // 交易单元
    char    security_category[ConstField::kTypesLen];                       // 证券类别
    char    declare_category[ConstField::kTypesLen];                        // 申报类别
    int64_t declare_volume;                                                 // 申报数量，实际值需除以100
    int64_t declare_price;                                                  // 申报价格，实际值需除以1000000
    int32_t deal_agreement_num;                                             // 成交约定号
    char    declare_time[ConstField::kTimeLen];                             // 申报时间
    char    record_status;                                                  // 记录状态
    char    backup_sign;                                                    // 备用标志
};
/**  @} */

/**
 * @name MDNEEQHierarchicalInfo 北交所分层信息库
 * @{ */
struct MDNEEQHierarchicalInfo
{
    int32_t market_type;                                                    // 市场类型
    char    security_code[ConstField::kSecurityCodeLen];                    // 证券代码
    char    trade_date[ConstField::kDateLen];                               // 交易日期 CCYYMMDD
    //char    security_abbreviation[ConstField::kSecurityAbbreviationLen];    // 证券简称
    char    layered_sign;                                                   // 分层标志
    char    layered_effective_date[ConstField::kDateLen];                   // 分层生效日期 CCYYMMDD
    char    backup_sign;                                                    // 备用标志
};
/**  @} */

}; // end of ama
}; // end of amd

#pragma pack(pop)
#endif
