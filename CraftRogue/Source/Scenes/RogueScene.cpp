#include "RogueScene.h"
#include "../GameObjects/Player.h"
#include "CoreStructs/Vector.h"
void RogueScene::Init()
{
    AddGameObject(new Player(*this), Vector2(10, 10));

}