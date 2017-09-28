#include "AFD.hpp"

using namespace std;

/**
 * Esta función realiza el cambio de estados (funcion de transicion), de un AFD
 * Recibe:
 *  -vector<Estado*> estados :: vector de estados del AFD
 *  -vector<Transicion*> tablaDeTransiciones :: tabla de transiciones del AFD
 *  -Estado* estadoActual :: El estado en el que se encuentra.
 *  -string cadena :: La cadena a evaluar
 *  -char simbolo :: El simbolo de transicion
 *  -int indice :: La posicion actual de la cadena
 * Regresa:
 *  -true :: Si la cadena fue validada
 *  -false :: Si la cadena no fue validada
 * **/
bool AFD::cambiarDeEstadoAFD(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice){
  int i;
  int k = tablaDeTransiciones.size();
  if(indice < (int)cadena.size()){
    indice++;
    cout << endl;
    for(i = 0; i < k; i++){
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->simboloDeTransicion == simbolo){
            cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            return cambiarDeEstadoAFD(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
          }
        }
    }
    cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
    cout << " = M" << endl;
    return false;
  }
  else
    return estadoActual->esFinal;
}
