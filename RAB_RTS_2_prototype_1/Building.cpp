#include "Building.h"

Building::Building(const Vector2& position) : 
	Actor{ position },  
	type{ BuildingType::none } 
{ 

}

Building:: ~Building() {}

// проверка типа времени выполнения
BuildingType Building::GetType() const {
	return type;
}

void Building::SetType(BuildingType type) {
	this->type = type;
}
 
void Building::ProductionPhase() {
	DoCurrentTask(TurnPhase::production);
	ResetMovePoints();
}