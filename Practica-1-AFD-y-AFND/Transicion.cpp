#include <iostream>
#include "Transicion.hpp"

Transicion::Transicion(int estado1, int estado2, char simbolo){
    estadoActual = estado1;
    estadoDeTransicion = estado2;
    simboloDeTransicion = simbolo;
};

Transicion::Transicion(int estado1, int estado2, char simbolo, bool esEpsilon){
    estadoActual = estado1;
    estadoDeTransicion = estado2;
    simboloDeTransicion = simbolo;
    esTransicionEpsilon = esEpsilon;
};
