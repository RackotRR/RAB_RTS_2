#pragma once
#include "MoveAnimation.h"
#include <assert.h> 
#include "Vector2.h"
#include "Node.h"
#include <stack>

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
	std::stack<Node>* way; 
	World* world;
	Unit* unit;  
};

