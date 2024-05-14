#include <string>
#include <iostream>
#include "./lista/persona.h"

using namespace std;

class Utils
{
public:
    static int imprimirMenu();
    static Persona guardarDatos();

private:
    static bool es_string(const string &s)
    {
        return all_of(s.begin(), s.end(), ::isalpha);
    }
};

Persona Utils::guardarDatos()
{
    string Nombre;
    string ApellidoPaterno;
    string ApellidoMaterno;
    string Sexo;
    int Edad;
    string Direccion;
    string Telefono;
    string Puesto;
    string Departamento;
    int HorasTrabajadas;
    double CostoPorHora;

    cout << "Escriba Nombre: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Nombre);
    while (Nombre.empty() || !es_string(Nombre))
    {
        cout << "Nombre no vacio y string. Escriba Nombre: ";
        getline(cin, Nombre);
    }
    cout << "Enter ApellidoPaterno: ";
    getline(cin, ApellidoPaterno);
    while (Nombre.empty() || !es_string(Nombre))
    {
        cout << "ApellidoPaterno no puede estar en blanco. Escriba ApellidoPaterno: ";
        getline(cin, ApellidoPaterno);
    }
    cout << "Enter ApellidoMaterno: ";
    cin >> ApellidoMaterno;
    cout << "Enter Sexo: ";
    cin >> Sexo;
    cout << "Escribe Edad: ";
    while (!(cin >> Edad) || Edad < 0 || Edad > 999)
    {
        cout << "Invalido. Escribe 0 y 999 para Edad: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Enter Direccion: ";
    cin >> Direccion;
    cout << "Enter Telefono: ";
    cin >> Telefono;
    cout << "Enter Puesto: ";
    cin >> Puesto;
    cout << "Enter Departamento: ";
    cin >> Departamento;
    cout << "Enter HorasTrabajadas: ";
    cin >> HorasTrabajadas;
    cout << "Enter CostoPorHora: ";
    cin >> CostoPorHora;
    return Persona(Nombre, ApellidoPaterno, ApellidoMaterno, Sexo, Edad, Direccion, Telefono, Puesto, Departamento, HorasTrabajadas, CostoPorHora);
}

int Utils::imprimirMenu()
{
    int option;
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
    return option;
}