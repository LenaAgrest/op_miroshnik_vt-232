#include <stdio.h>
#include "lr20.c"
#include <assert.h>
#include "../string/tasks/string_.h"

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

int main(){
    test_1();
    test_2();
    test_3();
    //test_4();
    test_5();
    test_6();

    return 0;
}