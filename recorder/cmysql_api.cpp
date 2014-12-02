#include "chstimer.h"
#include "cmysql_api.h"
#include "../Alchemist/asharefun.h"
//#include <CTP/api/trade/win/public/ThostFtdcUserApiStruct.h>

//#include <../Alchemist/inc/Ctp/windows/ThostFtdcUserApiStruct.h>
//#include "CShareFun.h"
#include <QtSql>
#include <qsqldatabase.h>
#include <qstring.h>
//#include <chstimer.h>
//#include <config.h>
//using namespace std;

CMySQL_Api::CMySQL_Api()
{
    m_user = "root";
    m_passwd = "niumuguang";
    m_database = "IronDB";
    m_table = "ag1506";
    m_address = "192.168.1.117";
    m_port = 3306;
    m_isConnect = false;
#ifdef Q_OS_WIN
    windowInit();
#else
    linuxInit();
#endif
}

/****************************/
CMySQL_Api::CMySQL_Api(std::string ipaddress, int port,
                       std::string username, std::string password,
                       std::string database)
{
    //mysql_init(&m_mysql);
    m_user = username;
    m_passwd = password;
    m_database = database;
    //m_table = tablename;
    m_address = ipaddress;
    m_port = port;
    m_isConnect = false;

#ifdef Q_OS_WIN
    windowInit();
#else
    linuxInit();
#endif
}

CMySQL_Api::~CMySQL_Api()
{
#ifdef Q_OS_LINUX
    mysql_close(&m_mysql);
#else

#endif
}

void CMySQL_Api::WriteMarket(CThostFtdcDepthMarketDataField *DepthMarketData)
{
    //HSTime tmpTime;
    int res = 0;
    CHSTimer tmpTime(DepthMarketData->TradingDay,DepthMarketData->UpdateTime,
                     DepthMarketData->UpdateMillisec);

    string testTime = DepthMarketData->TradingDay;// + DepthMarketData->UpdateTime;
    testTime.insert(4,"-");
    testTime.insert(7,"-");
    testTime = testTime + " " + DepthMarketData->UpdateTime;
    string sq = "insert into "+(string)DepthMarketData->InstrumentID+"_tick (InstrumentID,TradingStamp,UpdateMillisec,LastPrice,AskPrice1,BidPrice1,AskVolume1,BidVolume1,AskPrice2,BidPrice2,AskVolume2,BidVolume2,AskPrice3,BidPrice3,AskVolume3,BidVolume3,AskPrice4,BidPrice4,AskVolume4,BidVolume4,AskPrice5,BidPrice5,AskVolume5,BidVolume5,AveragePrice,ClosePrice,CurrDelta,ExchangeID,ExchangeInstID,HighestPrice,LowestPrice,UpperLimitPrice,LowerLimitPrice,OpenInterest,OpenPrice,PreClosePrice,PreDelta,PreOpenInterest,PreSettlementPrice,Volume) values ('" +
            (string)DepthMarketData->InstrumentID +"','"+testTime+"',"+
            this->Int2String(DepthMarketData->UpdateMillisec) +"," +
            this->Int2String(DepthMarketData->LastPrice) + ","+
            Int2String(DepthMarketData->AskPrice1) + ","+ Int2String(DepthMarketData->BidPrice1) + ","+Int2String(DepthMarketData->AskVolume1) + "," +
            Int2String(DepthMarketData->BidVolume1) + "," +Int2String(DepthMarketData->AskPrice2) + "," +Int2String(DepthMarketData->BidPrice2) + "," +
            Int2String(DepthMarketData->AskVolume2) + "," +Int2String(DepthMarketData->BidVolume2) + "," +Int2String(DepthMarketData->AskPrice3) + "," +
            Int2String(DepthMarketData->BidPrice3) + "," +Int2String(DepthMarketData->AskVolume3) + "," +Int2String(DepthMarketData->BidVolume3) + "," +
            Int2String(DepthMarketData->AskPrice4) + "," +Int2String(DepthMarketData->BidPrice4) + "," +Int2String(DepthMarketData->AskVolume4) + "," +
            Int2String(DepthMarketData->BidVolume4) + "," + Int2String(DepthMarketData->AskPrice5) + "," +Int2String(DepthMarketData->BidPrice5) + "," +
            Int2String(DepthMarketData->AskVolume5) + "," +Int2String(DepthMarketData->BidVolume5) + "," +
            Int2String(DepthMarketData->AveragePrice) + "," +Int2String(DepthMarketData->ClosePrice) + "," +Double2String(DepthMarketData->CurrDelta)+ ",'" +
            DepthMarketData->ExchangeID + "','" + DepthMarketData->ExchangeInstID + "'," + Int2String(DepthMarketData->HighestPrice) + "," +
            Int2String(DepthMarketData->LowestPrice) + "," +Int2String(DepthMarketData->UpperLimitPrice) + "," +
            Int2String(DepthMarketData->LowerLimitPrice) + "," +Int2String(DepthMarketData->OpenInterest) + "," +
            Int2String(DepthMarketData->OpenPrice) + "," +Int2String(DepthMarketData->PreClosePrice) + "," +
            Double2String(DepthMarketData->PreDelta) + "," + Int2String(DepthMarketData->PreOpenInterest) + "," +
            Int2String(DepthMarketData->PreSettlementPrice) + "," + Int2String(DepthMarketData->Volume) +
            ");";

    if(tmpTime.isInTradeTime() == true)
    {
        //res = mysql_query(&m_mysql, sq.c_str());
        QuerySQL(sq);
    }
    //return (bool)res;
    return;
}


//bool CMySQL_Api::IsConnect()
//{
//    if( !&m_mysql )
//    {
//        return false;
//    }
//    else
//    {
//        return true;
//    }
//}

//int CMySQL_Api::Testing()
//{
//    string sql = "insert into ag1409 (InstrumentID) values ('java1');";
//    int res = mysql_query(&m_mysql, sql.c_str());
//    return res;
//}


//char *CMySQL_Api::String2CharPt(string inputData)
//{
//    string str=inputData;
//    char * pstr=new char [str.length()+1];
//    return pstr;
//}

std::string CMySQL_Api::Int2String(int inputData)
{
    std::string res = "0";
    if( inputData < -1147480000)
    {
        return res;
    }
    int n = inputData;
    QString qs = QString::number(n, 10);
    res = qs.toStdString();
    return res;
}

std::string CMySQL_Api::Double2String(double inputData)
{
    std::string res = "0";
    if( inputData < -1147480000 )
    {
        return res;
    }
    double num = inputData;
    QString data = QString("%1").arg(num);
    res = data.toStdString();
    return res;
}

void CMySQL_Api::windowInit()
{
    win_db = QSqlDatabase::addDatabase(AShareFun::GetDBSQLDriver());

    win_db.setHostName(QString::fromStdString( m_address) );
    win_db.setDatabaseName(QString::fromStdString( m_database) );
    win_db.setPort( AShareFun::GetDBPortNum() );
    win_db.setUserName( QString::fromStdString(m_user) );
    win_db.setPassword(QString::fromStdString( m_passwd) );

    if (!win_db.open())
    {
        m_isConnect = false;
        qDebug() << "Failed to connect to root mysql admin";
    }
    else
    {
        m_isConnect = true;
        std::cout<<"succeed!"<<std::endl;
    }
}

void CMySQL_Api::linuxInit()
{
#ifdef Q_OS_LINUX
    mysql_init(&m_mysql);
    mysql_real_connect(&m_mysql, m_address.c_str(), m_user.c_str(),
                       m_passwd.c_str(), m_database.c_str(), m_port, NULL, 0);
#endif
}

bool CMySQL_Api::QuerySQL(std::string sql)
{
#ifdef Q_OS_WIN
    bool resTest = win_db.isOpen();
    QSqlQuery tmpQuery(win_db);
    tmpQuery.exec(QString::fromStdString(sql));
//    if(!win_db.open())
//    {
//        return win_query.exec( QString::fromStdString(sql) );
//    }

//    QSqlQuery myQuery(db);
//    if(!myQuery.exec(sqlcmd)){
//    qDebug() << "Database Error: When excute \"" << sqlcmd << "\"";
//    db.close();
//    return QSqlQuery();
    //    while (win_query.next()) {
    //        QString name =win_query.value(6).toString();
    //        int salary = win_query.value(0).toInt();
    //        qDebug() << name << salary;
    //    }
#else
    bool res = mysql_query(&m_mysql, sql.c_str());
    return (bool)res;
#endif
    return false;
}


