#pragma once
#include <cassert> 
#include <stack>

#include "MoveAnimation.h"
#include "Vector2.h"
#include "WayNode.h"

class Unit;
class World;
class TaskMove;

/*
�������� ����������� (Move()) ���� ����� ��������� ���� SetGoal()
���� ����� ���������� ����
*/
class MoveAbility : public MoveAnimation
{
public:
	MoveAbility();
	void InitializeMoving(Unit* unit, World* world);

	// ��������� � ����
	// ��� ������ � withRebuilding ����� ������ ��� ������������� �������
	// ��� ������ ������ ����� � ����: delete way, hasGoal = false
	void Move(bool withRebuilding = true);
	  
private:
	bool RebuildWay(TaskMove* moveTask);
	/// <summary>
	/// ������������������ ������ + ��� (���-�� movePoints ��� ����, ����� ���� �������)
	/// </summary>
	std::stack<WayNode>* way; 
	World* world;
	Unit* unit;  
};

