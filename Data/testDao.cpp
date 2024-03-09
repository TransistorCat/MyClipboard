
#include "testDao.h"

#include "dao.h"
// #include "testDao.moc"

void TestDao::Init()
{
    Dao Dao;
    QCOMPARE(Dao.Init(), 1);

}
QTEST_MAIN(TestDao)

