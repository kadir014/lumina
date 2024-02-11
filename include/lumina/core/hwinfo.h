/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_HWINFO_H
#define _LUMINA_HWINFO_H

#include "lumina/_lumina.h"


/**
 * @file core/hwinfo.h
 * 
 * @brief Hardware-related information gathering functions.
 */


/**
 * @brief Get memory usage of the current process in bytes.
 * 
 * Returns 0 if failed.
 * 
 * @return size_t 
 */
size_t lm_get_current_memory_usage();



#endif