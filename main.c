#include <stdio.h>
#include <stdlib.h>
#include "ressources/buffer.h"
#include "ressources/utils.h" 
#include "lexer.h" 
#include "ast.h"
#include "parser.h"
#include "writer.h"

int main() {
    buffer_t buffer;

    FILE *file = fopen("fileToRead.txt", "r");

    // Vérifie que le fichier a été ouvert correctement
    if (file == NULL) {
        perror("Erreur reading the file");
        return 1;
    }
    printf("File opened\n");

    buf_init(&buffer, file);

    //TEST DU PARSER
    ast_list_t* func_list = parser(&buffer);

    //Ecriture ds le fichier
    FILE *output = fopen("output.ts", "w");
    if (output == NULL) {
        perror("Erreur opening output file");
        return 1;
    }
    write_ast_to_file(output, func_list);
    fclose(output);
    printf("\nAST written to output.ts\n");

    //TEST DU LEXER
    //lexer_test(&buffer);

    //TEST DE LA CREATION LISTE CHAINÉ
    // ast_list_t *prev_node_list = ast_list_new_node(ast_new_integer(2));
    // ast_list_add(&prev_node_list, ast_new_variable("ma var", INT));
    // printList(prev_node_list);

    // Ferme le fichier pour éviter les erreurs
    fclose(file);
    printf("\nTHE END, file closed and memory freed \n");
}