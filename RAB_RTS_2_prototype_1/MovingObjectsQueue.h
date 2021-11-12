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
			[this, task](std::pair<Vector2, T*> i) { // ������, ���� �����, ������� ����� �������� ����� ����� ����
				return (i.second->GetMaster() == player) && // ������ ����������� �������� ������
					(i.second->CurrentTask()->GetType() == task) && // � ������� ���� ������
					(i.second->GetMovePoints() > 0); // � ���� ���� ���� ������������
			}),
			iter != objects.end())  // ���� ���� �����, ������� ����� ������, ��������� �������
		{
			objectsWantedToMove.insert(iter->second); // ��������� ��������� ������
			startIter = ++iter; // �������� ����� � ��������
		}
	}

	Player* player;
	World* world;
	// �����, ������� ������ ��������� movePoints ����� ����� ����
	std::set<Unit*> unitsWantedToMove;

	std::set<Building*> buildingsWantedToMove;
};