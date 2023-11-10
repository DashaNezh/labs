#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} Product; //Определяет структуру Product, которая содержит поля name - массив символов для названия продукта и price - цена продукта.

int comparePrices(const void *a, const void *b) {//`const` указывает на то, что указатели `a` и `b` являются указателями на константные объекты. 
    //Это означает, что внутри функции `comparePrices` нельзя изменять значения, на которые указывают эти указатели. 
    const Product *productA = (const Product *)a;
    const Product *productB = (const Product *)b;

    if (productA->price < productB->price) {
        return -1;
    } else if (productA->price > productB->price) {
        return 1;
    } else {
        return 0;
    }
} //Определяет функцию comparePrices, которая используется для сравнения цен двух продуктов. Она принимает два указателя
//a и b на объекты типа Product и сравнивает их цены. Возвращает -1, если цена a меньше цены b, 1, если цена a больше цены b, и 0, если цены равны.
int main() {
    char *inputFile = "input.txt";
    char *outputFile = "output.txt";
    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        printf("error\n");
        return 1;
    }
    int size;
    fscanf(file, "%d", &size); //Считывает значение переменной size из файла с помощью fscanf. Значение size указывает на количество записей о продуктах.
    Product *products = (Product *)malloc(size * sizeof(Product)); //Выделяет память для массива структур products размером size с помощью функции malloc.
    for (int i = 0; i < size; i++) {
        fscanf(file, "%s %f", products[i].name, &products[i].price); //& - обращение к памяти
    }//Считывает данные о продуктах из файла в массив products с помощью fscanf.
    fclose(file);
    printf("before:\n");
    for (int i = 0; i < size; i++) {
        printf("product: %s, price: %.2f\n", products[i].name, products[i].price);
    }//Выводит информацию о продуктах до сортировки в формате: название продукта и цена.
    qsort(products, size, sizeof(Product), comparePrices);//Сортирует массив products в порядке возрастания цен с помощью функции qsort
    //и передает функцию comparePrices в качестве параметра для сравнения.
    printf("after:\n");
    for (int i = 0; i < size; i++) {
        printf("product: %s, price: %.2f\n", products[i].name, products[i].price);
    }//Выводит информацию о продуктах после сортировки в формате: название продукта и цена.
    FILE *file2 = fopen(outputFile, "w");
    if (file2 == NULL) {
        printf("error \n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "product: %s, price: %.2f\n", products[i].name, products[i].price);
    }// Записывает отсортированные данные в файл с помощью fprintf.
    fclose(file);
    printf("sorted written to '%s'.\n", outputFile);
    free(products);
    return 0;
}
