#include "altraderspi.h"

#include <asharefun.h>
//#include <ThostFtdcTraderApi.h>
#include "../Alchemist/inc/Ctp/windows/ThostFtdcTraderApi.h"
//AlTraderSpi::AlTraderSpi()
//{
//}

// USER_API参数

void AlTraderSpi::init(CThostFtdcTraderApi *api)
{
    SumRequestID = 0;
    pUserApi = api;
    m_hasLogin = false;
    m_hasReturn = false;
}

bool AlTraderSpi::hasLogin()
{
    return m_hasLogin;
}

bool AlTraderSpi::hasReturn()
{
    return m_hasReturn;
}

void AlTraderSpi::OnFrontConnected()
{
    ///用户登录请求
    ReqUserLogin();
}

void AlTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    m_hasReturn = true;
    AShareFun::ALDebug("登录回报");
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        // 保存会话参数
        AShareFun::ALDebug("登陆成功");
        m_hasLogin = true;
        data_pRspUserLogin = *pRspUserLogin;
        //        FRONT_ID = pRspUserLogin->FrontID;
        //        SESSION_ID = pRspUserLogin->SessionID;
        m_CurOrderRef = atoi(pRspUserLogin->MaxOrderRef);
        //        iNextOrderRef++;
        //        sprintf(ORDER_REF, "%d", iNextOrderRef);
        //        ///获取当前交易日
        //        cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
        //        ///投资者结算结果确认
        //        ReqSettlementInfoConfirm();
    }
}

void AlTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    m_hasReturn = true;
    //
    AShareFun::ALDebug("登出回报");
    if(bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        AShareFun::ALDebug("登出成功");
        m_hasLogin = false;
    }
}

void AlTraderSpi::OnRspSettlementInfoConfirm( CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    m_hasReturn = true;
    //
    AShareFun::ALDebug("结算请求回报");
    if(bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        AShareFun::ALDebug("结算成功");
        //CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm
        data_pSettlementInfoConfirm = *pSettlementInfoConfirm;
    }
}

void AlTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    m_hasReturn = true;
    //
    AShareFun::ALDebug("查资金请求回报");
    if(bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        AShareFun::ALDebug("查资金成功");
        data_pTradingAccount = *pTradingAccount;
    }
}

void AlTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    m_hasReturn = true;
    //
    AShareFun::ALDebug("报单请求回报");
    if( IsErrorRspInfo(pRspInfo) )
    {
        AShareFun::ALDebug("报单成功");
        data_pInputOrder = *pInputOrder;
    }
}

void AlTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnFrontDisconnected(int nReason)
{

}

void AlTraderSpi::OnHeartBeatWarning(int nTimeLapse)
{

}

void AlTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    AShareFun::ALDebug("报单通知");
}

void AlTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    AShareFun::ALDebug("成交通知");
}

void AlTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    AShareFun::ALDebug("报单录入错误回报");
}

void AlTraderSpi::OnRspQryOrder(CThostFtdcOrderField *pOrder,
                                CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                bool bIsLast)
{
    if( bIsLast == true )
    {
        m_hasReturn = true;
    }
    AShareFun::ALDebug("报单查询回报");
    data_CurOrders.append(*pOrder);
}

void AlTraderSpi::ReqQryOrder()
{
    m_hasReturn = false;
    if( data_CurOrders.size() != 0)
    {
        data_CurOrders.clear();
    }
    //data_CurOrders.
    //
    CThostFtdcQryOrderField req;
    memset(&req, 0, sizeof(req));
    char *brokerID = ( char* )malloc(11);
    brokerID = AShareFun::GetBrokerID();
    strncpy(req.BrokerID, brokerID, strlen(brokerID) );
    char *investorID = ( char* )malloc(13);
    investorID = AShareFun::GetInvestorID();

    int iResult = pUserApi->ReqQryOrder(&req, SumRequestID++);
    if( iResult == 0 )
    {
        AShareFun::ALDebug("报单查询请求成功");
        return;
    }
    else
    {
        AShareFun::ALDebug("报单查询请求失败");
        return;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
void AlTraderSpi::ReqUserLogin()
{
    m_hasReturn = false;
    //
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    char *brokerID = ( char* )malloc(11);
    brokerID = AShareFun::GetBrokerID();
    strncpy(req.BrokerID, brokerID, strlen(brokerID) );
    char *investorID = ( char* )malloc(13);
    investorID = AShareFun::GetInvestorID();
    strcpy(req.UserID, investorID);
    char *password = ( char* )malloc(41);
    password = AShareFun::GetPassword();
    strcpy(req.Password, password);
    int iResult = pUserApi->ReqUserLogin(&req, SumRequestID++);
    if( iResult == 0 )
    {
        AShareFun::ALDebug("登录请求成功");
        return;
    }
    else
    {
        AShareFun::ALDebug("登录请求失败");
        return;
    }

}

void AlTraderSpi::ReqSettlementInfoConfirm()
{
    m_hasReturn = false;
    //
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
#ifdef Q_OS_LINUX
    strcpy(req.BrokerID, AShareFun::GetBrokerID());
    strcpy(req.InvestorID, AShareFun::GetInvestorID());
#else
    strncpy_s(req.BrokerID, AShareFun::GetBrokerID(), strlen( AShareFun::GetBrokerID() ) );
    strncpy_s(req.InvestorID, AShareFun::GetInvestorID(), strlen(AShareFun::GetInvestorID()) );
#endif

    int iResult = pUserApi->ReqSettlementInfoConfirm(&req, SumRequestID++);
    if(iResult == 0)
    {
        AShareFun::ALDebug("结算请求成功");
        return;
    }
    else
    {
        AShareFun::ALDebug("结算请求失败");
        return;
    }
}

void AlTraderSpi::ReqQryTradingAccount()
{
    m_hasReturn = false;
    //
    CThostFtdcQryTradingAccountField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, AShareFun::GetBrokerID());
    strcpy(req.InvestorID, AShareFun::GetInvestorID());
    int iResult = pUserApi->ReqQryTradingAccount(&req, SumRequestID++);
    if (iResult)
    {
        AShareFun::ALDebug("查资金请求成功");
    }
    else
    {
        AShareFun::ALDebug("查资金请求失败");
    }
}

void AlTraderSpi::ReqOrderInsert(int price, int volume,
                                 TThostFtdcDirectionType Direction, int OpenClose)
{
    m_hasReturn = false;
    //
    CThostFtdcInputOrderField req;
    memset(&req, 0, sizeof(req));
    ///经纪公司代码
#ifdef Q_OS_LINUX
    strncpy(req.BrokerID, AShareFun::GetBrokerID(), strlen( AShareFun::GetBrokerID() ) );
    strncpy(req.InvestorID, AShareFun::GetInvestorID(), strlen(AShareFun::GetInvestorID() ) );
    strncpy(req.UserID, AShareFun::GetInvestorID(), strlen( AShareFun::GetInvestorID() ) );
    strncpy(req.InstrumentID, AShareFun::GetInvestorID(), strlen(AShareFun::GetInvestorID() ) );
#else
    strncpy_s(req.BrokerID, AShareFun::GetBrokerID(), strlen( AShareFun::GetBrokerID() ) );
    strncpy_s(req.InvestorID, AShareFun::GetInvestorID(), strlen(AShareFun::GetInvestorID()) );
    strncpy_s(req.UserID, AShareFun::GetInvestorID(), strlen( AShareFun::GetInvestorID() ) );
    ///合约代码
    strncpy_s(req.InstrumentID, AShareFun::GetInvestorID(), strlen(AShareFun::GetInvestorID() ) );
#endif

    req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;
    ///买卖方向:
    req.Direction = Direction;
    ///组合开平标志: 开仓
    if( OpenClose == 0)
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    }
    else
    {
        req.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    }
    ///组合投机套保标志
    req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
    ///价格
    req.LimitPrice = price;
    ///数量: 1
    req.VolumeTotalOriginal = volume;
    ///有效期类型: 当日有效
    req.TimeCondition = THOST_FTDC_TC_GFD;
    ///GTD日期
    //	TThostFtdcDateType	GTDDate;
    ///成交量类型: 任何数量
    req.VolumeCondition = THOST_FTDC_VC_AV;
    ///最小成交量: 1
    req.MinVolume = 1;
    ///触发条件: 立即
    req.ContingentCondition = THOST_FTDC_CC_Immediately;
    ///止损价
    //	TThostFtdcPriceType	StopPrice;
    ///强平原因: 非强平
    req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
    ///自动挂起标志: 否
    req.IsAutoSuspend = 0;
    ///业务单元
    //	TThostFtdcBusinessUnitType	BusinessUnit;
    ///请求编号
    //	TThostFtdcRequestIDType	RequestID;
    ///用户强评标志: 否
    req.UserForceClose = 0;

    ///报单引用
    //strncpy_s(req.OrderRef, m_UserLoginField.MaxOrderRef);
    //req.LimitPrice = 0;
    //req.Direction = THOST_FTDC_D_Buy;
    //qDebug()<<"--->SumRequestID"<<SumRequestID;
    int iResult = pUserApi->ReqOrderInsert(&req, SumRequestID++);
    if( iResult == 0 )
    {
        AShareFun::ALDebug("报单请求成功");
    }
    else
    {
        AShareFun::ALDebug("报单请求失败");
    }
}

void AlTraderSpi::ReqUserLogout()
{
    m_hasReturn = false;
    //
    CThostFtdcUserLogoutField req;
    memset(&req, 0, sizeof(req));
    char *brokerID = ( char* )malloc(11);
    brokerID = AShareFun::GetBrokerID();
    strncpy(req.BrokerID, brokerID, strlen(brokerID) );
    char *investorID = ( char* )malloc(16);
    investorID = AShareFun::GetInvestorID();
    strncpy(req.UserID, investorID, strlen(brokerID) );
    int iResult = pUserApi->ReqUserLogout(&req, SumRequestID++); // 第二次登出时崩溃
    if(iResult == 0)
    {
        AShareFun::ALDebug("登出请求成功");
        return;
    }
    else
    {
        AShareFun::ALDebug("登出请求失败");
        return;
    }
}

bool AlTraderSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    // 如果ErrorID != 0, 说明收到了错误的响应
    bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (bResult)
        //cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
        AShareFun::ALDebug("发生错误");
    return bResult;
}
