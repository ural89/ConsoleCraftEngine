#pragma once
#include "Core/GameObject.h"

class Plant : public GameObject
{
public:
    Plant(std::string &&n, class Scene &s, class LaneGrid &grid, float maxHealth);

    void Init() override;
    void TakeBite(float dmg);

    int Col() const { return col; }
    int Row() const { return row; }
    void SetCell(int c, int r) { col = c; row = r; }
    float HealthFraction() const { return maxHealth > 0.f ? health / maxHealth : 0.f; }

protected:
    virtual void OnDied();

    class LaneGrid &grid;
    float health;
    float maxHealth;

private:
    int col = -1;
    int row = -1;
};
