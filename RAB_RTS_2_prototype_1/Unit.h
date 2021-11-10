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
������� ����� ��� ���� ������
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

	// �������� ���� ����� �� ����� ����������
	UnitType GetType() const;
	 
	// ���������� ��������� ����� ��� ������ ������ 
	void DoCurrentTask(TurnPhase phase = TurnPhase::common) override;
protected:

	// ��� ����� ��������������� ��������� ������� ������� �� ����� �� ��������
	void SetType(UnitType type);
private:
	UnitType type;
};


