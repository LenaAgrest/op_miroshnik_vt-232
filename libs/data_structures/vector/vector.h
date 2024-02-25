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

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity > v->capacity) {
        int *newData = (int *) realloc(v->data, newCapacity * sizeof(int));
        if (newData == NULL) {
            fprintf(stderr, "Failed to reallocate memory for the vector\n");
            exit(1);
        }
        v->data = newData;
        v->capacity = newCapacity;
    } else if (newCapacity == 0) {
        v->data = NULL;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}

void exceptBadAlloc(){
    fprintf(stderr, "bad alloc");
    exit(1);
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    int *new_data = (int *) realloc(v->data, v->size * sizeof(int));
}

void deleteVector(vector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}