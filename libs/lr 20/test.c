#include <stdio.h>
#include "lr20.c"
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <signal.h>


void test_1(){
    int n = 3;
    matrix got = getMemMatrix(n, n);
    matrixFillingZeros(&got, n, n);

    int countRequests = 2;
    int firstRequest[4] = {1, 1, 2, 2};
    int secondRequest[4] = {0, 0, 1, 1};
    int *requests[2] = {firstRequest, secondRequest};

    task_1(&got, countRequests, requests);

    matrix expected = createMatrixFromArray(
            (int[]) {
                    1, 1, 0,
                    1, 2, 1,
                    0, 1, 1
            }, 3, 3
    );

    assert(areTwoMatricesEqual(&got, &expected));
}

void test_2(){
    int r = 4;
    int c = 3;
    matrix start = createMatrixFromArray(
            (int[]) {
                    0, 1, 0,
                    0, 0, 1,
                    1, 1, 1,
                    0, 0, 0
            }, 4, 3
    );

    matrix got = getMemMatrix(r, c);
    task_2(start, &got, r, c);

    matrix expected = createMatrixFromArray(
            (int[]) {
                    0, 0, 0,
                    1, 0, 1,
                    0, 1, 1,
                    0, 1, 0
            }, 4, 3
    );

    assert(areTwoMatricesEqual(&got, &expected));
}

void test_3(){
    int n = 3;
    matrix got = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 35, 45,
                    15, 25, 35
            }, 3, 3
    );

    task_3(&got, n);

    matrix expected = createMatrixFromArray(
            (int[]) {
                    10, 20, 30,
                    25, 25, 45,
                    15, 25, 35
            }, 3, 3
    );

    assert(areTwoMatricesEqual(&got, &expected));
}

/*void test_4(){
    int size = 1;
    domain array[1] = {{9001, "discuss.codeforces.com"},};

    task_4(array, size);

    printf("\n");
}*/

void test_5(){
    int rows1 = 3;
    int cols1 = 3;

    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 1,
                    1, 1, 0,
                    1, 1, 0
            }, 3, 3
    );

    int result1 = 0;

    task_5(m1, rows1, cols1, &result1);

    assert(result1 == 13);
}

void test_6(){
    char s[10] = "IIIDIDDD";
    int len = 8;
    char got[10];
    int resLen;

    task_6(s, len, got, &resLen);

    char expected[10] = "123549876";

    assert(strcmp(got, expected) == 0);
}

void test_7(){
    int array[6] = {3, 2, 1, 6, 0, 5};
    int lengthArray = 6;
    task_7(array, lengthArray);
}

void test_8(){
    char s[4] = "abc";
    int lenS = 3;
    int indexes[3] = {0, 1, 2};
    char got[4];

    task_8(s, lenS, indexes, got);

    char expected[4] = "abc";

    assert(strcmp(got, expected) == 0);
}

void test_9(){
    int numsArray[5] = {2, 4, 1, 3, 5};
    int lengthArray = 5;
    int controlNum = 3;
    char *firstFileName = "C:\\Users\\wwwri\\files\\lr20\\original_task_9.txt";
    char *secondFileName = "C:\\Users\\wwwri\\files\\lr20\\converted_task_9.txt";

    vector v = createVector(10);

    task_9(numsArray, lengthArray, controlNum, firstFileName, secondFileName, &v);

    int expectedLength = 2;
    int expectedArrayNums[2] = {2, 1};

    assert(expectedLength == v.size);

    for (int i = 0; i < expectedLength; i++){
        assert(v.data[i] == expectedArrayNums[i]);
    }
}

void test_10(){
    char *fileName = "C:\\Users\\wwwri\\files\\lr20\\original_task_10.txt";
    int countOutputLines = 1;
    char text[200] = "abc\nABC\ndef\nDEF";

    task_10(fileName, countOutputLines, text);
}

int main(){
SetConsoleOutputCP(CP_UTF8);
    test_1();
    test_2();
    test_3();
    //test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();

    return 0;
}