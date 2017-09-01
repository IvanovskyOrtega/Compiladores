#ifndef _PRUEBAS_HPP_
#define _PRUEBAS_HPP_

#include <iostream>
#include <vector>
#include "Estado.hpp"
#include "Transicion.hpp"

class Pruebas{
public:
  Pruebas();
  bool buscarSimbolo(std::vector<char> alfabeto, char simbolo);
  std::vector<char> definirAlfabeto(int numeroDeSimbolos);
  std::vector<Estado*> agregarEstados(int numeroDeEstados);
};

#endif // _PRUEBAS_HPP_
