#ifndef RECORDER_H
#define RECORDER_H

#include "recorder_global.h"

#include "cmysql_api.h"

//#include <C:/Users/Lio/Documents/GitHub/Alchemist/Alchemist/inc/Ctp/windows/ThostFtdcMdApi.h>
#include "../Alchemist/inc/Ctp/windows/ThostFtdcMdApi.h"
//#include <C:/Users/Lio/Documents/GitHub/Alchemist/Alchemist/inc/Ctp/windows/ThostFtdcTraderApi.h>
#include "../Alchemist/inc/Ctp/windows/ThostFtdcTraderApi.h"

/**********************************************
 * 用于数据提取进程
 *
 * ********************************************/
class RECORDERSHARED_EXPORT MarketRecorder:public QThread
{
    Q_OBJECT
public:
    MarketRecorder(QObject *parent = 0);
    void run();         // 必须重写函数
    void stop();
    void TestConnect(); // 必须重写函数
    //void Logout();
    //bool HasLogin();    // 判断是否登录
    //void SendOrder(int price, int volume, int BuySell, int OpenClose);


private:
    CThostFtdcMdApi* pUserApi;
//    AlTraderSpi *m_tradeSpi;
};


/* *******************************
 * 用于数据库交互
 *
 * *******************************/
class RECORDERSHARED_EXPORT DatabaseRecorder
{

public:
    DatabaseRecorder();

    void testConnect();

private:
    CMySQL_Api* testApi;

};

#endif // RECORDER_H
