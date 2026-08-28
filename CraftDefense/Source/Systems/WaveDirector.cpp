#include "WaveDirector.h"
#include "Scenes/DefenseScene.h"
#include "GameObjects/Zombies/BasicZombie.h"
#include "DefenseConfig.h"
#include <cstdlib>

WaveDirector::WaveDirector(Scene &scene, LaneGrid &grid, DefenseScene &defenseScene)
    : scene(scene), grid(grid), defenseScene(defenseScene)
{
    BuildWaveTable();
}

void WaveDirector::BuildWaveTable()
{
    waves = {
        {{{2, 3.0f}}, 5.f},
        {{{3, 2.5f}}, 5.f},
        {{{4, 2.2f}}, 6.f},
        {{{5, 2.0f}}, 6.f},
        {{{5, 1.8f}, {2, 1.0f}}, 7.f},
        {{{7, 1.8f}}, 7.f},
        {{{7, 1.6f}, {3, 1.0f}}, 8.f},
        {{{00, 1.5f}}, 8.f},
        {{{00, 1.4f}, {4, 0.8f}}, 9.f},
        {{{04, 1.2f}}, 10.f},
    };
}

int WaveDirector::CurrentWaveNumber() const
{
    int n = waveIndex + 1;
    if (n > static_cast<int>(waves.size()))
        n = static_cast<int>(waves.size());
    return n;
}

void WaveDirector::Update(float deltaTime)
{
    if (completed)
        return;

    Wave &wave = waves[waveIndex];

    if (!waveDelayDone)
    {
        delayTimer += deltaTime;
        if (delayTimer >= wave.delayBefore)
            waveDelayDone = true;
        else
            return;
    }

    if (entryIndex >= static_cast<int>(wave.entries.size()))
    {
        if (aliveCount == 0)
        {
            waveIndex++;
            entryIndex = 0;
            spawnedInEntry = 0;
            spawnTimer = 0.f;
            delayTimer = 0.f;
            waveDelayDone = false;

            if (waveIndex >= static_cast<int>(waves.size()))
                completed = true;
        }
        return;
    }

    WaveEntry &entry = wave.entries[entryIndex];
    spawnTimer += deltaTime;

    if (spawnedInEntry == 0 || spawnTimer >= entry.interval)
    {
        spawnTimer = 0.f;
        SpawnZombie(PickLane());
        spawnedInEntry++;

        if (spawnedInEntry >= entry.count)
        {
            entryIndex++;
            spawnedInEntry = 0;
        }
    }
}

int WaveDirector::PickLane()
{
    int lane;
    do
    {
        lane = rand() % GRID_ROWS;
    } while (lane == lastSpawnLane && GRID_ROWS > 1);

    lastSpawnLane = lane;
    return lane;
}

void WaveDirector::SpawnZombie(int lane)
{
    BasicZombie *zombie = new BasicZombie(scene, grid);
    zombie->SetLane(lane);
    zombie->onDied = [this]() { aliveCount--; };
    zombie->onBreached = [this](int breachedLane) { defenseScene.OnLaneBreached(breachedLane); };

    scene.AddGameObject(zombie, LaneSpawnPos(lane));
    aliveCount++;
}
