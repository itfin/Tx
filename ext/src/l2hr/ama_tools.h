/**
 * @file         ama_tools.h
 * @breif        TODO
 * @author       郭光葵
 * @mail         guoguangkui@archforce.com.cn
 * @created time Wed 29 Nov 2017 10:03:29 AM CST
 *
 * Copyright (c) 2018 Archforce Financial Technology.  All rights reserved.
 * Redistribution and use in source and binary forms, with or without  modification, are not permitted.
 * For more information about Archforce, welcome to archforce.cn.
 */

#ifndef AMA_TOOLS_H_
#define AMA_TOOLS_H_

#include <string>
#include "ama_struct.h"
#include "ama_export.h"

namespace amd { namespace ama {

class AMA_EXPORT Tools
{
public:
    static void SetUMSServers(UMSItem* cfg,  uint32_t index, const UMSItem& value);
    static void GetUMSServers(UMSItem* cfg,  uint32_t index, UMSItem& value);

    static SubscribeItem* CreateSubscribeItem(uint32_t cnt);
    static void DestroySubscribeItem(SubscribeItem* item);
    static SubscribeCategoryItem* CreateSubscribeCategoryItem(uint32_t cnt);
    static void DestroySubscribeCategoryItem(SubscribeCategoryItem* item);

    static void SetSubscribeItem(SubscribeItem* item,  uint32_t index, const SubscribeItem& value);
    static const SubscribeItem& GetSubscribeItemByIndex(const SubscribeItem* item, uint32_t index);
    static void SetSubscribeCategoryItem(SubscribeCategoryItem* item,  uint32_t index, const SubscribeCategoryItem& value);
    static const SubscribeCategoryItem& GetSubscribeCategoryItemByIndex(const SubscribeCategoryItem* item, uint32_t index);

    static SubscribeOrderBookItem* CreateSubscribeOrderBookItem(uint32_t cnt);
    static void DestroySubscribeOrderBookItem(SubscribeOrderBookItem *item);

    static void SetSubscribeOrderBookItem(SubscribeOrderBookItem* item,  uint32_t index, const SubscribeOrderBookItem& value);
    static const SubscribeOrderBookItem& GetSubscribeOrderBookItemByIndex(const SubscribeOrderBookItem* item, uint32_t index);

     static SubscribeDerivedDataItem* CreateSubscribeDerivedDataItem(uint32_t cnt);
    static void DestroySubscribeDerivedDataItem(SubscribeDerivedDataItem *item);

    static void SetSubscribeDerivedDataItem(SubscribeDerivedDataItem* item,  uint32_t index, const SubscribeDerivedDataItem& value);
    static const SubscribeDerivedDataItem& GetSubscribeDerivedDataItemByIndex(const SubscribeDerivedDataItem* item, uint32_t index);

    static CodeTableRecordList* CreateCodeTableRecordList();
    static void DestroyCodeTableRecordList(CodeTableRecordList* item);

    static ETFCodeTableRecordList* CreateETFCodeTableRecordList();
    static void DestroyETFCodeTableRecordList(ETFCodeTableRecordList* item);

    static SubCodeTableItem* CreateSubCodeTableItem(uint32_t cnt);
    static void DestroySubCodeTableItem(SubCodeTableItem* item);
    static const SubCodeTableItem& GetSubCodeTableItemByIndex(const SubCodeTableItem* item, uint32_t index);
    static void SetSubCodeTableItem(SubCodeTableItem* item,  uint32_t index, const SubCodeTableItem& value);

    static ETFItem* CreateETFItem(uint32_t cnt);
    static void DestroyETFItem(ETFItem* item);
    static void SetETFItem(ETFItem* item,  uint32_t index, const ETFItem& value);
    static const ETFItem& GetETFItemByIndex(const ETFItem* item, uint32_t index);

    //RDIQueryItem
    static RDIQueryItem* CreateRDIQueryItem(uint32_t cnt);
    static void DestroyRDIQueryItem(RDIQueryItem* item);
    static void SetRDIQueryItem(RDIQueryItem* item,  uint32_t index, const RDIQueryItem& value);
    static const RDIQueryItem& GetRDIQueryItemByIndex(const RDIQueryItem* item, uint32_t index);
    
    static const MDSnapshot &GetDataByIndex(const MDSnapshot* snapshot, uint32_t index);
    static const MDOptionSnapshot &GetDataByIndex(const MDOptionSnapshot* snapshot, uint32_t index);
    static const MDHKTSnapshot &GetDataByIndex(const MDHKTSnapshot* snapshot, uint32_t index);
    static const MDIndexSnapshot &GetDataByIndex(const MDIndexSnapshot* snapshot, uint32_t index);
    static const MDTickOrder &GetDataByIndex(const MDTickOrder* tick, uint32_t index);
    static const MDTickExecution &GetDataByIndex(const MDTickExecution* tick, uint32_t index);
    static const MDOrderQueue &GetDataByIndex(const MDOrderQueue* orderqueue, uint32_t index);
    /*
    static const MDOptionBasicInfo &GetDataByIndex(const MDOptionBasicInfo* code, uint32_t index);
    */
    static const MDFutureSnapshot &GetDataByIndex(const MDFutureSnapshot* snapshot, uint32_t index);
    static const MDCSIIndexSnapshot &GetDataByIndex(const MDCSIIndexSnapshot* snapshot, uint32_t index);
    static const MDAfterHourFixedPriceSnapshot& GetDataByIndex(const MDAfterHourFixedPriceSnapshot* snapshots, uint32_t index);
    static const MDAfterHourFixedPriceTickExecution& GetDataByIndex(const MDAfterHourFixedPriceTickExecution* ticks, uint32_t index);
    static const MDIndicatorOfTradingVolumeSnapshot &GetDataByIndex(const MDIndicatorOfTradingVolumeSnapshot* snapshot, uint32_t index);
    static const MDCnIndexSnapshot &GetDataByIndex(const MDCnIndexSnapshot* snapshots, uint32_t index);
    static const MDRefinancingTickOrder& GetDataByIndex(const MDRefinancingTickOrder* ticks, uint32_t index);
    static const MDRefinancingTickExecution& GetDataByIndex(const MDRefinancingTickExecution* ticks, uint32_t index);
    static const MDNegotiableTickOrder& GetDataByIndex(const MDNegotiableTickOrder* ticks, uint32_t index);
    static const MDNegotiableTickExecution& GetDataByIndex(const MDNegotiableTickExecution* ticks, uint32_t index);
    static const MDHKTRealtimeLimit& GetDataByIndex(const MDHKTRealtimeLimit* limits, uint32_t index);
    static const MDHKMarketStatus& GetDataByIndex(const MDHKMarketStatus* limits, uint32_t index);
    static const MDHKTProductStatus& GetDataByIndex(const MDHKTProductStatus* status, uint32_t index);
    static const MDHKTVCM& GetDataByIndex(const MDHKTVCM* status, uint32_t index);
    static const MDNEEQSnapshot& GetDataByIndex(const MDNEEQSnapshot* snapshots, uint32_t index);
    static const MDNEEQSecurityInfo& GetDataByIndex(const MDNEEQSecurityInfo* infos, uint32_t index);
    static const MDNEEQNonPublicTransDeclaredInfo& GetDataByIndex(const MDNEEQNonPublicTransDeclaredInfo* infos, uint32_t index);
    static const MDNEEQHierarchicalInfo& GetDataByIndex(const MDNEEQHierarchicalInfo* infos, uint32_t index);
    static const MDNEEQNegotiableDeclaredInfo& GetDataByIndex(const MDNEEQNegotiableDeclaredInfo* infos, uint32_t index);
    static const MDNEEQMarketMakerDeclaredInfo& GetDataByIndex(const MDNEEQMarketMakerDeclaredInfo* infos, uint32_t index);
    static const MDNEEQNonPublicTransferDealInfo& GetDataByIndex(const MDNEEQNonPublicTransferDealInfo* infos, uint32_t index);
    static const MDOrderBook& GetDataByIndex(std::vector<MDOrderBook>& order_book, uint32_t index);
    static const MDOrderBookSnapshot &GetDataByIndex(const MDOrderBookSnapshot* snapshot, uint32_t index);
    static const MDIOPVSnapshot &GetDataByIndex(const MDIOPVSnapshot* snapshots, uint32_t index);
    static const CodeTableRecord& GetDataByIndex(const CodeTableRecord* records, uint32_t index);
    static const MDBondSnapshot &GetDataByIndex(const MDBondSnapshot* snapshot, uint32_t index);
    static const MDBondTickOrder &GetDataByIndex(const MDBondTickOrder* snapshot, uint32_t index);
    static const MDBondQuotedTickOrder &GetDataByIndex(const MDBondQuotedTickOrder* snapshot, uint32_t index);
    static const MDBondTickExecution &GetDataByIndex(const MDBondTickExecution* snapshot, uint32_t index);
    static const MDBondQuotedTickExecution &GetDataByIndex(const MDBondQuotedTickExecution* snapshot, uint32_t index);
    static const MDFundExpertSnapshot &GetDataByIndex(const MDFundExpertSnapshot* snapshot, uint32_t index);
    static const MDHKExSnapshot& GetDataByIndex(const MDHKExSnapshot* snapshots, uint32_t index);
    static const MDHKExOrderSnapshot& GetDataByIndex(const MDHKExOrderSnapshot* snapshots, uint32_t index);
    static const MDHKExOrderBrokerSnapshot& GetDataByIndex(const MDHKExOrderBrokerSnapshot* snapshots, uint32_t index);
    static const MDHKExTickExecution& GetDataByIndex(const MDHKExTickExecution* ticks, uint32_t index);
    static const MDHKExIndexSnapshot& GetDataByIndex(const MDHKExIndexSnapshot* snapshots, uint32_t index);
    static const MDHKExConnectTurnoverSnapshot& GetDataByIndex(const MDHKExConnectTurnoverSnapshot* snapshots, uint32_t index);
    static const SubTradingPhase& GetDataByIndex(const SubTradingPhase* array_data, uint32_t index);
    static const MDHKExListItem& GetDataByIndex(const MDHKExListItem* array_data, uint32_t index);
    static const MDHKExDetailItem& GetDataByIndex(const MDHKExDetailItem* array_data, uint32_t index);
    static const MDSpotTickExecution &GetDataByIndex(const MDSpotTickExecution* snapshot, uint32_t index);
    static const MDSpotSummarySnapshot &GetDataByIndex(const MDSpotSummarySnapshot* snapshot, uint32_t index);
    static const MDSpotXBondSnapshot &GetDataByIndex(const MDSpotXBondSnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoTickExecution &GetDataByIndex(const MDPledgeRepoTickExecution* snapshot, uint32_t index);
    static const MDPledgeRepoSummarySnapshot &GetDataByIndex(const MDPledgeRepoSummarySnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoInquirySnapshot &GetDataByIndex(const MDPledgeRepoInquirySnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoDepositSnapshot &GetDataByIndex(const MDPledgeRepoDepositSnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoXRepoSnapshot &GetDataByIndex(const MDPledgeRepoXRepoSnapshot* snapshot, uint32_t index);
    static const MDCeditLoanTickExecution &GetDataByIndex(const MDCeditLoanTickExecution* snapshot, uint32_t index);
    static const MDCeditLoanSnapshot &GetDataByIndex(const MDCeditLoanSnapshot* snapshot, uint32_t index);
    static const MDCeditLoanDepositSnapshot &GetDataByIndex(const MDCeditLoanDepositSnapshot* snapshot, uint32_t index);
    static const MDSwapFixedFloatTickExecution &GetDataByIndex(const MDSwapFixedFloatTickExecution* snapshot, uint32_t index);
    static const MDSwapFixedFloatSnapshot &GetDataByIndex(const MDSwapFixedFloatSnapshot* snapshot, uint32_t index);
    static const MDSwapXSwapSnapshot &GetDataByIndex(const MDSwapXSwapSnapshot* snapshot, uint32_t index);
    static const MDSwapXSwapBestOfferSnapshot &GetDataByIndex(const MDSwapXSwapBestOfferSnapshot* snapshot, uint32_t index);
    static const MDBondLoanTickExecution &GetDataByIndex(const MDBondLoanTickExecution* snapshot, uint32_t index);
    static const MDBondLoanUnderlyingSecurityRateSnapshot &GetDataByIndex(const MDBondLoanUnderlyingSecurityRateSnapshot* snapshot, uint32_t index);
    static const MDBondLoanTradingProductRateSnapshot &GetDataByIndex(const MDBondLoanTradingProductRateSnapshot* snapshot, uint32_t index);
    static const MDSpotMarketMakersQuoteSnapshot &GetDataByIndex(const MDSpotMarketMakersQuoteSnapshot* snapshot, uint32_t index);
    static const MDSpotDirectiveQuoteSnapshot &GetDataByIndex(const MDSpotDirectiveQuoteSnapshot* snapshot, uint32_t index);
    static const MDSpotXBondDepthQuoteSnapshot &GetDataByIndex(const MDSpotXBondDepthQuoteSnapshot* snapshot, uint32_t index);
    static const MDSpotXBondMatchQuoteSnapshot &GetDataByIndex(const MDSpotXBondMatchQuoteSnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoXRepoDepthQuoteSnapshot &GetDataByIndex(const MDPledgeRepoXRepoDepthQuoteSnapshot* snapshot, uint32_t index);
    static const MDPledgeRepoXRepoBestOfferQuoteSnapshot &GetDataByIndex(const MDPledgeRepoXRepoBestOfferQuoteSnapshot* snapshot, uint32_t index);
    static const MDSwapXSwapDepthQuoteSnapshot &GetDataByIndex(const MDSwapXSwapDepthQuoteSnapshot* snapshot, uint32_t index);
    static const MDSwapXSwapTickExecution &GetDataByIndex(const MDSwapXSwapTickExecution* snapshot, uint32_t index);
    static const MarketMakersQuoteItem& GetDataByIndex(const MarketMakersQuoteItem* ticks, uint32_t index);
    static const DirectiveQuoteItem& GetDataByIndex(const DirectiveQuoteItem* ticks, uint32_t index);
    static const MDBondInfoInterbank& GetDataByIndex(const MDBondInfoInterbank* data, uint32_t index);
    static const MDABSInfo& GetDataByIndex(const MDABSInfo* data, uint32_t index);
    static const MDABSHistoryInfo& GetDataByIndex(const MDABSHistoryInfo* data, uint32_t index);
    static const MDABSCreditRatings& GetDataByIndex(const MDABSCreditRatings* data, uint32_t index);
    static const MDPreIssuedBondInfo& GetDataByIndex(const MDPreIssuedBondInfo* data, uint32_t index);
    static const MDPreIPOBondInfo& GetDataByIndex(const MDPreIPOBondInfo* data, uint32_t index);
    static const BondInfoCreditItem& GetDataByIndex(const BondInfoCreditItem* data, uint32_t index);
    static const BondInfoConvertItem& GetDataByIndex(const BondInfoConvertItem* data, uint32_t index);
    static const BondInfoReissueItem& GetDataByIndex(const BondInfoReissueItem* data, uint32_t index);
    static const BondInfoExerciseItem& GetDataByIndex(const BondInfoExerciseItem* data, uint32_t index);
    static const PreIPOReissueItem& GetDataByIndex(const PreIPOReissueItem* data, uint32_t index);
    static const PreIPOExerciseItem& GetDataByIndex(const PreIPOExerciseItem* data, uint32_t index);
    static const PreIPOCreditItem& GetDataByIndex(const PreIPOCreditItem* data, uint32_t index);
    static const MDXBondTradeBondInfo& GetDataByIndex(const MDXBondTradeBondInfo* data, uint32_t index);
    static const PledgedConvertItem& GetDataByIndex(const PledgedConvertItem* data, uint32_t index);
    static const MDPledgedConvertRateACInfo& GetDataByIndex(const MDPledgedConvertRateACInfo* data, uint32_t index);
    static const XRepoHierGroupItem& GetDataByIndex(const XRepoHierGroupItem* data, uint32_t index);
    static const MDXRepoHierQuoteGroupInfo& GetDataByIndex(const MDXRepoHierQuoteGroupInfo* data, uint32_t index);
    static const MDXRepoContractInfo& GetDataByIndex(const MDXRepoContractInfo* data, uint32_t index);
    static const SwapAppTragItem& GetDataByIndex(const SwapAppTragItem* data, uint32_t index);
    static const MDSwapFixedFloatInfo& GetDataByIndex(const MDSwapFixedFloatInfo* data, uint32_t index);
    static const SwapBasisAppTragItem& GetDataByIndex(const SwapBasisAppTragItem* data, uint32_t index);
    static const MDSwapFixedFloatBasisContractInfo& GetDataByIndex(const MDSwapFixedFloatBasisContractInfo* data, uint32_t index);

    static const long long GetDataSize(std::vector<MDOrderBook>& order_book);
    static const SubTradingPhase& GetSubTradingPhaseByIndex(const SubTradingPhase* array_data, uint32_t index);

    static const long long& GetInt64DataByIndex(const long long* array_data, uint32_t index);

    static const ETFCodeTableRecord& GetDataByIndex(const ETFCodeTableRecord* records, uint32_t index);
    static const long long GetDataSize(std::vector<ConstituentStockInfo>& stocks);
    static const ConstituentStockInfo& GetDataByIndex(std::vector<ConstituentStockInfo>& stocks, uint32_t index);

    static const long long GetDataSize(std::vector<MDOrderBookItem>& book_item);
    static const MDOrderBookItem& GetDataByIndex(std::vector<MDOrderBookItem>& book_item, uint32_t index);

    static const IMCExchangeRate& GetDataByIndex(const IMCExchangeRate* rate, uint32_t index);

    //美股
    static const MDUsaStockSnapshot& GetDataByIndex(const MDUsaStockSnapshot* data, uint32_t index);
    static const MDUsaOrderSnapshot& GetDataByIndex(const MDUsaOrderSnapshot* data, uint32_t index);
    static const MDUsaEodSnapshot& GetDataByIndex(const MDUsaEodSnapshot* data, uint32_t index);

    //上海固收行情
    static const MDZQQDBJSnapshot &GetDataByIndex(const MDZQQDBJSnapshot* snapshot, uint32_t index);
    static const MDZQQDBJItem &GetDataByIndex(const MDZQQDBJItem* items, uint32_t index);
    static const MDZQCJHQSnapshot &GetDataByIndex(const MDZQCJHQSnapshot* snapshot, uint32_t index);
    static const MDZQCJMXSnapshot &GetDataByIndex(const MDZQCJMXSnapshot* snapshot, uint32_t index);

    static std::string Serialize(const MDSnapshot& snapshot);
    static std::string Serialize(const MDOptionSnapshot& snapshot);
    static std::string Serialize(const MDHKTSnapshot& snapshot);
    static std::string Serialize(const MDIndexSnapshot& snapshot);
    static std::string Serialize(const MDTickOrder& tick);
    static std::string Serialize(const MDTickExecution& tick);
    static std::string Serialize(const MDOrderQueue& orderqueue);
    static std::string Serialize(const MDFutureSnapshot& snapshot);
    static std::string Serialize(const MDCSIIndexSnapshot& snapshot);
    /*
    static std::string Serialize(const MDOptionBasicInfo& basicinfo);
    */
    static std::string Serialize(const MDAfterHourFixedPriceSnapshot& snapshot);
    static std::string Serialize(const MDAfterHourFixedPriceTickExecution& tick);
    static std::string Serialize(const MDIndicatorOfTradingVolumeSnapshot& snapshot);
    static std::string Serialize(const MDCnIndexSnapshot& snapshot);
    static std::string Serialize(const MDRefinancingTickOrder& tick);
    static std::string Serialize(const MDRefinancingTickExecution& tick);
    static std::string Serialize(const MDNegotiableTickOrder& tick);
    static std::string Serialize(const MDNegotiableTickExecution& tick);
    static std::string Serialize(const MDHKTRealtimeLimit& limit);
    static std::string Serialize(const MDHKTProductStatus& status);
    static std::string Serialize(const MDHKMarketStatus& status);
    static std::string Serialize(const MDHKTVCM& status);
    static std::string Serialize(const MDNEEQSnapshot& snapshot);
    static std::string Serialize(const MDNEEQSecurityInfo& info);
    static std::string Serialize(const MDNEEQNonPublicTransDeclaredInfo& info);
    static std::string Serialize(const MDNEEQHierarchicalInfo& info);
    static std::string Serialize(const MDNEEQNegotiableDeclaredInfo& info);
    static std::string Serialize(const MDNEEQMarketMakerDeclaredInfo& info);
    static std::string Serialize(const MDNEEQNonPublicTransferDealInfo& info);
    static std::string Serialize(const MDOrderBookSnapshot& snapshot);
    static std::string Serialize(const MDIOPVSnapshot& snapshot);
    static std::string Serialize(const MDOrderBook& order_book);
    static std::string Serialize(const CodeTableRecord& record);
    static std::string Serialize(const MDBondSnapshot& snapshot);
    static std::string Serialize(const MDBondTickOrder& snapshot);
    static std::string Serialize(const MDBondQuotedTickOrder& snapshot);
    static std::string Serialize(const MDBondTickExecution& snapshot);
    static std::string Serialize(const MDBondQuotedTickExecution& snapshot);
    static std::string Serialize(const ETFCodeTableRecord& record);
    static std::string Serialize(const MDFundExpertSnapshot& snapshot);
    static std::string Serialize(const MDHKExSnapshot& snapshot);
    static std::string Serialize(const MDHKExOrderSnapshot& snapshot);
    static std::string Serialize(const MDHKExOrderBrokerSnapshot& snapshot);
    static std::string Serialize(const MDHKExTickExecution& tick);
    static std::string Serialize(const MDHKExIndexSnapshot& snapshot);
    static std::string Serialize(const MDHKExConnectTurnoverSnapshot& snapshot);
    static std::string Serialize(const IMCExchangeRate& rate);

    static std::string Serialize(const MDSpotTickExecution& snapshot);
    static std::string Serialize(const MDSpotSummarySnapshot& snapshot);
    static std::string Serialize(const MDSpotXBondSnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoTickExecution& snapshot);
    static std::string Serialize(const MDPledgeRepoSummarySnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoInquirySnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoDepositSnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoXRepoSnapshot& snapshot);
    static std::string Serialize(const MDCeditLoanTickExecution& snapshot);
    static std::string Serialize(const MDCeditLoanSnapshot& snapshot);
    static std::string Serialize(const MDCeditLoanDepositSnapshot& snapshot);
    static std::string Serialize(const MDSwapFixedFloatTickExecution& snapshot);
    static std::string Serialize(const MDSwapFixedFloatSnapshot& snapshot);
    static std::string Serialize(const MDSwapXSwapSnapshot& snapshot);
    static std::string Serialize(const MDSwapXSwapBestOfferSnapshot& snapshot);
    static std::string Serialize(const MDBondLoanTickExecution& snapshot);
    static std::string Serialize(const MDBondLoanUnderlyingSecurityRateSnapshot& snapshot);
    static std::string Serialize(const MDBondLoanTradingProductRateSnapshot& snapshot);
    static std::string Serialize(const MDSpotMarketMakersQuoteSnapshot& snapshot);
    static std::string Serialize(const MDSpotDirectiveQuoteSnapshot& snapshot);
    static std::string Serialize(const MDSpotXBondDepthQuoteSnapshot& snapshot);
    static std::string Serialize(const MDSpotXBondMatchQuoteSnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoXRepoDepthQuoteSnapshot& snapshot);
    static std::string Serialize(const MDPledgeRepoXRepoBestOfferQuoteSnapshot& snapshot);
    static std::string Serialize(const MDSwapXSwapDepthQuoteSnapshot& snapshot);
    static std::string Serialize(const MDSwapXSwapTickExecution& snapshot);
    static std::string Serialize(const MDBondInfoInterbank& data);
    static std::string Serialize(const MDABSInfo& data);
    static std::string Serialize(const MDABSHistoryInfo& data);
    static std::string Serialize(const MDABSCreditRatings& data);
    static std::string Serialize(const MDPreIssuedBondInfo& data);
    static std::string Serialize(const MDPreIPOBondInfo& data);
    static std::string Serialize(const MDXBondTradeBondInfo& data);
    static std::string Serialize(const MDPledgedConvertRateACInfo& data);
    static std::string Serialize(const MDXRepoHierQuoteGroupInfo& data);
    static std::string Serialize(const MDXRepoContractInfo& data);
    static std::string Serialize(const MDSwapFixedFloatInfo& data);
    static std::string Serialize(const MDSwapFixedFloatBasisContractInfo& data);

    //美股
    static std::string Serialize(const MDUsaStockSnapshot& data);
    static std::string Serialize(const MDUsaOrderSnapshot& data);
    static std::string Serialize(const MDUsaEodSnapshot& data);

    //上海固收行情
    static std::string Serialize(const MDZQQDBJSnapshot& snapshot);
    static std::string Serialize(const MDZQCJHQSnapshot& snapshot);
    static std::string Serialize(const MDZQCJMXSnapshot& snapshot);

    static void FreeMemory(MDSnapshot* snapshots);
    static void FreeMemory(MDOptionSnapshot* snapshots);
    static void FreeMemory(MDHKTSnapshot* snapshots);
    static void FreeMemory(MDIndexSnapshot* snapshots);
    static void FreeMemory(MDTickOrder* ticks);
    static void FreeMemory(MDTickExecution* ticks);
    static void FreeMemory(MDOrderQueue* orderqueues);
    static void FreeMemory(MDAfterHourFixedPriceSnapshot* snapshots);
    static void FreeMemory(MDAfterHourFixedPriceTickExecution* ticks);
    static void FreeMemory(MDFutureSnapshot* snapshots);
    static void FreeMemory(MDCSIIndexSnapshot* snapshots);
    static void FreeMemory(MDIndicatorOfTradingVolumeSnapshot* snapshots);
    static void FreeMemory(MDCnIndexSnapshot* snapshots);
    static void FreeMemory(MDRefinancingTickOrder* ticks);
    static void FreeMemory(MDRefinancingTickExecution* ticks);
    static void FreeMemory(MDNegotiableTickOrder* ticks);
    static void FreeMemory(MDNegotiableTickExecution* ticks);
    static void FreeMemory(MDHKTRealtimeLimit* limit);
    static void FreeMemory(MDHKMarketStatus* limit);
    static void FreeMemory(MDHKTProductStatus* status);
    static void FreeMemory(MDHKTVCM* status);
    static void FreeMemory(MDNEEQSnapshot* snapshot);
    static void FreeMemory(MDNEEQSecurityInfo* info);
    static void FreeMemory(MDNEEQNonPublicTransDeclaredInfo* info);
    static void FreeMemory(MDNEEQHierarchicalInfo* info);
    static void FreeMemory(MDNEEQNegotiableDeclaredInfo* info);
    static void FreeMemory(MDNEEQMarketMakerDeclaredInfo* info);
    static void FreeMemory(MDNEEQNonPublicTransferDealInfo* info);
    static void FreeMemory(CodeTableRecord* info);
    static void FreeMemory(ETFCodeTableRecord* info);
    static void FreeMemory(IMCExchangeRate* info);
    static void FreeMemory(MDBondSnapshot* info);
    static void FreeMemory(MDBondTickOrder* info);
    static void FreeMemory(MDBondQuotedTickOrder* info);
    static void FreeMemory(MDBondTickExecution* info);
    static void FreeMemory(MDBondQuotedTickExecution* info);
    static void FreeMemory(MDOrderBookSnapshot* info);
    static void FreeMemory(MDIOPVSnapshot* info);
    static void FreeMemory(MDFundExpertSnapshot* info);
    static void FreeMemory(MDHKExSnapshot* infos);
    static void FreeMemory(MDHKExOrderSnapshot* infos);
    static void FreeMemory(MDHKExOrderBrokerSnapshot* infos);
    static void FreeMemory(MDHKExTickExecution* infos);
    static void FreeMemory(MDHKExIndexSnapshot* infos);
    static void FreeMemory(MDHKExConnectTurnoverSnapshot* infos);

    static void FreeMemory(MDSpotTickExecution* info);
    static void FreeMemory(MDSpotSummarySnapshot* info);
    static void FreeMemory(MDSpotXBondSnapshot* info);
    static void FreeMemory(MDPledgeRepoTickExecution* info);
    static void FreeMemory(MDPledgeRepoSummarySnapshot* info);
    static void FreeMemory(MDPledgeRepoInquirySnapshot* info);
    static void FreeMemory(MDPledgeRepoDepositSnapshot* info);
    static void FreeMemory(MDPledgeRepoXRepoSnapshot* info);
    static void FreeMemory(MDCeditLoanTickExecution* info);
    static void FreeMemory(MDCeditLoanSnapshot* info);
    static void FreeMemory(MDCeditLoanDepositSnapshot* info);
    static void FreeMemory(MDSwapFixedFloatTickExecution* info);
    static void FreeMemory(MDSwapFixedFloatSnapshot* info);
    static void FreeMemory(MDSwapXSwapSnapshot* info);
    static void FreeMemory(MDSwapXSwapBestOfferSnapshot* info);
    static void FreeMemory(MDBondLoanTickExecution* info);
    static void FreeMemory(MDBondLoanUnderlyingSecurityRateSnapshot* info);
    static void FreeMemory(MDBondLoanTradingProductRateSnapshot* info);
    static void FreeMemory(MDSpotMarketMakersQuoteSnapshot* info);
    static void FreeMemory(MDSpotDirectiveQuoteSnapshot* info);
    static void FreeMemory(MDSpotXBondDepthQuoteSnapshot* info);
    static void FreeMemory(MDSpotXBondMatchQuoteSnapshot* info);
    static void FreeMemory(MDPledgeRepoXRepoDepthQuoteSnapshot* info);
    static void FreeMemory(MDPledgeRepoXRepoBestOfferQuoteSnapshot* info);
    static void FreeMemory(MDSwapXSwapDepthQuoteSnapshot* info);
    static void FreeMemory(MDSwapXSwapTickExecution* info);
    static void FreeMemory(MDBondInfoInterbank* info);
    static void FreeMemory(MDABSInfo* info);
    static void FreeMemory(MDABSHistoryInfo* info);
    static void FreeMemory(MDABSCreditRatings* info);
    static void FreeMemory(MDPreIssuedBondInfo* info);
    static void FreeMemory(MDPreIPOBondInfo* info);
    static void FreeMemory(MDXBondTradeBondInfo* info);
    static void FreeMemory(MDPledgedConvertRateACInfo* info);
    static void FreeMemory(MDXRepoHierQuoteGroupInfo* info);
    static void FreeMemory(MDXRepoContractInfo* info);
    static void FreeMemory(MDSwapFixedFloatInfo* info);
    static void FreeMemory(MDSwapFixedFloatBasisContractInfo* info);

    //美股
    static void FreeMemory(MDUsaStockSnapshot* info);
    static void FreeMemory(MDUsaOrderSnapshot* info);
    static void FreeMemory(MDUsaEodSnapshot* info);

    //上海固收行情
    static void FreeMemory(MDZQQDBJSnapshot* info);
    static void FreeMemory(MDZQCJHQSnapshot* info);
    static void FreeMemory(MDZQCJMXSnapshot* info);

    static std::string GetEventLevelString(uint32_t level);
    static std::string GetEventCodeString(uint32_t level);
    
    //现在暂时只支持现货/债券/股票期权的交易阶段代码转换成TradingPhaseCode类型
    static uint16_t ConvertTradingPhaseCode(const uint32_t& market_type, const uint64_t& orig_time, char* trading_phase_code, const uint32_t& len = 8);


    static uint64_t GetRealTime();
};


};
};


#endif //SWIG_WRAP_H_
