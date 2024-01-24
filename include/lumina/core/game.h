/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_GAME_H
#define _LUMINA_GAME_H

#include "lumina/_lumina.h"
#include "lumina/core/window.h"
#include "lumina/core/clock.h"
#include "lumina/resource/resource_manager.h"


/**
 * @file core/game.h
 * 
 * @brief Top-level application class.
 */


typedef void ( *lmGameEvent)(struct lmGame *);


typedef struct {
    const char *window_title;
    lm_uint16 window_width;
    lm_uint16 window_height;
    lmGameEvent on_start;
    lmGameEvent on_update;
    lmGameEvent on_render;
    lm_uint16 target_fps;
} lmGameDef;

static const lmGameDef lmGameDef_default = {
    .window_title = "Lumina Game",
    .window_width = 1280,
    .window_height = 720,
    .on_start = NULL,
    .on_update = NULL,
    .on_render = NULL,
    .target_fps = 60
};


struct lmGame{
    lmWindow *window;
    lmGameEvent on_start;
    lmGameEvent on_update;
    lmGameEvent on_render;
    bool is_running;
    lm_uint16 target_fps;
    lmClock *clock;
    lmResourceManager *resource_manager;
};

typedef struct lmGame lmGame;


lmGame *lmGame_new(lmGameDef game_def);

void lmGame_free(lmGame *game);

void lmGame_run(lmGame *game);


#endif