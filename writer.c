/*
récup l'ast head que renvoie le parser (function main)
gros switch case sur le type de l'ast (ast_node_type_e)
Case function : 
    printf("function %s (%... ) : %s", function.name, function.param, function.return_type)
case declr_var: 
    printf("let %s : %s", ...)

*/

#include <stdio.h>
#include "ast.h"
#include "parser.h"
#include "writer.h"

void write_ast_to_file(ast_list_t *ast_list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur opening the file");
        return;
    }

    ast_list_t *current = ast_list;
    while (current != NULL) {
        switch (current->node->type) {
            case AST_FUNCTION:
                write_function(file, current->node);
                break;
            case AST_DECLARATION:
                write_declaration(file, current->node);
                break;
            case AST_ASSIGNMENT:
                write_assignment(file, current->node);
                break;
            case AST_RETURN:
                write_return(file, current->node);
                break;
            case AST_CONDITION:
                write_if(file, current->node);
                break;
            case AST_LOOP:
                write_while(file, current->node);
                break;
            // case AST_EXPRESSION:
            //     write_expression(file, current->node);
            //     break;
            default:
                fprintf(stderr, "Unknown AST node type\n");
                break;
        }
        current = current->next;
    }

    fclose(file);
}

void write_function(FILE *file, ast_t *ast) {
   
}

void write_declaration(FILE *file, ast_t *ast) {
    
}

void write_assignment(FILE *file, ast_t *ast) {

}

void write_return(FILE *file, ast_t *ast) {

}

void write_if(FILE *file, ast_t *ast) {

}

void write_while(FILE *file, ast_t *ast) {

}

void write_expression(FILE *file, ast_t *ast) {

}

// Helper functions to convert enums to strings
const char* var_type_to_str(var_type_e type) {
    switch (type) {
        case INT: return "int";
        case VOID: return "void";
        default: return "ya un probleme";
    }
}

const char* op_enum_to_str(ast_binary_e op) {
    switch (op) {
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case DIVIDE: return "/";
        case SUP: return ">";
        case INF: return "<";
        case SUP_OR_EQUAL: return ">=";
        case INF_OR_EQUAL: return "<=";
        case NOT_EQUAL: return "!=";
        default: return "unknown";
    }
}
