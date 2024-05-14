#pragma once
#include "./persona.h"

using namespace std;

// Definición de la clase Nodo
class Nodo
{
public:
    Persona persona;
    Nodo *siguiente;
};