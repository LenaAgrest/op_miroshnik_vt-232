#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <C:\Users\wwwri\OneDrive\Рабочий стол\2 семестр\оп\lab 14\op_miroshnik_vt-232\libs\data_structures\matrix\matrix.c>
#define MAX_FILE_SIZE 1024
//сравнивает два файла на равенство
void assertTXT(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Error...\n");

        return;
    }

    char buffer1[MAX_FILE_SIZE];
    char buffer2[MAX_FILE_SIZE];

    while (fgets(buffer1, MAX_FILE_SIZE, f1) != NULL && fgets(buffer2, MAX_FILE_SIZE, f2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            printf("Ошибка: файлы не одинаковые...\n");

            fclose(f1);
            fclose(f2);

            return;
        }
    }

    printf("It`s work)");
}

//Задание 1: в файле, где хранятся квадратные матрицы, транспонировать их
int task_1(const char *str1) {
    FILE *inputFile, *outputFile;
    int n, i, j;


    //открываем исходный файл для чтения
    inputFile = fopen("C:\\Users\\wwwri\\files\\original_task_1.txt", "r");
    if (inputFile == NULL) {
        printf("Error open file 1\n");

        return 1;
    }

    //открываем новый файл для записи
    outputFile = fopen("C:\\Users\\wwwri\\files\\converted_task_1.txt", "w");
    if (outputFile == NULL) {
        printf("Error open file 2\n");
        fclose(inputFile);

        return 1;
    }

    while (fscanf(inputFile, "%d", &n) == 1) {
        int matrix[n][n];

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                fscanf(inputFile, "%d", &matrix[i][j]);
            }
        }

        for (j = 0; j < n; j++) {
            for (i = 0; i < n; i++) {
                fprintf(outputFile, "%d ", matrix[i][j]);
            }

            fprintf(outputFile, "\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

//заполняет файл случайными квадратными матрицами
void generateFileWithRandomSquareMatrices(const char* filename, int numMatrices, int maxSize) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error open file 3\n");
        return;
    }

    srand(time(NULL));

    for (int k = 0; k < numMatrices; k++) {
        int n = rand() % maxSize + 1;

        fprintf(file, "%d\n", n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%d ", rand() % 100);
            }

            fprintf(file, "\n");
        }
    }

    fclose(file);
}

int main() {
    generateFileWithRandomSquareMatrices("C:\\Users\\wwwri\\files\\original_task_1.txt", 3, 3);

    return 0;
}
