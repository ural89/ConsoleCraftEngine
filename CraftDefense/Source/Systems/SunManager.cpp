#include "SunManager.h"
#include "SunBank.h"
#include "Core/Scene.h"
#include "GameObjects/SunToken.h"
#include "DefenseConfig.h"
#include <algorithm>
#include <cstdlib>

SunManager::SunManager(Scene &scene, SunBank &bank)
    : scene(scene), bank(bank)
{
}

void SunManager::Update(float deltaTime)
{
    skyTimer += deltaTime;
    if (skyTimer >= SKY_SUN_INTERVAL)
    {
        skyTimer = 0.f;
        SpawnAt(rand() % GRID_COLS, rand() % GRID_ROWS);
    }

    tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                                 [](SunToken *t) { return t->isDestroyedFlag; }),
                 tokens.end());
}

void SunManager::SpawnAt(int col, int row)
{
    SunToken *token = new SunToken(scene, col, row);
    scene.AddGameObject(token, CellToWorld(col, row) + Vector2(2, 1));
    tokens.push_back(token);
}

bool SunManager::CollectAt(int col, int row)
{
    for (auto t : tokens)
    {
        if (!t->isDestroyedFlag && t->Col() == col && t->Row() == row)
        {
            bank.Earn(SUN_VALUE);
            t->Destroy();
            return true;
        }
    }
    return false;
}

bool SunManager::HasLiveTokenAt(int col, int row) const
{
    for (auto t : tokens)
    {
        if (!t->isDestroyedFlag && t->Col() == col && t->Row() == row)
            return true;
    }
    return false;
}
