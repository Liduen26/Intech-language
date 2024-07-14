#ifndef LEXER_H
#define LEXER_H

#include "ressources/buffer.h"

char* lexer_getalphanum(buffer_t *buffer);
char* lexer_getalphanum_rollback(buffer_t *buffer);

char *lexer_getop(buffer_t *buffer);
char* lexer_getop_rollback(buffer_t *buffer);

long *lexer_getnumber(buffer_t *buffer);
char* lexer_getnumber_rollback(buffer_t *buffer);

void lexer_test(buffer_t *buffer);

char* lexer_getemoji(buffer_t *buffer);

#endif // LEXER_H