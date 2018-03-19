#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setWebSource(QString context)
{
    ui->textEdit->setPlainText(context);
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    delete ui;
}
