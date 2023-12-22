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
		

		PreviousPosition = Position.ToInt();
		
		if (Position.X + x >= SCREENWIDTH) x = -1; if(Position.X + x <= 0) x = 1;
		if (Position.Y + y >= SCREENHEIGHT) y = -1; if (Position.Y + y <= 0) y = 1;
		Position.X += x;
		Position.Y += y;
		if (PreviousPosition != Position.ToInt())
		{
			HasClearedFlag = false;
			
		}
	}
};