# Compiladores
Práctica de AFD:
  Lectura del autómata redirigiendo la entrada estándar:
    ./a.out < archivo.txt
  El archivo debe tener el siguiente formato:
    Número de símbolos del alfabeto
    N símbolos del alfabeto
    Número de estados
    Para todos los estados (excepto q0) indicar si es final (s) o no (n)
    Número de transiciones
    Número del primer estado
    Numero al estado de cambio
    Simbolo con el que se cambia
  Un ejemplo de archivo sería:
    3   // Se indica que tendrá tres símbolos el alfabeto
    a   // Se ingresan los 3 símbolos a,b,c  b
    c   
    2   // Se indica que tendrá dos estados q0 y q1
    s   // Se indica que q1 es final
    3   // Se indica que tendrá 3 transiciones
    0   // Estado inicial
    0   // Estado de transición
    a   // Simbolo con el que se cambia de estado
    0
    0
    b
    0
    1
    c
    
