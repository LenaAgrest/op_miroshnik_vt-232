#include "matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

matrix getMemMatrix(int nRows, int nCols) {
int **values = (int **) malloc(sizeof(int*) * nRows);
for (int i = 0; i < nRows; i++)
values[i] = (int *) malloc(sizeof(int) * nCols);
return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
for (int i = 0; i < nMatrices; i++)
ms[i] = getMemMatrix(nRows, nCols);
return ms;
}

void freeMemMatrix(matrix *m) {
    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix *m) {
    printf("Enter the number of rows: ");
    scanf("%d", &m->nRows);

    printf("Enter the number of columns: ");
    scanf("%d", &m->nCols);

    m->values = (int **)malloc(sizeof(int *) * m->nRows);
    for (int i = 0; i < m->nRows; i++) {
        m->values[i] = (int *)malloc(sizeof(int) * m->nCols);
    }

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void outputMatrix(matrix m) {
    printf("Matrix (%d x %d):\n", m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d\t", m.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        printf("Matrix %d:\n", i + 1);
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2) {
    assert(i1 >= 0 && i1 < m.nRows);
    assert(i2 >= 0 && i2 < m.nRows);

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    assert(j1 >= 0 && j1 < m.nCols);
    assert(j2 >= 0 && j2 < m.nCols);

    for (int i = 0; i < m.nRows; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}