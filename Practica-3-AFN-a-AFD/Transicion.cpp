#include <iostream>
#include "Transicion.hpp"

/**
 * Constructor de Transicion para AFD
 * **/
Transicion::Transicion(int estado1, int estado2, char simbolo){
    estadoActual = estado1;
    estadoDeTransicion = estado2;
    simboloDeTransicion = simbolo;
};

/**
 * Constructor de Transicion para AFN
 * **/
Transicion::Transicion(int estado1, int estado2, char simbolo, bool esEpsilon){
    estadoActual = estado1;
    estadoDeTransicion = estado2;
    simboloDeTransicion = simbolo;
    esTransicionEpsilon = esEpsilon;
};
