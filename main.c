#include <stdio.h>
#include <stdlib.h>
#include "ressources/buffer.h"
#include "ressources/utils.h" 
#include "lexer.h" 
#include "ast.h"
#include "parser.h"


int main() {
    buffer_t buffer;

    FILE *file = fopen("fileToRead2.txt", "r");

    // Vérifie que le fichier a été ouvert correctement
    if (file == NULL) {
        perror("Erreur reading the file");
        return 1;
    }
    printf("File opened\n");

    buf_init(&buffer, file);

    //lexer_test(&buffer);

    ast_list_t* func_list = parser(&buffer);

    // Ferme le fichier pour éviter les erreurs
    fclose(file);
    printf("THE END, file closed and memory freed \n");
}