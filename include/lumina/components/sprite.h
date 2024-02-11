/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_COMPONENTS_SPRITE_H
#define _LUMINA_COMPONENTS_SPRITE_H

#include "lumina/_lumina.h"
#include "lumina/graphics/texture.h"


/**
 * @file components/sprite.h
 * 
 * @brief 2D sprite component.
 */


/**
 * @brief 2D sprite component.
 */
typedef struct {
    lmTexture *texture;
    bool flip_horizontal;
    bool flip_vertical;
} lmSprite;


#endif