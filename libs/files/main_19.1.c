#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "task_1.c"

void test_task_1() {
    const char *str1 = "C:/Users/%userprofile%/OneDrive/Рабочий стол/2 семестр/оп/lab 14/op_miroshnik_vt-232/libs/files/converted_task_1.txt";
    const char *str2 = "C:/Users/%userprofile%/OneDrive/Рабочий стол/2 семестр/оп/lab 14/op_miroshnik_vt-232/libs/files/for_verification_task_1.txt";
    int r = task_1(str1);

    if (r == 0){
        assertTXT(str1, str2);
    }
}

int main(){
    SetConsoleOutputCP(CP_UTF8);

    test_task_1();
}