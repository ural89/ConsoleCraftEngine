#pragma once
#include <cmath>
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
	Vector2 operator +(const Vector2& other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}
	Vector2 operator -(const Vector2& other) const
	{
		return Vector2(X - other.X, Y - other.Y);
	}
	Vector2 ToInt() const
	{
		return Vector2(static_cast<int>(X), static_cast<int>(Y));
	}
	Vector2 operator*(float multiplier) const
	{
		return Vector2(X * multiplier, Y * multiplier);
	}
	float Length() const
	{
		return std::sqrt(X * X + Y * Y);
	}

	void Normalize()
	{
		float length = Length();
		if (length != 0.0f)
		{
			X /= length;
			Y /= length;
		}
	}
	Vector2 Lerp(const Vector2& target, float alpha) const
	{
		alpha = std::fmax(0.0f, std::fmin(1.0f, alpha)); // Ensure alpha is clamped between 0 and 1
		return (*this) * (1.0f - alpha) + target * alpha;
	}
};