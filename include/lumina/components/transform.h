/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_COMPONENTS_TRANSFORM_H
#define _LUMINA_COMPONENTS_TRANSFORM_H

#include "lumina/_lumina.h"
#include "lumina/math/vector.h"


/**
 * @file components/transform.h
 * 
 * @brief 2D transform component.
 */


/**
 * @brief 2D transform component.
 */
typedef struct {
    lmVector2 position; /**< Position of the transform. */
    float rotation; /**< Rotation of the transform as angle. */
    lmVector2 scale; /**< Scale of the transform. */
} lmTransform;

/**
 * @brief Default transform value.
 */
static const lmTransform lmTransform_default = {
    LM_VEC2(0.0, 0.0),
    0.0,
    LM_VEC2(1.0, 1.0)
};


#endif