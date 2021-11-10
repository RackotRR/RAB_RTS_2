#pragma once
#include "Building.h"


class Spaceport : public Building {
public:
	Spaceport(const Vector2& position) : Building(position) {
		SetType(BuildingType::spaceport); 
	}
};
