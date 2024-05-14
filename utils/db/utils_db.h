// #pragma once
// #include <iostream>
// #include <sqlite3.h>
// #include "../lista/personaLista.h"

// using namespace std;
// class Lista;
// class Persona' class DBUtils
// {
// private:
//     sqlite3 *DB;

// public:
//     DBUtils &connectToDatabase(const char *name)
//     {
//         int connection = sqlite3_open_v2(name, &DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

//         if (connection)
//         {
//             cerr << "Error: " << sqlite3_errmsg(DB) << endl;
//             throw(404);
//         }
//         else
//         {
//             cout << "¡Conectado a la DB!" << endl;
//         }

//         return *this;
//     }

//     DBUtils &createTable()
//     {
//         char *errMsg;
//         const char *sql = "CREATE TABLE IF NOT EXISTS PERSONAS("
//                           "ID_Trabajador INTEGER PRIMARY KEY AUTOINCREMENT,"
//                           "Nombre TEXT NOT NULL,"
//                           "ApellidoPaterno TEXT NOT NULL,"
//                           "ApellidoMaterno TEXT NOT NULL,"
//                           "Sexo CHAR(1) NOT NULL,"
//                           "Edad INT NOT NULL,"
//                           "Direccion TEXT,"
//                           "Telefono CHAR(10),"
//                           "Puesto TEXT,"
//                           "Departamento TEXT,"
//                           "HorasTrabajadas INT,"
//                           "CostoPorHora REAL );";

//         int exit = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

//         if (exit != SQLITE_OK)
//         {
//             std::cerr << "Error al crear tabla" << std::endl;
//             cout << errMsg << std::endl;
//             sqlite3_free(errMsg);
//             throw(500);
//         }
//         else
//         {
//             std::cout << "Tabla creada!!!" << std::endl;
//         }

//         return *this;
//     }

//     DBUtils &populateList(Lista *lista)
//     {
//         const char *sql = "SELECT * FROM PERSONAS";
//         sqlite3_stmt *stmt;

//         if (sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL) == SQLITE_OK)
//         {
//             while (sqlite3_step(stmt) == SQLITE_ROW)
//             {
//                 Persona persona;
//                 persona.ID_Trabajador = sqlite3_column_int(stmt, 0);
//                 persona.Nombre = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
//                 persona.ApellidoPaterno = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
//                 persona.ApellidoMaterno = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)));
//                 persona.Sexo = *reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
//                 persona.Edad = sqlite3_column_int(stmt, 5);
//                 persona.Direccion = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6)));
//                 persona.Telefono = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7)));
//                 persona.Puesto = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8)));
//                 persona.Departamento = string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9)));
//                 persona.HorasTrabajadas = sqlite3_column_int(stmt, 10);
//                 persona.CostoPorHora = sqlite3_column_double(stmt, 11);

//                 // lista->agregar(persona); // Asume que la clase Lista tiene un método agregar que toma un objeto Persona
//             }
//         }

//         sqlite3_finalize(stmt);

//         return *this;
//     }
// };

// int createAndPopulateTable(sqlite3 *DB)
// {
//     char *errMsg;
//     const char *sql = "CREATE TABLE IF NOT EXISTS PERSONAS("
//                       "ID_Trabajador INTEGER PRIMARY KEY AUTOINCREMENT,"
//                       "Nombre TEXT NOT NULL,"
//                       "ApellidoPaterno TEXT NOT NULL,"
//                       "ApellidoMaterno TEXT NOT NULL,"
//                       "Sexo CHAR(1) NOT NULL,"
//                       "Edad INT NOT NULL,"
//                       "Direccion TEXT,"
//                       "Telefono CHAR(10),"
//                       "Puesto TEXT,"
//                       "Departamento TEXT,"
//                       "HorasTrabajadas INT,"
//                       "CostoPorHora REAL );";

//     int result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

//     if (result != SQLITE_OK)
//     {
//         cerr << "SQL error: " << errMsg << endl;
//         sqlite3_free(errMsg);
//         return -1;
//     }

//     sql = "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
//           "VALUES ('Paul', 32, 'California', 200); "
//           "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
//           "VALUES ('Allen', 25, 'Texas', 150); "
//           "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
//           "VALUES ('Teddy', 23, 'Norway', 200); "
//           "INSERT INTO Students (NAME,AGE,ADDRESS,MARKS) "
//           "VALUES ('Mark', 25, 'Rich-Mond', 650);";

//     result = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

//     if (result != SQLITE_OK)
//     {
//         cerr << "SQL error: " << errMsg << endl;
//         sqlite3_free(errMsg);
//         return -1;
//     }

//     return 0;
// }
