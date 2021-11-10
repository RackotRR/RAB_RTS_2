#pragma once
#include "Vector2.h"
/*
Взвешенная вершина
*/
class Node
{
public:
	Node() : pos(), weight() {}
	Node(const Vector2& p, int weight) : pos(p), weight(weight) {}
	Vector2 pos;
	int weight;
};
 
class HashNode {
	size_t operator()(const Node& n) const {
		HashVector2 v;
		return v(n.pos);
	}
};