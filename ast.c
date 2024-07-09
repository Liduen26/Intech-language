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
