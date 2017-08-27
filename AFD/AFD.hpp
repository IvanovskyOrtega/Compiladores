#ifndef _AFD_HPP_
#define _AFD_HPP_

#include <vector>
#include "Estado.hpp"
#include "Transicion.hpp"

using namespace std;
class AFD{
private:
  vector<Estado*> afd_estados;
  Estado* afd_estadoInicial;
  vector<char> afd_alfabeto;
  vector<Transicion*> afd_tablaDeTransiciones;
public:
  void toString();
  vector<Estado*> obtenerEstados();
  vector<Transicion*> obtenerTransiciones();
  Estado* obtenerEstadoInicial();
  AFD();
  AFD(vector<Estado*> estados, Estado* estadoInicial, vector<char> alfabeto, vector<Transicion*> tablaDeTransiciones);
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

**/
