#ifndef Sym_TABLE_H
#define Sym_TABLE_H

#include "ast.h"

typedef struct sym_table_t {
    ast_t *node;
    struct sym_table *next;
} sym_table_t;

ast_list_t *sym_list_new_node (ast_t *elem);
ast_list_t *sym_list_add (ast_list_t **prev_node_list, ast_t *elem);

void printList(ast_list_t *node_list);


#endif // Sym_TABLE_H