#include "dao.h"

class Service {
public:
    bool readClipboard(QClipboard *clipboard);
    bool start();
private:
    Dao dao;
};
