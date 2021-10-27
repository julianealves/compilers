/*
Compiladores - Etapa 5 2021/1 - Juliane da Rocha Alves
*/

#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_MOVE 2
#define TAC_ADD 3
#define TAC_MUL 4
#define TAC_SUB 5
#define TAC_DIV 6
#define TAC_LABEL 7
#define TAC_BEGINFUN 8
#define TAC_ENDFUN 9
#define TAC_IFZ 10
#define TAC_JUMP 11
#define TAC_CALL 12
#define TAC_ARG 13
#define TAC_RET 14
#define TAC_PRINT 15
#define TAC_READ 16
#define TAC_COPY 17
#define TAC_IFZE 18
#define TAC_LE 19
#define TAC_GE 20
#define TAC_EQ 21
#define TAC_DIF 22
#define TAC_LESS 23
#define TAC_BIGGER 24
#define TAC_OR 25
#define TAC_AND 26
#define TAC_NOT 27
#define TAC_COMEFROM 28
#define TAC_COPY_VEC 29
#define TAC_LIST_EXPR 30
#define TAC_LIST_STR_PRINT 31
#define TAC_LIST_PRINT 32
#define TAC_VECTOR_ACCESS 33
#define TAC_FUNC 34
#define TAC_LIST_CMD 35
#define TAC_VECTOR_DECL 36

typedef struct tac_node{
    int type;
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    struct tac_node *prev;
    struct tac_node *next;
}TAC;

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);

//CODE GENERATION
TAC* generateCode(AST* node);
TAC* makeIfThen(TAC* code0, TAC* code1, TAC* code2);
TAC* binOperation(int tac_type, TAC* code0, TAC* code1);
TAC* makeUntil(TAC* code0, TAC* code1);
TAC* makeFunction(TAC* symbol, TAC* code1, TAC* code2);

#endif