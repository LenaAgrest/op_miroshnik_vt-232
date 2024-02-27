#include "matrix.c"
#include <assert.h>

void testFreeMemMatrix() {
    // Создаем матрицу для теста
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

    testMatrix.nRows = 2;
    testMatrix.nCols = 3;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    int counter = 1;
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = counter++;
        }
    }

    inputMatrix(&testMatrix);

    assert(testMatrix.nRows == 2);
    assert(testMatrix.nCols == 3);

    int expectedValue = 1;
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            assert(testMatrix.values[i][j] == expectedValue++);
        }
    }
}

void testOutputMatrix() {
    // Создаем матрицу для теста
    matrix testMatrix;
    testMatrix.nRows = 2;
    testMatrix.nCols = 3;

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


void test(){

void testFreeMemMatrix();
void testFreeMemMatrices();
void testInputMatrix();
void testOutputMatrix();
void testOutputMatrices();
}

int main(){
test();

return 0;
}