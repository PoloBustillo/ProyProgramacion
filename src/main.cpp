#include <iostream>
#include "./sqlite/sqlite3.h"
#include "lista/lista.h"
#include "lista/persona.h"
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
        int id;
        bool empleadoEnLista = false;
        Persona persona;

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
                cout << Utils::DELET_EMPLOYEE_PROMPT;
                cin >> id;
                lista->eliminarEmpleado(id);
                lista->mostrar();
                break;
            case 4:
                cout << Utils::MODIFY_EMPLOYEE_PROMPT;
                cin >> id;
                persona = lista->buscarPorID(id);
                if (persona.getID_Trabajador() == id)
                {
                    nuevaPersona = Utils::guardarDatos();
                    nuevaPersona.setID_Trabajador(id);
                    cout << nuevaPersona.getID_Trabajador() << endl;
                    lista->modificarPorID(id, nuevaPersona);
                    lista->updatePersona(nuevaPersona, id);
                }
                else
                {
                    cout << Utils::EMPLOYEE_NOT_FOUND;
                }
                break;
            case 5:
                int opcion;
                cout << Utils::SEARCH_OPTION_PROMPT;
                cin >> opcion;
                lista->mostrar();

                if (opcion == 1)
                {
                    int id;
                    cout << Utils::EMPLOYEE_ID_PROMPT;
                    cin >> id;
                    lista->buscarPorID(id);
                }
                else if (opcion == 2)
                {
                    string nombre, apellidoPaterno, apellidoMaterno;
                    cout << Utils::EMPLOYEE_NAME_PROMPT;
                    cin >> nombre >> apellidoPaterno >> apellidoMaterno;
                    lista->buscarPorNombre(nombre, apellidoPaterno, apellidoMaterno);
                }
                else
                {
                    cout << Utils::INVALID_OPTION;
                }
                break;
            case Utils::EXIT_OPTION:
                cout << Utils::EXITING;
                break;
            default:
                cout << Utils::INVALID_OPTION;
                break;
            }
        } while (option != 6);
    }
    catch (int error)
    {
        Utils::handleError(error);
    }

    return 0;
}
