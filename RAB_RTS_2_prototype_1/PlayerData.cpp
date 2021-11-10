#include "PlayerData.h"

PlayerData::PlayerData(int width, int height) : width(width), height(height) {
	// ресурсы игрока
	treasures = new PlayerTreasures;
	// исследования
	researches = new PlayerResearches;
	// обзор игрока
	visibility = new bool* [height];
	for (int i = 0; i < height; i++)
		visibility[i] = new bool[width];
}

PlayerData::~PlayerData() {
	// удаляем обзор игрока
	for (int i = 0; i < height; i++)
		delete[] visibility[i];
	delete[] visibility;
	// исследования
	delete researches;
	// удаляем ресурсы
	delete treasures;
}

PlayerTreasures* PlayerData::Treasures() {
	return treasures;
}

bool** PlayerData::Visibility(int* width, int* height) {
	if (width)
		*width = this->width;
	if (height)
		*height = this->height;
	return visibility;
}

PlayerResearches* PlayerData::Researches() {
	return researches;
}