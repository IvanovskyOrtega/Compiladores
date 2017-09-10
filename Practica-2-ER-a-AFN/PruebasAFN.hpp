#ifndef _PRUEBASAFN_HPP_
#define _PRUEBASAFN_HPP_

#include "Pruebas.hpp"
#include "AFN.hpp"
#include <string>

class PruebasAFN : public Pruebas{
public:
  std::vector<Transicion*> definirTransicionesAFN(int numeroDeTransiciones, std::vector<char> alfabeto);
  bool iniciarPruebaAFN(AFN automataDePrueba);
  void probarCadenasAFN(AFN automataDePrueba);
  void crearAFN();
  AFN convertirERaAFN(std::string expresionRegular);
  std::vector<Transicion*> obtenerTransiciones(Estado* estadoInicial, std::vector<Transicion*> transiciones);
  std::vector<Transicion*> obtenerTransicionesInicial(Estado* estadoInicial, Estado* estadoFinal, std::vector<Transicion*> transiciones);
};

#endif
