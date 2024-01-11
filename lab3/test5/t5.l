%{
#include "y.tab.h"
%}

%%

[0-9]+(\.[0-9]+)? {
yylval.d = atof(yytext);
return NUMBER;
}
[()] {return yytext[0];}
[*] {return MUL;}
[/] {return DIV;}
[+] {return ADD;}
[-] {return SUB;}

[ \t] {
/* пропускаем пробелы и символы табуляции */
}
\n {return yywrap();}
. {
fprintf(stderr, "Unexpected character: %s\n", yytext);
}

%%

int yywrap() {
return 0; // Продолжаем ввод на новой строке
}

