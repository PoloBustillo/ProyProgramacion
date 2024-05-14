#pragma once
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "./persona.h"
#include "./nodo.h"
#include "../utils/functions.h"

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
    void buscarPorID(int id)
    {
        Nodo *actual = cabeza;

        while (actual != nullptr)
        {
            if (actual->persona.getID_Trabajador() == id)
            {
                Utils::mostrarEmpleado(actual);
                return;
            }
            actual = actual->siguiente;
        }

        cout << "El empleado no se encontró en la nómina.\n";
    }
    void buscarPorNombre(string nombre, string apellidoPaterno, string apellidoMaterno)
    {
        Nodo *actual = cabeza;

        while (actual != nullptr)
        {
            if (actual->persona.getNombre() == nombre &&
                actual->persona.getApellidoPaterno() == apellidoPaterno &&
                actual->persona.getApellidoMaterno() == apellidoMaterno)
            {
                Utils::mostrarEmpleado(actual);
                return;
            }
            actual = actual->siguiente;
        }

        cout << "El empleado no se encontró en la nómina.\n";
    }
    void eliminarEmpleado(int id)
    {
        Nodo *actual = cabeza;
        Nodo *previo = nullptr;

        // Si la lista está vacía
        if (actual == nullptr)
        {
            cout << "No existen empleados.\n";
            return;
        }

        // Buscar el nodo con el ID dado
        while (actual != nullptr && actual->persona.getID_Trabajador() != id)
        {
            previo = actual;
            actual = actual->siguiente;
        }

        // Si no se encontró el ID
        if (actual == nullptr)
        {
            cout << "No se encontró el empleado con ID " << id << ".\n";
            return;
        }

        // Si el nodo a eliminar es el primer nodo
        if (actual == cabeza)
        {
            cabeza = actual->siguiente;
        }
        // Si el nodo a eliminar es el último nodo
        else if (actual->siguiente == nullptr)
        {
            previo->siguiente = nullptr;
        }
        // Si el nodo a eliminar está en medio
        else
        {
            previo->siguiente = actual->siguiente;
        }

        delete actual;
        cout << "Empleado con ID " << id << " eliminado.\n";
        eliminarEmpleadoDB(id);
    }

    void modificarPorID(int id, const Persona &nuevaPersona)
    {
        Nodo *actual = cabeza;
        while (actual != nullptr)
        {
            if (actual->persona.getID_Trabajador() == id)
            {
                actual->persona = nuevaPersona;
                return;
            }
            actual = actual->siguiente;
        }
        cout << "No se encontró ninguna persona con el ID " << id << ".\n";
    }
    void mostrar()
    {
        Nodo *actual = cabeza;
        if (actual == nullptr)
        {
            cout << "No existen personas.\n";
        }
        while (actual != nullptr)
        {
            Utils::mostrarEmpleado(actual);
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
                          "Sexo TEXT NOT NULL,"
                          "Edad INT NOT NULL,"
                          "Direccion TEXT,"
                          "Telefono CHAR(10),"
                          "Puesto TEXT,"
                          "Departamento TEXT,"
                          "HorasTrabajadas REAL,"
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
    void eliminarEmpleadoDB(int id)
    {
        const char *sql = "DELETE FROM PERSONAS WHERE ID_Trabajador = ?";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL) != SQLITE_OK)
        {
            cerr << "Error: " << sqlite3_errmsg(DB) << endl;
            throw(404);
        }

        if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK)
        {
            cerr << "Error: " << sqlite3_errmsg(DB) << endl;
            throw(404);
        }

        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            cerr << "Error: " << sqlite3_errmsg(DB) << endl;
            throw(404);
        }

        cout << "Empleado con ID " << id << " eliminado de la base de datos.\n";
        sqlite3_finalize(stmt);
    }
    long long insertPersona(const Persona &persona)
    {
        const char *sql = "INSERT INTO PERSONAS(Nombre, ApellidoPaterno, ApellidoMaterno, Sexo, Edad, Direccion, Telefono, Puesto, Departamento, HorasTrabajadas, CostoPorHora) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL) != SQLITE_OK)
        {
            cout << "La query no esta bien construida: " << sqlite3_errmsg(DB) << endl;
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
            cout << "No se pudo ejecutar la query: " << sqlite3_errmsg(DB) << endl;
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
                persona.setHorasTrabajadas(sqlite3_column_double(stmt, 10));
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