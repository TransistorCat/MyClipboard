#ifndef DATAPANEL_H
#define DATAPANEL_H

#include "customtimepanel.h"
#include "qtablewidget.h"
#include "service.h"

#include <QMainWindow>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui {
class DataPanel;
}
QT_END_NAMESPACE

class DataPanel : public QMainWindow
{
    Q_OBJECT

public:
    DataPanel(QWidget *parent = nullptr, Service *service=nullptr);
    void setService(Service *);
    void insertTableItem();
    ~DataPanel();

private:
    Ui::DataPanel *ui;
    CustomTimePanel *timePanel;
    Service *service;
    Filter *filter;


private slots:
    void closeEvent(QCloseEvent *event) override;


    // void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    // void on_refreshToolButton_clicked();
    void on_findToolButton_clicked();
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_timeTreeWidget_itemSelectionChanged();
    void on_typeTreeWidget_itemSelectionChanged();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_timeTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
};
#endif // DATAPANEL_H
