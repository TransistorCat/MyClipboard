#ifndef SERVICE_H
#define SERVICE_H
#include "dao.h"

struct QueryResult{
    unsigned int rowCount;
    QVector<Data> datas;
};
class Service {
public:
    bool readClipboard(QClipboard *clipboard);
   QueryResult queryDB(int startRow, int n, Filter &filters);

    bool start();
private:
    Dao dao;
};
#endif
