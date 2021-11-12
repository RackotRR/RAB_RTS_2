#pragma once
#include "PlayerTreasures.h"
#include "PlayerResearches.h"
#include "Array2D.h"

class PlayerData
{
public:
	PlayerData(int width, int height); 
	~PlayerData();

	PlayerTreasures* Treasures();
	PlayerResearches* Researches();

	Array2D<bool>& Visibility();  
private:
	PlayerResearches* researches;// ������������
	PlayerTreasures* treasures;  // ������� ������
	Array2D<bool> visibility;	 // ����� ������
};

