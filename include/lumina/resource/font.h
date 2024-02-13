/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_FONT_H
#define _LUMINA_FONT_H

#include "lumina/_lumina.h"


/**
 * @file resource/font.h
 * 
 * @brief Font resource.
 */


typedef struct {
    TTF_Font *ttf;
    char *filepath;
    lm_uint32 size;
} lmFont;

lmFont lmFont_load(const char *filepath, lm_uint32 size);


#endif