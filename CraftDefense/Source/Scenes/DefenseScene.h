#pragma once
#include "Core/Scene.h"
#include <string>

class DefenseScene : public Scene
{
public:
    ~DefenseScene();

    void Init() override;
    void Update(float deltaTime) override;

    void OnLaneBreached(int lane);

private:
    void OnInput(int input);
    void TryPlant();
    void TryShovel();
    void TryCollectSun();
    void EndGame(bool won);
    bool ComputeCanPlant() const;

    class LaneGrid *grid = nullptr;
    class SunBank *bank = nullptr;
    class SunManager *sunManager = nullptr;
    class SeedMenu *seedMenu = nullptr;
    class WaveDirector *waveDirector = nullptr;
    class DefenseHUD *hud = nullptr;
    class GridCursor *cursor = nullptr;

    bool gameEnded = false;
    float endScreenTimer = 0.f;
};
