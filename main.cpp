#include <iostream>
#include <sqlite3.h>
#include "utils/db/utils_db.h"

using namespace std;

int main()
{
    sqlite3 *DB;
    const char *dbName = "./Student.sqlite";
    char *zErrMsg = 0;
    int result;
    string sql;

    result = connectToDatabase(&DB, dbName);
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