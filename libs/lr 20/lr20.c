#include <stdio.h>
#include "lr20.h"
#include "matrix.c"
#include <stdbool.h>

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
void secondTask(matrix m, matrix *newM, int rows, int cols){
    for (int indRow = 0; indRow < rows; indRow++){
        for (int indCol = 0; indCol < cols; indCol++){
            int countNeighbors = calculateCountNeighbors(m, indRow, indCol, rows, cols);

            newM->values[indRow][indCol] = cellResultByPosition(m, indRow, indCol, countNeighbors);
        }
    }
}