#pragma once
#include "Level.h"
  
// Level - данные, World - методы доступа к ним
// после загрузки карты, GameFIO (LevelSaver) выдаёт указатель на мир
// после использования удалить!
class World
{
private:
	Level level;
public:
	World(Level&& level) : level{ std::move(level) } {}
	//~World(); // освобождение динамически выделенной памяти
	    
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
	 
	// выполняется после изменения координат объектов. обновляет обзор
	void UpdateChangedCoordinates(); 
};


