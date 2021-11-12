#include "PlayerData.h"

PlayerData::PlayerData(int width, int height) 
	:
	researches{ new PlayerResearches },
	treasures{ new PlayerTreasures },
	visibility{ width, height }
{}

PlayerData::~PlayerData() { 
	// исследования
	delete researches;
	// удаляем ресурсы
	delete treasures;
}

PlayerTreasures* PlayerData::Treasures() {
	return treasures;
}

Array2D<bool>& PlayerData::Visibility() {
	return visibility;
}

PlayerResearches* PlayerData::Researches() {
	return researches;
}