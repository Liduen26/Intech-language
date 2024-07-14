#ifndef PARSER_H
#define PARSER_H

#include "ressources/buffer.h"
#include "ast.h"
#include "sym_table.h"

typedef enum {
    INSTRUCTION,
    ARGUMENT,
    CONDITION
} context_e;

ast_list_t* parser(buffer_t *buffer);

ast_t* analyse_function(sym_table_t *global_sym_table, buffer_t *buffer);


ast_list_t* analyse_param(buffer_t *buffer, ast_list_t *list_param, sym_table_t *local_table);

var_type_e analyse_return(buffer_t *buffer);

ast_list_t* analyse_corps(buffer_t *buffer, ast_list_t *list_instructions, sym_table_t *global_sym_table, sym_table_t *local_table);
ast_list_t* analyse_instruction(buffer_t *buffer, ast_list_t *list_instructions, sym_table_t *global_sym_table, sym_table_t *local_table);
ast_t *analyse_condition(buffer_t *buffer, sym_table_t *global_sym_table, sym_table_t *local_table);

ast_t *parse_expression(buffer_t *buffer, context_e context, sym_table_t *global_sym_table, sym_table_t *local_table);

ast_list_t* analyse_args(buffer_t *buffer, ast_list_t *list_args, sym_table_t *global_sym_table, sym_table_t *local_table);


void check_valid_name(buffer_t *buffer);
bool is_function(buffer_t *buffer);
bool is_conditional_operator(const char *op);

var_type_e type_str_to_enum(char* type_str);
ast_binary_e op_str_to_enum(char* op);

#endif // PARSER_H