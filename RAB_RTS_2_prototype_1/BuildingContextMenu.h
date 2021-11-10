#pragma once
#include "ResourceContextMenu.h" 
#include "Building.h"

class Player;

class BuildingContextMenu :  public ResourceContextMenu
{ 
public:
	BuildingContextMenu(int height, Building* building, Player* player)  :
		ResourceContextMenu{ height, building->GetPosition(), building->GetMaxHP(), building->GetHP() },
		isMaster{ player == building->GetMaster() }
	{
	}

	virtual ~BuildingContextMenu() {}
protected:
	bool SeeingMaster() const {
		return isMaster;
	}
private:
	bool isMaster;
};

