#pragma once
#include <vector>
#include <unordered_map> 
#include <string> 

#include "Vector2.h"
#include "PlayerData.h"
#include "ObjectType.h"
#include "Array2D.h"
#include "Cell.h"

class Resource;
class Unit;
class Building;

/*
Абстракция данных о мире 
*/
struct Level
{
	Level(int width, int height, int playersNum)
		:
		playersNum{ playersNum },
		size{ width, height },
		ground{ width, height } {}

	// нельзя копировать
	Level(Level&) = delete;
	Level& operator=(Level&) = delete;

	// можно перемещать
	Level(Level&&) noexcept = default;
	Level& operator=(Level&&) noexcept = default;

	~Level();

	const int playersNum; 
	const Vector2 size; 
	Array2D<Cell> ground;

	std::string name, description; 
	std::vector<PlayerData*> playersData;

	std::unordered_map<Vector2, Unit*, HashVector2> units;
	std::unordered_map<Vector2, Building*, HashVector2> buildings;
	std::unordered_map<Vector2, Resource*, HashVector2> resources;
};