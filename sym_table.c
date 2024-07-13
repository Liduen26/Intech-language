#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "sym_table.h"


sym_table_t *sym_list_new_node (ast_t *elem){
    sym_table_t *node_list = malloc(sizeof(sym_table_t));
    if (node_list != NULL)
    {
        node_list->node = elem;
        node_list->next = NULL;
    }
    return node_list;
}

sym_table_t *sym_list_add (sym_table_t **prev_node_list, ast_t *elem){
    sym_table_t *new_node = sym_list_new_node(elem);

    if (new_node != NULL) {
        if (*prev_node_list == NULL) {
            *prev_node_list = new_node;
        } else {
            sym_table_t *current = *prev_node_list;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
    return new_node;

}

void printList(sym_table_t *node_list) {

    if (node_list == NULL)
    {
        exit(1);
    }
    
    printf("| %d ", node_list->node->type);
    printf("| %d |", node_list->next);

    if (node_list->next != NULL) {
        printf(" -> ");
        printList(node_list->next);
    }
}