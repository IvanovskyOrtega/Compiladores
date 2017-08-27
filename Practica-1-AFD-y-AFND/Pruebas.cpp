#include <iostream>
#include <cstring>
#include <string>
#include "Pruebas.hpp"
#include "AFN.hpp"
#include "AFD.hpp"
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

/**
    Esta funcion permite  definir las transiciones del automata AFD.
**/
vector<Transicion*> Pruebas::definirTransicionesAFD(int numeroDeTransiciones, vector<char> alfabeto){
  vector<Transicion*> transiciones;
  int estado1;
  int estado2;
  char simbolo;
  for(int i = 0; i < numeroDeTransiciones; i++){
    cout << "\nIngresa el numero del primer estado: ";
    cin >> estado1;
    cout << "\nIngresa el numero del segundo estado: ";
    cin >> estado2;
    cout << "\nIngresa el simbolo de transicion: ";
    cin >> simbolo;
    while(Pruebas::buscarSimbolo(alfabeto, simbolo)==false){
        cout << "\nIngresa un simbolo que pertenezca al alfabeto: ";
        cin >> simbolo;
    }
    transiciones.reserve(1);
    transiciones.push_back(new Transicion(estado1,estado2,simbolo));
  }
  return transiciones;
}

/**
    Esta funcion permite  definir las transiciones del automata AFN.
**/
vector<Transicion*> Pruebas::definirTransicionesAFN(int numeroDeTransiciones, vector<char> alfabeto){
  vector<Transicion*> transiciones;
  int estado1;
  int estado2;
  char simbolo;
  char esEpsilon;
  for(int i = 0; i < numeroDeTransiciones; i++){
    cout << "La transicion " << i << " es una transicion epsilon? (s/n)" << endl;
    cin >> esEpsilon;
    if(esEpsilon == 's' || esEpsilon == 'S'){
      cout << "\nIngresa el numero del primer estado: ";
      cin >> estado1;
      cout << "\nIngresa el numero del segundo estado: ";
      cin >> estado2;
      transiciones.reserve(1);
      transiciones.push_back(new Transicion(estado1,estado2,'E',true));
    }
    else{
      cout << "\nIngresa el numero del primer estado: ";
      cin >> estado1;
      cout << "\nIngresa el numero del segundo estado: ";
      cin >> estado2;
      cout << "\nIngresa el simbolo de transicion: ";
      cin >> simbolo;
      cout << "\n";
      while(Pruebas::buscarSimbolo(alfabeto, simbolo)==false){
        cout << "\nIngresa un simbolo que pertenezca al alfabeto: ";
        cin >> simbolo;
      }
      transiciones.reserve(1);
      transiciones.push_back(new Transicion(estado1,estado2,simbolo,false));
    }
  }
  return transiciones;
}

bool Pruebas::cambiarDeEstadoAFD(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice){
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

bool Pruebas::cambiarDeEstadoAFN(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice){
  int i;
  int k = tablaDeTransiciones.size();
  bool camino1, camino2, tieneTransicion = false;
  if(indice < (int)cadena.size()){
    indice++;
    cout << endl;
    for(i = 0; i < k; i++){
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->esTransicionEpsilon){
            tieneTransicion = true;
            cout << "Camino 2" << endl;
            indice--;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << ", E)";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            camino2 = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
          }
          if(tablaDeTransiciones[i]->simboloDeTransicion == simbolo){
            tieneTransicion = true;
            cout << "Camino 1" << endl;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            camino1 = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estados[tablaDeTransiciones[i]->estadoDeTransicion], cadena, cadena[indice],indice);
          }
          else if(!tieneTransicion && i == k-1){
            cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
            cout << " = M" << endl;
            return false;
          }
        }
    }
    return camino1||camino2;
  }
  else
    return estadoActual->esFinal;
}

bool Pruebas::iniciarPrueba(AFD automataDePrueba){
  string cadenaDePrueba;
  cout << "Ingresa una cadena de prueba: ";
  cin >> cadenaDePrueba;
  return cambiarDeEstadoAFD(automataDePrueba.obtenerEstados(), automataDePrueba.obtenerTransiciones(), automataDePrueba.obtenerEstadoInicial(), cadenaDePrueba, cadenaDePrueba[0],0);
}

void Pruebas::probarCadenas(AFD automataDePrueba){
  char opcion;
  automataDePrueba.toString();
  while(opcion != 'n'){
    if(iniciarPrueba(automataDePrueba))
      cout << "Cadena valida" << endl;
    else
      cout << "Cadena invalida" << endl;
    cout << "Desea probar otra cadena? (s/n)" << endl;
    cin >> opcion;
  }
}

bool Pruebas::iniciarPrueba(AFN automataDePrueba){
  string cadenaDePrueba;
  cout << "Ingresa una cadena de prueba: ";
  cin >> cadenaDePrueba;
  return cambiarDeEstadoAFN(automataDePrueba.obtenerEstados(), automataDePrueba.obtenerTransiciones(), automataDePrueba.obtenerEstadoInicial(), cadenaDePrueba, cadenaDePrueba[0],0);
}

void Pruebas::probarCadenas(AFN automataDePrueba){
  char opcion;
  automataDePrueba.toString();
  while(opcion != 'n'){
    if(iniciarPrueba(automataDePrueba))
      cout << "Cadena valida" << endl;
    else
      cout << "Cadena invalida" << endl;
    cout << "Desea probar otra cadena? (s/n)" << endl;
    cin >> opcion;
  }
}

void Pruebas::crearAFD(){
  int numeroDeSimbolos, numeroDeEstados, numeroDeTransiciones;
	vector <char> alfabeto;
	vector <Estado*> estados;
	vector <Transicion*> tablaDeTransiciones;
	cout << "\nIngresa el numero de simbolos para el alfabeto del automata: ";
	cin >> numeroDeSimbolos;
	alfabeto = definirAlfabeto(numeroDeSimbolos);
	cout << "\nIngresa el numero de estados del automata: ";
	cin >> numeroDeEstados;
	estados = agregarEstados(numeroDeEstados);
	cout << "\nIngresa el numero de transiciones del automata: ";
	cin >> numeroDeTransiciones;
	tablaDeTransiciones = definirTransicionesAFD(numeroDeTransiciones, alfabeto);
	AFD afd(estados, estados[0], alfabeto, tablaDeTransiciones);
	probarCadenas(afd);
}

void Pruebas::crearAFN(){
  int numeroDeSimbolos, numeroDeEstados, numeroDeTransiciones;
	vector <char> alfabeto;
	vector <Estado*> estados;
	vector <Transicion*> tablaDeTransiciones;
	cout << "\nIngresa el numero de simbolos para el alfabeto del automata: ";
	cin >> numeroDeSimbolos;
	alfabeto = definirAlfabeto(numeroDeSimbolos);
	cout << "\nIngresa el numero de estados del automata: ";
	cin >> numeroDeEstados;
	estados = agregarEstados(numeroDeEstados);
	cout << "\nIngresa el numero de transiciones del automata: ";
	cin >> numeroDeTransiciones;
	tablaDeTransiciones = definirTransicionesAFN(numeroDeTransiciones, alfabeto);
	AFN afn(estados, alfabeto, estados[0], tablaDeTransiciones);
	probarCadenas(afn);
}
