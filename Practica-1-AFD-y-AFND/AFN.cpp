#include <iostream>
#include <vector>
#include "AFN.hpp"
#include "Estado.hpp"
#include "Transicion.hpp"

using namespace std;

/** CONSTRUCTORES **/

AFN::AFN(vector<Estado*> estados, vector<char> alfabeto, Estado* estadoInicial, vector<Transicion*> tablaDeTransiciones){
    afn_estados = estados;
    afn_estadoInicial = estadoInicial;
    afn_alfabeto = alfabeto;
    afn_tablaDeTransiciones = tablaDeTransiciones;
};

AFN::AFN(){};

vector<Estado*> AFN::obtenerEstados(){
  return afn_estados;
}

vector<Transicion*> AFN::obtenerTransiciones(){
  return afn_tablaDeTransiciones;
}

Estado* AFN::obtenerEstadoInicial(){
  return afn_estadoInicial;
}

void AFN::toString(){
  int i;
  int k = afn_estados.size();
  cout << "\nAFN = {" << endl;
  cout << "\tQ = { ";
  for(i = 0 ; i < k ; i++){
    if(i != 0 && i != k-1 ){
      cout << "q" << afn_estados[i]->numeroDeEstado << ", ";
    }
    else if(i==0){
      cout << " q0 ,";
    }
    else{
      cout << "q" << afn_estados[i]->numeroDeEstado << " ";
    }
  }
  cout << " } , " << endl;
  cout << "\tΣ = {" << " ";
  for(i = 0 ; i < (int)afn_alfabeto.size() ; i++){
    if(i != (int)afn_alfabeto.size()-1)
      cout << afn_alfabeto[i] << ", ";
    else
      cout << afn_alfabeto[i] << " } ," << endl;
  }
  cout << "\tq0," << endl;
  cout << "\tδ = {" << endl;
  for(i = 0 ; i < (int)afn_tablaDeTransiciones.size() ; i++){
    cout << "\t\tδ(q" << afn_tablaDeTransiciones[i]->estadoActual;
    cout << " , " << afn_tablaDeTransiciones[i]->simboloDeTransicion;
    cout << ") = q" << afn_tablaDeTransiciones[i]->estadoDeTransicion;
    cout << endl;
  }
  cout << "\t}," << endl;cout << "\tQf = { ";
  for(i = 0 ; i < (int)afn_estados.size() ; i++){
    if(afn_estados[i]->esFinal){
      if(i != (int)(afn_estados.size()-1))
        cout << "q" << afn_estados[i]->numeroDeEstado << ", ";
      else
        cout << "q" << afn_estados[i]->numeroDeEstado;
    }
  }
  cout << " }" << endl;
  cout << "}" << endl;
}
