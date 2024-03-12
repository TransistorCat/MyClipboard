#include "mainwindow.h"
#include "service.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QClipboard>
#include <QDebug>
#include <QMimeData>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Service s;
    s.start();
    // s.readClipboard();


    // MainWindow w;
    // w.show();
    a.exec();
}
