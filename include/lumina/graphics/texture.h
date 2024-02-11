/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_TEXTURE_H
#define _LUMINA_TEXTURE_H

#include "lumina/_lumina.h"
#include "lumina/core/window.h"


/**
 * @file graphics/texture.h
 * 
 * @brief Texture.
 */


/**
 * @brief 2D texture.
 */
typedef struct {
    SDL_Texture *sdl_texture;
} lmTexture;

lmTexture *lmTexture_new(SDL_Texture *sdl_texture);

lmTexture *lmTexture_from_png(lmWindow *window, const char *filepath);

void lmTexture_free(lmTexture *texture);


#endif