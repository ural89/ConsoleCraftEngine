#pragma once
#include "Core/Scene.h"
class RogueScene : public Scene
{
public:
	void Init() override;
	void Update(float deltaTime) override;

private:
	void SpawnEnemy();

	int numberOfEnemyToSpawn = 10;
	float spawnTime = 1.f;
	float spawnDurationPassed = 0;
};
