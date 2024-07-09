#include <stdlib.h>
#include <string.h>
#include "ressources/buffer.h"
#include "ressources/utils.h"
#include "lexer.h"
#include "ast.h"

ast_list_t* parser(buffer_t *buffer, ast_list_t *nodeList) {
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
        return nodeList;
    }
    printf("parser end\n");
}

