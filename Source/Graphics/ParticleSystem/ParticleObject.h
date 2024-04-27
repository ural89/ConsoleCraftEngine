#pragma once

#include "Core/GameObject.h"

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
	void OnCollidedBorder() override;
protected:
	float gravity = 50;

	 std::array<Vector2, 5> trailPositions;
	 int trailCount = 0;
	 Vector2 lastPosition;
	 std::vector<std::vector<int>> fireParticle = { {0,2}, {0,0} };
	 std::vector<std::vector<int>> enemyParticle = { {0,6}, {4,0} };
	 std::vector<std::vector<int>> brickParticle = { {2} };
};

