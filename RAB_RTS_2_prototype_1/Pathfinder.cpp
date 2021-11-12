#include "Pathfinder.h"
#include "RRGamePlay.h"
#include "World.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
#include <limits>
#include <algorithm>
#include <unordered_map>


// ������� ������������� ��� away==1
std::unordered_set<Vector2, HashVector2> GetGroundIn(const Vector2& pos, int away, int width, int height) {
	std::unordered_set<Vector2, HashVector2> ground; 
	ground.insert(pos); // ������ ������ 
	if (away <= 0) return ground; 
	std::unordered_set<Vector2, HashVector2> toAdd;
	for (int j = 0; j < away; j++) { 
		for (auto& iter : ground) {
			// �������� �� ���� ���������� ����������� � ��������� ��� 4 �����������
			// ���� ����� ���������� ����� � �������� �����, �� ��������� � � ������
			Vector2 v(iter.X + 1, iter.Y);
			if (IsPositionSuitable(v, width, height)) toAdd.insert(v);
			v = Vector2(iter.X - 1, iter.Y);
			if (IsPositionSuitable(v, width, height)) toAdd.insert(v);
			v = Vector2(iter.X, iter.Y + 1);
			if (IsPositionSuitable(v, width, height)) toAdd.insert(v);
			v = Vector2(iter.X, iter.Y - 1);
			if (IsPositionSuitable(v, width, height)) toAdd.insert(v);
		}
		ground.merge(toAdd); // ��������� �� ���������� � ����� ��� ��������, ������� ��� � �� ���
		toAdd.clear();
	}
	return ground;
}

bool IsPositionSuitable(const Vector2& pos, int width, int height) {
	return !(pos.X < 0 || pos.X >= width || // ���������� true, ���� pos � �������� �����
		pos.Y < 0 || pos.Y >= height);
}
 
Vector2 TransofrmCoordinates(const Vector2& screen, const Camera* camera) { 
	Vector2 pos = screen - Vector2(camera->GetDX(), camera->GetDY()); // �������� ����������, �� ������� ������� � ������ �������� ������

	bool doNotSelect = pos.X < 0 || pos.Y < 0; // ��������� ������������ ���������� ������������� ���������� � int

	pos /= camera->GetCellSize(); // �������� � int � ����������� ����

	if (doNotSelect) // ���� �������� ���������� ���� �������������, �� ���������� ���������� � ������
		pos = Vector2::WrongPosition;

	return pos;
}
 
void UpdateVisibilityFor(const Level* level, int owner, bool** visibility) { 
	int height = level->height;
	int width = level->width;

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			visibility[j][i] = false;
	 
	for (auto& iter : level->buildings) {
		if (iter.second->GetOwner() == owner) {
			std::unordered_set<Vector2, HashVector2> vectors = GetGroundIn(iter.second->GetPosition(), iter.second->GetVisibility(), width, height);
			for (auto& i : vectors) {
				visibility[i.Y][i.X] = true;
			}
		}
	}
	for (auto& iter : level->units) {
		if (iter.second->GetOwner() == owner) {
			std::unordered_set<Vector2, HashVector2> vectors = GetGroundIn(iter.second->GetPosition(), iter.second->GetVisibility(), width, height);
			for (auto& i : vectors) {
				visibility[i.Y][i.X] = true;
			}
		}
	}
}


Pathfinder::Pathfinder(const Vector2& start, const Vector2& goal, const World* world, const Player* player, int speed) :
	start(start), 
	goal(goal), 
	world(world), 
	IMPASSABLE(INT_MAX), 
	speed(speed), 
	canSail(false), 
	reachable(false),
	way(nullptr) 
{ 
	WaveAlg();
}
 
 

void Pathfinder::WaveAlg() {
	if (GetPassability(goal) == IMPASSABLE) { // ���� ���� �������� �����������, �� �������
		reachable = false;
		way = nullptr;
		return;
	}

	const Level* level = world->GetLevel();
	int width = level->width;
	int height = level->height;

	 
	std::unordered_map<Vector2, int, HashVector2> activeCells; // �������, ���������� �� ��
	activeCells.insert(std::pair(start, 0));
	

	std::unordered_map<Vector2, int, HashVector2> toAdd;

	int currentWave = 0;

	while (true) { // ����� ������ ����, ���� ���� �� �����, ���� ���� �� �����, ��� �� �����
		for (auto& iter : activeCells) {
			if (iter.second != currentWave) continue; // ���������� ��� ������������ ������
			auto ptr = GetGroundIn(iter.first, 1, width, height); // �������� ������ ������ �������
			for (auto& iptr : ptr) {
				int passability = GetPassability(iptr);
				// �������� ������������ int
				if (passability == IMPASSABLE)
					toAdd[iptr] = IMPASSABLE;
				else
					toAdd[iptr] = iter.second + passability;

				if (iptr == goal) {
					// �����!!!!
					// ����� �� ������, ���� ��� ����� ��������� �� ��������� ������
					reachable = true;
				}
			}
		}
		auto before = activeCells.size();
		activeCells.merge(toAdd); // ��������� � ����� ���������� ������
		auto after = activeCells.size();
		toAdd.clear();

		if (reachable) {
			ConstructWay(activeCells);
			return;
		}
		if (before == after) {
			// ���� �� ���������. ��� ����� ������� ��� ���� ����������
			way = nullptr;
			reachable = false;
			return;
		}
		currentWave++;
	}
}

void Pathfinder::ConstructWay(const std::unordered_map<Vector2, int, HashVector2>& activeCells) { 

	const Level* level = world->GetLevel();
	int width = level->width;
	int height = level->height;

	way = new std::stack<WayNode>;
	way->push(WayNode(goal, 1)); // ������� ��� ������ ������ ����� ����

	for (int i = activeCells.at(goal); i > 0; i--) {
		auto ptr = GetGroundIn(way->top().pos, 1, width, height); // �������� ������   
		for (auto& iter : ptr) { // ���� ����� ��������
			auto activeIter = activeCells.find(iter); // ���� ����� ����� ������������
			if (activeIter != activeCells.cend()) // ���� ����� ����
				if (activeIter->second == i) { // � ��� ���� �� ������ �����
					way->push(WayNode(iter, 1));  // �� ������� � � ����
					break;
				}
		} 
	}
}

int Pathfinder::GetPassability(const Vector2& pos) const { 
	ObjectType type = world->CheckPosition(pos);

	switch (type)
	{
	case ObjectType::ground:
		if (world->GetLevel()->ground[pos.Y][pos.X].GetType() == GroundType::water && !canSail)
			return IMPASSABLE;
		else 
			return 1;
	case ObjectType::resource:
	case ObjectType::unit: 
	case ObjectType::building: 
	case ObjectType::none:
		return IMPASSABLE; 
	} 
	return -1;
}
 