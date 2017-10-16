#include "Automata.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

Automata::Automata(vector<Estado*> estados,vector<char> alfabeto, Estado* estadoInicial,vector<Transicion*> tablaDeTransiciones){
  automata_estados = estados;
  automata_alfabeto = alfabeto;
  automata_estadoInicial = estadoInicial;
  automata_tablaDeTransiciones = tablaDeTransiciones;
};

Automata::Automata(string archivo, string tipo){
    if(tipo=="AFN"){
      ifstream afn(archivo);
      string numSim;
      string numEdos;
      string numTran;
      string cadena;
      char simbolo;
      int i;
      int numSimbolos;
      int numEstados;
      int numTransiciones;
      int edo1,edo2;
      if(afn.is_open()){
          getline(afn,numSim);
          numSimbolos = stoi(numSim);
          for(i = 0; i < numSimbolos ; i++){
              automata_alfabeto.reserve(1);
              getline(afn,cadena);
              simbolo = cadena[0];
              automata_alfabeto.push_back(simbolo);
          }
          getline(afn,numEdos);
          numEstados = stoi(numEdos);
          automata_estados.reserve(numEstados);
          for(i = 0; i < numEstados; i++){
              automata_estados.reserve(1);
              getline(afn,cadena);
              if(cadena[0]=='s')
                  automata_estados.push_back(new Estado(i,true));
              else
                  automata_estados.push_back(new Estado(i,false));
          }
          automata_estadoInicial = automata_estados[0];
          getline(afn,numTran);
          numTransiciones = stoi(numTran);
          for(i = 0 ; i < numTransiciones ; i++){
              getline(afn,cadena);
              if(cadena[0]=='s'){
                  getline(afn,cadena);
                  edo1 = stoi(cadena);
                  getline(afn,cadena);
                  edo2 = stoi(cadena);
                  automata_tablaDeTransiciones.reserve(1);
                  automata_tablaDeTransiciones.push_back(new Transicion(edo1,edo2,'E',true));
              }
              else{
                  getline(afn,cadena);
                  edo1 = stoi(cadena);
                  getline(afn,cadena);
                  edo2 = stoi(cadena);
                  getline(afn,cadena);
                  simbolo = cadena[0];
                  automata_tablaDeTransiciones.reserve(1);
                  automata_tablaDeTransiciones.push_back(new Transicion(edo1,edo2,simbolo,false));
              }
            }
            afn.close();
          }
          else{
            cout << "No se encontro el archivo afn.txt" << endl;
          }
      }
      else if(tipo == "AFD"){
        ifstream afd(archivo);
        string numSim;
        string numEdos;
        string numTran;
        string cadena;
        char simbolo;
        int i;
        int numSimbolos;
        int numEstados;
        int numTransiciones;
        int edo1,edo2;;
        if(afd.is_open()){
            getline(afd,numSim);
            numSimbolos = stoi(numSim);
            for(i = 0; i < numSimbolos ; i++){
                automata_alfabeto.reserve(1);
                getline(afd,cadena);
                simbolo = cadena[0];
                automata_alfabeto.push_back(simbolo);
            }
            getline(afd,numEdos);
            numEstados = stoi(numEdos);
            automata_estados.reserve(numEstados);
            for(i = 0; i < numEstados; i++){
                getline(afd,cadena);
                if(cadena[0]=='s')
                    automata_estados.push_back(new Estado(i,true));
                else
                    automata_estados.push_back(new Estado(i,false));
            }
            automata_estadoInicial = automata_estados[0];
            getline(afd,numTran);
            numTransiciones = stoi(numTran);
            for(i = 0 ; i < numTransiciones ; i++){
                    getline(afd,cadena);
                    edo1 = stoi(cadena);
                    getline(afd,cadena);
                    edo2 = stoi(cadena);
                    getline(afd,cadena);
                    simbolo = cadena[0];
                    automata_tablaDeTransiciones.reserve(1);
                    automata_tablaDeTransiciones.push_back(new Transicion(edo1,edo2,simbolo));
            }
            afd.close();
          }
          else{
              cout << "No se encontro el archivo automata.txt" << endl;
          }
        }
        else
            cout << "Tipo invalido." << endl;
};

vector<Estado*> Automata::obtenerEstados(){
    return automata_estados;
}
vector<Transicion*> Automata::obtenerTablaDeTransiciones(){
    return automata_tablaDeTransiciones;
}
vector<char> Automata::obtenerAlfabeto(){
    return automata_alfabeto;
}
Estado* Automata::obtenerEstadoInicial(){
    return automata_estadoInicial;
}

void Automata::toString(string tipo){
  int i;
  int k = automata_estados.size();
  cout << "\n"<< tipo << "= {" << endl;
  cout << "\tQ = { ";
  for(i = 0 ; i < k ; i++){
    if(i != 0 && i != k-1 ){
      cout << "q" << automata_estados[i]->numeroDeEstado << ", ";
    }
    else if(i==0){
      cout << " q0 ,";
    }
    else{
      cout << "q" << automata_estados[i]->numeroDeEstado << " ";
    }
  }
  cout << "\t} , " << endl;
  cout << "\tΣ = {" << " ";
  for(i = 0 ; i < (int)automata_alfabeto.size() ; i++){
    if(i != (int)automata_alfabeto.size()-1)
      cout << automata_alfabeto[i] << ", ";
    else
      cout << automata_alfabeto[i] << " } ," << endl;
  }
  cout << "\tq0," << endl;
  cout << "\tδ = {" << endl;
  for(i = 0 ; i < (int)automata_tablaDeTransiciones.size() ; i++){
    cout << "\t\tδ(q" << automata_tablaDeTransiciones[i]->estadoActual;
    cout << " , " << automata_tablaDeTransiciones[i]->simboloDeTransicion;
    cout << ") = q" << automata_tablaDeTransiciones[i]->estadoDeTransicion;
    cout << endl;
  }
  cout << "\t}," << endl;cout << "\tQf = { ";
  for(i = 0 ; i < (int)automata_estados.size() ; i++){
    if(automata_estados[i]->esFinal){
      if(i != (int)(automata_estados.size()-1))
        cout << "q" << automata_estados[i]->numeroDeEstado << ", ";
      else
        cout << "q" << automata_estados[i]->numeroDeEstado;
    }
  }
  cout << " }" << endl;
  cout << "}" << endl;
}
