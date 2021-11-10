#include "MoveAbility.h"  
#include "Pathfinder.h"
#include "Unit.h"
#include "World.h" 
#include "TaskMove.h"

MoveAbility::MoveAbility() : way(nullptr), world(nullptr), unit(nullptr){}

void MoveAbility::InitializeMoving(Unit* unit, World* world) {
	this->unit = unit;
	this->world = world;
	InitializeMovingAnimation(unit);
} 

void MoveAbility::Move(bool withRebuilding) {
	const Vector2& current = unit->GetPosition();

	// текущая задача по перемещению
	auto moveTask = static_cast<TaskMove*>(unit->CurrentTask());

	if (moveTask->GetGoal() == current) { // если объект на месте 
		unit->FinishCurrentTask(); 
		delete way;
		way = nullptr;
		return;
	}
	 
	if (withRebuilding) // если вызов извне, то путь, возможно, надо поменять
		if (!RebuildWay(moveTask)) // если не получилось построить путь, то выходим
			return; 

	if (unit->TryToSpendMovePoints()) // есть очки передвижения  
	{
		assert(!way->empty()); // если длина стека > 0, то мы должны быть уже на месте
		Vector2 next = way->top().pos;

		Direction direction = Direction::right;

		// путь должен быть таким, что все координаты из way - смежные

		if (current.Y > next.Y) direction = Direction::up;
		//if (current.X < next.X) direction = Direction::right; - по умолчанию
		else if (current.Y < next.Y) direction = Direction::down;
		else if (current.X > next.X) direction = Direction::left;

		unit->SetDirection(direction); 
		StartMoving(direction); 
		way->pop();
	}
}

bool MoveAbility::RebuildWay(TaskMove* moveTask) {
	delete way;
	way = nullptr;
	// перестраиваем путь, т.к. он может быть уже не рентабельным или не существовать
	Pathfinder pathfinder = Pathfinder(unit->GetPosition(), moveTask->GetGoal(),
		world, unit->GetMaster(), unit->GetMaxMovePoints());
	if (pathfinder.IsGoalReachable()) {
		way = pathfinder.GetWay();
		return true;
	}
	else { // цель недоступна - закончить движение 
		unit->FailedTask();
		return false;
	}
}