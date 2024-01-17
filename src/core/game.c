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

    #ifdef LM_WEB
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

    game->font = TTF_OpenFont("assets/FiraCode-Regular.ttf", 18);
    if (game->font == NULL) {
        LM_ERROR(TTF_GetError());
    }
    TTF_SetFontStyle(game->font, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(game->font, 0);
    TTF_SetFontKerning(game->font, 1);
    TTF_SetFontHinting(game->font, TTF_HINTING_NORMAL);

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

    SDL_RenderClear(game->window->sdl_renderer);

    if (game->on_render) game->on_render(game);

    {
        char text[24];
        sprintf(text, "Lumina %d.%d.%d", LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH);
        SDL_Surface *text_surf = TTF_RenderText_Blended(game->font, text, (SDL_Color){255, 255, 255, 255});
        SDL_Texture *text_tex = SDL_CreateTextureFromSurface(game->window->sdl_renderer, text_surf);
        SDL_FreeSurface(text_surf);
        int width, height;
        SDL_QueryTexture(text_tex, NULL, NULL, &width, &height);
        SDL_Rect text_rect = {5, 5, width, height};
        SDL_RenderCopy(game->window->sdl_renderer, text_tex, NULL, &text_rect);
    }
    {
        char text[24];
        sprintf(text, "SDL %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
        SDL_Surface *text_surf = TTF_RenderText_Blended(game->font, text, (SDL_Color){255, 255, 255, 255});
        SDL_Texture *text_tex = SDL_CreateTextureFromSurface(game->window->sdl_renderer, text_surf);
        SDL_FreeSurface(text_surf);
        int width, height;
        SDL_QueryTexture(text_tex, NULL, NULL, &width, &height);
        SDL_Rect text_rect = {5, 5 + (20 * 1), width, height};
        SDL_RenderCopy(game->window->sdl_renderer, text_tex, NULL, &text_rect);
    }
    {
        char text[16];
        sprintf(text, "FPS: %.1f", game->clock->fps);
        SDL_Surface *text_surf = TTF_RenderText_Blended(game->font, text, (SDL_Color){255, 255, 255, 255});
        SDL_Texture *text_tex = SDL_CreateTextureFromSurface(game->window->sdl_renderer, text_surf);
        SDL_FreeSurface(text_surf);
        int width, height;
        SDL_QueryTexture(text_tex, NULL, NULL, &width, &height);
        SDL_Rect text_rect = {5, 5 + (20 * 2), width, height};
        SDL_RenderCopy(game->window->sdl_renderer, text_tex, NULL, &text_rect);
    }

    SDL_RenderPresent(game->window->sdl_renderer);
}

void lmGame_run(lmGame *game) {
    if (game->on_start) game->on_start(game);
    game->is_running = true;

    #ifdef LM_WEB

        emscripten_set_main_loop_arg(lmGame_main_loop, game, -1, true);

    #else

        while (game->is_running) {
            lmGame_main_loop(game);
        }

    #endif
}