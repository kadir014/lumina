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


/**
 * @brief Cantor pairing function for unsigned 64-bit integers.
 * 
 * @param x First number
 * @param y Second number
 * @return lm_uint64 
 */
static inline lm_uint64 lm_u64cantor(lm_uint64 x, lm_uint64 y) {
    // https://en.wikipedia.org/wiki/Pairing_function#Cantor_pairing_function
    // π(x, y) = ((x + y) * (x + y + 1) / 2) + y

    lm_uint64 sum = x + y;
    return ((sum * (sum + 1)) / 2) + y;
}


#define LM_FNV_PRIME 1099511628211ULL
#define LM_FNV_BASIS 14695981039346656037ULL

/**
 * @brief FNV-1a hash.
 * 
 * @param str Zero-terminated string to hash
 * @return lm_uint64
 */
static inline lm_uint64 lm_fnv1a(const char *str) {
    // https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
    
    lm_uint64 hash = LM_FNV_BASIS;

    for (size_t i = 0; str[i] != '\0'; i++) {
        hash ^= (lm_uint64)str[i];
        hash *= LM_FNV_PRIME;
    }

    return hash;
}


#endif