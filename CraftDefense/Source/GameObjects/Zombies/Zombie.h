#pragma once
#include "Core/GameObject.h"
#include <functional>

enum class ZombieState
{
    Walking,
    Eating
};

class Zombie : public GameObject
{
public:
    Zombie(std::string &&n, class Scene &s, class LaneGrid &grid, float maxHealth, float speed, float biteDamage, float biteInterval);

    void Init() override;
    void Update(float deltaTime) override;

    void SetLane(int l) { lane = l; }
    int Lane() const { return lane; }
    void TakeDamage(float dmg) { health -= dmg; }

    std::function<void()> onDied;
    std::function<void(int lane)> onBreached;

protected:
    class LaneGrid &grid;
    float health;
    float speed;
    float biteDamage;
    float biteInterval;
    float biteTimer = 0.f;
    int lane = 0;
    ZombieState state = ZombieState::Walking;
    class Plant *target = nullptr;
};
