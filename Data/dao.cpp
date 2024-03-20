#include "dao.h"

#include "QSqlQuery"
#include "QSqlTableModel"

bool Dao::init(const QString &DatabaseName){

    //create and connect db

    db = QSqlDatabase::addDatabase("QSQLITE",DatabaseName);
    db.setDatabaseName(DatabaseName);


    if (!db.open()){
        qDebug()<<"Error: mydb can`t open";

        return false;
    }

    //create data

    QString create_sql = "CREATE TABLE IF NOT EXISTS data("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
                         "content TEXT NOT NULL, "
                         "type INTEGER NOT NULL, "
                         "tap TEXT"
                         ")";

    QSqlQuery query(db);
    if (!query.exec(create_sql)) {
        qDebug() << "Error: failed to create table";
        return false;
    } else {
        qDebug() << "Table created successfully";

    }


    return true;
}

bool Dao::insertOneData(const Data &data)
{
    QSqlTableModel model(nullptr, db);


    model.setTable("data");
    model.insertRows(model.rowCount(), 1);
    model.setData(model.index(model.rowCount()-1, 3), int(data.type));
    model.setData(model.index(model.rowCount()-1, 2), data.content);
    if(!model.submitAll()){
        qDebug()<<"Error: fail insert ("<<data.content<<")"<<model.lastError().text();

        return false;
    }
    return true;
}

// bool Dao::query(QVector<Data> &datas, int startRow, int n,Filter& filters)
// {
//     QSqlTableModel model(nullptr, db);
//     model.setTable("data");
//     if (!model.select()) {
//         qDebug() << "Failed to execute query";
//         return false;
//     }
//     QString filter;
//     switch (filters.time) {
//     case Time::today: {
//         QDateTime currentTime = QDateTime::currentDateTime();
//         QDateTime todayStart = currentTime.date().startOfDay();
//         QDateTime todayEnd = currentTime.date().addDays(1).startOfDay();
//         filter = QString("time >= '%1' AND time < '%2'").arg(todayStart.toString("yyyy-MM-dd hh:mm:ss")).arg(todayEnd.toString("yyyy-MM-dd hh:mm:ss"));
//         break;
//     }
//     case Time::yesterday: {
//         QDateTime currentTime = QDateTime::currentDateTime();
//         QDateTime yesterdayStart = currentTime.date().addDays(-1).startOfDay();
//         QDateTime yesterdayEnd = currentTime.date().startOfDay();
//         filter = QString("time >= '%1' AND time < '%2'").arg(yesterdayStart.toString("yyyy-MM-dd hh:mm:ss")).arg(yesterdayEnd.toString("yyyy-MM-dd hh:mm:ss"));
//         break;
//     }
//     case Time::week: {
//         QDate weekAgoDate = QDate::currentDate().addDays(-7);
//         filter = QString("DATE(created_at) >= '%1'").arg(weekAgoDate.toString("yyyy-MM-dd hh:mm:ss"));
//         break;
//     }
//     case Time::custom: {
//         QDateTime specificDayStart(filters.startTime, QTime(0, 0, 0));
//         QDateTime specificDayEnd(filters.endTime, QTime(0, 0, 0));
//         filter = QString("time >= '%1' AND time < '%2'")
//                      .arg(specificDayStart.toString("yyyy-MM-dd hh:mm:ss"))
//                      .arg(specificDayEnd.toString("yyyy-MM-dd hh:mm:ss"));
//         break;
//     }

//     default:
//         break;
//     }
//     model.setFilter(filter);
//     model.select();


//     if (filters.type!=Type::all){
//         filter= QString("type = '%1'").arg(int(filters.type));
//         model.setFilter(filter);
//         model.select();
//     }
//     if (filters.tap!=""){
//         filter= QString("tap = '%1'").arg(filters.tap);
//         model.setFilter(filter);
//         model.select();
//     }
//     if (filters.content!=""){
//         filter = QString("content LIKE '%%1%'").arg(filters.content);
//         model.setFilter(filter);
//         model.select();
//     }
//     //查询data中type列等于filters.type
//     int rowCount = model.rowCount();
//     if (startRow >= rowCount) {
//         qDebug() << "Start row exceeds row count"<<rowCount;
//         return false;
//     }
//     int fetchCount = std::min(n, rowCount- startRow);
//     filter = QString("rowid BETWEEN %1 AND %2").arg(startRow).arg(startRow + fetchCount);

//     model.setFilter(filter);
//     model.select();
//     QVector<Data> tempDatas;
//     for (int i=0;i<fetchCount+1;++i){
//         QSqlRecord record = model.record(i);
//         int id=record.value(0).toInt();
//         QString created_at=record.value(1).toString();
//         QString content=record.value(2).toString();
//         int type=record.value(3).toInt();
//         QString tap=record.value(4).toString();
//         Data data(id,created_at,content,Type(type),tap);
//         tempDatas.push_back(data);
//     }
//     datas=tempDatas;
//     return true;
// }
unsigned int Dao::query(QVector<Data> &datas, int startRow, int n, Filter &filters) {
    QSqlTableModel model(nullptr, db);
    model.setTable("data");

    QString filter;

    switch (filters.time) {
    case Time::today: {
        // 设置今天的时间范围
        QDateTime currentTime = QDateTime::currentDateTime();
        QDateTime todayStart = currentTime.date().startOfDay();
        QDateTime todayEnd = currentTime.date().addDays(1).startOfDay();
        filter = QString("created_at >= '%1' AND created_at < '%2'").arg(todayStart.toString("yyyy-MM-dd hh:mm:ss")).arg(todayEnd.toString("yyyy-MM-dd hh:mm:ss"));

        break;
    }
    case Time::yesterday: {
        // 设置昨天的时间范围
        QDateTime currentTime = QDateTime::currentDateTime();
        QDateTime yesterdayStart = currentTime.date().addDays(-1).startOfDay();
        QDateTime yesterdayEnd = currentTime.date().startOfDay();
        filter = QString("created_at >= '%1' AND created_at < '%2'").arg(yesterdayStart.toString("yyyy-MM-dd hh:mm:ss")).arg(yesterdayEnd.toString("yyyy-MM-dd hh:mm:ss"));
        break;
    }
    case Time::week: {
        // 设置一周内的时间范围
        QDateTime currentTime = QDateTime::currentDateTime();
        QDateTime todayEnd = currentTime.date().addDays(1).startOfDay();
        QDateTime weekAgoDate = QDate::currentDate().addDays(-7).startOfDay();
        filter = QString("created_at >= '%1'  AND created_at < '%2'").arg(weekAgoDate.toString("yyyy-MM-dd hh:mm:ss")).arg(todayEnd.toString("yyyy-MM-dd hh:mm:ss"));
        break;
    }
    case Time::custom: {
        // 设置特定天的时间范围
        QDateTime specificDayStart(filters.startTime, QTime(0, 0, 0));
        QDateTime specificDayEnd(filters.endTime, QTime(23, 59, 59));
        filter = QString("created_at >= '%1' AND created_at < '%2'").arg(specificDayStart.toString("yyyy-MM-dd hh:mm:ss")).arg(specificDayEnd.toString("yyyy-MM-dd hh:mm:ss"));
        break;
    }
    default:
        filter = QString("created_at >= 2024-03-20 '00:00:00'"); //为了后面拼接“AND”
        break;
    }
    qDebug()<<filter;
    // 追加其他过滤条件
    if (filters.type != Type::all) {
        filter += QString(" AND type = '%1'").arg(int(filters.type));
        qDebug()<<filter;
    }
    if (!filters.tap.isEmpty()) {
        filter += QString(" AND tap = '%1'").arg(filters.tap);
        qDebug()<<filter;
    }
    if (!filters.content.isEmpty()) {
        filter += QString(" AND content LIKE '%%1%'").arg(filters.content);

        qDebug()<<filter;
    }
    model.setFilter(filter);

    // 执行查询
    if (!model.select()) {
        qDebug() << "Failed to execute query";
    }
    while(model.canFetchMore())
    {
        model.fetchMore(); //break 256 limit
    }
    int rowCount = model.rowCount();
    if (startRow >= rowCount) {
        qDebug() << "Start row exceeds row count" << rowCount;
    }

    int fetchCount = std::min(n, rowCount - startRow);

    QVector<Data> tempDatas;
    for (int i = startRow; i < fetchCount+startRow; ++i) {
        QSqlRecord record = model.record(i);
        int id = record.value(0).toInt();
        QString created_at = record.value(1).toString();
        QString content = record.value(2).toString();
        int type = record.value(3).toInt();
        QString tap = record.value(4).toString();
        Data data(id, created_at, content, Type(type), tap);
        tempDatas.push_back(data);
    }

    datas = tempDatas;
    return rowCount;
}


// bool Dao::query(QVector<Data> &datas, QString &queryString)
// {
//     QSqlTableModel model(nullptr, db);
//     model.setTable("data");
//     model.select();

//     QVector<Data> resultVector;



//     for (int i = 0; i < model.rowCount(); ++i) {
//         QSqlRecord record = model.record(i);
//         QString content = record.value(2).toString();

//         if (content.contains(queryString)) {
//             int id=record.value(0).toInt();
//             QString created_at=record.value(1).toString();
//             QString content=record.value(2).toString();
//             int type=record.value(3).toInt();
//             QString tap=record.value(4).toString();
//             Data data(id,created_at,content,type,tap);


//             resultVector.append(data);
//         }
//     }

//     datas = resultVector;

//     return true; // 或者根据情况返回false
// }

bool Dao::close(const QString &DatabaseName)
{
    db = QSqlDatabase(); //make DatabaseName unuse
    db.close();
    QSqlDatabase::removeDatabase(DatabaseName);
    return true;
}


Filter::Filter()
{
    this->type=Type::all;
    this->time=Time::all;
}
