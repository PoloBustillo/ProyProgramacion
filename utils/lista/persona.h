#pragma once
#include <string>
#include <iostream>
using namespace std;

// Definición de la clase Persona
class Persona
{
private:
    int ID_Trabajador; // ID del trabajador (6 numeros)
    string Nombre;
    string ApellidoPaterno;
    string ApellidoMaterno;
    string Sexo; // 'M' para masculino, 'F' para femenino
    int Edad;
    string Direccion;
    string Telefono;
    string Puesto;
    string Departamento;
    int HorasTrabajadas;
    double CostoPorHora;

public:
    Persona() {}
    Persona(string Nombre, string ApellidoPaterno, string ApellidoMaterno, string Sexo, int Edad, string Direccion, string Telefono, string Puesto, string Departamento, int HorasTrabajadas, double CostoPorHora)
        : Nombre(Nombre), ApellidoPaterno(ApellidoPaterno), ApellidoMaterno(ApellidoMaterno), Sexo(Sexo), Edad(Edad), Direccion(Direccion), Telefono(Telefono), Puesto(Puesto), Departamento(Departamento), HorasTrabajadas(HorasTrabajadas), CostoPorHora(CostoPorHora)
    {
    }
    // Método para calcular el sueldo
    double calcularSueldo() const
    {
        return HorasTrabajadas * CostoPorHora;
    }
    // Getters
    int getID_Trabajador() const { return ID_Trabajador; }
    string getNombre() const { return Nombre; }
    string getApellidoPaterno() const { return ApellidoPaterno; }
    string getApellidoMaterno() const { return ApellidoMaterno; }
    string getSexo() const { return Sexo; }
    int getEdad() const { return Edad; }
    string getDireccion() const { return Direccion; }
    string getTelefono() const { return Telefono; }
    string getPuesto() const { return Puesto; }
    string getDepartamento() const { return Departamento; }
    int getHorasTrabajadas() const { return HorasTrabajadas; }
    double getCostoPorHora() const { return CostoPorHora; }

    // Setters
    void setID_Trabajador(int id) { ID_Trabajador = id; }
    void setNombre(const string &nombre) { Nombre = nombre; }
    void setApellidoPaterno(const string &apellido) { ApellidoPaterno = apellido; }
    void setApellidoMaterno(const string &apellido) { ApellidoMaterno = apellido; }
    void setSexo(const string &sexo) { Sexo = sexo; }
    void setEdad(int edad) { Edad = edad; }
    void setDireccion(const string &direccion) { Direccion = direccion; }
    void setTelefono(const string &telefono) { Telefono = telefono; }
    void setPuesto(const string &puesto) { Puesto = puesto; }
    void setDepartamento(const string &departamento) { Departamento = departamento; }
    void setHorasTrabajadas(int horas) { HorasTrabajadas = horas; }
    void setCostoPorHora(double costo) { CostoPorHora = costo; }
};
