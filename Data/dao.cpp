#include "dao.h"

#include "QSqlQuery"
#include "QSqlTableModel"

bool Dao::init(const QString &DatabaseName){

    //create and connect db

    db = QSqlDatabase::addDatabase("QSQLITE",DatabaseName);
    db.setDatabaseName(DatabaseName);


    if (!db.open()){
        qDebug()<<"Error: mydb can`t open";

        return 1;
    }

    //create data

    QString create_sql = "CREATE TABLE IF NOT EXISTS data("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ,"
                         "data VARCHAR(5000) NOT NULL)";
    QSqlQuery query(db);
    if (!query.exec(create_sql)) {
        qDebug() << "Error: failed to create table";
        return 1;
    } else {
        qDebug() << "Table created successfully";

    }


    return 0;
}

bool Dao::insertOneData(const Data &data)
{
    QSqlTableModel model(nullptr, db);


    model.setTable("data");
    model.insertRows(model.rowCount(), 1);

    model.setData(model.index(model.rowCount()-1, 2), data.content);
    if(!model.submitAll()){
        qDebug()<<"Error: fail insert ("<<data.content<<")"<<model.lastError().text();

        // qDebug()<<
        return 1;
    }
    return 0;
}

bool Dao::query(QVector<Data> &datas, int startRow, int n)
{
    QSqlTableModel model(nullptr, db);
    model.setTable("data");
    if (!model.select()) {
        qDebug() << "Failed to execute query";
        return false;
    }

    int rowCount = model.rowCount();
    if (startRow >= rowCount) {
        qDebug() << "Start row exceeds row count"<<rowCount;
        return false;
    }
    int fetchCount = std::min(n, rowCount- startRow);
    QString filter = QString("rowid BETWEEN %1 AND %2").arg(startRow).arg(startRow + fetchCount);

    model.setFilter(filter);
    model.select();

    for (int i=0;i<fetchCount+1;++i){
        QSqlRecord record = model.record(i);
        int id=record.value(0).toInt();
        QString created_at=record.value(1).toString();
        QString content=record.value(2).toString();
        Data data(id,created_at,content);
        datas.push_back(data);
    }
    return 0;
}

bool Dao::close(const QString &DatabaseName)
{
    db = QSqlDatabase(); //make DatabaseName unuse
    db.close();
    QSqlDatabase::removeDatabase(DatabaseName);
    return 0;
}

