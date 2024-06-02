#include <stdio.h>
//#include "lr20.h"
#include "matrix.c"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../data_structures/vector/vector.c"
#include "C:\Users\wwwri\OneDrive\Рабочий стол\2 семестр\оп\lab 14\op_miroshnik_vt-232\libs\string\tasks\string_.c"

#define MAXN 300005
#define MAXQ 5005
#define MAXLEN 2000005

typedef struct domain{
    size_t visits;
    char name[200];
} domain;

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

void matrixFillingZeros(matrix *m, int row, int col){
    for (int indRow = 0; indRow < row; indRow++){
        for (int indCol = 0; indCol < col; indCol++){
            m->values[indRow][indCol] = 0;
        }
    }
}

//1
void task_1(matrix *m, int countRequests, int *requestsArray[]){
    int row1, col1, row2, col2;

    for (int request = 0; request < countRequests; request++){
        row1 = requestsArray[request][0];
        col1 = requestsArray[request][1];
        row2 = requestsArray[request][2];
        col2 = requestsArray[request][3];

        for (int indRow = row1; indRow <= row2; indRow++){
            for (int indCol = col1; indCol <= col2; indCol++){
                m->values[indRow][indCol]++;
            }
        }
    }
}

bool isIndex(int rows, int cols, int indRow, int indCol){
    if (indRow > -1 && indRow < rows && indCol > -1 && indCol < cols){
        return 1;
    }

    return 0;
}

int cellResultByPosition(matrix m, int indRow, int indCol, int countNeighbors){
    return ((m.values[indRow][indCol] == 1 && (countNeighbors == 2 || countNeighbors == 3)) || (m.values[indRow][indCol] == 0 && countNeighbors == 3));
}

int calculateCountNeighbors(matrix m, int rowInd, int colInd, int rows, int cols){
    int countNeighbors = 0;

    for (int indRowMath = rowInd - 1; indRowMath < rowInd + 2; indRowMath++){
        for (int indColMath = colInd - 1; indColMath < colInd + 2; indColMath++){
            if (isIndex(rows, cols, indRowMath, indColMath) &&
                m.values[indRowMath][indColMath] && (rowInd != indRowMath || colInd != indColMath)){

                countNeighbors++;
            }
        }
    }

    return countNeighbors;
}

//2
void task_2(matrix m, matrix *newM, int rows, int cols){
    for (int indRow = 0; indRow < rows; indRow++){
        for (int indCol = 0; indCol < cols; indCol++){
            int countNeighbors = calculateCountNeighbors(m, indRow, indCol, rows, cols);

            newM->values[indRow][indCol] = cellResultByPosition(m, indRow, indCol, countNeighbors);
        }
    }
}

int sortedNumsCompare(const void * firstNum, const void * secondNum){
    return ( *(int*)firstNum - *(int*)secondNum );
}

void fillingNumFrameSorted(int *array, matrix m, int indRow, int indCol){
    int arrayInd = 0;
    for (int mIndRow = indRow - 1; mIndRow < indRow + 2; mIndRow++){
        for(int mIndCol = indCol - 1; mIndCol < indCol + 2; mIndCol++){
            if (mIndRow != indRow || mIndCol != indCol){
                array[arrayInd++] = m.values[mIndRow][mIndCol];
            }
        }
    }

    qsort(array, 8, sizeof(int), sortedNumsCompare);
}

//3
void task_3(matrix *m, int size){
    int frame[8];
    for (int indRow = 1; indRow < size - 1; indRow++){
        for(int indCol = 1; indCol < size - 1; indCol++){
            fillingNumFrameSorted(frame, *m, indRow, indCol);

            int median = (frame[3] + frame[4]) / 2;

            m->values[indRow][indCol] = median;
        }
    }
}

void outputResultDomains(domain *results, int size){
    for (int i = 0; i < size; i++){
        printf("%ld %s\n", results[i].visits, results[i].name);
    }
}

bool searchNumFromArray(const int array[], int length, int num){
    for (int i = 0; i < length; i++){
        if (num == array[i]){
            return 1;
        }
    }

    return 0;
}

int searchDomainInResults(const domain results[], int size, char *s){
    for (int i = 0; i < size; i++){
        if (strcmp(results[i].name, s) == 0){
            return i;
        }
    }

    return size;
}

void handlerDotPrtNotNull(domain *array, int ind, char *dotPtr, domain results[], int *sizeResult){
    strcpy(array[ind].name, dotPtr + 1);

    int pos = searchDomainInResults(results, *sizeResult,array[ind].name);

    if (pos == *sizeResult){
        results[*sizeResult] = array[ind];
        *sizeResult += 1;
    } else{
        results[pos].visits += array[ind].visits;
    }
}

//4
/*void task_4(domain array[], int size){
    int closeIndexes[size];
    int countClose = 0;
    domain results[200];
    int sizeResult = 0;

    for (int i = 0; i < size; i++){
        results[sizeResult++] = array[i];
    }

    while(countClose != size){
        for (int i = 0; i < size; i++){
            if (!searchNumFromArray(closeIndexes, countClose, i)){
                char *dotPtr = strchr(array[i].name, '.');

                if (dotPtr != NULL){
                    handlerDotPrtNotNull(array, i, dotPtr, results, &sizeResult);
                } else{
                    closeIndexes[countClose++] = i;
                }
            }
        }
    }

    outputResultDomains(results, sizeResult);
}*/

void fillingCalcMatrix(matrix m, matrix *calcMatrix, int rows, int cols){
    for (int indRow = 0; indRow < rows; indRow++){
        for (int indCol = 0; indCol < cols; indCol++){
            if (m.values[indRow][indCol] == 1){
                if (indRow != 0){
                    calcMatrix->values[indRow][indCol] = calcMatrix->values[indRow - 1][indCol] + 1;
                }
                else{
                    calcMatrix->values[indRow][indCol] = 1;
                }
            } else {
                calcMatrix->values[indRow][indCol] = 0;
            }
        }
    }
}

//5
void task_5(matrix m, int rows, int cols, int *result){
    matrix calcMatrix = getMemMatrix(rows, cols);
    fillingCalcMatrix(m, &calcMatrix, rows, cols);

    int calcResult = 0;

    for (int indCol = 0; indCol < cols; indCol++){
        for (int indRow = 0; indRow < rows; indRow++){
            for (int indK = indCol + 1; indK < cols + 1; indK++){
                int min = calcMatrix.values[indRow][indCol];

                for (int indFromColToK = indCol; indFromColToK < indK; indFromColToK++){
                    if (calcMatrix.values[indRow][indFromColToK] < min){
                        min = calcMatrix.values[indRow][indFromColToK];
                    }
                }

                calcResult += min;
            }
        }
    }

    *result = calcResult;
}

void task_6(const char *s, int length, char *result, int *resultLength){
    char buffer[10];
    int bufferLength = 0;
    int calcResultLength = 0;

    char num = '1';
    for (int i = 0; i < length; i++) {
        buffer[bufferLength++] = num++;

        if (s[i] == 'I') {
            while (bufferLength > 0){
                result[calcResultLength++] = buffer[--bufferLength];
            }
        }
    }

    buffer[bufferLength++] = num;

    while (bufferLength > 0){
        result[calcResultLength++] = buffer[--bufferLength];
    }

    result[calcResultLength] = '\0';
    *resultLength = calcResultLength;
}

node *createNode(int k) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->key = k;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int searchMaxInd(int array[], int start, int end) {
    int maxNum = array[start];
    int maxInd = start;

    for (int i = start + 1; i <= end; i++) {
        if (array[i] > maxNum) {
            maxNum = array[i];
            maxInd = i;
        }
    }

    return maxInd;
}

void buildNodes(node *currentNode, int array[], int startInd, int endInd, bool isLeft) {
    if (startInd > endInd) {
        return;
    }

    int maxInd = searchMaxInd(array, startInd, endInd);
    node *newNode = createNode(array[maxInd]);

    if (isLeft) {
        currentNode->left = newNode;
    } else {
        currentNode->right = newNode;
    }

    buildNodes(newNode, array, startInd, maxInd - 1, true);
    buildNodes(newNode, array, maxInd + 1, endInd, false);
}

void breadthFirstTraversal(node *root) {
    if (root == NULL) {
        return;
    }

    node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        node *current = queue[front++];

        if (current != root) {
            printf(",");
        }

        if (current == NULL) {
            printf("null");
        } else {
            printf("%d", current->key);
            if(current->left != NULL || current->right != NULL) {
                queue[rear++] = current->left;
                queue[rear++] = current->right;
            }
        }
    }
}

//7
void task_7(int array[], int lengthArray) {
    if (lengthArray == 0) {
        return;
    }

    int maxNumInd = searchMaxInd(array, 0, lengthArray - 1);
    node *root = createNode(array[maxNumInd]);

    buildNodes(root, array, 0, maxNumInd - 1, true);
    buildNodes(root, array, maxNumInd + 1, lengthArray - 1, false);

    breadthFirstTraversal(root);

    printf("\n");
}

//8
void task_8(const char *s, int length, const int indexes[], char *newS){
    for (int i = 0; i < length; i++){
        newS[i] = s[indexes[i]];
    }

    newS[length] = '\0';
}

FILE* openFile(char *fileName, char *action){
    FILE *file = fopen(fileName, action);

    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }

    return file;
}

void fillingFile(int numsArray[], int lengthArray, char *fileName){
    FILE *file = openFile(fileName, "w");

    for (int i = 0; i < lengthArray; i++){
        fprintf(file, "%d ", numsArray[i]);
    }

    fclose(file);
}

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int controlNum, char *wFileName){
    FILE *rFile = openFile(rFileName, "r");
    FILE *wFile = openFile(wFileName, "w");

    int num;

    while (fscanf(rFile, "%d", &num) == 1){
        if (num < controlNum){
            pushBack(v, num);

            fprintf(wFile, "%d ", num);
        }
    }

    fclose(rFile);
    fclose(wFile);
}

//9
void task_9(int numsArray[], int lengthArray, int controlNum, char *firstFileName, char *secondFileName, vector *v){
    fillingFile(numsArray, lengthArray,firstFileName);
    readingNumsFilteringAndWriting(v, firstFileName, controlNum, secondFileName);
    shrinkToFit(v);
}

void fillingFileWithText(char *fileName, char *text){
    FILE *file = openFile(fileName, "w");
    fprintf(file, "%s", text);
    fclose(file);
}

//10
void task_10(char *fileName, size_t countOutputLines, char *text) {
    fillingFileWithText(fileName, text);

    FILE *file = openFile(fileName, "r");

    char line[127];
    int count = 0;

    while (fgets(line, 127, file) != NULL) {
        printf("%s", line);
        count++;

        if (count == countOutputLines) {
            printf("Пожалуйста, введите Ctrl + C\n");

            while (getch() != 3);
        }
    }
}

void task_11(char **dict, char **requests, int *num_in_req, int n, int q) {
    int temp_pepe = 0;
    int temp_pepe2 = 0;

    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < n; ++j) {

            if (strstr(dict[j], requests[i]) != NULL) {
                temp_pepe++;
                temp_pepe2++;
            } else
                temp_pepe++;

            if (temp_pepe2 == num_in_req[i]) {
                printf("%d\n", temp_pepe);
                break;
            }
        }

        if (num_in_req[i] > temp_pepe2) {
            printf("-1\n");

            temp_pepe = 0;
            temp_pepe2 = 0;
        } else {
            temp_pepe = 0;
            temp_pepe2 = 0;
        }
    }
}