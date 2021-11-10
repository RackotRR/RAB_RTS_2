#pragma once
#include <vector>
#include <unordered_map>
#include "World.h"

class Player; 
class RRTexture;

class ObjectsFactory {
public:
	// инициализировать все объекты в мире (подгрузить данные времени выполнения)
	// выставляет характеристики объектов, не меняет их текущее состояние
	void Initialize(World* world, const std::vector<Player*>* players); 

	static ObjectsFactory* Instance(); 
	
	// создать и добавить здание в мир
	void MakeBuilding(const Vector2& position, Player* master, BuildingType buildingType);

	// создать и добавить юнит в мир
	void MakeUnit(const Vector2& position, Player* master, UnitType unitType);

	// создаёт новый юнит на основе старого. удаляет старый
	void MakeUnitAndReplace(Unit* old, UnitType unitType);
private:
	ObjectsFactory();
	ObjectsFactory(const ObjectsFactory&) = delete;
	ObjectsFactory& operator= (const ObjectsFactory&) = delete;

	// установить текстуру для юнита
	void SetUnitTexture(Unit* unit);

	// установить текстуру для здания
	void SetBuildingTexture(Building* building);

	// установить текстуру для ресурса
	void SetResourceTexture(Resource* resource);
	 
	// установить направление по умолчанию для юнитов
	// актуально для 2-х игроков (если больше будет, то удалить эту штуку
	void SetUnitDirection(Unit* unit);

	// перед вызовом должно быть установлено поле owner
	void InitBuilding(Building* building);
	// перед вызовом должно быть установлено поле owner
	void InitUnit(Unit* unit);
	void InitResource(Resource* resource);

	const std::vector<Player*>* players;
	World* world;  
};