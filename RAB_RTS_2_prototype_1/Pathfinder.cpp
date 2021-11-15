#include <limits>
#include <algorithm>
#include <unordered_map>

#include "Pathfinder.h"
#include "RRGamePlay.h"
#include "World.h"
#include "Objects.h"
#include "Player.h"
#include "Camera.h"
 

std::unordered_set<Vector2, HashVector2> GetGroundIn(const Vector2& pos, int away, const Vector2& levelSize) {
	std::unordered_set<Vector2, HashVector2> ground; 
	ground.insert(pos); // первая клетка 
	
	if (away <= 0) { 
		return ground; 
	} 

	std::unordered_set<Vector2, HashVector2> toAdd;
	for (int j = 0; j < away; j++) { 
		for (auto& cell : ground) {
			// проходим по всем записанным координатам и проверяем все 4 направления
			// если новая координата будет в пределах карты, то добавляем её в список
			Vector2 v{ cell.X + 1, cell.Y };
			if (IsPositionSuitable(v, levelSize)) {
				toAdd.insert(v);
			}

			v = Vector2(cell.X - 1, cell.Y);
			if (IsPositionSuitable(v, levelSize)) {
				toAdd.insert(v);
			}

			v = Vector2(cell.X, cell.Y + 1);
			if (IsPositionSuitable(v, levelSize)) {
				toAdd.insert(v);
			}

			v = Vector2(cell.X, cell.Y - 1);
			if (IsPositionSuitable(v, levelSize)) {
				toAdd.insert(v);
			}
		}
		ground.merge(toAdd); // добавляем те координаты в набор для проверок, которых ещё в нём нет
		toAdd.clear();
	}
	return ground;
}

// возвращает true, если pos в пределах карты
bool IsPositionSuitable(const Vector2& pos, const Vector2& levelSize) {
	auto& [width, height] = levelSize;
	return pos.X >= 0 && pos.X < width &&
		pos.Y >= 0 && pos.Y < height;
}
 
Vector2 TransofrmCoordinates(const Vector2& screen, const Camera& camera) { 
	Vector2 pos = screen - Vector2(camera.GetDX(), camera.GetDY()); // получаем координату, по которой тыкнули с учётом смещения экрана

	bool doNotSelect = pos.X < 0 || pos.Y < 0; // исключаем неправильное приведение отрицательной координаты к int

	pos /= camera.GetCellSize(); // приводим к int с округлением вниз

	if (doNotSelect) // если экранная координата была отрицательная, то возвращаем координату в никуда
		pos = Vector2::WrongPosition;

	return pos;
}
 
void UpdateVisibilityFor(const Level* level, int owner, Array2D<bool>& visibility) { 
	visibility.Fill(false);
	 
	// добавляем обзор со зданий
	for (auto& buildingIter : level->buildings) {
		if (buildingIter.second->GetOwner() == owner) {
			std::unordered_set<Vector2, HashVector2> positions = 
				GetGroundIn(buildingIter.second->GetPosition(), buildingIter.second->GetVisibility(), level->size);

			for (auto& i : positions) {
				visibility(i.X, i.Y) = true;
			}
		}
	}

	// добавляем обзор с юнитов
	for (auto& unitIter : level->units) {
		if (unitIter.second->GetOwner() == owner) {
			std::unordered_set<Vector2, HashVector2> positions =
				GetGroundIn(unitIter.second->GetPosition(), unitIter.second->GetVisibility(), level->size);

			for (auto& i : positions) {
				visibility(i.X, i.Y) = true;
			}
		}
	}
}


Pathfinder::Pathfinder(const Vector2& start, const Vector2& goal, const World* world, const Player* player, int speed)
	:
	world{ world },
	player{ player },
	start{start}, 
	goal{ goal },
	speed{ speed }
{ 
	WaveAlg();
}
 
 

void Pathfinder::WaveAlg() {
	if (GetPassability(goal) == IMPASSABLE) { // если цель заведомо недостижима, то выходим
		reachable = false;
		way = nullptr;
		return;
	}  
	 
	std::unordered_map<Vector2, int, HashVector2> activeCells; // позиция, расстояние до неё
	activeCells.insert(std::pair(start, 0));
	

	std::unordered_map<Vector2, int, HashVector2> toAdd;

	int currentWave = 0;

	while (true) { // будем искать путь, либо пока не найдём, либо пока не поймём, что не найдём
		for (auto& iter : activeCells) {
			if (iter.second != currentWave) 
				continue; // пропускаем уже обработанные ячейки

			auto ptr = GetGroundIn(iter.first, 1, world->GetSize()); // получили клетки вокруг текущей
			for (auto& iptr : ptr) {
				int passability = GetPassability(iptr);
				// избегаем переполнения int
				if (passability == IMPASSABLE)
					toAdd[iptr] = IMPASSABLE;
				else
					toAdd[iptr] = iter.second + passability;

				if (iptr == goal) {
					// нашли!!!!
					// выйти из циклов, путь уже можно составить из имеющихся вершин
					reachable = true;
				}
			}
		}
		auto before = activeCells.size();
		activeCells.merge(toAdd); // добавляем в набор пройденные клетки
		auto after = activeCells.size();
		toAdd.clear();

		if (reachable) {
			ConstructWay(activeCells);
			return;
		}
		if (before == after) {
			// путь не построить. все новые вершины уже были обработаны
			way = nullptr;
			reachable = false;
			return;
		}
		currentWave++;
	}
}

void Pathfinder::ConstructWay(const std::unordered_map<Vector2, int, HashVector2>& activeCells) {  
	way = new std::stack<WayNode>;
	way->push(WayNode(goal, 1)); // добавим для начала клетку конца пути

	for (int i = activeCells.at(goal); i > 0; i--) {
		auto ptr = GetGroundIn(way->top().pos, 1, world->GetSize()); // соседние клетки   
		for (auto& iter : ptr) { // ищем среди соседних
			auto activeIter = activeCells.find(iter); // ищем такую среди обработанных
			if (activeIter != activeCells.cend()) // если такая есть
				if (activeIter->second == i) { // и она была на нужной волне
					way->push(WayNode(iter, 1));  // то добавим её в путь
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
		if (world->GetLevel()->ground(pos.X, pos.Y).GetType() == GroundType::water && canSail == false)
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
 