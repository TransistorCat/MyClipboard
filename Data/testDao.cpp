
#include "testDao.h"

// #include "dao.h"

const QString Constants::testDB = "test.db";
void TestDao::testInit()
{
    // Dao Dao;
    QCOMPARE(Dao.init(Constants::testDB), 0);
}

void TestDao::testInsertOneData()
{
    Dao.init(Constants::testDB);
    Data testData("Fuck Cpp!");
    QCOMPARE(Dao.insertOneData(testData), 0);


}

void TestDao::testQuery()
{

    Dao.init(Constants::testDB);
    Dao.insertOneData(Data("Fuck Cpp!"));
    Dao.insertOneData(Data("Fuck Golang!"));
    Dao.insertOneData(Data("Fuck Java!"));
    QVector<Data> testDatas;
    Dao.query(testDatas,1,3);

    QCOMPARE(testDatas.size(),3);
    QCOMPARE(testDatas[0].content,"Fuck Cpp!");
    QCOMPARE(testDatas[1].content,"Fuck Golang!");
    QCOMPARE(testDatas[2].content,"Fuck Java!");

}

void TestDao::cleanup()
{
    Dao.close(Constants::testDB);
    QFile file(Constants::testDB);
    file.remove();
}


QTEST_MAIN(TestDao)

#include "testDao.moc"
