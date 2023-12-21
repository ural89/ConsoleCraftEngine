#pragma once
#include "Vector.h"
#include <iostream>
struct Transform
{
public:
	Transform() {
		Position = Vector2();
		Rotation = 0;
	};
	Vector2 Position;
	Vector2 PreviousPosition;
	float Rotation;
	bool HasClearedFlag = false; //If removed its previous position from rendering
	friend std::ostream& operator<<(std::ostream& os, const Transform& transform)
	{
		os << "Position:" << transform.Position.X << "," << transform.Position.Y;
		return os;
	}
	void MovePosition(float x, float y)
	{
		HasClearedFlag = false;
		PreviousPosition = Position;
		if (Position.X + x >= SCREENWIDTH || Position.X + x <= 0) return;
		if (Position.Y + y >= SCREENHEIGHT || Position.Y + y <= 0) return;
		Position.X += x;
		Position.Y += y;
	
	/*  //Warp around
		if (Position.X >= SCREENWIDTH)
		{
			PreviousPosition.X = SCREENWIDTH;
			Position.X = 1;
		}
		if (Position.X <= 0)
		{
			PreviousPosition.X = 0;
			Position.X = SCREENWIDTH;
		}*/
	}
};