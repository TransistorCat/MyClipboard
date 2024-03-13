#include "mainwindow.h"
#include "service.h"
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
    Service s;
    s.start();
    // s.readClipboard();


    MainWindow w;
    QIcon icon(":/image/icon.svg");

    w.setWindowIcon(icon);
    w.show();
    a.exec();
}
