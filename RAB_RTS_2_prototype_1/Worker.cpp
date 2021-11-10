#include "Worker.h"
#include "Player.h"
#include "Building.h"
#include "RRGamePlay.h"

Worker::Worker(const Vector2& position) : Unit(position){
	SetType(UnitType::worker); 
}

// ���������� ����������� �������� (��� ���������)
void Worker::SetDirection(Direction direction)  {
	switch (direction)
	{
	case Direction::right: // ����� 
	case Direction::left: // ����
		HasUnitTexture::direction = direction;
		break;
	default:
		break;
	}
}

// �������� ���� �������� ��������
double Worker::GetAngle() const  {
	return 0;
}

// ��������� ��������
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
	// �������� ���������� ��� ������
	// ���� ��� ������ ����� ��� ������, �� ����������� ��� ������ � ������� ����� Unit
	switch (CurrentTask()->GetType())
	{ 
	case TaskType::build:
		// ������ � ������������� ������?
		if (auto buildTask = dynamic_cast<TaskBuild<BuildingType>*>(CurrentTask())) {
			// ���� ������������� ��� �� ���� ������
			if (buildTask->GetPosition() == Vector2::WrongPosition) {
				GetMaster()->Worker_Build(this);
			} 
		}
		// ������ � ������������� �����
		else { // TaskBuild<UnitType>
			GetMaster()->Worker_Become(this);
		} 
		break;
	case TaskType::buildProduction:
		if (phase == TurnPhase::production) // ������ ����������� ������ �� ����� production phase
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

	// ������ ��� ������ ��� ������, ��� ����� ������ ���������
	Building* building = GetMaster()->GetRRGamePlay()->GetWorld()->GetBuildingAt(buildTask->GetPosition());

	// ������� ����� ����� ���������, ����� ���������
	int toConstruct = building->GetUnderConstruction();
	if (toConstruct > 0) { // ������ �� ���������
		if (TryToSpendMovePoints(toConstruct)) { // �������� ��������� ���������
			building->Construct(toConstruct); // ���� ����������, �� ������ ��������� ������
			FinishCurrentTask(); // ��������� ������
		}
		else { // ���� �� ��������� ��������� ���������
			building->Construct(GetMovePoints()); // �� ������ �������, ������� �����
			TryToSpendMovePoints(GetMovePoints()); 
		}
	}
	else {
		// ���� ������ ���������, �� ��������� ������
		FinishCurrentTask();
	}

}