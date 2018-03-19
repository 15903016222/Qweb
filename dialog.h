
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setWebSource(QString);         //设置文本内容

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

