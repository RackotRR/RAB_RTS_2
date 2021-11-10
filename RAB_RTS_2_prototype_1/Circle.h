#pragma once
#include "Rectangle.h"
#include "Vector2.h" 

// ���������� � ������� � (x, y), �������� r
class Circle
{
public:
	Circle() : x(), y(), r() {}
	Circle(const Vector2& center, int r) : x(center.X), y(center.Y), r(r) {}
	Circle(int x, int y, int r) : x(x), y(y), r(r) {}

	int x, y, r;

	// ���������� Rectangle, � ������� ����������� �� ����������
	operator Rectangle() const;
	bool IsInCircle(const Vector2& pos) const;
};

