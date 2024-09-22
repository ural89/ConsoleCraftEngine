#pragma once
#include <cmath>
#include <ostream>
#include <string>
const int UPDIRECTION = 1;
const int RIGHTDIRECTION = 2;
const int DOWNDIRECTION = 3;
const int LEFTDIRECTION = 4;
struct Vector2
{
public:
	Vector2() {}
	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}
	float X;
	float Y;
	bool operator!=(const Vector2 &other) const
	{
		return (X != other.X) || (Y != other.Y);
	}
	bool operator==(const Vector2 &other) const
	{
		return (X == other.X) && (Y == other.Y);
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
	Vector2 &operator+=(const Vector2 &other)
	{
		X += other.X;
		Y += other.Y;
		return *this;
	}
	Vector2 &operator-=(const Vector2 &other)
	{
		X -= other.X;
		Y -= other.Y;
		return *this;
	}

	Vector2 operator*(float multiplier) const
	{
		return Vector2(X * multiplier, Y * multiplier);
	}
	friend std::ostream &operator<<(std::ostream &os, const Vector2 &vec)
	{
		os << "(" << vec.X << ", " << vec.Y << ")";
		return os;
	}
	std::string to_string() const
	{
		return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
	}
	bool operator<(const Vector2 &other) const
	{
		if (X == other.X)
			return Y < other.Y; // Compare y if x is the same
		return X < other.X;		// Compare x firstr
	}
	bool operator>(const Vector2 &other) const
	{
		return Vector2(X, Y).Length() > other.Length();
	}
	float Length() const
	{
		return std::sqrt(X * X + Y * Y);
	}
	int LengthInt() const
	{
		return ceil(std::sqrt(X * X + Y * Y));
	}
	static float Distance(const Vector2 &v1, const Vector2 &v2)
	{
		float dx = v2.X - v1.X;
		float dy = v2.Y - v1.Y;
		return std::sqrt(dx * dx + dy * dy);
	}
	float Dot(const Vector2 &other) const
	{
		return X * other.X + Y * other.Y;
	}

	Vector2 operator/(float scalar) const
	{
		if (scalar != 0)
		{
			return Vector2(X / scalar, Y / scalar);
		}
		else
		{

			return Vector2(0.0f, 0.0f);
		}
	}
	Vector2 operator/(const Vector2 &other) const
	{
		if (other.X != 0 && other.Y != 0)
		{
			return Vector2(X / other.X, Y / other.Y);
		}
		else
		{

			return Vector2(0.0f, 0.0f);
		}
	}
	Vector2 Normal() const
	{

		return Vector2(-Y, X);
	}

	Vector2 Perpendicular() const
	{
		return Vector2{-Y, X};
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
		alpha = std::fmax(0.0f, std::fmin(1.0f, alpha));
		return (*this) * (1.0f - alpha) + target * alpha;
	}
};
