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

    int option;

    do
    {
        cout << "\n********** MENU **********\n";
        cout << "1. Dar de Alta un nuevo empleado\n";
        cout << "2. Mostrar Nómina de empleados\n";
        cout << "3. Dar de baja un empleado\n";
        cout << "4. Realizar cambios en la nómina\n";
        cout << "5. Consultar información de un empleado\n";
        cout << "6. Salir\n";
        cout << "**************************\n";
        cout << "Elige una opción: ";
        cin >> option;

        switch (option)
        {
        case 1:
            // Código para dar de alta un nuevo empleado
            break;
        case 2:
            // Código para mostrar nómina de empleados
            break;
        case 3:
            // Código para dar de baja un empleado
            break;
        case 4:
            // Código para realizar cambios en la nómina
            break;
        case 5:
            // Código para consultar información de un empleado
            break;
        case 6:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opción no válida. Por favor, elige una opción del 1 al 6.\n";
            break;
        }
    } while (option != 6);

    return 0;
}