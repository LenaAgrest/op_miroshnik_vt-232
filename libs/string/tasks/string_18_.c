#include "string_18_.h"
#include "string_.c"
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

char _stringBuffer[MAX_STRING_SIZE + 1];
BagOfWords _bag;
BagOfWords _bag2;

//находит конечный элемент строки
/*char* getEndOfString(char *s) {
    char *end = s;

    while (*end != '\0') {
        end++;
    }

    return end;
}*/

//удаляет из строки все пробельные символы
void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

//функция тестирования, которая даёт информацию о том, где именно произошла ошибка
/*void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line){
    if (strcmp(expected, got)){
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stderr, "%s - OK\n", funcName);
    }}*/
void removeExtraSpaces(char *s){
    char *begin = s;
    char *destination = begin;
    char last = *begin;

    while (*begin != '\0') {
        if (*begin != last || last != ' ') {
            *destination++ = *begin;
        }

        last = *begin++;
    }

    if (last == ' ') {
        destination--;
    }

    *destination = '\0';
}