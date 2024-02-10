/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/core/ecs.h"
#include "lumina/math/hash.h"


/**
 * @file core/ecs.c
 * 
 * @brief Entity-Component-System implementation.
 */


static lm_uint64 _lm_entity_hash(void *item) {
    lmEntity *entity = (lmEntity *)item;
    // Entity IDs are supposed to be unique so no need to hash.
    return entity->id;
}

static lm_uint64 _lm_comp_hash(void *item) {
    lmComponent *comp = (lmComponent *)item;
    return lm_u64cantor(comp->id, comp->entity_id);
}

static lm_uint64 _lm_system_hash(void *item) {
    lmSystem *system = (lmSystem *)item;
    return lm_fnv1a(system->name);
}


lmECS *lmECS_new() {
    lmECS *ecs = LM_NEW(lmECS);
    LM_MEMORY_ASSERT(ecs);

    ecs->entities = lmHashMap_new(sizeof(lmEntity), 0, _lm_entity_hash);
    ecs->components = lmHashMap_new(sizeof(lmComponent), 0, _lm_comp_hash);
    ecs->systems = lmHashMap_new(sizeof(lmSystem), 0, _lm_system_hash);

    return ecs;
}

void lmECS_free(lmECS *ecs) {
    if (!ecs) return;

    size_t i = 0;
    void *item;
    while (lmHashMap_iter(ecs->entities, &i, &item)) {
        lmEntity *entity = (lmEntity *)item;
        free(entity->comp_ids);
    }

    i = 0;
    while (lmHashMap_iter(ecs->components, &i, &item)) {
        lmComponent *comp = (lmComponent *)item;
        free(comp->data);
    }

    i = 0;
    while (lmHashMap_iter(ecs->systems, &i, &item)) {
        lmSystem *system = (lmSystem *)item;
        free(system->comp_ids);
    }

    lmHashMap_free(ecs->entities);
    lmHashMap_free(ecs->components);
    lmHashMap_free(ecs->systems);
    free(ecs);
}

lm_uint64 lmEntity_new(lmECS *ecs) {
    lm_uint64 entity = ecs->entities->count;

    lm_uint64 *comp_ids = (lm_uint64 *)malloc(sizeof(lm_uint64) * LM_MAX_COMPONENTS);
    LM_MEMORY_ASSERT(comp_ids);

    lmHashMap_set(ecs->entities, &(lmEntity){.id=entity, .comp_ids=comp_ids, .comps_size=0});

    return entity;
}

void lmEntity_add_component(
    lmECS *ecs,
    lm_uint64 entity_id,
    lm_uint64 comp_id,
    void *comp_data,
    size_t comp_data_size
) {
    // Copy the component data passed by user to heap so it doesn't deallocate
    // when we go out of frame.
    // The memory is handled by the entity manager.
    void *heap_comp_data = malloc(comp_data_size);
    memcpy(heap_comp_data, comp_data, comp_data_size);
    lmHashMap_set(ecs->components, &(lmComponent){.id=comp_id, .entity_id=entity_id, .data=heap_comp_data});

    lmEntity *entity = lmHashMap_get(ecs->entities, &(lmEntity){.id=entity_id});
    entity->comp_ids[entity->comps_size] = comp_id;
    entity->comps_size++;
}

void lmEntity_add_system(
    lmECS *ecs,
    const char *system_name,
    lmSystem_function system_function,
    lm_uint64 *comp_ids,
    size_t comp_ids_size
) {
    lm_uint64 *heap_comp_ids = (lm_uint64 *)malloc(sizeof(lm_uint64) * comp_ids_size);

    for (size_t i = 0; i < comp_ids_size; i++) {
        heap_comp_ids[i] = comp_ids[i];
    }

    lmHashMap_set(ecs->systems, &(lmSystem){.name=system_name, .function=system_function, .comp_ids=heap_comp_ids, .comp_ids_size=comp_ids_size});
}

static inline bool _lm_array_match(lm_uint64 arr1[], size_t size1, lm_uint64 arr2[], size_t size2) {
    lm_int64 sum = 0;

    for (size_t i = 0; i < size1; i++) {
        sum += arr1[i];
    }

    for (size_t i = 0; i < size2; i++) {
        sum -= arr2[i];
    }

    return (sum == 0);
}

void lmEntity_run_system(lmECS *ecs, const char *system_name) {
    lmSystem *system = (lmSystem *)lmHashMap_get(ecs->systems, &(lmSystem){.name=system_name});
    size_t system_comps = system->comp_ids_size;

    lmComponent **comps = (lmComponent **)malloc(sizeof(lmComponent *) * LM_MAX_COMPONENTS);

    size_t i = 0;
    void *item;
    while (lmHashMap_iter(ecs->entities, &i, &item)) {
        lmEntity *entity = (lmEntity *)item;

        // Entity has all the components the system requires
        if (_lm_array_match(entity->comp_ids, entity->comps_size, system->comp_ids, system->comp_ids_size)) {
            for (size_t j = 0; j < system_comps; j++) {
                comps[j] = lmHashMap_get(ecs->components, &(lmComponent){.id=system->comp_ids[j], .entity_id=entity->id});
            }

            system->function(entity->id, comps, system_comps);
        }
    }

    free(comps);
}