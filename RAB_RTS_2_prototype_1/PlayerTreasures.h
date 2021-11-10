#pragma once
#include "Price.h"

class PlayerTreasures
{
public:
	PlayerTreasures() : gold(), buildingRes(), fuel() {}
	PlayerTreasures(int gold, int buildingRes, int fuel) : gold(gold), buildingRes(buildingRes), fuel(fuel) {}

	void AddGold(int val);
	void AddBuildingRes(int val);
	void AddFuel(int val);

	int GetGold() const;
	int GetBuildingRes() const;
	int GetFuel() const;

	bool TryToTakeGold(int val);
	bool TryToTakeBuildingRes(int val);
	bool TryToTakeFuel(int val);

	bool Have(const Price& price) const;
	bool Transaction(const Price& price);
private:
	bool Have(int goldNeed, int buildingResNeed, int fuelNeed) const;
	bool Transaction(int goldNeed, int buildingResNeed, int fuelNeed);
	int gold;
	int buildingRes;
	int fuel;
};

