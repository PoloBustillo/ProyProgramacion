#include <iostream>
#include <sqlite3.h>
#include "utils/db/utils_db.h"
using namespace std;

int createAndPopulateTable(sqlite3 *DB)
{
    char *errMsg;
    const char *sql = "CREATE TABLE IF NOT EXISTS Students("
                      "ID INT PRIMARY KEY     NOT NULL,"
                      "NAME           TEXT    NOT NULL,"
                      "AGE            INT     NOT NULL,"
                      "ADDRESS        CHAR(50),"
                      "MARKS          INT );";

    int result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

    if (result != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    sql = "INSERT INTO Students (ID,NAME,AGE,ADDRESS,MARKS) "
          "VALUES (1, 'Paul', 32, 'California', 200); "
          "INSERT INTO Students (ID,NAME,AGE,ADDRESS,MARKS) "
          "VALUES (2, 'Allen', 25, 'Texas', 150); "
          "INSERT INTO Students (ID,NAME,AGE,ADDRESS,MARKS) "
          "VALUES (3, 'Teddy', 23, 'Norway', 200); "
          "INSERT INTO Students (ID,NAME,AGE,ADDRESS,MARKS) "
          "VALUES (4, 'Mark', 25, 'Rich-Mond', 650);";

    result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

    if (result != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    return 0;
}

int main()
{
    sqlite3 *DB;
    const char *dbName = "./Student.sqlite";
    int result = connectToDatabase(&DB, dbName);
    if (result == -1)
    {
        return -1;
    }
    result = createAndPopulateTable(DB);
    if (result == -1)
    {
        return -1;
    }

    return 0;
}