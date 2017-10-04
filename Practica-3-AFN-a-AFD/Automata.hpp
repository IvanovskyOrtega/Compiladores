#pragma once
#ifndef _AUTOMATA_HPP_
#define _AUTOMATA_HPP

#include "Estado.hpp"
#include "Transicion.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Automata{
public:
    std::vector<Estado*> automata_estados;
    std::vector<char> automata_alfabeto;
    Estado* automata_estadoInicial;
    Estado* automata_estadoFinal;
    std::vector<Transicion*> automata_tablaDeTransiciones;
    Automata();
    Automata(std::string archivo, std::string tipo);
    Automata(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, std::vector<Transicion*> tablaDeTransiciones);
    Automata(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, Estado* estadoFinal, std::vector<Transicion*> tablaDeTransiciones);
    std::vector<Estado*> obtenerEstados();
    std::vector<Transicion*> obtenerTablaDeTransiciones();
    std::vector<char> obtenerAlfabeto();
    Estado* obtenerEstadoInicial();
    Estado* obtenerEstadoFinal();
    std::vector<Estado*> obtenerEstadosFinales();
    void toString(std::string tipo);
};

#endif
