#include "matrix.c"
#include <assert.h>

void testFreeMemMatrix() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = i * testMatrix.nCols + j + 1;
        }
    }

    freeMemMatrix(&testMatrix);

    for (int i = 0; i < testMatrix.nRows; i++) {
        assert(testMatrix.values[i] == NULL);
    }

    assert(testMatrix.nRows == 0);
    assert(testMatrix.nCols == 0);

    free(&testMatrix);
}

void testFreeMemMatrices() {
    int nMatrices = 3;
    matrix *testMatrices = (matrix *)malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        testMatrices[i].nRows = 2;
        testMatrices[i].nCols = 2;

        testMatrices[i].values = (int **)malloc(sizeof(int *) * testMatrices[i].nRows);
        for (int j = 0; j < testMatrices[i].nRows; j++) {
            testMatrices[i].values[j] = (int *)malloc(sizeof(int) * testMatrices[i].nCols);
        }

        for (int j = 0; j < testMatrices[i].nRows; j++) {
            for (int k = 0; k < testMatrices[i].nCols; k++) {
                testMatrices[i].values[j][k] = i * testMatrices[i].nCols + j * testMatrices[i].nCols + k + 1;
            }
        }
    }

    freeMemMatrices(testMatrices, nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        for (int j = 0; j < testMatrices[i].nRows; j++) {
            assert(testMatrices[i].values[j] == NULL);
        }
    }
    assert(testMatrices == NULL);

    printf("Test passed successfully.\n");
}

void testInputMatrix() {
    matrix testMatrix;

    printf("Test with valid input:\n");
    inputMatrix(&testMatrix);

    assert(testMatrix.nRows > 0);
    assert(testMatrix.nCols > 0);
    assert(testMatrix.values != NULL);

    printf("Entered matrix:\n");
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            printf("%d\t", testMatrix.values[i][j]);
        }
        printf("\n");
    }
}

void testOutputMatrix() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

    // Выделяем память для значений матрицы
    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    // Имитируем заполнение матрицы значениями
    int counter = 1;
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = counter++;
        }
    }

    printf("Test with valid output:\n");
    outputMatrix(testMatrix);

    // Очищаем память
    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);

    // Вызываем функцию вывода с некорректными значениями (негативные размеры)
    printf("\nTest with invalid output (negative sizes):\n");
    matrix invalidMatrix;
    invalidMatrix.nRows = -1;
    invalidMatrix.nCols = -1;
    invalidMatrix.values = NULL;

    // Должен произойти сбой с использованием assert
    outputMatrix(invalidMatrix);
}

void testOutputMatrices() {
    int nMatrices = 2;
    matrix *testMatrices = (matrix *)malloc(sizeof(matrix) * nMatrices);

    for (int i = 0; i < nMatrices; i++) {
        testMatrices[i].nRows = 2;
        testMatrices[i].nCols = 3;

        testMatrices[i].values = (int **)malloc(sizeof(int *) * testMatrices[i].nRows);
        for (int j = 0; j < testMatrices[i].nRows; j++) {
            testMatrices[i].values[j] = (int *)malloc(sizeof(int) * testMatrices[i].nCols);
        }

        int counter = 1;
        for (int j = 0; j < testMatrices[i].nRows; j++) {
            for (int k = 0; k < testMatrices[i].nCols; k++) {
                testMatrices[i].values[j][k] = counter++;
            }
        }
    }
}

void testSwapRows() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

    // Выделяем память для значений матрицы
    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    // Имитируем заполнение матрицы значениями
    int counter = 1;
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = counter++;
        }
    }

    printf("Test with valid indices:\n");
    swapRows(testMatrix, 0, 2);

    assert(testMatrix.values[0][0] == 5);
    assert(testMatrix.values[0][1] == 6);
    assert(testMatrix.values[2][0] == 1);
    assert(testMatrix.values[2][1] == 2);

    printf("\nTest with invalid indices (negative indices):\n");
    swapRows(testMatrix, -1, 2);

    printf("\nTest with invalid indices (indices exceeding matrix dimensions):\n");
    swapRows(testMatrix, 0, 4);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}

void testSwapColumns() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

    // Выделяем память для значений матрицы
    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    // Имитируем заполнение матрицы значениями
    int counter = 1;
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = counter++;
        }
    }

    printf("Test with valid indices:\n");
    swapColumns(testMatrix, 0, 1);

    assert(testMatrix.values[0][0] == 2);
    assert(testMatrix.values[0][1] == 1);
    assert(testMatrix.values[1][0] == 5);
    assert(testMatrix.values[1][1] == 4);
    assert(testMatrix.values[2][0] == 8);
    assert(testMatrix.values[2][1] == 7);

    printf("\nTest with invalid indices (negative indices):\n");
    swapColumns(testMatrix, -1, 1);

    printf("\nTest with invalid indices (indices exceeding matrix dimensions):\n");
    swapColumns(testMatrix, 0, 3);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}


void test(){

void testFreeMemMatrix();
void testFreeMemMatrices();
void testInputMatrix();
void testOutputMatrix();
void testOutputMatrices();
void testSwapRows();
void testSwapColumns();
}

int main(){
test();

return 0;
}