#include "asharefun.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_traderThread = new Dealer();
    m_OpenClose = 0;
    m_BuySell = 0;

    first_statusLabel = new QLabel;
    first_statusLabel->setText(tr("Unlogin"));

    //first_statusLabel->setMinimumSize(10,20);
    first_statusLabel->setFrameShape(QFrame::WinPanel);
    first_statusLabel->setFrameShadow(QFrame::Raised);
    this->ui->statusbar->addWidget(first_statusLabel);

    QValidator *validatorPrice=new QIntValidator(0,50000,this); // 0-100 only accept number
    this->ui->QED_Price->setValidator(validatorPrice);
    QValidator *validatorVolume=new QIntValidator(0,100,this); // 0-100 only accept number
    this->ui->QED_Volume->setValidator(validatorVolume);

    this->setMinimumSize(632,341);
    this->setMaximumSize(632,341);

    connect(this->ui->QTA_ResultTable,SIGNAL(Clicked(QModelIndex)),this,SLOT(on_QTA_ResultTable_clicked(QModelIndex)));
    connect(this->ui->QB_DBTest, SIGNAL(Clicked(QModelIndex)), this, SLOT(on_QB_DBTest_clicked(QModelIndex)));
    //登录前灰显
    this->ui->QB_LogoutCTP->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_QB_LogoutCTP_clicked()
{
    m_traderThread->Logout();
    m_traderThread = new Dealer();
}

void MainWindow::on_QB_LoginCTP_clicked()
{
    MarketRecorder* testMd = new MarketRecorder();
    testMd->start();
    //m_recorder.testConnect();
//    m_traderThread->start();
//    if( m_traderThread->HasLogin() == true )
//    {
//        // todo 状态栏更新登录状态
//        this->ui->QB_LogoutCTP->setDisabled(true);
//    }
}

void MainWindow::on_QB_SettlementConfirm_clicked()
{
    m_traderThread->ConfirmSettlement();
    AShareFun::ALDebug("完毕");
}

void MainWindow::on_QB_QueryAccount_clicked()
{
    CThostFtdcTradingAccountField res = m_traderThread->QueryAccount();
    AShareFun::ALDebug("完毕");
}

void MainWindow::on_QCB_OpenClose_currentIndexChanged(int index)
{
    m_OpenClose = this->ui->QCB_OpenClose->currentIndex();
}

void MainWindow::on_QCB_BuySell_currentIndexChanged(int index)
{
    m_BuySell = this->ui->QCB_BuySell->currentIndex();
}

void MainWindow::on_QB_SendOrder_clicked()
{
    QString price = this->ui->QED_Price->text();
    QString volume = this->ui->QED_Volume->text();
    int OpenClose = this->ui->QCB_OpenClose->currentIndex();
    int BuySell = this->ui->QCB_BuySell->currentIndex();
    int p = price.toInt();
    int v = volume.toInt();
    m_traderThread->SendOrder(p, v, BuySell, OpenClose);
}

void MainWindow::on_QB_RevokeOrder_clicked()
{
    //m_traderThread->QryOrder();
}

void MainWindow::on_QB_QueryOrder_clicked()
{
    QVector<CThostFtdcOrderField> res;
    res = m_traderThread->QryOrder();
    //this->ui->listWidget
    //QListWidgetItem *aitem = new QListWidgetItem()

    this->ui->QTA_ResultTable->showGrid();//显示格子
    // 整行选中
//    this->ui->QTA_ResultTable->setSelectionBehavior(QAbstractItemView::SelectRows);
//    QStandardItemModel *model = new QStandardItemModel;
//    model->setColumnCount(9);
//    model->setHeaderData(0,Qt::Horizontal,tr("ActiveTime"));
//    model->setHeaderData(1,Qt::Horizontal,tr("ClientID"));
//    model->setHeaderData(2,Qt::Horizontal,tr("CancelTime"));
//    model->setHeaderData(3,Qt::Horizontal,tr("BrokerOrderSeq"));
//    model->setHeaderData(4,Qt::Horizontal,tr("InsertTime"));
//    model->setHeaderData(5,Qt::Horizontal,tr("OrderLocalID"));
//    model->setHeaderData(6,Qt::Horizontal,tr("OrderRef"));
//    model->setHeaderData(7,Qt::Horizontal,tr("OrderStatus"));
//    model->setHeaderData(8,Qt::Horizontal,tr("OrderSubmitStatus"));

//    for(int i=0; i<res.size(); i++)
//    {
//        QStandardItem* item1 = new QStandardItem( tr(res.at(i).ActiveTime) );
//        QStandardItem* item2 = new QStandardItem( tr(res.at(i).ClientID) );
//        QStandardItem* item3 = new QStandardItem( tr(res.at(i).CancelTime) );
//        QStandardItem* item4 = new QStandardItem( res.at(i).BrokerOrderSeq );
//        QStandardItem* item5 = new QStandardItem( tr(res.at(i).InsertTime) );
//        QStandardItem* item6 = new QStandardItem( tr(res.at(i).OrderLocalID) );
//        QStandardItem* item7 = new QStandardItem( tr(res.at(i).OrderRef) );
//        QStandardItem* item8 = new QStandardItem( res.at(i).OrderStatus );
//        QStandardItem* item9 = new QStandardItem( res.at(i).OrderSubmitStatus );
//        QList<QStandardItem*> item;
//        //QString::append(res.at(i).OrderStatus)
//        item << item1 << item2 << item3 << item4 << item5 << item6 << item7 << item8 << item9;
//        model->appendRow(item);
//    }

//    this->ui->QTA_ResultTable->setModel(model);
}

void MainWindow::on_QTA_ResultTable_clicked()
{
    AShareFun::ALDebug("123");
    //m_recorder.testConnect();
}

void MainWindow::on_QB_DBTest_clicked()
{
    // 数据库连接测试
    //m_recorder.testConnect();
}
