#include "service.h"
#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QApplication>

bool Service::readClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();

    // 监听剪贴板内容改变信号
    QObject::connect(clipboard, &QClipboard::dataChanged, [&]() {
        QString clipboardText = clipboard->text();
        dao.insertOneData(Data(clipboardText));
        qDebug() << "Clipboard content changed:" << clipboardText;
    });
    return true;
}

bool Service::start()
{
    if(!dao.init()){
        qDebug()<<"Error: failed init dao";
        return false;
    }
    return true;
}
