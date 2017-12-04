package ll1;

import java.io.*;
import java.util.*;

public class Funciones {
    Character EPSILON = 'ε';
    Character axioma;
    Set<Character> terminales = new HashSet<Character>();
    Set<Character> noTerminales = new HashSet<Character>();
    ArrayList<Produccion> reglasDeProduccion = new ArrayList<Produccion>();
    Map<Character,Set<Character>> conjuntoPrimeros = new HashMap<Character,Set<Character>>();
    Map<Character,Set<Character>> conjuntoSiguientes = new HashMap<Character,Set<Character>>();
    Scanner input = new Scanner(System.in);
    
    void leerReglasDeProduccion(){
        List<String> lineasArchivo;
        Produccion p;
        System.out.println("Ingresa el nombre del archivo .txt que contiene la gramática (sin extensión):\t");
        lineasArchivo = leerArchivo(input.nextLine()+".txt");
        String linea;
        axioma = lineasArchivo.get(0).charAt(0);
        linea = lineasArchivo.get(1);
        for (int i = 0; i < linea.length() ; i+=2) {
            noTerminales.add(linea.charAt(i));
        }
        linea = lineasArchivo.get(2);
        for (int i = 0; i < linea.length() ; i+=2) {
            if(linea.charAt(i) != EPSILON){
                terminales.add(linea.charAt(i));
            }
        }
        for(int i = 3; i < lineasArchivo.size(); i++){
            linea  = lineasArchivo.get(i);
            p = new Produccion(linea.charAt(0),linea.substring(5,linea.length()));
            reglasDeProduccion.add(p);
        }
    }


    List<String> leerArchivo(String nombreDelArchivo) {
        List<String> lineasArchivo = new ArrayList<>();
        try {
            FileInputStream fstream = new FileInputStream("test/"+nombreDelArchivo);
            try (BufferedReader br = new BufferedReader(new InputStreamReader(fstream,"UTF-8"))){
                String linea;
                while ((linea = br.readLine()) != null){
                    if (linea.startsWith("\uFEFF")){ 
                        linea = linea.substring(1); 
                    }
                    lineasArchivo.add(linea);
                    System.out.println (linea);
                }
            }
        } catch (IOException e) {
        }
        return lineasArchivo;
    }

    Set<Character> obtenerPrimeros(Character c){
        if(conjuntoPrimeros.containsKey(c)){
            return conjuntoPrimeros.get(c);
        }
        Set<Character> primeros = new HashSet<Character>();
        
        // Si es un terminal, entonces se agrega y termina la funcion.
        if(terminales.contains(c)){
            primeros.add(c);
            conjuntoPrimeros.put(c, primeros);
            return primeros;
        }
        
        String produccion;
        Character simboloProduccion;
        Character productor;
        for(Produccion p : reglasDeProduccion){
            produccion = p.produccion;
            productor = p.simbolo;
            if(productor.equals(c)){
                for (int i = 0; i < produccion.length(); i++) {
                    simboloProduccion = produccion.charAt(i);
                
                    // Epsilon se agrega a primeros
                    if(simboloProduccion.equals(EPSILON)){
                        primeros.add(EPSILON);
                        break;
                    }
                
                    // De lo contrario, si es un no terminal, se calculan su
                    // conjunto de primeros.
                    Set<Character> primerosDeS = obtenerPrimeros(simboloProduccion);
                
                    // Si no contiene a epsilon, se agrega el subconjunto a primeros
                    if(!primerosDeS.contains(EPSILON)){
                        primeros.addAll(primerosDeS);
                        break;
                    }
                
                    // De lo contrario, si contiene epsilon, se agregan todos los
                    // elementos a excepcion de epsilon.
                    primeros.addAll(primerosDeS);
                    primeros.remove(EPSILON);
                }
                conjuntoPrimeros.put(c, primeros);
            }
        }
        return primeros;
    }
    
    Set<Character> obtenerSiguientes(Character c){
        if(conjuntoSiguientes.containsKey(c)){
            return conjuntoSiguientes.get(c);
        }
        Set<Character> siguientes = new HashSet<>();
        
        // Caso especial
        if(c.equals(axioma)){
            siguientes.add('$');
        }
        
        // Se analizan todas las producciones que contengan a c
        String produccion;
        Character productor;
        Character simboloProduccion;
        int posicionSimbolo;
        int sigPosicion;
        for(Produccion p : reglasDeProduccion){
            produccion = p.produccion;
            
            // Obtenemos la primera ocurrencia en la cadena.
            posicionSimbolo = produccion.indexOf(c);
            if(posicionSimbolo != -1){
                // Asignamos la siguiente posicion
                sigPosicion = posicionSimbolo + 1;
            
                // Se buscan los simbolo siguientes a c
                while(true){
                
                    // Si el simbolo esta al final de la cadena, se calculan los
                    // siguientes del simbolo que genera la produccion.
                    if(sigPosicion == produccion.length()){
                        productor = p.simbolo;
                        // evitamos el ciclamiento con producciones del tipo:
                        // S -> abS
                        if(!productor.equals(c)){
                            // Se agregan los siguientes del productor
                            siguientes.addAll(obtenerSiguientes(productor));
                            conjuntoSiguientes.put(c, siguientes);
                        }
                        break;
                    }
                
                    // Si el simbolo no es el útimo elemento en la cadena, se
                    // calculan los primeros del simbolo que le sigue.
                    simboloProduccion = produccion.charAt(sigPosicion);
                    Set<Character> primerosDeS = obtenerPrimeros(simboloProduccion);
                
                    // Si los primeros del siguiente no contienen a epsilon, 
                    // se agregan los elementos al conjunto
                    if(!primerosDeS.contains(EPSILON)){
                        siguientes.addAll(primerosDeS);
                        conjuntoSiguientes.put(c, siguientes);
                        break;
                    }
                
                    // De lo contrario, se agregan sin incluir a epsilon, y se 
                    // siguen buscando siguientes en las proximas posiciones.
                    siguientes.addAll(primerosDeS);
                    siguientes.remove(EPSILON);
                    conjuntoSiguientes.put(c, siguientes);
                    sigPosicion++;
                }
            }
        }
        return siguientes;
    }
}
