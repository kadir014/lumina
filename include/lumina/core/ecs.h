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


/**
 * @brief Internal representation of components.
 */
typedef struct {
    lm_uint64 id; /**< ID of the component. */
    lm_uint64 entity_id; /**< ID of the entity this component belongs to. */
    void *data; /**< Data of the component. */
    bool allocated;
} lmComponent;

/**
 * @brief Internal representation of entities.
 */
typedef struct {
    lm_uint64 id; /**< ID of the entity. */
    lm_uint64 *comp_ids; /**< Array of IDs to this entity's components. */
    size_t comps_size; /**< Size of the components array. */
} lmEntity;

// System function type
typedef void ( *lmSystem_function)(lm_uint64 entity_id, lmComponent **comps, size_t comps_size, void *user_context);

/**
 * @brief Internal representation of systems.
 */
typedef struct {
    const char *name; /**< Name of this system. */
    lmSystem_function function; /**< Function of this system. */
    lm_uint64 *comp_ids; /**< Array of component IDs to run the system for. */
    lm_uint64 comp_ids_size; /**< Size of the components array. */
    void *user_context;
} lmSystem;


/**
 * @brief ECS manager.
 */
typedef struct {
    lmHashMap *entities; /**< Hash map of entities. */
    lmHashMap *components; /**< Hash map of components. */
    lmHashMap *systems; /**< Hash map of systems. */
} lmECS;

lmECS *lmECS_new();

void lmECS_free(lmECS *ecs);

lm_uint64 lmECS_new_entity(lmECS *ecs);

void lmECS_add_component(
    lmECS *ecs,
    lm_uint64 entity_id,
    lm_uint64 comp_id,
    void *comp_data,
    size_t comp_data_size
);

void lmECS_add_component_p(
    lmECS *ecs,
    lm_uint64 entity_id,
    lm_uint64 comp_id,
    void *comp_data
);

void lmECS_add_system(
    lmECS *ecs,
    const char *system_name,
    lmSystem_function system_function,
    lm_uint64 *comp_ids,
    size_t comp_ids_size,
    void *user_context
);

void lmECS_run_system(lmECS *ecs, const char *system_name);


#endif