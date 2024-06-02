#ifndef LAB_14_LR20_H
#define LAB_14_LR20_H

#include <stdbool.h>
#include "matrix.h"
#include "../data_structures/vector/vector.h"
#include <signal.h>
#include <unistd.h>

typedef struct domain{
    size_t visits;
    char name[200];
} domain;

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

//заполняет матрицу нулями
void matrixFillingZeros(matrix *m, int row, int col);

void task_1(matrix *m, int countRequests, int *requestsArray[]);

bool isIndex(int rows, int cols, int indRow, int indCol);

int cellResultByPosition(matrix m, int indRow, int indCol, int countNeighbors);

int calculateCountNeighbors(matrix m, int rowInd, int colInd, int rows, int cols);

void task_2(matrix m, matrix *newM, int rows, int cols);

int sortedNumsCompare(const void * firstNum, const void * secondNum);

void fillingNumFrameSorted(int *array, matrix m, int indRow, int indCol);

void task_3(matrix *m, int size);

bool searchNumFromArray(const int array[], int length, int num);

int searchDomainInResults(const domain results[], int size, char *s);

void handlerDotPrtNotNull(domain *array, int ind, char *dotPtr, domain results[], int *sizeResult);

void task_4(domain array[], int size);

void fillingCalcMatrix(matrix m, matrix *calcMatrix, int rows, int cols);

void task_5(matrix m, int rows, int cols, int *result);

void task_6(const char *s, int length, char *result, int *resultLength);

node *createNode(int k);

int searchMaxInd(int array[], int start, int end);

void buildNodes(node *currentNode, int array[], int startInd, int endInd, bool isLeft);

void breadthFirstTraversal(node *root);

void task_7(int array[], int lengthArray);

void task_8(const char *s, int length, const int indexes[], char *newS);

FILE* openFile(char *fileName, char *action);

void fillingFile(int numsArray[], int lengthArray, char *fileName);

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int controlNum, char *wFileName);

void task_9(int numsArray[], int lengthArray, int controlNum, char *firstFileName, char *secondFileName, vector *v);

void fillingFileWithText(char *fileName, char *text);

void task_10(char *fileName, size_t countOutputLines, char *text);

void task_11(char **dict, char **requests, int *num_in_req, int n, int q);

#endif //LAB_14_LR20_H