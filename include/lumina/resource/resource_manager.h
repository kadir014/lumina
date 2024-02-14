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
#include "lumina/resource/font.h"
#include "lumina/resource/texture.h"


/**
 * @file resource/resource_manager.h
 * 
 * @brief Resource manager.
 */


typedef struct {
    lmHashMap *fonts;
    lmHashMap *textures;
} lmResourceManager;

lmResourceManager *lmResourceManager_new();

void lmResourceManager_free(lmResourceManager *resource_manager);

void lmResource_load_font(
    struct lmGame *game,
    char *filepath,
    lm_uint32 size
);

lmFont *lmResource_get_font(
    struct lmGame *game,
    char *name,
    lm_uint32 size
);

void lmResource_load_texture(
    struct lmGame *game,
    char *filepath
);

lmTexture *lmResource_get_texture(
    struct lmGame *game,
    char *name
);


#endif