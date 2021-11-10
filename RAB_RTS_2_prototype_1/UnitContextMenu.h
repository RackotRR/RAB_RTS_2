#pragma once
#include "ResourceContextMenu.h"
#include "Unit.h"

class Player;

class UnitContextMenu : public ResourceContextMenu
{
public:
	UnitContextMenu(int height, Unit* unit, Player* player) :
		ResourceContextMenu{ height, unit->GetPosition(), unit->GetMaxHP(), unit->GetHP() },
		isMaster{ unit->GetMaster() == player }
	{

	}

	virtual ~UnitContextMenu() {}
protected:
	bool SeeingMaster() const{
		return isMaster;
	}
private:
	bool isMaster;
};

