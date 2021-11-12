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

// ���������� ��������� ������� ������ 
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
		// ������ ����������� ������ �� ����� production phase
		if (phase != TurnPhase::production) return;

		// �������� ������, � ��� ������� ������. ���� ��� ������������ ������
		if (auto taskProduce = dynamic_cast<TaskProduce<Worker>*>(CurrentTask())) {
			// � ����� ���������� ��������, �� �� 

			// ���� ������� move points �� ���������� ������, �� ������ �������, ������� �����
			if (TryToSpendMovePoints(taskProduce->GetValueToProduce())) {
				// � ��������� �
				// spawn worker 
				FinishCurrentTask();
			}
			else { // ���� �� �������, �� ������ �������, ������� ����
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