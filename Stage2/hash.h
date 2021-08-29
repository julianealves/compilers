/*
Compiladores - Etapa 1 2021/1 - Juliane da Rocha Alves
*/

#ifndef HASH_HEADER
#define HASH_HEADER

#include <stdio.h>
#define HASH_SIZE 997

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void initializeHash(void);
int calculateAddress(char *text);
HASH_NODE *findElement (char *text);
HASH_NODE *insertElement (int type, char *text);
void printHashTable(void);

#endif