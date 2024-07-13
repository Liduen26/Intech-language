#ifndef PARSER_H
#define PARSER_H

#include "ressources/buffer.h"
#include "ast.h"
#include "sym_table.h"

typedef enum {
    INSTRUCTION,
    ARGUMENT
} context_e;

ast_list_t* parser(buffer_t *buffer);
 
ast_t* analyse_function(sym_table_t *global_sym_table, buffer_t *buffer);

ast_list_t* analyse_param(buffer_t *buffer, ast_list_t *list_param);
var_type_e analyse_return(buffer_t *buffer);
ast_list_t* analyse_corps(buffer_t *buffer, ast_list_t *list_instructions);


#endif // PARSER_H