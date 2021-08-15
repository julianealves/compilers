/*
Compiladores - Etapa 1 2021/1 - Juliane da Rocha Alves
*/

#define COMMA 44
#define SEMI_COLON 59
#define COLON 58
#define PARENTESES1 40
#define PARENTESES2 41
#define BRACKET1 91
#define BRACKET2 93
#define BRACE1 123
#define BRACE2 125
#define PLUS 43
#define DASH 45
#define ASTERISK 42
#define SLASH 47
#define LESS 60
#define GREATER 62
#define BAR 124
#define AMPERSAND 38
#define TILDE 126
#define EQUAL 61

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lex.yy.h"
#include "tokens.h"

extern char *yytext;
extern FILE *yyin;

int yylex();
int isRunning(void);
int getLineNumber(void);
void initMe(void);


int main(int argc, char **argv){
    int tok;

    initMe();

    if (argc < 2){
        fprintf(stderr, "Call ./etapa1.out file_name\n");
        exit(1);
    }

    if (0 == (yyin = fopen(argv[1], "r"))){
        printf("Invalid file\n");
        exit(1);
    }

    while (isRunning()){
        tok = yylex();
        if (isRunning() == 0){
            break;
        }
        switch(tok) {
            case KW_CHAR:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_INT:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_FLOAT:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_DATA:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_IF:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_ELSE:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_UNTIL:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_COMEFROM:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_PRINT:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case KW_RETURN:
                printf("KW %s in line %d\n", yytext, getLineNumber());
                break;
            case OPERATOR_LE:
                printf("Operator %s in line %d\n", yytext, getLineNumber());
                break;
            case OPERATOR_GE:
                printf("Operator %s in line %d\n", yytext, getLineNumber());
                break;
            case OPERATOR_EQ:
                printf("Operator %s in line %d\n", yytext, getLineNumber());
                break;
            case OPERATOR_DIF:
                printf("Operator %s in line %d\n", yytext, getLineNumber());
                break;
            case OPERATOR_RANGE:
                printf("Operator %s in line %d\n", yytext, getLineNumber());
                break;
            case TK_IDENTIFIER:
                printf("Indentifier %s in line %d\n", yytext, getLineNumber());
                break;
            case LIT_INTEGER:
                printf("Lit integer %s in line %d\n", yytext, getLineNumber());
                break;
            case LIT_CHAR:
                printf("Lit char %s in line %d\n", yytext, getLineNumber());
                break;
            case LIT_STRING:
                printf("Lit string %s in line %d\n", yytext, getLineNumber());
                break;
            case COMMA:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case SEMI_COLON:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case COLON:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case PARENTESES1:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case PARENTESES2:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case BRACKET1:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case BRACKET2:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case BRACE1:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case BRACE2:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case PLUS:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case DASH:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case ASTERISK:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case SLASH:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case LESS:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case GREATER:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case BAR:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case AMPERSAND:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case TILDE:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            case EQUAL:
                printf("Character %s in line %d\n", yytext, getLineNumber());
                break;
            default:
                printf("Unknown: %s in line %d\n", yytext, getLineNumber());
                break;
        }
    }

    printHashTable();
}