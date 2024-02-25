#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vector.h"
#include "vectorVoid.h"

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid v1;
    v1.data = (int *) malloc(n * sizeof(int));
    v1.size = 0;
    v1.capacity = n;
    v1.baseTypeSize = baseTypeSize;

    if (v1.data == NULL) {
        fprintf(stderr, "Failed to allocate memory for the vector\n");
        exit(1);
    }
    return v1;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    if (newCapacity > v->capacity) {
        int *newData = (int *) realloc(v->data, newCapacity * v->baseTypeSize);
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

void clearV(vectorVoid *v) {
    v->size = 0;
}

void shrinkToFitV(vectorVoid *v) {
    int *new_data = (int *) realloc(v->data, v->size * v->baseTypeSize);
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmptyV(vectorVoid *v) {
    return (v->size == 0);
}

bool isFullV(vectorVoid *v) {
    return (v->size == v->capacity);
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}


void pushBackV(vectorVoid *v, void *source) {
    if (v->capacity == 0) {
        reserve((vector *) v, 1);
    } else if (v->capacity == v->size) {
        reserve((vector *) v, v->capacity * 2);
    }
    setVectorValueV(v, v->size, source);
    v->size++;
}

void popBackV(vectorVoid *v) {
    if (v->size == 0) {
        fprintf(stderr, "Error, vector is empty!");
        exit(1);
    }

    v->size--;

    if (v->size < v->capacity / 2) {
        reserve((vector *) v, v->capacity / 2);
    }
}

