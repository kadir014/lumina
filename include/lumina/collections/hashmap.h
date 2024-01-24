/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_HASHMAP_H
#define _LUMINA_HASHMAP_H

#include "lumina/_lumina.h"


/**
 * @file collections/hashmap.h
 * 
 * @brief Hash map implementation.
 */


typedef struct {
    lm_uint64 hash: 48;
    lm_uint64 dib: 16;
} lmHashMapBucket;


/**
 * @brief Hash map.
 */
typedef struct {
    size_t elsize;
    size_t cap;
    lm_uint64 (*hash_func)(void *item);

    size_t count;
    bool oom;

    size_t bucketsz;
    size_t nbuckets;
    size_t mask;
    size_t growat;
    size_t shrinkat;
    lm_uint8 growpower;

    void *buckets;
    void *spare;
    void *edata;
} lmHashMap;

/**
 * @brief Create new hash map.
 * 
 * @param item_size Size of the entries stored in the hash map
 * @param cap Starting capacity of the hash map
 * @param hash_func Hash function callback
 * @return lmHashMap * 
 */
lmHashMap *lmHashMap_new(
    size_t item_size,
    size_t cap,
    lm_uint64 (*hash_func)(void *item)
);

/**
 * @brief Free hash map.
 * 
 * @param hashmap Hash map to free
 */
void lmHashMap_free(lmHashMap *hashmap);

/**
 * @brief Remove all entries in the hash map.
 * 
 * @param hashmap Hash map to clear
 */
void lmHashMap_clear(lmHashMap *hashmap);

/**
 * @brief Get entry from key.
 * 
 * @param hashmap Hash map
 * @param key Key
 * @return void * 
 */
void *lmHashMap_get(lmHashMap *map, void *item);

/**
 * @brief Set entry.
 * 
 * @param hashmap Hash map
 * @param item Entry item
 */
void *lmHashMap_set(lmHashMap *map, void *item);

/**
 * @brief Remove entry from hash map with key.
 * 
 * If removed during iteration, set counter back to 0.
 * 
 * @param hashmap Hash map
 * @param key Key
 * @return void *
 */
void *lmHashMap_remove(lmHashMap *hashmap, void *key);

/**
 * @brief Iterate over hash map entries.
 * 
 * @param hashmap Hash map
 * @param index Pointer to index counter
 * @param item Pointer to entry pointer
 * @return bool
 */
bool lmHashMap_iter(lmHashMap *hashmap, size_t *index, void **item);


#endif