/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ll1;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author Ivanovsky-ESCOM
 */
public class Main {
    public static void main(String[] args) {
        Map<Character, Object> tabla = new HashMap<Character,Object>();
        Funciones f = new Funciones();
        LL1 ll1 = new LL1();
        f.leerReglasDeProduccion();
        System.out.println("Axioma: "+f.axioma);
        for (Character c: f.noTerminales) {
            f.obtenerPrimeros(c);
        }
        for(Character c : f.noTerminales){
            if(f.conjuntoPrimeros.containsKey(c)){
                System.out.println("Primeros de "+c+":");
                System.out.println(f.conjuntoPrimeros.get(c).toString());
            };
        }
        for (Character c: f.noTerminales) {
            f.obtenerSiguientes(c);
        }
        for(Character c: f.noTerminales){
            if(f.conjuntoSiguientes.containsKey(c)){
                System.out.println("Siguientes de "+c+":");
                System.out.println(f.conjuntoSiguientes.get(c).toString());
            };
        }
        tabla = ll1.obtenerTabla(f);
        System.out.println(""+tabla.toString());
    }
}
