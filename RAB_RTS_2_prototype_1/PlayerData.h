#pragma once
#include "PlayerTreasures.h"
#include "PlayerResearches.h"

class PlayerData
{
public:
	PlayerData(int width, int height);

	~PlayerData();

	PlayerTreasures* Treasures();
	PlayerResearches* Researches();

	bool** Visibility(int* width = nullptr, int* height = nullptr);

private:
	PlayerResearches* researches;
	PlayerTreasures* treasures;
	bool** visibility;
	int height, width;
};

