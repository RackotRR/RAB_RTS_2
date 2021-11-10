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

	// ������� ������ �� �����������
	auto moveTask = static_cast<TaskMove*>(unit->CurrentTask());

	if (moveTask->GetGoal() == current) { // ���� ������ �� ����� 
		unit->FinishCurrentTask(); 
		delete way;
		way = nullptr;
		return;
	}
	 
	if (withRebuilding) // ���� ����� �����, �� ����, ��������, ���� ��������
		if (!RebuildWay(moveTask)) // ���� �� ���������� ��������� ����, �� �������
			return; 

	if (unit->TryToSpendMovePoints()) // ���� ���� ������������  
	{
		assert(!way->empty()); // ���� ����� ����� > 0, �� �� ������ ���� ��� �� �����
		Vector2 next = way->top().pos;

		Direction direction = Direction::right;

		// ���� ������ ���� �����, ��� ��� ���������� �� way - �������

		if (current.Y > next.Y) direction = Direction::up;
		//if (current.X < next.X) direction = Direction::right; - �� ���������
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
	// ������������� ����, �.�. �� ����� ���� ��� �� ������������ ��� �� ������������
	Pathfinder pathfinder = Pathfinder(unit->GetPosition(), moveTask->GetGoal(),
		world, unit->GetMaster(), unit->GetMaxMovePoints());
	if (pathfinder.IsGoalReachable()) {
		way = pathfinder.GetWay();
		return true;
	}
	else { // ���� ���������� - ��������� �������� 
		unit->FailedTask();
		return false;
	}
}