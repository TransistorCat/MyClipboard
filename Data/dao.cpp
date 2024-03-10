#include "dao.h"

#include "QSqlQuery"
#include "QSqlTableModel"

bool Dao::init(){

    //create and connect db
    // if (QSqlDatabase::contains("qt_sql_default_connection"))
    // {
    //     db = QSqlDatabase::database("qt_sql_default_connection");
    // }
    // else
    // {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./user.db");

    // }
    if (!db.open()){
        qDebug()<<"Error: mydb can`t open";

        return 1;
    }

    //create data table
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

bool Dao::insertOneData(Data& data)
{
    QSqlTableModel model;
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

