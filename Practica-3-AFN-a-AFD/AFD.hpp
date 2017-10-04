#ifndef _AFD_HPP_
#define _AFD_HPP_

#include "Automata.hpp"

class AFD : public Automata{
public:
  AFD(std::string archivo, std::string tipo):Automata(archivo, tipo){};
  AFD(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, std::vector<Transicion*> tablaDeTransiciones):Automata(estados, alfabeto, estadoInicial, tablaDeTransiciones){};
  bool cambiarDeEstadoAFD(std::vector<Estado*> estados, std::vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, std::string cadena, char simbolo, int indice);
};

#endif

/**
  REPORTE:
    INTRODUCCIÓN
    DESARROLLO
    RESULTADOS
    CONCLUSIONES
  PRÁCTICA 1:
    DISEÑAR E IMPLEMENTAR LAS CLASES AFN Y AFD
  PRÁCTICA 2:
    CONVERTIR UNA EXPRESION REGULAR A UN AFN POR THOMPSON
  PRÁCTICA 3:
    CONVERTIR UN AFN A AFD POR SUBCONJUNTOS
**/
