#include "RogueScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Enemy.h"
#include "CoreStructs/Vector.h"
void RogueScene::Init()
{
    AddGameObject(new Player(*this), Vector2(10, 10));
    AddGameObject(new EnemyRogue(*this), Vector2(20, 20));

}