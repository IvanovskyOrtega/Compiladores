package ll1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class LL1{
    
    LL1(){}
    
    Map<Character, Object> obtenerTabla(Funciones f){
        Map<Character, Object> tabla = new HashMap<Character,Object>();
        Character productor;
        Character simboloProduccion;
        String produccion;
        Set<Character> primerosSet = new HashSet<Character>();
        ArrayList<Character> primerosArray;
        Set<Character> siguientesSet = new HashSet<Character>();
        ArrayList<Character> siguientesArray;
        ArrayList<Produccion> producciones = new ArrayList<Produccion>();
        Map<Character, ArrayList<Produccion>> entradaTabla = new HashMap<Character, ArrayList<Produccion>>();
        for(Produccion p : f.reglasDeProduccion){
            productor = p.simbolo;
            produccion = p.produccion;
            simboloProduccion = produccion.charAt(0);
            primerosSet = f.obtenerPrimeros(simboloProduccion);
            primerosArray = new ArrayList<Character>(primerosSet);
            for (int i = 0; i < primerosArray.size(); i++) {
                if(tabla.containsKey(productor)){
                    entradaTabla = (Map)tabla.get(productor);
                    if(entradaTabla.containsKey(primerosArray.get(i))){
                        entradaTabla.get(primerosArray.get(i)).add(p);
                        tabla.replace(productor, entradaTabla);
                    }
                    else{
                        producciones.add(p);
                        entradaTabla.put(primerosArray.get(i),producciones);
                    }
                }
                else{
                    producciones.add(p);
                    entradaTabla.put(primerosArray.get(i),producciones);
                    tabla.put(productor,entradaTabla);
                }
            }
            if(primerosSet.contains(f.EPSILON)){
                siguientesSet = f.obtenerPrimeros(productor);
                siguientesArray = new ArrayList<Character>(siguientesSet);
                for (int i = 0; i < siguientesArray.size(); i++) {
                    if(tabla.containsKey(productor)){
                    entradaTabla = (Map)tabla.get(productor);
                    if(entradaTabla.containsKey(siguientesArray.get(i))){
                        entradaTabla.get(siguientesArray.get(i)).add(p);
                        tabla.replace(productor, entradaTabla);
                    }
                    else{
                        producciones.add(p);
                        entradaTabla.put(siguientesArray.get(i),producciones);
                    }
                }
                else{
                    producciones.add(p);
                    entradaTabla.put(siguientesArray.get(i),producciones);
                    tabla.put(productor,entradaTabla);
                }
                }
            }
        }
        return tabla;
    }
}
