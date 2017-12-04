package ll1;

public class LL1 extends Funciones{
    public static void main(String[] args) {
        Funciones f = new Funciones();
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
    }
}
