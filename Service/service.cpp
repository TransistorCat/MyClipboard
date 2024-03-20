#include "service.h"
#include "qimagereader.h"
#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QApplication>
QByteArray lastClipboardData;
bool Service::readClipboard(QClipboard *clipboard)
{

    // 监听剪贴板内容改变信号
    const QMimeData *mimeData = clipboard->mimeData();
    QString clipboardText = clipboard->text();
    QFile file(clipboardText);
    QImageReader reader(clipboardText);
    if (mimeData->hasImage()) {
        // 从剪贴板中获取图片
        QImage image = qvariant_cast<QImage>(mimeData->imageData());
        QByteArray currentData = mimeData->data("image/png");
        QDir currentDir = QDir::current();
        QString currentPath = currentDir.absolutePath();
        QString saveDir=currentPath+"/Images/";
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString savePath = saveDir + timestamp + ".png"; // 替换为您想要保存的路径和文件格式
        QDir dir(saveDir);
        if (!dir.exists()) {
            if (!dir.mkpath("./")) {
                qDebug() << "Failed to create directory";
                return false;
            }
        }
        if (currentData == lastClipboardData) {
            return false;
        } else {
            lastClipboardData = currentData;
        }
        // 保存图片到指定路径
        if (!image.save(savePath)) {
            qDebug() << "Failed to save image";
        } else {
            qDebug() << "Image saved successfully";
        }
        dao.insertOneData(Data(savePath,Type::image));
        // 创建一个标签用于显示图片

    }else if(file.exists()&&reader.canRead()){
        dao.insertOneData(Data(clipboardText,Type::image));
        qDebug() << "image save:" << clipboardText;
    }
    else if(file.exists()){
        dao.insertOneData(Data(clipboardText,Type::file));
        qDebug() << "FileDir save:" << clipboardText;
    }else{
        dao.insertOneData(Data(clipboardText,Type::text));
        qDebug() << "Clipboard content changed:" << clipboardText;
    }

    return true;
}


QueryResult Service::queryDB( int startRow, int n, Filter &filters)
{
    QueryResult q;
    q.rowCount=dao.query(q.datas,startRow,n,filters);
    return q;
}


bool Service::start()
{
    if(!dao.init()){
        qDebug()<<"Error: failed init dao";
        return false;
    }
    QClipboard *clipboard = QApplication::clipboard();

    QObject::connect(clipboard, &QClipboard::dataChanged, [&]() {
        readClipboard(clipboard);
    });
    return true;
}
