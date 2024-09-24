#pragma once
#include "Vector.h"
#include <iostream>
#include <vector>
#include "../Core.h"

const int LEFTBORDER = 0;
const int TOPBORDER = 1;
const int RIGHTBORDER = 2;
const int BOTTOMBORDER = 3;

struct Transform
{
public:
	Transform()
	{
		Position = Vector2(0, 0);
		Rotation = 0;
		PreviousPosition = Vector2(0, 0);
	};
	Transform(Vector2 position, Vector2 size, float rotation) : Position(position), Size(size), Rotation(rotation){}
	Vector2 Position;
	Vector2 PreviousPosition;
	Vector2 RopePreviousPosition;
	Vector2 Size;
	Transform* Parent = nullptr;
	
	float Rotation;
	bool IsStatic = false;
	bool HasClearedFlag = false; // If removed its previous position from rendering
	bool HasMovedThisFrame = true;
	bool HasOwnerDestroyed = false;

	void SetChild(Transform &child)
	{
		children.push_back(&child);
	}
	void SetParent(Transform &parent)
	{
		Parent = &parent;
		parent.SetChild(*this);
	}
	void SetPosition(float x, float y)
	{
		if(IsStatic) return;
		PreviousPosition = Position.ToInt();
		Position = Vector2(x, y);
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
	Vector2 GetCenterPosition() const
	{
		return Position + Size / 2;
	}
	void MovePosition(float x, float y, bool isCameraMove = false)
	{
		
		PreviousPosition = Position.ToInt();

		for (auto &child : children)
		{
			child->MovePosition(x, y);
		}
	
		if(IsStatic) return;
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
