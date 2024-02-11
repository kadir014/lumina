/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/graphics/texture.h"


/**
 * @file graphics/texture.c
 * 
 * @brief Texture.
 */


lmTexture *lmTexture_new(SDL_Texture *sdl_texture) {
    lmTexture *texture = LM_NEW(lmTexture);
    LM_MEMORY_ASSERT(texture);

    texture->sdl_texture = sdl_texture;

    return texture;
}


lmTexture *lmTexture_from_png(lmWindow *window, const char *filepath) {
    SDL_Texture *sdl_texture = IMG_LoadTexture(window->sdl_renderer, filepath);

    if (!sdl_texture) {
        LM_ERROR(IMG_GetError());
    }

    return lmTexture_new(sdl_texture);
}

void lmTexture_free(lmTexture *texture) {
    if (!texture) return;

    SDL_DestroyTexture(texture->sdl_texture);
    free(texture);
}