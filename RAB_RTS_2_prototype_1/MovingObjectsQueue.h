#pragma once
#include <set>
#include "World.h"
#include "Objects.h"

class Player;

class MovingObjectsQueue {
public:
	MovingObjectsQueue(World* world, Player* player);
	bool IsEmpty() const;

	void BuildMovingQueue(TaskType task);
	void UpdateMovingQueue();
private:
	void BuildUnitsQueue(TaskType task);

	template <typename T, typename ContainerType>
	void BuildMovingObjectsQueue(TaskType task, ContainerType& objects, std::set<T*>& objectsWantedToMove) {
		typedef typename ContainerType::iterator iterator;
		iterator iter;
		iterator startIter = objects.begin();

		while (iter = std::find_if(startIter, objects.end(),
			[this, task](std::pair<Vector2, T*> i) { // лямбда, ищет юниты, которые хотят походить после конца хода
				return (i.second->GetMaster() == player) && // объект принадлежит текущему игроку
					(i.second->CurrentTask()->GetType() == task) && // у объекта есть задача
					(i.second->GetMovePoints() > 0); // у него есть очки передвижения
			}),
			iter != objects.end())  // пока есть юниты, которые хотят ходить, формируем очередь
		{
			objectsWantedToMove.insert(iter->second); // добавляем желающего ходить
			startIter = ++iter; // начинаем поиск с текущего
		}
	}

	Player* player;
	World* world;
	// юниты, которые должны потратить movePoints после конца хода
	std::set<Unit*> unitsWantedToMove;

	std::set<Building*> buildingsWantedToMove;
};