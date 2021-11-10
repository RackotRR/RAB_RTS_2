#include "Unit.h"

Unit::Unit(const Vector2& position) : 
	Actor(position), 
	type(UnitType::none) 
{

}

Unit::~Unit() {}

void Unit::ProductionPhase() {
	DoCurrentTask(TurnPhase::production);
	ResetMovePoints();
}
 
UnitType Unit::GetType() const {
	return type;
}

void Unit::SetType(UnitType type) {
	this->type = type;
}

void Unit::DoCurrentTask(TurnPhase phase) {
	// пытаемся определить тип задачи
	// если это задача общая для юнитов, то перебросить эту задачу в базовый класс HasTask
	switch (CurrentTask()->GetType())
	{
	case TaskType::move:
		Move();
		break;
	default:
		HasTask::DoCurrentTask();
		break;
	} 
}
