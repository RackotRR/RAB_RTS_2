#include "RRGamePlay.h" 
#include "TaskMove.h"
#include "Objects.h"
#include "Pathfinder.h"

bool RRGamePlay::Initialize() {
	if (!world) return false;
	world->UpdateChangedCoordinates();
	return true;
}

void RRGamePlay::Shutdown() {
	// *world - ���� ������ ����� ����� � GameEngine
} 

void RRGamePlay::Move(Unit* who, const Vector2& at) {
	// �� ������ ������ �� ��������, ��� ��� ��������� �������� ���������� � ������ 
	ObjectType type = world->CheckPosition(at);
	if (type == ObjectType::ground) { // ������ ����� ���������
		// ������� �������� ���� ����� 
		who->SetTask(new TaskMove(at));
	}
	// ������ � ����� �����������, ���� ��� ����
	else if (type == ObjectType::unit) {
		if (world->GetUnitAt(at)->GetMaster() != who->GetMaster()) // ������� ������ �������
		{
			/*����� �� �����*/
		}
	}
	else if (type == ObjectType::building) {
		Building* building = world->GetBuildingAt(at);
		if (building->GetMaster() == who->GetMaster()) // ������� ������ ������
		{
			// ���� ������ �������� � ������ ������� 
			if (building->GetUnderConstruction() && who->GetType() == UnitType::worker) {
				// ��� ������������� ������� ������ ������ �� �������� ������ �� �������
				auto ground = GetGroundIn(at, 1, world->GetSize()); 
				auto iter = ground.find(who->GetPosition());
				if (iter != ground.end()) { // ���� �� ����� �����, �� ����� ������
					who->SetTask(new TaskBuildProduction{ building->GetType(), building->GetPosition() });
				}
			}
		}
		else {// ������� ������ �������
			/*����� �� ������*/
		}
	}
	// � �� ����� ���������, ���� ��� ��������� 
	/*
	���������, ����� �� �������, ����� ���������. ���� �����, �� MoveToAttack
	���� �� �����, �� Attack
	��� ���� ������� ���������� HasAttack
	*/ 
}

void RRGamePlay::MoveToAttack(Unit* who, const Vector2& at) {

}

void RRGamePlay::Attack(Unit* who, const Vector2& at) {

}

void RRGamePlay::ProductionPhase() {
	for (auto& iter : world->GetLevel()->units)
		iter.second->ProductionPhase();
	for (auto& iter : world->GetLevel()->buildings)
		iter.second->ProductionPhase();
} 
 
 