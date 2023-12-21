#include "PongScene.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Paddle.h"
PongScene::PongScene()
{

	AddGameObject(new Paddle(1), Vector2(SCREENWIDTH - 2, 10));
	AddGameObject(new Paddle(0), Vector2(1, 1));
	AddGameObject(new Ball(), Vector2(10, 10));


}

