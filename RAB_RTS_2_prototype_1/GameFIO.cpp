#include <cassert> 

#include "GameFIO.h" 
#include "Objects.h"

using std::ofstream;
using std::ifstream;
using std::endl;

void GameFIO::Save(string path, const World* world) {
	ofstream stream;
	stream.open(path, std::ios_base::binary);

	// ссылка на данные внутри мира
	const Level& level = *(world->GetLevel());

	// информаци€ о карте в целом
	stream << level.name << endl; // название
	stream << level.description << endl; // описание
	stream << level.playersNum << endl; // кол-во игроков
	stream << level.size.X << endl << level.size.X << endl; // размеры

	// ground
	for (int y{}; y < level.size.Y; ++y) {
		for (int x{}; x < level.size.X; ++x) {
			// типы хран€тс€ в виде чисел
			stream << static_cast<int>(level.ground(x, y).GetType()) << endl;
		}
	}

	// resources
	stream << level.resources.size() << endl; // кол-во ресурсов на карте
	for (auto& iter : level.resources) {
		stream << static_cast<int>(iter.second->GetType()) << endl; // тип
		stream << iter.second->GetPosition().X << endl << iter.second->GetPosition().Y << endl; // координата
		stream << iter.second->GetMaxValue() << endl << iter.second->GetValue() << endl; // объЄм
	}

	// units
	stream << level.units.size() << endl; // кол-во юнитов на карте
	for (auto& iter : level.units) {
		stream << static_cast<int>(iter.second->GetType()) << endl; // тип
		stream << iter.second->GetPosition().X << endl << iter.second->GetPosition().Y << endl; // координата
		stream << iter.second->GetOwner() << endl; // номер хоз€ина
		stream << iter.second->GetMaxHP() << endl; // макс. здоровье
		stream << iter.second->GetHP() << endl; // текущее здоровье
		// attack
		// speed
		// cost
		// task 
	}

	stream << level.buildings.size() << endl; // кол-во зданий на карте
	for (auto& iter : level.buildings) {
		stream << static_cast<int>(iter.second->GetType()) << endl; // тип
		stream << iter.second->GetPosition().X << endl << iter.second->GetPosition().Y << endl; // координата
		stream << iter.second->GetOwner() << endl; // номер хоз€ина
		stream << iter.second->GetMaxHP() << endl; // макс. здоровье
		stream << iter.second->GetHP() << endl; // текущее здоровье
	}

	// TODO:
	// researches

	// opened map

	// player's resources

	// space
}
 
World* GameFIO::Load(string path) {
	ifstream stream;
	stream.open(path, std::ios_base::binary);
	
	if (!stream.is_open()) { // если не удалось открыть файл
		std::ofstream stream("Log.txt"); // информаци€ заноситс€ в Log.txt
		stream << "Can't opent file: " << path << std::endl;
		stream.close(); 
		return nullptr; // возвращает nullptr при ошибке
	}
	 
	// параметры дл€ создани€ шаблона уровн€
	int width, height, playersNum;
	std::string name, description; 

	std::getline(stream, name);
	std::getline(stream, description); 
	stream >> playersNum;
	stream >> width >> height;
	 
	// создаЄм шаблон, после чего заполн€ем реальными данными
	Level level{ width, height, playersNum }; // данные о мире
	level.name = std::move(name);
	level.description = std::move(description);

	// ground 

	for (size_t y{}; y < height; ++y) {
		for (size_t x{}; x < width; ++x) {
			int a = 0;
			stream >> a;
			level.ground(x, y).SetType(static_cast<GroundType>(a)); // дл€ каждой клетки устанавливаетс€ еЄ тип
		}
	}

	// resources
	LoadResources(stream, level);
	  
	// units
	LoadUnits(stream, level);

	//buildings
	LoadBuildings(stream, level);


	/*
	player treasures и тому подобное
	*/
	// временно:
	PlayerData* ptr = new PlayerData(level.size.X, level.size.Y);
	ptr->Treasures()->AddGold(100);
	ptr->Treasures()->AddBuildingRes(100);
	ptr->Treasures()->AddFuel(100);
	auto researches = ptr->Researches();
	researches->SetMaxHP(UnitType::scout, 5);
	researches->SetMaxHP(UnitType::worker, 4);
	researches->SetMaxHP(UnitType::tank, 10);
	researches->SetMaxHP(BuildingType::factory, 15);
	researches->SetMaxHP(BuildingType::house, 10);
	researches->SetMaxHP(BuildingType::spaceport, 20);
	researches->SetVisibility(UnitType::scout, 4);
	researches->SetVisibility(UnitType::worker, 3);
	researches->SetVisibility(UnitType::tank, 2);
	researches->SetVisibility(BuildingType::factory, 2);
	researches->SetVisibility(BuildingType::house, 2);
	researches->SetVisibility(BuildingType::spaceport, 2);
	researches->SetMaxMovePoints(UnitType::scout, 7);
	researches->SetMaxMovePoints(UnitType::worker, 4);
	researches->SetMaxMovePoints(UnitType::tank, 4);
	researches->SetMaxMovePoints(BuildingType::factory, 3);
	researches->SetMaxMovePoints(BuildingType::house, 3);
	researches->SetMaxMovePoints(BuildingType::spaceport, 3);
	researches->SetPrice(UnitType::scout, {1, 3, 1});
	researches->SetPrice(UnitType::worker, {0, 2, 0});
	researches->SetPrice(UnitType::tank, {3, 3, 5});
	researches->SetPrice(BuildingType::factory, {2, 2, 0});
	researches->SetPrice(BuildingType::house, {2, 0, 0});
	researches->SetPrice(BuildingType::spaceport, {5, 10, 5});   
	researches->SetPointsToConstructBuilding(BuildingType::factory, researches->GetMaxHP(BuildingType::factory));
	researches->SetPointsToConstructBuilding(BuildingType::house, researches->GetMaxHP(BuildingType::house));
	researches->SetPointsToConstructBuilding(BuildingType::spaceport, researches->GetMaxHP(BuildingType::spaceport));
	researches->SetPointsToProduceUnit(UnitType::scout, researches->GetMaxHP(UnitType::scout));
	researches->SetPointsToProduceUnit(UnitType::tank, researches->GetMaxHP(UnitType::tank));
	researches->SetPointsToProduceUnit(UnitType::worker, researches->GetMaxHP(UnitType::worker));
	level.playersData.push_back(ptr);

	ptr = new PlayerData(level.size.X, level.size.Y);
	ptr->Treasures()->AddGold(50);
	ptr->Treasures()->AddBuildingRes(50);
	ptr->Treasures()->AddFuel(50);
	researches = ptr->Researches();
	researches->SetMaxHP(UnitType::scout, 5);
	researches->SetMaxHP(UnitType::worker, 4);
	researches->SetMaxHP(UnitType::tank, 10);
	researches->SetMaxHP(BuildingType::factory, 15);
	researches->SetMaxHP(BuildingType::house, 10);
	researches->SetMaxHP(BuildingType::spaceport, 20);
	researches->SetVisibility(UnitType::scout, 4);
	researches->SetVisibility(UnitType::worker, 3);
	researches->SetVisibility(UnitType::tank, 2);
	researches->SetVisibility(BuildingType::factory, 2);
	researches->SetVisibility(BuildingType::house, 2);
	researches->SetVisibility(BuildingType::spaceport, 2);
	researches->SetMaxMovePoints(UnitType::scout, 7);
	researches->SetMaxMovePoints(UnitType::worker, 4);
	researches->SetMaxMovePoints(UnitType::tank, 4);
	researches->SetMaxMovePoints(BuildingType::factory, 3);
	researches->SetMaxMovePoints(BuildingType::house, 3);
	researches->SetMaxMovePoints(BuildingType::spaceport, 3);
	researches->SetPrice(UnitType::scout, { 1, 3, 1 });
	researches->SetPrice(UnitType::worker, { 0, 2, 0 });
	researches->SetPrice(UnitType::tank, { 3, 3, 5 });
	researches->SetPrice(BuildingType::factory, { 2, 2, 0 });
	researches->SetPrice(BuildingType::house, { 2, 0, 0 });
	researches->SetPrice(BuildingType::spaceport, { 5, 10, 5 });
	researches->SetPointsToConstructBuilding(BuildingType::factory, researches->GetMaxHP(BuildingType::factory));
	researches->SetPointsToConstructBuilding(BuildingType::house, researches->GetMaxHP(BuildingType::house));
	researches->SetPointsToConstructBuilding(BuildingType::spaceport, researches->GetMaxHP(BuildingType::spaceport));
	researches->SetPointsToProduceUnit(UnitType::scout, researches->GetMaxHP(UnitType::scout));
	researches->SetPointsToProduceUnit(UnitType::tank, researches->GetMaxHP(UnitType::tank));
	researches->SetPointsToProduceUnit(UnitType::worker, researches->GetMaxHP(UnitType::worker));
	level.playersData.push_back(ptr);
	 
	return new World(std::move(level)); // выдел€ет пам€ть дл€ мира (освобождаетс€ где-то в другом месте)
}
 
void GameFIO::LoadUnits(ifstream& stream, Level& level) {
	int size = 0;
	stream >> size;
	level.units.reserve(size); // кол-во юнитов
	for (int i = 0; i < size; i++) { 
		int a = 0;
		Vector2 v; // координата
		stream >> a;
		UnitType type = static_cast<UnitType>(a); // тип юнита
		stream >> v.X >> v.Y; 

		Unit* unit; 
		switch (type) // в зависимости от типа, будет создан нужный объект
		{
		case UnitType::worker:
			unit = new Worker(v); 
			break;
		case UnitType::scout:
			unit = new Scout(v);
			break;
		case UnitType::tank:
			unit = new Tank(v);
			break;
		default:
			continue;
			assert(false);
		}

		// записываютс€ данные в этот объект
		stream >> a;
		unit->SetOwner(a);
		stream >> a;
		//unit->SetMaxHP(a);
		stream >> a;
		//unit->SetHP(a);
		/*
			остальные данные дл€ юнитов
		*/
		level.units[v] = unit; // объект сохран€етс€
	}

}

void GameFIO::LoadBuildings(ifstream& stream, Level& level) {
	int size = 0;
	stream >> size;
	level.buildings.reserve(size); // кол-во зданий
	for (int i = 0; i < size; i++){
		int a = 0;
		Vector2 v; // координата
		stream >> a;
		BuildingType type = static_cast<BuildingType>(a); // тип
		stream >> v.X >> v.Y;

		Building* building;
		switch (type) // создаЄтс€ нужный объект в зависимости от типа
		{
		case BuildingType::factory: 
			building = new Factory(v);
			break;
		case BuildingType::house:
			building = new House(v);
			break;
		case BuildingType::spaceport:
			building = new Spaceport(v);
			break; 
		default:
			continue;
		}

		// заполн€етс€ остальна€ информаци€
		stream >> a;
		building->SetOwner(a);
		stream >> a;
		//building->SetMaxHP(a);
		stream >> a;
		//building->SetHP(a);
		/*
			остальные данные дл€ зданий
		*/
		level.buildings[v] = building; // здание сохран€етс€ 
	}
}

void GameFIO::LoadResources(ifstream& stream, Level& level) {
	int size = 0;
	stream >> size;
	level.resources.reserve(size); // кол-во ресурсов
	for (int i = 0; i < size; i++) {
		int a = 0;
		int maxValue, value; // объЄм
		Vector2 v; // координата

		stream >> a;
		ResourceType type = static_cast<ResourceType>(a); // тип
		stream >> v.X >> v.Y;
		stream >> maxValue >> value;

		level.resources[v] = new Resource(v, value, maxValue, type); // создаЄтс€ и сохран€етс€ загруженный ресурс
	}
}