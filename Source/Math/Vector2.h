#pragma once

#include "Core/Typedefs.h"

class Vector2
{
public:
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
	Vector2 Lerp(const Vector2 &target, float alpha) const
	{
		alpha = std::fmax(0.0f, std::fmin(1.0f, alpha)); // Ensure alpha is clamped between 0 and 1
		return (*this) * (1.0f - alpha) + target * alpha;
	}
	Vector2 operator+(const Vector2 &other) const
	{
		return Vector2(X + other.X, Y + other.Y);
	}
	Vector2 operator-(const Vector2 &other) const
	{
		return Vector2(X - other.X, Y - other.Y);
	}
	Vector2 ToInt() const
	{
		return Vector2(static_cast<int>(X), static_cast<int>(Y));
	}


	bool operator<(const Vector2 &other) const
	{
		return Vector2(X, Y).Length() < other.Length();
	}
	bool operator>(const Vector2& other) const
	{
		return Vector2(X, Y).Length() > other.Length();
	}

	Vector2 operator*(float multiplier) const
	{
		return Vector2(X * multiplier, Y * multiplier);
	}
	
	bool operator==(const Vector2 &other) const
	{
		return (X == other.X) && (Y == other.Y);
	}
	bool operator!=(const Vector2 &other) const
	{
		return (X != other.X) || (Y != other.Y);
	}

	static float Distance(const Vector2& v1, const Vector2& v2) {
		float dx = v2.X - v1.X;
		float dy = v2.Y - v1.Y;
		return std::sqrt(dx * dx + dy * dy);
	}

	Vector2() {
		X = 0;
		Y = 0;
	}
	Vector2(float x, float y) {
		X = x;
		Y = y;
	}
	Vector2(int x, int y) {
		X = static_cast<float>(x);
		Y = static_cast<float>(y);
	}

public:
	float X;
	float Y;
};