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
������� ����� ��� ���� ������. ������ ���������������� ����� (type) � ������������ (position)
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

	// �������� ���� ������� ����������
	BuildingType GetType() const;

	void ProductionPhase();
	 
protected:
	// ��� ��������������� ��������� ����������� ������� ��� �� ��������
	void SetType(BuildingType type);
private:
	BuildingType type; 
}; 