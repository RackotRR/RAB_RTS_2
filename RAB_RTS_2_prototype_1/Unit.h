#pragma once
#include "Vector2.h"
#include "Actor.h"
#include "HasHP.h"
#include "HasMaster.h"
#include "HasUnitTexture.h"
#include "HasVisibility.h"
#include "HasMovePoints.h"
#include "MoveAbility.h"
#include "HasTask.h" 
#include "Price.h"
#include "UnitType.h"

/*
Базовый класс для всех юнитов
*/
class Unit : 
	public Actor, 
	public HasMaster, 
	public HasHP, 
	public HasUnitTexture, 
	public HasVisibility, 
	public HasMovePoints,
	public MoveAbility, 
	public HasTask 
{
public:
	Unit(const Vector2& position);

	virtual ~Unit();
	 
	void ProductionPhase();

	// проверка типа юнита во время выполнения
	UnitType GetType() const;
	 
	// попытаться выполнить общую для юнитов задачу 
	void DoCurrentTask(TurnPhase phase = TurnPhase::common) override;
protected:

	// тип юнита устанавливается объектами базовых классов во время их создания
	void SetType(UnitType type);
private:
	UnitType type;
};


