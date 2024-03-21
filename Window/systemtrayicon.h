#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include "datapanel.h"
#include <QtWidgets>

class SystemTrayIcon : public QWidget {
public:
    SystemTrayIcon() {
        service=new Service;
        service->start();
        datapanel=new DataPanel(nullptr,service);

        datapanel->setService(service);
        datapanel->show();
        createTrayIcon();

        connect(trayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::iconActivated);
    }

private:
    void createTrayIcon();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    DataPanel *datapanel;
    Service *service;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};




#endif // SYSTEMTRAYICON_H
