#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 10

int main(){
    int array[10];

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++){
        array[i] = rand();
    }

    printf("Сгенерированный массив:\n");

    for (int i = 0; i < ARRAY_SIZE; i ++){
        printf("%d\n", array[i]);
    }

    return 0;
}