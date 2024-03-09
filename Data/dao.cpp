#include "dao.h"
#include "qsqldatabase.h"

bool Dao::Init(){
    QSqlDatabase database;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("user.db");
        database.open();
    }
    if (database.isOpen()){
        qDebug()<<"mydb is open";
        database.close();
        return true;
    }
    return false;
}
