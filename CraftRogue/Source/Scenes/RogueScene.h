#pragma once
#include "Core/Scene.h"
class RogueScene : public Scene
{
public:
	void Init() override;
	void Update(float deltaTime) override;

private:
	void SpawnEnemy(int enemyType);

	int numberOfEnemyToSpawn = 5;
	float spawnTime = 1.5f;
	float spawnDurationPassed = 0;
};
