#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemtrayicon.h"
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
    SystemTrayIcon *systemTrayIcon;

private slots:
    void closeEvent(QCloseEvent *event) override;


    // void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

};
#endif // MAINWINDOW_H
