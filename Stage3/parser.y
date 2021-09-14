/*
Compiladores - Etapa 3 2021/1 - Juliane da Rocha Alves
*/

%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "hash.h"
  #include "ast.h"

  int yyerror(char *message);

  int yylex();

  extern int getLineNumber();

  AST *root;

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING

%token TOKEN_ERROR

%union{
    HASH_NODE *symbol;
    AST *ast;
}

%type<ast> expr
%type<ast> lexpr
%type<ast> cmd
%type<ast> lcmd
%type<ast> attribution
%type<ast> cmdprint
%type<ast> cmdreturn
%type<ast> cmd_else
%type<ast> cmd_block
%type<ast> lprint
%type<ast> variable_type
%type<ast> literals
%type<ast> var_decl
%type<ast> var
%type<ast> program
%type<ast> decl
%type<ast> data
%type<ast> vector
%type<ast> vector_range
%type<ast> vector_decl
%type<ast> lliteral
%type<ast> func
%type<ast> lparam
%type<ast> fparam


%left '~' '|' '&'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_DIF
%left '+' '-'
%left '*' '/'

%start program

%%

program: decl               {root = $$; astPrint(root, 0);}
	;

decl: data func             {$$ = astCreate(AST_DECL,0,$1,$2,0,0);}
	;

data: KW_DATA '{' var_decl '}'      {$$ = astCreate(AST_KW_DATA,0,$3,0,0,0);}
	;

var_decl: var var_decl      {$$ = astCreate(AST_VAR_DECL,0,$1,$2,0,0);}
	|                       {$$ = 0;}
	;

var: variable_type ':' TK_IDENTIFIER '=' literals ';'       {$$ = astCreate(AST_VAR,$3,$1,$5,0,0);}
    | vector                                                {$$ = $1;}
	;

variable_type: KW_CHAR          {$$ = astCreate(AST_KW_CHAR,0,0,0,0,0);}
    | KW_INT                    {$$ = astCreate(AST_KW_INT,0,0,0,0,0);}
    | KW_FLOAT                  {$$ = astCreate(AST_KW_FLOAT,0,0,0,0,0);}
	;

vector: variable_type '[' vector_range ']' ':' TK_IDENTIFIER vector_decl ';'      {$$ = astCreate(AST_VECTOR,$6,$1,$3,$7,0);}
	;

vector_range: LIT_INTEGER OPERATOR_RANGE LIT_INTEGER    {$$ = astCreate(AST_RANGE,$1,astCreate(AST_RANGE,$3,0,0,0,0),0,0,0);}
    ;

vector_decl: '=' literals lliteral      {$$ = astCreate(AST_VECTOR_DECL,0,$2,$3,0,0);}
	|                                   {$$ = 0;}
	;

literals: LIT_CHAR              {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | LIT_INTEGER               {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

lliteral: literals lliteral     {$$ = astCreate(AST_LIST_LITERALS,0,$1,$2,0,0);}
	|                           {$$ = 0;}
	;

func: variable_type ':' TK_IDENTIFIER '(' lparam ')' '{' lcmd '}' func      {$$ = astCreate(AST_FUNC,$3,$1,$5,$8,$10);}
	|                                                                       {$$ = 0;}
	;

lparam: fparam lparam       {$$ = astCreate(AST_FUNC_PARAM,0,$1,$2,0,0);}
	|                       {$$ = 0;}
	;

fparam: variable_type ':' TK_IDENTIFIER             {$$ = astCreate(AST_FUNC_SINGLE_PARAM,$3,$1,0,0,0);}
	| variable_type ':' TK_IDENTIFIER ',' fparam    {$$ = astCreate(AST_FUNC_LIST_PARAM,$3,$1,$5,0,0);}
	;

lcmd: cmd ';' lcmd                          {$$ = astCreate(AST_LIST_CMD,0,$1,$3,0,0);}
    |                                       {$$ = 0;}
    ;

cmd: attribution                            {$$ = $1;}
	| KW_COMEFROM ':' TK_IDENTIFIER         {$$ = astCreate(AST_KW_COMEFROM,$3,0,0,0,0);}
	| cmdprint                              {$$ = $1;}
	| cmdreturn                             {$$ = $1;}
	| cmd_block                             {$$ = $1;}
	| TK_IDENTIFIER                         {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}   //Label
	| KW_UNTIL '(' expr ')' cmd             {$$ = astCreate(AST_KW_UNTIL,0,$3,$5,0,0);}
	| KW_IF '(' expr ')' cmd cmd_else       {$$ = astCreate(AST_KW_IF,0,$3,$5,$6,0);}
	|                                       {$$ = 0;}
	;

cmd_else: KW_ELSE cmd                       {$$ = astCreate(AST_KW_ELSE,0,$2,0,0,0);}
    |                                       {$$ = 0;}
    ;

cmd_block: '{' lcmd '}'                     {$$ = astCreate(AST_BLOCK,0,$2,0,0,0);}
	;

attribution: TK_IDENTIFIER '=' expr         {$$ = astCreate(AST_ATTRIBUTION,$1,$3,0,0,0);}
	| TK_IDENTIFIER '[' expr ']' '=' expr   {$$ = astCreate(AST_VECT_ATTRIBUTION,$1,$3,$6,0,0);}
	;

expr: LIT_INTEGER                       {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR                          {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
	| TK_IDENTIFIER                     {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
	| expr '+' expr                     {$$ = astCreate(AST_ADD,0,$1,$3,0,0);}
	| expr '-' expr                     {$$ = astCreate(AST_SUB,0,$1,$3,0,0);}
	| expr '*' expr                     {$$ = astCreate(AST_MULT,0,$1,$3,0,0);}
	| expr '/' expr                     {$$ = astCreate(AST_DIV,0,$1,$3,0,0);}
	| '(' expr ')'                      {$$ = astCreate(AST_PAREN,0,$2,0,0,0);}
	| '[' expr ']'                      {$$ = astCreate(AST_BRACKETS,0,$2,0,0,0);}
	| '{' expr '}'                      {$$ = astCreate(AST_CURLY_BRACKET,0,$2,0,0,0);}
	| expr OPERATOR_LE expr             {$$ = astCreate(AST_LE,0,$1,$3,0,0);}
	| expr OPERATOR_GE expr             {$$ = astCreate(AST_GE,0,$1,$3,0,0);}
	| expr OPERATOR_EQ expr             {$$ = astCreate(AST_EQ,0,$1,$3,0,0);}
	| expr OPERATOR_DIF expr            {$$ = astCreate(AST_DIF,0,$1,$3,0,0);}
	| expr '<' expr                     {$$ = astCreate(AST_LESS,0,$1,$3,0,0);}
	| expr '>' expr                     {$$ = astCreate(AST_BIGGER,0,$1,$3,0,0);}
	| expr '|' expr                     {$$ = astCreate(AST_OR,0,$1,$3,0,0);}
	| '~' expr                          {$$ = astCreate(AST_NOT,0,$2,0,0,0);}
	| expr '&' expr                     {$$ = astCreate(AST_AND,0,$1,$3,0,0);}
	| TK_IDENTIFIER '(' lexpr ')' 		{$$ = astCreate(AST_CALL_FUNC,$1,$3,0,0,0);} //Call function
	| KW_READ                           {$$ = astCreate(AST_KW_READ,0,0,0,0,0);}
	| TK_IDENTIFIER '[' expr ']'        {$$ = astCreate(AST_VECTOR_ACCESS,$1,$3,0,0,0);}  //Vector
	;

lexpr: expr                             {$$ = $1;}
	| expr ',' lexpr                    {$$ = astCreate(AST_LIST_EXPR,0,$1,$3,0,0);}
	|                                   {$$ = 0;}
	;

cmdprint: KW_PRINT lprint               {$$ = astCreate(AST_KW_PRINT,0,$2,0,0,0);}
	;

lprint: expr                            {$$ = $1;}
    | LIT_STRING                        {$$ = astCreate(AST_SYMBOL,$1,0,0,0,0);}
    | expr ',' lprint                   {$$ = astCreate(AST_LIST_PRINT,0,$1,$3,0,0);}
    | LIT_STRING ',' lprint             {$$ = astCreate(AST_LIST_STR_PRINT,$1,$3,0,0,0);}
    |                                   {$$ = 0;}
    ;

cmdreturn: KW_RETURN expr               {$$ = astCreate(AST_KW_RETURN,0,$2,0,0,0);}
	;

%%

int yyerror(char *err){
	fprintf(stderr, "Syntax error at line %d.\n", getLineNumber());
	exit(3);
}

AST* return_ast(){
  return root;
}