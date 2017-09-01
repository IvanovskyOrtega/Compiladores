#pragma once
#ifndef _AUTOMATA_HPP_
#define _AUTOMATA_HPP

#include "Estado.hpp"
#include "Transicion.hpp"
#include <vector>
#include <string>
#include <iostream>

class Automata{
protected:
    std::vector<Estado*> automata_estados;
    std::vector<char> automata_alfabeto;
    Estado* automata_estadoInicial;
    std::vector<Transicion*> automata_tablaDeTransiciones;
public:
    Automata(std::string archivo, std::string tipo);
    Automata(std::vector<Estado*> estados, std::vector<char> alfabeto, Estado* estadoInicial, std::vector<Transicion*> tablaDeTransiciones);
    std::vector<Estado*> obtenerEstados();
    std::vector<Transicion*> obtenerTablaDeTransiciones();
    std::vector<char> obtenerAlfabeto();
    Estado* obtenerEstadoInicial();
    void toString(std::string tipo);
};

#endif
