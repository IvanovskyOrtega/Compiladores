#include <iostream>
#include <vector>
#include "Transicion.hpp"

using namespace std;

Transicion::Transicion(int estado1, int estado2, char simbolo){
    estadoActual = estado1;
    estadoDeTransicion = estado2;
    simboloDeTransicion = simbolo;
  };
