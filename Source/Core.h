#pragma once

#ifdef GE_BUILD_DLL
    #ifdef __GNUC__
        #define GE_API __attribute__((visibility("default")))
    #else
        #define GE_API
    #endif
#else
    #define GE_API
#endif

const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 110;

