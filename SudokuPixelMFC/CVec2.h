#pragma once


class CVec2
{
public:
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

	CVec2& operator=(const CVec2& other)
	{
		return CVec2(x = other.x, y = other.y);
	}

	CVec2& operator+(const CVec2& other)
	{
		return CVec2(x + other.x, y + other.y);
	}

	CVec2& operator-(const CVec2& other)
	{
		return CVec2(x - other.x, y - other.y);
	}
};

