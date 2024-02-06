/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/core/game.h"
#include "lumina/core/constants.h"
#include "lumina/graphics/draw.h"


/**
 * @file core/game.c
 * 
 * @brief Top-level application struct.
 */


lmGame *lmGame_new(lmGameDef game_def) {
    lmGame *game = LM_NEW(lmGame);
    LM_MEMORY_ASSERT(game);

    #ifdef LM_WEB
        // Some modules can't be initialized on web
        lm_uint32 init_flags = SDL_INIT_EVERYTHING & ~SDL_INIT_HAPTIC;
    #else
        lm_uint32 init_flags = SDL_INIT_EVERYTHING;
    #endif

    if (SDL_Init(init_flags) != 0) {
		LM_ERROR(SDL_GetError());
	}

    if (TTF_Init() != 0) {
        LM_ERROR(TTF_GetError());
    }

    game->window = lmWindow_new(
        game_def.window_title,
        game_def.window_width,
        game_def.window_height
    );

    game->resource_manager = lmResourceManager_new();
    lmResourceManager_load_font(game->resource_manager, "assets/FiraCode-Regular.ttf", 18);

    game->ecs = lmECS_new();

    game->on_ready = game_def.on_ready;
    game->on_update = game_def.on_update;
    game->on_render = game_def.on_render;

    game->target_fps = game_def.target_fps;
    game->clock = lmClock_new();

    game->is_running = false;

    return game;
}

void lmGame_free(lmGame *game) {
    if (!game) return;

    lmWindow_free(game->window);
    lmClock_free(game->clock);
    lmResourceManager_free(game->resource_manager);
    lmECS_free(game->ecs);
    free(game);

    SDL_Quit();
    TTF_Quit();
}

static void lmGame_main_loop(void *game_p) {
    lmGame *game = (lmGame *)game_p;

    lmClock_tick(game->clock, game->target_fps);

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
            game->is_running = false;
    }

    if (game->on_update) game->on_update(game);

    SDL_SetRenderDrawColor(game->window->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->window->sdl_renderer);

    if (game->on_render) game->on_render(game);

    //lmFont *font = lmResourceManager_get_font("FiraCode", 18);
    lmFont *font = lmResourceManager_get_font(game->resource_manager, "assets/FiraCode-Regular.ttf", 18);
    lmColor text_color = (lmColor){255, 255, 255, 255};

    char text0[24];
    sprintf(text0, "Lumina %d.%d.%d", LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH);
    lm_draw_text(game, font, text0, 5, 5 + (24 * 0), text_color);

    char text1[24];
    sprintf(text1, "SDL %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
    lm_draw_text(game, font, text1, 5, 5 + (24 * 1), text_color);

    char text2[16];
    sprintf(text2, "FPS: %.1f", game->clock->fps);
    lm_draw_text(game, font, text2, 5, 5 + (24 * 2), text_color);

    SDL_RenderPresent(game->window->sdl_renderer);
}

void lmGame_run(lmGame *game) {
    game->is_running = true;
    if (game->on_ready) game->on_ready(game);

    #ifdef LM_WEB

        emscripten_set_main_loop_arg(lmGame_main_loop, game, -1, true);

    #else

        while (game->is_running) {
            lmGame_main_loop(game);
        }

    #endif
}