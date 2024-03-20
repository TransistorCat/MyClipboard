#include "systemtrayicon.h"

// SystemTrayIcon::SystemTrayIcon() {}

void SystemTrayIcon::createTrayIcon() {
    trayIconMenu = new QMenu();
    trayIconMenu->addAction("DataPanel",datapanel,&QWidget::show);
    trayIconMenu->addAction("More");
    trayIconMenu->addSeparator();
    trayIconMenu->addAction("Quit", qApp, &QCoreApplication::quit);

    trayIcon = new QSystemTrayIcon(datapanel);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/image/icon.svg"));
    trayIcon->setVisible(true);
}

void SystemTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch(reason)
    {
    //双击托盘显示窗口
    // case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::Trigger:
    {
        datapanel->show();
        qDebug()<<"Trigger";
        break;
    }
    case QSystemTrayIcon::Context:
        trayIconMenu->popup(QCursor::pos());
    default:
        qDebug()<<reason;
        break;
    }
}

