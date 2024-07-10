#include <stdlib.h>
#include <string.h>
#include "ressources/buffer.h"
#include "lexer.h"
#include "ast.h"
#include "parser.h"


ast_list_t* parser(buffer_t *buffer) {
    printf("parser start\n");
    ast_list_t *func_list;

    while (!buf_eof_strict(buffer))
    {
        char *first_word = lexer_getalphanum(buffer);
        printf("%s\n", first_word);
        if (first_word != NULL && strcmp(first_word, "function") == 0) {
            printf("function !!\n");

            ast_t *function = analyse_function(buffer);

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

ast_t* analyse_function(buffer_t *buffer) {
    /**
    analyse du lexème qui sera le nom de la fonction
    appel de analyse_args()
    appel de analyse_type_de_retour()
    appel de analyse_corps_de_fonction()
    création de l’AST pour la fonction “main” avec les paramètres, type de retour et corps de
    fonction
     */
    char *func_name = lexer_getalphanum(buffer);
    ast_list_t *list_param; 
    list_param = analyse_param(buffer, list_param);
    var_type_e return_type = analyse_return(buffer);
    ast_list_t *list_instructions;
    list_instructions = analyse_corps(buffer, list_instructions);

    ast_t *func_node = ast_new_function(func_name, return_type, list_param, list_instructions);

    // TODO ajout du symbole correspondant au nom de la fonction dans la table des symboles

    // retourner l’AST pour la fonction “main”
    return func_node;
}

ast_list_t* analyse_param(buffer_t *buffer, ast_list_t *list_param) {
    /**
    Skip blank
    Si '(' alors first=true
    cherche Var (type + nom)
    get_alphanum type
    vérifier dans l'enum si le type existe

    Si type existe pas :
        crash :(
    check_valid_name
    get_alphanum nom 
    crée ast_t de la déclaration de var

    Si first
        new liste avec la var trouvée
    sinon
        add liste avec la var trouvée

    Si détecte , = recursif (rappel analyse_param)
    get_char
    Si détecte ) return
    return list 
     */
}

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

ast_list_t* analyse_corps(buffer_t *buffer, ast_list_t *list_lines) {
    /**
    Skip blank
    getchar
    Si '{' 
        = first
    Sinon 
        crash :(

    analyse_instruction

    Si détecte autre chose que } = crash :(
    Si détecte }, return la liste
    return la liste 
     */
}

ast_list_t* analyse_instruction(buffer_t *buffer, ast_list_t *list_instructions){
    /**
    Skip blank

    lexem_getalphanum 
    Si c'est un type
        check enum pour voir si le type existe

        Si existe pas :
            crash :(

        Si le type existe :
            stock l'enum dans une variable 
            check_valid_name
            get_alphanum
            creation ast new_declation
    Sinon 
        check_valid_name
         isFunc = is_function

        Si isFunc == true
            // C'est une fonction
            lexer get_alphanum
            analyse_param
            // TODO Regarde la table des symboles pour vérifier qu'on a le bon nombre de params avec le bon type au bon endroit
            // TODO Parcourir les deux listes, args dans les symboles, et params pour vérifier que tout correspond
            stocker ces infos et ast_new_fncall

        sinon 
            // C'est une variable
            var name = get alphanum 
            // TODO Verfier que la var exist dans la table des symboles de la func
            // TODO Récupère le type de la var dans la table des symboles
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

    */
}

ast_t *parse_expression(buffer_t *buffer, context_e context){
    /**
    Skipblank
    lexer get_num_rollback
    Si == NULL
        // TODO Mettre des vérifs pour les mots clé logiques (if, while, return) faut pas qu'il aille vérifier fonction/var

        isFunc = is_function

        Si isFunc == true
            // C'est une fonction
            lexer get_alphanum
            analyse_param
            // TODO Regarde la table des symboles pour vérifier qu'on a le bon nombre de params avec le bon type au bon endroit
            // TODO Parcourir les deux listes, args dans les symboles, et params pour vérifier que tout correspond
            stocker ces infos et ast_new_fncall

        sinon 
            // C'est une variable
            var name = get alphanum 
            // TODO Verfier que la var exist dans la table des symboles de la func
            // TODO Récupère le type de la var dans la table des symboles
            crée ast de la variable
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

ast_list_t* analyse_args(buffer_t *buffer, ast_list_t list_args) {
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
    
    stock le nom dans une variable

    return true, pak tout est ok

    // C'est sensé crash à chaque fois que ça respecte pas
    */
}

bool is_function(buffer_t *buffer) {
    /**
    Si check_valid_name == true
        get alphanum
        recup longueur de la string (strlen)
        skip blank
        next_char
        rollback strlen + 1 (la parenthese)
        Si next_char == '('
            // TODO Verfier que la var exist dans la table des symboles globale sinon crash
            return true
    
    return false
     */
}