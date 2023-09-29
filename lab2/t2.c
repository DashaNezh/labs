#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 10

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "w");

    if (file == NULL){
        printf("ERROR\n");
    }

    int array[ARRAY_SIZE];

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++){
        array[i] = rand();
    }

    fprintf(file, "Массив не в обратном порядке:\n");
    for (int i = 0; i < ARRAY_SIZE; i ++){
        fprintf(file, "%d\n", array[i]);
    }

    fprintf(file, "Массив в обратном порядке:\n");

    for (int i = ARRAY_SIZE - 1; i >= 0; i--){
        fprintf(file, "%d\n", array[i]);
    }
    
    fclose(file);

    return 0;
}