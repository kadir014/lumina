/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_ECS_H
#define _LUMINA_ECS_H

#include "lumina/_lumina.h"
#include "lumina/core/constants.h"
#include "lumina/collections/hashmap.h"
#include "lumina/math/vector.h"


/**
 * @file core/ecs.h
 * 
 * @brief Entity-Component-System implementation.
 */


typedef struct {
    lm_uint64 id;
    void *data;
} lmComponent;

typedef struct {
    lm_uint64 id;
    lm_uint64 *comp_ids;
    size_t comps_size;
} lmEntity;

typedef void ( *lmSystem_function)(lm_uint64 entity_id, lmComponent **comps, size_t comps_size);

typedef struct {
    const char *name;
    lmSystem_function function;
    lm_uint64 *comp_ids;
    lm_uint64 comp_ids_size;
} lmSystem;


typedef struct {
    lmHashMap *entities;
    lmHashMap *components;
    lmHashMap *systems;
} lmECS;

lmECS *lmECS_new();

void lmECS_free(lmECS *ecs);

lm_uint64 lmEntity_new(lmECS *ecs);

void lmEntity_add_component(
    lmECS *ecs,
    lm_uint64 entity,
    lm_uint64 comp,
    void *comp_data,
    size_t comp_data_size
);

void lmEntity_add_system(
    lmECS *ecs,
    const char *system_name,
    lmSystem_function system_function,
    lm_uint64 *comp_ids,
    size_t comp_ids_size
);

void lmEntity_run_system(lmECS *ecs, const char *system_name);


typedef struct {
    lmVector2 position;
    float rotation;
    lmVector2 scale;
} lmTransform;

static const lmTransform lmTransform_default = {LM_VEC2(0.0, 0.0), 0.0, LM_VEC2(1.0, 1.0)};


#endif