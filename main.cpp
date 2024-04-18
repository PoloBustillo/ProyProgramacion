#include <iostream>
#include <sqlite3.h>
#include "utils/db/utils_db.h"
using namespace std;

int main()
{
    sqlite3 *DB;
    int result = connectToDatabase(&DB);
    if (result == -1)
    {
        return -1;
    }

    return 0;
}