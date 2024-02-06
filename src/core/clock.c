/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/core/clock.h"
#include "lumina/core/constants.h"


/**
 * @file core/clock.c
 * 
 * @brief Clock.
 */


lmClock *lmClock_new() {
    lmClock *clock = LM_NEW(lmClock);
    LM_MEMORY_ASSERT(clock);

    clock->frequency = (double)SDL_GetPerformanceFrequency();
    clock->accumulated_fps = 0.0;
    clock->frame_time_full = 1.0;
    clock->fps = 0.0;
    clock->dt = 0.0;
    clock->start = (double)SDL_GetPerformanceCounter() / clock->frequency;
    clock->time = 0.0;
    clock->timer_start = 0;
    clock->timer_end = 0;
    clock->timer_full_end = 0;
    clock->fps_counter = 0;

    return clock;
}

void lmClock_free(lmClock *clock) {
    if (!clock) return;

    free(clock);
}

void lmClock_tick(lmClock *clock, double target_fps) {
    double start = (double)clock->timer_start / clock->frequency;

    clock->timer_end = SDL_GetPerformanceCounter();

    double frame_time = ((double)clock->timer_end / clock->frequency - start) * 1000.0;

    clock->fps_counter++;
    clock->accumulated_fps += 1000.0 / clock->frame_time_full;
    if (clock->fps_counter >= LM_FPS_UPDATE_FREQUENCY) {
        clock->fps = clock->accumulated_fps / (double)LM_FPS_UPDATE_FREQUENCY;

        clock->fps_counter = 0;
        clock->accumulated_fps = 0.0;
    }

    double target_wait_time = 1000.0 / target_fps;
    if (frame_time < target_wait_time) {
        SDL_Delay((lm_uint32)(target_wait_time - frame_time));
    }

    clock->timer_full_end = SDL_GetPerformanceCounter();
    clock->frame_time_full = ((double)clock->timer_full_end / clock->frequency - start) * 1000.0;
    clock->dt = clock->frame_time_full / 1000.0;

    clock->timer_start = SDL_GetPerformanceCounter();

    clock->time = (double)SDL_GetPerformanceCounter() / clock->frequency - clock->start;
}