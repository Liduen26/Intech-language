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

void sym_list_add (sym_table_t **list_head, ast_t *node) {
    sym_table_t* new_node = sym_list_new_node(node);
    sym_table_t *last = *list_head;

    // Si la liste est vide, le nouveau noeud devient le premier noeud
    if (*list_head == NULL) {
        *list_head = new_node;
        return;
    } else {
        crash_if_exist(list_head, node);
    }

    // Sinon, on parcourt la liste jusqu'au dernier noeud
    while (last->next != NULL) {
        last = last->next;
    }

    // On change le dernier noeud pour qu'il pointe vers le nouveau noeud
    last->next = new_node;
}

void crash_if_exist(sym_table_t **list_head, ast_t *node) {
    sym_table_t *last = *list_head;
    if (node == NULL) {
        exit(1);
    }

    while (last->next != NULL) {
        // printf("%s\n", current->node->function.name);
        if (last->node->type != node->type) {
            continue;
        }

        if (last->node->function.name == node->function.name) {
            printf("%s already exist !", last->node->function.name);
            exit(1);
        }
    }
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

var_type_e get_type(sym_table_t **list_head, ast_t *node) {
    sym_table_t *current = *list_head;
    if (node == NULL) {
        exit(1);
    }

    while (current->next == NULL) {
        switch (current->node->type)
        {
        case AST_FUNCTION:
            if (current->node->function.name == node->function.name) {
                return current->node->function.return_type;
            }
            break;

        case AST_VARIABLE:
            if (current->node->var.name == node->var.name) {
                return current->node->var.type;
            }
            break;

        default:
            continue;
            break;
        }
    }

    return INVALID_TYPE;
}