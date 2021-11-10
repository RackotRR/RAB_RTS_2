#pragma once
#include "BuildingType.h"
#include "UnitType.h"
#include <unordered_map>
#include "Price.h"

class PlayerResearches
{
public: 
	int GetMaxHP(BuildingType buildingType) const;
	int GetMaxHP(UnitType unitType) const;

	void SetMaxHP(BuildingType buildingType, int hp);
	void SetMaxHP(UnitType unitType, int hp);

	int GetVisibility(BuildingType buildingType) const;
	int GetVisibility(UnitType unitType) const;

	void SetVisibility(BuildingType buildingType, int visibility);
	void SetVisibility(UnitType unitType, int visibility);

	int GetMaxMovePoints(BuildingType buildingType) const;
	int GetMaxMovePoints(UnitType unitType) const;

	void SetMaxMovePoints(BuildingType buildingType, int movePoints);
	void SetMaxMovePoints(UnitType unitType, int movePoints);

	const Price& GetPrice(BuildingType buildingType) const;
	const Price& GetPrice(UnitType unitType) const;

	void SetPrice(BuildingType buildingType, const Price& price);
	void SetPrice(UnitType unitType, const Price& price);
	  
	void SetPointsToConstructBuilding(BuildingType buildingType, int points);
	int GetPointsToConstructBuilding(BuildingType buildingType) const;

	void SetPointsToProduceUnit(UnitType unitType, int points);
	int GetPointsToProduceUnit(UnitType unitType) const;
private:
	std::unordered_map<BuildingType, int> buildingsMaxHP;
	std::unordered_map<UnitType, int> unitsMaxHP;

	std::unordered_map<BuildingType, int> buildingsVisibility;
	std::unordered_map<UnitType, int> unitsVisibility;

	std::unordered_map<BuildingType, int> buildingsMovePoints;
	std::unordered_map<UnitType, int> unitsMovePoints;

	std::unordered_map<BuildingType, Price> buildingsPrice;
	std::unordered_map<UnitType, Price> unitsPrice;

	std::unordered_map<BuildingType, int> pointsToConstructBuilding;
	std::unordered_map<UnitType, int> pointsToProduceUnit;
};

