#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QtWidgets>

class SystemTrayIcon : public QWidget {
public:
    SystemTrayIcon(QWidget *parent) {
        this->parent=parent;
        createTrayIcon(parent);
        connect(trayIcon, &QSystemTrayIcon::activated, this, &SystemTrayIcon::iconActivated);
    }

private:
    void createTrayIcon(QWidget *parent);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    QWidget *parent;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
};




#endif // SYSTEMTRAYICON_H
