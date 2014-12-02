#ifndef DIALOGACTOR_H
#define DIALOGACTOR_H

#include <QDialog>

namespace Ui {
class DialogActor;
}

class DialogActor : public QDialog
{
    Q_OBJECT

public:
    explicit DialogActor(QWidget *parent = 0);
    ~DialogActor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogActor *ui;
};

#endif // DIALOGACTOR_H
