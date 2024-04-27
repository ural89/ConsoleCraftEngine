#pragma once

#ifndef GE_SHARED
    #define GE_API
#else // GE_SHARED
    #ifdef __GNUC__
        #ifdef GE_BUILD_DLL
            #define GE_API __attribute__((visibility("default")))
        #else
            #define GE_API
        #endif
    #else
        #ifdef GE_BUILD_DLL
            #define GE_API __declspec(dllexport)
        #else
            #define GE_API __declspec(dllimport)
        #endif
    #endif
#endif // GE_SHARED
