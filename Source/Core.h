#pragma once

#ifdef GE_BUILD_DLL
#define GE_API __declspec(dllexport)
#else
#define GE_API __declspec(dllimport)
#endif
const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 110;

