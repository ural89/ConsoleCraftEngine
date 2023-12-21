#pragma once
struct Vector2
{
public:
	Vector2(){}
	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}
	float X;
	float Y;
	bool operator!=(const Vector2& other) const
	{
		return (X != other.X) || (Y != other.Y);
	}
};