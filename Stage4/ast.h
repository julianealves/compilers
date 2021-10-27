/*
Compiladores - Etapa 3 2021/1 - Juliane da Rocha Alves
*/

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4
#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MULT 4
#define AST_DIV 5
#define AST_PAREN 6
#define AST_BRACKETS 7
#define AST_CURLY_BRACKET 8
#define AST_LE 9
#define AST_GE 10
#define AST_EQ 11
#define AST_DIF 12
#define AST_LESS 13
#define AST_BIGGER 14
#define AST_OR 15
#define AST_NOT 16
#define AST_AND 17
#define AST_CALL_FUNC 18
#define AST_KW_READ 19
#define AST_VECTOR_ACCESS 20
#define AST_LIST_EXPR 21
#define AST_ATTRIBUTION 22
#define AST_VECT_ATTRIBUTION 23
#define AST_KW_COMEFROM 24
#define AST_KW_PRINT 25
#define AST_LIST_PRINT 26
#define AST_LIST_STR_PRINT 27
#define AST_KW_RETURN 28
#define AST_KW_UNTIL 29
#define AST_KW_IF 30
#define AST_KW_ELSE 31
#define AST_BLOCK 32
#define AST_KW_CHAR 33
#define AST_KW_INT 34
#define AST_KW_FLOAT 35
#define AST_VAR 36
#define AST_VAR_DECL 37
#define AST_LIST_LITERALS 38
#define AST_VECTOR 39
#define AST_RANGE 40
#define AST_VECTOR_DECL 41
#define AST_FUNC_SINGLE_PARAM 42
#define AST_FUNC_LIST_PARAM 43
#define AST_FUNC_PARAM 44
#define AST_LIST_CMD 45
#define AST_FUNC 46
#define AST_KW_DATA 47
#define AST_DECL 48

#include "hash.h"


typedef struct ast
{
    int type;
    HASH_NODE *symbol;
    int line_number;
    int label;
    int label_declarated;
    struct ast *sons[MAX_SONS];
} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3, int line_number);
void astPrint(AST *node, int level);
void astDecompile(AST *node, FILE *file);

#endif