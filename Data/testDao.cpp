
#include "testDao.h"

// #include "dao.h"

const QString Constants::testDB = "test.db";
void TestDao::testInit()
{
    // Dao Dao;
    QCOMPARE(dao.init(Constants::testDB), true);
}

void TestDao::testInsertOneData()
{
    dao.init(Constants::testDB);
    Data testData("Fuck Cpp!",Type::text);
    QCOMPARE(dao.insertOneData(testData), true);

    QFile file(Constants::testDB);
    file.remove();
}

void TestDao::testQuery()
{
    
    dao.init(Constants::testDB);
    dao.insertOneData(Data("Fuck Cpp!",Type::text));
    dao.insertOneData(Data("Fuck Golang!",Type::text));
    dao.insertOneData(Data("Fuck Java!",Type::text));
    QVector<Data> testDatas;
    Filter f;
    f.type=Type::text;
    
    dao.query(testDatas,0,3,f);
qDebug()<<testDatas[0].content;
    // qDebug()<<testDatas[1].content;
    QCOMPARE(testDatas.size(),3);
    QCOMPARE(testDatas[0].content,"Fuck Cpp!");
    QCOMPARE(testDatas[1].content,"Fuck Golang!");
    QCOMPARE(testDatas[2].content,"Fuck Java!");
    f.time=Time::today;
    testDatas.clear();
    dao.query(testDatas,0,3,f);
    QCOMPARE(testDatas.size(),3);
    qDebug()<<testDatas[0].createAt;
    QCOMPARE(testDatas[0].content,"Fuck Cpp!");
    QCOMPARE(testDatas[1].content,"Fuck Golang!");
    QCOMPARE(testDatas[2].content,"Fuck Java!");
    testDatas.clear();
    f.time=Time::yesterday;
    dao.query(testDatas,0,3,f);
    QCOMPARE(testDatas.size(),0);

    f.type=Type::image;
    testDatas.clear();
    dao.query(testDatas,0,3,f);
    QCOMPARE(testDatas.size(),0);
    f.type=Type::text;
    f.time=Time::today;
    f.content="Cpp";
    testDatas.clear();
    dao.query(testDatas,0,3,f);
    QCOMPARE(testDatas.size(),1);
}

void TestDao::cleanup()
{
    dao.close(Constants::testDB);
    QFile file(Constants::testDB);
    file.remove();
}


QTEST_MAIN(TestDao)

#include "testDao.moc"
