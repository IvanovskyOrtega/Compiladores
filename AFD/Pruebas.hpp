#ifndef _PRUEBAS_HPP_
#define _PRUEBAS_HPP_

#include "AFD.hpp"
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
  bool cambiarDeEstado(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice);
  bool iniciarPrueba(AFD automataDePrueba);
  void probarCadenas(AFD automataDePrueba);
};

#endif // _PRUEBAS_HPP_
