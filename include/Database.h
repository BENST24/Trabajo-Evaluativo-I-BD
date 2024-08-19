#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <iostream>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();

    bool executeSQL(const std::string& sql);
    static void initialize(Database& db);
    sqlite3* getDB() const;

private:
    sqlite3* db;
};

#endif // DATABASE_H
