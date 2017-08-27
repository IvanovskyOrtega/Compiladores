#ifndef _PRUEBAS_HPP_
#define _PRUEBAS_HPP_

#include "AFD.hpp"
#include "AFN.hpp"
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
  vector<Transicion*> definirTransicionesAFD(int numeroDeTransiciones, vector<char> alfabeto);
  vector<Transicion*> definirTransicionesAFN(int numeroDeTransiciones, vector<char> alfabeto);
  bool cambiarDeEstadoAFD(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice);
  bool cambiarDeEstadoAFN(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice);
  bool iniciarPrueba(AFD automataDePrueba);
  bool iniciarPrueba(AFN automataDePrueba);
  void probarCadenas(AFD automataDePrueba);
  void probarCadenas(AFN automataDePrueba);
  void crearAFD();
  void crearAFN();
};

#endif // _PRUEBAS_HPP_
