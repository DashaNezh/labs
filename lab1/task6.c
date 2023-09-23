#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *file1 = fopen(argv[1], "r");
    char newFile[] = "newFile.txt";
    char line[256];
    int lineCount = 0;

    if (file1 == NULL){
        printf("ERROR\n");
    }

    FILE *file2 = fopen(newFile, "w");
    if (file2 == NULL){
        printf("ERROR");
    }

    while (fgets(line, sizeof(line), file1) != NULL){
        fputs(line, file2);
        lineCount++;
    }

    fclose(file1);
    fclose(file2);
    printf("GOOD\n");
    return 0;
    
}