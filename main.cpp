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
                int id;
                cout << "¿Qué empleado deseas eliminar? Dame por favor su ID: ";
                cin >> id;
                lista->eliminarEmpleado(id);
                break;
            case 4:
                // Código para realizar cambios en la nómina
                break;
            case 5:
                // Código para consultar información de un empleado
                int opcion;
                cout << "¿Deseas buscar por 1) ID o 2) Nombre? ";
                cin >> opcion;

                if (opcion == 1)
                {
                    int id;
                    cout << "¿Qué empleado deseas consultar? Dame por favor su ID: ";
                    cin >> id;
                    lista->buscarPorID(id);
                }
                else if (opcion == 2)
                {
                    string nombre, apellidoPaterno, apellidoMaterno;
                    cout << "¿Qué empleado deseas consultar? Dame por favor su nombre completo: ";
                    cin >> nombre >> apellidoPaterno >> apellidoMaterno;
                    lista->buscarPorNombre(nombre, apellidoPaterno, apellidoMaterno);
                }
                else
                {
                    cout << "Opción no válida. Por favor, elige 1 o 2.\n";
                }
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