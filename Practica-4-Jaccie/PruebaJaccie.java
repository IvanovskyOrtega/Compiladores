package pruebajaccie;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;

/**
 *
 * @author Ivanovsky
 */
public class PruebaJaccie {

    
    public static void main(String[] args) {
        Scanner scanner =  new Scanner();
        java.util.Scanner input = new java.util.Scanner(System.in);
        String entrada;
        char op = 's';
        char op2;
        while(op == 's'){
            System.out.println("1) Entrada desde consola\n");
            System.out.println("2) Entrada desde archivo\n");
            System.out.println("Ingrese opción:\t");
            op2 = input.nextLine().charAt(0);
            switch (op2) {
                case '1':
                    System.out.println("................\n");
                    entrada = input.nextLine();
                    break;
                case '2':
                    System.out.println("Nombre del archivo:\t");
                    String archivo = "test/"+input.nextLine();
                    entrada = leerArchivo(archivo);
                    break;
                default:
                    entrada = " ";
                    break;
            }
            scanner.getScannerInput().setInput(entrada);
            try {
                scanner.resetScanner();
                scanner.scanAll();
                System.out.println(scanner.getResultAsString());
            } catch (Exception e) {
                System.out.println("Error while scanning: "+e.toString()+"\n");
            }
            System.out.println("Continuar? (s/n):\t");
            op = input.nextLine().charAt(0);
            for(int i = 0; i < 100; i++)
            {
                System.out.println("\b") ;
            }
        }
    }
    
    /**
     * Este mtodo fue obtenido en: 
     * @url https://stackoverflow.com/questions/326390/how-do-i-create-a-java-string-from-the-contents-of-a-file
     * @autor user590444
     * @param nombreDelArchivo
     * @return 
     */
    
    public static String leerArchivo(String nombreDelArchivo) {
            File f = new File(nombreDelArchivo);
            try {
                byte[] bytes = Files.readAllBytes(f.toPath());
                System.out.println("AHH");
                return new String(bytes,"UTF-8");
            } catch (FileNotFoundException e) {
                System.out.println(e.toString());
            } catch (IOException e) {
                System.out.println(e.toString());
            }
            return "";
    }
 
}
