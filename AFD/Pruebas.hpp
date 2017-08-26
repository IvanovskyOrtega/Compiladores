#ifndef _PRUEBAS_HPP_
#define _PRUEBAS_HPP_

#include "Estado.hpp"
#include "Transicion.hpp"
#include <vector>

using namespace std;

class Pruebas{
public:
  Pruebas();
  bool buscarSimbolo(vector<char> alfabeto, char simbolo);
  vector<char> definirAlfabeto(int numeroDeSimbolos);
  vector<Estado*> agregarEstados(int numeroDeEstados);
  vector<Transicion*> definirTransiciones(int numeroDeTransiciones, vector<char> alfabeto);
};

#endif // _PRUEBAS_HPP_
