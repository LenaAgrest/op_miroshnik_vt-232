#include "matrix.h" 
#include "assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void task1(matrix *m) {
    int max, min;
    max = getMaxValuePos(*m).rowIndex;
    min = getMinValuePos(*m).rowIndex;

    swapRows(*m, max, min);
}

void test_task1() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {7, 8, 9,
                                                    4, 5, 6,
                                                    1, 2, 3},
                                           3, 3);

    task1(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

int getMax(int *a, int n) {
    int max = a[0];

    for (int i = 1; i < n; ++i)
        max = max > a[i] ? max : a[i];

    return max;
}

void sortRowsByMinElement(matrix m) {
    insertionSortRowsMatrixByRowCriteria(m, getMax);
}

void task2(matrix m) {
    sortRowsByMinElement(m);
}

void test_task2() {
    matrix m = createMatrixFromArray((int[]) {7, 1, 2,
                                              1, 8, 1,
                                              3, 2, 3},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {3, 2, 3,
                                                    7, 1, 2,
                                                    1, 8, 1},
                                           3, 3);

    task2(m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

int getMin(int *a, int n) {
    int min = a[0];

    for (int i = 1; i < n; ++i)
        min = min < a[i] ? min : a[i];

    return min;
}

void sortColsByMinElement(matrix *m) {
    selectionSortColsMatrixByColCriteria(*m, getMin);
}

void task3(matrix *m) {
    sortColsByMinElement(m);
}

void test_task3() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 2, 4, 3, 3,
                                              2, 5, 1, 8, 2, 7,
                                              6, 1, 4, 4, 8, 3},
                                     3, 6);
    matrix exp_res = createMatrixFromArray((int[]) {5, 2, 3, 3, 3, 4,
                                                    5, 1, 2, 2, 7, 8,
                                                    1, 4, 6, 8, 3, 4},
                                           3, 6);

    task3(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

matrix mulMatrices(matrix m1, matrix m2) {
    assert(m1.nRows * m1.nCols == m2.nRows * m2.nCols);

    matrix temp = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            temp.values[i][j] = 0;

            for (int k = 0; k < m2.nRows; k++)
                temp.values[i][j] += m1.values[i][k] * m2.values[k][j];
        }
    }

    return temp;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    assert(isSymmetricMatrix(m));

    matrix temp = mulMatrices(*m, *m);
    freeMemMatrix(m);
    *m = temp;
}

void task4(matrix *m) {
    getSquareOfMatrixIfSymmetric(m);
}

void test_task4() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              2, 4, 5,
                                              3, 5, 6},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {14, 25, 31,
                                                    25, 45, 56,
                                                    31, 56, 70},
                                           3, 3);

    task4(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j > 0; j--) {
            if (a[i] == a[j] && i != j)
                return false;
        }
    }
    return true;
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix *m) {
    long long temp[m->nRows];
    for (int i = 0; i < m->nRows; ++i)
        temp[i] = getSum(m->values[i], m->nCols);

    assert(isUnique(temp, m->nRows));

    transposeMatrix(m);
}

void task5(matrix *m) {
    transposeIfMatrixHasNotEqualSumOfRows(m);
}

void test_task5() {
    matrix m = createMatrixFromArray((int[]) {45, 55, 11,
                                              67, 95, 96,
                                              121, 51, 7},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {45, 67, 121,
                                                    55, 95, 51,
                                                    11, 96, 7},
                                           3, 3);

    task5(&m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

bool isMutuallyInverseMatrices(matrix m1, matrix m2) {
    if (m1.nCols != m2.nCols || m1.nRows != m2.nRows)
        return false;
    else {
        matrix mul_m = mulMatrices(m1, m2);
        return isEMatrix(&mul_m);
    }
}

bool task6(matrix m1, matrix m2) {
    return isMutuallyInverseMatrices(m1, m2);
}

void test_task6() {
    matrix m = createMatrixFromArray((int[]) {1, 2,
                                              2, 3},
                                     2, 2);
    matrix exp_res = createMatrixFromArray((int[]) {-3, 2,
                                                    2, -1},
                                           2, 2);

    assert(task6(m, exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

int maxim(int a, int b) {
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long count = 0;
    int max_num = 0;

    for (int i = 1; i < m.nCols; ++i) {
        int i_row = 0;
        int i_col = i;
        max_num = m.values[i_row][i_col];
        while (i_col < m.nCols && i_row < m.nRows) {
            max_num = maxim(max_num, m.values[i_row][i_col]);
            i_row++;
            i_col++;
        }
        count += max_num;
    }

    for (int i = 1; i < m.nRows; ++i) {
        int i_row = i;
        int i_col = 0;
        max_num = m.values[i_row][i_col];
        printf("\n");
        while (i_col < m.nRows && i_row < m.nRows) {
            max_num = max(max_num, m.values[i_row][i_col]);
            i_row++;
            i_col++;
        }
        count += max_num;
    }

    return count;
}

long long task7(matrix m) {
    return findSumOfMaxesOfPseudoDiagonal(m);
}

void test_task7() {
    matrix m = createMatrixFromArray((int[]) {3, 2, 5, 4,
                                              1, 3, 6, 3,
                                              3, 2, 1, 2},
                                     3, 4);
    assert(task7(m) == 20);
    freeMemMatrix(&m);
}

int getMinInArea(matrix m) {
    position max_pos = getMaxValuePos(m);
    int min = m.values[max_pos.rowIndex][max_pos.colIndex];

    int row = max_pos.rowIndex - 1;
    int start_col = max_pos.colIndex - 1 >= 0 ?
                    max_pos.colIndex - 1 : 0;
    int col = start_col;
    int col_end = max_pos.colIndex + 1 <= m.nCols - 1 ?
                  max_pos.colIndex + 1 : m.nCols - 1;

    for (int i = row; i >= 0; --i) {
        for (int j = col; j <= col_end; ++j)
            min = min < m.values[i][j] ? min : m.values[i][j];

        start_col = start_col - 1 >= 0 ?
                    start_col - 1 : 0;
        col = start_col;
        col_end = col_end + 1 <= m.nCols - 1 ?
                  col_end + 1 : m.nCols - 1;
    }

    return min;
}

int task8(matrix m) {
    return getMinInArea(m);
}

void test_task8() {
    matrix test = createMatrixFromArray((int[]) {10, 7, 5, 6,
                                                 3, 11, 8, 9,
                                                 4, 1, 12, 2},
                                        3, 4);
    assert(task8(test) == 5);
    freeMemMatrix(&test);

    test = createMatrixFromArray((int[]) {6, 8, 9, 2,
                                          7, 12, 3, 4,
                                          10, 11, 5, 1},
                                 3, 4);
    assert(task8(test) == 6);
    freeMemMatrix(&test);
}

float getDistance(int *a, int n) {
    float distance = 0;
    for (int i = 0; i < n; ++i)
        distance += a[i] * a[i];

    distance = sqrtf(distance);

    return distance;
}

void insertionSortRowsMatrixByRowCriteriaF(matrix *m, float (*criteria)(int *, int)) {
    float temp[m->nRows];
    float temp_pepe;
    for (int i = 0; i < m->nRows; ++i) {
        float res = criteria(m->values[i], m->nCols);
        temp[i] = res;
    }

    int min_idx;
    for (int j = 0; j < m->nRows; ++j) {
        min_idx = j;
        for (int i = j + 1; i < m->nRows; ++i) {
            if (temp[i] < temp[min_idx]) {
                min_idx = i;
            }
        }

        if (min_idx != j) {
            temp_pepe = temp[j];
            temp[j] = temp[min_idx];
            temp[min_idx] = temp_pepe;

            swapRows(*m, j, min_idx);
        }
    }
}

void sortByDistances(matrix *m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

void task9(matrix *m) {
    sortByDistances(m);
}

void test_task9() {
    int n = 4;
    int m = 4;
    matrix mat = createMatrixFromArray((int[]) {67, 4, 2, 6,
                                                1, 9, 9, 6,
                                                9, 9, 9, 9,
                                                84, 1, -39, 1
    }, m, n);
    matrix exp_res = createMatrixFromArray((int[]) {1, 9, 9, 6,
                                                    9, 9, 9, 9,
                                                    67, 4, 2, 6,
                                                    84, 1, -39, 1
    }, m, n);

    task9(&mat);

    assert(areTwoMatricesEqual(&mat, &exp_res));
    freeMemMatrix(&mat);
    freeMemMatrix(&exp_res);
}

int cmp_long_long(const void *pa, const void *pb) {
    if (*(long long int *) pa - *(long long int *) pb < 0)
        return -1;

    if (*(long long int *) pa - *(long long int *) pb > 0)
        return 1;

    return 0;
}

int countNUnique(long long *a, int n) {
    int count = 0;
    bool is_uniq = false;
    for (int i = 0; i < n - 1; ++i) {
        if (!is_uniq && a[i] == a[i + 1]) {
            count += 1;
            is_uniq = true;
        } else
            is_uniq = false;
    }

    return count;
}

int countEqClassesByRowsSum(matrix m) {
    long long temp[m.nRows];
    for (int i = 0; i < m.nRows; ++i) {
        temp[i] = 0;
        for (int j = 0; j < m.nCols; ++j)
            temp[i] += m.values[i][j];
    }

    qsort(temp, m.nRows, sizeof(long long int), cmp_long_long);

    return countNUnique(temp, m.nRows);
}

int task10(matrix m) {
    return countEqClassesByRowsSum(m);
}

void test_task10() {
    matrix m = createMatrixFromArray((int[]) {7, 1,
                                              2, 7,
                                              5, 4,
                                              4, 3,
                                              1, 6,
                                              8, 0
    }, 6, 2);

    assert(task10(m) == 3);
    freeMemMatrix(&m);
}

int getNSpecialElement(matrix m) {
    int max, sum;
    int count = 0;
    for (int i = 0; i < m.nCols; ++i) {
        max = m.values[0][i];
        sum = max;
        for (int j = 1; j < m.nRows; ++j) {
            max = max > m.values[j][i] ?
                  max : m.values[j][i];
            sum += m.values[j][i];
        }

        sum -= max;
        count = sum < max ? count + 1 : count;
    }

    return count;
}

int task11(matrix m) {
    return getNSpecialElement(m);
}

void test_task11() {
    matrix m = createMatrixFromArray((int[]) {3, 5, 5, 4,
                                              2, 3, 6, 7,
                                              12, 2, 1, 2},
                                     3, 4);

    assert(task11(m) == 2);
    freeMemMatrix(&m);
}

position getLeftMin(matrix m) {
    return getMinValuePos(m);
}

void swapPenultimateRow(matrix *m, int n) {
    for (int i = m->nRows - 1; i >= 0; i--)
        m->values[m->nRows - 2][i] = m->values[i][n];
}

void task12(matrix m) {
    swapPenultimateRow(&m, getLeftMin(m).colIndex);
}

void test_task12() {
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 1},
                                     3, 3);
    matrix exp_res = createMatrixFromArray((int[]) {1, 2, 3,
                                                    1, 4, 7,
                                                    7, 8, 1},
                                           3, 3);

    task12(m);

    assert(areTwoMatricesEqual(&m, &exp_res));
    freeMemMatrix(&m);
    freeMemMatrix(&exp_res);
}

bool isNonDescendingSorted(int *a, int n) {
    for (int i = 0; i < n - 1; ++i)
        if (a[i] > a[i + 1])
            return false;

    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; ++i)
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;

    return true;
}

void test() {
    test_task1();
    test_task2();
    test_task3();
    test_task4();
    test_task5();
    test_task6();
    test_task7();
    test_task8();
    test_task9();
    test_task10();
    test_task11();
    test_task12();
}

int main() {
    test();

    return 0;
}
