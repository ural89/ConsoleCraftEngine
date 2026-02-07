#include "PolygonCursor.h"
#include "../../../Component/PlayerController.h"
#include "../../../Input.h"
#include "PolygonCreator.h"
Cursor::Cursor(class Scene &scene) : GameObject("PolygonCursor", scene)
{
	Sprite sprite = {{1}};
	SetSprite(sprite);
}

void Cursor::Init()
{
	AddComponent(new PlayerController(*this, 0));
}
