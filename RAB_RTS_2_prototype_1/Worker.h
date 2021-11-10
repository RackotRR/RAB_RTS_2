#pragma once
#include "Unit.h"
#include "TaskBuild.h" 
  
class Worker : public Unit {
public:
	Worker(const Vector2& position);

	// ���������� ����������� �������� (��� ���������)
	void SetDirection(Direction direction) override;

	// �������� ���� �������� ��������
	double GetAngle() const override;

	// ��������� ��������
	DrawFlip GetDrawFlip() const override;

	// ���������� ��������� ������� ������
	void DoCurrentTask(TurnPhase phase = TurnPhase::common) override;
	
private:
	void SpendMovePointsOnBuilding();
};