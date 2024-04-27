#pragma once


#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <iostream>

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

#ifdef __GNUC__
#include "ncurses.h"
#else
#include <Windows.h>
#endif

#ifdef __GNUC__
#include "../conio.h"
#else
#include <conio.h>
#endif


#include "Export.h"


#undef min
#undef max

// These should ideally be somewhere else!!!
const int SCREENHEIGHT = 25;
const int SCREENWIDTH = 80;


