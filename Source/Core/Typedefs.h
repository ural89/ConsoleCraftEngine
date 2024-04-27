#pragma once


#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <iostream>

#include <atomic>
#include <type_traits>

#include <ctime>
#include <cmath>

#include <memory>
#include <algorithm>
#include <functional>

#include <algorithm>
#include <vector>
#include <map>
#include <array>
#include <queue>

#include <string>

#include <thread>

#include <conio.h>

#ifdef OS_WINDOWS
#include <Windows.h>
#else // OS_WINDOWS
#include "ncurses.h"
#endif // OS_WINDOWS

#include "Export.h"

// DEBUG_ENABLED
#ifdef _DEBUG
	#define DEBUG_ENABLED
#endif // _DEBUG

// ALWAYS_INLINE
#ifndef ALWAYS_INLINE
	#if defined(__GNUC__)
		#define ALWAYS_INLINE __attribute__((always_inline)) inline
	#elif defined(_MSC_VER)
		#define ALWAYS_INLINE __forceinline
	#else
		#define ALWAYS_INLINE inline
	#endif
#endif // ALWAYS_INLINE

// FORCE_INLINE
#ifndef FORCE_INLINE
	#ifdef DEBUG_ENABLED
		#define FORCE_INLINE inline
	#else // DEBUG_ENABLED
		#define FORCE_INLINE ALWAYS_INLINE
	#endif // DEBUG_ENABLED
#endif // FORCE_INLINE

#undef min
#undef max


// These should ideally be somewhere else!!!
const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 80;
