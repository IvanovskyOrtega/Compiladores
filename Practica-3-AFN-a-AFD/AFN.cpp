#include "AFN.hpp"

using namespace std;

/**
 * Esta función realiza el cambio de estados (funcion de transicion), de un AFN
 * Recibe:
 *  -vector<Estado*> estados :: vector de estados del AFN
 *  -vector<Transicion*> tablaDeTransiciones :: tabla de transiciones del AFN
 *  -Estado* estadoActual :: El estado en el que se encuentra.
 *  -string cadena :: La cadena a evaluar
 *  -char simbolo :: El simbolo de transicion
 *  -int indice :: La posicion actual de la cadena
 * Regresa:
 *  -true :: Si la cadena fue validada
 *  -false :: Si la cadena no fue validada
 * **/
bool AFN::cambiarDeEstadoAFN(vector<Estado*> estados, vector<Transicion*> tablaDeTransiciones, Estado* estadoActual, string cadena, char simbolo, int indice){
  int i;
  Estado* estadoDeTransicion;
  int k = tablaDeTransiciones.size();
  bool cambio, resultado = false, tieneTransicion = false;
  /*if((int)cadena.size()==1 && simbolo == 'E'){
    for(i = 0 ; i < k ; i++){
      if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
        if(tablaDeTransiciones[i]->simboloDeTransicion == 'E'){
          cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
          cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
          return estados[tablaDeTransiciones[i]->estadoDeTransicion]->esFinal;
        }
      }
    }
    cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
    cout << " = M" << endl;
    return false;
  }*/
  if(indice < (int)cadena.size()){
    indice++;
    for(i = 0; i < k; i++){
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->esTransicionEpsilon){ // Si hay transicion epsilon
            //cout << "Entra a recursion con simbolo" << endl;
            tieneTransicion = true;
            indice--;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << ", E)";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            estadoDeTransicion = obtenerEstado(tablaDeTransiciones[i]->estadoDeTransicion);
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estadoDeTransicion, cadena, cadena[indice],indice);
            //cout << "Termina recursion con simbolo" << endl;
            resultado = resultado || cambio;
            indice++;
          }
          else if(tablaDeTransiciones[i]->simboloDeTransicion == simbolo){ // Si hay trnasicion con el simbolo
            //cout << "Entra a recursion con epsilon" << endl;
            tieneTransicion = true;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            estadoDeTransicion = obtenerEstado(tablaDeTransiciones[i]->estadoDeTransicion);
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estadoDeTransicion, cadena, cadena[indice],indice);
            //cout << "Termina recursion con epsilon" << endl;
            resultado = resultado || cambio;
          }
        }
        else if(!tieneTransicion && i == k-1){// Si no tiene transiciones
          cout << "\tδ(q" << estadoActual->numeroDeEstado << "," << simbolo << ")";
          cout << " = M" << endl;
          return false;
        }
    }
    return resultado;
  }
  else{ // Si se llego al fin de cadena
    for(i = 0; i < k; i++){ // Se busca si se puede mover con epsilon a partir del estado actual
        if(tablaDeTransiciones[i]->estadoActual == estadoActual->numeroDeEstado){
          if(tablaDeTransiciones[i]->esTransicionEpsilon){ // Si tiene transicion epsilon
            tieneTransicion = true;
            //cout << "Entra a recursion con epsilon" << endl;
            cout << "\tδ(q" << estadoActual->numeroDeEstado << ", E)";
            cout << " = q" << tablaDeTransiciones[i]->estadoDeTransicion << endl;
            estadoDeTransicion = obtenerEstado(tablaDeTransiciones[i]->estadoDeTransicion);
            cambio = cambiarDeEstadoAFN(estados, tablaDeTransiciones, estadoDeTransicion, cadena, cadena[indice],indice);
            //cout << "Termina recursion con epsilon" << endl;
            resultado = resultado || cambio;
          }
        }
    }
    if(tieneTransicion)
        return resultado;
    else
        return estadoActual->esFinal;
  }
}

/**
 * Esta funcion obtiene un estado del automata AFN de acuerdo
 * al numero de estado que le correspone.
 * Recibe:
 *  - int numeroDeEstado :: el numero del estado del AFN
 * Regresa:
 *  - Estado* automata_estados[i] :: si se encontro dicho estado en la posicion
 *                                   i del vector de estados
 *  - Estado+ muerto :: Si no se encontro el estado
 * **/
Estado* AFN::obtenerEstado(int numeroDeEstado){
  int k = automata_estados.size();
  for(int i = 0 ; i < k ; i++){
    if(automata_estados[i]->numeroDeEstado == numeroDeEstado){
      return automata_estados[i];
    }
  }
  Estado* muerto = new Estado(-1,false);
  return muerto;
}

/**
 * Esta funcion agrega una transicion en la tabla del transiciones del AFN
 * Recibe:
 *  - AFN* afn :: El automata AFN
 * - int estado1 :: El estado desde el que inicia la transicion
 * - int estado2 :: El estado al que se transita
 * - char simbolo :: El simbolo con el que se transita
 * - bool esEpsilon :: Bandera para saber si la transicion es epsilon
 * **/
void AFN::agregarTransicion(AFN* afn, int estado1, int estado2, char simbolo, bool esEpsilon){
  afn->automata_tablaDeTransiciones.reserve(1);
  afn->automata_tablaDeTransiciones.push_back(new Transicion(estado1,estado2,simbolo,esEpsilon));
}

/**
 * Esta funcion busca un simbolo para saber si pertenece al alfabeto del automata.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - char c :: El simbolo a buscar en el alfabeto
 * Regresa:
 * - true :: Si se encontro el simbolo
 * - false :: si no se encontro
 * **/
bool AFN::buscarEnAlfabeto(AFN* afn, char c){
  int k = afn->automata_alfabeto.size();
  for(int i = 0 ; i < k ; i++){
    if(c == afn->automata_alfabeto[i]){
      return true;
    }
  }
  return false;
}

/**
 * Esta funcion agrega un simbolo al alfabeto del automata AFN
 * Recibe:
 *  -AFN * afn :: El automata AFN
 *  - char c :: El caracter a a agregar en el alfabeto
 * **/
void AFN::agregarSimboloAlAlfabeto(AFN* afn, char c){
  if(!buscarEnAlfabeto(afn,c)){
    afn->automata_alfabeto.reserve(1);
    afn->automata_alfabeto.push_back(c);
  }
}

/**
 * Esta funcion copia el alfabeto de un subAfn a un afn principal.
 * Recibe:
 *  -AFN* afn :: El automata AFN principal
 *  -AFN subafn :: El automata AFN subafn
 * **/
void AFN::copiarAlfabeto(AFN* afn, AFN subafn){
  int k = subafn.automata_alfabeto.size();
  char c;
  for(int i = 0 ; i < k ; i++){
    c = subafn.automata_alfabeto[i];
    if(!buscarEnAlfabeto(afn,c)){
      afn->automata_alfabeto.reserve(1);
      afn->automata_alfabeto.push_back(c);
    }
  }
}

/**
 * Esta función cambia la propiedad "tipo" del estado final
 * del AFN a un estado no final.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 * **/
void AFN::eliminarEstadoFinal(AFN *afn){
  int j = afn->automata_estados.size();
  for(int i = 0 ; i < j ; i++){
    if(afn->automata_estados[i]->esFinal){
      afn->automata_estados[i]->esFinal = false;
    }
  }
}

/**
 * Esta funcion elimina el estado inicial de un automata
 * AFN.
 * Recibe:
 *  - AFN* afn :: el automata AFN
 * **/
void AFN::eliminarEstadoInicial(AFN *afn){
  int j = afn->automata_estados.size();
  Estado *estado = afn->obtenerEstadoInicial();
  int numeroDeEstado = estado->numeroDeEstado;
  for(int i = 0 ; i < j ; i++){
    if(afn->automata_estados[i]->numeroDeEstado == numeroDeEstado){
      afn->automata_estados.erase(afn->automata_estados.begin()+i);
      break;
    }
  }
}

/**
 * Esta funcion realiza la operacion de concatenacion de 
 * un simbolo de acuerdo a las construcciones de Thompson.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - char c :: El simbolo a concatenar
 *  - bool esEpsilon :: bandera para saber si es una transicion epsilon
 * **/
void AFN::concatenar(AFN* afn, char simbolo, bool esEpsilon){
  Estado* estado1;
  Estado* estado2;
  int estadosDelAutomata = afn->automata_estados.size();
  if(estadosDelAutomata==0){
    estado1 = new Estado(0,false);
    estado2 = new Estado(1,true);
    afn->automata_estados.reserve(2);
    afn->automata_estados.push_back(estado1);
    afn->automata_estados.push_back(estado2);
    afn->automata_estadoInicial = estado1;
    agregarTransicion(afn, estado1->numeroDeEstado, estado2->numeroDeEstado, simbolo, esEpsilon);
  }
  else{
    estado2 = new Estado(estadosDelAutomata, true);
    estado1 = afn->obtenerEstadoFinal();
    agregarTransicion(afn, estado1->numeroDeEstado, estado2->numeroDeEstado, simbolo, esEpsilon);
    eliminarEstadoFinal(afn);
    afn->automata_estados.reserve(1);
    afn->automata_estados.push_back(estado2);
  }
  afn->automata_estadoFinal = estado2;
}

/**
 * Esta funcion renumera un estado del automata AFN.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - int antiguo :: El numero del estado a renumerar
 *  - int nuevo :: El nuevo numero del estado
 * **/
void AFN::renumerarEstado(AFN *afn, int antiguo, int nuevo){
  int k = afn->automata_estados.size();
  for(int i = 0 ; i < k ; i++){
    if(afn->automata_estados[i]->numeroDeEstado == antiguo){
      afn->automata_estados[i]->numeroDeEstado = nuevo;
      afn->automata_estadoInicial = afn->automata_estados[i];
      break;
    }
  }
}

/**
 * Esta funcion modifica las transiciones que corresponden a un estado,
 * remplazandolas por uno nuevo.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - int antiguo :: El numero del estado al que se le renumerarán las transiciones
 *  - int nuevo :: El numero de estado por el que serán remplazadas las transiciones
 *                 donde se encuentre el estado antiguo.
 * **/
void AFN::modificarTransiciones(AFN* afn, int antiguo, int nuevo){
  int k = afn->automata_tablaDeTransiciones.size();
  for(int i = 0 ; i < k ; i++){
    if(afn->automata_tablaDeTransiciones[i]->estadoActual == antiguo){
      afn->automata_tablaDeTransiciones[i]->estadoActual = nuevo;
    }
    if(afn->automata_tablaDeTransiciones[i]->estadoDeTransicion == antiguo){
      afn->automata_tablaDeTransiciones[i]->estadoDeTransicion = nuevo;
    }
  }
}

/**
 * Esta función intercambia las transiciones de un estado antiguo
 * a un estado nuevo y viceversa.
 * Recibe:
 *  - AFN* afn :: el automata AFN
 *  - int estado1 :: El estado 1 de intercambio
 *  - int estado2 :: El estado 2 de intercambio
 * **/
void AFN::swapTransiciones(AFN* afn, int estado1, int estado2){
  int k = afn->automata_tablaDeTransiciones.size();
  for(int i = 0 ; i < k ; i++){
    if(afn->automata_tablaDeTransiciones[i]->estadoActual == estado1){
      afn->automata_tablaDeTransiciones[i]->estadoActual = estado2;
    }
    else if(afn->automata_tablaDeTransiciones[i]->estadoActual == estado2){
      afn->automata_tablaDeTransiciones[i]->estadoActual = estado1;
    }
    if(afn->automata_tablaDeTransiciones[i]->estadoDeTransicion == estado1){
      afn->automata_tablaDeTransiciones[i]->estadoDeTransicion = estado2;
    } 
    else if(afn->automata_tablaDeTransiciones[i]->estadoDeTransicion == estado2){
      afn->automata_tablaDeTransiciones[i]->estadoDeTransicion = estado1;
    }
  }
}

/**
 * Esta funcion agrega los elementos de una tabla de transiciones a el automata
 * AFN.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - vector<Transicion*> tablaDeTransiciones :: El vector de transiciones
 * **/
void AFN::agregarTransiciones(AFN* afn, vector<Transicion*> tablaDeTransiciones){
  int k = tablaDeTransiciones.size();
  afn->automata_tablaDeTransiciones.reserve(k);
  for(int i = 0 ; i < k ; i++){
    afn->automata_tablaDeTransiciones.push_back(tablaDeTransiciones[i]);
  }
}

/**
 * Esta funcion agrega los elementos de un vector de estados a el automata
 * AFN.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - vector<Estado*> estados :: El vector de estados
 * **/
void AFN::agregarEstados(AFN* afn, vector<Estado*> estados){
  int k = estados.size();
  afn->automata_estados.reserve(k);
  for(int i = 0 ; i < k ; i++){
    afn->automata_estados.push_back(estados[i]);
  }
}

/**
 * Esta funcion renumera los estados de un automata sumandoles el numero 
 * de estados de el automata principal (Esta funcion se aplica a los subAfn's
 * que se van generando en la funcion recursiva de conversión de ER a AFN).
 * Ademas renumera los estados en la tabla de transiciones.
 * Recibe:
 *  - AFN *afn :: El automata AFN
 *  - int numero :: El numero de estados del afn principal
 * **/
void AFN::renumerarEstados(AFN* subafn, int numero){
  int k = subafn->automata_tablaDeTransiciones.size();
  for(int i = 0 ; i < k ; i++){ // Renumeracion en la tabla de transiciones
    subafn->automata_tablaDeTransiciones[i]->estadoDeTransicion += numero;
    subafn->automata_tablaDeTransiciones[i]->estadoActual += numero; 
  }
  k = subafn->automata_estados.size();
  for(int i = 0 ; i < k ; i++){ // Renumeracion en el vector de estados
    subafn->automata_estados[i]->numeroDeEstado += numero;
  }
}

/**
 * Esta funcion agrega una transicion epsilon a la tabla de transiciones
 * de un automata AFN.
 * Recibe:
 *  - AFN* afn :: El automata AFN
 *  - Estado* estado1 :: El estado donde inicia la transicion epsilon
 *  - Estado* estado2 :: El estado a donde se transita con epsilon
 * **/
void AFN::agregarTransicionEpsilon(AFN* afn, Estado* estado1,Estado* estado2){
  Transicion* t = new Transicion(estado1->numeroDeEstado,estado2->numeroDeEstado,'E',true);
  afn->automata_tablaDeTransiciones.reserve(1);
  afn->automata_tablaDeTransiciones.push_back(t);
}

/**
 * Esta funcion realiza la operacion de union de acuerdo a las
 * contrucciones de Thompson.
 * Recibe:
 *  - AFN* afn :: El afn principal.
 *  - AFN subafn :: el subafn
 * **/
void AFN::unir(AFN* afn, AFN subafn){
  Estado* estado1; // Estados adicionales para realizar la union
  Estado* estado2;
  Estado* aux1; // Estados auxiliares
  Estado* aux2;
  int numeroDeEstados = afn->automata_estados.size();
  renumerarEstados(&subafn, numeroDeEstados); // Renumeramos los estados del subafn
  agregarEstados(afn, subafn.automata_estados); // Agregamos los estados del subafn al afn
  agregarTransiciones(afn, subafn.automata_tablaDeTransiciones);  // Agregamos las transiciones del subafn al afn
  numeroDeEstados += (int)subafn.automata_estados.size(); // Se actualiza el valor del numero de estados
  estado1 = new Estado(numeroDeEstados,false);  // Instanciamos los estados necesarios para la union
  estado2 = new Estado(numeroDeEstados+1,true); // Uno de ellos es estado final
  aux1 = afn->obtenerEstadoInicial(); // Obtenemos la referencia del estado inicial del afn
  aux2 = subafn.obtenerEstadoInicial(); // Obtenemos la referencia del estado inicial de afn
  agregarTransicionEpsilon(afn,estado1,aux1); // Se agrega la transicion de estado1 a aux1
  agregarTransicionEpsilon(afn,estado1,aux2); // Se agrega la transicion de estado1 a aux2
  for(int i = 0 ; i < numeroDeEstados ; i++){
    if(afn->automata_estados[i]->esFinal){ 
      /*
      Se agregan transiciones epsilon de los estados finales del afn hacia el estado2.
      En este punto el afn tiene dos estados finales, pues al momento que se agregaron los estados
      del subafn, uno de ellos tenia la propiedad de ser final, mas el que al inicio, era eñ
      estado final del afn.
      */
      agregarTransicionEpsilon(afn,afn->automata_estados[i],estado2); 
    }
  }
  eliminarEstadoFinal(afn); // Los estados finales ahora son no finales
  afn->automata_estados.reserve(2);
  afn->automata_estados.push_back(estado1); // Se agrega el estado inicial
  afn->automata_estados.push_back(estado2); // Se agrega el estado final
  afn->automata_estadoInicial = estado1;  
  afn->automata_estadoFinal = estado2;
}

/**
 * Esta funcion aplica la cerradura de Kleen a un AFN.
 * Recibe:
 * - AFN* afn :: El automata AFN generado durante el proceso de 
 *               conversion de ER a AFN.
 * **/
void AFN::aplicarCerraduraKleenAFN(AFN *afn){
  Estado* estado1; // Estados adicionales necesarios para la cerradura
  Estado* estado2;
  Estado* aux1; // Estados auxiliares
  Estado* aux2;
  int numeroDeEstados = afn->automata_estados.size();
  aux1 = afn->obtenerEstadoInicial(); // Se obtienen las referencias de loos estados final e inicial
  aux2 = afn->obtenerEstadoFinal();
  estado1 = new Estado(numeroDeEstados,false);  // Se instancian los nuevos estados
  estado2 = new Estado(numeroDeEstados+1,true);
  agregarTransicionEpsilon(afn,aux2,aux1);  // Se agregan las transiciones de la cerradura de Kleen
  agregarTransicionEpsilon(afn,estado1,estado2);
  agregarTransicionEpsilon(afn,estado1,aux1);
  agregarTransicionEpsilon(afn,aux2,estado2);
  eliminarEstadoFinal(afn); // El estado final ahora es no final
  afn->automata_estados.reserve(2); // Se agregan los estados adicionales
  afn->automata_estados.push_back(estado1);
  afn->automata_estados.push_back(estado2);
  afn->automata_estadoInicial = estado1; // Se asignan los nuevos estados final e inicial
  afn->automata_estadoFinal = estado2;
}

/**
 * Esta funcion aplica la cerradura de Kleen de un simbolo c,
 * y se la concatena a un automata AFN.
 * Recibe:
 *  - AFN* afn :: El automata afn al que se le concatenará el automata
 *                que corresponde a la cerradura del simbolo.
 *  - char c :: El simbolo al que le corresponde la cerradura.
 *  - bool esEpsilon :: Bandera para saber si es una transicion epsilon.
 * **/
void AFN::aplicarCerraduraKleen(AFN* afn, char c, bool esEpsilon){
  Estado* estado1; // Estados adicionales necesarios para la cerradura
  Estado* estado2;
  Estado* estado3;
  Estado* estado4;
  int numeroDeEstados = afn->automata_estados.size();
  if(numeroDeEstados == 0){ // Si el AFN no tiene estados
    estado1 = new Estado(0,false); // Instanciamos los estados
    estado2 = new Estado(1,false);
    estado3 = new Estado(2,false);
    estado4 = new Estado(3,true);
    afn->automata_estadoInicial = estado1; // Asignamos el estado inicial
    agregarTransicionEpsilon(afn,estado1,estado2);  // Se agregan las transiciones necesarias
    agregarTransicion(afn, estado2->numeroDeEstado, estado3->numeroDeEstado, c, esEpsilon);
    agregarTransicionEpsilon(afn,estado3,estado4);
    agregarTransicionEpsilon(afn,estado3,estado2);
    agregarTransicionEpsilon(afn,estado1,estado4);
    afn->automata_estadoFinal = estado4; // Asignamos el estado final
    afn->automata_estados.reserve(4); //Agregamos los estados
    afn->automata_estados.push_back(estado1);
    afn->automata_estados.push_back(estado2);
    afn->automata_estados.push_back(estado3);
    afn->automata_estados.push_back(estado4);
  }
  else{ // Si el automata no esta vacio
    estado1 = new Estado(numeroDeEstados,false);  // Instanciamos los estados
    estado2 = new Estado(numeroDeEstados+1,false);
    estado3 = new Estado(numeroDeEstados+2,true);
    estado4 = afn->obtenerEstadoFinal();  // Obtenemos el estado final del AFN
    agregarTransicionEpsilon(afn,estado4,estado1);  // Agregamos las transiciones necesarias
    agregarTransicion(afn, estado1->numeroDeEstado, estado2->numeroDeEstado, c, esEpsilon);
    agregarTransicionEpsilon(afn,estado2,estado3);
    agregarTransicionEpsilon(afn,estado2,estado1);
    agregarTransicionEpsilon(afn,estado4,estado3);
    eliminarEstadoFinal(afn); // El estado final del AFN ahora es no final
    afn->automata_estadoFinal = estado3;  // Asignamos el nuevo estado final
    afn->automata_estados.reserve(3); // Agregamos los estados nuevos
    afn->automata_estados.push_back(estado1);
    afn->automata_estados.push_back(estado2);
    afn->automata_estados.push_back(estado3);
  }
}

/**
 * Esta funcion aplica la cerradura de positiva a un AFN.
 * Recibe:
 * - AFN* afn :: El automata AFN generado durante el proceso de 
 *               conversion de ER a AFN.
 * **/
void AFN::aplicarCerraduraPositivaAFN(AFN *afn){
  Estado* estado1;  // Estados adicionales necesarios para la cerradura
  Estado* estado2;
  Estado* aux1; // Estados auxiliares
  Estado* aux2;
  int numeroDeEstados = afn->automata_estados.size();
  aux1 = afn->obtenerEstadoInicial(); // Obtenemos las referencias de los estados final e inicial
  aux2 = afn->obtenerEstadoFinal(); 
  estado1 = new Estado(numeroDeEstados,false); // Instanciamos los nuevos estados
  estado2 = new Estado(numeroDeEstados+1,true);
  agregarTransicionEpsilon(afn,aux2,aux1); // Aregamos las transiciones necesarias
  agregarTransicionEpsilon(afn,estado1,aux1);
  agregarTransicionEpsilon(afn,aux2,estado2);
  eliminarEstadoFinal(afn); // El estado final del AFN ahora es no final
  afn->automata_estados.reserve(2); // Agregamos los nuevos estados
  afn->automata_estados.push_back(estado1);
  afn->automata_estados.push_back(estado2);
  afn->automata_estadoInicial = estado1;  // Se asignan los nuevos estados final e inicial
  afn->automata_estadoFinal = estado2; 
}

/**
 * Esta funcion aplica la cerradura de positiva de un simbolo c,
 * y se la concatena a un automata AFN.
 * Recibe:
 *  - AFN* afn :: El automata afn al que se le concatenará el automata
 *                que corresponde a la cerradura del simbolo.
 *  - char c :: El simbolo al que le corresponde la cerradura.
 *  - bool esEpsilon :: Bandera para saber si es una transicion epsilon.
 * **/
void AFN::aplicarCerraduraPositiva(AFN* afn, char c, bool esEpsilon){
  Estado* estado1; // Estados adicionales necesarios para la cerradura
  Estado* estado2;
  Estado* estado3;
  Estado* estado4;
  int numeroDeEstados = afn->automata_estados.size();
  if(numeroDeEstados == 0){ // Si el automata no tiene estados
    estado1 = new Estado(0,false); // Instanciamos los nuevos estados
    estado2 = new Estado(1,false);
    estado3 = new Estado(2,false);
    estado4 = new Estado(3,true);
    agregarTransicionEpsilon(afn,estado1,estado2); // Agregamos las transiciones necesarias
    agregarTransicion(afn, estado2->numeroDeEstado, estado3->numeroDeEstado, c, esEpsilon);
    agregarTransicionEpsilon(afn,estado3,estado4);
    agregarTransicionEpsilon(afn,estado3,estado2);
    afn->automata_estadoInicial = estado1;  // Asignamos los nuevos estados final e inicial
    afn->automata_estadoFinal = estado4;
    afn->automata_estados.reserve(4); // Agregamos los nuevos estados
    afn->automata_estados.push_back(estado1);
    afn->automata_estados.push_back(estado2);
    afn->automata_estados.push_back(estado3);
    afn->automata_estados.push_back(estado4);
  }
  else{ // Si el automata no es vacio
    estado1 = new Estado(numeroDeEstados,false); // Instanciamos los nuevos estados
    estado2 = new Estado(numeroDeEstados+1,false);
    estado3 = new Estado(numeroDeEstados+2,true);
    estado4 = afn->obtenerEstadoFinal();  // Obtenemos la referencia del estado final del AFN
    agregarTransicionEpsilon(afn,estado4,estado1);  // Agregamos las transiciones necesarias
    agregarTransicion(afn, estado1->numeroDeEstado, estado2->numeroDeEstado, c, esEpsilon);
    agregarTransicionEpsilon(afn,estado2,estado3);
    agregarTransicionEpsilon(afn,estado2,estado1);
    eliminarEstadoFinal(afn); // El estado final del AFN ahora es no final
    afn->automata_estadoFinal = estado3;  // Asignamos el nuevo estado final
    afn->automata_estados.reserve(3); // Agregamos los nuevos estados
    afn->automata_estados.push_back(estado1);
    afn->automata_estados.push_back(estado2);
    afn->automata_estados.push_back(estado3);
  }
}

/**
 * Esta funcion genera un archivo que contiene la informacion del afn 
 * generado por una expresion regular mediante construcciones de
 * Thompson.
 * **/
void AFN::generarArchivoAFN(AFN afn){
  int i,j,estadoInicial;
  ofstream archivo("afn.txt");
  if(archivo.is_open()){
    j = afn.automata_alfabeto.size();
    archivo << j << endl;
    for(i = 0 ; i < j ; i++){
        archivo << afn.automata_alfabeto[i] << endl;
    }
    j = afn.automata_estados.size();
    archivo << j << endl;
    estadoInicial = afn.obtenerEstadoInicial()->numeroDeEstado;
    archivo << estadoInicial << endl;
    for(i = 0 ; i < j ; i++){
      if(afn.automata_estados[i]->numeroDeEstado != estadoInicial){
        archivo << afn.automata_estados[i]->numeroDeEstado << endl;
        if(afn.automata_estados[i]->esFinal){
          archivo << "s" << endl;
        }
        else{
          archivo << "n" << endl;
        }
      }
    }
    j = afn.automata_tablaDeTransiciones.size();
    archivo << j << endl;
    for(i = 0 ; i < j ; i++){
      if(afn.automata_tablaDeTransiciones[i]->esTransicionEpsilon){
        archivo << "s" << endl;
        archivo << automata_tablaDeTransiciones[i]->estadoActual << endl;
        archivo << automata_tablaDeTransiciones[i]->estadoDeTransicion << endl;
      }
      else {
        archivo << "n" << endl;
        archivo << automata_tablaDeTransiciones[i]->estadoActual << endl;
        archivo << automata_tablaDeTransiciones[i]->estadoDeTransicion << endl;
        archivo << automata_tablaDeTransiciones[i]->simboloDeTransicion << endl;
      }
    }
  }
}

vector<char> AFN::obtenerAlfabeto(){
  return automata_alfabeto;
}