#pragma once

// #include "BuildConfig.h"

#ifdef _WIN32 // Use _WIN64 to check 64-bit
#   ifdef OCTO_BUILD_SHARED
#       define OCTO_API __declspec(dllexport)
#   else
#       define OCTO_API __declspec(dllimport)
#   endif
#elif __linux__
#   ifdef OCTO_BUILD_SHARED
#       define OCTO_API __attribute__((visibility("default")))
#   else
#       define OCTO_API // No need to import anything
#   endif
#else
#   error "Octo Engine is not supported on your platform"
#endif

#ifdef OCTO_ENABLE_ASSERTS
#   define OCTO_ASSERT(x, ...) { if(!(x)) { OCTO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#   define OCTO_CORE_ASSERT(x, ...) { if(!(x)) { OCTO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#   define OCTO_ASSERT(x, ...)
#   define OCTO_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)