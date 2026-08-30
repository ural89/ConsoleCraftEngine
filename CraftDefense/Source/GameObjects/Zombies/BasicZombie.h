#pragma once
#include "GameObjects/Zombies/Zombie.h"

class BasicZombie : public Zombie
{
public:
    float MaxHealth = 4.f;

    BasicZombie(class Scene &s, class LaneGrid &grid);

    void Init() override;
};
