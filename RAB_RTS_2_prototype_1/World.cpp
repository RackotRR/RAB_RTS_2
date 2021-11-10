#include "World.h"  
#include <assert.h>
#include "Pathfinder.h"
#include "Objects.h"
 
World::~World() {
	// Удаление данных Level 
	for (int i = 0; i < height; ++i)  
		delete [] ground[i]; 
	delete [] ground;

	for (auto& iter : units)
		delete iter.second; 

	for (auto& iter : buildings)
		delete iter.second; 

	for (auto& iter : resources)
		delete iter.second;

	for (auto& iter : playersData)
		delete iter;
}

void World::ReplaceUnit(const Vector2& key, Unit* unit) {
	auto iter = units.find(key);
	if (iter != units.end()) {
		units.erase(key);
	}
	units[unit->GetPosition()] = unit;
	UpdateChangedCoordinates();
}

void World::AddBuilding(Building* building) {
	buildings[building->GetPosition()] = building;
	UpdateChangedCoordinates();
}
void World::AddUnit(Unit* unit) { 
	units[unit->GetPosition()] = unit;
	UpdateChangedCoordinates();
}
void World::AddResource(Resource* resource) {
	resources[resource->GetPosition()] = resource;
	UpdateChangedCoordinates();
}

ObjectType World::CheckPosition(const Vector2& pos) const {
	// позиция может быть за пределами карты
	if (pos.X < 0 || pos.X >= width ||
		pos.Y < 0 || pos.Y >= height)
		return ObjectType::none;

	// это может быть здание 
	if (auto iter = buildings.find(pos); iter != buildings.end())
		return ObjectType::building;

	// юнит 
	if (auto iter = units.find(pos); iter != units.end())
		return ObjectType::unit;

	if (auto iter = resources.find(pos); iter != resources.end())
		return ObjectType::resource;

	// клетка земли
	return ObjectType::ground;
}

Building* World::GetBuildingAt(const Vector2& pos) {
	auto iter = buildings.find(pos);
	if (iter != buildings.end())
		return iter->second;
	else
		return nullptr;
}
Unit* World::GetUnitAt(const Vector2& pos) {
	auto iter = units.find(pos);
	if (iter != units.end())
		return iter->second;
	else
		return nullptr;
}
Resource* World::GetResourceAt(const Vector2& pos) {
	auto iter = resources.find(pos);
	if (iter != resources.end())
		return iter->second;
	else
		return nullptr;
}
Cell* World::GetGroundAt(const Vector2& pos) {
	// операция безопасна только, если была проведена проверка: CheckPosition(pos) != ObjectType::none;
	return &(ground[pos.Y][pos.X]);
}

const Building* World::GetBuildingAt(const Vector2& pos) const { 
	auto iter = buildings.find(pos);
	if (iter != buildings.end())
		return iter->second;
	else
		return nullptr;
}
const Unit* World::GetUnitAt(const Vector2& pos) const {
	auto iter = units.find(pos);
	if (iter != units.end())
		return iter->second;
	else
		return nullptr;
}
const Resource* World::GetResourceAt(const Vector2& pos) const{
	auto iter = resources.find(pos);
	if (iter != resources.end())
		return iter->second;
	else
		return nullptr;
}
const Cell* World::GetGroundAt(const Vector2& pos) const {
	// операция безопасна только, если была проведена проверка: CheckPosition(pos) != ObjectType::none;
	return &(ground[pos.Y][pos.X]);
}

void World::RemoveUnitFrom(const Vector2& pos) {
	units.erase(pos);
	UpdateChangedCoordinates();
}
void World::RemoveBuildingFrom(const Vector2& pos) {
	buildings.erase(pos);
	UpdateChangedCoordinates();
}
void World::RemoveResourceFrom(const Vector2& pos) {
	resources.erase(pos);
	UpdateChangedCoordinates();
}

PlayerData* World::GetPlayerData(int owner) {
	assert(owner >= 0 && owner < playersData.size());
	return playersData[owner];
}


void World::UpdateChangedCoordinates() {
	for (int i = 0; i < playersData.size(); ++i) {
		int owner = i + 1; // по какой-то причине, owner = 1,2,3... (надо исправить в дальнейшем)
		UpdateVisibilityFor(GetLevel(), owner, playersData[i]->Visibility());
	}
}