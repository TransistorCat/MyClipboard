#ifndef SERVICE_H
#define SERVICE_H
#include "dao.h"

class Service {
public:
    bool readClipboard(QClipboard *clipboard);
    QVector<Data>  queryDB();
    QVector<Data> queryDB(QString&);
    bool start();
private:
    Dao dao;
};
#endif
