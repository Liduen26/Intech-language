/*
récup l'ast head que renvoie le parser (function main)
gros switch case sur le type de l'ast (ast_node_type_e)
Case function : 
    printf("function %s (%... ) : %s", function.name, function.param, function.return_type)
case declr_var: 
    printf("let %s : %s", ...)

*/
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "parser.h"
#include "writer.h"
#include "ressources/utils.h"

int indent = 0;

void write_ast_to_file(FILE *file, ast_list_t *ast_list) {
    print_trace("Debut de l'ecriture");
    ast_list_t *current = ast_list;
    while (current != NULL) {
        if (current->node->type == AST_FUNCTION) {
            write_function(file, current->node);
        } else {
            print_error("First node isn't a function");
            exit(1);
        }
        
        current = current->next;
    }

    fclose(file);
}

void write_function(FILE *file, ast_t *node) {
    printf("function %s(", node->function.name);
    ast_list_t *param = node->function.params;
    while (param != NULL) {
        printf("%s: %s", param->node->var.name, type_to_str(param->node->var.type));
        if (param->next != NULL) {
            printf(", ");
        }
        param = param->next;
    }
    printf("): %s ", type_to_str(node->function.return_type));
    // printList(node->function.stmts);
    write_statements(file, node->function.stmts);
}

// void write_corps(FILE *file, ast_list_t *ast_list) {
//     ast_list_t *current = ast_list;
//     printf("%d", current->node->type);
//     while (current != NULL) {
//         if (current->node->type != AST_COMPOUND_STATEMENT) {
//             print_error("Not a compound statement in the corps");
//             exit(1);
//         }
//         // print_warn("corps warn %d", current->node->compound_stmt.stmts->node->type);

//         write_statements(file, current->node);
        
//         current = current->next;
//     }
// }

// Ecris une instruction
void write_statements(FILE *file, ast_list_t *head_stmts) {
    // Ajoute un d'indentation à chaque fois qu'on rentre dans un statement
    indent++;
    printf("{\n");
    ast_list_t *current = head_stmts;
    while (current != NULL) {
        if (current->node == NULL) {
            print_error("Node null");
        }

        // Met autant d'indentation que le compteur
        for (size_t i = 0; i < indent; i++) {
            printf("\t");
        }
        // print_warn("type : %d", current->node->type); 

        write_node(file, current->node);
        printf(";\n");
        current = current->next;
    }
    printf("}\n");
    indent--;
}

// Sert à print n'importe quel node
void write_node(FILE *file, ast_t *node) {   
    // print_warn("type : %d", node->type); 
    switch (node->type) {
        case AST_DECLARATION:
            write_variable_declaration(file, node);
            break;
        case AST_ASSIGNMENT:
            write_assignment(file, node);
            break;
        case AST_INTEGER:
            write_integer(file, node);
            break;
        case AST_BINARY:
            write_binary(file, node);
            break;
        case AST_VARIABLE:
            write_variable(file, node);
            break;
        case AST_FNCALL:
            write_fncall(file, node);
            break;
        case AST_CONDITION:
            write_condition(file, node);
            break;
        default:
            fprintf(stderr, "Unsupported AST node type\n");
            break;
    }
}

void write_variable_declaration(FILE *file, ast_t *ast) {
    printf("%s: %s", ast->declaration.name, type_to_str(ast->declaration.type));
}

void write_assignment(FILE *file, ast_t *ast) {
    write_node(file, ast->assignment.lvalue);
    printf(" = ");
    write_node(file, ast->assignment.rvalue);
}

void write_integer(FILE *file, ast_t *ast) {
    printf("%d", ast->integer);
}

void write_binary(FILE *file, ast_t *ast) {
    write_node(file, ast->binary.left);
    printf(" %s ", op_enum_to_str(ast->binary.op));
    write_node(file, ast->binary.right);
    // print_warn("type right : %d", ast->assignment.rvalue->type);
}

void write_variable(FILE *file, ast_t *ast) {
    printf("%s", ast->var.name);
}

void write_fncall(FILE *file, ast_t *ast) {
    printf("%s(%s)" , ast->call.name, ast->call.args);
}

void write_condition(FILE *file, ast_t *ast) {
    printf("if (");
    write_node(file, ast->branch.condition);
    printf(") ");

    write_statements(file, ast->branch.valid->compound_stmt.stmts);

    // if (ast->branch.invalid != NULL) {
    //     for (size_t i = 0; i > indent; i++) {
    //         printf("\t");
    //     }
    //     printf("else ");
    //     write_statements(file, ast->branch.invalid->compound_stmt.stmts);
    // }
}


// Helper functions to convert enums to strings
const char* type_to_str(var_type_e type) {
    switch (type) {
        case INT: return "number";
        case VOID: return "void";
        default: return "any";
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
