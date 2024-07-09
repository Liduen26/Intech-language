#include <stdlib.h>
#include <ctype.h> // Pour isalnum
#include <string.h> // Strlen
#include <errno.h>
#include "lexer.h"
#include "ressources/buffer.h"

char* lexer_getalphanum(buffer_t *buffer) {
    buf_skipblank(buffer);
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

bool is_operator(const char *op) {
    const char *operators[] = {"+", "-", ">=", ">", "<", "<=", "==", "!=", "*", "/", "&", "|", "!", "++"};
    size_t num_operators = sizeof(operators) / sizeof(operators[0]);

    for (size_t i = 0; i < num_operators; i++) {
        if (strcmp(op, operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

char *lexer_getop(buffer_t *buffer) {
    char temp_op[3] = {0};
    bool was_locked = buffer->islocked;

    if (!was_locked) {
        buf_lock(buffer);
    }

    while (!buf_eof_strict(buffer)) {
        temp_op[0] = buf_getchar(buffer);

        if (is_operator(temp_op)) {
            temp_op[1] = buf_getchar(buffer);

            if (is_operator(temp_op)) {
                if (!was_locked) {
                    buf_unlock(buffer);
                }
                return strdup(temp_op);
            } else {
                buf_rollback(buffer, 1);
                temp_op[1] = '\0';

                if (!was_locked) {
                    buf_unlock(buffer);
                }
                return strdup(temp_op);
            }
            
        } else {
            buf_rollback(buffer, 1);
            if (!was_locked) {
                buf_unlock(buffer);
            }
            return NULL;
        }


        // if (is_operator(temp_op)) {
        //     if (!was_locked) {
        //         buf_unlock(buffer);
        //     }
        //     return strdup(temp_op);
        // }
    }

    if (!was_locked) {
        buf_unlock(buffer);
    }

    return NULL;
}


long *lexer_getnumber(buffer_t *buffer) {
    buf_skipblank(buffer);
    buf_lock(buffer);
    size_t length = 0;
    char c = buf_getchar(buffer);

    if (c == '-') {
        length++;
        c = buf_getchar(buffer);
    }

    while (isdigit((unsigned char)c)) {
        length++;
        c = buf_getchar(buffer);
    }

    if (length > 0) {
        char *numberStr = (char *)malloc(length + 1);
        if (!numberStr) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        buf_rollback(buffer, length + 1);

        for (size_t i = 0; i < length; i++) {
            numberStr[i] = buf_getchar(buffer);
        }
        numberStr[length] = '\0';

        char *endptr;
        long number = strtol(numberStr, &endptr, 10);

        free(numberStr);

        long *result = (long *)malloc(sizeof(long));
        if (!result) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        *result = number;

        buf_unlock(buffer);
        return result;
    } else {
        buf_rollback(buffer, 1);
        buf_unlock(buffer);
        return NULL;
    }
}