/**
 * @file         ama.h
 * @author       郭光葵
 * @mail         guoguangkui@archforce.com.cn
 * @created time Thu 21 Sep 2017 09:45:45 AM CST
 *
 * Copyright (c) 2018 Archforce Financial Technology.  All rights reserved.
 * Redistribution and use in source and binary forms, with or without  modification, are not permitted.
 * For more information about Archforce, welcome to archforce.cn.
 */

#ifndef AMD_AMA_H_
#define AMD_AMA_H_

#include "ama_datatype.h"
#include "ama_struct.h"
#include "ama_export.h"

namespace amd { namespace ama {

class IAMDSpi;
/**
 * @brief AMD接口操作类，该类不需要创建实例，直接调用类函数即可。如IAMDApi::GetVersion().
 */
class AMA_EXPORT IAMDApi
{
public:

    /**
     * @brief GetVersion            获取AMA版本信息函数
     *
     * @return                      版本内容
     */
    static const char* GetVersion();

    /**
     * @brief Init 初始化AMA
     *
     * @param pSpi                  IAMDSpi的继承类实例指针，除非才调用Release函数之后，该实例才能被销毁。
     * @param cfg                   AMD内部需要的配置参数
     *
     * @return                      具体错误信息请参考ErrorCode
     */
    static int32_t Init(const IAMDSpi* pSpi, const Cfg& cfg);

    /**
     * @brief 对AMA内部线程先执行Join操作，资源暂不释放
     *
     * @return 
     */
    static void Join();

    /**
     * @brief Release               释放AMA内部资源
     *
     * @return                      具体错误信息请参考ErrorCode
     */
    static int32_t Release();

    /**
     * @brief                       释放内存函数
     *
     * @param data                  数据指针
     */
    static void FreeMemory(void* data);

    /**
     * @brief                       代码订阅操作
     *
     * @param subscribe_type        订阅类型，请参考 SubscribeType
     * @param item                  订阅代码的数据项，具体参数请参考 SubscribeItem
     * @param cnt                   订阅代码的数据项个数
     *
     * @return 
     */
    static int32_t SubscribeData(int32_t subscribe_type, const SubscribeItem* item, uint32_t cnt);
}; // end of IAMDApi

/**
 * @brief AMA中的接收数据的回调基类，用户使用时需要继续该类。并将该类的实例传递给IAMDApi::Init函数给AMA内部使用，必须保证该实例生命周期长于AMA
 */
class IAMDSpi
{
public:
    virtual ~IAMDSpi() {};

    /**
     * @brief OnLog                 接收日志数据回调
     *
     * @param level                 日志级别，具体请参考LogLevel
     * @param log                   日志内容
     * @param len                   日志内容字节长度
     */
    virtual void OnLog(const int32_t& level, const char* log, uint32_t len) { (void)level; (void)log; (void)len; }

    /**
     * @brief                       接收监控数据回调
     *
     * @param indicator             监控数据内容
     * @param len                   监控数据长度
     */
    virtual void OnIndicator(const char* indicator, uint32_t len) { (void)indicator; (void)len; }

    /**
     * @brief                       事件通知回调，使用者可根据该回调事件做相应的处理
     *
     * @param level                 事件级别
     * @param code                  事件代码
     * @param event_msg             事件具体信息 
     * @param len                   事件具体信息长度
     */
    virtual void OnEvent(uint32_t level, uint32_t code, const char* event_msg, uint32_t len) { (void)level; (void)code; (void)event_msg; (void)len; }
    /**
     * @brief OnMDSnapshot          接收现货快照数据回调
     *
     * @param snapshot              快照数据
     * @param cnt                   快照数据个数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */
    virtual void OnMDSnapshot(MDSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief OnMDOptionSnapshot    接收期权快照数据回调
     *
     * @param snapshot              快照数据
     * @param cnt                   快照数据个数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */
    virtual void OnMDOptionSnapshot(MDOptionSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief OnMDHKTSnapshot        接收港股快照数据回调
     *
     * @param snapshot              快照数据
     * @param cnt                   快照数据个数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */
    virtual void OnMDHKTSnapshot(MDHKTSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief OnMDIndexSnapshot     接收指数快照数据回调
     *
     * @param snapshot              指数快照数据
     * @param cnt                   指数快照数据个数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */
    virtual void OnMDIndexSnapshot(MDIndexSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief OnMDTickOrder         接收逐笔委托数据回调
     *
     * @param tick                  逐笔委托数据
     * @param cnt                   逐笔委托数据条数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */
    virtual void OnMDTickOrder(MDTickOrder* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief OnMDTickExection      接收逐笔成交数据回调
     *
     * @param tick                  逐笔成交数据
     * @param cnt                   逐笔成交数据条数
     *
     * @attention                   使用后需要通过接口 IAMDApi::FreeMemory释放数据
     */  
    virtual void OnMDTickExecution(MDTickExecution* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收委托队列数据回调
     *
     * @param orderqueues           委托队列数据
     * @param cnt                   委托队列数据条数
     */
    virtual void OnMDOrderQueue(MDOrderQueue* orderqueues, uint32_t cnt) { IAMDApi::FreeMemory(orderqueues); (void)cnt; }

    /**
     * @brief                       接收盘后快照数据回调
     *
     * @param snapshots             盘后快照数据
     * @param cnt                   盘后快照数据条数
     */
    virtual void OnMDAfterHourFixedPriceSnapshot(MDAfterHourFixedPriceSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收盘后逐笔成交数据回调
     *
     * @param ticks                 盘后逐笔成交数据
     * @param cnt                   盘后逐笔成交数据条数
     */
    virtual void OnMDAfterHourFixedPriceTickExecution(MDAfterHourFixedPriceTickExecution* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收期货数据回调
     *
     * @param snapshots             期货数据
     * @param cnt                   期货数据条数
     */
    virtual void OnMDFutureSnapshot(MDFutureSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收中证指数数据回调
     *
     * @param snapshots             中证指数数据
     * @param cnt                   中证指数数据条数
     */
    virtual void OnMDCSIIndexSnapshot(MDCSIIndexSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收深交所成交量统计指标快照数据回调
     *
     * @param snapshots             成交量统计指标快照数据
     * @param cnt                   成交量统计指标快照数据条数
     */
    virtual void OnMDIndicatorOfTradingVolumeSnapshot(MDIndicatorOfTradingVolumeSnapshot* snapshots, uint32_t cnt){ IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收国证指数快照数据回调
     *
     * @param snapshots             国证指数快照数据
     * @param cnt                   国证指数快照数据条数
     */
    virtual void OnMDCnIndexSnapshot(MDCnIndexSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收深交所转融通逐笔委托数据回调
     *  
     * @param ticks                 深交所转融通逐笔委托数据
     * @param cnt                   深交所转融通逐笔委托数据条数
     */
    virtual void OnMDRefinancingTickOrder(MDRefinancingTickOrder* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收深交所转融通逐笔成交数据回调
     *  
     * @param ticks                 深交所转融通逐笔成交数据
     * @param cnt                   深交所转融通逐笔成交数据条数
     */
    virtual void OnMDRefinancingTickExecution(MDRefinancingTickExecution* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收深交所协议交易逐笔委托数据回调
     *  
     * @param ticks                 深交所协议交易逐笔委托数据
     * @param cnt                   深交所协议交易逐笔委托数据条数
     */
    virtual void OnMDNegotiableTickOrder(MDNegotiableTickOrder* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收深交所协议交易逐笔成交数据回调
     *  
     * @param ticks                 深交所协议交易逐笔成交数据
     * @param cnt                   深交所协议交易逐笔成交数据条数
     */
    virtual void OnMDNegotiableTickExecution(MDNegotiableTickExecution* ticks, uint32_t cnt) { IAMDApi::FreeMemory(ticks); (void)cnt; }

    /**
     * @brief                       接收港股通实时额度数据回调
     *
     * @param limits                港股通实时额度数据
     * @param cnt                   港股通实时额度数据条数
     */
    virtual void OnMDHKTRealtimeLimit(MDHKTRealtimeLimit* limits, uint32_t cnt) { IAMDApi::FreeMemory(limits); (void)cnt; }

    /**
     * @brief                       接收港股通产品状态数据回调
     *
     * @param status                港股通产品状态数据
     * @param cnt                   港股通产品状态数据条数
     */
    virtual void OnMDHKTProductStatus(MDHKTProductStatus* status, uint32_t cnt) { IAMDApi::FreeMemory(status); (void)cnt; }

    /**
     * @brief                       接收港股VCM数据回调
     *
     * @param snapshots             VCM数据
     * @param cnt                   VCM数据条数
     */
    virtual void OnMDHKTVCM(MDHKTVCM* vcms, uint32_t cnt) { IAMDApi::FreeMemory(vcms); (void)cnt; }

    /**
     * @brief                       接收股转证券行情
     *
     * @param snapshots             接收股转证券行情数据
     * @param cnt                   接收股转证券行情数据条数
     */
    virtual void OnMDNEEQSnapshot(MDNEEQSnapshot* snapshots, uint32_t cnt) { IAMDApi::FreeMemory(snapshots); (void)cnt; }

    /**
     * @brief                       接收股转证券信息
     *
     * @param infos                 接收股转证券信息数据
     * @param cnt                   接收股转证券信息数据条数
     */
    virtual void OnMDNEEQSecurityInfo(MDNEEQSecurityInfo* infos, uint32_t cnt) { IAMDApi::FreeMemory(infos); (void)cnt; }

    /**
     * @brief                       接收股转非公开转让申报信息
     *
     * @param infos                 接收股转非公开转让申报信息数据
     * @param cnt                   接收股转非公开转让申报信息数据条数
     */
    virtual void OnMDNEEQNonPublicTransDeclaredInfo(MDNEEQNonPublicTransDeclaredInfo* infos, uint32_t cnt) { IAMDApi::FreeMemory(infos); (void)cnt; }

    /**
     * @brief                       接收股转分层信息信息
     *
     * @param infos                 接收股转分层信息数据
     * @param cnt                   接收股转分层信息数据条数
     */
    virtual void OnMDNEEQHierarchicalInfo(MDNEEQHierarchicalInfo* infos, uint32_t cnt) { IAMDApi::FreeMemory(infos); (void)cnt; }
    
}; // end of IAMDSpi

}; // end of ama
}; // end of amd

#endif // end of AMA_H_
