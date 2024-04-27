#pragma once

#include "Input/Input.h"
#include "Core/GameObject.h"

class Paddle : public GameObject
{
public:
	Paddle(int playerNo, class Scene& scene) : GameObject("Paddle", scene)
	{
		this->playerNo = playerNo;
		symbol = '\xDB';
	}

	
	void Init() override;

	friend std::ostream& operator<<(std::ostream& os, const Paddle& paddle)
	{
		os << "Paddle position: " << paddle.transform << "\n";
		return os;
	}
private:
	int playerNo;

};