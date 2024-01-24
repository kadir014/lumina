/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_ARRAY_H
#define _LUMINA_ARRAY_H

#include "lumina/_lumina.h"


/**
 * @file collections/array.h
 * 
 * @brief Type-generic dynamically growing array implementation.
 */


/**
 * @brief Type-generic dynamically growing array implementation.
 */
typedef struct {
    size_t size; /**< Length of the array. */
    size_t max; /**< Maximum size the array ever reached, this is basically the size of the array on HEAP. */
    void **data; /**< Array of void pointers. */
} lmArray;

/**
 * @brief Create new array.
 * 
 * @return lmArray *
 */
lmArray *lmArray_new();

/**
 * @brief Free array.
 * 
 * @param array Array to free
 */
void lmArray_free(lmArray *array);

/**
 * @brief Free each element of array.
 * 
 * @param array Array
 * @param free_func Free function
 */
void lmArray_free_each(lmArray *array, void (free_func)(void *));

/**
 * @brief Add new element to array.
 * 
 * @param array Array to append to
 * @param elem Void pointer to element
 */
void lmArray_add(lmArray *array, void *elem);

/**
 * @brief Remove element by index from array and return the element. Returns `NULL` if failed.
 * 
 * @note The array is not sorted after removal, meaning the array gets slightly randomized every remove call.
 * 
 * @param array Array
 * @param index Index of element to remove
 * @return void *
 */
void *lmArray_pop(lmArray *array, size_t index);

/**
 * @brief Remove element from array and return the index. Returns `-1` if failed.
 * 
 * @note The array is not sorted after removal, meaning the array gets slightly randomized every remove call.
 * 
 * @param array Array
 * @param elem Element to remove
 * @return size_t
 */
size_t lmArray_remove(lmArray *array, void *elem);

/**
 * @brief Clear the array.
 * 
 * Elements are not freed if `NULL` is passed as freeing function.
 * 
 * @param array Array
 * @param free_func Free function
 */
void lmArray_clear(lmArray *array, void (free_func)(void *));


#endif