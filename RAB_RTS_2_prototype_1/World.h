#pragma once
#include "Level.h"
  
// Level - ������, World - ������ ������� � ���
// ����� �������� �����, GameFIO (LevelSaver) ����� ��������� �� ���
// ����� ������������� �������!
class World
{
private:
	Level level;
public:
	World(Level&& level) : level{ std::move(level) } {}
	//~World(); // ������������ ����������� ���������� ������
	    
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

	const Vector2& GetSize() const {
		return level.size;
	}

	const Level* GetLevel() const { 
		return &level;
	}
	Level* GetLevel() { 
		return &level;
	}
	 
	PlayerData* GetPlayerData(int i);
	 
	// ����������� ����� ��������� ��������� ��������. ��������� �����
	void UpdateChangedCoordinates(); 
};


