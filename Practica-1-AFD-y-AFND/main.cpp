#include <iostream>
#include <cstring>
#include "PruebasAFD.hpp"
#include "PruebasAFN.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  char tipoAutomata, opcion;
	PruebasAFD *p1 = new PruebasAFD();
	PruebasAFN *p2 = new PruebasAFN();
  while(opcion != 'n'){
	   cout << "Ingrese el tipo de automata que desea crear:" << endl;
     cout << "1\tAutomata Finito Determinista (AFD)" << endl;
     cout << "2\tAutomata Finito No Determinista (AFN)" << endl;
     cout << "Ingrese su seleccion: ";
     cin >> tipoAutomata;
     switch(tipoAutomata){
       case '1':
        p1->crearAFD(); break;
       case '2':
        p2->crearAFN(); break;
       default:
        cout << "Opcion no valida" << endl;
     }
     cout << "Desea crear otro automata? (s/n)";
     cin >> opcion;
  }
	return 0;
}
