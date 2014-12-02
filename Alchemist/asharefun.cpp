#include "asharefun.h"
#include <QWaitCondition>
#include <QMutex>
#include <QCoreApplication>
//#include <QApplication>

AShareFun::AShareFun()
{
    //初始化读取配置文件
    ReadConfig();
}

bool AShareFun::ALWriteLogFile(char* inpData)
{
    QString sFilePath = AShareFun::ALGetAppPath() + "\\AlLog.txt";
    //qDebug()<<path<<endl;
    //QString sFilePath = "C:\\ALog.txt";
    QFile file(sFilePath);
    //方式：Append为追加，WriteOnly，ReadOnly
    if (!file.open(QIODevice::Append|QIODevice::Text)) {
        //QMessageBox::critical(NULL, "提示", "无法创建文件");
        return false;
    }
    QTextStream out(&file);
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    //    QTextCodec *codec=QTextCodec::codecForName("gbk");
    //    out.setCodec(codec);

#ifdef Q_OS_LINUX
#endif
#ifdef Q_OS_WIN
#endif
    //char* cTmp = inpData.toLatin1().data();//内存编辑器内查看，此时为GBK编码
    //QString string = QString::fromAscii_helper()
    // QString tmpStr = QStringLiteral(inpData);
    out<< inpData <<endl;
    out.flush();
    file.close();
    return true;
}

QString AShareFun::ALGetAppPath()
{
    QString path;
    QDir dir;
    path=dir.currentPath();
//    QString tmpStr = dir.absolutePath();
//    tmpStr = dir.filePath("test.txt");
//    QString strfile;
//    strfile = QCoreApplication::applicationDirPath();

    //QString strExePath1 = QApplication::applicationDirPath();
    //QString strExePath2  = QCoreApplication::applidcationDirPath();
//    QString strExePath2 = QDir::currentPath();

    return path;
    //QMessageBox::warning(0,"PATH",path,QMessageBox::Yes);//查看路径
}

void AShareFun::ALDebug(char *inpData)
{
    QTextCodec *codec = QTextCodec::codecForName("gb18030");
    QString qstr = codec->toUnicode(inpData);
    qDebug()<<qstr;
}

void AShareFun::ALSleep(int inpTime)
{
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, inpTime);
    mutex.unlock();
}

QVector<QString> AShareFun::ReadFile(char *filepath)
{
    QVector<QString> res;
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QString str(line);
        res.push_back(str);
        qDebug()<< str;
    }
    return res;
}

void AShareFun::ReadConfig()
{
    QString path = "/config.account";
    path = ALGetAppPath() + path;
    //QVector<QString> context =
    QByteArray ba = path.toLatin1();
    char *cstr = ba.data();
    QVector<QString> context = this->ReadFile( cstr );
    for(int i=0; i<context.size(); i++)
    {
        QString tmpStr = context.at(i);
        int re = tmpStr.indexOf("#");
        if(re != -1)
        {
            //QString realStr = tmpStr.left(re);
            tmpStr = tmpStr.left(re);
        }
        int tab = tmpStr.indexOf("\t");
        if( tab != -1)
        {
            QString KeyStr = tmpStr.left(tab);
            QString ValueStr = tmpStr.right(tmpStr.length() - tab );
            ValueStr.replace("\t", "");
            ValueStr.replace("\n", "");
            KeyStr.replace("\t", "");
            KeyStr.replace("\n","");
            ///////////////////////////////////////////////////////
            if(KeyStr == "FrontAddr")
            {
                m_FrontAddress = ValueStr;
            }
            if(KeyStr == "BrokerID")
            {
                m_BrokerID = ValueStr;
            }
            if(KeyStr == "InvestorID")
            {
                m_InvestorID = ValueStr;
            }
            if(KeyStr == "Password")
            {
                m_Password = ValueStr;
            }
            if(KeyStr == "InstrumentID")
            {
                //m_Inss = ValueStr;
            }
            if(KeyStr == "MkFrontAddr")
            {
                m_MkFrontAddress = ValueStr;
            }
            if(KeyStr == "MkBrokerID")
            {
                m_MkBrokerID = ValueStr;
            }
            if(KeyStr == "MkInvestorID")
            {
                m_MkInvestorID = ValueStr;
            }
            if(KeyStr == "MkPassword")
            {
                m_MkPassword = ValueStr;
            }
            if(KeyStr == "MkInstrumentID")
            {
                m_MkInstrumentID = ValueStr;
            }
            if(KeyStr == "DBHostName")
            {
                m_DBHostName = ValueStr;
            }
            if(KeyStr == "DBPortNum")
            {
                m_DBPortNum = ValueStr;
            }
            if(KeyStr == "DBAddress")
            {
                m_DBAddress = ValueStr;
            }
            if(KeyStr == "DBPassword")
            {
                m_DBPassword = ValueStr;
            }
            if(KeyStr == "DBName")
            {
                m_DBName = ValueStr;
            }
            qDebug()<<"ss";
        }
    }
    qDebug()<<"ss";
}
