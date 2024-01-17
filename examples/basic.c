/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/lumina.h"


void on_start(lmGame *game) {
    printf("Game started running!\n");
}

void on_update(lmGame *game) {
    //printf("FPS: %f  dt: %f\n", game->clock->fps, game->clock->dt);
}

int main(int argc, char **argv) {
    lmGameDef game_def = lmGameDef_default;
    game_def.window_title = "Basic Lumina Game Example";
    game_def.on_start = on_start;
    game_def.on_update = on_update;
    game_def.target_fps = 165;

    lmGame *game = lmGame_new(game_def);

    lmGame_run(game);

    lmGame_free(game);

    return EXIT_SUCCESS;
}