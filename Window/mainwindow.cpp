#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    service=new Service;
    service->start();
    ui->timeTreeWidget->topLevelItem(0)->setSelected(true);
     ui->typeTreeWidget->topLevelItem(0)->setSelected(true);
     ui->tapTreeWidget->topLevelItem(0)->setSelected(true);
     ui->tableWidget->setColumnCount(3);
     QStringList header;
     header<<"no"<<"time"<<"content";
     ui->tableWidget->setHorizontalHeaderLabels(header);
     ui->tableWidget->setColumnWidth(0,25);
     ui->tableWidget->setColumnWidth(1,125);
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
     ui->tableWidget->verticalHeader()->setVisible(false);
     insertTableItem(service->queryDB());
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

void MainWindow::insertTableItem(const QVector<Data> &datas)
{ QTableWidgetItem *item[3];

    for (int i=0;i<datas.size();++i){
        int nCount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0]=new QTableWidgetItem(QString("%1").arg(datas[i].id));
        ui->tableWidget->setItem(i,0,item[0]);

        item[1]=new QTableWidgetItem(datas[i].created_at);
        ui->tableWidget->setItem(i,1,item[1]);

        item[2]=new QTableWidgetItem(datas[i].content);
        ui->tableWidget->setItem(i,2,item[2]);
    }


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

void MainWindow::on_refreshToolButton_clicked(){
// int nCount=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(0);

    insertTableItem(service->queryDB());
}


void MainWindow::on_findToolButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    QString queryString =ui->lineEdit->text();
    insertTableItem(service->queryDB(queryString));
}


void MainWindow::on_pushButton_clicked()
{
    QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
    QString text;

    // 将选中的项的文本添加到字符串中
    for (int i = 0; i < selectedItems.size(); ++i) {
        text += selectedItems[i]->text();
        if (i < selectedItems.size() - 1)
            text += "\t"; // 添加制表符，以便在粘贴时保留列的分隔符
    }

    // 将文本复制到剪贴板
    QApplication::clipboard()->setText(text);
}

