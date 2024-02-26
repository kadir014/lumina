/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_MATH_H
#define _LUMINA_MATH_H

#include "lumina/_lumina.h"


/**
 * @file math/math.h
 * 
 * @brief General math utilities.
 */


/**
 * @brief Clamp double value between a range
 * 
 * @param value Value
 * @param min Minimum of range
 * @param max Maximum of range
 * @return double 
 */
double lm_dclamp(double value, double min, double max) {
    // Generates good ASM: https://stackoverflow.com/a/16659263
    const double t = value < min ? min : value;
    return t > max ? max : t;
}


#endif