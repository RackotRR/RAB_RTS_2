#include "MovingObjectsQueue.h"
#include <algorithm>
#include <assert.h>
#include "Objects.h"

MovingObjectsQueue::MovingObjectsQueue(World* world, Player* player) : world(world), player(player) {}

bool MovingObjectsQueue::IsEmpty() const {
	return unitsWantedToMove.empty() && buildingsWantedToMove.empty();
}

void MovingObjectsQueue::BuildMovingQueue(TaskType task) {
	//BuildUnitsQueue(task);
	// BuildBuildingsQueue();
	switch (task)
	{
	case TaskType::move: 
	case TaskType::build:
		BuildMovingObjectsQueue(task, world->GetLevel()->units, unitsWantedToMove);
		break;
	case TaskType::produce:
		BuildMovingObjectsQueue(task, world->GetLevel()->buildings, buildingsWantedToMove);
		break; 
	case TaskType::none: 
	default:
		assert("Task type in moving queue was none" && false);
		break;
	}
}


void MovingObjectsQueue::BuildUnitsQueue(TaskType task) {
	auto& units = world->GetLevel()->units;
	std::unordered_map<Vector2, Unit*, HashVector2>::iterator iter;
	std::unordered_map<Vector2, Unit*, HashVector2>::iterator startIter = units.begin();

	while (iter = std::find_if(startIter, units.end(),
		[this, task](std::pair<Vector2, Unit*> i) { // ������, ���� �����, ������� ����� �������� ����� ����� ����
			return (i.second->GetMaster() == player) && // ������ ����������� �������� ������
				(i.second->CurrentTask()->GetType() == task) && // � ������� ���� ������
				(i.second->GetMovePoints() > 0); // � ���� ���� ���� ������������
		}),
		iter != units.end())  // ���� ���� �����, ������� ����� ������, ����������� �������
	{ 
		unitsWantedToMove.insert(iter->second); // ��������� ��������� ������
		startIter = ++iter; // �������� ����� � ��������
	}
}

void MovingObjectsQueue::UpdateMovingQueue() {
	if (!unitsWantedToMove.empty()) { // ���� ���� ����� � �������
		auto ptr = unitsWantedToMove.begin(); // ���� ������� �� ���
		(*ptr)->DoCurrentTask(); // ���������� ����
		unitsWantedToMove.erase(ptr); // ������� �� �������
	}
	// �� �� ����� ��� buildings
	if (!buildingsWantedToMove.empty()) { // ���� ���� ����� � �������
		auto ptr = buildingsWantedToMove.begin(); // ���� ������� �� ���
		(*ptr)->DoCurrentTask(); // ���������� ����
		buildingsWantedToMove.erase(ptr); // ������� �� �������
	}
}