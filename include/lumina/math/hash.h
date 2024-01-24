/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_HASH_H
#define _LUMINA_HASH_H

#include "lumina/_lumina.h"


/**
 * @file math/hash.h
 * 
 * @brief Various hashing functions.
 */


#define LM_FNV_PRIME 1099511628211ULL
#define LM_FNV_BASIS 14695981039346656037ULL

/**
 * @brief FNV-1a hash.
 * 
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 * 
 * @param str Zero-terminated string to hash
 * @return lm_uint64
 */
static inline lm_uint64 lm_fnv1a(const char *str) {
    lm_uint64 hash = LM_FNV_BASIS;

    for (size_t i = 0; str[i] != '\0'; i++) {
        hash ^= (lm_uint64)str[i];
        hash *= LM_FNV_PRIME;
    }

    return hash;
}


#endif