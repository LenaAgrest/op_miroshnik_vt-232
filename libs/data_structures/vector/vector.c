#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector createVector(size_t n) {
    vector v1;
    v1.data = (int *) malloc(n * sizeof(int));
    v1.size = 0;
    v1.capacity = n;

    if (v1.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for the vector\n");
        exit(1);
    }
    return v1;
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