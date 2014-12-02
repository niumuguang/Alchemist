#ifndef CMYSQL_API_H
#define CMYSQL_API_H

#include "string.h"

#include <QtSql/qsql.h>
#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqldriver.h>

#ifdef Q_OS_LINUX
    #include <mysql/mysql.h>
#endif

//#include "../MySQL/include/mysql.h"
#include <iostream>
//#include "../../Alchemist/inc/Ctp/windows/ThostFtdcUserApiStruct.h"
#include "../Alchemist/inc/Ctp/windows/ThostFtdcUserApiStruct.h"

#include <QtSql>

using namespace std;

class CMySQL_Api
{
public:
    CMySQL_Api();
    CMySQL_Api(std::string ipaddress, int port, std::string username,
               std::string password, std::string database);

    ~CMySQL_Api();

private:
    std::string m_user;
    std::string m_passwd;
    std::string m_database;
    std::string m_table;
    std::string m_address;
    int m_port;
    bool m_isConnect;
    //MYSQL m_mysql;

    QSqlDatabase win_db; // window下数据库对象
    QSqlQuery win_query;

#ifdef Q_OS_LINUX
     MYSQL m_mysql;
#endif


public:
    //bool IsConnect();
    //int Testing();
    void WriteMarket(CThostFtdcDepthMarketDataField *DepthMarketData);

    //bool WriteDB(CThostFtdcDepthMarketDataField* DepthMarketData);
    //char* String2CharPt(string inputData);
    std::string Int2String(int inputData);
    std::string Double2String(double inputData);

private:
    void windowInit();
    void linuxInit();
    bool QuerySQL(std::string sql);

    std::string OrganizeMarketData2Sql(CThostFtdcDepthMarketDataField *pDepthMarketData);
};

#endif // CMYSQL_API_H
