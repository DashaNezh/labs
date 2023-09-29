#include <stdio.h>
#include <stdlib.h>

struct Tovar {
    char nameOfTovar[100];
    float price;
};

void sort_tovar(struct Tovar tovari[], int count_tovarov) {
    struct Tovar time;

    for (int i = 0; i < count_tovarov - 1; i++) {
        for (int j = 0; j < count_tovarov - i - 1; j++) {
            if (tovari[j].price > tovari[j + 1].price) {
                time = tovari[j];
                tovari[j] = tovari[j + 1];
                tovari[j + 1] = time;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Not enough arguments\n");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");

    if (input_file == NULL || output_file == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    struct Tovar tovari[100];
    int count_tovarov;

    if (fscanf(input_file, "%d", &count_tovarov) != 1) {
        printf("Error reading input file\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    for (int i = 0; i < count_tovarov; i++) {
        if (fscanf(input_file, "%s %f", tovari[i].nameOfTovar, &tovari[i].price) != 2) {
            printf("Error reading input file\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }

    fclose(input_file);

    sort_tovar(tovari, count_tovarov);

    for (int i = 0; i < count_tovarov; i++) {
        fprintf(output_file, "%s %.2f\n", tovari[i].nameOfTovar, tovari[i].price);
    }

    fclose(output_file);

    return 0;
}
