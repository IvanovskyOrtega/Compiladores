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
)

trastes = ('t0','t1','t2','t3','t4','t5','t6','t7','t8','t9','t10','t11',
           't12','t13','t14','t15','t16','t17','t18','t19','t20','t21','t22',)

cuerdas = ('c1','c2','c3','c4','c5','c6',)

instrumentos = {'nylon'                : 'AN',
                'acustica_nylon'       : 'AN',
                'AN'                   : 'AN',
                'acero'                : 'AA',
                'acustica_acero'       : 'AA',
                'AA'                   : 'AA',
                'jazz'                 : 'EJ',
                'electrica_jazz'       : 'EJ',
                'EJ'                   : 'EJ',
                'clean'                : 'EC',
                'electrica_limpia'     : 'EC',
                'EC'                   : 'EC',
                'muted'                : 'EM',
                'electrica_muted'      : 'EM',
                'EM'                   : 'EM',
                'overdriven'           : 'OG',
                'electrica_overdriven' : 'OG',
                'OG'                   : 'OG',
                'distorsion'           : 'DG',
                'electrica_distorsion' : 'DG',
                'DG'                   : 'DG',
                }

# Definimos las expresiones regulares para los tokens
t_TEMPO = r'\b\d{1,3}\b'
t_AN = r'(nylon)|(acustica_nylon)|(AN)'
t_AA = r'(acero)|(acustica_acero)|(AA)'
t_EJ = r'(jazz)|(electrica_jazz)|(EJ)'
t_EC = r'(clean)|(electrica_limpia)|(EC)'
t_EM = r'(muted)|(electrica_muted)|(EM)'
t_OG = r'(overdriven)|(electrica_overdriven)|(OG)'
t_DG = r'(distorsion)|(electrica_distorsion)|(DG)'

# Ignoramos espacios, tabuladores y saltos de linea
t_ignore  = ' \t\n'

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