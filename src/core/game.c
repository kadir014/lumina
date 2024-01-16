/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/game.h"
#include "lumina/constants.h"


/**
 * @file game.c
 * 
 * @brief Top-level application class.
 */


lmGame *lmGame_new(lmGameDef game_def) {
    lmGame *game = LM_NEW(lmGame);
    if (!game) LM_ERROR("Unable to allocate memory.");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		LM_ERROR(SDL_GetError());
	}

    game->window = lmWindow_new(
        game_def.window_title,
        game_def.window_width,
        game_def.window_height
    );

    game->on_start = game_def.on_start;
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
    free(game);
    SDL_Quit();
}

void lmGame_run(lmGame *game) {
    if (game->on_start) game->on_start(game);
    game->is_running = true;

    SDL_Event event;

    while (game->is_running) {
        lmClock_tick(game->clock, game->target_fps);

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT)
                game->is_running = false;
        }

        if (game->on_update) game->on_update(game);

        SDL_RenderClear(game->window->sdl_renderer);

        if (game->on_render) game->on_render(game);

		SDL_RenderPresent(game->window->sdl_renderer);
    }
}