
#include "testDao.h"

// #include "dao.h"


void TestDao::testInit()
{
    // Dao Dao;
    QCOMPARE(Dao.init(), 0);

}

void TestDao::testInsertOneData()
{
    Dao.init();
    QString a("Fuck CPP!");
    Data d(a);
    QCOMPARE(Dao.insertOneData(d), 0);

}


QTEST_MAIN(TestDao)

#include "testDao.moc"
