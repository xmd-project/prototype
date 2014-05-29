#ifndef XDATABASE_H
#define XDATABASE_H

class QString;

class XDatabase
{
public:
    XDatabase();
    ~XDatabase();

    int connect(const QString &dbName);
    int disconnect();
    int search(void *key);
    int insert(void *data);
    int remove(void *data);
};

#endif // XDATABASE_H
