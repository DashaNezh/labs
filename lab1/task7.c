#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1], "r");
    char str[100];
    int lineNum = 0;
    int curNum= 1;

    if (file == NULL){
        printf("ERROR\n");
    }

    if (fgets(str, sizeof(str), file) != NULL){
        lineNum = atoi(str);
    }else{
        printf("PUSTO\n");
    }

    fclose(file);

    file = fopen(argv[1], "r");

    if (file == NULL){
        printf("ERROR\n");
    }

    while (fgets(str, sizeof(str), file) != NULL){
        if (curNum == lineNum + 1){
            break;
        }
        curNum++;
    }

    file = fopen(argv[1], "a");

    if (file == NULL){
        printf("ERROR\n");
    }

    fprintf(file, "%s", str);

    fclose(file);

    return 0;
}
