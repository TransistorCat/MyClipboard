#include "systemtrayicon.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QtWidgets>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // a.setStyle(QStyleFactory::create("fusion"));
     // a.setAttribute(Qt::AA_DontUseNativeMenuBar, false);
    // Service s;
    // QVector<Data> datas;
    // s.start();
    // s.readClipboard();
    // datas=s.queryDB();
    
    SystemTrayIcon w;
    QIcon icon(":/image/icon.ico");

    // w.setWindowIcon(icon);
    a.setWindowIcon(icon);
    a.exec();
}
