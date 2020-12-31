/////////////////////////////////////////////////////////////////////////
///@system 今古交易系统
///@company 深圳市今古科技有限公司
///@file JGtdcUserApiStruct.h
///@brief  接口使用的业务数据结构
///@history 
///2018-02-24	zl	
/////////////////////////////////////////////////////////////////////////
#if !defined(JG_TDCSTRUCT_H)
#define JG_TDCSTRUCT_H

#if _MSC_VER > 1000 
#pragma once 
#endif 
#include <string.h>
#include "JGtdcUserApiDataType.h"


///< 响应信息
struct CJGtdcRspInfoField
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	int nFieldItem;                                 ///< 应答数据个数  
	CJGtdcRspInfoField()
	{
		memset(this, 0, sizeof(CJGtdcRspInfoField));
	}
};

///< 用户机器信息
struct CJGtdcMachineInfo
{
	///< 必送
	TJGtdcLocalIpType  LocalIPAddr;                 ///< 本地IP
	TJGtdcNetIpType    NetIPAddr;					///< 外网IP
	TJGtdcMACType      MacAddr;						///< MAC地址
	TJGtdcHDSequenceNoType  HDSequenceNo;			///< 硬盘序列号
	TJGtdcCPUIDType     CPUID;						///< CPUID

	///< 选送
	TJGtdcVersion     Version;						///< 客户端版本号
	TJGtdcQSIDType     QSID;						///< 券商ID

	CJGtdcMachineInfo()
	{
		memset(this, 0, sizeof(CJGtdcMachineInfo));
	}
};

///< 用户网络连接信息
struct CJGtdcNetInfo
{
	TJGtdcNetIpType      IPAddr;					///< 连接IP
	TJGtdcNetPortType    Port;						///< 端口
	TJGtdcNetDomain      Domain;                    ///< 是否为域名
	TJGtdcNetBytes       RecvBytes;					///< 发送字节数
	TJGtdcNetBytes       SendBytes;					///< 接收字节数
	TJGtdcConnectStates  ConnectState;				///< 网络连接状态
};

///< 用户登陆请求
struct CJGtdcReqUserLogin
{
	TJGtdcLoginType LoginType;					    ///< @登陆校验类型
	TJGtdcExchangeType ExchangeType;		        ///< @市场类型
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号  
	TJGtdcLoginCodeType LoginCode;			        ///< 登陆代码
	TJGtdcPassWordType  LoginPassword;			    ///< 登陆密码
	TJGtdcMacAddressType MACAddress;                ///< MAC地址
	TJGtdcIPAddrType IPAddress;                     ///< IP地址    
	TJGtdcMD5Type        MD5;                       ///< MD5
	CJGtdcReqUserLogin()
	{
		memset(this, 0, sizeof(CJGtdcReqUserLogin));
	}
};

///< 用户登陆应答
struct CJGtdcRspUserLogin
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcSupportSubType SupportSubType;			///< 支持的订阅类型
	CJGtdcRspUserLogin()
	{
		memset(this, 0, sizeof(CJGtdcRspUserLogin));
	}
};

///< 用户订阅数据类型
struct CJGtdcReqUserSubData
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcSubType SubType;							///< 订阅类型
	TJGtdcSupportSubType SubDataType;				///< 订阅数据类型
};

///< 用户订阅数据类型应答
struct CJGtdcRspUserSubData
{
	TJGtdcSupportSubType SubDataType;				///< 成功订阅数据类型
};

///< 投资资金账号基础信息
struct CJGtdcUserAccountInfo
{
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcPassWordType PassWord;                    ///< 账号密码  
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcClientNameType ClientName;                ///< 客户姓名
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcAccountRights AccountRights;              ///< 账户权限  
	CJGtdcUserAccountInfo()
	{
		memset(this, 0, sizeof(CJGtdcUserAccountInfo));
	}
};

///< 投资者资金账号股东信息
struct CJGtdcUserHolderInfo
{
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcHolderNameType HolderName;                ///< 股东姓名
	TJGtdcSeatNoType SeatNo;                        ///< 席位号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcHolderStatus HolderStatus;                ///< 股东状态
	TJGtdcMainFlag MainType;                        ///< 股东主副标志 
	CJGtdcUserHolderInfo()
	{
		memset(this, 0, sizeof(CJGtdcUserHolderInfo));
	}
};

///< 用户登出请求
struct CJGtdcReqUserLogout
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	CJGtdcReqUserLogout()
	{
		memset(this, 0, sizeof(CJGtdcReqUserLogout));
	}
};

///< 用户登出应答
struct CJGtdcRspUserLogout
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	CJGtdcRspUserLogout()
	{
		memset(this, 0, sizeof(CJGtdcRspUserLogout));
	}
};

///< 用户报单录入
struct CJGtdcReqOrderInsert
{
	TJGtdcClientIDType ClientID;                    ///< 客户号 
	TJGtdcBatchNoType BatchNo;                      ///< 批号 (暂时原值返回字段)
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格 (实际价格乘以10000 送入)
	CJGtdcReqOrderInsert()
	{
		memset(this, 0, sizeof(CJGtdcReqOrderInsert));
	}
};

///< 用户报单应答
struct CJGtdcRspOrderInsert
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号  
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格 
	CJGtdcRspOrderInsert()
	{
		memset(this, 0, sizeof(CJGtdcRspOrderInsert));
	}
};

///< 用户撤单请求
struct CJGtdcReqOrderCancel
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号  
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	CJGtdcReqOrderCancel()
	{
		memset(this, 0, sizeof(CJGtdcReqOrderCancel));
	}
};

///< 用户撤单应答
struct CJGtdcRspOrderCancel
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号  
	TJGtdcEntrustNoType NewEntrustNo;               ///< 新合同号
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	CJGtdcRspOrderCancel()
	{
		memset(this, 0, sizeof(CJGtdcRspOrderCancel));
	}
};

///< 投资者可撤单查询
struct CJGtdcReqQryCancel
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号 
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	CJGtdcReqQryCancel()
	{
		memset(this, 0, sizeof(CJGtdcReqQryCancel));
	}
};

///< 投资者可撤单查询应答
struct CJGtdcRspQryCancel
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcSeatNoType SeatNo;                        ///< 席位号
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcEntrustStatus EntrustStatus;              ///< 委托状态 
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcDate EntrustDate;                         ///< 委托日期
	TJGtdcTime EntrustTime;                         ///< 委托时间
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBuinessVolume  BusinessVolume;            ///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;              ///< 成交价格
	TJGtdcCancelVolume CancelVolume;                ///< 撤单数量
	TJGtdcBusinessBalance BusinessBalance;          ///< 成交金额
	TJGtdcServiceType  ServiceType;                 ///< 业务类型
	CJGtdcRspQryCancel()
	{
		memset(this, 0, sizeof(CJGtdcRspQryCancel));
	}
};

///< 投资者当日委托查询
struct CJGtdcReqQryOrder
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式 
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号  
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	CJGtdcReqQryOrder()
	{
		memset(this, 0, sizeof(CJGtdcReqQryOrder));
	}
};

///< 投资者当日委托查询应答
struct CJGtdcRspQryOrder
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcSeatNoType SeatNo;                        ///< 席位号
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcEntrustStatus EntrustStatus;              ///< 委托状态 
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcDate EntrustDate;                         ///< 委托日期
	TJGtdcTime EntrustTime;                         ///< 委托时间
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBuinessVolume  BusinessVolume;            ///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;              ///< 成交价格
	TJGtdcCancelVolume CancelVolume;                ///< 撤单数量
	TJGtdcBusinessBalance BusinessBalance;          ///< 成交金额
	TJGtdcServiceType  ServiceType;                 ///< 业务类型
	CJGtdcRspQryOrder()
	{
		memset(this, 0, sizeof(CJGtdcRspQryOrder));
	}
};

///< 投资者成交单查询
struct CJGtdcReqQryTrade
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号  
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	CJGtdcReqQryTrade()
	{
		memset(this, 0, sizeof(CJGtdcReqQryTrade));
	}
};

///< 投资者成交单查询应答
struct CJGtdcRspQryTrade
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcSeatNoType SeatNo;                        ///< 席位号
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号
	TJGtdcBusinessNoType BusinessNo;                ///< 成交编号 
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBusinessStatus BusinessStatus;            ///< 成交状态 
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcDate BusinessDate;                        ///< 成交日期
	TJGtdcTime BusinessTime;                        ///< 成交时间
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBuinessVolume  BusinessVolume;            ///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;              ///< 成交价格
	TJGtdcCancelVolume CancelVolume;                ///< 撤单数量
	TJGtdcBusinessBalance BusinessBalance;          ///< 成交金额
	CJGtdcRspQryTrade()
	{
		memset(this, 0, sizeof(CJGtdcRspQryTrade));
	}
};

///< 投资者持仓查询
struct CJGtdcReqQryHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	CJGtdcReqQryHold()
	{
		memset(this, 0, sizeof(CJGtdcReqQryHold));
	}
};

///< 投资者持仓查询应答
struct CJGtdcRspQryHold
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcYdAmount  YdAmount;                       ///< 昨日持仓量
	TJGtdcStockAmount StockAmount;                  ///< 股份余额
	TJGtdcEnableAmount EnableAmount;                ///< 可卖数量
	TJGtdcPurchaseAmount PurchaseAmount;            ///< 可申购数量
	TJGtdcPossessAmount PossessAmount;              ///< 当前拥股数量
	TJGtdcFrozenAmount FrozenAmount;                ///< 冻结数量
	TJGtdcYStoreAmount YStoreAmount;                ///< 昨日库存数量  
	TJGtdcCostPrice CostPrice;                      ///< 成本价格
	TJGtdcKeepCostPrice KeepCostPrice;              ///< 保本价格
	TJGtdcBuyCost BuyCost;                          ///< 当前成本
	TJGtdcStockBalance StockBalance;                ///< 证券市值
	TJGtdcFloatIncome FloatIncome;                  ///< 浮动盈亏
	TJGtdcProIncome ProIncome;                      ///< 累计盈亏 
	CJGtdcRspQryHold()
	{
		memset(this, 0, sizeof(CJGtdcRspQryHold));
	}
};

///< 投资者资金查询
struct CJGtdcReqQryFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcMoneyType MoneyType;                      ///< 币种
	CJGtdcReqQryFund()
	{
		memset(this, 0, sizeof(CJGtdcReqQryFund));
	}
};

///< 投资者资金查询应答
struct CJGtdcRspQryFund
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;                        ///< 主副标志
	TJGtdcEnableBalance EnableBalance;              ///< 可用余额
	TJGtdcFetchBalance FetchBalance;                ///< 可取余额
	TJGtdcFrozenBalance FrozenBalance;              ///< 冻结金额
	TJGtdcStockBalance StockBalance;                ///< 证券市值
	TJGtdcFundBalance FundBalance;                  ///< 资金余额
	TJGtdcAssetBalance AssetBalance;                ///< 资产总值
	TJGtdcIncome  InCome;                           ///< 总盈亏 
	TJGtdcEnableBalanceHK EnableBalanceHK;			///< 港股可用余额
	CJGtdcRspQryFund()
	{
		memset(this, 0, sizeof(CJGtdcRspQryFund));
	}
};

///< 投资者交割单查询
struct CJGtdcReqQryDelivery
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码 
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcDate nStartDate;							///< 起始日期
	TJGtdcDate nEndDate;							///< 结束日期
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串

	CJGtdcReqQryDelivery()
	{
		memset(this, 0, sizeof(CJGtdcReqQryDelivery));
	}
};

///< 投资者交割单查询应答
struct CJGtdcRspQryDelivery
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码 
	TJGtdcSeatNoType SeatNo;				        ///< 席位号
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBusinessNoType BusinessNo;				///< 成交号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcDigestType DigestType;					///< 业务类型
	TJGtdcDigestName DigestName;					///< 业务名称
	TJGtdcDate BusinessDate;						///< 成交日期
	TJGtdcTime BusinessTime;						///< 成交时间
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBuinessVolume  BusinessVolume;            ///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;              ///< 成交价格
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcBusinessCount BusinessCount;				///< 成交笔数
	TJGtdcClearBalance ClearBalance;				///< 清算金额
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcStockAmount StockAmount;					///< 股份余额
	TJGtdcFeeStamp FeeStamp;						///< 印花税
	TJGtdcFeeCommission FeeCommission;				///< 佣金
	TJGtdcFeeTransfer FeeTransfer;					///< 过户费
	TJGtdcFeeOther FeeOther;						///< 其它费用

	CJGtdcRspQryDelivery()
	{
		memset(this, 0, sizeof(CJGtdcRspQryDelivery));
	}
};

///< 投资者港股汇率查询
struct CJGtdcReqQryHKExRate
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种

	CJGtdcReqQryHKExRate()
	{
		memset(this, 0, sizeof(CJGtdcReqQryHKExRate));
	}
};

///< 投资者港股汇率查询应答
struct CJGtdcRspQryHKExRate
{
	TJGtdcDPriceType BuyPrice;						///< 买入价格
	TJGtdcDPriceType SellPrice;						///< 卖出价格
	TJGtdcDPriceType MidProce;						///< 中间价格
	TJGtdcDate      Date;							///< 适用日期
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种

	CJGtdcRspQryHKExRate()
	{
		memset(this, 0, sizeof(CJGtdcRspQryHKExRate));
	}
};

///< 投资者港股额度查询
struct CJGtdcReqQryHKLimit
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种

	CJGtdcReqQryHKLimit()
	{
		memset(this, 0, sizeof(CJGtdcReqQryHKLimit));
	}
};

///< 投资者港股额度查询应答
struct CJGtdcRspQryHKLimit
{
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBalanceType InitBalance;					///< 初始额度
	TJGtdcBalanceType RestBalance;					///< 剩余额度
	TJGtdcEdType  EdType;							///< 额度状态
	TJGtdcDate     Date;							///< 适用日期

	CJGtdcRspQryHKLimit()
	{
		memset(this, 0, sizeof(CJGtdcRspQryHKLimit));
	}
};

///< 投资者最大委托数查询
struct CJGtdcReqQryMax
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBatchNoType BatchNo;                      ///< 批号（原值返回字段）  
	CJGtdcReqQryMax()
	{
		memset(this, 0, sizeof(CJGtdcReqQryMax));
	}
};

///< 投资者最大委托数应答
struct CJGtdcRspQryMax
{
	TJGtdcStockAccountType StockAccount;            ///< 股东代码 
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcPriceType PriceType;                      ///< 价格类型
	TJGtdcOrderPrice OrderPrice;                    ///< 委托价格
	TJGtdcBatchNoType BatchNo;                      ///< 批号（原值返回字段） 
	TJGtdcMaxAmount MaxAmount;                      ///< 最大可交易数量 
	CJGtdcRspQryMax()
	{
		memset(this, 0, sizeof(CJGtdcRspQryMax));
	}
};

///< 投资者ETF交易品种查询
struct CJGtdcReqETFCode
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量

	CJGtdcReqETFCode()
	{
		memset(this, 0, sizeof(CJGtdcReqETFCode));
	}
};

///< 投资者ETF交易品种查询应答
struct CJGtdcRspETFCode
{
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockCodeType ETFPRCode;					///< ETF申赎代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcApplyRedeemUnit ApplyRedeemUnit;          ///< 最小申购赎回份数
	TJGtdcEstimateCashBalance EstimateCashBalance;  ///< 当日日预估现金余额
	TJGtdcMaxCashRatio MaxCashRatio;					///< 现金替代比例上限
	TJGtdcEstimateCashComponent EstimateCashComponent;	///< 上日预估现金差额
	TJGtdcETFType ETFType;							///< ETF属性
	TJGtdcSampleAmount SampleAmount;                ///< 成分股数量
	TJGtdcTotalAmount TotalAmount;                  ///< 篮子股总数量
	TJGtdcTNAV TNAV;								///< 资产净值
	TJGtdcApplyRedeem   ApplyRedeem;                ///< 是否允许进行申购赎回

	CJGtdcRspETFCode()
	{
		memset(this, 0, sizeof(CJGtdcRspETFCode));
	}
};

///< 投资者ETF篮子清单查询
struct CJGtdcReqETFBasketComponent
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码

	CJGtdcReqETFBasketComponent()
	{
		memset(this, 0, sizeof(CJGtdcReqETFBasketComponent));
	}
};

///< 投资者ETF篮子清单查询应答
struct CJGtdcRspETFBasketComponent
{
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;                  ///< 证券名称
	TJGtdcStockAmount StockAmount;					///< 股票数量
	TJGtdcCashSubstituteFlag CashSubstituteFlag;	///< 现金替代标志
	TJGtdcPremiumRatio PremiumRatio;				///< 溢价比例
	TJGtdcCashSubstituteAmount CashSubstituteAmount;///< 现金替代金额

	CJGtdcRspETFBasketComponent()
	{
		memset(this, 0, sizeof(CJGtdcRspETFBasketComponent));
	}
};


//股票银行账号查询请求
struct CJGtdcReqQryBankAccount
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码

	CJGtdcReqQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcReqQryBankAccount));
	}
};

//股票银行账号查询应答
struct CJGtdcRspQryBankAccount
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcBankAccount BankAccount;				    ///< 银行账户
	TJGtdcBankFlag BankFlag;						///< 银行标识
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcConvertOption SecToBank_ConvertOption;	///< 证转银@转账选项
	TJGtdcConvertOption BankToSec_ConvertOption;	///< 银转证@转账选项
	TJGtdcExchangeType ExchangeType;                ///< 市场类型

	CJGtdcRspQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcRspQryBankAccount));
	}
};


///股票银衍转账
struct CJGtdcReqBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankPassword BankPassword;				///< 银行密码
	TJGtdcFundPassword FundPassword;				///< 资金密码
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcReqBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqBankTrans));
	}
};

///股票银衍转账应答
struct CJGtdcRspBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 转账流水委托号
	TJGtdcEntrustNoType MoneyEntrustNo;				///< 资金流水委托号
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcRspBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspBankTrans));
	}
};

///股票银衍转账查询
struct CJGtdcReqQryBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcDate nStartDate;							///< 起始日期
	TJGtdcDate nEndDate;							///< 结束日期

	CJGtdcReqQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqQryBankTrans));
	}
};

///股票银衍转账查询应答
struct CJGtdcRspQryBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName	BankName;						///< 银行名称
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcEntrustNoType EntrustNo;					///< 委托号
	TJGtdcOpConfigInfo OpConfigInfo;				///< 操作确认信息
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcDate OperDate;							///< 操作日期
	TJGtdcTime OperTime;							///< 操作时间
	TJGtdcOpRetCode  OpRetCode;						///< 操作返回代码
	TJGtdcOperBalance OperBalance;					///< 操作金额



	CJGtdcRspQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspQryBankTrans));
	}
};

//股票银衍转账可转资金请求
struct CJGtdcReqQryBankMaxTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号

	CJGtdcReqQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqQryBankMaxTrans));
	}
};

//股票银衍转账可转资金应答
struct CJGtdcRspQryBankMaxTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	CJGtdcRspQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspQryBankMaxTrans));
	}
};

//股票查询子账户及其资金请求
struct CJGtdcReqQryChildBankFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	CJGtdcReqQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcReqQryChildBankFund));
	}
};

//股票查询子账户及其资金应答
struct CJGtdcRspQryChildBankFund
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	CJGtdcRspQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcRspQryChildBankFund));
	}
};


//股票同名账户资金内转请求
struct CJGtdcReqInTransferFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcTransBalance TransBalance;				///< 内转金额
	CJGtdcReqInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcReqInTransferFund));
	}
};


//股票同名账户资金内转应答
struct CJGtdcRspInTransferFund
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcEntrustNoType InTransNo;					///< 转入流水号
	TJGtdcEntrustNoType OutTransNo;					///< 转出流水号

	CJGtdcRspInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcRspInTransferFund));
	}
};


/////////////////////////////////////////融资融券专用///////////////////////////////////////////////////
///< 投资者直接还券
struct CJGtdcReqStockBack
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcBatchNoType BatchNo;				        ///< 批号
	TJGtdcStockBackMode StockBackMode;			    ///< 还券模式
	TJGtdcOrderVolume EntrustAmount;			    ///< 委托数量

	CJGtdcReqStockBack()
	{
		memset(this, 0, sizeof(CJGtdcReqStockBack));
	}
};

///< 投资者直接还券应答
struct CJGtdcRspStockBack
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;			        ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;			        ///< 合同号
	TJGtdcBatchNoType BatchNo;				        ///< 批号
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcStockBackMode StockBackMode;			    ///< 还券模式
	TJGtdcOrderVolume EntrustAmount;			    ///< 委托数量
	CJGtdcRspStockBack()
	{
		memset(this, 0, sizeof(CJGtdcRspStockBack));
	}
};

///< 投资者直接还款
struct CJGtdcReqMoneyBack
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockBackMode PayBackMode;				///< 还款模式
	TJGtdcPayBackBalance PayBackBalance;			///< 还款金额
	CJGtdcReqMoneyBack()
	{
		memset(this, 0, sizeof(CJGtdcReqMoneyBack));
	}
};

///< 投资者直接还款应答
struct CJGtdcRspMoneyBack
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;			        ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;			        ///< 合同号
	TJGtdcMoneyType MoneyType;					    ///< 币种
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockBackMode PayBackMode;			    ///< 还款模式
	TJGtdcPayBackBalance PayBackBalance;		    ///< 还款金额
	CJGtdcRspMoneyBack()
	{
		memset(this, 0, sizeof(CJGtdcRspMoneyBack));
	}
};

///< 投资者可融券卖出数量查询
struct CJGtdcReqQryMaxLoan
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockCodeType StockCode;		            ///< 证券代码
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	CJGtdcReqQryMaxLoan()
	{
		memset(this, 0, sizeof(CJGtdcReqQryMaxLoan));
	}
};


///< 投资者可融券卖出数量查询应答
struct CJGtdcRspQryMaxLoan
{
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockCodeType StockCode;		            ///< 证券代码
	TJGtdcStockNameType StockName;		            ///< 证券名称
	TJGtdcMaxLoanAmount MaxLoanAmount;			    ///< 可融券数量
	CJGtdcRspQryMaxLoan()
	{
		memset(this, 0, sizeof(CJGtdcRspQryMaxLoan));
	}
};

///< 投资者可融券私有卖出数量查询
struct CJGtdcReqQryReserveCreditStock
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockCodeType StockCode;		            ///< 证券代码

	CJGtdcReqQryReserveCreditStock()
	{
		memset(this, 0, sizeof(CJGtdcReqQryReserveCreditStock));
	}
};

///< 投资者可融券私有卖出数量查询应答
struct CJGtdcRspQryReserveCreditStock
{
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcStockCodeType StockCode;		            ///< 证券代码
	TJGtdcStockNameType StockName;			        ///< 证券名称
	TJGtdcReserveAmount ReserveAmount;				///< 保底数量
	TJGtdcReserveRemainAmount ReserveRemainAmount;	///< 保底剩余数量
	TJGtdcDate StartDate;							///< 开始日期
	TJGtdcDate EndDate;								///< 结束日期

	CJGtdcRspQryReserveCreditStock()
	{
		memset(this, 0, sizeof(CJGtdcRspQryReserveCreditStock));
	}
};

///< 投资者信用资产查询
struct CJGtdcReqQryAssets
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;				        ///< 查询模式
	TJGtdcMoneyType MoneyType;			            ///< 币种
	CJGtdcReqQryAssets()
	{
		memset(this, 0, sizeof(CJGtdcReqQryAssets));
	}
};

///< 投资者信用资产查询应答
struct CJGtdcRspQryAssets
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	TJGtdcFrozenBalance FrozenBalance;				///< 冻结金额
	TJGtdcStockBalance StockBalance;				///< 证券市值
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcAssetBalance AssetBalance;				///< 资产总值
	TJGtdcIncome Income;							///< 总盈亏
	TJGtdcEnableBail EnableBail;					///< 可用保证金
	TJGtdcCreditQuota CreditQuota;					///< 授信额度
	TJGtdcFinanceQuota FinanceQuota;				///< 可融资金
	TJGtdcShortsellQuota ShortsellQuota;			///< 可融券额度
	TJGtdcAssureRatio AssureRatio;					///< 维持担保比例
	TJGtdcTotalDebit TotalDebit;					///< 总负债
	TJGtdcFundDebit FundDebit;						///< 资金负债
	TJGtdcStockDebit StockDebit;					///< 股票负债
	TJGtdcMustBackBalance MustBackBalance;			///< 应还金额
	CJGtdcRspQryAssets()
	{
		memset(this, 0, sizeof(CJGtdcRspQryAssets));
	}
};

///< 投资者融资状况查询
struct CJGtdcReqQryFinance
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcDebitStatus DebitStatus;					///< 负债现状
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	CJGtdcReqQryFinance()
	{
		memset(this, 0, sizeof(CJGtdcReqQryFinance));
	}
};

///< 投资者融资状况查询应答
struct CJGtdcRspQryFinance
{
	TJGtdcBranchNoType BranchNo;			        ///< 营业部号
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcFundAccountType FundAccount;		        ///< 资金账号
	TJGtdcExchangeType ExchangeType;		        ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;				        ///< 席位号
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcStockNameType StockName;			        ///< 证券名称
	TJGtdcEntrustNoType EntrustNo;			        ///< 报盘合同号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcDebitStatus DebitStatus;					///< 负债现状
	TJGtdcDate OccurDate;							///< 发生日期
	TJGtdcOccurAmount OccurAmount;					///< (买入数量)融资
	TJGtdcOccurBalance OccurBalance;				///< 发生金额  融资
	TJGtdcBackAmount BackAmount;					///< 归还数量  融资
	TJGtdcBackBalance BackBalance;					///< 归还金额  融资

	CJGtdcRspQryFinance()
	{
		memset(this, 0, sizeof(CJGtdcRspQryFinance));
	}
};

///< 投资者融券状况查询
struct CJGtdcReqQryShortsell
{
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcExchangeType ExchangeType;		        ///< 市场类型
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcDebitStatus DebitStatus;			        ///< 负债现状
	TJGtdcDate StartDate;					        ///< 起始日期
	TJGtdcDate EndDate;						        ///< 结束日期
	CJGtdcReqQryShortsell()
	{
		memset(this, 0, sizeof(CJGtdcReqQryShortsell));
	}
};

///< 投资者融券状况查询应答
struct CJGtdcRspQryShortsell
{
	TJGtdcBranchNoType BranchNo;			        ///< 营业部号
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcFundAccountType FundAccount;		        ///< 资金账号
	TJGtdcExchangeType ExchangeType;		        ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;				        ///< 席位号
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcStockNameType StockName;			        ///< 证券名称
	TJGtdcEntrustNoType EntrustNo;			        ///< 合同号
	TJGtdcMoneyType MoneyType;				        ///< 币种
	TJGtdcDebitStatus DebitStatus;			        ///< 负债现状
	TJGtdcDate OccurDate;					        ///< 发生日期
	TJGtdcOccurAmount OccurAmount;			        ///< 发生数量 融券
	TJGtdcOccurBalance OccurBalance;		        ///< 发生金额 融券
	TJGtdcBackAmount BackAmount;			        ///< 归还数量 融券
	TJGtdcBackBalance BackBalance;			        ///< 归还金额 融券
	CJGtdcRspQryShortsell()
	{
		memset(this, 0, sizeof(CJGtdcRspQryShortsell));
	}
};

///担保品划转
struct CJGtdcReqMortgageTrans
{
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcExchangeType ExchangeType;		        ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;				        ///< 席位号
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码
	TJGtdcOtherSeatNoType OtherSeatNo;				///< 对方席位号

	CJGtdcReqMortgageTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqMortgageTrans));
	}
};

///担保品划转应答
struct CJGtdcRspMortgageTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 委托号
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	TJGtdcExchangeType ExchangeType;		        ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;			        ///< 证券代码
	TJGtdcTradeType TradeType;                      ///< 交易类型
	TJGtdcOrderVolume OrderVolume;                  ///< 委托数量
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码

	CJGtdcRspMortgageTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspMortgageTrans));
	}
};

///标的券查询
struct  CJGtdcReqQryObject
{
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式 
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	
	CJGtdcReqQryObject()
	{
		memset(this, 0, sizeof(CJGtdcReqQryObject));
	}
};

///标的券查询应答
struct  CJGtdcRspQryObject
{
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串 
	TJGtdcObjectRights  ObjectRights;				///< @标的权限（按位）
	TJGtdcFinanceBailRatio FinanceBailRatio;		///< 融资保证金比例
	TJGtdcShortsellBailRatio ShortsellBailRatio;	///< 融券保证金比例
	TJGtdcMortgageRatio MortgageRatio;				///< 担保品折算率

	CJGtdcRspQryObject()
	{
		memset(this, 0, sizeof(CJGtdcRspQryObject));
	}
};


//查询信用账户与普通账户对应关系
struct CJGtdcReqQryAccMatch
{
	TJGtdcClientIDType ClientID;			        ///< 客户号
	TJGtdcQueryMark QueryMark;                      ///< 查询标志 
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码

	CJGtdcReqQryAccMatch()
	{
		memset(this, 0, sizeof(CJGtdcReqQryAccMatch));
	}
};

//查询信用账户与普通账户对应关系应答
struct CJGtdcRspQryAccMatch
{
	TJGtdcClientNameType ClientName;				///< 客户姓名
	TJGtdcCertType CertType;						///< 证件类型
	TJGtdcCertCode CertCode;						///< 证件号码
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcBranchNoType CreditBranchNo;				///< 信用营业部号
	TJGtdcFundAccountType CreditFundAccount;		///< 信用资金帐号
	TJGtdcStockAccountType CreditHolderAccount;		///< 信用股东帐户
	TJGtdcBranchNoType StockBranchNo;				///< 普通营业部号
	TJGtdcFundAccountType StockFundAccount;			///< 普通资金帐号
	TJGtdcStockAccountType StockHolderAccount;		///< 普通股东帐户
	TJGtdcSeatNoType StockSeatNo;					///< 普通帐户席位
	CJGtdcRspQryAccMatch()
	{
		memset(this, 0, sizeof(CJGtdcReqQryAccMatch));
	}
};

//信用银行账号查询请求
struct CJGtdcReqCreditQryBankAccount
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码

	CJGtdcReqCreditQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditQryBankAccount));
	}
};

//信用银行账号查询应答
struct CJGtdcRspCreditQryBankAccount
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcBankAccount BankAccount;				    ///< 银行账户
	TJGtdcBankFlag BankFlag;						///< 银行标识
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcConvertOption SecToBank_ConvertOption;	///< 证转银@转账选项
	TJGtdcConvertOption BankToSec_ConvertOption;	///< 银转证@转账选项
	TJGtdcExchangeType ExchangeType;                ///< 市场类型

	CJGtdcRspCreditQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditQryBankAccount));
	}
};


///信用银衍转账
struct CJGtdcReqCreditBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankPassword BankPassword;				///< 银行密码
	TJGtdcFundPassword FundPassword;				///< 资金密码
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcReqCreditBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditBankTrans));
	}
};

///信用银衍转账应答
struct CJGtdcRspCreditBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 转账流水委托号
	TJGtdcEntrustNoType MoneyEntrustNo;				///< 资金流水委托号
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcRspCreditBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditBankTrans));
	}
};

///信用银衍转账查询
struct CJGtdcReqCreditQryBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcDate nStartDate;							///< 起始日期
	TJGtdcDate nEndDate;							///< 结束日期

	CJGtdcReqCreditQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditQryBankTrans));
	}
};

///信用银衍转账查询应答
struct CJGtdcRspCreditQryBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName	BankName;						///< 银行名称
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcEntrustNoType EntrustNo;					///< 委托号
	TJGtdcOpConfigInfo OpConfigInfo;				///< 操作确认信息
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcDate OperDate;							///< 操作日期
	TJGtdcTime OperTime;							///< 操作时间
	TJGtdcOpRetCode  OpRetCode;						///< 操作返回代码
	TJGtdcOperBalance OperBalance;					///< 操作金额



	CJGtdcRspCreditQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditQryBankTrans));
	}
};

//信用银衍转账可转资金请求
struct CJGtdcReqCreditQryBankMaxTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号

	CJGtdcReqCreditQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditQryBankMaxTrans));
	}
};

//信用银衍转账可转资金应答
struct CJGtdcRspCreditQryBankMaxTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	CJGtdcRspCreditQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditQryBankMaxTrans));
	}
};

//信用查询子账户及其资金请求
struct CJGtdcReqCreditQryChildBankFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	CJGtdcReqCreditQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditQryChildBankFund));
	}
};

//信用查询子账户及其资金应答
struct CJGtdcRspCreditQryChildBankFund
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	CJGtdcRspCreditQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditQryChildBankFund));
	}
};


//信用同名账户资金内转请求
struct CJGtdcReqCreditInTransferFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcTransBalance TransBalance;				///< 内转金额
	CJGtdcReqCreditInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcReqCreditInTransferFund));
	}
};


//信用同名账户资金内转应答
struct CJGtdcRspCreditInTransferFund
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcEntrustNoType InTransNo;					///< 转入流水号
	TJGtdcEntrustNoType OutTransNo;					///< 转出流水号

	CJGtdcRspCreditInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcRspCreditInTransferFund));
	}
};


///< 投资者期货账号登陆
struct CJGtdcFutureReqUserLogin
{
	TJGtdcLoginType LoginType;					    ///< @登陆校验类型
	TJGtdcExchangeType ExchangeType;		        ///< @市场类型
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号  
	TJGtdcLoginCodeType LoginCode;			        ///< 登陆代码
	TJGtdcPassWordType  LoginPassword;			    ///< 登陆密码
	TJGtdcMD5Type        MD5;                       ///< MD5
	CJGtdcFutureReqUserLogin()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqUserLogin));
	}
};

///< 投资者期货账号登陆应答
struct CJGtdcFutureRspUserLogin
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcSupportSubType SupportSubType;			///< 支持的订阅类型
	CJGtdcFutureRspUserLogin()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspUserLogin));
	}
};

///< 投资者期货账号登出
struct CJGtdcFutureReqUserLogout
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	CJGtdcFutureReqUserLogout()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqUserLogout));
	}
};

///< 投资者期货账号登出应答
struct CJGtdcFutureRspUserLogout
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	CJGtdcFutureRspUserLogout()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspUserLogout));
	}
};

///< 投资者期货账单查询
struct CJGtdcFutureReqQrySettlement
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcDate Date;					            ///< 日期

	CJGtdcFutureReqQrySettlement()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQrySettlement));
	}
};

///< 投资者期货账单查询应答
struct CJGtdcFutureRspQrySettlement
{
	TJGtdcBranchNoType BranchNo;		            ///< 营业部号
	TJGtdcClientIDType ClientID;		            ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcDate Date;								///< 日期
	TJGtdcSettleInfoLen SettleInfoLen;				///< 账单信息长度
	TJGtdcSettleInfoType SettleInfo;	            ///< 账单信息

	CJGtdcFutureRspQrySettlement()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQrySettlement));
	}
};

///< 投资者期货账单确认
struct CJGtdcFutureReqConfirmSettle
{
	TJGtdcClientIDType ClientID;		            ///< 客户号
	TJGtdcDate ConfirmDate;			                ///< 账单确认日期
	TJGtdcTime ConfirmTime;			                ///< 账单确认时间

	CJGtdcFutureReqConfirmSettle()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqConfirmSettle));
	}
};

///< 投资者期货账单确认应答
struct CJGtdcFutureRspConfirmSettle
{
	TJGtdcDate ConfirmDate;	                        ///< 账单确认日期
	CJGtdcFutureRspConfirmSettle()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspConfirmSettle));
	}
};

///< 投资者期货合约查询
struct CJGtdcFutureReqQryContract
{
	TJGtdcClientIDType ClientID;		            ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcContractCodeType ContractCode;	        ///< 合约代码
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcFutureReqQryContract()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryContract));
	}
};

///< 投资者期货合约查询应答
struct CJGtdcFutureRspQryContract
{
	TJGtdcExchangeType ExchangeType;			    ///< 市场类型
	TJGtdcContractCodeType ContractCode;	        ///< 合约代码
	TJGtdcContractNameType ContractName;	        ///< 合约名称
	TJGtdcPositionStrType PositionStr;		        ///< 定位串
	TJGtdcMoneyType MoneyType;					    ///< 币种
	TJGtdcAmountMultiple AmountMultiple;		    ///< 合约乘数
	TJGtdcPriceTick PriceTick;					    ///< 最小价位变动
	TJGtdcMaxMarketEntrustAmount MaxMarketEntrustAmount;///< 市价单最大下单量
	TJGtdcMaxLimitEntrustAmount MaxLimitEntrustAmount;	///< 限价单最大下单量
	TJGtdcBuyBailRatio BuyBailRatio;				///< 多头保证金比例
	TJGtdcSellBailRatio SellBailRatio;				///< 空头保证金比例

	CJGtdcFutureRspQryContract()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryContract));
	}
};

///< 投资者期货委托下单
struct CJGtdcFutureReqEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;	        ///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;		    ///< 合约代码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcFutureReqEntrust()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqEntrust));
	}
};

///< 投资者期货委托下单应答
struct CJGtdcFutureRspEntrust
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcFutureRspEntrust()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspEntrust));
	}
};

///< 投资者期货委托撤单
struct CJGtdcFutureReqCancel
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量

	CJGtdcFutureReqCancel()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqCancel));
	}
};

///< 投资者期货委托撤单应答
struct CJGtdcFutureRspCancel
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcNewEntrustNoType NewEntrustNo;			///< 新合同号
	TJGtdcBatchNoType BatchNo;						///< 批号

	CJGtdcFutureRspCancel()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspCancel));
	}
};

///< 投资者期货最大交易数量查询
struct CJGtdcFutureReqQryMax
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcFutureReqQryMax()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryMax));
	}
};

///< 投资者期货最大交易数量查询应答
struct CJGtdcFutureRspQryMax
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcMaxAmount MaxAmount;						///< 最大数量
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcFutureRspQryMax()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryMax));
	}
};

///< 投资者期货交易编码查询
struct CJGtdcFutureReqQryHolder
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型

	CJGtdcFutureReqQryHolder()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryHolder));
	}
};

///< 投资者期货交易编码查询应答
struct CJGtdcFutureRspQryHolder
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcHolderNameType HolderName;				///< 股东姓名
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcHolderStatus HolderStatus;				///< 股东状态
	TJGtdcMainFlag MainFlag;						///< 主副标志

	CJGtdcFutureRspQryHolder()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryHolder));
	}
};

///< 投资者期货资金查询
struct CJGtdcFutureReqQryFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcFutureReqQryFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryFund));
	}
};

///< 投资者期货资金查询应答
struct CJGtdcFutureRspQryFund
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcMainFlag MainFlag;						///< @主副标志
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	TJGtdcFrozenBalance FrozenBalance;				///< 冻结金额
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcStaticRightsBalance StaticRightsBalance;	///< 静态权益
	TJGtdcDynamicRightsBalance DynamicRightsBalance;///< 动态权益
	TJGtdcPossessBail PossessBail;					///< 占用保证金
	TJGtdcHoldIncome HoldIncome;					///< 持仓盈亏
	TJGtdcPayoffIncome PayoffIncome;				///< 平仓盈亏

	CJGtdcFutureRspQryFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryFund));
	}
};

///< 投资者期货持仓查询
struct CJGtdcFutureReqQryHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcFutureReqQryHold()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryHold));
	}
};

///< 投资者期货持仓查询应答
struct CJGtdcFutureRspQryHold
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcYdAmount YdAmount;						///< 昨日持仓量
	TJGtdcTodayAmount TodayAmount;					///< 今日持仓量
	TJGtdcEnableAmount EnableAmount;				///< 可卖数量
	TJGtdcFrozenAmount FrozenAmount;				///< 冻结数量
	TJGtdcOpenAmount OpenAmount;					///< 开仓数量
	TJGtdcPayoffAmount PayoffAmount;				///< 平仓数量
	TJGtdcHoldIncome HoldIncome;					///< 持仓盈亏
	TJGtdcPayoffIncome PayoffIncome;				///< 平仓盈亏
	TJGtdcHoldCost HoldCost;						///< 持仓成本
	TJGtdcPossessBail PossessBail;					///< 占用保证金

	CJGtdcFutureRspQryHold()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryHold));
	}
};

///< 投资者期货当日委托查询
struct CJGtdcFutureReqQryEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcFutureReqQryEntrust()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryEntrust));
	}
};

///< 投资者期货当日委托查询应答
struct CJGtdcFutureRspQryEntrust
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcRemarksInfoType RemarksInfo;				///< 备注信息
	TJGtdcSurplusAmount SurplusAmount;				///< 剩余数量

	CJGtdcFutureRspQryEntrust()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryEntrust));
	}
};

///< 投资者期货可撤单查询
struct CJGtdcFutureReqQryRevocEnt
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcFutureReqQryRevocEnt()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryRevocEnt));
	}
};

///< 投资者期货可撤单查询应答
struct CJGtdcFutureRspQryRevocEnt
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额

	CJGtdcFutureRspQryRevocEnt()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryRevocEnt));
	}
};

///< 投资者期货增量成交查询
struct CJGtdcFutureReqQryBusByPos
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcFutureReqQryBusByPos()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryBusByPos));
	}
};

///< 投资者期货增量成交查询应答
struct CJGtdcFutureRspQryBusByPos
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcFutureAccountType FutureAccount;			///< 交易编码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcBusinessNoType BusinessNo;				///< 成交编号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcBusinessStatus BusinessStatus;			///< 成交状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcHedgeType HedgeType;						///< 套保类型
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate BusinessDate;						///< 成交日期
	TJGtdcTime BusinessTime;						///< 成交时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额

	CJGtdcFutureRspQryBusByPos()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryBusByPos));
	}
};

//投资者期货银行账号查询请求
struct CJGtdcFutureReqQryBankAccount
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码

	CJGtdcFutureReqQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryBankAccount));
	}
};

//投资者期货银行账号查询应答
struct CJGtdcFutureRspQryBankAccount
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcBankAccount BankAccount;				    ///< 银行账户
	TJGtdcBankFlag BankFlag;						///< 银行标识
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcConvertOption SecToBank_ConvertOption;	///< 证转银@转账选项
	TJGtdcConvertOption BankToSec_ConvertOption;	///< 银转证@转账选项
	TJGtdcExchangeType ExchangeType;                ///< 市场类型

	CJGtdcFutureRspQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryBankAccount));
	}
};


///投资者期货银衍转账
struct CJGtdcFutureReqBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankPassword BankPassword;				///< 银行密码
	TJGtdcFundPassword FundPassword;				///< 资金密码
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcFutureReqBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqBankTrans));
	}
};

///投资者期货银衍转账应答
struct CJGtdcFutureRspBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 转账流水委托号
	TJGtdcEntrustNoType MoneyEntrustNo;				///< 资金流水委托号
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcFutureRspBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspBankTrans));
	}
};

///投资者期货银衍转账查询
struct CJGtdcFutureReqQryBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcDate nStartDate;							///< 起始日期
	TJGtdcDate nEndDate;							///< 结束日期

	CJGtdcFutureReqQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryBankTrans));
	}
};

///投资者期货银衍转账查询应答
struct CJGtdcFutureRspQryBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName	BankName;						///< 银行名称
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcEntrustNoType EntrustNo;					///< 委托号
	TJGtdcOpConfigInfo OpConfigInfo;				///< 操作确认信息
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcDate OperDate;							///< 操作日期
	TJGtdcTime OperTime;							///< 操作时间
	TJGtdcOpRetCode  OpRetCode;						///< 操作返回代码
	TJGtdcOperBalance OperBalance;					///< 操作金额



	CJGtdcFutureRspQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryBankTrans));
	}
};

//投资者期货银衍转账可转资金请求
struct CJGtdcFutureReqQryBankMaxTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号

	CJGtdcFutureReqQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryBankMaxTrans));
	}
};

//股票银衍转账可转资金应答
struct CJGtdcFutureRspQryBankMaxTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	CJGtdcFutureRspQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryBankMaxTrans));
	}
};

//投资者期货查询子账户及其资金请求
struct CJGtdcFutureReqQryChildBankFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	CJGtdcFutureReqQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqQryChildBankFund));
	}
};

//投资者期货查询子账户及其资金应答
struct CJGtdcFutureRspQryChildBankFund
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	CJGtdcFutureRspQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspQryChildBankFund));
	}
};


//投资者期货同名账户资金内转请求
struct CJGtdcFutureReqInTransferFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcTransBalance TransBalance;				///< 内转金额
	CJGtdcFutureReqInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureReqInTransferFund));
	}
};


//投资者期货同名账户资金内转应答
struct CJGtdcFutureRspInTransferFund
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcEntrustNoType InTransNo;					///< 转入流水号
	TJGtdcEntrustNoType OutTransNo;					///< 转出流水号

	CJGtdcFutureRspInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcFutureRspInTransferFund));
	}
};


///< 投资者期权合约查询
struct CJGtdcOptionReqQryContract
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcOptionType OptionType;					///< 期权类别
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryContract()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryContract));
	}
};

///< 投资者期权合约查询应答
struct CJGtdcOptionRspQryContract
{
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcOptionType OptionType;				    ///< 期权类别
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcStockType StockType;						///< 证券类别
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcAmountMultiple AmountMultiple;			///< 合约乘数
	TJGtdcOptionVersion OptionVersion;				///< 期权版本
	TJGtdcDate TradeBeginDate;						///< 交易开始日期
	TJGtdcDate TradeEndDate;						///< 交易结束日期
	TJGtdcDate ExerciseBeginDate;					///< 行权开始日期
	TJGtdcDate ExerciseEndDate;						///< 行权结束日期
	TJGtdcOptionPreClosePrice OptionPreClosePrice;	///< 期权前收盘价格
	TJGtdcStockPreClosePrice StockPreClosePrice;	///< 证券前收盘价格
	TJGtdcOptionUpPrice OptionUpPrice;				///< 期权涨停价格
	TJGtdcOptionDownPrice OptionDownPrice;			///< 期权跌停价格
	TJGtdcExercisePrice ExercisePrice;				///< 行权价格
	TJGtdcUnitBail UnitBail;						///< 单位保证金
	TJGtdcMaxMarketEntrustAmount MaxMarketEntrustAmount;		///< 市价单最大下单量
	TJGtdcMinMarketEntrustAmount MinMarketEntrustAmount;		///< 市价单最小下单量
	TJGtdcMaxLimitEntrustAmount MaxLimitEntrustAmount;			///< 限价单最大下单量
	TJGtdcMinLimitEntrustAmount MinLimitEntrustAmount;			///< 限价单最小下单量
	TJGtdcOptionStatus OptionStatus;				///< 期权状态
	TJGtdcOptionMode OptionMode;					///< 期权模式
	TJGtdcOpenType OpenType;						///< 开仓标识
	TJGtdcSuspendedType SuspendedType;				///< 停牌标识
	TJGtdcExpireType ExpireType;					///< 到期日标识
	TJGtdcAdjustType AdjustType;					///< 调整标识

	CJGtdcOptionRspQryContract()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryContract));
	}
};

///< 投资者期权委托下单
struct CJGtdcOptionReqEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcOptionReqEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqEntrust));
	}
};

///< 投资者期权委托下单应答
struct CJGtdcOptionRspEntrust
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcOptionRspEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspEntrust));
	}
};

///< 投资者期权委托撤单
struct CJGtdcOptionReqCancel
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量

	CJGtdcOptionReqCancel()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqCancel));
	}
};

///< 投资者期权委托撤单应答
struct CJGtdcOptionRspCancel
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcNewEntrustNoType NewEntrustNo;			///< 新合同号
	TJGtdcBatchNoType BatchNo;						///< 批号

	CJGtdcOptionRspCancel()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspCancel));
	}
};

///< 投资者期权最大交易数量查询
struct CJGtdcOptionReqQryMax
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcOptionReqQryMax()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryMax));
	}
};

///< 投资者期权最大交易数量查询应答
struct CJGtdcOptionRspQryMax
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcMaxAmount MaxAmount;						///< 最大数量
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格

	CJGtdcOptionRspQryMax()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryMax));
	}
};

///< 投资者期权备兑证券划转
struct CJGtdcOptionReqCoveredTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码
	TJGtdcOtherSeatNoType OtherSeatNo;				///< 对方席位号

	CJGtdcOptionReqCoveredTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqCoveredTrans));
	}
};

///< 投资者期权备兑证券划转应答
struct CJGtdcOptionRspCoveredTrans
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码

	CJGtdcOptionRspCoveredTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspCoveredTrans));
	}
};

///< 投资者期权备兑可划转数量查询
struct CJGtdcOptionReqQryCoveredMax
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码
	TJGtdcOtherSeatNoType OtherSeatNo;				///< 对方席位号

	CJGtdcOptionReqQryCoveredMax()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryCoveredMax));
	}
};

///< 投资者期权备兑可划转数量查询应答
struct CJGtdcOptionRspQryCoveredMax
{
	TJGtdcResultType ResultType;				    ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;					///< 错误信息
	TJGtdcMaxAmount MaxAmount;						///< 最大数量
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOtherFundAccountType OtherFundAccount;	///< 对方资金账号
	TJGtdcOtherStockAccountType OtherStockAccount;	///< 对方股东代码

	CJGtdcOptionRspQryCoveredMax()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryCoveredMax));
	}
};

///< 投资者期权资金查询
struct CJGtdcOptionReqQryFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcOptionReqQryFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryFund));
	}
};

///< 投资者期权资金查询应答
struct CJGtdcOptionRspQryFund
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	TJGtdcFrozenBalance FrozenBalance;				///< 冻结金额
	TJGtdcStockBalance StockBalance;				///< 证券市值
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcAssetBalance AssetBalance;				///< 资产总值
	TJGtdcIncome Income;							///< 总盈亏
	TJGtdcEnableBail EnableBail;					///< 可用保证金
	TJGtdcUsedBail UsedBail;						///< 已用保证金
	TJGtdcAgreeAssureRatio AgreeAssureRatio;	    ///< 履约担保比例
	TJGtdcRiskRatio RiskRatio;					    ///< 风险度
	TJGtdcRiskRatio1 RiskRatio1;				    ///< 风险度1

	CJGtdcOptionRspQryFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryFund));
	}
};

///< 投资者期权持仓查询
struct CJGtdcOptionReqQryHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryHold));
	}
};

///< 投资者期权持仓查询应答
struct CJGtdcOptionRspQryHold
{
	TJGtdcBranchNoType BranchNo;		            ///< 营业部号
	TJGtdcClientIDType ClientID;		            ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;		    ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOptionType OptionType;					///< 期权类别
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcOptionYDAmount OptionYDAmount;			///< 期权昨日余额
	TJGtdcOptionAmount OptionAmount;				///< 期权余额
	TJGtdcEnableAmount EnableAmount;				///< 可卖数量
	TJGtdcPossessAmount PossessAmount;				///< 当前拥股数量
	TJGtdcFrozenAmount FrozenAmount;				///< 冻结数量
	TJGtdcUnFrozenAmount UnFrozenAmount;			///< 解冻数量
	TJGtdcTransitAmount TransitAmount;				///< 在途数量
	TJGtdcTodayOpenAmount TodayOpenAmount;			///< 今日开仓量
	TJGtdcTodayPayoffAmount TodayPayoffAmount;		///< 今日平仓量
	TJGtdcPremiumBalance PremiumBalance;			///< 权利金
	TJGtdcBailBalance BailBalance;					///< 保证金
	TJGtdcCostPrice CostPrice;						///< 成本价格
	TJGtdcBuyCost BuyCost;						    ///< 当前成本
	TJGtdcOptionBalance OptionBalance;				///< 期权市值
	TJGtdcHoldIncome HoldIncome;					///< 持仓盈亏
	TJGtdcPayoffIncome PayoffIncome;				///< 平仓盈亏

	CJGtdcOptionRspQryHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryHold));
	}
};

///< 投资者期权委托查询
struct CJGtdcOptionReqQryEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryEntrust));
	}
};

///< 投资者期权委托查询应答
struct CJGtdcOptionRspQryEntrust
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcInvalidReason InvalidReason;				///< 废单原因

	CJGtdcOptionRspQryEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryEntrust));
	}
};

///< 投资者期权可撤单查询
struct CJGtdcOptionReqQryRevocEnt
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryRevocEnt()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryRevocEnt));
	}
};

///< 投资者期权可撤单查询应答
struct CJGtdcOptionRspQryRevocEnt
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcInvalidReason InvalidReason;				///< 废单原因

	CJGtdcOptionRspQryRevocEnt()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryRevocEnt));
	}
};

///< 投资者期权增量成交查询
struct CJGtdcOptionReqQryBusByPos
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryBusByPos()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBusByPos));
	}
};

///< 投资者期权增量成交查询应答
struct CJGtdcOptionRspQryBusByPos
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;			///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcBusinessNoType BusinessNo;				///< 成交号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcBusinessStatus BusinessStatus;			///< 成交状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate BusinessDate;						///< 成交日期
	TJGtdcTime BusinessTime;						///< 成交时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额

	CJGtdcOptionRspQryBusByPos()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBusByPos));
	}
};

///< 投资者期权备兑持仓查询
struct CJGtdcOptionReqQryCoveredHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryCoveredHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryCoveredHold));
	}
};

///< 投资者期权备兑持仓查询应答
struct CJGtdcOptionRspQryCoveredHold
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcStockAmount StockAmount;					///< 股份余额
	TJGtdcEnableAmount EnableAmount;				///< 可卖数量

	CJGtdcOptionRspQryCoveredHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryCoveredHold));
	}
};

///< 投资者期权行权指派查询
struct CJGtdcOptionReqQryExerciseAssign
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryExerciseAssign()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryExerciseAssign));
	}
};

///< 投资者期权行权指派查询应答
struct CJGtdcOptionRspQryExerciseAssign
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOptionType OptionType;					///< 期权类别
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcDate ExerciseBeginDate;					///< 行权开始日期
	TJGtdcExerciseAmount ExerciseAmount;			///< 行权数量
	TJGtdcExercisePrice ExercisePrice;				///< 行权价格
	TJGtdcSettleAmount SettleAmount;				///< 交收数量
	TJGtdcSettleBalance SettleBalance;				///< 结算金额
	TJGtdcFrozenBalance FrozenBalance;				///< 冻结金额
	TJGtdcNeedAmount NeedAmount;					///< 不足数量
	TJGtdcNeedBalance dNeedBalance;					///< 不足金额

	CJGtdcOptionRspQryExerciseAssign()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryExerciseAssign));
	}
};

///< 投资者期权备兑持仓不足查询
struct CJGtdcOptionReqQryLackCoveredStock
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryLackCoveredStock()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryLackCoveredStock));
	}
};

///< 投资者期权备兑持仓不足查询应答
struct CJGtdcOptionRspQryLackCoveredStock
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcCoveredLockAmount CoveredLockAmount;		///< 备兑锁定数量
	TJGtdcCoveredLackAmount CoveredLackAmount;		///< 备兑不足数量
	TJGtdcCoveredPreLackAmount CoveredPreLackAmount;///< 备兑预估不足数量

	CJGtdcOptionRspQryLackCoveredStock()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryLackCoveredStock));
	}
};

///< 投资者期权可取资金查询
struct CJGtdcOptionReqQryFetchFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcOptionReqQryFetchFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryFetchFund));
	}
};

///< 投资者期权可取资金查询应答
struct CJGtdcOptionRspQryFetchFund
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcFetchBalance FetchBalance;				///< 可取余额

	CJGtdcOptionRspQryFetchFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryFetchFund));
	}
};

///< 投资者期权历史委托查询
struct CJGtdcOptionReqQryHisEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryHisEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryHisEntrust));
	}
};

///< 投资者期权历史委托查询应答
struct CJGtdcOptionRspQryHisEntrust
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcInvalidReason InvalidReason;				///< 废单原因

	CJGtdcOptionRspQryHisEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryHisEntrust));
	}
};

///< 投资者期权历史成交查询
struct CJGtdcOptionReqQryHisBusiness
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryHisBusiness()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryHisBusiness));
	}
};

///< 投资者期权历史成交查询应答
struct CJGtdcOptionRspQryHisBusiness
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcBusinessNoType BusinessNo;				///< 成交号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcBusinessStatus BusinessStatus;			///< 成交状态
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDate BusinessDate;						///< 成交日期
	TJGtdcTime BusinessTime;						///< 成交时间
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcCancelVolume CancelAmount;				///< 撤销数量
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额

	CJGtdcOptionRspQryHisBusiness()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryHisBusiness));
	}
};

///< 投资者期权历史行权指派查询
struct CJGtdcOptionReqQryHisExerciseAssign
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryHisExerciseAssign()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryHisExerciseAssign));
	}
};

///< 投资者期权历史行权指派查询应答
struct CJGtdcOptionRspQryHisExerciseAssign
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOptionType OptionType;					///< 期权类别
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcDate ExerciseBeginDate;				    ///< 行权开始日期
	TJGtdcExerciseAmount ExerciseAmount;			///< 行权数量
	TJGtdcExercisePrice ExercisePrice;				///< 行权价格
	TJGtdcSettleAmount SettleAmount;				///< 交收数量
	TJGtdcSettleBalance SettleBalance;				///< 结算金额
	TJGtdcFrozenBalance FrozenBalance;				///< 冻结金额
	TJGtdcNeedAmount NeedAmount;					///< 不足数量
	TJGtdcNeedBalance NeedBalance;					///< 不足金额

	CJGtdcOptionRspQryHisExerciseAssign()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryHisExerciseAssign));
	}
};

///< 投资者期权银行权限查询
struct CJGtdcOptionReqQryBankRights
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;						///< 查询模式
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcBankCodeType BankCode;					///< 银行代码

	CJGtdcOptionReqQryBankRights()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBankRights));
	}
};

///< 投资者期权银行权限查询应答
struct CJGtdcOptionRspQryBankRights
{
	TJGtdcBankCodeType BankCode;					///< 银行代码
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcBankRights BankRights;					///< 银行权限

	CJGtdcOptionRspQryBankRights()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBankRights));
	}
};

///< 投资者期权银行参数查询
struct CJGtdcOptionReqQryBankArg
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcBankCodeType BankCode;					///< 银行代码

	CJGtdcOptionReqQryBankArg()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBankArg));
	}
};

///< 投资者期权银行参数查询应答
struct CJGtdcOptionRspQryBankArg
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcBankCodeType BankCode;					///< 银行代码
	TJGtdcBankNameType BankName;					///< 银行名称
	TJGtdcCheckPasswordFlag CheckPasswordFlag;		///< 校验密码标志

	CJGtdcOptionRspQryBankArg()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBankArg));
	}
};

///< 投资者期权增加自动行权
struct CJGtdcOptionReqAddAutoExercise
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量

	CJGtdcOptionReqAddAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqAddAutoExercise));
	}
};

///< 投资者期权增加自动行权应答
struct CJGtdcOptionRspAddAutoExercise
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量

	CJGtdcOptionRspAddAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspAddAutoExercise));
	}
};

///< 投资者期权修改自动行权
struct CJGtdcOptionReqModAutoExercise
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量

	CJGtdcOptionReqModAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqModAutoExercise));
	}
};

///< 投资者期权修改自动行权应答
struct CJGtdcOptionRspModAutoExercise
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量

	CJGtdcOptionRspModAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspModAutoExercise));
	}
};

///< 投资者期权删除自动行权
struct CJGtdcOptionReqDelAutoExercise
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量

	CJGtdcOptionReqDelAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqDelAutoExercise));
	}
};

///< 投资者期权删除自动行权应答
struct CJGtdcOptionRspDelAutoExercise
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcBatchNoType BatchNo;						///< 批号

	CJGtdcOptionRspDelAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspDelAutoExercise));
	}
};

///< 投资者期权自动行权查询
struct CJGtdcOptionReqQryAutoExercise
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcQueryDirection QueryDirection;            ///< 查询方向
	TJGtdcQueryAmount QueryAmount;                  ///< 查询数量
	TJGtdcPositionStrType PositionStr;              ///< 定位串 

	CJGtdcOptionReqQryAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryAutoExercise));
	}
};

///< 投资者期权自动行权查询应答
struct CJGtdcOptionRspQryAutoExercise
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;            ///< 股东代码
	TJGtdcSeatNoType SeatNo;                        ///< 席位号
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcContractCodeType ContractCode;	        ///< 合约代码
	TJGtdcContractNameType ContractName;	        ///< 合约名称
	TJGtdcPositionStrType PositionStr;              ///< 定位串
	TJGtdcEntrustNoType EntrustNo;                  ///< 合同号
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcExerciseStrategyType ExerciseStrategyType;///< 行权策略类型
	TJGtdcExerciseStrategyValue ExerciseStrategyValue;///< 行权策略值
	TJGtdcAgreeAmount AgreeAmount;					///< 协议数量
	TJGtdcDate ExerciseDate;						///< 行权日期

	CJGtdcOptionRspQryAutoExercise()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryAutoExercise));
	}
};

///< 投资者期权备兑可划转查询
struct CJGtdcOptionReqQryCovered
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;			        ///< 证券代码

	CJGtdcOptionReqQryCovered()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryCovered));
	}
};

///< 投资者期权备兑可划转查询应答
struct CJGtdcOptionRspQryCovered
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStockCodeType StockCode;                  ///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdciAmount Amount;							///< 数量/可用数量

	CJGtdcOptionRspQryCovered()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryCovered));
	}
};

///< 投资者期权昨日持仓查询
struct CJGtdcOptionReqQryHisHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryHisHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryHisHold));
	}
};

///< 投资者期权昨日持仓查询应答
struct CJGtdcOptionRspQryHisHold
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcPositionStrType PositionStr;		        ///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOptionType OptionType;					///< 期权类别
	TJGtdcOptionHoldType OptionHoldType;			///< 期权持仓类别
	TJGtdcOptionAmount OptionAmount;				///< 期权余额
	TJGtdcEnableAmount EnableAmount;				///< 可卖数量
	TJGtdcTodayOpenAmount TodayOpenAmount;			///< 今日开仓量
	TJGtdcTodayPayoffAmount TodayPayoffAmount;		///< 今日平仓量
	TJGtdcPremiumBalance PremiumBalance;			///< 权利金
	TJGtdcBailBalance BailBalance;					///< 保证金
	TJGtdcCostPrice CostPrice;						///< 成本价格
	TJGtdcBuyCost BuyCost;							///< 当前成本
	TJGtdcOptionBalance OptionBalance;				///< 期权市值
	TJGtdcHoldIncome HoldIncome;					///< 持仓盈亏

	CJGtdcOptionRspQryHisHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryHisHold));
	}
};

///< 投资者期权结算单查询
struct CJGtdcOptionReqQrySettlement
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcSettlementMode SettlementMode;			///< 帐单模式
	TJGtdcDate DateOrMonth;							///< 日期月份
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcOptionReqQrySettlement()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQrySettlement));
	}
};

///< 投资者期权结算单查询应答1
struct CJGtdcOptionRspQrySettlementTxt
{
	TJGtdcSettleInfoUseLen SettleInfoUseLen;		///< 账单信息使用长度
	TJGtdcSettleInfo SettleInfo;					///< 账单信息

	CJGtdcOptionRspQrySettlementTxt()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQrySettlementTxt));
	}
};

///< 投资者期权结算单查询应答2
struct CJGtdcOptionRspQrySettlementStruct
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcDigestType DigestType;					///< 业务类型
	TJGtdcDigestName DigestName;					///< 业务名称
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcBankCodeType BankCode;					///< 银行代码
	TJGtdcBankNameType BankName;					///< 银行名称
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;				///< 定位串
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcDate OccurDate;							///< 发生日期
	TJGtdcTime OccurTime;							///< 发生时间[HHMMSSmmm]
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcClearBalance ClearBalance;				///< 清算金额
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcStandardFare0 StandardFare0;				///< 标准佣金
	TJGtdcFeeStamp FeeStamp;						///< 印花税
	TJGtdcFeeCommission FeeCommission;				///< 佣金
	TJGtdcFeeTransfer FeeTransfer;					///< 过户费
	TJGtdcFeeOther FeeOther;						///< 其它费用
	TJGtdcFare3 Fare3;							    ///< 费用3
	TJGtdcFareX FareX;								///< 费用x
	TJGtdcExchange_AllFee Exchange_AllFee;			///< 一级总费用
	TJGtdcExchange_Fee0 Exchange_Fee0;				///< 一级经手费
	TJGtdcExchange_Stamp Exchange_Stamp;			///< 一级印花税
	TJGtdcExchange_Transfer Exchange_Transfer;		///< 一级过户费
	TJGtdcExchange_SEC Exchange_SEC;				///< 一级证管费
	TJGtdcExchange_Fee Exchange_Fee;				///< 一级手续费
	TJGtdcExchange_FareX Exchange_FareX;			///< 风险金
	TJGtdcInnerORG InnerORG;						///< 内部机构
	TJGtdcClientNameType ClientName;				///< 客户姓名
	TJGtdcFundPreBLN FundPreBLN;					///< 期初结存
	TJGtdcFundBLN FundBLN;							///< 期末结存
	TJGtdcFundAvl FundAvl;							///< 可用资金
	TJGtdcFundExeFRZ FundExeFRZ;					///< 行权资金冻结金额
	TJGtdcFundExeMargin FundExeMargin;				///< 行权冻结维持保证金
	TJGtdcPossessBail FundUsedMargin;				///< 占用保证金
	TJGtdcPaylater Paylater;						///< 垫付资金
	TJGtdcExpectPnint ExpectPnint;					///< 预计垫资罚息
	TJGtdcRepayPaylater RepayPaylater;				///< 归还垫资
	TJGtdcRepayPnint RepayPnint;					///< 归还罚息
	TJGtdcRemitPnint RemitPnint;					///< 减免罚息
	TJGtdcInterstIncome InterstIncome;				///< 利息归本
	TJGtdcInterstIncomeTax InterstIncomeTax;		///< 利息税
	TJGtdcInAmt InAmt;								///< 银衍入金
	TJGtdcOutAmt OutAmt;							///< 银衍出金
	TJGtdcPremiumPay PremiumPay;					///< 权利金收付
	TJGtdcExercisePay ExercisePay;					///< 行权收付
	TJGtdcClearingFee ClearingFee;					///< 结算费
	TJGtdcExchangeFee ExchangeFee;					///< 交易所经手费
	TJGtdcExerciseClearingFee ExerciseClearingFee;	///< 行权结算费
	TJGtdcExerciseFee ExerciseFee;					///< 行权手续费
	TJGtdcFloatIncome FloatProfit;					///< 浮动盈亏
	TJGtdcQuotaValUsed QuotaValUsed;				///< 占用买入额度
	TJGtdcQuotaVal QuotaVal;						///< 买入额度
	TJGtdcRightMktVal RightMktVal;					///< 权利仓市值
	TJGtdcDuteMktVal DuteMktVal;					///< 义务仓市值
	TJGtdcMarginRiskRate MarginRiskRate;			///< 保证金风险率
	TJGtdcAddMarginAmt AddMarginAmt;				///< 应追加保证金
	TJGtdcRemarksInfoType AddMarginNotice;			///< 备注信息
	TJGtdcConfirmFlag ConfirmFlag;					///< 客户确认标志
	TJGtdcTime ConfirmTime;							///< 账单确认时间

	CJGtdcOptionRspQrySettlementStruct()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQrySettlementStruct));
	}
};

///< 投资者期权结算单查询应答
struct CJGtdcOptionRspQrySettlement
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcDate DateOrMonth;							///< 日期月份
	TJGtdcSettlementType SettlementType;			///< 帐单类型
	CJGtdcOptionRspQrySettlementTxt InfoTxt;        ///< 结算单文本类型
	CJGtdcOptionRspQrySettlementStruct InfoStruct;  ///< 结算单结构体类型

	CJGtdcOptionRspQrySettlement()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQrySettlement));
	}
};

///< 投资者期权交割单查询
struct CJGtdcOptionReqQryDelivery
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcQueryAmount QueryAmount;					///< 查询数量
	TJGtdcPositionStrType PositionStr;				///< 定位串

	CJGtdcOptionReqQryDelivery()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryDelivery));
	}
};

///< 投资者期权交割单查询应答
struct CJGtdcOptionRspQryDelivery
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcContractNumber ContractNumber;	        ///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;		        ///< 定位串
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcReportNoType ReportNo;					///< 申报号
	TJGtdcBusinessNoType BusinessNo;				///< 成交号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcTradeType TradeType;						///< 交易类型
	TJGtdcOffsetType OffsetType;					///< 开平仓类型
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcPriceType PriceType;						///< 价格类型
	TJGtdcDigestType DigestType;					///< 业务类型
	TJGtdcDigestName DigestName;					///< 业务名称
	TJGtdcDate BusinessDate;						///< 成交日期
	TJGtdcTime BusinessTime;						///< 成交时间
	TJGtdcOccurAmount OccurAmount;					///< 发生数量
	TJGtdcOrderVolume EntrustAmount;				///< 委托数量
	TJGtdcOrderPrice EntrustPrice;					///< 委托价格
	TJGtdcBuinessVolume BusinessAmount;				///< 成交数量
	TJGtdcBusinessPrice BusinessPrice;				///< 成交价格
	TJGtdcBusinessBalance BusinessBalance;			///< 成交金额
	TJGtdcOccurBalance OccurBalance;				///< 发生金额
	TJGtdcBusinessCount BusinessCount;				///< 成交笔数
	TJGtdcClearBalance ClearBalance;				///< 清算金额
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcStockAmount StockAmount;					///< 股份余额
	TJGtdcFeeStamp FeeStamp;						///< 印花税
	TJGtdcFeeCommission FeeCommission;				///< 佣金
	TJGtdcFeeTransfer FeeTransfer;					///< 过户费
	TJGtdcFare3 Fare3;								///< 费用3
	TJGtdcFareX FareX;								///< 费用x
	TJGtdcFeeOther FeeOther;						///< 其它费用
	TJGtdcRemark Remark;							///< 备注字段

	CJGtdcOptionRspQryDelivery()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryDelivery));
	}
};

///< 投资者期权调拨资金
struct CJGtdcOptionReqTransferFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcTransDirection TransDirection;			///< 调拨方向
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcOccurBalance OccurBalance;				///< 发生金额

	CJGtdcOptionReqTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqTransferFund));
	}
};

///< 投资者期权调拨资金应答
struct CJGtdcOptionRspTransferFund
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息

	CJGtdcOptionRspTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspTransferFund));
	}
};

///< 投资者期权个股组合拆分委托
struct CJGtdcOptionReqShareCombSplitEntrust
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStrategyCode StrategyCode;				///< 策略代码
	TJGtdcContractNumber ContractNumber1;			///< 合约编码1
	TJGtdcContractNumber ContractNumber2;			///< 合约编码2
	TJGtdcContractNumber ContractNumber3;			///< 合约编码3
	TJGtdcContractNumber ContractNumber4;			///< 合约编码4
	TJGtdcCombSplitTag CombSplitTag;				///< 组合拆分标记
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcEntrustLots EntrustLots;					///< 委托手数
	TJGtdcEntrustType EntrustType;					///< 委托类型
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcInterceptionTag InterceptionTag;			///< 强拆标记
	TJGtdcBSTag BSTag1;								///< 买卖标记1
	TJGtdcBSTag BSTag2;								///< 买卖标记2
	TJGtdcBSTag BSTag3;								///< 买卖标记3
	TJGtdcBSTag BSTag4;								///< 买卖标记4
	TJGtdcExchangeCombID ExchangeCombID;			///< 交易所组合编号

	CJGtdcOptionReqShareCombSplitEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqShareCombSplitEntrust));
	}
};

///< 投资者期权个股组合拆分委托应答
struct CJGtdcOptionRspShareCombSplitEntrust
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBatchNoType BatchNo;                      ///< 批号
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcEntrustNoType EntrustNo;					///< 合同号
	TJGtdcStrategyCode StrategyCode;				///< 策略代码
	TJGtdcFullContractCode FullContractCode;		///< 完整合约代码
	TJGtdcCombSplitTag CombSplitTag;				///< 组合拆分标记
	TJGtdcBSTag BSTag;								///< 买卖标记
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdciAmount Amount;							///< 个数/合约个数
	TJGtdcContractNumber ContractNumber1;			///< 合约编码1
	TJGtdcContractNumber ContractNumber2;			///< 合约编码2
	TJGtdcContractNumber ContractNumber3;			///< 合约编码3
	TJGtdcContractNumber ContractNumber4;			///< 合约编码4
	TJGtdcEntrustLots EntrustLots;					///< 委托手数
	TJGtdcEntrustType EntrustType;					///< 委托类型
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcInterceptionTag InterceptionTag;			///< 强拆标记
	TJGtdcEntrustStatus EntrustStatus;				///< 委托状态
	TJGtdcDate EntrustDate;							///< 委托日期
	TJGtdcTime EntrustTime;							///< 委托时间
	TJGtdcFrozenBail FrozenBail;					///< 冻结保证金
	TJGtdcFrozenFee FrozenFee;						///< 冻结手续费
	TJGtdcBSTag BSTag1;								///< 买卖标记1
	TJGtdcBSTag BSTag2;								///< 买卖标记2
	TJGtdcBSTag BSTag3;								///< 买卖标记3
	TJGtdcBSTag BSTag4;								///< 买卖标记4
	TJGtdcTime ReportTime;							///< 申报时间[HHMMSSmmm]
	TJGtdcTime CancelTime;							///< 撤单时间[HHMMSSmmm]
	TJGtdcCancelCustomer CancelCustomer;			///< 撤单用户
	TJGtdcExchangeCombID ExchangeCombID;			///< 交易所组合编号

	CJGtdcOptionRspShareCombSplitEntrust()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspShareCombSplitEntrust));
	}
};

///< 投资者期权个股组合持仓明细查询
struct CJGtdcOptionReqQryShareCombSplitHold
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcQueryDirection QueryDirection;			///< 查询方向
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcExchangeCombID ExchangeCombID;			///< 交易所组合编号

	CJGtdcOptionReqQryShareCombSplitHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryShareCombSplitHold));
	}
};

///< 投资者期权个股组合持仓明细查询应答
struct CJGtdcOptionRspQryShareCombSplitHold
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcExchangeCombID ExchangeCombID;			///< 交易所组合编号
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStrategyCode StrategyCode;				///< 策略代码
	TJGtdcContractNumber ContractNumber1;			///< 合约编码1
	TJGtdcContractNumber ContractNumber2;			///< 合约编码2
	TJGtdcContractNumber ContractNumber3;			///< 合约编码3
	TJGtdcContractNumber ContractNumber4;			///< 合约编码4
	TJGtdcBailBalance BailBalance;					///< 保证金
	TJGtdcDistanceAutoSplitDates DistanceAutoSplitDates;///< 距离自动拆分天数
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcCombAmount CombAmount;					///< 当前组合持仓量
	TJGtdcBSTag BSTag1;								///< 买卖标记1
	TJGtdcBSTag BSTag2;								///< 买卖标记2
	TJGtdcBSTag BSTag3;								///< 买卖标记3
	TJGtdcBSTag BSTag4;								///< 买卖标记4
	TJGtdcBSComb BSComb;							///< 组合买卖方向
	TJGtdcCombAmount CombAmount1;					///< 组合持仓量1
	TJGtdcCombAmount CombAmount2;					///< 组合持仓量2
	TJGtdcCombAmount CombAmount3;					///< 组合持仓量3
	TJGtdcCombAmount CombAmount4;					///< 组合持仓量4

	CJGtdcOptionRspQryShareCombSplitHold()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryShareCombSplitHold));
	}
};

///< 投资者期权个股可组合可拆分手数查询
struct CJGtdcOptionReqQryShareCombSplitLots
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcStrategyCode StrategyCode;				///< 策略代码
	TJGtdcContractNumber ContractNumber1;			///< 合约编码1
	TJGtdcContractNumber ContractNumber2;			///< 合约编码2
	TJGtdcContractNumber ContractNumber3;			///< 合约编码3
	TJGtdcContractNumber ContractNumber4;			///< 合约编码4
	TJGtdcCombSplitTag CombSplitTag;				///< 组合拆分标记
	TJGtdcCoveredType CoveredType;					///< 备兑标识
	TJGtdcInterceptionTag InterceptionTag;			///< 强拆标记
	TJGtdcBSTag BSTag1;								///< 买卖标记1
	TJGtdcBSTag BSTag2;								///< 买卖标记2
	TJGtdcBSTag BSTag3;								///< 买卖标记3
	TJGtdcBSTag BSTag4;								///< 买卖标记4
	TJGtdcExchangeCombID ExchangeCombID;			///< 交易所组合编号

	CJGtdcOptionReqQryShareCombSplitLots()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryShareCombSplitLots));
	}
};

///< 投资者期权个股可组合可拆分手数查询应答
struct CJGtdcOptionRspQryShareCombSplitLots
{
	TJGtdcMaxCombAmount MaxCombAmount;		///< 最大组合数量
	TJGtdcMaxSplitAmount MaxSplitAmount;	///< 最大拆分数量

	CJGtdcOptionRspQryShareCombSplitLots()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryShareCombSplitLots));
	}
};

///< 投资者期权个股客户资金变动流水历史查询
struct CJGtdcOptionReqQryShareUserHisFundChange
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcDate StartDate;							///< 起始日期
	TJGtdcDate EndDate;								///< 结束日期
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcBankCodeType BankCode;					///< 银行代码
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码

	CJGtdcOptionReqQryShareUserHisFundChange()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryShareUserHisFundChange));
	}
};

///< 投资者期权个股客户资金变动流水历史查询应答
struct CJGtdcOptionRspQryShareUserHisFundChange
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcClientNameType ClientName;				///< 客户姓名
	TJGtdcFundAccountType FundAccount;	            ///< 资金账号
	TJGtdcExchangeType ExchangeType;				///< 市场类型
	TJGtdcStockAccountType StockAccount;	        ///< 股东代码
	TJGtdcSeatNoType SeatNo;						///< 席位号
	TJGtdcStockCodeType StockCode;					///< 证券代码
	TJGtdcStockNameType StockName;					///< 证券名称
	TJGtdcContractNumber ContractNumber;			///< 合约编码
	TJGtdcContractCodeType ContractCode;			///< 合约代码
	TJGtdcContractNameType ContractName;			///< 合约名称
	TJGtdcPositionStrType PositionStr;		        ///< 定位串
	TJGtdcSerialNo SerialNo;						///< 流水号
	TJGtdcMoneyType MoneyType;						///< 币种
	TJGtdcBankCodeType BankCode;					///< 银行代码
	TJGtdcBankNameType BankName;					///< 银行名称
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcDigestType DigestType;					///< 业务类型
	TJGtdcPaymentFlag PaymentFlag;					///< 收付标志
	TJGtdcDigestName DigestName;					///< 业务名称
	TJGtdcDate OccurDate;							///< 发生日期
	TJGtdcTime OccurTime;							///< 发生时间[HHMMSSmmm]
	TJGtdcOccurAmount OccurAmount;					///< 发生数量
	TJGtdcStockAmount StockAmount;					///< 股份余额
	TJGtdcOccurBalance OccurBalance;				///< 发生金额
	TJGtdcFundBalance FundBalance;					///< 资金余额
	TJGtdcOperationName OperationName;				///< 操作职工
	TJGtdcReviewName ReviewName;					///< 复核职工
	TJGtdcRemark Remark;							///< 备注字段

	CJGtdcOptionRspQryShareUserHisFundChange()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryShareUserHisFundChange));
	}
};

///< 投资者期权结算单确认
struct CJGtdcOptionReqSettlementConfrim
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcOptionReqSettlementConfrim()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqSettlementConfrim));
	}
};

///< 投资者期权结算单确认应答
struct CJGtdcOptionRspSettlementConfrim
{
	TJGtdcBranchNoType BranchNo;					///< 营业部号
	TJGtdcClientIDType ClientID;					///< 客户号
	TJGtdcFundAccountType FundAccount;				///< 资金账号
	TJGtdcMoneyType MoneyType;						///< 币种

	CJGtdcOptionRspSettlementConfrim()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspSettlementConfrim));
	}
};

//投资者期权银行账号查询请求
struct CJGtdcOptionReqQryBankAccount
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcExchangeType ExchangeType;                ///< 市场类型
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码

	CJGtdcOptionReqQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBankAccount));
	}
};

//投资者期权银行账号查询应答
struct CJGtdcOptionRspQryBankAccount
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcBankAccount BankAccount;				    ///< 银行账户
	TJGtdcBankFlag BankFlag;						///< 银行标识
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcConvertOption SecToBank_ConvertOption;	///< 证转银@转账选项
	TJGtdcConvertOption BankToSec_ConvertOption;	///< 银转证@转账选项
	TJGtdcExchangeType ExchangeType;                ///< 市场类型

	CJGtdcOptionRspQryBankAccount()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBankAccount));
	}
};


///投资者期权银衍转账
struct CJGtdcOptionReqBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankPassword BankPassword;				///< 银行密码
	TJGtdcFundPassword FundPassword;				///< 资金密码
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcOptionReqBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqBankTrans));
	}
};

///投资者期权银衍转账应答
struct CJGtdcOptionRspBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcEntrustNoType EntrustNo;					///< 转账流水委托号
	TJGtdcEntrustNoType MoneyEntrustNo;				///< 资金流水委托号
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcTransBalance TransBalance;				///< 转账金额

	CJGtdcOptionRspBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspBankTrans));
	}
};

///投资者期权银衍转账查询
struct CJGtdcOptionReqQryBankTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcQueryMode QueryMode;                      ///< 查询模式
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcDate nStartDate;							///< 起始日期
	TJGtdcDate nEndDate;							///< 结束日期

	CJGtdcOptionReqQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBankTrans));
	}
};

///投资者期权银衍转账查询应答
struct CJGtdcOptionRspQryBankTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankName	BankName;						///< 银行名称
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcEntrustNoType EntrustNo;					///< 委托号
	TJGtdcOpConfigInfo OpConfigInfo;				///< 操作确认信息
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcOperType OperType;						///< 操作类型
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcDate OperDate;							///< 操作日期
	TJGtdcTime OperTime;							///< 操作时间
	TJGtdcOpRetCode  OpRetCode;						///< 操作返回代码
	TJGtdcOperBalance OperBalance;					///< 操作金额



	CJGtdcOptionRspQryBankTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBankTrans));
	}
};

//投资者期权银衍转账可转资金请求
struct CJGtdcOptionReqQryBankMaxTrans
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号

	CJGtdcOptionReqQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryBankMaxTrans));
	}
};

//投资者期权银衍转账可转资金应答
struct CJGtdcOptionRspQryBankMaxTrans
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	CJGtdcOptionRspQryBankMaxTrans()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryBankMaxTrans));
	}
};

//投资者期权查询子账户及其资金请求
struct CJGtdcOptionReqQryChildBankFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	CJGtdcOptionReqQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqQryChildBankFund));
	}
};

//投资者期权查询子账户及其资金应答
struct CJGtdcOptionRspQryChildBankFund
{
	TJGtdcBranchNoType BranchNo;                    ///< 营业部号
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcFundAccountType FundAccount;              ///< 资金账号
	TJGtdcBankCodeType BankCode;                    ///< 银行代码
	TJGtdcBankAccountType BankAccount;				///< 银行账号
	TJGtdcBankName BankName;				        ///< 银行简称
	TJGtdcMainFlag MainFlag;						///< 主副标志
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcTransBalance TransBalance;				///< 可转账金额
	TJGtdcRestBalance RestBalance;					///< 资金余额
	TJGtdcEnableBalance EnableBalance;				///< 可用余额
	TJGtdcFetchBalance FetchBalance;				///< 可取余额
	CJGtdcOptionRspQryChildBankFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspQryChildBankFund));
	}
};


//投资者期权同名账户资金内转请求
struct CJGtdcOptionReqInTransferFund
{
	TJGtdcClientIDType ClientID;                    ///< 客户号
	TJGtdcMoneyType MoneyType;                      ///< 币种
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcTransBalance TransBalance;				///< 内转金额
	CJGtdcOptionReqInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionReqInTransferFund));
	}
};


//投资者期权同名账户资金内转应答
struct CJGtdcOptionRspInTransferFund
{
	TJGtdcResultType  ResultType;                   ///< 应答结果
	TJGtdcErrorInfoType ErrorInfo;                  ///< 错误信息
	TJGtdcFundAccountType InFundAccount;			///< 转入账户
	TJGtdcFundAccountType OutFundAccount;			///< 转出账户
	TJGtdcEntrustNoType InTransNo;					///< 转入流水号
	TJGtdcEntrustNoType OutTransNo;					///< 转出流水号

	CJGtdcOptionRspInTransferFund()
	{
		memset(this, 0, sizeof(CJGtdcOptionRspInTransferFund));
	}
};



#endif /*  JG_TDCSTRUCT_H */