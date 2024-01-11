%{
* Включение стандартных библиотек C */
#include <stdio.h>
#include <stdlib.h>

/* Определение структуры узлов для абстрактного синтаксического дерева */
struct ast {
  int nodetype;           /* Тип узла */
  struct ast *l;          /* Указатель на левый дочерний узел */
  struct ast *r;          /* Указатель на правый дочерний узел */
};

/* Определение структуры для узла, содержащего числовое значение */
struct numval {
  int nodetype;           /* Тип узла: 'K' */
  double number;          /* Числовое значение */
};

/* Прототипы функций, используемых в коде */
struct ast *newast(int nodetype, struct ast *l, struct ast *r);  /* Функция создания нового узла AST */
struct ast *newnum(double d);                                    /* Функция создания узла для числового значения */
double eval(struct ast *);                                       /* Функция вычисления результата на основе AST */
void treefree(struct ast *);                                     /* Функция освобождения памяти занятой AST */
%}

%union {
  struct ast *a;          /* Объединение, используемое для возвращения узлов AST */
  double d;               /* Объединение, используемое для возвращения числовых значений */
}

/* Определение типов токенов, используемых в грамматике */
%token <d> NUMBER                 /* Токен для числового значения */
%token ADD SUB MUL DIV            /* Токены для арифметических операций: сложения, вычитания, умножения, деления */
%left ADD SUB                     /* Определение ассоциативности и приоритета операций */
%left MUL DIV

%type <a> expression              /* Определение типа для правил грамматики */
%%
program: 
  /* Правило для выражения, возвращает вычисленный результат и очищает память */
  expression { printf("Result: %lf\n", eval($1)); treefree($1); }

expression: 
  /* Правило для числа, создает узел для числового значения */
  NUMBER { $$ = newnum($1); }
  
  /* Правила для арифметических операций, создают узлы в соответствии с типом операции */
  | expression ADD expression { $$ = newast('+', $1, $3); }
  | expression SUB expression { $$ = newast('-', $1, $3); }
  | expression MUL expression { $$ = newast('*', $1, $3); }
  | expression DIV expression { $$ = newast('/', $1, $3); }
  
  /* Правило для выражения в скобках, возвращает выражение без изменений */
  | '(' expression ')' { $$ = $2; }
%%

struct ast *newast(int nodetype, struct ast *l, struct ast *r) {
struct ast *node = (struct ast *)malloc(sizeof(struct ast));
if (!node) {
fprintf(stderr, "Out of memory\n");
exit(1);
}
node->nodetype = nodetype;
node->l = l;
node->r = r;
return node;
}

struct ast *newnum(double d) {
struct numval *node = (struct numval *)malloc(sizeof(struct numval));
if (!node) {
fprintf(stderr, "Out of memory\n");
exit(1);
}
node->nodetype = 'K';
node->number = d;
return (struct ast *)node;
}

double eval(struct ast *node) {
double result;
if (!node) {
fprintf(stderr, "Error in evaluating expression\n");
exit(1);
}
switch (node->nodetype) {
case 'K':
result = ((struct numval *)node)->number;
break;
case '+':
result = eval(node->l) + eval(node->r);
break;
case '-':
result = eval(node->l) - eval(node->r);
break;
case '*':
result = eval(node->l) * eval(node->r);
break;
case '/':
result = eval(node->l) / eval(node->r);
break;
default:
fprintf(stderr, "Unknown node type: %d\n", node->nodetype);
exit(1);
}
return result;
}

void treefree(struct ast *node) {
if (!node) return;
if (node->nodetype == 'K') {
free((struct numval *)node);
} else {
treefree(node->l);
treefree(node->r);
free(node);
}
}

int main() {
yyparse();
return 0;
}

void yyerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
}
