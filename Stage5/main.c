/*
Compiladores - Etapa 3 2021/1 - Juliane da Rocha Alves
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "ast.h"
#include "lex.yy.h"
#include "y.tab.h"

extern char *yytext;
extern FILE *yyin;

int yylex();
int isRunning(void);
int getLineNumber(void);
void initMe(void);
extern int yyparse();
extern AST* return_ast();
extern int check_semantic();


int main(int argc, char **argv){
    int tok;
    FILE *output;

    initMe();

    if (argc < 3){
        fprintf(stderr, "Call ./etapa1.out input_file_name.txt output_file_name.txt\n");
        exit(1);
    }

    if (0 == (yyin = fopen(argv[1], "r"))){
        printf("Invalid input file!\n");
        exit(2);
    }

    if (0 == (output = fopen(argv[2], "w+"))){
        fprintf(stderr, "Invalid output file!\n");
        exit(2);
    }

    yyparse();
    printHashTable();
    fprintf(stderr, "*** Finished compilation! ***\n");

    fprintf(stderr, "Decompiling...\n");
    astDecompile(return_ast(), output);
    fprintf(stderr, "Done!\n");
    fclose(output);

    check_semantic();

    exit(0);
}