#pragma once
#include "../../Core.h"
#include "../GameObject.h"
#include <array>

class GE_API ParticleObject : public GameObject
{
public:
	ParticleObject(Scene& scene,  int particleType);
	~ParticleObject()
	{
		
		brickParticle.clear();
		enemyParticle.clear();
		fireParticle.clear();

	}
	void Init() override;
	void Update(float deltaTime) override;
	void OnCollidedBorder(int border) override;
protected:
	float gravity = 50;

	 std::array<Vector2, 5> trailPositions;
	 int trailCount = 0;
	 Vector2 lastPosition;
	 Sprite fireParticle = { {0,2}, {0,0} };
	 Sprite enemyParticle = { {0,6}, {4,0} };
	 Sprite brickParticle = { {2} };
};

