#pragma once
class Component
{
public:
	Component(class GameObject& go) : owner(&go) { owner = &go; }
	virtual ~Component()
	{
		/*if(owner != nullptr)
			delete owner;*/
	}
	virtual void Update(float deltaTime) {};
	virtual void Init() {};
protected:
	GameObject* owner;
};

