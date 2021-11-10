#include "Circle.h"
#include <math.h>

bool Circle::IsInCircle(const Vector2& pos) const{
	int dx = x - pos.X;
	int dy = y - pos.Y;
	return sqrt(dx * dx + dy * dy) < r;
}

Circle::operator Rectangle() const {
	return Rectangle{ x - r, y - r, r * 2, r * 2 };
}