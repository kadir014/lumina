/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/resource/resource_manager.h"
#include "lumina/math/hash.h"


/**
 * @file resource/resource_manager.h
 * 
 * @brief Resource manager.
 */


static lm_uint64 _lmResourceManager_font_cache_hasher(void *item) {
    lmFont *font = (lmFont *)item;

    // TODO: combine path + size
    lm_uint64 hash = lm_fnv1a(font->path);

    return hash;
}


lmResourceManager *lmResourceManager_new() {
    lmResourceManager *resource_manager = LM_NEW(lmResourceManager);
    LM_MEMORY_ASSERT(resource_manager);

    resource_manager->font_cache = lmHashMap_new(
        sizeof(lmFont), 0, _lmResourceManager_font_cache_hasher
    );
    LM_MEMORY_ASSERT(resource_manager->font_cache);

    return resource_manager;
}

void lmResourceManager_free(lmResourceManager *resource_manager) {
    if (!resource_manager) return;

    size_t iter = 0;
    void *item;
    while (lmHashMap_iter(resource_manager->font_cache, &iter, &item)) {
        lmFont *font = (lmFont *)item;
        TTF_CloseFont(font->ttf);
    }

    lmHashMap_free(resource_manager->font_cache);
}

void lmResourceManager_load_font(
    lmResourceManager *resource_manager,
    char *path,
    lm_uint32 size
) {
    lmFont font;

    font.ttf = TTF_OpenFont(path, size);
    if (!font.ttf) LM_ERROR(TTF_GetError());

    TTF_SetFontStyle(font.ttf, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(font.ttf, 0);
    TTF_SetFontKerning(font.ttf, 1);
    TTF_SetFontHinting(font.ttf, TTF_HINTING_NORMAL);

    font.path = path;
    font.size = size;

    lmHashMap_set(resource_manager->font_cache, &font);
}

lmFont *lmResourceManager_get_font(
    lmResourceManager *resource_manager,
    char *name,
    lm_uint32 size
) {
    return lmHashMap_get(
        resource_manager->font_cache, &(lmFont){.path=name, .size=size}
    );
}