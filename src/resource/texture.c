/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/resource/texture.h"


/**
 * @file resource/texture.c
 * 
 * @brief Texture resource.
 */


lmTexture lmTexture_load(lmWindow *window, const char *filepath) {
    lmTexture texture;

    texture.sdl_texture = IMG_LoadTexture(window->sdl_renderer, filepath);

    if (!texture.sdl_texture) LM_ERROR(IMG_GetError());

    texture.filepath = filepath;

    return texture;
}