#pragma once
#include <vector>
#include <unordered_map>
#include "World.h"

class Player; 
class RRTexture;

class ObjectsFactory {
public:
	// ���������������� ��� ������� � ���� (���������� ������ ������� ����������)
	// ���������� �������������� ��������, �� ������ �� ������� ���������
	void Initialize(World* world, const std::vector<Player*>* players); 

	static ObjectsFactory* Instance(); 
	
	// ������� � �������� ������ � ���
	void MakeBuilding(const Vector2& position, Player* master, BuildingType buildingType);

	// ������� � �������� ���� � ���
	void MakeUnit(const Vector2& position, Player* master, UnitType unitType);

	// ������ ����� ���� �� ������ �������. ������� ������
	void MakeUnitAndReplace(Unit* old, UnitType unitType);
private:
	ObjectsFactory();
	ObjectsFactory(const ObjectsFactory&) = delete;
	ObjectsFactory& operator= (const ObjectsFactory&) = delete;

	// ���������� �������� ��� �����
	void SetUnitTexture(Unit* unit);

	// ���������� �������� ��� ������
	void SetBuildingTexture(Building* building);

	// ���������� �������� ��� �������
	void SetResourceTexture(Resource* resource);
	 
	// ���������� ����������� �� ��������� ��� ������
	// ��������� ��� 2-� ������� (���� ������ �����, �� ������� ��� �����
	void SetUnitDirection(Unit* unit);

	// ����� ������� ������ ���� ����������� ���� owner
	void InitBuilding(Building* building);
	// ����� ������� ������ ���� ����������� ���� owner
	void InitUnit(Unit* unit);
	void InitResource(Resource* resource);

	const std::vector<Player*>* players;
	World* world;  
};