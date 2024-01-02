#pragma once
#include "Vector.h"
#include <iostream>
#include <vector>
#include "../Core.h"
struct Transform
{
public:
	Transform()
	{
		Position = Vector2();
		Rotation = 0;
	};

	Vector2 Position;
	Vector2 PreviousPosition;

	float Rotation;
	bool HasClearedFlag = false; // If removed its previous position from rendering
	bool HasMovedThisFrame = false;

	void SetChild(Transform &child)
	{
		children.push_back(&child);
	}
	void SetParent(Transform &parent)
	{
		parent.SetChild(*this);
	}
	void MovePosition(float x, float y, bool isCameraMove = false)
	{

		PreviousPosition = Position.ToInt();

		for (auto &child : children)
		{
			child->MovePosition(x, y);
		}
		if (!isCameraMove)
		{
			if (Position.X + x >= SCREENWIDTH)
				x = -1;
			if (Position.X + x <= 0)
				x = 1;
			if (Position.Y + y >= SCREENHEIGHT)
				y = -1;
			if (Position.Y + y <= 0)
				y = 1;
		}
		Position.X += x;
		Position.Y += y;
		if (PreviousPosition != Position.ToInt())
		{
			HasMovedThisFrame = true;
			HasClearedFlag = false;
		}
		else
		{
			HasMovedThisFrame = false;
		}
	}

	friend std::ostream &operator<<(std::ostream &os, const Transform &transform)
	{
		os << "Position:" << transform.Position.X << "," << transform.Position.Y;
		return os;
	}

private:
	std::vector<Transform *> children;
};