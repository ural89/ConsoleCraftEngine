#include "Levels.h"

namespace Levels
{
    const std::vector<LevelData> &All()
    {
        static const std::vector<LevelData> levels = {
            // name              leftX rightX groundY  segs budget  pillar  pillarX pillarY startX finishX
            {"L1 First Steps",   30.f, 46.f,   16.f,    6,   340.f,  false,  0.f,    0.f,    24.f,  52.f},
            {"L2 The Span",      26.f, 50.f,   16.f,    8,   360.f,  false,  0.f,    0.f,    20.f,  56.f},
            {"L3 Deep Cut",      20.f, 52.f,   15.f,    10,  420.f,  false,  0.f,    0.f,    14.f,  58.f},
            {"L4 The Pillar",    20.f, 56.f,   15.f,    10,  460.f,  true,   38.f,   19.f,   14.f,  62.f},
        };
        return levels;
    }
}
