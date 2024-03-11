#ifndef DAO_H
#define DAO_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "qsqldatabase.h"

class Data
{
public:
    Data(const QString &data):content(data){};
    Data(int id,QString& time,QString& data):id(id),created_at(time),content(data){};

    int id;
    QString created_at;
    QString content;
};

class Dao{
public:
    bool init (const QString& DatabaseName="user.db");
    bool insertOneData(const Data&);
    bool deleteOneData();
    bool query(QVector<Data>&,int,int);
    bool close(const QString &DatabaseName);
private:
    QSqlDatabase db;
};



#endif // DAO_H
