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

AFN PruebasAFN::convertirERaAFN(string expresionRegular){
  AFN afn;
  Estado* e = afn.obtenerEstadoInicial();
  string subexpresion;
  int i = 0;
  int j;
  int k;
  int balanceo = 0;
  int cadlen = expresionRegular.size();
  while(i < cadlen){
    if(expresionRegular[i] == '('){
      j = i + 1;
      balanceo++;
      while(true){
        if(expresionRegular[j] == ')'){
          balanceo--;
          if(balanceo == 0){
            break;
          }
        }
        else if(expresionRegular[i] == '('){
          balanceo++;
        }
        j++;
      }
      subexpresion = expresionRegular.substr(i+1,j-1);
      AFN subAfn = convertirERaAFN(subexpresion);
      if(j != cadlen-1 && expresionRegular[j+1] == '*'){
        //kleen de el sub afn
      }
      else if(j != cadlen-1 && expresionRegular[j+1] == '+'){
        //positiva de el sub afn
      }
      vector<Transicion*> transiciones; 
      vector<Transicion*> transiciones2; 
      transiciones = obtenerTransiciones(subAfn.obtenerEstadoInicial(),subAfn.obtenerTablaDeTransiciones());
      int tamanioTabla = transiciones.size();
      for(k = 0 ; k < tamanioTabla ; k++){
        afn.automata_tablaDeTransiciones.reserve(1);
        afn.automata_tablaDeTransiciones.push_back(transiciones[k]);
      }
      transiciones2 = obtenerTransicionesInicial(subAfn.obtenerEstadoInicial(),afn.obtenerEstadoFinal(),subAfn.obtenerTablaDeTransiciones());
      tamanioTabla = transiciones2.size();
      for(k = 0 ; k < tamanioTabla ; k++){
        afn.automata_tablaDeTransiciones.reserve(1);
        afn.automata_tablaDeTransiciones.push_back(transiciones2[k]);
      }
      i = j+1;
    }
    if(isalpha(expresionRegular[i])){
      //concatenar
    }
    else if(expresionRegular[i] == '*'){
      //kleen del ultimo estado
    }
    else if(expresionRegular[i] == '+'){
      //
    }
    else if(expresionRegular[i] == '|'){
      AFN subAfnUnion;
      //Union
    }
  }
  return afn;
}

vector<Transicion*> PruebasAFN::obtenerTransiciones(Estado* estadoInicial, std::vector<Transicion*> transiciones){
  int numeroDeEstado = estadoInicial->numeroDeEstado;
  int estado1;
  int estado2;
  char simbolo;
  vector<Transicion*> nuevasTransiciones;
  for(int i = 0 ; i < (int)transiciones.size() ; i++){
    if(transiciones[i]->estadoDeTransicion != numeroDeEstado && transiciones[i]->estadoActual != numeroDeEstado){
      estado1 = transiciones[i]->estadoActual;
      estado2 = transiciones[i]->estadoDeTransicion;
      simbolo = transiciones[i]->simboloDeTransicion;
      nuevasTransiciones.reserve(1);
      nuevasTransiciones.push_back(new Transicion(estado1,estado2,simbolo));
    }
  }
  return nuevasTransiciones; 
}

vector<Transicion*> PruebasAFN::obtenerTransicionesInicial(Estado* estadoInicial, Estado* estadoFinal, std::vector<Transicion*> transiciones){
  int numeroDeEstado = estadoInicial->numeroDeEstado;
  int numeroDeEstadoFinal = estadoFinal->numeroDeEstado;
  int estado1;
  int estado2;
  char simbolo;
  vector<Transicion*> nuevasTransiciones;
  for(int i = 0 ; i < (int)transiciones.size() ; i++){
    if(transiciones[i]->estadoDeTransicion == numeroDeEstado && transiciones[i]->estadoActual == numeroDeEstado){
      estado1 = numeroDeEstadoFinal;
      estado2 = numeroDeEstadoFinal;
      simbolo = transiciones[i]->simboloDeTransicion;
      nuevasTransiciones.reserve(1);
      nuevasTransiciones.push_back(new Transicion(estado1,estado2,simbolo));
    }
    else if(transiciones[i]->estadoDeTransicion == numeroDeEstado){
      estado1 = transiciones[i]->estadoActual;
      estado2 = numeroDeEstadoFinal;
      simbolo = transiciones[i]->simboloDeTransicion;
      nuevasTransiciones.reserve(1);
      nuevasTransiciones.push_back(new Transicion(estado1,estado2,simbolo));
    }
    else if(transiciones[i]->estadoActual == numeroDeEstado){
      estado1 = numeroDeEstadoFinal;
      estado2 = transiciones[i]->estadoDeTransicion;
      simbolo = transiciones[i]->simboloDeTransicion;
      nuevasTransiciones.reserve(1);
      nuevasTransiciones.push_back(new Transicion(estado1,estado2,simbolo));
    }
  }
  return nuevasTransiciones; 
}
