#ifndef ASHAREFUN_H
#define ASHAREFUN_H

#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QDir>
#include <QDebug>
#include <QTextCodec>
#include <QVector>


class AShareFun
{
public:
    AShareFun();

    static bool ALWriteLogFile(char* inpData);
    static QString ALGetAppPath(void);
    static void ALDebug(char* inpData);
    static void ALSleep(int inpTime);

//private:

    QVector<QString> ReadFile(char* filepath);
    void ReadConfig();

public:

    inline static char* GetFrontAddr(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_FrontAddress.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetBrokerID (){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_BrokerID.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetInvestorID(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_InvestorID.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetPassword(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_Password.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    //////
    inline static char* GetMkFrontAddr(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_MkFrontAddress.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetMkBrokerID (){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_MkBrokerID.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetMkInvestorID(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_MkInvestorID.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetMkPassword(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_MkPassword.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char** GetMkInstrumentID()
    {
//        QByteArray tmpStr = ConfigMkInstrumentID.toLatin1();
//        char* tmpChar = tmpStr.data();
//        return &tmpChar;
        ///
        char *ppInstrumentID[] = {"i1505"};
        return &ppInstrumentID[0];
    };
    inline static int GetMkInstrumentIDNum()
    {
        return 1;
    };
    //
    inline static char* GetDBHostName(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_DBHostName.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static int GetDBPortNum(){
        AShareFun* a = new AShareFun();
        int tmpStr = a->m_DBPortNum.toInt();
        return tmpStr;
    };
    inline static char* GetDBSQLDriver(){
        return "QMYSQL";
    };
#ifdef Q_OS_WIN
    inline static char* GetDBAddress(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_DBAddress.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
#else
    inline static char* GetDBAddress(){ return "localhost"; };
#endif
    inline static char* GetDBPassword(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_DBPassword.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };
    inline static char* GetDBName(){
        AShareFun* a = new AShareFun();
        QByteArray tmpStr = a->m_DBName.toLatin1();
        char* tmpChar = tmpStr.data();
        return tmpChar;
    };

private:
    QString m_FrontAddress;
    QString m_BrokerID;
    QString m_InvestorID;
    QString m_Password;
    ///
    QString m_MkFrontAddress;
    QString m_MkBrokerID;
    QString m_MkInvestorID;
    QString m_MkPassword;
    QVector<QString> m_MkInstrumentIDVec;
    QString m_MkInstrumentID;
    ///
    QString m_DBHostName;
    QString m_DBPortNum;
    QString m_DBAddress;
    QString m_DBPassword;
    QString m_DBName;
};



#endif // ASHAREFUN_H
