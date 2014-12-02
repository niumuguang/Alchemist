#include "dialogactor.h"
#include "ui_dialogactor.h"

DialogActor::DialogActor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogActor)
{
    ui->setupUi(this);
}

DialogActor::~DialogActor()
{
    delete ui;
}

void DialogActor::on_buttonBox_accepted()
{

}
