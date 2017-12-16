import ply.yacc as yacc
import guitarLex

tokens = guitarLex.tokens
codigo_intermedio = open('codigoIntermedio.py','w')
codigo_intermedio.write('from midiutil import MIDIFile\n\n')
codigo_intermedio.write('track    = 0\n')
codigo_intermedio.write('channel  = 0\n')
codigo_intermedio.write('duration = 1\n')
codigo_intermedio.write('volume   = 100\n')

notas_cuerda_6 = {
    't0' : '40','t1' : '41','t2' : '42','t3' : '43','t4' : '44','t5' : '45','t6' : '46',
    't7' : '47','t8' : '48','t9' : '49','t10' : '50','t11' : '51','t12' : '52','t13' : '53',
    't14' : '54','t15' : '55','t16' : '56','t17' : '57','t18' : '58','t19' : '59','t20' : '60',
    't21' : '61','t22' : '62',
}

notas_cuerda_5 = {
    't0' : '45','t1' : '46','t2' : '47','t3' : '48','t4' : '49','t5' : '50','t6' : '51',
    't7' : '52','t8' : '53','t9' : '54','t10' : '55','t11' : '56','t12' : '57','t13' : '58',
    't14' : '59','t15' : '60','t16' : '61','t17' : '62','t18' : '63','t19' : '64','t20' : '65',
    't21' : '66','t22' : '67',
}

notas_cuerda_4 = {
    't0' : '50','t1' : '51','t2' : '52','t3' : '53','t4' : '54','t5' : '55','t6' : '56',
    't7' : '57','t8' : '58','t9' : '59','t10' : '60','t11' : '61','t12' : '62','t13' : '63',
    't14' : '64','t15' : '65','t16' : '66','t17' : '67','t18' : '68','t19' : '69','t20' : '70',
    't21' : '71','t22' : '72',
}
notas_cuerda_3 = {
    't0' : '55','t1' : '56','t2' : '57','t3' : '58','t4' : '59','t5' : '60','t6' : '61',
    't7' : '62','t8' : '63','t9' : '64','t10' : '65','t11' : '66','t12' : '67','t13' : '68',
    't14' : '69','t15' : '70','t16' : '71','t17' : '72','t18' : '73','t19' : '74','t20' : '75',
    't21' : '76','t22' : '77',
}

notas_cuerda_2 = {
    't0' : '59','t1' : '60','t2' : '61','t3' : '62','t4' : '63','t5' : '64','t6' : '65',
    't7' : '66','t8' : '67','t9' : '68','t10' : '69','t11' : '70','t12' : '71','t13' : '72',
    't14' : '73','t15' : '74','t16' : '75','t17' : '76','t18' : '77','t19' : '78','t20' : '79',
    't21' : '80','t22' : '81',
}

notas_cuerda_1 = {
    't0' : '64','t1' : '65','t2' : '66','t3' : '67','t4' : '68','t5' : '69','t6' : '70',
    't7' : '71','t8' : '72','t9' : '73','t10' : '74','t11' : '75','t12' : '76','t13' : '77',
    't14' : '78','t15' : '79','t16' : '80','t17' : '81','t18' : '82','t19' : '83','t20' : '84',
    't21' : '85','t22' : '86',
}

def p_PISTA(p):
    '''PISTA : NOMBRE DEFINICION_PISTA'''
    declaracion_archivo = 'archivoMIDI = open(\'' + str(p[1]) +'.mid\',\'wb\')\n'
    codigo_intermedio.write(declaracion_archivo)

#def p_NOMBRE_ARCHIVO(p):
#    '''NOMBRE_ARCHIVO : NOMBRE'''

def p_DEFINICION_PISTA(p):
    '''DEFINICION_PISTA : VALOR_TEMPO INSTRUMENTO NOTAS'''

def p_VALOR_TEMPO(p):
    '''VALOR_TEMPO : TEMPO'''
    codigo_intermedio.write('tempo    = ' + str(p[1]) + '\n')
    codigo_intermedio.write('MyMIDI = MIDIFile(1)\n')
    codigo_intermedio.write('MyMIDI.addTempo(track, 0, tempo)\n')

def p_INSTRUMENTO(p):
    '''INSTRUMENTO : AN
                   | AA
                   | EJ
                   | EC
                   | EM
                   | OG
                   | DG'''
    if str(p[1]) == "AN":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 25)\n')
    elif str(p[1]) == "AA":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 26)\n')
    elif str(p[1]) == "EJ":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 27)\n')
    elif str(p[1]) == "EC":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 28)\n')
    elif str(p[1]) == "EM":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 29)\n')
    elif str(p[1]) == "OG":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 30)\n')
    elif str(p[1]) == "DG":
        codigo_intermedio.write('MyMIDI.addProgramChange(track, channel, 0, 31)\n')
        

def p_NOTAS(p):
    '''NOTAS : NOTA NOTAS
             | NOTA'''

def p_NOTA(p):
    '''NOTA : TRASTE CUERDA'''
    cuerda = str(p[2])
    traste = str(p[1])
    time = p.lineno(1)-4
    if cuerda == "c1":
        valor_nota = notas_cuerda_1[traste]
    elif cuerda == "c2":
        valor_nota = notas_cuerda_2[traste]
    elif cuerda == "c3":
        valor_nota = notas_cuerda_3[traste]
    elif cuerda == "c4":
        valor_nota = notas_cuerda_4[traste]
    elif cuerda == "c5":
        valor_nota = notas_cuerda_5[traste]
    elif cuerda == "c6":
        valor_nota = notas_cuerda_6[traste]
    codigo_intermedio.write('MyMIDI.addNote(track, channel,'+ str(valor_nota) +','+ str(time) +', duration, volume)\n')

def p_error(p):
        if p:
            print("Error de sintaxis en '%s'" % p.value)
        else:
            print("Error de sintaxis en EOF")

parser = yacc.yacc(start='PISTA') 
