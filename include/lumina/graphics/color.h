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
 * @file graphics/color.h
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

#define lmColor_TO_SDL(color) (SDL_Color){(color).r, (color).g, (color).b, (color).a}

/**
 * @brief Convert color from HSV to RGB.
 * 
 * @param hsv_color Color in HSV space.
 * @return lmColor 
 */
lmColor lmColor_from_hsv(lmColor hsv_color);


#endif