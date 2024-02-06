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
#include "lumina/math/vector.h"


/**
 * @file graphics/draw.h
 * 
 * @brief Drawing functions.
 */


/**
 * @brief Draw text.
 * 
 * @param game Game instance
 * @param font Font
 * @param text String of text to render
 * @param x Top-left X position to render the text at
 * @param y Top-left Y position to render the text at
 * @param color Text color
 */
void lm_draw_text(
    struct lmGame *game,
    lmFont *font,
    char *text,
    float x,
    float y,
    lmColor color
);

/**
 * @brief Draw circle.
 * 
 * @param game Game instance
 * @param x Circle center X
 * @param y Circle center Y
 * @param radius Circle radius
 */
void lm_draw_circle(struct lmGame *game, float x, float y, float radius);

/**
 * @brief Draw polygon.
 * 
 * @param game Game instance
 * @param vertices Array of polygon vertices
 * @param vertices_len Length of the vertices array
 */
void lm_draw_polygon(struct lmGame *game, lmVector2 vertices[], size_t vertices_len);

/**
 * @brief Fill polygon.
 * 
 * @param game Game instance
 * @param vertices Array of polygon vertices
 * @param vertices_len Length of the vertices array
 */
void lm_fill_polygon(struct lmGame *game, lmVector2 vertices[], size_t vertices_len);


#endif