typedef struct matrix {
int **values; // элементы матрицы
int nRows; // количество рядов
int nCols; // количество столбцов
} matrix;
typedef struct position {
int rowIndex;
int colIndex;
} position;

matrix getMemMatrix(int nRows, int nCols);

matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols);

void freeMemMatrix(matrix *m);

void freeMemMatrices(matrix *ms, int nMatrices);

void inputMatrix(matrix *m);

void outputMatrix(matrix m);

void outputMatrices(matrix *ms, int nMatrices);

void swapRows(matrix m, int i1, int i2);

void swapColumns(matrix m, int j1, int j2);

int compareRows(int *row1, int *row2, int nCols);

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int));

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int *, int));