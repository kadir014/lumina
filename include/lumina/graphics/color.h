/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_COLOR_H
#define _LUMINA_COLOR_H

#include "lumina/_lumina.h"


/**
 * @file color.h
 * 
 * @brief Color.
 */


/**
 * @brief Color struct in RGB space.
 */
typedef struct {
    lm_uint8 r;
    lm_uint8 g;
    lm_uint8 b;
    lm_uint8 a;
} lmColor;

/**
 * @brief Convert color from HSV to RGB.
 * 
 * @param rgb_color Color in RGB space.
 * @return lmColor 
 */
lmColor lmColor_from_hsv(lmColor rgb_color);


#endif