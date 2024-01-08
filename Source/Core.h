#pragma once

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


const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 90;

