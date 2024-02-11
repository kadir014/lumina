/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_MATH_CONSTANTS_H
#define _LUMINA_MATH_CONSTANTS_H

#include "lumina/_lumina.h"


/**
 * @file math/constants.h
 * 
 * @brief Mathematical constants.
 */


#define LM_PI 3.141592653589793238462643383279502884
#define LM_TAU 6.283185307179586476925286766559005768


#ifndef INFINITY
    #define LM_INF (1.0 / 0.0)
#else
    #define LM_INF INFINITY
#endif


#endif