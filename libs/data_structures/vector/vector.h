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

bool isEmpty(vector *v) {
    return (v->size == 0);
}

bool isFull(vector *v) {
    return (v->size == v->capacity);
}

int getVectorValue(vector *v, size_t i) {
    return (v->data[i]);
}

void pushBack(vector *v, int x) {
    if (v->capacity == 0) {
        reserve(v, 1);
    } else if (v->capacity == v->size) {
        reserve(v, v->capacity * 2);
    }
    v->data[v->size] = x;
    v->size++;
    printf("");
}

void popBack(vector *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error, vector is empty!");
        exit(1);
    }

    v->size--;

    if (v->size < v->capacity / 2) {
        reserve(v, v->capacity / 2);
    }
}

int *atVector(vector *v, size_t index) {
    if (index >= v->size) {
        fprintf(stderr, "IndexError: a[index] is not exists");
        exit(1);
    } else{
        return &(v->data[index]);
    }
}

int* back(vector *v) {
    return &(v->data[v->size - 1]);
}

int* front(vector *v) {
    return &(v->data[0]);
}