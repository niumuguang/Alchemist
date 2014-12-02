#include "altraderspi.h"

//#include <asharefun.h>
#include "asharefun.h"
//#include <ThostFtdcTraderApi.h>
#include "inc/Ctp/windows/ThostFtdcTraderApi.h"
//AlTraderSpi::AlTraderSpi()
//{
//}

// USER_API参数
extern CThostFtdcTraderApi *pUserApi;
int SumRequestID = 0;

void AlTraderSpi::OnFrontConnected()
{
    AShareFun::ALDebug("发送连接请求");
    ///用户登录请求
    ReqUserLogin();
}

void AlTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    AShareFun::ALDebug("登陆请求回报");

    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        // 保存会话参数
        AShareFun::ALDebug("登陆成功");
//        FRONT_ID = pRspUserLogin->FrontID;
//        SESSION_ID = pRspUserLogin->SessionID;
//        int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
//        iNextOrderRef++;
//        sprintf(ORDER_REF, "%d", iNextOrderRef);
//        ///获取当前交易日
//        cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
//        ///投资者结算结果确认
//        ReqSettlementInfoConfirm();
    }
}

void AlTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

void AlTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

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

}

void AlTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

}

void AlTraderSpi::ReqUserLogin()
{
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
        AShareFun::ALDebug("发送登陆请求成功");
        return;
    }
    else
    {
        AShareFun::ALDebug("发送登陆请求失败");
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
