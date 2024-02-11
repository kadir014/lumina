/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_RANDOM_H
#define _LUMINA_RANDOM_H

#include "lumina/_lumina.h"


/**
 * @file math/random.h
 * 
 * @brief Pseudo-random functions.
 */


/**
 * @brief Return random float in range [lower, higher).
 * 
 * @param lower Lower limit
 * @param higher Higher limit
 * @return float 
 */
static inline float frandom(float lower, float higher) {
    float normal = rand() / (float)RAND_MAX;
    return lower + normal * (higher - lower);
}

/**
 * @brief Return random double in range [lower, higher).
 * 
 * @param lower Lower limit
 * @param higher Higher limit
 * @return double 
 */
static inline double drandom(double lower, double higher) {
    double normal = rand() / (double)RAND_MAX;
    return lower + normal * (higher - lower);
}

/**
 * @brief Return random integer in range [lower, higher).
 * 
 * @param lower Lower limit
 * @param higher Higher limit
 * @return int 
 */
static inline int irandom(int lower, int higher) {
    return (rand() % (higher - lower + 1)) + lower;
}

/**
 * @brief Return random boolean.
 * 
 * @return bool
 */
static inline bool brandom() {
    return irandom(0, 1);
}


#endif