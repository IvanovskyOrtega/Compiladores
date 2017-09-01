#ifndef _PRUEBASAFN_HPP_
#define _PRUEBASAFN_HPP_

#include "Pruebas.hpp"
#include "AFN.hpp"

class PruebasAFN : public Pruebas{
public:
  std::vector<Transicion*> definirTransicionesAFN(int numeroDeTransiciones, std::vector<char> alfabeto);
  bool iniciarPruebaAFN(AFN automataDePrueba);
  void probarCadenasAFN(AFN automataDePrueba);
  void crearAFN();
};

#endif
