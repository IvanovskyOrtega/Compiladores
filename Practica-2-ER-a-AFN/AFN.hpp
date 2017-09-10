#ifndef _AFN_HPP_
#define _AFN_HPP_

#include "Automata.hpp"

class AFN: public Automata{
public:
    AFN():Automata(){};
    AFN(std::string archivo, std::string tipo):Automata(archivo, tipo){};
    AFN(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, std::vector<Transicion*> tablaDeTransiciones):Automata(estados, alfabeto, estadoInicial, tablaDeTransiciones){};
    AFN(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, Estado* estadoFinal, std::vector<Transicion*> tablaDeTransiciones):Automata(estados, alfabeto, estadoInicial, tablaDeTransiciones){};
    bool cambiarDeEstadoAFN(std::vector<Estado*> estados, std::vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, std::string cadena, char simbolo, int indice);

};

#endif
