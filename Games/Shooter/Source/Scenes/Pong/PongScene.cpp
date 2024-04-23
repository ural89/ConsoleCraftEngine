#include "PongScene.h"
#include "../../GameObjects/Pong/Ball.h"
#include "../../GameObjects/Pong/Paddle.h"
PongScene::PongScene()
{


}

void PongScene::Init()
{
	AddGameObject(new Paddle(1, *this), Vector2(SCREENWIDTH - 2, 10));
	AddGameObject(new Paddle(0, *this), Vector2(1, 1));
	AddGameObject(new Ball(), Vector2(10, 10));

}

