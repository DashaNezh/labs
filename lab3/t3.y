%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%union {
    int number;
}

%token <number> NUMBER
%token EOL

%left '+' '-'
%left '*' '/'

%%

statement: exp EOL {printf("\n");}

exp: term
    | exp '+' term { printf("+ "); }
    | exp '-' term { printf("- "); }

term: factor
    | term '*' factor { printf("* "); }
    | term '/' factor { printf("/ "); }

factor: NUMBER { printf("%d", $1); }
      | '(' exp ')' {}

%%

int main(void) {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
