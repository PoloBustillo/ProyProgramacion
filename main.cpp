#include <iostream>
#include <sqlite3.h>
#include "utils/lista/lista.h"
#include "utils/lista/persona.h"
#include "utils/functions.h"

using namespace std;

int main()
{
    try
    {
        Lista *lista = Lista::obtenerInstancia();
        Persona nuevaPersona;
        int ID_Trabajador;
        int option;

        do
        {
            option = Utils::imprimirMenu();
            switch (option)
            {
            case 1:
                nuevaPersona = Utils::guardarDatos();
                ID_Trabajador = lista->insertPersona(nuevaPersona);
                nuevaPersona.setID_Trabajador(ID_Trabajador);
                lista->agregar_ordenado_por_apellido(nuevaPersona);
                lista->mostrar();
                break;
            case 2:
                lista->mostrar();
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
    }
    catch (int error)
    {
        if (error == 500)
        {
            cout << "Error al crear Tabla" << endl;
            return -1;
        }
        if (error == 404)
        {
            cout << "Error al conectar con DB" << endl;
            return -1;
        }
    }

    return 0;
}