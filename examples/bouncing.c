/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/lumina.h"


#define N 30000


void movement_system(lm_uint64 entity_id, lmComponent **comps, size_t comps_size, void *user_context) {
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
    transform->rotation += ((float)(entity_id % 2) - 0.5) * 2.5;
}

void bounce_system(lm_uint64 entity_id, lmComponent **comps, size_t comps_size, void *user_context) {
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

void sprite_render_system(lm_uint64 entity_id, lmComponent **comps, size_t comps_size, void *user_context) {
    lmGame *game = (lmGame *)user_context;
    lmTransform *transform;
    lmTexture *texture;

    for (size_t i = 0; i < comps_size; i++) {
        lmComponent *comp = comps[i];
        switch (comp->id) {
            case 1:
                transform = comp->data;
                break;

            case 3:
                texture = comp->data;
                break;
        }
    }

    int texture_width, texture_height;
    SDL_QueryTexture(texture->sdl_texture, NULL, NULL, &texture_width, &texture_height);

    float width = texture_width * transform->scale.x;
    float height = texture_height * transform->scale.y;

    SDL_FRect dest_rect = {
        transform->position.x - width / 2.0,
        transform->position.y - height / 2.0,
        width,
        height
    };

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    float x = transform->position.x / 1280.0;
    float x0 = x * 2.0 - 1.0;
    float alpha = x0 * x0 * x0 * x0 - 2.0 * (x0 * x0) + 1.0;

    float h = entity_id % 256;
    lmColor color = lmColor_from_hsv((lmColor){h, 255, 255});
    SDL_SetTextureColorMod(texture->sdl_texture, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(texture->sdl_texture, dclamp(alpha, 0.0, 1.0) * 255);

    SDL_RenderCopyExF(
        game->window->sdl_renderer,
        texture->sdl_texture,
        NULL,
        &dest_rect,
        transform->rotation,
        NULL,
        flip
    );
}

void on_ready(lmGame *game) {
    printf(
        "Game started running!\n"
        "Lumina:        %d.%d.%d\n",
        LM_VERSION_MAJOR, LM_VERSION_MINOR, LM_VERSION_PATCH
    );

    lmTexture *texture = lmTexture_from_png(game->window, "assets/gem.png");

    lm_uint64 start = SDL_GetPerformanceCounter();

    for (size_t j = 0; j < N; j++) {
        lm_uint64 ball = lmECS_new_entity(game->ecs);

        lmTransform transform = lmTransform_default;
        transform.position = LM_VEC2(frandom(100.0, 1280.0 - 100.0), frandom(100.0, 720.0 - 100.0));
        float scale = frandom(1.5, 2.75);
        transform.scale = LM_VEC2(scale, scale);
        transform.rotation = frandom(0.0, LM_TAU);
        lmECS_add_component(game->ecs, ball, 1, &transform, sizeof(lmTransform));

        lmVector2 velocity = lmVector2_rotate(LM_VEC2(1.5, 0.0), frandom(0.0, LM_TAU));
        lmECS_add_component(game->ecs, ball, 2, &velocity, sizeof(lmVector2));

        lmECS_add_component_p(game->ecs, ball, 3, texture);
    }

    lmECS_add_system(game->ecs, "movement", movement_system, (lm_uint64[]){1, 2}, 2, NULL);
    lmECS_add_system(game->ecs, "bounce", bounce_system, (lm_uint64[]){1, 2}, 2, NULL);
    lmECS_add_system(game->ecs, "sprite_render", sprite_render_system, (lm_uint64[]){1, 3}, 2, game);

    lm_uint64 end = SDL_GetPerformanceCounter();
    double elapsed = (double)end / game->clock->frequency - (double)start / game->clock->frequency;

    printf("ECS setup: %fms\n", elapsed * 1000.0);
}

void on_render(lmGame *game) {
    lm_uint64 start = SDL_GetPerformanceCounter();

    lmECS_run_system(game->ecs, "movement");
    lmECS_run_system(game->ecs, "bounce");

    lm_uint64 end = SDL_GetPerformanceCounter();
    double systems_elapsed = (double)end / game->clock->frequency - (double)start / game->clock->frequency;

    start = SDL_GetPerformanceCounter();

    lmECS_run_system(game->ecs, "sprite_render");

    end = SDL_GetPerformanceCounter();
    double render_elapsed = (double)end / game->clock->frequency - (double)start / game->clock->frequency;
    //printf("Systems: %fms - Render:  %fms\n", systems_elapsed * 1000.0, render_elapsed * 1000.0);
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