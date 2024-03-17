#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemtrayicon.h"
#include "service.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Service *service;
    SystemTrayIcon *systemTrayIcon;
    Filter *filter;
    void insertTableItem();

private slots:
    void closeEvent(QCloseEvent *event) override;


    // void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_refreshToolButton_clicked();
    void on_findToolButton_clicked();
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_timeTreeWidget_itemSelectionChanged();
    void on_typeTreeWidget_itemSelectionChanged();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
};
#endif // MAINWINDOW_H
