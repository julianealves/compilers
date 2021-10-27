/*
Compiladores - Etapa 3 2021/1 - Juliane da Rocha Alves
*/

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3, int line_number){
    AST *new_node;

    new_node = (AST*) calloc(1, sizeof (AST));

    new_node->type = type;
    new_node->symbol = symbol;
    new_node->line_number = line_number;
    new_node->label = 0;
    new_node->label_declarated = 0;
    new_node->sons[0] = s0;
    new_node->sons[1] = s1;
    new_node->sons[2] = s2;
    new_node->sons[3] = s3;

    return new_node;
}

void astPrint(AST *node, int level){

    int i;

    if (node == 0){
        return;
    }

    for (i=0; i<level; i++){
        fprintf(stderr, "   ");
    }

    fprintf(stderr, "AST Level %d: ", level);
    switch (node->type) {
        case AST_SYMBOL:
            fprintf(stderr, "AST_SYMBOL");
            break;
        case AST_ADD:
            fprintf(stderr, "AST_ADD");
            break;
        case AST_SUB:
            fprintf(stderr, "AST_SUB");
            break;
        case AST_MULT:
            fprintf(stderr, "AST_MULT");
            break;
        case AST_DIV:
            fprintf(stderr, "AST_DIV");
            break;
        case AST_PAREN:
            fprintf(stderr, "AST_PAREN");
            break;
        case AST_BRACKETS:
            fprintf(stderr, "AST_BRACKETS");
            break;
        case AST_CURLY_BRACKET:
            fprintf(stderr, "AST_CURLY_BRACKET");
            break;
        case AST_LE:
            fprintf(stderr, "AST_LE");
            break;
        case AST_GE:
            fprintf(stderr, "AST_GE");
            break;
        case AST_EQ:
            fprintf(stderr, "AST_EQ");
            break;
        case AST_DIF:
            fprintf(stderr, "AST_DIF");
            break;
        case AST_LESS:
            fprintf(stderr, "AST_LESS");
            break;
        case AST_BIGGER:
            fprintf(stderr, "AST_BIGGER");
            break;
        case AST_OR:
            fprintf(stderr, "AST_OR");
            break;
        case AST_NOT:
            fprintf(stderr, "AST_NOT");
            break;
        case AST_AND:
            fprintf(stderr, "AST_AND");
            break;
        case AST_CALL_FUNC:
            fprintf(stderr, "AST_CALL_FUNC");
            break;
        case AST_KW_READ:
            fprintf(stderr, "AST_KW_READ");
            break;
        case AST_VECTOR_ACCESS:
            fprintf(stderr, "AST_VECTOR");
            break;
        case AST_LIST_EXPR:
            fprintf(stderr, "AST_LIST_EXPR");
            break;
        case AST_ATTRIBUTION:
            fprintf(stderr, "AST_ATTRIBUTION");
            break;
        case AST_VECT_ATTRIBUTION:
            fprintf(stderr, "AST_VECT_ATTRIBUTION");
            break;
        case AST_KW_COMEFROM:
            fprintf(stderr, "AST_KW_COMEFROM");
            break;
        case AST_KW_PRINT:
            fprintf(stderr, "AST_KW_PRINT");
            break;
        case AST_LIST_PRINT:
            fprintf(stderr, "AST_LIST_PRINT");
            break;
        case AST_LIST_STR_PRINT:
            fprintf(stderr, "AST_LIST_STR_PRINT");
            break;
        case AST_KW_RETURN:
            fprintf(stderr, "AST_KW_RETURN");
            break;
        case AST_KW_UNTIL:
            fprintf(stderr, "AST_KW_UNTIL");
            break;
        case AST_KW_IF:
            fprintf(stderr, "AST_KW_IF");
            break;
        case AST_KW_ELSE:
            fprintf(stderr, "AST_KW_ELSE");
            break;
        case AST_BLOCK:
            fprintf(stderr, "AST_BLOCK");
            break;
        case AST_KW_CHAR:
            fprintf(stderr, "AST_KW_CHAR");
            break;
        case AST_KW_INT:
            fprintf(stderr, "AST_KW_INT");
            break;
        case AST_KW_FLOAT:
            fprintf(stderr, "AST_KW_FLOAT");
            break;
        case AST_VAR:
            fprintf(stderr, "AST_VAR");
            break;
        case AST_VAR_DECL:
            fprintf(stderr, "AST_VAR_DECL");
            break;
        case AST_LIST_LITERALS:
            fprintf(stderr, "AST_LIST_LITERALS");
            break;
        case AST_VECTOR:
            fprintf(stderr, "AST_VECTOR");
            break;
        case AST_RANGE:
            fprintf(stderr, "AST_RANGE");
            break;
        case AST_VECTOR_DECL:
            fprintf(stderr, "AST_VECTOR_DECL");
            break;
        case AST_FUNC_SINGLE_PARAM:
            fprintf(stderr, "AST_FUNC_SINGLE_PARAM");
            break;
        case AST_FUNC_LIST_PARAM:
            fprintf(stderr, "AST_FUNC_LIST_PARAM");
            break;
        case AST_FUNC_PARAM:
            fprintf(stderr, "AST_FUNC_PARAM");
            break;
        case AST_LIST_CMD:
            fprintf(stderr, "AST_LIST_CMD");
            break;
        case AST_FUNC:
            fprintf(stderr, "AST_FUNC");
            break;
        case AST_KW_DATA:
            fprintf(stderr, "AST_KW_DATA");
            break;
        case AST_DECL:
            fprintf(stderr, "AST_DECL");
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN");
            break;
    }

    if (node->symbol != 0){
        fprintf(stderr, ",%s", node->symbol->text);
    }
    else{
        fprintf(stderr, ",0");
    }

    fprintf(stderr, "\n");

    for (i=0; i<MAX_SONS; i++){
        astPrint(node->sons[i], level+1);
    }
}

void astDecompile(AST *node, FILE *file){
    if (node == 0){
        return;
    }

    switch (node->type) {
        case AST_SYMBOL:
            fprintf(file, "%s", node->symbol->text);
            break;
        case AST_ADD:
            astDecompile(node->sons[0], file);
            fprintf(file, " + ");
            astDecompile(node->sons[1], file);
            break;
        case AST_SUB:
            astDecompile(node->sons[0], file);
            fprintf(file, " - ");
            astDecompile(node->sons[1], file);
            break;
        case AST_MULT:
            astDecompile(node->sons[0], file);
            fprintf(file, " * ");
            astDecompile(node->sons[1], file);
            break;
        case AST_DIV:
            astDecompile(node->sons[0], file);
            fprintf(file, " / ");
            astDecompile(node->sons[1], file);
            break;
        case AST_PAREN:
            fprintf(file, "(");
            astDecompile(node->sons[0], file);
            fprintf(file, ")");
            break;
        case AST_BRACKETS:
            fprintf(file, "[");
            astDecompile(node->sons[0], file);
            fprintf(file, "]");
            break;
        case AST_CURLY_BRACKET:
            fprintf(file, "{");
            astDecompile(node->sons[0], file);
            fprintf(file, "}");
            break;
        case AST_LE:
            astDecompile(node->sons[0], file);
            fprintf(file, " <= ");
            astDecompile(node->sons[1], file);
            break;
        case AST_GE:
            astDecompile(node->sons[0], file);
            fprintf(file, " >= ");
            astDecompile(node->sons[1], file);
            break;
        case AST_EQ:
            astDecompile(node->sons[0], file);
            fprintf(file, " == ");
            astDecompile(node->sons[1], file);
            break;
        case AST_DIF:
            astDecompile(node->sons[0], file);
            fprintf(file, " != ");
            astDecompile(node->sons[1], file);
            break;
        case AST_LESS:
            astDecompile(node->sons[0], file);
            fprintf(file, " < ");
            astDecompile(node->sons[1], file);
            break;
        case AST_BIGGER:
            astDecompile(node->sons[0], file);
            fprintf(file, " > ");
            astDecompile(node->sons[1], file);
            break;
        case AST_OR:
            astDecompile(node->sons[0], file);
            fprintf(file, " | ");
            astDecompile(node->sons[1], file);
            break;
        case AST_NOT:
            fprintf(file, "~");
            astDecompile(node->sons[0], file);
            break;
        case AST_AND:
            astDecompile(node->sons[0], file);
            fprintf(file, " & ");
            astDecompile(node->sons[1], file);
            break;
        case AST_CALL_FUNC:
            fprintf(file, "%s", node->symbol->text);
            fprintf(file, "(");
            astDecompile(node->sons[0], file);
            fprintf(file, ")");
            break;
        case AST_KW_READ:
            fprintf(file, "read");
            break;
        case AST_VECTOR_ACCESS:
            fprintf(file, "%s", node->symbol->text);
            fprintf(file, "[");
            astDecompile(node->sons[0], file);
            fprintf(file, "]");
            break;
        case AST_LIST_EXPR:
            astDecompile(node->sons[0], file);
            fprintf(file, ",");
            astDecompile(node->sons[1], file);
            break;
        case AST_ATTRIBUTION:
            fprintf(file, "%s", node->symbol->text);
            fprintf(file, "=");
            astDecompile(node->sons[0], file);
            break;
        case AST_VECT_ATTRIBUTION:
            fprintf(file, "%s", node->symbol->text);
            fprintf(file, "[");
            astDecompile(node->sons[0], file);
            fprintf(file, "] = ");
            astDecompile(node->sons[1], file);
            break;
        case AST_KW_COMEFROM:
            fprintf(file, "comefrom: %s", node->symbol->text);
            break;
        case AST_KW_PRINT:
            fprintf(file, "print\t");
            astDecompile(node->sons[0], file);
            break;
        case AST_LIST_PRINT:
            astDecompile(node->sons[0], file);
            fprintf(file, ",");
            astDecompile(node->sons[1], file);
            break;
        case AST_LIST_STR_PRINT:
            fprintf(file, "%s,", node->symbol->text);
            astDecompile(node->sons[0], file);
            break;
        case AST_KW_RETURN:
            fprintf(file, "return\t");
            astDecompile(node->sons[0], file);
            break;
        case AST_KW_UNTIL:
            fprintf(file, "until (");
            astDecompile(node->sons[0], file);
            fprintf(file, ")\n");
            astDecompile(node->sons[1], file);
            break;
        case AST_KW_IF:
            fprintf(file, "if (");
            astDecompile(node->sons[0], file);
            fprintf(file, ")\n");
            astDecompile(node->sons[1], file);
            astDecompile(node->sons[2], file);
            break;
        case AST_KW_ELSE:
            fprintf(file, "\nelse\n");
            astDecompile(node->sons[0], file);
            break;
        case AST_BLOCK:
            fprintf(file, "{\n");
            astDecompile(node->sons[0], file);
            fprintf(file, "}");
            break;
        case AST_KW_CHAR:
            fprintf(file, "char");
            break;
        case AST_KW_INT:
            fprintf(file, "int");
            break;
        case AST_KW_FLOAT:
            fprintf(file, "float");
            break;
        case AST_VAR:
            astDecompile(node->sons[0], file);
            fprintf(file, ": %s", node->symbol->text);
            fprintf(file, " = ");
            astDecompile(node->sons[1], file);
            fprintf(file, ";\n");
            break;
        case AST_VAR_DECL:
            astDecompile(node->sons[0], file);
            astDecompile(node->sons[1], file);
            break;
        case AST_LIST_LITERALS:
            astDecompile(node->sons[0], file);
            fprintf(file, " ");
            astDecompile(node->sons[1], file);
            break;
        case AST_VECTOR:
            astDecompile(node->sons[0], file);
            fprintf(file, "[");
            astDecompile(node->sons[1], file);
            fprintf(file, "]:%s", node->symbol->text);
            astDecompile(node->sons[2], file);
            fprintf(file, ";\n");
            break;
        case AST_RANGE:
            if (node->sons[0] != 0){
                fprintf(file, "%s..", node->symbol->text);
            }
            else{
                fprintf(file, "%s", node->symbol->text);
            }
            astDecompile(node->sons[0], file);
            break;
        case AST_VECTOR_DECL:
            fprintf(file, " = ");
            astDecompile(node->sons[0], file);
            fprintf(file, " ");
            astDecompile(node->sons[1], file);
            break;
        case AST_FUNC_SINGLE_PARAM:
            astDecompile(node->sons[0], file);
            fprintf(file, ":");
            fprintf(file, "%s", node->symbol->text);
            break;
        case AST_FUNC_LIST_PARAM:
            astDecompile(node->sons[0], file);
            fprintf(file, ":");
            fprintf(file, "%s,", node->symbol->text);
            astDecompile(node->sons[1], file);
            break;
        case AST_FUNC_PARAM:
            astDecompile(node->sons[0], file);
            astDecompile(node->sons[1], file);
            break;
        case AST_LIST_CMD:
            astDecompile(node->sons[0], file);
            fprintf(file, ";\n");
            astDecompile(node->sons[1], file);
            break;
        case AST_FUNC:
            astDecompile(node->sons[0], file);
            fprintf(file, ":%s (", node->symbol->text);
            astDecompile(node->sons[1], file);
            fprintf(file, ") {\n");
            astDecompile(node->sons[2], file);
            fprintf(file, "}\n");
            astDecompile(node->sons[3], file);
            break;
        case AST_KW_DATA:
            fprintf(file, "data {\n");
            astDecompile(node->sons[0], file);
            fprintf(file, "}\n");
            break;
        case AST_DECL:
            astDecompile(node->sons[0], file);
            astDecompile(node->sons[1], file);
            break;
        default:
            fprintf(stderr, "AST_UNKNOWN");
            break;
    }

}