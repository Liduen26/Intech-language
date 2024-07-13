#ifndef Sym_TABLE_H
#define Sym_TABLE_H

#include "ast.h"

typedef struct sym_table {
    ast_t *node;
    struct sym_table *next;
} sym_table;


#endif // Sym_TABLE_H