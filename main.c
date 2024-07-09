#include <stdio.h>
#include <stdlib.h>
#include "ressources/buffer.h"
#include "ressources/utils.h" 
#include "lexer.h" 

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
    // printf("%c\n", buf_getchar_rollback(&buffer));

    char *alphanum = lexer_getalphanum(&buffer);
    printf("Get alphanum : %s\n", alphanum);
    buf_print(&buffer);

    buf_forward(&buffer, 1);
    printf("Forward 1\n");
    buf_print(&buffer);

    char *alphanum_rb = lexer_getalphanum_rollback(&buffer);
    printf("Get alphanum rollback : %s\n", alphanum_rb);
    buf_print(&buffer);

    printf("%s\n", lexer_getop(&buffer));
    buf_print(&buffer);

    long *number = lexer_getnumber(&buffer);
    if (number != NULL) {
        printf("Number: %ld\n", *number);
        free(number);
    } else {
        printf("No number found\n");
    }
    buf_print(&buffer);
    
    // Ferme le fichier pour éviter les erreurs
    fclose(file);
    free(alphanum);
    free(alphanum_rb);
    printf("THE END, file closed and memory freed \n");
}