import ply.yacc as yacc
import guitarLex

tokens = guitarLex.tokens

def p_PISTA(p):
    '''PISTA : NOMBRE DEFINICION_PISTA'''

def p_DEFINICION_PISTA(p):
    '''DEFINICION_PISTA : INSTRUMENTO TEMPO NOTAS'''

def p_INSTRUMENTO(p):
    '''INSTRUMENTO : AN
                   | AA
                   | EJ
                   | EC
                   | EM
                   | OG
                   | DG'''

def p_NOTAS(p):
    '''NOTAS : NOTA NOTAS
             | NOTA'''

def p_NOTA(p):
    '''NOTA : TRASTE CUERDA'''

def p_error(p):
        if p:
            print("Error de sintaxis en '%s'" % p.value)
        else:
            print("Error de sintaxis en EOF")

parser = yacc.yacc(start='PISTA') 