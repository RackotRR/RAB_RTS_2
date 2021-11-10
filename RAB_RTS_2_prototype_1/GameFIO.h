#pragma once
#include <string> 
#include "World.h" 
#include <fstream>

using std::string;
using std::ifstream;

/*
Класс, отвечающий за сохранение и загрузку данных об уровне.
Новые карты и сохранения записываются, хранятся и считываются одинаково
*/
class GameFIO
{
public: 
	GameFIO() = delete;
	// сохранить мир в файле path
	static void Save(string path, const World* world); 

	// загрузить мир. возвращает nullptr в случае неудачи
	// требуется удалить World* после завершения работы с ним
	static World* Load(string path);

private:
	static void LoadUnits(ifstream& stream, Level& level);
	static void LoadBuildings(ifstream& stream, Level& level);
	static void LoadResources(ifstream& stream, Level& level);
};

