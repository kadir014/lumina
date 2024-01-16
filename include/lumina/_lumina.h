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


#define SDL_MAIN_HANDLED


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "lumina/types.h"


/**
 * @brief Allocate on HEAP.
 * 
 * @param type Type
 */
#define LM_NEW(type) ((type *)malloc(sizeof(type)))


/**
 * @brief Log the error message and abort.
 * 
 * @param message Error message. Do not end with newline.
 */
#define LM_ERROR(message) ({                                              \
    char errmsg[128];                                                     \
    sprintf(errmsg, "Lumina error in %s, line %d\n", __FILE__, __LINE__); \
                                                                          \
    fprintf(stderr, errmsg);                                              \
    fprintf(stderr, message);                                             \
    fprintf(stderr, "\n");                                                \
                                                                          \
    exit(EXIT_FAILURE);                                                   \
})


#endif