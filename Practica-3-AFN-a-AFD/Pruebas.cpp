#include "Pruebas.hpp"

using namespace std;

/**
 * Constructor
 * **/
Pruebas::Pruebas(){};

/**
    Esta funcion determina si un simbolo pertenece al alfabeto
    del automata.
    Recibe:
      - vector<char> alfabeto :: El alfabeto del automata
      - char simbolo :: El simbolo a buscar en el automata
    Regresa:
      - true :: si se encontro el simbolo
      - false :: si no se encontro el simbolo
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
    Recibe:
      - int numeroDeSimbolos :: El numero de simbolos del alfabeto
    Regresa:
      - vector<char> alfabetoAux :: El alfabeto generado
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
    Recibe:
      - int numeroDeEstados :: la cantidad de estados a agregar.
    Regresa:
      - vector<Estado*> estados :: El vector de estados
**/
vector<Estado*> Pruebas::agregarEstados(int numeroDeEstados){
  char esFinal; // Variable para saber si es estado final o no
  vector<Estado*> estados; //Vector de estados
  for(int i = 0; i < numeroDeEstados; i++){
    if(i != 0){
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
    else{
      cout << "\nEstado inicial q0" << endl;
      estados.reserve(1);
      estados.push_back(new Estado(i,false));
    }
  }
  return estados;
}
