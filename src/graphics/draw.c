/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/graphics/draw.h"
#include "lumina/core/game.h"


/**
 * @file graphics/draw.c
 * 
 * @brief Drawing functions.
 */


void lm_draw_text(
    lmGame *game,
    lmFont *font,
    char *text,
    int x,
    int y,
    lmColor color
) {
    SDL_Renderer *renderer = game->window->sdl_renderer;

    SDL_Surface *text_surf = TTF_RenderText_Blended(font->ttf, text, lmColor_TO_SDL(color));
    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surf);
    SDL_FreeSurface(text_surf);

    int tex_width, tex_height;
    SDL_QueryTexture(text_tex, NULL, NULL, &tex_width, &tex_height);

    SDL_Rect text_rect = {x, y, tex_width, tex_height};

    SDL_RenderCopy(renderer, text_tex, NULL, &text_rect);
}