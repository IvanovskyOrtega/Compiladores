#include "Subconjunto.hpp"

/**
 * Esta funcion convierte un automata AFN a un automata AFD
 * por medio del algoritmo de los subconjuntos.
 * **/
void Subconjunto::iniciarAlgoritmo(){
    int i = 0, k = 0;   // Contadores, i para subconjuntos, k para kernels
    AFN afn("afn.txt","AFN");   // Cargamos un AFN desde archivo 
    cout << "Se cargo el siguiente automata AFN:" << endl;
    afn.toString("AFN");
    cout << endl;
    cout << "/*****************************/" << endl << endl;
    cout << "Inicia el algoritmo..." << endl;
    generarTablaDePreprocesamiento(afn);    // Tabla sin transiciones epsilon
    procesarEstadoInicial(afn);    // Se procesa el estado inicial
    while(i < (int)subconjuntos.size()){
        for(int j = 0 ; j < (int)afn.automata_alfabeto.size() ; j++){
            moverConSimbolo(subconjuntos[i],afn.automata_alfabeto[j]); // Obtenemos el kernel
            sort(kernel.begin(),kernel.end());  // Ordenamos el kernel
            if(kernel.size() > 0 && !existeElKernel()){ // Se busca si el kernel ya existe
                cout << "Mover (Q" << i << ", " << afn.automata_alfabeto[j] << ")" << endl;
                agregarKernel(); // Si no existe, se agrega al vector de kernels
                aplicarCerraduraEpsilon(kernels[k],afn.automata_tablaDeTransiciones); // Se aplica la cerradura
                k++; // Incrementamos el contador de kernels
                sort(subconjunto.begin(),subconjunto.end()); // Ordenamos el vector obtenido de la cerradura
                if(!existeElSubconjunto()){ // Buscamos si existe el subconjunto
                    agregarSubconjunto(); // Si no existe, lo agregamos el vector de subconjuntos
                    agregarTransicionAFD(i,(int)subconjuntos.size()-1,afn.automata_alfabeto[j]); // Agregamos la transicion para el AFD
                }else{ // Si ya existe (a pesar de ser un nuevo kernel)
                    subconjunto.clear(); 
                    agregarTransicionAFD(i,subconjuntoActual,afn.automata_alfabeto[j]);  
                    k--; 
                    kernels.erase(kernels.begin()+k); // Eliminamos el ultimo kernel agregado
                }
            }else{ // Si ya existe el kernel
                if(kernel.size() > 0){  // Comprobamos que no sea un kernel sin elementos
                    cout << "Mover (Q" << i << ", " << afn.automata_alfabeto[j] << ")" << endl;
                    imprimirMoverConSimbolo();
                    agregarTransicionAFD(i,kernelActual,afn.automata_alfabeto[j]); 
                    kernel.clear();
                }
            }
        }
        i++; // Avanzamos al siguiente estado (subconjunto)
    }
    generarEstados();   // Se llena el vector de estados para el AFD
    generarArchivo(&afn);   // Se crea el archivo para que se pueda cargar el AFD
    limpiarVectores();  // Limpiamos los atributos de la clase
    cout << "Termino el algoritmo." << endl << endl;
    cout << "/*****************************/" << endl << endl;
    cout << "Cargue el AFD desde archivo." << endl;
}

/**
 * Esta funcion procesa el estado inicial del AFN, aplicandole la cerradura
 * epsilon y agrega el subconjunto obtenido de la cerradura al vector de 
 * subconjuntos de la clase. Ademas, obtiene el numero del estado final
 * que se utilizara en la funcion generarEstados(), para saber que estados 
 * seran estados finales.
 * **/
void Subconjunto::procesarEstadoInicial(AFN afn){
    estadoInicial = afn.obtenerEstadoInicial()->numeroDeEstado; // Obtenemos el numero del estado inicial
    estadoFinal = afn.obtenerEstadosFinales().at(0)->numeroDeEstado;    // Obtenemos el numero del estado final
    aplicarCerraduraEpsilon(estadoInicial,afn.automata_tablaDeTransiciones);    // A partir de aqui inicia el algoritmo
    sort(subconjunto.begin(),subconjunto.end()); // Ordenamos el subconjunto obtenido de la cerradura
    agregarSubconjunto(); // Lo agregamos al vector de subconjuntos
}

/**
 * Esta funcion limpia los vectores de la clase.
 * **/
void Subconjunto::limpiarVectores(){
    estadosAFD.clear();
    transicionesAFD.clear();
    tablaDePreprocesamiento.clear();
    subconjunto.clear();
    subconjuntos.clear();
    kernel.clear();
    kernels.clear();
}

/**
 * Esta funcion genera el archivo para crear el AFD equivalente al AFN
 * de entrada, generado por el algoritmo de los subconjuntos.
 * Recibe:
 *  - AFN *afn :: El automata afn (será para copiar su alfabeto).
 * **/
void Subconjunto::generarArchivo(AFN *afn){
    ofstream archivo("afd.txt");
    if(archivo.is_open()){
        int j;
        j = afn->automata_alfabeto.size();
        archivo << j << endl;
        for(int i = 0 ; i < j ; i++){
            archivo << afn->automata_alfabeto[i] << endl;
        }
        j = estadosAFD.size();
        archivo << j << endl;
        for(int i = 0 ; i < j ; i++){
            if(estadosAFD[i]->esFinal){
                archivo << "s" << endl;
            }
            else{
                archivo << "n" << endl;
            }
        }
        j = transicionesAFD.size();
        archivo << j << endl;
        for(int i = 0 ; i < j ; i++){
            archivo << transicionesAFD[i]->estadoActual << endl;
            archivo << transicionesAFD[i]->estadoDeTransicion << endl;
            archivo << transicionesAFD[i]->simboloDeTransicion << endl;
        }
    }
}

/**
 * Esta funcion genera los estados del afn a partir de los subconjuntos
 * generados durante el algoritmo.
 * **/
void Subconjunto::generarEstados(){
    for(int i = 0 ; i < (int)subconjuntos.size() ; i++){
        estadosAFD.reserve(1);
        if(estaEnElSubconjunto(estadoFinal,subconjuntos[i])){ 
            // El estado sera final si contiene al estado final del AFN
            estadosAFD.push_back(new Estado(i,true));
        }
        else{
            // De lo contrario es no final
            estadosAFD.push_back(new Estado(i,false));
        }
    }
}

/**
 * Esta funcion agrega una trancicion a la tabla de tranciciones
 * para el AFD, las transiciones se generan durante el algoritmo de
 * los subconjuntos.
 * **/
void Subconjunto::agregarTransicionAFD(int estado1, int estado2, char simbolo){
    transicionesAFD.reserve(1);
    transicionesAFD.push_back(new Transicion(estado1,estado2,simbolo));
}

/**
 * Esta funcion comprueba si el ultimo subconjunto creado, que se
 * almacena el el vector "subconjunto" de la clase, ya se encuentra
 * en el vector de subconjuntos.
 * Regresa:
 *  - true :: Si el subconjunto esta en el vector de subconjuntos
 *  - flase :: Si el subconjunto no esta en el vector de subconjuntos
 * **/
bool Subconjunto::existeElSubconjunto(){
    int j = subconjuntos.size();
    vector<int> diferencia;
    vector<int>::iterator it;
    for(int i = 0 ; i < j ; i++){
        if(subconjunto.size() == subconjuntos[i].size()){
            diferencia.reserve(subconjunto.size()*2);
            it = set_difference(subconjunto.begin(),subconjunto.end(),subconjuntos[i].begin(),subconjuntos[i].end(),diferencia.begin());
            diferencia.resize(it-diferencia.begin());
            if(diferencia.size() == 0){
                subconjuntoActual = i;
                return true;
            }
            else{
                diferencia.clear();
            }
        }
    }
    return false;
}

/**
 * Esta funcion comprueba si el ultimo kernel creado, que se
 * almacena el el vector "kernel" de la clase, ya se encuentra
 * en el vector de kernels.
 * Regresa:
 *  - true :: Si el kernel esta en el vector de kernels
 *  - flase :: Si el kernel no esta en el vector de kernels
 * **/
bool Subconjunto::existeElKernel(){
    int j = kernels.size();
    vector<int> diferencia;
    vector<int>::iterator it;
    for(int i = 0 ; i < j ; i++){
        if(kernel.size() == kernels[i].size()){
            diferencia.reserve(kernel.size()*2);
            it = set_difference(kernel.begin(),kernel.end(),kernels[i].begin(),kernels[i].end(),diferencia.begin());
            diferencia.resize(it-diferencia.begin());
            if(diferencia.size() == 0){
                kernelActual = i+1;
                return true;
            }
            else{
                diferencia.clear();
            }
        }
    }
    return false;
}

/**
 * Esta funcion agrega el ultimo subconjunto creado, que se almacena
 * en el vector "subconjunto" de la clase, al vector de sunconjuntos.
 * Ademas, limpia el comtenido, para una siguiente iteracion del
 * algoritmo en la que se genere un nuevo subconjunto.
 * **/
void Subconjunto::agregarSubconjunto(){
    subconjuntos.reserve(1);
    subconjuntos.push_back(subconjunto);
    imprimirCerraduraEpsilon();
    subconjunto.clear();
}

/**
 * Esta funcion agrega el ultimo kernel creado, que se almacena
 * en el vector "kernel" de la clase, al vector de kernels.
 * Ademas, limpia el comtenido, para una siguiente iteracion del
 * algoritmo en la que se genere un nuevo kernel.
 * **/
void Subconjunto::agregarKernel(){
    kernels.reserve(1);
    kernels.push_back(kernel);
    imprimirMoverConSimbolo();
    kernel.clear();
}

/**
 * Esta funcion, imprime el resultado de aplicar la cerradura
 * epsilon a un kernel.
 * **/
void Subconjunto::imprimirCerraduraEpsilon(){
    cout << "\tCerradura-E: {";
    for(int i = 0 ; i < (int)subconjunto.size() ; i++){
        if(i != (int)subconjunto.size()-1){
            cout << subconjunto[i] << ",";
        }
        else{
            cout << subconjunto[i];
        }
    }
    cout << "}" << endl;
}

/**
 * Esta funcion, imprime el resultado de aplicar la funcion
 * moverConSimbolo a un subconjunto, lo cual da como resultado
 * un kernel.
 * **/
void Subconjunto::imprimirMoverConSimbolo(){
    cout << "\tKernel: {";
    for(int i = 0 ; i < (int)kernel.size() ; i++){
        if(i != (int)kernel.size()-1){
            cout << kernel[i] << ",";
        }
        else{
            cout << kernel[i];
        }
    }
    cout << "}" << endl;
}

/**
 * Esta funcion genera la tabla de procesamiento para generar
 * mas rapido los kernels. Esta tabla almacena todas las transiciones
 * posibles (que no sean epsilon) del automata AFN.
 * **/
void Subconjunto::generarTablaDePreprocesamiento(AFN afn){
    for(int i = 0 ; i < (int)afn.automata_tablaDeTransiciones.size() ; i++){
        if(!afn.automata_tablaDeTransiciones[i]->esTransicionEpsilon){
            tablaDePreprocesamiento.reserve(1);
            tablaDePreprocesamiento.push_back(afn.automata_tablaDeTransiciones[i]);
        }
    }
}

/**
 * Esta funcion verifica si existen transiciones a partir de los
 * estados de un subconjunto usando un simbolo. Si la transicion existe,
 * se agrega el estado de transicion al vector kernel. 
 * **/
void Subconjunto::moverConSimbolo(vector<int> misubconjunto, char simbolo){
    for(int i = 0 ; i < (int)misubconjunto.size() ; i++){
        for(int j = 0 ; j < (int)tablaDePreprocesamiento.size() ; j++){
            if(tablaDePreprocesamiento[j]->estadoActual == misubconjunto[i]){
                if(tablaDePreprocesamiento[j]->simboloDeTransicion == simbolo){
                    if(!estaEnElSubconjunto(tablaDePreprocesamiento[j]->estadoDeTransicion,kernel)){                 
                        kernel.reserve(1);
                        kernel.push_back(tablaDePreprocesamiento[j]->estadoDeTransicion);
                       }
                }
            }
        }
    }
}

/**
 * Esta funcion verifica si un elemento esta contenido en un subconjunto,
 * evitando asi la repeticion de elementos.
 * Recibe:
 *  - int estado :: El estado a buscar en el subconjunto
 *  - vector<int> misubconjunto :: El subconjunto sobre el que se hara la busqueda.
 * Regresa:
 *  - true :: Si se encontro el estado en el subconjunto
 *  - false :: Si no se encontro el estado en el subconjunto
 * **/
bool Subconjunto::estaEnElSubconjunto(int estado, vector<int> misubconjunto){
    int j = misubconjunto.size();
    for(int i = 0 ; i < j ; i++){
        if(misubconjunto[i] == estado){
            return true;
        }
    }
    return false;
}

/**
 * Esta funcion aplica la cerradura epsilon a un estado, y si existen
 * transiciones con epsilon, agrega los estados a los que se puede mover
 * con epsilon al vector "subconjunto" de la clase.
 * Recibe:
 *  - int numeroDeEstado :: El estado al que se le aplicara la cerradura
 *  - vector<Transicion*> tablaDeTransiciones :: la tabla de transiciones del AFN
 *                     donde se consultaran las transiciones.
 * **/
void Subconjunto::aplicarCerraduraEpsilon(int numeroDeEstado, vector<Transicion*> tablaDeTransiciones){
    int i;
    int k = tablaDeTransiciones.size();
    if(!estaEnElSubconjunto(numeroDeEstado,subconjunto)){
        subconjunto.reserve(1);
        subconjunto.push_back(numeroDeEstado);
    }
      for(i = 0 ; i < k ; i++){
        if(tablaDeTransiciones[i]->estadoActual == numeroDeEstado){
          if(tablaDeTransiciones[i]->simboloDeTransicion == 'E'){
            if(!estaEnElSubconjunto(tablaDeTransiciones[i]->estadoDeTransicion,subconjunto)){
                aplicarCerraduraEpsilon(tablaDeTransiciones[i]->estadoDeTransicion,tablaDeTransiciones);
            }
          }
        }
    }
}

/**
 * Esta funcion aplica la cerradura epsilon a todos los elementos de un
 * subconjunto, si existen transiciones con epsilon para algun estado del
 * subconjunto, aplicara la cerradura epsilon de ese estado.
 * Agrega los estados a los que se puede mover con epsilon al vector 
 * "subconjunto" de la clase.
 * Recibe:
 *  - vector<int> miSubconjunto :: El subconjunto de estados al que se le aplicara la cerradura
 *  - vector<Transicion*> tablaDeTransiciones :: la tabla de transiciones del AFN
 *                     donde se consultaran las transiciones.
 * **/
void Subconjunto::aplicarCerraduraEpsilon(vector<int> miSubconjunto, vector<Transicion*> tablaDeTransiciones){
    int i;
    int k = tablaDeTransiciones.size();
    for(int j = 0 ; j < (int)miSubconjunto.size() ; j++){
        if(!estaEnElSubconjunto(miSubconjunto[j],subconjunto)){
            subconjunto.reserve(1);
            subconjunto.push_back(miSubconjunto[j]);
        }
    }
    for(int j = 0 ; j < (int)miSubconjunto.size() ; j++){
        for(i = 0 ; i < k ; i++){
            if(tablaDeTransiciones[i]->estadoActual == miSubconjunto[j]){
                if(tablaDeTransiciones[i]->simboloDeTransicion == 'E'){
                    if(!estaEnElSubconjunto(tablaDeTransiciones[i]->estadoDeTransicion,subconjunto)){
                        aplicarCerraduraEpsilon(tablaDeTransiciones[i]->estadoDeTransicion,tablaDeTransiciones);
                    }
                }
            }
        }
    }
}