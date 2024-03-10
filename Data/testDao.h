#ifndef TESTDAO_H
#define TESTDAO_H
#include "dao.h"
#include <QTest>




class TestDao: public QObject
{
    Q_OBJECT
    Dao Dao;
private slots:
    void testInit();
    void testInsertOneData();

};
#endif // TESTDAO_H
