#include <cassert>

#include "World.h"  
#include "Pathfinder.h"
#include "Objects.h"
   
World::~World() {  
	for (auto& iter : level.units)
		delete iter.second; 

	for (auto& iter : level.buildings)
		delete iter.second; 

	for (auto& iter : level.resources)
		delete iter.second;

	for (auto& iter : level.playersData)
		delete iter;
}

void World::ReplaceUnit(const Vector2& key, Unit* unit) {
	auto iter = level.units.find(key);
	if (iter != level.units.end()) {
		level.units.erase(key);
	}
	level.units[unit->GetPosition()] = unit;
	UpdateChangedCoordinates();
}

void World::AddBuilding(Building* building) {
	level.buildings[building->GetPosition()] = building;
	UpdateChangedCoordinates();
}
void World::AddUnit(Unit* unit) { 
	level.units[unit->GetPosition()] = unit;
	UpdateChangedCoordinates();
}
void World::AddResource(Resource* resource) {
	level.resources[resource->GetPosition()] = resource;
	UpdateChangedCoordinates();
}

ObjectType World::CheckPosition(const Vector2& pos) const {
	// позиция может быть за пределами карты
	if (pos.X < 0 || pos.X >= level.width ||
		pos.Y < 0 || pos.Y >= level.height)
		return ObjectType::none;

	// это может быть здание 
	if (auto iter = level.buildings.find(pos); iter != level.buildings.end())
		return ObjectType::building;

	// юнит 
	if (auto iter = level.units.find(pos); iter != level.units.end())
		return ObjectType::unit;

	if (auto iter = level.resources.find(pos); iter != level.resources.end())
		return ObjectType::resource;

	// клетка земли
	return ObjectType::ground;
}

Building* World::GetBuildingAt(const Vector2& pos) {
	auto iter = level.buildings.find(pos);
	if (iter != level.buildings.end())
		return iter->second;
	else
		return nullptr;
}
Unit* World::GetUnitAt(const Vector2& pos) {
	auto iter = level.units.find(pos);
	if (iter != level.units.end())
		return iter->second;
	else
		return nullptr;
}
Resource* World::GetResourceAt(const Vector2& pos) {
	auto iter = level.resources.find(pos);
	if (iter != level.resources.end())
		return iter->second;
	else
		return nullptr;
}
Cell* World::GetGroundAt(const Vector2& pos) {
	// операция безопасна только, если была проведена проверка: CheckPosition(pos) != ObjectType::none;
	return &level.ground(pos.X, pos.Y);
}

const Building* World::GetBuildingAt(const Vector2& pos) const { 
	auto iter = level.buildings.find(pos);
	if (iter != level.buildings.end())
		return iter->second;
	else
		return nullptr;
}
const Unit* World::GetUnitAt(const Vector2& pos) const {
	auto iter = level.units.find(pos);
	if (iter != level.units.end())
		return iter->second;
	else
		return nullptr;
}
const Resource* World::GetResourceAt(const Vector2& pos) const{
	auto iter = level.resources.find(pos);
	if (iter != level.resources.end())
		return iter->second;
	else
		return nullptr;
}
const Cell* World::GetGroundAt(const Vector2& pos) const {
	// операция безопасна только, если была проведена проверка: CheckPosition(pos) != ObjectType::none;
	return &level.ground(pos.X, pos.Y);
}

void World::RemoveUnitFrom(const Vector2& pos) {
	level.units.erase(pos);
	UpdateChangedCoordinates();
}
void World::RemoveBuildingFrom(const Vector2& pos) {
	level.buildings.erase(pos);
	UpdateChangedCoordinates();
}
void World::RemoveResourceFrom(const Vector2& pos) {
	level.resources.erase(pos);
	UpdateChangedCoordinates();
}

PlayerData* World::GetPlayerData(int owner) {
	assert(owner >= 0 && owner < level.playersData.size());
	return level.playersData[owner];
}


void World::UpdateChangedCoordinates() {
	for (int i = 0; i < level.playersData.size(); ++i) {
		int owner = i + 1; // по какой-то причине, owner = 1,2,3... (надо исправить в дальнейшем)
		UpdateVisibilityFor(GetLevel(), owner, level.playersData[i]->Visibility());
	}
}