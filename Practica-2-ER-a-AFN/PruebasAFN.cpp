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
  string subexpresion;
  int i = 0;
  int j;
  int balanceo = 0;
  int cadlen = expresionRegular.size();
  bool parentesis = true;
  while(i < cadlen){
    balanceo = 0;
    parentesis = true;
    j=0;
    if(expresionRegular[i] == '('){
      j = i + 1;
      balanceo++;
      while(parentesis && j < cadlen){
        if(expresionRegular[j] == ')'){
          balanceo--;
          if(balanceo == 0){
            parentesis = false;
          }
        }
        else if(expresionRegular[j] == '('){
          balanceo++;
        }
        j++;
      }
      subexpresion = expresionRegular.substr(i+1,j-2-(i));
      AFN subAfn = convertirERaAFN(subexpresion);
      if(j < cadlen){
        if(expresionRegular[j] == '*'){
          //kleen de el sub afn
          afn.aplicarCerraduraKleenAFN(&subAfn);
          j++;
        }
        else if(expresionRegular[j] == '+'){
          //positiva de el sub afn
          afn.aplicarCerraduraPositivaAFN(&subAfn);
          j++;
        }
      }
      afn.copiarAlfabeto(&afn,subAfn);
      int numeroDeEstados = afn.automata_estados.size();
      afn.eliminarEstadoFinal(&afn);
      Estado * estado = subAfn.obtenerEstadoInicial();
      if((int)afn.automata_estados.size()==0){
        afn.automata_estadoInicial = subAfn.automata_estadoInicial;
      }
      else{
        if(estado->numeroDeEstado != 0){
          subAfn.renumerarEstado(&subAfn,0,estado->numeroDeEstado);
          subAfn.renumerarEstado(&subAfn,estado->numeroDeEstado,0);
          subAfn.swapTransiciones(&subAfn,estado->numeroDeEstado,0);
        }
        subAfn.renumerarEstados(&subAfn, numeroDeEstados-1);
        subAfn.modificarTransiciones(&subAfn,0,numeroDeEstados-1);
        subAfn.eliminarEstadoInicial(&subAfn);
      }
      afn.agregarEstados(&afn, subAfn.automata_estados);
      afn.agregarTransiciones(&afn, subAfn.automata_tablaDeTransiciones);
      afn.automata_estadoFinal = subAfn.automata_estadoFinal;
      i += (j-i);
    }
    if(isalpha(expresionRegular[i])){
      //concatenar
      bool esEpsilon = false;
      if(expresionRegular[i]=='E'){
        esEpsilon = true;
      }
      if(i < cadlen - 1 ){
        if(expresionRegular[i+1]=='*'){
          afn.aplicarCerraduraKleen(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i+=2;
        }
        else if(expresionRegular[i+1]=='+'){
          afn.aplicarCerraduraPositiva(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i+=2;
        }
        else{
          afn.concatenar(&afn,expresionRegular[i],esEpsilon);
          afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
          i++;
        }
      }
      else{
        afn.concatenar(&afn,expresionRegular[i],esEpsilon);
        afn.agregarSimboloAlAlfabeto(&afn,expresionRegular[i]);
        i++;
      }
    }
    else if(expresionRegular[i] == '|'){
      //Union
      AFN subAfnUnion;
      subAfnUnion = convertirERaAFN(expresionRegular.substr(i+1,expresionRegular.size()-1));
      afn.unir(&afn,subAfnUnion);
      afn.copiarAlfabeto(&afn,subAfnUnion);
      i=expresionRegular.size();
    }
  }
  return afn;
}
