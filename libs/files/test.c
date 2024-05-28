#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "task.c"

void test_task_1() {
    const char *str1 = "C:\\Users\\wwwri\\files\\converted_task_1.txt";
    const char *str2 = "C:\\Users\\wwwri\\files\\for_verification_task_1.txt";
    int r = task_1(str1);
    printf("1:");

    if (r == 0){
        assertTXT(str1, str2);

    }
}
void test_task_2() {
    const char *str1 = "C:\\Users\\wwwri\\files\\converted_task_2.txt";
    const char *str2 = "C:\\Users\\wwwri\\files\\for_verification_task_2.txt";
    int r = task_2(str1);
    printf("2:");

    if (r == 0){
        assertTXT(str1, str2);

    }
}
int main(){
    SetConsoleOutputCP(CP_UTF8);

    test_task_1();
    test_task_2();
}