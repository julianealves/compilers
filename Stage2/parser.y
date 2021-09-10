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

data: KW_DATA '{' var_decl '}'
	;

var_decl: var var_decl
	|
	;

var: variable_type ':' TK_IDENTIFIER '=' literals ';' | vector
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

func: variable_type ':' TK_IDENTIFIER '(' lparam ')' '{' lcmd '}' func
	|
	;

lparam: fparam lparam
	|
	;

fparam: variable_type ':' TK_IDENTIFIER
	| variable_type ':' TK_IDENTIFIER ',' fparam
	;

lcmd: cmd ';' lcmd
    |
    ;

cmd: attribution
	| KW_COMEFROM ':' TK_IDENTIFIER
	| cmdprint
	| cmdretunr
	| cmd_block
	| TK_IDENTIFIER         //Label
	| KW_UNTIL '(' expr ')' cmd
	| KW_IF '(' expr ')' cmd cmd_else
	|
	;

cmd_else: KW_ELSE cmd
    |
    ;

cmd_block: '{' lcmd '}'
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
	|
	;

cmdprint: KW_PRINT lprint
	;

lprint: expr
    | LIT_STRING
    | expr ',' lprint
    | LIT_STRING ',' lprint
    |
    ;

cmdretunr: KW_RETURN expr
	;

%%

int yyerror(char *err){
	fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
	exit(3);
}