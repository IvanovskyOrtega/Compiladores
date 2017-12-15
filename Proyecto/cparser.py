import ply.yacc as yacc
import clexer
tokens = clexer.tokens

class C_Parser:   
    def p_primary_expression(self,p):
        '''primary_expression : IDENTIFIER
                              | CONSTANT
                              | STRING_LITERAL
                              | OP_PARENTHESES expression CL_PARENTHESES'''
    def p_postfix_expression(self,p):
        '''postfix_expression : primary_expression
                              | postfix_expression OP_BRACKET expression CL_BRACKET
                              | postfix_expression OP_PARENTHESES CL_PARENTHESES
                              | postfix_expression OP_PARENTHESES argument_expresion_list CL_PARENTHESES
                              | postfix_expression DOT IDENTIFIER
                              | postfix_expression PTR_OP IDENTIFIER
                              | postfix_expression INC_OP
                              | postfix_expression DEC_OP'''
    def p_argument_expression_list(self,p):
        '''argument_expression_list : assignment_expression
                                    : argument_expression_list COMMA assignment_expression'''
    def p_unary_expression(self,p):
        '''unary_expression : postfix_expression
                            | INC_OP unary_expression
                            | DEC_OP unary_expression
                            | unary_operator cast_expression
                            | SIZEOF unary_expression
                            | SIZEOF OP_PARENTHESES type_name CL_PARANTHESES'''
    def p_cast_expression(self,p):
        '''cast_expression : unary_expression
                           | OP_PARENTHESES type_name CL_PARENTHESES cast_expression'''
    def p_multiplicative_expression(self,p):
        '''multiplicative_expression : cast_expression
                                     | multiplicative_expression TIMES cast_expression
                                     | multiplicative_expression OVER cast_expression
                                     | multiplicative_expression MOD cast_expression'''
    def p_additive_expression(self,p):
        '''additive_expression : multiplicative_expression
                               | additive_expression PLUS multiplicative_expression
                               | additive_expression MINUS multiplicative_expression'''
    def p_shif_expression(self,p):
        '''shift_expression : additive_expression
                            | shift_expression LEFT_OP additive_expression
                            | shift_expression RIGHT_OP additive_expression'''
    def p_relational_expression(self,p):
        '''relational_expression : shift_expression
                                 | relational_expression LESS_THAN shift_expression
                                 | relational_expression MORE_THAN shitf_expression
                                 | relational_expression LE_OP shift_expression
                                 | relational_expression GE_OP shift_expression'''
    def p_equality_expression(self,p):
        '''equality_expression : relational_expression
                               | equality_expression LESS_THAN relational_expression
                               | equality_expression MORE_THAN relational_expression
                               | equality_expression LE_OP relational_expression
                               | equality_expression GE_OP relational_expression'''
    def p_and_expression(self,p):
        '''and_expression : equality_expression
                          | and_expression AND equality_expression'''
    def p_exlusive_or_expression(self,p):
        '''exlusive_or_expression : equality_expression
                                  | exlusive_or_expression XOR and_expression'''
    def p_inclusive_or_expression(self,p):
        '''inclusive_or_expression : equality_expression
                                   | inclusive_or_expression OR exclusive_or_expression'''
    def p_logical_and_expression(self,p):
        '''logical_and_expression : inclusive_or_expression
                                  | logical_and_expression AND_OP inclusive_or_expression'''
    def p_logical_or_expression(self,p):
        '''logical_or_expression : logical_and_expression
                                | logical_or_expression OR_OP logical_and_expression'''
    def p_conditional_expression(self,p):
        '''conditional_expression : logical_or_expression
                                  | logical_or_expression INTERROGATIVE expression COLON conditional_expression'''
    def p_assignment_expression(self,p):
        '''assignement_expression : conditional_expression
                                  | unary_expression assignment_operator assignment_expression'''
    def p_assignment_operator(self,p):
        '''assignment_operator : ASSIGN
                               | MUL_ASSIGN
                               | DIV_ASSIGN
                               | MOD_ASSIGN
                               | ADD_ASSIGN
                               | SUB_ASSIGN
                               | LEFT_ASSIGN
                               | RIGHT_ASSIGN
                               | AND_ASSIGN
                               | XOR_ASSIGN
                               | OR_ASSIGN'''
    def p_expression(self,p):
        '''expression : assignment_expression
                      | expression COMMA assignment_expression'''
    def p_constant_expression(self,p):
        '''constant_expression : conditional_expression'''
    def p_declaration(self,p):
        '''declaration : declaration_specifiers SEMICOLON
                       | declaration_specifiers init_declarator_list SEMICOLON'''
    def init_declarator_list(self,p):
        '''init_declarator_list : init_declarator
                                | init_declarator_list COMMA init_declarator'''
    def p_init_delcarator(self,p):
        '''init_declarator : declarator
                           | declarator ASSIGN initializer'''
    def p_storage_class_specifier(self,p):
        '''storage_class_specifier : TYPEDEF
                                   | EXTERN
                                   | STATIC
                                   | AUTO
                                   | REGISTER'''
    def p_type_specifier(self,p):
        '''type_specifier : VOID
                          | CHAR
                          | SHORT
                          | INT
                          | LONG
                          | FLOAT
                          | DOUBLE
                          | SIGNED
                          | UNSIGNED
                          | struct_or_union_specifier
                          | enum_specifier
                          | TYPE_NAME'''
    def p_struct_or_union_specifier(self,p):
        '''struct_or_union_specifier : struct_or_union IDENTIFIER OP_PARENTHESES struct_declaration_list CL_PARENTHESES
                                     | struct_or_union OP_PARENTHESES struct_declaration_list CL_PARENTHESES
                                     | struct_or_union IDENTIFIER'''
    def p_struct_or_union(self,p):
        '''struct_or_union : STRUCT
                           | UNION'''    
    def p_struct_declaration_list(self,p):
        '''struct_declaration_list : struct_declaration
                                   | struct_declaration_list struct_declaration''' 
    def p_struct_declaration(self,p):
        '''struct_declaration : specifier_qualifier_list struct_declarator_list SEMICOLON''' 
    def p_specifier_qualifier_list(self,p):
        '''specifier_qualifier_list : type_specifier specifier_qualifier_list
                                    | type_specifier
                                    | type_qualifier specifier_qualifier_list
                                    | type_qualifier'''
    def p_struct_declarator_list(self,p):
        '''struct_declarator_list : struct_declarator
                                  | struct_declarator_list COMMA struct_declarator'''
    def p_struct_declarator(self,p):
        '''struct_declarator : declarator
                             | COLON constant_expression
                             | declarator COLON constant_expression'''
    def p_enum_specifier(self,p):
        '''enum_specifier : ENUM OP_PARENTHESES enumerator_list CL_PARENTHESES
                          | ENUM IDENTIFIER OP_PARENTHESES enumerator_list CL_PARENTHESES
                          | ENUM IDENTIFIER'''
    def p_enumerator_list(self,p):
        '''enumerator_list : enumerator
                           | enumerator_list COMMA enumerator'''
    def p_enumerator(self,p):
        '''enumerator : IDENTIFIER
                      | IDENTIFIER ASSIGN constant_expression'''
    def p_type_qualifier(self,p):
        '''type_qualifier : CONST
                          | VOLATILE'''
    def p_declarator(self,p):
        '''declarator : pointer direct_declarator
                      | direct_declarator'''
    def p_direct_declarator(self,p):
        '''direct_declarator : IDENTIFIER
                             | OP_PARENTHESES declarator CL_PARENTHESES
                             | direct_declarator OP_BRACKET constant_expression CL_BRACKET
                             | direct_declarator OP_BRACKET CL_BRACKET
                             | direct_declarator OP_PARENTHESES parameter_type_list CL_PARENTHESES
                             | direct_declarator OP_PARENTHESES identifier_list CL_PARENTHESES
                             | direct_declarator OP_PARENTHESES CL_PARENTHESES'''
    def p_pointer(self,p):
        '''pointer : TIMES
                   | TIMES type_qualifier_list
                   | TIMES pointer
                   | TIMES typer_qualifier_list pointer'''
    def p_type_qualifier_list(self,p):
        '''type_qualifier_list : type_qualifier
                               | type_qualifier_list type_qualifier'''
    def p_parameter_type_list(self,p):
        '''parameter_type_list : parameter_list
                               | parameter_list COMMA ELLIPSIS'''
    def p_parameter_list(self,p):
        '''parameter_list : parameter_declaration
                          | parameter_list COMMA parameter_declaration'''
    def p_parameter_declaration(self,p):
        '''parameter_declaration : declaration_specifiers declarator
                                 | declaration_specifiers abstract_declarator
                                 | declaration_specifiers'''
    def p_identifier_list(self,p):
        '''identifier_list : IDENTIFIER
                           | identifier_list COMMA IDENTIFIER'''
    def p_type_name(self,p):
        '''type_name : specifier_qualifier_list
                     | specifier_qualifier_list abstract_declarator'''
    def p_abstract_declarator(self,p):
        '''abstract_declarator : pointer
                               | direct_abstract_declarator
                               | pointer direct_abstract_declarator'''
    def p_direct_abstract_declarator(self,p):
        '''direct_abstract_declarator : OP_PARENTHESES abstract_declarator CL_PARENTHESES
                                      | OP_BRACKET CL_BRACKET
                                      | OP_BRACKET constant_expression CL_BRACKET
                                      | direct_abstract_declarator OP_BRACKET CL_BRACKET
                                      | OP_PARENTHESES CL_PARENTHESES
                                      | OP_PARENTHESES parameter_type_list CL_PARENTHESES
                                      | direct_abstract_declarator OP_PARENTHESES CL_PARENTHESES
                                      | direct_abstract_declarator OP_PARENTHESES parameter_type_list CL_PARENTHESES'''
    def p_initializer(self,p):
        '''initializer : assignment_expression
                       | CURLY_OP_BRACKET initializer_list CURLY_CL_BRACKET
                       | CURLY_OP_BRACKET initializer_list COMMA CURLY_CL_BRACKET'''
    def p_initializer_list(self,p):
        '''initializer_list : initializer
                            | initializer_list COMMA initializer'''
    def p_statement(self,p):
        '''statement : labeled_statement
                     | compound_statement
                     | expression_statement
                     | selection_statement
                     | iteration_statement
                     | jump_statement'''
    def p_labeled_statement(self,p):
        '''labeled_statement : IDENTIFIER COLON statement
                             | CASE constant_expression COLON statement
                             | DEFAULT COLON statement'''
    def p_compound_statement(self,p):
        '''compound_statement : CURLY_OP_BRACKET CURLY_CL_BRACKET
                              | CURLY_OP_BRACKET statement_list CURLY_CL_BRACKET
                              | CURLY_OP_BRACKET declaration_list CURLY_CL_BRACKET
                              | CURLY_OP_BRACKET declaration_list statement_list CURLY_CL_BRACKET'''
    def p_declaration_list(self,p):
        '''declaration_list : declaration
                            | declaration_list declaration'''
    def p_statement_list(self,p):
        '''statement_list : statement
                          | statement_list statement'''
    def p_expression_statement(self,p):
        '''expression_statement : SEMICOLON
                                | expression SEMICOLON'''
    def p_selection_statement(self,p):
        '''selection_statement : IF OP_PARENTHESES expression CL_PARENTHESES statement
                               | IF OP_PARENTHESES expression CL_PARENTHESES statement ELSE statement
                               | SWITCH OP_PARENTHESES expression CL_PARENTHESES statement'''
    def p_iteration_statement(self,p):
        '''iteration_statement : WHILE OP_PARENTHESES expression CL_PARENTHESES statement
                               | DO statement WHILE OP_PARENTHESES expression CL_PARENTHESES SEMICOLON
                               | FOR OP_PARENTHESES expression_statement expression_statement CL_PARENTHESES statement
                               | FOR OP_PARENTHESES expression_statement expression_statement expression CL_PARENTHESES statement'''
    def p_jump_statement(self,p):
        '''jump_statement : GOTO IDENTIFIER SEMICOLON
                          | CONTINUE SEMICOLON
                          | BREAK SEMICOLON
                          | RETURN SEMICOLON
                          | RETURN expression SEMICOLON'''
    def p_translation_unit(self,p):
        '''translation_unit : external_declaration
                            | translation_unit external_declaration'''
    def external_declaration(self,p):
        '''external_declaration : function_definition
                                | declaration'''
    def function_definition(self,p):
        '''function_definition : declaration_specifiers declarator declaration_list compound statement
                               | declaration_specifiers declarator compound_statement
                               | declarator declaration_list compound_statement
                               | declarator compound_statement'''
    def p_funcall_err(self,p):
        '''ID LPAREN error RPAREN'''
        print "Error\n"
    def build(self):
        self.parser = yacc.yacc(object=self)