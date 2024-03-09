#ifndef TESTDAO_H
#define TESTDAO_H
#include <QTest>




class TestDao: public QObject
{
    Q_OBJECT
private slots:
    void Init();
};
#endif // TESTDAO_H
