#pragma once

//2D-vector mit Vergleichs- und Rechenoperationen
struct CVec2
{
	int x;
	int y;

	CVec2() : x(0), y(0) {}

	CVec2(int xValue, int yValue) : x(xValue), y(yValue) {}

	bool operator==(const CVec2& other) const
	{
		return (x == other.x && y == other.y);
	}

	bool operator!=(const CVec2& other) const
	{
		return !(*this == other);
	}

	bool operator<(const CVec2& other) const
	{
		return (x < other.x, y < other.y);
	}

	bool operator>(const CVec2& other) const
	{
		return (x > other.x, y > other.y);
	}

	bool operator<=(const CVec2& other) const
	{
		return (x <= other.x, y <= other.y);
	}

	bool operator>=(const CVec2& other) const
	{
		return (x >= other.x, y >= other.y);
	}

	CVec2& operator=(const CVec2& other)
	{
		return CVec2(x = other.x, y = other.y);
	}

	CVec2 operator+(const CVec2& other) const
	{
		return CVec2(x + other.x, y + other.y);
	}

	CVec2 operator-(const CVec2& other) const
	{
		return CVec2(x - other.x, y - other.y);
	}

	CVec2 operator*(const CVec2& other) const
	{
		return CVec2(x * other.x, y * other.y);
	}

	inline CVec2 operator*(const int scalar) const
	{
		return CVec2(x * scalar, y * scalar);
	}

	CVec2 operator/(const CVec2& other) const
	{
		return CVec2(x / other.x, y / other.y);
	}

	CVec2 operator/(const int scalar) const
	{
		return CVec2(x / scalar, y / scalar);
	}
};

inline CVec2 operator*(int scalar, const CVec2& other)
{
	return CVec2(other.x * scalar, other.y * scalar);
}