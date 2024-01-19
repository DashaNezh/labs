%{
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%option noyywrap

%%

[0-9]+      { yylval.number = atoi(yytext); return NUMBER; }
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"<"         { return LESS; }
">"         { return MORE; }
"=="        { return EQUALS; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
","         { return COMMA; }
";"         { return SEMICOLON; }
[ \t\n]+    ;

%%

#undef yywrap
int yywrap() {
    return 1;
}
