#ifndef ASTRUCT_H
#define ASTRUCT_H

// 通用包含
#include <QStringList>
#include <QString>

// 分平台包含
#ifdef Q_OS_LINUX
// linux
#include "inc/Ctp/linux/ThostFtdcMdApi.h"
#include "inc/Ctp/linux/ThostFtdcTraderApi.h"
#include "inc/Ctp/linux/ThostFtdcUserApiStruct.h"
#include "inc/Ctp/linux/ThostFtdcUserApiStruct.h"
#endif

#ifdef Q_OS_WIN
// win
#include "inc/Ctp/windows/ThostFtdcMdApi.h"
#include "inc/Ctp/windows/ThostFtdcTraderApi.h"
#include "inc/Ctp/windows/ThostFtdcUserApiStruct.h"
#include "inc/Ctp/windows/ThostFtdcUserApiStruct.h"
#endif


#ifndef MDINFO
typedef struct MdInfo
{
    // 构造函数
public:
    MdInfo(){
        m_Front_addr = "tcp://22.66.235.70:61213";    //222.66.235.70:61214
        m_Broker_id = "1026";
        Investor_id = "00000035";
        Password = "123456";
        m_ppInstrumentID.append("ag1412");
    }
    // 私有变量
public:
    QString m_Front_addr;
    QString m_Broker_id;
    QString    Investor_id;
    QString    Password;
    QStringList m_ppInstrumentID;
    char* QString2CharPt(QString inpData)
    {
        char* ch = "";
        QByteArray ba = inpData.toLatin1();
        ch = ba.data();
        return ch;
    }

    // 获取函数
public:
    char * GetFrontAddr()
    {
        char* res = QString2CharPt(m_Front_addr);
        return res;
    }


} MDINFO;
#endif // MDINFO


#ifndef TRINFO
typedef struct TrInfo
{
public:
    TrInfo(){
        Front_addr = "tcp://222.66.235.70:61205";    //222.66.235.70:61206
        Broker_id = "1026";				////
        Investor_id = "00000035";			//
        Password = "123456";			////
        Direction = THOST_FTDC_D_Sell;
        Limit_price = 60000;
        Instrument_ID = "ag1412";
    }

private:
    QString  Front_addr;
    QString    Broker_id;
    QString    Investor_id;
    QString    Password;
    QString Instrument_ID;
    TThostFtdcDirectionType	Direction;	//
    TThostFtdcPriceType	Limit_price; ////
    char* QString2CharPt(QString inpData)
    {
        char* ch = "";
        QByteArray ba = inpData.toLatin1();
        ch = ba.data();
        return ch;
    }
public:

} TRINFO;
#endif



#endif // ASTRUCT_H
