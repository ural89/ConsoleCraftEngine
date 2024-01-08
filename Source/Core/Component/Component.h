#pragma once
class Component
{
public:
	Component(class GameObject& go) : owner(&go) { owner = &go; }
	virtual ~Component()
	{

	}
	virtual void Init() {};
	virtual void Update(float deltaTime) {};
protected:
	GameObject* owner;
};

