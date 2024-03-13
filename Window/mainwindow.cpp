#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->horizontalLayout.
    systemTrayIcon = new SystemTrayIcon(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    event->ignore(); // 忽略窗口关闭事件
    hide(); // 隐藏窗口
}


