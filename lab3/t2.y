%{
    #include<stdio.h>
    int yyerror(char *s);
    int yylex();
%}

%token NUMBER 
%token END
%token ADD SUB

%%

statement: exp END {printf("%d\n",$1);}

 exp: NUMBER         {$$ = $1; }
    | exp ADD NUMBER {$$ = $1 + $3; }
    | exp SUB NUMBER {$$ = $1 - $3; }
    ;

%%
int main()
{
    printf("Enter expression:\n");
    yyparse();
    return 0;
}

int yyerror(char *s){
    fprintf(stderr, "error: %s\n", s);
    return 1;
}
