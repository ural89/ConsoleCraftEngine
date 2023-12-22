#include "ShooterScene.h"
#include "../../GameObjects/Shooter/PlayerShip.h"
#include "../../GameObjects/Shooter/Enemy.h"
void ShooterScene::CreateGameObjects()
{
	AddGameObject(new PlayerShip(*this), Vector2(20,15));
	AddGameObject(new Enemy(*this), Vector2(60, 15));

}
