#pragma once 
#include <unordered_set> 
#include <stack>

#include "Vector2.h"
#include "WayNode.h"

/*
����� ������� ��� ������ ����
*/  
class Level;
class World;
class Player;
class Camera;


class Pathfinder {
public:
	/// <summary>
	/// start != goal - ��� ����� ��������� ����� �������!
	/// </summary>
	/// <param name="start">-������ ����</param>
	/// <param name="goal">-����� ����</param>
	/// <param name="level">-��������� �� �����</param>
	/// <param name="player">-��������� �� ������ (����������)</param>
	/// <param name="speed">-�������� �����</param>
	Pathfinder(const Vector2& start, const Vector2& goal, const World* world, const Player* player, int speed); 
	 
	// ���������� ��������� �� ����������� ����
	// ���� ���� ���������, �� ������ ���� ����� �������������� ����������
	// ���� ������� �� ��� ��������, �� ����� ��������� nullptr
	std::stack<WayNode>* GetWay() {
		return way;
	}

	// ��������� �� ���� 
	bool IsGoalReachable() {
		return reachable;
	}
	 
private:
	void ConstructWay(const std::unordered_map<Vector2, int, HashVector2>& activeCells);
	// ����������� ��������� ����
	void WaveAlg();
	// ���������� ������������ ��� ������ �� pos
	int GetPassability(const Vector2& pos) const;


	// ������� �������
	std::stack<WayNode>* way;

	// ��������� �� ����
	bool reachable;

	const World* world;
	const Player* player;
	Vector2 start, goal;

	// �������� �������
	int speed;

	// ����� �� �������
	bool canSail;

	// ��� ��� ������������ ������
	const int IMPASSABLE;
	 
};



// ���������� ����� ���������, ����������� �� ���������� away �� position
std::unordered_set<Vector2, HashVector2> GetGroundIn(const Vector2& position, int away, int width, int height);

// ����������, ��������� �� Position � ������� �����
bool IsPositionSuitable(const Vector2& pos, int width, int height);
 
// ���������� ���������� �������� � ���������� �� �����
Vector2 TransofrmCoordinates(const Vector2& screen, const Camera* player);
 
// ��������� ������� ���������� ��� Player
void UpdateVisibilityFor(const Level* level, int owner, bool** visibility);