#pragma once 
class GameIO;
class Player;
class RRGamePlay;
class Level;
/*
�����, ���������� �� ����� �� ����� �����, ��� ����� �����
*/
class PlayerOutput
{
public:
	void Initialize(Player* player, RRGamePlay* gameplay, int width, int height);
	  
	// ��������� ���� � ����� ������ ������
	void DrawWorld();

	// ��������� ���������� �������
	void DrawSelectedObject();
private:
	void DrawUnits(const Level* level, int dx, int dy, int size);
	void DrawBuildings(const Level* level, int dx, int dy, int size);
	void DrawResources(const Level* level, int dx, int dy, int size);
	void DrawGround(const Level* level, int dx, int dy, int size);
	 

	Player* player;
	GameIO* gameIO;
	RRGamePlay* gameplay; 
	int width, height; 
};

