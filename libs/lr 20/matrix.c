#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include "matrix.h"

//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols){
    int **values = (int **) malloc(sizeof(int*) * nRows);

    for (int i = 0; i < nRows; i++){
        values[i] = (int *) malloc(sizeof(int) * nCols);
    }

    return (matrix){values, nRows, nCols};
}

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols){
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        ms[i] = getMemMatrix(nRows, nCols);
    }

    return ms;
}

//освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix *m){
    free (m->values);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
}

//ввод матрицы m
void inputMatrix(matrix *m){
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            scanf("%d ", &m->values[i][j]);
        }

        scanf("\n");
    }
}

//ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices){
    for (int k = 0; k < nMatrices; k++) {
        inputMatrix(&ms[k]);
    }
}

//вывод матрицы m
void outputMatrix(matrix m){
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }

        printf("\n");
    }
}

//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices){
    for (int i = 0; i < nMatrices; i++) {
        outputMatrix(ms[i]);

        printf("\n");
    }
}

//обмен строк с порядковыми номерами i1 и i2 в матрице m
void swapRows(matrix m, int i1, int i2){
    if (0 <= i1 && i1 < m.nRows && 0 <= i2 && i2 < m.nRows) {
        int *temp = m.values[i1];
        m.values[i1] = m.values[i2];
        m.values[i2] = temp;
    }
}

//обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2){
    if(0 <= j1 && j1 < m.nCols && 0 <= j2 && j2 < m.nCols){
        for (int i = 0; i < m.nRows; i++) {
            int temp = m.values[i][j1];
            m.values[i][j1] = m.values[i][j2];
            m.values[i][j2] = temp;
        }
    }
}

//меняет значения указателей местами
void swap_pointers(int **a, int **b) {
    int *t = *a;
    *a = *b;
    *b = t;
}

//выполняет сортировку вставками строк матрицы m по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)){
    int *criteriaValues = (int*)malloc(sizeof(int) * m.nRows);

    for (int i = 0; i < m.nRows; i++) {
        criteriaValues[i] = criteria(m.values[i], m.nCols);
    }

    for (int i = 0; i < m.nRows; i++) {
        int minIndex = i;

        for (int j = i + 1; j < m.nRows; j++) {
            if (criteriaValues[j] > criteriaValues[minIndex])
                minIndex = j;
        }

        if (i != minIndex) {
            swap_pointers(&criteriaValues[i], &criteriaValues[minIndex]);
            swapRows(m, i, minIndex);
        }
    }

    free(criteriaValues);
}

//меняет местами значения переменных через указатели
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

//выполняет сортировку выбором столбцов матрицы m по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m,int (*criteria)(int*, int)){
    int *criteriaValues = (int*)malloc(sizeof(int) * m.nCols);
    int *column = (int*)malloc(sizeof(int) * m.nRows);

    for (int j = 0; j < m.nCols; j++) {
        for (int i = 0; i < m.nRows; i++) {
            column[i] = m.values[i][j];
        }

        criteriaValues[j] = criteria(column, m.nCols);
    }

    for (int i = 0; i < m.nCols; i++) {
        int minIndex = i;

        for (int j = i + 1; j < m.nCols; j++) {
            if (criteriaValues[j] < criteriaValues[minIndex])
                minIndex = j;
        }

        if (i != minIndex) {
            swap(&criteriaValues[i], &criteriaValues[minIndex]);
            swapColumns(m, i, minIndex);
        }
    }

    free(column);
    free(criteriaValues);
}

//возвращает значение ’истина’, если матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m){
    return (m->nCols == m->nRows);
}

//возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if (m1->nRows != m2->nRows || m1->nCols != m2->nCols) {
        return 0;
    }
    for (int i = 0; i < m1->nRows; i++) {
        for (int j = 0; j < m1->nCols; j++) {
            if (m1->values[i][j] != m2->values[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

//возвращает значение ’истина’, если матрица m является единичной, ложь – в противном случае
bool isEMatrix(matrix *m){
    if (m->nRows != m->nCols) {
        return 0;
    }

    int n = m->nRows;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i == j) != m->values[i][j]) {
                return 0;
            }
        }
    }

    return 1;
}

//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m){
    if (m->nRows != m->nCols) {
        return 0;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < i; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return 0;
            }
        }
    }

    return 1;
}

//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m){
    if (isSquareMatrix(m) == 1) {
        for (int i = 0; i < m->nRows; i++) {
            for (int j = i + 1; j < m->nCols; j++) {
                int temp = m->values[i][j];
                m->values[i][j] = m->values[j][i];
                m->values[j][i] = temp;
            }
        }
    }
}

//транспонирует матрицу m
void transposeMatrix(matrix *m){
    matrix t = getMemMatrix(m->nRows, m->nCols);
    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            t.values[j][i] = m->values[i][j];
        }
    }

    freeMemMatrix(m);
    *m = t;
}

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m){
    int min = m.values[0][0];
    position min_pos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] < min) {
                min = m.values[i][j];
                min_pos = (position) {i, j};
            }
        }
    }

    return min_pos;
}

//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m){
    int max = m.values[0][0];
    position max_pos = {0, 0};

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            if (m.values[i][j] > max) {
                max = m.values[i][j];
                max_pos = (position) {i, j};
            }
        }
    }

    return max_pos;
}

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols){
    matrix m = getMemMatrix(nRows, nCols);
    int k = 0;

    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            m.values[i][j] = a[k++];
        }
    }

    return m;
}

//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols){
    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);
    int l = 0;

    for (size_t k = 0; k < nMatrices; k++) {
        for (size_t i = 0; i < nRows; i++) {
            for (size_t j = 0; j < nCols; j++) {
                ms[k].values[i][j] = values[l++];
            }
        }
    }

    return ms;
}