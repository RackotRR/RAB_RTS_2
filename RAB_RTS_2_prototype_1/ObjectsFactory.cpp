#include "ObjectsFactory.h"
#include "Player.h"
#include "PlayerData.h"
#include "RRTextureManager.h"
#include "Objects.h"
#include <assert.h>
#include <algorithm>

ObjectsFactory::ObjectsFactory() : 
	world(nullptr),
	players(nullptr)
{}

ObjectsFactory* ObjectsFactory::Instance() {
	static ObjectsFactory instance;
	return &instance;
}

void ObjectsFactory::Initialize(World* world, const std::vector<Player*>* players) {
	this->world = world; 
	this->players = players;
	  
	for (auto& iter : world->GetLevel()->units)
		InitUnit(iter.second);
	for (auto& iter : world->GetLevel()->buildings)
		InitBuilding(iter.second);
	for (auto& iter : world->GetLevel()->resources)
		InitResource(iter.second);
} 

void ObjectsFactory::InitBuilding(Building* building) {
	size_t owner = building->GetOwner() - 1UL; // owner объектов начинается с 1 (пока)
	building->SetMaster(players->at(owner));
	SetBuildingTexture(building);

	// характеристики, зависящие от исследований игрока
	auto researches = building->GetMaster()->GetPlayerData()->Researches();
	building->SetMaxHP(researches->GetMaxHP(building->GetType()));
	building->SetVisibility(researches->GetVisibility(building->GetType()));
	building->SetMaxMovePoints(researches->GetMaxMovePoints(building->GetType()));

	// временно, пока не работает нормально GameFIO
	building->InitHP();
	building->ResetMovePoints();
}

void ObjectsFactory::InitUnit(Unit* unit) {
	size_t owner = unit->GetOwner() - 1UL;
	unit->SetMaster(players->at(owner));

	SetUnitDirection(unit);
	SetUnitTexture(unit);
	unit->InitializeMoving(unit, world); 

	// характеристики, зависящие от исследований игрока
	auto researches = unit->GetMaster()->GetPlayerData()->Researches();
	unit->SetMaxHP(researches->GetMaxHP(unit->GetType()));
	unit->SetVisibility(researches->GetVisibility(unit->GetType()));
	unit->SetMaxMovePoints(researches->GetMaxMovePoints(unit->GetType()));

	// временно, пока не работает нормально GameFIO
	unit->InitHP();
	unit->ResetMovePoints();
}

void ObjectsFactory::InitResource(Resource* resource) {
	SetResourceTexture(resource);
}

void ObjectsFactory::SetUnitTexture(Unit* unit) {
	TextureType texture = TextureType::none;
	size_t owner = unit->GetOwner();
	/*
	заменить, когда будет больше 2-х игроков
	*/
	switch (unit->GetType())
	{
	case UnitType::scout:
		if (owner == 1) {
			texture = TextureType::scout1;
		}
		else if (owner == 2) {
			texture = TextureType::scout2;
		}
		break;
	case UnitType::worker:
		if (owner == 1) {
			texture = TextureType::worker1;
		}
		else if (owner == 2) {
			texture = TextureType::worker2;
		}
		break;
	case UnitType::tank:
		if (owner == 1) {
			texture = TextureType::tank1;
		}
		else if (owner == 2) {
			texture = TextureType::tank2;
		}
		break;
	default:
		assert("Wrong unit type" && false);
		break;
	}
	assert("Wrong texture" && texture != TextureType::none); 
	unit->AddTexture(RRTextureManager::Instance()->GetTexture(texture));
}
 
void ObjectsFactory::SetBuildingTexture(Building* building) {
	TextureType texture = TextureType::none;
	size_t owner = building->GetOwner();
	switch (building->GetType())
	{
	case BuildingType::factory:
		if (owner == 1) {
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory1_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory1_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory1_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory1_4));
		}
		else if (owner == 2) { 
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory2_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory2_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory2_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::factory2_4));
		}
		break;
	case BuildingType::house:
		if (owner == 1) {
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house1_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house1_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house1_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house1_4));
		}
		else if (owner == 2) {
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house2_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house2_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house2_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::house2_4));
		} 
		break;
	case BuildingType::spaceport:
		if (owner == 1) {
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport1_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport1_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport1_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport1_4));
		}
		else if (owner == 2) {
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport2_1));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport2_2));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport2_3));
			building->AddTexture(RRTextureManager::Instance()->GetTexture(TextureType::spaceport2_4));
		} 
		break;
	default:
		assert("Wrong building type" && false);
		break;
	} 
}

void ObjectsFactory::SetResourceTexture(Resource* resource) {
	TextureType texture = TextureType::none; 
	switch (resource->GetType())
	{
	case ResourceType::forest:
		texture = TextureType::forest;
		break;
	case ResourceType::mountain:
		texture = TextureType::mountain;
		break;
	case ResourceType::gold:
		texture = TextureType::gold;
		break;
	case ResourceType::oil:
		texture = TextureType::oil;
		break;
	default:
		assert("Wrong building type" && false);
		break;
	}
	assert("Wrong texture" && texture != TextureType::none);
	resource->AddTexture(RRTextureManager::Instance()->GetTexture(texture));
}
 
void ObjectsFactory::SetUnitDirection(Unit* unit) { 
	/*
	удалить, когда будет больше 2-х игроков
	*/
	switch (unit->GetOwner())
	{
	case 1:
		unit->SetDirection(Direction::right);
		break;
	case 2:
		unit->SetDirection(Direction::left);
		break;
	}
}

void ObjectsFactory::MakeBuilding(const Vector2& position, Player* master, BuildingType buildingType) {
	Building* building;
	// создаётся здание в соответствии с его типом
	switch (buildingType)
	{
	case BuildingType::factory:
		building = new Factory(position);
		break;
	case BuildingType::house:
		building = new House(position);
		break;
	case BuildingType::spaceport:
		building = new Spaceport(position);
		break; 
	default:
		building = nullptr; // быть того не может, но всё же
		break;
	}
	assert(building != nullptr); 

	// ищем хозяина
	auto iter = std::find(players->begin(), players->end(), master);
	assert(iter != players->end()); // если не нашли, то что-то криво было написано

	// вычисляем номер owner объекта
	auto owner = iter - players->begin();
	owner++; // отсчёт начинается с 1 (пока)
	building->SetOwner(owner);
	building->SetMaster(master);

	// характеристики, зависящие от исследований игрока
	auto researches = master->GetPlayerData()->Researches();

	building->SetMaxHP(researches->GetMaxHP(buildingType));
	building->InitHP();

	building->SetVisibility(researches->GetVisibility(buildingType));

	building->SetMaxMovePoints(researches->GetMaxMovePoints(buildingType));
	building->ResetMovePoints();

	SetBuildingTexture(building);
	building->SetPointsToConstruct(researches->GetPointsToConstructBuilding(buildingType), building);
	// это был новый объект. добавляем его в мир
	world->AddBuilding(building);
}

void ObjectsFactory::MakeUnit(const Vector2& position, Player* master, UnitType unitType) {
	Unit* unit;
	// создаётся юнит в соответствии с типом
	switch (unitType)
	{
	case UnitType::scout:
		unit = new Scout(position);
		break;
	case UnitType::worker:
		unit = new Worker(position);
		break;
	case UnitType::tank:
		unit = new Tank(position);
		break;
	default:
		unit = nullptr;
		break;
	}
	assert(unit != nullptr); // вряд ли такое будет, но всё же

	// ищем хозяина
	auto iter = std::find(players->begin(), players->end(), master);
	assert(iter != players->end());

	// вычисляем его номер
	auto owner = iter - players->begin();
	owner++; // номер здесь начинается с 1
	unit->SetOwner(owner);
	unit->SetMaster(master);

	// характеристики, зависящие от исследований игрока
	auto researches = master->GetPlayerData()->Researches();

	unit->SetMaxHP(researches->GetMaxHP(unitType));
	unit->InitHP();

	unit->SetVisibility(researches->GetVisibility(unitType));

	unit->SetMaxMovePoints(researches->GetMaxMovePoints(unitType));
	unit->ResetMovePoints();

	SetUnitTexture(unit);
	SetUnitDirection(unit); // удалить, когда будет больше 2-х игроков
	unit->InitializeMoving(unit, world);

	// добавляем нового юнита на карту
	world->AddUnit(unit);
}

void ObjectsFactory::MakeUnitAndReplace(Unit* old, UnitType unitType) {
	Player* player = old->GetMaster();
	Vector2 position = old->GetPosition();
	world->RemoveUnitFrom(position);
	MakeUnit(position, player, unitType);
	world->GetUnitAt(position)->SetMovePoints(0);
}