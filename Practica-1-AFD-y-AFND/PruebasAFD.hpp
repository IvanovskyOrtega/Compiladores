#ifndef _PRUEBASAFD_HPP_
#define _PRUEBASAFD_HPP_

#include "Pruebas.hpp"
#include "AFD.hpp"

class PruebasAFD : public Pruebas{
public:
  std::vector<Transicion*> definirTransicionesAFD(int numeroDeTransiciones, std::vector<char> alfabeto);
  bool iniciarPruebaAFD(AFD automataDePrueba);
  void probarCadenasAFD(AFD automataDePrueba);
  void crearAFD();
};

#endif
