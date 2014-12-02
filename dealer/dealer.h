/************************************************************************************************
 *
 * **********************************************************************************************/
#ifndef DEALER_H
#define DEALER_H

#include "dealer_global.h"
#include <QThread>

#include "../Alchemist/inc/Ctp/windows/ThostFtdcTraderApi.h"

#include "altraderspi.h"

class DEALERSHARED_EXPORT Dealer:public QThread
{
    Q_OBJECT
public:
    Dealer(QObject *parent = 0);
    void run();         // 必须重写函数
    void TestConnect(); // 必须重写函数
    void Logout();
    bool HasLogin();    // 判断是否登录
    void SendOrder(int price, int volume, int BuySell, int OpenClose);
    QVector<CThostFtdcOrderField> QryOrder();   // 查单

    CThostFtdcTradingAccountField QueryAccount(); // 查账户
    CThostFtdcSettlementInfoConfirmField ConfirmSettlement(); // 查资金


private:
    CThostFtdcTraderApi* pUserApi;
    AlTraderSpi *m_tradeSpi;
};

#endif // DEALER_H
