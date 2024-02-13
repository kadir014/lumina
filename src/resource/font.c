/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/resource/font.h"


/**
 * @file resource/font.c
 * 
 * @brief Font resource.
 */


lmFont lmFont_load(const char *filepath, lm_uint32 size) {
    lmFont font;

    font.ttf = TTF_OpenFont(filepath, size);
    if (!font.ttf) LM_ERROR(TTF_GetError());

    TTF_SetFontStyle(font.ttf, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(font.ttf, 0);
    TTF_SetFontKerning(font.ttf, 1);
    TTF_SetFontHinting(font.ttf, TTF_HINTING_NORMAL);

    font.filepath = filepath;
    font.size = size;

    return font;
}