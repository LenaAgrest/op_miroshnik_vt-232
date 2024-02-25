#include <assert.h>
#include "test.h"
#include "vector.h"

void test_pushBack_emptyVector() {
    vector test_vector1 = createVector(0);

    pushBack(&test_vector1, 3);

    assert(test_vector1.data[0] == 3);
    assert(test_vector1.size == 1);
}

void test_pushBack_fullVector() {
    vector test_vector1 = createVector(1);

    pushBack(&test_vector1, 2);
    pushBack(&test_vector1, 4);

    assert(test_vector1.data[1] == 4);
    assert(test_vector1.size == 2);
}

void test_popBack_notEmptyVector() {
    vector test_vector1 = createVector(0);

    pushBack(&test_vector1, 10);

    assert(test_vector1.size == 1);

    popBack(&test_vector1);

    assert(test_vector1.size == 0);
    assert(test_vector1.capacity == 1);
}

void test_atVector_notEmptyVector() {
    vector test_vector1 = createVector(2);

    pushBack(&test_vector1, 1);
    pushBack(&test_vector1, 2);

    int first_element = *atVector(&test_vector1, 0);
    int second_element = *atVector(&test_vector1, 1);


    assert(first_element == 1);
    assert(second_element == 2);
}

void test_atVector_requestToLastElement() {
    vector test_vector1 = createVector(2);

    pushBack(&test_vector1, 1);
    pushBack(&test_vector1, 2);

    int last_element = *atVector(&test_vector1, 1);


    assert(last_element == 2);
}

void test_back_oneElementInVector() {
    vector test_vector1 = createVector(2);

    pushBack(&test_vector1, 1);
    pushBack(&test_vector1, 2);

    int last_element = *back(&test_vector1);


    assert(last_element == 2);
}

void test_front_oneElementInVector(){
    vector test_vector1 = createVector(2);

    pushBack(&test_vector1, 1);
    pushBack(&test_vector1, 2);

    int first_element = *front(&test_vector1);


    assert(first_element == 1);
};