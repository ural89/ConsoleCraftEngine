#pragma once
#include "Core/Scene.h"
class ShooterScene : public Scene
{
public:
	~ShooterScene() override
	{
		std::cout << "Destructed main scene" << '\n';
	}
	void Init() override;
	void Update(float deltaTime) override;

private:
	void SpawnEnemy();

	int numberOfEnemyToSpawn = 10;
	float spawnTime = 2.f;
	float spawnDurationPassed = 0;
};

