#include "stdio.h"
#include <stdbool.h>

typedef struct vector {
int *data; // указатель на элементы вектора
size_t size; // размер вектора
size_t capacity; // вместимость вектора
} vector;

vector createVector(size_t n){
    vector new;

    if (n == 0){
        new.data = NULL;
    } else {
        new.data = (int *) malloc(n * sizeof(int));
        if (!new.data){
            exceptBadAlloc();
        }
    }

    new.size = 0;
    new.capacity = n;

    return new;
}

void exceptBadAlloc(){
    fprintf(stderr, "bad alloc");
    exit(1);
}