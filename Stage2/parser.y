/*
Compiladores - Etapa 2 2021/1 - Juliane da Rocha Alves
*/

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "hash.h"

  int yyerror(char *message);

  int yylex();

  extern int getLineNumber();

%}

%token KW_CHAR
%token KW_INT
%token KW_FLOAT
%token KW_DATA

%token KW_IF
%token KW_ELSE
%token KW_UNTIL
%token KW_COMEFROM
%token KW_READ
%token KW_PRINT
%token KW_RETURN

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_DIF
%token OPERATOR_RANGE

%token TK_IDENTIFIER

%token LIT_INTEGER
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '~' '|' '&'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%start program

%%

program: decl
	;

decl: data func
	;

data: KW_DATA body
	;

body: '{' lcmd '}'

lcmd: cmd lcmd
	|
	;

cmd: variable_decl | vector
	;

variable_decl: variable_type ':' TK_IDENTIFIER '=' literals ';'
	;

variable_type: KW_CHAR | KW_INT | KW_FLOAT
	;

vector: variable_type '[' LIT_INTEGER OPERATOR_RANGE LIT_INTEGER ']' ':' TK_IDENTIFIER vector_decl ';'
	;

vector_decl: '=' literals lliteral
	|
	;

literals: LIT_CHAR | LIT_INTEGER
	;

lliteral: literals lliteral
	|
	;

func: variable_type ':' TK_IDENTIFIER '(' lparam ')' '{' body_func '}' func
	|
	;

lparam: fparam lparam
	|
	;

fparam: variable_type ':' TK_IDENTIFIER
	| variable_type ':' TK_IDENTIFIER ',' fparam
	;

body_func: attribution ';' body_func
	| expr ';' body_func
	| KW_COMEFROM ':' TK_IDENTIFIER ';' body_func
	| cmdprint ';' body_func
	| cmdretunr ';' body_func
	| cmd_block body_func
	| KW_UNTIL '(' expr ')' cmd_block body_func
	| KW_UNTIL '(' expr ')' simplecmd ';' body_func
	| if_else body_func
	| ';' body_func		//empty command
	|
	;

if_else: KW_IF '(' expr ')' cmd_block
	| KW_IF '(' expr ')' '{' body_func '}' KW_ELSE
        | KW_IF '(' expr ')' simplecmd ';'
        | KW_IF '(' expr ')' simplecmd KW_ELSE
        ;


simplecmd: attribution
	| expr
	| cmdprint
	| cmdretunr
	|
	;

cmd_block: '{' body_func '}' ';'
	;

attribution: TK_IDENTIFIER '=' expr
	| TK_IDENTIFIER '[' expr ']' '=' expr
	;

expr: LIT_INTEGER
	| LIT_CHAR
	| TK_IDENTIFIER
	| expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' expr
	| '(' expr ')'
	| '[' expr ']'
	| '{' expr '}'
	| expr OPERATOR_LE expr
	| expr OPERATOR_GE expr
	| expr OPERATOR_EQ expr
	| expr OPERATOR_DIF expr
	| expr '<' expr
	| expr '>' expr
	| expr '|' expr
	| '~' expr
	| expr '&' expr
	| TK_IDENTIFIER '(' lexpr ')' 		//Call function
	| KW_READ
	| TK_IDENTIFIER '[' expr ']'
	;

lexpr: expr
	| expr ',' lexpr
	| LIT_STRING ',' lexpr
	| LIT_STRING
	|
	;

cmdprint: KW_PRINT lprint
	| KW_PRINT '(' lexpr ')'
	;

lprint: LIT_STRING
	| LIT_STRING ',' lexpr
	;

cmdretunr: KW_RETURN '(' expr ')'
	;

%%

int yyerror(char *err){
	fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
	exit(3);
}