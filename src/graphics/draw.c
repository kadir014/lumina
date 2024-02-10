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
 * @brief Primitive drawing functions using SDL_Renderer utilities.
 */


void lm_draw_text(
    lmGame *game,
    lmFont *font,
    char *text,
    float x,
    float y,
    lmColor color
) {
    SDL_Renderer *renderer = game->window->sdl_renderer;

    SDL_Surface *text_surf = TTF_RenderText_Blended(font->ttf, text, lmColor_TO_SDL(color));
    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surf);
    SDL_FreeSurface(text_surf);

    int tex_width, tex_height;
    SDL_QueryTexture(text_tex, NULL, NULL, &tex_width, &tex_height);

    SDL_FRect text_rect = {x, y, tex_width, tex_height};

    SDL_RenderCopyF(renderer, text_tex, NULL, &text_rect);
    SDL_DestroyTexture(text_tex);
}

void lm_draw_circle(lmGame *game, float x, float y, float radius) {
    // https://discourse.libsdl.org/t/query-how-do-you-draw-a-circle-in-sdl2-sdl2/33379

    SDL_Renderer *renderer = game->window->sdl_renderer;

    float diameter = (radius * 2);

    float ox = (radius - 1);
    float oy = 0;
    float tx = 1;
    float ty = 1;
    float error = (tx - diameter);

    while (ox >= oy) {
        // Each of the following renders an octant of the circle
        // Use SDL_RenderDrawPointsF maybe?
        SDL_RenderDrawPointF(renderer, x + ox, y - oy);
        SDL_RenderDrawPointF(renderer, x + ox, y + oy);
        SDL_RenderDrawPointF(renderer, x - ox, y - oy);
        SDL_RenderDrawPointF(renderer, x - ox, y + oy);
        SDL_RenderDrawPointF(renderer, x + oy, y - ox);
        SDL_RenderDrawPointF(renderer, x + oy, y + ox);
        SDL_RenderDrawPointF(renderer, x - oy, y - ox);
        SDL_RenderDrawPointF(renderer, x - oy, y + ox);

        if (error <= 0) {
            ++oy;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --ox;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void lm_draw_polygon(lmGame *game, lmVector2 vertices[], size_t vertices_len) {
    SDL_Renderer *renderer = game->window->sdl_renderer;

    for (size_t i = 0; i < vertices_len; i++) {
        lmVector2 va = vertices[i];
        lmVector2 vb = vertices[(i + 1) % vertices_len];

        SDL_RenderDrawLineF(
            renderer,
            va.x, va.y,
            vb.x, vb.y
        );
    }
}

void lm_fill_polygon(lmGame *game, lmVector2 vertices[], size_t vertices_len) {
    SDL_Renderer *renderer = game->window->sdl_renderer;

    size_t triangles = 3 * vertices_len - 6;
    SDL_Vertex *sdl_vertices = (SDL_Vertex *)malloc(sizeof(SDL_Vertex) * vertices_len);

    SDL_Color color;
    SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);

    for (size_t i = 0; i < vertices_len; i++) {
        lmVector2 v = vertices[i];

        sdl_vertices[i] = (SDL_Vertex){
            .color = color,
            .position = (SDL_FPoint){v.x, v.y},
            .tex_coord = (SDL_FPoint){0.0, 0.0}
        };
    }

    // Cast the array size to uint32_t so the compiler doesn't complain
    // about maximum object size
    // A polygon should have that many indices anyway
    int *indices = (int *)malloc((uint32_t)(sizeof(int) * triangles));

    // Triangulate the polygon
    size_t j = 2;
    for (size_t i = 2; i < triangles; i += 3) {
        indices[i - 2] = 0;
        indices[i - 1] = j;
        indices[i] = j - 1;
        j++;
    }

    SDL_RenderGeometry(renderer, NULL, sdl_vertices, vertices_len, indices, triangles);

    free(sdl_vertices);
    free(indices);
}