%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.tab.h"
#include <stdbool.h>
int yylex(void);

extern int yylineno;
extern FILE* yyin;
extern FILE* yyout;
extern int yylex();
extern int yyparse();

void yyerror(char *str);


struct ast *newAst(int nodetype, struct ast *l, struct ast *r);
struct ast *newNum(int integer);
struct ast *newFlow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el);
char* eval(struct ast *a);

static int tempVarCount = 0;
static int labelCount = 0;

char* generateLC3Code(struct ast *a);
char* createTempVar();
char* createLabel();

struct ast{
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct numval{
    int nodetype;			
    int number;
};

struct flow{
    int nodetype;			
    struct ast *cond;		
    struct ast *tl;		   
    struct ast *el;		   
};

int Flag = true;
int Type_func;
int left_number; 
int stepwhile; 
%}

%union{
    struct ast *a;
    int number;
}
%type <a> expr command  condition


%token PLUS MINUS MUL DIV LESS UMINUS MORE EQUALS
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA
%token IF ELSE WHILE
%token <number> NUMBER




%%
commands:
| commands command { eval($2); }
;

command: IF LPAREN condition RPAREN LBRACE expr RBRACE { $$ = newFlow('I', $3, $6, NULL);  }
| WHILE LPAREN condition RPAREN LBRACE expr RBRACE { $$ = newFlow('W', $3, $6, NULL);  }
| expr { $$ = newAst('a', $1, NULL); }
;

condition: expr LESS expr { $$ = newAst('<', $1, $3); }
| expr MORE expr { $$ = newAst('>', $1, $3); }
| expr EQUALS expr { $$ = newAst('=', $1, $3); }
| condition SEMICOLON expr {$$ = newAst('w', $1, $3);}
;

expr:
    NUMBER                  { $$ = newNum($1);  }
    | expr PLUS expr        { $$ = newAst('+', $1, $3); }
    | expr MINUS expr       { $$ = newAst('-', $1, $3);  }
    | expr MUL expr    { $$ = newAst('*', $1, $3);  }
    | expr DIV expr      { $$ = newAst('/', $1, $3);  }
    | LPAREN expr RPAREN    { $$ = $2; }
    | MINUS expr UMINUS { $$ = newAst('M', $2, NULL);  }
    ;


%%

int main(void){
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");
    yyparse();
    
    fflush(yyout);
    fclose(yyin);
    fclose(yyout);
    return 0;
}



void yyerror(char *str){
    fprintf(yyout , "error: %s at line %d\n", str, yylineno);
    exit(1);
}

struct ast *newAst(int nodetype, struct ast *l, struct ast *r){
    struct ast *a = malloc(sizeof(struct ast));

    if (!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct ast *newNum(int i){
    struct numval *a = malloc(sizeof(struct numval));

    if (!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = i;
    return (struct ast *)a;
}

struct ast *newFlow(int nodetype, struct ast *cond, struct ast *tl, struct ast *el){
    struct flow *a = malloc(sizeof(struct flow));

    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (struct ast *)a;
}

int morelessequals(int num1, int num2){
    switch(Type_func){
        case '<':
            if( num1 < num2){
                return 't';
            } else {
                return 'f';
            }
        case '>':
            if( num1 > num2){
                return 't';
            } else {
                return 'f';
            }
        case '=':
            if( num1 == num2){
                return 't';
            } else {
                return 'f';
            }
    }
    
}

char* generateMultiplication(char* resultVar, char* leftVar, char* rightVar) {
    char* code = malloc(1024); // Allocate space for the code
    char* loopLabel = createLabel();
    char* endLabel = createLabel();

    // Initialize resultVar to 0
    sprintf(code, "AND %s, %s, #0\n", resultVar, resultVar);

    // Check if rightVar is zero, if so, skip the loop
    sprintf(code + strlen(code), "BRz %s\n", endLabel);

    // Start of the loop
    sprintf(code + strlen(code), "%s:\n", loopLabel);
    sprintf(code + strlen(code), "ADD %s, %s, %s\n", resultVar, resultVar, leftVar); // resultVar += leftVar
    sprintf(code + strlen(code), "ADD %s, %s, #-1\n", rightVar, rightVar); // rightVar -= 1
    sprintf(code + strlen(code), "BRp %s\n", loopLabel); // Repeat if rightVar > 0

    // End of the loop
    sprintf(code + strlen(code), "%s:\n", endLabel);

    return code;
}

char* generateDivision(char* resultVar, char* leftVar, char* rightVar) {
    char* code = malloc(1024); 
    char* loopLabel = createLabel();
    char* endLabel = createLabel();
    sprintf(code, "AND %s, %s, #0\n", resultVar, resultVar);
    sprintf(code + strlen(code), "BRz %s\n", endLabel);
    sprintf(code + strlen(code), "%s:\n", loopLabel);
    sprintf(code + strlen(code), "NOT %s, %s\nADD %s, %s, #1\n", rightVar, rightVar, rightVar, rightVar); // Negate rightVar for subtraction
    sprintf(code + strlen(code), "ADD %s, %s, %s\n", leftVar, leftVar, rightVar); // leftVar -= rightVar
    sprintf(code + strlen(code), "ADD %s, %s, #1\n", resultVar, resultVar); // Increment resultVar
    sprintf(code + strlen(code), "BRn %s\n", loopLabel); // Repeat if leftVar >= 0

    // End of the loop
    sprintf(code + strlen(code), "%s:\n", endLabel);

    return code;
}

char* eval(struct ast *a) {
    char* code = malloc(1024); // Allocate space for the assembly code string
    switch(a->nodetype) {
        case 'K':  // Handling a number
            sprintf(code, "LD %s, #%d\n", createTempVar(), ((struct numval *)a)->number);
            break;
        case '+':  // Handling addition
            char *left = eval(a->l);
            char *right = eval(a->r);
            sprintf(code, "%s%sADD %s, %s, %s\n", left, right, createTempVar(), left, right);
            free(left);
            free(right);или целиро
            break;
        
        case '-':  // Handling subtraction
            char *leftSub = eval(a->l);
            char *rightSub = eval(a->r);
            sprintf(code, "%s%sNOT %s, %s\nADD %s, %s, #1\nADD %s, %s, %s\n", rightSub, rightSub, rightSub, rightSub, rightSub, rightSub, createTempVar(), leftSub, rightSub);
            free(leftSub);
            free(rightSub);
            break;

        case '*':  // Handling multiplication
            char *leftMul = eval(a->l);
            char *rightMul = eval(a->r);
            sprintf(code, "%s%s%s", leftMul, rightMul, generateMultiplication(createTempVar(), leftMul, rightMul));
            free(leftMul);
            free(rightMul);
            break;

        case '/':  // Handling division
            char *leftDiv = eval(a->l);
            char *rightDiv = eval(a->r);
            sprintf(code, "%s%s%s", leftDiv, rightDiv, generateDivision(createTempVar(), leftDiv, rightDiv));
            free(leftDiv);
            free(rightDiv);
            break;

        case 'I':  // Handling 'if' condition
            char *condCode = eval(((struct flow *)a)->cond);
            char *thenCode = eval(((struct flow *)a)->tl);
            char *label = createLabel();
            sprintf(code, "%sBRnzp %s\n%s%s:\n", condCode, label, thenCode, label);
            free(condCode);
            free(thenCode);
            break;

        // Handling 'while' loop
        case 'W':
            char *startLabel = createLabel();
            char *condCodeLoop = eval(((struct flow *)a)->cond);
            char *bodyCode = eval(((struct flow *)a)->tl);
            char *endLabel = createLabel();
            sprintf(code, "%s:\n%sBRnzp %s\n%sBRnzp %s\n%s:\n", startLabel, condCodeLoop, endLabel, bodyCode, startLabel, endLabel);
            free(condCodeLoop);
            free(bodyCode);
            break;
        default:
            sprintf(code, "Unknown nodetype %c\n", a->nodetype);
    }

    return code;
}

char* createTempVar() {
    char* tempVar = malloc(10);
    sprintf(tempVar, "TEMP%d", tempVarCount++);
    return tempVar;
}

char* createLabel() {
    char* label = malloc(10);
    sprintf(label, "LABEL%d", labelCount++);
    return label;
}
