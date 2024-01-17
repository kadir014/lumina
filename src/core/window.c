/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/window.h"


/**
 * @file window.c
 * 
 * @brief Window.
 */


lmWindow *lmWindow_new(const char *title, lm_uint16 width, lm_uint16 height) {
    lmWindow *window = LM_NEW(lmWindow);
    if (!window) {
        LM_ERROR("Unable to allocate memory.");
    }

    window->sdl_window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (!window->sdl_window) {
        LM_ERROR(SDL_GetError());
    }

    window->sdl_renderer = SDL_CreateRenderer(
        window->sdl_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    if (!window->sdl_renderer) {
        SDL_DestroyWindow(window->sdl_window);
        SDL_Quit();
        LM_ERROR(SDL_GetError());
    };

    SDL_SetRenderDrawBlendMode(window->sdl_renderer, SDL_BLENDMODE_BLEND);

    return window;
}

void lmWindow_free(lmWindow *window) {
    if (!window) return;

    SDL_DestroyWindow(window->sdl_window);
    SDL_DestroyRenderer(window->sdl_renderer);
    free(window);
}

const char *lmWindow_get_title(lmWindow *window) {
    return SDL_GetWindowTitle(window->sdl_window);
}

void lmWindow_set_title(lmWindow *window, const char *title) {
    SDL_SetWindowTitle(window->sdl_window, title);
}