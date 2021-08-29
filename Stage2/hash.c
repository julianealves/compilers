/*
Compiladores - Etapa 1 2021/1 - Juliane da Rocha Alves
*/

#include <stdlib.h>
#include <string.h>
#include "hash.h"

HASH_NODE *HashTable[HASH_SIZE];

void initializeHash(void){
    int i;
    for (i=0; i<HASH_SIZE; i++){
        HashTable[i] = 0;
    }
}

int calculateAddress(char *text){
    int address = 1;
    int i;

    for (i=0; i<strlen(text); i++){
        address = (address*text[i]) % HASH_SIZE + 1;
    }
    return address-1;
}

HASH_NODE *findElement(char *text){
    HASH_NODE *node;
    int address;

    address = calculateAddress(text);

    for (node=HashTable[address]; node; node = node->next){
        if (strcmp(node->text, text) == 0){
            return node;
        }
    }
    return 0;
}

HASH_NODE *insertElement(int type, char *text){
    HASH_NODE *newelement;
    int address;

    address = calculateAddress(text);

    if ((newelement = findElement(text)) != 0){
        return newelement;
    }

    newelement = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newelement->type = type;
    newelement->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strcpy(newelement->text, text);
    newelement->next = HashTable[address];
    HashTable[address] = newelement;

    return newelement;
}

void printHashTable(void){
    int i;
    HASH_NODE *node;

    for (i=0; i<HASH_SIZE; i++){
        for (node=HashTable[i]; node; node=node->next){
            printf("HashTable[%d] has %s\n", i, node->text);
        }
    }
}