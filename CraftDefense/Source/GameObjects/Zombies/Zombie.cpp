#include "Zombie.h"
#include "Grid/LaneGrid.h"
#include "GameObjects/Plants/Plant.h"
#include "DefenseConfig.h"

Zombie::Zombie(std::string &&n, Scene &s, LaneGrid &grid, float maxHealth, float speed, float biteDamage, float biteInterval)
    : GameObject(std::move(n), s), grid(grid), health(maxHealth), speed(speed), biteDamage(biteDamage), biteInterval(biteInterval)
{
}

void Zombie::Init()
{
    grid.RegisterZombie(this);
}

void Zombie::Update(float deltaTime)
{
    if (health <= 0.f)
    {
        grid.UnregisterZombie(this);
        Destroy();
        if (onDied)
            onDied();
        return;
    }

    if (state == ZombieState::Walking)
    {
        transform.MovePosition(-speed * deltaTime, 0);

        Plant *front = grid.FrontPlantFor(*this);
        if (front)
        {
            state = ZombieState::Eating;
            target = front;
            biteTimer = 0.f;
        }
        else if (transform.Position.X <= BREACH_X)
        {
            grid.UnregisterZombie(this);
            int breachedLane = lane;
            Destroy();
            if (onBreached)
                onBreached(breachedLane);
            return;
        }
    }
    else // Eating
    {
        if (!target || grid.At(target->Col(), target->Row()) != target)
        {
            target = nullptr;
            state = ZombieState::Walking;
        }
        else
        {
            biteTimer += deltaTime;
            if (biteTimer >= biteInterval)
            {
                biteTimer -= biteInterval;
                target->TakeBite(biteDamage);
            }
        }
    }
}
