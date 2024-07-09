#include <stdlib.h>
#include <string.h>
#include "ressources/buffer.h"
#include "ressources/utils.h"
#include "lexer.h"
#include "ast.h"

ast_list_t* parser(buffer_t *buffer, ast_list_t *nodeList) {
    printf("parser start\n");
    while (!buf_eof_strict(buffer))
    {
        char *firstWord = lexer_getalphanum(buffer);
        printf("%s\n", firstWord);
        if (strcmp(firstWord, "function") == 0) {
            printf("function !!\n");
        } else {
            printf("pas fonction\n");
            free(firstWord);
            return EXIT_FAILURE;
        }
        
        free(firstWord);
        return nodeList;
    }
    printf("parser end\n");
}

ast_t *ast_new_integer (long val) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_INTEGER; 
        node->integer = val;
    }
    return node;
}

ast_t* ast_new_variable (char *name, var_type_e type) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_VARIABLE; 
        node->var.name = name; 
        node->var.type = type;
    }
    return node;
}

ast_t *ast_new_binary (ast_binary_e op, ast_t *left, ast_t *right) {
    ast_t *my_ast = malloc(sizeof(ast_t));
    if (my_ast != NULL) {
        my_ast->type = AST_BINARY; 
        my_ast->binary.op = op; 
        my_ast->binary.left = left;
        my_ast->binary.right = right;
    }
}

ast_t *ast_new_unary (ast_unary_e op, ast_t *operand) {
    ast_t *my_ast = malloc(sizeof(ast_t));
    if (my_ast != NULL) {
        my_ast->type = AST_UNARY; 
        my_ast->unary.op = op; 
        my_ast->unary.operand = operand;
    }
}

ast_t *ast_new_fncall (char *name, ast_list_t *args) {
    ast_t *my_ast = malloc(sizeof(ast_t));
    if (my_ast != NULL) {
        my_ast->type = AST_FNCALL;
        my_ast->call.name = name;
        my_ast->call.args = args;
    }
}

ast_t *ast_new_function (char *name, var_type_e return_type, ast_list_t *params, ast_list_t *stmts) {
    ast_t *my_ast = malloc(sizeof(ast_t));
    if (my_ast != NULL) {
        my_ast->type = AST_FUNCTION; 
        my_ast->function.name = name;
        my_ast->function.return_type = return_type;
        my_ast->function.params = params;
        my_ast->function.stmts = stmts;
    }
}

ast_t* ast_new_comp_stmt(ast_list_t *stmts) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_COMPOUND_STATEMENT;
        node->compound_stmt.stmts = stmts;
    }
    return node;
}

ast_t* ast_new_assignment(ast_t *lvalue, ast_t *rvalue) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_ASSIGNMENT;
        node->assignment.lvalue = lvalue;
        node->assignment.rvalue = rvalue;
    }
    return node;
}

ast_t* ast_new_declaration(ast_t *lvalue, ast_t *rvalue) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_DECLARATION;
        node->declaration.lvalue = lvalue;
        node->declaration.rvalue = rvalue;
    }
    return node;
}

ast_t* ast_new_condition(ast_t *condition, ast_t *valid, ast_t *invalid) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_CONDITION;
        node->branch.condition = condition;
        node->branch.valid = valid;
        node->branch.invalid = invalid;
    }
    return node;
}

ast_t* ast_new_loop(ast_t *condition, ast_t *stmt) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_LOOP;
        node->loop.condition = condition;
        node->loop.stmt = stmt;
    }
    return node;
}

ast_t* ast_new_return(ast_t *expr) {
    ast_t *node = malloc(sizeof(ast_t));
    if (node != NULL) {
        node->type = AST_RETURN;
        node->ret.expr = expr;
    }
    return node;
}

ast_list_t *ast_list_new_node (ast_t *elem){
    ast_list_t *node_list = malloc(sizeof(ast_list_t));
    if (node_list != NULL)
    {
        node_list->node = elem;
        node_list->next = NULL;
    }
    return node_list;
}

ast_list_t *ast_list_add (ast_list_t **prev_node_list, ast_t *elem){

    ast_list_new_node(elem);
    /**
    recup le return du noeud d'avant

    l'adresse du noeud qu'on viens de crée (*node_list)

    avoir accès au node_list du noeud d'avant

    remplacer next = NULL par next = *node_list
     */


}