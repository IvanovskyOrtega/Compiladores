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
    void renumerarEstados(AFN* subafn, int numero);
    bool buscarEnAlfabeto(AFN* afn, char c);
    void agregarSimboloAlAlfabeto(AFN* afn, char c);
    void copiarAlfabeto(AFN* afn, AFN subafn);
    void agregarTransicion(AFN* afn, int estado1, int estado2, char simbolo, bool esEpsilon);
    void agregarTransicionEpsilon(AFN* afn, Estado* estado1,Estado* estado2);
    void agregarTransiciones(AFN* afn, std::vector<Transicion*> tablaDeTransiciones);
    void agregarEstados(AFN* afn, std::vector<Estado*> estados);
    void eliminarEstadoFinal(AFN* afn);
    void eliminarEstadoInicial(AFN *afn);
    void modificarTransiciones(AFN* afn, int antiguo, int nuevo);
    void swapTransiciones(AFN* afn, int antiguo, int nuevo);
    void renumerarEstado(AFN *afn, int antiguo, int nuevo);
    void concatenar(AFN* afn, char simbolo, bool esEpsilon);
    void unir(AFN* afn, AFN subafn);
    void aplicarCerraduraKleenAFN(AFN *afn);
    void aplicarCerraduraKleen(AFN* afn, char c, bool esEpsilon);
    void aplicarCerraduraPositivaAFN(AFN *afn);
    void aplicarCerraduraPositiva(AFN* afn, char c, bool esEpsilon);
    void generarArchivoAFN(AFN afn);
    Estado* obtenerEstado(int numeroDeEstado);
    std::vector<char> obtenerAlfabeto();
};

#endif
