/*
Compiladores - Etapa 1 2021/1 - Juliane da Rocha Alves
*/

%{

#include "hash.h"
#include "ast.h"
#include "y.tab.h"

int lineNumber = 1;
int running = 1;

%}

%x COMMENT

%%

data    {return KW_DATA;}
char    {return KW_CHAR;}
int     {return KW_INT;}
float   {return KW_FLOAT;}
if      {return KW_IF;}
else    {return KW_ELSE;}
until   {return KW_UNTIL;}
comefrom    {return KW_COMEFROM;}
read    {return KW_READ;}
print   {return KW_PRINT;}
return  {return KW_RETURN;}

[-,;:(){}+*/<>|&~=\[\]] {return yytext[0];}

"<="      {return OPERATOR_LE;}
">="      {return OPERATOR_GE;}
"=="      {return OPERATOR_EQ;}
"!="      {return OPERATOR_DIF;}
".."      {return OPERATOR_RANGE;}

[0-9]+    {yylval.symbol = insertElement(LIT_INTEGER, yytext); return LIT_INTEGER;}
'.'   {yylval.symbol = insertElement(LIT_CHAR, yytext); return LIT_CHAR;}
\"[^"]*\"  {yylval.symbol = insertElement(LIT_STRING, yytext); return LIT_STRING;}

[a-zA-Z]([a-zA-Z0-9 ]*[a-zA-Z0-9]+)* {yylval.symbol = insertElement(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}

"##".*
"#/"    {BEGIN(COMMENT);}

[ \t]   {}

[\n]    {++lineNumber;}

.       {return TOKEN_ERROR;}

<COMMENT>"/#"  {BEGIN(INITIAL);}
<COMMENT>\n  {++lineNumber;}
<COMMENT>.

%%

int isRunning(void){
    return running;
}

int getLineNumber(void){
    return lineNumber;
}

void initMe(void){
    initializeHash();
}

int yywrap()
{
    running = 0;
    return 1;
}
