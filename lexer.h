#ifndef LEXER_H
#define LEXER_H

#include "ressources/buffer.h"

char* lexer_getalphanum(buffer_t *buffer);
char* lexer_getalphanum_rollback(buffer_t *buffer);


#endif // LEXER_H