#include <stdio.h>

int main (int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");

    if (file == NULL){
        printf("ERROR\n");
    }

    int countStr = 0;
    int countLine = 0;

    while (!feof(file)){
        if(fgetc(file) == '\n'){
            countStr++;
        }
        else{
            countLine++;
        }
    }

    int j = 0;

    char text [countStr][countLine];

    fseek(file, 0, SEEK_SET);

    while (!feof(file)){
        fgets(text[j], countLine - 1, file);
        j++;
    }

    fclose(file);

    file = fopen(argv[1], "w");

    if (file == NULL){
        printf("ERROR\n");
    }

    printf("Input text:\n");
    char textNew[256];
    fgets(textNew, 256, stdin);
    fputs(textNew, file);

    for (int i = 0; i < countStr; i++){
        fputs(text[i], file);
    }

    fclose(file);
    return 0;
}