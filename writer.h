#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include "ast.h"

// Fonction principale pour écrire l'AST dans un fichier
void write_ast_to_file(FILE *file, ast_list_t *ast_list);

// Fonctions pour écrire différents types de nœuds AST
void write_function(FILE *file, ast_t *node);

// void write_corps(FILE *file, ast_list_t *ast_list);
void write_statements(FILE *file, ast_list_t *head_stmts);
void write_node(FILE *file, ast_t *node);
void write_variable_declaration(FILE *file, ast_t *ast);
void write_assignment(FILE *file, ast_t *ast);
void write_integer(FILE *file, ast_t *ast);
void write_binary(FILE *file, ast_t *ast);
void write_variable(FILE *file, ast_t *ast);
void write_fncall(FILE *file, ast_t *ast);
void write_condition(FILE *file, ast_t *ast);



// Fonctions auxiliaires pour convertir les enums en chaînes de caractères
// const char* var_type_to_str(var_type_e type);
const char* op_enum_to_str(ast_binary_e op);
const char* type_to_str(var_type_e type);

#endif // WRITER_H

