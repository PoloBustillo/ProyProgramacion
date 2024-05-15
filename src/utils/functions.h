#pragma once
#include <string>
#include <iostream>
#include "../lista/persona.h"
#include "../lista/nodo.h"
#include <iomanip>

using namespace std;

class Utils
{
public:
    static const string INVALID_OPTION;
    static const string EXITING;
    static const string EMPLOYEE_ID_PROMPT;
    static const string EMPLOYEE_NAME_PROMPT;
    static const string SEARCH_OPTION_PROMPT;
    static const string DELET_EMPLOYEE_PROMPT;
    static const string MODIFY_EMPLOYEE_PROMPT;
    static const string EMPLOYEE_NOT_FOUND;
    static const int EXIT_OPTION;

    static int imprimirMenu();
    static Persona guardarDatos();
    static void mostrarEmpleado(Nodo *actual);
    static void handleError(int error);
    static string obtenerEntradaValida(const string &mensaje);
    static long obtenerNumeroValido(const std::string &mensaje, int min, long max);
    static string obtenerEntradaConEspacios(const string &mensaje);

private:
    static bool es_string(const string &s)
    {
        return all_of(s.begin(), s.end(), ::isalpha);
    };
    static bool es_string_espacios(const string &str)
    {
        for (char c : str)
        {
            if (!isalpha(c) && !isspace(c))
            {
                return false;
            }
        }
        return true;
    }
};

const string Utils::INVALID_OPTION = "Opción no válida. Por favor, elige otra.\n";
const string Utils::EXITING = "Saliendo...\n";
const string Utils::EMPLOYEE_ID_PROMPT = "¿Qué empleado deseas consultar? Dame por favor su ID: ";
const string Utils::EMPLOYEE_NAME_PROMPT = "¿Qué empleado deseas consultar? Dame por favor su nombre completo: ";
const string Utils::SEARCH_OPTION_PROMPT = "¿Deseas buscar por 1) ID o 2) Nombre? ";
const string Utils::DELET_EMPLOYEE_PROMPT = "¿Qué empleado deseas eliminar? Dame por favor su ID: ";
const string Utils::MODIFY_EMPLOYEE_PROMPT = "¿Qué empleado deseas modificar? Dame por favor su ID: ";
const string Utils::EMPLOYEE_NOT_FOUND = "Empleado no encontrado";
const int Utils::EXIT_OPTION = 6;

long Utils::obtenerNumeroValido(const std::string &mensaje, int min, long max)
{
    long numero;
    cout << mensaje;

    while (!(cin >> numero) || numero < min || numero > max)
    {
        cout << "Entrada inválida. Por favor, introduce un número entre " << min << " y " << max << ": ";
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return numero;
}
string Utils::obtenerEntradaConEspacios(const string &mensaje)
{
    string entrada;
    cout << mensaje;
    getline(cin, entrada);
    while (!es_string_espacios(entrada))
    {
        cout << "La entrada tiene que ser caracteres. " << mensaje;
        getline(cin, entrada);
    }
    return entrada;
};
string Utils::obtenerEntradaValida(const string &mensaje)
{
    string entrada;
    cout << mensaje;
    getline(cin, entrada);
    while (entrada.empty() || !es_string(entrada))
    {
        cout << "La entrada no puede estar en blanco y tiene que ser caracteres. " << mensaje;
        getline(cin, entrada);
    }
    return entrada;
};
void Utils::handleError(int error)
{
    switch (error)
    {
    case 500:
        cout << "Error al crear Tabla" << endl;
        exit(-1);
    case 404:
        cout << "Error al conectar con DB" << endl;
        exit(-1);
    default:
        cout << "Error desconocido" << endl;
        exit(-1);
    }
}
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
    cout << "Por favor, introduce los siguientes datos:\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Nombre = obtenerEntradaConEspacios("Escriba Nombre:");
    ApellidoPaterno = obtenerEntradaValida("Escriba Apellido Paterno: ");
    ApellidoMaterno = obtenerEntradaValida("Escriba Apellido Materno: ");
    Sexo = obtenerEntradaValida("Escriba Sexo: ");
    Edad = obtenerNumeroValido("Escriba Edad: ", 18, 100);
    cout << "Escriba Dirección: ";
    cin >> Direccion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Telefono = to_string(obtenerNumeroValido("Escriba Telefono: ", 0, 99999999999L));
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Puesto = obtenerEntradaValida("Escriba Puesto: ");
    Departamento = obtenerEntradaValida("Escriba Departamento: ");
    HorasTrabajadas = obtenerNumeroValido("Escriba Horas Trabajadas: ", 0, 2400);
    CostoPorHora = obtenerNumeroValido("Escriba Costo Por Hora: ", 0, 700);
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
         << setw(18) << "Direccion" << "|"
         << setw(12) << "Telefono" << "|"
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
         << setw(18) << actual->persona.getDireccion() << "|"
         << setw(12) << actual->persona.getTelefono() << "|"
         << setw(8) << actual->persona.getPuesto() << "|"
         << setw(10) << actual->persona.getDepartamento() << "|"
         << setw(6) << actual->persona.getHorasTrabajadas() << "|"
         << setw(6) << actual->persona.getCostoPorHora() << "|"
         << setw(6) << actual->persona.calcularSueldo() << "\n\n";
}