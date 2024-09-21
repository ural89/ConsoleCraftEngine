#pragma once
#include "Core/Scene.h"
class EntryScene : public Scene
{
public:
	~EntryScene();
	
	void Init() override;
    void Start() override;
	void Update(float deltaTime) override;


private:

};

