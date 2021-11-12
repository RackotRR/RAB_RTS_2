#include <cassert>

#include "PlayerTreasures.h"


void PlayerTreasures::AddGold(int val) {
	assert(val > 0);

	gold += val;
}
void PlayerTreasures::AddBuildingRes(int val) { 
	assert(val > 0);

	buildingRes += val;
}
void PlayerTreasures::AddFuel(int val) {
	assert(val > 0);

	fuel += val;
}

int PlayerTreasures::GetGold() const {
	return gold;
}
int PlayerTreasures::GetBuildingRes() const {
	return buildingRes;
}
int PlayerTreasures::GetFuel() const {
	return fuel;
}

bool PlayerTreasures::TryToTakeGold(int val) {
	if (gold < val) return false;
	
	gold -= val;
	return true;
}
bool PlayerTreasures::TryToTakeBuildingRes(int val) {
	if (buildingRes < val) return false;

	buildingRes -= val;
	return true;
}
bool PlayerTreasures::TryToTakeFuel(int val) {
	if (fuel < val) return false;

	fuel -= val;
	return true;
}

bool PlayerTreasures::Have(int goldNeed, int buildingResNeed, int fuelNeed) const {
	if (gold >= goldNeed &&
		buildingRes >= buildingResNeed &&
		fuel >= fuelNeed)
		return true;
	else
		return false;
}

bool PlayerTreasures::Have(const Price& price) const {
	return Have(price.gold, price.buildingRes, price.fuel);
}

bool PlayerTreasures::Transaction(int goldNeed, int buildingResNeed, int fuelNeed) {
	if (Have(goldNeed, buildingResNeed, fuelNeed)) {
		gold -= goldNeed;
		buildingRes -= buildingResNeed;
		fuel -= fuelNeed;
		return true;
	}
	else
	{
		return false;
	}
}

bool PlayerTreasures::Transaction(const Price& price) {
	return Transaction(price.gold, price.buildingRes, price.fuel);
}