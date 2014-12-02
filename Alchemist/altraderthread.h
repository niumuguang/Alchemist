/**********************************************************************************
 *
 * ********************************************************************************/
#ifndef ALTRADERTHREAD_H
#define ALTRADERTHREAD_H

#include <QThread>
//#include <C:/Users/Lio/Documents/GitHub/Alchemist/dealer/dealer.h>
#include "../dealer/dealer.h"

class AlTraderThread : public QThread
{
    Q_OBJECT
public:
    AlTraderThread(QObject *parent = 0);
    ~AlTraderThread();
    //AlTraderThread();
    //AlTraderThread(QObject *parent = 0);

    void run();
    void TestConnect();

private:
    Dealer m_Dealer;
    bool m_ThreadSwitch;

};

#endif // ALTRADERTHREAD_H
