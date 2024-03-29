/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_INTERNAL_H
#define _LUMINA_INTERNAL_H


/**
 * @file _lumina.h
 * 
 * @brief Internal API header.
 */


// Version in MAJOR.MINOR.PATCH format
#define LM_VERSION_MAJOR 0
#define LM_VERSION_MINOR 1
#define LM_VERSION_PATCH 0


#define SDL_MAIN_HANDLED


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "lumina/core/types.h"
#include "lumina/core/platform.h"


#if defined(__EMSCRIPTEN__)
    #define LM_WEB
    #include <emscripten.h>
#endif


/**
 * @brief Allocate on HEAP.
 * 
 * @param type Type
 */
#define LM_NEW(type) ((type *)malloc(sizeof(type)))


#ifdef LM_WEB
    #define LM_EXIT(exit_code) (emscripten_force_exit(exit_code))
#else
    #define LM_EXIT(exit_code) (exit(exit_code))
#endif


/**
 * @brief Log the error message and abort.
 * 
 * @param message Error message. No need to end with newline.
 */
#define LM_ERROR(message) ({            \
    fprintf(                            \
        stderr,                         \
        "Lumina error in %s, line %d\n" \
        "%s\n",                         \
        __FILE__, __LINE__,             \
        message                         \
    );                                  \
                                        \
    LM_EXIT(EXIT_FAILURE);              \
})

/**
 * @brief Raise error if the memory was not allocated.
 * 
 * @param object Pointer to memory. Raises if NULL.
 */
#define LM_MEMORY_ASSERT(object) \
    if (!(object)) LM_ERROR("Unable to allocate memory.")


/* Forward decleration of game struct for other headers. */

struct lmGame;



#endif