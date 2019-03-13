#include <CallBack.h>
#include <string.h>
#include <iostream>
#ifndef INT_MAX  //兼容linux
#define INT_MAX       2147483647    /* maximum (signed) int value */
#endif


using namespace std;

namespace xti
{
    Callback::Callback(const string& address, const string& username, const string& password, const string& fundAccountId, int orderTimes)
        :m_nRequestId(50),
        m_strAddress(address),
        m_strUserName(username),
        m_strPassWord(password),
        m_strFundAccountId(fundAccountId),
        m_nOrderTimes(orderTimes),
        m_client(NULL)
    {
    }

    Callback::~Callback()
    {
        if (m_client != NULL)
        {
            m_client->destroy();
            delete m_client;
        }
    }

    int Callback::init()
    {
        if (m_strAddress.empty())
        {
            cout << "[" << __FUNCTION__ << "] address is NULL\n";
            return -1;
        }

        m_client = XtTraderApi::createXtTraderApi(m_strAddress.c_str());
        if (NULL == m_client)
        {
            cout << "[" << __FUNCTION__ << "] create api client fails\n";
            return -1;
        }

        m_client->setCallback(this);
        return m_client->init();
    }

    void Callback::join()
    {
        m_client->join();
    }

    void Callback::onConnected(bool success, const char* errorMsg) 
    {
        cout << "[onConnected] connect " << (success?"true":"false") << endl;
        if (success)
        {
            m_client->userLogin(m_strUserName.c_str(), m_strPassWord.c_str(), m_nRequestId++);
        }
    }

    void Callback::onUserLogin(const char* userName, const char* password, int nRequestId, const XtError& error)
    {
        cout << "[" << __FUNCTION__ << "] ErrorID: " << error.errorID() 
            << ", msg: " << error.errorMsg() 
            << endl;
        if (error.isSuccess())
        {
        }
    }

    void Callback::onRtnLoginStatus(const char* accountId, EBrokerLoginStatus status, int brokerType, const char* errorMsg)
    {
        cout << "[" << __FUNCTION__ << "] accountId: " << accountId << " "; 
        switch(status)
        {
        case BROKER_LOGIN_STATUS_INALID:    cout << "登录无效" << endl;  break;
        case BROKER_LOGIN_STATUS_OK:        cout << "可用，初始化完成" << endl;  break;
        case BROKER_LOGIN_STATUS_WAITING_LOGIN:  cout << "连接中" << endl;  break;
        case BROKER_LOGIN_STATUS_LOGINING:  cout << "登录中" << endl;  break;
        case BROKER_LOGIN_STATUS_FAIL:      cout << "失败" << endl;    break;
        case BROKER_LOGIN_STATUS_INITING:   cout << "在初始化中 "<< endl;  break;
        case BROKER_LOGIN_STATUS_CORRECTING:cout << "数据刷新校正中" << endl; break;
        case BROKER_LOGIN_STATUS_CLOSED:    cout << "收盘后（休市中）"<< endl; break;
        }

        if (status == BROKER_LOGIN_STATUS_OK && strcmp(accountId, m_strFundAccountId.c_str()) == 0)
        {
            // 请求类函数reqXXX 都可以在此处调用
            m_client->reqAccountDetail(m_strFundAccountId.c_str(), ++m_nRequestId);

            // 报单类参数
            testOrdinaryOrder(CB_AT_STOCK, accountId, m_nOrderTimes); // 普通单，股票
            // testAlgorithmOrder(AT_STOCK, accountId); // 算法单，股票
            // testGroupOrder(accountId);               // 组合单, 只支持股票
        }
    }

    // ----------------------普通单----------------------------------------------


    void Callback::testFutureOrdinaryOrder(const string& accountId,  int times)
    {
        for (int i = 0; i < times; ++i)
        {
            // 参数中所有char[]数组默认值都为空。
             COrdinaryOrder orderInfo;

            // 资金账号，必填参数。不填会被api打回，并且通过onOrder反馈失败
            strcpy(orderInfo.m_strAccountID, accountId.c_str());
            orderInfo.m_strAccountID[accountId.length()] = '\0';

            // 单笔超价百分比，选填字段。默认为0
            orderInfo.m_dSuperPriceRate = 0;

            // 报单市场。必填字段。股票市场有"CFFEX"/"SHFE"/"DCE"/"CZCE"，如果填空或填错都会被api直接打回
            strcpy(orderInfo.m_strMarket, "CZCE");

            // 报单合约代码，必填字段。
            strcpy(orderInfo.m_strInstrument, "CF503");

            // 报单委托量，必填字段。默认int最大值，填0或不填会被api打回
            orderInfo.m_nVolume = 1;

            // 报单委托类型。必填字段。根据相应的业务选择，具体请参考XtDataType.h，默认为无效值(OPT_INVALID)。不填会被api打回
            orderInfo.m_eOperationType = OPT_OPEN_LONG;

            // 报单价格类型，必填字段。默认为无效(PTRP_INVALID)，具体可参考XtDataType.h
            orderInfo.m_ePriceType = PRTP_LATEST;

            // 报单价格，默认为double最大值。当价格类型m_ePriceType为指定价PRTP_FIX时，必填字段。当价格类型为其他时填了也没用
            orderInfo.m_dPrice = 12895;

            // 投机套保标志，选填字段。有"投机"/"套利"/"套保"方式。除期货三个方式都可选之外都是填“投机”。默认为“投机”
            orderInfo.m_eHedgeFlag = HEDGE_FLAG_SPECULATION;

            // 直接还款的金额。仅直接还款用，信用业务类型专用
            orderInfo.m_dOccurBalance = 100;

            m_client->order(&orderInfo, ++m_nRequestId);
        }
    }

    void Callback::testStockOrdinaryOrder(const string& accountId,  int times)
    {
        for (int i = 0; i < times; ++i)
        {
            // 参数中所有char[]数组默认值都为空。
             COrdinaryOrder orderInfo;

            // 资金账号，必填参数。不填会被api打回，并且通过onOrder反馈失败
            strcpy(orderInfo.m_strAccountID, accountId.c_str());
            orderInfo.m_strAccountID[accountId.length()] = '\0';

            // 单笔超价百分比，选填字段。默认为0
            orderInfo.m_dSuperPriceRate = 0;

            // 报单市场。必填字段。股票市场有"SH"/"SZ"，如果填空或填错都会被api直接打回
            strcpy(orderInfo.m_strMarket, "SH");

            // 报单合约代码，必填字段。
            strcpy(orderInfo.m_strInstrument, "600000");

            // 报单委托量，必填字段。默认int最大值，填0或不填会被api打回
            orderInfo.m_nVolume = 100;

            // 报单委托类型。必填字段。根据相应的业务选择，具体请参考XtDataType.h，默认为无效值(OPT_INVALID)。不填会被api打回
            orderInfo.m_eOperationType = OPT_BUY;

            // 报单价格类型，必填字段。默认为无效(PTRP_INVALID)，具体可参考XtDataType.h
            orderInfo.m_ePriceType = PRTP_LATEST;

            // 报单价格，默认为double最大值。当价格类型m_ePriceType为指定价PRTP_FIX时，必填字段。当价格类型为其他时填了也没用
            orderInfo.m_dPrice = 12.3;

            // 投机套保标志，选填字段。有"投机"/"套利"/"套保"方式。除期货三个方式都可选之外都是填“投机”。默认为“投机”
            orderInfo.m_eHedgeFlag = HEDGE_FLAG_SPECULATION;

            // 直接还款的金额。仅直接还款用，信用业务类型专用
            orderInfo.m_dOccurBalance = 100;

            m_client->order(&orderInfo, ++m_nRequestId);
        }
    }


    void Callback::testCreditOrdinaryOrder(const string& accountId,  int times)
    {
        // 参考股票和期货普通单
    }

    void Callback::testStockOptionOrdinaryOrder(const string& accountId,  int times)
    {
        // 参考股票和期货普通单
    }


    void Callback::testOrdinaryOrder(AccoutType fundAccountType, const string& accountId,  int times)
    {
        switch(fundAccountType)
        {
            case CB_AT_FUTURE:
                testFutureOrdinaryOrder(accountId, times);
                break;

            case CB_AT_STOCK: // 资金账号为股票类型时
                testStockOrdinaryOrder(accountId, times);
                break;

            case CB_AT_CREDIT:
                testCreditOrdinaryOrder(accountId, times);
                break;

            case CB_AT_STOCK_OPTION:
                testStockOptionOrdinaryOrder(accountId, times);
                break;

            default:
                break;
        }
    }


    // ----------------------算法单（以股票、期货为例，不支持etf申赎）----------------------------------------------

    /*case CB_AT_FUTURE:
        {
            orderInfo.m_nVolume = 1; // 委托量
            strcpy(orderInfo.m_strMarket, "CZCE"); // 市场
            strcpy(orderInfo.m_strInstrument, "CF503"); // 合约代码
            orderInfo.m_eOperationType = OPT_OPEN_LONG; // 委托类型
            orderInfo.m_dPrice = 12895;// 当PriceType为PTRP_FIX时，必须填写。如果不为指定价，则apiservice会根据行情获取相应价格
            orderInfo.m_ePriceType = PRTP_LATEST;
        }
        break;

    case CB_AT_CREDIT:
        {
            orderInfo.m_nVolume = 100;
            strcpy(orderInfo.m_strMarket, "SH");
            strcpy(orderInfo.m_strInstrument, "600000");
            orderInfo.m_eOperationType = OPT_FIN_BUY;
            orderInfo.m_dPrice = 18;// 当PriceType为PTRP_FIX时，必须填写
            orderInfo.m_ePriceType = PRTP_LATEST;
        }
        break;

    case CB_AT_STOCK_OPTION:
        {
            orderInfo.m_nVolume = 1;
            strcpy(orderInfo.m_strMarket, "SHO");
            strcpy(orderInfo.m_strInstrument, "11120100");   
            orderInfo.m_eOperationType = OPT_OPTION_BUY_OPEN;
            orderInfo.m_dPrice = 18;// 当PriceType为PTRP_FIX时，必须填写
            orderInfo.m_ePriceType = PRTP_LATEST;
        }
        break;
    */

    void Callback::testAlgorithmOrder(AccoutType fundAccountType, const string& accountId) 
    {
        // 这里以股票为例，期货、信用和股票期权见上面
        CAlgorithmOrder orderInfo;

        // 资金账号，必填字段。如果不填写会被api打回
        strcpy(orderInfo.m_strAccountID, accountId.c_str());
        orderInfo.m_strAccountID[accountId.length()] = '\0';

        // 价格波动区间，必填字段。默认值为double最大值。取值范围 0 <= orderInfo.m_dPriceRangeRate <= 1，如果不在这个范围内，直接被api打回
        orderInfo.m_dPriceRangeRate = 0.1;

        // 单笔超价比率，必填字段。-2 * orderInfo.m_dPriceRangeRate <= orderInfo.m_dSuperPriceRate <= 2 * orderInfo.m_dPriceRangeRate
        orderInfo.m_dSuperPriceRate = 0.2;  

        // 指令有效起始终止时间，api处理，写了也没用
        orderInfo.m_nValidTimeStart = time(NULL);
        orderInfo.m_nValidTimeEnd = time(NULL) + 1800;

        // 报单下撤单间隔，股票最小为10s，期货为0.5s
        orderInfo.m_dPlaceOrderInterval = 10; 
        orderInfo.m_dWithdrawOrderInterval = 10; 

        // 超价起始笔数，默认为1
        orderInfo.m_nSuperPriceStart = 1;

        // 报单量，必填字段。不可为0，默认值为无效值。不填或填0或被api打回
        orderInfo.m_nVolume = 1000;

        // 单笔下单比率，默认值为1，委托总量m_nVolume*单笔下单比率m_dSingleVolumeRate = 单笔下单量
        // 比如，下单总量1000 * 0.005 = 5 < 最小委托量100(限于股票)， 
        orderInfo.m_dSingleVolumeRate = 1;

        // 单笔下单最小值，默认为int型最大值。股票最小为100，期货最小为1
        orderInfo.m_nSingleNumMin = 100;

        // 单笔委托最大量，默认为int型最大值。最大可报100W
        // 如果 m_nVolume*m_dSingleVolumeRate > m_nMaxOrderCount，则以m_nMaxOrderCount为准
        orderInfo.m_nSingleNumMax = 1000; 

        // 尾单最小量
        orderInfo.m_nLastVolumeMin = 100;

        // 最大下单数
        orderInfo.m_nMaxOrderCount = 100;

        // 单笔基准：目标量、买1、买1+2、买1+2+3等，默认为目标量
        orderInfo.m_eSingleVolumeType = VOLUME_FIX;

        // 投机套保标志，选填字段。有"投机"/"套利"/"套保"方式。除期货三个方式都可选之外都是填“投机”。默认为“投机”
        orderInfo.m_eHedgeFlag = HEDGE_FLAG_SPECULATION;

        // 市场，必填字段。应该填写MarketType.h里的，股票市场有"SH"/"SZ"，如果填空或填错都会被api直接打回
        strcpy(orderInfo.m_strMarket, "SH");

        // 合约代码，必填字段。
        strcpy(orderInfo.m_strInstrument, "600000");

        // 报单委托类型。必填字段。根据相应的业务选择，具体请参考XtDataType.h，默认为无效值(OPT_INVALID)。不填会被api打回
        orderInfo.m_eOperationType = OPT_BUY;

        // 报单价格，默认为double最大值。当价格类型m_ePriceType为指定价PRTP_FIX时，必填字段。当价格类型为其他时填了也没用
        orderInfo.m_dPrice = 12.3;

        // 报单价格，默认为double最大值。当价格类型m_ePriceType为指定价PRTP_FIX时，必填字段。当价格类型为其他时填了也没用
        orderInfo.m_ePriceType = PRTP_LATEST;

        //requestID，本地用于确定服务器返回的 
        m_client->order(&orderInfo, ++m_nRequestId);
    }


    // ----------------------组合单<只支持股票>----------------------------------------------

    void Callback::testGroupOrder(const string& accountId)
    {
        CGroupOrder orderInfo;


        // m_orderParam为算法单结构体，具体请参考面文件
        // 波动区间   小于等于1，大于等于0的数
        orderInfo.m_orderParam.m_dPriceRangeRate = 0.03;
        // 单笔超价
        orderInfo.m_orderParam.m_dSuperPriceRate = 0.01;
        // 报价类型
        orderInfo.m_orderParam.m_ePriceType = PRTP_LATEST;
        // 下单类型
        orderInfo.m_orderParam.m_eOperationType = OPT_BUY;
        // 超价起始笔数
        orderInfo.m_orderParam.m_nSuperPriceStart = 1;
        // 下单间隔(秒）
        orderInfo.m_orderParam.m_dPlaceOrderInterval = 30;
        // 撤单间隔（秒）
        orderInfo.m_orderParam.m_dWithdrawOrderInterval = 30;
        // 单比下单比率(1 为一次全部下单）
        orderInfo.m_orderParam.m_dSingleVolumeRate = 1; 
        // 单笔下单基准
        orderInfo.m_orderParam.m_eSingleVolumeType = VOLUME_FIX;
        // 最大下单次数
        orderInfo.m_orderParam.m_nMaxOrderCount = 100;
        // 单笔下单量最大值，必须大于或等于 m_nVolume[i] * m_dSingleVolumeRate
        // 否则，以单笔下单量最大值为准
        orderInfo.m_orderParam.m_nSingleNumMax = 200;
        // 单笔下单量最小值, 不能比100 再小了
        orderInfo.m_orderParam.m_nLastVolumeMin = 100;

        // 资金账号，必填字段。如果不填写会被api打回
        strcpy(orderInfo.m_orderParam.m_strAccountID, accountId.c_str());
        orderInfo.m_orderParam.m_strAccountID[accountId.length()] = '\0';

        // 股票只数，必填参数，默认值为0。必须大于0，小于等于500
        orderInfo.m_nOrderNum = 2;

        // 合约代码， 必填字段。不填会被api打回
        strcpy(orderInfo.m_strInstrument[0], "000002");
        strcpy(orderInfo.m_strInstrument[1], "000004");

        // 市场，只有"SH"/"SZ"两个市场可以填写
        strcpy(orderInfo.m_strMarket[0], "SZ");
        strcpy(orderInfo.m_strMarket[1], "SZ");

        // 报单数量
        orderInfo.m_nVolume[0] = 100;
        orderInfo.m_nVolume[1] = 200;

        // 说明：m_nOrderNum、m_strInstrument、m_strMarket、m_nVolume必须统一
        m_client->order(&orderInfo, m_nRequestId++);
    }


        // ----------------------撤委托----------------------------------------------

    void Callback::testCancekOrder(AccoutType fundAccountType, const char* accountId)
    {
        switch(fundAccountType)
        {
            case CB_AT_STOCK:
                {
                    char* market = "SZ";
                    char* code = "000002";
                    char orderSyeId[32];
                    strcpy(orderSyeId, "B2151109");
                    m_client->cancelOrder(accountId, orderSyeId, market, code, ++m_nRequestId);
                }
                break;

            case CB_AT_FUTURE:
                {
                    char* market = "CFFEX";
                    char* code = "IF1504";
                    char orderSyeId[32];
                    strcpy(orderSyeId,"1288606");
                    m_client->cancelOrder(accountId, orderSyeId, market, code, ++m_nRequestId);
                }
                break;
        }
    }

    void Callback::onOrder(int nRequestId, int orderId, const XtError& error)
    {
        cout << "[" <<__FUNCTION__ <<"] isSuccess: " << (error.isSuccess()?"true":"false") 
            << "\n    orderId:  " << orderId
            << "\n    RequestId: " << nRequestId  
            << "\n    errorMsg: " << error.errorMsg()
            << endl;
        if (error.isSuccess())
        {
            // 撤单<撤单与撤委托的区别请详见常见错误文档>
            m_client->cancel(orderId, ++m_nRequestId);
        }
    }

    void Callback::onCancel(int nRequestId, const XtError& error)
    {
        cout << "onCancel: error: " << (error.isSuccess()?"no error":error.errorMsg()) << ", requestID: " << nRequestId << endl;
    }

    void Callback::onUserLogout(const string& userName, const string& password, int nRequestId, const XtError& error) 
    {
        cout << "onUserLogout " << endl;
    }

    // 通用
    void Callback::onReqAccountDetail(const char* accountId, int nRequestId, const CAccountDetail* data, bool isLast, const XtError& error)
    {
        cout << "onReqAccountDetail: accountId: " << accountId << ", error: " << (error.isSuccess()?"no error":error.errorMsg()) << endl;
    }

    void Callback::onReqCreditAccountDetail(const char* accountID, int nRequestId, const CCreditAccountDetail* data, bool isLast, const XtError& error) 
    {
        cout << "onReqCreditAccountDetail: accountId: " << accountID << ", error: " << (error.isSuccess()?"no error":error.errorMsg()) << endl;
    }

    void Callback::onReqOrderDetail(const char* accountID, int nRequestId, const COrderDetail* data, bool isLast, const XtError& error)
    {
        cout << "onReqOrderDetail: accountId: " << accountID << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    void Callback::onReqDealDetail(const char* accountID, int nRequestId, const CDealDetail* data, bool isLast, const XtError& error)
    {
        cout << "onReqDealDetail: accountId: " << accountID << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    void Callback::onReqPositionDetail(const char* accountID, int nRequestId, const CPositionDetail* data, bool isLast, const XtError& error)
    {
        cout << "onReqPositionDetail: accountId: " << accountID << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    void Callback::onReqPositionStatics(const char* accountID, int nRequestId, const CPositionStatics* data, bool isLast, const XtError& error)
    {
        cout << "onReqPositionStatics: accountId: " << accountID << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    // 信用
    void Callback::onReqStksubjects(const char* accountId, int nRequestId, const CStkSubjects* data, bool isLast, const XtError& error)
    {
        cout << "onReqStksubjects: accountId: " << accountId << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    void Callback::onReqStkcompacts(const char* accountId, int nRequestId, const CStkCompacts* data, bool isLast, const XtError& error)
    {
        cout << "onReqStkcompacts: accountId: " << accountId << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    // 股票期权
    void Callback::onReqCoveredStockPosition(const char* accountId, int nRequestId, const CCoveredStockPosition* data, bool isLast, const XtError& error)
    {
        cout << "onReqCoveredStockPosition: accountId: " << accountId << ", error: " << (error.isSuccess()?"No error":error.errorMsg()) << endl;
    }

    // 查询产品接口
    void Callback::onReqProductData(int nRequestId, const CProductData* data, bool isLast, const XtError& error)
    {
        cout <<" [onReqProductData]  产品净值 :"<<  data->m_dTotalNetValue
            << "\n    产品ID:"<< data->m_nProductId
            << "\n    当前资金余额:"<< data->m_dBalance 
            << "\n    期初资金余额:"<< data-> m_dPreBalance
            << "\n    期货帐号的可用资金之和:"<< data-> m_dAvaliableFuture
            << "\n    期货账号占用保证金:"<< data-> m_dCurrMargin
            << "\n    期货动态权益之和:"<< data-> m_dBalancefuture
            << "\n    股票总市值:"<< data-> m_dStockValue
            << "\n    债券总市值:"<< data-> m_dLoanValue
            << "\n    基金总市值:"<< data-> m_dFundValue
            << "\n    回购总市值:"<< data-> m_dRepurchaseValue << endl;
    }

    void Callback::onReqPriceData(int nRequestId, const CPriceData* data, const XtError& error)
    {
        cout << "[" << __FUNCTION__ << "] errorID: " << error.errorID();
        if (!error.isSuccess())
        {
            cout << "error msg: " << error.errorMsg() << endl;
        }
        else
        {
            cout << endl;
        }
    }

    // 主推类接口回调函数
    void Callback::onRtnOrder(const COrderInfo* data)
    {
        string orderStatus = "";
        switch(data->m_eStatus)
        {
        case OCS_CHECKING:   orderStatus = "风控检查中";  break;
        case OCS_APPROVING:  orderStatus = "审批中";  break;
        case OCS_REJECTED:   orderStatus = "已驳回";  break;
        case OCS_RUNNING:    orderStatus = "运行中";  break;
        case OCS_CANCELING:  orderStatus = "撤销中";  break;
        case OCS_FINISHED:   orderStatus = "已完成";  break;
        case OCS_STOPPED:    orderStatus = "已撤销";  break;
        }

        cout << ">>>>>>>>>>[" << __FUNCTION__ << "]"
            << "\n    下单ID: " << data->m_nOrderID
            << "\n    m_startTime：" << data->m_startTime
            << "\n    m_endTime: " << data->m_endTime
            << "\n    指令状态：" << orderStatus
            << "\n    成交量：" << data->m_dTradedVolume
            << "\n    撤销者：" << data->m_canceler
            << "\n    指令执行信息：" << data->m_strMsg
            << endl;
    }

    void Callback::onRtnOrderDetail(const COrderDetail* data)
    {
        string entrust_status;
        switch(data->m_eOrderStatus)
        {
        case ENTRUST_STATUS_UNREPORTED:  entrust_status = "未报";  break;
        case ENTRUST_STATUS_WAIT_REPORTING:  entrust_status = "待报"; break;
        case ENTRUST_STATUS_REPORTED:        entrust_status = "已报"; break;
        case ENTRUST_STATUS_REPORTED_CANCEL: entrust_status = "已报待撤";  break;
        case ENTRUST_STATUS_PARTSUCC_CANCEL: entrust_status = "部成待撤";  break;
        case ENTRUST_STATUS_PART_CANCEL:     entrust_status = "部撤";  break;
        case ENTRUST_STATUS_CANCELED:        entrust_status = "已撤";  break;
        case ENTRUST_STATUS_PART_SUCC:       entrust_status = "部成";  break;
        case ENTRUST_STATUS_SUCCEEDED:       entrust_status = "已成";  break;
        case ENTRUST_STATUS_JUNK:            entrust_status = "废单";  break;
        }
        if (data == NULL)
        {
            return;
        }
        cout << ">>>>>[onRtnOrderDetail]"
            << "\n    委托号：" << data->m_strOrderSysID
            << "\n    委托状态：" << entrust_status
            << "\n    已成交量：" << data->m_nTradedVolume 
            << "\n    成交均价：" << data->m_dTradeAmount 
            << "\n    成交额: " << data->m_dTradeAmount 
            << "\n    市场ID：" << data->m_strExchangeID
            << "\n    产品ID：" << data->m_strProductID
            << "\n    股票/期货代码：" << data->m_strInstrumentID
            << "\n    冻结保证金：" << data->m_dFrozenMargin
            << "\n    冻结手续费：" << data->m_dFrozenCommission
            << "\n    ErrorID：" << data->m_nErrorID
            << "\n    ErrorMsg: " << data->m_strErrorMsg
            << endl;

    }


    void Callback::onRtnDealDetail(const CDealDetail* data)
    {
        if (data == NULL)
        {
            return;
        }
        cout << ">>>>>>[" << __FUNCTION__ << "]"
            << "\n    orderId: " << data->m_nOrderID 
            << "\n    成交量： " << data->m_nVolume
            << "\n    成交额: " << data->m_dAmount
            << "\n    成交均价： " << data->m_dAveragePrice
            << endl;
    }

    void Callback::onRtnOrderError(const COrderError* data)
    {
        if (data == NULL)
        {
            return;
        }
        cout << ">>>>>[onRtnOrderError] orderId: " << data->m_nOrderID 
            << "\n    error id: " << data->m_nErrorID
            << "\n    errormsg: " << data->m_strErrorMsg
            << endl;
    }

    ///获得主推的撤销信息
    void Callback::onRtnCancelError(const CCancelError* data)
    {
        if (data == NULL)
        {
            return;
        }
        cout << "[" << __FUNCTION__ << "]"
            << "\n      OrderId: " << data->m_nOrderID 
            << "\n      ErrorId: " << data->m_nErrorID 
            << "\n      ErrorMsg: " << data->m_strErrorMsg
            << endl;
    }

    void Callback::onRtnDeliveryStatus(const char* accountID, bool status, const char* errorMsg)
    {
        cout << ">>>>>>[" << __FUNCTION__ << "], accountID: accountID: " << accountID << ", status: "<< status << endl;
    }

    void Callback::onRtnAccountDetail(const char* accountId, const CAccountDetail* accountDetail)
    {
    }

    void Callback::onRtnCreditAccountDetail(const char* accountID, const CCreditAccountDetail* data)
    {

    }

    void Callback::onRtnNetValue(const CNetValue* data)
    {
        //cout << "[onRtnNetValue] productId: " << data->m_nProductId
        //<< "\n    产品类型: " << data->m_nTypes // 产品类型 1-普通基金 2-分级基金
        //<< "\n    产品净值: " << data->m_dTotalNetValue  //产品净资产, 产品净值
        //<< "\n    母基金单位净值: " << data->m_dNetValue 
        //<< "\n    B级基金单位净值:" << data->m_dBNetValue
        //<< "\n    更新时间：      " << data->m_nUpdateTime
        //<< endl;
    }

}