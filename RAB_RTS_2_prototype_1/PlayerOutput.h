#pragma once 
#include "Vector2.h"
#include "TreasureFields.h"

class GameIO;
class Player;
class RRGamePlay;
struct Level;

/*
�����, ���������� �� ����� �� ����� �����, ��� ����� �����
*/

class PlayerOutput
{
public:
	PlayerOutput(Player* player, RRGamePlay* gameplay);
	  
	// ��������� ���� � ����� ������ ������
	void DrawWorld();

	// ��������� ���������� �������
	void DrawSelectedObject();
	 
	// ���������� �������� � ��������� ������
	void DrawTreasureFields();
private:
	void DrawUnits(int dx, int dy, int size);
	void DrawBuildings(int dx, int dy, int size);
	void DrawResources(int dx, int dy, int size);
	void DrawGround(int dx, int dy, int size);
	 

	Player* player;
	GameIO* gameIO;
	RRGamePlay* gameplay;  
	const Level* level;

	TreasureFields treasureFields;
};

