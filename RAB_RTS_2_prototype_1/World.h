#pragma once
#include <vector>
#include <unordered_map> 
#include <string> 

#include "Vector2.h"
#include "PlayerData.h"
#include "ObjectType.h"
#include "Array2D.h"
#include "Cell.h"
 
class Resource; 
class Unit;
class Building;
  
/*
Абстракция данных о мире. Выделенную память нужно освобождать!
*/
struct Level
{
	Level(int width, int height, int playersNum)
		:
		playersNum{ playersNum },
		size{ width, height },
		ground{ width, height } {}

	std::string name, description;

	const int playersNum;
	std::vector<PlayerData*> playersData;

	const Vector2 size;
	std::unordered_map<Vector2, Unit*, HashVector2> units;
	std::unordered_map<Vector2, Building*, HashVector2> buildings;
	std::unordered_map<Vector2, Resource*, HashVector2> resources;
	Array2D<Cell> ground; 
};

// Level - данные, World - методы доступа к ним
// после загрузки карты, GameFIO (LevelSaver) выдаёт указатель на мир
// после использования удалить!
class World
{
private:
	Level level;
public:
	World(Level level) : level{ std::move(level) } {}
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
		return &level;
	}
	Level* GetLevel() { 
		return &level;
	}
	 
	PlayerData* GetPlayerData(int i);
	 
	// выполняется после изменения координат объектов. обновляет обзор
	void UpdateChangedCoordinates(); 
};


