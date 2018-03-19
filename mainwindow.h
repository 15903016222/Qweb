#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebKit/QtWebKit>
#include <QWebView>
#include <QUrl>
#include <QProgressBar>     //使用进度条
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QWebFrame>
#include <QAction>

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
    void setUrlSlot(QUrl);                      //网页更改修改url输入框
    void settitleSlot(QString);                 //网页更改修改标题
    void browserWebSlot();                      //LineEdit回车刷新网页
    void deleteprogressbarSlot(bool);           //进度条结束后状态栏显示Load Finish 5秒
    void sourceCodeSlot();                      //网页显示源代码
    void setMainpageSlot();                     //设置主页

private:
    Ui::MainWindow *ui;
    QProgressBar *progressbar;

    QAction *viewsourcecodeAction;
    QAction *setmainpageAction;

    void initMainPage();                        //浏览器初始化
};

#endif // MAINWINDOW_H
