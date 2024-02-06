/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/lumina.h"


void on_ready(lmGame *game) {
    #if LM_PLATFORM == LM_PLATFORM_WEB

        printf(
            "Game started running!\n"
            "Lumina:        %d.%d.%d\n"
            "Compiled with: Emscripten %d.%d.%d (%s %s)\n"
            "Architecture:  %s\n"
            "Platform:      %s\n",
            LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH,
            __EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__,
            LM_COMPILER_as_string(), LM_COMPILER_VERSION_STR,
            LM_ARCH_as_string(),
            LM_PLATFORM_as_string()
        );

    #else

        printf(
            "Game started running!\n"
            "Lumina:        %d.%d.%d\n"
            "Compiled with: %s %s\n"
            "Architecture:  %s\n"
            "Platform:      %s\n",
            LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH,
            LM_COMPILER_as_string(), LM_COMPILER_VERSION_STR,
            LM_ARCH_as_string(),
            LM_PLATFORM_as_string()
        );

    #endif
}

void on_render(lmGame *game) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);


    size_t n = 6;
    float radius = 500.0;
    lmVector2 vertices[n];
    lmVector2 arm = LM_VEC2(radius / 2.0, 0.0);
    arm = lmVector2_rotate(arm, game->clock->time * 3.0);

    for (size_t i = 0; i < n; i++) {
        vertices[i] = lmVector2_add(arm, LM_VEC2(640.0, 360.0));
        arm = lmVector2_rotate(arm, 2.0 * 3.14 / (float)n);
    }

    lmColor color = lmColor_from_hsv((lmColor){(lm_uint8)(game->clock->time * 75.0) % 255, 255, 255});
    SDL_SetRenderDrawColor(game->window->sdl_renderer, color.r, color.g, color.b, 255);
    lm_fill_polygon(game, vertices, n);


    SDL_SetRenderDrawColor(game->window->sdl_renderer, 255, 0, 0, 255);
    lm_draw_circle(game, mx, my, 15.0);

    SDL_SetRenderDrawColor(game->window->sdl_renderer, 0, 255, 0, 255);
    lm_draw_circle(game, mx, 720-my, 15.0);

    SDL_SetRenderDrawColor(game->window->sdl_renderer, 0, 0, 255, 255);
    lm_draw_circle(game, 1280-mx, my, 15.0);

    SDL_SetRenderDrawColor(game->window->sdl_renderer, 255, 255, 0, 255);
    lm_draw_circle(game, 1280-mx, 720-my, 15.0);
}

int main(int argc, char **argv) {
    lmGameDef game_def = lmGameDef_default;
    game_def.window_title = "Basic Lumina Game Example";
    game_def.on_ready = on_ready;
    game_def.on_render = on_render;
    game_def.target_fps = 165;

    lmGame *game = lmGame_new(game_def);

    lmGame_run(game);

    lmGame_free(game);

    return EXIT_SUCCESS;
}