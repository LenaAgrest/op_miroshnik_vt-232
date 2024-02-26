#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector createVector(size_t n){
    vector new;

    if (n == 0){
        new.data = NULL;
    } else {
        new.data = (int *) malloc(n * sizeof(int));
        if (!new.data){
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }

    new.size = 0;
    new.capacity = n;

    return new;
}

void reserve(vector *v, size_t newCapacity){
    if (newCapacity == 0) {
        v->data = NULL;
    } else {
        v->data = (int *) realloc(v->data, sizeof(int) * newCapacity);
    }
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    if (v->size > newCapacity) {
        v->size = newCapacity;
    }
    v->capacity = newCapacity;
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v){
    reserve(v, v->size);
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

void pushBack(vector *v, int x){
    if (v->capacity == 0)
        reserve(v, 1);
    else if (v->size == v->capacity)
        reserve(v, v->size * 2);
    v->data[v->size++] = x;
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