#ifndef _SUBCONJUNTO_HPP_
#define _SUBCONJUNTO_HPP_

#include <algorithm>
#include "AFN.hpp"
#include "AFD.hpp"

class Subconjunto{
public:
    Subconjunto(){};
    int subconjuntoActual;
    int kernelActual;
    int estadoInicial;  
    int estadoFinal;
    void iniciarAlgoritmo();
    std::vector<int> subconjunto;
    std::vector<int> kernel;
    std::vector<std::vector<int>> subconjuntos;
    std::vector<std::vector<int>> kernels;
    std::vector<Transicion*> tablaDePreprocesamiento;
    std::vector<Transicion*> transicionesAFD;
    std::vector<Estado*> estadosAFD;
    void generarTablaDePreprocesamiento(AFN afn);
    void procesarEstadoInicial(AFN afn);
    void aplicarCerraduraEpsilon(int numeroDeEstado, std::vector<Transicion*> tablaDeTransiciones);
    void aplicarCerraduraEpsilon(std::vector<int> miSubconjunto, std::vector<Transicion*> tablaDeTransiciones);
    void moverConSimbolo(std::vector<int> misubconjunto, char simbolo);
    std::vector<int> obtenerDiferencia(std::vector<int> subconjunto1, std::vector<int> subconjunto2);
    bool estaEnElSubconjunto(int estado, std::vector<int> misubconjunto);
    void agregarSubconjunto();
    void agregarKernel();
    bool existeElSubconjunto();
    bool existeElKernel();
    void imprimirMoverConSimbolo();
    void imprimirCerraduraEpsilon();
    void imprimirTransicionesAFD();
    void agregarTransicionAFD(int estado1, int estado2, char simbolo);
    void generarEstados();
    void generarArchivo(AFN *afn);
    void limpiarVectores();
};

#endif