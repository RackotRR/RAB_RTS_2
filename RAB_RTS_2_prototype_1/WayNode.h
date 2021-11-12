#pragma once
#include "Vector2.h"
/*
Взвешенная вершина
*/
struct WayNode
{ 
	WayNode() = default;
	WayNode(const Vector2& p, int weight) : pos(p), weight(weight) {}

	Vector2 pos{};
	int weight{};
};
 
class HashWayNode {
	size_t operator()(const WayNode& n) const {
		HashVector2 v;
		return v(n.pos);
	}
};