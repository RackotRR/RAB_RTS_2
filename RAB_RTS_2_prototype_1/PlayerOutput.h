#pragma once 
#include "Vector2.h"
#include "TreasureFields.h"

class GameIO;
class Player;
class RRGamePlay;
struct Level;

/*
Класс, отвечающий за вывод на экран всего, что видит игрок
*/

class PlayerOutput
{
public:
	PlayerOutput(Player* player, RRGamePlay* gameplay, Vector2 levelSize);
	  
	// отрисовка мира с точки зрения игрока
	void DrawWorld();

	// выделение выбранного объекта
	void DrawSelectedObject();
	 
	// нарисовать таблички с ресурсами игрока
	void DrawTreasureFields();
private:
	void DrawUnits(const Level* level, int dx, int dy, int size);
	void DrawBuildings(const Level* level, int dx, int dy, int size);
	void DrawResources(const Level* level, int dx, int dy, int size);
	void DrawGround(const Level* level, int dx, int dy, int size);
	 

	Player* player;
	GameIO* gameIO;
	RRGamePlay* gameplay; 
	Vector2 levelSize;

	TreasureFields treasureFields;
};

