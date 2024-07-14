#ifndef Sym_TABLE_H
#define Sym_TABLE_H

#include "ast.h"

typedef struct sym_table_t {
    ast_t *node;
    struct sym_table_t *next;
} sym_table_t;

sym_table_t *sym_list_new_node (ast_t *elem);
void sym_list_add (sym_table_t **prev_node_list, ast_t *elem);

void print_table(sym_table_t *node_list);

var_type_e get_type(sym_table_t **list_head, ast_t *node);

void crash_if_exist(sym_table_t **list_head, ast_t *node);


#endif // Sym_TABLE_H