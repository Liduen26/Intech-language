#ifndef WRITER_H
#define WRITER_H

#include <stdio.h>
#include "ast.h"

// Fonction principale pour écrire l'AST dans un fichier
void write_ast_to_file(ast_list_t *ast_list, FILE *file);

// Fonctions pour écrire différents types de nœuds AST
void write_function(FILE *file, ast_t *ast);
void write_declaration(FILE *file, ast_t *ast);
void write_assignment(FILE *file, ast_t *ast);
void write_return(FILE *file, ast_t *ast);
void write_if(FILE *file, ast_t *ast);
void write_while(FILE *file, ast_t *ast);
void write_expression(FILE *file, ast_t *ast);

// Fonctions auxiliaires pour convertir les enums en chaînes de caractères
const char* var_type_to_str(var_type_e type);
const char* op_enum_to_str(ast_binary_e op);

#endif // WRITER_H

