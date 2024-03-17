#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    service=new Service;
    service->start();
    filter=new Filter;
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
     ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

     // insertTableItem(service->queryDB());
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

void MainWindow::insertTableItem()
{
    ui->tableWidget->setRowCount(0);
    int onePageItemN=50;
    auto n =ui->spinBox->value()-1;
    auto result =service->queryDB(n*onePageItemN,(n+1)*onePageItemN,*filter);
    ui->spinBox->setMaximum(result.rowCount/onePageItemN+1);
    ui->label->setText("/ "+QString::number(result.rowCount/onePageItemN+1));
    QTableWidgetItem *item[3];

    for (int i=0;i<result.datas.size();++i){
        int nCount=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(nCount);
        item[0]=new QTableWidgetItem(QString("%1").arg(n*onePageItemN+i+1));
        ui->tableWidget->setItem(i,0,item[0]);

        item[1]=new QTableWidgetItem(result.datas[i].createAt);
        ui->tableWidget->setItem(i,1,item[1]);
        item[2] = new QTableWidgetItem();

        if(result.datas[i].type == Type::image) {
            auto pixmap = QPixmap(result.datas[i].content);
            auto icon = QIcon(pixmap);
            item[2]->setIcon(icon);
        }
            item[2]->setText(result.datas[i].content); // 非图像类型直接设置文本


        ui->tableWidget->setItem(i, 2, item[2]);
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
    // Filter filter;
    // ui->tableWidget->setRowCount(0);
    // auto result =ui->spinBox->value()-1;
    // auto r =service->queryDB(result*100,(result+1)*100,filter);
    // insertTableItem(r.datas);
}


void MainWindow::on_findToolButton_clicked()
{
    filter->content=ui->lineEdit->text();
    ui->spinBox->setValue(1);
    insertTableItem();
}

std::string generateRandomComment() {
    // 可以根据需要修改评论的内容或者长度
    std::vector<std::string> comments = {
        "This is a great product!",
        "I love this!",
        "Not bad.",
        "Could be better.",
        "Amazing!",
        "Terrible...",
        "It's okay.",
        "I'm not impressed.",
        "Would recommend!",
        "Don't waste your money."
    };

    // 生成随机评论
    int index = rand() % comments.size();
    return comments[index];
}

// void make(){
//     // 设置随机数种子
//     srand(time(nullptr));

//     // 生成一万条随机评论

void MainWindow::on_pushButton_clicked()
{
    QList<QTableWidgetItem *> selectedItems = ui->tableWidget->selectedItems();
    QString text;
    QString filePath=selectedItems[0]->text();
    QFile file(filePath);
    if(selectedItems.size()==1&&file.exists()){
        //把文件拷贝到剪贴板
    }
    // 将选中的项的文本添加到字符串中
    for (int i = 0; i < selectedItems.size(); ++i) {
        text += selectedItems[i]->text();
        if (i < selectedItems.size() - 1)
            text += "\t"; // 添加制表符，以便在粘贴时保留列的分隔符
    }

    // 将文本复制到剪贴板
    QApplication::clipboard()->setText(text);
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{


    insertTableItem();
}


void MainWindow::on_timeTreeWidget_itemSelectionChanged()
{
    auto selectItem=ui->timeTreeWidget->selectedItems();
    auto text=selectItem[0]->text(0);
    qDebug()<<text;
    if (text=="today"){
        filter->time=Time::today;
    }
    if (text=="yesterday"){
        filter->time=Time::yesterday;
    }
    if (text=="week"){
        filter->time=Time::week;
    }
    if (text=="custom"){
        filter->time=Time::today;
    }
    if (text=="all"){
        filter->time=Time::all;
    }
insertTableItem();
}


void MainWindow::on_typeTreeWidget_itemSelectionChanged()
{
    auto selectItem=ui->typeTreeWidget->selectedItems();
    auto text=selectItem[0]->text(0);
    qDebug()<<text;
    if (text=="text"){
        filter->type=Type::text;
    }
    if (text=="image"){
        filter->type=Type::image;
    }
    if (text=="file"){
        filter->type=Type::file;
    }
    if (text=="all"){
        filter->type=Type::all;
    }
    insertTableItem();
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    filter->content=arg1;
    ui->spinBox->setValue(1);
    insertTableItem();
}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)

{
    QFile file(item->text());
    if(file.exists()){
        QString filePath = item->text();
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}

