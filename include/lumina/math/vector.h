/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_VECTOR_H
#define _LUMINA_VECTOR_H

#include "lumina/_lumina.h"


/**
 * @file vector.h
 * 
 * @brief 2D vector math.
 */


/**
 * @brief 2D vector type.
 */
typedef struct {
    float x; /**< X component of the vector. */
    float y; /**< Y component of the vector. */
} lmVector2;


/**
 * @brief Initialize vector.
 * 
 * @param x X component
 * @param y Y component
 * @return lmVector2
*/
#define LM_VEC2(x, y) ((lmVector2){(x), (y)})


/**
 * @brief Constant zero vector.
 */
static const lmVector2 lmVector2_zero = {0.0, 0.0};


/**
 * @brief Check if two vectors are equal.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return bool
 */
static inline bool lmVector2_eq(lmVector2 a, lmVector2 b) {
    return (a.x == b.x && a.y == b.y);
}

/**
 * @brief Add two vectors.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_add(lmVector2 a, lmVector2 b) {
    return LM_VEC2(a.x + b.x, a.y + b.y);
}

/**
 * @brief Subtract two vectors.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_sub(lmVector2 a, lmVector2 b) {
    return LM_VEC2(a.x - b.x, a.y - b.y);
}

/**
 * @brief Multiply vector by scalar.
 * 
 * @param v Vector
 * @param s Scalar
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_mul(lmVector2 v, float s) {
    return LM_VEC2(v.x * s, v.y * s);
}

/**
 * @brief Divide vector by scalar.
 * 
 * @param v Vector
 * @param s Scalar
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_div(lmVector2 v, float s) {
    return LM_VEC2(v.x / s, v.y / s);
}

/**
 * @brief Negate a vector.
 * 
 * @param v Vector to negate
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_neg(lmVector2 v) {
    return LM_VEC2(-v.x, -v.y);
}

/**
 * @brief Rotate vector around the origin.
 * 
 * @param v Vector to rotate 
 * @param a Angle in radians
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_rotate(lmVector2 v, float a) {
    float c = cosf(a);
    float s = sinf(a);
    return LM_VEC2(c * v.x - s * v.y, s * v.x + c * v.y);
}

/**
 * @brief Perpendicular vector (+90 degrees).
 * 
 * @param v Vector
 * @param a Angle in radians
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_perp(lmVector2 v) {
    return LM_VEC2(-v.y, v.x);
}

/**
 * @brief Perpendicular vector (-90 degrees).
 * 
 * @param v Vector
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_perpr(lmVector2 v) {
    return LM_VEC2(v.y, -v.x);
}

/**
 * @brief Calculate squared length (magnitude) of a vector.
 * 
 * @param v Vector
 * @return float 
 */
static inline float lmVector2_len2(lmVector2 v) {
    return v.x * v.x + v.y * v.y;
}

/**
 * @brief Calculate length (magnitude) of a vector.
 * 
 * @param v Vector
 * @return float 
 */
static inline float lmVector2_len(lmVector2 v) {
    return sqrtf(lmVector2_len2(v));
}

/**
 * @brief Dot product of two vectors.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector 
 * @return float
 */
static inline float lmVector2_dot(lmVector2 a, lmVector2 b) {
    return a.x * b.x + a.y * b.y;
}

/**
 * @brief Z component of cross product of two vectors.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return float 
 */
static inline float lmVector2_cross(lmVector2 a, lmVector2 b) {
    return a.x * b.y - a.y * b.x;
}

/**
 * @brief Squared distance from one vector to another.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return float 
 */
static inline float lmVector2_dist2(lmVector2 a, lmVector2 b) {
    return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

/**
 * @brief Distance from one vector to another.
 * 
 * @param a Left-hand vector
 * @param b Right-hand vector
 * @return float 
 */
static inline float lmVector2_dist(lmVector2 a, lmVector2 b) {
    return sqrtf(lmVector2_dist2(a, b));
}

/**
 * @brief Normalize a vector.
 * 
 * @param v Vector to normalize
 * @return lmVector2 
 */
static inline lmVector2 lmVector2_normalize(lmVector2 v) {
    return lmVector2_div(v, lmVector2_len(v));
}


#endif