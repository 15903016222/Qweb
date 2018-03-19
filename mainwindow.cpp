#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //实例化进度条
    this->progressbar = new QProgressBar;
    ui->statusBar->addWidget(progressbar);
    this->initMainPage();
    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(setUrlSlot(QUrl)));
    connect(ui->webView, SIGNAL(titleChanged(QString)), this, SLOT(settitleSlot(QString)));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(browserWebSlot()));
    connect(ui->webView, SIGNAL(loadProgress(int)), this->progressbar, SLOT(setValue(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(deleteprogressbarSlot(bool)));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(sourceCodeSlot()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(setMainpageSlot()));
//    connect(ui->viewsourcecodeAction, SIGNAL(triggered()), this, SLOT(sourceCodeSlot()));
//    connect(ui->setmainpageAction, SIGNAL(triggered()), this, SLOT(setMainpageSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//网页更改修改url输入框
void MainWindow::setUrlSlot(QUrl url)
{
    ui->lineEdit->setText(url.toString());
}

//网页更改修改标题
void MainWindow::settitleSlot(QString title)
{
    this->setWindowTitle(title);
}

//LineEdit回车刷新网页
void MainWindow::browserWebSlot()
{
    ui->webView->load(QUrl(ui->lineEdit->text()));
}

//进度条结束后状态栏显示Load Finish 5秒
void MainWindow::deleteprogressbarSlot(bool ok)
{
    if(ok)
    {
        delete this->progressbar;
        this->progressbar = NULL;
        ui->statusBar->showMessage("Load Finish", 5*1000);
    }
}

//网页显示源代码
void MainWindow::sourceCodeSlot()
{
    QString context = ui->webView->page()->currentFrame()->toHtml();
    this->hide();
    Dialog *dialog = new Dialog;
    dialog->setWebSource(context);
    dialog->show();
}

//设置主页
void MainWindow::setMainpageSlot()
{
    QString filename = "mainpage.ini";
    QFile *file = new QFile;
    file->setFileName(filename);
    bool ok = file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<"mainpage="+ui->lineEdit->text();
        file->close();
        delete file;
        file = NULL;

        QMessageBox::information(this, "information", "set main page success");
    }
    else
    {
        qDebug()<<"set fail";
    }
}

//浏览器初始化
void MainWindow::initMainPage()
{
    QString filename = "mainpage.ini";
    QFile *file = new QFile;
    file->setFileName(filename);
    bool ok = file->open(QIODevice::ReadOnly);
    if(ok)
    {
        QTextStream in(file);
        ui->webView->load(QUrl(in.readLine().split("=").at(1)));
        file->close();
        delete file;
        file = NULL;
    }
    else
    {
        QMessageBox::information(this, "Error Message", "init main page error:"+file->errorString());
        return;
    }
}