#pragma once 
#include <unordered_set> 
#include <stack>

#include "Vector2.h"
#include "WayNode.h"

/*
набор функций для поиска пути
*/  
class Level;
class World;
class Player;
class Camera;


class Pathfinder {
public:
	/// <summary>
	/// start != goal - это нужно проверить перед вызовом!
	/// </summary>
	/// <param name="start">-начало пути</param>
	/// <param name="goal">-конец пути</param>
	/// <param name="level">-указатель на карту</param>
	/// <param name="player">-указатель на игрока (технологии)</param>
	/// <param name="speed">-скорость юнита</param>
	Pathfinder(const Vector2& start, const Vector2& goal, const World* world, const Player* player, int speed); 
	 
	// возвращает указатель на построенный путь
	// если цель достижима, то память надо будет самостоятельно освободить
	// если маршрут не был построен, то будет возвращён nullptr
	std::stack<WayNode>* GetWay() {
		return way;
	}

	// достижима ли цель 
	bool IsGoalReachable() {
		return reachable;
	}
	 
private:
	void ConstructWay(const std::unordered_map<Vector2, int, HashVector2>& activeCells);
	// попробовать построить путь
	void WaveAlg();
	// возвращает проходимость для клетки на pos
	int GetPassability(const Vector2& pos) const;


	// готовый маршрут
	std::stack<WayNode>* way;

	// достижима ли цель
	bool reachable;

	const World* world;
	const Player* player;
	Vector2 start, goal;

	// скорость объекта
	int speed;

	// может ли плавать
	bool canSail;

	// вес для непроходимой клетки
	const int IMPASSABLE;
	 
};



// возвращает набор координат, находящихся на расстоянии away от position
std::unordered_set<Vector2, HashVector2> GetGroundIn(const Vector2& position, int away, int width, int height);

// определяет, находится ли Position в области карты
bool IsPositionSuitable(const Vector2& pos, int width, int height);
 
// превращает координаты экранные в координаты на карте
Vector2 TransofrmCoordinates(const Vector2& screen, const Camera* player);
 
// обновляет видимые координаты для Player
void UpdateVisibilityFor(const Level* level, int owner, bool** visibility);