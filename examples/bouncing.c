/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/lumina.h"


void movement_system(lm_uint64 entity_id, lmComponent **comps, size_t comps_size) {
    lmTransform *transform;
    lmVector2 *velocity;

    for (size_t i = 0; i < comps_size; i++) {
        lmComponent *comp = comps[i];
        switch (comp->id) {
            case 1:
                transform = comp->data;
                break;

            case 2:
                velocity = comp->data;
                break;
        }
    }

    transform->position = lmVector2_add(transform->position, *velocity);
}

void bounce_system(lm_uint64 entity_id, lmComponent **comps, size_t comps_size) {
    lmTransform *transform;
    lmVector2 *velocity;

    for (size_t i = 0; i < comps_size; i++) {
        lmComponent *comp = comps[i];
        switch (comp->id) {
            case 1:
                transform = comp->data;
                break;

            case 2:
                velocity = comp->data;
                break;
        }
    }

    if (transform->position.x - 15.0 < 0.0) {
        transform->position.x += (0.0 - (transform->position.x - 15.0));
        velocity->x *= -1.0;
    }
    if (transform->position.y - 15.0 < 0.0) {
        transform->position.y += (0.0 - (transform->position.y - 15.0));
        velocity->y *= -1.0;
    }
    if (transform->position.x + 15.0 > 1280.0) {
        transform->position.x -= ((transform->position.x + 15.0) - 1280.0);
        velocity->x *= -1.0;
    }
    if (transform->position.y + 15.0 > 720.0) {
        transform->position.y -= ((transform->position.y + 15.0) - 720.0);
        velocity->y *= -1.0;
    }
}

void on_ready(lmGame *game) {
    printf(
        "Game started running!\n"
        "Lumina:        %d.%d.%d\n",
        LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH
    );

    lm_uint64 ball = lmEntity_new(game->ecs);

    lmTransform transform = lmTransform_default;
    transform.position = LM_VEC2(400.0, 300.0);
    lmEntity_add_component(game->ecs, ball, 1, &transform, sizeof(lmTransform));

    lmVector2 velocity = LM_VEC2(4.0, 1.2);
    lmEntity_add_component(game->ecs, ball, 2, &velocity, sizeof(lmVector2));

    lmEntity_add_system(game->ecs, "movement", movement_system, (lm_uint64[]){1, 2}, 2);
    lmEntity_add_system(game->ecs, "bounce", bounce_system, (lm_uint64[]){1, 2}, 2);
}

void on_render(lmGame *game) {
    lmEntity_run_system(game->ecs, "movement");
    lmEntity_run_system(game->ecs, "bounce");

    int mx, my;
    SDL_GetMouseState(&mx, &my);

    lmEntity *entity = lmHashMap_get(game->ecs->entities, &(lmEntity){.id=0});
    
    for (size_t i = 0; i < entity->comps_size; i++) {
        lmComponent *comp = lmHashMap_get(game->ecs->components, &(lmComponent){.id=entity->comp_ids[i]});

        if (comp->id == 1) {
            lmTransform *transform = (lmTransform *)comp->data;
            SDL_SetRenderDrawColor(game->window->sdl_renderer, 255, 0, 0, 255);
            lm_draw_circle(game, transform->position.x, transform->position.y, 15.0);
        }
    }
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