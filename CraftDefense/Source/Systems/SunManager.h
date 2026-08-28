#pragma once
#include <vector>

class SunManager
{
public:
    SunManager(class Scene &scene, class SunBank &bank);

    void Update(float deltaTime);
    void SpawnAt(int col, int row);
    bool CollectAt(int col, int row);
    bool HasLiveTokenAt(int col, int row) const;

private:
    Scene &scene;
    SunBank &bank;
    std::vector<class SunToken *> tokens;
    float skyTimer = 0.f;
    static constexpr float SKY_SUN_INTERVAL = 10.f;
    static constexpr int SUN_VALUE = 25;
};
