#ifndef __JGDFDAPI_DATADEF_H__
#define __JGDFDAPI_DATADEF_H__
#include "JGDataTypesDef.h"

#ifndef VHANDLE
typedef void* VHANDLE;									///< 句柄标识
#endif // !VHANDLE

#define JGAPI_SERVERINFO_MAX	4						///< 最大服务器个数

#pragma pack(push, 1)

/*-----------------------------------------------枚举定义----------------------------------------------------------*/
///< 消息类型对应的结构体见后面
enum DFDAPI_MSG_ID
{
	MSG_INVALID = -100,
	
	///< 系统消息
	MSG_SYS_DISCONNECT_NETWORK,							///< 网络断开事件, 相应的结构体为NULL
	MSG_SYS_CONNECT_RESULT,								///< 主动发起连接的结果
	MSG_SYS_LOGIN_RESULT,								///< 登陆应答
	MSG_SYS_CODETABLE_RESULT,							///< 代码表结果，收到此消息后可获取对应代码表,此消息表示所有授权市场代码表可取
	MSG_SYS_QUOTATIONDATE_CHANGE,						///< 行情日期变更通知（已取消）
	MSG_SYS_MARKET_CLOSE,								///< 闭市（已取消）
	MSG_SYS_HEART_BEAT,									///< 服务器心跳消息, 相应的结构体为NULL
	MSG_SYS_MARKET_EVENT,								///< 市场事件通知消息(如市场清盘，转数等),收到此事件的清盘或者快照后可获取快照和期权信息
	
	//单个市场代码表通知.由于某些较小市场数据回调时，同时请求的其他市场才处理完代码表，行情数据较MSG_SYS_CODETABLE_RESULT先到，
	//增加该消息，通知每一市场代码表处理结果，客户可据此选择何时请求代码表
	MSG_SYS_SINGLE_CODETABLE_RESULT,					///< 单个市场代码表结果，收到此消息后可获取对应的单个市场代码表
	MSG_SYS_QUOTEUNIT_CHANGE,							///< 价差变化
	MSG_SYS_PACK_OVER,									///< 当前网络包解析完毕

	///< 数据消息
	MSG_DATA_INDEX,										///< 指数数据
	MSG_DATA_MARKET,									///< 行情数据
	MSG_DATA_FUTURE,									///< 期货行情
	MSG_DATA_HKEX,										///< 港股行情
	MSG_DATA_TRANSACTION,								///< 逐笔成交
	MSG_DATA_ORDERQUEUE,								///< 委托队列
	MSG_DATA_ORDER,										///< 逐笔委托
	MSG_DATA_BBQTRANSACTION,							///< BBQ现券成交数据
	MSG_DATA_BBQBID,									///< BBQ现券报价数据
	MSG_DATA_NON_MD,									///< 非行情消息
	MSG_DATA_OTC_OPTION,								///< 场外期权
	MSG_DATA_BROKERQUEUE,								///< 经纪商队列(港股)

	MSG_SH_ETF_LIST,									///< 收到沪市ETF清单信息.
	MSG_SZ_ETF_LIST,									///< 收到深市ETF清单信息.
	MSG_UPDATE_ETFLIST,									///< ETF清单有更新,沪深两市需请重新获取.
	MSG_HKEX_BASICINFO,									///< 港股基本信息更新,请获取.

	MSG_DATA_OPTION,									///< 期权行情
	MSG_OPTION_BASICINFO,								///< 期权基本信息更新,请获取.
};

///< 环境变量设置 
enum DFDAPI_SET_ENVIRONMENT
{
	DFDAPI_ENVIRON_HEART_BEAT_INTERVAL,					///< Heart Beat间隔（秒数）, 若值为0则表示默认值10秒钟
	//DFDAPI_ENVIRON_MISSED_BEAT_COUNT,					///< 如果没有收到心跳次数超过这个值，且没收到其他任何数据，则判断为掉线，若值0为默认次数2次
	DFDAPI_ENVIRON_OPEN_TIME_OUT,						///< 在调DFDAPI_Open期间，接收每一个数据包的超时时间（秒数，不是DFDAPI_Open调用总的最大等待时间），若值为0则默认30秒
	DFDAPI_ENVIRON_USE_PACK_OVER,
	DFDAPI_ENVIRON_HEART_BEAT_FLAG,						///< 心跳数据发送方式（0: 取消发送心跳包 1：没有数据发送的时候发送心跳数据，2：有规律发送心跳数据）
	DFDAPI_ENVIRON_SOURCE_MODE,							///< 双活数据源模式,值参考DFDAPI_SOURCE_SETTING枚举类
	DFDAPI_ENVIRON_SOURCE_MODE_VALUE,					///< 双活数据源模式下参数的值
	DFDAPI_ENVIRON_OUT_LOG,								///< 1、当前目录下创建log，否则在当前路径有log文件夹时创建到log文件夹中
	DFDAPI_ENVIRON_SNAPSHOT_ENENT,						///< 1、发送快照事件和清盘通知但快照不发送到回调函数，否则直接发送快照到回调函数，无快照通知
	DFDAPI_ENVIRON_ORIGINAL_VOL,						///< 原始结构有效，1、指数成交量和成交额的单位为股和元，默认为100股和100元
	DFDAPI_ENVIRON_BREAKPOINT,							///< 1.网络断开后断点续传，else.请求最新快照
	DFDAPI_ENVIRON_PUSHMODE,							///< 0:启用默认订阅推送；1:禁用默认订阅推送。
};

///< 错误码 区别错误类型
enum DFDAPI_ERR_CODE
{
	DFDAPI_ERR_UNKOWN = -400,							///< 未知错误
	DFDAPI_ERR_UNINITIALIZE = -399,						///< 接口环境未初始化
	DFDAPI_ERR_INITIALIZE_FAILURE = -200,				///< 初始化socket环境失败
	DFDAPI_ERR_NETWORK_ERROR,							///< 网络连接出现问题
	DFDAPI_ERR_INVALID_PARAMS,							///< 输入参数无效
	DFDAPI_ERR_VERIFY_FAILURE,							///< 登陆验证失败：原因为用户名或者密码错误；超出登陆数量
	DFDAPI_ERR_NO_AUTHORIZED_MARKET,					///< 所有请求的市场都没有授权
	DFDAPI_ERR_NO_CODE_TABLE,							///< 所有请求的市场该天都没有代码表
	DFDAPI_ERR_NO_BASICINFO,							///< 所有请求的市场基本信息数据为空.
	DFDAPI_ERR_SUCCESS = 0,								///< 成功
};

//代理服务器设置
enum DFDAPI_PROXY_TYPE
{
	DFDAPI_PROXY_SOCK4,
	DFDAPI_PROXY_SOCK4A,
	DFDAPI_PROXY_SOCK5,
	DFDAPI_PROXY_HTTP11,
};

enum SUBSCRIPTION_STYLE
{
	SUBSCRIPTION_SET = 0,								///< 设置订阅行情，再次设置订阅时会自动取消之前所有订阅代码.
	SUBSCRIPTION_ADD = 1,								///< 增加订阅代码
	SUBSCRIPTION_DEL = 2,								///< 删除订阅代码
};


/*-----------------------------------------------消息头------------------------------------------------------------*/
///< 应用头
struct DFDAPI_APP_HEAD
{
	int	nHeadSize;										///< 本记录结构大小
	int	nItemCount;										///< 记录条数
	int	nItemSize;										///< 记录大小
};

///< 数据消息结构
struct DFDAPI_CALLBACK_MSG
{
	int  	                nDataType;					///< 数据类型 
	int			            nDataLen;					///< 数据长度（不包括DFDAPI_APP_HEAD的长度）
	int			            nServerTime;				///< 服务器本地时间戳（精确到毫秒HHMMSSmmm）
	int                     nConnectId;					///< 连接ID
	DFDAPI_APP_HEAD*        pAppHead;					///< 应用头
	void*                   pData;						///< 数据指针
};
/*-----------------------------------------------消息头------------------------------------------------------------*/



/*-----------------------------------------------回调函数----------------------------------------------------------*/
/*
* 数据回调
* @param vHandle 回调实例标识
* @param pMsg 回调消息，用于通知用户收到了行情快照，逐笔成交，逐笔委托，委托队列等数据
*/
#ifdef _WIN32
typedef void(__stdcall *dfdapi_data_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#else
typedef void(*dfdapi_data_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#endif

/*
* 通知回调
* @param vHandle 回调实例标识
* @param pMsg 回调消息，用于通知用户收到了网络断开事件、连接（重连）结果、代码表结果等
*/
#ifdef _WIN32
typedef void(__stdcall *dfdapi_notice_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#else
typedef void(*dfdapi_notice_callback)  (VHANDLE vHandle, DFDAPI_CALLBACK_MSG* pMsg);
#endif
/*-----------------------------------------------回调函数----------------------------------------------------------*/




///< ETF清单文件数据.
struct DFDAPI_ETFLISTFILE
{
	char szMarket[4];
	char szCode[12];
	char szFileName[32];
	int nFileLen;
	char *pFileData;
};


//详细类型	类型定义
//0x01	交易所指数
//0x03	亚洲指数
//0x04	国际指数
//0x05	系统分类指数
//0x06	用户分类指数
//0x07	期货指数
//0x08	指数现货
//
//0x10	A股
//0x11	中小板股
//0x12	创业板股
//0x16	B股
//0x17	H股
//0x1a	US
//0x1b	US ADR
//0x1e	扩展板块股票(港)
//
//0x20	基金
//0x21	未上市开放基金（开放式基金申赎）
//0x22	上市开放基金（LOF基金）
//0x23	交易型开放式指数基金（ETF基金）
//0x25	扩展板块基金(港)
//0x26	分级子基金
//0x27	封闭式基金
//
//
//0x30	政府债券（国债）
//0x31	企业债券
//0x32	金融债券（证券资产化）
//0x33	可转债券
//0x34	可转可分离债
//0x35	地方债
//0x36	公司债
//0x37	贴债
//0x38	私募债
//
//0x40	国债回购
//0x41	企债回购
//0x42	债券质押式回购
//
//0x60	权证
//0x61	认购权证
//0x62	认沽权证
//0x64	认购权证(B股)
//0x65	认沽权证(B股)
//0x66	牛证（moo - cow）
//0x67	熊证（bear）
//
//0x70	指数期货
//0x71	商品期货
//0x72	股票期货
//0x73	同业拆借利率期货
//0x74	外汇基金债券(Exchange Fund Note Futures)
//0x75	期货转现货交易(Exchange For Physicals)
//0x76	期货转掉期交易(Exchange of Futures For Swaps)
//0x78	指数期货连线CX
//0x79	指数期货连线CC
//0x7a	商品期货连线CX
//0x7b	商品期货连线CC
//0x7c	股票期货连线CX
//0x7d	股票期货连线CC
//0x7e	期现差价线
//0x7f	跨期差价线
//
//0x80	基本汇率
//0x81	交叉汇率
//0x82	反向汇率
//
//0x90	认购期权
//0x91	认沽期权
//0x92	指数认购期权
//0x93	指数认沽期权
//0x94	商品认沽期权
//0x95	商品认沽期权
//
//0xd0	银行利率
//0xd1	银行利率(HK)
//0xd2	银行利率(Interal)
//
//0xe0	贵金属(noble metal)
//
//0xf0	其他
//0xf1	A股新股申购
//0xf2	A股增发

///< 代码表信息.
struct DFDAPI_CODEINFO
{
	char szWindCode[32];									///< 000001.SZ;600000.SH;IH1711.CFF;
	char szSecurityID[16];									///< 今古行情证券代码.
	char szSecurityCode[24];								///< 交易所原始证券代码.
	char szMarket[8];										///< SZ;SH;CFF;SHO;SZO;
	char szENName[32];										///< 英文名称.
	char szCNName[32];										///< 证券名称.
	int nType;												///< 证券类型.
};

///< 连接结果：MSG_SYS_CONNECT_RESULT
struct DFDAPI_CONNECT_RESULT
{
	char szIp[32];
	char szPort[8];
	char szUser[64];
	char szPwd[64];
	unsigned int nConnResult;								///< 为0则表示连接成功，非0则表示连接失败
	int nConnectionID;										///< 连接ID
};

///< 登录应答：MSG_SYS_LOGIN_RESULT
struct DFDAPI_LOGIN_RESULT
{
	unsigned int nLoginResult;								///< 为0则表示验证成功，非0则表示登陆验证失败
	char szInfo[256];										///< 登陆结果文本
	int nMarkets;											///< 市场个数
	char szMarket[256][8];									///< 市场代码 SZ, SH, CF, SHF, CZC, DCE
	int nDynDate[256];										///< 动态数据日期
};

///< 系统消息：MSG_SYS_CODETABLE_RESULT 对应的结构
struct DFDAPI_CODE_RESULT
{
	char szInfo[128];										///< 代码表结果文本
	int nMarkets;											///< 市场个数
	char szMarket[256][8];									///< 市场代码
	int nCodeCount[256];									///< 代码表项数
	int nCodeDate[256];										///< 代码表日期
};



///< 行情快照：MSG_DATA_MARKET.
struct DFDAPI_MARKET_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< 原始Code
	int			nActionDay;									///< 业务发生日(自然日)
	int			nTradingDay;								///< 交易日
	int			nTime;										///< 时间(HHMMSSmmm)
	int			nStatus;									///< 状态
    T_I64		nPreClose;									///< 前收盘价
    T_I64		nOpen;										///< 开盘价
    T_I64		nHigh;										///< 最高价
    T_I64		nLow;										///< 最低价
    T_I64		nMatch;										///< 最新价
    T_I64		nAskPrice[10];								///< 申卖价
    T_I64		nAskVol[10];								///< 申卖量
    T_I64		nBidPrice[10];								///< 申买价
    T_I64		nBidVol[10];								///< 申买量
	int			nNumTrades;									///< 成交笔数
    T_I64		iVolume;									///< 成交总量
    T_I64		iTurnover;									///< 成交总金额
    T_I64		nTotalBidVol;								///< 委托买入总量
    T_I64		nTotalAskVol;								///< 委托卖出总量
    T_I64		nWeightedAvgBidPrice;						///< 加权平均委买价格
    T_I64		nWeightedAvgAskPrice;						///< 加权平均委卖价格
	int			nIOPV;										///< IOPV净值估值
	int			nYieldToMaturity;							///< 到期收益率
    T_I64		nHighLimited;								///< 涨停价
    T_I64		nLowLimited;								///< 跌停价
	char		chPrefix[4];								///< 证券信息前缀
	int			nSyl1;										///< 市盈率1
	int			nSyl2;										///< 市盈率2
	int			nSD2;										///< 升跌2（对比上一笔）
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 指数行情快照：MSG_DATA_INDEX.
struct DFDAPI_INDEX_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< 原始Code
	int         nActionDay;									///< 业务发生日(自然日)
	int         nTradingDay;								///< 交易日
	int         nTime;										///< 时间(HHMMSSmmm)
	int			nStatus;									///< 状态，20151223新增
    T_I64		nOpenIndex;									///< 今开盘指数
    T_I64 	nHighIndex;									///< 最高指数
    T_I64 	nLowIndex;									///< 最低指数
    T_I64 	nLastIndex;									///< 最新指数
    T_I64	    iTotalVolume;								///< 参与计算相应指数的交易数量
    T_I64	    iTurnover;									///< 参与计算相应指数的成交金额
    T_I64		nPreCloseIndex;								///< 前盘指数
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 期货行情快照：MSG_DATA_FUTURE.
struct DFDAPI_FUTURE_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< 原始Code
	int         nActionDay;									///< 业务发生日(自然日)
	int         nTradingDay;								///< 交易日
	int			nTime;										///< 时间(HHMMSSmmm)	
	int			nStatus;									///< 状态
    T_I64		iPreOpenInterest;							///< 昨持仓
	T_I64		nPreClose;									///< 昨收盘价
	unsigned int	nPreSettlePrice;						///< 昨结算
	T_I64		nOpen;										///< 开盘价	
	T_I64		nHigh;										///< 最高价
	T_I64		nLow;										///< 最低价
	T_I64		nMatch;										///< 最新价
	T_I64		iVolume;									///< 成交总量
	T_I64		iTurnover;									///< 成交总金额
	T_I64		iOpenInterest;								///< 持仓总量
	T_I64		nClose;										///< 今收盘
	unsigned int	nSettlePrice;							///< 今结算
	T_I64		nHighLimited;								///< 涨停价
	T_I64		nLowLimited;								///< 跌停价
	int			nPreDelta;									///< 昨虚实度
	int			nCurrDelta;									///< 今虚实度
	T_I64		nAskPrice[5];								///< 申卖价
	T_I64		nAskVol[5];									///< 申卖量
	T_I64		nBidPrice[5];								///< 申买价
	T_I64		nBidVol[5];									///< 申买量
	T_I64		nAuctionPrice;								///< 波动性中断参考价
	int			nAuctionQty;								///< 波动性中断集合竞价虚拟匹配量	
	int			nAvgPrice;									///< 郑商所期货均价
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 期权行情快照：MSG_DATA_OPTION.
struct DFDAPI_OPTION_DATA
{
	char        szWindCode[32];								///< 600001.SH 
	char        szCode[32];									///< 原始Code
	int			nDate;										///< 行情日期(YYYYMMDD).
	int			nTime;										///< 行情时间(HHMMSSmmm).	
	T_I64		iTotalLongPosition;							///< 当前合约未平仓数 N12 （单位是 （张））.
	T_I64		iTradeVolume;								///< 总成交数量 N16.
	double		dTotalValueTraded;							///< 成交金额 N16(2) （精确到分）.
	unsigned int	nPreSettlePrice;						///< 昨日结算价 N11(4) （精确到0.1厘）.
	unsigned int	nOpenPrice;								///< 今日开盘价 N11(4) （精确到0.1厘）.
	unsigned int	nAuctionPrice;							///< 动态参考价格 N11(4) （波动性中断参考价，精确到0.1厘）.
	T_I64		iAuctionQty;								///< 虚拟匹配数量 N12.
	unsigned int	nHighPrice;								///< 最高价 N11(4) （精确到0.1厘）.
	unsigned int	nLowPrice;								///< 最低价 N11(4) （精确到0.1厘）.
	unsigned int	nTradePrice;							///< 最新价 N11(4) （最新成交价，精确到0.1厘）.
	unsigned int	arrnBidPrice[5];						///< 申买价 N11(4) （当前买入价（当前最优价），精确到0.1厘）.
	T_I64		arriBidVolume[5];							///< 申买量 N12.
	unsigned int	arrnAskPrice[5];						///< 申卖价 N11(4) （当前卖出价（当前最优价），精确到0.1厘）.
	T_I64		arriAskVolume[5];							///< 申卖量 N12.
	unsigned int	nSettlePrice;							///< 今日结算价 N11(4) ***交易所期权行情目前取消了结算价的发布***.
	char		szTradingPhaseCode[4];						///< 产品实时阶段及标志 C4 

	int			nRFValue;									///< 价差（最新价对比减上一个价格）（精确到0.1厘）.
	T_I64		iNumTrades;									///< 成交笔数.
	unsigned int	nSecurityClosePx;						///< 合约前收盘价 N11(4) (昨日收盘价，右对齐，精确到厘).
	unsigned int	nHighLimitedPrice;						///< 涨幅上限价格 N11(4) (当日期权涨停价格，精确到0.1厘).
	unsigned int	nLowLimitedPrice;						///< 跌幅下限价格 N11(4) (当日期权跌停价格，精确到0.1厘).
};

///< 逐笔成交MSG_DATA_TRANSACTION.
struct DFDAPI_TRANSACTION
{
	char		szWindCode[32];								///< 600001.SH.
	char		szCode[32];									///< 原始Code.
	int			nActionDay;									///< 自然日.
	int 		nTime;										///< 成交时间(HHMMSSmmm).
	int 		nChannelNo;									///< 成交通道.
	T_I64		iTradeIndex;								///< 成交序号.
	T_I64		iAskOrder;									///< 叫卖方委托序号.
	T_I64		iBidOrder;									///< 叫买方委托序号.
	unsigned int unPrice;									///< 成交价格.
	T_I64 	iVolume;									///< 成交数量.
	T_I64		iTurnover;									///< 成交金额.
	int			nBSFlag;									///< 买卖方向(买：'B', 卖：'A', 不明：' ')
	char		chOrderKind;								///< 成交类别
	char		chFunctionCode;								///< 成交代码
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效.
};

///< 逐笔委托MSG_DATA_ORDER.
struct DFDAPI_ORDER_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< 原始Code
	int 		nActionDay;									///< 委托日期(YYMMDD)
	int 		nTime;										///< 委托时间(HHMMSSmmm)
	int			nChannelNo;									///< 频道代码(成交通道).
	T_I64		iApplSeqNum;								///< 委托序号.
	unsigned int unPrice;									///< 委托价格
	unsigned int unVolume;									///< 委托数量
	char		chOrderKind;								///< 委托类别
	char		chFunctionCode;								///< 委托代码('B','S','C')
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 委托队列MSG_DATA_ORDERQUEUE.
struct DFDAPI_AB50_DATA
{
	char		szWindCode[32];								///< 600001.SH 
	char		szCode[32];									///< 原始Code
	int			nActionDay;									///< 自然日
	int 		nTime;										///< 时间(HHMMSSmmm)
	int			nSide;										///< 买卖方向('B':Bid 'A':Ask)
	T_I64		nPrice;										///< 委托价格
	int 		nOrders;									///< 订单数量
	int 		nABItems;									///< 明细个数
	int 		nABVolume[200];								///< 订单明细
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 港股行情快照：MSG_DATA_HKEX.
struct DFDAPI_HKEX_DATA
{
	char szWindCode[32];									///< 600001.SH 
	char szCode[32];										///< 原始Code
	int nDate;												///< 行情日期(YYYYMMDD).
	int nTime;					       		 				///< 行情切片(HHMMSSmmm).
	int	nStatus;					   						///< 产品实时阶段及标志.
	unsigned int unPreClosePx;								///< 前收盘价.*10000
	unsigned int unNominalPrice;							///< 按盘价.*10000
	unsigned int unOpenPrice;								///< 开盘价.*10000
	unsigned int unHighPrice;								///< 最高价.*10000
	unsigned int unLowPrice;								///< 最低价.*10000
	unsigned int unTradePrice;								///< 最新价.*10000
	long long llTotalVolume;		    					///< 成交总量.
	double dTotalAmount;									///< 成交总金额.
	unsigned int arrnAskPrice[10];							///< 委卖价.*10000
	long long arriAskVolume[10];							///< 委卖量.
	long long arriTotalAskOty[10];							///< 委卖总委托笔数.
	unsigned int arrnBidPrice[10];							///< 委买价.*10000
	long long arriBidVolume[10];							///< 委买量.
	long long arriTotalBuyOty[10];							///< 委买总委托笔数.
	unsigned int unTradeVolume;								///< 瞬时成交量.
	unsigned int unSpread;									///< 价差.*10000
	//const DFDAPI_CODE_INFO *  pCodeInfo;					///< 代码信息， DFDAPI_Close，清盘重连后，此指针无效
};

///< 港股代码基本信息
struct DFDAPI_BASICINFO_HKEX
{
	char szWindCode[32];									///< 00001.HK 
	char szCode[32];										///< 原始Code
	int nDate;												///< 日期(YYYYMMDD).
	char szISIN[16];										///< ISIN
	char szSymbol[32];										///< 中文证券简称
	char szSymbolEn[16];									///< 英文证券简称
	char szSecurityDesc[32];								///< 英文全称
	char szUnderlyingSecurityID[8];							///< 辅助证券代码
	char szMarketID[8];										///< 市场种类 MAIN- 主板  GEM-创业板	ETS - 扩充交易证券   NASD - Nasdaq AMX市场
	char szSecurityType[8];									///< 证券类别 BOND - Bond 债券 BWRT - Basket Warrant 一篮子权证		EQTY - Equity  股本			TRST - Trust  信托
	char szCurrency[4];										///< 货币种类
	int nAmountTimes;										///< 货币单位 货币单位表示前收盘价格字段的单位，当货币单位取值为0时，前收盘价格=前收盘价格字段取值×10的0次幂，当货币单位取值为1时，前收盘价格=前收盘价格字段取值×10的1次幂，依次类推。
	double dPerValue;										///< 面值
	char szPerValueCurrency[4];								///< 面值货币种类
	double dInterest;										///< 利息
	int nIssueDate;											///< 上市日期
	unsigned int unRoundLot;								///< 买卖单位
	unsigned int unPreClosePx;								///< 前收盘价格 * 10000
	char szText[50];										///< 备注
	char SecurityStatusFlag[12];							///< 产品状态信息 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。第1位：无定义。第2位：无定义。第3位：‘0’表示非标的证券，‘1’表示标的证券。
	char szDataSource[8];									///< 行情数据的来源。如果第一位非零，表示来自深港通，如果第二位非零，表示来自沪港通。
};

///< 期权基本信息
struct DFDAPI_BASICINFO_OPTION
{
	int nDate;												///< 日期(YYYYMMDD).
	char szWindCode[32];									///< 00001.HK 
	char szCode[32];										///< 原始Code
	char szContractID[24];									///< [sh][sz]合约交易代码 C19.
	char szContractSymbol[24];								///< [sh][sz]期权合约简称 C20.
	char szUnderlyingSecurityID[8];							///< [sh][sz]标的证券代码 C6.
	char szUnderlyingSymbol[16];							///< [sh]基础证券证券名称 C8 .
	char szUnderlyingType[4];								///< [sh]标的证券类型 C3 (EBS–ETF，ASH–A股)			///< [sz](取值为29-个股期权）,30 -ETF期权)).
	char chOptionType;										///< [sh][sz]欧式美式 C1 (若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A” “B”-百慕大式).
	char chCallOrPut;										///< [sh][sz]认购认沽 C1 认购，则本字段为“C”；若为认沽，则本字段为“P”.
	long long iContractMultiplierUnit;						///< [sh][sz]合约单位 N11 (经过除权除息调整后的合约单位).
	unsigned int nExercisePrice;							///< [sh][sz]期权行权价 N11(4) (经过除权除息调整后的期权行权价，精确到0.1厘).
	int  nStartDate;										///< [sh]首个交易日(YYYYMMDD) C8.
	int  nEndDate;											///< [sh][sz]最后交易日(YYYYMMDD) C8.
	int  nExerciseDate;										///< [sh][sz]期权行权日(YYYYMMDD) C8.
	int  nDeliveryDate;										///< [sh]行权交割日(YYYYMMDD) C8.
	int  nExpireDate;										///< [sh][sz]期权到期日(YYYYMMDD) C8.
	char chUpdateVersion;									///< [sh]合约版本号 C1.							///< [sz]交割方式(DeliveryType) 'S'=证券结算 'C='现金结算
	long long iTotalLongPosition;							///< [sh][sz]当前合约未平仓数 N12 (单位是 （张）).
	unsigned int nSecurityClosePx;							///< [sh]合约前收盘价 N11(4) (昨日收盘价，右对齐，精确到厘).
	unsigned int nSettlePrice;								///< [sh][sz]合约前结算价 N11(4) (昨日结算价，如遇除权除息则为调整后的结算价（合约上市首日填写参考价），右对齐，精确到0.1厘).
	unsigned int nUnderlyingClosePx;						///< [sh]标的证券前收盘价 N11(4) (期权标的证券除权除息调整后的前收盘价格，右对齐，精确到0.1厘).
	char chPriceLimitType;									///< [sh]涨跌幅限制类型 C1 (‘N’有涨跌幅限制类型). 	///< [sz]该字段代表挂牌类型（ListType） 1=品种新挂. 2=到期加挂. 3=调整加挂. 4=波动加挂.
	unsigned int nUpLimitDailyPrice;						///< [sh][sz]涨幅上限价格 N11(4) (当日期权涨停价格，精确到0.1厘).
	unsigned int nDownLimitDailyPrice;						///< [sh][sz]跌幅下限价格 N11(4) (当日期权跌停价格，精确到0.1厘).
	double dMarginUnit;										///< [sh]单位保证金 N16(2) (当日持有一张合约所需要的保证金数量，精确到分).		///< [sz]今卖开每张保证金(SellMargin)
	double dMarginRatioParam1;								///< [sh][sz]保证金计算比例参数一 N3 (保证金计算参数，单位：%).
	double dMarginRatioParam2;								///< [sh][sz]保证金计算比例参数二 N3 (保证金计算参数，单位：%).
	long long iRoundLot;             						///< [sh]整手数 N12 一手对应的合约数.						///<[sz]调整次数(AdjustTimes).
	long long iLmtOrdMinFloor;       						///< [sh]单笔限价申报下限 N12 (单笔限价申报的申报张数下限。).	///< [sz]买数量上限(BuyQtyUpperLimit).
	long long iLmtOrdMaxFloor;       						///< [sh]单笔限价申报上限 N12 (单笔限价申报的申报张数上限。).	///< [sz]卖数量上限(SellQtyUpperLimit).
	long long iMktOrdMinFloor;       						///< [sh]单笔市价申报下限 N12 (单笔市价申报的申报张数下限。).	///< [sz]买数量单位(BuyQtyUnit).
	long long iMktOrdMaxFloor;       						///< [sh]单笔市价申报上限 N12 (单笔市价申报的申报张数上限。).	///< [sz]卖数量单位(SellQtyUnit).

	char szSecurityStatusFlag[8];							///< [sh][sz]. 证券状态.

	///上海【sh】期权合约状态信息标签 C8 (该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。).
	///第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（包括备兑开仓）和买入开仓。
	///第2位：‘0’表示未连续停牌，‘1’表示连续停牌。
	///第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足10个交易日。
	///第4位：‘0’表示近期未做调整，‘1’表示最近10个交易日内合约发生过调整。
	///第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。

	///深圳【sz】证券状态,由于深交所可能有多个状态同时出现在一个代码中，所以当前处理为每个字节填一个状态，
	///如果遇到0值的字节值表示结束，如果第一个字节填0则表示代码处于正常状态.
	///1-停牌
	///2-除权
	///3-除息
	///4-ST
	///5-*ST
	///6-上市首日
	///7-公司再融资
	///8-恢复上市首日
	///9-网络投票
	///10-退市整理期
	///11-暂停上市
	///12-增发股份上市
	///13-合约调整

	unsigned int nTickSize;          						///< [sh]最小报价单位 N11(4) 单位：元，精确到0.1厘(行情通讯按价格类型处理) .
};

///< 期权代码表
struct DFDAPI_OPTION_CODE
{
	//DFDAPI_CODEINFO basicCode;
	char szContractID[32];									///< 期权合约代码
	char szUnderlyingSecurityID[32];						///< 标的证券代码
	char chCallOrPut;										///< 认购认沽C1 认购，则本字段为“C”；若为认沽，则本字段为“P”
	int  nExerciseDate;										///< 期权行权日，YYYYMMDD    
	//扩充字段
	char chUnderlyingType;									///< 标的证券类型C3 0-A股 1-ETF (EBS – ETF， ASH – A 股)
	char chOptionType;										///< 欧式美式C1 若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
	char chPriceLimitType;									///< 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型
	int  nContractMultiplierUnit;							///< 合约单位,经过除权除息调整后的合约单位, 一定是整数
	T_I64  nExercisePrice;								///< 期权行权价,经过除权除息调整后的期权行权价，右对齐，精确到厘
	int  nStartDate;										///< 期权首个交易日,YYYYMMDD
	int  nEndDate;											///< 期权最后交易日/行权日，YYYYMMDD
	int  nExpireDate;										///< 期权到期日，YYYYMMDD
};

union DFDAPI_EXCODE_INFO
{
	struct DFDAPI_OptionCodeInfo							///< futures options 专用 (nType >= 0x90 && nType <= 0x95),非期权下列字段无效
	{
		char chContractID[32];								///< 期权合约代码C19
		char szUnderlyingSecurityID[32];					///< 标的证券代码
		char chUnderlyingType;								///< 标的证券类型C3    0-A股 1-ETF (EBS – ETF， ASH – A 股)
		char chOptionType;									///< 欧式美式C1        若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A”
		char chCallOrPut;									///< 认购认沽C1        认购，则本字段为“C”；若为认沽，则本字段为“P”
		char chPriceLimitType;								///< 涨跌幅限制类型C1 ‘N’表示有涨跌幅限制类型, ‘R’表示无涨跌幅限制类型
		int  nContractMultiplierUnit;						///< 合约单位,         经过除权除息调整后的合约单位, 一定是整数
		T_I64  nExercisePrice;							///< 期权行权价,       经过除权除息调整后的期权行权价，右对齐，精确到厘
		int  nStartDate;									///< 期权首个交易日,YYYYMMDD
		int  nEndDate;										///< 期权最后交易日/行权日，YYYYMMDD
		int  nExerciseDate;									///< 期权行权日，YYYYMMDD
		int  nExpireDate;									///< 期权到期日，YYYYMMDD
	}Option;
};

//struct DFDAPI_CODE_INFO
//{
//	int  nMarketID;											///< 交易所ID,定义如下
//	int  nDataLevel;										///< 数据Level
//	int  nFlag;												///< 数据来源
//	int  nType;												///< 证券类型
//	char chCode[32];										///< 证券代码
//	char chName[64];										///< 汉语证券名称
//	DFDAPI_EXCODE_INFO exCodeInfo;
//	char chWindType[8];										///< windType : FUR(期货),测试
//	int nLotSize;											///< 交易量纲,港股有效
//};

struct DFDAPI_SZBaseETF
{
	char szVersion[8];										///< 版本号.
	int nMarketType;										///< 市场类型.
	int nETFType;											///< ETF类型，参见MDData_inner::EETFType定义.
	char szSecurityID[16];									///< ETF代码.
	char szPurchaseAndRedem[16];							///< 申购赎回代码.
	char szSecuritySymbol[32];								///< ETF简称【SZ】.
	char szFundManagementCompany[64];						///< 基金公司名称.
	char szUnderlyingSecurityID[16];						///< 拟合指数代码.
	int nUnderlyingSecurityMarketType;						///< 拟合指数代码市场类型.
	unsigned int unCreationRedemptionUnit;					///< 最小申购赎回单位,对应的 ETF 份数，目前只能为正整数.
	double dEstimateCashComponent;							///< 预估现金差额.
	double dMaxCashRatio;									///< 最大现金替代比例.
	char chPublish;											///< 是否发布 IOPV,Y=是,N = 否.
	char chCreation;										///< 是否允许申购,Y=是,N = 否.
	char chRedemption;										///< 是否允许赎回,Y=是,N = 否.
	unsigned int unRecordNum;								///< 深市成份证券数目.
	unsigned int unTotalRecordNum;							///< 所有成份证券数目.
	int nTradingDay;										///< 交易日.
	int nPreTradingDay;										///< 前交易日.
	double dCashComponent;									///< 现金余额, T-X 日申购赎回基准单位的现金余额.
	double dNAVperCU;										///< 申购赎回基准单位净值, T - X 日申购赎回基准单位净值.
	double dNAV;											///< 单位净值,T-X 日基金的单位净值.
	double dDividendPerCU;									///< T 日申购赎回基准单位的红利金额.
	int nCreationLimit;										///< 当天累计可申购的基金份额上	限，为 0 表示没有限制，目前只能为整数.
	int nRedemptionLimit;									///< 当天累计可赎回的基金份额上限，为 0 表示没有限制， 目前只能为整数.
	int nCreationLimitPerUser;								///< 单个证券账户当天累计可申购的基金份额上限，为 0 表示没有限制，目前只能为整数.
	int nRedemptionLimitPerUser;							///< 单个证券账户当天累计可赎回的基金份额上限，为 0 表示没有限制，目前只能为整数.
	int nNetCreationLimit;									///< 当天净申购的基金份额上限，为 0表示没有限制，目前只能为整数.
	int nNetRedemptionLimit;								///< 当天净赎回的基金份额上限，为 0表示没有限制，目前只能为整数.
	int nNetCreationLimitPerUser;							///< 单个证券账户当天净申购的基金份额上限，为 0 表示没有限制，目前只能为整数.
	int nNetRedemptionLimitPerUser;							///< 单个证券账户当天净赎回的基金份额上限，为 0 表示没有限制，目前只能为整数.
};

struct DFDAPI_SZBaseETFComponent
{
	int nMarketType;										///< 市场类型.
	char szSecurityID[16];									///< 证券代码.
	char szSecuritySymbol[32];								///< 证券简称.
	unsigned int unComponentShare;							///< 成分数量.
	double dPremiumRatio;									///< 溢价比例.此字段只有现金替代标志为‘1’时才有效.
	double dCreationCashSubstitute;							///< 申购替代金额.此字段只有当替代标志为‘2’时才有效.
	double dRedemptionCashSubstitute;						///< 赎回替代金额;对于跨境 ETF、跨市场 ETF、黄金 ETF 和现金债券 ETF，该字段为 0.0000;此字段只有当替代标志为‘2’时才有效.

	///< 0 = 禁止现金替代（必须有证券）
	///< 1 = 可以进行现金替代（先用证券，证券不足时差额部分用现金替代）
	///< 2 = 必须用现金替代
	char chSubstituteFlag;									///< 现金替代标志.
};


struct DFDAPI_SHBaseETF
{
	int nMarketType;										///< 市场类型.
	int nETFType;											///< ETF类型，参见MDData_inner::EETFType定义.
	char szSecurityID[16];									///< ETF一级市场申购赎回代码.
	char szPurchaseAndRedem[16];							///< 申购赎回代码.
	unsigned int unCreationRedemptionUnit;					///< 最小申购赎回单位,对应的 ETF 份数.
	double dMaxCashRatio;									///< 最大现金替代比例.
	char chPublish;											///< 是否发布 IOPV,Y=是,N = 否.（Y表示计算IOPV并通过行情发布；N表示不计算IOPV也无需通过行情发布)
	char chCreation;										///< 是否允许申购,Y=是,N = 否.
	char chRedemption;										///< 是否允许赎回,Y=是,N = 否.
	unsigned int unRecordNum;								///< 成分证券数量.
	double dEstimateCashComponent;							///< 预估现金差额.
	int nTradingDay;										///< 交易日.
	int nPreTradingDay;										///< 前交易日.
	double dCashComponent;									///< 现金余额, T-X 日申购赎回基准单位的现金余额.
	double dNAVperCU;										///< 申购赎回基准单位净值, T - X 日申购赎回基准单位净值.
	double dNAV;											///< 单位净值,T-X 日基金的单位净值.
};

struct DFDAPI_SHBaseETFComponent
{
	int nMarketType;										///< 市场类型.
	char szSecurityID[16];									///< 证券代码.
	char szSecuritySymbol[32];								///< 证券简称.
	unsigned int unComponentShare;							///< 成分数量.
	double dPremiumRatio;									///< 溢价比例.替代标志为1、3、5时，此字段必填，且取值范围为[0, 1）.
	double dCashSubstitute;									///< 替代总金额金额.替代标志为2、3、4、5、6时此字段必填，且必须大于等于0.

	///< 0表示该证券为沪市证券，禁止现金替代（必须有证券）
	///< 1表示该证券为沪市证券，可以进行现金替代（先用证券，证券不足的话用现金替代）
	///< 2表示该证券为沪市证券，必须用现金替代。
	///< 3表示该证券为深市证券，退补现金替代。
	///< 4表示该证券为深市证券，必须现金替代。
	///< 5表示非沪深市场成分证券退补现金替代。
	///< 6表示非沪深市场成份证券必须现金替代。
	char chSubstituteFlag;									///< 现金替代标志.
};


/*------------------------------------------------参数设置------------------------------------------------------------------*/
//服务器配置信息
struct DFDAPI_SERVER_INFO
{
	char szIp[32];											///< IP
	short nPort;											///< 端口
	char szUser[64];										///< 用户名
	char szPwd[64];											///< 密码
	bool bDoMain;											///< 是否使用域名
};

struct DFDAPI_OPEN_CONNECT_SET
{
	DFDAPI_SERVER_INFO	ServerInfo[JGAPI_SERVERINFO_MAX];	///< 服务器信息
	unsigned int unServerNum;								///< 服务器数量
	dfdapi_data_callback data_fun;							///< 数据消息处理回调
	dfdapi_notice_callback notice_fun;						///< 系统消息通知回调
	///< 订阅设置 注意：订阅是市场独立的！对于每个市场必须订阅市场或代码，只订阅市场，则发送此市场全部代码
	const char* szMarkets;									///< 市场订阅！例如"SZ;SH;CF;SHF;DCE;SHF"，需要订阅的市场列表，以“;”分割.
	const char* szSubScriptions;							///< 代码订阅！例如"600000.sh;IH1711.cf;000001.sz"，需要订阅的股票，以“;”分割.
	const char* szTypeFlags;								///< 数据类型订阅！支持订阅3种类型TRANSACTION;ORDER;ORDERQUEUE。！注意：行情数据任何时候都发送，不需要订阅! 参见enum DATA_TYPE_FLAG.
	unsigned int nTime;										///< 为0则请求实时行情，为0xffffffff从头请求.
	unsigned int nConnectionID;								///< 连接ID，连接回调消息的附加结构 DFDAPI_CONNECT_RESULT中 会包含这个ID，消息头也会包含该ID.
};

struct DFDAPI_PROXY_SET
{
	DFDAPI_PROXY_TYPE nProxyType;							///< 代理类型
	char szProxyHostIp[32];									///< 代理IP
	char szProxyPort[8];									///< 代理端口
	char szProxyUser[32];									///< 代理用户名
	char szProxyPwd[32];									///< 代理密码
};
/*------------------------------------------------参数设置------------------------------------------------------------------*/

#pragma pack(pop)
#endif