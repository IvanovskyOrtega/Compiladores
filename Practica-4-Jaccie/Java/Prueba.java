

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */




/**
 *
 * @author ivanovsky
 */
public class Prueba{
    public static void main(String[] args) {
        Compile compilador = new Compile();
        java.util.Scanner input = new java.util.Scanner(System.in);
        String entrada;
        System.out.println("Expresion a evaluar: ");
        entrada = input.next();
        compilador.setInput(entrada);
        compilador.run();
    }
}
