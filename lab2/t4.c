#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateArray(float array[], int size, float min, float max) {

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        array[i] = min + ((float) rand() / RAND_MAX) * (max - min);
    }
}

void printArray(float array[], int size) {

    printf("Сгенерированный массив:\n");
    for (int i = 0; i < size; i++) {
        printf("%f\n", array[i]);
    }
}

int compare_func(const void *a, const void *b) {
    float *float_a = (float *)a;
    float *float_b = (float *)b;
    if (*float_a > *float_b) return 1;
    if (*float_a < *float_b) return -1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Некорректное число аргументов. Введите размер массива, нижнюю и верхнюю границы интервала.\n");
        return 1;
    }

    int size = atoi(argv[2]);
    float min = atof(argv[3]);
    float max = atof(argv[4]);

    if (size <= 0) {
        printf("Размер массива должен быть положительным числом.\n");
        return 1;
    }

    if (max <= min) {
        printf("Верхняя граница интервала должна быть больше нижней границы.\n");
        return 1;
    }

    float array[size];

    generateArray(array, size, min, max);
    printArray(array, size);

    qsort(array, size, sizeof(float), compare_func);

    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        printf("Не удалось открыть файл\n");
    }

    fprintf(file, "Отсортированный массив:\n");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%f\n", array[i]);
    }

    fclose(file);

    return 0;
}