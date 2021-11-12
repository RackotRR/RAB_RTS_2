#include <cassert>

#include "PlayerResearches.h"


void PlayerResearches::SetMaxHP(BuildingType buildingType, int hp) {
	buildingsMaxHP[buildingType] = hp;
}

void PlayerResearches::SetMaxHP(UnitType unitType, int hp) {
	unitsMaxHP[unitType] = hp;
}

int PlayerResearches::GetMaxHP(BuildingType buildingType) const {
	auto iter = buildingsMaxHP.find(buildingType);
	assert(iter != buildingsMaxHP.end());
	return iter->second;
}

int PlayerResearches::GetMaxHP(UnitType unitType) const {
	auto iter = unitsMaxHP.find(unitType);
	assert(iter != unitsMaxHP.end());
	return iter->second;
}
 
int PlayerResearches::GetVisibility(BuildingType buildingType) const {
	auto iter = buildingsVisibility.find(buildingType);
	assert(iter != buildingsVisibility.end());
	return iter->second;
}
int PlayerResearches::GetVisibility(UnitType unitType) const {
	auto iter = unitsVisibility.find(unitType);
	assert(iter != unitsVisibility.end());
	return iter->second;
}

void PlayerResearches::SetVisibility(BuildingType buildingType, int visibility) {
	buildingsVisibility[buildingType] = visibility;
}
void PlayerResearches::SetVisibility(UnitType unitType, int visibility) {
	unitsVisibility[unitType] = visibility;
} 
int PlayerResearches::GetMaxMovePoints(BuildingType buildingType) const {
	auto iter = buildingsMovePoints.find(buildingType);
	assert(iter != buildingsMovePoints.end());
	return iter->second;
}
int PlayerResearches::GetMaxMovePoints(UnitType unitType) const {
	auto iter = unitsMovePoints.find(unitType);
	assert(iter != unitsMovePoints.end());
	return iter->second;
}

void PlayerResearches::SetMaxMovePoints(BuildingType buildingType, int movePoints) {
	buildingsMovePoints[buildingType] = movePoints;
}
void PlayerResearches::SetMaxMovePoints(UnitType unitType, int movePoints) {
	unitsMovePoints[unitType] = movePoints;
}
 
const Price& PlayerResearches::GetPrice(BuildingType buildingType) const {
	auto iter = buildingsPrice.find(buildingType);
	assert(iter != buildingsPrice.end());
	return iter->second;
}
const Price& PlayerResearches::GetPrice(UnitType unitType) const {
	auto iter = unitsPrice.find(unitType);
	assert(iter != unitsPrice.end());
	return iter->second;
}

void PlayerResearches::SetPrice(BuildingType buildingType, const Price& price) {
	buildingsPrice[buildingType] = price;
}
void PlayerResearches::SetPrice(UnitType unitType, const Price& price) {
	unitsPrice[unitType] = price;
}
 
void PlayerResearches::SetPointsToConstructBuilding(BuildingType buildingType, int points) {
	pointsToConstructBuilding[buildingType] = points;
} 
int PlayerResearches::GetPointsToConstructBuilding(BuildingType buildingType) const {
	auto iter = pointsToConstructBuilding.find(buildingType);
	assert(iter != pointsToConstructBuilding.end());
	return iter->second;
}

void PlayerResearches::SetPointsToProduceUnit(UnitType unitType, int points) {
	pointsToProduceUnit[unitType] = points;
}

int PlayerResearches::GetPointsToProduceUnit(UnitType unitType) const {
	auto iter = pointsToProduceUnit.find(unitType);
	assert(iter != pointsToProduceUnit.end());
	return iter->second;
}