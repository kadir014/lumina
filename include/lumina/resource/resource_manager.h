/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_RESOURCE_MANAGER_H
#define _LUMINA_RESOURCE_MANAGER_H

#include "lumina/_lumina.h"
#include "lumina/collections/hashmap.h"


/**
 * @file resource/resource_manager.h
 * 
 * @brief Resource manager.
 */


typedef struct {
    TTF_Font *ttf;
    char *path;
    lm_uint32 size;
} lmFont;


typedef struct {
    lmHashMap *font_cache;
} lmResourceManager;

lmResourceManager *lmResourceManager_new();

void lmResourceManager_free(lmResourceManager *resource_manager);

void lmResourceManager_load_font(
    lmResourceManager *resource_manager,
    char *path,
    lm_uint32 size
);

lmFont *lmResourceManager_get_font(
    lmResourceManager *resource_manager,
    char *name,
    lm_uint32 size
);


#endif