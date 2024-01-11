%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
"+" {return ADD; } 
"-" {return SUB; } 
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
"\n" {return END;}
. {printf("Mystery character %c\n", *yytext);}
%%

