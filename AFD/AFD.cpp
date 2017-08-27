#include <iostream>
#include "AFD.hpp"
#include "Estado.hpp"
#include "Transicion.hpp"

using namespace std;

/** CONSTRUCTORES **/

AFD::AFD(vector<Estado*> estados, Estado* estadoInicial, vector<char> alfabeto, vector<Transicion*> tablaDeTransiciones){
    afd_estados = estados;
    afd_estadoInicial = estadoInicial;
    afd_alfabeto = alfabeto;
    afd_tablaDeTransiciones = tablaDeTransiciones;
};

AFD::AFD(){};

vector<Estado*> AFD::obtenerEstados(){
  return afd_estados;
}

vector<Transicion*> AFD::obtenerTransiciones(){
  return afd_tablaDeTransiciones;
}

Estado* AFD::obtenerEstadoInicial(){
  return afd_estadoInicial;
}

void AFD::toString(){
  int i;
  cout << "\nAFD = {" << endl;
  cout << "\tQ = {" << endl;
  for(i = 0 ; i < (int)afd_estados.size() ; i++){
    if(i != 0){
      cout << "\t\tq" << afd_estados[i]->numeroDeEstado;
      if(afd_estados[i]->esFinal)
        cout << " (final)" << endl;
    }
    else{
      cout << "\t\tq0 ," << endl;
    }
  }
  cout << "\t} , " << endl;
  cout << "\tΣ = {" << " ";
  for(i = 0 ; i < (int)afd_alfabeto.size() ; i++){
    if(i != (int)afd_alfabeto.size()-1)
      cout << afd_alfabeto[i] << ", ";
    else
      cout << afd_alfabeto[i] << " } ," << endl;
  }
  cout << "\tq0," << endl;
  cout << "\tδ = {" << endl;
  for(i = 0 ; i < (int)afd_tablaDeTransiciones.size() ; i++){
    cout << "\t\tδ(q" << afd_tablaDeTransiciones[i]->estadoActual;
    cout << " , " << afd_tablaDeTransiciones[i]->simboloDeTransicion;
    cout << ") = q" << afd_tablaDeTransiciones[i]->estadoDeTransicion;
    cout << endl;
  }
  cout << "\t}," << endl;cout << "\tQf = {" << endl;
  for(i = 0 ; i < (int)afd_estados.size() ; i++){
    if(afd_estados[i]->esFinal){
      if(i != (int)(afd_estados.size()-1))
        cout << "\t\tq" << afd_estados[i]->numeroDeEstado << "," << endl;
      else
        cout << "\t\tq" << afd_estados[i]->numeroDeEstado << endl;
    }
  }
  cout << "\t} , " << endl;
  cout << "}" << endl;
}
