#include <iostream>
#include <sqlite3.h>
using namespace std;

int connectToDatabase(sqlite3 **DB)
{
    int connection = sqlite3_open_v2("Student.db", DB, SQLITE_OPEN_READWRITE, NULL);

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
