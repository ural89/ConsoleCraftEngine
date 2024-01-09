#pragma once
#include "Core/Scene.h"
class RogueScene : public Scene
{
public:
	void Init() override;
	void Update(float deltaTime) override;

private:
	void SpawnEnemy(int enemyType);
	class Rope* rope;
	class Player* player;
	int numberOfEnemyToSpawn = 5;
	float spawnTime = 2;
	float spawnDurationPassed = 0;
};
