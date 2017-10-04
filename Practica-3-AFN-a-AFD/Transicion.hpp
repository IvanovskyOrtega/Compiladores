#ifndef _TRANSICION_HPP_
#define _TRANSICION_HPP_

using namespace std;

class Transicion{
public:
  int estadoActual;
  int estadoDeTransicion;
  char simboloDeTransicion;
  bool esTransicionEpsilon;
  Transicion(int estado1, int estado2, char simbolo);
  Transicion(int estado1, int estado2, char simbolo, bool esEpsilon);
};

#endif
