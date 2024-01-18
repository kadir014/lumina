/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/collections/array.h"


/**
 * @file array.c
 * 
 * @brief Type-generic dynamically growing array implementation.
 */


lmArray *lmArray_new() {
    lmArray *array = LM_NEW(lmArray);
    if (!array) return NULL;

    array->size = 0;
    array->max = 0;
    array->data = (void **)malloc(sizeof(void *));
    if (!array->data) {
        free(array);
        return NULL;
    }

    return array;
}

void lmArray_free(lmArray *array) {
    free(array->data);
    array->data = NULL;
    array->size = 0;
    free(array);
}

void lmArray_free_each(lmArray *array, void (free_func)(void *)) {
    for (size_t i = 0; i < array->size; i++)
        free_func(array->data[i]);
}

void lmArray_add(lmArray *array, void *elem) {
    // Only reallocate when max capacity is reached
    if (array->size == array->max) {
        array->size++;
        array->max++;
        array->data = (void **)realloc(array->data, array->size * sizeof(void *));
    }
    else {
        array->size++;
    }

    array->data[array->size - 1] = elem;
}

void *lmArray_pop(lmArray *array, size_t index) {
    for (size_t i = 0; i < array->size; i++) {
        if (i == index) {
            array->size--;
            void *elem = array->data[i];

            array->data[i] = array->data[array->size];
            array->data[array->size] = NULL;

            return elem;
        }
    }

    return NULL;
}

size_t lmArray_remove(lmArray *array, void *elem) {
    for (size_t i = 0; i < array->size; i++) {
        if (array->data[i] == elem) {
            array->size--;

            array->data[i] = array->data[array->size];
            array->data[array->size] = NULL;

            return i;
        }
    }

    return -1;
}

void lmArray_clear(lmArray *array, void (free_func)(void *)) {
    /*
        We can set array->max to 0 and reallocate but
        not doing it might be more efficient for the developer
        since they will probably fill the array up again.
        Maybe a separate parameter for this?
    */

    if (array->size == 0) return;
   
    if (!free_func) {
        while (array->size > 0) {
            lmArray_pop(array, 0);
        }
    }

    else {
        while (array->size > 0) {
            free_func(lmArray_pop(array, 0));
        }
    }
}