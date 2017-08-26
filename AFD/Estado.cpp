#include <iostream>
#include "Estado.hpp"

using namespace std;

Estado::Estado(int numDeEstado, bool tipo){
  numeroDeEstado = numDeEstado;
  esFinal = tipo;
}
