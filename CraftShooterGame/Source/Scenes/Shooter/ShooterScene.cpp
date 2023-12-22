#include "ShooterScene.h"
#include "../../GameObjects/Shooter/PlayerShip.h"
void ShooterScene::CreateGameObjects()
{
	AddGameObject(new PlayerShip(*this), Vector2(20,15));
}
