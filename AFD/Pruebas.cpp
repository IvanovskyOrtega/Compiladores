#include <iostream>
#include "Pruebas.hpp"
#include <vector>

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
    else
      return false;
  }
  return false;
}

/**
    Esta funcion define el alfabeto del automata.
**/
vector<char> Pruebas::definirAlfabeto(int numeroDeSimbolos){
  vector<char> alfabetoAux(numeroDeSimbolos); // Usamos un arreglo auxiliar
  char simbolo;
  for(int i = 0; i < numeroDeSimbolos; i++){    // Loop para inicializar el vector
    cout << "Ingresa el simbolo " << i << ": ";
    cin >> simbolo;
    alfabetoAux[i] = simbolo;
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
      cout << "Estado inicial q0" << endl;
      estados.reserve(1);
      estados.push_back(new Estado(i,false));
    }
  }
  return estados;
}

/**
    Esta funcion permite  definir las transiciones del automata.
**/
vector<Transicion*> Pruebas::definirTransiciones(int numeroDeTransiciones, vector<char> alfabeto){
  vector<Transicion*> transiciones;
  for(int i = 0; i < numeroDeTransiciones; i++){
    int estado1;
    int estado2;
    char simbolo;
    cout << "Ingresa el numero del primer estado: ";
    cin >> estado1;
    cout << "Ingresa el numero del segundo estado: ";
    cin >> estado2;
    cout << "Ingresa el simbolo de transicion: ";
    cin >> simbolo;
    while(!Pruebas::buscarSimbolo(alfabeto, simbolo)){
        cout << "Ingresa un simbolo que pertenezca al alfabeto: ";
        cin >> simbolo;
    }
    transiciones.reserve(1);
    transiciones.push_back(new Transicion(estado1,estado2,simbolo));
  }
  return transiciones;
}
