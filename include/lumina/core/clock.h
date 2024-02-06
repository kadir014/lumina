/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_CLOCK_H
#define _LUMINA_CLOCK_H

#include "lumina/_lumina.h"


/**
 * @file core/clock.h
 * 
 * @brief Clock.
 */


typedef struct {
    double frequency;
    double accumulated_fps;
    double frame_time_full;
    double fps;
    double dt;
    double start;
    double time;
    lm_uint64 timer_start;
    lm_uint64 timer_end;
    lm_uint64 timer_full_end;
    lm_uint32 fps_counter;
} lmClock;

lmClock *lmClock_new();

void lmClock_free(lmClock *clock);

void lmClock_tick(lmClock *clock, double target_fps);


#endif