void on_QB_QueryOrder_clicked();
void on_QB_LogoutCTP_clicked();
void on_StartTradeThread_clicked();
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "altraderthread.h"

#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include "../dealer/dealer.h"
#include <QVector>
#include "../Alchemist/inc/Ctp/windows/ThostFtdcUserApiStruct.h"
#include "../recorder/recorder.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_QB_LoginCTP_clicked();

    void on_QB_LogoutCTP_clicked();

    void on_QB_SettlementConfirm_clicked();

    void on_QB_QueryAccount_clicked();

    void on_QCB_OpenClose_currentIndexChanged(int index);

    void on_QCB_BuySell_currentIndexChanged(int index);

    void on_QB_SendOrder_clicked();

    void on_QB_RevokeOrder_clicked();

    void on_QB_QueryOrder_clicked();

    void on_QTA_ResultTable_clicked();

private:
    Ui::MainWindow *ui;
    void on_QB_DBTest_clicked();
    Dealer* m_traderThread;
    //QComboBox *cbo_OpenClose;
    int m_OpenClose; // 0 Open,  1 Close;
    int m_BuySell; // 0 Buy,  1 Sell;
    QLabel* first_statusLabel;
    //Recorder m_recorder;
};

#endif // MAINWINDOW_H
