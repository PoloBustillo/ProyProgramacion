#pragma once
#include <string>
#include <iostream>
#include "./lista/persona.h"
#include "./lista/nodo.h"
#include <iomanip>

using namespace std;

class Utils
{
public:
    static int imprimirMenu();
    static Persona guardarDatos();
    static void mostrarEmpleado(Nodo *actual);

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
    string options[] = {
        "1. Dar de Alta un nuevo empleado",
        "2. Mostrar Nómina de empleados",
        "3. Dar de baja un empleado",
        "4. Realizar cambios en la nómina",
        "5. Consultar información de un empleado",
        "6. Salir"};
    cout << right << setw(54) << "\n"
         << setw(54) << setfill('*') << " MENU " << setfill('*') << setw(50) << "\n";
    cout << setfill(' ');
    int consoleWidth = 100; // Change this to your console's width
    for (const auto &option : options)
    {
        int padding = (consoleWidth - option.size()) / 2;
        cout << setw(padding) << "" << option << "\n";
    }
    cout << setw(104) << setfill('*') << "" << setfill(' ') << "\n\n";
    cout << "Elige una opción: ";
    cin >> option;
    return option;
}

void Utils::mostrarEmpleado(Nodo *actual)
{
    cout << left << setw(5) << "ID" << "|"
         << setw(10) << "Nombre" << "|"
         << setw(10) << "ApellidoP" << "|"
         << setw(10) << "ApellidoM" << "|"
         << setw(6) << "Sexo" << "|"
         << setw(4) << "Edad" << "|"
         << setw(20) << "Direccion" << "|"
         << setw(10) << "Telefono" << "|"
         << setw(8) << "Puesto" << "|"
         << setw(10) << "Dep." << "|"
         << setw(6) << "HorasT" << "|"
         << setw(6) << "CostoH" << "|"
         << setw(6) << "Sueldo" << "\n";

    cout << setw(5) << actual->persona.getID_Trabajador() << "|"
         << setw(10) << actual->persona.getNombre() << "|"
         << setw(10) << actual->persona.getApellidoPaterno() << "|"
         << setw(10) << actual->persona.getApellidoMaterno() << "|"
         << setw(6) << actual->persona.getSexo() << "|"
         << setw(4) << actual->persona.getEdad() << "|"
         << setw(20) << actual->persona.getDireccion() << "|"
         << setw(10) << actual->persona.getTelefono() << "|"
         << setw(8) << actual->persona.getPuesto() << "|"
         << setw(10) << actual->persona.getDepartamento() << "|"
         << setw(6) << actual->persona.getHorasTrabajadas() << "|"
         << setw(6) << actual->persona.getCostoPorHora() << "|"
         << setw(6) << actual->persona.calcularSueldo() << "\n\n";
}