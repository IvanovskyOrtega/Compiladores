#include <iostream>
#include <cstring>
#include "AFD.hpp"
#include "Estado.hpp"
#include "Transicion.hpp"
#include "Pruebas.hpp"

//#include "AFN.hpp"
using namespace std;

int main(int argc, char *argv[]){
  string cadenaDePrueba;
  Pruebas *p = new Pruebas();
  int numeroDeSimbolos, numeroDeEstados, numeroDeTransiciones;
  vector<char> alfabeto;
  vector<Estado*> estados;
  vector<Transicion*> tablaDeTransiciones;
  cout << "Ingresa el numero de simbolos para el alfabeto del automata: ";
  cin >> numeroDeSimbolos;
  alfabeto = p->definirAlfabeto(numeroDeSimbolos);
  cout << "Ingresa el numero de estados del automata: ";
  cin >> numeroDeEstados;
  estados = p->agregarEstados(numeroDeEstados);
  cout << "Ingresa el numero de transiciones del automata: ";
  cin >> numeroDeTransiciones;
  tablaDeTransiciones = p->definirTransiciones(numeroDeTransiciones, alfabeto);
  AFD afd(estados,estados[0],alfabeto,tablaDeTransiciones);
  afd.toString();
  cout << "Ingresa una cadena de prueba: ";
  cin >> cadenaDePrueba;
  //iniciarPrueba(afd, cadenaDePrueba);
  return 0;
}
