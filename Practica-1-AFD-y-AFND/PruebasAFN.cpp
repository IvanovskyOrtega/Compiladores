#include "PruebasAFN.hpp"

/**
    Esta funcion permite  definir las transiciones del automata AFN.
**/
vector<Transicion*> PruebasAFN::definirTransicionesAFN(int numeroDeTransiciones, vector<char> alfabeto){
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

bool PruebasAFN::iniciarPruebaAFN(AFN automataDePrueba){
  string cadenaDePrueba;
  cout << "Ingresa una cadena de prueba: ";
  cin >> cadenaDePrueba;
  return automataDePrueba.cambiarDeEstadoAFN(automataDePrueba.Automata::obtenerEstados(), automataDePrueba.Automata::obtenerTablaDeTransiciones(), automataDePrueba.Automata::obtenerEstadoInicial(), cadenaDePrueba, cadenaDePrueba[0],0);
}

void PruebasAFN::probarCadenasAFN(AFN automataDePrueba){
  char opcion;
  automataDePrueba.Automata::toString("AFN");
  while(opcion != 'n'){
    if(iniciarPruebaAFN(automataDePrueba))
      cout << "Cadena valida" << endl;
    else
      cout << "Cadena invalida" << endl;
    cout << "Desea probar otra cadena? (s/n)" << endl;
    cin >> opcion;
  }
}

void PruebasAFN::crearAFN(){
    char opcion;
    cout << "Crear desde archivo? (s/n)" << endl;
    cin >> opcion;
    if(opcion == 's'){
        AFN afn("afn.txt","AFN");
        probarCadenasAFN(afn);
    }
    else{
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
        probarCadenasAFN(afn);
    }
}
