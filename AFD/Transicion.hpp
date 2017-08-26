#ifndef _TRANSICION_HPP_
#define _TRANSICION_HPP_

#include <vector>

using namespace std;

class Transicion{
public:
  int estadoActual;
  int estadoDeTransicion;
  char simboloDeTransicion;
  Transicion(int estado1, int estado2, char simbolo);
};

#endif
