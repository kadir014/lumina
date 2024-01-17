/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#ifndef _LUMINA_PLATFORM_H
#define _LUMINA_PLATFORM_H


/**
 * @file platform.h
 * 
 * @brief Platform identification.
 */


#define __LM_LM_STR(x) #x
#define _LM_STR(x) __LM_LM_STR(x)


/*
    Compiler identification
*/

typedef enum {
    lmCompiler_GCC,
    lmCompiler_CLANG,
    lmCompiler_MSVC,
    lmCompiler_UNKNOWN
} lmCompiler;

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)

    #define LM_COMPILER lmCompiler_GCC
    #define LM_COMPILER_VERSION_STR  \
            _LM_STR(__GNUC__) "."       \
            _LM_STR(__GNUC_MINOR__) "." \
            _LM_STR(__GNUC_PATCHLEVEL__)

#elif defined(__clang__)

    #define LM_COMPILER lmCompiler_CLANG
    #define LM_COMPILER_VERSION_STR   \
            _LM_STR(__clang_major_) "."  \
            _LM_STR(__clang_minor__) "." \
            _LM_STR(__clang_patchlevel__)

#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSVC_LANG)

    #define LM_COMPILER lmCompiler_MSVC
    #define LM_COMPILER_VERSION_STR _LM_STR(_MSC_VER)

#else

    #define LM_COMPILER lmCompilerType_UNKNOWN
    #define LM_COMPILER_VERSION_STR ""

#endif


/*
    Platform identification
*/

typedef enum {
    lmPlatform_WEB,
    lmPlatform_WINDOWS,
    lmPlatform_LINUX,
    lmPlatform_MACOS,
    lmPlatform_IOS,
    lmPlatform_ANDROID,
    lmPlatform_UNIX,
    lmPlatform_UNKNOWN,
} lmPlatform;

#if defined(__EMSCRIPTEN__) || defined(__wasi__)

    #define LM_PLATFORM lmPlatform_WEB

#elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

    #define LM_PLATFORM lmPlatform_WINDOWS
    
#elif defined(__linux__) && !defined(__ANDROID__)

    #define LM_PLATFORM lmPlatform_LINUX

#elif defined(__APPLE__) || defined(__MACH__)

    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE

        #define LM_PLATFORM lmPlatform_IOS

    #elif TARGET_OS_MAC

        #define LM_PLATFORM lmPlatform_MACOS

    #endif

#elif defined(__ANDROID__)

    #define LM_PLATFORM lmPlatform_ANDROID

#elif defined(__unix__) || defined(__unix)

    #define LM_PLATFORM lmPlatform_UNIX

#else

    #define LM_PLATFORM lmPlatform_UNKNOWN

#endif


/*
    Architecture identification
*/

typedef enum {
    lmArch_X86_64,
    lmArch_X86,
    lmArch_ARM,
    lmArch_UNKNOWN
} lmArch;

#if defined(__x86_64) || \
    defined(__x86_64) || \
    defined(__amd64)  || \
    defined(__amd64__)

    #define LM_ARCH lmArch_X86_64

#elif defined(i386)     || \
      defined(__i386)   || \
      defined(__i386__) || \
      defined(_X86_)    || \
      defined(__I86__)

    #define LM_ARCH lmArch_X86

#elif defined(__arm__)     || \
      defined(__arm64)     || \
      defined(__aarch64__)

    #define LM_ARCH lmArch_ARM

#else

    #define LM_ARCH lmArch_UNKNOWN

#endif


/**
 * @brief Get the compiler identification as string.
 * 
 * @return char *
 */
static inline const char *lmCompiler_as_string() {
    switch (LM_COMPILER) {
        case lmCompiler_GCC:
            return "GCC";

        case lmCompiler_CLANG:
            return "Clang";

        case lmCompiler_MSVC:
            return "MSVC";

        default:
            return "Unknown";
    }
}

/**
 * @brief Get the platform identification as string.
 * 
 * @return char *
 */
static inline const char *lmPlatform_as_string() {
    switch (LM_PLATFORM) {
        case lmPlatform_WEB:
            return "Web";

        case lmPlatform_WINDOWS:
            return "Windows";

        case lmPlatform_LINUX:
            return "Linux";

        case lmPlatform_MACOS:
            return "MacOS";

        case lmPlatform_IOS:
            return "iOS";

        case lmPlatform_ANDROID:
            return "Android";

        case lmPlatform_UNIX:
            return "Unix";

        default:
            return "Unknown";
    }
}

/**
 * @brief Get the architecture identification as string.
 * 
 * @return char *
 */
static inline const char *lmArch_as_string() {
    switch (LM_ARCH) {
        case lmArch_X86_64:
            return "x86_64";

        case lmArch_X86:
            return "x86";

        case lmArch_ARM:
            return "ARM";

        default:
            return "Unknown";
    }
}


#endif