/*
Compiladores - Etapa 2 2021/1 - Juliane da Rocha Alves
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lex.yy.h"
#include "y.tab.h"

extern char *yytext;
extern FILE *yyin;

int yylex();
int isRunning(void);
int getLineNumber(void);
void initMe(void);
extern int yyparse();


int main(int argc, char **argv){
    int tok;

    initMe();

    if (argc < 2){
        fprintf(stderr, "Call ./etapa1.out file_name\n");
        exit(1);
    }

    if (0 == (yyin = fopen(argv[1], "r"))){
        printf("Invalid file\n");
        exit(2);
    }

    yyparse();
    printHashTable();
    fprintf(stderr, "Compilation Successful!\n");
    exit(0);
}