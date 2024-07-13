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

sym_table_t *sym_list_add (sym_table_t **list_head, ast_t *node){
    crash_if_exist(*list_head, node);

    sym_table_t *new_node = sym_list_new_node(node);

    if (new_node != NULL) {
        if (*list_head == NULL || "\0") {
            *list_head = new_node;
        } else {
            sym_table_t *current = *list_head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
    return new_node;

}

void print_table(sym_table_t *node_list) {

    if (node_list == NULL)
    {
        exit(1);
    }
    
    printf("| %d ", node_list->node->type);
    printf("| %d |", node_list->next);

    if (node_list->next != NULL) {
        printf(" -> ");
        print_table(node_list->next);
    } else {
        printf("\n");
    }
}

var_type_e *check_already_exist(sym_table_t *list_head, ast_t *node) {
    sym_table_t *current = list_head;
    if (node == NULL) {
        exit(1);
    }

    while (current->next == NULL) {
        switch (current->node->type)
        {
        case AST_FUNCTION:
            if (current->node->function.name == node->function.name) {
                return &current->node->function.return_type;
            }
            break;

        case AST_VARIABLE:
            if (current->node->var.name == node->var.name) {
                return &current->node->var.type;
            }
            break;

        default:
            continue;
            break;
        }
    }

    return NULL;
}

void crash_if_exist(sym_table_t *list_head, ast_t *node) {
    sym_table_t *current = list_head;
    if (node == NULL) {
        exit(1);
    }

    while (current->next == NULL) {
        if (current->node->type != node->type) {
            continue;
        }

        if (current->node->function.name == node->function.name) {
            printf("Function %s already exist !", node->function.name);
            exit(1);
        }
    }
}