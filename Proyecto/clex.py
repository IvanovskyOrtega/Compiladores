# ------------------------------------------------------------
# clex.py
#
# Analizador lexico de expresiones de lenguaje C
# 
# ------------------------------------------------------------
import ply.lex as lex

# List of token names.   This is always required
tokens = (
    'D',
    'L',
    'H',
    'E',
    'FS',
    'IS',
    'COMMENT',
    'AUTO',
    'BREAK',
    'CASE',
    'CHAR',
    'CONST',
    'CONTINUE',
    'DEFAULT',
    'DO',
    'DOUBLE',
    'ELSE',
    'ENUM',
    'EXTERN',
    'FLOAT',
    'FOR',
    'GOTO',
    'IF',
    'INT',
    'LONG',
    'REGISTER',
    'RETURN',
    'SHORT',
    'SIGNED',
    'SIZEOF',
    'STATIC',
    'STRUCT',
    'SWITCH',
    'TYPEDEF',
    'UNION',
    'UNSIGNED',
    'VOID',
    'VOLATILE',
    'WHILE',
    'IDENTIFIER',
    'CONSTANT',
    'STRING_LITERAL',
    'ELLIPSIS',
    'RIGHT_ASSIGN',
    'LEFT_ASSIGN',
    'ADD_ASSIGN',
    'SUB_ASSIGN',
    'MUL_ASSIGN',
    'DIV_ASSIGN',
    'MOD_ASSIGN',
    'AND_ASSIGN',
    'XOR_ASSIGN',
    'OR_ASSIGN',
    'RIGHT_OP',
    'LEFT_OP',
    'INC_OP',
    'DEC_OP',
    'PTR_OP',
    'AND_OP',
    'OR_OP',
    'LE_OP',
    'GE_OP',
    'EQ_OP',
    'NE_OP',
    'SEMICOLON',
    'CURLY_OP_BRACKET',
    'CURLY_CL_BRACKET',
    'COMMA',
    'COLON',
    'ASSIGN',
    'OP_PARENTHESES',
    'CL_PARENTHESES',
    'OP_BRACKET',
    'CL_BRACKET',
    'DOT',
    'AMPERSAND',
    'EXCLAMATION',
    'PRIME',
    'MINUS',
    'PLUS',
    'TIMES',
    'OVER',
    'MOD',
    'LESS_THAN',
    'MORE_THAN',
    'POWER',
    'OR',
    'INTERROGATIVE',
   )

# Regular expression rules for simple tokens
t_AUTO = r'auto'
t_BREAK = r'break'
t_CASE = r'case'
t_CHAR = r'char' 
t_CONST = r'const'
t_CONTINUE = r'continue'
t_DEFAULT = r'default'
t_DO = r'do'
t_DOUBLE = r'double'
t_ELSE = r'else'
t_ENUM = r'enum'
t_EXTERN = r'extern'
t_FLOAT = r'float'
t_FOR = r'for'
t_GOTO = r'for'
t_IF = r'if'
t_INT = r'int'
t_LONG = r'long'
t_REGISTER = r'register'
t_RETURN = r'return'
t_SHORT = r'short'
t_SIGNED = r'signed'
t_SIZEOF = r'sizeof'
t_STATIC = r'static'
t_STRUCT = r'struct'
t_SWITCH = r'switch'
t_TYPEDEF = r'typedef'
t_UNION = r'union'
t_UNSIGNED = r'unsigned'
t_VOID = r'void'
t_VOLATILE = r'volatile'
t_WHILE = r'while'
t_D   = r'[0-9]'
t_L = r'[a-zA-Z]'
t_H = r'[a-fA-F0-9]'
t_E = r'[Ee][\+-]?{D}+'
t_FS = r'f|F|l|L'
t_IS = r'(u|U|l|L)+'
t_IDENTIFIER = r'{L}({L}|{D})*'
t_CONSTANT = r'(0[xX]{H}+{IS}?)|(0{D}+{IS}?)|({D}+{IS}?)|({D}+{E}{FS}?)|({D}*"."{D}+({E})?{FS}?)|({D}+"."{D}+({E})?{FS}?)'
t_STRING_LITERAL = r'L?"([^"\n]|(\\"))*"$'
t_ELLIPSIS = r'"..."'
t_RIGHT_ASSIGN = r'>>='
t_LEFT_ASSIGN = r'<<='
t_ADD_ASSIGN = r'\+='
t_SUB_ASSIGN = r'-='
t_MUL_ASSIGN = r'\*='
t_DIV_ASSIGN = r'/='
t_MOD_ASSIGN = r'%='
t_AND_ASSIGN = r'&='
t_XOR_ASSIGN = r'^='
t_OR_ASSIGN = r'\|='
t_RIGHT_OP = r'>>'
t_LEFT_OP = r'<<'
t_INC_OP = r'\+\+'
t_DEC_OP = r'--'
t_PTR_OP = r'->'
t_AND_OP = r'&&'
t_OR_OP = r'\|\|'
t_LE_OP = r'<='
t_GE_OP = r'>='
t_EQ_OP = r'=='
t_NE_OP = r'!='
t_SEMICOLON = r';'
t_CURLY_OP_BRACKET = r'\{'
t_CURLY_CL_BRACKET = r'\}'
t_COMMA = r','
t_COLON = r':'
t_ASSIGN = r'='
t_OP_PARENTHESES = r'\('
t_CL_PARENTHESES = r'\)'
t_OP_BRACKET = r'\['
t_CL_BRACKET = r'\]'
t_DOT = r'.'
t_AMPERSAND = r'&'
t_EXCLAMATION = r'°'
t_PRIME = r'~'
t_MINUS = r'-'
t_PLUS = r'\+'
t_TIMES = r'\*'
t_OVER = r'/'
t_MOD = r'%'
t_LESS_THAN = r'<'
t_MORE_THAN = r'>'
t_POWER = r'"^"'
t_OR = r'\|'
t_INTERROGATIVE = '\?'

# A regular expression rule with some action code
def t_COMMENT(t):
    r'\#.*'
    pass

# A string containing ignored characters (spaces and tabs)
t_ignore  = ' \t\n'

# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()