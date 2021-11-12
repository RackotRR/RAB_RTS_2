#include <cassert> 

#include "House.h"
#include "TaskProduce.h"
#include "UnitType.h"
#include "Player.h"

class Worker;

House::House(const Vector2& position) :
	Building{ position }
{
	SetType(BuildingType::house);
}

// попытатьс€ выполнить текущую задачу 
void House::DoCurrentTask(TurnPhase phase) {
	switch (CurrentTask()->GetType())
	{
	case TaskType::produceStart: 
		if (auto taskProduceStart = dynamic_cast<TaskProduceStart<Worker>*>(CurrentTask())) {
			GetMaster()->House_Produce(this);
		}
		else {
			assert("House must produce only workers!" && false);
		}
		break;
	case TaskType::produce:
		// задача выполн€етс€ только во врем€ production phase
		if (phase != TurnPhase::production) return;

		// пытаемс€ пон€ть, о чЄм текуща€ задача. если это производство юнитов
		if (auto taskProduce = dynamic_cast<TaskProduce<Worker>*>(CurrentTask())) {
			// и нужно произвести рабочего, то ќ  

			// если хватает move points на выполнение задачи, то тратим столько, сколько нужно
			if (TryToSpendMovePoints(taskProduce->GetValueToProduce())) {
				// и выполн€ем еЄ
				// spawn worker 
				FinishCurrentTask();
			}
			else { // если не хватает, то тратим столько, сколько есть
				TryToSpendMovePoints(GetMovePoints());
				taskProduce->Produce(GetMovePoints());
			}
		}
		break;
	default:
		Building::DoCurrentTask();
		break;
	}
}