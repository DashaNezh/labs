%{
#include <stdio.h>
#include "y.tab.h"
void Errors();
%}

%%
[0-9]+ { yylval.number = atoi(yytext); return NUMBER; }
[-+*/()] { return yytext[0]; }
\n { return EOL; }
[ \t] { /* ignore whitespace */ }
. { Errors(); }
%%
void Errors(){
printf("chto sluchilos'?");
}
