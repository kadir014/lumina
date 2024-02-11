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
 * @brief Math.
 */


double dclamp(double d, double min, double max) {
    // Generates good ASM: https://stackoverflow.com/a/16659263
    const double t = d < min ? min : d;
    return t > max ? max : t;
}


#endif