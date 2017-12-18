import ply.lex as lex

# Lista de tokens
tokens = (
    'TEMPO',
    'AN',
    'AA',
    'EJ',
    'EC',
    'EM',
    'OG',
    'DG',
    'TRASTE',
    'CUERDA',
    'COMENTARIO',
    'NOMBRE',
    'NUEVA_LINEA',
)

trastes = ('t0','t1','t2','t3','t4','t5','t6','t7','t8','t9','t10','t11',
           't12','t13','t14','t15','t16','t17','t18','t19','t20','t21','t22',)

cuerdas = ('c1','c2','c3','c4','c5','c6',)

instrumentos = {'AN'                   : 'AN',
                'AA'                   : 'AA',
                'EJ'                   : 'EJ',
                'EC'                   : 'EC',
                'EM'                   : 'EM',
                'OG'                   : 'OG',
                'DG'                   : 'DG',
                }

# Definimos las expresiones regulares para los tokens
t_TEMPO = r'\b\d{1,3}\b'
t_AN = r'AN'
t_AA = r'AA'
t_EJ = r'EJ'
t_EC = r'EC'
t_EM = r'EM'
t_OG = r'OG'
t_DG = r'DG'

# Ignoramos espacios, tabuladores y saltos de linea
t_ignore  = ' \t'

def t_TRASTE(t):
    r'(t0)|(t((1[0-9])|(2[0-4])))'
    if t.value in trastes:
        t.type = 'TRASTE'
    return t

def t_CUERDA(t):
    r'c[1-6]'
    if t.value in cuerdas:
        t.type = 'CUERDA'
    return t

# Se pueden agregar comentarios del tipo: /* texto */
def t_COMENTARIO(t):
    r'//.*|/\*(.|\n)*\*/'
    pass # Hace que no cuente como token

# Esta funcion sera de ayuda para los "time" en el midi
def t_NUEVA_LINEA(t):
	r'\n+'
	t.lexer.lineno += len(t.value)
	return t

def t_NOMBRE(t):
    r'[a-zA-Z_][a-zA-Z0-9_]+'
    if t.value not in trastes:
        if t.value not in cuerdas:
            if t.value not in instrumentos:
                t.type = 'NOMBRE'
            else:
                t.type = instrumentos[t.value]
        else:
            t.type = 'CUERDA'
    else:
        t.type = 'TRASTE'
    return t

# Regla para el manejo de errores
def t_error(t):
    print("Caracter no reconocido '%s'" % t.value[0])
    t.lexer.skip(1)

# Construimos el lexer
lexer = lex.lex()
