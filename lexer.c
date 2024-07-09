#include <stdlib.h>
#include <ctype.h> // Pour isalnum
#include <string.h> // Strlen
#include "lexer.h"
#include "ressources/buffer.h"

char* lexer_getalphanum(buffer_t *buffer) {
    size_t length = 0;
    bool locked_in = false;

    if (!buffer->islocked) {
        buf_lock(buffer);
        locked_in = true;
    }

    char charRead = buf_getchar(buffer);
    while (isalnum(charRead) || buf_eof_strict(buffer)) {
        charRead = buf_getchar(buffer);
        length++; 
    }

    if (length > 0) {
        char* result = (char*)malloc(length + 1); // +1 pour le caractère null

        buf_rollback(buffer, length + 1);

        for (size_t i = 0; i < length; i++) {
            result[i] = buf_getchar(buffer);
        }
        result[length] = '\0'; // char null de la fin

        if (locked_in)
            buf_unlock(buffer);
        
        return result;
    } else {
        // Remettre le curseur à la position initiale
        buf_rollback(buffer, 1);
        if (locked_in)
            buf_unlock(buffer);
        
        return NULL;
    }
}  

char* lexer_getalphanum_rollback(buffer_t *buffer) {
    buf_lock(buffer);
    char *string = lexer_getalphanum(buffer);
    if (string != NULL) {
        buf_rollback(buffer, strlen(string));
    }
    
    buf_unlock(buffer);
    return string;
}

char *lexer_getop(buffer_t *buffer) {
    
}