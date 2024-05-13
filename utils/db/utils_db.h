#include <iostream>
#include <sqlite3.h>

using namespace std;

int connectToDatabase(sqlite3 **DB, const char *name)
{
    int connection = sqlite3_open_v2(name, DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

    if (connection)
    {
        cerr << "Error: " << sqlite3_errmsg(*DB) << endl;
        return -1;
    }
    else
    {
        cout << "¡Conectado a la DB!" << endl;
        return 0;
    }
}

int createAndPopulateTable(sqlite3 *DB)
{
    char *errMsg;
    const char *sql = "CREATE TABLE IF NOT EXISTS Students("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "NAME TEXT NOT NULL,"
                      "AGE INT NOT NULL,"
                      "ADDRESS CHAR(50),"
                      "MARKS INT );";

    int result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

    if (result != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    sql = "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
          "VALUES ('Paul', 32, 'California', 200); "
          "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
          "VALUES ('Allen', 25, 'Texas', 150); "
          "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
          "VALUES ('Teddy', 23, 'Norway', 200); "
          "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
          "VALUES ('Mark', 25, 'Rich-Mond', 650);";

    result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

    if (result != SQLITE_OK)
    {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return -1;
    }

    return 0;
}