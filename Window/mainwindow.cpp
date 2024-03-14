#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->timeTreeWidget->topLevelItem(0)->setSelected(true);
     ui->typeTreeWidget->topLevelItem(0)->setSelected(true);
     ui->tapTreeWidget->topLevelItem(0)->setSelected(true);
    // ui->horizontalLayout.
    // QTreeWidget *treeWidget=ui->treeWidget;
    // QTreeWidgetItem *item = ui->treeWidget->itemAt(0,0);


    // // 创建按钮
    // QPushButton *button = new QPushButton(treeWidget);
    // button->setText("Button");
    // treeWidget->setItemWidget(item, 0, button);

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



// void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
// {
//     ui->lineEdit->setText(item->text(column));
//     if(item->parent()!=nullptr&&item->parent()->text(0)=="time"){
//         auto time=item->parent();
//         qDebug()<<time->childCount();
//         // 遍历所有项目，将除了当前被勾选的项目外的其他项目的勾选状态设置为未勾选
//         for (int i = 0; i < time->childCount(); ++i) {
//             // qDebug()<<i;
//             QTreeWidgetItem *currentItem =time->child(i);
//             qDebug()<<currentItem->text(0)<<item->text(0);
//             if (currentItem->text(0)!=item->text(0)) {
//                 // time->child(i)->setBackground(0,QColor(Qt::white));
//                 time->child(i)->setSelected(false);
//             }else{
//                 time->child(i)->setSelected(true);
//             }
//         }
//         // item->setBackground(column,QColor(85,170,255));
//         // item->setCheckState(0,Qt::CheckState::Checked);
//     }
// }
