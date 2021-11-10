#include "Worker.h"
#include "Player.h"
#include "Building.h"
#include "RRGamePlay.h"

Worker::Worker(const Vector2& position) : Unit(position){
	SetType(UnitType::worker); 
}

// установить направление движения (для отрисовки)
void Worker::SetDirection(Direction direction)  {
	switch (direction)
	{
	case Direction::right: // право 
	case Direction::left: // лево
		HasUnitTexture::direction = direction;
		break;
	default:
		break;
	}
}

// получить угол поворота текстуры
double Worker::GetAngle() const  {
	return 0;
}

// отражение текстуры
DrawFlip Worker::GetDrawFlip() const  {
	switch (GetDirection())
	{
	case Direction::left:
		return DrawFlip::horizontal;
	case Direction::right:
	default:
		return DrawFlip::none;
	}
}
 
void Worker::DoCurrentTask(TurnPhase phase) {
	// пытаемся определить тип задачи
	// если это задача общая для юнитов, то перебросить эту задачу в базовый класс Unit
	switch (CurrentTask()->GetType())
	{ 
	case TaskType::build:
		// задача о строительстве здания?
		if (auto buildTask = dynamic_cast<TaskBuild<BuildingType>*>(CurrentTask())) {
			// если строительство ещё не было начато
			if (buildTask->GetPosition() == Vector2::WrongPosition) {
				GetMaster()->Worker_Build(this);
			} 
		}
		// задача о строительстве юнита
		else { // TaskBuild<UnitType>
			GetMaster()->Worker_Become(this);
		} 
		break;
	case TaskType::buildProduction:
		if (phase == TurnPhase::production) // задача выполняется только во время production phase
			SpendMovePointsOnBuilding();
		break;
	default:
		Unit::DoCurrentTask();
		break;
	}
}

void Worker::SpendMovePointsOnBuilding() { 
	auto buildTask = static_cast<TaskBuildProduction*>(CurrentTask());

	assert(buildTask->GetPosition() != Vector2::WrongPosition);

	// здание уже должно там стоять, его нужно только достроить
	Building* building = GetMaster()->GetRRGamePlay()->GetWorld()->GetBuildingAt(buildTask->GetPosition());

	// сколько очков нужно потратить, чтобы достроить
	int toConstruct = building->GetUnderConstruction();
	if (toConstruct > 0) { // здание не достроено
		if (TryToSpendMovePoints(toConstruct)) { // пытаемся построить полностью
			building->Construct(toConstruct); // если получилось, то меняем состояние здания
			FinishCurrentTask(); // завершаем задачу
		}
		else { // если не получится построить полностью
			building->Construct(GetMovePoints()); // то строим столько, сколько можем
			TryToSpendMovePoints(GetMovePoints()); 
		}
	}
	else {
		// если здание достроено, то завершаем задачу
		FinishCurrentTask();
	}

}