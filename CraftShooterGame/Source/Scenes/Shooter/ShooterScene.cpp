#include "ShooterScene.h"
#include "../../GameObjects/Shooter/PlayerShip.h"
#include "../../GameObjects/Shooter/Enemy.h"
void ShooterScene::CreateGameObjects()
{
	AddGameObject(new PlayerShip(*this), Vector2(20,15));
	srand(static_cast<unsigned int>(time(nullptr)));
	//SpawnEnemy();

}

void ShooterScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
	if (numberOfEnemyToSpawn > 0)
		spawnDurationPassed += deltaTime;
	

	if (spawnDurationPassed >= spawnTime)
	{
		spawnDurationPassed = 0;
		SpawnEnemy();
	}

}

void ShooterScene::SpawnEnemy()
{
	numberOfEnemyToSpawn--;
	int random_number = rand() % 20;

	AddGameObject(new Enemy(*this), Vector2(90, random_number + 2));
}
