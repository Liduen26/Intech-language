/*
Y doit
récup l'ast head que renvoie le parser (function main)
gros switch case sur le type de l'ast (ast_node_type_e)
Case function : 
    printf("function %s (%... ) : %s", fucntion.name, funciton.param, function.return_type)
case declr_var: 
    printf("let %s : %s", ...)



*/
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "writer.h"

// Déclarations des fonctions avant leur utilisation
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

// Fonction pour écrire une déclaration de variable en TypeScript
void write_variable_declaration(FILE *file, ast_t *node) {
    fprintf(file, "let %s: %s;\n", node->var.name, get_type_str(node->var.type));
}

// Fonction pour écrire une déclaration de fonction en TypeScript
void write_function_declaration(FILE *file, ast_t *node) {
    fprintf(file, "function %s(", node->function.name);
    ast_list_t *param = node->function.params;
    while (param != NULL) {
        fprintf(file, "%s: %s", param->node->var.name, get_type_str(param->node->var.type));
        if (param->next != NULL) {
            fprintf(file, ", ");
        }
        param = param->next;
    }
    fprintf(file, "): %s {\n", get_type_str(node->function.return_type));
    write_statements(file, node->function.stmts);
    fprintf(file, "}\n");
}

// Fonction pour écrire une liste d'instructions en TypeScript
void write_statements(FILE *file, ast_list_t *stmts) {
    while (stmts != NULL) {
        write_statement(file, stmts->node);
        stmts = stmts->next;
    }
}

// Fonction pour écrire une instruction en TypeScript
void write_statement(FILE *file, ast_t *node) {
    switch (node->type) {
        case AST_VARIABLE:
            write_variable_declaration(file, node);
            break;
        case AST_FUNCTION:
            write_function_declaration(file, node);
            break;
        case AST_ASSIGNMENT:
            write_assignment(file, node);
            break;
        case AST_RETURN:
            write_return(file, node);
            break;
        case AST_CONDITION:
            write_condition(file, node);
            break;
        case AST_LOOP:
            write_loop(file, node);
            break;
        default:
            fprintf(stderr, "Unsupported AST node type\n");
            break;
    }
}

// Fonction pour écrire une assignation en TypeScript
void write_assignment(FILE *file, ast_t *node) {
    fprintf(file, "%s = ", node->assignment.lvalue->var.name);
    write_expression(file, node->assignment.rvalue);
    fprintf(file, ";\n");
}

// Fonction pour écrire une expression en TypeScript
void write_expression(FILE *file, ast_t *node) {
    switch (node->type) {
        case AST_INTEGER:
            fprintf(file, "%ld", node->integer);
            break;
        case AST_VARIABLE:
            fprintf(file, "%s", node->var.name);
            break;
        case AST_BINARY:
            write_expression(file, node->binary.left);
            fprintf(file, " %s ", get_binary_operator_str(node->binary.op));
            write_expression(file, node->binary.right);
            break;
        case AST_FNCALL:
            fprintf(file, "%s(", node->call.name);
            ast_list_t *arg = node->call.args;
            while (arg != NULL) {
                write_expression(file, arg->node);
                if (arg->next != NULL) {
                    fprintf(file, ", ");
                }
                arg = arg->next;
            }
            fprintf(file, ")");
            break;
        default:
            fprintf(stderr, "Unsupported AST node type\n");
            break;
    }
}

// Fonction pour écrire un return en TypeScript
void write_return(FILE *file, ast_t *node) {
    fprintf(file, "return ");
    write_expression(file, node->ret.expr);
    fprintf(file, ";\n");
}

// Fonction pour écrire une condition (if) en TypeScript
void write_condition(FILE *file, ast_t *node) {
    fprintf(file, "if (");
    write_expression(file, node->branch.condition);
    fprintf(file, ") {\n");
    write_statements(file, node->branch.valid->compound_stmt.stmts);
    fprintf(file, "} else {\n");
    write_statements(file, node->branch.invalid->compound_stmt.stmts);
    fprintf(file, "}\n");
}

// Fonction pour écrire une boucle (while) en TypeScript
void write_loop(FILE *file, ast_t *node) {
    fprintf(file, "while (");
    write_expression(file, node->loop.condition);
    fprintf(file, ") {\n");
    write_statements(file, node->loop.stmt->compound_stmt.stmts);
    fprintf(file, "}\n");
}

// Fonction pour obtenir la représentation en chaîne de caractères d'un type
const char* get_type_str(var_type_e type) {
    switch (type) {
        case INT: return "number";
        case VOID: return "void";
        default: return "any";
    }
}

// Fonction pour obtenir la représentation en chaîne de caractères d'un opérateur binaire
const char* get_binary_operator_str(ast_binary_e op) {
    switch (op) {
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case DIVIDE: return "/";
        case SUP: return ">";
        case SUP_OR_EQUAL: return ">=";
        case INF: return "<";
        case INF_OR_EQUAL: return "<=";
        case NOT_EQUAL: return "!=";
        default: return "unknown";
    }
}

// Fonction principale pour écrire l'AST dans un fichier TypeScript
void write_ast_to_ts(ast_list_t *ast, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    while (ast != NULL) {
        write_statement(file, ast->node);
        ast = ast->next;
    }

    fclose(file);
    printf("Conversion de l'AST en TypeScript terminée.\n");
}
