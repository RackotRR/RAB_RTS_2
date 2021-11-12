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
движение запускаетс€ (Move()) либо после установки цели SetGoal()
либо после завершени€ хода
*/
class MoveAbility : public MoveAnimation
{
public:
	MoveAbility();
	void InitializeMoving(Unit* unit, World* world);

	// двигатьс€ к цели
	// при вызове с withRebuilding будет каждый раз перестраивать маршрут
	// как только объект придЄт к цели: delete way, hasGoal = false
	void Move(bool withRebuilding = true);
	  
private:
	bool RebuildWay(TaskMove* moveTask);
	/// <summary>
	/// последовательность вершин + вес (кол-во movePoints дл€ того, чтобы туда попасть)
	/// </summary>
	std::stack<WayNode>* way; 
	World* world;
	Unit* unit;  
};

