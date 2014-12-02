//#include "mainwindow.h"
#include <QApplication>
//#include <altraderspi.h>
#include "altraderspi.h"
#include "altraderthread.h"
//#include <dealer.h>

#include <qstringlist.h>
#include <QtDebug>
#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include "AStruct.h"
#include "asharefun.h"
#include "mainwindow.h"

#ifdef Q_OS_MAC
// mac
#endif

#ifdef Q_OS_LINUX
// linux
#include "inc/Ctp/linux/ThostFtdcMdApi.h"
#endif

#ifdef Q_OS_WIN
// win
#include "inc/Ctp/windows/ThostFtdcMdApi.h"
#endif

//#include "../TradeLib/TradeLib/tradelib_global.h"
//#include "../TradeLib/TradeLib/tradelib.h"

//CThostFtdcTraderApi* pUserApi;


//TThostFtdcInstrumentIDType
//char *ppInstrumentID[] = {"ag1412","i1501","ag1409","i1409"};
//int iInstrumentID = 4;
//int iRequestID = 0;

#include <QTextCodec>
#include "actor.h"

#include "QtSql/qsql.h"

//#include <C:/Users/Lio/Documents/GitHub/Alchemist/dealer/dealer.h>
#include <qDebug>

int main(int argc, char *argv[])
{
    AShareFun s;
//    s.ReadFile("s");
    s.ReadConfig();


    //显示需要区分系统
    if(argc == 2)
    {

        QString tmpQStr = argv[1];
        if( tmpQStr == "-M")
        {
            QApplication a(argc, argv);
            MarketRecorder* testMd = new MarketRecorder();
            testMd->start();
            return a.exec();
        }
        else if(tmpQStr == "-H")
        {

        }
    }
    else if(argc == 1)
    {
        QApplication a(argc, argv);
        MainWindow mw;
        mw.show();
        return a.exec();
    }
    return 0;
    //return a.exec();
}
