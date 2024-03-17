#ifndef DAO_H
#define DAO_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "qsqldatabase.h"
enum class Type:int{
    all,text,image,file
};

enum class Time:int{
    all,today,yesterday,week,custom
};



struct Data
{
    Data(const QString &data,Type type):content(data),type(type){};
    Data(int id,QString& time,QString& content,Type type,const QString &tap=""):id(id),createAt(time),content(content),type(type),tap(tap){};

    int id;
    Type type;
    QString createAt;
    QString content;
    QString tap;
};

struct Filter{
    Filter();
    enum Time time;
    enum Type type;
    QDate startTime;
    QDate endTime;
    QString content;
    QString tap;
};

class Dao{
public:
    bool init (const QString& DatabaseName="user.db");
    bool insertOneData(const Data&);
    bool deleteOneData();
    unsigned int query(QVector<Data>&, int, int, Filter &);
    // bool query(QVector<Data>&,);
    bool close(const QString &DatabaseName);
private:
    QSqlDatabase db;
};



#endif // DAO_H
