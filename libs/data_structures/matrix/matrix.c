#include "matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>

matrix getMemMatrix(int nRows, int nCols)
{
    int **values = (int **)malloc(sizeof(int *) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *)malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols)
{
    matrix *ms = (matrix *)malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}

void freeMemMatrix(matrix *m)
{
    for (int i = 0; i < m->nRows; i++)
    {
        free(m->values[i]);
    }
    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
}

void freeMemMatrices(matrix *ms, int nMatrices)
{
    for (int i = 0; i < nMatrices; i++)
    {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}

void inputMatrix(matrix *m)
{
    printf("Enter the number of rows: ");
    scanf("%d", &m->nRows);

    printf("Enter the number of columns: ");
    scanf("%d", &m->nCols);

    m->values = (int **)malloc(sizeof(int *) * m->nRows);
    for (int i = 0; i < m->nRows; i++)
    {
        m->values[i] = (int *)malloc(sizeof(int) * m->nCols);
    }

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < m->nRows; i++)
    {
        for (int j = 0; j < m->nCols; j++)
        {
            scanf("%d", &m->values[i][j]);
        }
    }
}

void outputMatrix(matrix m)
{
    printf("Matrix (%d x %d):\n", m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; i++)
    {
        for (int j = 0; j < m.nCols; j++)
        {
            printf("%d\t", m.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void outputMatrices(matrix *ms, int nMatrices)
{
    for (int i = 0; i < nMatrices; i++)
    {
        printf("Matrix %d:\n", i + 1);
        outputMatrix(ms[i]);
    }
}

void swapRows(matrix m, int i1, int i2)
{
    assert(i1 >= 0 && i1 < m.nRows);
    assert(i2 >= 0 && i2 < m.nRows);

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2)
{
    assert(j1 >= 0 && j1 < m.nCols);
    assert(j2 >= 0 && j2 < m.nCols);

    for (int i = 0; i < m.nRows; i++)
    {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}

int getSum(int *a, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    return sum;
}

/*int compareRows(matrix m, int row1, int row2, int (*criteria)(int*, int)) {
    return criteria(m.values[row1], m.nCols) - criteria(m.values[row2], m.nCols);
}*/

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int))
{
    assert(m.nRows > 0 && m.nCols > 0);
    assert(m.values != NULL);

    int *criteriaValues = (int *)malloc(sizeof(int) * m.nRows);
    assert(criteriaValues != NULL);

    for (int i = 0; i < m.nRows; i++)
    {
        criteriaValues[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 1; i < m.nRows; i++)
    {
        int j = i;
        while (j > 0 && criteriaValues[j] < criteriaValues[j - 1])
        {
            int tempValue = criteriaValues[j];
            criteriaValues[j] = criteriaValues[j - 1];
            criteriaValues[j - 1] = tempValue;

            for (int k = 0; k < m.nCols; k++)
            {
                int temp = m.values[j][k];
                m.values[j][k] = m.values[j - 1][k];
                m.values[j - 1][k] = temp;
            }
            j--;
        }
    }

    free(criteriaValues);
}

int compareCols(matrix m, int col1, int col2, int (*criteria)(int*, int)) {
    return criteria(m.values[col1], m.nRows) - criteria(m.values[col2], m.nRows);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    assert(m.nRows > 0 && m.nCols > 0);
    assert(m.values != NULL);


    for (int i = 0; i < m.nCols - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < m.nCols; j++) {
            if (compareCols(m, j, minIndex, criteria) < 0) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            for (int k = 0; k < m.nRows; k++) {
                int temp = m.values[k][i];
                m.values[k][i] = m.values[k][minIndex];
                m.values[k][minIndex] = temp;
            }
        }
    }
}

bool isSquareMatrix(matrix *m) {
    assert(m != NULL);
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    assert(m1 != NULL && m2 != NULL);

    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool isEMatrix(matrix *m) {
    assert(m != NULL);
    assert(m->nRows == m->nCols);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (i == j && m->values[i][j] != 1) {
                return false;
            } else if (i != j && m->values[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool isSymmetricMatrix(matrix *m) {
    assert(m != NULL);
    assert(m->nRows == m->nCols);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }
    return true;
}

void transposeSquareMatrix(matrix *m) {
    assert(m != NULL);
    assert(m->nRows == m->nCols);

    for (int i = 0; i < m->nRows; i++) {
        for (int j = i + 1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}

void transposeMatrix(matrix *m) {
    assert(m != NULL);

    int **transposedValues = (int **)malloc(sizeof(int *) * m->nCols);
    for (int i = 0; i < m->nCols; i++) {
        transposedValues[i] = (int *)malloc(sizeof(int) * m->nRows);
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            transposedValues[j][i] = m->values[i][j];
        }
    }

    for (int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }
    free(m->values);

    m->values = transposedValues;
    
    int temp = m->nRows;
    m->nRows = m->nCols;
    m->nCols = temp;
}