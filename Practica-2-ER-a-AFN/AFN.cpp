#include "AFN.hpp"

using namespace std;

bool AFN::cambiarDeEstadoAFN(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice){
  int i;
  int k = tablaDeTransiciones.size();
  bool cambio, resultado = false, tieneTransicion = false;
  if(indice < (int)cadena.size()){
    indice++;
    cout << endl;
    for(i = 0; i < k; i++){
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->esTransicionEpsilon){
            tieneTransicion = true;
            indice--;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << ", E)";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
            resultado = resultado || cambio;
            indice++;
          }
          else if(tablaDeTransiciones[i]->simboloDeTransicion == simbolo){
            tieneTransicion = true;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
            resultado = resultado || cambio;
          }
        }
        else if(!tieneTransicion && i == k-1){
          cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
          cout << " = M" << endl;
          return false;
        }
    }
    return resultado;
  }
  else{
    for(i = 0; i < k; i++){
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->esTransicionEpsilon){
            tieneTransicion = true;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << ", E)";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
            resultado = resultado || cambio;
          }
        }
    }
    if(tieneTransicion)
        return resultado;
    else
        return estadoActual->esFinal;
  }
}
