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
 * @file resource/texture.h
 * 
 * @brief Texture resource.
 */


/**
 * @brief 2D texture.
 */
typedef struct {
    SDL_Texture *sdl_texture;
    const char *filepath;
} lmTexture;

lmTexture lmTexture_load(lmWindow *window, const char *filepath);


#endif