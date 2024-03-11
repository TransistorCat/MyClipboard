#ifndef TESTDAO_H
#define TESTDAO_H
#include "dao.h"
#include <QTest>


#include <QString>

class Constants {
public:
    static const QString testDB;
};

class TestDao: public QObject
{
    Q_OBJECT
    Dao Dao;
private slots:
    void testInit();
    void testInsertOneData();
    void testQuery();
    void cleanup();

};
#endif // TESTDAO_H
