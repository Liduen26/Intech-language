#include <stdlib.h>
#include <string.h>
#include "ressources/buffer.h"
#include "ressources/utils.h"
#include "lexer.h"

int parser(buffer_t *buffer) {
    printf("parser start\n");
    while (!buf_eof_strict(buffer))
    {
        char *firstWord = lexer_getalphanum(buffer);
        printf("%s\n", firstWord);
        if (strcmp(firstWord, "function") == 0) {
            printf("function !!\n");
        } else {
            printf("pas fonction\n");
            free(firstWord);
            return EXIT_FAILURE;
        }
        

        free(firstWord);
    }
    printf("parser end\n");
}