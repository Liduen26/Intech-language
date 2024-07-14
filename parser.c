#include <stdlib.h>
#include <string.h>
#include "ressources/buffer.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include "sym_table.h"


ast_list_t* parser(buffer_t *buffer) {
    printf("parser start\n");
    ast_list_t *func_list;
    sym_table_t *global_sym_table;
    
    while (!buf_eof_strict(buffer))
    {
        char *first_word = lexer_getalphanum(buffer);
        printf("first word : %s\n", first_word);
        if (first_word != NULL && strcmp(first_word, "function") == 0) {
            printf("function !!\n");

            ast_t *function = analyse_function(global_sym_table, buffer);   

            if (func_list->node == NULL){
                // Si c'est null, c'est la première, donc new node
                ast_list_new_node(function);
                
            } else {
                // Pas null, add node
                ast_list_add(&func_list, function);
            }
            
            
        } else {
            printf("pas fonction, exit 1\n");
            free(first_word);
            exit(1);
        }
        
        free(first_word);
    }
    
    printf("parser end\n");
    return func_list;
}

//analyse la fonction dans son ensemble (chef d'orchestre)
ast_t* analyse_function(sym_table_t *global_sym_table, buffer_t *buffer) {
    /**
    analyse du lexème qui sera le nom de la fonction
    appel de analyse_args()
    appel de analyse_type_de_retour()
    appel de analyse_corps_de_fonction()
    création de l’AST pour la fonction “main” avec les paramètres, type de retour et corps de
    fonction
     */

    char *func_name = lexer_getalphanum(buffer);

    sym_table_t *local_table;

    ast_list_t *list_param; 
    list_param = analyse_param(buffer, list_param, local_table);
    var_type_e return_type = analyse_return(buffer);
    ast_list_t *list_instructions;
    list_instructions = analyse_corps(buffer, list_instructions, global_sym_table, local_table);

    ast_t *func_node = ast_new_function(func_name, return_type, list_param, list_instructions);

    // ajout du symbole correspondant au nom de la fonction dans la table des symboles
    sym_list_add(&global_sym_table, func_node);
    // retourner l’AST pour la fonction “main”
    return func_node;
}

//analyse les paramètres d'un fonction, si ',', recursive, si ')' fin
ast_list_t* analyse_param(buffer_t *buffer, ast_list_t *list_param, sym_table_t *local_table) {
    /**
    Skip blank
    cherche Var (type + nom)
    get_alphanum type
    vérifier dans l'enum si le type existe

    Si type existe pas :
        crash :(
    get_alphanum nom 
    check_valid_name
    crée ast_t de la déclaration de var
    sym_list_add dans la table locale du nouveau node

    Si détecte , = recursif (rappel analyse_param)
    get_char
    Si détecte ) return
    return list 
     */

    // Cherche une ( en premier char
    char first_char = buf_getchar_after_blank(buffer);

    // cherche un type
    char *type = lexer_getalphanum(buffer);
    if (type == NULL) {
        printf("ERROR : Incorrect char in parameter type");
        exit(1);
    }
    var_type_e type_e = type_str_to_enum(type);
    if (type_e == INVALID_TYPE) {
        printf("ERROR : Incorrect type name !");
        exit(1);
    }

    // Cherche une var
    char *param_name = lexer_getalphanum(buffer);
    if (param_name == NULL) {
        printf("ERROR : Incorrect var name in parameter");
        exit(1);
    }

    ast_t *ast_var = ast_new_variable(param_name, type_e);
    
    // Ajoute a la table des symboles et crash si elle est déjà dedans
    sym_list_add(&local_table, ast_var);
    
    ast_list_t *list_parameter = ast_list_add(&list_param, ast_var);

    // Regarde le prochain char pour savoir si c'est une "," ou pas
    char next_char = buf_getchar_after_blank(buffer);
    if (next_char == ',') {
        free(type);
        free(param_name);
        analyse_param(buffer, list_parameter, local_table);
    } else if (next_char == ')') {
        free(type);
        free(param_name);
        return list_parameter;
    } else {
        printf("ERROR : ',' or ')' expected after a parameter");
        exit(1);
    }

    return list_parameter;
}

//analyse le return d'une déclaration de fonction
var_type_e analyse_return(buffer_t *buffer) {
    /**
    Skip blank
    Cherche :
    Si pas ':'
        crash :(
    
    Cherche Return type dans l'enum var_type_e
    Si type de retour existe pas dans l'enum :
        crash :(
    
    return type de l'enum
     */
}

//analyse les instruction du début jusqu'a la fin d'une fonction
ast_list_t* analyse_corps(buffer_t *buffer, ast_list_t *list_lines, sym_table_t *global_sym_table, sym_table_t *local_table) {
    /**
    Skip blank
    getchar
    Si '{' 
        = first
    Sinon 
        crash :(

    analyse_instruction

    Si détecte autre chose que } = crash :(
    Crée un ast new_comp_stmt
    return l'ast
     */
}

//analyse une instruction jusqu'a son ";"
ast_list_t* analyse_instruction(buffer_t *buffer, ast_list_t *list_instructions, sym_table_t *global_sym_table, sym_table_t *local_table){
    /**
    Skip blank
    word = lexem_getalphanum 
    switch (word)
    {
    case if:
    /////////////////////////////////////////////////
        analyse_condition < condition
        analyse_corps < valid
        get_alphanum_rollback
        si "else"
            get_alphanum
            get_alphanum_rollback
            Si "if"
                recursif et return un conditional < invalid
            sinon
                get_char_after_blank
                si "{"
                    analyse corps et stocke le cmpd stmt < invalid
                sinon
                    crash :(

        ast_t new_condition avec le binary de condition, le comp stmt de corps, et le résultat du else (conditional ou cmpd stmt)

        break;

    case while:
        analyse_condition < condition
        analyse_corps < stmt
        ast new_loop
        break:
    
    case return:
        parse_expression
        ast new_return
        break:

    default:
        check enum pour voir si le type existe
        Si c'est un type
            get_alphanum
            creation ast new_declation

            sym_list_add dans la table locale du nouveau node
                
        Sinon 
            check_valid_name
    /////////////////////////////////////////////////
            isFunc = is_function

            Si isFunc == true
                // C'est une fonction
                lexer get_alphanum
                analyse_param
                // TODO Regarde la table des symboles pour vérifier qu'on a le bon nombre de params avec le bon type au bon endroit

                check_already_exist dans la table globale
                stocker ces infos et ast_new_fncall

            sinon 
                // C'est une variable
                var name = get alphanum 
                check_already_exist dans la table locale et récup le type de la var

                crée ast de la variable

        Skipblank
        Lire next char
        Si c'est un ';'
            return l'ast créé, ou var ou declaration
        sinon Si c'est un '='
            left = ast du if avant
            right = parse_expression
            créer ast new assignment
            end_char = getchar_after_blank
            rollback 1
        Sinon 
            crash :(

        Si endchar = '}' :
            return asignment
        Sinon
            analyse_instruction (recursivité)
            break;
        }

    return
    */

    char *first_word = lexer_getalphanum(buffer);
    ast_t *ast_result;

    if (strcmp(first_word, "if") == 0) {
        // le mot est un if

    } else if (strcmp(first_word, "while") == 0) {
        // le mot est un while

    } else if (strcmp(first_word, "return") == 0) {
        // le mot est un return

    } else {
        // le mot n'est pas un mot-clé logique, c'est donc var ou un appel de fonction
        var_type_e type = type_str_to_enum(first_word);
        if (type != INVALID_TYPE) {
            // Type, c'est donc une déclaration de var
            char *var_name = lexer_getalphanum(buffer);
            ast_result = ast_new_variable(var_name, type);

            sym_list_add(&local_table, ast_result);
        } else {
            // Pas un type, c'est un appel de var ou de fonction
            
            // Crash si c'est pas qqchose de valide
            check_valid_name(buffer);


        }
        
    }
   


}

// Analyse une condition (2 < 3)
ast_t analyse_condition(buffer_t *buffer, sym_table_t *global_sym_table, sym_table_t *local_table) {
    /*
    Skipblank
    getchar "("

    Si != "("
        crash :(

    Sinon 
        parse_expression dans le context CONDITION
        getoperator
            SI == NULL
                crash :(
            Sinon
                parse_expression
        build ast_t binary
    
    return l'ast
    */
}

//check si func ou var et agit, check binary operator et recursive 
ast_t *parse_expression(buffer_t *buffer, context_e context, sym_table_t *global_sym_table, sym_table_t *local_table){

    char *num = lexer_getalphanum_rollback(buffer);
    ast_t *node = NULL;

    if(num == NULL){

    }
    /**
    Skipblank
    lexer get_num_rollback
    Si == NULL
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        isFunc = is_function

        Si isFunc == true
            // C'est une fonction
            lexer get_alphanum
            analyse_args
            // TODO Regarde la table des symboles pour vérifier qu'on a le bon nombre de params avec le bon type au bon endroit
            // TODO Parcourir les deux listes, args dans les symboles, et params pour vérifier que tout correspond

            check_already_exist dans la table GLOBALE
            stocker ces infos et ast_new_fncall

        sinon 
            // C'est une variable
            var name = get alphanum 
            // TODO Verfier que la var exist dans la table des symboles de la func
            // TODO Récupère le type de la var dans la table des symboles
            crée ast de la variable
            check_already_exist dans la table LOCALE
    sinon
        crée ast integer


    getchar_after_blank
    Si c'est un ';' ET context INSTRUCTION 
        return le result
    sinon Si c'est une ',' ET context ARGUMENT
        return le result
    sinon SI c'est une ')' ET context ARGUMENT
        getchar_after_blank
        Si c'est un ';'
            return 
    sinon SI c'est un "operateur conditionel" || ')' ET context CONDITION
        rollback
        return resultat




    Si c'est pas un ';'
        rollback de 1  
        operator = get_operator 
        If operator == NULL
            crash :(
        recursivité parse_expression 
        créer ast_new_binary avec : l'operateur, left = résultat du if précédent, right result de la recursivité


    return node

    */
}

//vérifie qu'on donne des args quand on déclare une fonction sinon crash
ast_list_t* analyse_args(buffer_t *buffer, ast_list_t *list_args, sym_table_t *global_sym_table, sym_table_t *local_table) {

    char ch = buf_getchar_after_blank(buffer);

    if(ch != '('){
        //si pas de '(', rollback 1 et return null
        buf_rollback(buffer, 1);
        return NULL;
    }

    buf_skipblank(buffer);

    long *num = lexer_getnumber_rollback(buffer);
    ast_t *arg_node = NULL;

    if(num == NULL){
        char *var_name = lexer_getalphanum_rollback(buffer);
        if (var_name == NULL) {
            ch = buf_getchar_after_blank(buffer);
            if (ch == ')') {
                return NULL;
            } else {
                printf("ERROR line %d : Unexpected char in argument(s)\n", buf_getline());
                exit(1);
            }
        } else {
            //si variable
            buf_skipblank(buffer);
            char *next= lexer_getalphanum(buffer);
            var_type_e type = type_str_to_enum(next);
            if (type == INVALID_TYPE) {
                printf("ERROR line %d : Invalid type for argument\n", buf_getline());
                exit(1);
            }
        arg_node = ast_new_variable(var_name, type);
        sym_list_add(&local_table, arg_node);

        list_args = ast_list_add(&list_args, arg_node);
        }
    } else {
        //number donc crash :(
        printf("ERROR line %d : Number in function arguments\n", buf_getline());
        exit(1);
    }

    ch = buf_getchar_after_blank(buffer);
    if (ch == ',')
    {
        analyse_args(buffer, list_args, global_sym_table, local_table);
    } else if (ch == ')'){
        return list_args;
    } else {
        printf("ERRROR line %d : ',' or ')' expected after an argument\n", buf_getline());
        exit(1);
    }

    return list_args;
    


    /**
    Skip blank
    get char
    Si ( 
        = first
    Sinon
        rollback 1

    lexer_get_number_rollback
    si NULL
        lexer_get_alphanum_rollback
        si NULL
            get char after blank
            si c'est ')'
                return NULL (pas de params)
            sinon
                crash :(

    parse_expression

    Si first
        new liste avec la var trouvée
    sinon
        add liste avec la var trouvée

    Si détecte , = recursif (rappel analyse_args)
    Si détecte ) return
    return list 
     */
}

// Renvoie true si le nom de fonction/var est bon sinon crash
void check_valid_name(buffer_t *buffer){
    /**
    Skipblank
    lexem get_operator_rollback
    Si != NULL
        crash :(

    lexem get_number_rollback
    Si != NULL
        crash :(

    lexem get_alphanum_rollback
    Si == NULL
        crash :(
    
    return true, pak tout est ok

    // C'est sensé crash à chaque fois que ça respecte pas
    */
    char* word = lexer_getop_rollback(buffer);
    if (word != NULL) {
        printf("ERROR line %d : Fonctions and Variables must begin with an alphanumeric char !\n", buf_getline());
        exit(1);
    }
    long* num = lexer_getnumber_rollback(buffer);
    if (num != NULL) {
        printf("ERROR line %d: Fonctions and Variables must begin with an alphanumeric char !\n", buf_getline());
        exit(1);
    }

    word = lexer_getalphanum_rollback(buffer);
    if (word == NULL) {
        printf("ERROR line %d: Fonctions and Variables must begin with an alphanumeric char !\n", buf_getline());
        exit(1);
    }
   
    free(word);
    free(num);
}

//renvoie true si c'est une fonction et false si non
bool is_function(buffer_t *buffer) {
    /**
    check_valid_name()
        get alphanum
        recup longueur de la string (strlen)
        skip blank
        next_char
        rollback strlen + 1 (la parenthese)
        Si next_char == '('
            return true
    return false

     */
    
    check_valid_name(buffer);

    //recup le nom de la fonction
    char *name = lexer_getalphanum(buffer);
    if (name == NULL){
        return false;
    }

    size_t name_length = strlen(name);
    buf_getchar_after_blank(buffer);
    char next_char = buf_getchar(buffer);
    buf_rollback(buffer, name_length + 1);

    //check si c'est une '(' après le nom de la fonction
    if (next_char == '('){
        return true;
    }
    return false;

}
bool is_conditional_operator(const char *op) {
    const char *operators[] = {">=", ">", "<", "<=", "==", "!="};
    size_t num_operators = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < num_operators; i++) {
        if (strcmp(op, operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Renvoie l'enum de type en fonction de la var d'entrée
var_type_e type_str_to_enum(char* type_str) {
    if (strcmp(type_str, "int") == 0) {
        return INT;
    } else if (strcmp(type_str, "void") == 0) {
        return VOID;
    } else {
        return INVALID_TYPE;
    }
}