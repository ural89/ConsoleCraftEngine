#include "PolygonCursor.h"
#include "PolygonCreator.h"
#include "../../../Input.h"
#include "../../../Component/PlayerController.h"
Cursor::Cursor(class Scene &scene) : GameObject("PolygonCursor", scene)
{
    sprite = {{1}};
}

void Cursor::Init()
{
    AddComponent(new PlayerController(*this, 0));

}


