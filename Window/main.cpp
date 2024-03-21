#include "systemtrayicon.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QtWidgets>

void customMessageHandler(QtMsgType, const QMessageLogContext &, const QString &) {
    // 空函数，不输出任何内容
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef QT_DEBUG
    // 在 Release 模式下禁用所有 Qt 调试输出
    qInstallMessageHandler(customMessageHandler);
#endif
    // a.setStyle(QStyleFactory::create("fusion"));
     // a.setAttribute(Qt::AA_DontUseNativeMenuBar, false);
    // Service s;
    // QVector<Data> datas;
    // s.start();
    // s.readClipboard();
    // datas=s.queryDB();
    
    SystemTrayIcon w;


    // w.setWindowIcon(icon);

    a.exec();
}
