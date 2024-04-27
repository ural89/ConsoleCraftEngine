#pragma once

#include "Core/Typedefs.h"

// @TODO: This will need a redesign.
//        A Component holds a GameObject
//        But.......
//        A GameObject has a list of Components
//        My first thought is to have a GameObjectComponent???
class GameObject;

class Component
{
public:
	virtual void Init() {}
	virtual void Update(float deltaTime) {}

	Component(GameObject& go) : owner(&go) { owner = &go; }
	virtual ~Component() {}

protected:
	GameObject* owner;
};
