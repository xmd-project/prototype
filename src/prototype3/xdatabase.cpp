#include "xdatabase.h"
#include <QString>

XDatabase::XDatabase()
{
}

XDatabase::~XDatabase()
{
}

int XDatabase::connect(const QString &dbName)
{
    Q_ASSERT(dbName.size());
    return 0;
}

int XDatabase::disconnect()
{
    return 0;
}

int XDatabase::search(void *key)
{
    Q_ASSERT(key);
    return 0;
}

int XDatabase::insert(void *data)
{
    Q_ASSERT(data);
    return 0;
}

int XDatabase::remove(void *data)
{
    Q_ASSERT(data);
    return 0;
}
