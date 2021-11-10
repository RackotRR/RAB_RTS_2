#pragma once
#include "Vector2.h"
#include <vector>
#include <unordered_map> 
#include <string> 

#include "PlayerData.h"
#include "ObjectType.h"
 
class Resource;
class Cell;
class Unit;
class Building;

using std::unordered_map;
 

/*
���������� ������ � ����. ���������� ������ ����� �����������!
*/
class Level 
{
public:
	std::string name, description;

	int playersNum = 0;
	std::vector<PlayerData*> playersData;

	int width = 0, height = 0;
	unordered_map<Vector2, Unit*, HashVector2> units;
	unordered_map<Vector2, Building*, HashVector2> buildings;
	unordered_map<Vector2, Resource*, HashVector2> resources;
	Cell** ground = nullptr; 

};

// Level - ������, World - ������ ������� � ���
// ����� �������� �����, GameFIO (LevelSaver) ����� ��������� �� ���
// ����� ������������� �������!
class World : private Level
{
public:
	World() : Level() {}
	~World(); // ������������ ����������� ���������� ������
	    
	// ����������� ����
	void ReplaceUnit(const Vector2& key, Unit* unit);

	// ����������� ������� ����� ������� ��� �������� World
	void AddUnit(Unit* unit); // �������� ���� � ��� 
	void AddBuilding(Building* building); // �������� ������ � ���
	void AddResource(Resource* resource); // �������� ������ � ���

	ObjectType CheckPosition(const Vector2& pos) const; // ���������� ��� ������ �� ���� ����������� 
	 
	// ����� ������� ���� ������� ���������� ���������, ��� ��� ������������� ��������� ������ ����� ���� (CheckPosition)
	// ���������� nullptr, ���� ���-�� �� ���
	Unit* GetUnitAt(const Vector2& pos);
	Building* GetBuildingAt(const Vector2& pos);
	Resource* GetResourceAt(const Vector2& pos);
	Cell* GetGroundAt(const Vector2& pos);
	const Unit* GetUnitAt(const Vector2& pos) const;
	const Building* GetBuildingAt(const Vector2& pos) const;
	const Resource* GetResourceAt(const Vector2& pos) const;
	const Cell* GetGroundAt(const Vector2& pos) const;

	void RemoveUnitFrom(const Vector2& pos);
	void RemoveBuildingFrom(const Vector2& pos);
	void RemoveResourceFrom(const Vector2& pos);

	const Level* GetLevel() const {
		const Level* level = static_cast<const Level*>(this);
		return level;
	}
	Level* GetLevel() {
		Level* level = static_cast<Level*>(this);
		return level;
	}
	 
	PlayerData* GetPlayerData(int i);
	 
	// ����������� ����� ��������� ��������� ��������. ��������� �����
	void UpdateChangedCoordinates(); 
};


