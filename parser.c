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
    appel de analyse_paramètres()
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

    // ajout du symbole correspondant au nom de la fonction dans la table des symboles
    // retourner l’AST pour la fonction “main”

    return func_node;
}

ast_list_t* analyse_param(buffer_t *buffer, ast_list_t *list_param) {
    /**
    Skip blank
    Si ( = first
    cherche Var (type + nom)
    Si first
     - new liste avec la var trouvée
    sinon
     - add liste avec la var trouvée

    Si détecte , = recursif (rappel analyse_param)
    Si détecte ) return
    return list 
     */
}

var_type_e analyse_return(buffer_t *buffer) {
    /**
    Skip blank
    Cherche :
    Cherche Return type dans l'enum var_type_e
     */
}

ast_list_t* analyse_corps(buffer_t *buffer, ast_list_t *list_lines) {
    /**
    Skip blank
    Si { = first


    Faire des trucs pour comprendre une ligne de code, HF

    Si first
     - new liste avec l'instruction trouvée
    sinon
     - add liste avec l'instruction trouvée

    Si détecte autre chose que } = récursif (rapelle analyse_corps)
    Si détecte }, return la liste
    return la liste 
     */
}

ast_list_t* analyse_line(buffer_t *buffer, ast_list_t *list_instructions){
    /**
    Skip blank

    Analyse lexem pour chercher un type
    check enum pour voir si le type existe

    Si le type existe :
     - stock l'enum dans une variable 
     - Analyse lexem pour le nom
     - stock le nom dans une variable
     - check si le prochain charactère est un ';'

        new_assignment
        Si c'est un ';'
         - return assignment
        Si c'est pas un ';'
         - rollback de 1 
         - get_operator
         - on stock l'operator
         - analyse_binary



    */
}

ast_t *parse_expression(buffer_t *buffer){
    /**
    lexer get_alphanum
    stock le result 

    Si c'est un ';'
     - return le result
    Si c'est pas un ';'
     
        Faut regarder si c'est une fonction

     - rollback de 1  
     - get_operator 
     - on stock l'operator 
     - recursivité analyse_binary 


    */
}