#include "dealer.h"
#include "asharefun.h"
#include "altraderspi.h"


Dealer::Dealer(QObject *parent)
{
    pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
    m_tradeSpi = new AlTraderSpi();
    m_tradeSpi->init(pUserApi);
}

void Dealer::run()
{
    pUserApi->RegisterSpi((CThostFtdcTraderSpi*)m_tradeSpi);			// 注册事件类
    pUserApi->SubscribePublicTopic(THOST_TERT_QUICK);				// 注册公有流
    pUserApi->SubscribePrivateTopic(THOST_TERT_QUICK);				// 注册私有流
    pUserApi->RegisterFront(AShareFun::GetFrontAddr());							// connect
    pUserApi->Init();
    pUserApi->Join();
    AShareFun::ALDebug("Dealer进程结束");
}

void Dealer::TestConnect()
{

}

void Dealer::Logout()
{
    if( m_tradeSpi->hasLogin() == true)
    {
        m_tradeSpi->ReqUserLogout();
        pUserApi->Release();
    }
    this ->terminate();
}

bool Dealer::HasLogin()
{
    return m_tradeSpi->hasLogin();
}

void Dealer::SendOrder(int price, int volume,  int BuySell, int OpenClose)
{
    TThostFtdcDirectionType	Direct;
    if( BuySell == 0)
    {
        Direct = THOST_FTDC_D_Buy;
    }
    else
    {
        Direct = THOST_FTDC_D_Sell;
    }

    m_tradeSpi->ReqOrderInsert(price, volume, Direct, OpenClose);
    for( int i=0; i<10; i++)
    {
        if(m_tradeSpi->hasReturn() == true)
        {
            return;
        }
        AShareFun::ALDebug("等待回报中...");
        AShareFun::ALSleep(1000);
    }
    AShareFun::ALDebug("响应超时");
    return;
}

QVector<CThostFtdcOrderField> Dealer::QryOrder()
{
    m_tradeSpi->ReqQryOrder();
    // 获取查询数据
    for( int i=0; i<20; i++)
    {
        if(m_tradeSpi->hasReturn() == true)
        {
            return m_tradeSpi->data_CurOrders;
        }
        //AShareFun::ALDebug("报单无快速return");
        AShareFun::ALSleep(2000);
    }
    AShareFun::ALDebug("响应超时");
    QVector<CThostFtdcOrderField> res;
    return res;
}

CThostFtdcTradingAccountField Dealer::QueryAccount()
{
    m_tradeSpi->ReqQryTradingAccount();
    for( int i=0; i<10; i++)
    {
        if(m_tradeSpi->hasReturn() == true)
        {
            return m_tradeSpi->data_pTradingAccount;
        }
        AShareFun::ALDebug("等待回报中...");
        AShareFun::ALSleep(1000);
    }
    AShareFun::ALDebug("响应超时");
    return m_tradeSpi->data_pTradingAccount;
}

CThostFtdcSettlementInfoConfirmField Dealer::ConfirmSettlement()
{
    m_tradeSpi->ReqSettlementInfoConfirm();
    for( int i=0; i<10; i++)
    {
        if(m_tradeSpi->hasReturn() == true)
        {
            return m_tradeSpi->data_pSettlementInfoConfirm;
        }
        AShareFun::ALDebug("等待回报中...");
        AShareFun::ALSleep(1000);
    }
    AShareFun::ALDebug("响应超时");
    return m_tradeSpi->data_pSettlementInfoConfirm;
}



