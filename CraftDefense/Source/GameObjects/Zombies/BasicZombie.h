#pragma once
#include "GameObjects/Zombies/Zombie.h"

class BasicZombie : public Zombie
{
public:
    BasicZombie(class Scene &s, class LaneGrid &grid);

    void Init() override;
};
