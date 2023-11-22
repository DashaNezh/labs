#include <stdio.h>
int MAXSIZE = 8;
int stack[8]; //хранение стека в памяти
int top = -1;

int isempty(){ // проверяет пуст ли стек
   if(top == -1)
      return 1;
   else
      return 0;
}

int isfull(){ // проверяет заполнен ли стек
   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek(){ // возвращает верхний элемент стека
   return stack[top];
}

int pop(){ // возвращает элементы из стека
   int data;
   if(!isempty()) {
      data = stack[top];
      top = top - 1;
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n"); // Не удалось получить данные. Стек пуст.
   }
}

int push(int data){ //добавляет элементы в стек
   if(!isfull()) {
      top = top + 1;
      stack[top] = data;
   } else {
      printf("Could not insert data, Stack is full.\n"); //Не удалось вставить данные, стек заполнен.
   }
}

int main(){
   push(44);
   push(10);
   push(62);
   push(123);
   push(15);
   push(57);
   push(3874);
   push(234);
   push(352);
   push(89);
   push(3);
   push(673);
   push(7777);
   push(83421);
   printf("Element at top of the stack: %d\n" ,peek()); //выводит верхний элемент
   printf("Elements: \n");
   while(!isempty()) { //пока стек не заполнен выводит эмененты на экран
      int data = pop();
      printf("%d\n",data);
   }
   if (isfull()){
    printf("Stack is full\n"); //сообщение о заполненном стеке
   }
   else {
    printf("Stack isn't full\n"); // сообщение о не заполненном стеке
   }
   if (isempty()){
    printf("Stack is empty\n"); // сообщение о пустом стеке
   }
   else {
    printf("Stack isn't empty\n"); // сообщение о не пустом стеке
   }
   return 0;
}
