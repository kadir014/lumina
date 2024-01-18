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

#define LM_COMPILER_GCC    0
#define LM_COMPILER_CLANG  1
#define LM_COMPILER_MSVC   2
#define LM_COMPILER_UNKNOW 3

#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)

    #define LM_COMPILER LM_COMPILER_GCC
    #define LM_COMPILER_VERSION_STR  \
            _LM_STR(__GNUC__) "."       \
            _LM_STR(__GNUC_MINOR__) "." \
            _LM_STR(__GNUC_PATCHLEVEL__)

#elif defined(__clang__)

    #define LM_COMPILER LM_COMPILER_CLANG
    #define LM_COMPILER_VERSION_STR   \
            _LM_STR(__clang_major_) "."  \
            _LM_STR(__clang_minor__) "." \
            _LM_STR(__clang_patchlevel__)

#elif defined(_MSC_VER) || defined(_MSC_FULL_VER) || defined(_MSVC_LANG)

    #define LM_COMPILER LM_COMPILER_MSVC
    #define LM_COMPILER_VERSION_STR _LM_STR(_MSC_VER)

#else

    #define LM_COMPILER LM_COMPILERType_UNKNOWN
    #define LM_COMPILER_VERSION_STR ""

#endif


/*
    Platform identification
*/

#define LM_PLATFORM_WEB     4
#define LM_PLATFORM_WINDOWS 5
#define LM_PLATFORM_LINUX   6
#define LM_PLATFORM_MACOS   7
#define LM_PLATFORM_IOS     8
#define LM_PLATFORM_ANDROID 9
#define LM_PLATFORM_UNIX    10
#define LM_PLATFORM_UNKNOWN 11

#if defined(__EMSCRIPTEN__)

    #define LM_PLATFORM LM_PLATFORM_WEB

#elif defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)

    #define LM_PLATFORM LM_PLATFORM_WINDOWS
    
#elif defined(__linux__) && !defined(__ANDROID__)

    #define LM_PLATFORM LM_PLATFORM_LINUX

#elif defined(__APPLE__) || defined(__MACH__)

    #include <TargetConditionals.h>
    #if TARGET_OS_IPHONE

        #define LM_PLATFORM LM_PLATFORM_IOS

    #elif TARGET_OS_MAC

        #define LM_PLATFORM LM_PLATFORM_MACOS

    #endif

#elif defined(__ANDROID__)

    #define LM_PLATFORM LM_PLATFORM_ANDROID

#elif defined(__unix__) || defined(__unix)

    #define LM_PLATFORM LM_PLATFORM_UNIX

#else

    #define LM_PLATFORM LM_PLATFORM_UNKNOWN

#endif


/*
    Architecture identification
*/

#define LM_ARCH_X86_64  12
#define LM_ARCH_X86     13
#define LM_ARCH_ARM     14
#define LM_ARCH_WASM    15
#define LM_ARCH_UNKNOWN 16

#if defined(__x86_64) || \
    defined(__x86_64) || \
    defined(__amd64)  || \
    defined(__amd64__)

    #define LM_ARCH LM_ARCH_X86_64

#elif defined(i386)     || \
      defined(__i386)   || \
      defined(__i386__) || \
      defined(_X86_)    || \
      defined(__I86__)

    #define LM_ARCH LM_ARCH_X86

#elif defined(__arm__)     || \
      defined(__arm64)     || \
      defined(__aarch64__)

    #define LM_ARCH LM_ARCH_ARM

#elif LM_PLATFORM == LM_PLATFORM_WEB

    #define LM_ARCH LM_ARCH_WASM

#else

    #define LM_ARCH LM_ARCH_UNKNOWN

#endif


/**
 * @brief Get the compiler identification as string.
 * 
 * @return char *
 */
static inline const char *LM_COMPILER_as_string() {
    switch (LM_COMPILER) {
        case LM_COMPILER_GCC:
            return "GCC";

        case LM_COMPILER_CLANG:
            return "Clang";

        case LM_COMPILER_MSVC:
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
static inline const char *LM_PLATFORM_as_string() {
    switch (LM_PLATFORM) {
        case LM_PLATFORM_WEB:
            return "Web";

        case LM_PLATFORM_WINDOWS:
            return "Windows";

        case LM_PLATFORM_LINUX:
            return "Linux";

        case LM_PLATFORM_MACOS:
            return "MacOS";

        case LM_PLATFORM_IOS:
            return "iOS";

        case LM_PLATFORM_ANDROID:
            return "Android";

        case LM_PLATFORM_UNIX:
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
static inline const char *LM_ARCH_as_string() {
    switch (LM_ARCH) {
        case LM_ARCH_X86_64:
            return "x86_64";

        case LM_ARCH_X86:
            return "x86";

        case LM_ARCH_ARM:
            return "ARM";

        case LM_ARCH_WASM:
            return "WebAssembly";

        default:
            return "Unknown";
    }
}


#endif