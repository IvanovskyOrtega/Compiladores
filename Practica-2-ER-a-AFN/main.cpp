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
  string cadena;
  AFN afn;
  while(opcion != 'n'){
     cout << "Ingrese el tipo de automata que desea crear:" << endl;
     cout << "1\tAutomata Finito Determinista (AFD)" << endl;
     cout << "2\tAutomata Finito No Determinista (AFN)" << endl;
     cout << "3\tER a AFN (Contrucciones de Thompson)" << endl;
     cout << "Ingrese su seleccion: ";
     cin >> tipoAutomata;
     switch(tipoAutomata){
       case '1':
        p1->crearAFD(); break;
       case '2':
        p2->crearAFN(); break;
       case '3':
        cout << "Ingresa una ER: ";
        cin >> cadena;
        afn = p2->convertirERaAFN(cadena);
        p2->probarCadenasAFN(afn);
        break;
       default:
        cout << "Opcion no valida" << endl;
     }
     cout << "Desea crear otro automata? (s/n):" << endl;
     cin >> opcion;
  }
	return 0;
}
