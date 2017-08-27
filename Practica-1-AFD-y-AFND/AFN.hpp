#ifndef _AFN_HPP_
#define _AFN_HPP_

#include <vector>
#include "Estado.hpp"
#include "Transicion.hpp"

using namespace std;

class AFN{
private:
  vector<Estado*> afn_estados;
  vector<char> afn_alfabeto;
  Estado* afn_estadoInicial;
  vector<Transicion*> afn_tablaDeTransiciones;
public:
  void toString();
  vector<Estado*> obtenerEstados();
  vector<Transicion*> obtenerTransiciones();
  Estado* obtenerEstadoInicial();
  AFN(vector<Estado*> estados, vector<char> alfabeto, Estado* estadoInicial, vector<Transicion*> tablaDeTransiciones);
  AFN();
};

#endif
