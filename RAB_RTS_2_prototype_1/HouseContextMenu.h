#pragma once 
#include "BuildingContextMenu.h"
#include <vector>
#include "Circle.h"

class House;

class HouseContextMenu : public BuildingContextMenu {
public:
	HouseContextMenu(int height, House* house, Player* player);
	 
private: 
	void SendTask(uint8_t num) override;
	 
	House* house; 
};