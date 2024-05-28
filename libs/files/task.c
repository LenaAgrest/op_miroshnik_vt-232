#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <C:\Users\wwwri\OneDrive\Рабочий стол\2 семестр\оп\lab 14\op_miroshnik_vt-232\libs\data_structures\matrix\matrix.c>

#define MAX_FILE_SIZE 1024
#define MAX_LENGTH 100
#define MAX_WORD_LENGTH 15
#define MAX_NUM_WORDS 5
#define NUM_LINES 10

typedef struct {
    int power;
    int coefficient;
} Polynomial;
//сравнивает два файла на равенство
void assertTXT(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Ошибка...\n");

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

    printf("It`s work) \n");
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

//1
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

//2
int task_2(const char *str) {
    FILE *inputFile, *outputFile;
    float number;

    inputFile = fopen("C:\\Users\\wwwri\\files\\original_task_2.txt", "r");
    outputFile = fopen("C:\\Users\\wwwri\\files\\converted_task_2.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error open file 3\n");
        return 1;
    }

    while (fscanf(inputFile, "%f", &number) == 1) {
        fprintf(outputFile, "%.2f\n", number);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

//3
int task_3(const char *str) {
    FILE *file, *file1;
    char expression[100];
    int result;
    char ch;
    int count = 0;

    file = fopen("C:\\Users\\wwwri\\files\\original_task_3.txt", "r");
    if (file == NULL) {
        printf("Error open file 5\n");
        return 1;
    }
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    fclose(file);

    file1 = fopen("C:\\Users\\wwwri\\files\\original_task_3.txt", "r+");
    int num1, num2, num3;
    char op1, op2;
    if (count == 5){
        fscanf(file1, "%d %c %d", &num1, &op1, &num2);

        if (op1 == '+') {
            result = num1 + num2;
        } else if (op1 == '-') {
            result = num1 - num2;
        } else if (op1 == '*') {
            result = num1 * num2;
        } else if (op1 == '/') {
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                printf("Error: division by zero\n");
                fclose(file1);
                return 1;
            }
        } else {
            printf("Error: invalid operator 1\n");
            fclose(file1);
            return 1;
        }
    } else if (count == 9){
        fscanf(file1, "%d %c %d %c %d", &num1, &op1, &num2, &op2, &num3);

        if (op1 == '+' && op2 == '+') {
            result = num1 + num2 + num3;
        } else if (op1 == '+' && op2 == '-') {
            result = num1 + num2 - num3;
        } else if (op1 == '+' && op2 == '*') {
            result = num1 + (num2 * num3);
        } else if (op1 == '+' && op2 == '/') {
            if (num3 != 0) {
                result = num1 + (num2 / num3);
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '-' && op2 == '+') {
            result = num1 - num2 + num3;
        } else if (op1 == '-' && op2 == '-') {
            result = num1 - num2 - num3;
        } else if (op1 == '-' && op2 == '*') {
            result = num1 - (num2 * num3);
        } else if (op1 == '-' && op2 == '/') {
            if (num3 != 0) {
                result = num1 - (num2 / num3);
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '*' && op2 == '+') {
            result = num1 * num2 + num3;
        } else if (op1 == '*' && op2 == '-') {
            result = num1 * num2 - num3;
        } else if (op1 == '*' && op2 == '*') {
            result = num1 * num2 * num3;
        } else if (op1 == '*' && op2 == '/') {
            if (num3 != 0) {
                result = num1 * num2 / num3;
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '/' && op2 == '+') {
            if (num2 != 0) {
                result = num1 / num2 + num3;
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '/' && op2 == '-') {
            if (num2 != 0) {
                result = num1 / num2 - num3;
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '/' && op2 == '*') {
            if (num2 != 0) {
                result = num1 / num2 * num3;
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else if (op1 == '/' && op2 == '/') {
            if (num2 != 0 && num3 != 0) {
                result = num1 / num2 / num3;
            } else {
                fprintf(file1, "\nError: division by zero");;
                fclose(file1);
                return 1;
            }
        } else {
            printf("Error: invalid operator2\n");
            fclose(file1);
            return 1;
        }
    } else {
        fclose(file1);
    }

    fprintf(file1, "\nResult: %d\n", result);

    fclose(file1);

    return 0;
}

//заполняет файл различными последовательностями символов через пробел
void generateFileWithDifSequences(const char* filename, int numWords) {
    FILE *file = fopen(filename, "w");
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int i, j;

    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }

    srand(time(NULL));

    for (i = 0; i < numWords; i++) {
        char word[rand() % 100];
        for (j = 0; j < rand() % 100; j++) {
            word[j] = alphabet[rand() % strlen(alphabet)]; //выбор случайной буквы из алфавита
        }
        word[rand() % 100] = '\0';
        fprintf(file, "%s ", word);
    }

    fclose(file);
}

//Задание 4: сохранить в файле только те слова, которые содержат данную последовательность символов
int task_4(const char* sourceFilename, const char* destinationFilename, const char* sequence) {
    FILE *sourceFile, *destinationFile;

    sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) {
        printf("Error open file in\n");
        return 1;
    }

    destinationFile = fopen(destinationFilename, "w");
    if (destinationFile == NULL) {
        printf("Error open file out\n");
        fclose(sourceFile);
        return 1;
    }

    char word[MAX_FILE_SIZE];

    while (fscanf(sourceFile, "%s", word) == 1) {
        if (strstr(word, sequence) != NULL) {
            fprintf(destinationFile, "%s\n", word);
        }
    }

    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}
//заполняет файл 10 строками с различными последовательностями (словами)
void generateFileWithStringsSequences(const char* fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error open file \n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_LINES; i++) {
        int numWords = rand() % MAX_NUM_WORDS + 1;
        for (int j = 0; j < numWords; j++) {
            int wordLength = rand() % MAX_WORD_LENGTH + 1;
            for (int k = 0; k < wordLength; k++) {
                char randomChar = 'a' + rand() % 26;
                fputc(randomChar, file);
            }
            if (j < numWords - 1) {
                fputc(' ', file);
            }
        }
        fprintf(file, " \n");
    }

    fclose(file);
}

//Задание 5: преобразовать файл, оставив в каждой строке только самое длинное слово
int task_5(const char* sourceFilename, const char* destinationFilename) {
    FILE *sourceFile, *destinationFile;

    sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) {
        printf("Error open file in\n");
        return 1;
    }

    destinationFile = fopen(destinationFilename, "w");
    if (destinationFile == NULL) {
        printf("Error open file out\n");
        fclose(sourceFile);
        return 1;
    }

    char line[MAX_LENGTH];
    char longestWord[MAX_LENGTH];
    int maxLength = 0;

    while (fgets(line, sizeof(line), sourceFile)) {
        char* word = strtok(line, " ");
        char* lastWord = NULL;
        while (word != NULL) {
            int length = strlen(word);
            if (length > maxLength) {
                maxLength = length;
                strcpy(longestWord, word);
            }

            lastWord = word;
            word = strtok(NULL, " ");
        }

        fprintf(destinationFile, "%s\n", longestWord);

        maxLength = 0;
    }

    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}

//возводит число в степень
int pow_(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }

    return result;
}

//Задание 6: удалить многочлены с корнем x из бинарного файла
void task_6(const char *filename, int x) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error open file in\n");
        exit(-3);
    }

    FILE *temp_file = fopen("C:\\Users\\wwwri\\files\\converted_task_6.txt", "wb");

    if (!temp_file) {
        printf("Error open file out\n");
        fclose(file);
        exit(-3);
    }

    Polynomial poly;

    while (fread(&poly, sizeof(Polynomial), 1, file)) {
        if ((poly.coefficient * pow_(x, poly.power)) != (x * x)) {
            fwrite(&poly, sizeof(Polynomial), 1, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);
}