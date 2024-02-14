/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/resource/resource_manager.h"
#include "lumina/math/hash.h"
#include "lumina/core/game.h"


/**
 * @file resource/resource_manager.h
 * 
 * @brief Resource manager.
 */


static lm_uint64 _font_hasher(void *item) {
    lmFont *font = (lmFont *)item;

    // TODO: combine path + size
    lm_uint64 hash = lm_fnv1a(font->filepath);

    return hash;
}

static lm_uint64 _texture_hasher(void *item) {
    lmTexture *texture = (lmTexture *)item;

    return lm_fnv1a(texture->filepath);
}


lmResourceManager *lmResourceManager_new() {
    lmResourceManager *resource_manager = LM_NEW(lmResourceManager);
    LM_MEMORY_ASSERT(resource_manager);

    resource_manager->fonts = lmHashMap_new(
        sizeof(lmFont), 0, _font_hasher
    );
    LM_MEMORY_ASSERT(resource_manager->fonts);

    resource_manager->textures = lmHashMap_new(
        sizeof(lmTexture), 0, _texture_hasher
    );
    LM_MEMORY_ASSERT(resource_manager->textures);

    return resource_manager;
}

void lmResourceManager_free(lmResourceManager *resource_manager) {
    if (!resource_manager) return;

    size_t iter = 0;
    void *item;
    while (lmHashMap_iter(resource_manager->fonts, &iter, &item)) {
        lmFont *font = (lmFont *)item;
        TTF_CloseFont(font->ttf);
    }

    iter = 0;
    while (lmHashMap_iter(resource_manager->fonts, &iter, &item)) {
        lmTexture *texture = (lmTexture *)item;
        SDL_DestroyTexture(texture->sdl_texture);
    }

    lmHashMap_free(resource_manager->fonts);
    lmHashMap_free(resource_manager->textures);
}

void lmResource_load_font(
    lmGame *game,
    char *filepath,
    lm_uint32 size
) {
    lmFont font = lmFont_load(filepath, size);

    lmHashMap_set(game->resource_manager->fonts, &font);
}

lmFont *lmResource_get_font(
    lmGame *game,
    char *name,
    lm_uint32 size
) {
    return lmHashMap_get(
        game->resource_manager->fonts, &(lmFont){.filepath=name, .size=size}
    );
}

void lmResource_load_texture(
    lmGame *game,
    char *filepath
) {
    lmTexture texture = lmTexture_load(game->window, filepath);

    lmHashMap_set(game->resource_manager->textures, &texture);
}

lmTexture *lmResource_get_texture(
    lmGame *game,
    char *name
) {
    return lmHashMap_get(
        game->resource_manager->textures, &(lmTexture){.filepath=name}
    );
}