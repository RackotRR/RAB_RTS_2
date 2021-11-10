#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "HasHP.h"
#include "HasMaster.h"
#include "HasTexture.h"
#include "HasVisibility.h"
#include "HasMovePoints.h"    
#include "BuildingType.h"
#include "UnderConstruction.h"
#include "HasTask.h"

/*
Базовый класс для всех зданий. Здания идентифицируются типом (type) и координатами (position)
*/
class Building : 
	public Actor, 
	public HasHP, 
	public HasMaster, 
	public HasTexture,
	public HasVisibility,
	public HasMovePoints, 
	public UnderConstruction,
	public HasTask
{
public:
	Building(const Vector2& position);

	virtual ~Building();

	// проверка типа времени выполнения
	BuildingType GetType() const;

	void ProductionPhase();
	 
protected:
	// тип устанавливается объектами производных классов при их создании
	void SetType(BuildingType type);
private:
	BuildingType type; 
}; 