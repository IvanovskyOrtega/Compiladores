#include "PruebasAFD.hpp"

/**
    Esta funcion permite  definir las transiciones del automata AFD.
    Recibe: 
      - int numeroDeTransiciones :: El numero de transiciones a definir
      - vector<char> alfabeto :: El alfabeto del automata
    Regresa:
      - vector<Transicion*> transiciones :: La tabla de transiciones del AFD
**/
vector<Transicion*> PruebasAFD::definirTransicionesAFD(int numeroDeTransiciones, vector<char> alfabeto){
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
 * Esta funcion ejecuta pruebas con cadenas en un automata AFD.
 * Recibe:
 *  -AFD automataDePrueba :: Automata para la prueba.
 * Regresa:
 *  -true :: si la cadena fue reconocida por el AFD
 *  -false :: si la cadena no fue reconocida por el AFD
 * **/
bool PruebasAFD::iniciarPruebaAFD(AFD automataDePrueba){
  string cadenaDePrueba;
  cout << "Ingresa una cadena de prueba: ";
  cin >> cadenaDePrueba;
  return automataDePrueba.cambiarDeEstadoAFD(automataDePrueba.Automata::obtenerEstados(), automataDePrueba.Automata::obtenerTablaDeTransiciones(), automataDePrueba.Automata::obtenerEstadoInicial(), cadenaDePrueba, cadenaDePrueba[0],0);
}

/**
 * Esta funcion prueba una cadena en un AFD con base a su funcion
 * de transicion.
 * Recibe:
 *  - AFD automataDePrueba :: El automata AFD a probar
 * **/
void PruebasAFD::probarCadenasAFD(AFD automataDePrueba){
  char opcion;
  while(opcion != 'n'){
    if(iniciarPruebaAFD(automataDePrueba))
      cout << "Cadena valida" << endl;
    else
      cout << "Cadena invalida" << endl;
    cout << "Desea probar otra cadena? (s/n)" << endl;
    cin >> opcion;
  }
}

/**
 * Esta funcion permite crear un AFD a partir de un archivo
 * o ingresando informacion desde consola.
 * **/
void PruebasAFD::crearAFD(){
    char opcion;
    cout << "Cargar desde archivo? (s/n)" << endl;
    cin >> opcion;
    if(opcion == 's'){
        AFD afd("afd.txt","AFD");
        afd.toString("AFD");
        probarCadenasAFD(afd);
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
        tablaDeTransiciones = definirTransicionesAFD(numeroDeTransiciones, alfabeto);
        AFD afd(estados, alfabeto, estados[0], tablaDeTransiciones);
        probarCadenasAFD(afd);
    }
}
