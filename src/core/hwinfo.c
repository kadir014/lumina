/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/core/hwinfo.h"

#if LM_PLATFORM == LM_PLATFORM_WINDOWS
    #include <windows.h>
    #include <psapi.h>
#endif


/**
 * @file core/hwinfo.c
 * 
 * @brief Hardware-related information gathering functions.
 */


size_t lm_get_current_memory_usage() {
    #if LM_PLATFORM == LM_PLATFORM_WEB

        return 0;

    #elif LM_PLATFORM == LM_PLATFORM_WINDOWS

        // https://learn.microsoft.com/en-us/windows/win32/psapi/collecting-memory-usage-information-for-a-process

        HANDLE current_process = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS_EX pmc;

        if (GetProcessMemoryInfo(current_process, (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc))) {
            return pmc.WorkingSetSize;
        }
        else {
            return 0;
        }

    #else

        FILE *status = fopen("/proc/self/status", "r");
        
        if (status) {
            char line[128];
            while (fgets(line, 128, status) != NULL) {
                if (strncmp(line, "VmSize:", 7) == 0) {
                    char *val = line + 7;
                    fclose(status);
                    return strtoul(val, NULL, 10) * 1024;
                }
            }
        }
        
        fclose(status);
        return 0;

    #endif
}