#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateArray(float array[], int size) {

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = (float) rand() / RAND_MAX;
    }
}

void printArray(float array[], int size) {
    int i;

    printf("Сгенерированный массив:\n");
    for (i = 0; i < size; i++) {
        printf("%f\n", array[i]);
    }
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Некорректное число аргументов. Введите размер массива.\n");
    }

    int size = atoi(argv[1]);
    if (size <= 0) {
        printf("Размер массива должен быть положительным числом.\n");
    }

    float array[size];

    generateArray(array, size);
    printArray(array, size);

    return 0;
}