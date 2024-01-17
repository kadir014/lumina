/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_WINDOW_H
#define _LUMINA_WINDOW_H

#include "lumina/_lumina.h"


/**
 * @file window.h
 * 
 * @brief Window.
 */


/**
 * @brief Window.
 */
typedef struct {
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
} lmWindow;

/**
 * @brief Create new window.
 * 
 * @param title Title string
 * @param width Width in pixels
 * @param height Height in pixels
 * @return lmWindow *
 */
lmWindow *lmWindow_new(const char *title, lm_uint16 width, lm_uint16 height);

/**
 * @brief Free window.
 * 
 * @param window Window
 */
void lmWindow_free(lmWindow *window);

/**
 * @brief Get title string.
 * 
 * @return char *
 */
const char *lmWindow_get_title(lmWindow *window);

/**
 * @brief Set title string.
 * 
 * @param title Title string
 */
void lmWindow_set_title(lmWindow *window, const char *title);


#endif