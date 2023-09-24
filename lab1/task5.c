#include <stdio.h>

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    int i = sizeof(file);
    char mas[i];

    if (file == NULL){
        printf("ERROR");
    }

    while(fgets(mas, i, file) != NULL){
        printf("%s", mas);
    }

    fclose(file);

    return 0;
}
