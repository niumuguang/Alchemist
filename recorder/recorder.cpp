#include "ctpmdspi.h"
#include "recorder.h"

//nclude <C:/Users/Lio/Documents/GitHub/Alchemist/Alchemist/inc/Ctp/windows/ThostFtdcMdApi.h>
//#include "../Alchemist/inc/Ctp/windows/ThostFtdcMdApi.h"
//#include <C:/Users/Lio/Documents/GitHub/Alchemist/Alchemist/asharefun.h>
#include "../Alchemist/asharefun.h"



MarketRecorder::MarketRecorder(QObject *parent)
{

}

void MarketRecorder::run()
{
    //pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(".\\",false);
    pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();
    CThostFtdcMdSpi* pUserSpi = new CtpMdSpi(pUserApi);

    pUserApi->RegisterSpi(pUserSpi);
    pUserApi->RegisterFront(AShareFun::GetMkFrontAddr());
    pUserApi->Init();
    pUserApi->Join();
    cerr << "Start MySQL test" << endl;
}

void MarketRecorder::stop()
{
    pUserApi->Release();
}

void MarketRecorder::TestConnect()
{

}


DatabaseRecorder::DatabaseRecorder()
{

}

void DatabaseRecorder::testConnect()
{
    testApi = new CMySQL_Api();
}
