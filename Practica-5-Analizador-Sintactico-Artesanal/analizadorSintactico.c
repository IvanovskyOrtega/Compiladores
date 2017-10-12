#include <stdio.h>
#include <stdlib.h>

#define TAM 9 // Tamanio de la cadena

char cadena[TAM] = "aaaacbbab"; // Cadena a evaluar
int indice = 0; // Posicion del indice de la cadena

void S();
void consume(char caracter);
void error();
void aceptada();

int main(){
    S();
    return 0;
}

/**
 * Esta funcion realiza las reglas de produccion de la gramatica:
 * G(S,P,N,T)
 *  N = {S}
 *  T = {a,b,c}
 *  P = {
 *          S -> aSb
 *          S -> c
 *      }
 * */
void S(){
    if(cadena[indice]=='a'){
        consume('a');
        S();
        consume('b');
    }
    else if(cadena[indice]=='c'){
        consume('c');
    }
    else{
        error();
    }
}

/**
 * Esta funcion avanza una posicion en la cadena, si y solo si
 * el caracter en la posicion actual es el caracter que se recibe.
 * Recibe:
 *  char caracter : El caracter que se espera consumir.
*/
void consume(char caracter){
    if(cadena[indice]==caracter)
        indice++;
    else
        error();
    if(indice == TAM)
        aceptada();
}

/**
 * Esta funcion imprime un mensaje de error y termina el proceso con
 * exit(0) al momento que se detecta un error y evitar que siga analizando
*/
void error(){
    printf("Cadena invalida\n");
    exit(0);
}

/**
 * Esta funcion imprime un mensaje de aceptacion.
*/
void aceptada(){
    printf("Cadena valida\n");
}