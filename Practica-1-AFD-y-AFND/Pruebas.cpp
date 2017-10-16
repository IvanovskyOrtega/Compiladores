#include "Pruebas.hpp"

using namespace std;

Pruebas::Pruebas(){};
/**
    Esta funcion determina si un simbolo pertenece al alfabeto
    del automata.
**/
bool Pruebas::buscarSimbolo(vector<char> alfabeto, char simbolo){
  int k = alfabeto.size();
  for(int i = 0; i < k ; i++){
    if(alfabeto[i] == simbolo)
      return true;
  }
  return false;
}

/**
    Esta funcion define el alfabeto del automata.
**/
vector<char> Pruebas::definirAlfabeto(int numeroDeSimbolos){
  vector<char> alfabetoAux; // Usamos un arreglo auxiliar
  char simbolo;
  for(int i = 0; i < numeroDeSimbolos; i++){    // Loop para inicializar el vector
    cout << "\nIngresa el simbolo " << i << ": ";
    cin >> simbolo;
    alfabetoAux.reserve(1);
    alfabetoAux.push_back(simbolo);
  }
  return alfabetoAux;   // Devolvemos el vector
}

/**
    Esta funcion permite agregar estados al automata.
**/
vector<Estado*> Pruebas::agregarEstados(int numeroDeEstados){
  char esFinal; // Variable para saber si es estado final o no
  vector<Estado*> estados; //Vector de estados
  for(int i = 0; i < numeroDeEstados; i++){
      cout << "Estado q" << i << endl;
      cout << "\tEs estado final? (s/n) : ";
      cin >> esFinal;
      if(esFinal == 's' || esFinal == 'S'){
        estados.reserve(1);
        estados.push_back(new Estado(i,true));
      }
      else if(esFinal == 'n' || esFinal == 'N'){
          estados.reserve(1);
          estados.push_back(new Estado(i,false));
      }
  }
  return estados;
}
