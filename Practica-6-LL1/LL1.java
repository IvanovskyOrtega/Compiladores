package ll1;

public class LL1 {
    public static void main(String[] args) {
        Funciones f = new Funciones();
        f.leerReglasDeProduccion();
        for (Character c: f.noTerminales) {
            f.obtenerPrimeros(c);
        }
        for(PS p : f.primeros){
            System.out.println("Primeros de "+p.simbolo+":");
            System.out.println(p.primeros.toString());
        }
        for (Character c: f.noTerminales) {
            f.obtenerSiguientes(c);
        }
        for(PS p : f.siguientes){
            System.out.println("Siguientes de "+p.simbolo+":");
            System.out.println(p.siguientes.toString());
        }
    }
}
