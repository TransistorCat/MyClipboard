#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QClipboard>
#include <QDebug>
#include <QMimeData>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    // 获取剪贴板实例
    QClipboard *clipboard = QGuiApplication::clipboard();

    // 监听剪贴板内容改变信号
    QObject::connect(clipboard, &QClipboard::dataChanged, [&]() {
        QString clipboardText = clipboard->text();
        qDebug() << "Clipboard content changed:" << clipboardText;
    });
    MainWindow w;
    w.show();
    a.exec();
}
