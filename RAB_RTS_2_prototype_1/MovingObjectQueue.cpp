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
		[this, task](std::pair<Vector2, Unit*> i) { // лямбда, ищет юниты, которые хотят походить после конца хода
			return (i.second->GetMaster() == player) && // объект принадлежит текущему игроку
				(i.second->CurrentTask()->GetType() == task) && // у объекта есть задача
				(i.second->GetMovePoints() > 0); // у него есть очки передвижения
		}),
		iter != units.end())  // пока есть юниты, которые хотят ходить, формировать очередь
	{ 
		unitsWantedToMove.insert(iter->second); // добавляем желающего ходить
		startIter = ++iter; // начинаем поиск с текущего
	}
}

void MovingObjectsQueue::UpdateMovingQueue() {
	if (!unitsWantedToMove.empty()) { // если есть юниты в очереди
		auto ptr = unitsWantedToMove.begin(); // берём первого из них
		(*ptr)->DoCurrentTask(); // заставляем идти
		unitsWantedToMove.erase(ptr); // удаляем из очереди
	}
	// то же самое для buildings
	if (!buildingsWantedToMove.empty()) { // если есть юниты в очереди
		auto ptr = buildingsWantedToMove.begin(); // берём первого из них
		(*ptr)->DoCurrentTask(); // заставляем идти
		buildingsWantedToMove.erase(ptr); // удаляем из очереди
	}
}