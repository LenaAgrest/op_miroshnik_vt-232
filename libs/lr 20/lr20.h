#ifndef LAB_14_LR20_H
#define LAB_14_LR20_H

#include <stdbool.h>
#include "matrix.h"
#include <stdbool.h>

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

#endif //LAB_14_LR20_H