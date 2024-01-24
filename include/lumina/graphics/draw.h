/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_DRAW_H
#define _LUMINA_DRAW_H

#include "lumina/_lumina.h"
#include "lumina/graphics/color.h"
#include "lumina/resource/resource_manager.h"


/**
 * @file graphics/draw.h
 * 
 * @brief Drawing functions.
 */


void lm_draw_text(
    struct lmGame *game,
    lmFont *font,
    char *text,
    int x,
    int y,
    lmColor color
);


#endif