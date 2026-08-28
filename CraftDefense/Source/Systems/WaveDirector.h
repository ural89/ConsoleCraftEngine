#pragma once
#include <vector>

struct WaveEntry
{
    int count;
    float interval;
};

struct Wave
{
    std::vector<WaveEntry> entries;
    float delayBefore;
};

class WaveDirector
{
public:
    WaveDirector(class Scene &scene, class LaneGrid &grid, class DefenseScene &defenseScene);

    void Update(float deltaTime);
    int CurrentWaveNumber() const;
    int TotalWaves() const { return static_cast<int>(waves.size()); }
    bool IsComplete() const { return completed; }

private:
    Scene &scene;
    LaneGrid &grid;
    DefenseScene &defenseScene;
    std::vector<Wave> waves;

    int waveIndex = 0;
    int entryIndex = 0;
    int spawnedInEntry = 0;
    float spawnTimer = 0.f;
    float delayTimer = 0.f;
    bool waveDelayDone = false;
    int aliveCount = 0;
    bool completed = false;
    int lastSpawnLane = -1;

    void BuildWaveTable();
    void SpawnZombie(int lane);
    int PickLane();
};
