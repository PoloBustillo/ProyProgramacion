#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <algorithm>

#include "./persona.h"
#include "./nodo.h"

using namespace std;

// Definición de la clase Lista
class Lista
{
private:
    Nodo *cabeza;
    static Lista *instancia;
    sqlite3 *DB;

    // Constructor privado
    Lista() : cabeza(nullptr){};

public:
    // Método estático para obtener la única instancia de la clase
    static Lista *obtenerInstancia()
    {
        if (instancia == nullptr)
        {
            instancia = new Lista();
            const char *dbName = "./Student.sqlite";
            instancia->connectToDatabase(dbName);
            instancia->createTable();
            instancia->populateList();
        }
        return instancia;
    }

    void agregar_ordenado_por_apellido(Persona p)
    {
        Nodo *nuevo = new Nodo;
        nuevo->persona = p;
        nuevo->siguiente = nullptr;

        if (cabeza == nullptr || cabeza->persona.getApellidoPaterno() >= p.getApellidoPaterno())
        {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
        else
        {
            Nodo *actual = cabeza;
            while (actual->siguiente != nullptr && actual->siguiente->persona.getApellidoPaterno() < p.getApellidoPaterno())
            {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }

    void agregar_al_final(Persona p)
    {
        Nodo *nuevo = new Nodo;
        nuevo->persona = p;
        nuevo->siguiente = nullptr;
        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Nodo *actual = cabeza;
            while (actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    void mostrar()
    {
        Nodo *actual = cabeza;
        while (actual != nullptr)
        {
            cout << "ID Trabajador: " << actual->persona.getID_Trabajador() << "\n"
                 << "Nombre: " << actual->persona.getNombre() << "\n"
                 << "Apellido Paterno: " << actual->persona.getApellidoPaterno() << "\n"
                 << "Apellido Materno: " << actual->persona.getApellidoMaterno() << "\n"
                 << "Sexo: " << actual->persona.getSexo() << "\n"
                 << "Edad: " << actual->persona.getEdad() << "\n"
                 << "Direccion: " << actual->persona.getDireccion() << "\n"
                 << "Telefono: " << actual->persona.getTelefono() << "\n"
                 << "Puesto: " << actual->persona.getPuesto() << "\n"
                 << "Departamento: " << actual->persona.getDepartamento() << "\n"
                 << "Horas Trabajadas: " << actual->persona.getHorasTrabajadas() << "\n"
                 << "Costo por Hora: " << actual->persona.getCostoPorHora() << "\n"
                 << "Sueldo: " << actual->persona.calcularSueldo() << "\n\n";
            actual = actual->siguiente;
        }
    }

    void createTable()
    {
        char *errMsg;
        const char *sql = "CREATE TABLE IF NOT EXISTS PERSONAS("
                          "ID_Trabajador INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "Nombre TEXT NOT NULL,"
                          "ApellidoPaterno TEXT NOT NULL,"
                          "ApellidoMaterno TEXT NOT NULL,"
                          "Sexo CHAR(1) NOT NULL,"
                          "Edad INT NOT NULL,"
                          "Direccion TEXT,"
                          "Telefono CHAR(10),"
                          "Puesto TEXT,"
                          "Departamento TEXT,"
                          "HorasTrabajadas INT,"
                          "CostoPorHora REAL );";

        int exit = sqlite3_exec(DB, sql, NULL, 0, &errMsg);

        if (exit != SQLITE_OK)
        {
            std::cerr << "Error al crear tabla" << std::endl;
            cout << errMsg << std::endl;
            sqlite3_free(errMsg);
            throw(500);
        }
        else
        {
            std::cout << "Tabla cargada!!!" << std::endl;
        }
    }
    void connectToDatabase(const char *name)
    {
        int connection = sqlite3_open_v2(name, &DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

        if (connection)
        {
            cerr << "Error: " << sqlite3_errmsg(DB) << endl;
            throw(404);
        }
        else
        {
            cout << "¡Conectado a la DB!" << endl;
        }
    }

    long long insertPersona(const Persona &persona)
    {
        const char *sql = "INSERT INTO PERSONAS(Nombre, ApellidoPaterno, ApellidoMaterno, Sexo, Edad, Direccion, Telefono, Puesto, Departamento, HorasTrabajadas, CostoPorHora) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL) != SQLITE_OK)
        {
            cout << "Could not prepare statement: " << sqlite3_errmsg(DB) << endl;
            return -1;
        }

        sqlite3_bind_text(stmt, 1, persona.getNombre().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, persona.getApellidoPaterno().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, persona.getApellidoMaterno().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, persona.getSexo().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 5, persona.getEdad());
        sqlite3_bind_text(stmt, 6, persona.getDireccion().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, persona.getTelefono().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, persona.getPuesto().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 9, persona.getDepartamento().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 10, persona.getHorasTrabajadas());
        sqlite3_bind_double(stmt, 11, persona.getCostoPorHora());

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            cout << "Could not execute statement: " << sqlite3_errmsg(DB) << endl;
        }

        sqlite3_finalize(stmt);

        long long id = sqlite3_last_insert_rowid(DB);
        return id;
    }

    void populateList()
    {
        const char *sql = "SELECT * FROM PERSONAS";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL) == SQLITE_OK)
        {
            std::vector<Persona> personas;
            while (sqlite3_step(stmt) == SQLITE_ROW)
            {
                Persona persona;
                persona.setID_Trabajador(sqlite3_column_int(stmt, 0));
                persona.setNombre(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))));
                persona.setApellidoPaterno(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))));
                persona.setApellidoMaterno(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3))));
                persona.setSexo(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4))));
                persona.setEdad(sqlite3_column_int(stmt, 5));
                persona.setDireccion(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 6))));
                persona.setTelefono(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 7))));
                persona.setPuesto(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 8))));
                persona.setDepartamento(string(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9))));
                persona.setHorasTrabajadas(sqlite3_column_int(stmt, 10));
                persona.setCostoPorHora(sqlite3_column_double(stmt, 11));
                personas.push_back(persona);
            }

            sort(personas.begin(), personas.end(), [](const Persona &a, const Persona &b)
                 { return a.getApellidoPaterno() < b.getApellidoPaterno(); });

            for (const Persona &persona : personas)
            {
                instancia->agregar_al_final(persona);
            }
        }

        sqlite3_finalize(stmt);
    }
};

// Inicialización de la variable estática
Lista *Lista::instancia = nullptr;