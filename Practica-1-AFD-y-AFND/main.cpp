#include <iostream>
#include <cstring>
#include "AFD.hpp"
#include "AFN.hpp"
#include "Estado.hpp"
#include "Transicion.hpp"
#include "Pruebas.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  char tipoAutomata, opcion;
	Pruebas *p = new Pruebas();
  while(opcion != 'n'){
	   cout << "Ingrese el tipo de automata que desea crear:" << endl;
     cout << "1\tAutomata Finito Determinista (AFD)" << endl;
     cout << "2\tAutomata Finito No Determinista (AFN)" << endl;
     cout << "Ingrese su seleccion: ";
     cin >> tipoAutomata;
     switch(tipoAutomata){
       case '1':
        p->crearAFD(); break;
       case '2':
        p->crearAFN(); break;
       default:
        cout << "Opcion no valida" << endl;
     }
     cout << "Desea crear otro automata? (s/n)" << endl;
     cin >> opcion;
  }
	return 0;
}
