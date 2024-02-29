#include "matrix.c"
#include <assert.h>

void testFreeMemMatrix() {
    matrix testMatrix;
    testMatrix.nRows = 2;
    testMatrix.nCols = 3;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    freeMemMatrix(&testMatrix);

    assert(testMatrix.values == NULL);
    assert(testMatrix.nRows == 0);
    assert(testMatrix.nCols == 0);
}

void testFreeMemMatrices() {
    matrix *testMatrices = (matrix *)malloc(sizeof(matrix) * 2);
    for (int i = 0; i < 2; i++) {
        testMatrices[i].nRows = 2;
        testMatrices[i].nCols = 3;

        testMatrices[i].values = (int **)malloc(sizeof(int *) * testMatrices[i].nRows);
        for (int j = 0; j < testMatrices[i].nRows; j++) {
            testMatrices[i].values[j] = (int *)malloc(sizeof(int) * testMatrices[i].nCols);
        }
    }
    freeMemMatrices(testMatrices, 2);
    assert(testMatrices == NULL);
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

    printf("Test with valid output:\n");
    outputMatrix(testMatrix);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);

    printf("\nTest with invalid output (negative sizes):\n");
    matrix invalidMatrix;
    invalidMatrix.nRows = -1;
    invalidMatrix.nCols = -1;
    invalidMatrix.values = NULL;

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

void testInsertionSortRowsMatrixByRowCriteria() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

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

    insertionSortRowsMatrixByRowCriteria(testMatrix, getSum);

    assert(testMatrix.values[0][0] == 1);
    assert(testMatrix.values[0][1] == 2);
    assert(testMatrix.values[1][0] == 3);
    assert(testMatrix.values[1][1] == 4);
    assert(testMatrix.values[2][0] == 5);
    assert(testMatrix.values[2][1] == 6);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}
void testSelectionSortColsMatrixByColCriteria() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 2;

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

    selectionSortColsMatrixByColCriteria(testMatrix, getSum);

    assert(testMatrix.values[0][0] == 1);
    assert(testMatrix.values[1][0] == 3);
    assert(testMatrix.values[2][0] == 5);
    assert(testMatrix.values[0][1] == 2);
    assert(testMatrix.values[1][1] == 4);
    assert(testMatrix.values[2][1] == 6);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}

void testIsSquareMatrix() {
    matrix squareMatrix;
    squareMatrix.nRows = 3;
    squareMatrix.nCols = 3;

    squareMatrix.values = (int **)malloc(sizeof(int *) * squareMatrix.nRows);
    for (int i = 0; i < squareMatrix.nRows; i++) {
        squareMatrix.values[i] = (int *)malloc(sizeof(int) * squareMatrix.nCols);
    }

    assert(isSquareMatrix(&squareMatrix) == true);

    for (int i = 0; i < squareMatrix.nRows; i++) {
        free(squareMatrix.values[i]);
    }
    free(squareMatrix.values);

    matrix rectangularMatrix;
    rectangularMatrix.nRows = 3;
    rectangularMatrix.nCols = 2;

    rectangularMatrix.values = (int **)malloc(sizeof(int *) * rectangularMatrix.nRows);
    for (int i = 0; i < rectangularMatrix.nRows; i++) {
        rectangularMatrix.values[i] = (int *)malloc(sizeof(int) * rectangularMatrix.nCols);
    }

    assert(isSquareMatrix(&rectangularMatrix) == false);

    for (int i = 0; i < rectangularMatrix.nRows; i++) {
        free(rectangularMatrix.values[i]);
    }
    free(rectangularMatrix.values);
}

void testAreTwoMatricesEqual() {
    matrix matrix1;
    matrix1.nRows = 2;
    matrix1.nCols = 2;

    matrix1.values = (int **)malloc(sizeof(int *) * matrix1.nRows);
    for (int i = 0; i < matrix1.nRows; i++) {
        matrix1.values[i] = (int *)malloc(sizeof(int) * matrix1.nCols);
    }
    matrix matrix2;
    matrix2.nRows = 2;
    matrix2.nCols = 2;
    matrix2.values = (int **)malloc(sizeof(int *) * matrix2.nRows);
    for (int i = 0; i < matrix2.nRows; i++) {
        matrix2.values[i] = (int *)malloc(sizeof(int) * matrix2.nCols);
    }

    matrix1.values[0][0] = 1;
    matrix1.values[0][1] = 2;
    matrix1.values[1][0] = 3;
    matrix1.values[1][1] = 4;
    matrix2.values[0][0] = 1;
    matrix2.values[0][1] = 2;
    matrix2.values[1][0] = 3;
    matrix2.values[1][1] = 4;

    assert(areTwoMatricesEqual(&matrix1, &matrix2) == true);

    matrix2.values[1][1] = 5;

    assert(areTwoMatricesEqual(&matrix1, &matrix2) == false);

    for (int i = 0; i < matrix1.nRows; i++) {
        free(matrix1.values[i]);
    }
    free(matrix1.values);

    for (int i = 0; i < matrix2.nRows; i++) {
        free(matrix2.values[i]);
    }
    free(matrix2.values);
}

void testIsEMatrix() {
    matrix eMatrix;
    eMatrix.nRows = 3;
    eMatrix.nCols = 3;

    eMatrix.values = (int **)malloc(sizeof(int *) * eMatrix.nRows);
    for (int i = 0; i < eMatrix.nRows; i++) {
        eMatrix.values[i] = (int *)malloc(sizeof(int) * eMatrix.nCols);
    }

    for (int i = 0; i < eMatrix.nRows; i++) {
        for (int j = 0; j < eMatrix.nCols; j++) {
            eMatrix.values[i][j] = (i == j) ? 1 : 0;
        }
    }

    assert(isEMatrix(&eMatrix) == true);
    eMatrix.values[1][1] = 2;
    assert(isEMatrix(&eMatrix) == false);

    for (int i = 0; i < eMatrix.nRows; i++) {
        free(eMatrix.values[i]);
    }
    free(eMatrix.values);
}

void testIsSymmetricMatrix() {
    matrix symmetricMatrix;
    symmetricMatrix.nRows = 3;
    symmetricMatrix.nCols = 3;

    symmetricMatrix.values = (int **)malloc(sizeof(int *) * symmetricMatrix.nRows);
    for (int i = 0; i < symmetricMatrix.nRows; i++) {
        symmetricMatrix.values[i] = (int *)malloc(sizeof(int) * symmetricMatrix.nCols);
    }

    for (int i = 0; i < symmetricMatrix.nRows; i++) {
        for (int j = 0; j < symmetricMatrix.nCols; j++) {
            symmetricMatrix.values[i][j] = i + j;
        }
    }
    assert(isSymmetricMatrix(&symmetricMatrix) == true);
    symmetricMatrix.values[1][2] = 10;
    assert(isSymmetricMatrix(&symmetricMatrix) == false);

    for (int i = 0; i < symmetricMatrix.nRows; i++) {
        free(symmetricMatrix.values[i]);
    }
    free(symmetricMatrix.values);
}

void testTransposeSquareMatrix() {
    matrix squareMatrix;
    squareMatrix.nRows = 3;
    squareMatrix.nCols = 3;

    squareMatrix.values = (int **)malloc(sizeof(int *) * squareMatrix.nRows);
    for (int i = 0; i < squareMatrix.nRows; i++) {
        squareMatrix.values[i] = (int *)malloc(sizeof(int) * squareMatrix.nCols);
    }

    for (int i = 0; i < squareMatrix.nRows; i++) {
        for (int j = 0; j < squareMatrix.nCols; j++) {
            squareMatrix.values[i][j] = i * squareMatrix.nCols + j + 1;
        }
    }
    transposeSquareMatrix(&squareMatrix);

    assert(squareMatrix.values[0][0] == 1);
    assert(squareMatrix.values[1][0] == 2);
    assert(squareMatrix.values[2][0] == 3);
    assert(squareMatrix.values[0][1] == 4);
    assert(squareMatrix.values[1][1] == 5);
    assert(squareMatrix.values[2][1] == 6);
    assert(squareMatrix.values[0][2] == 7);
    assert(squareMatrix.values[1][2] == 8);
    assert(squareMatrix.values[2][2] == 9);

    for (int i = 0; i < squareMatrix.nRows; i++) {
        free(squareMatrix.values[i]);
    }
    free(squareMatrix.values);
}

void testTransposeMatrix() {
    matrix testMatrix;
    testMatrix.nRows = 2;
    testMatrix.nCols = 3;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }
    for (int i = 0; i < testMatrix.nRows; i++) {
        for (int j = 0; j < testMatrix.nCols; j++) {
            testMatrix.values[i][j] = i * testMatrix.nCols + j + 1;
        }
    }
    transposeMatrix(&testMatrix);

    assert(testMatrix.values[0][0] == 1);
    assert(testMatrix.values[0][1] == 4);
    assert(testMatrix.values[1][0] == 2);
    assert(testMatrix.values[1][1] == 5);
    assert(testMatrix.values[2][0] == 3);
    assert(testMatrix.values[2][1] == 6);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}

void testGetMinValuePos() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 3;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    testMatrix.values[0][0] = 5;
    testMatrix.values[0][1] = 8;
    testMatrix.values[0][2] = 3;
    testMatrix.values[1][0] = 2;
    testMatrix.values[1][1] = 9;
    testMatrix.values[1][2] = 1;
    testMatrix.values[2][0] = 7;
    testMatrix.values[2][1] = 4;
    testMatrix.values[2][2] = 6;

    position minPos = getMinValuePos(testMatrix);

    assert(minPos.rowIndex == 1);
    assert(minPos.colIndex == 2);
    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}

void testGetMaxValuePos() {
    matrix testMatrix;
    testMatrix.nRows = 3;
    testMatrix.nCols = 3;

    testMatrix.values = (int **)malloc(sizeof(int *) * testMatrix.nRows);
    for (int i = 0; i < testMatrix.nRows; i++) {
        testMatrix.values[i] = (int *)malloc(sizeof(int) * testMatrix.nCols);
    }

    testMatrix.values[0][0] = 5;
    testMatrix.values[0][1] = 8;
    testMatrix.values[0][2] = 3;
    testMatrix.values[1][0] = 2;
    testMatrix.values[1][1] = 9;
    testMatrix.values[1][2] = 1;
    testMatrix.values[2][0] = 7;
    testMatrix.values[2][1] = 4;
    testMatrix.values[2][2] = 6;

    position maxPos = getMaxValuePos(testMatrix);
    assert(maxPos.rowIndex == 1);
    assert(maxPos.colIndex == 1);

    for (int i = 0; i < testMatrix.nRows; i++) {
        free(testMatrix.values[i]);
    }
    free(testMatrix.values);
}

void testCreateMatrixFromArray() {
    int array[] = {1, 2, 3, 4, 5, 6};

    matrix testMatrix = createMatrixFromArray(array, 2, 3);

    assert(testMatrix.nRows == 2);
    assert(testMatrix.nCols == 3);
    assert(testMatrix.values[0][0] == 1);
    assert(testMatrix.values[0][1] == 2);
    assert(testMatrix.values[0][2] == 3);
    assert(testMatrix.values[1][0] == 4);
    assert(testMatrix.values[1][1] == 5);
    assert(testMatrix.values[1][2] == 6);

    freeMemMatrix(&testMatrix);
}

void testCreateArrayOfMatrixFromArray() {
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    size_t nMatrices = 2;
    size_t nRows = 3;
    size_t nCols = 2;

    matrix *resultMatrices = createArrayOfMatrixFromArray(values, nMatrices, nRows, nCols);

    assert(resultMatrices[0].values[0][0] == 1);
    assert(resultMatrices[0].values[0][1] == 2);
    assert(resultMatrices[0].values[1][0] == 3);
    assert(resultMatrices[0].values[1][1] == 4);
    assert(resultMatrices[0].values[2][0] == 5);
    assert(resultMatrices[0].values[2][1] == 6);

    assert(resultMatrices[1].values[0][0] == 7);
    assert(resultMatrices[1].values[0][1] == 8);
    assert(resultMatrices[1].values[1][0] == 9);
    assert(resultMatrices[1].values[1][1] == 10);
    assert(resultMatrices[1].values[2][0] == 11);
    assert(resultMatrices[1].values[2][1] == 12);

    freeMemMatrices(resultMatrices, nMatrices);
}

int main(){
void testFreeMemMatrix();
void testFreeMemMatrices();
void testInputMatrix();
void testOutputMatrix();
void testOutputMatrices();
void testSwapRows();
void testSwapColumns();
void testInsertionSortRowsMatrixByRowCriteria();
void testIsSquareMatrix();
void testAreTwoMatricesEqual();
void testTransposeSquareMatrix();
void testTransposeMatrix();
void testGetMinValuePos();
void testGetMaxValuePos();
void testCreateMatrixFromArray();
void testCreateArrayOfMatrixFromArray();

return 0;
}