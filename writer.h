#ifndef WRITER_H
#define WRITER_H

#include "ast.h"

// Déclarations des fonctions
void write_ast_to_ts(ast_list_t *ast, const char *filename);
void write_variable_declaration(FILE *file, ast_t *node);
void write_function_declaration(FILE *file, ast_t *node);
void write_statements(FILE *file, ast_list_t *stmts);
void write_statement(FILE *file, ast_t *node);
void write_assignment(FILE *file, ast_t *node);
void write_expression(FILE *file, ast_t *node);
void write_return(FILE *file, ast_t *node);
void write_condition(FILE *file, ast_t *node);
void write_loop(FILE *file, ast_t *node);
const char* get_type_str(var_type_e type);
const char* get_binary_operator_str(ast_binary_e op);

#endif
