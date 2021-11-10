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
Абстракция данных о мире. Выделенную память нужно освобождать!
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

// Level - данные, World - методы доступа к ним
// после загрузки карты, GameFIO (LevelSaver) выдаёт указатель на мир
// после использования удалить!
class World : private Level
{
public:
	World() : Level() {}
	~World(); // освобождение динамически выделенной памяти
	    
	// переместить юнит
	void ReplaceUnit(const Vector2& key, Unit* unit);

	// добавленные объекты будут удалены при удалении World
	void AddUnit(Unit* unit); // добавить юнит в мир 
	void AddBuilding(Building* building); // добавить здание в мир
	void AddResource(Resource* resource); // добавить ресурс в мир

	ObjectType CheckPosition(const Vector2& pos) const; // возвращает тип объект по этим координатам 
	 
	// перед вызовом этих методов необходимо проверить, что там действительно находится объект этого типа (CheckPosition)
	// возвращают nullptr, если что-то не так
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
	 
	// выполняется после изменения координат объектов. обновляет обзор
	void UpdateChangedCoordinates(); 
};


