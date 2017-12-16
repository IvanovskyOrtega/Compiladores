from ply.yacc import yacc
from ply.lex import lex
from guitarYacc import parser
from guitarLex import lexer
from guitarYacc import codigo_intermedio
import sys

class AnalizadorSintactico:

    def __init__(self):
        self.lexer = lexer
        self.parser = parser

    def analizar(self,nombreArchivo):
        with open(nombreArchivo,'r') as f:
            input = f.read()
            #print(input)
            print(parser.parse(input,lexer=lexer))
        codigo_intermedio.write('MyMIDI.writeFile(archivoMIDI)')


class Main:

    def iniciar(self):
        analizador_sintactico = AnalizadorSintactico()
        try:
            analizador_sintactico.analizar(str(sys.argv[1]))
        except:
            print('Intenta con archivo valido')

main = Main()
main.iniciar()
