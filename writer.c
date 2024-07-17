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
    print_trace("Fin de l'ecriture");
}

void write_function(FILE *file, ast_t *node) {
    fprintf(file, "function %s(", node->function.name);
    print_trace("ecris fonction %s", node->function.name);

    ast_list_t *param = node->function.params;
    while (param != NULL) {
        fprintf(file, "%s: %s", param->node->declaration.name, type_to_str(param->node->declaration.type));
        print_trace("ecris param %s", param->node->declaration.name);
        if (param->next != NULL) {
            fprintf(file, ", ");
        }
        param = param->next;
    }
    fprintf(file, "): %s ", type_to_str(node->function.return_type));
    // printList(node->function.stmts);
    write_statements(file, node->function.stmts);
}

void write_statements(FILE *file, ast_list_t *head_stmts) {
    // Ajoute un d'indentation à chaque fois qu'on rentre dans un statement
    fprintf(file, "\n");
    for (size_t i = 0; i < indent; i++) {
        fprintf(file, "\t");
    }
    fprintf(file, "{\n");
    indent++;
    ast_list_t *current = head_stmts;
    while (current != NULL) {
        if (current->node == NULL) {
            print_error("Node null");
        }

        // Met autant d'indentation que le compteur
        for (size_t i = 0; i < indent; i++) {
            fprintf(file, "\t");
        }
        // print_warn("type : %d", current->node->type); 

        bool semi_colon = write_node(file, current->node);
        if (semi_colon) {
            fprintf(file, ";\n");
        }
        
        current = current->next;
    }
    indent--;
    for (size_t i = 0; i < indent; i++) {
        fprintf(file, "\t");
    }

    fprintf(file, "}\n");
}

// Sert à print n'importe quel node
bool write_node(FILE *file, ast_t *node) {   
    // print_warn("type : %d", node->type); 
    bool semi_colon = true;
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
            semi_colon = false;
            break;
        case AST_RETURN: 
            write_return(file, node);
            break;
        default:
            print_error("Unsupported AST node type");
            break;
    }
    return semi_colon;
}

void write_variable_declaration(FILE *file, ast_t *ast) {
    fprintf(file, "let %s: %s", ast->declaration.name, type_to_str(ast->declaration.type));
}

void write_assignment(FILE *file, ast_t *ast) {
    write_node(file, ast->assignment.lvalue);
    fprintf(file, " = ");
    write_node(file, ast->assignment.rvalue);
}

void write_integer(FILE *file, ast_t *ast) {
    fprintf(file, "%d", ast->integer);
}

void write_binary(FILE *file, ast_t *ast) {
    write_node(file, ast->binary.left);
    fprintf(file, " %s ", op_enum_to_str(ast->binary.op));
    write_node(file, ast->binary.right);
    // print_warn("type right : %d", ast->assignment.rvalue->type);
}

void write_variable(FILE *file, ast_t *ast) {
    fprintf(file, "%s", ast->var.name);
}

void write_fncall(FILE *file, ast_t *ast) {
    fprintf(file, "%s(" , ast->call.name);
    ast_list_t *last = ast->call.args;
    while (last != NULL) {
        if (last->node->type != AST_VARIABLE) {
            exit(1);
        }

        fprintf(file, "%s", last->node->var.name);
        
        if (last->next != NULL) {
            fprintf(file, ", ");
        }
        
        last = last->next;
    }
    fprintf(file, ")");
}

void write_condition(FILE *file, ast_t *ast) {
    fprintf(file, "if (");
    write_node(file, ast->branch.condition);
    fprintf(file, ") ");

    write_statements(file, ast->branch.valid->compound_stmt.stmts);

    if (ast->branch.invalid != NULL) {
        for (size_t i = 0; i < indent; i++) {
            fprintf(file, "\t");
        }
        fprintf(file, "else ");
        write_statements(file, ast->branch.invalid->compound_stmt.stmts);
    }
}


void write_return(FILE *file, ast_t *ast) {
    fprintf(file, "return ");
    write_node(file, ast->ret.expr);
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
