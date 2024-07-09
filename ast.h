#ifndef AST_H
#define AST_H

#include "ressources/buffer.h"

typedef enum {
    AST_VOID,
    AST_INTEGER,
    AST_BINARY,
    AST_UNARY,
    AST_FUNCTION,
    AST_FNCALL,
    AST_VARIABLE,
    AST_CONDITION,
    AST_LOOP,
    AST_DECLARATION,
    AST_ASSIGNMENT,
    AST_COMPOUND_STATEMENT,
    AST_RETURN
} ast_node_type_e;

typedef struct ast_t {
    ast_node_type_e type;
    union {
        long integer;
        struct {
            char *name;
            var_type_e type;
        } var;
        struct {
            ast_binary_e op;
            struct ast_t *left;
            struct ast_t *right;
        } binary;
        struct {
            char op;
            struct ast_t *operand;
        } unary;
        struct {
            char *name;
            struct ast_list_t *args;
        } call;
        struct {
            char *name;
            var_type_e return_type;
            struct ast_list_t *params;
            struct ast_list_t *stmts;
        } function;
        struct {
            struct ast_list_t *stmts;
        } compound_stmt;
        struct {
            struct ast_t *lvalue;
            struct ast_t *rvalue;
        } assignment;
        struct {
            struct ast_t *lvalue;
            struct ast_t *rvalue;
        } declaration;
        struct {
            struct ast_t *condition;
            struct ast_t *valid;
            struct ast_t *invalid;
        } branch;
        struct {
            struct ast_t *condition;
            struct ast_t *stmt;
        } loop;
        struct {
            struct ast_t *expr;
        } ret;
    };
} ast_t;

#endif // AST_H