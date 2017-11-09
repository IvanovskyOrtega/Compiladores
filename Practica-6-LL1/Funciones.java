package ll1;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Stream;

public class Funciones {
    public PS aux = new PS();
    public char axioma;
    public Set<Character> terminales = new HashSet<Character>();
    public Set<Character> noTerminales = new HashSet<Character>();
    public Set<Produccion> reglasDeProduccion = new HashSet<Produccion>();
    public Set<PS> primeros = new HashSet<PS>();
    public Set<PS> siguientes = new HashSet<PS>();
    public Set<Character> listaDeEspera = new HashSet<Character>();
    Scanner input = new Scanner(System.in);

    /**
     * Esta función lee desde consola las reglas de producción de la Gramática Libre de Contexto.
     *
     */
    public void leerReglasDeProduccion(){
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
            terminales.add(linea.charAt(i));
        }
        for(int i = 3; i < lineasArchivo.size(); i++){
            linea  = lineasArchivo.get(i);
            p = new Produccion(linea.charAt(0),linea.substring(5,linea.length()));
            reglasDeProduccion.add(p);
        }
    }


    public List<String> leerArchivo(String nombreDelArchivo) {
        FileInputStream fstream = null;
        List<String> lineasArchivo = new ArrayList<String>();
        try {
            fstream = new FileInputStream("test/"+nombreDelArchivo);
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
            String linea;
            while ((linea = br.readLine()) != null){
                lineasArchivo.add(linea);
                System.out.println (linea);
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return lineasArchivo;
    }

    public Set<Character> obtenerPrimeros(Character c){
        char posiblePrimero;
        Set<Character> res = new HashSet<Character>();
        PS primerosDeC = new PS();
        primerosDeC.simbolo = c;
        int index = 1;
        for (Produccion p:reglasDeProduccion) {
            if(p.simbolo == c){
                posiblePrimero = p.produccion.charAt(0);
                if(terminales.contains(posiblePrimero)){
                    primerosDeC.primeros.add(posiblePrimero);
                    res.add(posiblePrimero);
                }
                else  if(noTerminales.contains(posiblePrimero)){
                    if(yaSeCalculoPrimeros(posiblePrimero)){
                        if(aux.primeros.contains('Ø') && index < p.produccion.length()){
                            if(terminales.contains(p.produccion.charAt(index))){
                                primerosDeC.primeros.add(p.produccion.charAt(index));
                                res.add(p.produccion.charAt(index));
                            }
                            else{
                                Set<Character> aux = new HashSet<Character>();
                                aux = obtenerPrimeros(p.produccion.charAt(index));
                                res.addAll(aux);
                                primerosDeC.primeros.addAll(aux);
                                index++;
                            }
                        }
                    }
                    else if(obtenerPrimeros(posiblePrimero).contains('Ø')){
                        obtenerPrimeros(p.produccion.charAt(index));
                        index++;
                    }
                }
                else if(posiblePrimero == 'Ø'){
                    primerosDeC.primeros.add(posiblePrimero);
                    res.add(posiblePrimero);
                }
            }
        }
        if(noTerminales.contains(c))
            primeros.add(primerosDeC);
        return res;
    }

    public boolean yaSeCalculoPrimeros(Character c){
        int i = 0;
        for (PS p: primeros) {
            if(p.simbolo == c){
                aux = p;
                return true;
            }
            i++;
        }
        return false;
    }

    public boolean yaSeCalculoSiguientes(Character c){
        int i = 0;
        for (PS s: siguientes) {
            if(s.simbolo == c){
                aux = s;
                return true;
            }
            i++;
        }
        return false;
    }

    public Set<Character> obtenerSiguientes(Character c){
        PS siguientesDeC = new PS();
        char posibleSiguiente;
        Set<Character> res = new HashSet<Character>();
        siguientesDeC.simbolo = c;
        if(c == axioma){
            res.add('$');
            siguientesDeC.siguientes.add('$');
        }
        if(yaSeCalculoSiguientes(c)) {
            res.addAll(aux.siguientes);
            siguientesDeC.siguientes.addAll(aux.siguientes);
        }
        else{
            for (Produccion p: reglasDeProduccion) {
                System.out.println(listaDeEspera.toString());
                System.out.println(p.produccion);
                if(!listaDeEspera.contains(c)){
                    listaDeEspera.add(c);
                    for(int i = 0; i < p.produccion.length(); i++){
                        if(c == p.produccion.charAt(i)){
                            if(i == p.produccion.length()-1){
                                if(yaSeCalculoSiguientes(p.simbolo)){
                                    res.addAll(aux.siguientes);
                                    siguientesDeC.siguientes.addAll(aux.siguientes);
                                }
                                else{
                                    res.addAll(obtenerSiguientes(p.simbolo));
                                    siguientesDeC.siguientes.addAll(obtenerSiguientes(p.simbolo));
                                }
                            }
                            else{
                                boolean flag = false;
                                for(int j = i+1; j < p.produccion.length(); j++){
                                    if(!obtenerPrimeros(p.produccion.charAt(j)).contains('Ø')){
                                        res.addAll(aux.primeros);
                                        siguientesDeC.siguientes.addAll(aux.primeros);
                                        flag = true;
                                        break;
                                    }
                                }
                                if(flag){
                                    res.add('Ø');
                                    siguientesDeC.siguientes.add('Ø');
                                }

                            }
                        }
                    }
                }
                try{
                    listaDeEspera.remove(c);
                }
                catch(Exception e){
                    System.out.println(e.toString());
                }
            }
        }

        siguientes.add(siguientesDeC);
        return res;
    }
}
