#include "dao.h"

class Service {
public:
    bool readClipboard();
    bool start();
private:
    Dao dao;
};
