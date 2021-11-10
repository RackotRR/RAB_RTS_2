#pragma once
#include "Building.h"

class Factory : public Building {
public:
	Factory(const Vector2& position) : Building(position) {
		SetType(BuildingType::factory); 
	}
private: 
};