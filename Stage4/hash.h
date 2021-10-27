/*
Compiladores - Etapa 4 2021/1 - Juliane da Rocha Alves
*/

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#define HASH_SIZE 997

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LIT_INT 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_FLOAT 4
#define SYMBOL_FUNCTION 5
#define SYMBOL_VECTOR 6
#define SYMBOL_VARIABLE 7
#define SYMBOL_LIT_STRING 8
#define SYMBOL_PARAMETER 9

#define DATA_TYPE_INT 10
#define DATA_TYPE_CHAR 11
#define DATA_TYPE_FLOAT 12

typedef struct hash_node
{
    int type;
    int data_type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void initializeHash(void);
int calculateAddress(char *text);
HASH_NODE *findElement (char *text);
HASH_NODE *insertElement (int type, char *text);
void printHashTable(void);

#endif