
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_SIZE 100

int define(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
//используется для определения, является ли символ оператором или нет. 
//Она принимает символ c и возвращает 1, если c является одним из операторов +, -, * или /, в противном случае возвращает 0.

int prio(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}
//используется для определения приоритета оператора. 
//Она принимает на вход оператор op и возвращает 1, если op является + или -, 2, если op является  или /, и 0 во всех остальных случаях.

int main() {
    char infix[STACK_SIZE]; //для хранения введенного инфиксного выражения
    printf("type infix exp\n");
    scanf("%s",infix);
    char postfix[STACK_SIZE]; //для хранения постфиксной записи
    char oper[STACK_SIZE]; //для хранения операторов
    int top = -1;
    int i, j;
    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isdigit(c)) {
            postfix[j++] = c; //eсли символ является цифрой, он добавляется в постфиксную запись
        } else if (c == '(') {
            oper[++top] = c; //eсли символ - открывающая скобка '(', он помещается в стек операторов
        } else if (c == ')') {
            while (top >= 0 && oper[top] != '(') {
                postfix[j++] = oper[top--]; 
            }
            if (top >= 0 && oper[top] == '(') {
                top--; //eсли символ - закрывающая скобка ')', 
                //то извлекаются все операторы из стека операторов и добавляются в постфиксную запись, пока не встретится открывающая скобка '('.
            }
        } else if (define(c)) {
            while (top >= 0 && prio(oper[top]) >= prio(c)) {
                postfix[j++] = oper[top--];
            }
            oper[++top] = c;
        }
        //eсли символ - оператор, сравнивается приоритет оператора со стеком операторов. eсли текущий оператор имеет меньший или равный приоритет, 
        //чем оператор на вершине стека, извлекается оператор из стека и добавляется в постфиксную запись, пока это условие выполняется. 
        //затем текущий оператор помещается в стек.
    }
    while (top >= 0) {
        postfix[j++] = oper[top--];
    }
    //после обработки инфиксной записи, все оставшиеся операторы из стека операторов извлекаются и добавляются в постфиксную запись.
    postfix[j] = '\0'; //возвращается в конец строки
    printf("infix: %s\n", infix);
    printf("postfix: %s\n", postfix);
    return 0;
}
